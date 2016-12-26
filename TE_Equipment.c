//==============================================================================
// Include files
#include "Windows.h"
#include "TE_Equipment.h"
#include "GlobalDefines.h"
#include <utility.h>
#include "dblayer.h"
#include "defines.h"
#include "TE_GlobalDefines.h"
#include "TEST_EXEC_UI.h"
#include "var.h"
#include "formatio.h" 
#include "MathLibrary.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

typedef int 		(*tfDRIVER_MANAGER_GetErrorTextMessage) ( int Handle , int iError , char **pErrorMessage );

typedef STD_ERROR   (*tfDRIVER_MANAGER_STD_Init)( char *pszDriverLocation , int iDeviceID , char *pszConnectionName , char *pszAddress , int *pHandle , ... );
typedef STD_ERROR   (*tfDRIVER_MANAGER_Init) ( char *pszDriverLocation , char *pszAddressString , int *pHandle );
typedef STD_ERROR   (*tfDRIVER_MANAGER_Close) ( int *pHandle );
typedef STD_ERROR   (*tfDRIVER_MANAGER_Reset) ( int Handle );

typedef STD_ERROR   (*tfDRIVER_MANAGER_STD_LoadConfigFile)( int hHandle , char *pFileName );
typedef STD_ERROR   (*tfDRIVER_MANAGER_STD_Get_Commands_List)( int Handle , char ***pCommandsList , int *piNumberOfCommands );
typedef STD_ERROR   (*tfDRIVER_MANAGER_STD_Check_Connection)( int hHandle , char *pCommandName , int *piStatus );

typedef int			(*tfDRIVER_MANAGER_SETUP_UpdateCallbacksStructure)( void *pSTD_SetCallBackSet , int iNumberOfParams , ... );

typedef int 		(*tfDRIVER_MANAGER_Set_Calibration_Port_Number)( int Handle , int iCalibrationPortNumber );  
typedef int 		(*tfDRIVER_MANAGER_Get_Number_Of_Channels)( int Handle , int *piNumberOfChannels );
typedef STD_ERROR   (*tfDRIVER_MANAGER_PowerMeter_Calibrate)( int Handle , int iChannel );
typedef STD_ERROR   (*tfDRIVER_MANAGER_CALIBRATION_FillCalibrationRanges)( int Handle , char *pRangesString );
typedef int 		(*tfDRIVER_MANAGER_Set_Calibration_Power)( int Handle , double lfSetPower );
typedef int 		(*tfDRIVER_MANAGER_Set_Calibration_MeasureDelay)( int Handle , double lfMeasureDelay );
typedef STD_ERROR   (*tfDRIVER_MANAGER_CALIBRATION_Run)( int StimulusHandle , int MeasureHandle , int StoreHandle , int iProgressPanel , int iProgressControl );
typedef STD_ERROR   (*tfDRIVER_MANAGER_CALIBRATION_GetCalibrationInfo)( int Handle , double **plfFrequency , double **plfLoss , int *piNumberOfPoints , double *plfStartFrequnecy , double *plfStopFrequency );
typedef STD_ERROR   (*tfDRIVER_MANAGER_PowerMeter_SetFrequency)( int Handle , int iChannel , double lfFrequency );
typedef STD_ERROR   (*tfDRIVER_MANAGER_CALIBRATION_FillCalibrationInfo)( int Handle , double *plfFrequency , double *plfLoss , int iNumberOfPoints , double lfStartFrequnecy , double lfStopFrequency );
typedef int 		(*tfDRIVER_MANAGER_Set_Calibration_StateFileName)( int Handle , char *pStateFileName );
typedef int 		(*tfDRIVER_MANAGER_Set_Calibration_ReferenceLevel)( int Handle , double lfReferenceLevel );
typedef int 		(*tfDRIVER_MANAGER_Set_Calibration_Attenuator)( int Handle , double lfAttenuator );  
typedef int 		(*tfDRIVER_MANAGER_Get_SimulationMode)( int Handle , int *piSimulationMode );

typedef STD_ERROR   (*tfDRV_NetworkAnalyzer_Calibration_SetFrequencyPlan)( int Handle , double lfStartFrequncy , double lfStopFrequency , double lfPowerLevel , double lfReferenceLevel , int iNumberOfPoints );

typedef STD_ERROR   (*tfDRIVER_MANAGER_CALIBRATION_Fill_AdditionalPower_CalibrationInfo)( int Handle , double lfPower , double *plfLoss , int iNumberOfPoints );
typedef STD_ERROR   (*tfDRIVER_MANAGER_CALIBRATION_Get_AdditionalPower_CalibrationInfo)( int Handle , int iPowerIndex , double **plfLoss , int *piNumberOfPoints , double *plfPower );
typedef STD_ERROR   (*tfDRIVER_MANAGER_CALIBRATION_Set_NumberOf_AdditionalPower)( int Handle , double *plfPowerList , int iNumberOfPowers );
typedef STD_ERROR   (*tfDRIVER_MANAGER_CALIBRATION_Gel_3D_Factor)( int Handle , double lfPower , double lfFrequency , double *plfFactor );

typedef STD_ERROR   (*tfDRV_NetworkAnalyzer_SaveStateAndCalibration)( int Handle , char *pFileName ); 
typedef STD_ERROR   (*tfDRV_NetworkAnalyzer_LoadStateAndCalibration)( int Handle , char *pFileName );
typedef STD_ERROR   (*tfDRV_NetworkAnalyzer_ECAL_Calibrate)( int Handle , char *pszPortList , char *pUserCal , double lfTimeout ); 

typedef STD_ERROR   (*tfDRIVER_MANAGER_CALIBRATION_GetCalibrationRangeInfo)( int Handle , double *plfStart , double *plfStop , int *piNumberOfPoints ); 

typedef STD_ERROR   (*tfDRIVER_MANAGER_CALIBRATION_CreateEmptyHandle)( int *pHandle ); 
typedef STD_ERROR   (*tfDRIVER_MANAGER_CALIBRATION_DiscardHandle)( int *pHandle ); 

typedef STD_ERROR   (*tfDRIVER_MANAGER_StandardDevice_SetValue)( int hHandle , char *pCommandName , void *pValue , int iValueLength , int  iValueSize, ...  ); 

typedef STD_ERROR   (*tfDRIVER_MANAGER_StandardDevice_SetListOfValues)( int Handle , char *pCommandsList , int bCheckResponds , int iNumberOfRetries );

typedef STD_ERROR   (*tfDRIVER_MANAGER_GetEquipmentInformation)( int hHandle , char **pVendor , char **pSerialNumber , char **pModel , char **pFirmware );

typedef	int			(*tfDRIVER_MANAGER_GetDriversFileList)( char *pRootDirectory , char ***pDriversList , int **pDriversTypes , int *pCount );

typedef STD_ERROR   (*tfDRIVER_MANAGER_CheckEquipmentDriverCompatibility)( char *pszDriverLocation , char *pszAddressString , int *pStatus , char **pVendor , char **pSerialNumber , char **pModel , char **pFirmware  , char **pIDN , char **pID_Responds );

typedef STD_ERROR   (*tfDRV_SpectrumAnalyzer_AlignNow)( int Handle , double lfTimeout );

typedef STD_ERROR   (*tfDRIVER_MANAGER_Equipment_BrowseSelectStateFiles)( int hHandle , char *pStoreFilePath , int *piNumberOfSelectedFiles , char ***pvszSelectedFileNamesList , int **pvszSelectedFileSizesList );

typedef STD_ERROR   (*tfDRIVER_MANAGER_UpdateIgnoreDuplicationAddresses)( int hHandle );


typedef struct
{
	tEquipment							*equipmentForInit;
	
	STD_ERROR							StdError;
	
	int									bPassStatus,
										bSkipRunning,
										hPanelEquipment;
	
	int									hLockHandle;
	
	int									hMainHandle,
										hDatabaseHandle;
	
	HINSTANCE							hDriverManagerLibrary;
	
	int									iEquipmentIndex;
	
} tsInitBlockMemory;

//==============================================================================
// Global functions

int	 FillCallbacksDataStructureOnly( int MainHandle , void	**pCallBackStructure , unsigned long long ullDataBaseLinkID );

//==============================================================================

int CVICALLBACK RUN_MultiInitThread( void *pData ) 
{
	STD_ERROR															StdError															=	{0};

	tsInitBlockMemory													*pInitBlockMemory													=	NULL;
	
	int																	iCheckDeviceIndex													=	0;
																		
	tfDRIVER_MANAGER_GetErrorTextMessage								fDRIVER_MANAGER_GetErrorTextMessage									=	NULL;
	tfDRIVER_MANAGER_STD_Init											fDRIVER_MANAGER_STD_Init											=	NULL;  
	tfDRIVER_MANAGER_Init												fDRIVER_MANAGER_Init												=	NULL;
	tfDRIVER_MANAGER_Reset												fDRIVER_MANAGER_Reset												=	NULL;

	tfDRIVER_MANAGER_STD_LoadConfigFile									fDRIVER_MANAGER_STD_LoadConfigFile									=	NULL;
	tfDRIVER_MANAGER_STD_Get_Commands_List								fDRIVER_MANAGER_STD_Get_Commands_List								=	NULL;
	tfDRIVER_MANAGER_STD_Check_Connection								fDRIVER_MANAGER_STD_Check_Connection								=	NULL;
	tfDRIVER_MANAGER_SETUP_UpdateCallbacksStructure						fDRIVER_MANAGER_SETUP_UpdateCallbacksStructure						=	NULL;
	tfDRIVER_MANAGER_Get_SimulationMode									fDRIVER_MANAGER_Get_SimulationMode									=	NULL;
	
	tfDRIVER_MANAGER_Set_Calibration_Power								fDRIVER_MANAGER_Set_Calibration_Power              					=	NULL;
	tfDRIVER_MANAGER_CALIBRATION_FillCalibrationInfo					fDRIVER_MANAGER_CALIBRATION_FillCalibrationInfo						=	NULL;
	
	tfDRIVER_MANAGER_CALIBRATION_Fill_AdditionalPower_CalibrationInfo   fDRIVER_MANAGER_CALIBRATION_Fill_AdditionalPower_CalibrationInfo	=	NULL;
	
	tfDRIVER_MANAGER_UpdateIgnoreDuplicationAddresses					fDRIVER_MANAGER_UpdateIgnoreDuplicationAddresses						=	NULL;
	
	char																*pFilePathName														=	NULL,
																		*pSubDriverFilePathName												=	NULL; 
																		
	char																szMessage[LOW_STRING]												=	{0},
																		szFormatedString[LOW_STRING]										=	{0};
																		
	unsigned long long													ulCommandID															=	0;
	
	char																**vszSTD_Device_Commands_List										=	NULL;
	int																	iNumberOfSTD_Device_Commands										=	0,
																		bCheckDeviceStatus													=	0;
	
	int																	hDefaultRfBoxHandle													=	0;
																		
	double																*plfCalibration_PowersList											=	NULL, 
																		*plfCalibration_Power												=	NULL;
																
	int																	iSimulationMode														=	0, 
																		iPowerIndex															=	0;
																		
	double																*pCalibFrequencyList												=	NULL,
																		*pCalibFactorList													=	NULL;
																	
	int																	iNumberOfPowers														=	0,
																		iNumOfCalibPoints													=	0; 
																		
	double																lfLastCalibrationDate												=	0.0;   
	
	void																*pCallBackStructure													=	NULL;
	
	int																	*pRFBoxUnitsList													=	NULL;
	
	pInitBlockMemory = pData;
	
	if ( pInitBlockMemory == NULL )
		return 0;

	//----------------------------------- Initialization -----------------------------------------//
	
	fDRIVER_MANAGER_CALIBRATION_FillCalibrationInfo = (tfDRIVER_MANAGER_CALIBRATION_FillCalibrationInfo) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRIVER_MANAGER_CALIBRATION_FillCalibrationInfo" );                 
	
	fDRIVER_MANAGER_CALIBRATION_Fill_AdditionalPower_CalibrationInfo = (tfDRIVER_MANAGER_CALIBRATION_Fill_AdditionalPower_CalibrationInfo) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRIVER_MANAGER_CALIBRATION_Fill_AdditionalPower_CalibrationInfo" );
	
	fDRIVER_MANAGER_Set_Calibration_Power = (tfDRIVER_MANAGER_Set_Calibration_Power) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRIVER_MANAGER_Set_Calibration_Power" );                        
	
	fDRIVER_MANAGER_SETUP_UpdateCallbacksStructure = (tfDRIVER_MANAGER_SETUP_UpdateCallbacksStructure) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRIVER_MANAGER_SETUP_UpdateCallbacksStructure" );
	
	fDRIVER_MANAGER_Get_SimulationMode = (tfDRIVER_MANAGER_Get_SimulationMode) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRIVER_MANAGER_Get_SimulationMode" );

	UPDATERR( GetDataBaseFileByID( pInitBlockMemory->hDatabaseHandle , pInitBlockMemory->equipmentForInit->driverlink , NULL , NULL , NULL  , NULL , &pFilePathName ));

	// fill driver manager call back data  
	FillCallbacksDataStructureOnly( pInitBlockMemory->hMainHandle , &pCallBackStructure , pInitBlockMemory->equipmentForInit->id ); 

	fDRIVER_MANAGER_SETUP_UpdateCallbacksStructure( pCallBackStructure , 2 , pInitBlockMemory->equipmentForInit->address , pInitBlockMemory->equipmentForInit->id );

	FREE(pCallBackStructure);  
	
	if ( IS_NOT_OK )
	{
		sprintf( szMessage , "File Driver is not found for equipment %s" , pInitBlockMemory->equipmentForInit->name );
	}
	else
	{
		if ( pInitBlockMemory->equipmentForInit->depends_on_power )
		{
			RETURN;	
		}
		
		if ( pInitBlockMemory->equipmentForInit->driverchildlink )
		{
			UPDATERR( GetDataBaseFileByID( pInitBlockMemory->hDatabaseHandle , pInitBlockMemory->equipmentForInit->driverchildlink , NULL , NULL , NULL  , NULL , &pSubDriverFilePathName )); 	
			
			if ( IS_OK && pSubDriverFilePathName )
			{
				if ( FileExists( pSubDriverFilePathName , NULL ))	
				{
					LoadLibrary ( pSubDriverFilePathName ); 	
				}
			}
			
			FREE(pSubDriverFilePathName);
		}
		
		switch(pInitBlockMemory->equipmentForInit->type)
		{
			case EQUIPMENT_TYPE_STANDARD_DEVICE:	
		
				fDRIVER_MANAGER_STD_Init = (tfDRIVER_MANAGER_STD_Init) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_StandardDevice_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_StandardDevice_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_StandardDevice_GetErrorTextMessage" ); 
			
				fDRIVER_MANAGER_STD_LoadConfigFile = (tfDRIVER_MANAGER_STD_LoadConfigFile) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_StandardDevice_LoadConfigFile" );		
				fDRIVER_MANAGER_STD_Get_Commands_List = (tfDRIVER_MANAGER_STD_Get_Commands_List) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_StandardDevice_Get_Commands_List" );	
				fDRIVER_MANAGER_STD_Check_Connection = (tfDRIVER_MANAGER_STD_Check_Connection) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_StandardDevice_Check_Connection" );	
			
				fDRIVER_MANAGER_UpdateIgnoreDuplicationAddresses = (tfDRIVER_MANAGER_UpdateIgnoreDuplicationAddresses) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_StandardDevice_UpdateIgnoreDuplicationAddresses" );

				if (( strchr( pInitBlockMemory->equipmentForInit->id_command , 'x' )) || ( strchr( pInitBlockMemory->equipmentForInit->id_command , 'X' )) )
					sscanf( pInitBlockMemory->equipmentForInit->id_command , "%llx" , &ulCommandID );
				else
					ulCommandID = atol(pInitBlockMemory->equipmentForInit->id_command);
				
				UPDATERR( fDRIVER_MANAGER_STD_Init( pFilePathName , (int)ulCommandID , pInitBlockMemory->equipmentForInit->alias , pInitBlockMemory->equipmentForInit->address , &( pInitBlockMemory->equipmentForInit->handle ) , 1 , 1 ));

				if ( pInitBlockMemory->equipmentForInit->dup_address )
				{
					fDRIVER_MANAGER_UpdateIgnoreDuplicationAddresses( pInitBlockMemory->equipmentForInit->handle );
				}
				
				if (( IS_OK ) && ( pInitBlockMemory->equipmentForInit->configlink )) 
				{
					UPDATERR( GetDataBaseFileByID( pInitBlockMemory->hDatabaseHandle , pInitBlockMemory->equipmentForInit->configlink , NULL , NULL , NULL  , NULL , &pFilePathName )); 
				
					if ( IS_OK )
					{
						UPDATERR( fDRIVER_MANAGER_STD_LoadConfigFile( pInitBlockMemory->equipmentForInit->handle , pFilePathName ));
					}
					
					if ( pInitBlockMemory->equipmentForInit->check_commands )
					{
						if ( IS_OK )
						{
							UPDATERR( fDRIVER_MANAGER_STD_Get_Commands_List( pInitBlockMemory->equipmentForInit->handle , &vszSTD_Device_Commands_List , &iNumberOfSTD_Device_Commands ));
						}
					
						if ( IS_OK )
						{
							for ( iCheckDeviceIndex = 0; iCheckDeviceIndex < iNumberOfSTD_Device_Commands; iCheckDeviceIndex++ )
							{
								if ( vszSTD_Device_Commands_List[iCheckDeviceIndex] && strlen(vszSTD_Device_Commands_List[iCheckDeviceIndex]) && ( vszSTD_Device_Commands_List[iCheckDeviceIndex][0] != '-' ))
								{
									CHK_STDERR_BREAK( fDRIVER_MANAGER_STD_Check_Connection ( pInitBlockMemory->equipmentForInit->handle , vszSTD_Device_Commands_List[iCheckDeviceIndex] , &bCheckDeviceStatus ));
							
									if ( bCheckDeviceStatus == 0 )
									{
										sprintf( szMessage , "Command [%s] is not initializet yet!!!" , vszSTD_Device_Commands_List[iCheckDeviceIndex] );
									
										IF (( ConfirmPopup(szMessage,"Do you want to continue?") == 0 ) , szMessage );
									}
								}
							}
						}
					}
				}
				
				if ( pRFBoxUnitsList && ( pRFBoxUnitsList[0] == pInitBlockMemory->equipmentForInit->id ))
					hDefaultRfBoxHandle = pInitBlockMemory->equipmentForInit->handle;
					
				break;
			 
			case EQUIPMENT_TYPE_POWER_SUPPLY:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_PowerSupply_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_PowerSupply_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_PowerSupply_GetErrorTextMessage" ); 
			
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , pInitBlockMemory->equipmentForInit->address , &( pInitBlockMemory->equipmentForInit->handle )));

				break;
			 
			case EQUIPMENT_TYPE_NETWORK_ANALYZER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_NetworkAnalyzer_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_NetworkAnalyzer_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_NetworkAnalyzer_GetErrorTextMessage" ); 
			
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , pInitBlockMemory->equipmentForInit->address , &( pInitBlockMemory->equipmentForInit->handle )));

				break;
			 
			case EQUIPMENT_TYPE_SIGNAL_GENERATOR:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_SignalGenerator_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_SignalGenerator_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_SignalGenerator_GetErrorTextMessage" ); 
			
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , pInitBlockMemory->equipmentForInit->address , &( pInitBlockMemory->equipmentForInit->handle )));

				break;
			 
			case EQUIPMENT_TYPE_SPECTRUM_ANALYZER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_SpectrumAnalyzer_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_SpectrumAnalyzer_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_SpectrumAnalyzer_GetErrorTextMessage" ); 
			
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , pInitBlockMemory->equipmentForInit->address , &( pInitBlockMemory->equipmentForInit->handle )));

				break;
			 
			case EQUIPMENT_TYPE_OSCILLOSCOPE:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_Oscilloscope_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_Oscilloscope_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_Oscilloscope_GetErrorTextMessage" ); 
			
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , pInitBlockMemory->equipmentForInit->address , &( pInitBlockMemory->equipmentForInit->handle )));

				break;
			 
			case EQUIPMENT_TYPE_FUNCTION_GENERATOR:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_FunctionGenerator_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_FunctionGenerator_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_FunctionGenerator_GetErrorTextMessage" ); 

				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , pInitBlockMemory->equipmentForInit->address , &( pInitBlockMemory->equipmentForInit->handle )));

				break;
			 
			case EQUIPMENT_TYPE_POWER_METER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_PowerMeter_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_PowerMeter_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_PowerMeter_GetErrorTextMessage" ); 

				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , pInitBlockMemory->equipmentForInit->address , &( pInitBlockMemory->equipmentForInit->handle )));

				break;
			 
			case EQUIPMENT_TYPE_NOISE_FIGURE:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_NoiseFigure_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_NoiseFigure_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_NoiseFigure_GetErrorTextMessage" ); 

				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , pInitBlockMemory->equipmentForInit->address , &( pInitBlockMemory->equipmentForInit->handle )));
			
				break;
			 
			case EQUIPMENT_TYPE_MULTI_METER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_MultiMeter_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_MultiMeter_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_MultiMeter_GetErrorTextMessage" ); 

				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , pInitBlockMemory->equipmentForInit->address , &( pInitBlockMemory->equipmentForInit->handle )));
			
				break;
			 
			case EQUIPMENT_TYPE_WAVE_FORM_ANALYZER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_WaveAnalyzer_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_WaveAnalyzer_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( pInitBlockMemory->hDriverManagerLibrary , "DRV_WaveAnalyzer_GetErrorTextMessage" ); 
		
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , pInitBlockMemory->equipmentForInit->address , &( pInitBlockMemory->equipmentForInit->handle )));
			
				break;
		
			default:
			
				break;
		}
	}
	
	if ( IS_OK )
	{
		if ( pInitBlockMemory->equipmentForInit->handle == 0 )
		{
			SET_ERR( -23 , "Wrong Driver Initialization." );
		}
	}
	
	if ( IS_OK )
	{
		NO_CHK_STDERR( fDRIVER_MANAGER_Reset( pInitBlockMemory->equipmentForInit->handle ));	
		
		FREE( plfCalibration_Power );
		FREE( pCalibFrequencyList );
		FREE( pCalibFactorList );
		iNumOfCalibPoints = 0;
		lfLastCalibrationDate = 0.0;
		
		VarGetCalibration( pInitBlockMemory->hMainHandle , VAR_CONFIG_EQUIPMENT , pInitBlockMemory->equipmentForInit->id , 0 , "Calibration" , &pCalibFrequencyList , &pCalibFactorList , &iNumOfCalibPoints , &lfLastCalibrationDate );    
		
		NO_CHK_STDERR( fDRIVER_MANAGER_CALIBRATION_FillCalibrationInfo( pInitBlockMemory->equipmentForInit->handle , pCalibFrequencyList , pCalibFactorList , iNumOfCalibPoints , 0.0 , 0.0 )); 
		
		if ( VarGetDouble( pInitBlockMemory->hMainHandle , VAR_CONFIG_EQUIPMENT , pInitBlockMemory->equipmentForInit->id , "Calibration_Power" , &plfCalibration_Power ) == 0 )
		{
			CALLOC( plfCalibration_Power , 1 , sizeof(double));

			if ( plfCalibration_Power )
			{
				VarSetDouble( pInitBlockMemory->hMainHandle , VAR_CONFIG_EQUIPMENT , pInitBlockMemory->equipmentForInit->id , "Calibration_Power" , 1 , plfCalibration_Power );  
			}
		}
			
		if ( plfCalibration_Power )
		{
			fDRIVER_MANAGER_Set_Calibration_Power( pInitBlockMemory->equipmentForInit->handle , (*plfCalibration_Power) );
		}
				
		iNumberOfPowers = VarGetDouble( pInitBlockMemory->hMainHandle , VAR_CONFIG_EQUIPMENT , pInitBlockMemory->equipmentForInit->id , "Calibration_AdditionalPowers" , &plfCalibration_PowersList );
		
		if ( iNumberOfPowers == 0 )
		{
			CALLOC( plfCalibration_PowersList , 1 , sizeof(double));

			if ( plfCalibration_PowersList )
			{
				VarSetDouble( pInitBlockMemory->hMainHandle , VAR_CONFIG_EQUIPMENT , pInitBlockMemory->equipmentForInit->id , "Calibration_AdditionalPowers" , 1 , plfCalibration_PowersList );  
				iNumberOfPowers++;
			}
		}
		
		if ( iNumberOfPowers )
		{
			if (( iNumberOfPowers > 1 ) || ( plfCalibration_PowersList[0] != plfCalibration_Power[0] ))
			{
				for ( iPowerIndex = 0; iPowerIndex < iNumberOfPowers; iPowerIndex++ )
				{
					FREE( pCalibFrequencyList );
					FREE( pCalibFactorList );
					iNumOfCalibPoints = 0;
					lfLastCalibrationDate = 0.0;
		
					sprintf( szFormatedString , "Calibration%d" , (iPowerIndex+1) );
					VarGetCalibration( pInitBlockMemory->hMainHandle , VAR_CONFIG_EQUIPMENT , pInitBlockMemory->equipmentForInit->id , 0 , szFormatedString , &pCalibFrequencyList , &pCalibFactorList , &iNumOfCalibPoints , &lfLastCalibrationDate );    

					NO_CHK_STDERR( fDRIVER_MANAGER_CALIBRATION_Fill_AdditionalPower_CalibrationInfo( pInitBlockMemory->equipmentForInit->handle , plfCalibration_PowersList[iPowerIndex] , pCalibFactorList , iNumOfCalibPoints )); 
				}
			}
			
			FREE(plfCalibration_PowersList);
		} 
	}

Error:
	
	if ( IS_OK )
	{
		pInitBlockMemory->bPassStatus = 1;

		memcpy( &(pInitBlockMemory->StdError) , &StdError , sizeof(STD_ERROR) );
	}
	
	if ( CmtGetLock ( pInitBlockMemory->hLockHandle ) == 0 )
	{
		if ( pInitBlockMemory->equipmentForInit->depends_on_power == 0 )
		{
			//SetActivePanel ( pInitBlockMemory->hPanelEquipment );  
			SetActiveTableCell ( pInitBlockMemory->hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(3,(pInitBlockMemory->iEquipmentIndex+1)) );       
	
			if ( IS_OK ) 
			{
				fDRIVER_MANAGER_Get_SimulationMode( pInitBlockMemory->equipmentForInit->handle , &iSimulationMode );

				SetTableCellAttribute ( pInitBlockMemory->hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (3,(pInitBlockMemory->iEquipmentIndex+1)), ATTR_TEXT_COLOR, VAL_DK_GREEN ); 
			
				if ( iSimulationMode )
				{
					SetTableCellVal ( pInitBlockMemory->hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(3,(pInitBlockMemory->iEquipmentIndex+1)), "DEMO" );   						
				}
				else
				{
					SetTableCellVal ( pInitBlockMemory->hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(3,(pInitBlockMemory->iEquipmentIndex+1)), "PASS" );   						
				}	
			}
			else
			{
				SetTableCellAttribute ( pInitBlockMemory->hPanelEquipment, EQUIP_INIT_TABLE ,MakePoint (3,(pInitBlockMemory->iEquipmentIndex+1)), ATTR_TEXT_COLOR,VAL_DK_RED); 
				SetTableCellVal ( pInitBlockMemory->hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(3,(pInitBlockMemory->iEquipmentIndex+1)), "FAIL" );  
				pInitBlockMemory->bSkipRunning = 1; 
			}
		}
		else
		{
			SetTableCellAttribute ( pInitBlockMemory->hPanelEquipment, EQUIP_INIT_TABLE ,MakePoint (1,(pInitBlockMemory->iEquipmentIndex+1)), ATTR_TEXT_COLOR,VAL_DK_GRAY);
			SetTableCellAttribute ( pInitBlockMemory->hPanelEquipment, EQUIP_INIT_TABLE ,MakePoint (2,(pInitBlockMemory->iEquipmentIndex+1)), ATTR_TEXT_COLOR,VAL_DK_GRAY); 
			SetTableCellAttribute ( pInitBlockMemory->hPanelEquipment, EQUIP_INIT_TABLE ,MakePoint (3,(pInitBlockMemory->iEquipmentIndex+1)), ATTR_TEXT_COLOR,VAL_DK_GRAY); 
			SetTableCellVal ( pInitBlockMemory->hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(3,(pInitBlockMemory->iEquipmentIndex+1)), "SKIP" );   						
		}
		
		CmtReleaseLock ( pInitBlockMemory->hLockHandle );
		
		ProcessDrawEvents();
	}
	
	FREE( plfCalibration_Power );
	FREE( pCalibFrequencyList );
	FREE( pCalibFactorList );
	FREE( pFilePathName );	
	
	FREE_LIST( vszSTD_Device_Commands_List , iNumberOfSTD_Device_Commands );   
	
	RETURN_ERROR_VALUE;
}

