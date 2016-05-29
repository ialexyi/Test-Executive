#include "Select_SN_RMA_Module.h"
#include "Select_SN_RMA_Defines.h"

#define		CURRENT_USAGE_OF_EX_PARAMS			2

#define		USER_CLICK_LEFT_BUTTON				1001

int		LoadLastConfiguration (int hVariableHandle);

int		ClearPanelCallbackData( int hPanel );  
int		FillPanelCallbackData( int hPanel , int hHandle );

//==============================================================================
// DLL main entry-point functions

int __stdcall DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            if (InitCVIRTE (hinstDLL, 0, 0) == 0)
                return 0;     /* out of memory */
            break;
        case DLL_PROCESS_DETACH:
            CloseCVIRTE ();
            break;
    }
    
    return 1;
}

int __stdcall DllEntryPoint (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    /* Included for compatibility with Borland */

    return DllMain (hinstDLL, fdwReason, lpvReserved);
}


void* DLLEXPORT PLUG_SerialNumbersSelect ( tuSelectSerialNumberItem *ptConfig , tsSSNRList *pResponds )
{
	STD_ERROR			StdError											=	{0};
	
	CmtTSVHandle		hMainGuiInfo										=	0;
										
	tsMainGuiInfo		*pMainGuiInfo										=	NULL;
	
	int					hPanel												=	0,
						event												=	0,
						panel												=	0,
						control 											=	0;
							
	int					iStatus												=	0;
	
	int					iCurrentRow												=	0,
						iControlID											=	0,
						iControlIndex										=	0,
						iSnMaxNum											=	0,
						iNotEmptyCounter									=	0;
							
	char				szSnNum[16]											=	{0},
						szCtrlConstName[256]								=	{0};
	
	int					iHistorysQuantity									=	0;
							
	char				*pTagName											=	NULL,
						szTagName[256]										=	{0},
						szSN[256]											=	{0},
						szPN[256]											=	{0};
	
	int					iSelectedNumberOfSlots								=	0;
	
	tfSN_Parsing		pfSN_Parsing										=	NULL;
	
	tfAUTO_Selection	pfAUTO_Selection									=	NULL;
		
	int					hSlotHandle											=	0;
	
	HINSTANCE			hSN_Parse_ModuleLibraryHandle						=	0,
						hAUTO_Selection_ModuleLibraryHandle					=	0;             
						
	int					iNumberOfExItems									=	0;
	
	int					index												=	0;
	
	int					bGetMainVariable									=	0;
	
	IF (( ptConfig == NULL ) , "Serial Input panel can't receive NULL pointer." );

	if (( ptConfig->iMaxNumberOfSlots < 1 ) || ( ptConfig->iMaxNumberOfSlots > MAX_SN_NUM ))
		{FORCE_ERR(ERROR_SLOTS_NUM_OUT_OF_RANGE ,"Number of Slots is out of range.");}
	
	//------------- Load Parsing Module --------------------------------------//
	if ( ptConfig->pszSerialNumberParsingModulePath && strlen( ptConfig->pszSerialNumberParsingModulePath ))
		if ( FileExists( ptConfig->pszSerialNumberParsingModulePath , NULL ))
		{
			hSN_Parse_ModuleLibraryHandle = LoadLibrary ( ptConfig->pszSerialNumberParsingModulePath );
			
			if ( hSN_Parse_ModuleLibraryHandle )
			{
				pfSN_Parsing = (tfSN_Parsing)GetProcAddress ( hSN_Parse_ModuleLibraryHandle , "SN_Parsing" );
			
				if ( pfSN_Parsing == NULL )
				{
					FreeLibrary( hSN_Parse_ModuleLibraryHandle );
					hSN_Parse_ModuleLibraryHandle=0;
				}
			}

		}
		
	//------------- Load Auto Selection Module --------------------------------------//
	if ( ptConfig->pszAutoSelectionModulePath && strlen( ptConfig->pszAutoSelectionModulePath ))
		if ( FileExists( ptConfig->pszAutoSelectionModulePath , NULL ))
		{
			hAUTO_Selection_ModuleLibraryHandle = LoadLibrary ( ptConfig->pszAutoSelectionModulePath );
			
			if ( hAUTO_Selection_ModuleLibraryHandle )
			{
				pfAUTO_Selection = (tfAUTO_Selection)GetProcAddress ( hAUTO_Selection_ModuleLibraryHandle , "AUTO_Selection" );
			
				if ( pfAUTO_Selection == NULL )
				{
					FreeLibrary( hAUTO_Selection_ModuleLibraryHandle );
					hAUTO_Selection_ModuleLibraryHandle=0;
				}
			}

		}
		
	//------------------------------------------------------------------------------------------------------------------------//
	
	CHK_CMT (CmtNewTSV (sizeof(tsMainGuiInfo), &hMainGuiInfo ));
	
	CHK_CMT (CmtGetTSVPtr (hMainGuiInfo, &pMainGuiInfo ));
	bGetMainVariable = 1;
	
	pMainGuiInfo->fSN_Parsing = pfSN_Parsing;
	pMainGuiInfo->fAUTO_Selection = pfAUTO_Selection;
	pMainGuiInfo->iMaxSnQuantity = ptConfig->iMaxNumberOfSlots;								
	pMainGuiInfo->iActiveSnIndex = 0;
	pMainGuiInfo->iSelectedSnQuantity = 1;
	pMainGuiInfo->SnControlsList = calloc (pMainGuiInfo->iMaxSnQuantity, sizeof(tsSnControl));  // Allocate memory for SnControlsInfo by given max number
	
	for ( index = 0 ; index < pMainGuiInfo->iMaxSnQuantity ; index++ )
	{
		pMainGuiInfo->SnControlsList[index].extraParameters.iNumberOfItems = iNumberOfExItems;
		FREE_CALLOC( pMainGuiInfo->SnControlsList[index].extraParameters.pList , iNumberOfExItems , sizeof(tsExtraItem)); 
	}
		
	if (pMainGuiInfo->SnControlsList == NULL)
		{STD_ERR (ERROR_OUTOFMEMORY);}
	
	pMainGuiInfo->hPanelHandle = LoadPanelEx ( 0 , "Select_SN_RMA_Module.uir" , PANEL , __CVIUserHInst );
	
	if (pMainGuiInfo->hPanelHandle < 0)
		{FORCE_ERR(ERROR_CREATE_HANDLE ,"Can't load SelectSN GUI panel.");} 
	
	hPanel = pMainGuiInfo->hPanelHandle;		//Local store
	iSnMaxNum = pMainGuiInfo->iMaxSnQuantity;   //Local store
	
	GetPanelAttribute (hPanel, ATTR_PANEL_FIRST_CTRL, &iControlID);
	
	/* store control GUI ID for usefull controls */
	while (iControlID)
	{
		GetCtrlAttribute (hPanel, iControlID , ATTR_CONSTANT_NAME, szCtrlConstName);
		
		if (strstr(szCtrlConstName, "SERIAL_") != NULL)
		{
			sscanf(szCtrlConstName, "SERIAL_%d", &iControlIndex);
			
			if (iControlIndex <= iSnMaxNum)
				pMainGuiInfo->SnControlsList[iControlIndex-1].sn_contorlID = iControlID;
		}
		
		if (strstr(szCtrlConstName, "PART_") != NULL)
		{
			sscanf(szCtrlConstName, "PART_%d", &iControlIndex);
			
			if (iControlIndex <= iSnMaxNum)
				pMainGuiInfo->SnControlsList[iControlIndex-1].pn_contorlID = iControlID;
		}
		
		if (strstr(szCtrlConstName, "RING_SN") != NULL)
		{
			sscanf(szCtrlConstName, "RING_SN_%d", &iControlIndex);
			
			if (iControlIndex <= iSnMaxNum)
				pMainGuiInfo->SnControlsList[iControlIndex-1].ring_sn_ID = iControlID;
		}
		
		if (strstr(szCtrlConstName, "RING_PN") != NULL)
		{
			sscanf(szCtrlConstName, "RING_PN_%d", &iControlIndex);
			
			if (iControlIndex <= iSnMaxNum)
				pMainGuiInfo->SnControlsList[iControlIndex-1].ring_pn_ID = iControlID;
		}
		
		if (strstr(szCtrlConstName, "ENABLE_") != NULL)
		{
			sscanf(szCtrlConstName, "ENABLE_%d", &iControlIndex);
			
			if (iControlIndex <= iSnMaxNum)
			{
				pMainGuiInfo->SnControlsList[iControlIndex-1].enableID = iControlID;
				pMainGuiInfo->SnControlsList[iControlIndex-1].bEnableRun = 1;
			}
		}
		
		if (strstr(szCtrlConstName, "RMA_") != NULL)
		{
			sscanf(szCtrlConstName, "RMA_%d", &iControlIndex);
			
			if (iControlIndex <= iSnMaxNum)
			{
				pMainGuiInfo->SnControlsList[iControlIndex-1].rmaID = iControlID;
				pMainGuiInfo->SnControlsList[iControlIndex-1].bRMA = 0;
			}
		}
		
		GetCtrlAttribute (hPanel, iControlID, ATTR_NEXT_CTRL, &iControlID);
	}
	
	GetPanelAttribute (hPanel , ATTR_TOP,&pMainGuiInfo->iPanelTopAttr);
	
	/* load history serial numbers form .ini store */
	pMainGuiInfo->hIniBuffer = Ini_New (0);
	
	if (FileExists (INI_HISTORY_FILE_NAME, 0))
	{
		CHK_INI (Ini_ReadFromFile (pMainGuiInfo->hIniBuffer, INI_HISTORY_FILE_NAME));
		
		if (Ini_SectionExists (pMainGuiInfo->hIniBuffer, INI_SEC_SN_HISTORYS))
		{
			iHistorysQuantity = Ini_NumberOfItems (pMainGuiInfo->hIniBuffer, INI_SEC_SN_HISTORYS);
			
			/* remove over histores */
			if (iHistorysQuantity >= MAX_HISTORY_NUM)
			{
				for (iCurrentRow = 1; iCurrentRow <= (iHistorysQuantity - MAX_HISTORY_NUM); iCurrentRow++)
				{
					Ini_NthItemName (pMainGuiInfo->hIniBuffer, INI_SEC_SN_HISTORYS, 1, &pTagName);
					Ini_RemoveItem (pMainGuiInfo->hIniBuffer, INI_SEC_SN_HISTORYS, pTagName);
				}
				
			
				/* fill the first history ring */
				for (iCurrentRow = 1; iCurrentRow <= iHistorysQuantity; iCurrentRow++)
				{
					if (Ini_NthItemName (pMainGuiInfo->hIniBuffer, INI_SEC_SN_HISTORYS, iCurrentRow, &pTagName ))
					{
						CHK_INI0 (Ini_GetStringIntoBuffer (pMainGuiInfo->hIniBuffer, INI_SEC_SN_HISTORYS, pTagName, szSN, 256));
					
						InsertListItem (hPanel, PANEL_RING_SN_1, iCurrentRow-1, szSN, iCurrentRow);
					}
				}
			}
			
			iHistorysQuantity = Ini_NumberOfItems (pMainGuiInfo->hIniBuffer, INI_SEC_PN_HISTORYS);
			
			if (iHistorysQuantity >= MAX_HISTORY_NUM)  
			{								
				/* remove over histores */  
				for (iCurrentRow = 1; iCurrentRow <= (iHistorysQuantity - MAX_HISTORY_NUM); iCurrentRow++)
				{
					Ini_NthItemName (pMainGuiInfo->hIniBuffer, INI_SEC_PN_HISTORYS, 1, &pTagName);
					Ini_RemoveItem (pMainGuiInfo->hIniBuffer, INI_SEC_PN_HISTORYS, pTagName);
				}
			
				/* fill the first history ring */  
				for (iCurrentRow = 1; iCurrentRow <= iHistorysQuantity; iCurrentRow++)
				{
					if (Ini_NthItemName (pMainGuiInfo->hIniBuffer, INI_SEC_PN_HISTORYS, iCurrentRow, &pTagName ))
					{
						CHK_INI0 (Ini_GetStringIntoBuffer (pMainGuiInfo->hIniBuffer, INI_SEC_PN_HISTORYS, pTagName, szPN, 256));
					
						InsertListItem (hPanel, PANEL_RING_PN_1, iCurrentRow-1, szPN, iCurrentRow);
					}
				}
			}
		}
	}
	
	CHK_CMT (CmtReleaseTSVPtr (hMainGuiInfo));
	bGetMainVariable = 0;
	
	FillPanelCallbackData( hPanel , hMainGuiInfo ); 
	
	SetCtrlAttribute( hPanel , PANEL_RING_SN_1 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_SN_2 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_SN_3 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_SN_4 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_SN_5 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_SN_6 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_SN_7 , ATTR_DISABLE_CHECK_MARK , 1 );	
	SetCtrlAttribute( hPanel , PANEL_RING_SN_8 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_SN_9 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_SN_10 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_PN_1 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_PN_2 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_PN_3 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_PN_4 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_PN_5 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_PN_6 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_PN_7 , ATTR_DISABLE_CHECK_MARK , 1 );	
	SetCtrlAttribute( hPanel , PANEL_RING_PN_8 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_PN_9 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_PN_10 , ATTR_DISABLE_CHECK_MARK , 1 );
	
	SetCtrlVal( hPanel, PANEL_tbOPERATOR, ptConfig->szOperator );
	
	/* fill values for select_number ring */
	for (iCurrentRow = 0; iCurrentRow < iSnMaxNum; iCurrentRow++)
	{
		sprintf(szSnNum, "%d", iCurrentRow+1);
		InsertListItem (hPanel, PANEL_NUMBER, iCurrentRow, szSnNum, iCurrentRow+1);
	}
	
	SetCtrlIndex (hPanel, PANEL_NUMBER, 0);
	
	if ( ptConfig->bRunLastSnConfig )
	{
		{STD_ERR (LoadLastConfiguration(hMainGuiInfo));}
	
		iStatus == ATTENTION_OK;
	}
	else
	{
		clbNumber (hPanel, PANEL_NUMBER, EVENT_COMMIT, &hMainGuiInfo, 0, 0);  
		
		InstallPopup (hPanel);  
		
		do
		{
			MakeApplicationActive ();
			SetActivePanel ( hPanel );
			ProcessDrawEvents();
		
			event = GetUserEvent ( 1 , &panel , &control );   
		
			if ( panel != hPanel )
				continue;
		
			if  ( control == PANEL_OK_BUTTON )
			{
				if (( iStatus == ATTENTION_OK ) && ( event == USER_CLICK_LEFT_BUTTON ))
					break;
				
				CHK_CMT (CmtGetTSVPtr (hMainGuiInfo, &pMainGuiInfo )); 
				bGetMainVariable = 1;
				
				iNotEmptyCounter = 0;
				
				for (iCurrentRow = 0; iCurrentRow < pMainGuiInfo->iSelectedSnQuantity; iCurrentRow++) 
				{
					GetCtrlVal( pMainGuiInfo->hPanelHandle , pMainGuiInfo->SnControlsList[iCurrentRow].enableID , &(pMainGuiInfo->SnControlsList[iCurrentRow].bEnableRun) );
					
					if ( pMainGuiInfo->SnControlsList[iCurrentRow].bEnableRun == 0 )
					{
						iNotEmptyCounter++; 
					}
					else
					{
						if ( (pMainGuiInfo->SnControlsList[iCurrentRow].pszPartNumber == NULL ) || ( strlen(pMainGuiInfo->SnControlsList[iCurrentRow].pszPartNumber) == 0 ))
						{
							SetActiveCtrl( pMainGuiInfo->hPanelHandle , pMainGuiInfo->SnControlsList[iCurrentRow].pn_contorlID );
							break;	
						}
						
						if ( (pMainGuiInfo->SnControlsList[iCurrentRow].pszSerialNumber == NULL ) || ( strlen(pMainGuiInfo->SnControlsList[iCurrentRow].pszSerialNumber) == 0 ))
						{
							SetActiveCtrl( pMainGuiInfo->hPanelHandle , pMainGuiInfo->SnControlsList[iCurrentRow].sn_contorlID );
							break;
						}
						
						iNotEmptyCounter++;
					}
				}
				
				CHK_CMT (CmtReleaseTSVPtr (hMainGuiInfo));
				bGetMainVariable = 0;
					
				if ( iNotEmptyCounter == pMainGuiInfo->iSelectedSnQuantity )
				{
					iStatus = ATTENTION_OK;
					
					if ( ptConfig->bAutoContinue )
						break;
					
					if ( event == USER_CLICK_LEFT_BUTTON )
						break;
				}
				else
					iStatus = 0;
			}
			
		}while (!(( control == PANEL_CANCEL_BUTTON ) && ( event == EVENT_COMMIT )));
			
	}
	
	if (iStatus == ATTENTION_OK)
	{
		CHK_CMT (CmtGetTSVPtr (hMainGuiInfo, &pMainGuiInfo ));
		bGetMainVariable = 1;
		
		Ini_RemoveSection (pMainGuiInfo->hIniBuffer, INI_SEC_LAST_CONFIG);
		
		CHK_INI (Ini_PutInt (pMainGuiInfo->hIniBuffer, INI_SEC_LAST_CONFIG, "selected_quantity", pMainGuiInfo->iSelectedSnQuantity));
		
		iSelectedNumberOfSlots = pMainGuiInfo->iSelectedSnQuantity; 
		
		pResponds->iNumberOfSlots = iSelectedNumberOfSlots;
		
		if ( pResponds->pSelect == NULL )
		{
			CALLOC_ERR( pResponds->pSelect , iSelectedNumberOfSlots , sizeof(tsSSNRItem));
		}
				
		for (iCurrentRow = 0; iCurrentRow < pMainGuiInfo->iSelectedSnQuantity; iCurrentRow++)
		{	
			sprintf (szTagName, "sn_%d", iCurrentRow);
			
			if ( pMainGuiInfo->SnControlsList[iCurrentRow].pszSerialNumber )
				CHK_INI (Ini_PutString (pMainGuiInfo->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, pMainGuiInfo->SnControlsList[iCurrentRow].pszSerialNumber));
			
			sprintf (szTagName, "pn_%d", iCurrentRow);
			if ( pMainGuiInfo->SnControlsList[iCurrentRow].pszPartNumber )
				CHK_INI (Ini_PutString (pMainGuiInfo->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, pMainGuiInfo->SnControlsList[iCurrentRow].pszPartNumber));
			
			sprintf (szTagName, "note_%d", iCurrentRow);
			
			if ( pMainGuiInfo->SnControlsList[iCurrentRow].pszNote )
				CHK_INI (Ini_PutString (pMainGuiInfo->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, pMainGuiInfo->SnControlsList[iCurrentRow].pszNote));
			
			sprintf (szTagName, "enable_%d", iCurrentRow);
			CHK_INI (Ini_PutUInt (pMainGuiInfo->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, pMainGuiInfo->SnControlsList[iCurrentRow].bEnableRun));
			
			sprintf (szTagName, "rma_%d", iCurrentRow);
			CHK_INI (Ini_PutUInt (pMainGuiInfo->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, pMainGuiInfo->SnControlsList[iCurrentRow].bRMA ));
			
			sprintf (szTagName, "rma_number_%d", iCurrentRow);
			CHK_INI (Ini_PutString (pMainGuiInfo->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, pMainGuiInfo->SnControlsList[iCurrentRow].szRMANumber )); 
			
			sprintf (szTagName, "work_number_%d", iCurrentRow);
			CHK_INI (Ini_PutString (pMainGuiInfo->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, pMainGuiInfo->SnControlsList[iCurrentRow].szWorkNumber )); 
			
			sprintf (szTagName, "auto_sel_uut_%d", iCurrentRow);
			CHK_INI (Ini_PutUInt (pMainGuiInfo->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, pMainGuiInfo->SnControlsList[iCurrentRow].iAutoSelect_UUT_Index));

			sprintf (szTagName, "auto_sel_ver_%d", iCurrentRow);
			CHK_INI (Ini_PutUInt (pMainGuiInfo->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, pMainGuiInfo->SnControlsList[iCurrentRow].iAutoSelect_Verion_Index));

			pResponds->pSelect[iCurrentRow].tExtraList = pMainGuiInfo->SnControlsList[iCurrentRow].extraParameters;
			pResponds->pSelect[iCurrentRow].pSerialNumber = pMainGuiInfo->SnControlsList[iCurrentRow].pszSerialNumber;
			pResponds->pSelect[iCurrentRow].pPartNumber = pMainGuiInfo->SnControlsList[iCurrentRow].pszPartNumber;
			pResponds->pSelect[iCurrentRow].pNote = pMainGuiInfo->SnControlsList[iCurrentRow].pszNote;
			pResponds->pSelect[iCurrentRow].bRunEnable = pMainGuiInfo->SnControlsList[iCurrentRow].bEnableRun;
			//pResponds->pSelect[iCurrentRow].iAutoSelect_UUT_Index = pMainGuiInfo->iAutoSelect_UUT_Index;
			//pResponds->pSelect[iCurrentRow].iAutoSelect_Verion_Index = pMainGuiInfo->iAutoSelect_Verion_Index;
			//pResponds->pSelect[iCurrentRow].piAutoSelect_ExtraData = pMainGuiInfo->piAutoSelect_ExtraData;
			//pResponds->pSelect[iCurrentRow].iAutoSelect_ExtraDataLength = pMainGuiInfo->iAutoSelect_ExtraDataLength;
			
			for ( index = 0 ; index < pMainGuiInfo->SnControlsList[iCurrentRow].extraParameters.iNumberOfItems ; index++ )
			{
				if ( pMainGuiInfo->SnControlsList[iCurrentRow].extraParameters.pList[index].pszParameter )
				{
					sprintf (szTagName, "ex_param_%d_%d", iCurrentRow+1 , index+1);
					CHK_INI (Ini_PutString (pMainGuiInfo->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, pMainGuiInfo->SnControlsList[iCurrentRow].extraParameters.pList[index].pszParameter));
				}
			}
				
			CHK_CMT (CmtReleaseTSVPtr ( hSlotHandle ));
		}
		
		CHK_CMT (CmtReleaseTSVPtr (hMainGuiInfo));
		bGetMainVariable = 0;
	}
	else if (iStatus != ATTENTION_CANCEL)
		{FORCE_ERR(ERROR_GUI_SN ,"SN selection GUI error..");}
	
Error:
	
	if (hMainGuiInfo)
	{
		if ( bGetMainVariable == 0 )
			CmtGetTSVPtr (hMainGuiInfo, &pMainGuiInfo );
		
		if (pMainGuiInfo->hIniBuffer)
		{
			Ini_WriteToFile (pMainGuiInfo->hIniBuffer, INI_HISTORY_FILE_NAME);
			Ini_Dispose (pMainGuiInfo->hIniBuffer);
		}
		
		FREE (pMainGuiInfo->SnControlsList);
		
		CmtReleaseTSVPtr (hMainGuiInfo);
		CmtDiscardTSV (hMainGuiInfo);
	}
	
	if ( hSN_Parse_ModuleLibraryHandle )
		FreeLibrary( hSN_Parse_ModuleLibraryHandle ); 
	
	if ( hAUTO_Selection_ModuleLibraryHandle )
		FreeLibrary( hAUTO_Selection_ModuleLibraryHandle ); 

	if (hPanel)
	{
		ClearPanelCallbackData(hPanel);
		RemovePopup (0);
		DiscardPanel (hPanel);
	}
	
	FREE(ptConfig->pszSerialNumberParsingModulePath );
	FREE(ptConfig->pszAutoSelectionModulePath );
	FREE(ptConfig->szOperator);
	FREE(ptConfig);
		
	return NULL;
}


