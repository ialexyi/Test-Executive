//all the test functions are of this type
//typedef int (*test_func)(sClb*);

#ifndef _CLB_H_
#define _CLB_H_

#include "GlobalDefines.h"

#ifndef				__TEST_EXECUTIVE__
#define				__TEST_EXECUTIVE__
#endif

#define				CONFIG_STATION_DISABLE_MAIN_RESIZING			"DisableMainPanelResizing"
#define				CONFIG_STATION_MAX_NUMBER_OF_SLOTS				"MaxNumberOfSlots"
#define				CONFIG_STATION_START_MAIN_PANEL_TOP				"StartMainPanelTop"
#define				CONFIG_STATION_START_MAIN_PANEL_LEFT			"StartMainPanelLeft"
#define				CONFIG_STATION_START_MAIN_PANEL_MAX				"StartMainPanelMax" 
#define				CONFIG_STATION_LAST_REPORT_COUNT				"LastReportCount" 
#define				CONFIG_STATION_LAST_USER_INDEX					"LastUserIndex" 
#define				CONFIG_STATION_LAST_UUT_SELECTED				"LastSelectedUUT" 
#define				CONFIG_STATION_DISABLE_EXPORT_REPORTS			"DisableExportReports"
#define				CONFIG_STATION_DISABLE_BUILDING_REPORTS			"DisableBuildingReports"
#define				CONFIG_STATION_DISABLE_AUTO_UPDATE				"DisableConfigurationAutoUpdate"   
#define				CONFIG_STATION_MAKE_REPORTS_AUTOMATICALLY		"MakeReportsAutomatically"
#define				CONFIG_STATION_MAKE_REPORTS_BY_STATUS_LEVEL		"MakeReportsByStatusLevel"
#define				CONFIG_STATION_DISABLE_REPORTS_AUTOMATICALLY	"DisableGenerateReportsAfterTest"
#define				CONFIG_STATION_BLOCK_TEST_REPORTS_GEN			"BlockStartTestWhileGeneratingReports"
#define				CONFIG_STATION_REPORT_FULL_PATH					"AutoReportFullPath"
#define				CONFIG_STATION_REPORT_PDF_FULL_PATH				"AutoReport_PDF_FullPath" 

#define				CONFIG_STATION_ALLOW_NUM_OF_REPORT_THREADS		"AllowedNumberOfReportThreads" 
#define				CONFIG_STATION_ALLOW_NUM_OF_REPORT_TEST_THREADS	"AllowedNumberOfTestThreads" 

#define				CONFIG_STATION_DEFAULT_UUT_INDEX				"DefaultUUT" 
#define				CONFIG_STATION_DEFAULT_VER_INDEX				"DefaultVersion" 

#define				CONFIG_USER_REPORT_ORDER						"ReportOrderDown"

#define				CONFIG_USER_POPUP_VARIABLES_STRING_EDITOR		"PopupVariablesStringEditor"

#define				CONFIG_UUT_LAST_VERSION_INDEX					"LastVersionIndex"

#define				CONFIG_UUT_VER_LAST_TESTS_SELECTED				"LastSelectedTests"

#define				CONFIG_UUT_VER_PRE_TEST_RUN						"RunPreTest" 
#define				CONFIG_UUT_VER_POST_TEST_RUN					"RunPostTest"

#define				CONFIG_UUT_VER_EN_SEL_PRE_TEST					"EnableSelPreTest" 
#define				CONFIG_UUT_VER_EN_SEL_POST_TEST					"EnableSelPostTest"

#define				CONFIG_UUT_VER_CALIB_NUMBER_OF_SLOTS			"CalibrationNumberOfSlotsToSelect"
#define				CONFIG_UUT_VER_MAX_NUMBER_OF_SLOTS				"MaxNumberOfSlotsToSelect"
#define				CONFIG_UUT_VER_SKIP_SERIAL_NUMBER				"SkipSerialNumber" 
#define				CONFIG_UUT_VER_AUTO_CONTINUE_SERIAL_NUMBER		"AutoContinueSerialNumber"
#define				CONFIG_UUT_VER_BREAK_ON_ERROR					"BreakAllTestsOnError" 
#define				CONFIG_UUT_VER_RUN_POST_TEST_ONCE				"RunPostTestOnce" 
#define				CONFIG_UUT_VER_RUN_PRE_TEST_ONCE				"RunPreTestOnce"  