STD_ERROR		TE_EQUIP_RunInitialization( int hMainHandle , int *pbSkipRunning , int bRunAutoSelectionOnly )
{	
	STD_ERROR															StdError															=	{0};
	
	tlEquipmentUse														*equipmentUseList													=	NULL;

	tlEquipment															*equipmentList														=	NULL;
	
	tEquipment															**equipmentForInit													=	NULL;
	
	tsMainStore															*pMainStore															=	NULL,
																		tMainStore															=	{0}; 
	
	int																	index																=	0,
																		iIndex																=	0, 
																		iPlotIndex															=	0, 
																		iEquipmentIndex														=	0,
																		iPathCommandIndex													=	0, 
																		iDuplicationsIndex													=	0,
																		iEquipmentUseIndex													=	0,
																		iEquipmentUseSelectIndex											=	0,
																		iCalibrationSequenceIndex											=	0;
																		
	int																	hPanelEquipment														=	0;
	
	int																	iEquipmentCount														=	0;
	
	tfDRIVER_MANAGER_Get_SimulationMode									fDRIVER_MANAGER_Get_SimulationMode									=	NULL;
	
	tfDRIVER_MANAGER_Set_Calibration_Port_Number						fDRIVER_MANAGER_Set_Calibration_Port_Number        					=	NULL;
	tfDRIVER_MANAGER_Get_Number_Of_Channels								fDRIVER_MANAGER_Get_Number_Of_Channels             					=	NULL;
	tfDRIVER_MANAGER_PowerMeter_Calibrate								fDRIVER_MANAGER_PowerMeter_Calibrate               					=	NULL;
	tfDRIVER_MANAGER_CALIBRATION_FillCalibrationRanges					fDRIVER_MANAGER_CALIBRATION_FillCalibrationRanges  					=	NULL;
	tfDRIVER_MANAGER_Set_Calibration_Power								fDRIVER_MANAGER_Set_Calibration_Power              					=	NULL;
	tfDRIVER_MANAGER_Set_Calibration_MeasureDelay						fDRIVER_MANAGER_Set_Calibration_MeasureDelay       					=	NULL;
	tfDRIVER_MANAGER_CALIBRATION_Run									fDRIVER_MANAGER_CALIBRATION_Run                    					=	NULL;
	tfDRIVER_MANAGER_CALIBRATION_GetCalibrationInfo						fDRIVER_MANAGER_CALIBRATION_GetCalibrationInfo     					=	NULL;
	tfDRIVER_MANAGER_PowerMeter_SetFrequency							fDRIVER_MANAGER_PowerMeter_SetFrequency								=	NULL; 
	tfDRIVER_MANAGER_CALIBRATION_FillCalibrationInfo					fDRIVER_MANAGER_CALIBRATION_FillCalibrationInfo						=	NULL;
	tfDRIVER_MANAGER_Set_Calibration_StateFileName						fDRIVER_MANAGER_Set_Calibration_StateFileName						=	NULL;
	tfDRIVER_MANAGER_Set_Calibration_ReferenceLevel						fDRIVER_MANAGER_Set_Calibration_ReferenceLevel						=	NULL; 
	tfDRIVER_MANAGER_Set_Calibration_Attenuator							fDRIVER_MANAGER_Set_Calibration_Attenuator							=	NULL;  
	tfDRIVER_MANAGER_CALIBRATION_GetCalibrationRangeInfo				fDRIVER_MANAGER_CALIBRATION_GetCalibrationRangeInfo					=	NULL;
	tfDRIVER_MANAGER_CALIBRATION_CreateEmptyHandle						fDRIVER_MANAGER_CALIBRATION_CreateEmptyHandle						=	NULL; 
	tfDRIVER_MANAGER_CALIBRATION_DiscardHandle							fDRIVER_MANAGER_CALIBRATION_DiscardHandle							=	NULL;
	tfDRIVER_MANAGER_StandardDevice_SetValue							fDRIVER_MANAGER_StandardDevice_SetValue								=	NULL; 
	
	tfDRIVER_MANAGER_CALIBRATION_Fill_AdditionalPower_CalibrationInfo   fDRIVER_MANAGER_CALIBRATION_Fill_AdditionalPower_CalibrationInfo	=	NULL;
	tfDRIVER_MANAGER_CALIBRATION_Get_AdditionalPower_CalibrationInfo	fDRIVER_MANAGER_CALIBRATION_Get_AdditionalPower_CalibrationInfo		=	NULL;
	tfDRIVER_MANAGER_CALIBRATION_Set_NumberOf_AdditionalPower			fDRIVER_MANAGER_CALIBRATION_Set_NumberOf_AdditionalPower			=	NULL;
	tfDRIVER_MANAGER_CALIBRATION_Gel_3D_Factor							fDRIVER_MANAGER_CALIBRATION_Gel_3D_Factor							=	NULL;
	
	tfDRV_NetworkAnalyzer_Calibration_SetFrequencyPlan					fDRV_NetworkAnalyzer_Calibration_SetFrequencyPlan					=	NULL;
	tfDRV_NetworkAnalyzer_SaveStateAndCalibration						fDRV_NetworkAnalyzer_SaveStateAndCalibration						=	NULL;
	tfDRV_NetworkAnalyzer_LoadStateAndCalibration						fDRV_NetworkAnalyzer_LoadStateAndCalibration						=	NULL;
	tfDRV_NetworkAnalyzer_ECAL_Calibrate								fDRV_NetworkAnalyzer_ECAL_Calibrate									=	NULL;

	tfDRIVER_MANAGER_StandardDevice_SetListOfValues						fDRIVER_MANAGER_StandardDevice_SetListOfValues						=	NULL;
	
	tfDRV_SpectrumAnalyzer_AlignNow										fDRV_SpectrumAnalyzer_AlignNow										=	NULL;
	
	char																*pFilePathName														=	NULL;
																		
	int 																bPopup																=	0,
																		bFoundDuplication													=	0, 
																		event																=	0,
																		panel																=	0,
																		control																=	0;

	char																szAliasName[LOW_STRING]												=	{0},
																		szFormatedString[LOW_STRING]										=	{0},
																		szCalibPowerMeter[LOW_STRING]										=	{0},
																		szCommandVariableName[LOW_STRING]									=	{0},
																		szCalibSignalGenerator[LOW_STRING]									=	{0},
																		szCalibNetworkAnalyzer[LOW_STRING]									=	{0},
																		szCalibSpectrumAnalyzer[LOW_STRING]									=	{0};
																		
	int																	hCurrentRfBoxHandle													=	0,
																		hCalibrationMeasureHandle											=	0,
																		hCalibrationReferencePathHandle										=	0,
																		hCalibrationPowerMeterHandle										=	0,
																		hCalibrationSignalGeneratorHandle									=	0,
																		hCalibrationNetworkAnalyzerHandle									=	0,
																		hCalibrationSpectrumAnalyzerHandle									=	0;
																		
	int																	*piCalibrationPowerMeter_PortNumber									=	NULL;

	int																	iCalibrationPowerMeter_PortNumber									=	0;
	
	double																*plfCalibrationPowerMeter_Frequency									=	NULL,
																		*plfCalibration_ReferenceLevel										=	NULL, 
																		*plfCalibration_Attenuator											=	NULL,
																		*plfCalibration_PowersList											=	NULL, 
																		*plfCalibration_Timeout												=	NULL, 
																		*plfCalibration_Power												=	NULL,
																		*plfCalibration_Delay												=	NULL,
																		*plfAligning_Timeout												=	NULL;
																		
	char																*pszCalibration_FrequencyRanges										=	NULL,
																		*pszCalibration_SG_FrequencyRanges									=	NULL, 
																		*pszCalibration_AuxFrequencyRanges									=	NULL,  
																		*pszCalibration_StateFile											=	NULL, 
																		*pszCalibration_Generator_StateFile									=	NULL,  
																		*pszCalibration_Instruction											=	NULL,  
																		*pszCalibration_Picture												=	NULL, 
																		*pInstruction														=	NULL;  
																		
	char																**pszNetworkCalibration_FrequencyRanges								=	NULL,
																		**pszNetworkCalibration_StateFile									=	NULL; 
																				
	char																*pszECAL_Configuration												=	NULL,
																		*pszECAL_UserCharacterizations										=	NULL;
	
	int																	*piCalibration_AuxCable_Disable										=	NULL,
																		*piCalibration_SelfAuxCalibration									=	NULL, 
																		*piCalibration_Aux_Auto												=	NULL,
																		*piCalibration_Auto													=	NULL;
	
	int																	iNumberOfChannels													=	0,
																		iNetworkCalIndex													=	0, 
																		iChannelIndex														=	0, 
																		iPowerIndex															=	0,
																		iTryIndex															=	0;
																		
	int																	hPopupPanel															=	0,
																		hPopupCalibrationGraphPanel											=	0;  
																	
	double																*pCalibFrequencyList												=	NULL,
																		*pCalibFactorList													=	NULL,
																		*pCalibDeltaList													=	NULL,
																		*pSinglePlot														=	NULL; 
																	
	double																*pRefCalibFrequencyList												=	NULL,
																		*pRefCalibFactorList												=	NULL;
	
	int																	iNumberOfPowers														=	0, 
																		iNumOfCalibPoints													=	0,
																		iNumberOfPoints														=	0,
																		iRefNumOfCalibPoints												=	0;
	
	double																*pOldCalibFrequencyList												=	NULL,
																		*pOldCalibFactorList												=	NULL;
	
	int																	iOldNumOfCalibPoints												=	0;
	
	double																lfLastCalibrationDate												=	0.0,
																		lfReferenceLevel													=	0.0,
																		lfPowerValue														=	0.0,									   
																		lfAligning_Timeout													=	0.0,
																		lfReferenceCableLoss												=	0.0,
																		lfCalibrationTimeout												=	0.0,
																		lfCurrentDateTime													=	0.0,
																		lfRefCalibDateTime													=	0.0,
																		lfCalibrationPower													=	0.0, 
																		lfStartFrequency													=	0.0,
																		lfStopFrequency														=	0.0,
																		lfStepFrequency														=	0.0;   
	
	int																	*pRFBoxUnitsList													=	NULL;
	
	int																	iRFBoxUnitsCount													=	0;
	
	int																	iNumberOfPathCommands												=	0,
																		iNumberOfAuxPathCommands											=	0,
																		iNumberOfNetworkRanges												=	0,
																		iNumberOfNetworkStateFiles											=	0;
	
	char																**pRF_CalibrationPathCommand										=	NULL,
																		**pRF_CalibrationAuxPathCommand										=	NULL;
	
	tsInitBlockMemory													**pInitBlockMemory													=	NULL;
	
	int																	*pThreadFunctionIdList												=	NULL;
	
	int																	hPanelEquipmentLock													=	NULL;
	
	int																	iStatus																=	0;
	
	int																	bPassStatus															=	0,
																		bSelfAuxCalibration													=	0,
																		bReferenceCableInUse												=	0; 
																		
	char																*pTemp																=	NULL;
	
	CHK_CMT( CmtGetTSVPtr ( hMainHandle , &pMainStore )); 
	memcpy( &tMainStore , pMainStore , sizeof(tsMainStore));  
	CHK_CMT(CmtReleaseTSVPtr (hMainHandle));
	
	IF (( tMainStore.hDriverManagerLibrary == NULL ) , "Driver Manager is not found." );
		
	db_equipment_getlist_by_type_station( tMainStore.hDatabaseHandle , tMainStore.hCurrentStationId , -1 ,&equipmentList);

	if (( equipmentList == NULL ) || ( equipmentList->equipment == NULL )) 
	{
		RETURN;
	}
	
	db_equipment_use_getlist_by_station_version( tMainStore.hDatabaseHandle , tMainStore.hCurrentStationId , tMainStore.hCurrentSelectedVersionId , tMainStore.tRunMode , &equipmentUseList);

	if (( equipmentUseList == NULL ) || ( equipmentUseList->equipment == NULL )) 
	{
		RETURN;
	}
		
	CALLOC_ERR( equipmentForInit , equipmentList->count , sizeof(tEquipment*));
	CALLOC_ERR( pRFBoxUnitsList , equipmentList->count , sizeof(int));
	
	CHK_CMT( CmtGetTSVPtr ( hMainHandle , &pMainStore )); 

	for ( index = 0 ; index < pMainStore->tCurrentRunTestSeq.iNumberOfSelectedTests ; index++ )   
		if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[index].ptlDB_EquipmentList )
			for ( iEquipmentUseIndex = 0 ; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[index].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
				for ( iEquipmentUseSelectIndex = 0 ; iEquipmentUseSelectIndex < equipmentUseList->count ; iEquipmentUseSelectIndex++ )    
					if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[index].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id == equipmentUseList->equipment[iEquipmentUseSelectIndex].id )
						if ( equipmentUseList->equipment[iEquipmentUseSelectIndex].disable == 0 )
						{
							equipmentUseList->equipment[iEquipmentUseSelectIndex].selected = 1; 	
	
							for ( iEquipmentIndex = 0 ; iEquipmentIndex < equipmentList->count ; iEquipmentIndex++ )   
								if ( equipmentList->equipment[iEquipmentIndex].id == equipmentUseList->equipment[iEquipmentUseSelectIndex].equipment_id )
								{
									if (( equipmentList->equipment[iEquipmentIndex].rfboxlink ) && ( tMainStore.tRunMode == RUN_MODE_CALIBRATION ))
										pRFBoxUnitsList[iRFBoxUnitsCount++] = equipmentList->equipment[iEquipmentIndex].rfboxlink;	
									
									break;	
								}
						}
	
	for ( index = 0 ; index < iRFBoxUnitsCount ; index++ )   
		for ( iEquipmentUseSelectIndex = 0 ; iEquipmentUseSelectIndex < equipmentUseList->count ; iEquipmentUseSelectIndex++ )    
			if ( pRFBoxUnitsList[index] == equipmentUseList->equipment[iEquipmentUseSelectIndex].equipment_id )
				if ( equipmentUseList->equipment[iEquipmentUseSelectIndex].disable == 0 )
					equipmentUseList->equipment[iEquipmentUseSelectIndex].selected = 1; 	
		
	CHK_CMT(CmtReleaseTSVPtr (hMainHandle));
	
	CHK_UIL (hPanelEquipment = LoadPanel (0, "TEST_EXEC_UI.uir", EQUIP_INIT ));

	for ( iEquipmentUseSelectIndex = 0 ; iEquipmentUseSelectIndex < equipmentUseList->count ; iEquipmentUseSelectIndex++ )   
	{
		if ( equipmentUseList->equipment[iEquipmentUseSelectIndex].selected )
		{
			bFoundDuplication = 0;
			
			//-------- check duplications --------------//
			for ( iDuplicationsIndex = 0 ; iDuplicationsIndex < iEquipmentCount ; iDuplicationsIndex++ )  
				if ( equipmentForInit[iDuplicationsIndex]->id == equipmentUseList->equipment[iEquipmentUseSelectIndex].equipment_id )
				{
					bFoundDuplication = 1;
					break;	
				}
				
			if ( bFoundDuplication )
				continue;
						
			InsertTableRows ( hPanelEquipment , EQUIP_INIT_TABLE , (iEquipmentCount+1) , 1 , VAL_CELL_STRING );
			SetTableRowAttribute (hPanelEquipment, EQUIP_INIT_TABLE, (iEquipmentCount+1), ATTR_LABEL_BOLD, 1);
			SetTableRowAttribute (hPanelEquipment, EQUIP_INIT_TABLE, (iEquipmentCount+1), ATTR_LABEL_COLOR, VAL_WHITE);
			SetTableRowAttribute (hPanelEquipment, EQUIP_INIT_TABLE, (iEquipmentCount+1), ATTR_LABEL_POINT_SIZE, 15);
			
			for ( iEquipmentIndex = 0 ; iEquipmentIndex < equipmentList->count ; iEquipmentIndex++ )   
				if ( equipmentList->equipment[iEquipmentIndex].id == equipmentUseList->equipment[iEquipmentUseSelectIndex].equipment_id )
				{   
					SetTableCellAttribute ( hPanelEquipment, EQUIP_INIT_TABLE ,MakePoint (1,(iEquipmentCount+1)), ATTR_TEXT_BOLD, 1); 
					SetTableCellAttribute ( hPanelEquipment, EQUIP_INIT_TABLE ,MakePoint (2,(iEquipmentCount+1)), ATTR_TEXT_BOLD, 1);
					SetTableCellAttribute ( hPanelEquipment, EQUIP_INIT_TABLE ,MakePoint (3,(iEquipmentCount+1)), ATTR_TEXT_BOLD, 1);
					
					SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (1,(iEquipmentCount+1)), ATTR_CELL_JUSTIFY, VAL_CENTER_CENTER_JUSTIFIED);
					SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (2,(iEquipmentCount+1)), ATTR_CELL_JUSTIFY, VAL_CENTER_CENTER_JUSTIFIED);
					SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (3,(iEquipmentCount+1)), ATTR_CELL_JUSTIFY, VAL_CENTER_CENTER_JUSTIFIED); 
					
					SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (1,(iEquipmentCount+1)), ATTR_TEXT_COLOR, MAIN_COLOR );
					SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (2,(iEquipmentCount+1)), ATTR_TEXT_COLOR, MAIN_COLOR );
					
					if ( equipmentUseList->equipment[iEquipmentUseSelectIndex].nr )
						sprintf( szAliasName , "%s%d" , equipmentUseList->equipment[iEquipmentUseSelectIndex].alias , equipmentUseList->equipment[iEquipmentUseSelectIndex].nr );
					else
						strcpy( szAliasName , equipmentUseList->equipment[iEquipmentUseSelectIndex].alias );
					
					SetTableCellVal ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(1,(iEquipmentCount+1)), szAliasName );
					SetTableCellVal ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(2,(iEquipmentCount+1)), equipmentList->equipment[iEquipmentIndex].name ); 
					
					equipmentForInit[iEquipmentCount++] = &(equipmentList->equipment[iEquipmentIndex]);
					
					break;
				}
		}
	}
	
	if ( iEquipmentCount == 0 )
	{
		RETURN;	
	}
	
	InstallPopup (hPanelEquipment);
	bPopup = 1;
	
	GetCurrentDateTime(&lfCurrentDateTime);
	
	//----------------------------------- Initialization -----------------------------------------//
	
	fDRIVER_MANAGER_CALIBRATION_FillCalibrationInfo = (tfDRIVER_MANAGER_CALIBRATION_FillCalibrationInfo) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_CALIBRATION_FillCalibrationInfo" );                 
	
	fDRIVER_MANAGER_CALIBRATION_Fill_AdditionalPower_CalibrationInfo = (tfDRIVER_MANAGER_CALIBRATION_Fill_AdditionalPower_CalibrationInfo) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_CALIBRATION_Fill_AdditionalPower_CalibrationInfo" );
	
	fDRIVER_MANAGER_Set_Calibration_Power = (tfDRIVER_MANAGER_Set_Calibration_Power) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_Set_Calibration_Power" );                        
	
	fDRIVER_MANAGER_Get_SimulationMode = (tfDRIVER_MANAGER_Get_SimulationMode) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_Get_SimulationMode" );
	
	CHK_CMT( CmtNewLock ( "Equipment Init GUI" , OPT_TL_PROCESS_EVENTS_WHILE_WAITING , &hPanelEquipmentLock ));
	
	CALLOC( pInitBlockMemory , iEquipmentCount , sizeof(tsInitBlockMemory*)); 
	CALLOC( pThreadFunctionIdList , iEquipmentCount , sizeof(int));  
	
	for ( iEquipmentIndex = 0 ; iEquipmentIndex < iEquipmentCount ; iEquipmentIndex++ )  
	{  
		if (( equipmentForInit[iEquipmentIndex]->calib_expr != 0.0 ) && ( lfCurrentDateTime > equipmentForInit[iEquipmentIndex]->calib_expr ))
		{
			sprintf( szFormatedString , "Calibration is necessary for \"%s\"." , equipmentForInit[iEquipmentIndex]->name );
			ShowMessage ( tMainStore.hDatabaseHandle , INSTR_TYPE_CONTINUE ,  "Calibration Expired" , szFormatedString , NULL );	
		}
		
		CALLOC( pInitBlockMemory[iEquipmentIndex] , 1 , sizeof(tsInitBlockMemory));				
		
		if ( pInitBlockMemory )
		{   
			db_equipment_get( tMainStore.hDatabaseHandle , equipmentForInit[iEquipmentIndex]->id , &(pInitBlockMemory[iEquipmentIndex]->equipmentForInit));
			
			pInitBlockMemory[iEquipmentIndex]->hMainHandle = hMainHandle;
			pInitBlockMemory[iEquipmentIndex]->hDatabaseHandle = tMainStore.hDatabaseHandle;
			pInitBlockMemory[iEquipmentIndex]->hDriverManagerLibrary = tMainStore.hDriverManagerLibrary; 
			pInitBlockMemory[iEquipmentIndex]->hPanelEquipment = hPanelEquipment;
			pInitBlockMemory[iEquipmentIndex]->hLockHandle = hPanelEquipmentLock;
			pInitBlockMemory[iEquipmentIndex]->iEquipmentIndex = iEquipmentIndex;
			
			CHK_CMT( CmtScheduleThreadPoolFunction ( DEFAULT_THREAD_POOL_HANDLE , RUN_MultiInitThread , pInitBlockMemory[iEquipmentIndex] , &(pThreadFunctionIdList[iEquipmentIndex]) ));

			ProcessSystemEvents();  
			
			DelayWithEventProcessing(0.1);
		}
	}
			
	for ( iEquipmentIndex = 0 ; iEquipmentIndex < iEquipmentCount ; iEquipmentIndex++ )  
	{
		do
		{
			CmtGetThreadPoolFunctionAttribute ( DEFAULT_THREAD_POOL_HANDLE , pThreadFunctionIdList[iEquipmentIndex] , ATTR_TP_FUNCTION_EXECUTION_STATUS , &iStatus ); 
			
			if ( iStatus >= kCmtThreadFunctionComplete )
				break;
						
			ProcessSystemEvents();  
			DelayWithEventProcessing(0.5);

		} while ( iStatus < kCmtThreadFunctionComplete );  
		
		CmtReleaseThreadPoolFunctionID ( DEFAULT_THREAD_POOL_HANDLE  , pThreadFunctionIdList[iEquipmentIndex] );
		
		ProcessSystemEvents();
	}
	
	bPassStatus = 1;
	
	for ( iEquipmentIndex = 0 ; iEquipmentIndex < iEquipmentCount ; iEquipmentIndex++ )  
	{ 
		*pbSkipRunning |= pInitBlockMemory[iEquipmentIndex]->bSkipRunning;

		bPassStatus &= pInitBlockMemory[iEquipmentIndex]->bPassStatus;
		
		equipmentForInit[iEquipmentIndex]->handle = (pInitBlockMemory[iEquipmentIndex]->equipmentForInit)->handle;	
	}	
	
	*pbSkipRunning |= !bPassStatus;
	
	//----------------------------------- Calibrations -----------------------------------------//
	if (( tMainStore.tRunMode == RUN_MODE_CALIBRATION ) && ( bPassStatus ))
	{			
		hPopupPanel = LoadPanel (0, "TEST_EXEC_UI.uir", WAIT );
	
		fDRIVER_MANAGER_Set_Calibration_Port_Number = (tfDRIVER_MANAGER_Set_Calibration_Port_Number) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_Set_Calibration_Port_Number" );                 
		fDRIVER_MANAGER_Get_Number_Of_Channels = (tfDRIVER_MANAGER_Get_Number_Of_Channels) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_Get_Number_Of_Channels" );                       
		fDRIVER_MANAGER_PowerMeter_Calibrate = (tfDRIVER_MANAGER_PowerMeter_Calibrate) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerMeter_Calibrate" );                         
		fDRIVER_MANAGER_CALIBRATION_FillCalibrationRanges = (tfDRIVER_MANAGER_CALIBRATION_FillCalibrationRanges) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_CALIBRATION_FillCalibrationRanges" );            
		fDRIVER_MANAGER_Set_Calibration_MeasureDelay = (tfDRIVER_MANAGER_Set_Calibration_MeasureDelay) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_Set_Calibration_MeasureDelay" );                 
		fDRIVER_MANAGER_CALIBRATION_Run = (tfDRIVER_MANAGER_CALIBRATION_Run) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_CALIBRATION_Run" );                              
		fDRIVER_MANAGER_CALIBRATION_GetCalibrationInfo = (tfDRIVER_MANAGER_CALIBRATION_GetCalibrationInfo) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_CALIBRATION_GetCalibrationInfo" );               
		fDRIVER_MANAGER_PowerMeter_SetFrequency = (tfDRIVER_MANAGER_PowerMeter_SetFrequency) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerMeter_SetFrequency" );               
		fDRIVER_MANAGER_Set_Calibration_StateFileName = (tfDRIVER_MANAGER_Set_Calibration_StateFileName) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_Set_Calibration_StateFileName" );                 
		fDRIVER_MANAGER_Set_Calibration_ReferenceLevel = (tfDRIVER_MANAGER_Set_Calibration_ReferenceLevel) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_Set_Calibration_ReferenceLevel" );                 
		fDRIVER_MANAGER_Set_Calibration_Attenuator = (tfDRIVER_MANAGER_Set_Calibration_Attenuator) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_Set_Calibration_Attenuator" );                 
		fDRIVER_MANAGER_CALIBRATION_GetCalibrationRangeInfo = (tfDRIVER_MANAGER_CALIBRATION_GetCalibrationRangeInfo) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_CALIBRATION_GetCalibrationRangeInfo" );                 
		fDRIVER_MANAGER_CALIBRATION_CreateEmptyHandle = (tfDRIVER_MANAGER_CALIBRATION_CreateEmptyHandle) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_CALIBRATION_CreateEmptyHandle" );                 
		fDRIVER_MANAGER_CALIBRATION_DiscardHandle = (tfDRIVER_MANAGER_CALIBRATION_DiscardHandle) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_CALIBRATION_DiscardHandle" );                 
		fDRIVER_MANAGER_StandardDevice_SetValue = (tfDRIVER_MANAGER_StandardDevice_SetValue) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_StandardDevice_SetValue" );                 
		
		fDRV_NetworkAnalyzer_SaveStateAndCalibration = (tfDRV_NetworkAnalyzer_SaveStateAndCalibration) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NetworkAnalyzer_SaveStateAndCalibration");
		fDRV_NetworkAnalyzer_LoadStateAndCalibration = (tfDRV_NetworkAnalyzer_LoadStateAndCalibration) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NetworkAnalyzer_LoadStateAndCalibration");
		fDRV_NetworkAnalyzer_ECAL_Calibrate = (tfDRV_NetworkAnalyzer_ECAL_Calibrate) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NetworkAnalyzer_ECAL_Calibrate");
		fDRV_NetworkAnalyzer_Calibration_SetFrequencyPlan = (tfDRV_NetworkAnalyzer_Calibration_SetFrequencyPlan) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NetworkAnalyzer_Calibration_SetFrequencyPlan");
		
		fDRIVER_MANAGER_CALIBRATION_Get_AdditionalPower_CalibrationInfo = (tfDRIVER_MANAGER_CALIBRATION_Get_AdditionalPower_CalibrationInfo) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_CALIBRATION_Get_AdditionalPower_CalibrationInfo" );	 
		fDRIVER_MANAGER_CALIBRATION_Set_NumberOf_AdditionalPower = (tfDRIVER_MANAGER_CALIBRATION_Set_NumberOf_AdditionalPower) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_CALIBRATION_Set_NumberOf_AdditionalPower" );		 
		fDRIVER_MANAGER_CALIBRATION_Gel_3D_Factor = (tfDRIVER_MANAGER_CALIBRATION_Gel_3D_Factor) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_CALIBRATION_Gel_3D_Factor" );						 

		fDRIVER_MANAGER_StandardDevice_SetListOfValues = (tfDRIVER_MANAGER_StandardDevice_SetListOfValues) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_SetListOfValues" );  
		
		fDRV_SpectrumAnalyzer_AlignNow = (tfDRV_SpectrumAnalyzer_AlignNow) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SpectrumAnalyzer_AlignNow" );  
		
		for( iCalibrationSequenceIndex = 0; iCalibrationSequenceIndex < 2; iCalibrationSequenceIndex++ )
		{
			//============================== Network Analyzer Calibration =============================================//
			for ( iEquipmentIndex = 0 ; iEquipmentIndex < iEquipmentCount ; iEquipmentIndex++ )  
			{
				if ( equipmentForInit[iEquipmentIndex]->type == EQUIPMENT_TYPE_NETWORK_ANALYZER )
				{
					if ( equipmentForInit[iEquipmentIndex]->priority == 0 )
					{
						hCalibrationNetworkAnalyzerHandle = equipmentForInit[iEquipmentIndex]->handle;
					
						if ( equipmentForInit[iEquipmentIndex]->name  )
							strcpy( szCalibNetworkAnalyzer , equipmentForInit[iEquipmentIndex]->name );
					}
				
					if (( equipmentForInit[iEquipmentIndex]->calibratable ) && ( equipmentForInit[iEquipmentIndex]->bAlreadyCalibrated == 0 ))
					{
						FREE_LIST ( pszNetworkCalibration_FrequencyRanges , iNumberOfNetworkRanges );
						
						iNumberOfNetworkRanges = VarGetStringArray( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Frequency_Ranges" , &pszNetworkCalibration_FrequencyRanges );
						
						if ( iNumberOfNetworkRanges == 0 ) 
						{
							iNumberOfNetworkRanges = 1;
							
							FREE_CALLOC( pszCalibration_FrequencyRanges , 64 , sizeof(char));
		
							if ( pszCalibration_FrequencyRanges )
							{
								strcpy( pszCalibration_FrequencyRanges , "1E6-2E6:201" );   
						
								VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Frequency_Ranges" , pszCalibration_FrequencyRanges );  
							}
						}	
				
						FREE_LIST ( pszNetworkCalibration_StateFile , iNumberOfNetworkStateFiles );    
						
						iNumberOfNetworkStateFiles = VarGetStringArray( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_StateFile" , &pszNetworkCalibration_StateFile );
						
						if ( iNumberOfNetworkStateFiles == 0 ) 
						{
							iNumberOfNetworkStateFiles = 1;
							
							CALLOC( pszCalibration_StateFile , 64 , sizeof(char));
		
							if ( pszCalibration_StateFile )
							{
								strcpy( pszCalibration_StateFile , "calib.sta" );   
						
								VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_StateFile" , pszCalibration_StateFile );  
							}
						}
			
						if ( VarGetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Power" , &plfCalibration_Power ) == 0 )
						{
							CALLOC( plfCalibration_Power , 1 , sizeof(double));
			
							if ( plfCalibration_Power )
							{
								VarSetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Power" , 1 , plfCalibration_Power );  
							}
						}
				
						if ( VarGetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Delay" , &plfCalibration_Delay ) == 0 )
						{
							CALLOC( plfCalibration_Delay , 1 , sizeof(double));
			
							if ( plfCalibration_Delay )
							{
								VarSetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Delay" , 1 , plfCalibration_Delay );  
							}
						}

						if ( VarGetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Timeout" , &plfCalibration_Timeout ) == 0 )
						{
							CALLOC( plfCalibration_Timeout , 1 , sizeof(double));
			
							if ( plfCalibration_Timeout )
							{
								*plfCalibration_Timeout = 300.0;
								
								VarSetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Timeout" , 1 , plfCalibration_Timeout );  
							}
						}
						
						if ( plfCalibration_Timeout )
							lfCalibrationTimeout = *plfCalibration_Timeout;
							
						if ( VarGetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_ReferenceLevel" , &plfCalibration_ReferenceLevel ) == 0 )
						{
							CALLOC( plfCalibration_ReferenceLevel , 1 , sizeof(double));
			
							if ( plfCalibration_ReferenceLevel )
							{
								VarSetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_ReferenceLevel" , 1 , plfCalibration_ReferenceLevel );  
							}
						}
				
						if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_ECAL_PortList" , &pszECAL_Configuration ) <= 0 ) 
						{
							CALLOC( pszECAL_Configuration , 128 , sizeof(char));

							if ( pszECAL_Configuration )
							{
								sprintf( pszECAL_Configuration , "1,2" );
								
								VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_ECAL_PortList" , pszECAL_Configuration );  
							}
						}
						
						if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_ECAL_UserCalSet" , &pszECAL_UserCharacterizations ) <= 0 ) 
						{
							CALLOC( pszECAL_UserCharacterizations , 128 , sizeof(char));

							if ( pszECAL_UserCharacterizations )
							{
								sprintf( pszECAL_UserCharacterizations , "." );
								
								VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_ECAL_UserCalSet" , pszECAL_UserCharacterizations );  
							}
						}
						
						if ( plfCalibration_Power )
						{
							lfPowerValue = *plfCalibration_Power; 
							
							fDRIVER_MANAGER_Set_Calibration_Power( equipmentForInit[iEquipmentIndex]->handle , (*plfCalibration_Power) );
							FREE(plfCalibration_Power);
						}
						
						if ( plfCalibration_Delay )
						{
							fDRIVER_MANAGER_Set_Calibration_MeasureDelay( equipmentForInit[iEquipmentIndex]->handle , (*plfCalibration_Delay) );
							FREE(plfCalibration_Delay);
						}
				
						if ( plfCalibration_ReferenceLevel )
						{
							lfReferenceLevel = *plfCalibration_ReferenceLevel;
							
							fDRIVER_MANAGER_Set_Calibration_ReferenceLevel( equipmentForInit[iEquipmentIndex]->handle , (*plfCalibration_ReferenceLevel) );
							FREE(plfCalibration_ReferenceLevel);
						}
						
						if ( pszCalibration_StateFile && ( strlen(pszCalibration_StateFile)))
						{
							FREE(pszCalibration_StateFile); 
							fDRIVER_MANAGER_Set_Calibration_StateFileName( equipmentForInit[iEquipmentIndex]->handle , pszCalibration_StateFile );
						}
				
						if ( pszNetworkCalibration_StateFile )
						{
							sprintf( szFormatedString , "Do you want to calibrate the Network Analyzer:\n- %s ?" , equipmentForInit[iEquipmentIndex]->name );
					
							if( ShowMessage ( tMainStore.hDatabaseHandle , INSTR_TYPE_YES_NO , "Network Analyzer", szFormatedString , NULL ))
							{   
								//=============================================== Spectrum Analyzer Calibration =======================================================================//
								if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Instruction" , &pszCalibration_Instruction ) <= 0 ) 
								{
									CALLOC( pszCalibration_Instruction , 256 , sizeof(char));
		
									if ( pszCalibration_Instruction )
									{
										sprintf( pszCalibration_Instruction , "Please prepare calibration setup\nfor calibrating the Network Analyzer \"%s\".\nConnect Ecal beetween Port1 and Port2.\n* Wait for ready on the ECal." , equipmentForInit[iEquipmentIndex]->name );
								
										VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Instruction" , pszCalibration_Instruction );  
									}
								}
						
								if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Picture" , &pszCalibration_Picture ) <= 0 ) 
								{
									CALLOC( pszCalibration_Picture , 64				 , sizeof(char));
		
									if ( pszCalibration_Picture )
									{
										strcpy( pszCalibration_Picture , "." );
								
										VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Picture" , pszCalibration_Picture );  
									}
								}
								
								if ( pszCalibration_Instruction )
								{
									pInstruction = StringReplaceAll( pszCalibration_Instruction , "\\n" , "\n" , NULL);
									
									ShowMessage ( tMainStore.hDatabaseHandle , INSTR_TYPE_CONTINUE , "Instruction",pInstruction , pszCalibration_Picture );       
								}
								
								FREE(pInstruction);  
								FREE(pszCalibration_Instruction);
								FREE(pszCalibration_Picture);  
								
								sprintf( szFormatedString , "Calibrating : %s" , equipmentForInit[iEquipmentIndex]->name ); 
							
								SetCtrlVal( hPopupPanel , WAIT_TEXTMSG , szFormatedString ); 
								InstallPopup ( hPopupPanel );
									
								if ( lfCalibrationTimeout == 0.0 )
									lfCalibrationTimeout = 300.0;
								
								for ( iNetworkCalIndex = 0; iNetworkCalIndex < iNumberOfNetworkStateFiles; iNetworkCalIndex++ )
								{
									if ( iNetworkCalIndex < iNumberOfNetworkRanges )
									{
										if ( pszNetworkCalibration_FrequencyRanges && pszNetworkCalibration_FrequencyRanges[iNetworkCalIndex] && strlen(pszNetworkCalibration_FrequencyRanges[iNetworkCalIndex]))
										{
											NO_CHK_STDERR( fDRIVER_MANAGER_CALIBRATION_FillCalibrationRanges( equipmentForInit[iEquipmentIndex]->handle , pszNetworkCalibration_FrequencyRanges[iNetworkCalIndex] ));     
										}
									}
									
									if (( pszNetworkCalibration_StateFile[iNetworkCalIndex] ) && ( strlen(pszNetworkCalibration_StateFile[iNetworkCalIndex])))
									{
										UPDATERR( fDRV_NetworkAnalyzer_LoadStateAndCalibration ( equipmentForInit[iEquipmentIndex]->handle , pszNetworkCalibration_StateFile[iNetworkCalIndex] ));
								
										if ( IS_NOT_OK ) 
										{
											fDRIVER_MANAGER_CALIBRATION_GetCalibrationRangeInfo( equipmentForInit[iEquipmentIndex]->handle , &lfStartFrequency , &lfStopFrequency , &iNumberOfPoints );

											fDRV_NetworkAnalyzer_Calibration_SetFrequencyPlan ( equipmentForInit[iEquipmentIndex]->handle , lfStartFrequency , lfStopFrequency , lfPowerValue , lfReferenceLevel , iNumberOfPoints );
										}
									}
								
									for ( iTryIndex = 0; iTryIndex < 3; iTryIndex++ )
									{
										UPDATERR( fDRV_NetworkAnalyzer_ECAL_Calibrate ( equipmentForInit[iEquipmentIndex]->handle , pszECAL_Configuration , pszECAL_UserCharacterizations , lfCalibrationTimeout )); 
								
										if ( IS_OK && pszNetworkCalibration_StateFile[iNetworkCalIndex] && (strlen(pszNetworkCalibration_StateFile[iNetworkCalIndex])))
										{
											fDRV_NetworkAnalyzer_SaveStateAndCalibration ( equipmentForInit[iEquipmentIndex]->handle , pszNetworkCalibration_StateFile[iNetworkCalIndex] );
											break;
										}
										else
										{
											ShowMessage ( tMainStore.hDatabaseHandle , INSTR_TYPE_CONTINUE , "Calibration Error...","Please Check the Ecal connectivity." , NULL );	
										}
									}
								}
								
								RemovePopup(0); 
							}
						}
						
						equipmentForInit[iEquipmentIndex]->bAlreadyCalibrated = 1;
					}
				}
			}
			
			//============================== Power Meters Calibration =============================================//
			for ( iEquipmentIndex = 0 ; iEquipmentIndex < iEquipmentCount ; iEquipmentIndex++ )  
			{
				if ( equipmentForInit[iEquipmentIndex]->type == EQUIPMENT_TYPE_POWER_METER ) 
				{
					if ( equipmentForInit[iEquipmentIndex]->priority == 0 )
					{
						hCalibrationPowerMeterHandle = equipmentForInit[iEquipmentIndex]->handle;
					
						if ( equipmentForInit[iEquipmentIndex]->name  )
							strcpy( szCalibPowerMeter , equipmentForInit[iEquipmentIndex]->name );
					}
				
					if ( equipmentForInit[iEquipmentIndex]->calibratable && ( equipmentForInit[iEquipmentIndex]->bAlreadyCalibrated == 0 ))
					{   
						if ( VarGetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_With_PortNumber" , &piCalibrationPowerMeter_PortNumber ) == 0 )
						{
							fDRIVER_MANAGER_Set_Calibration_Port_Number( equipmentForInit[iEquipmentIndex]->handle , 1 ); 
	
							CALLOC( piCalibrationPowerMeter_PortNumber , 1 , sizeof(int));
					
							if ( piCalibrationPowerMeter_PortNumber )
							{
								*piCalibrationPowerMeter_PortNumber = 1;
						
								VarSetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_With_PortNumber" , 1 , piCalibrationPowerMeter_PortNumber );  
							}
						}
				
						if ( piCalibrationPowerMeter_PortNumber )
							iCalibrationPowerMeter_PortNumber = (*piCalibrationPowerMeter_PortNumber);
						else
							iCalibrationPowerMeter_PortNumber = 1;
				
						fDRIVER_MANAGER_Set_Calibration_Port_Number( equipmentForInit[iEquipmentIndex]->handle , iCalibrationPowerMeter_PortNumber ); 
				
						FREE(piCalibrationPowerMeter_PortNumber);
				
						sprintf( szFormatedString , "Do you want to calibrate the Power Meter:\n- %s\nSensors?" , equipmentForInit[iEquipmentIndex]->name );
					
						if( ShowMessage ( tMainStore.hDatabaseHandle , INSTR_TYPE_YES_NO , "Power Meter Calibration", szFormatedString , NULL ))
						{
							if ( equipmentForInit[iEquipmentIndex]->channels == 0 )
								fDRIVER_MANAGER_Get_Number_Of_Channels( equipmentForInit[iEquipmentIndex]->handle , &iNumberOfChannels );
							else
								iNumberOfChannels = equipmentForInit[iEquipmentIndex]->channels;
		
							for ( iChannelIndex = 0; iChannelIndex < iNumberOfChannels; iChannelIndex++ )
							{
								sprintf( szFormatedString , "Calibration_CH_%d_SelftCalFrequency" , (iChannelIndex+1) );  

								if ( VarGetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , szFormatedString , &plfCalibrationPowerMeter_Frequency ) == 0 )
								{
									CALLOC( plfCalibrationPowerMeter_Frequency , 1 , sizeof(double));
					
									if ( plfCalibrationPowerMeter_Frequency )
									{
										*plfCalibrationPowerMeter_Frequency = 50e6;
						
										VarSetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , szFormatedString , 1 , plfCalibrationPowerMeter_Frequency );  
									}
								}
						
								if ( plfCalibrationPowerMeter_Frequency )
								{
									NO_CHK_STDERR( fDRIVER_MANAGER_PowerMeter_SetFrequency ( equipmentForInit[iEquipmentIndex]->handle , (iChannelIndex+1) , *plfCalibrationPowerMeter_Frequency )); 
								}
						
								FREE(plfCalibrationPowerMeter_Frequency);
						
								sprintf( szFormatedString , "Connect Power Meter Sensor N - %d to Calib RF Port." , (iChannelIndex+1) );
			
								ShowMessage ( tMainStore.hDatabaseHandle , INSTR_TYPE_CONTINUE ,  "Instruction" , szFormatedString , NULL );
	
								sprintf( szFormatedString , "Zeroing : Sensor %d " , (iChannelIndex+1) );
			
								SetCtrlVal( hPopupPanel , WAIT_TEXTMSG , szFormatedString ); 
								InstallPopup ( hPopupPanel );
		
								NO_CHK_STDERR( fDRIVER_MANAGER_PowerMeter_Calibrate ( equipmentForInit[iEquipmentIndex]->handle , (iChannelIndex+1) )); 
						
								RemovePopup(0);
							}
						}
					
						equipmentForInit[iEquipmentIndex]->bAlreadyCalibrated = 1;
					}  
				}
			}
				
			//============================== Signal Generators Calibration =============================================//
			for ( iEquipmentIndex = 0 ; iEquipmentIndex < iEquipmentCount ; iEquipmentIndex++ )  
			{
				if ( equipmentForInit[iEquipmentIndex]->type == EQUIPMENT_TYPE_SIGNAL_GENERATOR ) 
				{
					FREE(plfCalibration_PowersList);
			
					iNumberOfPowers = VarGetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_AdditionalPowers" , &plfCalibration_PowersList );
			
					if ( iNumberOfPowers )
					do
					{
						if ( iNumberOfPowers == 1 ) 
						{
							VarGetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Power" , &plfCalibration_Power );

							if ( plfCalibration_Power )
							{
								if ( plfCalibration_Power[0] == plfCalibration_PowersList[0] )
									break;
							}
						}
								
						fDRIVER_MANAGER_CALIBRATION_Set_NumberOf_AdditionalPower( equipmentForInit[iEquipmentIndex]->handle , plfCalibration_PowersList , iNumberOfPowers );
					
						iNumberOfPowers++;
				
					} while(0);
			
					if ( equipmentForInit[iEquipmentIndex]->priority == 0 )
					{
						hCalibrationSignalGeneratorHandle = equipmentForInit[iEquipmentIndex]->handle;
					
						if ( equipmentForInit[iEquipmentIndex]->name  )
							strcpy( szCalibSignalGenerator , equipmentForInit[iEquipmentIndex]->name );
					}
				
					if (( equipmentForInit[iEquipmentIndex]->calibratable ) && ( hCalibrationPowerMeterHandle || hCalibrationSpectrumAnalyzerHandle ) && ( equipmentForInit[iEquipmentIndex]->bAlreadyCalibrated == 0 ))
					{
						if ( hCalibrationSpectrumAnalyzerHandle )
							hCalibrationMeasureHandle = hCalibrationSpectrumAnalyzerHandle;
							
						if ( hCalibrationPowerMeterHandle )
							hCalibrationMeasureHandle = hCalibrationPowerMeterHandle;
						
						if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Frequency_Ranges" , &pszCalibration_FrequencyRanges ) <= 0 ) 
						{
							FREE_CALLOC( pszCalibration_FrequencyRanges , 64 , sizeof(char));
		
							if ( pszCalibration_FrequencyRanges )
							{
								strcpy( pszCalibration_FrequencyRanges , "1E6-2E6:201" );
							
								VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Frequency_Ranges" , pszCalibration_FrequencyRanges );  
							}
						}	
				
						if ( VarGetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Power" , &plfCalibration_Power ) == 0 )
						{
							FREE_CALLOC( plfCalibration_Power , 1 , sizeof(double));
			
							if ( plfCalibration_Power )
							{
								VarSetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Power" , 1 , plfCalibration_Power );  
							}
						}
				
						if ( VarGetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Delay" , &plfCalibration_Delay ) == 0 )
						{
							FREE_CALLOC( plfCalibration_Delay , 1 , sizeof(double));
			
							if ( plfCalibration_Delay )
							{
								VarSetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Delay" , 1 , plfCalibration_Delay );  
							}
						}

						if ( VarGetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_AuxCable_Disable" , &piCalibration_AuxCable_Disable ) == 0 )
						{
							FREE_CALLOC( piCalibration_AuxCable_Disable , 1 , sizeof(int));
			
							if ( piCalibration_AuxCable_Disable )
							{
								VarSetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_AuxCable_Disable" , 1 , piCalibration_AuxCable_Disable );  
							}
						}
						
						if ( VarGetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Auto" , &piCalibration_Auto ) == 0 )
						{
							FREE_CALLOC( piCalibration_Auto , 1 , sizeof(int));
			
							if ( piCalibration_Auto )
							{
								VarSetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Auto" , 1 , piCalibration_Auto );  
							}
						}
						
						if ( VarGetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_Auto" , &piCalibration_Aux_Auto ) == 0 )
						{
							FREE_CALLOC( piCalibration_Aux_Auto , 1 , sizeof(int));
			
							if ( piCalibration_Aux_Auto )
							{
								VarSetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_Auto" , 1 , piCalibration_Aux_Auto );  
							}
						}
						
						if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_StateFile" , &pszCalibration_StateFile ) <= 0 ) 
						{
							CALLOC( pszCalibration_StateFile , 64 , sizeof(char));
		
							if ( pszCalibration_StateFile )
							{
								strcpy( pszCalibration_StateFile , "calib.sta" );   
						
								VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_StateFile" , pszCalibration_StateFile );  
							}
						}
				
						if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Generator_StateFile" , &pszCalibration_Generator_StateFile ) <= 0 ) 
						{
							FREE_CALLOC( pszCalibration_Generator_StateFile , 64 , sizeof(char));
		
							if ( pszCalibration_Generator_StateFile )
							{
								strcpy( pszCalibration_Generator_StateFile , "" );   
						
								VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Generator_StateFile" , pszCalibration_Generator_StateFile );  
							}
						}
						
						if ( plfCalibration_Power )
						{
							fDRIVER_MANAGER_Set_Calibration_Power( equipmentForInit[iEquipmentIndex]->handle , (*plfCalibration_Power) );
							lfCalibrationPower = (*plfCalibration_Power);
						
							FREE(plfCalibration_Power);
						}
				
						if ( plfCalibration_Delay )
						{
							fDRIVER_MANAGER_Set_Calibration_MeasureDelay( equipmentForInit[iEquipmentIndex]->handle , (*plfCalibration_Delay) );
							FREE(plfCalibration_Delay);
						}
				
						if ( pszCalibration_StateFile && ( strlen(pszCalibration_StateFile)))
						{
							fDRIVER_MANAGER_Set_Calibration_StateFileName( hCalibrationMeasureHandle , pszCalibration_StateFile );
							FREE(pszCalibration_StateFile);
						}
						
						if ( pszCalibration_Generator_StateFile && ( strlen(pszCalibration_Generator_StateFile)))
						{
							fDRIVER_MANAGER_Set_Calibration_StateFileName( equipmentForInit[iEquipmentIndex]->handle , pszCalibration_Generator_StateFile );
							FREE(pszCalibration_Generator_StateFile);
						}
						
						if ( pszCalibration_FrequencyRanges && ( strlen(pszCalibration_FrequencyRanges)))
						{
							NO_CHK_STDERR( fDRIVER_MANAGER_CALIBRATION_FillCalibrationRanges( equipmentForInit[iEquipmentIndex]->handle , pszCalibration_FrequencyRanges ));
					
							sprintf( szFormatedString , "Do you want to calibrate the Signal Generator:\n- %s\nFactors?" , equipmentForInit[iEquipmentIndex]->name );
						
							if (( piCalibration_Auto && piCalibration_Auto[0] ) || ( ShowMessage ( tMainStore.hDatabaseHandle , INSTR_TYPE_YES_NO , "Signal Generator", szFormatedString  , NULL )))
							{
								//------------------- Prepare RF Box configuration ---------------------------------//
								FREE( pCalibFrequencyList );
								FREE( pCalibFactorList );
								iNumOfCalibPoints = 0;
								lfLastCalibrationDate = 0.0;
								hCurrentRfBoxHandle = 0;
								
								FREE_LIST( pRF_CalibrationPathCommand , iNumberOfPathCommands );
								FREE_LIST( pRF_CalibrationAuxPathCommand , iNumberOfAuxPathCommands );
								
								if ( equipmentForInit[iEquipmentIndex]->rfboxlink )
								{
									for ( index = 0 ; index < iEquipmentCount ; index++ )   
										if ( equipmentForInit[iEquipmentIndex]->rfboxlink == equipmentForInit[index]->id )
										{
											hCurrentRfBoxHandle = equipmentForInit[index]->handle;
											
											sprintf( szCommandVariableName , "%s_CAL_RF_PATH_COMMANDS" , equipmentForInit[iEquipmentIndex]->name );
											
											StringUpperCase ( szCommandVariableName );
											
											pTemp = StringReplaceAll( szCommandVariableName , " " , "_" , NULL); 
											
											if ( pTemp )
											{
												strcpy( szCommandVariableName , pTemp );
												
												FREE(pTemp);
											}
												
											iNumberOfPathCommands = VarGetStringArray( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[index]->id , szCommandVariableName , &pRF_CalibrationPathCommand ); 
										
											if (( iNumberOfPathCommands == 0 ) || ( pRF_CalibrationPathCommand == NULL ))
											{
												VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[index]->id , szCommandVariableName , "" );	
											}
											
											sprintf( szCommandVariableName , "%s_CAL_RF_AUX_PATH_COMMANDS" , equipmentForInit[iEquipmentIndex]->name );
											
											StringUpperCase ( szCommandVariableName );
											
											pTemp = StringReplaceAll( szCommandVariableName , " " , "_" , NULL); 
											
											if ( pTemp )
											{
												strcpy( szCommandVariableName , pTemp );
												
												FREE(pTemp);
											}
												
											iNumberOfAuxPathCommands = VarGetStringArray( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[index]->id , szCommandVariableName , &pRF_CalibrationAuxPathCommand ); 
										
											if (( iNumberOfAuxPathCommands == 0 ) || ( pRF_CalibrationAuxPathCommand == NULL ))
											{
												VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[index]->id , szCommandVariableName , "" );	
											}
											
											break;
										}
								}
									
								//=============================================== Auxiliary Cable Signal Generators Calibration =======================================================================//
								if ( hCalibrationNetworkAnalyzerHandle )
								{
									if ( pszCalibration_FrequencyRanges && ( strlen(pszCalibration_FrequencyRanges)))
									{   
										if (( piCalibration_AuxCable_Disable == NULL ) || ( (*piCalibration_AuxCable_Disable) == 0 ))
											if (( piCalibration_Aux_Auto && piCalibration_Aux_Auto[0] ) || ( ShowMessage ( tMainStore.hDatabaseHandle , INSTR_TYPE_YES_NO , "Auxiliary Cable", "Do you want to calibrate the Auxiliary Cable Factors?" , NULL ))) 
											{
												//------------- Apply Path Commands --------------------------------------//
												if ( pRF_CalibrationAuxPathCommand && iNumberOfAuxPathCommands && hCurrentRfBoxHandle && pRF_CalibrationAuxPathCommand[0] && strlen( pRF_CalibrationAuxPathCommand[0] ))
												{
													for( iPathCommandIndex = 0; iPathCommandIndex < iNumberOfAuxPathCommands; iPathCommandIndex++ )
													{
														if ( pRF_CalibrationAuxPathCommand[iPathCommandIndex] && strlen( pRF_CalibrationAuxPathCommand[iPathCommandIndex] ))
														{
															CHK_STDERR( fDRIVER_MANAGER_StandardDevice_SetListOfValues( hCurrentRfBoxHandle , pRF_CalibrationAuxPathCommand[iPathCommandIndex] , 1 , 3 ));
														}
													}
												}
												//-------------------------------------------------------------------------//
												
												//=============================================== Auxiliary Cable Instruction =======================================================================//
												if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_Instruction" , &pszCalibration_Instruction ) <= 0 ) 
												{
													CALLOC( pszCalibration_Instruction , 128 , sizeof(char));
		
													if ( pszCalibration_Instruction )
													{
														if ( hCalibrationSignalGeneratorHandle && hCalibrationPowerMeterHandle ) 
															sprintf( pszCalibration_Instruction , "Please connect the reference cable between\nSignal Generator \"%s\" and Power Meter \"%s\"" , szCalibSignalGenerator , szCalibPowerMeter );
														else
															sprintf( pszCalibration_Instruction , "Please connect the reference cable between\nPort 1 and Port 2 of the Network Analyzer \"%s\"" , szCalibNetworkAnalyzer );
												
														VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_Instruction" , pszCalibration_Instruction );  
													}
												}
												
												if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_Picture" , &pszCalibration_Picture ) <= 0 ) 
												{
													CALLOC( pszCalibration_Picture , 128 , sizeof(char));
		
													if ( pszCalibration_Picture )
													{
														strcpy( pszCalibration_Picture , "." );
								
														VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_Picture" , pszCalibration_Picture );  
													}
												}
								
												if ( pszCalibration_Instruction && strlen(pszCalibration_Instruction)) 
												{   
													pInstruction = StringReplaceAll( pszCalibration_Instruction , "\\n" , "\n" , NULL);  
													
													ShowMessage ( tMainStore.hDatabaseHandle , INSTR_TYPE_CONTINUE , "Instruction", pInstruction , pszCalibration_Picture );       
												}
												
												FREE(pInstruction);  
												FREE(pszCalibration_Instruction);  
												FREE(pszCalibration_Picture);  
								
												if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_NA_StateFile" , &pszCalibration_StateFile ) <= 0 ) 
												{
													CALLOC( pszCalibration_StateFile , 128 , sizeof(char));
	
													if ( pszCalibration_StateFile )
													{
														strcpy( pszCalibration_StateFile , "calib.sta" );
														VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_NA_StateFile" , pszCalibration_StateFile );  
													}
												}
										
												if ( pszCalibration_StateFile && strlen(pszCalibration_StateFile)) 
												{
													UPDATERR( fDRV_NetworkAnalyzer_LoadStateAndCalibration ( hCalibrationNetworkAnalyzerHandle , pszNetworkCalibration_StateFile[iNetworkCalIndex] ));
												}
											
											
												if ( VarGetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_NA_PortNumber" , &piCalibrationPowerMeter_PortNumber ) == 0 )
												{
													fDRIVER_MANAGER_Set_Calibration_Port_Number( equipmentForInit[iEquipmentIndex]->handle , 1 ); 

													CALLOC( piCalibrationPowerMeter_PortNumber , 1 , sizeof(int));
				
													if ( piCalibrationPowerMeter_PortNumber )
													{
														*piCalibrationPowerMeter_PortNumber = 1;
					
														VarSetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_NA_PortNumber" , 1 , piCalibrationPowerMeter_PortNumber );  
													}
												}
			
												if ( piCalibrationPowerMeter_PortNumber )
													iCalibrationPowerMeter_PortNumber = (*piCalibrationPowerMeter_PortNumber);
												else
													iCalibrationPowerMeter_PortNumber = 1;
			
												fDRIVER_MANAGER_Set_Calibration_Port_Number(hCalibrationNetworkAnalyzerHandle , iCalibrationPowerMeter_PortNumber ); 
			
												FREE(piCalibrationPowerMeter_PortNumber);
												
												SetCtrlVal( hPopupPanel , WAIT_TEXTMSG , "Calibrating : Auxiliary Cable"); 
												InstallPopup ( hPopupPanel );
						
												fDRIVER_MANAGER_CALIBRATION_CreateEmptyHandle( &hCalibrationReferencePathHandle );
												fDRIVER_MANAGER_CALIBRATION_FillCalibrationRanges( hCalibrationReferencePathHandle , pszCalibration_FrequencyRanges );
												
												CHK_STDERR( fDRIVER_MANAGER_CALIBRATION_Run( hCalibrationNetworkAnalyzerHandle , hCalibrationNetworkAnalyzerHandle , hCalibrationReferencePathHandle , hPopupPanel , WAIT_PROGRESS ));	
			
												RemovePopup(0);
									
												NO_CHK_STDERR( fDRIVER_MANAGER_CALIBRATION_GetCalibrationInfo( hCalibrationReferencePathHandle , &pRefCalibFrequencyList , &pRefCalibFactorList , &iRefNumOfCalibPoints , NULL , NULL )); 

												fDRIVER_MANAGER_CALIBRATION_DiscardHandle( &hCalibrationReferencePathHandle );
												
												if ( pCalibFrequencyList && pCalibFactorList && iNumOfCalibPoints )
												{
													SetWaitCursor (1);
													VarSetCalibration( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , 0 , "Auxiliary_Cable" , pRefCalibFrequencyList , pRefCalibFactorList , iRefNumOfCalibPoints , 1 , 1 );               
													SetWaitCursor (0);
												}
												else
												{   
													VarGetCalibration( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , 0 , "Auxiliary_Cable" , &pRefCalibFrequencyList , &pRefCalibFactorList , &iRefNumOfCalibPoints , &lfRefCalibDateTime );               
												}
											}
									}
								}
								
								if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Instruction" , &pszCalibration_Instruction ) <= 0 ) 
								{
									CALLOC( pszCalibration_Instruction , 128 , sizeof(char));
		
									if ( pszCalibration_Instruction )
									{
										if ( hCalibrationPowerMeterHandle )
										{
											sprintf( pszCalibration_Instruction , "Please connect the Power Meter \"%s\" Sensor %d\nto the Signal generator \"%s\"." , szCalibPowerMeter , iCalibrationPowerMeter_PortNumber , equipmentForInit[iEquipmentIndex]->name );
										}
										else
										{
											if ( hCalibrationSpectrumAnalyzerHandle )
												sprintf( pszCalibration_Instruction , "Please connect the Spectrum Analyzer \"%s\"\nto the Signal generator \"%s\"." , szCalibSpectrumAnalyzer , equipmentForInit[iEquipmentIndex]->name );
										}
									
										VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Instruction" , pszCalibration_Instruction );  
									}
								}
						
								if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Picture" , &pszCalibration_Picture ) <= 0 ) 
								{
									CALLOC( pszCalibration_Picture , 128 , sizeof(char));

									if ( pszCalibration_Picture )
									{
										strcpy( pszCalibration_Picture , "." );
				
										VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Picture" , pszCalibration_Picture );  
									}
								}
				
								//------------- Apply Path Commands --------------------------------------//
								if ( pRF_CalibrationPathCommand && iNumberOfPathCommands && hCurrentRfBoxHandle && pRF_CalibrationPathCommand[0] && strlen( pRF_CalibrationPathCommand[0] ))
								{
									for( iPathCommandIndex = 0; iPathCommandIndex < iNumberOfPathCommands; iPathCommandIndex++ )
									{
										if ( pRF_CalibrationPathCommand[iPathCommandIndex] && strlen( pRF_CalibrationPathCommand[iPathCommandIndex] ))
										{
											CHK_STDERR( fDRIVER_MANAGER_StandardDevice_SetListOfValues( hCurrentRfBoxHandle , pRF_CalibrationPathCommand[iPathCommandIndex] , 1 , 3 ));
										}
									}
								}
								//-------------------------------------------------------------------------//
								
								if ( pszCalibration_Instruction && strlen(pszCalibration_Instruction) )
								{
									pInstruction = StringReplaceAll( pszCalibration_Instruction , "\\n" , "\n" , NULL);
								
									ShowMessage ( tMainStore.hDatabaseHandle , INSTR_TYPE_CONTINUE , "Instruction",pInstruction , pszCalibration_Picture ); 
								}     
								
								FREE(pInstruction);  
								FREE(pszCalibration_Instruction);  
								FREE(pszCalibration_Picture); 
												
								sprintf( szFormatedString , "Calibrating : %s" , equipmentForInit[iEquipmentIndex]->name ); 
							
								SetCtrlVal( hPopupPanel , WAIT_TEXTMSG , szFormatedString ); 
								InstallPopup ( hPopupPanel );
							
								CHK_STDERR( fDRIVER_MANAGER_CALIBRATION_Run( equipmentForInit[iEquipmentIndex]->handle , hCalibrationMeasureHandle , equipmentForInit[iEquipmentIndex]->handle , hPopupPanel , WAIT_PROGRESS ));	
				
								RemovePopup(0); 
							
								for( iPowerIndex = 0; iPowerIndex < iNumberOfPowers; iPowerIndex++ )
								{
									if ( iPowerIndex == 0 )
									{
										NO_CHK_STDERR( fDRIVER_MANAGER_CALIBRATION_GetCalibrationInfo( equipmentForInit[iEquipmentIndex]->handle , &pCalibFrequencyList , &pCalibFactorList , &iNumOfCalibPoints , NULL , NULL )); 
									}
									else
									{
										NO_CHK_STDERR( fDRIVER_MANAGER_CALIBRATION_Get_AdditionalPower_CalibrationInfo( equipmentForInit[iEquipmentIndex]->handle , (iPowerIndex-1) , &pCalibFactorList , &iNumOfCalibPoints , &lfCalibrationPower )); 
									}
							
									if ( pCalibFrequencyList && pCalibFactorList && iNumOfCalibPoints )
									{
										lfStartFrequency = pCalibFrequencyList[0];
										lfStopFrequency = pCalibFrequencyList[iNumOfCalibPoints-1];

										if ( hPopupCalibrationGraphPanel )
											DiscardPanel ( hPopupCalibrationGraphPanel ); 
								
										hPopupCalibrationGraphPanel = LoadPanel (0, "TEST_EXEC_UI.uir", CALIBGRAPH );

										SetCtrlAttribute (hPopupCalibrationGraphPanel , CALIBGRAPH_GRAPH , ATTR_NUM_TRACES , 2 ); 
	
										SetTraceAttributeEx ( hPopupCalibrationGraphPanel , CALIBGRAPH_GRAPH , 1 , ATTR_TRACE_LG_TEXT , "Cal Factor" );
										SetTraceAttributeEx ( hPopupCalibrationGraphPanel , CALIBGRAPH_GRAPH , 2 , ATTR_TRACE_LG_TEXT , "Delta" );
								
										FREE(pOldCalibFactorList);
										FREE(pOldCalibFrequencyList);
										iOldNumOfCalibPoints = 0;
										lfLastCalibrationDate = 0.0;
								
										if ( iPowerIndex )
											sprintf( szFormatedString , "Calibration%d" , iPowerIndex );
										else
											strcpy( szFormatedString , "Calibration" );
								
										VarGetCalibration( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , 0 , szFormatedString , &pOldCalibFrequencyList , &pOldCalibFactorList , &iOldNumOfCalibPoints , &lfLastCalibrationDate );         
							
										FREE_CALLOC_ERR( pCalibDeltaList , iNumOfCalibPoints , sizeof(double));
										FREE_CALLOC_ERR( pSinglePlot , (iNumOfCalibPoints*2) , sizeof(double));
							
										if ( iOldNumOfCalibPoints == iNumOfCalibPoints )
											for ( iIndex=0; iIndex < iNumOfCalibPoints; iIndex++ )
												pCalibDeltaList[iIndex] = pCalibFactorList[iIndex] - pOldCalibFactorList[iIndex];
							
										if ( iNumOfCalibPoints > 3 )
											SetCtrlAttribute ( hPopupCalibrationGraphPanel , CALIBGRAPH_GRAPH , ATTR_POINTS_PER_SCREEN , iNumOfCalibPoints );
									
										iPlotIndex = 0;
							
										for ( iIndex = 0 ; iIndex < iNumOfCalibPoints  ; iIndex++ ) 
										{
											pSinglePlot[iPlotIndex++] = pCalibFactorList[iIndex];
											pSinglePlot[iPlotIndex++] = pCalibDeltaList[iIndex];
										}
	
										PlotStripChart ( hPopupCalibrationGraphPanel , CALIBGRAPH_GRAPH , pSinglePlot , iPlotIndex , 0 , 0 , VAL_DOUBLE );

										lfStepFrequency = ( lfStopFrequency - lfStartFrequency ) / ( iNumOfCalibPoints - 1 );
								
										SetAxisScalingMode (hPopupCalibrationGraphPanel, CALIBGRAPH_GRAPH, VAL_BOTTOM_XAXIS, VAL_MANUAL, lfStartFrequency, lfStepFrequency);
								
										InstallPopup ( hPopupCalibrationGraphPanel );  
							
										SetCtrlVal ( hPopupCalibrationGraphPanel , CALIBGRAPH_POWER , lfCalibrationPower );
									
										do
										{
											MakeApplicationActive ();
											SetActivePanel ( hPopupCalibrationGraphPanel );
											ProcessDrawEvents();
																
											event = GetUserEvent ( 1 , &panel , &control );   
		
											if ( panel != hPopupCalibrationGraphPanel )
												continue;

											if ( control == CALIBGRAPH_SAVE )
											{   
												if ( iPowerIndex )
													sprintf( szFormatedString , "Calibration%d" , iPowerIndex );
												else
													strcpy( szFormatedString , "Calibration" );
											
												SetWaitCursor (1);
												VarSetCalibration( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , 0 , szFormatedString , pCalibFrequencyList , pCalibFactorList , iNumOfCalibPoints , 1 , 1 );               
												SetWaitCursor (0);
												
												break;
											}
		
										}while ( control != CALIBGRAPH_DISCARD );
								
										RemovePopup(0); 
									}	 
								}
							}
						}
						else
						{
							ShowMessage ( tMainStore.hDatabaseHandle , INSTR_TYPE_CONTINUE , "Frequency Range Error","No frequency range found." , NULL );
						}
					
						equipmentForInit[iEquipmentIndex]->bAlreadyCalibrated = 1;  
					}
				}
			}
		
			//============================== Spectrum Analyzer Calibration =============================================//
			for ( iEquipmentIndex = 0 ; iEquipmentIndex < iEquipmentCount ; iEquipmentIndex++ )  
			{
				bReferenceCableInUse = 0;
				
				if ( equipmentForInit[iEquipmentIndex]->type == EQUIPMENT_TYPE_SPECTRUM_ANALYZER )
				{
					if ( equipmentForInit[iEquipmentIndex]->priority == 0 )
					{
						hCalibrationSpectrumAnalyzerHandle = equipmentForInit[iEquipmentIndex]->handle;
					
						if ( equipmentForInit[iEquipmentIndex]->name  )
							strcpy( szCalibSpectrumAnalyzer , equipmentForInit[iEquipmentIndex]->name );
					}
				
					if ( fDRV_SpectrumAnalyzer_AlignNow == NULL )
						fDRV_SpectrumAnalyzer_AlignNow = (tfDRV_SpectrumAnalyzer_AlignNow) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SpectrumAnalyzer_AlignNow" );  

					if ( fDRV_SpectrumAnalyzer_AlignNow && ( equipmentForInit[iEquipmentIndex]->bAligning == 0 ))
					{
						SetCtrlVal( hPopupPanel , WAIT_TEXTMSG , "Spectrum Analyzer : Aligning..."); 
						InstallPopup ( hPopupPanel );
							
						lfAligning_Timeout = 60.0;
						
						if ( VarGetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Aligning_Timeout" , &plfAligning_Timeout ) == 0 )
						{
							FREE_CALLOC( plfAligning_Timeout , 1 , sizeof(double));
			
							if ( plfAligning_Timeout )
							{
								*plfAligning_Timeout = lfAligning_Timeout;
								
								VarSetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Aligning_Timeout" , 1 , plfAligning_Timeout );  
							}
						}
						
						if ( plfAligning_Timeout )
							lfAligning_Timeout = *plfAligning_Timeout;
							
						fDRV_SpectrumAnalyzer_AlignNow ( hCalibrationSpectrumAnalyzerHandle , lfAligning_Timeout );
						
						RemovePopup(0); 
						
						equipmentForInit[iEquipmentIndex]->bAligning = 1;
					}
					
					if ((( equipmentForInit[iEquipmentIndex]->calibratable ) && hCalibrationSignalGeneratorHandle ) && ( equipmentForInit[iEquipmentIndex]->bAlreadyCalibrated == 0 ))
					{
						FREE(plfCalibration_PowersList);
			
						iNumberOfPowers = VarGetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_AdditionalPowers" , &plfCalibration_PowersList );
		
						if ( iNumberOfPowers )
						do
						{
							if ( iNumberOfPowers == 1 ) 
							{
								VarGetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Power" , &plfCalibration_Power );

								if ( plfCalibration_Power )
								{
									if ( plfCalibration_Power[0] == plfCalibration_PowersList[0] )
										break;
								}
							}
							
							fDRIVER_MANAGER_CALIBRATION_Set_NumberOf_AdditionalPower( equipmentForInit[iEquipmentIndex]->handle , plfCalibration_PowersList , iNumberOfPowers );
					
							iNumberOfPowers++;
			
						} while(0);
			
						if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Frequency_Ranges" , &pszCalibration_FrequencyRanges ) <= 0 ) 
						{
							FREE_CALLOC( pszCalibration_FrequencyRanges , 64 , sizeof(char));
		
							if ( pszCalibration_FrequencyRanges )
							{
								strcpy( pszCalibration_FrequencyRanges , "1E6-2E6:201" );   
						
								VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Frequency_Ranges" , pszCalibration_FrequencyRanges );  
							}
						}	
				
						if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_SG_Frequency_Ranges" , &pszCalibration_SG_FrequencyRanges ) <= 0 ) 
						{
							FREE_CALLOC( pszCalibration_SG_FrequencyRanges , 64 , sizeof(char));
		
							if ( pszCalibration_SG_FrequencyRanges )
							{
								strcpy( pszCalibration_SG_FrequencyRanges , "1E6-2E6:201" );
							
								VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_SG_Frequency_Ranges" , pszCalibration_SG_FrequencyRanges );  
							}
						}
					
						if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_StateFile" , &pszCalibration_StateFile ) <= 0 ) 
						{
							CALLOC( pszCalibration_StateFile , 64 , sizeof(char));
		
							if ( pszCalibration_StateFile )
							{
								strcpy( pszCalibration_StateFile , "calib.sta" );   
						
								VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_StateFile" , pszCalibration_StateFile );  
							}
						}
				
						if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Generator_StateFile" , &pszCalibration_Generator_StateFile ) <= 0 ) 
						{
							FREE_CALLOC( pszCalibration_Generator_StateFile , 64 , sizeof(char));
		
							if ( pszCalibration_Generator_StateFile )
							{
								strcpy( pszCalibration_Generator_StateFile , "" );   
						
								VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Generator_StateFile" , pszCalibration_Generator_StateFile );  
							}
						}
						
						if ( VarGetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Power" , &plfCalibration_Power ) == 0 )
						{
							FREE_CALLOC( plfCalibration_Power , 1 , sizeof(double));
			
							if ( plfCalibration_Power )
							{
								VarSetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Power" , 1 , plfCalibration_Power );  
							}
						}
				
						if ( VarGetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Delay" , &plfCalibration_Delay ) == 0 )
						{
							FREE_CALLOC( plfCalibration_Delay , 1 , sizeof(double));
			
							if ( plfCalibration_Delay )
							{
								VarSetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Delay" , 1 , plfCalibration_Delay );  
							}
						}

						if ( VarGetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_ReferenceLevel" , &plfCalibration_ReferenceLevel ) == 0 )
						{
							FREE_CALLOC( plfCalibration_ReferenceLevel , 1 , sizeof(double));
			
							if ( plfCalibration_ReferenceLevel )
							{
								VarSetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_ReferenceLevel" , 1 , plfCalibration_ReferenceLevel );  
							}
						}
				
						if ( VarGetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Attenuator" , &plfCalibration_Attenuator ) == 0 )
						{
							FREE_CALLOC( plfCalibration_Attenuator , 1 , sizeof(double));
			
							if ( plfCalibration_Attenuator )
							{
								VarSetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Attenuator" , 1 , plfCalibration_Attenuator );  
							}
						}
				
						if ( VarGetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_AuxCable_Disable" , &piCalibration_AuxCable_Disable ) == 0 )
						{
							FREE_CALLOC( piCalibration_AuxCable_Disable , 1 , sizeof(int));
			
							if ( piCalibration_AuxCable_Disable )
							{
								VarSetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_AuxCable_Disable" , 1 , piCalibration_AuxCable_Disable );  
							}
						}
				
						if ( VarGetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Auto" , &piCalibration_Auto ) == 0 )
						{
							FREE_CALLOC( piCalibration_Auto , 1 , sizeof(int));
			
							if ( piCalibration_Auto )
							{
								VarSetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Auto" , 1 , piCalibration_Auto );  
							}
						}
						
						if ( VarGetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_Auto" , &piCalibration_Aux_Auto ) == 0 )
						{
							FREE_CALLOC( piCalibration_Aux_Auto , 1 , sizeof(int));
			
							if ( piCalibration_Aux_Auto )
							{
								VarSetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_Auto" , 1 , piCalibration_Aux_Auto );  
							}
						}
						
						if ( VarGetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_SelfAuxCalibration" , &piCalibration_SelfAuxCalibration ) == 0 )
						{
							FREE_CALLOC( piCalibration_SelfAuxCalibration , 1 , sizeof(int));
			
							if ( piCalibration_SelfAuxCalibration )
							{
								VarSetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_SelfAuxCalibration" , 1 , piCalibration_SelfAuxCalibration );  
							}
						}
						
						if ( plfCalibration_Power )
						{
							fDRIVER_MANAGER_Set_Calibration_Power( equipmentForInit[iEquipmentIndex]->handle , (*plfCalibration_Power) );
							FREE(plfCalibration_Power);
						}
				
						if ( plfCalibration_Delay )
						{
							fDRIVER_MANAGER_Set_Calibration_MeasureDelay( equipmentForInit[iEquipmentIndex]->handle , (*plfCalibration_Delay) );
							FREE(plfCalibration_Delay);
						}
				
						if ( plfCalibration_ReferenceLevel )
						{
							fDRIVER_MANAGER_Set_Calibration_ReferenceLevel( equipmentForInit[iEquipmentIndex]->handle , (*plfCalibration_ReferenceLevel) );
							FREE(plfCalibration_ReferenceLevel);
						}
				
						if ( plfCalibration_Attenuator )
						{
							fDRIVER_MANAGER_Set_Calibration_Attenuator( equipmentForInit[iEquipmentIndex]->handle , (*plfCalibration_Attenuator) );
							FREE(plfCalibration_Attenuator);
						}
				
						if ( pszCalibration_StateFile && ( strlen(pszCalibration_StateFile)))
						{
							fDRIVER_MANAGER_Set_Calibration_StateFileName( equipmentForInit[iEquipmentIndex]->handle , pszCalibration_StateFile );
							FREE(pszCalibration_StateFile);
						}
				
						if ( pszCalibration_Generator_StateFile && (strlen(pszCalibration_Generator_StateFile))) 
						{
							fDRIVER_MANAGER_Set_Calibration_StateFileName( hCalibrationSignalGeneratorHandle , pszCalibration_Generator_StateFile );
							FREE(pszCalibration_Generator_StateFile);	
						}
						
						if ( pszCalibration_FrequencyRanges && ( strlen(pszCalibration_FrequencyRanges)))
						{
							NO_CHK_STDERR( fDRIVER_MANAGER_CALIBRATION_FillCalibrationRanges( equipmentForInit[iEquipmentIndex]->handle , pszCalibration_FrequencyRanges ));
							
							if ( pszCalibration_SG_FrequencyRanges && ( strlen(pszCalibration_SG_FrequencyRanges))) 
							{
								NO_CHK_STDERR( fDRIVER_MANAGER_CALIBRATION_FillCalibrationRanges( hCalibrationSignalGeneratorHandle , pszCalibration_SG_FrequencyRanges ));
							}
							
							sprintf( szFormatedString , "Do you want to calibrate the Spectrum Analyzer:\n- %s\nFactors?" , equipmentForInit[iEquipmentIndex]->name );
					
							if (( piCalibration_Auto && piCalibration_Auto[0] ) || ( ShowMessage ( tMainStore.hDatabaseHandle , INSTR_TYPE_YES_NO , "Spectrum Analyzer", szFormatedString , NULL )))
							{
								//------------------- Prepare RF Box configuration ---------------------------------//
								FREE( pCalibFrequencyList );
								FREE( pCalibFactorList );
								iNumOfCalibPoints = 0;
								lfLastCalibrationDate = 0.0;
								hCurrentRfBoxHandle = 0;
								
								FREE_LIST( pRF_CalibrationPathCommand , iNumberOfPathCommands );
								FREE_LIST( pRF_CalibrationAuxPathCommand , iNumberOfAuxPathCommands );
								
								if ( equipmentForInit[iEquipmentIndex]->rfboxlink )
								{
									for ( index = 0 ; index < iEquipmentCount ; index++ )   
										if ( equipmentForInit[iEquipmentIndex]->rfboxlink == equipmentForInit[index]->id )
										{
											hCurrentRfBoxHandle = equipmentForInit[index]->handle;
											
											sprintf( szCommandVariableName , "%s_CAL_RF_PATH_COMMANDS" , equipmentForInit[iEquipmentIndex]->name );
											
											StringUpperCase ( szCommandVariableName );
											
											pTemp = StringReplaceAll( szCommandVariableName , " " , "_" , NULL); 
											
											if ( pTemp )
											{
												strcpy( szCommandVariableName , pTemp );
												
												FREE(pTemp);
											}
												
											iNumberOfPathCommands = VarGetStringArray( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[index]->id , szCommandVariableName , &pRF_CalibrationPathCommand ); 
										
											if (( iNumberOfPathCommands == 0 ) || ( pRF_CalibrationPathCommand == NULL ))
											{
												VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[index]->id , szCommandVariableName , "" );	
											}
											
											sprintf( szCommandVariableName , "%s_CAL_RF_AUX_PATH_COMMANDS" , equipmentForInit[iEquipmentIndex]->name );
											
											StringUpperCase ( szCommandVariableName );
											
											pTemp = StringReplaceAll( szCommandVariableName , " " , "_" , NULL); 
											
											if ( pTemp )
											{
												strcpy( szCommandVariableName , pTemp );
												
												FREE(pTemp);
											}
												
											iNumberOfAuxPathCommands = VarGetStringArray( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[index]->id , szCommandVariableName , &pRF_CalibrationAuxPathCommand ); 
										
											if (( iNumberOfAuxPathCommands == 0 ) || ( pRF_CalibrationAuxPathCommand == NULL ))
											{
												VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[index]->id , szCommandVariableName , "" );	
											}
											
											break;
										}
								}
								
								if ( piCalibration_SelfAuxCalibration )
									bSelfAuxCalibration = piCalibration_SelfAuxCalibration[0];
									
								//=============================================== Auxiliary Cable Spectrum Analyzer Calibration =======================================================================//
								if (( hCalibrationSignalGeneratorHandle && hCalibrationPowerMeterHandle ) || hCalibrationNetworkAnalyzerHandle || bSelfAuxCalibration )
								{
									FREE(pszCalibration_AuxFrequencyRanges);
									
									if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_Frequency_Ranges" , &pszCalibration_AuxFrequencyRanges ) <= 0 ) 
									{
										FREE_CALLOC( pszCalibration_AuxFrequencyRanges , 64 , sizeof(char));
		
										if ( pszCalibration_AuxFrequencyRanges )
										{
											strcpy( pszCalibration_AuxFrequencyRanges , "1E6-2E6:201" );   
						
											VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_Frequency_Ranges" , pszCalibration_AuxFrequencyRanges );  
										}
									}	
									
									if ( pszCalibration_AuxFrequencyRanges && ( strlen(pszCalibration_AuxFrequencyRanges)))
									{   
										if (( piCalibration_AuxCable_Disable == NULL ) || ( (*piCalibration_AuxCable_Disable) == 0 ))
										{
											bReferenceCableInUse = 1;  
											
											if ( ( piCalibration_Aux_Auto && piCalibration_Aux_Auto[0] ) || ( ShowMessage ( tMainStore.hDatabaseHandle , INSTR_TYPE_YES_NO , "Auxiliary Cable", "Do you want to calibrate the Auxiliary Cable Factors?" , NULL )))
											{
												//------------- Apply Path Commands --------------------------------------//
												if ( pRF_CalibrationAuxPathCommand && iNumberOfAuxPathCommands && hCurrentRfBoxHandle && pRF_CalibrationAuxPathCommand[0] && strlen( pRF_CalibrationAuxPathCommand[0] ))
												{
													for( iPathCommandIndex = 0; iPathCommandIndex < iNumberOfAuxPathCommands; iPathCommandIndex++ )
													{
														if ( pRF_CalibrationAuxPathCommand[iPathCommandIndex] && strlen( pRF_CalibrationAuxPathCommand[iPathCommandIndex] ))
														{
															CHK_STDERR( fDRIVER_MANAGER_StandardDevice_SetListOfValues( hCurrentRfBoxHandle , pRF_CalibrationAuxPathCommand[iPathCommandIndex] , 1 , 3 ));
														}
													}
												}
												//-------------------------------------------------------------------------//
												
												if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_Instruction" , &pszCalibration_Instruction ) <= 0 ) 
												{
													CALLOC( pszCalibration_Instruction , 128 , sizeof(char));
		
													if ( pszCalibration_Instruction )
													{
														if ( bSelfAuxCalibration )
														{
															sprintf( pszCalibration_Instruction , "Please connect the reference cable between\nSignal Generator \"%s\" and Spectrum Analyzer \"%s\"" , szCalibSignalGenerator , szCalibSpectrumAnalyzer );
														}
														else
														{
															if (( hCalibrationSignalGeneratorHandle == hCalibrationPowerMeterHandle ) && ( hCalibrationPowerMeterHandle == hCalibrationNetworkAnalyzerHandle ))
																sprintf( pszCalibration_Instruction , "Please connect the reference cable between\nPort 1 and Port 2 of the Network Analyzer \"%s\"" , szCalibNetworkAnalyzer );
															else
																sprintf( pszCalibration_Instruction , "Please connect the reference cable between\nSignal Generator \"%s\" and Power Meter \"%s\"" , szCalibSignalGenerator , szCalibPowerMeter );
														}
														
														VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_Instruction" , pszCalibration_Instruction );  
													}
												}
												
												if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_Picture" , &pszCalibration_Picture ) <= 0 ) 
												{
													CALLOC( pszCalibration_Picture , 128 , sizeof(char));

													if ( pszCalibration_Picture )
													{
														strcpy( pszCalibration_Picture , "." );
				
														VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_Picture" , pszCalibration_Picture );  
													}
												}
												
												if ( pszCalibration_Instruction && strlen(pszCalibration_Instruction)) 
												{
													pInstruction = StringReplaceAll( pszCalibration_Instruction , "\\n" , "\n" , NULL);
								
													ShowMessage ( tMainStore.hDatabaseHandle , INSTR_TYPE_CONTINUE , "Instruction",pInstruction , pszCalibration_Picture ); 
												}
					
												FREE(pInstruction);  
												FREE(pszCalibration_Instruction);  
												FREE(pszCalibration_Picture); 
												
												if ( hCalibrationNetworkAnalyzerHandle && ( bSelfAuxCalibration == 0 ))
												{
													if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_NA_StateFile" , &pszCalibration_StateFile ) <= 0 ) 
													{
														CALLOC( pszCalibration_StateFile , 128 , sizeof(char));
		
														if ( pszCalibration_StateFile )
														{
															strcpy( pszCalibration_StateFile , "calib.sta" );
															VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_NA_StateFile" , pszCalibration_StateFile );  
														}
													}
											
													if ( pszCalibration_StateFile && strlen(pszCalibration_StateFile)) 
													{
														UPDATERR( fDRV_NetworkAnalyzer_LoadStateAndCalibration ( hCalibrationNetworkAnalyzerHandle , pszCalibration_StateFile ));
													}
													
													if ( VarGetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_NA_PortNumber" , &piCalibrationPowerMeter_PortNumber ) == 0 )
													{
														fDRIVER_MANAGER_Set_Calibration_Port_Number( equipmentForInit[iEquipmentIndex]->handle , 1 ); 

														CALLOC( piCalibrationPowerMeter_PortNumber , 1 , sizeof(int));
				
														if ( piCalibrationPowerMeter_PortNumber )
														{
															*piCalibrationPowerMeter_PortNumber = 1;
					
															VarSetInt( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Aux_NA_PortNumber" , 1 , piCalibrationPowerMeter_PortNumber );  
														}
													}
			
													if ( piCalibrationPowerMeter_PortNumber )
														iCalibrationPowerMeter_PortNumber = (*piCalibrationPowerMeter_PortNumber);
													else
														iCalibrationPowerMeter_PortNumber = 1;
			
													fDRIVER_MANAGER_Set_Calibration_Port_Number(hCalibrationNetworkAnalyzerHandle , iCalibrationPowerMeter_PortNumber ); 
			
													FREE(piCalibrationPowerMeter_PortNumber);
												
												}
												
												SetCtrlVal( hPopupPanel , WAIT_TEXTMSG , "Calibrating : Auxiliary Cable"); 
												InstallPopup ( hPopupPanel );
						
												fDRIVER_MANAGER_CALIBRATION_CreateEmptyHandle( &hCalibrationReferencePathHandle );
												fDRIVER_MANAGER_CALIBRATION_FillCalibrationRanges( hCalibrationReferencePathHandle , pszCalibration_AuxFrequencyRanges );
												fDRIVER_MANAGER_CALIBRATION_GetCalibrationInfo( hCalibrationReferencePathHandle , NULL  , NULL , &iNumOfCalibPoints , &lfStartFrequency , &lfStopFrequency ); 
												
												if ( bSelfAuxCalibration )
												{
													CHK_STDERR( fDRIVER_MANAGER_CALIBRATION_Run( hCalibrationSignalGeneratorHandle , hCalibrationSpectrumAnalyzerHandle , hCalibrationReferencePathHandle , hPopupPanel , WAIT_PROGRESS ));	
												}
												else
												{
													if ( hCalibrationSignalGeneratorHandle && hCalibrationPowerMeterHandle )
													{
														CHK_STDERR( fDRIVER_MANAGER_CALIBRATION_Run( hCalibrationSignalGeneratorHandle , hCalibrationPowerMeterHandle , hCalibrationReferencePathHandle , hPopupPanel , WAIT_PROGRESS ));	
													}
													else
													{
														CHK_STDERR( fDRIVER_MANAGER_CALIBRATION_Run( hCalibrationNetworkAnalyzerHandle , 0 , hCalibrationReferencePathHandle , hPopupPanel , WAIT_PROGRESS ));	
													}
												}
												
												NO_CHK_STDERR( fDRIVER_MANAGER_CALIBRATION_GetCalibrationInfo( hCalibrationReferencePathHandle , &pRefCalibFrequencyList , &pRefCalibFactorList , &iRefNumOfCalibPoints , NULL , NULL )); 

												fDRIVER_MANAGER_CALIBRATION_DiscardHandle( &hCalibrationReferencePathHandle );
												
												if ( pRefCalibFrequencyList && pRefCalibFactorList && iRefNumOfCalibPoints )
												{								
													if (( pRefCalibFrequencyList[0] != lfStartFrequency ) || ( pRefCalibFrequencyList[iRefNumOfCalibPoints-1] != lfStopFrequency ) || ( iRefNumOfCalibPoints != iNumOfCalibPoints ))
													{
														MTH_LinearExtrapolationArray( pRefCalibFrequencyList , pRefCalibFactorList , iRefNumOfCalibPoints , 0 , iRefNumOfCalibPoints , iNumOfCalibPoints , lfStartFrequency , lfStopFrequency , &pCalibFrequencyList  , &pCalibFactorList );
														
														FREE( pRefCalibFrequencyList );
														FREE( pRefCalibFactorList );
														
														pRefCalibFrequencyList = pCalibFrequencyList;
														pRefCalibFactorList = pCalibFactorList;
													}
													
													SetCtrlVal( hPopupPanel , WAIT_TEXTMSG , "Saving . . .");  
													
													SetWaitCursor (1);
													VarSetCalibration( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , 0 , "Auxiliary_Cable" , pRefCalibFrequencyList , pRefCalibFactorList , iRefNumOfCalibPoints , 1 , 1 );               
													SetWaitCursor (0);
													
													FREE( pRefCalibFrequencyList );
													FREE( pRefCalibFactorList );  
												}
												
												RemovePopup(0);  
											}
										}
									}
								}
								//=============================================== Spectrum Analyzer Calibration =======================================================================//
								if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Instruction" , &pszCalibration_Instruction ) <= 0 ) 
								{
									CALLOC( pszCalibration_Instruction , 128 , sizeof(char));
		
									if ( pszCalibration_Instruction )
									{
										sprintf( pszCalibration_Instruction , "Please connect the Signal Generator \"%s\"\nto the Spectrum Analyzer \"%s\"." , szCalibSignalGenerator , equipmentForInit[iEquipmentIndex]->name );
								
										VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Instruction" , pszCalibration_Instruction );  
									}
								}
						
								if ( VarGetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Picture" , &pszCalibration_Picture ) <= 0 ) 
								{
									CALLOC( pszCalibration_Picture , 128 , sizeof(char));

									if ( pszCalibration_Picture )
									{
										strcpy( pszCalibration_Picture , "." );

										VarSetString( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , "Calibration_Picture" , pszCalibration_Picture );  
									}
								}
								
								//------------- Apply Path Commands --------------------------------------//
								if ( pRF_CalibrationPathCommand && iNumberOfPathCommands && hCurrentRfBoxHandle && pRF_CalibrationPathCommand[0] && strlen( pRF_CalibrationPathCommand[0] ))
								{
									for( iPathCommandIndex = 0; iPathCommandIndex < iNumberOfPathCommands; iPathCommandIndex++ )
									{
										if ( pRF_CalibrationPathCommand[iPathCommandIndex] && strlen( pRF_CalibrationPathCommand[iPathCommandIndex] ))
										{
											CHK_STDERR( fDRIVER_MANAGER_StandardDevice_SetListOfValues( hCurrentRfBoxHandle , pRF_CalibrationPathCommand[iPathCommandIndex] , 1 , 3 ));
										}
									}
								}
								//-------------------------------------------------------------------------//

								if ( pszCalibration_Instruction && strlen(pszCalibration_Instruction) )
								{
									pInstruction = StringReplaceAll( pszCalibration_Instruction , "\\n" , "\n" , NULL);
								
									ShowMessage ( tMainStore.hDatabaseHandle , INSTR_TYPE_CONTINUE , "Instruction",pInstruction , pszCalibration_Picture );  
								}     
								
								FREE(pInstruction);  
								FREE(pszCalibration_Instruction);  
								FREE(pszCalibration_Picture); 
												
								sprintf( szFormatedString , "Calibrating : %s" , equipmentForInit[iEquipmentIndex]->name ); 
							
								SetCtrlVal( hPopupPanel , WAIT_TEXTMSG , szFormatedString ); 
								InstallPopup ( hPopupPanel );
							
								CHK_STDERR( fDRIVER_MANAGER_CALIBRATION_Run( hCalibrationSignalGeneratorHandle , equipmentForInit[iEquipmentIndex]->handle , equipmentForInit[iEquipmentIndex]->handle , hPopupPanel , WAIT_PROGRESS ));	
				
								RemovePopup(0); 
						
								for( iPowerIndex = 0; iPowerIndex < iNumberOfPowers; iPowerIndex++ )
								{
									if ( iPowerIndex == 0 )
									{
										NO_CHK_STDERR( fDRIVER_MANAGER_CALIBRATION_GetCalibrationInfo( equipmentForInit[iEquipmentIndex]->handle , &pCalibFrequencyList , &pCalibFactorList , &iNumOfCalibPoints , NULL , NULL )); 
									}
									else
									{
										NO_CHK_STDERR( fDRIVER_MANAGER_CALIBRATION_Get_AdditionalPower_CalibrationInfo( equipmentForInit[iEquipmentIndex]->handle , (iPowerIndex-1) , &pCalibFactorList , &iNumOfCalibPoints , &lfCalibrationPower )); 
									}  
							
									if ( pCalibFrequencyList && pCalibFactorList && iNumOfCalibPoints )
									{
										lfStartFrequency = pCalibFrequencyList[0];
										lfStopFrequency = pCalibFrequencyList[iNumOfCalibPoints-1];

										if ( hPopupCalibrationGraphPanel )
											DiscardPanel ( hPopupCalibrationGraphPanel ); 
							
										hPopupCalibrationGraphPanel = LoadPanel (0, "TEST_EXEC_UI.uir", CALIBGRAPH );

										SetCtrlAttribute (hPopupCalibrationGraphPanel , CALIBGRAPH_GRAPH , ATTR_NUM_TRACES , 2 ); 
										
										SetTraceAttributeEx ( hPopupCalibrationGraphPanel , CALIBGRAPH_GRAPH , 1 , ATTR_TRACE_LG_TEXT , "Cal Factor" );
										SetTraceAttributeEx ( hPopupCalibrationGraphPanel , CALIBGRAPH_GRAPH , 2 , ATTR_TRACE_LG_TEXT , "Delta" );
				
										FREE(pOldCalibFactorList);
										FREE(pOldCalibFrequencyList);
										iOldNumOfCalibPoints = 0;
										lfLastCalibrationDate = 0.0;
								
										if ( iPowerIndex )
											sprintf( szFormatedString , "Calibration%d" , iPowerIndex );
										else
											strcpy( szFormatedString , "Calibration" );
								
										VarGetCalibration( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , 0 , szFormatedString , &pOldCalibFrequencyList , &pOldCalibFactorList , &iOldNumOfCalibPoints , &lfLastCalibrationDate );         
							
										FREE_CALLOC_ERR( pCalibDeltaList , iNumOfCalibPoints , sizeof(double));
										FREE_CALLOC_ERR( pSinglePlot , (iNumOfCalibPoints*2) , sizeof(double));
							
										if ( bReferenceCableInUse )
										{
											VarGetCalibration( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , 0 , "Auxiliary_Cable" , &pRefCalibFrequencyList , &pRefCalibFactorList , &iRefNumOfCalibPoints , &lfRefCalibDateTime );               
										
											for ( iIndex=0; iIndex < iNumOfCalibPoints; iIndex++ )
											{
												MTH_InterpolationSingle( 0 , pRefCalibFrequencyList , pRefCalibFactorList ,  iRefNumOfCalibPoints , pCalibFrequencyList[iIndex] , &lfReferenceCableLoss );
																							
												pCalibFactorList[iIndex] -= lfReferenceCableLoss;
											}
										}
										
										if ( iOldNumOfCalibPoints == iNumOfCalibPoints )
											for ( iIndex=0; iIndex < iNumOfCalibPoints; iIndex++ )
												pCalibDeltaList[iIndex] = pCalibFactorList[iIndex] - pOldCalibFactorList[iIndex];
							
										SetCtrlAttribute ( hPopupCalibrationGraphPanel , CALIBGRAPH_GRAPH , ATTR_POINTS_PER_SCREEN , iNumOfCalibPoints );
							
										iPlotIndex = 0;
							
										for ( iIndex = 0 ; iIndex < iNumOfCalibPoints  ; iIndex++ ) 
										{
											pSinglePlot[iPlotIndex++] = pCalibFactorList[iIndex];
											pSinglePlot[iPlotIndex++] = pCalibDeltaList[iIndex];
										}
	
										PlotStripChart ( hPopupCalibrationGraphPanel , CALIBGRAPH_GRAPH , pSinglePlot , iPlotIndex , 0 , 0 , VAL_DOUBLE );
	
										lfStepFrequency = ( lfStopFrequency - lfStartFrequency ) / ( iNumOfCalibPoints - 1 );
							
										SetAxisScalingMode (hPopupCalibrationGraphPanel, CALIBGRAPH_GRAPH, VAL_BOTTOM_XAXIS, VAL_MANUAL, lfStartFrequency, lfStepFrequency);  
							
										SetCtrlVal ( hPopupCalibrationGraphPanel , CALIBGRAPH_POWER , lfCalibrationPower );

										InstallPopup ( hPopupCalibrationGraphPanel );  
							
										do
										{
											MakeApplicationActive ();
											SetActivePanel ( hPopupCalibrationGraphPanel );
											ProcessDrawEvents();
																
											event = GetUserEvent ( 1 , &panel , &control );   
		
											if ( panel != hPopupCalibrationGraphPanel )
												continue;

											if ( control == CALIBGRAPH_SAVE )
											{
												if ( iPowerIndex )
													sprintf( szFormatedString , "Calibration%d" , iPowerIndex );
												else
													strcpy( szFormatedString , "Calibration" );
									
												SetCtrlVal( hPopupPanel , WAIT_TEXTMSG , "Saving. . ."); 
												
												SetWaitCursor (1);
												VarSetCalibration( hMainHandle , VAR_CONFIG_EQUIPMENT , equipmentForInit[iEquipmentIndex]->id , 0 , szFormatedString , pCalibFrequencyList , pCalibFactorList , iNumOfCalibPoints , 1 , 1 );               
												SetWaitCursor (0);
												
												break;
											}
		
										}while ( control != CALIBGRAPH_DISCARD );
							
										RemovePopup(0); 
									}	 
								}
							}
						}
						else
						{
							ShowMessage ( tMainStore.hDatabaseHandle , INSTR_TYPE_CONTINUE , "Frequency Range Error","No frequency range found." , NULL );
						}
				
						equipmentForInit[iEquipmentIndex]->bAlreadyCalibrated = 1;  
					}
				}
			}
		}
	}
	
	if ( bRunAutoSelectionOnly == 0 )
	{
		do
		{
			MakeApplicationActive ();
			SetActivePanel ( hPanelEquipment );
			ProcessDrawEvents();
		
			CHK_CMT( CmtGetTSVPtr ( hMainHandle , &pMainStore ));  
			STDERR_COPY ( pMainStore->pRet );
			CmtReleaseTSVPtr (hMainHandle);
			StdError.pNextLevelError = NULL; 
			CHK_STDERR(StdError);
		
			event = GetUserEvent ( 1 , &panel , &control );   
		
			if ( panel != hPanelEquipment )
				continue;

			if ( control == EQUIP_INIT_CANCEL )
			{
				*pbSkipRunning = 1;
				break;
			}
		
		}while ( control != EQUIP_INIT_ACCEPT );
	}
	
Error:

	if ( bPopup )
		RemovePopup (0);
	
	if ( hPanelEquipment )
		DiscardPanel ( hPanelEquipment );
	
	if ( hPopupCalibrationGraphPanel )
		DiscardPanel ( hPopupCalibrationGraphPanel ); 
		
	if ( hPopupPanel )
		DiscardPanel ( hPopupPanel ); 
	
	if ( hPanelEquipmentLock )
		CmtDiscardLock ( hPanelEquipmentLock );
	
	if ( iEquipmentCount && ( CmtGetTSVPtr ( hMainHandle , &pMainStore ) == 0 ))
	{ 
		for ( index = 0 ; index < pMainStore->tCurrentRunTestSeq.iNumberOfSelectedTests ; index++ )   
			if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[index].ptlDB_EquipmentList )
				for ( iEquipmentUseIndex = 0 ; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[index].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
					for ( iEquipmentIndex = 0 ; iEquipmentIndex < iEquipmentCount ; iEquipmentIndex++ ) 			
						if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[index].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].equipment_id == equipmentForInit[iEquipmentIndex]->id )
						{
							pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[index].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle = (pInitBlockMemory[iEquipmentIndex]->equipmentForInit)->handle;	
							pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[index].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].type = equipmentForInit[iEquipmentIndex]->type;	
							pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[index].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].depends_on_power = equipmentForInit[iEquipmentIndex]->depends_on_power;	
						}
		CmtReleaseTSVPtr (hMainHandle);
	}
	
	db_equipment_use_freelist(&equipmentUseList);      
	db_equipment_freelist(&equipmentList);
	
	FREE_LIST( pRF_CalibrationPathCommand , iNumberOfPathCommands );
	FREE_LIST( pRF_CalibrationAuxPathCommand , iNumberOfAuxPathCommands ); 
	
	for ( iEquipmentIndex = 0 ; iEquipmentIndex < iEquipmentCount ; iEquipmentIndex++ )   
	{
		if ( pInitBlockMemory[iEquipmentIndex] )
		{
			db_equipment_free( &(pInitBlockMemory[iEquipmentIndex]->equipmentForInit) );
				
			FREE(pInitBlockMemory[iEquipmentIndex]);
		}
	}
	
	FREE_LIST ( pszNetworkCalibration_FrequencyRanges , iNumberOfNetworkRanges );
	FREE_LIST ( pszNetworkCalibration_StateFile , iNumberOfNetworkStateFiles );
	
	FREE( pInitBlockMemory );
	
	FREE(plfCalibration_Power);
	FREE(pCalibFrequencyList);
	FREE(pCalibFactorList);
	FREE(pOldCalibFrequencyList);
	FREE(pOldCalibFactorList);
	FREE(pRefCalibFrequencyList);
	FREE(pRefCalibFactorList);
	FREE(pszCalibration_FrequencyRanges);
	FREE(plfCalibration_PowersList);
	FREE(plfCalibration_Timeout);
	FREE(plfCalibration_Delay);
	FREE(pCalibDeltaList);
	FREE(pSinglePlot);
	FREE(equipmentForInit);
	FREE(pFilePathName);
	FREE(pszCalibration_Instruction);
	FREE(pInstruction);  
	FREE(pszCalibration_Picture); 
	FREE(pszCalibration_Generator_StateFile);
	FREE(pszCalibration_AuxFrequencyRanges);
	FREE(piCalibration_SelfAuxCalibration);						
	FREE(pszCalibration_StateFile); 
	FREE(piCalibration_AuxCable_Disable);
	FREE(piCalibration_Aux_Auto);  
	FREE(piCalibration_Auto);  
	FREE(pRFBoxUnitsList);
	FREE(pszECAL_Configuration);
	FREE(pszECAL_UserCharacterizations);
	FREE(pThreadFunctionIdList);
	
	return StdError;
}

STD_ERROR		TE_EQUIP_CloseEquipment( int hMainHandle , unsigned long long hEquipmentID , int hEquipmentHandle )
{	
	STD_ERROR										StdError											=	{0};

	tsMainStore										*pMainStore											=	NULL,
													tMainStore											=	{0}; 
													
	tfDRIVER_MANAGER_Close							fDRIVER_MANAGER_Close								=	NULL;

	int												index												=	0,
													iTestIndex											=	0,
													iEquipmentUseIndex									=	0;  
													
	int												iNumberOfEquipment									=	0,
													iNumberOfEquipmentUsed								=	0;
	
	int												vToCloseHandles[1024]								=	{0},
													vEquipmentTypess[1024]								=	{0};
	
	int												bCloseOnlyOneDevice									= 	0;
	
	CHK_CMT( CmtGetTSVPtr ( hMainHandle , &pMainStore )); 
	memcpy( &tMainStore , pMainStore , sizeof(tsMainStore));
	
	for ( iTestIndex = 0 ; iTestIndex < tMainStore.tCurrentRunTestSeq.iNumberOfSelectedTests ; iTestIndex++ )   
		if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList )    
		{
			iNumberOfEquipment = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->count;
											  
			for ( iEquipmentUseIndex = 0 ; iEquipmentUseIndex < iNumberOfEquipment ; iEquipmentUseIndex++ )    
			{
				for ( index = 0; index < iNumberOfEquipmentUsed; index++ )
				{
					if ( vToCloseHandles[index] == pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle )
					{
						pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle = 0;
						break;
					}
				}

				if ( bCloseOnlyOneDevice )
					continue;
				
				if ( hEquipmentID > 0 ) 
				{
					if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].equipment_id == hEquipmentID )
					{
						if ( hEquipmentHandle == 0 )
						{
							bCloseOnlyOneDevice = 1;
						}
						else
						{
							if ( hEquipmentHandle != pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle )
								continue;
							
							bCloseOnlyOneDevice = 1; 
						}
					}
					else
						continue;
				}

				if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle )
				{
					vToCloseHandles[iNumberOfEquipmentUsed] = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle;
	
					pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle = 0;
	
					vEquipmentTypess[iNumberOfEquipmentUsed] = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].type;
			
					iNumberOfEquipmentUsed++;
				}				
			}
		}
	
	CHK_CMT( CmtReleaseTSVPtr (hMainHandle));   
	
	IF (( tMainStore.hDriverManagerLibrary == NULL ) , "Driver Manager is not found." );    
	
	for ( iEquipmentUseIndex = 0 ; iEquipmentUseIndex < iNumberOfEquipmentUsed; iEquipmentUseIndex++ )  
		if ( vToCloseHandles[iEquipmentUseIndex] )
		{   
			switch( vEquipmentTypess[iEquipmentUseIndex] )
			{
				case EQUIPMENT_TYPE_STANDARD_DEVICE:	
	
					fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_Close" ); 
		
					break;
		 
				case EQUIPMENT_TYPE_POWER_SUPPLY:	
	
					fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerSupply_Close" ); 

					break;
		 
				case EQUIPMENT_TYPE_NETWORK_ANALYZER:	
	
					fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NetworkAnalyzer_Close" ); 
		
					break;
		 
				case EQUIPMENT_TYPE_SIGNAL_GENERATOR:	
	
					fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SignalGenerator_Close" ); 

					break;
		 
				case EQUIPMENT_TYPE_SPECTRUM_ANALYZER:	
	
					fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SpectrumAnalyzer_Close" ); 

					break;
		 
				case EQUIPMENT_TYPE_OSCILLOSCOPE:	
	
					fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_Oscilloscope_Close" ); 

					break;
		 
				case EQUIPMENT_TYPE_FUNCTION_GENERATOR:	
	
					fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_FunctionGenerator_Close" ); 

					break;
		 
				case EQUIPMENT_TYPE_POWER_METER:	
	
					fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerMeter_Close" ); 

					break;
		 
				case EQUIPMENT_TYPE_NOISE_FIGURE:	
	
					fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NoiseFigure_Close" ); 
		
					break;
		 
				case EQUIPMENT_TYPE_MULTI_METER:	
	
					fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_MultiMeter_Close" ); 
		
					break;
		 
				case EQUIPMENT_TYPE_WAVE_FORM_ANALYZER:	
	
					fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_WaveAnalyzer_Close" ); 
		
					break;
	
				default:
		
					break;
			}
			
			if ( fDRIVER_MANAGER_Close )
			{
				NO_CHK_STDERR( fDRIVER_MANAGER_Close( &(vToCloseHandles[iEquipmentUseIndex]) ));	 
			}
				
		}
	
Error:
	
	return StdError;
}

STD_ERROR		TE_EQUIP_TestConnection( int hMainHandle , unsigned long long ulEquipmentID , int *pbTestStaus )
{	
	STD_ERROR															StdError															=	{0};
	
	tlEquipment															*equipmentList														=	NULL;
	
	tsMainStore															*pMainStore															=	NULL,
																		tMainStore															=	{0}; 
	
	int																	iIndex																=	0,
																		iEquipmentIndex														=	0,
																		iCheckDeviceIndex													=	0;
										
	int																	hPanelEquipment														=	0;
	
	tfDRIVER_MANAGER_GetErrorTextMessage								fDRIVER_MANAGER_GetErrorTextMessage									=	NULL;
	tfDRIVER_MANAGER_STD_Init											fDRIVER_MANAGER_STD_Init											=	NULL;  
	tfDRIVER_MANAGER_Init												fDRIVER_MANAGER_Init												=	NULL;
	tfDRIVER_MANAGER_Reset												fDRIVER_MANAGER_Reset												=	NULL;
	tfDRIVER_MANAGER_Close												fDRIVER_MANAGER_Close												=	NULL;
	
	tfDRIVER_MANAGER_STD_LoadConfigFile									fDRIVER_MANAGER_STD_LoadConfigFile									=	NULL;
	tfDRIVER_MANAGER_STD_Get_Commands_List								fDRIVER_MANAGER_STD_Get_Commands_List								=	NULL;
	tfDRIVER_MANAGER_STD_Check_Connection								fDRIVER_MANAGER_STD_Check_Connection								=	NULL;

	tfDRIVER_MANAGER_SETUP_UpdateCallbacksStructure						fDRIVER_MANAGER_SETUP_UpdateCallbacksStructure						=	NULL;

	tfDRIVER_MANAGER_Get_SimulationMode									fDRIVER_MANAGER_Get_SimulationMode									=	NULL;
	
	char																*pFilePathName														=	NULL,
																		*pSubDriverFilePathName												=	NULL; 
																
	int 																bPopup																=	0,
																		event																=	0,
																		panel																=	0,
																		control																=	0;

	char																szMessage[LOW_STRING]												=	{0};
	
	unsigned long long													ulCommandID															=	0;
	
	char																**vszSTD_Device_Commands_List										=	NULL;
	int																	iNumberOfSTD_Device_Commands										=	0,
																		bCheckDeviceStatus													=	0;
																	 
	int																	hPopupPanel															=	0,
																		hPopupCalibrationGraphPanel											=	0;  

	char																*pStringToStore														=	0;

	int																	iStringLength														=	0,
																		iBufferLength														=	0;

	void																*pCallBackStructure													=	NULL;

	int																	iSimulationMode														=	0;
	
	CHK_CMT( CmtGetTSVPtr ( hMainHandle , &pMainStore )); 
	memcpy( &tMainStore , pMainStore , sizeof(tsMainStore));  
	CHK_CMT(CmtReleaseTSVPtr (hMainHandle));
	
	if ( pbTestStaus )
		*pbTestStaus = 0; 
	
	IF (( tMainStore.hDriverManagerLibrary == NULL ) , "Driver Manager is not found." );
		
	db_equipment_getlist_by_type_station( tMainStore.hDatabaseHandle , tMainStore.hCurrentStationId , -1 ,&equipmentList);

	if (( equipmentList == NULL ) || ( equipmentList->equipment == NULL )) 
	{
		RETURN;
	}
	
	for ( iEquipmentIndex = 0 ; iEquipmentIndex < equipmentList->count ; iEquipmentIndex++ ) 
		if ( equipmentList->equipment[iEquipmentIndex].id == ulEquipmentID )
			break;
		
	IF (( equipmentList->equipment[iEquipmentIndex].id != ulEquipmentID ) , "Wrong Equipment ID" );
	
	fDRIVER_MANAGER_SETUP_UpdateCallbacksStructure = (tfDRIVER_MANAGER_SETUP_UpdateCallbacksStructure) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_SETUP_UpdateCallbacksStructure" );

	// fill driver manager call back data  
	FillCallbacksDataStructureOnly( hMainHandle , &pCallBackStructure , ulEquipmentID ); 

	fDRIVER_MANAGER_SETUP_UpdateCallbacksStructure( pCallBackStructure , 2 , equipmentList->equipment[iEquipmentIndex].address , ulEquipmentID );

	FREE(pCallBackStructure);  
	
	CHK_UIL (hPanelEquipment = LoadPanel (0, "TEST_EXEC_UI.uir", EQUIP_INIT ));

	InstallPopup (hPanelEquipment);
	bPopup = 1;
	
	InsertTableRows ( hPanelEquipment , EQUIP_INIT_TABLE , (1) , 1 , VAL_CELL_STRING );
	SetTableRowAttribute (hPanelEquipment, EQUIP_INIT_TABLE, (1), ATTR_LABEL_BOLD, 1);
	SetTableRowAttribute (hPanelEquipment, EQUIP_INIT_TABLE, (1), ATTR_LABEL_COLOR, VAL_WHITE);
	SetTableRowAttribute (hPanelEquipment, EQUIP_INIT_TABLE, (1), ATTR_LABEL_POINT_SIZE, 15);
	
	SetTableCellAttribute ( hPanelEquipment, EQUIP_INIT_TABLE ,MakePoint (1,(1)), ATTR_TEXT_BOLD, 1); 
	SetTableCellAttribute ( hPanelEquipment, EQUIP_INIT_TABLE ,MakePoint (2,(1)), ATTR_TEXT_BOLD, 1);
	SetTableCellAttribute ( hPanelEquipment, EQUIP_INIT_TABLE ,MakePoint (3,(1)), ATTR_TEXT_BOLD, 1);
	
	SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (1,(1)), ATTR_CELL_JUSTIFY, VAL_CENTER_CENTER_JUSTIFIED);
	SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (2,(1)), ATTR_CELL_JUSTIFY, VAL_CENTER_CENTER_JUSTIFIED);
	SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (3,(1)), ATTR_CELL_JUSTIFY, VAL_CENTER_CENTER_JUSTIFIED); 
	
	SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (1,(1)), ATTR_TEXT_COLOR, MAIN_COLOR );
	SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (2,(1)), ATTR_TEXT_COLOR, MAIN_COLOR );
	
	SetTableCellVal ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(1,(1)), equipmentList->equipment[iEquipmentIndex].alias );
	SetTableCellVal ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(2,(1)), equipmentList->equipment[iEquipmentIndex].name ); 
	
	//----------------------------------- Initialization -----------------------------------------//
	
	UPDATERR( GetDataBaseFileByID( tMainStore.hDatabaseHandle , equipmentList->equipment[iEquipmentIndex].driverlink , NULL , NULL , NULL  , NULL , &pFilePathName ));

	fDRIVER_MANAGER_Get_SimulationMode = (tfDRIVER_MANAGER_Get_SimulationMode) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_Get_SimulationMode" );
	
	if ( IS_NOT_OK )
	{
		sprintf( szMessage , "File Driver is not found for equipment %s" , equipmentList->equipment[iEquipmentIndex].name );
		ShowMessage ( tMainStore.hDatabaseHandle , INSTR_TYPE_CONTINUE , "Driver Error.",szMessage , NULL );
	}
	else
	{
		if ( equipmentList->equipment[iEquipmentIndex].driverchildlink )
		{
			UPDATERR( GetDataBaseFileByID( tMainStore.hDatabaseHandle , equipmentList->equipment[iEquipmentIndex].driverchildlink , NULL , NULL , NULL  , NULL , &pSubDriverFilePathName )); 	
			
			if ( IS_OK && pSubDriverFilePathName )
			{
				if ( FileExists( pSubDriverFilePathName , NULL ))	
				{
					LoadLibrary ( pSubDriverFilePathName ); 	
				}
			}
			
			FREE(pSubDriverFilePathName);
		}
			
		switch(equipmentList->equipment[iEquipmentIndex].type)
		{
			case EQUIPMENT_TYPE_STANDARD_DEVICE:	
		
				fDRIVER_MANAGER_STD_Init = (tfDRIVER_MANAGER_STD_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_Close" ); 
				
				fDRIVER_MANAGER_STD_LoadConfigFile = (tfDRIVER_MANAGER_STD_LoadConfigFile) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_LoadConfigFile" );		
				fDRIVER_MANAGER_STD_Get_Commands_List = (tfDRIVER_MANAGER_STD_Get_Commands_List) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_Get_Commands_List" );	
				fDRIVER_MANAGER_STD_Check_Connection = (tfDRIVER_MANAGER_STD_Check_Connection) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_Check_Connection" );	
				
				if (( strchr( equipmentList->equipment[iEquipmentIndex].id_command , 'x' )) || ( strchr( equipmentList->equipment[iEquipmentIndex].id_command , 'X' )) )
					sscanf( equipmentList->equipment[iEquipmentIndex].id_command , "%llx" , &ulCommandID );
				else
					ulCommandID = atol(equipmentList->equipment[iEquipmentIndex].id_command);
				
				UPDATERR( fDRIVER_MANAGER_STD_Init( pFilePathName , (int)ulCommandID , equipmentList->equipment[iEquipmentIndex].alias , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle ) , 1 , 1 ));

				if (( IS_OK ) && ( equipmentList->equipment[iEquipmentIndex].configlink )) 
				{
					UPDATERR( GetDataBaseFileByID( tMainStore.hDatabaseHandle , equipmentList->equipment[iEquipmentIndex].configlink , NULL , NULL , NULL  , NULL , &pFilePathName )); 
				
					if ( IS_OK )
					{
						UPDATERR( fDRIVER_MANAGER_STD_LoadConfigFile( equipmentList->equipment[iEquipmentIndex].handle , pFilePathName ));
					}
					
					if ( IS_OK )
					{
						UPDATERR( fDRIVER_MANAGER_STD_Get_Commands_List( equipmentList->equipment[iEquipmentIndex].handle , &vszSTD_Device_Commands_List , &iNumberOfSTD_Device_Commands ));
						
						if ( IS_OK )
						{
							IF ((( vszSTD_Device_Commands_List == NULL ) || ( iNumberOfSTD_Device_Commands == 0 )) , "No configuration info found." );
							
							for ( iIndex = 0; iIndex < iNumberOfSTD_Device_Commands; iIndex++ )
								iStringLength += strlen( vszSTD_Device_Commands_List[iIndex] ) + 1;

							CALLOC_ERR( pStringToStore , iStringLength , sizeof(char));
		
							for ( iIndex = 0; iIndex < iNumberOfSTD_Device_Commands; iIndex++ )
								iBufferLength += sprintf(( pStringToStore + iBufferLength ) , "%s\0" , vszSTD_Device_Commands_List[iIndex] ) + 1;
	
							if ( iBufferLength )
								iBufferLength--;
	
							VarSetBuffer(  hMainHandle ,  VAR_CONFIG_EQUIPMENT , equipmentList->equipment[iEquipmentIndex].id , "Commands_List" , pStringToStore , iBufferLength );
							
							FREE(pStringToStore);
						}
					}
					
					if ( equipmentList->equipment[iEquipmentIndex].check_commands )
					{
						if ( IS_OK )
						{
							for ( iCheckDeviceIndex = 0; iCheckDeviceIndex < iNumberOfSTD_Device_Commands; iCheckDeviceIndex++ )
							{
								if ( vszSTD_Device_Commands_List[iCheckDeviceIndex] && strlen(vszSTD_Device_Commands_List[iCheckDeviceIndex]) && ( vszSTD_Device_Commands_List[0] != '-'))
								{
									CHK_STDERR_BREAK( fDRIVER_MANAGER_STD_Check_Connection ( equipmentList->equipment[iEquipmentIndex].handle , vszSTD_Device_Commands_List[iCheckDeviceIndex] , &bCheckDeviceStatus ));
							
									if ( bCheckDeviceStatus == 0 )
									{
										sprintf( szMessage , "Command [%s] is not initializet yet!!!" , vszSTD_Device_Commands_List[iCheckDeviceIndex] );
								
										IF (( ConfirmPopup(szMessage,"Do you want to continue?") == 0 ) , szMessage );
									}
								}
							}
						}
					}
				}
				
				break;
			 
			case EQUIPMENT_TYPE_POWER_SUPPLY:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerSupply_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerSupply_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerSupply_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerSupply_Close" );      
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_NETWORK_ANALYZER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NetworkAnalyzer_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NetworkAnalyzer_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NetworkAnalyzer_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NetworkAnalyzer_Close" );      
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_SIGNAL_GENERATOR:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SignalGenerator_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SignalGenerator_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SignalGenerator_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SignalGenerator_Close" );        
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_SPECTRUM_ANALYZER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SpectrumAnalyzer_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SpectrumAnalyzer_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SpectrumAnalyzer_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SpectrumAnalyzer_Close" ); 
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_OSCILLOSCOPE:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_Oscilloscope_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_Oscilloscope_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_Oscilloscope_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_Oscilloscope_Close" ); 
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_FUNCTION_GENERATOR:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_FunctionGenerator_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_FunctionGenerator_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_FunctionGenerator_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_FunctionGenerator_Close" ); 

				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_POWER_METER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerMeter_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerMeter_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerMeter_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerMeter_Close" ); 

				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_NOISE_FIGURE:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NoiseFigure_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NoiseFigure_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NoiseFigure_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NoiseFigure_Close" ); 
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));
			
				break;
			 
			case EQUIPMENT_TYPE_MULTI_METER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_MultiMeter_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_MultiMeter_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_MultiMeter_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_MultiMeter_Close" ); 
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));
			
				break;
			 
			case EQUIPMENT_TYPE_WAVE_FORM_ANALYZER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_WaveAnalyzer_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_WaveAnalyzer_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_WaveAnalyzer_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_WaveAnalyzer_Close" ); 
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));
			
				break;
		
			default:
			
				break;
		}
	}
	
	if ( IS_OK )
	{
		if ( equipmentList->equipment[iEquipmentIndex].handle == 0 )
		{
			SET_ERR( -23 , "Wrong Driver Initialization." );
		}
	}
	
	if ( IS_OK )
	{
		UPDATERR( fDRIVER_MANAGER_Reset( equipmentList->equipment[iEquipmentIndex].handle ));	
	}
	
	fDRIVER_MANAGER_Get_SimulationMode( equipmentList->equipment[iEquipmentIndex].handle , &iSimulationMode );  
	
	if ( fDRIVER_MANAGER_Close )
		fDRIVER_MANAGER_Close( &(equipmentList->equipment[iEquipmentIndex].handle) );	 

	SetActivePanel ( hPanelEquipment );  
	SetActiveTableCell ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(3,(1)) );       
	
	if ( IS_OK ) 
	{
		SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (3,(1)), ATTR_TEXT_COLOR, VAL_DK_GREEN ); 
		
		if ( iSimulationMode )
		{
			SetTableCellVal ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(3,(1)), "DEMO" );   						
		}
		else
		{   
			SetTableCellVal ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(3,(1)), "PASS" );   						
			
			equipmentList->equipment[iEquipmentIndex].dev_exists = 1;
		}
		
		if ( pbTestStaus )
			*pbTestStaus = 1; 
	}
	else
	{
		SetTableCellAttribute ( hPanelEquipment, EQUIP_INIT_TABLE ,MakePoint (3,(1)), ATTR_TEXT_COLOR,VAL_DK_RED); 
		SetTableCellVal ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(3,(1)), "FAIL" );  
		
		equipmentList->equipment[iEquipmentIndex].dev_exists = 0;
	}
	
	db_equipment_edit( tMainStore.hDatabaseHandle , &(equipmentList->equipment[iEquipmentIndex]));
	
	ProcessDrawEvents(); 
	
	do
	{
		MakeApplicationActive ();
		SetActivePanel ( hPanelEquipment );
		ProcessDrawEvents();
	
		CHK_CMT( CmtGetTSVPtr ( hMainHandle , &pMainStore ));  
		if ( pMainStore->pRet && pMainStore->pRet->error )
		{
			FILL_STDERR( pMainStore->pRet ); 
		}
		CmtReleaseTSVPtr (hMainHandle);
		CHK_STDERR(StdError);
	
		event = GetUserEvent ( 1 , &panel , &control );   
	
		if ( panel != hPanelEquipment )
			continue;

		if ( control == EQUIP_INIT_CANCEL )
			break;
	
	}while ( control != EQUIP_INIT_ACCEPT );
	
