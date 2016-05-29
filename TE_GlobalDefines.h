#ifndef __TE_GlobalDefines_H__
#define __TE_GlobalDefines_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "GlobalDefines.h"
#include "dblayer.h"

//==============================================================================
// Constants

#define			TEST_SEL_EVENT_ADD_TEST						1999
#define			TEST_SEL_EVENT_REMOVE_TEST					1998
#define			TEST_PANEL_SIZE_CHECK						1997
		
#define			MAX_NUMBER_OF_PANELS_STORE					32 
		
//==============================================================================
//DB
#define			TEST_EXECUTIVE_SUB_KEY						"Software\\ATE\\Test Executive"
#define			TEST_EXECUTIVE_DB_SUB_KEY					"Software\\ATE\\Test Executive\\Databases" 
		
#define			ALLOW_ACTIVE_CONTANT_SUB_KEY				"Software\\Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_LOCALMACHINE_LOCKDOWN" 

#define			LAST_ODBC_CONNECTION						"LAST_ODBC_Connection"
#define			DEFAULT_ODBC_CONNECTION						"DEFAULT_ODBC_Connection"
#define			DEFAULT_LICENSE_SERVER						"DEFAULT_License_Server" 
		
#define			DB_ODBC_NAME								"DB_ODBC_NAME"
#define			DB_DATABASE_NAME							"DB_DATABASE_NAME"
#define			DB_DRIVER_NAME								"DB_DRIVER_NAME"
#define			DB_SERVER_LOCATION							"DB_SERVER_LOCATION"
#define			DB_USER_NAME								"DB_USER_NAME"
#define			DB_USER_PASSWORD							"DB_USER_PASSWORD"
#define			DB_PROJECT_NAME								"DB_PROJECT_NAME" 
#define			DB_PROJECT_NUMBER							"DB_PROJECT_NUMBER" 
#define			DB_LOCAL_SERVER								"DB_LOCAL_SERVER" 
#define			DB_MAIN_ODBC_NAME							"MAIN_DB_ODBC_NAME"
		
#define			MAIN_DB_ODBC_NAME							"MAIN_DB_ODBC_NAME"
#define			MAIN_DB_DATABASE_NAME						"MAIN_DB_DATABASE_NAME"
#define			MAIN_DB_DRIVER_NAME							"MAIN_DB_DRIVER_NAME"
#define			MAIN_DB_SERVER_LOCATION						"MAIN_DB_SERVER_LOCATION"
#define			MAIN_DB_USER_NAME							"MAIN_DB_USER_NAME"
#define			MAIN_DB_USER_PASSWORD						"MAIN_DB_USER_PASSWORD"

#define			INSTR_TYPE_CONTINUE							0
#define			INSTR_TYPE_YES_NO							1		
//================================================================================
// Types

typedef int   (*tfEXLX_Init)( char *szTemplateFile , int bVisible , int *pHandle );
typedef int   (*tfEXLX_UpdateTargetFileName)( int handle , char *szFileName  );
typedef int   (*tfEXLX_GetTargetFileName)( int handle , char **szFileName  );    
typedef int   (*tfEXLX_Print_VectorOfLabels)( int handle , char **pszLabelName , char **pszLabelValue , int iNumberOfItems );    
typedef int   (*tfEXLX_Read_VectorOfLabels)( int handle , char ***pszLabelName , char ***pszLabelValue , int *piNumberOfItems );  
typedef int   (*tfEXLX_ExportAllToPDF)( int handle , char *szFileNamePath );
typedef int   (*tfEXLX_SetVisibleStatus)( int handle , int bVisible );
typedef int   (*tfEXLX_SetActivePage)( int handle , int iSheetNumber );   
typedef int   (*tfEXLX_GetCurrentRange)( int handle , char **pszCellIndexName , char **pszCellName );
typedef int   (*tfEXLX_IsCellNameExists)( int handle , char *szCellName , int bSelectCell , int *piExists );
typedef int   (*tfEXLX_SetCellFontAttributes)( int handle , char *szLabelName , int fontColor , int fontSize , int fontBold , int fontUnderline );
typedef int   (*tfEXLX_SetCellName)( int handle , char *szCellIndexName , char *szCellName );
typedef int   (*tfEXLX_OpenTemplateFileEx)( int handle , char *szFileName  );  
typedef int   (*tfEXLX_OpenTemplateFile)( int handle );
typedef int   (*tfEXLX_SaveTemplateFile)( int handle );
typedef int   (*tfEXLX_CloseTemplateFile)( int handle );
typedef int   (*tfEXLX_Close)( int *pHandle );  

