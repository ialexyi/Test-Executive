
//==============================================================================
// Include files
#include "defines.h"
#include "PathSupport.h"
#include "GlobalDefines.h"
#include <ansi_c.h>
#include <utility.h>
#include "TE_GlobalDefines.h"
#include "GUI.h"
#include "clb.h"
#include "TE_Equipment.h"
#include "formatio.h"
//==============================================================================
// Constants

//==============================================================================
// Types

typedef int (*path_func)( int *pHandle, char *pAddress, char *pPathString , char **pRespondsString );

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
int VarGetString( int handle , int vartype , unsigned long long linked , char* name, char** string); 
int VarSetString( int handle , int vartype , unsigned long long linked , char* name, char* string);

int VarGetInt( int handle , int vartype , unsigned long long linked , char* name, int** data);
int VarSetInt( int handle , int vartype , unsigned long long linked , char* name, int count, int* data);

int VarGetStringArray( int handle , int vartype , unsigned long long linked , char* name, char*** string);

int	GetEquipmentHandle ( int handle , int iType , char *pszAlias , int iNumber , int bAllowCreate , int *pEquipmentHandle ); 

//==============================================================================
// Global functions

STD_ERROR				PATH_SetPath( int handle , int iType , int iCalibPathPartIndex , char *pDeviceAddress , char *pszForcePathName , int *pSkipThisPath , ... )			
{		 
	STD_ERROR										StdError													=	{0};

	path_func										fpCurrentPathFunction										=	NULL;   

	char											szPathVariableName[LOW_STRING]								=	{0},
													szPathNameFormated[LOW_STRING]								=	{0}, 
													szDeviceAlias[LOW_STRING]									=	{0};  
														
	char											*pGetString													=	NULL,
													*pPathString												=	NULL,
													*pPathFunction												=	NULL, 
													*pPathPartName												=	NULL,  
													*pPathPartAlias												=	NULL, 
													*pPathFrequencies											=	NULL,   
													*pCurrentPathName											=	NULL,
													*pPathDeviceAddress											=	NULL,
													*pszPreviousPathName										=	NULL,  
													*pPathPartDescription										=	NULL,   
													*pCurrentPathPartName										=	NULL,
													*pCurrentPathDescription									=	NULL, 
													*pPathManualConnectionDescription							=	NULL,
													*pPathManualConnectionPicture								=	NULL,
													*pLastPathManualConnectionDescription						=	NULL;  
										
	char											**pStringArray												=	NULL;
	
	int												*pDisablePopupPathInstructions								=	NULL,
													*pSkipSamePathIgnoration									=	NULL, 
													*pCurrentPathPartDisabled									=	NULL,
													*pCurrentPathCalibratableStatus								=	NULL, 
													*pCurrentPathTestStepsQuantity								=	NULL; 
													
	tsMainStore										*pMainStore													=	NULL,
													tMainStore													=	{0};
	
	int												hMainHandle													=	0;
	
	tsSlotStore										*ptCurrentSlote												=	NULL;

	int												iSelectedTestIndex											=	0,
													iEquipmentUseIndex											=	0,  
													iPathQuantity												=	0, 
													iSlotIndex													=	0, 
													iPathPartIndex												=	0, 
													iCurrentFrequencyIndex										=	0, 
													iCalibratedPathListIndex									=	0, 
													iPathPartsQuantity											=	0, 
													iTrySetPathIndex											=	0,  
													iPathIndex													=	0; 
										
	int												bSkipSamePathIgnoration										=	0;
	
	va_list											parametersList												=	{0};

	int												bPathSetError												=	0,
													bEquipmentFound												=	0; 
													
	int												bUserBreak													=	0,
													bSkipped													=	0,
													bMainPathExists												=	0, 
													bPathControlSupporting										=	0;
													
	int												hPathModuleRefHandle										=	0,
													hUnitUnderTestModuleRefHandle								=	0;
										
	unsigned long long								hCurrentSelectedVersionId									=	0,
													ullLinkedID													=	0,
													hCurrentTestId												=	0;
										
	double											lfCurrentFrequency											=	0.0;
														
	int												iSlotNumber													=	0;
	
	va_start( parametersList , pSkipThisPath );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote ));
	hMainHandle = ptCurrentSlote->hMainStoreHandle;
	iSelectedTestIndex = ptCurrentSlote->iCurrentTestIndex;   
	hCurrentSelectedVersionId = ptCurrentSlote->hCurrentSelectedVersionId;   
	iSlotIndex = ptCurrentSlote->iSlotIndex;
	CALLOC_COPY_STRING( pLastPathManualConnectionDescription , ptCurrentSlote->pLastPathManualConnectionDescription );  
	CALLOC_COPY_STRING( pszPreviousPathName , ptCurrentSlote->pszPreviousPathName ); 
	
	if (( ptCurrentSlote->bRunMultiThread ) || ( ptCurrentSlote->iSelectedNumberOfSlots > 1 ) || ( ptCurrentSlote->iMaxNumberOfSlotsToSelect > 1 ))
		iSlotNumber = ptCurrentSlote->iSlotIndex + 1;
	
	CHK_CMT(CmtReleaseTSVPtr (handle)); 
	
	CHK_CMT( CmtGetTSVPtr ( hMainHandle , &pMainStore )); 
	pMainStore->bLastPathCommandHasApplied = 0;
	memcpy( &tMainStore , pMainStore , sizeof(tsMainStore));             
	CHK_CMT(CmtReleaseTSVPtr (hMainHandle));
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote )); 
	
	iPathQuantity = ptCurrentSlote->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptDB_Test->number_of_paths;
	iPathIndex = ptCurrentSlote->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].iCurrentPathIndex; 
	iPathPartsQuantity = ptCurrentSlote->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptDB_Test->number_of_path_parts; 
	
	if (iPathPartsQuantity < 0 ) 
		iPathPartsQuantity = 0;
	
	fpCurrentPathFunction = NULL;
	
	if ( ptCurrentSlote->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].dllPathHandle )
		fpCurrentPathFunction = (path_func) ptCurrentSlote->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].pPathApplyFunction;
		
	hCurrentTestId = ptCurrentSlote->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptDB_Test->id;
	hPathModuleRefHandle = ptCurrentSlote->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].hPathModuleRefHandle;
	CALLOC_COPY_STRING( pPathFunction , ptCurrentSlote->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptDB_Test->path_function );

	iCurrentFrequencyIndex = ptCurrentSlote->iCurrentFrequencyIndex; 
	
	if ( ptCurrentSlote->ptlFrequencies && ( iCurrentFrequencyIndex < ptCurrentSlote->ptlFrequencies->count))
		lfCurrentFrequency = ptCurrentSlote->ptlFrequencies->frequencies[iCurrentFrequencyIndex].frequency;
	
	CHK_CMT(CmtReleaseTSVPtr (handle)); 
	
	switch (iType)
	{
		
		case PATH_TYPE_CURRENT:
				
				IF (( iPathQuantity == 0 ) , "No Paths defined" );
					
			break;
		case PATH_TYPE_INDEX:
			
				IF (( iPathQuantity == 0 ) , "No Paths defined" );   
				
				iPathIndex = va_arg(parametersList, int); 
				
			break;
		case PATH_TYPE_NAME:
			
			
			pGetString = va_arg(parametersList, char*);
			
			if ( pGetString )
				FREE_CALLOC_COPY_STRING(pCurrentPathName,pGetString);
			
			break;
		case PATH_TYPE_VALUE:
			
			pGetString = va_arg(parametersList, char*);
			
			if ( pGetString )
				FREE_CALLOC_COPY_STRING(pPathString,pGetString);
				
			iPathPartsQuantity = va_arg(parametersList, int); 
			
			break;
			
		default:
			break;
	}
	
	VarGetInt( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , "DisablePopupPathInstructions" , &pDisablePopupPathInstructions );
		
	if ( pDisablePopupPathInstructions == NULL )     
	{
		CALLOC( pDisablePopupPathInstructions , 1 , sizeof(int));
			
		VarSetInt( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , "DisablePopupPathInstructions" , 1 , pDisablePopupPathInstructions ); 	
	}
	
	if ( tMainStore.iSpecGroup != CALIBRATION_SPEC_GROUP )
	{
		VarGetInt( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , "SkipSamePathIgnoration" , &pSkipSamePathIgnoration );
		
		if ( pSkipSamePathIgnoration == NULL )     
		{
			CALLOC( pSkipSamePathIgnoration , 1 , sizeof(int));
			
			VarSetInt( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , "SkipSamePathIgnoration" , 1 , pSkipSamePathIgnoration ); 	
		}
	}
	else
	{
		VarGetInt( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , "Calibration_SkipSamePathIgnoration" , &pSkipSamePathIgnoration );
		
		if ( pSkipSamePathIgnoration == NULL )     
		{
			CALLOC( pSkipSamePathIgnoration , 1 , sizeof(int));
			
			*pSkipSamePathIgnoration = 1;
			
			VarSetInt( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , "Calibration_SkipSamePathIgnoration" , 1 , pSkipSamePathIgnoration ); 	
		}
	}
			
	if ( pSkipSamePathIgnoration )
		bSkipSamePathIgnoration = *pSkipSamePathIgnoration;
	
	if ( pPathString == NULL )
	{
		if ( pCurrentPathName == NULL )
		{
			sprintf( szPathVariableName , "Path_%d_Name" , iPathIndex+1 ); 
			if (( VarGetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , &pCurrentPathName ) <= 0 ) || ( pCurrentPathName == NULL ))
				VarSetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName, "." ); 	
			
			if ( pCurrentPathName && ( strlen(pCurrentPathName) > 1 ))
				bMainPathExists = 1;   
			
			sprintf( szPathVariableName , "Path_%d_Description" , iPathIndex+1 ); 
			if (( VarGetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , &pCurrentPathDescription ) <= 0 ) || ( pCurrentPathDescription == NULL ))
				VarSetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName, "." ); 	
			
			sprintf( szPathVariableName , "Path_%d_Calibratable" , iPathIndex+1 ); 
			if (( VarGetInt( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , &pCurrentPathCalibratableStatus ) == 0 ) || ( pCurrentPathCalibratableStatus == NULL ))
			{
				CALLOC_ERR( pCurrentPathCalibratableStatus , 1 , sizeof(int));  
				
				if ( pCurrentPathCalibratableStatus )
				{
					*pCurrentPathCalibratableStatus = 1;
					
					VarSetInt( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName, 1 , pCurrentPathCalibratableStatus ); 
				}
			}
		}
		
		IF (( pCurrentPathName == NULL ) , "Path name is empty" );
		
	}
	
	if ( pCurrentPathName )
	{
		RemoveSurroundingWhiteSpace (pCurrentPathName);
	
		if ( strstr( pCurrentPathName , "%d" ))
		{
			sprintf( szPathNameFormated , pCurrentPathName , ( iSlotIndex+1 ));
			strcpy( pCurrentPathName , szPathNameFormated );                   
		}
	}
	
	if ( pszForcePathName && pSkipThisPath && pszForcePathName && strlen(pszForcePathName) )
	{
		bSkipped = strcmp( pCurrentPathName , pszForcePathName );
		
		if ( bSkipped )
			RETURN;
	}
	
	CALLOC_ERR( pCurrentPathPartName , 64 , sizeof(char));
	
	if ( iPathPartsQuantity ) 
	{
		sprintf( szPathVariableName , "Path_%d_%d_Alias" , iPathIndex+1 , iCalibPathPartIndex+1 ); 
		VarGetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , &pPathPartAlias );

		if ( pPathPartAlias == NULL )     
			VarSetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , "." ); 
		else
		{
			if ( strstr( pPathPartAlias , "%d" ))
			{
				sprintf( szPathNameFormated , pPathPartAlias , ( iSlotIndex+1 ));
				strcpy( pPathPartAlias , szPathNameFormated );                   
			}
		}
		
		sprintf( szPathVariableName , "Path_%d_%d_Disabled" , iPathIndex+1 , iCalibPathPartIndex+1 ); 
		if (( VarGetInt( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , &pCurrentPathPartDisabled ) == 0 ) || ( pCurrentPathPartDisabled == NULL ))
		{
			CALLOC_ERR( pCurrentPathPartDisabled , 1 , sizeof(int));  
			
			if ( pCurrentPathPartDisabled )
				VarSetInt( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName, 1 , pCurrentPathPartDisabled ); 
		}
		
		if (( pCurrentPathPartDisabled ) && ( *pCurrentPathPartDisabled ))
		{
			if ( tMainStore.iSpecGroup == CALIBRATION_SPEC_GROUP )  
			{
				bSkipped = 1;
				RETURN; 
			}			
		}
	}	
			
	if ( iPathQuantity ) 
	{
		sprintf( szPathVariableName , "Path_%d_%d_Frequencies" , iPathIndex+1 , iCalibPathPartIndex+1 ); 
		VarGetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , &pPathFrequencies );

		if ( pPathFrequencies == NULL )     
			VarSetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , "." ); 
		
	}
	
	if ( iPathQuantity > 1 )
	{
		if ( pMainStore->tRunMode == RUN_MODE_CALIBRATION ) 
			sprintf( szPathVariableName , CONFIG_TEST_FORMATED_CALIB_STEPS_QUANTITY , (iPathIndex+1) );
		else
			sprintf( szPathVariableName , CONFIG_TEST_FORMATED_STEPS_QUANTITY , (iPathIndex+1) );
		
		if (( VarGetInt( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , &pCurrentPathTestStepsQuantity ) == 0 ) || ( pCurrentPathTestStepsQuantity == NULL ))
		{
			CALLOC_ERR( pCurrentPathTestStepsQuantity , 1 , sizeof(int));  
	
			if ( pCurrentPathTestStepsQuantity )
			{
				VarSetInt( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName, 1 , pCurrentPathTestStepsQuantity ); 
			}
		}
	}

	if ( pPathString == NULL ) 
	{
		do
		{
			if ( tMainStore.iSpecGroup != CALIBRATION_SPEC_GROUP )  
			{
				if ( pCurrentPathName && strlen(pCurrentPathName) && strcmp(pCurrentPathName , "."))  
				{
					if ( strstr( pCurrentPathName , "%d" ))
					{
						sprintf( szPathNameFormated , pCurrentPathName , ( iSlotIndex+1 ));
						strcpy( pCurrentPathName , szPathNameFormated );                   
					}
					
					if (( VarGetString( hMainHandle , VAR_CONFIG_STATION , tMainStore.hCurrentStationId , pCurrentPathName , &pPathString ) <= 0 ) || ( pPathString == NULL ))    
						VarSetString( hMainHandle , VAR_CONFIG_STATION , tMainStore.hCurrentStationId , pCurrentPathName, "." );	
				
					break;
				}
		
			}
			
			if ( iPathPartsQuantity )
			{
				if ( pPathPartAlias && ( strlen(pPathPartAlias)) && ( pPathPartAlias[0] != '.' ))
				{
					FREE_CALLOC_COPY_STRING( pCurrentPathPartName , pPathPartAlias );
			
					if ( tMainStore.iSpecGroup == CALIBRATION_SPEC_GROUP )  
					{
						FREE_CALLOC_COPY_STRING( pCurrentPathName , pPathPartAlias );
					}
				}
				else
				{
					sprintf( pCurrentPathPartName , "%s_%d" , pCurrentPathName , iCalibPathPartIndex+1 );
				}
		
				sprintf( szPathVariableName , "Path_%d_%d_Name" , iPathIndex+1 , iCalibPathPartIndex+1 ); 
				VarGetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , &pPathPartName );

				if ( pPathPartName == NULL )     
					VarSetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , "." ); 	
		
				if ( pPathPartName && ( strlen(pPathPartName)) && ( pPathPartName[0] != '.' ))
				{
					FREE_CALLOC_COPY_STRING( pCurrentPathName , pPathPartName );
				}   
			
				if ( tMainStore.iSpecGroup == CALIBRATION_SPEC_GROUP )  
				{
					sprintf( szPathVariableName , "Path_%d_%d_Description" , iPathIndex+1 , iCalibPathPartIndex+1 ); 
					VarGetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , &pPathPartDescription );

					if ( pPathPartDescription == NULL )     
						VarSetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , "." ); 	
			
					if ( pPathPartDescription && ( strlen(pPathPartDescription)) && ( pPathPartDescription[0] != '.' ))
					{
						FREE_CALLOC_COPY_STRING( pCurrentPathDescription , pPathPartDescription );
					}  
				
					if (( pCurrentPathCalibratableStatus == NULL ) || ( pCurrentPathCalibratableStatus[0] == 1 ))
					{
						sprintf( szPathVariableName , "Path_%d_%d_Calibratable" , iPathIndex+1 , iCalibPathPartIndex+1 );         
						if (( VarGetInt( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , &pCurrentPathCalibratableStatus ) == 0 ) || ( pCurrentPathCalibratableStatus == NULL ))
						{
							CALLOC_ERR( pCurrentPathCalibratableStatus , 1 , sizeof(int));  
				
							if ( pCurrentPathCalibratableStatus )
							{
								*pCurrentPathCalibratableStatus = 1;
					
								VarSetInt( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName, 1 , pCurrentPathCalibratableStatus ); 
							}
						}
					}
				
					sprintf( szPathVariableName , "Path_%d_%d_TestStepsQuantity" , iPathIndex+1 , iCalibPathPartIndex+1 );         
					if (( VarGetInt( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , &pCurrentPathTestStepsQuantity ) == 0 ) || ( pCurrentPathTestStepsQuantity == NULL ))
					{
						CALLOC_ERR( pCurrentPathTestStepsQuantity , 1 , sizeof(int));  
				
						if ( pCurrentPathTestStepsQuantity )
						{
							VarSetInt( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName, 1 , pCurrentPathTestStepsQuantity ); 
						}
					}
				}
			}
			else
				sprintf( pCurrentPathPartName , "%s" , pCurrentPathName );
		
			if ( pCurrentPathName && strlen(pCurrentPathName) )  
			{   
				if ( strlen(pCurrentPathPartName) > 1 )
				{
					if ( strstr( pCurrentPathPartName , "%d" ))
					{
						sprintf( szPathNameFormated , pCurrentPathPartName , ( iSlotIndex+1 ));
						strcpy( pCurrentPathPartName , szPathNameFormated );                   
					}
					
					if (( VarGetString( hMainHandle , VAR_CONFIG_STATION , tMainStore.hCurrentStationId , pCurrentPathPartName , &pPathString ) <= 0 ) || ( pPathString == NULL ))    
						VarSetString( hMainHandle , VAR_CONFIG_STATION , tMainStore.hCurrentStationId , pCurrentPathPartName, "." );
				}
			}
			
		} while(0);
	}

	if ( pCurrentPathName )
	{
		RemoveSurroundingWhiteSpace (pCurrentPathName);
	
		if ( strstr( pCurrentPathName , "%d" ))
		{
			sprintf( szPathNameFormated , pCurrentPathName , ( iSlotIndex+1 ));
			strcpy( pCurrentPathName , szPathNameFormated );                   
		}
	}
	
	if ( tMainStore.iSpecGroup == CALIBRATION_SPEC_GROUP )
	{
		if ( pCurrentPathCalibratableStatus && (( *pCurrentPathCalibratableStatus ) == 0 ))
		{
			bSkipped = 1;
			RETURN;
		}
		
		CHK_CMT( CmtGetTSVPtr ( hMainHandle , &pMainStore )); 
		
		if ( pMainStore->pCalibratedPathList )
		{
			for( iCalibratedPathListIndex = 0; iCalibratedPathListIndex < pMainStore->iCalibratedPathListCount; iCalibratedPathListIndex++ )
				if ( strcmp( pCurrentPathName , pMainStore->pCalibratedPathList[iCalibratedPathListIndex] ) == 0 )
				{
					bSkipped = 1;
			
					break;
				}
		}
		
		CHK_CMT(CmtReleaseTSVPtr (hMainHandle));
		
		if ( bSkipped )
			RETURN;
	}
	
	if( pDeviceAddress == NULL )
	{
		VarGetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , "Path_Device_Address" , &pPathDeviceAddress );

		if ( pPathDeviceAddress == NULL )
		{
			VarGetString( hMainHandle , VAR_CONFIG_UUTVER , hCurrentSelectedVersionId , "Path_Device_Address" , &pPathDeviceAddress );

			if ( pPathDeviceAddress == NULL )     
				VarSetString( hMainHandle , VAR_CONFIG_UUTVER , hCurrentSelectedVersionId , "Path_Device_Address", "." ); 	
		}
	}
	else
	{
		pPathDeviceAddress = pDeviceAddress;	
	}
	
	if (( pszPreviousPathName == NULL ) || (strlen(pszPreviousPathName) == 0 ) || ( strcmp(pszPreviousPathName,pCurrentPathName)) || bSkipSamePathIgnoration )
	{
		if ( tMainStore.iSpecGroup == CALIBRATION_SPEC_GROUP )
		{
			// Calibration selection path
			sprintf( szPathVariableName , "Path_%d_%d_CalibrationConnectDescription" , iPathIndex+1 , iCalibPathPartIndex+1 ); 
			VarGetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , &pPathManualConnectionDescription );
	
			if ( pPathManualConnectionDescription == NULL )     
				VarSetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , "." ); 	
		
			sprintf( szPathVariableName , "Path_%d_%d_CalibrationConnectPicture" , iPathIndex+1 , iCalibPathPartIndex+1 ); 
			VarGetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , &pPathManualConnectionPicture );

			if ( pPathManualConnectionPicture == NULL )     
				VarSetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , "." ); 	
			
			do
			{
				if (( pPathManualConnectionDescription == NULL ) && ( pPathManualConnectionPicture == NULL ))
					break;
				
				if ( pPathManualConnectionDescription && ( strlen(pPathManualConnectionDescription) == 1 ) && ( pPathManualConnectionDescription[0] == '.' ) && ( pPathManualConnectionPicture == NULL ))  
					break;
				
				if ( pPathManualConnectionPicture && ( strlen(pPathManualConnectionPicture) == 1 ) && ( pPathManualConnectionPicture[0] == '.' ) && ( pPathManualConnectionDescription == NULL ))  
					break;
				
				if ( pPathManualConnectionDescription && ( strlen(pPathManualConnectionDescription) == 1 ) && ( pPathManualConnectionDescription[0] == '.' ) && pPathManualConnectionPicture && ( strlen(pPathManualConnectionPicture) == 1 ) && ( pPathManualConnectionPicture[0] == '.' ))  
					break;
				
				bUserBreak = !GUI_Instruction ( handle , 1 , pPathManualConnectionDescription , pPathManualConnectionPicture );
				
			} while(0);
			
			if ( bPathSetError )
				ShowMessage ( 0 , INSTR_TYPE_CONTINUE ,  "Warning..." , "Path is not setted..." , NULL );
		}   
	
		if ( bUserBreak == 0 )
		{
			for( iTrySetPathIndex = 0; iTrySetPathIndex < 2; iTrySetPathIndex++ )
			{
				GetEquipmentHandle ( handle , EQUIPMENT_TYPE_STANDARD_DEVICE , STANDARD_DEVICE_RF_BOX_ALIAS , 0 , 0 , &hPathModuleRefHandle );  
			
				 //try to set path automatically
				if (( fpCurrentPathFunction == NULL ) || ( fpCurrentPathFunction(&(hPathModuleRefHandle) , pPathDeviceAddress , pPathString , NULL ) ))
				{
					if ( pPathFunction && ( strlen( pPathFunction ) > 1 ))
						bPathSetError = 1;
				}
				else
					break;
			}
		
			if (( tMainStore.iSpecGroup != CALIBRATION_SPEC_GROUP ) && ( bPathSetError ))
			{
				bPathSetError = 0;
				// Manual selection path
				sprintf( szPathVariableName , "Path_%d_ManualConnectDescription" , iPathIndex+1 ); 
				VarGetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , &pPathManualConnectionDescription );
	
				if ( pPathManualConnectionDescription == NULL )     
					VarSetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , "." ); 	
		
				sprintf( szPathVariableName , "Path_%d_ManualConnectPicture" , iPathIndex+1 ); 
				VarGetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , &pPathManualConnectionPicture );

				if ( pPathManualConnectionPicture == NULL )     
					VarSetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , "." ); 	
			
				if (( pDisablePopupPathInstructions == NULL ) || ( *pDisablePopupPathInstructions == 0 ))
				{
					do
					{
						if (( pPathManualConnectionDescription == NULL ) && ( pPathManualConnectionPicture == NULL ))
							break;
						
						if ( pLastPathManualConnectionDescription && pPathManualConnectionDescription && ( strcmp( pLastPathManualConnectionDescription , pPathManualConnectionDescription ) == 0 ))
							break;	
						
						if ( pPathManualConnectionDescription && ( strlen(pPathManualConnectionDescription) == 1 ) && ( pPathManualConnectionDescription[0] == '.' ) && ( pPathManualConnectionPicture == NULL ))  
							break;
							
						if ( pPathManualConnectionPicture && ( strlen(pPathManualConnectionPicture) == 1 ) && ( pPathManualConnectionPicture[0] == '.' ) && ( pPathManualConnectionDescription == NULL ))  
							break;
						
						if ( pPathManualConnectionDescription && ( strlen(pPathManualConnectionDescription) == 1 ) && ( pPathManualConnectionDescription[0] == '.' ) && pPathManualConnectionPicture && ( strlen(pPathManualConnectionPicture) == 1 ) && ( pPathManualConnectionPicture[0] == '.' ))  
							break;
						
						bUserBreak = !GUI_Instruction ( handle , 1 , pPathManualConnectionDescription , pPathManualConnectionPicture );
					
					} while(0);
				}
			}
		}
	}
	
	if ( bUserBreak == 0 )
	{
		iEquipmentUseIndex = 0;
		
		do
		{
			bEquipmentFound = 0;
			hUnitUnderTestModuleRefHandle = 0;
			bPathControlSupporting = 0;
			
			if ( CmtGetTSVPtr ( hMainHandle , &pMainStore ) == 0 )
			{	   
				for ( ; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
					if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle )
						if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].type == EQUIPMENT_TYPE_STANDARD_DEVICE )  
						{
							bEquipmentFound = 1;
							
							hUnitUnderTestModuleRefHandle = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle;
							ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;
							
							strcpy( szDeviceAlias , pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias );
							
							bPathControlSupporting = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].switch_control;
							
							break;
						}
						
				CmtReleaseTSVPtr ( hMainHandle );	
			}
					
			if ( hUnitUnderTestModuleRefHandle && bEquipmentFound )
			{
				//----------------- RF BOX Support --------------------------------------//
				StringLowerCase ( szDeviceAlias );
				
				if (( strcmp( szDeviceAlias , STANDARD_DEVICE_RF_BOX_ALIAS ) == 0 ) || ( bPathControlSupporting ))
				{
					//----------------- Global Commands ---------------------------------// 
					iPathPartIndex = 0;
						
					do
					{
						if ( pPathString && strlen(pPathString) && ( pPathString[0] != '.' )) 
						{
							NO_CHK_STDERR( TE_EQUIP_Devices_Apply_PathConnection( hMainHandle , iSelectedTestIndex , hUnitUnderTestModuleRefHandle , pPathString ));
						}
						
						if ( tMainStore.iSpecGroup == CALIBRATION_SPEC_GROUP )
						{
							break;
						}
						else
						{
							if ( bMainPathExists )
								break;
						}
						
						FREE(pPathPartName);
						
						sprintf( szPathVariableName , "Path_%d_%d_Name" , iPathIndex+1 , iPathPartIndex+1 ); 
						VarGetString( hMainHandle , VAR_CONFIG_TEST , hCurrentTestId , szPathVariableName , &pPathPartName );
						
						if ( pPathPartName )
						{
							FREE(pPathString);
							
							if ( strstr( pPathPartName , "%d" ))
							{
								sprintf( szPathNameFormated , pPathPartName , ( iSlotIndex+1 ));
								strcpy( pPathPartName , szPathNameFormated );                   
							}
					
							VarGetString( hMainHandle , VAR_CONFIG_STATION , tMainStore.hCurrentStationId , pPathPartName , &pPathString );	
						}
						
						if ( pPathString == NULL )
							break;
						
						iPathPartIndex++;
						
					} while( iPathPartIndex <= iPathPartsQuantity );
				}
			}
			
			iEquipmentUseIndex++;
			
		} while( bEquipmentFound );
	}
	