int CVICALLBACK panelCB (int panel, int event, void *callbackData , int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
	}
	return 0;
}


int CVICALLBACK clbInputCtrl (int panel, int control, int event , void *callbackData, int eventData1, int eventData2)
{
	int					*pTemp					=	0, 
						hVariableHandle			=	0;
			
	tsMainGuiInfo		*pVariable				=	NULL;
	
	int					iCurrentRow				=	0,
						bSN_HistoryChange		=	0,
						bPN_HistoryChange		=	0,
						iHistoryCount			=	0,
						iHistorysQuantity		=	0;
	
	int					iStringLength			=	0;
	
	char				*pTagName				=	NULL,
						szSN[256]				=	{0},
						szPN[256]				=	{0};

	tfSN_Parsing		pfSN_Parsing			=	NULL; 
	
	tfAUTO_Selection	pfAUTO_Selection		=	NULL;
	
	if ( callbackData == NULL )
		return 0;
	
	if (event)
	{
		pTemp = (int*) callbackData;
		hVariableHandle = *pTemp;

		if ( CmtGetTSVPtr ( hVariableHandle , &pVariable ) != 0 )
			return 0;
			
		pfSN_Parsing = pVariable->fSN_Parsing; 
			
		pfAUTO_Selection = pVariable->fAUTO_Selection; 
		
		switch (event)
		{
			case EVENT_COMMIT:
				
				/* find the changed control */
				for (iCurrentRow = 0; iCurrentRow < pVariable->iSelectedSnQuantity; iCurrentRow++)
					if (( pVariable->SnControlsList[iCurrentRow].sn_contorlID == control ) | ( pVariable->SnControlsList[iCurrentRow].pn_contorlID == control ))
						break;
					
				if ( iCurrentRow >= pVariable->iSelectedSnQuantity )
					break;
					
				//------------------- Prepare Serial Number --------------------------------------------------//  
				FREE(pVariable->SnControlsList[iCurrentRow].pszSerialNumber);
						
				GetCtrlAttribute( pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].sn_contorlID , ATTR_STRING_TEXT_LENGTH , &iStringLength );
					
				CALLOC( pVariable->SnControlsList[iCurrentRow].pszSerialNumber , (iStringLength + 64) , sizeof(char));
					
				if ( pVariable->SnControlsList[iCurrentRow].pszSerialNumber == NULL )
					return 0;
						
				GetCtrlVal(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].sn_contorlID, pVariable->SnControlsList[iCurrentRow].pszSerialNumber);
				
				//------------------- Prepare Part Number --------------------------------------------------//
				FREE(pVariable->SnControlsList[iCurrentRow].pszPartNumber);
						
				GetCtrlAttribute( pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].pn_contorlID , ATTR_STRING_TEXT_LENGTH , &iStringLength );
					
				CALLOC( pVariable->SnControlsList[iCurrentRow].pszPartNumber , (iStringLength + 64) , sizeof(char));
					
				if ( pVariable->SnControlsList[iCurrentRow].pszPartNumber == NULL )
					return 0;
						
				GetCtrlVal(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].pn_contorlID, pVariable->SnControlsList[iCurrentRow].pszPartNumber);
				
				//------------------------------------------------------------------------------------------//
				GetCtrlVal(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].enableID , &(pVariable->SnControlsList[iCurrentRow].bEnableRun) );
				
				if ( pVariable->SnControlsList[iCurrentRow].sn_contorlID == control )
				{
					if ( pfSN_Parsing )
						if ( pfSN_Parsing( pVariable->SnControlsList[iCurrentRow].pszSerialNumber , CURRENT_USAGE_OF_EX_PARAMS , pVariable->SnControlsList[iCurrentRow].extraParameters ) == 0 )
						{
							SetCtrlVal(pVariable->hPanelHandle, control, pVariable->SnControlsList[iCurrentRow].pszSerialNumber);
																											   
							ProcessDrawEvents();
						}
				}
				
				if ( pfAUTO_Selection )
					pfAUTO_Selection( pVariable->SnControlsList[iCurrentRow].pszPartNumber , pVariable->SnControlsList[iCurrentRow].pszSerialNumber , &(pVariable->SnControlsList[iCurrentRow].iAutoSelect_UUT_Index) , &(pVariable->SnControlsList[iCurrentRow].iAutoSelect_Verion_Index) , &(pVariable->SnControlsList[iCurrentRow].piAutoSelect_ExtraData) , &(pVariable->SnControlsList[iCurrentRow].iAutoSelect_ExtraDataLength) );
				
				if ( pVariable->SnControlsList[iCurrentRow].pszSerialNumber && HasNonWhiteSpace (pVariable->SnControlsList[iCurrentRow].pszSerialNumber))
				{
					/* save new serial number (.ini history) */
					if (!Ini_ItemExists (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS, pVariable->SnControlsList[iCurrentRow].pszSerialNumber))
					{
						if (Ini_NumberOfItems (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS) >= MAX_HISTORY_NUM)
						{
							Ini_NthItemName (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS, 1, &pTagName);
							Ini_RemoveItem (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS, pTagName);
						}
						
						Ini_PutString (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS, pVariable->SnControlsList[iCurrentRow].pszSerialNumber, pVariable->SnControlsList[iCurrentRow].pszSerialNumber);
						bSN_HistoryChange = 1;
					}
				}
				
				if ( pVariable->SnControlsList[iCurrentRow].pszPartNumber && HasNonWhiteSpace (pVariable->SnControlsList[iCurrentRow].pszPartNumber))
				{
					/* save new serial number (.ini history) */
					if (!Ini_ItemExists (pVariable->hIniBuffer, INI_SEC_PN_HISTORYS, pVariable->SnControlsList[iCurrentRow].pszPartNumber))
					{
						if (Ini_NumberOfItems (pVariable->hIniBuffer, INI_SEC_PN_HISTORYS) >= MAX_HISTORY_NUM)
						{
							Ini_NthItemName (pVariable->hIniBuffer, INI_SEC_PN_HISTORYS, 1, &pTagName);
							Ini_RemoveItem (pVariable->hIniBuffer, INI_SEC_PN_HISTORYS, pTagName);
						}
						
						Ini_PutString (pVariable->hIniBuffer, INI_SEC_PN_HISTORYS, pVariable->SnControlsList[iCurrentRow].pszPartNumber, pVariable->SnControlsList[iCurrentRow].pszPartNumber);
						bPN_HistoryChange = 1;
					}
				}
				
				if ( pVariable->SnControlsList[iCurrentRow].pszNote )
					strcpy(pVariable->SnControlsList[iCurrentRow].pszNote, "");
				
				strcpy(pVariable->SnControlsList[iCurrentRow].szRMANumber, "");
				strcpy(pVariable->SnControlsList[iCurrentRow].szWorkNumber, "");
				
				ResetTextBox (pVariable->hPanelHandle, PANEL_NOTE , "");
				
				if ( pVariable->SnControlsList[iCurrentRow].pszNote )
					SetCtrlVal(pVariable->hPanelHandle, PANEL_NOTE, pVariable->SnControlsList[iCurrentRow].pszNote);
				
				ResetTextBox (pVariable->hPanelHandle, PANEL_RMA_NUM , "");
				SetCtrlVal(pVariable->hPanelHandle, PANEL_RMA_NUM, pVariable->SnControlsList[iCurrentRow].szRMANumber);
				
				ResetTextBox (pVariable->hPanelHandle, PANEL_WORK_NUM , "");
				SetCtrlVal(pVariable->hPanelHandle, PANEL_WORK_NUM, pVariable->SnControlsList[iCurrentRow].szWorkNumber);
				
				pVariable->iActiveSnIndex = iCurrentRow;
		
				
				/* update rings for the new list of serials history */
				if (bSN_HistoryChange)
				{
					for (iCurrentRow = 0; iCurrentRow < pVariable->iSelectedSnQuantity; iCurrentRow++)
					{
						DeleteListItem (pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].ring_sn_ID, 0, -1);

						iHistorysQuantity = Ini_NumberOfItems (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS);

						for (iHistoryCount = 1; iHistoryCount <= iHistorysQuantity; iHistoryCount++)
						{
							if (Ini_NthItemName (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS, iHistoryCount, &pTagName ))
							{
								Ini_GetStringIntoBuffer (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS, pTagName, szSN, 256);
	
								InsertListItem (pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].ring_sn_ID, iHistoryCount-1, szSN, iHistoryCount);
							}
						}	 
					}
				}
			
				if (bPN_HistoryChange)
				{
					for (iCurrentRow = 0; iCurrentRow < pVariable->iSelectedSnQuantity; iCurrentRow++)
					{
						DeleteListItem (pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].ring_pn_ID, 0, -1);

						iHistorysQuantity = Ini_NumberOfItems (pVariable->hIniBuffer, INI_SEC_PN_HISTORYS);

						for (iHistoryCount = 1; iHistoryCount <= iHistorysQuantity; iHistoryCount++)
						{
							if (Ini_NthItemName (pVariable->hIniBuffer, INI_SEC_PN_HISTORYS, iHistoryCount, &pTagName ))
							{
								Ini_GetStringIntoBuffer (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS, pTagName, szPN, 256);
	
								InsertListItem (pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].ring_pn_ID, iHistoryCount-1, szPN, iHistoryCount);
							}
						}	 
					}
				}
				
				break;
				
				
			case EVENT_GOT_FOCUS:
				
				for (iCurrentRow = 0; iCurrentRow < pVariable->iSelectedSnQuantity; iCurrentRow++)
				{
					if ((pVariable->SnControlsList[iCurrentRow].sn_contorlID == control) || (pVariable->SnControlsList[iCurrentRow].pn_contorlID == control))
					{
						ResetTextBox (pVariable->hPanelHandle, PANEL_NOTE , "");
						
						if ( pVariable->SnControlsList[iCurrentRow].pszNote )
							SetCtrlVal(pVariable->hPanelHandle, PANEL_NOTE, pVariable->SnControlsList[iCurrentRow].pszNote);
						
						ResetTextBox (pVariable->hPanelHandle, PANEL_RMA_NUM , "");
						SetCtrlVal(pVariable->hPanelHandle, PANEL_RMA_NUM, pVariable->SnControlsList[iCurrentRow].szRMANumber);
						
						ResetTextBox (pVariable->hPanelHandle, PANEL_WORK_NUM , "");
						SetCtrlVal(pVariable->hPanelHandle, PANEL_WORK_NUM, pVariable->SnControlsList[iCurrentRow].szWorkNumber);
						
						pVariable->iActiveSnIndex = iCurrentRow;
					}
				}
			
				break;
		}
		
		if (hVariableHandle)
				CmtReleaseTSVPtr (hVariableHandle);
	}
	
	return 0;
}