typedef int   (*tfWRDX_Init)( char *szTemplateFile , int bVisible , int *pHandle );
typedef int   (*tfWRDX_GetCurrentRange)( int handle , char **pszCellIndexName , char **pszCellName );
typedef int   (*tfWRDX_IsBookmarkExists)( int handle , char *szCellName , int bSelectCell , int *piExists );
typedef int   (*tfWRDX_SetBookmarkName)( int handle , char *szCellIndexName , char *szCellName );
typedef int   (*tfWRDX_OpenTemplateFileEx)( int handle , char *szFileName  );  
typedef int   (*tfWRDX_OpenTemplateFile)( int handle );
typedef int   (*tfWRDX_SaveTemplateFile)( int handle );
typedef int   (*tfWRDX_UpdateTargetFileName)( int handle , char *szFileName  );
typedef int   (*tfWRDX_GetTargetFileName)( int handle , char **szFileName  );
typedef int   (*tfWRDX_Print_VectorOfLabels)( int handle , char **pszLabelName , char **pszLabelValue , int iNumberOfItems );    
typedef int   (*tfWRDX_Read_VectorOfLabels)( int handle , char ***pszLabelName , char ***pszLabelValue , int *piNumberOfItems ); 
typedef int   (*tfWRDX_SetRangeFontAttributes)( int handle , char *szLabelName , int fontColor , int fontSize , int fontBold , int fontUnderline , int textAlignment ); 
typedef int   (*tfWRDX_ExportAllToPDF)( int handle , char *szFileNamePath );
typedef int   (*tfWRDX_SetVisibleStatus)( int handle , int bVisible );
typedef int   (*tfWRDX_SetActivePage)( int handle , int iSheetNumber );   
typedef int   (*tfWRDX_CloseTemplateFile)( int handle ); 
typedef int   (*tfWRDX_Close)( int *pHandle );

typedef struct
{

		HINSTANCE							hExcelPlugInLibrary;
		
		tfEXLX_Init							EXLX_Init;                   
		tfEXLX_UpdateTargetFileName			EXLX_UpdateTargetFileName;   
		tfEXLX_GetTargetFileName			EXLX_GetTargetFileName;
		tfEXLX_Print_VectorOfLabels			EXLX_Print_VectorOfLabels;   
		tfEXLX_Read_VectorOfLabels			EXLX_Read_VectorOfLabels;
		tfEXLX_ExportAllToPDF				EXLX_ExportAllToPDF;         
		tfEXLX_SetVisibleStatus				EXLX_SetVisibleStatus;       
		tfEXLX_SetActivePage				EXLX_SetActivePage;          
		tfEXLX_GetCurrentRange				EXLX_GetCurrentRange;        
		tfEXLX_IsCellNameExists				EXLX_IsCellNameExists;       
		tfEXLX_SetCellName					EXLX_SetCellName;            
		tfEXLX_SetCellFontAttributes		EXLX_SetCellFontAttributes;
		tfEXLX_OpenTemplateFileEx			EXLX_OpenTemplateFileEx;     
		tfEXLX_OpenTemplateFile				EXLX_OpenTemplateFile;       
		tfEXLX_SaveTemplateFile				EXLX_SaveTemplateFile;       
		tfEXLX_CloseTemplateFile			EXLX_CloseTemplateFile;      
		tfEXLX_Close						EXLX_Close;                  
	
} tuExcelPlugInItem;

typedef struct
{
		HINSTANCE							hWordPlugInLibrary;
		
		tfWRDX_Init							WRDX_Init;                         								   
		tfWRDX_GetCurrentRange				WRDX_GetCurrentRange;              								   
		tfWRDX_IsBookmarkExists				WRDX_IsBookmarkExists;             
		tfWRDX_SetBookmarkName				WRDX_SetBookmarkName;                 
		tfWRDX_OpenTemplateFileEx			WRDX_OpenTemplateFileEx;           
		tfWRDX_OpenTemplateFile				WRDX_OpenTemplateFile;             
		tfWRDX_SaveTemplateFile				WRDX_SaveTemplateFile;             
		tfWRDX_UpdateTargetFileName			WRDX_UpdateTargetFileName;         
		tfWRDX_GetTargetFileName			WRDX_GetTargetFileName;
		tfWRDX_Print_VectorOfLabels			WRDX_Print_VectorOfLabels;         
		tfWRDX_Read_VectorOfLabels			WRDX_Read_VectorOfLabels;
		tfWRDX_SetRangeFontAttributes		WRDX_SetRangeFontAttributes;
		tfWRDX_ExportAllToPDF				WRDX_ExportAllToPDF;               
		tfWRDX_SetVisibleStatus				WRDX_SetVisibleStatus;             
		tfWRDX_SetActivePage				WRDX_SetActivePage;                
		tfWRDX_CloseTemplateFile			WRDX_CloseTemplateFile;            
		tfWRDX_Close						WRDX_Close;                        
	
} tuWordPlugInItem;