Error:

	va_end( parametersList );
	
	if ( pSkipThisPath )
		*pSkipThisPath = bSkipped;
	
	if (( pCurrentPathName ) && ( CmtGetTSVPtr ( handle , &ptCurrentSlote ) == 0 ))
	{
		if ( bUserBreak )
		{
			ptCurrentSlote->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].iTestStatus = RUN_STATUS_ABORT;
			StdError.error = -1;
		}
		
		ptCurrentSlote->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].hPathModuleRefHandle = hPathModuleRefHandle;
						
		FREE(ptCurrentSlote->pPathFrequenciesList);
		FREE(ptCurrentSlote->pPathRangesList);
		
		PATH_Extract_Frequency_Ranges( pPathFrequencies , &(ptCurrentSlote->pPathFrequenciesList) , &(ptCurrentSlote->pPathRangesList) , &(ptCurrentSlote->iPathFreqNumberOfPoints) , &(ptCurrentSlote->iPathFreqNumberOfRanges));
			
		if ( pCurrentPathTestStepsQuantity )
		{
			ptCurrentSlote->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].iNumberOfTestSteps = *pCurrentPathTestStepsQuantity;	
		}
		
		if ( bSkipped == 0 )
		{
			if ( tMainStore.iSpecGroup == CALIBRATION_SPEC_GROUP )
			{
				FREE_CALLOC_COPY_STRING( ptCurrentSlote->pszPreviousCalibrationPathName , pCurrentPathName ); 
			
				if ( pPathPartAlias && ( strcmp( pPathPartAlias , "." )))
				{
					FREE_CALLOC_COPY_STRING( ptCurrentSlote->pszCurrentPathName , pPathPartAlias );
					FREE_CALLOC_COPY_STRING( ptCurrentSlote->pszPreviousPathName , pPathPartAlias ); 
				}
				else
				{
					FREE_CALLOC_COPY_STRING( ptCurrentSlote->pszCurrentPathName , pCurrentPathPartName );
					FREE_CALLOC_COPY_STRING( ptCurrentSlote->pszPreviousPathName , pCurrentPathPartName ); 
				}
			}
			else
			{
				FREE_CALLOC_COPY_STRING( ptCurrentSlote->pszCurrentPathName , pCurrentPathName );
				FREE_CALLOC_COPY_STRING( ptCurrentSlote->pszPreviousPathName , pCurrentPathName ); 
			}
		}
		
		FREE_CALLOC_COPY_STRING( ptCurrentSlote->pPathPartAlias , pPathPartAlias );
		FREE_CALLOC_COPY_STRING( ptCurrentSlote->pszCurrentPathDescription , pCurrentPathDescription );  
		FREE_CALLOC_COPY_STRING( ptCurrentSlote->pLastPathManualConnectionDescription , pPathManualConnectionDescription );
		
		CmtReleaseTSVPtr (handle);
	}
	
	FREE(pPathString);
	FREE(pStringArray);
	FREE(pPathFunction);
	FREE(pPathPartName);
	FREE(pPathPartAlias); 
	FREE(pCurrentPathName);
	FREE(pPathFrequencies);
	FREE(pPathDeviceAddress);
	FREE(pszPreviousPathName);
	FREE(pPathPartDescription);
	FREE(pCurrentPathPartName);
	FREE(pSkipSamePathIgnoration);
	FREE(pCurrentPathDescription);
	FREE(pCurrentPathPartDisabled);
	FREE(pPathManualConnectionPicture);
	FREE(pCurrentPathTestStepsQuantity);
	FREE(pDisablePopupPathInstructions);
	FREE(pCurrentPathCalibratableStatus);
	FREE(pPathManualConnectionDescription); 
	FREE(pLastPathManualConnectionDescription);
	
	return StdError;
}