#define				CONFIG_UUT_VER_RUN_POST_TEST_FIRST_ONCE			"RunPostTestFirstOnce" 
#define				CONFIG_UUT_VER_RUN_PRE_TEST_LAST_ONCE			"RunPreTestLastOnce" 
#define				CONFIG_UUT_VER_RUN_POST_TEST_ANY_WAY			"RunPostTestAnyWay"
#define				CONFIG_UUT_VER_RUN_SEQ_PATH_ORDER				"RunSequencyPathOriented"
#define				CONFIG_UUT_VER_EN_RETEST						"RunTestAgainOnFail"
#define				CONFIG_UUT_VER_SKIP_DEV_COM_REPIAT_CHECK		"SkipDeviceCommandRepeatCheck"
#define				CONFIG_UUT_VER_TEMP_VIBR_MEASURE_DEVICE			"TemperatureVibrationMeasureDevice"   

#define				CONFIG_UUT_VER_RUN_MULTI_THREAD					"RunMultiThread" 

#define				CONFIG_UUT_VER_DELAY_BETWEEN_START_SLOT			"DelayBetweenStartSlots"  

#define				CONFIG_UUT_VER_TESTS_PANELS_MOVEBLE				"Tests_Panels_Moveble"

#define				CONFIG_UUT_VER_RUN_ANY_WAY						"RunAnyWay"

#define				CONFIG_UUT_VER_REPORT_ONE_BASED_INDEX			"ReportsOneBasedTemperatureIndex"

#define				CONFIG_UUT_VER_DISABLE_CHECK_TEMP_TRIG			"DisableToCheckTemperatureTrigger"

#define				CONFIG_UUT_VER_TEMP_UPDATE_PERIOD				"TemperatureUpdatePeriod"
#define				CONFIG_UUT_VER_VIBR_UPDATE_PERIOD				"VibrationUpdatePeriod"
#define				CONFIG_UUT_VER_PROFILE_LOG_UPDATE_PERIOD		"ProfileLogUpdatePeriod"

#define				CONFIG_UUT_VER_TEMP_MODULE_ADDRESS				"TemperatureModuleDeviceAddress"  
#define				CONFIG_UUT_VER_TEMP_MODULE_LOCATION				"TemperatureModuleDriverLocation"
#define				CONFIG_UUT_VER_TEMP_MODULE_CONFIG_FILE			"TemperatureModuleConfigFile"
#define				CONFIG_UUT_VER_TEMP_MODULE_ID_NUMBER			"TemperatureModuleDriverIdNumber"  

#define				CONFIG_UUT_VER_STATUS_WINDOW_TIMEOUT			"StatusWindowTimeOut"

#define				CONFIG_UUT_VER_DEFAULT_TEMPERATURE				"DefaultTemperature"

#define				CONFIG_USER_POPUP_SN_REPEAT						"PopupWarningAtSerialNumberRepeat"
	
#define				CONFIG_USER_STOP_ON_TESTS_EVENTS_FOR_ALL		"TestStopEventsForAllTests"   

#define				CONFIG_USER_VIEW_TEST_TOTAL_TIME_ON_SUMM		"ViewTestTotalTimeOnSummery" 

#define				CONFIG_USER_VIEW_REPORT_LART_TYPE				"ViewReportLastType" 

#define				CONFIG_TEST_TRY_TO_START_TEST_WHILE_BUSY		"TryToStartTestWhileSlotBusy"

#define				CONFIG_TEST_DISABLE_CHECK_RESULT_QUANTITY		"DisableToCheckResultsQuantity" 

#define				CONFIG_TEST_REPORT_DISABLE_VIEW					"ReportDisableView" 

