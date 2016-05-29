#ifndef	_COMMON_H_
#define _COMMON_H_

#include <clb.h>

int		GetVarInt(sClb* clb, int vartype, char *name , ... );
double	GetVarDouble(sClb* clb, int vartype, char *name , ... );

//make sure you FREE the result array after use!!!!!!
int 	GetVarIntArray(sClb* clb, int vartype, char *name,int** result , ... );
int 	GetVarDoubleArray(sClb* clb, int vartype, char *name,double** result , ... );

//Make sure you FREE the string after use!!!!!
char*	GetVarString(sClb* clb, int vartype, char *name , ... );
int		SetVarInt(sClb* clb, int vartype, char *name, int value  , ... );

int		SetVarString(sClb* clb, int vartype, char *name , char *string  , ... );
int	 	SetVarDouble( sClb* clb , int vartype, char *name , double value  , ... );  

int		SetVarIntArray( sClb* clb, int vartype, char *name, int *pArrayValues , int Count  , ... );
int	 	SetVarDoubleArray( sClb* clb, int vartype, char *name, double *pArrayValues , int Count  , ... );

int		GetVarCalibration( sClb* clb, int vartype, int iRange , char *name , double **frequency , double **factor , int *piNumOfPoints , double *plfCalibrationDate  , ... );
int		SetVarCalibration( sClb* clb, int vartype, int iRange , int bCleanBefore , char *name , double *frequency , double *factor , int iNumOfPoints , ... );

int		GetVarCurrentCalibration( sClb* clb, int iRange , double **frequency , double **factor , int *piNumOfPoints , double *plfCalibrationDate  , ... );    
int		SetVarCurrentCalibration( sClb* clb, int iRange , int bCleanBefore , double *frequency , double *factor , int iNumOfPoints , ... );

int		GetVarCalibrationByName( sClb* clb, char *pszName , int iRange , double **frequency , double **factor , int *piNumOfPoints , double *plfCalibrationDate  , ... );

int		SetVarStringArray( sClb* clb, int vartype, char *name , char **string  , int iNumberOfItems , ... );
char** 	GetVarStringArray( sClb* clb, int vartype, char *name , int *pNumberOfItems , ... );

//Emulation of the TRY/EXCEPT system
#define 		W_SUCCEED 					0

#define 		TRY(action)																																										{if(W_SUCCEED!= (action))return W_FAILED;}

#define			INSTR_TYPE_CONTINUE			0
#define			INSTR_TYPE_YES_NO			1

//If 0, ok. Else, show error screen and abort test if user chose so.
#define W_TRY(action)																																									{if(W_SUCCEED!= clb->Step(0,(int)(action),__FILE__,__LINE__,#action)){goto catch;}}
//If 0, ok. Do not show the error screen.
#define WD_TRY(action)																																									{if(W_SUCCEED!= clb->Step(4,(int)(action),__FILE__,__LINE__,#action)){goto catch;}}
//Same as W_TRY. If 0, Error.
#define N_TRY(action)																																									{if(!clb->Step(1,(int)(action),__FILE__,__LINE__,#action)){goto catch;}}
#define CHAR_N_TRY(action)																																								{if(!clb->Step(1,(char)(action),__FILE__,__LINE__,#action)){goto catch;}}
#define STEP(action)																																									clb->Step(0,(int)(action),__FILE__,__LINE__,#action)
#define STEP1(action)																																									clb->Step(0,(action),__FILE__,__LINE__,#action))
#define FINALIZE																																										goto finally;
#define CATCH																																											goto finally;Error:
#define FINALLY																																											finally:

#define CFREE(x)																																										{if(x) free(x);x=0;}
//Helper functions

//Use this to declare a test fucntion
#define TSTE_TEST(name)																																									int DLLEXPORT name(sClb* clb)

//Log a line to the execution window
#define LOG(mode,test)																																									{ clb->Log(clb->handle,mode,test); if ( clb->Check_Events(clb->handle,StdError)) {FINALIZE;}}
#define LOG_END(mode,test)																																								clb->Log(clb->handle,mode,test); 

#define WAIT(msg, time)																																									{ clb->Wait(clb->handle,msg,time);if ( clb->Check_Events(clb->handle,StdError)) {FINALIZE;}} 

#define EVENTS																																											clb->Check_Events(clb->handle,StdError)

//Report a result
#define RESULT(type,desc,res,defdesc)																																					{clb->Result(clb->handle,type, desc,res,defdesc); } 
#define RESULT_CONST(type,desc,res,defdesc)																																				{clb->ResultConst(clb->handle,-1,type, desc,res,defdesc); } 
#define RESULT_CONST_NUM(number,type,desc,res,defdesc)																																	{clb->ResultConst(clb->handle,number,type, desc,res,defdesc); } 

#define RESULT_END(type,desc,res,defdesc)																																				{clb->Result(clb->handle,type, desc,res,defdesc);} 
#define RESULT_CONST_END(type,desc,res,defdesc)																																			{clb->ResultConst(clb->handle,-1,type, desc,res,defdesc);} 
#define RESULT_CONST_NUM_END(number,type,desc,res,defdesc)																																{clb->ResultConst(clb->handle,number,type, desc,res,defdesc);} 

#define MRESULT(unit,type,desc,res,defdesc)																																				clb->Result(clb->handle,type, desc,res,defdesc); 

//Show the user an instruction
#define INSTRUCTION(text,picture)																																						clb->Instruction(clb->handle,INSTR_TYPE_CONTINUE,text,picture); if ( clb->Check_Events(clb->handle,StdError)) {FINALIZE;}  