STD_ERROR PATH_Devices_Apply_Post_Commands( int handle )			
{
	STD_ERROR										StdError													=	{0};

	int												iPathIndex													=	0, 
													iSlotIndex													=	0,  
													iEquipmentUseIndex											=	0,
													iSelectedTestIndex											=	0, 
													iCurrentFrequencyIndex										=	0;
													
	int												bEquipmentFound												=	0; 

	int												hMainHandle													=	0;
	
	tsMainStore										*pMainStore													=	NULL;

	tsSlotStore										*ptCurrentSlote												=	NULL;
	
	int												hUnitUnderTestModuleRefHandle								=	0;

	char											szDeviceAlias[LOW_STRING]									=	{0};  
	
	unsigned long long								ullLinkedID													=	0;
	
	double 											lfCurrentFrequency											=	0.0;
	
	int												iSlotNumber													=	0;
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote ));
	hMainHandle = ptCurrentSlote->hMainStoreHandle;
	iSelectedTestIndex = ptCurrentSlote->iCurrentTestIndex;   
	iSlotIndex = ptCurrentSlote->iSlotIndex;
	iPathIndex = ptCurrentSlote->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].iCurrentPathIndex;
	
	if (( ptCurrentSlote->bRunMultiThread ) || ( ptCurrentSlote->iSelectedNumberOfSlots > 1 ) || ( ptCurrentSlote->iMaxNumberOfSlotsToSelect > 1 ))
		iSlotNumber = ptCurrentSlote->iSlotIndex + 1;
	
	iCurrentFrequencyIndex = ptCurrentSlote->iCurrentFrequencyIndex; 
	
	if ( ptCurrentSlote->ptlFrequencies && ( iCurrentFrequencyIndex < ptCurrentSlote->ptlFrequencies->count))
		lfCurrentFrequency = ptCurrentSlote->ptlFrequencies->frequencies[iCurrentFrequencyIndex].frequency;
	
	CHK_CMT(CmtReleaseTSVPtr (handle)); 

	do
	{
		bEquipmentFound = 0;
		hUnitUnderTestModuleRefHandle = 0;
		
		if ( CmtGetTSVPtr ( hMainHandle , &pMainStore ) == 0 )
		{	   
			for ( ; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
				if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle )
					if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].type == EQUIPMENT_TYPE_STANDARD_DEVICE )  
					{
						bEquipmentFound = 1;
						
						hUnitUnderTestModuleRefHandle = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle;
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;
						
						strcpy( szDeviceAlias , pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias );
						
						
						break;
					}
					
			CmtReleaseTSVPtr ( hMainHandle );	
		}
				
		if ( hUnitUnderTestModuleRefHandle && bEquipmentFound )
		{
			//----------------- Global Commands ( Post Commands ) ---------------------------------//
			NO_CHK_STDERR( TE_EQUIP_Devices_Apply_PathCommands( hMainHandle , "Post_Connect" , iSelectedTestIndex , hUnitUnderTestModuleRefHandle , iPathIndex , iSlotNumber ));
		
			//----------------- Frequency Commands ( Post Commands )  ---------------------------------//
			if ( lfCurrentFrequency > 0.0 )
			{
				NO_CHK_STDERR( TE_EQUIP_Devices_Apply_FrequencyCommands( hMainHandle , "Post_Frequency" , iSelectedTestIndex , hUnitUnderTestModuleRefHandle , iCurrentFrequencyIndex , lfCurrentFrequency , iSlotNumber ));
			}
		}
		
		iEquipmentUseIndex++;
		
	} while( bEquipmentFound );
	