#define				CONFIG_TEST_STEPS_QUANTITY						"TestStepsQuantity"  

#define				CONFIG_TEST_CALIB_STEPS_QUANTITY				"CalibrationTestStepsQuantity"

#define				CONFIG_TEST_FORMATED_STEPS_QUANTITY				"Path_%d_TestStepsQuantity"  

#define				CONFIG_TEST_FORMATED_CALIB_STEPS_QUANTITY		"Path_%d_CalibrationTestStepsQuantity"

#define				CONFIG_TEST_FREQUENCY_DISABLE_LIST				"FrequencyLoopDisableList"

#define				CONFIG_USER_VIEW_REPORT_ATTACH_FILES			"ReportEnableViewAttachedFiles"

#define				CONFIG_UUT_VER_ERROR_WINDOW_TIMEOUT				"ErrorWindowTimeout"

#define				CONFIG_USER_RUN_ONLY_AUTO_SELECT				"UserCanRunAutoSelectionOnly"

#define				CONFIG_USER_RUN_IN_DEMO_MODE					"DEMO_MODE_Enable"

#define				CONFIG_USER_READY_TO_RUN_UUT					"UserReadyToRunUUT"

#define				CONFIG_USER_OPEN_SOURCE_REPORT_ONLY				"OpenSourceReportOnly"

#define				CONFIG_USER_DELETE_SOURCE_REPORT_ONLY			"DeleteSourceReportAfterGeneration"  

#define				CONFIG_USER_SELECT_AUTO_REPORT					"SelectAutoReport"

//the callbacks structure
typedef void (*clbGUI_StoreFile) (int handle , int mode, char filepath[]);  
typedef void (*clbGUI_Line_To_Window) (int handle , int mode, char msg[]);
typedef void (*clbGUI_Result) (int handle , int type,char* description,...);
typedef void (*clbGUI_Result_Const)( int handle , int iResultNumber , int type , char* description , ... );

typedef int  (*clbGUI_Instruction) (int handle ,int type, char *text, char *picture);
typedef int  (*clbGUI_Wait) (int handle ,char message[], double time_To_Wait);
typedef int  (*clbGUI_Timeout) ( int handle , char message[] , double lfTimeout , int bActivate );  

typedef int  (*clbUpdateExtraParameter) ( int handle , int index , char *szParameter ); 
typedef int  (*clbGetExtraParameter) ( int handle , int index , char *szParameter ); 

typedef int  (*clbGUI_Check_Events) ( int handle , STD_ERROR error );
typedef int  (*clbGUI_Check_Break) ( int handle );

typedef enum { RUN_STATUS_RUNNING , RUN_STATUS_PASS , RUN_STATUS_FAIL , RUN_STATUS_ABORT , RUN_STATUS_ERROR , RUN_STATUS_SENTINEL } teRunStatus;

#define		INSTR_TYPE_CONTINUE					0
#define		INSTR_TYPE_YES_NO					1

#define		VARTYPE_MEASURE_STORE				1
#define		VARTYPE_GLOBAL						2
#define		VARTYPE_UUT							3
#define		VARTYPE_UUTVER						4
#define		VARTYPE_TEST						5
#define		VARTYPE_USER						6
#define		VARTYPE_STATION						7
#define		VARTYPE_EQUIPMENT					8
#define		VARTYPE_EQUIPMENT_USE				9

#define		VARTYPE_CONFIG_OFFSET				10

#define		CLB_LINE_NORMAL        				0
#define		CLB_LINE_HEADER_1      				1
#define		CLB_LINE_HEADER_2      				2
#define		CLB_LINE_HEADER_3      				3
#define		CLB_LINE_HEADER_4      				4
#define		CLB_LINE_COM_HEADER     			5
#define		CLB_LINE_SYSTEM_HEADER  			6
#define		CLB_LINE_WARNING        			7
#define		CLB_LINE_INSTRUMENT     			8
#define		CLB_LINE_HEADER_TEST				9