Error:

	if ( bPopup )
		RemovePopup (0);
	
	if ( hPanelEquipment )
		DiscardPanel ( hPanelEquipment );
	
	if ( hPopupCalibrationGraphPanel )
		DiscardPanel ( hPopupCalibrationGraphPanel ); 
		
	if ( hPopupPanel )
		DiscardPanel ( hPopupPanel ); 
	
	db_equipment_freelist(&equipmentList);
	
	FREE(pFilePathName);
	
	FREE_LIST( vszSTD_Device_Commands_List , iNumberOfSTD_Device_Commands );
	
	return StdError;
}

STD_ERROR		TE_EQUIP_ViewCalibration( int hMainHandle , unsigned long long ulEquipmentID )
{	
	STD_ERROR															StdError															=	{0};
	
	tlEquipment															*equipmentList														=	NULL;
	
	tsMainStore															*pMainStore															=	NULL,
																		tMainStore															=	{0}; 
	
	int																	iEquipmentIndex														=	0,																
																		iPlotIndex															=	0,
																		iIndex																=	0;
																		
	
	int 																bPopup																=	0,
																		event																=	0,
																		panel																=	0,
																		control																=	0;

	char																szFormatedString[LOW_STRING]										=	{0},
																		szDateString[LOW_STRING]											=	{0};
	
	double																*plfCalibration_PowersList											=	NULL, 
																		*plfCalibration_Power												=	NULL;
																
	int																	iPowerIndex															=	0;
																		
	int																	hPopupCalibrationGraphPanel											=	0;  
																	
	double																*pCalibFrequencyList												=	NULL,
																		*pCalibFactorList													=	NULL,
																		*pSinglePlot														=	NULL; 
																	
	int																	iNumberOfPowers														=	0, 
																		iNumOfCalibPoints													=	0;
	
	double																lfCalibrationDate													=	0.0,
																		lfCalibrationPower													=	0.0, 
																		lfStartFrequency													=	0.0,
																		lfStopFrequency														=	0.0,
																		lfStepFrequency														=	0.0;   
	
															
	CHK_CMT( CmtGetTSVPtr ( hMainHandle , &pMainStore )); 
	memcpy( &tMainStore , pMainStore , sizeof(tsMainStore));  
	CHK_CMT(CmtReleaseTSVPtr (hMainHandle));
	
	IF (( tMainStore.hDriverManagerLibrary == NULL ) , "Driver Manager is not found." );
		
	db_equipment_getlist_by_type_station( tMainStore.hDatabaseHandle , tMainStore.hCurrentStationId , -1 ,&equipmentList);

	if (( equipmentList == NULL ) || ( equipmentList->equipment == NULL )) 
	{
		RETURN;
	}
	
	for ( iEquipmentIndex = 0 ; iEquipmentIndex < equipmentList->count ; iEquipmentIndex++ ) 
		if ( equipmentList->equipment[iEquipmentIndex].id == ulEquipmentID )
			break;
		
	IF (( equipmentList->equipment[iEquipmentIndex].id != ulEquipmentID ) , "Wrong Equipment ID" );
	
	IF ( ( VarGetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , ulEquipmentID , "Calibration_Power" , &plfCalibration_Power ) == 0 ) , "No Calibration found" );
	
	IF ( ( VarGetCalibration( hMainHandle , VAR_CONFIG_EQUIPMENT , ulEquipmentID , 0 , "Calibration" , &pCalibFrequencyList , &pCalibFactorList , &iNumOfCalibPoints , &lfCalibrationDate ) < 0 ) , "No Calibration" );
	
	IF ( ( iNumOfCalibPoints == 0 ) , "No Calibration" );
	
	iNumberOfPowers = VarGetDouble( hMainHandle , VAR_CONFIG_EQUIPMENT , ulEquipmentID , "Calibration_AdditionalPowers" , &plfCalibration_PowersList );
			
	if (( iNumberOfPowers == 1 ) && ( plfCalibration_PowersList[0] == plfCalibration_Power[0] ))
		iNumberOfPowers = 1;
	else
		iNumberOfPowers++;
	
	hPopupCalibrationGraphPanel = LoadPanel (0, "TEST_EXEC_UI.uir", CALIBGRAPH );  

	SetCtrlAttribute( hPopupCalibrationGraphPanel , CALIBGRAPH_SAVE , ATTR_VISIBLE , 0 );
	
	SetCtrlAttribute (hPopupCalibrationGraphPanel , CALIBGRAPH_GRAPH , ATTR_NUM_TRACES , iNumberOfPowers ); 
	
	SetCtrlAttribute ( hPopupCalibrationGraphPanel , CALIBGRAPH_GRAPH , ATTR_POINTS_PER_SCREEN , iNumOfCalibPoints );
	
	lfStartFrequency = pCalibFrequencyList[0];
	lfStopFrequency = pCalibFrequencyList[iNumOfCalibPoints-1];
	
	iPlotIndex = 0;
			
	FREE_CALLOC_ERR( pSinglePlot , (iNumOfCalibPoints*iNumberOfPowers) , sizeof(double));
	
	for( iPowerIndex = 0; iPowerIndex < iNumberOfPowers; iPowerIndex++ )
	{
		FREE(pCalibFactorList);
		FREE(pCalibFrequencyList);
		iNumOfCalibPoints = 0;
		lfCalibrationDate = 0.0;
		
		if ( iPowerIndex )
		{
			sprintf( szFormatedString , "Calibration%d" , iPowerIndex );
			lfCalibrationPower = plfCalibration_PowersList[iPowerIndex-1];
		}
		else
		{
			strcpy( szFormatedString , "Calibration" );
			lfCalibrationPower = plfCalibration_Power[0];
		}
		
		VarGetCalibration( hMainHandle , VAR_CONFIG_EQUIPMENT , ulEquipmentID , 0 , szFormatedString , &pCalibFrequencyList , &pCalibFactorList , &iNumOfCalibPoints , &lfCalibrationDate );         
	
		if ( pCalibFrequencyList && pCalibFactorList && ( iNumOfCalibPoints > 2 ))
			for ( iIndex = 0 ; iIndex < iNumOfCalibPoints  ; iIndex++ ) 
				pSinglePlot[(iIndex*iNumberOfPowers+iPowerIndex)] = pCalibFactorList[iIndex];
		
		sprintf( szFormatedString , "%0.1lf dBm" , lfCalibrationPower );
		SetTraceAttributeEx ( hPopupCalibrationGraphPanel , CALIBGRAPH_GRAPH , iPowerIndex+1 , ATTR_TRACE_LG_TEXT , szFormatedString );
	}
	
	PlotStripChart ( hPopupCalibrationGraphPanel , CALIBGRAPH_GRAPH , pSinglePlot , (iNumOfCalibPoints*iNumberOfPowers) , 0 , 0 , VAL_DOUBLE );

	lfStepFrequency = ( lfStopFrequency - lfStartFrequency ) / ( iNumOfCalibPoints - 1 );

	SetAxisScalingMode (hPopupCalibrationGraphPanel, CALIBGRAPH_GRAPH, VAL_BOTTOM_XAXIS, VAL_MANUAL, lfStartFrequency, lfStepFrequency);  

	SetCtrlAttribute ( hPopupCalibrationGraphPanel , CALIBGRAPH_POWER , ATTR_VISIBLE , 0 );
	SetCtrlAttribute ( hPopupCalibrationGraphPanel , CALIBGRAPH_DATE , ATTR_VISIBLE , 1 );
	
	FormatDateTimeString ( lfCalibrationDate , "%d/%m/%Y", szDateString , LOW_STRING );
	
	SetCtrlVal( hPopupCalibrationGraphPanel , CALIBGRAPH_DATE , szDateString );
	
	SetCtrlAttribute ( hPopupCalibrationGraphPanel , CALIBGRAPH_GRAPH , ATTR_LEGEND_NUM_VISIBLE_ITEMS , iNumberOfPowers );  
	
	InstallPopup ( hPopupCalibrationGraphPanel );  

	do
	{
		MakeApplicationActive ();
		SetActivePanel ( hPopupCalibrationGraphPanel );
		ProcessDrawEvents();
									
		event = GetUserEvent ( 1 , &panel , &control );   

		if ( panel != hPopupCalibrationGraphPanel )
			continue;

	}while ( control != CALIBGRAPH_DISCARD );

	RemovePopup(0); 