int CVICALLBACK clbNote (int panel, int control, int event , void *callbackData, int eventData1, int eventData2)
{
	int					*pTemp					=	0, 
						hVariableHandle			=	0;
			
	tsMainGuiInfo		*pVariable				=	NULL;
	
	int					iActiveIndex			=	0;
	
	int					iStringLength			=	0;
	
	char				szAttention[256]		=	{0};
	
	if ( callbackData == NULL )
		return 0;
	
	switch (event)
	{
		case EVENT_COMMIT:

			pTemp = (int*) callbackData;
			hVariableHandle = *pTemp;
	
			if ( CmtGetTSVPtr ( hVariableHandle , &pVariable ) != 0 )
				return 0;
			
			iActiveIndex = pVariable->iActiveSnIndex;
			
			do
			{
				if ( ( pVariable->SnControlsList[iActiveIndex].pszSerialNumber == NULL ) || ( HasNonWhiteSpace (pVariable->SnControlsList[iActiveIndex].pszSerialNumber) == 0 ))
				{
					ResetTextBox (pVariable->hPanelHandle, PANEL_NOTE , "");
					sprintf(szAttention , "The S.N. %d: is empty.\nCan't add note to an empty Serial Number.", iActiveIndex+1);
					MessagePopup("Attention!",szAttention);
					SetActiveCtrl( pVariable->hPanelHandle , pVariable->SnControlsList[iActiveIndex].sn_contorlID );
					break;
				}
			
				if ( ( pVariable->SnControlsList[iActiveIndex].pszPartNumber == NULL ) || ( HasNonWhiteSpace (pVariable->SnControlsList[iActiveIndex].pszPartNumber) == 0 ))
				{
					ResetTextBox (pVariable->hPanelHandle, PANEL_NOTE , "");
					sprintf(szAttention , "The P.N. %d: is empty.\nCan't add note to an empty Part Number.", iActiveIndex+1);
					MessagePopup("Attention!",szAttention);
					SetActiveCtrl( pVariable->hPanelHandle , pVariable->SnControlsList[iActiveIndex].pn_contorlID );  
					break;
				}
				
				FREE(pVariable->SnControlsList[iActiveIndex].pszNote);
						
				GetCtrlAttribute( pVariable->hPanelHandle, PANEL_NOTE , ATTR_STRING_TEXT_LENGTH , &iStringLength );
						
				CALLOC( pVariable->SnControlsList[iActiveIndex].pszNote , (iStringLength + 64) , sizeof(char));
						
				if ( pVariable->SnControlsList[iActiveIndex].pszNote == NULL )
					return 0;
						
				GetCtrlVal(pVariable->hPanelHandle, PANEL_NOTE, pVariable->SnControlsList[iActiveIndex].pszNote );
				
				
			}while(0);
			
			if (hVariableHandle)
				CmtReleaseTSVPtr (hVariableHandle);
			
			break;
	}
	return 0;
}