//Ask for user confirmation
#define CONFIRM(text,picture)																																							clb->Instruction(clb->handle,INSTR_TYPE_YES_NO,text,picture);  if ( clb->Check_Events(clb->handle,StdError)) {FINALIZE;}  

#define INSTRUCTION_END(text,picture)																																					clb->Instruction(clb->handle,INSTR_TYPE_CONTINUE,text,picture); 

//Ask for user confirmation
#define CONFIRM_END(text,picture)																																						clb->Instruction(clb->handle,INSTR_TYPE_YES_NO,text,picture);  

#define GET_SERIAL_NUMBER(xxSerialNumber)																																				clb->GetSerialNumber(clb->handle,xxSerialNumber);
#define SET_SERIAL_NUMBER(xxSerialNumber)																																				clb->UpdateSerialNumber(clb->handle,xxSerialNumber);
#define GET_PART_NUMBER(xxPartNumber)																																					clb->GetPartNumber(clb->handle,xxPartNumber); 
#define GET_SLOT_NUMBER(xxSlotNumber)																																					xxSlotNumber = clb->GetSlotNumber(clb->handle);  

#define GET_OPERATOR_NAME(xxName)																																						clb->GetOperatorName(clb->handle,xxName);
#define GET_UUT_VER_NAME(xxName)																																						clb->GetUutVersionName(clb->handle,xxName); 
#define GET_UUT_NAME(xxName)																																							clb->GetUutName(clb->handle,xxName); 

#define GET_TEST_PREFIX(xxpPrefix)																																						clb->GetCurrentTestInfo(clb->handle,NULL,NULL,&xxpPrefix);
#define GET_TEST_NAME(xxpTestName)																																						clb->GetCurrentTestInfo(clb->handle,NULL,&xxpTestName,NULL);

#define GET_TEST_PREFIX_BY_ENTRY_NAME(xxEntryName,xxpPrefix)																															clb->GetTestInfoBy_TestEntryName(clb->handle,xxEntryName,NULL,NULL,&xxpPrefix);

#define GET_TEST_LOCK 																																									{ do { StdError.error = clb->GetTestLock(clb->handle); } while ( StdError.error ); }
#define RELEASE_TEST_LOCK 																																								{ StdError.error = clb->ReleaseTestLock(clb->handle);  }
#define TRY_GET_TEST_LOCK_ERROR 																																						{ int xxStatus = 0; StdError.error = clb->TryToGetTestLock(clb->handle,&xxStatus); if ( StdError.error ) goto Error; if ( xxStatus == 0 ) goto Error;}

#define ENTRY_TO_MAIN_SEMAPHORE_SPACE																																					{ clb->EntryToSemaphoreSpace(clb->handle,1); bGetMainSemaphoreLock = 1; }
#define EXIT_FROM_MAIN_SEMAPHORE_SPACE																																					{ if ( bGetMainSemaphoreLock ) { clb->ExitFromSemaphoreSpace(clb->handle,1); bGetMainSemaphoreLock = 0; }}
#define ENTRY_TO_SUB_SEMAPHORE_SPACE																																					{ clb->EntryToSemaphoreSpace(clb->handle,0); bGetSubSemaphoreLock = 1; }   
#define EXIT_FROM_SUB_SEMAPHORE_SPACE																																					{ if ( bGetSubSemaphoreLock ) { clb->ExitFromSemaphoreSpace(clb->handle,0); bGetSubSemaphoreLock = 0; }}	
	
#define SAVE_SLOT_VARIABLE(xxSlotVariable)																																				clb->SaveSlotVariable(clb->handle,xxSlotVariable); 
#define LOAD_SLOT_VARIABLE(xxSlotVariable)																																				xxSlotVariable = clb->LoadSlotVariable(clb->handle);  
	
#define GET_FULL_ATP(xxFullAtp)																																							{xxFullAtp=clb->GetFullAtp(clb->handle);}
#define GET_RUN_STATUS(xxRunStatus)																																						{xxRunStatus=clb->GetRunStatus(clb->handle);}   

#define GET_ACT_SLOTS_NUM(xxActSlotsNumber)																																				xxActSlotsNumber = clb->GetNumberOfActiveSlots(clb->handle);   
#define GET_ACT_TEST_THREADS_NUM(xxActTestThreadsNumber)																																xxActTestThreadsNumber = clb->GetNumberOfActiveTestThreads(clb->handle);   

#define DO_THIS_TEST_NEXT_TIME																																							clb->DoThisTestNextTime(clb->handle); 
#define BREAK_CURRENT_SEQUENCE																																							{ clb->BreakCurrentRunningSequence(clb->handle); FINALIZE }
	
#define SAVE_GLOBAL_VARIABLE(xxGlobalVariable) 																																			clb->SaveGlobalVariable(clb->handle,xxGlobalVariable); 
#define LOAD_GLOBAL_VARIABLE(xxGlobalVariable) 																																			xxGlobalVariable = clb->LoadGlobalVariable(clb->handle);  

#define SET_EXTRA_PARAMETER(xxIndex,xxStringParam)																																		clb->UpdateExtraParameter ( clb->handle , xxIndex , xxStringParam ); 
#define GET_EXTRA_PARAMETER(xxIndex,xxStringParam)																																		clb->GetExtraParameter ( clb->handle , xxIndex , xxStringParam ); 