typedef int (*EXT_TRIG_TemperatureInitModule)( int ,char*,char*,char*,int*);
typedef double (*EXT_TRIG_TemperatureSyncSigment)(int,double,double,double);
typedef double (*EXT_TRIG_VibrationSyncSigment)( int, double, double, double );

typedef int (*EXT_TRIG_TemperatureCloseModule)(int*);

typedef enum { VALUE_TYPE_INT , VALUE_TYPE_DOUBLE , VALUE_TYPE_STRING , VALUE_TYPE_IMAGE , VALUE_TYPE_INT_ARRAY , VALUE_TYPE_DOUBLE_ARRAY , VALUE_TYPE_SENTINEL } teValueType;
		
typedef enum{ NOT_SELECTED , RUN_SELECTION , DOC_SELCTION , DATABASE_SELECTION , REPORT_SELECTION , CLEAR_SELECTION , SENTINEL_SELECTION } teMAIN_SELECTION;
		
typedef enum{ RUN_MODE_TEST , RUN_MODE_CALIBRATION , RUN_MODE_DEBUG , RUN_MODE_DEMO , RUN_MODE_SENTINEL } teMAIN_RUN_MODE;

typedef enum{ TEST_STATUS_RUNNING, TEST_STATUS_PASS, TEST_STATUS_FAIL, TEST_STATUS_ABORT, TEST_STATUS_ERROR, TEST_STATUS_DEMO, TEST_STATUS_SENTINEL } teSTATUS_TEST;


typedef struct
{
	int											hPanel,
												bDisplayed;
	
	int	  							 			control_lb_TEST_MESSAGES,
												control_rb_STOP_ON_RESULT,  
												control_num_RESULT_NUM,
												control_rb_STOP_ON_TEST_END,
												control_rb_SINGLE_STEP,
												control_rb_STOP_ON_FAIL,    
												control_tb_TEST_FLOW,       
												control_tb_UUT_NAME,        
												control_tb_USER_NAME,       
												control_tb_SN,              
												control_tb_UUT_VERSION,     
												control_tb_TEST_NAME,       
												control_ns_RESULT_BAR,      
												control_cb_ABORT_TEST,      
												control_cb_ABORT_ALL,       
												control_TABLE_RESULT,       
												control_cb_STOP_TEST,       
												control_cb_CONTINUE_TEST,   
												control_STOP_LED,           
												control_TESTS_LIST,         
												control_LOOP,               
												control_PROGRESS_DELAY,
												control_PROGRESS_TIMEOUT,
												control_DELAY_TIME,
												control_TIMEOUT_TIME,
												control_UUT_NUMBER,
												control_TIME,
												control_cb_OPEN_REPORT,
												control_RESULT_BAR_TIME,
												control_rb_PAUSE_ON_DELAY,
												control_TEMPERATURE,
												control_SERMENT,
												control_PATH_NAME,
												control_PATH_INDEX,
												control_FREQ_INDEX,
												control_TOTAL_COMP,
												control_REPORT_TYPE;
								
	int											left,
												top;
	
}teTestPanel;


typedef struct 
{
	int											iControlID;
	
	int											iLeft,
												iTop,
												iWidth,
												iHeight;   
	
	int											iBeforeMoveLeft,
												iBeforeMoveTop;
	
	int											iXCoordinate,
												iYCoordinate;
	
	int											iPreviousLinkedControl,
												iPreviousLinkedIndex;
	
	int											iNextLinkedControl,
												iNextLinkedIndex;
}tsConfigSingleItem;

typedef struct 
{
	tsConfigSingleItem							tLabelCtrlID,
												tValueCtrlID,
												tNumberCtrlID,
												tPictureCtrlID;
	
	int											iNumber,
												iDefCtrl,
												iType,
												iUnique;

	unsigned long long							iImageID;
	
}tsConfigControlsItem;
	