#define		CLB_RESULT_DOUBLE					0
#define		CLB_RESULT_INT						1
#define		CLB_RESULT_STRING					2
#define		CLB_RESULT_PICTURE					3
#define		CLB_RESULT_GRAPH					4

#define		CLB_Normal            		 		0
#define		CLB_Print			  		 		1
#define		CLB_Type_Normal		  				2
#define		CLB_Type_High_Lim	  				3
#define		CLB_Type_Low_Lim	  				4
#define		CLB_Type_Both_Lim	  				5
	
#define		PATH_TYPE_CURRENT					0
#define		PATH_TYPE_INDEX						1
#define		PATH_TYPE_NAME						2
#define		PATH_TYPE_VALUE						3
		  
#define		CALIBRATION_SPEC_GROUP				999

#define		SPEC_ALLOW_TYPE_ENABLE				0
#define		SPEC_ALLOW_TYPE_DISABLE				1
#define		SPEC_ALLOW_TYPE_NO_COMPARE			2
#define		SPEC_ALLOW_TYPE_COMPARE_HIGH		3
#define		SPEC_ALLOW_TYPE_COMPARE_LOW			4

#define		EQUIPMENT_TYPE_STANDARD_DEVICE		1
#define		EQUIPMENT_TYPE_POWER_SUPPLY			2
#define		EQUIPMENT_TYPE_NETWORK_ANALYZER		3
#define		EQUIPMENT_TYPE_SIGNAL_GENERATOR		4
#define		EQUIPMENT_TYPE_SPECTRUM_ANALYZER	5
#define		EQUIPMENT_TYPE_OSCILLOSCOPE			6
#define		EQUIPMENT_TYPE_FUNCTION_GENERATOR	7
#define		EQUIPMENT_TYPE_POWER_METER			8
#define		EQUIPMENT_TYPE_NOISE_FIGURE			9
#define		EQUIPMENT_TYPE_MULTI_METER			10
#define		EQUIPMENT_TYPE_WAVE_FORM_ANALYZER	11

#define		STANDARD_DEVICE_RF_BOX_ALIAS		"rfbox"
#define		STANDARD_DEVICE_OVEN_ALIAS			"oven"
#define		STANDARD_DEVICE_UUT					"uut"

typedef int				(*clbGetVarInt)(int handle, int vartype, char *name , va_list arguments );
typedef double			(*clbGetVarDouble)(int handle, int vartype, char *name , va_list arguments );

typedef int 			(*clbGetVarIntArray)(int handle, int vartype, char *name,int** result , va_list arguments );
typedef int 			(*clbGetVarDoubleArray)(int handle, int vartype, char *name,double** result , va_list arguments );

typedef char*			(*clbGetVarString)(int handle, int vartype, char *name , va_list arguments );
typedef int				(*clbSetVarInt)(int handle, int vartype, char *name, int value  , va_list arguments );

typedef int				(*clbSetVarString)(int handle, int vartype, char *name , char *string  , va_list arguments );
typedef int	 			(*clbSetVarDouble)( int handle , int vartype, char *name , double value  , va_list arguments );  

typedef int				(*clbSetVarIntArray)( int handle, int vartype, char *name, int *pArrayValues , int Count  , va_list arguments );
typedef int	 			(*clbSetVarDoubleArray)( int handle, int vartype, char *name, double *pArrayValues , int Count  , va_list arguments );

typedef int				(*clbGetVarCalibration)( int handle, int vartype, int iRange , char *name , double **frequency , double **factor , int *piNumOfPoints , double *plfCalibrationDate  , va_list arguments );
typedef int				(*clbSetVarCalibration)( int handle, int vartype, int iRange , int bCleanBefore , char *name , double *frequency , double *factor , int iNumOfPoints , va_list arguments );

typedef int				(*clbGetVarCurrentCalibration)( int handle, int iRange , double **frequency , double **factor , int *piNumOfPoints , double *plfCalibrationDate  , va_list arguments );    
typedef int				(*clbSetVarCurrentCalibration)( int handle, int iRange , int bCleanBefore , double *frequency , double *factor , int iNumOfPoints , va_list arguments );

