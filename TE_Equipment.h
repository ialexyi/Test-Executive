#ifndef __TE_Equipment_H__
#define __TE_Equipment_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "GlobalDefines.h"

//==============================================================================
// Constants

//==============================================================================
// Types
typedef enum{	EQUIP_TYPE_DV = EQUIPMENT_TYPE_STANDARD_DEVICE,\
				EQUIP_TYPE_PS = EQUIPMENT_TYPE_POWER_SUPPLY,\
				EQUIP_TYPE_NA = EQUIPMENT_TYPE_NETWORK_ANALYZER,\
				EQUIP_TYPE_SG = EQUIPMENT_TYPE_SIGNAL_GENERATOR,\
				EQUIP_TYPE_SA = EQUIPMENT_TYPE_SPECTRUM_ANALYZER,\
				EQUIP_TYPE_SC = EQUIPMENT_TYPE_OSCILLOSCOPE,\
				EQUIP_TYPE_FG = EQUIPMENT_TYPE_FUNCTION_GENERATOR,\
				EQUIP_TYPE_PM = EQUIPMENT_TYPE_POWER_METER,\
				EQUIP_TYPE_NF = EQUIPMENT_TYPE_NOISE_FIGURE,\
				EQUIP_TYPE_MM = EQUIPMENT_TYPE_MULTI_METER,\
				EQUIP_TYPE_WA = EQUIPMENT_TYPE_WAVE_FORM_ANALYZER } teEquipmentTypes;

//==============================================================================
// External variables

//==============================================================================
// Global functions

STD_ERROR		TE_EQUIP_RunInitialization( int hMainHandle , int *pbSkipRunning , int bRunAutoSelectionOnly );

STD_ERROR		TE_EQUIP_CloseEquipment( int hMainHandle );

STD_ERROR		TE_EQUIP_TestConnection( int hMainHandle , unsigned long long ulEquipmentID , int *pbTestStaus );

STD_ERROR		TE_EQUIP_ViewCalibration( int hMainHandle , unsigned long long ulEquipmentID );

STD_ERROR		TE_EQUIP_ConnectToEquipment( int hMainHandle , unsigned long long ulEquipmentID , int *pEquipmentHandle );

STD_ERROR		TE_EQUIP_Devices_Apply_PathCommands( int hMainHandle , const char szPrefix[] , int iTestIndex , int hEquipmentHandle , int iPathIndex , int iSlotNumber );

STD_ERROR		TE_EQUIP_Devices_Apply_FrequencyCommands( int hMainHandle , const char szPrefix[] , int iTestIndex , int hEquipmentHandle , int iCurrentFrequencyIndex , double lfCurrentFrequency , int iSlotNumber );

STD_ERROR		TE_EQUIP_Devices_Apply_PathConnection( int hMainHandle , int iTestIndex , int hEquipmentHandle , char *pPathString );

STD_ERROR		TE_EQUIP_Get_Equipment_Information( int hMainHandle , char *pAddress , unsigned long long ulEquipmentID , int *pbConnectionStatus , char **pVendor , char **pSerialNumber , char **pModel , char **pFirmware );

STD_ERROR		TE_EQUIP_Get_Drivers_FileList ( int hMainHandle , char ***pDriversList , int **pDriversTypes , int *pCount );

STD_ERROR		TE_EQUIP_Check_Driver( int hMainHandle , char *pDriverFile , char *pEquipmentAddress , int *pCompatibility , char **pVendor , char **pSerialNumber , char **pModel , char **pFirmware , char **pIDN , char **pID_Responds );  

STD_ERROR		TE_EQUIP_BrowseStateFiles( int hMainHandle , unsigned long long ulEquipmentID );

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __TE_Equipment_H__ */