Error:

	if ( bPopup )
		RemovePopup (0);
	
	if ( hPopupCalibrationGraphPanel )
		DiscardPanel ( hPopupCalibrationGraphPanel ); 
		
	db_equipment_freelist(&equipmentList);
	
	FREE(pCalibFrequencyList);
	FREE(pCalibFactorList);
	FREE(plfCalibration_Power);
	FREE(plfCalibration_PowersList);
	FREE(pSinglePlot);
	
	return StdError;
}


STD_ERROR		TE_EQUIP_ConnectToEquipment( int hMainHandle , unsigned long long ulEquipmentID , int *pEquipmentHandle , int bViewConnectionWindow )
{	
	STD_ERROR													StdError											=	{0};
	
	tlEquipment													*equipmentList										=	NULL;
	
	tsMainStore													*pMainStore											=	NULL,
																tMainStore											=	{0}; 
	
	int															iEquipmentIndex										=	0,
																iCheckDeviceIndex									=	0;
										
	int															hPanelEquipment										=	0;
	
	tfDRIVER_MANAGER_GetErrorTextMessage						fDRIVER_MANAGER_GetErrorTextMessage					=	NULL;
	tfDRIVER_MANAGER_STD_Init									fDRIVER_MANAGER_STD_Init							=	NULL;  
	tfDRIVER_MANAGER_Init										fDRIVER_MANAGER_Init								=	NULL;
	tfDRIVER_MANAGER_Reset										fDRIVER_MANAGER_Reset								=	NULL;
	tfDRIVER_MANAGER_Close										fDRIVER_MANAGER_Close								=	NULL;
	
	tfDRIVER_MANAGER_STD_LoadConfigFile							fDRIVER_MANAGER_STD_LoadConfigFile					=	NULL;
	tfDRIVER_MANAGER_STD_Get_Commands_List						fDRIVER_MANAGER_STD_Get_Commands_List				=	NULL;
	tfDRIVER_MANAGER_STD_Check_Connection						fDRIVER_MANAGER_STD_Check_Connection				=	NULL;
	tfDRIVER_MANAGER_SETUP_UpdateCallbacksStructure				fDRIVER_MANAGER_SETUP_UpdateCallbacksStructure		=	NULL;
	
	tfDRIVER_MANAGER_Get_SimulationMode							fDRIVER_MANAGER_Get_SimulationMode					=	NULL;
	
	tfDRIVER_MANAGER_UpdateIgnoreDuplicationAddresses			fDRIVER_MANAGER_UpdateIgnoreDuplicationAddresses	=	NULL;
	
	char														*pFilePathName										=	NULL,
																*pSubDriverFilePathName								=	NULL;  
																
	int 														bPopup												=	0,
																event												=	0,
																panel												=	0,
																control												=	0;

	char														szMessage[LOW_STRING]								=	{0};
	
	unsigned long long											ulCommandID											=	0;
	
	char														**vszSTD_Device_Commands_List						=	NULL;
	int															iNumberOfSTD_Device_Commands						=	0,
																bCheckDeviceStatus									=	0;
																	 
	int															hPopupPanel											=	0,
																hPopupCalibrationGraphPanel							=	0;  
															
	int															hEquipmentHandle									=	0;
	
	int															iSimulationMode										=	0;

	void														*pCallBackStructure									=	NULL;
	
	CHK_CMT( CmtGetTSVPtr ( hMainHandle , &pMainStore )); 
	memcpy( &tMainStore , pMainStore , sizeof(tsMainStore));  
	CHK_CMT(CmtReleaseTSVPtr (hMainHandle));
	
	if ( pEquipmentHandle )
		*pEquipmentHandle = 0; 
	
	IF (( tMainStore.hDriverManagerLibrary == NULL ) , "Driver Manager is not found." );
		
	db_equipment_getlist_by_type_station( tMainStore.hDatabaseHandle , tMainStore.hCurrentStationId , -1 ,&equipmentList);

	if (( equipmentList == NULL ) || ( equipmentList->equipment == NULL )) 
	{
		RETURN;
	}
	
	for ( iEquipmentIndex = 0 ; iEquipmentIndex < equipmentList->count ; iEquipmentIndex++ ) 
		if ( equipmentList->equipment[iEquipmentIndex].id == ulEquipmentID )
			break;
		
	IF (( equipmentList->equipment[iEquipmentIndex].id != ulEquipmentID ) , "Wrong Equipment ID" );
	
	if ( bViewConnectionWindow )
	{
		CHK_UIL (hPanelEquipment = LoadPanel (0, "TEST_EXEC_UI.uir", EQUIP_INIT ));

		InstallPopup (hPanelEquipment);
		bPopup = 1;

		InsertTableRows ( hPanelEquipment , EQUIP_INIT_TABLE , (1) , 1 , VAL_CELL_STRING );
		SetTableRowAttribute (hPanelEquipment, EQUIP_INIT_TABLE, (1), ATTR_LABEL_BOLD, 1);
		SetTableRowAttribute (hPanelEquipment, EQUIP_INIT_TABLE, (1), ATTR_LABEL_COLOR, VAL_WHITE);
		SetTableRowAttribute (hPanelEquipment, EQUIP_INIT_TABLE, (1), ATTR_LABEL_POINT_SIZE, 15);
	
		SetTableCellAttribute ( hPanelEquipment, EQUIP_INIT_TABLE ,MakePoint (1,(1)), ATTR_TEXT_BOLD, 1); 
		SetTableCellAttribute ( hPanelEquipment, EQUIP_INIT_TABLE ,MakePoint (2,(1)), ATTR_TEXT_BOLD, 1);
		SetTableCellAttribute ( hPanelEquipment, EQUIP_INIT_TABLE ,MakePoint (3,(1)), ATTR_TEXT_BOLD, 1);
	
		SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (1,(1)), ATTR_CELL_JUSTIFY, VAL_CENTER_CENTER_JUSTIFIED);
		SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (2,(1)), ATTR_CELL_JUSTIFY, VAL_CENTER_CENTER_JUSTIFIED);
		SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (3,(1)), ATTR_CELL_JUSTIFY, VAL_CENTER_CENTER_JUSTIFIED); 
	
		SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (1,(1)), ATTR_TEXT_COLOR, MAIN_COLOR );
		SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (2,(1)), ATTR_TEXT_COLOR, MAIN_COLOR );
	
		SetTableCellVal ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(1,(1)), equipmentList->equipment[iEquipmentIndex].alias );
		SetTableCellVal ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(2,(1)), equipmentList->equipment[iEquipmentIndex].name ); 
	}
	
	//----------------------------------- Initialization -----------------------------------------//
	
	UPDATERR( GetDataBaseFileByID( tMainStore.hDatabaseHandle , equipmentList->equipment[iEquipmentIndex].driverlink , NULL , NULL , NULL  , NULL , &pFilePathName ));

	fDRIVER_MANAGER_SETUP_UpdateCallbacksStructure = (tfDRIVER_MANAGER_SETUP_UpdateCallbacksStructure) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_SETUP_UpdateCallbacksStructure" );
	
	// fill driver manager call back data  
	FillCallbacksDataStructureOnly( hMainHandle , &pCallBackStructure , ulEquipmentID ); 

	fDRIVER_MANAGER_SETUP_UpdateCallbacksStructure( pCallBackStructure , 2 , equipmentList->equipment[iEquipmentIndex].address , ulEquipmentID );

	FREE(pCallBackStructure); 
	
	fDRIVER_MANAGER_Get_SimulationMode = (tfDRIVER_MANAGER_Get_SimulationMode) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_Get_SimulationMode" );

	if ( IS_NOT_OK )
	{
		sprintf( szMessage , "File Driver is not found for equipment %s" , equipmentList->equipment[iEquipmentIndex].name );
	}
	else
	{
		if ( equipmentList->equipment[iEquipmentIndex].driverchildlink )
		{
			UPDATERR( GetDataBaseFileByID( tMainStore.hDatabaseHandle , equipmentList->equipment[iEquipmentIndex].driverchildlink , NULL , NULL , NULL  , NULL , &pSubDriverFilePathName )); 	
			
			if ( IS_OK && pSubDriverFilePathName )
			{
				if ( FileExists( pSubDriverFilePathName , NULL ))	
				{
					LoadLibrary ( pSubDriverFilePathName ); 	
				}
			}
			
			FREE(pSubDriverFilePathName);
		}
		
		switch(equipmentList->equipment[iEquipmentIndex].type)
		{
			case EQUIPMENT_TYPE_STANDARD_DEVICE:	
		
				fDRIVER_MANAGER_STD_Init = (tfDRIVER_MANAGER_STD_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_Close" ); 
				
				fDRIVER_MANAGER_STD_LoadConfigFile = (tfDRIVER_MANAGER_STD_LoadConfigFile) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_LoadConfigFile" );		
				fDRIVER_MANAGER_STD_Get_Commands_List = (tfDRIVER_MANAGER_STD_Get_Commands_List) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_Get_Commands_List" );	
				fDRIVER_MANAGER_STD_Check_Connection = (tfDRIVER_MANAGER_STD_Check_Connection) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_Check_Connection" );	
				fDRIVER_MANAGER_UpdateIgnoreDuplicationAddresses = (tfDRIVER_MANAGER_UpdateIgnoreDuplicationAddresses) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_UpdateIgnoreDuplicationAddresses" );
				
				if (( strchr( equipmentList->equipment[iEquipmentIndex].id_command , 'x' )) || ( strchr( equipmentList->equipment[iEquipmentIndex].id_command , 'X' )) )
					sscanf( equipmentList->equipment[iEquipmentIndex].id_command , "%llx" , &ulCommandID );
				else
					ulCommandID = atol(equipmentList->equipment[iEquipmentIndex].id_command);
				
				UPDATERR( fDRIVER_MANAGER_STD_Init( pFilePathName , (int)ulCommandID , equipmentList->equipment[iEquipmentIndex].alias , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle ) , 1 , 1 ));

				if ( equipmentList->equipment[iEquipmentIndex].dup_address )
				{
					fDRIVER_MANAGER_UpdateIgnoreDuplicationAddresses( equipmentList->equipment[iEquipmentIndex].handle );
				}
				
				if (( IS_OK ) && ( equipmentList->equipment[iEquipmentIndex].configlink )) 
				{
					UPDATERR( GetDataBaseFileByID( tMainStore.hDatabaseHandle , equipmentList->equipment[iEquipmentIndex].configlink , NULL , NULL , NULL  , NULL , &pFilePathName )); 
				
					if ( IS_OK )
					{
						UPDATERR( fDRIVER_MANAGER_STD_LoadConfigFile( equipmentList->equipment[iEquipmentIndex].handle , pFilePathName ));
					}
					
					if ( equipmentList->equipment[iEquipmentIndex].check_commands )
					{
						if ( IS_OK )
						{
							UPDATERR( fDRIVER_MANAGER_STD_Get_Commands_List( equipmentList->equipment[iEquipmentIndex].handle , &vszSTD_Device_Commands_List , &iNumberOfSTD_Device_Commands ));
						
							if ( IS_OK )
							{
								IF ((( vszSTD_Device_Commands_List == NULL ) || ( iNumberOfSTD_Device_Commands == 0 )) , "No configuration info found." );
							}
						}
					
						if ( IS_OK )
						{
							for ( iCheckDeviceIndex = 0; iCheckDeviceIndex < iNumberOfSTD_Device_Commands; iCheckDeviceIndex++ )
							{
								CHK_STDERR_BREAK( fDRIVER_MANAGER_STD_Check_Connection ( equipmentList->equipment[iEquipmentIndex].handle , vszSTD_Device_Commands_List[iCheckDeviceIndex] , &bCheckDeviceStatus ));
							
								if ( bCheckDeviceStatus == 0 )
								{
									sprintf( szMessage , "Command [%s] is not initializet yet!!!" , vszSTD_Device_Commands_List[iCheckDeviceIndex] );
								
									IF (( ConfirmPopup(szMessage,"Do you want to continue?") == 0 ) , szMessage );
								}
							}
						}
					}
				}
				
				break;
			 
			case EQUIPMENT_TYPE_POWER_SUPPLY:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerSupply_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerSupply_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerSupply_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerSupply_Close" );      
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_NETWORK_ANALYZER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NetworkAnalyzer_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NetworkAnalyzer_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NetworkAnalyzer_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NetworkAnalyzer_Close" );      
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_SIGNAL_GENERATOR:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SignalGenerator_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SignalGenerator_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SignalGenerator_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SignalGenerator_Close" );        
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_SPECTRUM_ANALYZER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SpectrumAnalyzer_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SpectrumAnalyzer_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SpectrumAnalyzer_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SpectrumAnalyzer_Close" ); 
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_OSCILLOSCOPE:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_Oscilloscope_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_Oscilloscope_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_Oscilloscope_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_Oscilloscope_Close" ); 
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_FUNCTION_GENERATOR:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_FunctionGenerator_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_FunctionGenerator_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_FunctionGenerator_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_FunctionGenerator_Close" ); 

				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_POWER_METER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerMeter_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerMeter_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerMeter_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerMeter_Close" ); 

				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_NOISE_FIGURE:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NoiseFigure_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NoiseFigure_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NoiseFigure_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NoiseFigure_Close" ); 
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));
			
				break;
			 
			case EQUIPMENT_TYPE_MULTI_METER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_MultiMeter_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_MultiMeter_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_MultiMeter_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_MultiMeter_Close" ); 
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));
			
				break;
			 
			case EQUIPMENT_TYPE_WAVE_FORM_ANALYZER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_WaveAnalyzer_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_WaveAnalyzer_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_WaveAnalyzer_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_WaveAnalyzer_Close" ); 
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));
			
				break;
		
			default:
			
				break;
		}
	}
	
	if ( IS_OK )
	{
		if ( equipmentList->equipment[iEquipmentIndex].handle == 0 )
		{
			SET_ERR( -23 , "Wrong Driver Initialization." );
		}
	}
	
	if ( IS_OK )
	{
		UPDATERR( fDRIVER_MANAGER_Reset( equipmentList->equipment[iEquipmentIndex].handle ));	
		
		hEquipmentHandle = equipmentList->equipment[iEquipmentIndex].handle;
	}
	
	fDRIVER_MANAGER_Get_SimulationMode( equipmentList->equipment[iEquipmentIndex].handle , &iSimulationMode );    
	
	if ( IS_NOT_OK )
	{
		hEquipmentHandle = 0;
		
		if ( fDRIVER_MANAGER_Close )
			fDRIVER_MANAGER_Close( &(equipmentList->equipment[iEquipmentIndex].handle) );	 
	}
	
	if ( bViewConnectionWindow )
	{
		SetActivePanel ( hPanelEquipment );  
		SetActiveTableCell ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(3,(1)) );       
	
		if ( IS_OK ) 
		{
			SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (3,(1)), ATTR_TEXT_COLOR, VAL_DK_GREEN ); 
		
			if ( iSimulationMode )
			{
				SetTableCellVal ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(3,(1)), "DEMO" );
			}
			else
			{
				SetTableCellVal ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(3,(1)), "PASS" );   						
			}
		}
		else
		{
			SetTableCellAttribute ( hPanelEquipment, EQUIP_INIT_TABLE ,MakePoint (3,(1)), ATTR_TEXT_COLOR,VAL_DK_RED); 
			SetTableCellVal ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(3,(1)), "FAIL" );  
		}
	
		ProcessDrawEvents(); 
	
		do
		{
			MakeApplicationActive ();
			SetActivePanel ( hPanelEquipment );
			ProcessDrawEvents();
	
			CHK_CMT( CmtGetTSVPtr ( hMainHandle , &pMainStore ));  
			STDERR_COPY ( pMainStore->pRet );
			CmtReleaseTSVPtr (hMainHandle);
			StdError.pNextLevelError = NULL; 
			CHK_STDERR(StdError);
	
			event = GetUserEvent ( 1 , &panel , &control );   
	
			if ( panel != hPanelEquipment )
				continue;

			if ( control == EQUIP_INIT_CANCEL )
				break;
	
		}while ( control != EQUIP_INIT_ACCEPT );
	}
	