typedef int				(*clbGetVarCalibrationByName)( int handle, char *pszName , int iRange , double **frequency , double **factor , int *piNumOfPoints , double *plfCalibrationDate  , va_list arguments );

typedef int				(*clbSetVarStringArray)( int handle, int vartype, char *name , char **string  , int iNumberOfItems , va_list arguments );
typedef char** 			(*clbGetVarStringArray)( int handle, int vartype, char *name , int *pNumberOfItems , va_list arguments );

typedef int 			(*clbVarSetBuffer)( int handle , int vartype , unsigned long long linked , char* name, char* buffer, int count );

typedef int 			(*clbGetFullAtp) ( int handle );

typedef int 			(*clbGetSerialNumber) ( int handle , char *pszSerialNumber); 
typedef int 			(*clbUpdateSerialNumber) ( int handle , char *pszSerialNumber);
typedef int 			(*clbGetPartNumber) ( int handle , char *pszPartNumber);
typedef teRunStatus		(*clbGetRunStatus) ( int handle );
typedef int 			(*clbGetSlotNumber) ( int handle ); 

typedef int				(*clbGetTestLock) ( int handle ); 
typedef int				(*clbReleaseTestLock) ( int handle );
typedef int				(*clbTryToGetTestLock) ( int handle , int *status );
	
typedef int				(*clbGetInstructionLock)( int handle );
typedef int				(*clbReleaseInstructionLock)( int handle );
	
typedef int				(*clbSaveSlotVariable) ( int handle , int variable ); 
typedef int				(*clbLoadSlotVariable) ( int handle );
typedef int				(*clbGetNumberOfActiveSlots) ( int handle ); 
typedef int				(*clbGetNumberOfActiveTestThreads) ( int handle );
typedef int				(*clbDoThisTestNextTime) ( int handle ); 
	
typedef int				(*clbSaveGlobalVariable) ( int handle , int variable ); 
typedef int				(*clbLoadGlobalVariable) ( int handle );

typedef int				(*clbUpdateLastError) ( int handle , STD_ERROR ret );
typedef int				(*clbGetUpdatedLastError) ( int handle , STD_ERROR *pExRet ); 

typedef int				(*clbGetOperatorName)( int handle , char *pszName );
typedef int				(*clbGetUutVersionName)( int handle , char *pszName );
typedef int				(*clbGetUutName)( int handle , char *pszName );
	
typedef int				(*clbGetCurrentResultGraphItem)( int handle , int number , void **pItem );
typedef int				(*clbAddTraceToCurrentResultGraph)( int handle , int number , void *pItem , double *pTraceBuffer , unsigned int buffer_size , unsigned int startFromIndex , unsigned int numberOfPoints , double StartX , double StopX , char *szTraceName  , int color );

typedef int				(*clbBreakCurrentRunningSequence)( int handle );

typedef int				(*clbFillCallbacksDataStructure) ( int handle , void **pCallBackStructure );

typedef int				(*clbGetCurrentResultUnitsAcc)( int handle , int number , char *pUnits , double *plfAccuracy );
typedef int				(*clbGetCurrentResultMinMax)( int handle , int number , double **pMin , double **pMax , int *pCount , int *piFloatingType , double *plfFloatingValue );
typedef int				(*clbSetCurrentResultMinMax)( int handle , int iResultNumber , double *pMin , double *pMax , int iCount , double lfStartX );

typedef int				(*clbInterpolationTransfer)( int type , double *vlfXaxisArray , double *vlfYaxisArray , unsigned int numberOfPoints , unsigned int iNewNumberOfPoints  , double lfStartX , double lfStopX , double **vlfNewXaxisArray , double **vlfNewYaxisArray );  
typedef int				(*clbInterpolationPoint)( int type , double *vlfXaxisArray , double *vlfYaxisArray , unsigned int numberOfPoints , double lfXcoordinate , double *pYcoordinate );  

