//==============================================================================
// Include files

#include "Windows.h"
#include <formatio.h>
#include "toolbox.h"
#include <ansi_c.h>
#include <userint.h>
#include <utility.h>
#include "common.h"
#include "EmbeddedTests_StandardCalibration.h"
#include "MathLibrary.h"
#include "TE_GlobalDefines.h"

//==============================================================================
// Constants

//==============================================================================
// Types

typedef STD_ERROR   (*tfDRV_NetworkAnalyzer_ReCallRegister)(int Handle,char *szRegister_FileName);
typedef STD_ERROR   (*tfDRV_NetworkAnalyzer_GetPointsNum)(int Handle,int *points) ;
typedef STD_ERROR   (*tfDRV_NetworkAnalyzer_GetFrequency)(int Handle,double *plfStartFrequency, double *plfStopFrequency);  
typedef STD_ERROR   (*tfDRV_NetworkAnalyzer_GetTrace)( int Handle , int iChannel , int iMeasurementType , int iMeasurementFormat , double lfTimeout ,  double **plfFrequency , double **plfTrace , int *piNumberOfPoints );
typedef STD_ERROR   (*tfDRV_NetworkAnalyzer_ECAL_Calibrate)( int Handle , char *pszPortList , char *pUserCal , double lfTimeout );
typedef STD_ERROR   (*tfDRV_NetworkAnalyzer_SaveStateAndCalibration)( int Handle , char *pFileName );
typedef STD_ERROR   (*tfDRV_NetworkAnalyzer_Reponse_OpenShortLoad_Calibrate)(int hInstrumentHandle , int iType_OSL , char *pszPortList , double lfTimeout );
typedef STD_ERROR   (*tfDRV_NetworkAnalyzer_Reponse_Thru_Calibrate)(int hInstrumentHandle, char *pszPortList , double lfTimeout );
typedef STD_ERROR   (*tfDRV_NetworkAnalyzer_Reponse_Done_Calibrate)(int hInstrumentHandle );
typedef STD_ERROR   (*tfDRV_NetworkAnalyzer_Avarage)( int Handle , int iChannel, int bEnable , int iAverageValue );  
typedef STD_ERROR   (*tfDRV_NetworkAnalyzer_ClearAvarage)( int Handle , int iChannel ); 
typedef STD_ERROR   (*tfDRV_NetworkAnalyzer_WaitSweep)( int Handle , int iChannel , int iCount );

typedef STD_ERROR   (*tfDRV_SpectrumAnalyzer_Recall)( int Handle , char *szFilePath  );
typedef STD_ERROR   (*tfDRV_SpectrumAnalyzer_SaveState)( int Handle , char *szFilePath  );
typedef STD_ERROR   (*tfDRV_SpectrumAnalyzer_SetFrequency)( int Handle , double dCenterFreq );
typedef STD_ERROR   (*tfDRV_SpectrumAnalyzer_InitiateMeasure)( int Handle );
typedef STD_ERROR   (*tfDRV_SpectrumAnalyzer_SearchMarkerPeak)( int Handle  , int iMarkerNr );
typedef STD_ERROR   (*tfDRV_SpectrumAnalyzer_GetMarkerAmplitude)( int Handle , int iMarkerNr , double *vlfAmplitude );
typedef STD_ERROR   (*tfDRV_SpectrumAnalyzer_SetReferenceLevel)( int Handle , double lfReferenceLevel );
typedef STD_ERROR   (*tfDRV_SpectrumAnalyzer_Attenuator)( int Handle , double lfAttenuator ); 
typedef STD_ERROR   (*tfDRV_SpectrumAnalyzer_GetAttenuator)( int Handle , double *plfAttenuator ); 
typedef STD_ERROR   (*tfDRV_SpectrumAnalyzer_GetReferenceLevel)( int Handle , double *vlfReferenceLevel );
typedef STD_ERROR   (*tfDRV_SpectrumAnalyzer_Reset)( int Handle );
typedef STD_ERROR   (*tfDRV_SpectrumAnalyzer_NoiseFigure_CalibrateNow)( int Handle , double lfTimeout );
typedef STD_ERROR   (*tfDRV_SpectrumAnalyzer_WaitForIntrumentDone)( int Handle , double lfTimeout );
typedef STD_ERROR   (*tfDRV_SpectrumAnalyzer_NoiseFigure_SetLossCompensationTable)( int Handle , int bAfterDUT , double *pvFrequencies, double *pvLoss , int iNumberOfPoints );

typedef STD_ERROR   (*tfDRV_SignalGenerator_Reset)( int Handle );
typedef STD_ERROR   (*tfDRV_SignalGenerator_SetPower)( int Handle , int Channel , double dPower );
typedef STD_ERROR   (*tfDRV_SignalGenerator_SetFrequency)( int Handle , int Channel , double dFrequency );
typedef STD_ERROR   (*tfDRV_SignalGenerator_RF_On)( int Handle , int Channel );
typedef STD_ERROR   (*tfDRV_SignalGenerator_RF_Off)( int Handle , int Channel );
typedef STD_ERROR   (*tfDRV_SignalGenerator_RecallState)( int Handle , char *szFilePath  ); 
					 
typedef STD_ERROR   (*tfDRV_PowerMeter_Reset)( int Handle );
typedef STD_ERROR   (*tfDRV_PowerMeter_SetActiveChannel)( int Handle , int iChannelNumber );  
typedef STD_ERROR   (*tfDRV_PowerMeter_SetMode)( int Handle , int channel , unsigned int Mode );      
typedef STD_ERROR   (*tfDRV_PowerMeter_SetActivePort)( int Handle , int iSensorNumber );
typedef STD_ERROR   (*tfDRV_PowerMeter_SetFrequency)( int Handle , int iChannel , double lfFrequency );
typedef STD_ERROR   (*tfDRV_PowerMeter_InitSweep)( int Handle , int channel );
typedef STD_ERROR   (*tfDRV_PowerMeter_ReadCWpower)( int Handle , int iChannel , double timeout , double *value );   
typedef STD_ERROR   (*tfDRV_PowerMeter_SetContinuesSweep)( int Handle , int iChannel );

typedef STD_ERROR   (*tfDRIVER_MANAGER_CALIBRATION_GelFactor)( int Handle , double lfFrequency , double *plfFactor );
typedef STD_ERROR   (*tfDRIVER_MANAGER_CALIBRATION_Gel_3D_Factor)( int Handle , double lfPower , double lfFrequency , double *plfFactor );


//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