Error:

	if ( pEquipmentHandle ) 
		*pEquipmentHandle = hEquipmentHandle;
		
	if ( bPopup )
		RemovePopup (0);
	
	if ( hPanelEquipment )
		DiscardPanel ( hPanelEquipment );
	
	if ( hPopupCalibrationGraphPanel )
		DiscardPanel ( hPopupCalibrationGraphPanel ); 
		
	if ( hPopupPanel )
		DiscardPanel ( hPopupPanel ); 
	
	db_equipment_freelist(&equipmentList);
	
	FREE(pFilePathName);
	
	FREE_LIST( vszSTD_Device_Commands_List , iNumberOfSTD_Device_Commands );  
	
	return StdError;
}

STD_ERROR		TE_EQUIP_Devices_Apply_PathConnection( int hMainHandle , int iTestIndex , int hEquipmentHandle , char *pPathString )
{

	STD_ERROR											StdError													=	{0};

	tsMainStore											*pMainStore													=	NULL;
																						 
	char												szDeviceName[LOW_STRING]									=	{0};  
														
	int													iEquipmentUseIndex											=	0; 
										
	unsigned long long									ullLinkedID													=	0;
										
	tfDRIVER_MANAGER_StandardDevice_SetListOfValues		DRIVER_MANAGER_StandardDevice_SetListOfValues				=	NULL;

	int													bEquipmentFound												=	0;
	
	int													*pPath_CheckFeedback										=	NULL,
														*pPath_CheckFeedbackRetries									=	NULL; 
														
	int													bCheckFeedback												=	0;
	
	int													iNumberOfValues												=	0,
														iCheckFeedbackRetries										=	0;
	
	if ( hEquipmentHandle == 0 )
	{
		RETURN;
	}
	
	if ( pPathString == NULL )
	{
		RETURN;
	}
	
	CHK_CMT( CmtGetTSVPtr ( hMainHandle , &pMainStore )); 

	DRIVER_MANAGER_StandardDevice_SetListOfValues = (tfDRIVER_MANAGER_StandardDevice_SetListOfValues) GetProcAddress( pMainStore->hDriverManagerLibrary , "DRV_StandardDevice_SetListOfValues" );  

	for ( iEquipmentUseIndex = 0; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
		if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle == hEquipmentHandle )  
		{
			bEquipmentFound = 1;
		
			ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;
			
			if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias )
				strcpy( szDeviceName , pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias );
		
			break;
		}

	CHK_CMT(CmtReleaseTSVPtr (hMainHandle));
	
	IF (( bEquipmentFound == 0 ) , "No Equipment found" );
	
	iNumberOfValues = VarGetInt( hMainHandle , VAR_LINK_EQUIPMENT_USE , ullLinkedID , "Path_CheckFeedback" , &pPath_CheckFeedback );
	
	if ( iNumberOfValues == 0 )
	{
		CALLOC( pPath_CheckFeedback , 1 , sizeof(int));
		
		if ( pPath_CheckFeedback )
		{
			*pPath_CheckFeedback = 0;
			VarSetInt( hMainHandle , VAR_LINK_EQUIPMENT_USE , ullLinkedID , "Path_CheckFeedback" , 1 , pPath_CheckFeedback );	
		}
	}
	
	if ( pPath_CheckFeedback )
	{
		bCheckFeedback = pPath_CheckFeedback[0];
	}
	
	iNumberOfValues = VarGetInt( hMainHandle , VAR_LINK_EQUIPMENT_USE , ullLinkedID , "Path_CheckFeedbackRetries" , &pPath_CheckFeedbackRetries );
	
	if ( iNumberOfValues == 0 )
	{
		CALLOC( pPath_CheckFeedbackRetries , 1 , sizeof(int));
		
		if ( pPath_CheckFeedbackRetries )
		{
			*pPath_CheckFeedbackRetries = 0;
			VarSetInt( hMainHandle , VAR_LINK_EQUIPMENT_USE , ullLinkedID , "Path_CheckFeedbackRetries" , 1 , pPath_CheckFeedbackRetries );	
		}
	}
	
	if ( pPath_CheckFeedbackRetries )
	{
		iCheckFeedbackRetries =  pPath_CheckFeedbackRetries[0];
	}
	
	CHK_STDERR( DRIVER_MANAGER_StandardDevice_SetListOfValues( hEquipmentHandle , pPathString , bCheckFeedback , iCheckFeedbackRetries ));
	