typedef struct 
{
	tsConfigControlsItem						*pConfigControls;
	
	int											iNumberOfConfigs,
												iCurrentControlIndexMouseMoveIndex,
												iCurrentControlIDMouseMove,
												iCurrentPanelIDMouseMove;
							
	
	int											iNextLinkedControl,
												iNextLinkedIndex;
	
	int											bSaveNeeded;
	
}tsConfigControl;

typedef struct 
{ 
			tTest								*ptDB_Test;
			tlSpec								*ptlDB_Specs; 
			
			HMODULE								dllTestHandle,
												dllPathHandle,
												dllCalibHandle;
	
			char								*pPathApplyFunction;
	
			int									hPathModuleRefHandle;
	
			char								*pszLibraryPath;
	
			int									iTestStatus,
												iTotalTestStatus;
	
			int									hLockHandle,
												lockStatus;
	
			int									iCurrentLoop,
												iNumberOfLoops;
	
			int									iCurrentPathIndex,
												iCurrentCalibPathPartIndex;
	
			int									iNumberOfTestSteps;
	
			double								lfLoopTime,
												lfLoopStartTime;
	
			unsigned long long					database_session;
	
			int									bStopOnFail,
												bSingleStep,
												bStopOnTestEnd,
												bPauseOnDelay,
												iPauseOnResult;
	
			int									bConfig_TryToStartTestWhileBusy,
												bConfig_ReportDisableView;

			int									bTryNextTime; 
			
			//------------ Version 4.4.0.0 --------------------// 
			
			tlEquipmentUse						*ptlDB_EquipmentList;				
			
			//------------ Version 4.4.2.0 --------------------//
			
			int									*pPathDisableList,
												*pPathHasDoneList;
			//------------ Version 4.6.12.0 --------------------// 
			int									*pFrequencyDisableList;
			int									iFrequencyListLength;
	
			//------------ Version 4.6.20.0 --------------------// 
			int									iNumberOfReTestHaveDone;

			//------------ Version 5.2.6.0 --------------------//     
			int									bDisableTestResultCountCheck;
			
}tsSingleTestItem;

typedef struct 
{
	tsSingleTestItem							*pCurrentRunTestSeq;
	
	int											iNumberOfSelectedTests;
	
} tsTestListItem;

typedef struct
{
	int											number;
	
	char										*pszParameter;
	
}tsExtraItem;

typedef struct
{
	int											iNumberOfItems;
	
	tsExtraItem									*pList;
	
}tsExtraParamsList;

typedef struct
{
		char									*pszSerialNumberParsingModulePath,
												*pszAutoSelectionModulePath,
												*szOperator;
	
		int										bRunLastSnConfig,
												bAutoContinue;
	
		int										iMaxNumberOfSlots,
												iMaxNumberOfExtraParams;
} tuSelectSerialNumberItem;
	
typedef struct
{
	tsExtraParamsList							tExtraList;
	
	char										*pSerialNumber,
												*pPartNumber,
												*pNote;
	
	int											bRunEnable;
	
	int											iAutoSelect_UUT_Index,
												iAutoSelect_Verion_Index;
	void										*piAutoSelect_ExtraData;
	int											iAutoSelect_ExtraDataLength;

} tsSSNRItem;

typedef struct
{
	tsSSNRItem									*pSelect;
					
	int											iNumberOfSlots;

} tsSSNRList;

typedef struct
{
	double										lfStartToolTipTime;

	int											iLastXcoordinates,
												iLastYcoordinates,
												iToolTipControl,
												bToolTipEnabled,
												iToolTipPanel;
	
	int											hProcessingToolTipLock;
	
}tsToolTipItem;