#define START_TIMEOUT(msg, time)																																						clb->GUI_Timeout( clb->handle , msg , time , 1 ); 
#define STOP_TIMEOUT																																									clb->GUI_Timeout( clb->handle , "" , 0.0 , 0 ); 

#define	CHECK_BREAK																																										{ if ( clb->GUI_Check_Break(clb->handle)) {FINALIZE}}

#define GET_INSTRUCTION_LOCK 																																							{ do { StdError.error = clb->GetInstructionLock(clb->handle); } while ( StdError.error ); }  
#define RELEASE_INSTRUCTION_LOCK 																																						{ StdError.error = clb->ReleaseInstructionLock(clb->handle);  }  

#define UPDATE_ERROR(xxRet)																																								clb->UpdateLastError( clb->handle , xxRet ); 
#define GET_LAST_ERROR(xxRet)																																							clb->GetUpdatedLastError( clb->handle , &xxRet ); 
	
#define GET_CURRENT_RESULT_GRAPH_ITEM(xxGraphItem)																																		clb->GetCurrentResultGraphItem( clb->handle , -1 , &xxGraphItem );
#define GET_RESULT_GRAPH_ITEM(xxNumber,xxGraphItem)																																		clb->GetCurrentResultGraphItem( clb->handle , xxNumber , &xxGraphItem );

#define ADD_TRACE_TO_CURRENT_RESULT_GRAPH(xxGraphItem,xxTraceBuffer,xxBuffer_size,xxStartFromIndex,xxNumberOfPoints,xxStartX,xxStopX,xxTraceName,xxColor)								clb->AddTraceToCurrentResultGraph( clb->handle , -1 , xxGraphItem , xxTraceBuffer , xxBuffer_size , xxStartFromIndex , xxNumberOfPoints , xxStartX , xxStopX , xxTraceName  , xxColor );
#define ADD_TRACE_TO_RESULT_GRAPH(xxNumber,xxGraphItem,xxTraceBuffer,xxBuffer_size,xxStartFromIndex,xxNumberOfPoints,xxStartX,xxStopX,xxTraceName,xxColor)								clb->AddTraceToCurrentResultGraph( clb->handle , xxNumber , xxGraphItem , xxTraceBuffer , xxBuffer_size , xxStartFromIndex , xxNumberOfPoints , xxStartX , xxStopX , xxTraceName  , xxColor );

#define FILL_TE_CALLBACK_STRUCTURE( xxxCallBackStructure )																																clb->FillCallbacksDataStructure( clb->handle , &xxxCallBackStructure );

#define GET_SPECS_UNITS_ACC(xxxUnitsString,xxxAccuracyFormatDouble)																														clb->GetCurrentResultUnitsAcc( clb->handle , 0 , xxxUnitsString , &xxxAccuracyFormatDouble );
#define GET_MAX_MIN_SPECS(xxxPointerToMinSpec,xxxPointerToMaxSpec,xxxSpecValuesCount,xxxSpecFloatType,xxxSpecFloatValue)																clb->GetCurrentResultMinMax( clb->handle , 0 , &xxxPointerToMinSpec , &xxxPointerToMaxSpec , &xxxSpecValuesCount , &xxxSpecFloatType , &xxxSpecFloatValue );
#define GET_SPECS_VALUE_COUNT(xxxSpecValuesCount)																																		clb->GetCurrentResultMinMax( clb->handle , 0 , NULL , NULL , &xxxSpecValuesCount , NULL , NULL );

#define GET_SPECS_UNITS_ACC_NUMBER(number,xxxUnitsString,xxxAccuracyFormatDouble)																										clb->GetCurrentResultUnitsAcc( clb->handle , number , xxxUnitsString , &xxxAccuracyFormatDouble );
#define GET_MAX_MIN_SPECS_NUMBER(number,xxxPointerToMinSpec,xxxPointerToMaxSpec,xxxSpecValuesCount,xxxSpecFloatType,xxxSpecFloatValue)													clb->GetCurrentResultMinMax( clb->handle , number , &xxxPointerToMinSpec , &xxxPointerToMaxSpec , &xxxSpecValuesCount , &xxxSpecFloatType , &xxxSpecFloatValue );
#define GET_SPECS_VALUE_COUNT_NUMBER(number,xxxSpecValuesCount)																															clb->GetCurrentResultMinMax( clb->handle , number , NULL , NULL , &xxxSpecValuesCount , NULL , NULL );

#define GET_MAX_SPECS(xxxPointerToMaxSpec)																																				clb->GetCurrentResultMinMax( clb->handle , 0 , NULL , &xxxPointerToMaxSpec , NULL , NULL , NULL );
#define GET_MIN_SPECS(xxxPointerToMinSpec)																																				clb->GetCurrentResultMinMax( clb->handle , 0 , &xxxPointerToMinSpec , NULL , NULL , NULL , NULL );

#define GET_MAX_SPECS_NUMBER(xxNumber,xxxPointerToMaxSpec)																																clb->GetCurrentResultMinMax( clb->handle , xxNumber , NULL , &xxxPointerToMaxSpec , NULL , NULL , NULL );
#define GET_MIN_SPECS_NUMBER(xxNumber,xxxPointerToMinSpec)																																clb->GetCurrentResultMinMax( clb->handle , xxNumber , &xxxPointerToMinSpec , NULL , NULL , NULL , NULL );
									  