int CVICALLBACK clbRmaNum (int panel, int control, int event , void *callbackData, int eventData1, int eventData2)
{
	int					*pTemp					=	0, 
						hVariableHandle			=	0;
			
	tsMainGuiInfo		*pVariable				=	NULL;
	
	int					iActiveIndex			=	0;
	
	char				szAttention[256]		=	{0};
	
	if ( callbackData == NULL )
		return 0;
	
	switch (event)
	{
		case EVENT_COMMIT:

			pTemp = (int*) callbackData;
			hVariableHandle = *pTemp;
	
			if ( CmtGetTSVPtr ( hVariableHandle , &pVariable ) != 0 )
				return 0;
			
			iActiveIndex = pVariable->iActiveSnIndex;
			
			do
			{
				if ( ( pVariable->SnControlsList[iActiveIndex].pszSerialNumber == NULL ) || ( HasNonWhiteSpace (pVariable->SnControlsList[iActiveIndex].pszSerialNumber) == 0 ))
				{
					ResetTextBox (pVariable->hPanelHandle, PANEL_RMA_NUM , "");
					sprintf(szAttention , "The S.N. %d: is empty.\nCan't add rma number to an empty Serial Number.", iActiveIndex+1);
					MessagePopup("Attention!",szAttention);
					SetActiveCtrl( pVariable->hPanelHandle , pVariable->SnControlsList[iActiveIndex].sn_contorlID );
					break;
				}	
				
				if ( ( pVariable->SnControlsList[iActiveIndex].pszPartNumber == NULL ) || ( HasNonWhiteSpace (pVariable->SnControlsList[iActiveIndex].pszPartNumber) == 0 ))
				{
					ResetTextBox (pVariable->hPanelHandle, PANEL_RMA_NUM , "");
					sprintf(szAttention , "The P.N. %d: is empty.\nCan't add rma number to an empty Part Number.", iActiveIndex+1);
					MessagePopup("Attention!",szAttention);
					SetActiveCtrl( pVariable->hPanelHandle , pVariable->SnControlsList[iActiveIndex].pn_contorlID );
					break;
				}
				
				GetCtrlVal(pVariable->hPanelHandle, PANEL_RMA_NUM, pVariable->SnControlsList[iActiveIndex].szRMANumber );
				
				SetCtrlVal( pVariable->hPanelHandle , pVariable->SnControlsList[iActiveIndex].rmaID , 1 );
				
				if ( pVariable->SnControlsList[iActiveIndex].extraParameters.iNumberOfItems )
					strcpy( pVariable->SnControlsList[iActiveIndex].extraParameters.pList[0].pszParameter , pVariable->SnControlsList[iActiveIndex].szRMANumber);
			
				pVariable->SnControlsList[iActiveIndex].bRMA = 1;
				
			} while (0);
			
			if (hVariableHandle)
				CmtReleaseTSVPtr (hVariableHandle);
			
			break;
	}
	return 0;
}