TSTE_TEST( embeddedTestCalibration )
{	
	//---------------------- Functions Definitions ---------------------------//
	tfDRV_NetworkAnalyzer_ReCallRegister								DRV_NetworkAnalyzer_ReCallRegister             					=	NULL;
	tfDRV_NetworkAnalyzer_GetPointsNum									DRV_NetworkAnalyzer_GetPointsNum               					=	NULL;
	tfDRV_NetworkAnalyzer_GetFrequency									DRV_NetworkAnalyzer_GetFrequency               					=	NULL;
	tfDRV_NetworkAnalyzer_GetTrace										DRV_NetworkAnalyzer_GetTrace                   					=	NULL;
    tfDRV_NetworkAnalyzer_ECAL_Calibrate								DRV_NetworkAnalyzer_ECAL_Calibrate             					=	NULL;  
	tfDRV_NetworkAnalyzer_SaveStateAndCalibration						DRV_NetworkAnalyzer_SaveStateAndCalibration						=	NULL;
	tfDRV_NetworkAnalyzer_Reponse_OpenShortLoad_Calibrate  			 	DRV_NetworkAnalyzer_Reponse_OpenShortLoad_Calibrate				=	NULL;
	tfDRV_NetworkAnalyzer_Reponse_Thru_Calibrate						DRV_NetworkAnalyzer_Reponse_Thru_Calibrate         				=	NULL;
	tfDRV_NetworkAnalyzer_Reponse_Done_Calibrate						DRV_NetworkAnalyzer_Reponse_Done_Calibrate         				=	NULL;
	tfDRV_NetworkAnalyzer_Avarage										DRV_NetworkAnalyzer_Avarage     								=	NULL;
	tfDRV_NetworkAnalyzer_ClearAvarage									DRV_NetworkAnalyzer_ClearAvarage								=	NULL;
	tfDRV_NetworkAnalyzer_WaitSweep										DRV_NetworkAnalyzer_WaitSweep   								=	NULL;
	
	tfDRV_SpectrumAnalyzer_Recall										DRV_SpectrumAnalyzer_Recall                   					=	NULL;
	tfDRV_SpectrumAnalyzer_SaveState									DRV_SpectrumAnalyzer_SaveState									=	NULL; 
	tfDRV_SpectrumAnalyzer_SetFrequency									DRV_SpectrumAnalyzer_SetFrequency             					=	NULL;
	tfDRV_SpectrumAnalyzer_InitiateMeasure								DRV_SpectrumAnalyzer_InitiateMeasure          					=	NULL;
	tfDRV_SpectrumAnalyzer_SearchMarkerPeak								DRV_SpectrumAnalyzer_SearchMarkerPeak         					=	NULL;
	tfDRV_SpectrumAnalyzer_GetMarkerAmplitude  	 						DRV_SpectrumAnalyzer_GetMarkerAmplitude       					=	NULL;
    tfDRV_SpectrumAnalyzer_SetReferenceLevel							DRV_SpectrumAnalyzer_SetReferenceLevel        					=	NULL;                     				                                               \
	tfDRV_SpectrumAnalyzer_Attenuator									DRV_SpectrumAnalyzer_Attenuator									=	NULL; 
	tfDRV_SpectrumAnalyzer_GetAttenuator								DRV_SpectrumAnalyzer_GetAttenuator								=	NULL; 
	tfDRV_SpectrumAnalyzer_GetReferenceLevel							DRV_SpectrumAnalyzer_GetReferenceLevel							=	NULL; 
	tfDRV_SpectrumAnalyzer_Reset										DRV_SpectrumAnalyzer_Reset										=	NULL; 
	tfDRV_SpectrumAnalyzer_NoiseFigure_CalibrateNow						DRV_SpectrumAnalyzer_NoiseFigure_CalibrateNow					=	NULL;
	tfDRV_SpectrumAnalyzer_WaitForIntrumentDone							DRV_SpectrumAnalyzer_WaitForIntrumentDone						=	NULL;
	tfDRV_SpectrumAnalyzer_NoiseFigure_SetLossCompensationTable			DRV_SpectrumAnalyzer_NoiseFigure_SetLossCompensationTable		=	NULL; 
	
	tfDRV_SignalGenerator_Reset											DRV_SignalGenerator_Reset                     				 	=	NULL;
	tfDRV_SignalGenerator_SetPower										DRV_SignalGenerator_SetPower                  				 	=	NULL;
	tfDRV_SignalGenerator_SetFrequency									DRV_SignalGenerator_SetFrequency              				 	=	NULL;
	tfDRV_SignalGenerator_RF_On											DRV_SignalGenerator_RF_On                     				 	=	NULL;
	tfDRV_SignalGenerator_RF_Off 										DRV_SignalGenerator_RF_Off                    				 	=	NULL;
	tfDRV_SignalGenerator_RecallState									DRV_SignalGenerator_RecallState									=	NULL;
	
	tfDRV_PowerMeter_Reset												DRV_PowerMeter_Reset                							=	NULL;
	tfDRV_PowerMeter_SetActiveChannel									DRV_PowerMeter_SetActiveChannel     							=	NULL;
	tfDRV_PowerMeter_SetMode											DRV_PowerMeter_SetMode              							=	NULL;
	tfDRV_PowerMeter_SetActivePort										DRV_PowerMeter_SetActivePort        							=	NULL;
	tfDRV_PowerMeter_SetFrequency										DRV_PowerMeter_SetFrequency         							=	NULL;
	tfDRV_PowerMeter_InitSweep											DRV_PowerMeter_InitSweep            							=	NULL;
	tfDRV_PowerMeter_ReadCWpower										DRV_PowerMeter_ReadCWpower          							=	NULL;
	tfDRV_PowerMeter_SetContinuesSweep									DRV_PowerMeter_SetContinuesSweep								=	NULL;
	
	tfDRIVER_MANAGER_CALIBRATION_GelFactor								DRIVER_MANAGER_CALIBRATION_GelFactor							=	NULL;
	tfDRIVER_MANAGER_CALIBRATION_Gel_3D_Factor							DRIVER_MANAGER_CALIBRATION_Gel_3D_Factor						=	NULL; 
	//------------------------------------------------------------------------//
	
	STD_ERROR															StdError														=	{0};
	
	int																	iTestError														=	0;
	
	int																	iRangeLength													=	0,
																		iActualyPointsNumber											=	0,
																		iOutputNumberOfPoints											=	0,   
																		iAuxilityActualyPointsNumber									=	0,
																		iInputActualyPointsNumber										=	0, 
																		iAuxilityPresentPointsNumber									=	0, 
																		iVSWRActualyPointsNumber										=	0;  
												
	double																*pTraceData														=	NULL,
																		*pTraceDeltaData												=	NULL,
																		*pVSWRData														=	NULL,  
																		*pFrequencyData													=	NULL,
																		*pOutputFrequencyTrace											=	NULL,   
																		*pOutputDataTrace												=	NULL,
																		*pAuxilityTraceData												=	NULL;
			
	double																lfCurrentFrequency  											=	0.0, 
																		lfStartFrequency												=	0.0,
																		lfStopFrequency													=	0.0,
																		lfMeasurePower													=	0.0,
																		lfResult														=	0.0; 
															
	double																lfDB_Power														=	0.0,
																		lfDB_Timeout													=	0.0,
																		lfDB_Attenuator													=	0.0,  
																		lfDB_ReferenceLevel												=	0.0,  
																		lfDB_MaxGainOffset												=	0.0,  
																		lfDB_MeasureDelay												=	0.0,
																		lfDB_MeasureTimeout												=	0.0,
																		lfDB_StartFrequency												=	0.0,
																		lfDB_StopFrequency												=	0.0,
																		lfDB_OrigStartFrequency											=	0.0,
																		lfDB_OrigStopFrequency											=	0.0,
																		lfDB_MinimumMeasureLimit										=	0.0; 
															
	int																	index															=	0, 
																		iIndex															=	0,
																		iTryIndex														=	0,
																		iRangeIndex									 					=	0,  
																		iAuxilityIndex													=	0, 
																		iInputStartIndex												=	0,  
																		iRangeStartIndex												=	0;
																		
	double																*pOldCalibFrequencyList											=	NULL,
																		*pOldCalibFactorList											=	NULL;
	
	int																	iOldNumOfCalibPoints											=	0;
	
	double																lfLastCalibrationDate											=	0.0,
																		lfNewCalibrationDate											=	0.0,
																		lfOutputStartFrequency											=	0.0,  
																		lfCurrentReferenceLevel											=	0.0,  
																		lfPowerMeterLossFactor											=	0.0, 
																		lfDifferentialMeasurePower										=	0.0, 
																		lfSpectrumAnalyzerLossFactor									=	0.0, 
																		lfSignalGeneratorLossFactor										=	0.0; 
												
	int																	iDB_AverageValue												=	0,
																		iDB_NumberOfPoints												=	0,
																		iDB_NumberOfRanges												=	0,
																		iDB_VSWR_TraceNumber											=	0,
																		iDB_GetFromTraceNumber											=	0,
																		iDB_PowerMeterPortNumber										=	0,
																		iDB_NumberOfNetworkFiles										=	0,
																		iDB_PowerMeterSubPortNumber										=	0,
																		iDB_NumberOfReferenceLevels										=	0,
																		iDB_LastExtrapolationRangeNumber								=	0,
																		iDB_NumberOfNetworkAnalyzerStates								=	0;  
												
	int																	bDB_Use_Aux_Cable												=	0,  
																		bDB_AllowExtrapolation											=	0, 
																		bDB_DifferentialMeas											=	0,  
																		bDB_DisableResults												=	0, 
																		bDB_DisableDeltaResults											=	0, 
																		bDB_ECal_Calibration											=	0, 
																		bDB_EnableCalibration											=	0,
																		bDB_ClearCalibration											=	0, 
																		bDB_SA_IsANoiseSource											=	0, 
																		bDB_ApplyOpenCalibration										=	0,  
																		bDB_ApplyShortCalibration										=	0,  
																		bDB_ApplyLoadCalibration										=	0,  
																		bDB_ApplyThruCalibration										=	0,  
																		bDB_AnalyzeWorstCaseResults										=	0,   
																		bDB_DisableToStoreCalibration									=	0,
																		bDB_AutoReferenceCalculation									=	0,
																		bDB_SA_NoiseSource_FillTables									=	0, 
																		bDB_SA_NoiseSource_CalibrateNow									=	0; 
																		
	char																**pszNetworkAnalyzerStateFiles									=	NULL;
	
	char																*pszSpectrumAnalyzerStateFile									=	NULL,  
																		*pszSignalGeneratorState										=	NULL,
																		*pszNetworkAnalyzerCalPortsList									=	NULL,   
																		*pszPostEcal_Instruction										=	NULL, 
																		*pszPostEcal_Instruction_Pic							   		=	NULL, 
																		*pszCalibrated_With_Other_Path								 	=	NULL,
																		*pszAux_Cable_Instruction										=	NULL,
																		*pszAux_Cable_InstructionPic									=	NULL,
																		*pszEcalUserCharacterizations									=	NULL,
																		*pszNetworkAnalyzer_ECAL_PortList								=	NULL,
																		*pszNoiseSourceFillTableFromPath								=	NULL; 
												
	char																szFormatedString[LOW_STRING]									=	{0},
																		szFormatedVariable[LOW_STRING]									=	{0};
	
	void																*pGraphItem														=	NULL;
	
	int																	iResultStatus													=	0,
																		iResultNumber													=	0; 
										
	int																	iCurrentPathIndex												=	0,
																		iCurrentResultIndex												=	0,
																		iCurrentPathPartIndex											=	0,
																		iNetworkAnalyzerStateFileIndex									=	0;  
												
	int																	hPowerMeter														=	0, 
																		hNetworkAnalyzer												=	0,
																		hSpectrumAnalyzer												=	0,
																		hSignalGenerator												=	0;
	
	double																*pDB_FrequencyList												=	NULL,
																		*vlfDB_ReferenceLevelList										=	NULL; 
												
	int																	*pDB_RangesList													=	NULL;
	
	int																	bUserAcceptCalibration											=	0,
																		bEnableToSaveCallibration										=	0;
												
	int																	bForceNetworkAnalyzer											=	0,
																		bForceSignalGenerator											=	0,
																		bForceSpectrumAnalyzer											=	0, 
																		bForcePowerMeter												=	0, 
																		bNoStimulusFound												=	0;
	
	int																	iLastRange														=	0;
	
	char																*pszStimulusEquipmentType										=	NULL,
																		*pszMeasureEquipmentType										=	NULL;
	
	
	double																*pPointerToMinSpec												=	NULL,
																		*pPointerToMaxSpec												=	NULL;
	
	int																	iSpecValuesCount												=	0,
																		iSpecFloatType													=	0;
	
	double																lfSpecFloatValue												=	0;
	
	double																lfWorstCaseValue												=	0, 
																		lfWorstCaseCalculation											=	0;
	
	int																	iWorstCaseIndex													=	0;
	
	LOG(CLB_LINE_SYSTEM_HEADER, "Calibration."); 

	PATH_GET_CURRENT_INDEX(iCurrentPathIndex);
	
	PATH_PART_GET_CURRENT_INDEX(iCurrentPathPartIndex);
	
	bDB_AnalyzeWorstCaseResults = GetVarInt( clb, VARTYPE_TEST , "Calibration_Analyze_WorstCase_Results" );  
	
	if ( iCurrentPathPartIndex )
	{
		sprintf( szFormatedVariable , "Calibration_%d_%d_StartFromResultIndex" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 ); 
		iCurrentResultIndex = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable );   
	}
	
	PATH_GET_CURRENT_FREQUENCY_LIST(pDB_FrequencyList,pDB_RangesList,iDB_NumberOfPoints,iDB_NumberOfRanges);
	
	if ( pDB_FrequencyList && iDB_NumberOfPoints )
	{
		lfDB_OrigStartFrequency = pDB_FrequencyList[0];
	
		lfDB_OrigStopFrequency = pDB_FrequencyList[iDB_NumberOfPoints-1];
	}
	
	sprintf( szFormatedVariable , "Calibration_%d_%d_Measure_Delay" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 ); 
	lfDB_MeasureDelay = GetVarDouble( clb, VARTYPE_TEST , szFormatedVariable ); 
	
	sprintf( szFormatedVariable , "Calibration_%d_%d_CalibratedWithOtherPath" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );  
	pszCalibrated_With_Other_Path = GetVarString( clb, VARTYPE_TEST , szFormatedVariable  );   
		
	sprintf( szFormatedVariable , "Calibration_%d_%d_Use_Aux_Cable" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 ); 
	bDB_Use_Aux_Cable = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable ); 
	
	if ( bDB_Use_Aux_Cable )
	{
		sprintf( szFormatedVariable , "Calibration_%d_%d_Aux_Cable_Instruction" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );  
		pszAux_Cable_Instruction = GetVarString( clb, VARTYPE_TEST , szFormatedVariable  );     
		
		sprintf( szFormatedVariable , "Calibration_%d_%d_Aux_Cable_Instruction_Pic" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );  
		pszAux_Cable_InstructionPic = GetVarString( clb, VARTYPE_TEST , szFormatedVariable );     
		
		if ( pszAux_Cable_InstructionPic && (strlen( pszAux_Cable_InstructionPic ) < 3 ))
		{
			FREE(pszAux_Cable_InstructionPic);	
		}
	}
	
	GET_NA_EQUIPMENT_HANDLE_IF_EXISTS(hNetworkAnalyzer);
	GET_SA_EQUIPMENT_HANDLE_IF_EXISTS(hSpectrumAnalyzer);
	GET_SG_EQUIPMENT_HANDLE_IF_EXISTS(hSignalGenerator); 
	GET_PM_EQUIPMENT_HANDLE_IF_EXISTS(hPowerMeter); 
	
	sprintf( szFormatedVariable , "Calibration_%d_%d_AllowExtrapolation" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 ); 
	bDB_AllowExtrapolation = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable );    
	
	sprintf( szFormatedVariable , "Calibration_%d_%d_LastExtrapolationRangeNumber" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 ); 
	iDB_LastExtrapolationRangeNumber = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable );    
	
	iAuxilityPresentPointsNumber = GetVarDoubleArray( clb, VARTYPE_MEASURE_STORE , "AuxilityCabelLoss" , NULL );  
	
	sprintf( szFormatedVariable , "Calibration_Path_%d_%d_Stimulus_EquipmentType" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 ); 
	pszStimulusEquipmentType = GetVarString( clb, VARTYPE_TEST , szFormatedVariable );     
	
	bNoStimulusFound = 1;
	
	if ( pszStimulusEquipmentType == NULL ) 
	{
		if ( hNetworkAnalyzer ) 
		{
			CALLOC_COPY_STRING( pszStimulusEquipmentType , "NA" );
		}
		
		if ( hSignalGenerator ) 
		{
			CALLOC_COPY_STRING( pszStimulusEquipmentType , "SG" );
		}
		
		if ( pszStimulusEquipmentType == NULL ) 
		{
			CALLOC_COPY_STRING( pszStimulusEquipmentType , "-" );	
		}
		
		if ( pszStimulusEquipmentType )
		{
			SetVarString( clb, VARTYPE_TEST , szFormatedVariable , pszStimulusEquipmentType );	
		}   
	}
	
	if ( pszStimulusEquipmentType )
	{
		if ( strstr( pszStimulusEquipmentType , "NA" ))
		{
			bForceNetworkAnalyzer = 1;
			bNoStimulusFound = 0;
		}
		
		if ( strstr( pszStimulusEquipmentType , "SG" ))
		{
			bForceSignalGenerator = 1;
			bNoStimulusFound = 0;
		}
	}
	
	sprintf( szFormatedVariable , "Calibration_Path_%d_%d_Measure_EquipmentType" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 ); 
	pszMeasureEquipmentType = GetVarString( clb, VARTYPE_TEST , szFormatedVariable ); 
	
	if ( pszMeasureEquipmentType == NULL )   
	{
		if ( hNetworkAnalyzer ) 
		{
			CALLOC_COPY_STRING( pszMeasureEquipmentType , "NA" );
		}
		
		if ( hPowerMeter ) 
		{
			CALLOC_COPY_STRING( pszMeasureEquipmentType , "PM" );
		}
		
		if ( hSpectrumAnalyzer ) 
		{
			CALLOC_COPY_STRING( pszMeasureEquipmentType , "SA" );
		}
		
		if ( pszMeasureEquipmentType )
		{
			SetVarString( clb, VARTYPE_TEST , szFormatedVariable , pszMeasureEquipmentType );	
		}   
	}
	
	if ( pszMeasureEquipmentType )
	{
		if ( strstr( pszMeasureEquipmentType , "NA" ))
		{
			bForceNetworkAnalyzer = 1;
		}
		
		if ( strstr( pszMeasureEquipmentType , "PM" ))
		{
			bForcePowerMeter = 1;
		}
		
		if ( strstr( pszMeasureEquipmentType , "SA" ))
		{
			bForceSpectrumAnalyzer = 1;
		}
	}
	
	if ( bForceNetworkAnalyzer )
	{
		if ( hNetworkAnalyzer == 0 )
		{
			GET_NA_EQUIPMENT_HANDLE(hNetworkAnalyzer); 
		}
		
		DRV_NetworkAnalyzer_ReCallRegister = (tfDRV_NetworkAnalyzer_ReCallRegister) GetProcAddress( clb->hDriverManagerLibrary , "DRV_NetworkAnalyzer_ReCallRegister" );
		DRV_NetworkAnalyzer_GetPointsNum = (tfDRV_NetworkAnalyzer_GetPointsNum) GetProcAddress( clb->hDriverManagerLibrary , "DRV_NetworkAnalyzer_GetPointsNum" );	
		DRV_NetworkAnalyzer_GetFrequency = (tfDRV_NetworkAnalyzer_GetFrequency) GetProcAddress( clb->hDriverManagerLibrary , "DRV_NetworkAnalyzer_GetFrequency" );	
		DRV_NetworkAnalyzer_GetTrace = (tfDRV_NetworkAnalyzer_GetTrace) GetProcAddress( clb->hDriverManagerLibrary , "DRV_NetworkAnalyzer_GetTrace" );
		DRV_NetworkAnalyzer_ECAL_Calibrate = (tfDRV_NetworkAnalyzer_ECAL_Calibrate) GetProcAddress( clb->hDriverManagerLibrary , "DRV_NetworkAnalyzer_ECAL_Calibrate" );
		DRV_NetworkAnalyzer_SaveStateAndCalibration = (tfDRV_NetworkAnalyzer_SaveStateAndCalibration) GetProcAddress( clb->hDriverManagerLibrary , "DRV_NetworkAnalyzer_SaveStateAndCalibration" );
		DRV_NetworkAnalyzer_Reponse_OpenShortLoad_Calibrate = (tfDRV_NetworkAnalyzer_Reponse_OpenShortLoad_Calibrate) GetProcAddress( clb->hDriverManagerLibrary , "DRV_NetworkAnalyzer_Reponse_OpenShortLoad_Calibrate" );
		DRV_NetworkAnalyzer_Reponse_Thru_Calibrate = (tfDRV_NetworkAnalyzer_Reponse_Thru_Calibrate) GetProcAddress( clb->hDriverManagerLibrary , "DRV_NetworkAnalyzer_Reponse_Thru_Calibrate" );         
		DRV_NetworkAnalyzer_Reponse_Done_Calibrate = (tfDRV_NetworkAnalyzer_Reponse_Done_Calibrate) GetProcAddress( clb->hDriverManagerLibrary , "DRV_NetworkAnalyzer_Reponse_Done_Calibrate" );         
		DRV_NetworkAnalyzer_Avarage = (tfDRV_NetworkAnalyzer_Avarage) GetProcAddress( clb->hDriverManagerLibrary , "DRV_NetworkAnalyzer_Avarage" );      
		DRV_NetworkAnalyzer_ClearAvarage = (tfDRV_NetworkAnalyzer_ClearAvarage) GetProcAddress( clb->hDriverManagerLibrary , "DRV_NetworkAnalyzer_ClearAvarage" ); 
		DRV_NetworkAnalyzer_WaitSweep = (tfDRV_NetworkAnalyzer_WaitSweep) GetProcAddress( clb->hDriverManagerLibrary , "DRV_NetworkAnalyzer_WaitSweep" );    
										 
		sprintf( szFormatedVariable , "Calibration_%d_%d_Get_From_Trace_Number" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );   
		iDB_GetFromTraceNumber = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable ); 

		sprintf( szFormatedVariable , "Calibration_%d_%d_VSWR_TraceNumber" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );
		iDB_VSWR_TraceNumber = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable );   
		
		sprintf( szFormatedVariable , "Calibration_%d_%d_Enable_BuildIn_Calibration" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );
		bDB_EnableCalibration = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable ); 
		
		sprintf( szFormatedVariable , "Calibration_%d_%d_ECal_Calibration" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );
		bDB_ECal_Calibration = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable ); 
		
		sprintf( szFormatedVariable , "Calibration_%d_%d_DisableResults" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );
		bDB_DisableResults = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable );
		
		sprintf( szFormatedVariable , "Calibration_%d_%d_DisableToStoreCalibration" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 ); 
		bDB_DisableToStoreCalibration = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable );
		
		sprintf( szFormatedVariable , "Calibration_%d_%d_DisableDeltaResults" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 ); 
		bDB_DisableDeltaResults = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable );
		
		sprintf( szFormatedVariable , "Calibration_%d_%d_Measure_Timeout" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );
		lfDB_MeasureTimeout = GetVarDouble( clb, VARTYPE_TEST , szFormatedVariable );  

		sprintf( szFormatedVariable , "Calibration_%d_%d_NumberOfNetworkFiles" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );
		iDB_NumberOfNetworkFiles = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable );   
		
		bEnableToSaveCallibration = 1; 
		
		for ( iRangeIndex = 0; (( iRangeIndex < iDB_NumberOfRanges ) || ( iRangeIndex < 1 )); iRangeIndex++ )
		{
			FREE_LIST(pszNetworkAnalyzerStateFiles,iDB_NumberOfNetworkAnalyzerStates);  
			
			if ( iDB_NumberOfRanges <= 1 )
				sprintf( szFormatedVariable , "Calibration_%d_%d_StateFile" , (iCurrentPathIndex+1) , (iCurrentPathPartIndex+1) );
			else
				sprintf( szFormatedVariable , "Calibration_%d_%d_Range_%d_StateFile" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 , iRangeIndex+1 );

			pszNetworkAnalyzerStateFiles = GetVarStringArray( clb, VARTYPE_EQUIPMENT_USE , szFormatedVariable , &iDB_NumberOfNetworkAnalyzerStates , hNetworkAnalyzer );     
			
			if ( iDB_NumberOfNetworkAnalyzerStates && pszNetworkAnalyzerStateFiles )
			{
				for ( iNetworkAnalyzerStateFileIndex = 0; iNetworkAnalyzerStateFileIndex < iDB_NumberOfNetworkAnalyzerStates; iNetworkAnalyzerStateFileIndex++ )
				{
					sprintf( szFormatedString , "Network Analyzer :: Loading state (%s)" , pszNetworkAnalyzerStateFiles[iNetworkAnalyzerStateFileIndex] );   //1
					LOG(CLB_LINE_NORMAL, szFormatedString ); 

					CHK_STDERR( DRV_NetworkAnalyzer_ReCallRegister( hNetworkAnalyzer , pszNetworkAnalyzerStateFiles[iNetworkAnalyzerStateFileIndex] ));   

					if ( bDB_EnableCalibration || bDB_ECal_Calibration )
					{
						if ( bDB_ECal_Calibration )
						{						
							sprintf( szFormatedVariable , "Calibration_%d_%d_ECAL_PortList" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );
							pszNetworkAnalyzer_ECAL_PortList = GetVarString( clb, VARTYPE_EQUIPMENT_USE , szFormatedVariable , hNetworkAnalyzer );     
			
							sprintf( szFormatedVariable , "Calibration_%d_%d_ECal_User_Characterizations" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );
							pszEcalUserCharacterizations = GetVarString( clb, VARTYPE_TEST , szFormatedVariable  );
						
							sprintf( szFormatedVariable , "Calibration_%d_%d_Post_ECal_Instruction" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );
							pszPostEcal_Instruction = GetVarString( clb, VARTYPE_TEST , szFormatedVariable  );
				
							sprintf( szFormatedVariable , "Calibration_%d_%d_Post_ECal_Instruction_Pic" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );
							pszPostEcal_Instruction_Pic = GetVarString( clb, VARTYPE_TEST , szFormatedVariable  );
						
							if ( pszEcalUserCharacterizations && ( strlen(pszEcalUserCharacterizations) > 1 ))
							{
								sprintf( szFormatedString , "ECal :: Using User Characterizations ( %s )" , pszEcalUserCharacterizations );
								LOG(CLB_LINE_NORMAL, szFormatedString ); 	
							}
						
							for ( iTryIndex = 0; iTryIndex < 3; iTryIndex++ )
							{
								START_TIMEOUT("",lfDB_MeasureTimeout);
					
								UPDATERR( DRV_NetworkAnalyzer_ECAL_Calibrate ( hNetworkAnalyzer , pszNetworkAnalyzer_ECAL_PortList , pszEcalUserCharacterizations , lfDB_MeasureTimeout )); 
		
								STOP_TIMEOUT; 
					
								if ( IS_OK && pszNetworkAnalyzerStateFiles[iNetworkAnalyzerStateFileIndex] && (strlen(pszNetworkAnalyzerStateFiles[iNetworkAnalyzerStateFileIndex])))
								{
									sprintf( szFormatedString , "Network Analyzer :: Saving state (%s)" , pszNetworkAnalyzerStateFiles[iNetworkAnalyzerStateFileIndex] );   //1
									LOG(CLB_LINE_NORMAL, szFormatedString ); 
				
									DRV_NetworkAnalyzer_SaveStateAndCalibration ( hNetworkAnalyzer , pszNetworkAnalyzerStateFiles[iNetworkAnalyzerStateFileIndex] );
									break;
								}
								else
								{
									INSTRUCTION("Calibration Error.\nPlease Check the Ecal connectivity.",NULL); 
								}
							}
						}
						else
						{
							sprintf( szFormatedVariable , "Calibration_%d_%d_AverageValue" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );  
							iDB_AverageValue = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable );
						
							sprintf( szFormatedString , "Network Analyzer :: Set Average %d" , iDB_AverageValue );   
							LOG(CLB_LINE_NORMAL, szFormatedString ); 
				
							CHK_STDERR( DRV_NetworkAnalyzer_Avarage( hNetworkAnalyzer , iDB_GetFromTraceNumber , 1 , iDB_AverageValue ));
						
							START_TIMEOUT("",lfDB_MeasureTimeout); 
						
							FREE(pszNetworkAnalyzerCalPortsList);
						
							sprintf( szFormatedVariable , "Calibration_%d_%d_Range_%d_Cal_PortsList" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 , iRangeIndex+1 );  
							pszNetworkAnalyzerCalPortsList = GetVarString( clb, VARTYPE_TEST , szFormatedVariable , hNetworkAnalyzer );     

							sprintf( szFormatedVariable , "Calibration_%d_%d_Clear_Calibration" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );
							bDB_ClearCalibration = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable ); 
						
							if ( bDB_ClearCalibration )
							{
								LOG(CLB_LINE_NORMAL, "Network Analyzer :: Cleaning Calibration ..." ); 
							
								UPDATERR( DRV_NetworkAnalyzer_Reponse_OpenShortLoad_Calibrate( hNetworkAnalyzer , -1 , NULL , lfDB_MeasureTimeout ));
							}
						
							sprintf( szFormatedVariable , "Calibration_%d_%d_Open_Calibration" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );
							bDB_ApplyOpenCalibration = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable ); 
						
							if ( bDB_ApplyOpenCalibration )
							{
								LOG(CLB_LINE_NORMAL, "Network Analyzer :: Calibrating Open ..." ); 
							
								UPDATERR( DRV_NetworkAnalyzer_Reponse_OpenShortLoad_Calibrate( hNetworkAnalyzer , 0 , pszNetworkAnalyzerCalPortsList , lfDB_MeasureTimeout ));
							}
						
							sprintf( szFormatedVariable , "Calibration_%d_%d_Short_Calibration" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );
							bDB_ApplyShortCalibration = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable ); 
						
							if ( bDB_ApplyShortCalibration )
							{
								LOG(CLB_LINE_NORMAL, "Network Analyzer :: Calibrating Short ..." ); 
							
								UPDATERR( DRV_NetworkAnalyzer_Reponse_OpenShortLoad_Calibrate( hNetworkAnalyzer , 1 , pszNetworkAnalyzerCalPortsList , lfDB_MeasureTimeout ));
							}
						
							sprintf( szFormatedVariable , "Calibration_%d_%d_Load_Calibration" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );
							bDB_ApplyLoadCalibration = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable ); 
						
							if ( bDB_ApplyLoadCalibration )
							{
								LOG(CLB_LINE_NORMAL, "Network Analyzer :: Calibrating Load ..." ); 
							
								UPDATERR( DRV_NetworkAnalyzer_Reponse_OpenShortLoad_Calibrate( hNetworkAnalyzer , 2 , pszNetworkAnalyzerCalPortsList , lfDB_MeasureTimeout ));
							}
						
							sprintf( szFormatedVariable , "Calibration_%d_%d_Thru_Calibration" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );
							bDB_ApplyThruCalibration = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable ); 
						
							if ( bDB_ApplyThruCalibration )
							{
								LOG(CLB_LINE_NORMAL, "Network Analyzer :: Calibrating Thru ..." );  
							
								UPDATERR( DRV_NetworkAnalyzer_Reponse_Thru_Calibrate( hNetworkAnalyzer , pszNetworkAnalyzerCalPortsList , lfDB_MeasureTimeout ));
							}
						
							if ( IS_OK )
							{
								UPDATERR( DRV_NetworkAnalyzer_Reponse_Done_Calibrate( hNetworkAnalyzer ));
							
								LOG(CLB_LINE_NORMAL, "Network Analyzer :: Calibration has Done" ); 
							
								WAIT("",5.0);
							}
						
							STOP_TIMEOUT; 
					
							if ( IS_OK && pszNetworkAnalyzerStateFiles[iNetworkAnalyzerStateFileIndex] && (strlen(pszNetworkAnalyzerStateFiles[iNetworkAnalyzerStateFileIndex])))
							{
								sprintf( szFormatedString , "Network Analyzer :: Saving state (%s)" , pszNetworkAnalyzerStateFiles[iNetworkAnalyzerStateFileIndex] );   //1
								LOG(CLB_LINE_NORMAL, szFormatedString ); 
				
								DRV_NetworkAnalyzer_SaveStateAndCalibration ( hNetworkAnalyzer , pszNetworkAnalyzerStateFiles[iNetworkAnalyzerStateFileIndex] );
							}
						}
					
						if ( pszPostEcal_Instruction && ( strlen(pszPostEcal_Instruction) > 1 ))
						{
							INSTRUCTION(pszPostEcal_Instruction,pszPostEcal_Instruction_Pic);
						}
					}
			
					if ( iNetworkAnalyzerStateFileIndex > iDB_NumberOfNetworkFiles )
						continue;
					
					START_TIMEOUT("",lfDB_MeasureTimeout); 
		
					CHK_STDERR( DRV_NetworkAnalyzer_GetPointsNum( hNetworkAnalyzer , &iActualyPointsNumber ));  

					CHK_STDERR( DRV_NetworkAnalyzer_GetFrequency( hNetworkAnalyzer , &lfStartFrequency, &lfStopFrequency )); 

					if ( iDB_GetFromTraceNumber > 0 )
					{
						WAIT("",lfDB_MeasureDelay );

						LOG(CLB_LINE_NORMAL, "Reading Trace.");  
			
						CHK_STDERR( DRV_NetworkAnalyzer_GetTrace ( hNetworkAnalyzer , iDB_GetFromTraceNumber , 0 , 0 , lfDB_MeasureTimeout , &pFrequencyData , &pTraceData , &iActualyPointsNumber ));
					}
			
					if ( pTraceData == NULL )
					{
						bEnableToSaveCallibration = 0;
						break;
					}
		
					if ( pFrequencyData )
					{
						lfStartFrequency = pFrequencyData[0];
						lfStopFrequency = pFrequencyData[iActualyPointsNumber-1];
					}
			
					if ( bDB_AllowExtrapolation )
					{
						if (( lfDB_OrigStartFrequency != 0.0 ) && ( lfDB_OrigStopFrequency != 0.0 ) && (( lfDB_OrigStartFrequency != lfStartFrequency ) || ( lfDB_OrigStopFrequency != lfStopFrequency ) || ( iActualyPointsNumber != iDB_NumberOfPoints )))
						{
							if ( iDB_NumberOfRanges > 1 )
							{
								iIndex = (iActualyPointsNumber-1);
				
								iLastRange = iDB_LastExtrapolationRangeNumber-1;
				
								lfOutputStartFrequency = pFrequencyData[iIndex];  
				
								for ( ; iIndex >= 0; iIndex-- )
								{
									if ( pDB_RangesList[iIndex] >= iLastRange )
										continue;
					
									iIndex++;
					
									iInputStartIndex = iIndex; 
									iInputActualyPointsNumber = iActualyPointsNumber - iIndex;
					
									iOutputNumberOfPoints = iDB_NumberOfPoints - iActualyPointsNumber;
					
									break;
								}													 
							}
							else
							{
								iInputActualyPointsNumber = iActualyPointsNumber;
								lfOutputStartFrequency = lfDB_OrigStartFrequency;
								iOutputNumberOfPoints = iDB_NumberOfPoints;
								iInputStartIndex = 0;
							}
			
							MTH_LinearExtrapolationArray( pFrequencyData , pTraceData , iActualyPointsNumber , iInputStartIndex , iInputActualyPointsNumber , iOutputNumberOfPoints , lfOutputStartFrequency , lfDB_OrigStopFrequency , &pOutputFrequencyTrace  , &pOutputDataTrace );
			
							if ( iDB_NumberOfRanges > 1 )
							{
								if ( pOutputDataTrace )
								{
									iIndex = (iActualyPointsNumber-1);  
			
									iLastRange++;
			
									index = 1;
				
									for ( --index ; iIndex < iDB_NumberOfPoints; iIndex++ )  
									{
										for ( index = 0; index < iOutputNumberOfPoints; index++ )   
											if ( pOutputFrequencyTrace[index] < pFrequencyData[iIndex] )
												continue;
											else
												break;
					
										if ( index > iOutputNumberOfPoints )
											break;
					
										pTraceData[iIndex] = pOutputDataTrace[index];
										pFrequencyData[iIndex] = pOutputFrequencyTrace[index];
										pDB_RangesList[iIndex] = iLastRange;
									}
			
									iActualyPointsNumber = iDB_NumberOfPoints;
								}
							}
							else
							{
								FREE( pFrequencyData );
								FREE( pTraceData );
						
								pFrequencyData = pOutputFrequencyTrace;
								pTraceData = pOutputDataTrace;
						
								iActualyPointsNumber = iDB_NumberOfPoints;  
						
								pOutputDataTrace = NULL;
								pOutputFrequencyTrace = NULL;
							}
						}
					}
			
					if ( pszCalibrated_With_Other_Path && ( strlen(pszCalibrated_With_Other_Path) > 1 ))
					{
						GetVarCalibrationByName( clb, pszCalibrated_With_Other_Path , -1 , &pOldCalibFrequencyList , &pOldCalibFactorList , &iOldNumOfCalibPoints , &lfLastCalibrationDate );   
							
						IF ((( iOldNumOfCalibPoints == 0 ) || ( pOldCalibFrequencyList == 0 ) || ( pOldCalibFactorList == 0 )) , "Calibration is not found." );
				
						if ( iOldNumOfCalibPoints == iActualyPointsNumber )
							for ( iIndex=0; iIndex < iActualyPointsNumber; iIndex++ )
								pTraceData[iIndex] -= pOldCalibFactorList[iIndex];
				
						FREE(pOldCalibFrequencyList);
						FREE(pOldCalibFactorList);	
					}
			
					if ( bDB_DisableResults == 0 )
					{
						if (( bDB_DisableDeltaResults == 0 ) && ( bDB_DisableToStoreCalibration == 0 ))
						{
							GetVarCurrentCalibration( clb, iRangeIndex , &pOldCalibFrequencyList , &pOldCalibFactorList , &iOldNumOfCalibPoints , &lfLastCalibrationDate );   
	
							if ( iOldNumOfCalibPoints )
							{
								CALLOC_ERR( pTraceDeltaData , iDB_NumberOfPoints , sizeof(double));
	
								if ( iOldNumOfCalibPoints == iActualyPointsNumber )
									for ( iIndex=0; iIndex < iActualyPointsNumber; iIndex++ )
										pTraceDeltaData[iIndex] = pTraceData[iIndex] - pOldCalibFactorList[iIndex];
							}
						}
				
						iCurrentResultIndex++;
						iResultNumber = iCurrentResultIndex;

						GET_RESULT_GRAPH_ITEM(iResultNumber,pGraphItem);
						ADD_TRACE_TO_RESULT_GRAPH(iResultNumber,pGraphItem,pTraceData,iActualyPointsNumber,0,iActualyPointsNumber,lfStartFrequency,lfStopFrequency,"Cal Trace", VAL_GREEN );
		
						RESULT_CONST_NUM(iResultNumber,CLB_RESULT_GRAPH,"Cal Trace", pGraphItem , "Calibration Trace" );
		
						if ( bDB_AnalyzeWorstCaseResults )
						{
							GET_MAX_MIN_SPECS_NUMBER( iResultNumber , pPointerToMinSpec, pPointerToMaxSpec, iSpecValuesCount, iSpecFloatType, lfSpecFloatValue );
					
							if ( pPointerToMinSpec && pPointerToMaxSpec && ( iSpecValuesCount >= iActualyPointsNumber ))
							{
								for ( iIndex = 0; iIndex < iActualyPointsNumber; iIndex++ )
								{
									lfWorstCaseCalculation = pPointerToMinSpec[iIndex] - pTraceData[iIndex];
							
									if (( lfWorstCaseCalculation > lfWorstCaseValue ) || ( iIndex == 0 ))
									{
										lfWorstCaseValue = lfWorstCaseCalculation;
										iWorstCaseIndex = iIndex;
									}
							
									lfWorstCaseCalculation = pTraceData[iIndex] - pPointerToMaxSpec[iIndex];   
							
									if ( lfWorstCaseCalculation > lfWorstCaseValue )
									{
										lfWorstCaseValue = lfWorstCaseCalculation;
										iWorstCaseIndex = iIndex;
									}
							
								}
							}
					
							iCurrentResultIndex++;
							iResultNumber = iCurrentResultIndex;
					
							sprintf( szFormatedVariable , "%0.3lf GHz" ,  (pFrequencyData[iWorstCaseIndex] / 1E9) );
					
							RESULT_CONST_NUM(iResultNumber,CLB_RESULT_DOUBLE, szFormatedVariable , pTraceData[iWorstCaseIndex] , "Worst Case Value" );
						}
				
						WAIT_LAST_RESULT_STATUS(iResultStatus);
		
						if ( iResultStatus != RUN_STATUS_PASS )  
							bEnableToSaveCallibration = 0;
		
						if ( pTraceDeltaData && ( bDB_DisableDeltaResults == 0 ))
						{
							iCurrentResultIndex++;
							iResultNumber = iCurrentResultIndex;

							GET_RESULT_GRAPH_ITEM(iResultNumber,pGraphItem);
							ADD_TRACE_TO_RESULT_GRAPH(iResultNumber,pGraphItem,pTraceDeltaData,iActualyPointsNumber,0,iActualyPointsNumber,lfStartFrequency,lfStopFrequency,"Delta Trace", VAL_BLUE );
		
							FormatDateTimeString ( lfLastCalibrationDate , "%c" , szFormatedString , LOW_STRING );

							RESULT_CONST_NUM(iResultNumber,CLB_RESULT_GRAPH, szFormatedString , pGraphItem , "Calibration Delta" );
					
							if ( bDB_AnalyzeWorstCaseResults )
							{
								GET_MAX_MIN_SPECS_NUMBER( iResultNumber , pPointerToMinSpec, pPointerToMaxSpec, iSpecValuesCount, iSpecFloatType, lfSpecFloatValue );
					
								if ( pPointerToMinSpec && pPointerToMaxSpec && ( iSpecValuesCount >= iActualyPointsNumber ))
								{
									for ( iIndex = 0; iIndex < iActualyPointsNumber; iIndex++ )
									{
										lfWorstCaseCalculation = pPointerToMinSpec[iIndex] - pTraceDeltaData[iIndex];
							
										if (( lfWorstCaseCalculation > lfWorstCaseValue ) || ( iIndex == 0 ))
										{
											lfWorstCaseValue = lfWorstCaseCalculation;
											iWorstCaseIndex = iIndex;
										}
							
										lfWorstCaseCalculation = pTraceDeltaData[iIndex] - pPointerToMaxSpec[iIndex];   
							
										if ( lfWorstCaseCalculation > lfWorstCaseValue )
										{
											lfWorstCaseValue = lfWorstCaseCalculation;
											iWorstCaseIndex = iIndex;
										}
							
									}
								}
						
								iCurrentResultIndex++;
								iResultNumber = iCurrentResultIndex;
					
								sprintf( szFormatedVariable , "%0.3lf GHz" ,  (pFrequencyData[iWorstCaseIndex] / 1E9)  );
					
								RESULT_CONST_NUM(iResultNumber,CLB_RESULT_DOUBLE, szFormatedVariable , pTraceDeltaData[iWorstCaseIndex] , "Worst Case Value" );
							}
						}
			
						if ( iDB_VSWR_TraceNumber > 0 )
						{
							CHK_STDERR( DRV_NetworkAnalyzer_GetTrace ( hNetworkAnalyzer , iDB_VSWR_TraceNumber , 0 , 0 , lfDB_MeasureTimeout , NULL , &pVSWRData , &iVSWRActualyPointsNumber ));
			
							iCurrentResultIndex++;
							iResultNumber = iCurrentResultIndex;

							GET_RESULT_GRAPH_ITEM(iResultNumber,pGraphItem);
							ADD_TRACE_TO_RESULT_GRAPH(iResultNumber,pGraphItem,pVSWRData,iVSWRActualyPointsNumber,iRangeStartIndex,iVSWRActualyPointsNumber,lfStartFrequency,lfStopFrequency,"VSWR Trace", VAL_DK_YELLOW );
		
							RESULT_CONST_NUM(iResultNumber,CLB_RESULT_GRAPH, "" , pGraphItem , "VSWR" );  
					
							if ( bDB_AnalyzeWorstCaseResults )
							{
								GET_MAX_MIN_SPECS_NUMBER( iResultNumber , pPointerToMinSpec, pPointerToMaxSpec, iSpecValuesCount, iSpecFloatType, lfSpecFloatValue );
					
								if ( pPointerToMinSpec && pPointerToMaxSpec && ( iSpecValuesCount >= iVSWRActualyPointsNumber ))
								{
									for ( iIndex = iRangeStartIndex; iIndex < iVSWRActualyPointsNumber; iIndex++ )
									{
										lfWorstCaseCalculation = pVSWRData[iIndex] - pPointerToMaxSpec[iIndex];   
							
										if (( lfWorstCaseCalculation > lfWorstCaseValue ) || ( iIndex == 0 ))
										{
											lfWorstCaseValue = lfWorstCaseCalculation;
											iWorstCaseIndex = iIndex;
										}
							
									}
								}
					
								iCurrentResultIndex++;
								iResultNumber = iCurrentResultIndex;
					
								sprintf( szFormatedVariable , "%0.3lf GHz" ,  (pFrequencyData[iWorstCaseIndex] / 1E9)  );
					
								RESULT_CONST_NUM(iResultNumber,CLB_RESULT_DOUBLE, szFormatedVariable , pVSWRData[iWorstCaseIndex] , "Worst Case Value" );
							}
						}
		
						STOP_TIMEOUT;
	
						if (( bDB_DisableToStoreCalibration == 0 ) && bEnableToSaveCallibration && pFrequencyData && pTraceData )
						{
							GetCurrentDateTime( &lfNewCalibrationDate );   

							LOG(CLB_LINE_NORMAL, "Saving Loss.");   

							WAIT_LAST_LOG_DISPLAYED;
					
							START_TIMEOUT("",(60.0 * iActualyPointsNumber / 1000.0));

							SetVarCurrentCalibration( clb, iRangeIndex , (!iRangeIndex) , pFrequencyData , pTraceData , iActualyPointsNumber ); 
				
							STOP_TIMEOUT;
						}
					}
				}
			}
		}
		
	}
	else  //=================================== Signal Generator vs Spectrum Analyzer ===================================================//
	{
		DRIVER_MANAGER_CALIBRATION_GelFactor							= (tfDRIVER_MANAGER_CALIBRATION_GelFactor) GetProcAddress( clb->hDriverManagerLibrary , "DRIVER_MANAGER_CALIBRATION_GelFactor" );	    
		DRIVER_MANAGER_CALIBRATION_Gel_3D_Factor						= (tfDRIVER_MANAGER_CALIBRATION_Gel_3D_Factor) GetProcAddress( clb->hDriverManagerLibrary , "DRIVER_MANAGER_CALIBRATION_Gel_3D_Factor" );

		if ( bForceSignalGenerator )
		{
			if ( hSignalGenerator == 0 )
			{
				GET_SG_EQUIPMENT_HANDLE(hSignalGenerator); 
			}
			
			DRV_SignalGenerator_Reset									= (tfDRV_SignalGenerator_Reset) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SignalGenerator_Reset" );	    
			DRV_SignalGenerator_SetPower								= (tfDRV_SignalGenerator_SetPower) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SignalGenerator_SetPower" );             
			DRV_SignalGenerator_SetFrequency							= (tfDRV_SignalGenerator_SetFrequency) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SignalGenerator_SetFrequency" ); 
			DRV_SignalGenerator_RF_On									= (tfDRV_SignalGenerator_RF_On) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SignalGenerator_RF_On" );	    
			DRV_SignalGenerator_RF_Off 									= (tfDRV_SignalGenerator_RF_Off) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SignalGenerator_RF_Off" );	    
			DRV_SignalGenerator_RecallState								= (tfDRV_SignalGenerator_RecallState) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SignalGenerator_RecallState" );	    
		}
		
		if ( bForcePowerMeter )
		{
			if ( hPowerMeter == 0 )
			{
				GET_PM_EQUIPMENT_HANDLE(hPowerMeter);
			}

			DRV_PowerMeter_Reset										= (tfDRV_PowerMeter_Reset) GetProcAddress( clb->hDriverManagerLibrary , "DRV_PowerMeter_Reset" );
			DRV_PowerMeter_SetActiveChannel								= (tfDRV_PowerMeter_SetActiveChannel) GetProcAddress( clb->hDriverManagerLibrary , "DRV_PowerMeter_SetActiveChannel" );
			DRV_PowerMeter_SetMode              						= (tfDRV_PowerMeter_SetMode) GetProcAddress( clb->hDriverManagerLibrary , "DRV_PowerMeter_SetMode" );
			DRV_PowerMeter_SetActivePort        						= (tfDRV_PowerMeter_SetActivePort) GetProcAddress( clb->hDriverManagerLibrary , "DRV_PowerMeter_SetActivePort" );
			DRV_PowerMeter_SetFrequency         						= (tfDRV_PowerMeter_SetFrequency) GetProcAddress( clb->hDriverManagerLibrary , "DRV_PowerMeter_SetFrequency" );
			DRV_PowerMeter_InitSweep            						= (tfDRV_PowerMeter_InitSweep) GetProcAddress( clb->hDriverManagerLibrary , "DRV_PowerMeter_InitSweep" );
			DRV_PowerMeter_ReadCWpower          						= (tfDRV_PowerMeter_ReadCWpower) GetProcAddress( clb->hDriverManagerLibrary , "DRV_PowerMeter_ReadCWpower" );
			DRV_PowerMeter_SetContinuesSweep							= (tfDRV_PowerMeter_SetContinuesSweep) GetProcAddress( clb->hDriverManagerLibrary , "DRV_PowerMeter_SetContinuesSweep" );
		}
		
		if ( bForceSpectrumAnalyzer )
		{
			if ( hSpectrumAnalyzer == 0 )
			{
				GET_SA_EQUIPMENT_HANDLE(hSpectrumAnalyzer);
			}
			
			DRV_SpectrumAnalyzer_Recall									= (tfDRV_SpectrumAnalyzer_Recall) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SpectrumAnalyzer_Recall" );
			DRV_SpectrumAnalyzer_SaveState								= (tfDRV_SpectrumAnalyzer_SaveState) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SpectrumAnalyzer_SaveState" );
			DRV_SpectrumAnalyzer_SetFrequency							= (tfDRV_SpectrumAnalyzer_SetFrequency) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SpectrumAnalyzer_SetFrequency" );	
			DRV_SpectrumAnalyzer_InitiateMeasure						= (tfDRV_SpectrumAnalyzer_InitiateMeasure) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SpectrumAnalyzer_InitiateMeasure" );	
			DRV_SpectrumAnalyzer_SearchMarkerPeak						= (tfDRV_SpectrumAnalyzer_SearchMarkerPeak) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SpectrumAnalyzer_SearchMarkerPeak" );
			DRV_SpectrumAnalyzer_GetMarkerAmplitude   					= (tfDRV_SpectrumAnalyzer_GetMarkerAmplitude) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SpectrumAnalyzer_GetMarkerAmplitude" ); 
			DRV_SpectrumAnalyzer_SetReferenceLevel						= (tfDRV_SpectrumAnalyzer_SetReferenceLevel) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SpectrumAnalyzer_SetReferenceLevel" ); 
			DRV_SpectrumAnalyzer_Attenuator								= (tfDRV_SpectrumAnalyzer_Attenuator) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SpectrumAnalyzer_Attenuator" ); 
			DRV_SpectrumAnalyzer_GetAttenuator							= (tfDRV_SpectrumAnalyzer_GetAttenuator) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SpectrumAnalyzer_GetAttenuator" ); 
			DRV_SpectrumAnalyzer_GetReferenceLevel						= (tfDRV_SpectrumAnalyzer_GetReferenceLevel) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SpectrumAnalyzer_GetReferenceLevel" ); 
			DRV_SpectrumAnalyzer_Reset 									= (tfDRV_SpectrumAnalyzer_Reset) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SpectrumAnalyzer_Reset" );
			DRV_SpectrumAnalyzer_NoiseFigure_CalibrateNow				= (tfDRV_SpectrumAnalyzer_NoiseFigure_CalibrateNow) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SpectrumAnalyzer_NoiseFigure_CalibrateNow" );
			DRV_SpectrumAnalyzer_WaitForIntrumentDone					= (tfDRV_SpectrumAnalyzer_WaitForIntrumentDone) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SpectrumAnalyzer_WaitForIntrumentDone" );
			DRV_SpectrumAnalyzer_NoiseFigure_SetLossCompensationTable	= (tfDRV_SpectrumAnalyzer_NoiseFigure_SetLossCompensationTable) GetProcAddress( clb->hDriverManagerLibrary , "DRV_SpectrumAnalyzer_NoiseFigure_SetLossCompensationTable");
		}
			
		if ( bNoStimulusFound )
		{
			//======================== Measure Equipment BuildIn Calibrations ===========================================================//
			
			if ( hSpectrumAnalyzer && ( bForcePowerMeter == 0 )) 
			{
				sprintf( szFormatedVariable , "Calibration_%d_%d_SA_IsANoiseSource" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );  
				bDB_SA_IsANoiseSource = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable );  
				
				sprintf( szFormatedVariable , "Calibration_%d_%d_Timeout" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );
				lfDB_Timeout = GetVarDouble( clb, VARTYPE_EQUIPMENT_USE , szFormatedVariable , hSpectrumAnalyzer );  
				
				if ( bDB_SA_IsANoiseSource ) //------------------------------- Noise Source Calibration ------------------------------//
				{
					iTestError = -1;
					
					sprintf( szFormatedVariable , "Calibration_NoiseSource_%d_%d_StateFile" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );
					
					pszSpectrumAnalyzerStateFile = GetVarString( clb, VARTYPE_EQUIPMENT_USE , szFormatedVariable , hSpectrumAnalyzer ); 
					
					if (( pszSpectrumAnalyzerStateFile == NULL ) || ( strlen(pszSpectrumAnalyzerStateFile) == 0 ))
					{
						FREE(pszSpectrumAnalyzerStateFile);
	
						pszSpectrumAnalyzerStateFile = GetVarString( clb, VARTYPE_EQUIPMENT , "Calibration_NoiseSource_StateFile" , hSpectrumAnalyzer );  
					}

					sprintf( szFormatedString , "Loading spectrum analyzer state (%s)" , pszSpectrumAnalyzerStateFile );  
					LOG(CLB_LINE_NORMAL, szFormatedString ); 

					CHK_STDERR( DRV_SpectrumAnalyzer_Recall ( hSpectrumAnalyzer , pszSpectrumAnalyzerStateFile )); 
					
					CHK_STDERR( DRV_SpectrumAnalyzer_WaitForIntrumentDone ( hSpectrumAnalyzer , lfDB_Timeout ));
					
					sprintf( szFormatedVariable , "Calibration_%d_%d_SA_NoiseSource_FillTables" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );  
					bDB_SA_NoiseSource_FillTables = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable ); 
				
					if ( bDB_SA_NoiseSource_FillTables )
					{
						sprintf( szFormatedVariable , "Calibration_%d_%d_SA_NoiseSource_LossTable_Before_PathName" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 ); 
						pszNoiseSourceFillTableFromPath = GetVarString( clb, VARTYPE_TEST, szFormatedVariable );
						
						if ( pszNoiseSourceFillTableFromPath && ( strlen(pszNoiseSourceFillTableFromPath)))
						{
							GetVarCalibrationByName( clb, pszNoiseSourceFillTableFromPath , -1 , &pOldCalibFrequencyList , &pOldCalibFactorList , &iOldNumOfCalibPoints , &lfLastCalibrationDate );   
							
							IF ((( iOldNumOfCalibPoints == 0 ) || ( pOldCalibFrequencyList == 0 ) || ( pOldCalibFactorList == 0 )) , "Calibration is not found." );
							
							CHK_STDERR( DRV_SpectrumAnalyzer_NoiseFigure_SetLossCompensationTable( hSpectrumAnalyzer , 0 , pOldCalibFrequencyList, pOldCalibFactorList , iOldNumOfCalibPoints ));	
							
							FREE(pOldCalibFrequencyList);
							FREE(pOldCalibFactorList);
						}
							
						FREE(pszNoiseSourceFillTableFromPath);
						
						sprintf( szFormatedVariable , "Calibration_%d_%d_SA_NoiseSource_LossTable_After_PathName" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 ); 
						pszNoiseSourceFillTableFromPath = GetVarString( clb, VARTYPE_TEST, szFormatedVariable );
						
						if ( pszNoiseSourceFillTableFromPath && ( strlen(pszNoiseSourceFillTableFromPath)))
						{
							GetVarCalibrationByName( clb, pszNoiseSourceFillTableFromPath , -1 , &pOldCalibFrequencyList , &pOldCalibFactorList , &iOldNumOfCalibPoints , &lfLastCalibrationDate );   
							
							IF ((( iOldNumOfCalibPoints == 0 ) || ( pOldCalibFrequencyList == 0 ) || ( pOldCalibFactorList == 0 )) , "Calibration is not found." );
							
							CHK_STDERR( DRV_SpectrumAnalyzer_NoiseFigure_SetLossCompensationTable( hSpectrumAnalyzer , 1 , pOldCalibFrequencyList, pOldCalibFactorList , iOldNumOfCalibPoints ));	
							
							FREE(pOldCalibFrequencyList);
							FREE(pOldCalibFactorList);
						}
									
						FREE(pszNoiseSourceFillTableFromPath);
					}
					
					sprintf( szFormatedVariable , "Calibration_%d_%d_SA_NoiseSource_CalibrateNow" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );  
					bDB_SA_NoiseSource_CalibrateNow = GetVarInt( clb, VARTYPE_TEST , szFormatedVariable ); 
					
					if ( bDB_SA_NoiseSource_CalibrateNow )
					{
						LOG(CLB_LINE_NORMAL, "Calibrating Noise Figure." ); 
					
						CHK_STDERR( DRV_SpectrumAnalyzer_NoiseFigure_CalibrateNow ( hSpectrumAnalyzer , lfDB_Timeout ));  
					}
					
					CHK_STDERR( DRV_SpectrumAnalyzer_WaitForIntrumentDone ( hSpectrumAnalyzer , lfDB_Timeout ));
					
					sprintf( szFormatedString , "Saveing spectrum analyzer state (%s)" , pszSpectrumAnalyzerStateFile );  
					LOG(CLB_LINE_NORMAL, szFormatedString ); 
					
					CHK_STDERR( DRV_SpectrumAnalyzer_SaveState ( hSpectrumAnalyzer , pszSpectrumAnalyzerStateFile )); 
					
					iTestError = 0;
				}
				
			}
			
		}
		else
		{
			//======================== Stimulus vs Measure Equipment ===========================================================//
		
			for( iAuxilityIndex = 0; iAuxilityIndex < 2; iAuxilityIndex++ )
			{
				if ( iAuxilityIndex ) 
				{
					if ( bDB_Use_Aux_Cable == 0 )
						break;
				}
		
				do
				{
					if ( iAuxilityIndex )
					{
						bUserAcceptCalibration = 1;
		
						if (( iAuxilityPresentPointsNumber == iAuxilityActualyPointsNumber ) && ( iAuxilityActualyPointsNumber != 0 ))
						{
							bUserAcceptCalibration = ShowMessage ( 0 , INSTR_TYPE_YES_NO , "Auxiliary Cable", "Do you want to calibrate the Auxiliary Cable Factors?" , NULL );
			
							if ( bUserAcceptCalibration == 0 )
								break;
		
						}
		
						INSTRUCTION(pszAux_Cable_Instruction,pszAux_Cable_InstructionPic);  
					}
				   
					sprintf( szFormatedVariable , "Calibration_%d_%d_StartFrequency" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );    
					lfDB_StartFrequency = GetVarDouble( clb, VARTYPE_TEST , szFormatedVariable ); 
					
					sprintf( szFormatedVariable , "Calibration_%d_%d_StopFrequency" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );    
					lfDB_StopFrequency = GetVarDouble( clb, VARTYPE_TEST , szFormatedVariable );   

					sprintf( szFormatedString , "Calibration_%d_%d_SG_PathPart_Power" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 ); 
					lfDB_Power = GetVarDouble( clb, VARTYPE_TEST , szFormatedString );

					sprintf( szFormatedString , "Calibration_%d_%d_SG_PathPart_MaxGainOffset" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 ); 
					lfDB_MaxGainOffset = GetVarDouble( clb, VARTYPE_TEST ,  szFormatedString );    

					sprintf( szFormatedString , "Calibration_%d_%d_MinimumMeasureLimit" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 ); 
					lfDB_MinimumMeasureLimit = GetVarDouble( clb, VARTYPE_TEST ,  szFormatedString );
					
					LOG(CLB_LINE_NORMAL, "Reset signal generator" );
					CHK_STDERR( DRV_SignalGenerator_Reset ( hSignalGenerator )); 

					FREE(pszSignalGeneratorState); 
					//---------------------- Signal Generator State -----------------------------------------------------------//
					sprintf( szFormatedVariable , "Calibration_%d_%d_StateFile" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );    
					pszSignalGeneratorState = GetVarString( clb, VARTYPE_EQUIPMENT_USE , szFormatedVariable , hSignalGenerator );

					if (( pszSignalGeneratorState == NULL ) || ( strlen(pszSignalGeneratorState) == 0 ))
					{
						FREE(pszSignalGeneratorState);
	
						pszSignalGeneratorState = GetVarString( clb, VARTYPE_EQUIPMENT , "Calibration_StateFile" , hSignalGenerator );  
					}

					if (( pszSignalGeneratorState ) && ( strlen(pszSignalGeneratorState)) && ( pszSignalGeneratorState[0] != '.')) 
					{
						sprintf( szFormatedString , "Signal Gererator :: Loading state (%s)" , pszSignalGeneratorState );   //1
						LOG(CLB_LINE_NORMAL, szFormatedString ); 
					
						CHK_STDERR( DRV_SignalGenerator_RecallState( hSignalGenerator , pszSignalGeneratorState ));   
					}

					if ( hSpectrumAnalyzer && ( bForcePowerMeter == 0 ))
					{
						DRV_SpectrumAnalyzer_Reset(hSpectrumAnalyzer);
	
						FREE(pszSpectrumAnalyzerStateFile);
			
						sprintf( szFormatedVariable , "Calibration_%d_%d_StateFile" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );    
						pszSpectrumAnalyzerStateFile = GetVarString( clb, VARTYPE_EQUIPMENT_USE , szFormatedVariable , hSpectrumAnalyzer );  

						if (( pszSpectrumAnalyzerStateFile == NULL ) || ( strlen(pszSpectrumAnalyzerStateFile) == 0 ))
						{
							FREE(pszSpectrumAnalyzerStateFile);
		
							pszSpectrumAnalyzerStateFile = GetVarString( clb, VARTYPE_EQUIPMENT , "Calibration_StateFile" , hSpectrumAnalyzer );  
						}
	
						sprintf( szFormatedString , "Spectrum Analyzer :: Loading  state (%s)" , pszSpectrumAnalyzerStateFile );  
						LOG(CLB_LINE_NORMAL, szFormatedString ); 

						CHK_STDERR( DRV_SpectrumAnalyzer_Recall ( hSpectrumAnalyzer , pszSpectrumAnalyzerStateFile )); 
	
						sprintf( szFormatedVariable , "Calibration_%d_%d_AutoReferenceCalculation" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );
						bDB_AutoReferenceCalculation = GetVarInt( clb, VARTYPE_EQUIPMENT_USE , szFormatedVariable , hSpectrumAnalyzer );    
	
						if ( bDB_AutoReferenceCalculation )
						{
							CHK_STDERR( DRV_SpectrumAnalyzer_SetReferenceLevel( hSpectrumAnalyzer , ( lfDB_Power + lfDB_MaxGainOffset )));
						}
						else
						{
							sprintf( szFormatedVariable , "Calibration_%d_%d_ReferenceLevel" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );  
							iDB_NumberOfReferenceLevels = GetVarDoubleArray( clb, VARTYPE_EQUIPMENT_USE , szFormatedVariable , &vlfDB_ReferenceLevelList , hSpectrumAnalyzer );    
		
							if ( vlfDB_ReferenceLevelList )
							{
								if ( iDB_NumberOfReferenceLevels > 1 )
								{
									lfDB_ReferenceLevel = vlfDB_ReferenceLevelList[iCurrentPathPartIndex];
								}
								else
								{
									lfDB_ReferenceLevel = vlfDB_ReferenceLevelList[0];
								}
							}
			
							CHK_STDERR( DRV_SpectrumAnalyzer_SetReferenceLevel( hSpectrumAnalyzer , lfDB_ReferenceLevel ));
						}
	
						sprintf( szFormatedVariable , "Calibration_%d_%d_Attenuator" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 );   
						lfDB_Attenuator = GetVarDouble( clb, VARTYPE_EQUIPMENT_USE , szFormatedVariable , hSpectrumAnalyzer );   
	
						CHK_STDERR( DRV_SpectrumAnalyzer_Attenuator( hSpectrumAnalyzer , lfDB_Attenuator ));
					}
					else
					{
						sprintf( szFormatedString , "Calibration_%d_%d_ChannelNumber" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 ); 
						iDB_PowerMeterPortNumber = GetVarInt( clb, VARTYPE_EQUIPMENT_USE , szFormatedString , hPowerMeter );   
	
						sprintf( szFormatedString , "Calibration_%d_%d_bDifferentialMeas" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 ); 
						bDB_DifferentialMeas = GetVarDouble( clb, VARTYPE_TEST ,  szFormatedString );
					
						if ( bDB_DifferentialMeas )
						{
							sprintf( szFormatedString , "Calibration_%d_%d_SubChannelNumber" , iCurrentPathIndex+1 , iCurrentPathPartIndex+1 ); 
							iDB_PowerMeterSubPortNumber	= GetVarInt( clb, VARTYPE_EQUIPMENT_USE , szFormatedString , hPowerMeter );   
						}
						
						CHK_STDERR( DRV_PowerMeter_Reset ( hPowerMeter ));
		
						CHK_STDERR( DRV_PowerMeter_SetActiveChannel( hPowerMeter , 1 ));  
	
						CHK_STDERR( DRV_PowerMeter_SetMode ( hPowerMeter , 1 , 0 ));     
	
						CHK_STDERR( DRV_PowerMeter_SetActivePort( hPowerMeter , iDB_PowerMeterPortNumber ));  
						
						if ( bDB_DifferentialMeas )
						{
							CHK_STDERR( DRV_PowerMeter_SetActiveChannel( hPowerMeter , 2 ));  
									
							CHK_STDERR( DRV_PowerMeter_SetMode ( hPowerMeter , 2 , 0 ));  
						
							CHK_STDERR( DRV_PowerMeter_SetActivePort( hPowerMeter , iDB_PowerMeterSubPortNumber ));    
							
							CHK_STDERR( DRV_PowerMeter_SetActiveChannel( hPowerMeter , 1 ));  			
						}																				
					}

					sprintf( szFormatedString , "Set signal generator power to %0.3lf dBm" , lfDB_Power );  
					LOG(CLB_LINE_NORMAL, szFormatedString ); 

					CHK_STDERR( DRV_SignalGenerator_SetPower ( hSignalGenerator , 0 , lfDB_Power )); 
	
					CHK_STDERR( DRV_SignalGenerator_SetFrequency ( hSignalGenerator , 0 , lfDB_StartFrequency )); 

					LOG(CLB_LINE_NORMAL, "Set signal generator power on" );  
	
					CHK_STDERR( DRV_SignalGenerator_RF_On( hSignalGenerator , 0 ));
	
					FREE_CALLOC_ERR( pTraceData , iDB_NumberOfPoints , sizeof(double));
					FREE_CALLOC_ERR( pFrequencyData , iDB_NumberOfPoints , sizeof(double)); 

					for ( iIndex=0; iIndex < iDB_NumberOfPoints; iIndex++ )
					{	 
						sprintf( szFormatedString , "Point == %d ==" , ( iIndex + 1 ));  
						LOG(CLB_LINE_NORMAL, szFormatedString );
		
						lfCurrentFrequency = pDB_FrequencyList[iIndex];
	
						if ( lfCurrentFrequency > lfDB_StopFrequency )
							break;
			
						sprintf( szFormatedString , "Set signal generator frequency %0.3lf MHz" , ( lfCurrentFrequency / 1E6 ));  
						LOG(CLB_LINE_NORMAL, szFormatedString ); 

						CHK_STDERR( DRV_SignalGenerator_SetFrequency ( hSignalGenerator , 0 , lfCurrentFrequency ));     

						if ( hSpectrumAnalyzer && ( bForcePowerMeter == 0 )) 
						{
							sprintf( szFormatedString , "Set spectrum frequency %0.3lf MHz" , ( lfCurrentFrequency / 1E6 ));  
							LOG(CLB_LINE_NORMAL, szFormatedString );
	
							CHK_STDERR( DRV_SpectrumAnalyzer_SetFrequency ( hSpectrumAnalyzer , lfCurrentFrequency ));  
						}
						else
						{
							sprintf( szFormatedString , "Set power meter frequency %0.3lf MHz" , ( lfCurrentFrequency / 1E6 ));  
							LOG(CLB_LINE_NORMAL, szFormatedString );
	
							CHK_STDERR( DRV_PowerMeter_SetFrequency ( hPowerMeter , iDB_PowerMeterPortNumber , lfCurrentFrequency )); 	
							
							if ( bDB_DifferentialMeas )      
							{
								CHK_STDERR( DRV_PowerMeter_SetActiveChannel( hPowerMeter , 2 ));  
								
								CHK_STDERR( DRV_PowerMeter_SetFrequency ( hPowerMeter , iDB_PowerMeterSubPortNumber , lfCurrentFrequency )); 	
								
								CHK_STDERR( DRV_PowerMeter_SetActiveChannel( hPowerMeter , 1 ));  
							}
						}
	
						for ( iTryIndex = 0; iTryIndex < 10; iTryIndex++ )
						{
							WAIT("",lfDB_MeasureDelay);
		
							if ( hSpectrumAnalyzer && ( bForcePowerMeter == 0 )) 
							{
								DRV_SpectrumAnalyzer_InitiateMeasure( hSpectrumAnalyzer ); 
							}
							else
							{
								CHK_STDERR( DRV_PowerMeter_InitSweep( hPowerMeter , 1 )); 
							}
	
							if ( hSpectrumAnalyzer && ( bForcePowerMeter == 0 )) 
							{
								CHK_STDERR( DRV_SpectrumAnalyzer_SearchMarkerPeak( hSpectrumAnalyzer , 1 ));  
	
								CHK_STDERR( DRV_SpectrumAnalyzer_GetMarkerAmplitude( hSpectrumAnalyzer , 1 , &lfMeasurePower )); 
							}
							else
							{
								CHK_STDERR( DRV_PowerMeter_ReadCWpower ( hPowerMeter , 1 , 20.0 , &lfMeasurePower ));  
								
								if ( bDB_DifferentialMeas )      
								{			
									CHK_STDERR( DRV_PowerMeter_SetContinuesSweep( hPowerMeter , 1 )); 
										
									CHK_STDERR( DRV_PowerMeter_SetActiveChannel( hPowerMeter , 2 ));  
									
									CHK_STDERR( DRV_PowerMeter_InitSweep( hPowerMeter , 2 ));  
									
									CHK_STDERR( DRV_PowerMeter_ReadCWpower ( hPowerMeter , 2 , 20.0 , &lfDifferentialMeasurePower ));   
									
									CHK_STDERR( DRV_PowerMeter_SetContinuesSweep( hPowerMeter , 2 )); 
									
									lfDifferentialMeasurePower -= lfMeasurePower;
									
									CHK_STDERR( DRV_PowerMeter_SetActiveChannel( hPowerMeter , 1 ));  
								}
							}
		
							if (( lfMeasurePower < ( lfDB_Power + lfDB_MaxGainOffset )) && ( lfMeasurePower > (-200)))
								break;
						}
	
						lfResult = lfMeasurePower - lfDB_Power;
						
						if ( lfResult < lfDB_MinimumMeasureLimit )
						{
							CONFIRM("Measure fail.\nPlease check connections.\nPress OK to repeat Measurement.",NULL);
							
							iIndex--;
							continue;
						}
						
						pTraceData[iIndex] = lfResult;   
		
						sprintf( szFormatedString , "Measured Power = %0.1lf dBm" , lfMeasurePower );  
						LOG(CLB_LINE_NORMAL, szFormatedString );
	
						if ( hSignalGenerator )  
						{
							DRIVER_MANAGER_CALIBRATION_Gel_3D_Factor( hSignalGenerator , lfDB_Power , lfCurrentFrequency , &lfSignalGeneratorLossFactor );  
	
							if ( lfSignalGeneratorLossFactor != 0.0 )
							{
								sprintf( szFormatedString , "Signal Generator Factor = %0.3lf dBm" , lfSignalGeneratorLossFactor );  
								LOG(CLB_LINE_NORMAL,szFormatedString);
							}																													  
	
							pTraceData[iIndex] -= lfSignalGeneratorLossFactor;
						}
	
						if ( hPowerMeter )  
						{
							DRIVER_MANAGER_CALIBRATION_GelFactor( hPowerMeter , lfCurrentFrequency , &lfPowerMeterLossFactor );  
	
							if ( lfPowerMeterLossFactor != 0.0 )
							{
								sprintf( szFormatedString , "Power Meter Factor = %0.3lf dBm" , lfPowerMeterLossFactor );  
								LOG(CLB_LINE_NORMAL,szFormatedString);
							}

							pTraceData[iIndex] -= lfPowerMeterLossFactor;
						}
	
						if ( hSpectrumAnalyzer && ( bForcePowerMeter == 0 )) 
						{
							DRV_SpectrumAnalyzer_GetReferenceLevel( hSpectrumAnalyzer , &lfCurrentReferenceLevel );
		
							DRIVER_MANAGER_CALIBRATION_Gel_3D_Factor( hSpectrumAnalyzer , lfCurrentReferenceLevel , lfCurrentFrequency , &lfSpectrumAnalyzerLossFactor );  

							if ( lfSpectrumAnalyzerLossFactor < 0.0 )
							{
								sprintf( szFormatedString , "Spectrum Analyzer Factor = %0.3lf dBm" , lfSpectrumAnalyzerLossFactor );  
								LOG(CLB_LINE_NORMAL,szFormatedString);
							}

							pTraceData[iIndex] -= lfSpectrumAnalyzerLossFactor;
						}		
	
						if ( bDB_DifferentialMeas ) 
						{
							sprintf( szFormatedString , "Path Loss = %0.1lf dBm" , pTraceData[iIndex] );  
							LOG(CLB_LINE_NORMAL, szFormatedString );
							
							pTraceData[iIndex] = lfDifferentialMeasurePower;
							
							sprintf( szFormatedString , "Differentia Path Loss = %0.1lf dBm [Forced]" , lfDifferentialMeasurePower );  
							LOG(CLB_LINE_NORMAL, szFormatedString );
						}
						
						sprintf( szFormatedString , "Path Loss = %0.1lf dBm" , pTraceData[iIndex] );  
						LOG(CLB_LINE_NORMAL, szFormatedString );
	
						pFrequencyData[iIndex] = lfCurrentFrequency;
					}

					CHK_STDERR( DRV_SignalGenerator_RF_Off( hSignalGenerator , 0 ));
					
					iActualyPointsNumber = iIndex;

					lfStartFrequency = pFrequencyData[0];
					lfStopFrequency = pFrequencyData[iActualyPointsNumber-1];
		
				} while(0); 
				
		
				if ( bDB_Use_Aux_Cable ) 
				{
					if ( iAuxilityIndex == 0 )
					{														
						pAuxilityTraceData = pTraceData;
						iAuxilityActualyPointsNumber = iActualyPointsNumber;
			
						pTraceData = NULL;
						iActualyPointsNumber = 0;
					}
					else
					{
						if ( bUserAcceptCalibration == 0 )
						{
							iActualyPointsNumber = GetVarDoubleArray( clb, VARTYPE_MEASURE_STORE , "AuxilityCabelLoss" , &pTraceData ); 
					
							pTraceData = realloc( pTraceData , (iDB_NumberOfPoints * sizeof(double))); 
						}
						else 
						{
							SetVarDoubleArray( clb, VARTYPE_MEASURE_STORE , "AuxilityCabelLoss" , pTraceData , iActualyPointsNumber );  
						}
					}
				}
			}
	
			if ( bDB_Use_Aux_Cable && pTraceData && pAuxilityTraceData )  
			{
				for ( iIndex=0; (( iIndex < iActualyPointsNumber ) && ( iIndex < iAuxilityActualyPointsNumber )); iIndex++ )
				{
					pTraceData[iIndex] = pAuxilityTraceData[iIndex] - pTraceData[iIndex];
				}
			}

			if ( bDB_AllowExtrapolation )
			{
				if (( lfDB_OrigStartFrequency != 0.0 ) && ( lfDB_OrigStopFrequency != 0.0 ) && (( lfDB_OrigStartFrequency != lfStartFrequency ) || ( lfDB_OrigStopFrequency != lfStopFrequency ) || ( iActualyPointsNumber != iDB_NumberOfPoints )))
				{
					if ( iDB_NumberOfRanges )
					{
						iIndex = (iActualyPointsNumber-1);
				
						iLastRange = iDB_LastExtrapolationRangeNumber-1;
				
						lfOutputStartFrequency = pFrequencyData[iIndex];  
				
						for ( ; iIndex >= 0; iIndex-- )
						{
							if ( pDB_RangesList[iIndex] >= iLastRange )
								continue;
					
							iIndex++;
					
							iInputStartIndex = iIndex; 
							iInputActualyPointsNumber = iActualyPointsNumber - iIndex;
					
							iOutputNumberOfPoints = iDB_NumberOfPoints - iActualyPointsNumber;
					
							break;
						}													 
					}
					else
					{
						iInputActualyPointsNumber = iActualyPointsNumber;
						lfOutputStartFrequency = lfDB_OrigStartFrequency;
						iOutputNumberOfPoints = iDB_NumberOfPoints;
						iInputStartIndex = 0;
					}
			
					MTH_LinearExtrapolationArray( pFrequencyData , pTraceData , iActualyPointsNumber , iInputStartIndex , iInputActualyPointsNumber , iOutputNumberOfPoints , lfOutputStartFrequency , lfDB_OrigStopFrequency , &pOutputFrequencyTrace  , &pOutputDataTrace );
			
					if ( pOutputDataTrace )
					{
						iIndex = (iActualyPointsNumber-1);  
			
						iLastRange++;
			
						index = 1;
				
						for ( --index ; iIndex < iDB_NumberOfPoints; iIndex++ )  
						{
							for ( index = 0; index < iOutputNumberOfPoints; index++ )   
								if ( pOutputFrequencyTrace[index] < pFrequencyData[iIndex] )
									continue;
								else
									break;
					
							if ( index > iOutputNumberOfPoints )
								break;
					
							pTraceData[iIndex] = pOutputDataTrace[index];
							pFrequencyData[iIndex] = pOutputFrequencyTrace[index];
							pDB_RangesList[iIndex] = iLastRange;
						}
			
						iActualyPointsNumber = iDB_NumberOfPoints;
					}
				}
			}
	
			if ( pszCalibrated_With_Other_Path && ( strlen(pszCalibrated_With_Other_Path) > 1 ))
			{
				GetVarCalibrationByName( clb, pszCalibrated_With_Other_Path , -1 , &pOldCalibFrequencyList , &pOldCalibFactorList , &iOldNumOfCalibPoints , &lfLastCalibrationDate );   
						
				IF ((( iOldNumOfCalibPoints == 0 ) || ( pOldCalibFrequencyList == 0 ) || ( pOldCalibFactorList == 0 )) , "Calibration is not found." );
			
				if ( iOldNumOfCalibPoints == iActualyPointsNumber )
					for ( iIndex=0; iIndex < iActualyPointsNumber; iIndex++ )
						pTraceData[iIndex] -= pOldCalibFactorList[iIndex];
			
				FREE(pOldCalibFrequencyList);
				FREE(pOldCalibFactorList);	
			}
			
			GetVarCurrentCalibration( clb, 0 , &pOldCalibFrequencyList , &pOldCalibFactorList , &iOldNumOfCalibPoints , &lfLastCalibrationDate );   
	
			CALLOC_ERR( pTraceDeltaData , iDB_NumberOfPoints , sizeof(double));
	
			if ( iOldNumOfCalibPoints == iActualyPointsNumber )
				for ( iIndex=0; iIndex < iActualyPointsNumber; iIndex++ )
					pTraceDeltaData[iIndex] = pTraceData[iIndex] - pOldCalibFactorList[iIndex];
	
			iRangeLength = iActualyPointsNumber;
	
			bEnableToSaveCallibration = 1;
	
			if ( pFrequencyData )
			{
				lfStartFrequency = pFrequencyData[0];
				lfStopFrequency = pFrequencyData[iActualyPointsNumber-1];  
			}
	
			for ( iRangeIndex = 0; (( iRangeIndex < iDB_NumberOfRanges ) || ( iRangeIndex < 1 )); iRangeIndex++ )
			{
				if ( iDB_NumberOfRanges )
				{
					for ( index = 0; index < iActualyPointsNumber; index++ ) 
						if ( pDB_RangesList[index] == iRangeIndex )
						{
							iRangeStartIndex = index;	
					
							lfStartFrequency = pFrequencyData[iRangeStartIndex];
							break;
						}
			
					for ( ; index < iActualyPointsNumber; index++ ) 
						if ( pDB_RangesList[index] != iRangeIndex )
							break;
			
					lfStopFrequency = pDB_FrequencyList[index-1];  
			
					iRangeLength = index - iRangeStartIndex;
				}
		
				if ( pTraceData == NULL )
				{
					bEnableToSaveCallibration = 0;
					break;
				}
				
				iCurrentResultIndex++;
				iResultNumber = iCurrentResultIndex;

				GET_RESULT_GRAPH_ITEM(iResultNumber,pGraphItem);
				ADD_TRACE_TO_RESULT_GRAPH(iResultNumber,pGraphItem,pTraceData,iActualyPointsNumber,iRangeStartIndex,iRangeLength,lfStartFrequency,lfStopFrequency,"Cal Trace", VAL_GREEN );
		
				RESULT_CONST_NUM(iResultNumber,CLB_RESULT_GRAPH,"Cal Trace", pGraphItem , "Calibration Trace" );
		
				if ( bDB_AnalyzeWorstCaseResults )
				{
					GET_MAX_MIN_SPECS_NUMBER( iResultNumber , pPointerToMinSpec, pPointerToMaxSpec, iSpecValuesCount, iSpecFloatType, lfSpecFloatValue );
					
					if ( pPointerToMinSpec && pPointerToMaxSpec && ( iSpecValuesCount >= iRangeLength ))
					{
						for ( iIndex = iRangeStartIndex; iIndex < iRangeLength; iIndex++ )
						{
							lfWorstCaseCalculation = pPointerToMinSpec[iIndex] - pTraceData[iIndex];
							
							if (( lfWorstCaseCalculation > lfWorstCaseValue ) || ( iIndex == 0 ))
							{
								lfWorstCaseValue = lfWorstCaseCalculation;
								iWorstCaseIndex = iIndex;
							}
							
							lfWorstCaseCalculation = pTraceData[iIndex] - pPointerToMaxSpec[iIndex];   
							
							if ( lfWorstCaseCalculation > lfWorstCaseValue )
							{
								lfWorstCaseValue = lfWorstCaseCalculation;
								iWorstCaseIndex = iIndex;
							}
						}
					}
					
					iCurrentResultIndex++;
					iResultNumber = iCurrentResultIndex;
					
					sprintf( szFormatedVariable , "%0.3lf GHz" ,  (pFrequencyData[iWorstCaseIndex] / 1E9)  );
					
					RESULT_CONST_NUM(iResultNumber,CLB_RESULT_DOUBLE, szFormatedVariable , pTraceData[iWorstCaseIndex] , "Worst Case Value" );
				}
				
				WAIT_LAST_RESULT_STATUS(iResultStatus);
		
				if ( iResultStatus != RUN_STATUS_PASS )  
					bEnableToSaveCallibration = 0;
		
				iCurrentResultIndex++;
				iResultNumber = iCurrentResultIndex;

				GET_RESULT_GRAPH_ITEM(iResultNumber,pGraphItem);
				ADD_TRACE_TO_RESULT_GRAPH(iResultNumber,pGraphItem,pTraceDeltaData,iActualyPointsNumber,iRangeStartIndex,iRangeLength,lfStartFrequency,lfStopFrequency,"Delta Trace", VAL_BLUE );
		
				FormatDateTimeString ( lfLastCalibrationDate , "%c" , szFormatedString , LOW_STRING );

				RESULT_CONST_NUM(iResultNumber,CLB_RESULT_GRAPH, szFormatedString , pGraphItem , "Calibration Delta" );
		
				if ( bDB_AnalyzeWorstCaseResults )
				{
					GET_MAX_MIN_SPECS_NUMBER( iResultNumber , pPointerToMinSpec, pPointerToMaxSpec, iSpecValuesCount, iSpecFloatType, lfSpecFloatValue );
				
					if ( pPointerToMinSpec && pPointerToMaxSpec && ( iSpecValuesCount >= iRangeLength ))
					{
						for ( iIndex = iRangeStartIndex; iIndex < iRangeLength; iIndex++ )
						{
							lfWorstCaseCalculation = pPointerToMinSpec[iIndex] - pTraceDeltaData[iIndex];
						
							if (( lfWorstCaseCalculation > lfWorstCaseValue ) || ( iIndex == 0 ))
							{
								lfWorstCaseValue = lfWorstCaseCalculation;
								iWorstCaseIndex = iIndex;
							}
						
							lfWorstCaseCalculation = pTraceDeltaData[iIndex] - pPointerToMaxSpec[iIndex];   
						
							if ( lfWorstCaseCalculation > lfWorstCaseValue )
							{
								lfWorstCaseValue = lfWorstCaseCalculation;
								iWorstCaseIndex = iIndex;
							}
						}
					}
					
					iCurrentResultIndex++;
					iResultNumber = iCurrentResultIndex;
				
					sprintf( szFormatedVariable , "%0.3lf GHz" ,  (pFrequencyData[iWorstCaseIndex] / 1E9)  );
				
					RESULT_CONST_NUM(iResultNumber,CLB_RESULT_DOUBLE, szFormatedVariable , pTraceDeltaData[iWorstCaseIndex] , "Worst Case Value" );
				}
			
				if ( iDB_VSWR_TraceNumber )
				{
					iCurrentResultIndex++;
					iResultNumber = iCurrentResultIndex;

					GET_RESULT_GRAPH_ITEM(iResultNumber,pGraphItem);
					ADD_TRACE_TO_RESULT_GRAPH(iResultNumber,pGraphItem,pVSWRData,iVSWRActualyPointsNumber,iRangeStartIndex,iVSWRActualyPointsNumber,lfStartFrequency,lfStopFrequency,"VSWR Trace", VAL_DK_YELLOW );
		
					RESULT_CONST_NUM(iResultNumber,CLB_RESULT_GRAPH, szFormatedString , pGraphItem , "VSWR" );  
					
					if ( bDB_AnalyzeWorstCaseResults )
					{
						GET_MAX_MIN_SPECS_NUMBER( iResultNumber , pPointerToMinSpec, pPointerToMaxSpec, iSpecValuesCount, iSpecFloatType, lfSpecFloatValue );
					
						if ( pPointerToMinSpec && pPointerToMaxSpec && ( iSpecValuesCount >= iVSWRActualyPointsNumber ))
						{
							for ( iIndex = iRangeStartIndex; iIndex < iVSWRActualyPointsNumber; iIndex++ )
							{
								lfWorstCaseCalculation = pVSWRData[iIndex] - pPointerToMaxSpec[iIndex];   
							
								if (( lfWorstCaseCalculation > lfWorstCaseValue ) || ( iIndex == 0 ))
								{
									lfWorstCaseValue = lfWorstCaseCalculation;
									iWorstCaseIndex = iIndex;
								}
							}
						}
					
						iCurrentResultIndex++;
						iResultNumber = iCurrentResultIndex;
					
						sprintf( szFormatedVariable , "%0.3lf GHz" ,  (pFrequencyData[iWorstCaseIndex] / 1E9)  );
					
						RESULT_CONST_NUM(iResultNumber,CLB_RESULT_DOUBLE, szFormatedVariable , pVSWRData[iWorstCaseIndex] , "Worst Case Value" );
					}
				}
			}
	
			if ( bEnableToSaveCallibration )
			{
				GetCurrentDateTime( &lfNewCalibrationDate );   

				LOG(CLB_LINE_NORMAL, "Saving Loss.");   

				WAIT_LAST_LOG_DISPLAYED;
					
				START_TIMEOUT("",(60.0 * iActualyPointsNumber / 1000.0));

				SetVarCurrentCalibration( clb, 0 , 1 , pDB_FrequencyList , pTraceData , iActualyPointsNumber ); 

				STOP_TIMEOUT;
			}
		}
	}
	
