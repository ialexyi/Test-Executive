#include "Select_SN_Module.h"
#include "Select_SN_Defines.h"

int	LoadLastConfiguration (int hVariableHandle);

#define		EVENT_OK_BUTTON		1001

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
	
	int					iLoop												=	0,
						iControlID											=	0,
						iControlIndex										=	0,
						iSnMaxNum											=	0,
						iNotEmptyCounter									=	0;
							
	char				szSnNum[256]										=	{0},
						szCtrlConstName[256]								=	{0};
	
	int					iHistorysQuantity									=	0;
							
	char				*pTagName											=	NULL,
						szTagName[256]										=	{0},
						szSN[256]											=	{0};
	
	int					iSelectedNumberOfSlots								=	0;
	
	tfSN_Parsing		pfSN_Parsing										=	NULL;

	tfAUTO_Selection	pfAUTO_Selection									=	NULL;
	
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
	FREE_CALLOC_ERR( pMainGuiInfo->SnControlsList , pMainGuiInfo->iMaxSnQuantity+1 , sizeof(tsSnControl));  // Allocate memory for SnControlsInfo by given max number
	
	for ( index = 0 ; index < pMainGuiInfo->iMaxSnQuantity ; index++ )
	{
		pMainGuiInfo->SnControlsList[index].extraParameters.iNumberOfItems = iNumberOfExItems;
		FREE_CALLOC( pMainGuiInfo->SnControlsList[index].extraParameters.pList , iNumberOfExItems , sizeof(tsExtraItem)); 
	}
		
	if (pMainGuiInfo->SnControlsList == NULL)
		{STD_ERR (ERROR_OUTOFMEMORY);}
	
	pMainGuiInfo->hPanelHandle = LoadPanelEx ( 0 , "Select_SN_Module.uir" , PANEL , __CVIUserHInst );
	
	if (pMainGuiInfo->hPanelHandle < 0)
		{FORCE_ERR(ERROR_CREATE_HANDLE ,"Can't load SelectSN GUI panel.");} 
	
	hPanel = pMainGuiInfo->hPanelHandle;		//Local store
	iSnMaxNum = pMainGuiInfo->iMaxSnQuantity;   //Local store
	
	GetPanelAttribute (hPanel, ATTR_PANEL_FIRST_CTRL, &iControlID);
	
	/* store control GUI ID for usefull controls */
	while (iControlID)
	{
		GetCtrlAttribute (hPanel, iControlID , ATTR_CONSTANT_NAME, szCtrlConstName);
		
		if (strstr(szCtrlConstName, "SN_") != NULL)
		{
			sscanf(szCtrlConstName, "SN_%d", &iControlIndex);
			
			if (iControlIndex <= iSnMaxNum)
				pMainGuiInfo->SnControlsList[iControlIndex-1].contorlID = iControlID;
		}
		
		if (strstr(szCtrlConstName, "RING_") != NULL)
		{
			sscanf(szCtrlConstName, "RING_%d", &iControlIndex);
			
			if (iControlIndex <= iSnMaxNum)
				pMainGuiInfo->SnControlsList[iControlIndex-1].ringID = iControlID;
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
				for (iLoop = 1; iLoop <= (iHistorysQuantity - MAX_HISTORY_NUM); iLoop++)
				{
					Ini_NthItemName (pMainGuiInfo->hIniBuffer, INI_SEC_SN_HISTORYS, 1, &pTagName);
					Ini_RemoveItem (pMainGuiInfo->hIniBuffer, INI_SEC_SN_HISTORYS, pTagName);
				}
			}
			
			/* fill the first history ring */
			for (iLoop = 1; iLoop <= iHistorysQuantity; iLoop++)
			{
				if (Ini_NthItemName (pMainGuiInfo->hIniBuffer, INI_SEC_SN_HISTORYS, iLoop, &pTagName ))
				{
					CHK_INI0 (Ini_GetStringIntoBuffer (pMainGuiInfo->hIniBuffer, INI_SEC_SN_HISTORYS, pTagName, szSN, 256));
					
					InsertListItem (hPanel, PANEL_RING_1, iLoop-1, szSN, iLoop);
				}
			}
		}
	}
	
	CHK_CMT (CmtReleaseTSVPtr (hMainGuiInfo));
	bGetMainVariable = 0;
	
	FillPanelCallbackData( hPanel , hMainGuiInfo ); 
	
	SetCtrlAttribute( hPanel , PANEL_RING_1 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_2 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_3 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_4 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_5 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_6 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_7 , ATTR_DISABLE_CHECK_MARK , 1 );	
	SetCtrlAttribute( hPanel , PANEL_RING_8 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_9 , ATTR_DISABLE_CHECK_MARK , 1 );
	SetCtrlAttribute( hPanel , PANEL_RING_10 , ATTR_DISABLE_CHECK_MARK , 1 );
	
	SetCtrlVal( hPanel, PANEL_tbOPERATOR, ptConfig->szOperator );
	
	/* fill values for select_number ring */
	for (iLoop = 0; iLoop < iSnMaxNum; iLoop++)
	{
		sprintf(szSnNum, "%d", iLoop+1);
		InsertListItem (hPanel, PANEL_NUMBER, iLoop, szSnNum, iLoop+1);
	}
	
	SetCtrlIndex (hPanel, PANEL_NUMBER, 0);
	
	if ( iSnMaxNum < 2 )
	{
		SetCtrlAttribute (hPanel, PANEL_NUMBER, ATTR_DIMMED , 1 );
		SetCtrlAttribute (hPanel, PANEL_ENABLE_1, ATTR_DIMMED , 1 );  
	}
	
	if ( ptConfig->bRunLastSnConfig )
	{
		{STD_ERR (LoadLastConfiguration(hMainGuiInfo));}
	
		iStatus == ATTENTION_OK;
	}
	else
	{
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
				CHK_CMT (CmtGetTSVPtr (hMainGuiInfo, &pMainGuiInfo )); 
				bGetMainVariable = 1; 
				
				iNotEmptyCounter = 0;
				
				for (iLoop = 0; iLoop < pMainGuiInfo->iSelectedSnQuantity; iLoop++) 
				{
					GetCtrlVal( pMainGuiInfo->hPanelHandle , pMainGuiInfo->SnControlsList[iLoop].enableID , &(pMainGuiInfo->SnControlsList[iLoop].bEnableRun) );
					
					if ( ( pMainGuiInfo->SnControlsList[iLoop].pszSerialNumber && strlen(pMainGuiInfo->SnControlsList[iLoop].pszSerialNumber)) || ( pMainGuiInfo->SnControlsList[iLoop].bEnableRun == 0 ))
						iNotEmptyCounter++;
					else
						SetActiveCtrl( pMainGuiInfo->hPanelHandle , pMainGuiInfo->SnControlsList[iLoop].contorlID );
				}
				
				CHK_CMT (CmtReleaseTSVPtr (hMainGuiInfo));
				bGetMainVariable = 0; 
				
				if ( iNotEmptyCounter == pMainGuiInfo->iSelectedSnQuantity )
				{
					iStatus = ATTENTION_OK;
					
					if ( ptConfig->bAutoContinue )
						break;
				}
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
		
		for (iLoop = 0; iLoop < pMainGuiInfo->iSelectedSnQuantity; iLoop++)
		{	
			if ( pMainGuiInfo->SnControlsList[iLoop].pszSerialNumber )
			{
				sprintf (szTagName, "sn_%d", iLoop);
				CHK_INI (Ini_PutString (pMainGuiInfo->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, pMainGuiInfo->SnControlsList[iLoop].pszSerialNumber));
			}
			
			if ( pMainGuiInfo->SnControlsList[iLoop].pszNote )
			{
				sprintf (szTagName, "note_%d", iLoop);
				CHK_INI (Ini_PutString (pMainGuiInfo->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, pMainGuiInfo->SnControlsList[iLoop].pszNote));
			}
			
			sprintf (szTagName, "enable_%d", iLoop);
			CHK_INI (Ini_PutUInt (pMainGuiInfo->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, pMainGuiInfo->SnControlsList[iLoop].bEnableRun));
			
			pResponds->pSelect[iLoop].tExtraList = pMainGuiInfo->SnControlsList[iLoop].extraParameters;
			pResponds->pSelect[iLoop].pSerialNumber = pMainGuiInfo->SnControlsList[iLoop].pszSerialNumber;
			pResponds->pSelect[iLoop].pPartNumber = NULL;
			pResponds->pSelect[iLoop].pNote = pMainGuiInfo->SnControlsList[iLoop].pszNote;
			pResponds->pSelect[iLoop].bRunEnable = pMainGuiInfo->SnControlsList[iLoop].bEnableRun;
			pResponds->pSelect[iLoop].iAutoSelect_UUT_Index = pMainGuiInfo->iAutoSelect_UUT_Index;
			pResponds->pSelect[iLoop].iAutoSelect_Verion_Index = pMainGuiInfo->iAutoSelect_Verion_Index;
			pResponds->pSelect[iLoop].piAutoSelect_ExtraData = pMainGuiInfo->piAutoSelect_ExtraData;
			pResponds->pSelect[iLoop].iAutoSelect_ExtraDataLength = pMainGuiInfo->iAutoSelect_ExtraDataLength;
	
			for ( index = 0 ; index < pMainGuiInfo->SnControlsList[iLoop].extraParameters.iNumberOfItems ; index++ )
			{
				if ( pMainGuiInfo->SnControlsList[iLoop].extraParameters.pList[index].pszParameter )
				{
					sprintf (szTagName, "ex_param_%d_%d", iLoop+1 , index+1);
					Ini_PutString (pMainGuiInfo->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, pMainGuiInfo->SnControlsList[iLoop].extraParameters.pList[index].pszParameter);
				}
			}
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
	
	if ( ptConfig )
	{
		FREE(ptConfig->pszSerialNumberParsingModulePath );
		FREE(ptConfig->pszAutoSelectionModulePath );
		FREE(ptConfig->szOperator);
		FREE(ptConfig);
	}
		
	return 0;
}


int CVICALLBACK panelCB (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
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


int CVICALLBACK clbSnCtrl (int panel, int control, int event , void *callbackData, int eventData1, int eventData2)
{
	int					*pTemp					=	0, 
						hVariableHandle			=	0;
			
	tsMainGuiInfo		*pVariable				=	NULL;
	
	int					iLoop					=	0,
						bHistoryChange			=	0,
						iHistoryCount			=	0,
						iHistorysQuantity		=	0;
	
	char				*pTagName				=	NULL,
						szSN[256]				=	{0};

	tfSN_Parsing		pfSN_Parsing			=	NULL; 
	
	int					iStartIndex				=	0,
						iStringLength			=	0;
	
	int					bEnterRequired			=	0; 
		 
	if ( callbackData == NULL )
		return 0;
	
	if (event)
	{
		pTemp = (int*) callbackData;
		hVariableHandle = *pTemp;

		if ( hVariableHandle == 0 )
			return 0;
			
		if ( CmtGetTSVPtr ( hVariableHandle , &pVariable ) != 0 )
			return 0;
			
		pfSN_Parsing = pVariable->fSN_Parsing; 
			
		switch (event)
		{
			case EVENT_COMMIT:
			//case EVENT_VAL_CHANGED:  
				
				/* find the changed control */
				for (iLoop = 0; iLoop < pVariable->iSelectedSnQuantity; iLoop++)
				{
					if (pVariable->SnControlsList[iLoop].contorlID == control)
					{
						FREE(pVariable->SnControlsList[iLoop].pszSerialNumber);
						
						GetCtrlAttribute( pVariable->hPanelHandle, control , ATTR_STRING_TEXT_LENGTH , &iStringLength );
						
						FREE_CALLOC( pVariable->SnControlsList[iLoop].pszSerialNumber , (iStringLength + 64) , sizeof(char));
						
						if ( pVariable->SnControlsList[iLoop].pszSerialNumber == NULL )
							return 0;
						
						GetCtrlVal(pVariable->hPanelHandle, control, pVariable->SnControlsList[iLoop].pszSerialNumber);
						
						GetCtrlVal(pVariable->hPanelHandle, pVariable->SnControlsList[iLoop].enableID , &(pVariable->SnControlsList[iLoop].bEnableRun) );
						
						if ( pfSN_Parsing )
							if ( pfSN_Parsing( pVariable->SnControlsList[iLoop].pszSerialNumber , iStartIndex , pVariable->SnControlsList[iLoop].extraParameters , &bEnterRequired ) == 0 )
							{
								if ( bEnterRequired )
								{
									SetCtrlVal(pVariable->hPanelHandle, control, pVariable->SnControlsList[iLoop].pszSerialNumber);  
									QueueUserEvent ( EVENT_OK_BUTTON , panel , PANEL_OK_BUTTON);  
								}
							}
																													   
						ProcessDrawEvents();
						
						FREE(pVariable->SnControlsList[iLoop].pszSerialNumber);
						
						GetCtrlAttribute( pVariable->hPanelHandle, control , ATTR_STRING_TEXT_LENGTH , &iStringLength );
						
						FREE_CALLOC( pVariable->SnControlsList[iLoop].pszSerialNumber , (iStringLength + 64) , sizeof(char));
						
						GetCtrlVal(pVariable->hPanelHandle, control, pVariable->SnControlsList[iLoop].pszSerialNumber); 	
						
						if (HasNonWhiteSpace (pVariable->SnControlsList[iLoop].pszSerialNumber))
						{
							/* save new serial number (.ini history) */
							if (!Ini_ItemExists (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS, pVariable->SnControlsList[iLoop].pszSerialNumber))
							{
								if (Ini_NumberOfItems (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS) >= MAX_HISTORY_NUM)
								{
									Ini_NthItemName (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS, 1, &pTagName);
									Ini_RemoveItem (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS, pTagName);
								}
								
								Ini_PutString (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS, pVariable->SnControlsList[iLoop].pszSerialNumber, pVariable->SnControlsList[iLoop].pszSerialNumber);
								bHistoryChange = 1;
							}
						}
						else
							if ( pVariable->SnControlsList[iLoop].pszNote )
								strcpy(pVariable->SnControlsList[iLoop].pszNote, "");
						
						ResetTextBox (pVariable->hPanelHandle, PANEL_NOTE , "");
						
						if ( pVariable->SnControlsList[iLoop].pszNote )
							SetCtrlVal(pVariable->hPanelHandle, PANEL_NOTE, pVariable->SnControlsList[iLoop].pszNote);
						
						pVariable->iActiveSnIndex = iLoop;
					}
				}
				
				/* update rings for the new list of serials history */
				if (bHistoryChange)
				{
					for (iLoop = 0; iLoop < pVariable->iSelectedSnQuantity; iLoop++)
					{
						DeleteListItem (pVariable->hPanelHandle, pVariable->SnControlsList[iLoop].ringID, 0, -1);

						iHistorysQuantity = Ini_NumberOfItems (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS);

						for (iHistoryCount = 1; iHistoryCount <= iHistorysQuantity; iHistoryCount++)
						{
							if (Ini_NthItemName (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS, iHistoryCount, &pTagName ))
							{
								Ini_GetStringIntoBuffer (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS, pTagName, szSN, 256);
	
								InsertListItem (pVariable->hPanelHandle, pVariable->SnControlsList[iLoop].ringID, iHistoryCount-1, szSN, iHistoryCount);
							}
						}	 
					}
				}
			
				break;
				
				
			case EVENT_GOT_FOCUS:
				
				for (iLoop = 0; iLoop < pVariable->iSelectedSnQuantity; iLoop++)
				{
					if (pVariable->SnControlsList[iLoop].contorlID == control)
					{
						ResetTextBox (pVariable->hPanelHandle, PANEL_NOTE , "");
						
						if ( pVariable->SnControlsList[iLoop].pszNote ) 
							SetCtrlVal(pVariable->hPanelHandle, PANEL_NOTE, pVariable->SnControlsList[iLoop].pszNote); 
						
						pVariable->iActiveSnIndex = iLoop;
					}
				}
			
				break;
		}
		
		CmtReleaseTSVPtr (hVariableHandle);
	}
	
	return 0;
}

int CVICALLBACK clbNote (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int					*pTemp					=	0, 
						hVariableHandle			=	0;
			
	tsMainGuiInfo		*pVariable				=	NULL;
	
	int					iActiveIndex			=	0,
						iStringLength			=	0;
	
	char				szAttention[256]		=	{0};
	
	if ( callbackData == NULL )
		return 0;
	
	switch (event)
	{
		case EVENT_COMMIT:

			pTemp = (int*) callbackData;
			hVariableHandle = *pTemp;
	
			if ( hVariableHandle == 0 )
				return 0;
			
			if ( CmtGetTSVPtr ( hVariableHandle , &pVariable ) != 0 )
				return 0;
			
			iActiveIndex = pVariable->iActiveSnIndex;
			
			if ( pVariable->SnControlsList[iActiveIndex].pszSerialNumber == NULL )
				FREE_CALLOC( pVariable->SnControlsList[iActiveIndex].pszSerialNumber , 64 , sizeof(char));
			
			if (HasNonWhiteSpace (pVariable->SnControlsList[iActiveIndex].pszSerialNumber))
			{
				GetCtrlAttribute( pVariable->hPanelHandle, PANEL_NOTE , ATTR_STRING_TEXT_LENGTH , &iStringLength );
						
				FREE_CALLOC( pVariable->SnControlsList[iActiveIndex].pszNote , (iStringLength + 64) , sizeof(char));
						
				if ( pVariable->SnControlsList[iActiveIndex].pszNote == NULL )
					return 0;
						
				GetCtrlVal(pVariable->hPanelHandle, PANEL_NOTE, pVariable->SnControlsList[iActiveIndex].pszNote );
				
			}
			else
			{
				ResetTextBox (pVariable->hPanelHandle, PANEL_NOTE , "");
				sprintf(szAttention , "The S.N. %d: is empty.\nCan't add note to an empty Serial Number.", iActiveIndex+1);
				MessagePopup("Attention!",szAttention);
			}
			
			CmtReleaseTSVPtr (hVariableHandle);
			
			break;
	}
	return 0;
}

int CVICALLBACK clbNumber (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int					*pTemp					=	0, 
						hVariableHandle			=	0;
			
	tsMainGuiInfo		*pVariable				=	NULL;
	
	int					iNumber					=	0,
						iLoop					=	0;
	
	int					iHistoryCount			=	0,
						iHistorysQuantity		=	0;
	
	char				*pTagName				=	NULL,
						szSN[256]				=	{0};
	
	if ( callbackData == NULL )
		return 0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			pTemp = (int*) callbackData;
			hVariableHandle = *pTemp;
	
			if ( hVariableHandle == 0 )
				return 0;
				
			if ( CmtGetTSVPtr ( hVariableHandle , &pVariable ) != 0 )
				return 0;
			
			GetCtrlVal(pVariable->hPanelHandle, PANEL_NUMBER, &iNumber);
			
			pVariable->iSelectedSnQuantity = iNumber;
			
			/* unhide selected controls */
			for (iLoop = 0; iLoop < iNumber; iLoop++)
			{
				SetCtrlAttribute(pVariable->hPanelHandle, pVariable->SnControlsList[iLoop].contorlID, ATTR_VISIBLE, 1);
				SetCtrlAttribute(pVariable->hPanelHandle, pVariable->SnControlsList[iLoop].ringID, ATTR_VISIBLE, 1);
				SetCtrlAttribute(pVariable->hPanelHandle, pVariable->SnControlsList[iLoop].enableID, ATTR_VISIBLE, 1); 
				
				if ( pVariable->SnControlsList[iLoop].pszSerialNumber )
					SetCtrlVal(pVariable->hPanelHandle, pVariable->SnControlsList[iLoop].contorlID, pVariable->SnControlsList[iLoop].pszSerialNumber);
				
				SetCtrlVal(pVariable->hPanelHandle, pVariable->SnControlsList[iLoop].enableID , pVariable->SnControlsList[iLoop].bEnableRun );
				
				DeleteListItem (pVariable->hPanelHandle, pVariable->SnControlsList[iLoop].ringID, 0, -1);
				
				iHistorysQuantity = Ini_NumberOfItems (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS);
			
				for (iHistoryCount = 1; iHistoryCount <= iHistorysQuantity; iHistoryCount++)
				{
					if (Ini_NthItemName (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS, iHistoryCount, &pTagName ))
					{
						Ini_GetStringIntoBuffer (pVariable->hIniBuffer, INI_SEC_SN_HISTORYS, pTagName, szSN, 256);
					
						InsertListItem (pVariable->hPanelHandle, pVariable->SnControlsList[iLoop].ringID, iHistoryCount-1, szSN, iHistoryCount);
					}
				}	 
			}
			
			/* hide non selected controls */
			for (iLoop = iNumber; iLoop < pVariable->iMaxSnQuantity; iLoop++)
			{
				SetCtrlAttribute(pVariable->hPanelHandle, pVariable->SnControlsList[iLoop].contorlID, ATTR_VISIBLE, 0);
				SetCtrlAttribute(pVariable->hPanelHandle, pVariable->SnControlsList[iLoop].ringID, ATTR_VISIBLE, 0);
				SetCtrlAttribute(pVariable->hPanelHandle, pVariable->SnControlsList[iLoop].enableID, ATTR_VISIBLE, 0); 
				
				if ( pVariable->SnControlsList[iLoop].pszSerialNumber )
					strcpy(pVariable->SnControlsList[iLoop].pszSerialNumber, "");
				
				if ( pVariable->SnControlsList[iLoop].pszNote )
					strcpy(pVariable->SnControlsList[iLoop].pszNote, "");
				
				DeleteListItem (pVariable->hPanelHandle, pVariable->SnControlsList[iLoop].ringID, 0, -1);
			}
			
			SetActiveCtrl (pVariable->hPanelHandle, PANEL_SN_1);
			pVariable->iActiveSnIndex = 0;
			ResetTextBox (pVariable->hPanelHandle, PANEL_NOTE , "");
			
			if ( pVariable->SnControlsList[0].pszNote )
				SetCtrlVal( pVariable->hPanelHandle, PANEL_NOTE, pVariable->SnControlsList[0].pszNote);
			
			/* resize and relocate panel and controls */
			SetPanelAttribute( pVariable->hPanelHandle, ATTR_TOP, pVariable->iPanelTopAttr - ((SN_STEP/2) * (iNumber-1)) ); 
			SetPanelAttribute( pVariable->hPanelHandle, ATTR_HEIGHT, START_POSITION_P_DOWN + (SN_STEP * (iNumber-1)) );
			SetCtrlAttribute( pVariable->hPanelHandle, PANEL_PICTURE, ATTR_HEIGHT, START_POSITION_P_DOWN + (SN_STEP * (iNumber-1)) );
			SetCtrlAttribute( pVariable->hPanelHandle, PANEL_NOTE, ATTR_TOP, START_POSITION_NOTE + (SN_STEP * (iNumber-1)) ); 
			SetCtrlAttribute( pVariable->hPanelHandle, PANEL_CANCEL_BUTTON, ATTR_TOP, START_POSITION_BUTTONS + (SN_STEP * (iNumber-1)) ); 
			SetCtrlAttribute( pVariable->hPanelHandle, PANEL_OK_BUTTON, ATTR_TOP, START_POSITION_BUTTONS + (SN_STEP * (iNumber-1)) ); 
			
			CmtReleaseTSVPtr (hVariableHandle);

			break;
	}
	
	return 0;
}

int CVICALLBACK clbRingCtrl (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int					*pTemp					=	0, 
						hVariableHandle			=	0;
			
	tsMainGuiInfo		*pVariable				=	NULL;
	
	int					iIndex					=	0,
						iLoop					=	0;
	
	char				szSN[256]				=	{0};
	
	if ( callbackData == NULL )
		return 0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			pTemp = (int*) callbackData;
			hVariableHandle = *pTemp;
	
			if ( hVariableHandle == 0 )
				return 0;
				
			if ( CmtGetTSVPtr ( hVariableHandle , &pVariable ) != 0 )
				return 0;
			
			GetCtrlIndex (pVariable->hPanelHandle, control, &iIndex);
			GetLabelFromIndex (pVariable->hPanelHandle, control, iIndex, szSN);
					
			for (iLoop = 0; iLoop < pVariable->iSelectedSnQuantity; iLoop++)
			{
				if (pVariable->SnControlsList[iLoop].ringID == control)
				{
					pVariable->iActiveSnIndex = iLoop;
			
					FREE_CALLOC( pVariable->SnControlsList[iLoop].pszSerialNumber , (strlen(szSN) + 64) , sizeof(char));
					
					if ( pVariable->SnControlsList[iLoop].pszSerialNumber )
					{
						strcpy (pVariable->SnControlsList[iLoop].pszSerialNumber, szSN);
						SetCtrlVal(pVariable->hPanelHandle, pVariable->SnControlsList[iLoop].contorlID, pVariable->SnControlsList[iLoop].pszSerialNumber);
					}
					
					if ( pVariable->SnControlsList[iLoop].pszNote )
						strcpy (pVariable->SnControlsList[iLoop].pszNote , "");

					ResetTextBox (pVariable->hPanelHandle, PANEL_NOTE , "");
				}
			}
			
			CmtReleaseTSVPtr (hVariableHandle);

			break;
	}
	return 0;
}