int CVICALLBACK clbWorkNum (int panel, int control, int event , void *callbackData, int eventData1, int eventData2)
{
	int					*pTemp					=	0, 
						hVariableHandle			=	0;
			
	tsMainGuiInfo		*pVariable				=	NULL;
	
	int					iActiveIndex			=	0;
	
	char				szAttention[256]		=	{0};
	
	if ( callbackData == NULL )
		return 0;
	
	switch (event)
	{
		case EVENT_COMMIT:

			pTemp = (int*) callbackData;
			hVariableHandle = *pTemp;
	
			if ( CmtGetTSVPtr ( hVariableHandle , &pVariable ) != 0 )
				return 0;
			
			iActiveIndex = pVariable->iActiveSnIndex;
			
			do
			{
				if ( ( pVariable->SnControlsList[iActiveIndex].pszSerialNumber == NULL ) || ( HasNonWhiteSpace (pVariable->SnControlsList[iActiveIndex].pszSerialNumber) == 0 ))
				{
					ResetTextBox (pVariable->hPanelHandle, PANEL_WORK_NUM , "");
					sprintf(szAttention , "The S.N. %d: is empty.\nCan't add work order number to an empty Serial Number.", iActiveIndex+1);
					MessagePopup("Attention!",szAttention);
					SetActiveCtrl( pVariable->hPanelHandle , pVariable->SnControlsList[iActiveIndex].sn_contorlID );
					break;
				}	
			
				if ( ( pVariable->SnControlsList[iActiveIndex].pszPartNumber == NULL ) || ( HasNonWhiteSpace (pVariable->SnControlsList[iActiveIndex].pszPartNumber) == 0 ))
				{
					ResetTextBox (pVariable->hPanelHandle, PANEL_WORK_NUM , "");
					sprintf(szAttention , "The P.N. %d: is empty.\nCan't add work order number to an empty Part Number.", iActiveIndex+1);
					MessagePopup("Attention!",szAttention);
					SetActiveCtrl( pVariable->hPanelHandle , pVariable->SnControlsList[iActiveIndex].pn_contorlID );
					break;
				}
				
				GetCtrlVal(pVariable->hPanelHandle, PANEL_WORK_NUM, pVariable->SnControlsList[iActiveIndex].szWorkNumber );
				
				SetCtrlVal( pVariable->hPanelHandle , pVariable->SnControlsList[iActiveIndex].rmaID , 1 );
				
				if ( pVariable->SnControlsList[iActiveIndex].extraParameters.iNumberOfItems > 1 )
					strcpy( pVariable->SnControlsList[iActiveIndex].extraParameters.pList[1].pszParameter , pVariable->SnControlsList[iActiveIndex].szWorkNumber);
			
				pVariable->SnControlsList[iActiveIndex].bRMA = 1;
			
			} while (0); 
			
			if (hVariableHandle)
				CmtReleaseTSVPtr (hVariableHandle);
			
			break;
	}
	return 0;
}