CATCH

	UPDATE_ERROR(StdError);
	
	if ( StdError.pszErrorDescription )
	{
		LOG_END(CLB_LINE_WARNING, (char*)StdError.pszErrorDescription );
	}
	
	iTestError = -1;
	
FINALLY
	
	if ( hSignalGenerator )
		DRV_SignalGenerator_RF_Off( hSignalGenerator , 0 ); 
		
	FREE(pszSpectrumAnalyzerStateFile);
	FREE(pszSignalGeneratorState);
	
	FREE(pszNetworkAnalyzer_ECAL_PortList);
	FREE(pszEcalUserCharacterizations);
	
	FREE(pszPostEcal_Instruction);
	FREE(pszPostEcal_Instruction_Pic);
	
	FREE(pOldCalibFrequencyList);
	FREE(pOldCalibFactorList);

	FREE(pOutputDataTrace); 
	FREE(pOutputFrequencyTrace);
	
	FREE(pAuxilityTraceData);
	FREE(pszAux_Cable_Instruction);	
	FREE(pszAux_Cable_InstructionPic);
	
	FREE(pszCalibrated_With_Other_Path);
	
	FREE(pDB_FrequencyList);
	
	FREE(pFrequencyData); 
	FREE(pTraceData);
	FREE(pVSWRData); 		 
	
	FREE(pDB_RangesList);
	
	FREE(pTraceDeltaData);
	
	FREE(vlfDB_ReferenceLevelList);
	
	FREE(pszNetworkAnalyzerCalPortsList);
	
	FREE(pszStimulusEquipmentType);
	FREE(pszMeasureEquipmentType);
	
	FREE(pszNoiseSourceFillTableFromPath);  
	
	FREE_LIST(pszNetworkAnalyzerStateFiles,iDB_NumberOfNetworkAnalyzerStates);
	
	RETURN_VALUE(iTestError);
}