Error:

	return StdError;
}


STD_ERROR PATH_Devices_Apply_Auto_Commands( int handle )			
{
	STD_ERROR										StdError													=	{0};

	int												iPathIndex													=	0, 
													iSlotIndex													=	0,  
													iEquipmentUseIndex											=	0,
													iSelectedTestIndex											=	0, 
													iCurrentFrequencyIndex										=	0;
													
	int												bEquipmentFound												=	0; 

	int												hMainHandle													=	0;
	
	tsMainStore										*pMainStore													=	NULL;

	tsSlotStore										*ptCurrentSlote												=	NULL;
	
	int												hUnitUnderTestModuleRefHandle								=	0;

	char											szDeviceAlias[LOW_STRING]									=	{0};  
	
	unsigned long long								ullLinkedID													=	0;
	
	double 											lfCurrentFrequency											=	0.0;
	
	int												iSlotNumber													=	0;
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote ));
	hMainHandle = ptCurrentSlote->hMainStoreHandle;
	iSelectedTestIndex = ptCurrentSlote->iCurrentTestIndex;   
	iSlotIndex = ptCurrentSlote->iSlotIndex;
	iPathIndex = ptCurrentSlote->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].iCurrentPathIndex;
	
	if (( ptCurrentSlote->bRunMultiThread ) || ( ptCurrentSlote->iSelectedNumberOfSlots > 1 ) || ( ptCurrentSlote->iMaxNumberOfSlotsToSelect > 1 ))
		iSlotNumber = ptCurrentSlote->iSlotIndex + 1;
	
	iCurrentFrequencyIndex = ptCurrentSlote->iCurrentFrequencyIndex; 
	
	if ( ptCurrentSlote->ptlFrequencies && ( iCurrentFrequencyIndex < ptCurrentSlote->ptlFrequencies->count))
		lfCurrentFrequency = ptCurrentSlote->ptlFrequencies->frequencies[iCurrentFrequencyIndex].frequency;
	
	CHK_CMT(CmtReleaseTSVPtr (handle)); 

	do
	{
		bEquipmentFound = 0;
		hUnitUnderTestModuleRefHandle = 0;
		
		if ( CmtGetTSVPtr ( hMainHandle , &pMainStore ) == 0 )
		{	   
			for ( ; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
				if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle )
					if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].type == EQUIPMENT_TYPE_STANDARD_DEVICE )  
					{
						bEquipmentFound = 1;
						
						hUnitUnderTestModuleRefHandle = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle;
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;
						
						strcpy( szDeviceAlias , pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias );
						
						
						break;
					}
					
			CmtReleaseTSVPtr ( hMainHandle );	
		}
				
		if ( hUnitUnderTestModuleRefHandle && bEquipmentFound )
		{
			//----------------- Global Commands ( Post Commands ) ---------------------------------//
			//----------------- Global Commands ---------------------------------//
			
			NO_CHK_STDERR( TE_EQUIP_Devices_Apply_PathCommands( hMainHandle , "Auto_Connect" , iSelectedTestIndex , hUnitUnderTestModuleRefHandle , iPathIndex , iSlotNumber ));
			
			//----------------- Frequency Commands ---------------------------------//
			if ( lfCurrentFrequency > 0.0 )
			{
				NO_CHK_STDERR( TE_EQUIP_Devices_Apply_FrequencyCommands( hMainHandle , "Auto_Frequency" , iSelectedTestIndex , hUnitUnderTestModuleRefHandle , iCurrentFrequencyIndex , lfCurrentFrequency , iSlotNumber ));
			}
		}
		
		iEquipmentUseIndex++;
		
	} while( bEquipmentFound );
	