typedef	struct
{
	int											handle,
												type;
	
	void										*pResult,
												*pResdata;
	
	int											iCurrentTestIndex,
												iResultIndex,
												iCurrentSpecIndex;
	
	int											iTestStatus;
	
	char										*pszPicturePath;
	
	unsigned long long							ulTestBatabaseSession;
	
	tSpec										*spec;
	
} tsSTANDARD_RESULT_ITEM;
/*
typedef	struct
{
	tsSTANDARD_RESULT_ITEM						*pResults;
	
	int											iNumberOfResults;

} tsSTANDARD_RESULT_LIST;
*/
typedef struct
{
			int									bSkipSerialNumber,
												bAutoContinueSerialNumber,
												bBreakAllTestsOnError,
												bRunPreTestOnce,
												bRunPostTestOnce,
												bRunPreTestFirstOnce,
												bRunPostTestLastOnce,
												bRunPostTestAnyWay,
												bTestsPanelsMoveble,
												bPopupVariablesStringEditor,
												bReportOrderDown,
												bRunAnyWay,
												bTestStopEventsForAllTests,
												bViewTestTotalTimeOnSummery,
												bViewReportAttachedFiles,
												bRunAutoSelectionOnly,
												bUserSelectAllReports;
	
			int									iUserSelectReportType;
	
			double								lfStatusWindowTimeout;
	
			//------------ Version 4.2.0.0 --------------------// 
			
			int									bDisableMainWindowResizing;

			//------------ Version 4.4.2.0 --------------------// 
			int									bRunSequencyPathOriented;
			
			//------------ Version 4.4.4.0 --------------------// 
			int									bEnableedToRepeatTestAtFail;
			
			//------------ Version 4.4.5.0 --------------------// 
			int									bWarningForSerialNumberRepeat;
			//------------ Version 4.6.6.0 --------------------// 
			int									bRunInDemoMode;
			//------------ Version 4.6.21.0 --------------------// 
			int									bSkipDeviceCommandRepeatCheck;
			//------------ Version 4.7.0.0 --------------------// 
			int									iAllowedNumberOfReportThreads,
												iAllowedNumberOfTestThreads;
			//------------ Version 4.8.3.0 --------------------// 
			int									bDeleteReportSourceAfterGeneration;
		
			//------------ Version 5.0.10.0 --------------------// 
			int									bUserReadyToRunUUT;
			
			//------------ Version 5.1.8.0 --------------------// 
			int									bOpenReportSourceOnly;
	
			//------------ Version 5.2.2.0 --------------------// 
			int									bTempVibrMeasureDev;
			
			//------------ Version 5.2.4.0 --------------------//     
			int									bDisableExportReports;

			//------------ Version 5.2.5.0 --------------------//     
			int									bReportsOneBasedTemperatureIndex;
			
			//------------ Version 5.2.8.0 --------------------//     
			int									bDisableToCheckTemperatureTrigger;

			//------------ Version 5.2.16.0 --------------------//     
			double								lfVibrationUpdatePeriod,
												lfTemperatureUpdatePeriod;

			//------------ Version 5.2.18.0 --------------------//     
			double								lfProfileLogUpdatePeriod;
			
			//------------ Version 5.3.1.0 --------------------//     
			int									bGenerateReportsAutomatically;
			
			//------------ Version 5.4.6.0 --------------------//     
			int									bDisableGenerateReportsAfterTest,
												bBlockStartTestWhileGeneratingReports;
			
			//------------ Version 5.4.9.0 --------------------//     
			int									iGenerateReportsByStatusLevel;
			
} tsConfiguration;