typedef int				(*clbExtrapolationPoint)( int type , double *vlfXaxisArray , double *vlfYaxisArray , unsigned int numberOfPoints , double lfXcoordinate , double *pYcoordinate );  

typedef int				(*clbEntryToSemaphoreSpace)( int handle , int bLockSpace );
typedef int				(*clbExitFromSemaphoreSpace)( int handle , int bReleaseSpace );

typedef int				(*clbPathGetLoss)( int handle , int iPathPartIndex , int bSingleValue ,  double lfXaxisValue , double **pYaxisData , ... ); 

typedef int				(*clbGetLastResultStatus)( int handle , int *piTestStatus );

typedef int				(*clbGetCurrentPathInfo)( int handle , int *piPathIndex , int *piPathPartIndex , char **pszPathName );

typedef int				(*clbGetTestReferenceFile_ByName)( int handle , char *pszFileName ); 

typedef int				(*clbGetCurrentTemperatureSegmentInfo) ( int handle , double *plfTemperature , int *piSegmentNumber , int *piSegmentLoopNumber );

typedef int				(*clbSetDirectCommandToPathModule) ( int handle , char *pCommand , char **pRespondsString );

typedef int				(*clbTemperatureModule_EnableExtremeMode) ( int handle , int bEnable );

typedef int				(*clbTemperatureModule_AddTemperatureRepair) ( int handle , double lfTemperatureDelta , double lfSlope );
typedef int				(*clbTemperatureModule_GetCurrentTemperature) ( int handle , double *plfCurrentTemperature );
typedef int				(*clbTemperatureModule_SetTemperature) ( int handle , double lfTemperature , double lfSlope );

typedef int				(*clbIsRunningModeOperational) ( int handle );  	
typedef int				(*clbIsRunningModeCalibration) ( int handle );

typedef int				(*clbGetCurrentPathFrequencyList) ( int handle , double **pFrequencyList , int **pPathRangesList , int *pNumberOfPoints , int *pNumberOfRanges );

typedef int				(*clbGetEquipmentHandle) ( int handle , int iType , char *pszAlias , int iNumber , int bAllowCreate , int *pEquipmentHandle );

typedef int				(*clbCloseEquipmentHandle) ( int handle , int hEquipmentHandle );

typedef int				(*clbGetCurrentResultDisbaleStatus) ( int handle , int iResultNumber ,int *piResultDisbaleStatus );

typedef int				(*clbGetCurrentTestInfo)( int handle , int *piTestIndex , char **pszTestName , char **pszTestPrefix );

typedef int				(*clbGetCurrentTestFrequencyInfo)( int handle , double *pFrequency , int *pSecured , int *pFrequencyIndex );
typedef int				(*clbGetConfiguredFrequenciesInfo)( int handle , double **pFrequencyList , int **pSecuredListInfo , int *pNumberOfPoints );

typedef int				(*clbGetTestInfoBy_TestEntryName)( int handle , char *pszTestEntryName , int *piTestIndex , char **pszTestName , char **pszTestPrefix );

typedef int				(*clbApplyDevicePathLoopCommands)( int handle , int hEquipmentHandle , int iPathIndex );

typedef int				(*clbApplyDeviceFrequencyLoopCommands)( int handle , int hEquipmentHandle , int iFrequencyIndex );

typedef int				(*clbIsLastPathCommandApplied)( int handle , int *pbStatus );

typedef int				(*clbApplyRfBoxPathConnectionCommands)( int handle , int iPathIndex , char *pszPathName );

typedef int				(*clbGetCurrentResultSpecType)( int handle , int iResultNumber ,int *piResultSpecType );

typedef int				(*clbWaitForLastLogDisplayed)( int handle ); 

typedef int				(*clbIsRunnningInDemoMode)( int handle );

typedef int				(*clbSynchronizeAllSlotsAtThisPoint)( int handle , int bFirstRunWait , int *pIamTheMaster );