#define GET_RESULT_DISABLE_STATUS(number,xxxStatus)																																		clb->GetCurrentResultDisbaleStatus( clb->handle , number , &xxxStatus );
#define GET_CURRENT_RESULT_DISABLE_STATUS(xxxStatus)																																	clb->GetCurrentResultDisbaleStatus( clb->handle , 0 , &xxxStatus );

#define GET_RESULT_SPEC_TYPE(number,xxxSpecType)																																		clb->GetCurrentResultSpecType( clb->handle , number , &xxxSpecType );
#define GET_CURRENT_RESULT_SPEC_TYPE(xxxSpecType)																																		clb->GetCurrentResultSpecType( clb->handle , 0 , &xxxSpecType );


//#define SET_MAX_MIN_SPECS(xxxPointerToMinSpec,xxxPointerToMaxSpec,xxxSpecValuesCount,xxxSpecFloatType,xxxSpecFloatValue)																clb->SetCurrentResultMinMax( clb->handle , &xxxPointerToMinSpec , &xxxPointerToMaxSpec , &xxxSpecValuesCount , &xxxSpecFloatType , &xxxSpecFloatValue );     

#define APPLY_LINEAR_INTERPOLATION( xxxXaxisArray , xxxYaxisArray , xxxNumberOfPoints , xxxNewNumberOfPoints  , xxxStartX , xxxStopX , xxxNewXaxisArray , xxxNewYaxisArray )			clb->InterpolationTransfer( 0 , xxxXaxisArray , xxxYaxisArray , xxxNumberOfPoints , xxxNewNumberOfPoints  , xxxStartX , xxxStopX , &xxxNewXaxisArray , &xxxNewYaxisArray );  
#define APPLY_NON_LINEAR_INTERPOLATION( xxxXaxisArray , xxxYaxisArray , xxxNumberOfPoints , xxxNewNumberOfPoints  , xxxStartX , xxxStopX , xxxNewXaxisArray , xxxNewYaxisArray )		clb->InterpolationTransfer( 3 , xxxXaxisArray , xxxYaxisArray , xxxNumberOfPoints , xxxNewNumberOfPoints  , xxxStartX , xxxStopX , &xxxNewXaxisArray , &xxxNewYaxisArray );  

#define GET_POINT_LINEAR_INTERPOLATION( xxxXaxisArray , xxxYaxisArray , xxxNumberOfPoints , xxxXcoordinate , xxxYcoordinate )															clb->InterpolationPoint( 0 , xxxXaxisArray , xxxYaxisArray , xxxNumberOfPoints , xxxXcoordinate , &xxxYcoordinate );  
#define GET_POINT_NON_LINEAR_INTERPOLATION( xxxXaxisArray , xxxYaxisArray , xxxNumberOfPoints , xxxXcoordinate , xxxYcoordinate )														clb->InterpolationPoint( 3 , xxxXaxisArray , xxxYaxisArray , xxxNumberOfPoints , xxxXcoordinate , &xxxYcoordinate );  

#define GET_POINT_EXTRAPOLATION( xxxXaxisArray , xxxYaxisArray , xxxNumberOfPoints , xxxXcoordinate , xxxYcoordinate )																	clb->ExtrapolationPoint( 0 , xxxXaxisArray , xxxYaxisArray , xxxNumberOfPoints , xxxXcoordinate , &xxxYcoordinate );  

#define GET_POINT_LINEAR_EXTRAPOLATION( xxxXaxisArray , xxxYaxisArray , xxxNumberOfPoints , xxxXcoordinate , xxxYcoordinate )																	clb->ExtrapolationPoint( 1 , xxxXaxisArray , xxxYaxisArray , xxxNumberOfPoints , xxxXcoordinate , &xxxYcoordinate );  

#define STORE_FILE(xxxFileFullPath)																																						clb->StoreFile(clb->handle,0,xxxFileFullPath); 

#define PATH_GET_LOSS_VALUE(xxFrequency,xxLossValue)																																	{ double *xxReturnValue=NULL; StdError.error = clb->PathGetLoss( clb->handle , 0 , 1 , xxFrequency , &xxReturnValue ); if ( xxReturnValue ) { xxLossValue = *xxReturnValue; free(xxReturnValue); } if ( IS_NOT_OK ) { strcpy(StdError.pszErrorDescription , "Error get loss factor" ); goto Error; }}
#define PATH_PART_GET_LOSS_VALUE(xxPartIndex , xxFrequency,xxLossValue)																													{ double *xxReturnValue=NULL; StdError.error = clb->PathGetLoss( clb->handle , xxPartIndex , 1 , xxFrequency , &xxReturnValue ); if ( xxReturnValue ) { xxLossValue = *xxReturnValue; free(xxReturnValue); } if ( IS_NOT_OK ) { strcpy(StdError.pszErrorDescription , "Error get loss factor" ); goto Error; }}  

#define PATH_GET_CURRENT_INDEX(xxIndex)																																					{ StdError.error = clb->GetCurrentPathInfo( clb->handle , &xxIndex , NULL  , NULL ); if ( IS_NOT_OK ) { strcpy(StdError.pszErrorDescription , "Error get path index" ); goto Error; }}  

#define PATH_PART_GET_CURRENT_INDEX(xxIndex)																																			{ StdError.error = clb->GetCurrentPathInfo( clb->handle , NULL , &xxIndex , NULL ); if ( IS_NOT_OK ) { strcpy(StdError.pszErrorDescription , "Error get path index" ); goto Error; }}

#define PATH_GET_CURRENT_PATH_NAME(xxpPathName)																																			{ StdError.error = clb->GetCurrentPathInfo( clb->handle , NULL , NULL , &xxpPathName ); if ( IS_NOT_OK ) { strcpy(StdError.pszErrorDescription , "Error get path index" ); goto Error; }}  