typedef struct 
{ 				  
			//-------------------------- Local Store -------------------------------------//
		
			int									bEnableRun,
												bRunning;
	
			int									hDatabaseHandle,
												hMainDatabaseHandle; 
	
			int									hSlotPoolThreadHandle;

			teTestPanel							*pvhTestPanels;
			
			int									hCurrentVisiblePanel,
												hCurrentVisiblePanelIndex;
	
			int									hMainStoreHandle;
	
			int									iSlotIndex;
	
			STD_ERROR							*pLastError;
	
			unsigned __int64					dwOperatorPrivileges; 
	
			int									bInSleepState;
	
			int									iSpecGroup;
			teMAIN_RUN_MODE						tRunMode;
	
			tSession							*pCurrent_database_session;
	
			unsigned long long					hCurrentTestId; 
	
			int									iCurrentTestIndex,
												iDrawStatusTestIndex;
								
			int									iNextResultIndex,
												iCurrentSpecIndex;
	
			tsTestListItem						tCurrentRunTestSeq;  

			int									iCurrentLoop,
												iNumberOfLoops;
	
			double								lfCurrentTestStartTime;
	
			double								lfCurrentTemperature; 
	
			int									iCurrentTemperatureLoop,
												iNumberOfTemperatureLoops;
	
			int									iCurrentTemperatureSegment,
												iNumberOfTemperatureSegments;
	
			int									hTemperatureModuleHandle;
	
			EXT_TRIG_TemperatureSyncSigment		EXT_TRIG_TemperatureModuleSet;
		
			tsToolTipItem						tToolTips;
	
			double								lfLoopTime,
												lfLoopStartTime;
	
			double								lfStartTimeoutTime,
												lfMaxTimeoutTime;
	
			double								lfStartDelayTime,
												lfMaxDelayTime;
	
			int									hThreadID,
												hGuiThreadID;
	
			int									bSetPaused,
												bPaused;
	
			int									bTryNextTime;
												
			int									bDisableStatusWindow;
	
			int									bBreakRunningSequence; 
	
			int									hSlotGuiLockHandle,
												hSlotGuiBusyLockHandle;
	
			int									slotVariableSaving;
	
			tsExtraParamsList					extraParameters;
	
			unsigned long long					hCurrentSelectedUutId,
												hCurrentSelectedVersionId;
	
			char								*pszCurrentSelected_UUT_PartNumber,
												*pszCurrentSelected_UUT_Name,
												*pszCurrentSelected_UUT_VersionName;
	
			unsigned int						iAtuo_UUT_Selection_Index,
												iAtuo_VER_Selection_Index;
		
			void								*pAuto_ExtraData;
			int									iAuto_ExtraDataLength;
	
			int									bRunningStatus,
												iTotalStatus;
	
			int									bBreakTemperatureRunning,
												bEnableOvenExtremeMode;
	
			int									iStatusWindowTop, 
												iStatusWindowLeft;
	
			char								*pszTitleName,
												*pszCurrentPathName;
			
			//------------ Version 4.2.0.0 --------------------// 
			
			char								*pszOperatorName;
			
			tsConfiguration						*pRunConfig;
			
			int									iCurrentMonitorID;
			
			int									iSelectedNumberOfSlots;
			
			int									bRunMultiThread;
			
			unsigned long long					hCurrentUserId;
			
			char								*pszStationLocation, 
												*pszStationName,
												*pszStationPartNumber,
												*pszStationSerialNumber;
			
			double								*pPathFrequenciesList;
			int									iPathFreqNumberOfPoints;
				
			int									hSlotBackgroundThreadID,
												hSlotBackgroundBusyLockHandle;
			
			int									bRunDelayProcess;
			
			//------------ Version 4.2.3.0 --------------------// 
			
			char								*pLastPathManualConnectionDescription;
			
			//------------ Version 4.2.14.0 --------------------//  
			
			int									iLastResultStatus;

			//------------ Version 4.4.3.0 --------------------//  
			char								*pszPreviousPathName;

			//------------ Version 4.4.4.0 --------------------//  
			int									iPathGroup; 
			//------------ Version 4.4.5.0 --------------------//  
			char								*pszCurrentPathDescription;
			double								lfUserResponseTime;
			
			char								*pszPreviousCalibrationPathName;
			//------------ Version 4.4.6.0 --------------------//  
			char								*pPathPartAlias;
			
			//------------ Version 4.6.3.0 --------------------// 
			tlFrequency							*ptlFrequencies;
			int									iCurrentFrequencyIndex;
			
			//------------ Version 4.6.10.0 --------------------//
			int									bGuiUpdatingDisabled;
			
			//------------ Version 4.6.13.0 --------------------//
			double								lfDefaultTemperature;
			
			//------------ Version 4.8.2.0 --------------------//
			int									bGuiUpdatingDisabledReleased;

			//------------ Version 4.9.2.0 --------------------//
			int									*pPathRangesList;
			int									iPathFreqNumberOfRanges;

			//------------ Version 5.1.9.0 --------------------//  
			char								*pszCurrentSelected_UUT_Project_Number;
			
			//------------ Version 5.1.15.0 --------------------//     
			double								lfCurrentVibration;  
			//------------ Version 5.1.17.0 --------------------//     
			int									bTestIsEnding;  
			
			//------------ Version 5.2.4.0 --------------------//     
			unsigned long long					*pTemperatureProfileReportList;
		
			//------------ Version 5.2.6.0 --------------------//     
			int									hResultToWindowQueueHandle,
												hResultAnalyzeQueueHandle;
			
			int									hLogProcessQueueHandle,
												hLogToWindowQueueHandle;
			
			int									hFileProcessQueueHandle;
			
			tLog								tCurrentLogBuffer;
			
			//------------ Version 5.2.8.0 --------------------//     
			int									iMaxNumberOfSlots,
												iMaxNumberOfSlotsToSelect;
			//------------ Version 5.4.1.0 --------------------//     
			int									bSlotFinishedRunning;
			
}tsSlotStore;