typedef struct
{
	union
	{
		char												max_size[1024];
		
		struct
		{
			//===================================================================//
			int												handle; 	
			
			clbGUI_Line_To_Window 							Log;
			clbGUI_Result 									Result;
			clbGUI_Result_Const 							ResultConst;
			clbGUI_Instruction 								Instruction;
		    clbGUI_Check_Events 							Check_Events;

			clbGUI_Wait										Wait;
	
			clbGetFullAtp 									GetFullAtp;
			clbGetRunStatus 								GetRunStatus;
			clbGetSerialNumber 								GetSerialNumber;
			clbUpdateSerialNumber 							UpdateSerialNumber;
			clbGetPartNumber 								GetPartNumber;
			clbGetSlotNumber 								GetSlotNumber; 
	
			clbGetOperatorName 								GetOperatorName;
			clbGetUutVersionName 							GetUutVersionName;
			clbGetUutName 									GetUutName;
	
			clbGetTestLock 									GetTestLock;
			clbReleaseTestLock 								ReleaseTestLock;
			clbTryToGetTestLock 							TryToGetTestLock;
	
			clbSaveSlotVariable 							SaveSlotVariable; 
			clbLoadSlotVariable 							LoadSlotVariable;
	
			clbGetNumberOfActiveSlots 						GetNumberOfActiveSlots;
			clbDoThisTestNextTime 							DoThisTestNextTime;
	
			clbSaveGlobalVariable 							SaveGlobalVariable;
			clbLoadGlobalVariable 							LoadGlobalVariable;
		
			clbGUI_Timeout 									GUI_Timeout;
	
			clbUpdateExtraParameter 						UpdateExtraParameter;
			clbGetExtraParameter 							GetExtraParameter;
	
			clbGUI_Check_Break 								GUI_Check_Break;
	
			clbGetInstructionLock 							GetInstructionLock;
			clbReleaseInstructionLock 						ReleaseInstructionLock;
	
			clbUpdateLastError 								UpdateLastError;
			clbGetUpdatedLastError 							GetUpdatedLastError;
	
			clbGetCurrentResultGraphItem 					GetCurrentResultGraphItem;
			clbAddTraceToCurrentResultGraph		 			AddTraceToCurrentResultGraph;
	
			clbGetNumberOfActiveTestThreads		 			GetNumberOfActiveTestThreads;
	
			clbBreakCurrentRunningSequence 					BreakCurrentRunningSequence;
	
			clbFillCallbacksDataStructure 					FillCallbacksDataStructure;
	
			clbGetCurrentResultMinMax 						GetCurrentResultMinMax;
			
			clbInterpolationTransfer 						InterpolationTransfer;
			clbInterpolationPoint 							InterpolationPoint;
	
			clbGUI_StoreFile 								StoreFile;
	
			clbEntryToSemaphoreSpace 						EntryToSemaphoreSpace;
			clbExitFromSemaphoreSpace 						ExitFromSemaphoreSpace;
	
			clbPathGetLoss 									PathGetLoss;
			clbGetLastResultStatus 							GetLastResultStatus;
	
			clbGetCurrentPathInfo 							GetCurrentPathInfo;
	
			clbGetTestReferenceFile_ByName 					GetTestReferenceFile_ByName;
	
			clbGetCurrentTemperatureSegmentInfo 			GetCurrentTemperatureSegmentInfo;
	
			clbSetDirectCommandToPathModule					SetDirectCommandToPathModule;
	
			clbTemperatureModule_EnableExtremeMode			TemperatureModuleEnableExtremeMode;
	
			clbTemperatureModule_AddTemperatureRepair		TemperatureModuleAddTemperatureRepair;
			
			//============================ rev 4.0.0.0 =============================================//
			
			clbIsRunningModeOperational						IsRunningModeOperational;
			clbIsRunningModeCalibration						IsRunningModeCalibration;
			
			//============================ rev 4.2.1.0 =============================================//
			
			clbGetCurrentPathFrequencyList					GetCurrentPathFrequencyList;

			//============================ rev 4.4.0.0 =============================================//
			
			clbGetEquipmentHandle							GetEquipmentHandle; 
			
			//============================ rev 4.4.1.0 =============================================//
			clbVarSetBuffer									VarSetBuffer;

			//============================ rev 4.4.2.0 =============================================//
			clbGetCurrentResultDisbaleStatus				GetCurrentResultDisbaleStatus;	 
			
			//============================ rev 4.4.5.0 =============================================//
			
			HINSTANCE										hDriverManagerLibrary;
			
			//============================ rev 4.5.2.0 =============================================//
			clbGetCurrentTestInfo							GetCurrentTestInfo;
			
			//============================ rev 4.6.4.0 =============================================//
			clbGetCurrentTestFrequencyInfo					GetCurrentTestFrequencyInfo;
			clbGetConfiguredFrequenciesInfo					GetConfiguredFrequenciesInfo;
			
			//============================ rev 4.6.7.0 =============================================//
			clbGetTestInfoBy_TestEntryName					GetTestInfoBy_TestEntryName;

			//============================ rev 4.6.12.0 =============================================//
			clbApplyDevicePathLoopCommands					ApplyDevicePathLoopCommands;
			clbApplyDeviceFrequencyLoopCommands				ApplyDeviceFrequencyLoopCommands; 
		
			//============================ rev 4.6.20.0 =============================================//
			clbIsLastPathCommandApplied						IsLastPathCommandApplied;
			
			//============================ rev 4.9.3.0 =============================================//
			clbApplyRfBoxPathConnectionCommands				ApplyRfBoxPathConnectionCommands;

			//============================ rev 5.0.0.0 =============================================//
			clbGetVarInt						  			GetVarInt;
			clbGetVarIntArray						  		GetVarIntArray;
			clbGetVarDouble	 					  			GetVarDouble;
			clbGetVarDoubleArray						  	GetVarDoubleArray;
			clbGetVarString					  				GetVarString;
			clbGetVarStringArray							GetVarStringArray;
			clbSetVarString						  			SetVarString;
			clbSetVarStringArray						  	SetVarStringArray;
			clbSetVarInt						  			SetVarInt;
			clbSetVarIntArray						  		SetVarIntArray;
			clbSetVarDouble						  			SetVarDouble;
			clbSetVarDoubleArray						  	SetVarDoubleArray;
			clbSetVarCalibration						  	SetVarCalibration;
			clbGetVarCalibration						  	GetVarCalibration;
			clbSetVarCurrentCalibration						SetVarCurrentCalibration;
			clbGetVarCurrentCalibration						GetVarCurrentCalibration;
			clbGetVarCalibrationByName						GetVarCalibrationByName;
			
			//============================ rev 5.0.3.0 =============================================//
			clbExtrapolationPoint							ExtrapolationPoint;

			//============================ rev 5.0.6.0 =============================================//
			clbGetCurrentResultUnitsAcc						GetCurrentResultUnitsAcc;

			//============================ rev 5.1.2.0 =============================================//
			clbGetCurrentResultSpecType						GetCurrentResultSpecType;

			//============================ rev 5.1.17.0 =============================================//
			clbWaitForLastLogDisplayed						WaitForLastLogDisplayed;

			//============================ rev 5.1.20.0 =============================================//
			clbTemperatureModule_GetCurrentTemperature		TemperatureModule_GetCurrentTemperature;
			clbTemperatureModule_SetTemperature				TemperatureModule_SetTemperature;
			
			//============================ rev 5.1.28.0 =============================================//
			clbIsRunnningInDemoMode							IsRunnningInDemoMode;
			
			//============================ rev 5.5.2.0 =============================================//
			clbCloseEquipmentHandle							CloseEquipmentHandle;

			//============================ rev 5.6.6.0 =============================================//
			clbSynchronizeAllSlotsAtThisPoint				SynchronizeAllSlotsAtThisPoint; 

			//============================ rev 5.7.0.0 =============================================//
			clbSetCurrentResultMinMax						SetCurrentResultMinMax;
		};
	};
	
} sClb;



#endif