Error:

	return StdError;
}

STD_ERROR				PATH_Discard( int handle , int iSelectedTestIndex )			
{

	STD_ERROR						StdError											=	{0};

	path_func						fpCurrentPathFunction								=	NULL;   

	tsSlotStore						*ptCurrentSlote										=	NULL;

	HMODULE							dllPathHandle										=	NULL;
	
	void							*pPathApplyFunction									=	NULL;
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote ));
	dllPathHandle = ptCurrentSlote->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].dllPathHandle;
	pPathApplyFunction = ptCurrentSlote->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].pPathApplyFunction;
	CHK_CMT(CmtReleaseTSVPtr (handle)); 

	if ( dllPathHandle )
		fpCurrentPathFunction = (path_func) pPathApplyFunction;

	if ( fpCurrentPathFunction )
	{
		fpCurrentPathFunction( NULL  , NULL , NULL , NULL );
	
		FreeLibrary( dllPathHandle );
	}
		
Error:

	return StdError;
}

STD_ERROR				PATH_SetDirectCommand( int handle , char *pCommand , char **pRespondsString )			
{

	STD_ERROR						StdError											=	{0};

	path_func						fpCurrentPathFunction								=	NULL;   

	tsSlotStore						*ptCurrentSlote										=	NULL;

	HMODULE							dllPathHandle										=	NULL;
	
	void							*pPathApplyFunction									=	NULL;

	int								iSelectedTestIndex									=	0;
	
	int								hPathModuleRefHandle								=	0;
	
	IF (( pCommand == NULL ) , "Command is empty" );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote ));
	iSelectedTestIndex = ptCurrentSlote->iCurrentTestIndex;   
	dllPathHandle = ptCurrentSlote->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].dllPathHandle;
	pPathApplyFunction = ptCurrentSlote->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].pPathApplyFunction;
	hPathModuleRefHandle = ptCurrentSlote->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].hPathModuleRefHandle;
	CHK_CMT(CmtReleaseTSVPtr (handle)); 

	if ( dllPathHandle )
		fpCurrentPathFunction = (path_func) pPathApplyFunction;

	if ( fpCurrentPathFunction )
	{  
		IF ((fpCurrentPathFunction(&(hPathModuleRefHandle) , NULL , pCommand , pRespondsString )) , "Error set command" );
	}
		