Error:
	
	FREE(pPath_CheckFeedback);
	FREE(pPath_CheckFeedbackRetries);
	
	return StdError;
}

STD_ERROR		TE_EQUIP_Devices_Apply_PathCommands( int hMainHandle , const char szPrefix[] , int iTestIndex , int hEquipmentHandle , int iPathIndex , int iSlotNumber )
{

	STD_ERROR										StdError													=	{0};

	tsMainStore										*pMainStore													=	NULL;
																						 
	char											szCommandVariableName[LOW_STRING]							=	{0},
													szMessage[LOW_STRING]										=	{0},
													szDeviceName[LOW_STRING]									=	{0};  
														
	char											**pStringArray												=	NULL;
	
	int												*pUnitUnderTestAutoConnectValuesList						=	NULL;
	double											*pUnitUnderTestAutoConnectDelayList							=	NULL;
	
	int												iEquipmentUseIndex											=	0, 
													iCommandIndex												=	0, 
													iCommandByteIndex											=	0, 
													iLoopIndex													=	0, 
													iIndex														=	0;
	
	unsigned long long								ullLinkedID													=	0;
										
	tfDRIVER_MANAGER_StandardDevice_SetValue		DRIVER_MANAGER_StandardDevice_SetValue						=	NULL;
	
	int												iCharacterCounter											=	0,
													iTotalCharacterCounter										=	0,
													iCommandLength												=	0, 
													iNumberOfCommands											=	0,
													iNumberOfValues												=	0, 
													iAllocationSize												=	0, 
													iNumberOfDelay												=	0;
	
	int												bEquipmentFound												=	0;
	
	char											**pCommandsList												=	NULL;
	int												*piCommandValuesList										=	NULL;
	double											*plfCommandDelaysList										=	NULL;
													
	int												bNeedToApplyPathCommand										=	0,
													bLastPathCommandHasApplied									=	0;

	double											lfDelay														=	0.0,
													lfProgressDelay												=	0.0, 
													lfTotalDelay												=	0.0, 
													lfCurrentTime												=	0.0,
													lfStartTime													=	0.0;
	
	int												hPopupPanel													=	0,
													hPanelHandle												=	0;  
	
	int												iControlID													=	0;
	
	if ( hEquipmentHandle == 0 )
	{
		RETURN;
	}
	
	CHK_CMT( CmtGetTSVPtr ( hMainHandle , &pMainStore )); 

	DRIVER_MANAGER_StandardDevice_SetValue = (tfDRIVER_MANAGER_StandardDevice_SetValue) GetProcAddress( pMainStore->hDriverManagerLibrary , "DRV_StandardDevice_SetValue" );  

	for ( iEquipmentUseIndex = 0; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
		if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle == hEquipmentHandle )  
		{
			bEquipmentFound = 1;
		
			ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;
			
			if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias )
				strcpy( szDeviceName , pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias );
		
			break;
		}

	CHK_CMT(CmtReleaseTSVPtr (hMainHandle));
	  
	IF (( bEquipmentFound == 0 ) , "No Equipment found" );
	
	do
	{
		FREE_LIST(pStringArray,iLoopIndex);  
		
		if ( iCommandIndex >= iAllocationSize )
		{
			iAllocationSize = ( iAllocationSize * 2 ) + 32;
			
			pCommandsList = realloc( pCommandsList , (iAllocationSize * sizeof(char*)) );
			piCommandValuesList = realloc( piCommandValuesList , (iAllocationSize * sizeof(int)) );
			plfCommandDelaysList = realloc( plfCommandDelaysList , (iAllocationSize * sizeof(double)) ); 
		
			for ( iIndex = iCommandIndex; iIndex < iAllocationSize; iIndex++ )
			{
				pCommandsList[iIndex] = NULL;
				piCommandValuesList[iIndex] = 0;
				plfCommandDelaysList[iIndex] = 0.0;    
			}
		}
		
		iLoopIndex = 0;
		iCharacterCounter = 0;
		iTotalCharacterCounter = 0;
		
		if ( iSlotNumber > 0 )
		{
			if ( iCommandIndex )
				sprintf( szCommandVariableName , "%s_Slot_%d_Commands%d" , szPrefix , iSlotNumber , (iCommandIndex));
			else
				sprintf( szCommandVariableName , "%s_Slot_%d_Commands" , szPrefix , iSlotNumber );
		}
		else
		{
			if ( iCommandIndex )
				sprintf( szCommandVariableName , "%s_Commands%d" , szPrefix , (iCommandIndex));
			else
				sprintf( szCommandVariableName , "%s_Commands" , szPrefix );
		}
		
		iLoopIndex = VarGetStringArray( hMainHandle , VAR_LINK_EQUIPMENT_USE , ullLinkedID , szCommandVariableName , &pStringArray ); 
	
		if ( iCommandIndex && ( iLoopIndex == 0 ))
			break;
	
		if ( pStringArray == NULL )     
			VarSetString( hMainHandle , VAR_LINK_EQUIPMENT_USE , ullLinkedID , szCommandVariableName , "" ); 	

		//-------------- Values List -----------------------------//
		
		if ( iSlotNumber > 0 )
		{
			if ( iCommandIndex )
				sprintf( szCommandVariableName , "%s_Slot_%d_Values%d" , szPrefix , iSlotNumber , (iCommandIndex));
			else
				sprintf( szCommandVariableName , "%s_Slot_%d_Values" , szPrefix , iSlotNumber );
		}
		else
		{
			if ( iCommandIndex )
				sprintf( szCommandVariableName , "%s_Values%d" , szPrefix , (iCommandIndex));
			else
				sprintf( szCommandVariableName , "%s_Values" , szPrefix);
		}
		
		iNumberOfValues = VarGetInt( hMainHandle , VAR_LINK_EQUIPMENT_USE , ullLinkedID , szCommandVariableName , &pUnitUnderTestAutoConnectValuesList );

		if ( pUnitUnderTestAutoConnectValuesList == NULL )     
		{
			CALLOC_ERR( pUnitUnderTestAutoConnectValuesList , 1 , sizeof(int));

			VarSetInt( hMainHandle , VAR_LINK_EQUIPMENT_USE , ullLinkedID , szCommandVariableName , 1 , pUnitUnderTestAutoConnectValuesList ); 	
		}
		
		//-------------- Delays List -----------------------------//
		if ( iSlotNumber > 0 )
		{
			if ( iCommandIndex )
				sprintf( szCommandVariableName , "%s_Slot_%d_Delay%d" , szPrefix , iSlotNumber , (iCommandIndex));
			else
				sprintf( szCommandVariableName , "%s_Slot_%d_Delay" , szPrefix , iSlotNumber );
		}
		else
		{
			if ( iCommandIndex )
				sprintf( szCommandVariableName , "%s_Delay%d" , szPrefix , (iCommandIndex));
			else
				sprintf( szCommandVariableName , "%s_Delay" , szPrefix);
		}
		
		iNumberOfDelay = VarGetDouble( hMainHandle , VAR_LINK_EQUIPMENT_USE , ullLinkedID , szCommandVariableName , &pUnitUnderTestAutoConnectDelayList );

		if ( pUnitUnderTestAutoConnectDelayList == NULL )     
		{
			CALLOC_ERR( pUnitUnderTestAutoConnectDelayList , 1 , sizeof(double));

			VarSetDouble( hMainHandle , VAR_LINK_EQUIPMENT_USE , ullLinkedID , szCommandVariableName , 1 , pUnitUnderTestAutoConnectDelayList ); 	
		}
		
		if ( pStringArray && pStringArray[0] ) 
		{
			if (( pStringArray[iPathIndex] && strlen(pStringArray[iPathIndex]) && ( pStringArray[iPathIndex][0] != '.' ) && ( iPathIndex < iLoopIndex ) && ( iNumberOfValues > iPathIndex ))) 
			{
				CALLOC_COPY_STRING( pCommandsList[iCommandIndex] , pStringArray[iPathIndex] );
				piCommandValuesList[iCommandIndex] = pUnitUnderTestAutoConnectValuesList[iPathIndex];
				plfCommandDelaysList[iCommandIndex] = pUnitUnderTestAutoConnectDelayList[iPathIndex]; 
			}
			else
			{
				if ( pStringArray[0][0] != '.' )
				{
					CALLOC_COPY_STRING( pCommandsList[iCommandIndex] , pStringArray[0] );
					piCommandValuesList[iCommandIndex] = pUnitUnderTestAutoConnectValuesList[0];
					plfCommandDelaysList[iCommandIndex] = pUnitUnderTestAutoConnectDelayList[0]; 
				}
			}
		}
		
		iCommandIndex++;
	
		FREE_LIST(pStringArray,iLoopIndex);
		FREE(pUnitUnderTestAutoConnectValuesList);
		FREE(pUnitUnderTestAutoConnectDelayList);    
		
	} while( 1 );
	
	iNumberOfCommands = iCommandIndex;
	
	if ( CmtGetTSVPtr ( hMainHandle , &pMainStore ) == 0 )
	{
		if (( pMainStore->iLastPathNumberOfCommands == iNumberOfCommands ) && pMainStore->pLastPathCommandsList && pMainStore->piLastPathCommandValuesList )
		{
			for ( iCommandIndex = 0; iCommandIndex < iNumberOfCommands; iCommandIndex++ )
			{
				if ( pCommandsList[iCommandIndex] && pMainStore->pLastPathCommandsList[iCommandIndex] )
				{
					iCommandLength = strlen(pCommandsList[iCommandIndex]);
					
					if ( iCommandLength != strlen(pMainStore->pLastPathCommandsList[iCommandIndex]))
					{
						bNeedToApplyPathCommand = 1;
						break;
					}
					else
					{
						for( iCommandByteIndex = 0; iCommandByteIndex < iCommandLength; iCommandByteIndex++ )
							if ( pCommandsList[iCommandIndex][iCommandByteIndex] != pMainStore->pLastPathCommandsList[iCommandIndex][iCommandByteIndex] )
							{
								bNeedToApplyPathCommand = 1;
								break;
							}
						
						if ( bNeedToApplyPathCommand )
							break;
					}
				}
				else
				{
					if ( pCommandsList[iCommandIndex] != pMainStore->pLastPathCommandsList[iCommandIndex] ) 
					{
						bNeedToApplyPathCommand = 1;
						break;
					}
				}
		
				if ( piCommandValuesList[iCommandIndex] && pMainStore->piLastPathCommandValuesList[iCommandIndex] )
				{
					if ( piCommandValuesList[iCommandIndex] != pMainStore->piLastPathCommandValuesList[iCommandIndex] )
					{
						bNeedToApplyPathCommand = 1;
						break;
					}
				}
				else
				{
					if ( piCommandValuesList[iCommandIndex] != pMainStore->piLastPathCommandValuesList[iCommandIndex] ) 
					{
						bNeedToApplyPathCommand = 1;
						break;
					}
				}
			}
		}
		else
		{
			bNeedToApplyPathCommand = 1;	
		}
		
		bNeedToApplyPathCommand += pMainStore->config.bSkipDeviceCommandRepeatCheck;
		
		CmtReleaseTSVPtr (hMainHandle);
	}	
	
	if ( bNeedToApplyPathCommand )
	{
		for ( iCommandIndex = 0; iCommandIndex < iNumberOfCommands; iCommandIndex++ )
			if ( plfCommandDelaysList[iCommandIndex] < 86400.0 )  
				lfTotalDelay += plfCommandDelaysList[iCommandIndex];  
			
		if ( lfTotalDelay > 1.0 )
		{
			hPopupPanel = LoadPanel (0, "TEST_EXEC_UI.uir", WAIT ); 
		
			SetPanelAttribute( hPopupPanel , ATTR_WIDTH , 500 );
			
			sprintf( szMessage , "Setting Commands ( %s )" , szDeviceName );
			
			SetCtrlVal( hPopupPanel , WAIT_TEXTMSG , szMessage ); 
			
			SetCtrlAttribute( hPopupPanel , WAIT_TEXTMSG , ATTR_WIDTH , 450 );
			
			SetCtrlAttribute( hPopupPanel , WAIT_PROGRESS , ATTR_WIDTH , 450 );
			
			SetCtrlAttribute( hPopupPanel , WAIT_PROGRESS , ATTR_MAX_VALUE , (int)(lfTotalDelay * 10.0) ); 
			
			SetCtrlAttribute( hPopupPanel , WAIT_PROGRESS , ATTR_VISIBLE , 1 );
	
			SetCtrlAttribute( hPopupPanel , WAIT_CLOSE , ATTR_VISIBLE , 1 );
			
			SetCtrlVal( hPopupPanel , WAIT_PROGRESS , 0 ); 
			
			InstallPopup ( hPopupPanel );
			
			lfTotalDelay = 0.0;  
		}
		
		for ( iCommandIndex = 0; iCommandIndex < iNumberOfCommands; iCommandIndex++ )
		{
			if ( pCommandsList && pCommandsList[iCommandIndex] ) 
			{
				CHK_STDERR( DRIVER_MANAGER_StandardDevice_SetValue( hEquipmentHandle , pCommandsList[iCommandIndex] , &(piCommandValuesList[iCommandIndex]) , 1 , sizeof(int)));
				bLastPathCommandHasApplied = 1;
			}

			if ( plfCommandDelaysList[iCommandIndex] < 3600.0 )
				lfDelay = plfCommandDelaysList[iCommandIndex];
			else
				DelayWithEventProcessing(0.1);
			
			GetCurrentDateTime(&lfStartTime);  
	
			do
			{   
				DelayWithEventProcessing(lfDelay*0.1);
		
				GetCurrentDateTime(&lfCurrentTime);  
				
				if ( hPopupPanel )
					SetCtrlVal( hPopupPanel , WAIT_PROGRESS , (int)((lfProgressDelay+(lfCurrentTime-lfStartTime)) * 10.0) );   
				
				GetUserEvent (0, &hPanelHandle , &iControlID );
				
				if (( hPanelHandle == hPopupPanel ) && ( iControlID == WAIT_CLOSE ))
					break;
				
			}while((lfCurrentTime-lfStartTime)<lfDelay );
			
			lfProgressDelay += lfDelay;  
		}
	}
	