#define PATH_GET_CURRENT_FREQUENCY_LIST(xxFrequencyList,xxRangesList,xxNumberOfPoints,xxNumberOfRanges) 																				clb->GetCurrentPathFrequencyList ( clb->handle , &xxFrequencyList , &xxRangesList , &xxNumberOfPoints , &xxNumberOfRanges ); 

#define WAIT_LAST_RESULT_STATUS(xxStatus)																																				clb->GetLastResultStatus(clb->handle, &xxStatus);

#define WAIT_LAST_LOG_DISPLAYED																																							clb->WaitForLastLogDisplayed(clb->handle);

#define UPDATE_LOCAL_TEST_FILE(xxFileName)																																				{ StdError.error = clb->GetTestReferenceFile_ByName(clb->handle, xxFileName);  if ( IS_NOT_OK ) { sprintf(StdError.pszErrorDescription , "File \"%s\" is not found in database" , xxFileName ); goto Error; }}  

#define GET_SEGMENT_TEMPERATURE(xxTemp)																																					clb->GetCurrentTemperatureSegmentInfo ( clb->handle , &xxTemp , NULL , NULL );
#define GET_SEGMENT_LOOP_NUM(xxNumber)																																					clb->GetCurrentTemperatureSegmentInfo ( clb->handle , NULL , NULL , &xxNumber );   
#define GET_SEGMENT_NUMBER(xxNumber)																																					clb->GetCurrentTemperatureSegmentInfo ( clb->handle , NULL , &xxNumber , NULL );   

#define PATH_MODULE_SET_DIRECT_COMMAND(xxString)																																		clb->SetDirectCommandToPathModule ( clb->handle , xxString , NULL );
#define PATH_MODULE_QUERY_DIRECT_COMMAND(xxSendString,xxRespondsPointer)																												clb->SetDirectCommandToPathModule ( clb->handle , xxSendString , &xxRespondsPointer );

#define OVEN_MODULE_ENABLE_EXTREME_MODE																																					clb->TemperatureModuleEnableExtremeMode ( clb->handle , 1 );
#define OVEN_MODULE_DISABLE_EXTREME_MODE																																				clb->TemperatureModuleEnableExtremeMode ( clb->handle , 0 );

#define OVEN_MODULE_REPAIR_TEMPERATURE(xxTemperatureDelta)																																clb->TemperatureModuleAddTemperatureRepair( clb->handle , xxTemperatureDelta , 0.0 );  
#define OVEN_MODULE_GET_TEMPERATURE(xxTemperature)																																		clb->TemperatureModule_GetCurrentTemperature( clb->handle , &xxTemperature );  
#define OVEN_MODULE_SET_TEMPERATURE(xxTemperature,xxSlope)																																clb->TemperatureModule_SetTemperature( clb->handle , xxTemperature , xxSlope );  

#define IS_CURRENT_RUN_MODE_CALIBRATION																																					( clb->IsRunningModeCalibration( clb->handle ) > 0 )  	// use for if conditions
#define IS_CURRENT_RUN_MODE_OPERATIONAL																																					( clb->IsRunningModeOperational( clb->handle ) > 0 )  	// use for if conditions
#define IS_CURRENT_RUN_MODE_SIMULATION																																					( clb->IsRunnningInDemoMode( clb->handle ) > 0 )  	// use for if conditions

#define GET_LAST_PATH_COMMAND_APPLIED_STATUS( xxStatus )																																{ clb->IsLastPathCommandApplied( clb->handle , &xxStatus );}

#define	GET_FREQUENCIES_LOOP_INFO_LIST(xxpFrequencyList,xxpSecuredListInfo,xxiNumberOfPoints)																							{ clb->GetConfiguredFrequenciesInfo( clb->handle , &xxpFrequencyList , &xxpSecuredListInfo , &xxiNumberOfPoints ); }
#define	GET_FREQUENCIES_LOOP_INFO_SINGLE(xxpFrequency,xxpSecured,xxiFrequencyIndex)																										{ clb->GetCurrentTestFrequencyInfo( clb->handle , &xxpFrequency , &xxpSecured , &xxiFrequencyIndex ); }

#define APPLY_DEVICE_PATH_COMMAND_BY_INDEX( xxEquipmentHandle , xxPathIndex )																											{ clb->ApplyDevicePathLoopCommands ( clb->handle , xxEquipmentHandle , xxPathIndex ); } 

#define APPLY_RF_BOX_CURRENT_TEST_PATH																																					{ clb->ApplyRfBoxPathConnectionCommands ( clb->handle , -1 , NULL ); }
#define APPLY_RF_BOX_TEST_PATH_BY_INDEX( xxPathIndex )																																	{ clb->ApplyRfBoxPathConnectionCommands ( clb->handle , xxPathIndex , NULL ); }
#define APPLY_RF_BOX_PATH_BY_NAME( xxPathName )																																			{ clb->ApplyRfBoxPathConnectionCommands ( clb->handle , -1 , xxPathName ); } 