typedef struct
{
			//----------------- Main Store -------------------------//
			int									bRunMultiThread;
	
			int									bRunningStatus; 
	
			int									hMainPanelHandle,
												hMenuBarHandle;
	
			int									hTestPoolThreadHandle;
			
			int									hInstructionLockHandle;
	
			int									hSemaphoreLockHandle;
	
			unsigned int						uiSemaphoreSpaceCounter;
	
			int									bMainThreadBusy;   
	
			int									hDatabaseHandle,
												hMainDatabaseHandle;
	
			int									iCurrentSlotIndex;
	
			int									hMainThreadLock;
	
			int									iMaxNumberOfSlots,
												iMaxNumberOfSlotsToSelect,
												iCalibNumberOfSlotsToSelect;
	
			int									iSelectedNumberOfSlots;
			int									*pSlotsHandleList;
			int									*pSlotsDisabledList;
	
			int									iNumberOfCurrentRunningSlots,
												iNumberOfActiveTestThread,
												iMaximumNumberOfActiveTestThread;    
	
			int									globalTestsVariableSaving;  
	
			int									bLoadLastSnConfig,
												bRunLastSnConfig;
	
			char								*pszSW_Revision,
												*pszStationName,
												*pszStationLocation,
												*pszOperator,
												*pszOperatorPassword,
												*pszStationPartNumber,
												*pszStationSerialNumber;
	
			unsigned __int64					dwOperatorPrivileges;
		
			char								*pszCurrentSelected_UUT_PartNumber,
												*pszCurrentSelected_UUT_Name,
												*pszCurrentSelected_UUT_VersionName;
	
			char								*pszSerialNumberSelectModulePath,
												*pszSerialNumberParsingModulePath,
												*pszAutoSelectionModulePath,
												*pszProfileTriggerModulePath,
												*pszProfileModuleDeviceAddress_,
												*pszProfileModuleDeviceDriverLocation_,
												*pszProfileModuleDeviceConfigFile_,
												*pszExcelTemplatePath,
												*pszWordTemplatePath;
	
			unsigned int						iTemperatureModuleDriverID;
	
			int									iVersionNumber;
			double								lfTemperatureCelsius,
												lfDelayBetweenStartSlots;
	
			tsTestListItem						tCurrentRunTestSeq;   
	
			int									bSelectedFullATP;

			int									bPreTestSelected,
												bPostTestSelected;
	
			int									iNumberOfExtraParameters;
	
			teMAIN_RUN_MODE						tRunMode;
			int									iSpecGroup;
	
			unsigned long long					hCurrentStationId,
												hCurrentUserId,
												hCurrentSelectedUutId,
												hCurrentSelectedVersionId;

			unsigned long long					hLastSessionReport;

			unsigned long long					hEditorCurrentSelectedStationID,
												hEditorCurrentSelectedUserID,
												hEditorCurrentSelectedUutID,
												hEditorCurrentSelectedUutVersionID,
												hEditorCurrentSelectedTestID,
												hEditorCurrentSelectedVariableID,
												hEditorCurrentSelectedSpecID,
							
												hEditorCurrentSelectedTemperatureProfileID, 
												hEditorCopyCameFromVersionID,
												hEditorCopyCameFromUutID;
	
			int									hEditorCurrentSelectedVarType;

			char								*pszEditorCurrentSelectedTestName,
												*pszEditorTestTemplatePrefix;
									
			int									hEditorTemplateHandle;
			unsigned long long					hEditorTemplateFileDatabaseID;
			char								iEditorTemplateBookmarkStyle;
			
			char								*pTemplateFileFullPath;
	
			int									iLastSelectionSectionIndex;
	
			tsConfigControl						*ptConfigControls;

			tlUser								*copyUsers;
			tlStation							*copyStations;
			tlUut								*copyUUTs;
			tlUutVer							*copyUUTversions;
			tlFile								*copyFiles;
			tlTest								*copyTests;
			tlSpec								*copySpecs;
			tlVar								*copyVariables;
			tlCalibration						*copyCalibrations;
			tlVerConfig							*copyConfigControls;
			tlTempProfile						*copyTempProfileList;

			double								lfLastMainPanelSizeingTime;

			int									iMainPanelLastWidth,
												iMainPanelLastHeight,
												iMainPanelLastZoom,
												iStartMainPanelTop,
												iStartMainPanelLeft,
												iStartMainPanelMax;

			int									bRunLast,
												bInitRun;
	
			int									bGlobalExitRequest;
	
			tsConfiguration						config;
	
			STD_ERROR							*pRet;
	
			char								*pApplicationFileName,
												*pDatabaseName;
			
			//------------ Version 4.2.0.0 --------------------//
			
			char								*pszReferanceDataBaseName;

			//------------ Version 4.3.1.0 --------------------//
			
			HINSTANCE							hDriverManagerLibrary;
			
			//------------ Version 4.3.4.0 --------------------//  
			unsigned long long					hEditorCurrentSelectedEquipmentID,
												hEditorCurrentSelectedEquipmentUsedID;
			
			int									iEditorCurrentSelectedEquipmentType;

			//------------ Version 4.4.0.0 --------------------//  
			tlEquipmentUse						*copyEquipmentUse; 
			
			//------------ Version 4.4.4.0 --------------------//  
			int									iPathGroup; 
			//------------ Version 4.5.0.0 --------------------//  
			char								**pCalibratedPathList;
			int									iCalibratedPathListCount;
			//------------ Version 4.5.1.0 --------------------// 
			
			int									hMainDatabaseLockHandle;
			
			//------------ Version 4.6.0.0 --------------------// 
			tuExcelPlugInItem					*ptExcelPlugIn;
			tuWordPlugInItem 					*ptWordPlugIn;
			
			//------------ Version 4.6.13.0 --------------------//
			double								lfDefaultTemperature;

			//------------ Version 4.6.20.0 --------------------//
			char								**pLastPathCommandsList;
			int									*piLastPathCommandValuesList;
			int									iLastPathNumberOfCommands;
			int									bLastPathCommandHasApplied;
			
			//------------ Version 4.8.7.0 --------------------//  
			tlEquipment							*copyEquipment; 
			
			//------------ Version 4.8.11.0 --------------------//  
			
			char								*pLicenseServerAddress;
			
			//------------ Version 5.0.3.0 --------------------//  
			
			int									iEditorCurrentSpecGroup;
		
			//------------ Version 5.0.9.0 --------------------//  
			unsigned int						ulCurrentUserLevelNumber;

			//------------ Version 5.1.9.0 --------------------//  
			char								*pszCurrentSelected_UUT_Project_Number;
			
			//------------ Version 5.2.3.0 --------------------//               
			int									bCurrentRunningDatabaseIsServer;
			
			//------------ Version 5.2.5.0 --------------------//               
			int									hExcelGeneratorHandle,
												hWordGeneratorHandle;
			
			//------------ Version 5.2.6.0 --------------------//  
			int									bSchedulingTesting;
			int									iNumberOfFinalizingTestThread;
			
			//------------ Version 5.2.16.0 --------------------//  
			int									hOvenControlHandle,
												hOvenControlLockHandle;
			
			//------------ Version 5.2.18.0 --------------------//  
			int									iRunningTestSlots,
												iSlotsHaveFinishedSegment,
												iSlotsWantToFinishSegment,
												iNumberOfScheduledTestThread;
			
			//------------ Version 5.2.24.0 --------------------//  
			unsigned long long					station_unique;
			
			//------------ Version 5.3.4.0 --------------------//  
			int									hImportFilesFunctiondID;

			//------------ Version 5.4.6.0 --------------------//  
			int									bGeneratingReportsInProgress;
			
}tsMainStore;