Error:

	if ( hPopupPanel )
		DiscardPanel ( hPopupPanel ); 
	
	FREE(plfCommandDelaysList);	
	
	if ( CmtGetTSVPtr ( hMainHandle , &pMainStore ) == 0 )
	{
		FREE_LIST( pMainStore->pLastPathCommandsList , pMainStore->iLastPathNumberOfCommands );
		FREE(pMainStore->piLastPathCommandValuesList);  
		
		pMainStore->pLastPathCommandsList = pCommandsList;
		pMainStore->piLastPathCommandValuesList = piCommandValuesList;
		pMainStore->iLastPathNumberOfCommands = iNumberOfCommands;
		pMainStore->bLastPathCommandHasApplied = bLastPathCommandHasApplied;
		CmtReleaseTSVPtr (hMainHandle);
	}
	
	FREE_LIST(pStringArray,iLoopIndex);
	FREE(pUnitUnderTestAutoConnectValuesList);
	FREE(pUnitUnderTestAutoConnectDelayList);
	
	return StdError;
}


STD_ERROR		TE_EQUIP_Devices_Apply_FrequencyCommands( int hMainHandle , const char szPrefix[] , int iTestIndex , int hEquipmentHandle , int iCurrentFrequencyIndex , double lfCurrentFrequency , int iSlotNumber )
{

	STD_ERROR										StdError													=	{0};

	tsMainStore										*pMainStore													=	NULL;
	
	char											szCommandVariableName[LOW_STRING]							=	{0};  
														
	char											**pStringArray												=	NULL;
	
	int												*pUnitUnderTestAutoConnectValuesList						=	NULL, 
													*pUnitUnderTestAutoFrequencyCommand							=	NULL;  

	double											*pUnitUnderTestAutoConnectDelayList							=	NULL;
																   
	int												iEquipmentUseIndex											=	0,
													iCommandIndex												=	0, 
													iLoopIndex													=	0, 
													iIndex														=	0;
										
	unsigned long long								ullLinkedID													=	0;
										
	tfDRIVER_MANAGER_StandardDevice_SetValue		DRIVER_MANAGER_StandardDevice_SetValue						=	NULL;
	
	int												iCharacterCounter											=	0,
													iTotalCharacterCounter										=	0,
													iNumberOfCommands											=	0,  
													iAllocationSize												=	0, 
													iNumberOfValues												=	0,
													iNumberOfDelay												=	0;  
													
	int												bEquipmentFound												=	0;
	
	char											**pCommandsList												=	NULL;
	int												*piCommandValuesList										=	NULL;
	double											*plfCommandDelaysList										=	NULL;
													
	int												bNeedToApplyPathCommand										=	0,
													bLastPathCommandHasApplied									=	0;
	
	double											lfDelay														=	0;
	
	if ( hEquipmentHandle == 0 )
	{
		RETURN;
	}
	
	CHK_CMT( CmtGetTSVPtr ( hMainHandle , &pMainStore )); 

	DRIVER_MANAGER_StandardDevice_SetValue = (tfDRIVER_MANAGER_StandardDevice_SetValue) GetProcAddress( pMainStore->hDriverManagerLibrary , "DRV_StandardDevice_SetValue" );  
	
	for ( iEquipmentUseIndex = 0; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
		if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle == hEquipmentHandle )  
		{
			bEquipmentFound = 1;
	
			ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;
	
			break;
		}
			
	CHK_CMT(CmtReleaseTSVPtr (hMainHandle));
	
	IF (( bEquipmentFound == 0 ) , "No Equipment found" );
	
	do
	{
		FREE_LIST_ONLY(pStringArray,iLoopIndex);  
		
		if ( iCommandIndex >= iAllocationSize )
		{
			iAllocationSize = ( iAllocationSize * 2 ) + 32;
			
			pCommandsList = realloc( pCommandsList , (iAllocationSize * sizeof(char*)) );
			piCommandValuesList = realloc( piCommandValuesList , (iAllocationSize * sizeof(int)) );
			plfCommandDelaysList = realloc( plfCommandDelaysList , (iAllocationSize * sizeof(double)) ); 
		
			for ( iIndex = iCommandIndex; iIndex < iAllocationSize; iIndex++ )
			{
				pCommandsList[iIndex] = NULL;
				piCommandValuesList[iIndex] = 0;
				plfCommandDelaysList[iIndex] = 0.0;    
			}
		}

		iLoopIndex = 0;
		iCharacterCounter = 0;
		iTotalCharacterCounter = 0;
		
		
		if ( iCommandIndex )
			sprintf( szCommandVariableName , "%s_Commands%d" , szPrefix , (iCommandIndex));
		else
			sprintf( szCommandVariableName , "%s_Commands" , szPrefix );

		iLoopIndex = VarGetStringArray( hMainHandle , VAR_LINK_EQUIPMENT_USE , ullLinkedID , szCommandVariableName , &pStringArray ); 

		if ( iCommandIndex && ( iLoopIndex == 0 ))
			break;

		if ( pStringArray == NULL )     
			VarSetString( hMainHandle , VAR_LINK_EQUIPMENT_USE , ullLinkedID , szCommandVariableName , "" ); 	

		if ( iCommandIndex )
			sprintf( szCommandVariableName , "%s_Values%d" , szPrefix , (iCommandIndex));
		else
			sprintf( szCommandVariableName , "%s_Values" , szPrefix );

		iNumberOfValues = VarGetInt( hMainHandle , VAR_LINK_EQUIPMENT_USE , ullLinkedID , szCommandVariableName , &pUnitUnderTestAutoConnectValuesList );

		if ( pUnitUnderTestAutoConnectValuesList == NULL )     
		{
			CALLOC_ERR( pUnitUnderTestAutoConnectValuesList , 1 , sizeof(int));

			VarSetInt( hMainHandle , VAR_LINK_EQUIPMENT_USE , ullLinkedID , szCommandVariableName , 1 , pUnitUnderTestAutoConnectValuesList ); 	
		}

		//-------------- Delays List -----------------------------//
		if ( iSlotNumber > 0 )
		{
			if ( iCommandIndex )
				sprintf( szCommandVariableName , "%s_Slot_%d_Delay%d" , szPrefix , iSlotNumber , (iCommandIndex));
			else
				sprintf( szCommandVariableName , "%s_Slot_%d_Delay" , szPrefix , iSlotNumber );
		}
		else
		{
			if ( iCommandIndex )
				sprintf( szCommandVariableName , "%s_Delay%d" , szPrefix , (iCommandIndex));
			else
				sprintf( szCommandVariableName , "%s_Delay" , szPrefix);
		}
		
		iNumberOfDelay = VarGetDouble( hMainHandle , VAR_LINK_EQUIPMENT_USE , ullLinkedID , szCommandVariableName , &pUnitUnderTestAutoConnectDelayList );

		if ( pUnitUnderTestAutoConnectDelayList == NULL )     
		{
			CALLOC_ERR( pUnitUnderTestAutoConnectDelayList , 1 , sizeof(double));

			VarSetDouble( hMainHandle , VAR_LINK_EQUIPMENT_USE , ullLinkedID , szCommandVariableName , 1 , pUnitUnderTestAutoConnectDelayList ); 	
		}
		
		if ( pStringArray && pStringArray[0] ) 
		{
			if (( pStringArray[iCurrentFrequencyIndex] && strlen(pStringArray[iCurrentFrequencyIndex]) && ( pStringArray[iCurrentFrequencyIndex][0] != '.' ) && ( iCurrentFrequencyIndex < iLoopIndex ) && ( iNumberOfValues > iCurrentFrequencyIndex ))) 
			{
				FREE_CALLOC( pUnitUnderTestAutoFrequencyCommand , (strlen(pStringArray[iCurrentFrequencyIndex])+32) , sizeof(char));
				
				if ( pUnitUnderTestAutoFrequencyCommand )
				{
					if ( strchr( pStringArray[iCurrentFrequencyIndex] , '%' ))
					{
						sprintf( pUnitUnderTestAutoFrequencyCommand , pStringArray[iCurrentFrequencyIndex] , lfCurrentFrequency );
					}
					else
					{
						strcpy( pUnitUnderTestAutoFrequencyCommand , pStringArray[iCurrentFrequencyIndex] );
					}
			
					CALLOC_COPY_STRING( pCommandsList[iCommandIndex] , pStringArray[iCurrentFrequencyIndex] );
					piCommandValuesList[iCommandIndex] = pUnitUnderTestAutoConnectValuesList[iCurrentFrequencyIndex];
					plfCommandDelaysList[iCommandIndex] = pUnitUnderTestAutoConnectDelayList[iCurrentFrequencyIndex]; 
				}
			}
			else
			{
				FREE_CALLOC( pUnitUnderTestAutoFrequencyCommand , (strlen(pStringArray[0])+32) , sizeof(char));
				
				if ( pUnitUnderTestAutoFrequencyCommand )
				{
					if ( strchr( pStringArray[0] , '%' ))
					{
						sprintf( pUnitUnderTestAutoFrequencyCommand , pStringArray[0] , lfCurrentFrequency );
					}
					else
					{
						strcpy( pUnitUnderTestAutoFrequencyCommand , pStringArray[0] );
					}
			
					CALLOC_COPY_STRING( pCommandsList[iCommandIndex] , pStringArray[0] );
					piCommandValuesList[iCommandIndex] = pUnitUnderTestAutoConnectValuesList[0];
					plfCommandDelaysList[iCommandIndex] = pUnitUnderTestAutoConnectDelayList[0]; 
				}
			}
		}
	
		FREE_LIST_ONLY(pStringArray,iLoopIndex);
		FREE(pUnitUnderTestAutoConnectValuesList);
		FREE(pUnitUnderTestAutoConnectDelayList);
	
		iCommandIndex++;

	} while( 1 );
				
	iNumberOfCommands = iCommandIndex;
	
	if ( CmtGetTSVPtr ( hMainHandle , &pMainStore ) == 0 )
	{
		if (( pMainStore->iLastPathNumberOfCommands == iNumberOfCommands ) && pMainStore->pLastPathCommandsList && pMainStore->piLastPathCommandValuesList )
		{
			for ( iCommandIndex = 0; iCommandIndex < iNumberOfCommands; iCommandIndex++ )
			{
				if ( pCommandsList[iCommandIndex] && pMainStore->pLastPathCommandsList[iCommandIndex] )
				{
					if ( strstr ( pCommandsList[iCommandIndex] , pMainStore->pLastPathCommandsList[iCommandIndex] ))
					{
						bNeedToApplyPathCommand = 1;
						break;
					}
				}
				else
				{
					if ( pCommandsList[iCommandIndex] != pMainStore->pLastPathCommandsList[iCommandIndex] ) 
					{
						bNeedToApplyPathCommand = 1;
						break;
					}
				}
		
				if ( piCommandValuesList[iCommandIndex] && pMainStore->piLastPathCommandValuesList[iCommandIndex] )
				{
					if ( piCommandValuesList[iCommandIndex] != pMainStore->piLastPathCommandValuesList[iCommandIndex] )
					{
						bNeedToApplyPathCommand = 1;
						break;
					}
				}
				else
				{
					if ( piCommandValuesList[iCommandIndex] != pMainStore->piLastPathCommandValuesList[iCommandIndex] ) 
					{
						bNeedToApplyPathCommand = 1;
						break;
					}
				}
			}
		}
		else
		{
			bNeedToApplyPathCommand = 1;	
		}
		
		bNeedToApplyPathCommand += pMainStore->config.bSkipDeviceCommandRepeatCheck;
		
		CmtReleaseTSVPtr (hMainHandle);
	}	
	
	if ( bNeedToApplyPathCommand )
	{
		for ( iCommandIndex = 0; iCommandIndex < iNumberOfCommands; iCommandIndex++ )
		{
			if ( pCommandsList && pCommandsList[iCommandIndex] ) 
			{
				CHK_STDERR( DRIVER_MANAGER_StandardDevice_SetValue( hEquipmentHandle , pCommandsList[iCommandIndex] , &(piCommandValuesList[iCommandIndex]) , 1 , sizeof(int)));
				bLastPathCommandHasApplied = 1;
			}
		}
		
		if ( plfCommandDelaysList )
			lfDelay = plfCommandDelaysList[iCommandIndex];    
			
		DelayWithEventProcessing(lfDelay);	
	}
	
Error:

	FREE(plfCommandDelaysList);
	
	FREE_LIST( pCommandsList , iNumberOfCommands );
	FREE(piCommandValuesList);  
		
	FREE_LIST_ONLY(pStringArray,iLoopIndex);
	FREE(pUnitUnderTestAutoConnectValuesList);
	FREE(pUnitUnderTestAutoFrequencyCommand);
	FREE(pUnitUnderTestAutoConnectDelayList);
	
	return StdError;
}