//----------------------------------------------- Get Equipment handles single -----------------------------------------------------//
#define GET_UUT_EQUIPMENT_HANDLE(xxHandle)																																				clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_STANDARD_DEVICE , STANDARD_DEVICE_UUT , 0 , 1 , &xxHandle );  
#define GET_RFBOX_EQUIPMENT_HANDLE(xxHandle)																																			clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_STANDARD_DEVICE , STANDARD_DEVICE_RF_BOX_ALIAS , 0 , 1 , &xxHandle );  
#define GET_DEV_EQUIPMENT_HANDLE(xxHandle)																																				clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_STANDARD_DEVICE , NULL , 0 , 1 , &xxHandle );  
#define GET_PS_EQUIPMENT_HANDLE(xxHandle)																																				clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_POWER_SUPPLY , NULL , 0 , 1 , &xxHandle );		
#define GET_NA_EQUIPMENT_HANDLE(xxHandle)																																				clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_NETWORK_ANALYZER , NULL , 0 , 1 , &xxHandle );	
#define GET_SG_EQUIPMENT_HANDLE(xxHandle)																																				clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_SIGNAL_GENERATOR , NULL , 0 , 1 , &xxHandle );	
#define GET_SA_EQUIPMENT_HANDLE(xxHandle)																																				clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_SPECTRUM_ANALYZER , NULL , 0 , 1 , &xxHandle );
#define GET_SC_EQUIPMENT_HANDLE(xxHandle)																																				clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_OSCILLOSCOPE , NULL , 0 , 1 , &xxHandle );		
#define GET_FG_EQUIPMENT_HANDLE(xxHandle)																																				clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_FUNCTION_GENERATOR , NULL , 0 , 1 , &xxHandle );
#define GET_PM_EQUIPMENT_HANDLE(xxHandle)																																				clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_POWER_METER , NULL , 0 , 1 , &xxHandle );		
#define GET_NF_EQUIPMENT_HANDLE(xxHandle)																																				clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_NOISE_FIGURE , NULL , 0 , 1 , &xxHandle );		
#define GET_MM_EQUIPMENT_HANDLE(xxHandle)																																				clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_MULTI_METER , NULL , 0 , 1 , &xxHandle );		
#define GET_WA_EQUIPMENT_HANDLE(xxHandle)																																				clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_WAVE_FORM_ANALYZER , NULL , 0 , 1 , &xxHandle );

//----------------------------------------------- Get Equipment handles single -----------------------------------------------------//
#define GET_UUT_EQUIPMENT_HANDLE_IF_EXISTS(xxHandle)																																	clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_STANDARD_DEVICE , STANDARD_DEVICE_UUT , 0 , 0 , &xxHandle );  
#define GET_RFBOX_EQUIPMENT_HANDLE_IF_EXISTS(xxHandle)																																	clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_STANDARD_DEVICE , STANDARD_DEVICE_RF_BOX_ALIAS , 0 , 0 , &xxHandle );  
#define GET_DEV_EQUIPMENT_HANDLE_IF_EXISTS(xxHandle)																																	clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_STANDARD_DEVICE , NULL , 0 , 0 , &xxHandle );  
#define GET_PS_EQUIPMENT_HANDLE_IF_EXISTS(xxHandle)																																		clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_POWER_SUPPLY , NULL , 0 , 0 , &xxHandle );		
#define GET_NA_EQUIPMENT_HANDLE_IF_EXISTS(xxHandle)																																		clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_NETWORK_ANALYZER , NULL , 0 , 0 , &xxHandle );	
#define GET_SG_EQUIPMENT_HANDLE_IF_EXISTS(xxHandle)																																		clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_SIGNAL_GENERATOR , NULL , 0 , 0 , &xxHandle );	
#define GET_SA_EQUIPMENT_HANDLE_IF_EXISTS(xxHandle)																																		clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_SPECTRUM_ANALYZER , NULL , 0 , 0 , &xxHandle );
#define GET_SC_EQUIPMENT_HANDLE_IF_EXISTS(xxHandle)																																		clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_OSCILLOSCOPE , NULL , 0 , 0 , &xxHandle );		
#define GET_FG_EQUIPMENT_HANDLE_IF_EXISTS(xxHandle)																																		clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_FUNCTION_GENERATOR , NULL , 0 , 0 , &xxHandle );
#define GET_PM_EQUIPMENT_HANDLE_IF_EXISTS(xxHandle)																																		clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_POWER_METER , NULL , 0 , 0 , &xxHandle );		
#define GET_NF_EQUIPMENT_HANDLE_IF_EXISTS(xxHandle)																																		clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_NOISE_FIGURE , NULL , 0 , 0 , &xxHandle );		
#define GET_MM_EQUIPMENT_HANDLE_IF_EXISTS(xxHandle)																																		clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_MULTI_METER , NULL , 0 , 0 , &xxHandle );		
#define GET_WA_EQUIPMENT_HANDLE_IF_EXISTS(xxHandle)																																		clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_WAVE_FORM_ANALYZER , NULL , 0 , 0 , &xxHandle );