typedef	struct
{
			int									handle,
												iValue,
												iValue2,
												iValue3,
												iValue4;
	
			void								*pData,
												*pData2;
	
			char								szParameter[10][64];

			char								szBigParameter[1024];
			
			double								lfValue;
	
			int									hGuiThreadID,
												bGuiUpdatingDisabled;
			
} tsSTANDARD_POST_DATA;


typedef	struct
{
	tSpec								*spec;
	
	tResult								*pResult;
	
	void								*resdata;

	int									hDatabaseHandle;
	
} tsRESULT_THREAD_ITEM;
	
typedef	struct
{
	double										lfCurrentVibration,
												lfVibrationUpdateTime,
												lfCurrentTemperature,
												lfTemperatureUpdateTime,
												lfExportReportsUpdateTime;
	
	int											bTriggeredStart,
												bTriggeredStop;
	
} tsOVEN_CONTROL_ITEM;

//==============================================================================
// External variables

//==============================================================================
// Global functions

STD_ERROR 	FreeCopySlotStore ( tsSlotStore *ptTargetStore , tsSlotStore *ptSourceStore );

void MainPanelSelectGroup( int hMainHandle , teMAIN_SELECTION teGroupIndex );

STD_ERROR	Update_CLIENT_Pic( int hMainHandle );

//---------------- Tools -----------------------------------------------------//
int  	ShowMessage ( int hDatabaseHandle , int type , char *pTitle , char *pText, char *pPicture );

int  	InputMessage ( char *pTitle , char *pText, char *pInputMessage );

char	*StringReplaceAll( char *szSourceString , char *szFindWhat , char *szReplaceWith , int *pCount );

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __TE_GlobalDefines_H__ */