int CVICALLBACK clbNumber (int panel, int control, int event , void *callbackData, int eventData1, int eventData2)
{
	int					*pTemp					=	0, 
						hVariableHandle			=	0;
			
	tsMainGuiInfo		*pVariable				=	NULL;
	
	int					iNumber					=	0,
						iCurrentRow					=	0;
	
	int					iHistoryCount			=	0,
						iHistorysQuantity		=	0;
	
	char				*pTagName				=	NULL,
						szSN[256]				=	{0},
						szPN[256]				=	{0};
	
	if ( callbackData == NULL )
		return 0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			pTemp = (int*) callbackData;
			hVariableHandle = *pTemp;
	
			if ( CmtGetTSVPtr ( hVariableHandle , &pVariable ) != 0 )
				return 0;
			
			GetCtrlVal(pVariable->hPanelHandle, PANEL_NUMBER, &iNumber);
			
			pVariable->iSelectedSnQuantity = iNumber;
			
			/* unhide selected controls */
			for (iCurrentRow = 0; iCurrentRow < iNumber; iCurrentRow++)
			{
				SetCtrlAttribute(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].sn_contorlID, ATTR_VISIBLE, 1);
				SetCtrlAttribute(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].pn_contorlID, ATTR_VISIBLE, 1);
				SetCtrlAttribute(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].ring_sn_ID, ATTR_VISIBLE, 1);
				SetCtrlAttribute(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].ring_pn_ID, ATTR_VISIBLE, 1);
				SetCtrlAttribute(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].enableID, ATTR_VISIBLE, 1); 
				SetCtrlAttribute(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].rmaID, ATTR_VISIBLE, 1);
				
				if ( pVariable->SnControlsList[iCurrentRow].pszSerialNumber )
					SetCtrlVal(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].sn_contorlID, pVariable->SnControlsList[iCurrentRow].pszSerialNumber);
				
				if ( pVariable->SnControlsList[iCurrentRow].pszPartNumber )
					SetCtrlVal(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].pn_contorlID, pVariable->SnControlsList[iCurrentRow].pszPartNumber);
				
				SetCtrlVal(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].enableID , pVariable->SnControlsList[iCurrentRow].bEnableRun );
				SetCtrlVal(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].rmaID , pVariable->SnControlsList[iCurrentRow].bRMA ); 
				
				DeleteListItem (pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].ring_sn_ID, 0, -1);
				DeleteListItem (pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].ring_pn_ID, 0, -1);
				
				iHistorysQuantity = Ini_NumberOfItems (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS);
			
				for (iHistoryCount = 1; iHistoryCount <= iHistorysQuantity; iHistoryCount++)
				{
					if (Ini_NthItemName (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS, iHistoryCount, &pTagName ))
					{
						Ini_GetStringIntoBuffer (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS, pTagName, szSN, 256);
					
						InsertListItem (pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].ring_sn_ID, iHistoryCount-1, szSN, iHistoryCount);
					}
				}
				
				iHistorysQuantity = Ini_NumberOfItems (pVariable->hIniBuffer, INI_SEC_PN_HISTORYS);
			
				for (iHistoryCount = 1; iHistoryCount <= iHistorysQuantity; iHistoryCount++)
				{
					if (Ini_NthItemName (pVariable->hIniBuffer, INI_SEC_PN_HISTORYS, iHistoryCount, &pTagName ))
					{
						Ini_GetStringIntoBuffer (pVariable->hIniBuffer, INI_SEC_PN_HISTORYS, pTagName, szPN, 256);
					
						InsertListItem (pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].ring_pn_ID, iHistoryCount-1, szPN, iHistoryCount);
					}
				}
			}
			
			/* hide non selected controls */
			for (iCurrentRow = iNumber; iCurrentRow < pVariable->iMaxSnQuantity; iCurrentRow++)
			{
				SetCtrlAttribute(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].sn_contorlID, ATTR_VISIBLE, 0);
				SetCtrlAttribute(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].pn_contorlID, ATTR_VISIBLE, 0);
				SetCtrlAttribute(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].ring_sn_ID, ATTR_VISIBLE, 0);
				SetCtrlAttribute(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].ring_pn_ID, ATTR_VISIBLE, 0);
				SetCtrlAttribute(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].enableID, ATTR_VISIBLE, 0); 
				SetCtrlAttribute(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].rmaID, ATTR_VISIBLE, 0);
				
				if ( pVariable->SnControlsList[iCurrentRow].pszSerialNumber )
					strcpy(pVariable->SnControlsList[iCurrentRow].pszSerialNumber, "");
				
				if ( pVariable->SnControlsList[iCurrentRow].pszPartNumber )
					strcpy(pVariable->SnControlsList[iCurrentRow].pszPartNumber, "");
				
				if ( pVariable->SnControlsList[iCurrentRow].pszNote )
					strcpy(pVariable->SnControlsList[iCurrentRow].pszNote, "");
				
				strcpy(pVariable->SnControlsList[iCurrentRow].szRMANumber, "");
				strcpy(pVariable->SnControlsList[iCurrentRow].szWorkNumber, "");
				
				DeleteListItem (pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].ring_sn_ID, 0, -1);
				DeleteListItem (pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].ring_pn_ID, 0, -1);
			}
			
			SetActiveCtrl (pVariable->hPanelHandle, PANEL_PART_1);
			pVariable->iActiveSnIndex = 0;
			ResetTextBox (pVariable->hPanelHandle, PANEL_NOTE , "");
			
			if ( pVariable->SnControlsList[0].pszNote )
				SetCtrlVal( pVariable->hPanelHandle, PANEL_NOTE, pVariable->SnControlsList[0].pszNote);
			
			ResetTextBox (pVariable->hPanelHandle, PANEL_RMA_NUM , "");
			SetCtrlVal( pVariable->hPanelHandle, PANEL_RMA_NUM, pVariable->SnControlsList[0].szRMANumber);
			
			ResetTextBox (pVariable->hPanelHandle, PANEL_WORK_NUM , "");
			SetCtrlVal( pVariable->hPanelHandle, PANEL_WORK_NUM, pVariable->SnControlsList[0].szWorkNumber);
			
			/* resize and relocate panel and controls */
			SetPanelAttribute( pVariable->hPanelHandle, ATTR_TOP, pVariable->iPanelTopAttr - ((SN_STEP/2) * (iNumber-1)) ); 
			SetPanelAttribute( pVariable->hPanelHandle, ATTR_HEIGHT, START_POSITION_P_DOWN + (SN_STEP * (iNumber-1)) );
			SetCtrlAttribute( pVariable->hPanelHandle, PANEL_PICTURE, ATTR_HEIGHT, START_POSITION_P_DOWN + (SN_STEP * (iNumber-1)) );
			SetCtrlAttribute( pVariable->hPanelHandle, PANEL_NOTE, ATTR_TOP, START_POSITION_NOTE + (SN_STEP * (iNumber-1)) ); 
			SetCtrlAttribute( pVariable->hPanelHandle, PANEL_CANCEL_BUTTON, ATTR_TOP, ( START_POSITION_BUTTONS + (SN_STEP * (iNumber-1)) + 10 ) ); 
			SetCtrlAttribute( pVariable->hPanelHandle, PANEL_OK_BUTTON, ATTR_TOP, ( START_POSITION_BUTTONS + (SN_STEP * (iNumber-1))+ 10 ) ); 
			
			SetCtrlAttribute( pVariable->hPanelHandle, PANEL_RMA_NUM, ATTR_TOP, START_POSITION_RMA_NUM + (SN_STEP * (iNumber-1)) ); 
			SetCtrlAttribute( pVariable->hPanelHandle, PANEL_WORK_NUM, ATTR_TOP, START_POSITION_WORK_NUM + (SN_STEP * (iNumber-1)) ); 
			
			if (hVariableHandle)
				CmtReleaseTSVPtr (hVariableHandle);

			break;
	}
	
	return 0;
}