//----------------------------------------------- Get Equipment handles By Number -----------------------------------------------------//
#define GET_UUT_EQUIPMENT_HANDLE_BY_NUMBER(xxNumber,xxHandle)																															clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_STANDARD_DEVICE , STANDARD_DEVICE_UUT , xxNumber , 1 , &xxHandle ); 
#define GET_RFBOX_EQUIPMENT_HANDLE_BY_NUMBER(xxNumber,xxHandle)																															clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_STANDARD_DEVICE , STANDARD_DEVICE_RF_BOX_ALIAS , xxNumber , 1 , &xxHandle ); 
#define GET_DEV_EQUIPMENT_HANDLE_BY_NUMBER(xxNumber,xxHandle)																															clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_STANDARD_DEVICE , NULL , xxNumber , 1 , &xxHandle ); 
#define GET_PS_EQUIPMENT_HANDLE_BY_NUMBER(xxNumber,xxHandle)																															clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_POWER_SUPPLY , NULL , xxNumber , 1 , &xxHandle );		
#define GET_NA_EQUIPMENT_HANDLE_BY_NUMBER(xxNumber,xxHandle)																															clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_NETWORK_ANALYZER , NULL , xxNumber , 1 , &xxHandle );	
#define GET_SG_EQUIPMENT_HANDLE_BY_NUMBER(xxNumber,xxHandle)																															clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_SIGNAL_GENERATOR , NULL , xxNumber , 1 , &xxHandle );	
#define GET_SA_EQUIPMENT_HANDLE_BY_NUMBER(xxNumber,xxHandle)																															clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_SPECTRUM_ANALYZER , NULL , xxNumber , 1 , &xxHandle );
#define GET_SC_EQUIPMENT_HANDLE_BY_NUMBER(xxNumber,xxHandle)																															clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_OSCILLOSCOPE , NULL , xxNumber , 1 , &xxHandle );		
#define GET_FG_EQUIPMENT_HANDLE_BY_NUMBER(xxNumber,xxHandle)																															clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_FUNCTION_GENERATOR , NULL , xxNumber , 1 , &xxHandle );
#define GET_PM_EQUIPMENT_HANDLE_BY_NUMBER(xxNumber,xxHandle)																															clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_POWER_METER , NULL , xxNumber , 1 , &xxHandle );		
#define GET_NF_EQUIPMENT_HANDLE_BY_NUMBER(xxNumber,xxHandle)																															clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_NOISE_FIGURE , NULL , xxNumber , 1 , &xxHandle );		
#define GET_MM_EQUIPMENT_HANDLE_BY_NUMBER(xxNumber,xxHandle)																															clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_MULTI_METER , NULL , xxNumber , 1 , &xxHandle );		
#define GET_WA_EQUIPMENT_HANDLE_BY_NUMBER(xxNumber,xxHandle)																															clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_WAVE_FORM_ANALYZER , NULL , xxNumber , 1 , &xxHandle );

//----------------------------------------------- Get Equipment handles By Alias -----------------------------------------------------//
#define GET_UUT_EQUIPMENT_HANDLE_BY_ALIAS(xxAlias,xxHandle)																																clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_STANDARD_DEVICE , xxAlias , 0 , 1 , &xxHandle );
#define GET_RFBOX_EQUIPMENT_HANDLE_BY_ALIAS(xxAlias,xxHandle)																															clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_STANDARD_DEVICE , xxAlias , 0 , 1 , &xxHandle );
#define GET_DEV_EQUIPMENT_HANDLE_BY_ALIAS(xxAlias,xxHandle)																																clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_STANDARD_DEVICE , xxAlias , 0 , 1 , &xxHandle );
#define GET_PS_EQUIPMENT_HANDLE_BY_ALIAS(xxAlias,xxHandle)																																clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_POWER_SUPPLY , xxAlias , 0 , 1 , &xxHandle );		
#define GET_NA_EQUIPMENT_HANDLE_BY_ALIAS(xxAlias,xxHandle)																																clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_NETWORK_ANALYZER , xxAlias , 0 , 1 , &xxHandle );	
#define GET_SG_EQUIPMENT_HANDLE_BY_ALIAS(xxAlias,xxHandle)																																clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_SIGNAL_GENERATOR , xxAlias , 0 , 1 , &xxHandle );	
#define GET_SA_EQUIPMENT_HANDLE_BY_ALIAS(xxAlias,xxHandle)																																clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_SPECTRUM_ANALYZER , xxAlias , 0 , 1 , &xxHandle );
#define GET_SC_EQUIPMENT_HANDLE_BY_ALIAS(xxAlias,xxHandle)																																clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_OSCILLOSCOPE , xxAlias , 0 , 1 , &xxHandle );		
#define GET_FG_EQUIPMENT_HANDLE_BY_ALIAS(xxAlias,xxHandle)																																clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_FUNCTION_GENERATOR , xxAlias , 0 , 1 , &xxHandle );
#define GET_PM_EQUIPMENT_HANDLE_BY_ALIAS(xxAlias,xxHandle)																																clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_POWER_METER , xxAlias , 0 , 1 , &xxHandle );		
#define GET_NF_EQUIPMENT_HANDLE_BY_ALIAS(xxAlias,xxHandle)																																clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_NOISE_FIGURE , xxAlias , 0 , 1 , &xxHandle );		
#define GET_MM_EQUIPMENT_HANDLE_BY_ALIAS(xxAlias,xxHandle)																																clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_MULTI_METER , xxAlias , 0 , 1 , &xxHandle );		
#define GET_WA_EQUIPMENT_HANDLE_BY_ALIAS(xxAlias,xxHandle)																																clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_WAVE_FORM_ANALYZER , xxAlias , 0 , 1 , &xxHandle );