int CVICALLBACK clbLastBut (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
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

int	LoadLastConfiguration (CmtTSVHandle hVariableHandle)
{
	tsMainGuiInfo		*pVariable				=	NULL;
	
	int					iStatus					=	0;
	
	int					iLastSelectedQuantity	=	0,
						iStringLength			=	0,
						iLoop					=	0,
						iIndex					=	0,
						hPanel					=	0;
	
	char				szTagName[256]			=	{0},
						szTempParam[1024]		=	{0},
						*pTempString			=	NULL;
	
	int					iSnMaxNum				=	0;
	
	iStatus = ERROR_LOAD_LAST;
	
	if ( hVariableHandle == 0 )
		return 0;

	if ( CmtGetTSVPtr ( hVariableHandle , &pVariable ) != 0 )
		return 0;
	
	iSnMaxNum = pVariable->iMaxSnQuantity;
	
	do
	{
		Ini_GetInt (pVariable->hIniBuffer, INI_SEC_LAST_CONFIG, "selected_quantity", &iLastSelectedQuantity);
		
		if (pVariable->iMaxSnQuantity < iLastSelectedQuantity)
			break;
		
		SetCtrlVal(pVariable->hPanelHandle, PANEL_NUMBER, iLastSelectedQuantity);
		
		for (iLoop = 0; iLoop < iLastSelectedQuantity; iLoop++)
		{
			FREE(pVariable->SnControlsList[iLoop].pszSerialNumber);
			
			sprintf (szTagName, "sn_%d", iLoop);
			Ini_GetPointerToString (pVariable->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, &pTempString);
			
			if ( pTempString )
			{
				iStringLength = strlen(pTempString);
			
				FREE_CALLOC( pVariable->SnControlsList[iLoop].pszSerialNumber , iStringLength + 64 , sizeof(char));
			
				if ( pVariable->SnControlsList[iLoop].pszSerialNumber )
					strcpy( pVariable->SnControlsList[iLoop].pszSerialNumber , pTempString );
			}
			
			FREE(pVariable->SnControlsList[iLoop].pszNote); 
			
			sprintf (szTagName, "note_%d", iLoop);
			Ini_GetPointerToString (pVariable->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, &pTempString);
			
			if ( pTempString )
			{
				iStringLength = strlen(pTempString);
			
				FREE_CALLOC( pVariable->SnControlsList[iLoop].pszNote , iStringLength + 64 , sizeof(char));
			
				if ( pVariable->SnControlsList[iLoop].pszNote )
					strcpy( pVariable->SnControlsList[iLoop].pszNote , pTempString );
			}
			
			sprintf (szTagName, "enable_%d", iLoop);
			Ini_GetUInt (pVariable->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName, (unsigned int*)&(pVariable->SnControlsList[iLoop].bEnableRun) );
			
			for ( iIndex = 0; iIndex < pVariable->SnControlsList[iLoop].extraParameters.iNumberOfItems; iIndex++) 
			{
				sprintf (szTagName, "ex_param_%d_%d", iLoop+1 , iIndex+1);
				Ini_GetStringIntoBuffer (pVariable->hIniBuffer, INI_SEC_LAST_CONFIG, szTagName , szTempParam , 1024 );
				
				FREE_CALLOC_COPY( pVariable->SnControlsList[iLoop].extraParameters.pList[iIndex].pszParameter , strlen(szTempParam)+1 , 1 , szTempParam , strlen(szTempParam));
			}	
			
		}
		
		if ( iSnMaxNum < 2 )
		{
			SetCtrlAttribute (pVariable->hPanelHandle, PANEL_NUMBER, ATTR_DIMMED , 1 );
			SetCtrlAttribute (pVariable->hPanelHandle, PANEL_ENABLE_1, ATTR_DIMMED , 1 ); 
			
			SetCtrlIndex(pVariable->hPanelHandle, PANEL_NUMBER, 0 );
			SetCtrlVal(pVariable->hPanelHandle, PANEL_ENABLE_1, 1 );
		}
	
		if (iLoop < iLastSelectedQuantity)
			break;
		
		iStatus = 0; 
		
	}while (0);
	
	hPanel = pVariable->hPanelHandle;
	
	CmtReleaseTSVPtr (hVariableHandle);
	
	if (!iStatus)
		iStatus = clbNumber (hPanel, PANEL_NUMBER, EVENT_COMMIT, &hVariableHandle, 0, 0); 
				
	return iStatus;
}

int		FillPanelCallbackData( int hPanel , CmtTSVHandle hHandle )
{
	int			*pSharedPointer		=	NULL;
	
	pSharedPointer = calloc( 1 , sizeof(int) );
	
	if ( pSharedPointer )
	{
		*pSharedPointer = hHandle;
		
		SetCtrlAttribute( hPanel , PANEL_NUMBER , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_SN_1 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_SN_2 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_SN_3 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_SN_4 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_SN_5 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_SN_6 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_SN_7 , ATTR_CALLBACK_DATA , pSharedPointer );	
		SetCtrlAttribute( hPanel , PANEL_SN_8 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_SN_9 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_SN_10 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_1 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_2 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_3 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_4 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_5 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_6 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_7 , ATTR_CALLBACK_DATA , pSharedPointer );	
		SetCtrlAttribute( hPanel , PANEL_RING_8 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_9 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_RING_10 , ATTR_CALLBACK_DATA , pSharedPointer );
		SetCtrlAttribute( hPanel , PANEL_NOTE , ATTR_CALLBACK_DATA , pSharedPointer );
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
	SetCtrlAttribute( hPanel , PANEL_SN_1 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_SN_2 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_SN_3 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_SN_4 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_SN_5 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_SN_6 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_SN_7 , ATTR_CALLBACK_DATA , NULL );	
	SetCtrlAttribute( hPanel , PANEL_SN_8 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_SN_9 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_SN_10 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_1 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_2 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_3 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_4 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_5 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_6 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_7 , ATTR_CALLBACK_DATA , NULL );	
	SetCtrlAttribute( hPanel , PANEL_RING_8 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_9 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_RING_10 , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_NOTE , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_LAST_BUTTON , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_OK_BUTTON , ATTR_CALLBACK_DATA , NULL );
	SetCtrlAttribute( hPanel , PANEL_CANCEL_BUTTON , ATTR_CALLBACK_DATA , NULL );
	
	return 0;
}