int CVICALLBACK clbRingCtrl (int panel, int control, int event , void *callbackData, int eventData1, int eventData2)
{
	int					*pTemp					=	0, 
						hVariableHandle			=	0;
			
	tsMainGuiInfo		*pVariable				=	NULL;
	
	int					iIndex					=	0,
						iStringLength			=	0, 
						iCurrentRow				=	0;
	
	char				szSN[256]				=	{0},
						szPN[256]				=	{0}; 
	
	tfSN_Parsing		pfSN_Parsing			=	NULL; 
	
	tfAUTO_Selection	pfAUTO_Selection		=	NULL;
	
	if ( callbackData == NULL )
		return 0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			pTemp = (int*) callbackData;
			hVariableHandle = *pTemp;
	
			if ( CmtGetTSVPtr ( hVariableHandle , &pVariable ) != 0 )
				return 0;
			
			pfSN_Parsing = pVariable->fSN_Parsing; 
			
			pfAUTO_Selection = pVariable->fAUTO_Selection; 
		
			for (iCurrentRow = 0; iCurrentRow < pVariable->iSelectedSnQuantity; iCurrentRow++)
			{
				if ((pVariable->SnControlsList[iCurrentRow].ring_sn_ID == control) || (pVariable->SnControlsList[iCurrentRow].ring_pn_ID == control))
					break;
			}
	
			if ( iCurrentRow >= pVariable->iSelectedSnQuantity )
				break;
			
			pVariable->iActiveSnIndex = iCurrentRow; 
			
			if ( pVariable->SnControlsList[iCurrentRow].ring_sn_ID == control )
			{
				GetCtrlIndex (pVariable->hPanelHandle, control, &iIndex);
				GetLabelFromIndex (pVariable->hPanelHandle, control, iIndex, szSN);
				
				iStringLength = strlen(szSN);
					
				FREE_CALLOC( pVariable->SnControlsList[iCurrentRow].pszSerialNumber , (iStringLength + 64) , sizeof(char));
				
				if ( pVariable->SnControlsList[iCurrentRow].pszSerialNumber )
				{
					strcpy (pVariable->SnControlsList[iCurrentRow].pszSerialNumber, szSN);
					SetCtrlVal(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].sn_contorlID, pVariable->SnControlsList[iCurrentRow].pszSerialNumber);
				}
			}

			if ( pVariable->SnControlsList[iCurrentRow].ring_pn_ID == control )
			{
				GetCtrlIndex (pVariable->hPanelHandle, control, &iIndex);
				GetLabelFromIndex (pVariable->hPanelHandle, control, iIndex, szPN);
					
				iStringLength = strlen(szPN);
				
				CALLOC( pVariable->SnControlsList[iCurrentRow].pszPartNumber , (iStringLength + 64) , sizeof(char));
				
				if ( pVariable->SnControlsList[iCurrentRow].pszPartNumber )
				{
					strcpy (pVariable->SnControlsList[iCurrentRow].pszPartNumber, szPN);
					SetCtrlVal(pVariable->hPanelHandle, pVariable->SnControlsList[iCurrentRow].pn_contorlID, pVariable->SnControlsList[iCurrentRow].pszPartNumber);
				}
			}
			
			//===========================================================//
			if ( pVariable->SnControlsList[iCurrentRow].sn_contorlID == control )
			{
				if ( pfSN_Parsing )
					if ( pfSN_Parsing( pVariable->SnControlsList[iCurrentRow].pszSerialNumber , CURRENT_USAGE_OF_EX_PARAMS , pVariable->SnControlsList[iCurrentRow].extraParameters ) == 0 )
					{
						SetCtrlVal(pVariable->hPanelHandle, control, pVariable->SnControlsList[iCurrentRow].pszSerialNumber);
																										   
						ProcessDrawEvents();
					}
			}
			
			if ( pfAUTO_Selection )
				pfAUTO_Selection( pVariable->SnControlsList[iCurrentRow].pszPartNumber , pVariable->SnControlsList[iCurrentRow].pszSerialNumber , &(pVariable->SnControlsList[iCurrentRow].iAutoSelect_UUT_Index) , &(pVariable->SnControlsList[iCurrentRow].iAutoSelect_Verion_Index) , &(pVariable->SnControlsList[iCurrentRow].piAutoSelect_ExtraData) , &(pVariable->SnControlsList[iCurrentRow].iAutoSelect_ExtraDataLength) );
			//===========================================================//
				
			if ( pVariable->SnControlsList[iCurrentRow].pszNote )
				strcpy (pVariable->SnControlsList[iCurrentRow].pszNote , "");
			
			ResetTextBox (pVariable->hPanelHandle, PANEL_NOTE , "");
			
			strcpy (pVariable->SnControlsList[iCurrentRow].szRMANumber, "");
			ResetTextBox (pVariable->hPanelHandle, PANEL_RMA_NUM , "");
			
			strcpy (pVariable->SnControlsList[iCurrentRow].szWorkNumber , "");
			ResetTextBox (pVariable->hPanelHandle, PANEL_WORK_NUM , "");
		
			if (hVariableHandle)
				CmtReleaseTSVPtr (hVariableHandle);

			break;
	}
	return 0;
}

int CVICALLBACK clbLastBut (int panel, int control, int event , void *callbackData, int eventData1, int eventData2)
{
	int					*pTemp					=	0, 
						hVariableHandle			=	0;
	
	int					iError					=	0;
			
	if ( callbackData == NULL )
		return 0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			pTemp = (int*) callbackData;
			hVariableHandle = *pTemp;
	
			iError = LoadLastConfiguration (hVariableHandle);
			
			break;
	}
	return 0;
}