STD_ERROR		TE_EQUIP_Get_Equipment_Information( int hMainHandle , char *pAddress , unsigned long long ulEquipmentID , int *pbConnectionStatus , char **pVendor , char **pSerialNumber , char **pModel , char **pFirmware )
{
	STD_ERROR															StdError															=	{0};

	tsMainStore															*pMainStore															=	NULL,
																		tMainStore															=	{0}; 
	
	tfDRIVER_MANAGER_GetEquipmentInformation							fDRIVER_MANAGER_GetEquipmentInformation								=	NULL;

	tfDRIVER_MANAGER_Close												fDRIVER_MANAGER_Close												=	NULL;
	
	int																	EquipmentHandle														=	0;
	
	int																	bConnectionStatus													=	0;
	
	CHK_CMT( CmtGetTSVPtr ( hMainHandle , &pMainStore )); 
	memcpy( &tMainStore , pMainStore , sizeof(tsMainStore));  
	CHK_CMT(CmtReleaseTSVPtr (hMainHandle));
	
	IF (( tMainStore.hDriverManagerLibrary == NULL ) , "Driver Manager is not found." );
	
	fDRIVER_MANAGER_GetEquipmentInformation = (tfDRIVER_MANAGER_GetEquipmentInformation) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_GetEquipmentInformation" );
	
	fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_Close" ); 
	
	CHK_STDERR( TE_EQUIP_ConnectToEquipment( hMainHandle , ulEquipmentID , &EquipmentHandle , 0 ));

	if ( EquipmentHandle > 0 )
		bConnectionStatus = 1;
	
	if ( fDRIVER_MANAGER_GetEquipmentInformation )
	{
		CHK_STDERR( fDRIVER_MANAGER_GetEquipmentInformation( EquipmentHandle , pVendor , pSerialNumber , pModel , pFirmware ));  
	}
	
Error:

	if ( EquipmentHandle && fDRIVER_MANAGER_Close )
		fDRIVER_MANAGER_Close( EquipmentHandle );
	
	if ( pbConnectionStatus )
		*pbConnectionStatus = bConnectionStatus;
	
	return StdError;
}

STD_ERROR		TE_EQUIP_Get_Drivers_FileList ( int hMainHandle , char ***pDriversList , int **pDriversTypes , int *pCount )
{
	STD_ERROR															StdError															=	{0};

	tsMainStore															*pMainStore															=	NULL,
																		tMainStore															=	{0}; 
	
	tfDRIVER_MANAGER_GetDriversFileList									fDRIVER_MANAGER_GetDriversFileList									=	NULL;

	CHK_CMT( CmtGetTSVPtr ( hMainHandle , &pMainStore )); 
	memcpy( &tMainStore , pMainStore , sizeof(tsMainStore));  
	CHK_CMT(CmtReleaseTSVPtr (hMainHandle));
	
	IF (( tMainStore.hDriverManagerLibrary == NULL ) , "Driver Manager is not found." );
	
	fDRIVER_MANAGER_GetDriversFileList = (tfDRIVER_MANAGER_GetDriversFileList) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_GetDriversFileList" );
	
	if ( fDRIVER_MANAGER_GetDriversFileList )
	{
		fDRIVER_MANAGER_GetDriversFileList( NULL , pDriversList , pDriversTypes , pCount );
	}

Error:

	return StdError;
}


STD_ERROR		TE_EQUIP_Check_Driver( int hMainHandle , char *pDriverFile , char *pEquipmentAddress , int *pCompatibility , char **pVendor , char **pSerialNumber , char **pModel , char **pFirmware , char **pIDN , char **pID_Responds )  
{
	STD_ERROR															StdError															=	{0};

	tsMainStore															*pMainStore															=	NULL,
																		tMainStore															=	{0}; 
	
	tfDRIVER_MANAGER_CheckEquipmentDriverCompatibility					fDRIVER_MANAGER_CheckEquipmentDriverCompatibility					=	NULL;

	CHK_CMT( CmtGetTSVPtr ( hMainHandle , &pMainStore )); 
	memcpy( &tMainStore , pMainStore , sizeof(tsMainStore));  
	CHK_CMT(CmtReleaseTSVPtr (hMainHandle));
	
	IF (( tMainStore.hDriverManagerLibrary == NULL ) , "Driver Manager is not found." );
	
	fDRIVER_MANAGER_CheckEquipmentDriverCompatibility = (tfDRIVER_MANAGER_CheckEquipmentDriverCompatibility) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_CheckEquipmentDriverCompatibility" );
	
	if ( fDRIVER_MANAGER_CheckEquipmentDriverCompatibility )
	{
		CHK_STDERR( fDRIVER_MANAGER_CheckEquipmentDriverCompatibility( pDriverFile , pEquipmentAddress , pCompatibility , pVendor , pSerialNumber , pModel , pFirmware , pIDN , pID_Responds ));
	}

Error:

	return StdError;
}

STD_ERROR		TE_EQUIP_BrowseStateFiles( int hMainHandle , unsigned long long ulEquipmentID )
{	
	STD_ERROR															StdError															=	{0};
	
	tlEquipment															*equipmentList														=	NULL;
	
	tsMainStore															*pMainStore															=	NULL,
																		tMainStore															=	{0}; 
	
	int																	iIndex																=	0,
																		iEquipmentIndex														=	0,
																		iCheckDeviceIndex													=	0;
										
	int																	hPanelEquipment														=	0;
	
	tfDRIVER_MANAGER_GetErrorTextMessage								fDRIVER_MANAGER_GetErrorTextMessage									=	NULL;
	tfDRIVER_MANAGER_STD_Init											fDRIVER_MANAGER_STD_Init											=	NULL;  
	tfDRIVER_MANAGER_Init												fDRIVER_MANAGER_Init												=	NULL;
	tfDRIVER_MANAGER_Reset												fDRIVER_MANAGER_Reset												=	NULL;
	tfDRIVER_MANAGER_Close												fDRIVER_MANAGER_Close												=	NULL;
	
	tfDRIVER_MANAGER_STD_LoadConfigFile									fDRIVER_MANAGER_STD_LoadConfigFile									=	NULL;
	tfDRIVER_MANAGER_STD_Get_Commands_List								fDRIVER_MANAGER_STD_Get_Commands_List								=	NULL;
	tfDRIVER_MANAGER_STD_Check_Connection								fDRIVER_MANAGER_STD_Check_Connection								=	NULL;

	tfDRIVER_MANAGER_SETUP_UpdateCallbacksStructure						fDRIVER_MANAGER_SETUP_UpdateCallbacksStructure						=	NULL;

	tfDRIVER_MANAGER_Get_SimulationMode									fDRIVER_MANAGER_Get_SimulationMode									=	NULL;
	
	tfDRIVER_MANAGER_Equipment_BrowseSelectStateFiles					fDRIVER_MANAGER_Equipment_BrowseSelectStateFiles					=	NULL;

	tfDRIVER_MANAGER_UpdateIgnoreDuplicationAddresses					fDRIVER_MANAGER_UpdateIgnoreDuplicationAddresses						=	NULL;
	
	char																*pFilePathName														=	NULL,
																		*pSubDriverFilePathName												=	NULL; 
																
	int 																bPopup																=	0,
																		event																=	0,
																		panel																=	0,
																		control																=	0;

	char																szMessage[LOW_STRING]												=	{0};
	
	unsigned long long													ulCommandID															=	0;
	
	char																**vszSTD_Device_Commands_List										=	NULL;
	int																	iNumberOfSTD_Device_Commands										=	0,
																		bCheckDeviceStatus													=	0;
																	 
	int																	hPopupPanel															=	0,
																		hPopupCalibrationGraphPanel											=	0;  

	char																*pStringToStore														=	0;

	int																	iStringLength														=	0,
																		iBufferLength														=	0;

	void																*pCallBackStructure													=	NULL;

	int																	iSimulationMode														=	0;
	
	int																	bTestStaus															=	0;
	
	CHK_CMT( CmtGetTSVPtr ( hMainHandle , &pMainStore )); 
	memcpy( &tMainStore , pMainStore , sizeof(tsMainStore));  
	CHK_CMT(CmtReleaseTSVPtr (hMainHandle));
	
	IF (( tMainStore.hDriverManagerLibrary == NULL ) , "Driver Manager is not found." );
		
	db_equipment_getlist_by_type_station( tMainStore.hDatabaseHandle , tMainStore.hCurrentStationId , -1 ,&equipmentList);

	if (( equipmentList == NULL ) || ( equipmentList->equipment == NULL )) 
	{
		RETURN;
	}
	
	for ( iEquipmentIndex = 0 ; iEquipmentIndex < equipmentList->count ; iEquipmentIndex++ ) 
		if ( equipmentList->equipment[iEquipmentIndex].id == ulEquipmentID )
			break;
		
	IF (( equipmentList->equipment[iEquipmentIndex].id != ulEquipmentID ) , "Wrong Equipment ID" );
	
	fDRIVER_MANAGER_SETUP_UpdateCallbacksStructure = (tfDRIVER_MANAGER_SETUP_UpdateCallbacksStructure) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_SETUP_UpdateCallbacksStructure" );

	// fill driver manager call back data  
	FillCallbacksDataStructureOnly( hMainHandle , &pCallBackStructure , ulEquipmentID ); 

	fDRIVER_MANAGER_SETUP_UpdateCallbacksStructure( pCallBackStructure , 2 , equipmentList->equipment[iEquipmentIndex].address , ulEquipmentID );

	FREE(pCallBackStructure);  
	
	CHK_UIL (hPanelEquipment = LoadPanel (0, "TEST_EXEC_UI.uir", EQUIP_INIT ));

	InstallPopup (hPanelEquipment);
	bPopup = 1;
	
	InsertTableRows ( hPanelEquipment , EQUIP_INIT_TABLE , (1) , 1 , VAL_CELL_STRING );
	SetTableRowAttribute (hPanelEquipment, EQUIP_INIT_TABLE, (1), ATTR_LABEL_BOLD, 1);
	SetTableRowAttribute (hPanelEquipment, EQUIP_INIT_TABLE, (1), ATTR_LABEL_COLOR, VAL_WHITE);
	SetTableRowAttribute (hPanelEquipment, EQUIP_INIT_TABLE, (1), ATTR_LABEL_POINT_SIZE, 15);
	
	SetTableCellAttribute ( hPanelEquipment, EQUIP_INIT_TABLE ,MakePoint (1,(1)), ATTR_TEXT_BOLD, 1); 
	SetTableCellAttribute ( hPanelEquipment, EQUIP_INIT_TABLE ,MakePoint (2,(1)), ATTR_TEXT_BOLD, 1);
	SetTableCellAttribute ( hPanelEquipment, EQUIP_INIT_TABLE ,MakePoint (3,(1)), ATTR_TEXT_BOLD, 1);
	
	SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (1,(1)), ATTR_CELL_JUSTIFY, VAL_CENTER_CENTER_JUSTIFIED);
	SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (2,(1)), ATTR_CELL_JUSTIFY, VAL_CENTER_CENTER_JUSTIFIED);
	SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (3,(1)), ATTR_CELL_JUSTIFY, VAL_CENTER_CENTER_JUSTIFIED); 
	
	SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (1,(1)), ATTR_TEXT_COLOR, MAIN_COLOR );
	SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (2,(1)), ATTR_TEXT_COLOR, MAIN_COLOR );
	
	SetTableCellVal ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(1,(1)), equipmentList->equipment[iEquipmentIndex].alias );
	SetTableCellVal ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(2,(1)), equipmentList->equipment[iEquipmentIndex].name ); 
	
	//----------------------------------- Initialization -----------------------------------------//
	
	UPDATERR( GetDataBaseFileByID( tMainStore.hDatabaseHandle , equipmentList->equipment[iEquipmentIndex].driverlink , NULL , NULL , NULL  , NULL , &pFilePathName ));

	fDRIVER_MANAGER_Get_SimulationMode = (tfDRIVER_MANAGER_Get_SimulationMode) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_Get_SimulationMode" );
	
	fDRIVER_MANAGER_Equipment_BrowseSelectStateFiles = ( tfDRIVER_MANAGER_Equipment_BrowseSelectStateFiles ) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRIVER_MANAGER_Equipment_BrowseSelectStateFiles" );
	
	if ( IS_NOT_OK )
	{
		sprintf( szMessage , "File Driver is not found for equipment %s" , equipmentList->equipment[iEquipmentIndex].name );
		ShowMessage ( tMainStore.hDatabaseHandle , INSTR_TYPE_CONTINUE , "Driver Error.",szMessage , NULL );
	}
	else
	{
		if ( equipmentList->equipment[iEquipmentIndex].driverchildlink )
		{
			UPDATERR( GetDataBaseFileByID( tMainStore.hDatabaseHandle , equipmentList->equipment[iEquipmentIndex].driverchildlink , NULL , NULL , NULL  , NULL , &pSubDriverFilePathName )); 	
			
			if ( IS_OK && pSubDriverFilePathName )
			{
				if ( FileExists( pSubDriverFilePathName , NULL ))	
				{
					LoadLibrary ( pSubDriverFilePathName ); 	
				}
			}
			
			FREE(pSubDriverFilePathName);
		}
			
		switch(equipmentList->equipment[iEquipmentIndex].type)
		{
			case EQUIPMENT_TYPE_STANDARD_DEVICE:	
		
				fDRIVER_MANAGER_STD_Init = (tfDRIVER_MANAGER_STD_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_Close" ); 
				
				fDRIVER_MANAGER_STD_LoadConfigFile = (tfDRIVER_MANAGER_STD_LoadConfigFile) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_LoadConfigFile" );		
				fDRIVER_MANAGER_STD_Get_Commands_List = (tfDRIVER_MANAGER_STD_Get_Commands_List) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_Get_Commands_List" );	
				fDRIVER_MANAGER_STD_Check_Connection = (tfDRIVER_MANAGER_STD_Check_Connection) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_Check_Connection" );	
				fDRIVER_MANAGER_UpdateIgnoreDuplicationAddresses = (tfDRIVER_MANAGER_UpdateIgnoreDuplicationAddresses) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_StandardDevice_UpdateIgnoreDuplicationAddresses" );
				
				if (( strchr( equipmentList->equipment[iEquipmentIndex].id_command , 'x' )) || ( strchr( equipmentList->equipment[iEquipmentIndex].id_command , 'X' )) )
					sscanf( equipmentList->equipment[iEquipmentIndex].id_command , "%llx" , &ulCommandID );
				else
					ulCommandID = atol(equipmentList->equipment[iEquipmentIndex].id_command);
				
				UPDATERR( fDRIVER_MANAGER_STD_Init( pFilePathName , (int)ulCommandID , equipmentList->equipment[iEquipmentIndex].alias , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle ) , 1 , 1 ));

				if ( equipmentList->equipment[iEquipmentIndex].dup_address )
				{
					fDRIVER_MANAGER_UpdateIgnoreDuplicationAddresses( equipmentList->equipment[iEquipmentIndex].handle );
				}
				
				if (( IS_OK ) && ( equipmentList->equipment[iEquipmentIndex].configlink )) 
				{
					UPDATERR( GetDataBaseFileByID( tMainStore.hDatabaseHandle , equipmentList->equipment[iEquipmentIndex].configlink , NULL , NULL , NULL  , NULL , &pFilePathName )); 
				
					if ( IS_OK )
					{
						UPDATERR( fDRIVER_MANAGER_STD_LoadConfigFile( equipmentList->equipment[iEquipmentIndex].handle , pFilePathName ));
					}
					
					if ( IS_OK )
					{
						UPDATERR( fDRIVER_MANAGER_STD_Get_Commands_List( equipmentList->equipment[iEquipmentIndex].handle , &vszSTD_Device_Commands_List , &iNumberOfSTD_Device_Commands ));
						
						if ( IS_OK )
						{
							IF ((( vszSTD_Device_Commands_List == NULL ) || ( iNumberOfSTD_Device_Commands == 0 )) , "No configuration info found." );
							
							for ( iIndex = 0; iIndex < iNumberOfSTD_Device_Commands; iIndex++ )
								iStringLength += strlen( vszSTD_Device_Commands_List[iIndex] ) + 1;

							CALLOC_ERR( pStringToStore , iStringLength , sizeof(char));
		
							for ( iIndex = 0; iIndex < iNumberOfSTD_Device_Commands; iIndex++ )
								iBufferLength += sprintf(( pStringToStore + iBufferLength ) , "%s\0" , vszSTD_Device_Commands_List[iIndex] ) + 1;
	
							if ( iBufferLength )
								iBufferLength--;
	
							VarSetBuffer(  hMainHandle ,  VAR_CONFIG_EQUIPMENT , equipmentList->equipment[iEquipmentIndex].id , "Commands_List" , pStringToStore , iBufferLength );
							
							FREE(pStringToStore);
						}
					}
					
					if ( equipmentList->equipment[iEquipmentIndex].check_commands )
					{   
						if ( IS_OK )
						{
							for ( iCheckDeviceIndex = 0; iCheckDeviceIndex < iNumberOfSTD_Device_Commands; iCheckDeviceIndex++ )
							{
								if ( vszSTD_Device_Commands_List[iCheckDeviceIndex] && strlen(vszSTD_Device_Commands_List[iCheckDeviceIndex]))
								{
									CHK_STDERR_BREAK( fDRIVER_MANAGER_STD_Check_Connection ( equipmentList->equipment[iEquipmentIndex].handle , vszSTD_Device_Commands_List[iCheckDeviceIndex] , &bCheckDeviceStatus ));
							
									if ( bCheckDeviceStatus == 0 )
									{
										sprintf( szMessage , "Command [%s] is not initializet yet!!!" , vszSTD_Device_Commands_List[iCheckDeviceIndex] );
								
										IF (( ConfirmPopup(szMessage,"Do you want to continue?") == 0 ) , szMessage );
									}
								}
							}
						}
					}
				}
				
				break;
			 
			case EQUIPMENT_TYPE_POWER_SUPPLY:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerSupply_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerSupply_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerSupply_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerSupply_Close" );      
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_NETWORK_ANALYZER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NetworkAnalyzer_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NetworkAnalyzer_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NetworkAnalyzer_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NetworkAnalyzer_Close" );      
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_SIGNAL_GENERATOR:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SignalGenerator_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SignalGenerator_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SignalGenerator_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SignalGenerator_Close" );        
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_SPECTRUM_ANALYZER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SpectrumAnalyzer_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SpectrumAnalyzer_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SpectrumAnalyzer_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_SpectrumAnalyzer_Close" ); 
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_OSCILLOSCOPE:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_Oscilloscope_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_Oscilloscope_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_Oscilloscope_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_Oscilloscope_Close" ); 
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_FUNCTION_GENERATOR:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_FunctionGenerator_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_FunctionGenerator_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_FunctionGenerator_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_FunctionGenerator_Close" ); 

				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_POWER_METER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerMeter_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerMeter_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerMeter_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_PowerMeter_Close" ); 

				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));

				break;
			 
			case EQUIPMENT_TYPE_NOISE_FIGURE:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NoiseFigure_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NoiseFigure_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NoiseFigure_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_NoiseFigure_Close" ); 
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));
			
				break;
			 
			case EQUIPMENT_TYPE_MULTI_METER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_MultiMeter_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_MultiMeter_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_MultiMeter_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_MultiMeter_Close" ); 
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));
			
				break;
			 
			case EQUIPMENT_TYPE_WAVE_FORM_ANALYZER:	
		
				fDRIVER_MANAGER_Init = (tfDRIVER_MANAGER_Init) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_WaveAnalyzer_Init" );
				fDRIVER_MANAGER_Reset = (tfDRIVER_MANAGER_Reset) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_WaveAnalyzer_Reset" ); 
				fDRIVER_MANAGER_GetErrorTextMessage = (tfDRIVER_MANAGER_GetErrorTextMessage) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_WaveAnalyzer_GetErrorTextMessage" ); 
				fDRIVER_MANAGER_Close = (tfDRIVER_MANAGER_Close) GetProcAddress( tMainStore.hDriverManagerLibrary , "DRV_WaveAnalyzer_Close" ); 
				
				UPDATERR( fDRIVER_MANAGER_Init( pFilePathName , equipmentList->equipment[iEquipmentIndex].address , &( equipmentList->equipment[iEquipmentIndex].handle )));
			
				break;
		
			default:
			
				break;
		}
	}
	
	if ( IS_OK )
	{
		if ( equipmentList->equipment[iEquipmentIndex].handle == 0 )
		{
			SET_ERR( -23 , "Wrong Driver Initialization." );
		}
	}
	
	if ( IS_OK )
	{
		UPDATERR( fDRIVER_MANAGER_Reset( equipmentList->equipment[iEquipmentIndex].handle ));	
	}
	
	fDRIVER_MANAGER_Get_SimulationMode( equipmentList->equipment[iEquipmentIndex].handle , &iSimulationMode );  
	
	SetActivePanel ( hPanelEquipment );  
	SetActiveTableCell ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(3,(1)) );       
	
	if ( IS_OK ) 
	{
		SetTableCellAttribute (hPanelEquipment, EQUIP_INIT_TABLE, MakePoint (3,(1)), ATTR_TEXT_COLOR, VAL_DK_GREEN ); 
		
		if ( iSimulationMode )
		{
			SetTableCellVal ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(3,(1)), "DEMO" );   						
		}
		else
		{   
			SetTableCellVal ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(3,(1)), "PASS" );   						
			bTestStaus = 1; 
		}
	}
	else
	{
		SetTableCellAttribute ( hPanelEquipment, EQUIP_INIT_TABLE ,MakePoint (3,(1)), ATTR_TEXT_COLOR,VAL_DK_RED); 
		SetTableCellVal ( hPanelEquipment, EQUIP_INIT_TABLE , MakePoint(3,(1)), "FAIL" );  
	}
	
	ProcessDrawEvents(); 
	
	do
	{
		MakeApplicationActive ();
		SetActivePanel ( hPanelEquipment );
		ProcessDrawEvents();
	
		CHK_CMT( CmtGetTSVPtr ( hMainHandle , &pMainStore ));  
		if ( pMainStore->pRet && pMainStore->pRet->error )
		{
			FILL_STDERR( pMainStore->pRet ); 
		}
		CmtReleaseTSVPtr (hMainHandle);
		CHK_STDERR(StdError);
	
		event = GetUserEvent ( 1 , &panel , &control );   
	
		if ( panel != hPanelEquipment )
			continue;

		if ( control == EQUIP_INIT_CANCEL )
			break;
	
	}while ( control != EQUIP_INIT_ACCEPT );
							   
	if (( bTestStaus ) && ( control == EQUIP_INIT_ACCEPT ))
	{
		if ( bPopup )
		{
			RemovePopup (0);
			bPopup = 0;
		}
		
		if ( fDRIVER_MANAGER_Equipment_BrowseSelectStateFiles )
			fDRIVER_MANAGER_Equipment_BrowseSelectStateFiles( equipmentList->equipment[iEquipmentIndex].handle , NULL , NULL , NULL , NULL );	
	}
	
Error:

	if ( fDRIVER_MANAGER_Close )
		fDRIVER_MANAGER_Close( &(equipmentList->equipment[iEquipmentIndex].handle) );	 
	
	if ( bPopup )
		RemovePopup (0);
	
	if ( hPanelEquipment )
		DiscardPanel ( hPanelEquipment );
	
	if ( hPopupCalibrationGraphPanel )
		DiscardPanel ( hPopupCalibrationGraphPanel ); 
		
	if ( hPopupPanel )
		DiscardPanel ( hPopupPanel ); 
	
	db_equipment_freelist(&equipmentList);
	
	FREE(pFilePathName);
	
	FREE_LIST( vszSTD_Device_Commands_List , iNumberOfSTD_Device_Commands );
	
	return StdError;
}