Error:
	
	return StdError;
}


STD_ERROR		PATH_Extract_Frequency_Ranges( char *pRangesString , double **pFrequencyList , int **pRangesList , int *piNumberOfPoints , int *piNumberOfRanges ) // sample "1E9,2E9-8E9:50"
{
	STD_ERROR									StdError								=	{0};
	
	char										*pNext									=	NULL,
												*pTemp									=	NULL,
												*pCurrnet								=	NULL;
	
	double										lfStart									=	0.0,
												lfStop									=	0.0,
												lfCurrent								=	0.0,
												lfStep									=	0.0;
	
	int											iRangeLength							=	0,
												iNumberOfPoints							=	0,
												iAllocatePoints							=	0;
												
	int											iCurrentIndex							=	0,
												iIndex									=	0;
	
	double										*pvlfFrequencyList						=	NULL;
	
	int											*pviRangesList							=	NULL;
	
	int											iRangeIndex								=	0,
												iPreviousRange							=	0; 
	
	char										*pTempString							=	NULL;
						
	
	CALLOC_COPY_STRING_ERR( pTempString , pRangesString );
	
	pNext = pTempString;
	
	while(pNext)
	{ 
		pTemp = strchr( pNext , ',');
		pNext = NULL;
		
		if ( pTemp )
		{
			pNext = pTemp; 
			*pTemp = 0;	
			pNext++;
			iAllocatePoints++;
		}
	};
	
	FREE_CALLOC_COPY_STRING_ERR( pTempString , pRangesString );   
	pNext = pTempString;  
	
	while(pNext)
	{ 
		pTemp = strchr( pNext , ':');
		pNext = NULL;
		
		if ( pTemp )
		{
			pNext = pTemp;
			*pTemp = 0;	
			pNext++;
			
			iAllocatePoints += atoi(pNext);
		}
	};
		   
	if ( iAllocatePoints )
	{
		iAllocatePoints += 32;
		
		CALLOC_ERR( pvlfFrequencyList , iAllocatePoints , sizeof(double));
		CALLOC_ERR( pviRangesList , iAllocatePoints , sizeof(int));     
	}
	
	FREE_CALLOC_COPY_STRING_ERR( pTempString , pRangesString );   
	pNext = pTempString;   
	
	while(pNext)
	{ 
		iNumberOfPoints++;	
		
		if ( iAllocatePoints <= iNumberOfPoints )
		{
			iAllocatePoints = (iAllocatePoints * 2) + 32;
			pvlfFrequencyList = realloc( pvlfFrequencyList , ( iAllocatePoints * sizeof(double)));
			pviRangesList = realloc( pviRangesList , ( iAllocatePoints * sizeof(int)));     
		}
		
		pTemp = strchr( pNext , ',');
		
		pCurrnet = pNext;
		pNext = pTemp; 
		
		if ( pTemp )
		{
			*pTemp = 0;	
			pNext++;
		}
		
		pTemp = strchr( pCurrnet , '-');
		
		if ( pTemp )
		{   //-------- Range --------//
			*pTemp = 0;
			
			lfStart = atof(pCurrnet); 
			
			pCurrnet = pTemp+1;  
			
			pTemp = strchr( pCurrnet , ':');  
			
			if ( pTemp == NULL )
				continue;
			
			*pTemp = 0; 
			
			lfStop = atof(pCurrnet);
			
			pCurrnet = pTemp+1; 
			
			iRangeLength = atoi(pCurrnet); 

			iNumberOfPoints += iRangeLength;
			
			if ( iAllocatePoints <= iNumberOfPoints )
			{
				iAllocatePoints += iNumberOfPoints;
				pvlfFrequencyList = realloc( pvlfFrequencyList , ( iAllocatePoints * sizeof(double)));
				pviRangesList = realloc( pviRangesList , ( iAllocatePoints * sizeof(int)));     
			}
		
			lfStep = ( lfStop - lfStart ) / ( iRangeLength - 1 );
			lfCurrent = lfStart;
			
			for ( iIndex = 0; iIndex < iRangeLength; iIndex++ )
			{
				pviRangesList[iCurrentIndex] = iRangeIndex;
				pvlfFrequencyList[iCurrentIndex++] = lfCurrent;
				lfCurrent += lfStep;
				
				iPreviousRange = iRangeIndex;
			}
			
			iRangeIndex++;
		}
		else
		{
			pvlfFrequencyList[iCurrentIndex++] = atof(pCurrnet);  	
		}
		
	};
	
Error:
	
	if ( piNumberOfPoints )
		*piNumberOfPoints = iCurrentIndex;
	
	if ( piNumberOfRanges )
		*piNumberOfRanges = iRangeIndex;
	
	if ( pFrequencyList )
	{
		FREE(*pFrequencyList);
		
		*pFrequencyList = pvlfFrequencyList;
	}
	else
	{
		FREE(pvlfFrequencyList);
	}
	
	if ( pRangesList )
	{
		FREE(*pRangesList);
		
		*pRangesList = pviRangesList;
	}
	else
	{
		FREE(pviRangesList);
	}
	
	FREE(pTempString);
	
	return StdError;			
}