int	LoadLastConfiguration (int hVariableHandle)
{
	tsMainGuiInfo		*pVariable				=	NULL;
	
	int					iStatus					=	0;
	
	int					iLastSelectedQuantity	=	0,
						iStringLength			=	0,
						iCurrentRow				=	0,
						iIndex					=	0,
						hPanel					=	0;
	
	char				szTagName[256]			=	{0},
						szTempParam[1024]		=	{0},
						*pTempString			=	NULL;
	
	iStatus = ERROR_LOAD_LAST;
	
	if ( CmtGetTSVPtr ( hVariableHandle , &pVariable ) != 0 )
		return 0;
	
	do
	{
		Ini_GetInt (pVariable->hIniBuffer, INI_SEC_LAST_CONFIG, "selected_quantity", &iLastSelectedQuantity);
		
		if (pVariable->iMaxSnQuantity < iLastSelectedQuantity)
			break;
		
		SetCtrlVal(pVariable->hPanelHandle, PANEL_NUMBER, iLastSelectedQuantity);
		
		for (iCurrentRow = 0; iCurrentRow < iLastSelectedQuantity; iCurrentRow++)
		{
			FREE(pVariable->SnControlsList[iCurrentRow].pszSerialNumber);
			
			sprintf (szTagName, "sn_%d", iCurrentRow);
			Ini_GetPointerToString (pVariable->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, &pTempString);
			
			if ( pTempString )
			{
				iStringLength = strlen(pTempString);
			
				CALLOC( pVariable->SnControlsList[iCurrentRow].pszSerialNumber , iStringLength + 64 , sizeof(char));
			
				if ( pVariable->SnControlsList[iCurrentRow].pszSerialNumber )
					strcpy( pVariable->SnControlsList[iCurrentRow].pszSerialNumber , pTempString );
			}
			
			FREE(pVariable->SnControlsList[iCurrentRow].pszPartNumber);
			
			sprintf (szTagName, "pn_%d", iCurrentRow);
			Ini_GetPointerToString (pVariable->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, &pTempString);
			
			if ( pTempString )
			{
				iStringLength = strlen(pTempString);
			
				CALLOC( pVariable->SnControlsList[iCurrentRow].pszPartNumber , iStringLength + 64 , sizeof(char));
			
				if ( pVariable->SnControlsList[iCurrentRow].pszPartNumber )
					strcpy( pVariable->SnControlsList[iCurrentRow].pszPartNumber , pTempString );
			}
			
			FREE(pVariable->SnControlsList[iCurrentRow].pszNote);
			
			sprintf (szTagName, "note_%d", iCurrentRow);
			Ini_GetPointerToString (pVariable->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, &pTempString);
			
			if ( pTempString )
			{
				iStringLength = strlen(pTempString);
			
				CALLOC( pVariable->SnControlsList[iCurrentRow].pszNote , iStringLength + 64 , sizeof(char));
			
				if ( pVariable->SnControlsList[iCurrentRow].pszNote )
					strcpy( pVariable->SnControlsList[iCurrentRow].pszNote , pTempString );
			}
			
			sprintf (szTagName, "enable_%d", iCurrentRow);
			Ini_GetUInt (pVariable->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, (unsigned int*)&(pVariable->SnControlsList[iCurrentRow].bEnableRun) );
			
			sprintf (szTagName, "rma_%d", iCurrentRow);
			Ini_GetUInt (pVariable->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, (unsigned int*)&(pVariable->SnControlsList[iCurrentRow].bRMA) );
			
			sprintf (szTagName, "rma_number_%d", iCurrentRow);
			Ini_GetStringIntoBuffer (pVariable->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, pVariable->SnControlsList[iCurrentRow].szRMANumber, 256); 
			
			sprintf (szTagName, "work_number_%d", iCurrentRow);
			Ini_GetStringIntoBuffer (pVariable->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, pVariable->SnControlsList[iCurrentRow].szWorkNumber, 256); 
			
			sprintf (szTagName, "auto_sel_uut_%d", iCurrentRow);
			Ini_GetUInt (pVariable->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, (unsigned int*)&(pVariable->SnControlsList[iCurrentRow].iAutoSelect_UUT_Index) );
	
			sprintf (szTagName, "auto_sel_ver_%d", iCurrentRow);
			Ini_GetUInt (pVariable->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, (unsigned int*)&(pVariable->SnControlsList[iCurrentRow].iAutoSelect_Verion_Index) );
		
			for ( iIndex = 0; iIndex < pVariable->SnControlsList[iCurrentRow].extraParameters.iNumberOfItems; iIndex++) 
			{
				sprintf (szTagName, "ex_param_%d_%d", iCurrentRow+1 , iIndex+1);
				Ini_GetStringIntoBuffer (pVariable->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName , szTempParam , 1024 );
				
				FREE_CALLOC_COPY( pVariable->SnControlsList[iCurrentRow].extraParameters.pList[iIndex].pszParameter , strlen(szTempParam) , 1 , szTempParam , strlen(szTempParam));
			}	
			
		}
		
		if (iCurrentRow < iLastSelectedQuantity)
			break;
		
		iStatus = 0; 
		
	}while (0);
	
	hPanel = pVariable->hPanelHandle;
	
	if (hVariableHandle)
				CmtReleaseTSVPtr (hVariableHandle);
	
	if (!iStatus)
		iStatus = clbNumber (hPanel, PANEL_NUMBER, EVENT_COMMIT, &hVariableHandle, 0, 0); 
				
	return iStatus;
}

int CVICALLBACK clbOkButton (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:

			QueueUserEvent ( USER_CLICK_LEFT_BUTTON , panel , control );
			
			break;
	}
	return 0;
}



int		FillPanelCallbackData( int hPanel , CmtTSVHandle hHandle )
{
	int			*pSharedPointer		=	NULL;
	
	pSharedPointer = calloc( 1 , sizeof(int) );
	
	if ( pSharedPointer )
	{
		*pSharedPointer = hHandle;
		
		SetCtrlAttribute( hPanel , PANEL_NUMBER , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_SERIAL_1 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_SERIAL_2 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_SERIAL_3 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_SERIAL_4 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_SERIAL_5 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_SERIAL_6 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_SERIAL_7 , ATTR_CALLBACK_DATA , pSharedPointer );	
		SetCtrlAttribute( hPanel , PANEL_SERIAL_8 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_SERIAL_9 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_SERIAL_10 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_PART_1 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_PART_2 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_PART_3 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_PART_4 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_PART_5 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_PART_6 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_PART_7 , ATTR_CALLBACK_DATA , pSharedPointer );	
		SetCtrlAttribute( hPanel , PANEL_PART_8 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_PART_9 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_PART_10 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_SN_1 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_SN_2 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_SN_3 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_SN_4 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_SN_5 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_SN_6 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_SN_7 , ATTR_CALLBACK_DATA , pSharedPointer );	
		SetCtrlAttribute( hPanel , PANEL_RING_SN_8 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_SN_9 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_SN_10 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_PN_1 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_PN_2 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_PN_3 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_PN_4 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_PN_5 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_PN_6 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_PN_7 , ATTR_CALLBACK_DATA , pSharedPointer );	
		SetCtrlAttribute( hPanel , PANEL_RING_PN_8 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_PN_9 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_PN_10 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RMA_1 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RMA_2 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RMA_3 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RMA_4 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RMA_5 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RMA_6 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RMA_7 , ATTR_CALLBACK_DATA , pSharedPointer );	
		SetCtrlAttribute( hPanel , PANEL_RMA_8 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RMA_9 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RMA_10 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_NOTE , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RMA_NUM , ATTR_CALLBACK_DATA , pSharedPointer ); 
		SetCtrlAttribute( hPanel , PANEL_WORK_NUM , ATTR_CALLBACK_DATA , pSharedPointer ); 
		SetCtrlAttribute( hPanel , PANEL_LAST_BUTTON , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_OK_BUTTON , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_CANCEL_BUTTON , ATTR_CALLBACK_DATA , pSharedPointer );
	}
	
	return 0;
}

int		ClearPanelCallbackData( int hPanel )
{
	int			*pSharedPointer		=	NULL;
	  
	GetCtrlAttribute( hPanel , PANEL_NUMBER , ATTR_CALLBACK_DATA , &pSharedPointer ); 
		  
	if ( pSharedPointer )
		free(pSharedPointer);
		
	SetCtrlAttribute( hPanel , PANEL_NUMBER , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_SERIAL_1 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_SERIAL_2 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_SERIAL_3 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_SERIAL_4 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_SERIAL_5 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_SERIAL_6 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_SERIAL_7 , ATTR_CALLBACK_DATA , NULL );	
	SetCtrlAttribute( hPanel , PANEL_SERIAL_8 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_SERIAL_9 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_SERIAL_10 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_PART_1 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_PART_2 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_PART_3 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_PART_4 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_PART_5 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_PART_6 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_PART_7 , ATTR_CALLBACK_DATA , NULL );	
	SetCtrlAttribute( hPanel , PANEL_PART_8 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_PART_9 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_PART_10 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_SN_1 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_SN_2 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_SN_3 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_SN_4 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_SN_5 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_SN_6 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_SN_7 , ATTR_CALLBACK_DATA , NULL );	
	SetCtrlAttribute( hPanel , PANEL_RING_SN_8 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_SN_9 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_SN_10 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_PN_1 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_PN_2 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_PN_3 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_PN_4 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_PN_5 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_PN_6 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_PN_7 , ATTR_CALLBACK_DATA , NULL );	
	SetCtrlAttribute( hPanel , PANEL_RING_PN_8 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_PN_9 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_PN_10 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RMA_1 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RMA_2 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RMA_3 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RMA_4 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RMA_5 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RMA_6 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RMA_7 , ATTR_CALLBACK_DATA , NULL );	
	SetCtrlAttribute( hPanel , PANEL_RMA_8 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RMA_9 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RMA_10 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_NOTE , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RMA_NUM , ATTR_CALLBACK_DATA , NULL ); 
	SetCtrlAttribute( hPanel , PANEL_WORK_NUM , ATTR_CALLBACK_DATA , NULL ); 
	SetCtrlAttribute( hPanel , PANEL_LAST_BUTTON , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_OK_BUTTON , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_CANCEL_BUTTON , ATTR_CALLBACK_DATA , NULL );
	
	return 0;
}