//----------------------------------------------- Get Equipment handles By Alias -----------------------------------------------------//
#define GET_UUT_EQUIPMENT_HANDLE_BY_ALIAS_IF_EXISTS(xxAlias,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_STANDARD_DEVICE , xxAlias , 0 , 0 , &xxHandle );
#define GET_RFBOX_EQUIPMENT_HANDLE_BY_ALIAS_IF_EXISTS(xxAlias,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_STANDARD_DEVICE , xxAlias , 0 , 0 , &xxHandle );
#define GET_DEV_EQUIPMENT_HANDLE_BY_ALIAS_IF_EXISTS(xxAlias,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_STANDARD_DEVICE , xxAlias , 0 , 0 , &xxHandle );
#define GET_PS_EQUIPMENT_HANDLE_BY_ALIAS_IF_EXISTS(xxAlias,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_POWER_SUPPLY , xxAlias , 0 , 0 , &xxHandle );		
#define GET_NA_EQUIPMENT_HANDLE_BY_ALIAS_IF_EXISTS(xxAlias,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_NETWORK_ANALYZER , xxAlias , 0 , 0 , &xxHandle );	
#define GET_SG_EQUIPMENT_HANDLE_BY_ALIAS_IF_EXISTS(xxAlias,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_SIGNAL_GENERATOR , xxAlias , 0 , 0 , &xxHandle );	
#define GET_SA_EQUIPMENT_HANDLE_BY_ALIAS_IF_EXISTS(xxAlias,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_SPECTRUM_ANALYZER , xxAlias , 0 , 0 , &xxHandle );
#define GET_SC_EQUIPMENT_HANDLE_BY_ALIAS_IF_EXISTS(xxAlias,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_OSCILLOSCOPE , xxAlias , 0 , 0 , &xxHandle );		
#define GET_FG_EQUIPMENT_HANDLE_BY_ALIAS_IF_EXISTS(xxAlias,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_FUNCTION_GENERATOR , xxAlias , 0 , 0 , &xxHandle );
#define GET_PM_EQUIPMENT_HANDLE_BY_ALIAS_IF_EXISTS(xxAlias,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_POWER_METER , xxAlias , 0 , 0 , &xxHandle );		
#define GET_NF_EQUIPMENT_HANDLE_BY_ALIAS_IF_EXISTS(xxAlias,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_NOISE_FIGURE , xxAlias , 0 , 0 , &xxHandle );		
#define GET_MM_EQUIPMENT_HANDLE_BY_ALIAS_IF_EXISTS(xxAlias,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_MULTI_METER , xxAlias , 0 , 0 , &xxHandle );		
#define GET_WA_EQUIPMENT_HANDLE_BY_ALIAS_IF_EXISTS(xxAlias,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_WAVE_FORM_ANALYZER , xxAlias , 0 , 0 , &xxHandle );

//----------------------------------------------- Get Equipment handles By Number -----------------------------------------------------//
#define GET_UUT_EQUIPMENT_HANDLE_BY_NUMBER_IF_EXISTS(xxNumber,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_STANDARD_DEVICE , STANDARD_DEVICE_UUT , xxNumber , 0 , &xxHandle ); 
#define GET_RFBOX_EQUIPMENT_HANDLE_BY_NUMBER_IF_EXISTS(xxNumber,xxHandle)																												clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_STANDARD_DEVICE , STANDARD_DEVICE_RF_BOX_ALIAS , xxNumber , 0 , &xxHandle ); 
#define GET_DEV_EQUIPMENT_HANDLE_BY_NUMBER_IF_EXISTS(xxNumber,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_STANDARD_DEVICE , NULL , xxNumber , 0 , &xxHandle ); 
#define GET_PS_EQUIPMENT_HANDLE_BY_NUMBER_IF_EXISTS(xxNumber,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_POWER_SUPPLY , NULL , xxNumber , 0 , &xxHandle );		
#define GET_NA_EQUIPMENT_HANDLE_BY_NUMBER_IF_EXISTS(xxNumber,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_NETWORK_ANALYZER , NULL , xxNumber , 0 , &xxHandle );	
#define GET_SG_EQUIPMENT_HANDLE_BY_NUMBER_IF_EXISTS(xxNumber,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_SIGNAL_GENERATOR , NULL , xxNumber , 0 , &xxHandle );	
#define GET_SA_EQUIPMENT_HANDLE_BY_NUMBER_IF_EXISTS(xxNumber,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_SPECTRUM_ANALYZER , NULL , xxNumber , 0 , &xxHandle );
#define GET_SC_EQUIPMENT_HANDLE_BY_NUMBER_IF_EXISTS(xxNumber,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_OSCILLOSCOPE , NULL , xxNumber , 0 , &xxHandle );		
#define GET_FG_EQUIPMENT_HANDLE_BY_NUMBER_IF_EXISTS(xxNumber,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_FUNCTION_GENERATOR , NULL , xxNumber , 0 , &xxHandle );
#define GET_PM_EQUIPMENT_HANDLE_BY_NUMBER_IF_EXISTS(xxNumber,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_POWER_METER , NULL , xxNumber , 0 , &xxHandle );		
#define GET_NF_EQUIPMENT_HANDLE_BY_NUMBER_IF_EXISTS(xxNumber,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_NOISE_FIGURE , NULL , xxNumber , 0 , &xxHandle );		
#define GET_MM_EQUIPMENT_HANDLE_BY_NUMBER_IF_EXISTS(xxNumber,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_MULTI_METER , NULL , xxNumber , 0 , &xxHandle );		
#define GET_WA_EQUIPMENT_HANDLE_BY_NUMBER_IF_EXISTS(xxNumber,xxHandle)																													clb->GetEquipmentHandle ( clb->handle  , EQUIPMENT_TYPE_WAVE_FORM_ANALYZER , NULL , xxNumber , 0 , &xxHandle );

#endif
