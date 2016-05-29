#ifndef __TestExecutiveCommon_H__
#define __TestExecutiveCommon_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants
	
#define		CLB_RUN_STATUS_RUNNING				0
#define		CLB_RUN_STATUS_PASS					1
#define		CLB_RUN_STATUS_FAIL					2
#define		CLB_RUN_STATUS_ABORT				3
#define		CLB_RUN_STATUS_ERROR				4

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

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions

/**
 * @brief TECOM_Init
 *
 * Used for Initialyzation of Current Slot Thread.
 * @see TECOM_Close
 *
 * @param[in]  pTE_Context (void*) - Bypass parameter,that was received from top level ( Test Executive )
 * @param[out] pHandle (int*) - Handle for Current session
 * 
 * @return an Error code.
 */		

int	TECOM_Init( void *pTE_Context , int *pHandle );

/**
 * @brief TECOM_Close
 *
 * Close Current Slot Thread.
 * @see TECOM_Close
 *
 * @param[in] pHandle (int*) - Handle for Current session
 * 
 * @return an Error code.
 */	

int	DLLEXPORT	TECOM_Close( int *pHandle );

/**
 * @brief TECOM_GetLastError
 *
 * Get Last Error.
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[out] piErrorCode (int*) - Code of Error 
 * @param[out] pszErrorDiscription (int**) - Error Discription ( needed free after use )
 * @param[out] pszErrorFromFunction (int**) - Function Name ( needed free after use )    
 * @param[out] piLineNumber (int*) - Line number
 * @param[out] piThreadId (int*) - Thread ID
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_GetLastError( int handle , int *piErrorCode ,  char **pszErrorDiscription ,  char **pszErrorFromFunction , int *piLineNumber , int *piThreadId );

/**
 * @brief TECOM_DB_Variables_GetIntegerValue
 *
 * Get Integer variable from Database By Section type.
 *
 * Types : 
 * 1. VARTYPE_MEASURE_STORE - Temporary section for real time use.
 * 2. VARTYPE_GLOBAL		- Global Section ( not recomended to use )		
 * 3. VARTYPE_UUT			- Current Selection UUT Section.			
 * 4. VARTYPE_UUTVER		- Current Selection UUT Version Section.
 * 5. VARTYPE_TEST			- Current Running Test Section.
 * 6. VARTYPE_USER			- Current User Section. 
 * 7. VARTYPE_STATION		- Current Station Section.
 * 8. VARTYPE_EQUIPMENT		- Equipment Properties Section ( Linked by Station ).
 * 9. VARTYPE_EQUIPMENT_USE - Equipment Used in Current Test ( Linked by Station ). 
 *
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in]  vartype (int) - Type of section. 
 * @param[in]  name (char*) - Name of variable.
 * @param[out] piIntegerValue (int*) - Pointer to return Integer Value.    
 * @param[in]  hEquipmentHandle (int) - Equipment Handle used only with types (VARTYPE_EQUIPMENT,VARTYPE_EQUIPMENT_USE)
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_DB_Variables_GetIntegerValue( int handle , int vartype , char *name , int *piIntegerValue , int hEquipmentHandle );

/**
 * @brief TECOM_DB_Variables_GetIntegerArrayOfValues
 *
 * Get Integer Array of variables from Database By Section type.
 *
 * Types : 
 * 1. VARTYPE_MEASURE_STORE - Temporary section for real time use.
 * 2. VARTYPE_GLOBAL		- Global Section ( not recomended to use )		
 * 3. VARTYPE_UUT			- Current Selection UUT Section.			
 * 4. VARTYPE_UUTVER		- Current Selection UUT Version Section.
 * 5. VARTYPE_TEST			- Current Running Test Section.
 * 6. VARTYPE_USER			- Current User Section. 
 * 7. VARTYPE_STATION		- Current Station Section.
 * 8. VARTYPE_EQUIPMENT		- Equipment Properties Section ( Linked by Station ).
 * 9. VARTYPE_EQUIPMENT_USE - Equipment Used in Current Test ( Linked by Station ). 
 *
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in]  vartype (int) - Type of section. 
 * @param[in]  name (char*) - Name of variable.
 * @param[out] piIntegerValuesArray (int**) - Pointer to return Array of Integer Values. ( needed free after use )   
 * @param[out] piNumberOfValues (int*) - Pointer to return Number of Integer Values. 
 * @param[in]  hEquipmentHandle (int) - Equipment Handle used only with types (VARTYPE_EQUIPMENT,VARTYPE_EQUIPMENT_USE)
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_DB_Variables_GetIntegerArrayOfValues( int handle , int vartype , char *name , int **piIntegerValuesArray , int *piNumberOfValues , int hEquipmentHandle );
 
/**
 * @brief TECOM_DB_Variables_GetDoubleValue
 *
 * Get Double variable from Database By Section type.
 *
 * Types : 
 * 1. VARTYPE_MEASURE_STORE - Temporary section for real time use.
 * 2. VARTYPE_GLOBAL		- Global Section ( not recomended to use )		
 * 3. VARTYPE_UUT			- Current Selection UUT Section.			
 * 4. VARTYPE_UUTVER		- Current Selection UUT Version Section.
 * 5. VARTYPE_TEST			- Current Running Test Section.
 * 6. VARTYPE_USER			- Current User Section. 
 * 7. VARTYPE_STATION		- Current Station Section.
 * 8. VARTYPE_EQUIPMENT		- Equipment Properties Section ( Linked by Station ).
 * 9. VARTYPE_EQUIPMENT_USE - Equipment Used in Current Test ( Linked by Station ). 
 *
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in]  vartype (int) - Type of section. 
 * @param[in]  name (char*) - Name of variable.
 * @param[out] plfDoubleValue (double*) - Pointer to return Double Value.    
 * @param[in]  hEquipmentHandle (int) - Equipment Handle used only with types (VARTYPE_EQUIPMENT,VARTYPE_EQUIPMENT_USE)
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_DB_Variables_GetDoubleValue( int handle , int vartype , char *name , double *plfDoubleValue , int hEquipmentHandle );

/**
 * @brief TECOM_DB_Variables_GetDoubleArrayOfValues
 *
 * Get Double Array of variables from Database By Section type.
 *
 * Types : 
 * 1. VARTYPE_MEASURE_STORE - Temporary section for real time use.
 * 2. VARTYPE_GLOBAL		- Global Section ( not recomended to use )		
 * 3. VARTYPE_UUT			- Current Selection UUT Section.			
 * 4. VARTYPE_UUTVER		- Current Selection UUT Version Section.
 * 5. VARTYPE_TEST			- Current Running Test Section.
 * 6. VARTYPE_USER			- Current User Section. 
 * 7. VARTYPE_STATION		- Current Station Section.
 * 8. VARTYPE_EQUIPMENT		- Equipment Properties Section ( Linked by Station ).
 * 9. VARTYPE_EQUIPMENT_USE - Equipment Used in Current Test ( Linked by Station ). 
 *
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in]  vartype (int) - Type of section. 
 * @param[in]  name (char*) - Name of variable.
 * @param[out] plfDoubleValuesArray (double**) - Pointer to return Array of Double Values. ( needed free after use )   
 * @param[out] piNumberOfValues (int*) - Pointer to return Number of Double Values. 
 * @param[in]  hEquipmentHandle (int) - Equipment Handle used only with types (VARTYPE_EQUIPMENT,VARTYPE_EQUIPMENT_USE)
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_DB_Variables_GetDoubleArrayOfValues( int handle , int vartype , char *name , double **plfDoubleValuesArray , int *piNumberOfValues , int hEquipmentHandle );

/**
 * @brief TECOM_DB_Variables_GetStringValue
 *
 * Get String variable from Database By Section type.
 *
 * Types : 
 * 1. VARTYPE_MEASURE_STORE - Temporary section for real time use.
 * 2. VARTYPE_GLOBAL		- Global Section ( not recomended to use )		
 * 3. VARTYPE_UUT			- Current Selection UUT Section.			
 * 4. VARTYPE_UUTVER		- Current Selection UUT Version Section.
 * 5. VARTYPE_TEST			- Current Running Test Section.
 * 6. VARTYPE_USER			- Current User Section. 
 * 7. VARTYPE_STATION		- Current Station Section.
 * 8. VARTYPE_EQUIPMENT		- Equipment Properties Section ( Linked by Station ).
 * 9. VARTYPE_EQUIPMENT_USE - Equipment Used in Current Test ( Linked by Station ). 
 *
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in]  vartype (int) - Type of section. 
 * @param[in]  name (char*) - Name of variable.
 * @param[out] pszStringValue (char**) - Pointer to return String Value. ( needed free after use )    
 * @param[in]  hEquipmentHandle (int) - Equipment Handle used only with types (VARTYPE_EQUIPMENT,VARTYPE_EQUIPMENT_USE)
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_DB_Variables_GetStringValue( int handle , int vartype , char *name , char **pszStringValue , int hEquipmentHandle );

/**
 * @brief TECOM_DB_Variables_GetStringArrayOfValues
 *
 * Get String Array of variables from Database By Section type.
 *
 * Types : 
 * 1. VARTYPE_MEASURE_STORE - Temporary section for real time use.
 * 2. VARTYPE_GLOBAL		- Global Section ( not recomended to use )		
 * 3. VARTYPE_UUT			- Current Selection UUT Section.			
 * 4. VARTYPE_UUTVER		- Current Selection UUT Version Section.
 * 5. VARTYPE_TEST			- Current Running Test Section.
 * 6. VARTYPE_USER			- Current User Section. 
 * 7. VARTYPE_STATION		- Current Station Section.
 * 8. VARTYPE_EQUIPMENT		- Equipment Properties Section ( Linked by Station ).
 * 9. VARTYPE_EQUIPMENT_USE - Equipment Used in Current Test ( Linked by Station ). 
 *
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in]  vartype (int) - Type of section. 
 * @param[in]  name (char*) - Name of variable.
 * @param[out] pszStringValuesArray (char***) - Pointer to return Array of String Values. ( needed free after use )   
 * @param[out] piNumberOfValues (int*) - Pointer to return Number of String Values. 
 * @param[in]  hEquipmentHandle (int) - Equipment Handle used only with types (VARTYPE_EQUIPMENT,VARTYPE_EQUIPMENT_USE)
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_DB_Variables_GetStringArrayOfValues( int handle , int vartype , char *name , char ***pszStringValuesArray , int *piNumberOfValues , int hEquipmentHandle );

/**
 * @brief TECOM_DB_Variables_SetIntegerValue
 *
 * Set Integer variable to Database By Section type.
 *
 * Types : 
 * 1. VARTYPE_MEASURE_STORE - Temporary section for real time use.
 * 2. VARTYPE_GLOBAL		- Global Section ( not recomended to use )		
 * 3. VARTYPE_UUT			- Current Selection UUT Section.			
 * 4. VARTYPE_UUTVER		- Current Selection UUT Version Section.
 * 5. VARTYPE_TEST			- Current Running Test Section.
 * 6. VARTYPE_USER			- Current User Section. 
 * 7. VARTYPE_STATION		- Current Station Section.
 * 8. VARTYPE_EQUIPMENT		- Equipment Properties Section ( Linked by Station ).
 * 9. VARTYPE_EQUIPMENT_USE - Equipment Used in Current Test ( Linked by Station ). 
 *
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in]  vartype (int) - Type of section. 
 * @param[in]  name (char*) - Name of variable.
 * @param[in]  iIntegerValue (int) - Integer Value.    
 * @param[in]  hEquipmentHandle (int) - Equipment Handle used only with types (VARTYPE_EQUIPMENT,VARTYPE_EQUIPMENT_USE)
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_DB_Variables_SetIntegerValue( int handle , int vartype , char *name , int iIntegerValue , int hEquipmentHandle );

/**
 * @brief TECOM_DB_Variables_SetIntegerArrayOfValues
 *
 * Set Integer Array of variables to Database By Section type.
 *
 * Types : 
 * 1. VARTYPE_MEASURE_STORE - Temporary section for real time use.
 * 2. VARTYPE_GLOBAL		- Global Section ( not recomended to use )		
 * 3. VARTYPE_UUT			- Current Selection UUT Section.			
 * 4. VARTYPE_UUTVER		- Current Selection UUT Version Section.
 * 5. VARTYPE_TEST			- Current Running Test Section.
 * 6. VARTYPE_USER			- Current User Section. 
 * 7. VARTYPE_STATION		- Current Station Section.
 * 8. VARTYPE_EQUIPMENT		- Equipment Properties Section ( Linked by Station ).
 * 9. VARTYPE_EQUIPMENT_USE - Equipment Used in Current Test ( Linked by Station ). 
 *
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in]  vartype (int) - Type of section. 
 * @param[in]  name (char*) - Name of variable.
 * @param[in]  piIntegerValuesArray (int**) - Pointer of Integer Array Values. ( needed free after use )   
 * @param[in]  iNumberOfValues (int) - Number of Integer Values. 
 * @param[in]  hEquipmentHandle (int) - Equipment Handle used only with types (VARTYPE_EQUIPMENT,VARTYPE_EQUIPMENT_USE)
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_DB_Variables_SetIntegerArrayOfValues( int handle , int vartype , char *name , int *piIntegerValuesArray , int iNumberOfValues , int hEquipmentHandle );
 
/**
 * @brief TECOM_DB_Variables_SetDoubleValue
 *
 * Set Double variable to Database By Section type.
 *
 * Types : 
 * 1. VARTYPE_MEASURE_STORE - Temporary section for real time use.
 * 2. VARTYPE_GLOBAL		- Global Section ( not recomended to use )		
 * 3. VARTYPE_UUT			- Current Selection UUT Section.			
 * 4. VARTYPE_UUTVER		- Current Selection UUT Version Section.
 * 5. VARTYPE_TEST			- Current Running Test Section.
 * 6. VARTYPE_USER			- Current User Section. 
 * 7. VARTYPE_STATION		- Current Station Section.
 * 8. VARTYPE_EQUIPMENT		- Equipment Properties Section ( Linked by Station ).
 * 9. VARTYPE_EQUIPMENT_USE - Equipment Used in Current Test ( Linked by Station ). 
 *
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in]  vartype (int) - Type of section. 
 * @param[in]  name (char*) - Name of variable.
 * @param[in] lfDoubleValue (double) - Double Value.    
 * @param[in]  hEquipmentHandle (int) - Equipment Handle used only with types (VARTYPE_EQUIPMENT,VARTYPE_EQUIPMENT_USE)
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_DB_Variables_SetDoubleValue( int handle , int vartype , char *name , double lfDoubleValue , int hEquipmentHandle );

/**
 * @brief TECOM_DB_Variables_SetDoubleArrayOfValues
 *
 * Set Double Array of variables to Database By Section type.
 *
 * Types : 
 * 1. VARTYPE_MEASURE_STORE - Temporary section for real time use.
 * 2. VARTYPE_GLOBAL		- Global Section ( not recomended to use )		
 * 3. VARTYPE_UUT			- Current Selection UUT Section.			
 * 4. VARTYPE_UUTVER		- Current Selection UUT Version Section.
 * 5. VARTYPE_TEST			- Current Running Test Section.
 * 6. VARTYPE_USER			- Current User Section. 
 * 7. VARTYPE_STATION		- Current Station Section.
 * 8. VARTYPE_EQUIPMENT		- Equipment Properties Section ( Linked by Station ).
 * 9. VARTYPE_EQUIPMENT_USE - Equipment Used in Current Test ( Linked by Station ). 
 *
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in]  vartype (int) - Type of section. 
 * @param[in]  name (char*) - Name of variable.
 * @param[out] plfDoubleValuesArray (double**) - Pointer to return Array of Double Values. ( needed free after use )   
 * @param[out] piNumberOfValues (int*) - Pointer to return Number of Double Values. 
 * @param[in]  hEquipmentHandle (int) - Equipment Handle used only with types (VARTYPE_EQUIPMENT,VARTYPE_EQUIPMENT_USE)
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_DB_Variables_SetDoubleArrayOfValues( int handle , int vartype , char *name , double *plfDoubleValuesArray , int iNumberOfValues , int hEquipmentHandle );

/**
 * @brief TECOM_DB_Variables_SetStringValue
 *
 * Set String variable to Database By Section type.
 *
 * Types : 
 * 1. VARTYPE_MEASURE_STORE - Temporary section for real time use.
 * 2. VARTYPE_GLOBAL		- Global Section ( not recomended to use )		
 * 3. VARTYPE_UUT			- Current Selection UUT Section.			
 * 4. VARTYPE_UUTVER		- Current Selection UUT Version Section.
 * 5. VARTYPE_TEST			- Current Running Test Section.
 * 6. VARTYPE_USER			- Current User Section. 
 * 7. VARTYPE_STATION		- Current Station Section.
 * 8. VARTYPE_EQUIPMENT		- Equipment Properties Section ( Linked by Station ).
 * 9. VARTYPE_EQUIPMENT_USE - Equipment Used in Current Test ( Linked by Station ). 
 *
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in]  vartype (int) - Type of section. 
 * @param[in]  name (char*) - Name of variable.
 * @param[out] pszStringValue (char**) - Pointer to return String Value. ( needed free after use )    
 * @param[in]  hEquipmentHandle (int) - Equipment Handle used only with types (VARTYPE_EQUIPMENT,VARTYPE_EQUIPMENT_USE)
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_DB_Variables_SetStringValue( int handle , int vartype , char *name , char *pszStringValue , int hEquipmentHandle );

/**
 * @brief TECOM_DB_Variables_SetStringArrayOfValues
 *
 * Set String Array of variables to Database By Section type.
 *
 * Types : 
 * 1. VARTYPE_MEASURE_STORE - Temporary section for real time use.
 * 2. VARTYPE_GLOBAL		- Global Section ( not recomended to use )		
 * 3. VARTYPE_UUT			- Current Selection UUT Section.			
 * 4. VARTYPE_UUTVER		- Current Selection UUT Version Section.
 * 5. VARTYPE_TEST			- Current Running Test Section.
 * 6. VARTYPE_USER			- Current User Section. 
 * 7. VARTYPE_STATION		- Current Station Section.
 * 8. VARTYPE_EQUIPMENT		- Equipment Properties Section ( Linked by Station ).
 * 9. VARTYPE_EQUIPMENT_USE - Equipment Used in Current Test ( Linked by Station ). 
 *
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in]  vartype (int) - Type of section. 
 * @param[in]  name (char*) - Name of variable.
 * @param[out] pszStringValuesArray (char***) - Pointer to return Array of String Values. ( needed free after use )   
 * @param[out] piNumberOfValues (int*) - Pointer to return Number of String Values. 
 * @param[in]  hEquipmentHandle (int) - Equipment Handle used only with types (VARTYPE_EQUIPMENT,VARTYPE_EQUIPMENT_USE)
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_DB_Variables_SetStringArrayOfValues( int handle , int vartype , char *name , char **pszStringValuesArray , int iNumberOfValues , int hEquipmentHandle );

/**
 * @brief TECOM_DB_Variables_GetCalibrationFromVariable
 *
 * Get Calibration Array of variable from Database By Section type.
 *
 * Types : 
 * 1. VARTYPE_MEASURE_STORE - Temporary section for real time use.
 * 2. VARTYPE_GLOBAL		- Global Section ( not recomended to use )		
 * 3. VARTYPE_UUT			- Current Selection UUT Section.			
 * 4. VARTYPE_UUTVER		- Current Selection UUT Version Section.
 * 5. VARTYPE_TEST			- Current Running Test Section.
 * 6. VARTYPE_USER			- Current User Section. 
 * 7. VARTYPE_STATION		- Current Station Section.
 * 8. VARTYPE_EQUIPMENT		- Equipment Properties Section ( Linked by Station ).
 * 9. VARTYPE_EQUIPMENT_USE - Equipment Used in Current Test ( Linked by Station ). 
 *
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in]  vartype (int) - Type of section. 
 * @param[in]  range  (int) - Virtual range
 * @param[in]  name (char*) - Name of variable.
 * @param[out] plfFrequencies (double**) - Pointer to return Array of Frequency Values. ( needed free after use )
 * @param[out] plfFactors (double**) - Pointer to return Array of Factor Values. ( needed free after use )   
 * @param[out] piNumberOfValues (int*) - Pointer to return Number of Items.
 * @param[out] plfCalibrationDate (double*) - Pointer to return Date of Calibration. 
 * @param[in]  hEquipmentHandle (int) - Equipment Handle used only with types (VARTYPE_EQUIPMENT,VARTYPE_EQUIPMENT_USE)
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_DB_Variables_GetCalibrationFromVariable( int handle , int vartype , int range , char *name , double **plfFrequencies , double **plfFactors , int *piNumberOfValues , double *plfCalibrationDate , int hEquipmentHandle );

/**
 * @brief TECOM_DB_Variables_SetCalibrationFromVariable
 *
 * Set Calibration Array of variable from Database By Section type.
 *
 * Types : 
 * 1. VARTYPE_MEASURE_STORE - Temporary section for real time use.
 * 2. VARTYPE_GLOBAL		- Global Section ( not recomended to use )		
 * 3. VARTYPE_UUT			- Current Selection UUT Section.			
 * 4. VARTYPE_UUTVER		- Current Selection UUT Version Section.
 * 5. VARTYPE_TEST			- Current Running Test Section.
 * 6. VARTYPE_USER			- Current User Section. 
 * 7. VARTYPE_STATION		- Current Station Section.
 * 8. VARTYPE_EQUIPMENT		- Equipment Properties Section ( Linked by Station ).
 * 9. VARTYPE_EQUIPMENT_USE - Equipment Used in Current Test ( Linked by Station ). 
 *
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in]  vartype (int) - Type of section. 
 * @param[in]  range  (int) - Virtual range
 * @param[in]  bCleanBefore  (int) - Clean Before  
 * @param[in]  name (char*) - Name of variable.
 * @param[in] plfFrequencies (double*) - Array Pointer of Frequency Values. ( needed free after use )
 * @param[in] plfFactors (double*) - Array Pointer of Factor Values. ( needed free after use )   
 * @param[in] iNumberOfValues (int) - Number of Items.
 * @param[in]  hEquipmentHandle (int) - Equipment Handle used only with types (VARTYPE_EQUIPMENT,VARTYPE_EQUIPMENT_USE)
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_DB_Variables_SetCalibrationFromVariable( int handle , int vartype , int range , int bCleanBefore, char *name , double *plfFrequencies , double *plfFactors , int iNumberOfValues , int hEquipmentHandle );

/**
 * @brief TECOM_DB_Variables_GetCurrentPathCalibration
 *
 * Get Calibration Array of Current Path from Database.
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in]  range  (int) - Virtual range    
 * @param[out] plfFrequencies (double**) - Pointer to return Array of Frequency Values. ( needed free after use )
 * @param[out] plfFactors (double**) - Pointer to return Array of Factor Values. ( needed free after use )   
 * @param[out] piNumberOfValues (int*) - Pointer to return Number of Items.
 * @param[out] plfCalibrationDate (double*) - Pointer to return Date of Calibration. 
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_DB_Variables_GetCurrentPathCalibration( int handle , int range , double **plfFrequencies , double **plfFactors , int *piNumberOfValues , double *plfCalibrationDate );

/**
 * @brief TECOM_DB_Variables_SetCurrentPathCalibration
 *
 * Set Calibration Array of Current Path to Database.
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in]  range  (int) - Virtual range    
 * @param[in]  bCleanBefore  (int) - Clean Before  
 * @param[in] plfFrequencies (double*) - Pointer to return Array of Frequency Values. ( needed free after use )
 * @param[in] plfFactors (double*) - Pointer to return Array of Factor Values. ( needed free after use )   
 * @param[in] iNumberOfValues (int) - Number of Items.
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_DB_Variables_SetCurrentPathCalibration( int handle , int range , int bCleanBefore, double *plfFrequencies , double *plfFactors , int iNumberOfValues );


/**
 * @brief TECOM_DB_Variables_GetCurrentPathCalibration
 *
 * Get Calibration Array of Current Path from Database.
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in]  range  (int) - Virtual range    
 * @param[in]  name (char*) - Name of variable. 
 * @param[out] plfFrequencies (double**) - Pointer to return Array of Frequency Values. ( needed free after use )
 * @param[out] plfFactors (double**) - Pointer to return Array of Factor Values. ( needed free after use )   
 * @param[out] piNumberOfValues (int*) - Pointer to return Number of Items.
 * @param[out] plfCalibrationDate (double*) - Pointer to return Date of Calibration. 
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_DB_Variables_GetPathCalibrationByName( int handle , int range , char *name , double **plfFrequencies , double **plfFactors , int *piNumberOfValues , double *plfCalibrationDate );

/**
 * @brief TECOM_DB_AttachFileToReport
 *
 * Used to store file with report session.
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in] pFileNamePath (char*) - Pointer to File Full Path.
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_RPT_AttachFileToReport( int handle , char *pFileNamePath );

/**
 * @brief TECOM_RPT_Log
 *
 * Used to add single line log for current Test.
 *
 * Types :
 * 0. CLB_LINE_NORMAL
 * 1. CLB_LINE_HEADER_1     
 * 2. CLB_LINE_HEADER_2     
 * 3. CLB_LINE_HEADER_3     
 * 4. CLB_LINE_HEADER_4     
 * 5. CLB_LINE_COM_HEADER   
 * 6. CLB_LINE_SYSTEM_HEADER
 * 7. CLB_LINE_WARNING      
 * 8. CLB_LINE_INSTRUMENT   
 * 9. CLB_LINE_HEADER_TEST
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in] iMessageType (int) - Type of Message for vision only.    
 * @param[in] pMessageText (char*) - Log Message Text.
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_RPT_Log( int handle , int iMessageType , char *pMessageText );

/**
 * @brief TECOM_RPT_Result_Double
 *
 * Used to add single result for current test.
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in] pResultDescription (char*) - Result Description.    
 * @param[in] lfResult (double) - Numeric Real Result Value..
 * @param[in] pDefaultDescription - Use for first creation of spec record.
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_RPT_Result_Double( int handle , char *pResultDescription , double lfResult , char *pDefaultDescription );

/**
 * @brief TECOM_RPT_Result_Int
 *
 * Used to add single result for current test.
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in] pResultDescription (char*) - Result Description.    
 * @param[in] iResult (int) - Numeric Integer Result Value.
 * @param[in] pDefaultDescription - Use for first creation of spec record.
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_RPT_Result_Int( int handle , char *pResultDescription , int iResult , char *pDefaultDescription );

/**
 * @brief TECOM_RPT_Result_Picture
 *
 * Used to add single result for current test.
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in] pResultDescription (char*) - Result Description.    
 * @param[in] pPicturePath (char*) - Picture Full Path.
 * @param[in] pDefaultDescription - Use for first creation of spec record.
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_RPT_Result_Picture( int handle , char *pResultDescription , char *pPicturePath , char *pDefaultDescription );

/**
 * @brief TECOM_RPT_Result_Graph
 *
 * Used to add single result for current test.
 *
 * @see TECOM_RPT_Prepare_Graph_Result_Create , TECOM_RPT_Prepare_Graph_Result_Add_Trace
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in] pResultDescription (char*) - Result Description.    
 * @param[in] pGraphItem (void*) - Graph Item.
 * @param[in] pDefaultDescription - Use for first creation of spec record.
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_RPT_Result_Graph( int handle , char *pResultDescription , void *pGraphItem , char *pDefaultDescription );

/**
 * @brief TECOM_RPT_Prepare_Graph_Result_Create
 *
 * Used to create graph item by current result index.
 *
 * @see TECOM_RPT_Prepare_Graph_Result_Create 
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[out] pGraphItem (void**) - New Graph Item.
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_RPT_Prepare_Graph_Result_Create( int handle , void **pGraphItem );

/**
 * @brief TECOM_RPT_Prepare_Graph_Result_Add_Trace
 *
 * Used to add new trace to graph item.
 *
 * @see TECOM_RPT_Prepare_Graph_Result_Create 
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in] pGraphItem (void*) - Graph Item.
 * @param[in] pTraceBuffer - Trace Data
 * @param[in] buffer_size - Size of Trace Data Buffer
 * @param[in] startFromIndex - Srart from index in the buffer
 * @param[in] numberOfPoints - Number of points to get from buffer.
 * @param[in] StartX - Start X axis value of Trace data.
 * @param[in] StopX - Stop X axis value of Trace data.
 * @param[in] pszTraceName - Trace Name for Legend
 * @param[in] color - trace colot (RRGGBB)
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_RPT_Prepare_Graph_Result_Add_Trace( int handle , void *pGraphItem , double *pTraceBuffer , unsigned int buffer_size , unsigned int startFromIndex , unsigned int numberOfPoints , double StartX , double StopX , char *pszTraceName  , int color );

/**
 * @brief TECOM_RPT_Result_Double_ByNumber
 *
 * Used to add single result for current test.
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in] iResultNumber (int) - Result Reference to Spec Index ( Based 1 )
 * @param[in] pResultDescription (char*) - Result Description.    
 * @param[in] lfResult (double) - Numeric Real Result Value.
 * @param[in] pDefaultDescription - Use for first creation of spec record.
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_RPT_Result_Double_ByNumber( int handle , int iResultNumber , char *pResultDescription , double lfResult , char *pDefaultDescription );

/**
 * @brief TECOM_RPT_Result_Int
 *
 * Used to add single result for current test.
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in] iResultNumber (int) - Result Reference to Spec Index ( Based 1 )
 * @param[in] pResultDescription (char*) - Result Description.    
 * @param[in] iResult (int) - Numeric Integer Result Value.
 * @param[in] pDefaultDescription - Use for first creation of spec record.
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_RPT_Result_Int_ByNumber( int handle , int iResultNumber , char *pResultDescription , int iResult , char *pDefaultDescription );

/**
 * @brief TECOM_RPT_Result_Picture
 *
 * Used to add single result for current test.
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in] iResultNumber (int) - Result Reference to Spec Index ( Based 1 )
 * @param[in] pResultDescription (char*) - Result Description.    
 * @param[in] pPicturePath (char*) - Picture Full Path.
 * @param[in] pDefaultDescription - Use for first creation of spec record.
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_RPT_Result_Picture_ByNumber( int handle , int iResultNumber , char *pResultDescription , char *pPicturePath , char *pDefaultDescription );

/**
 * @brief TECOM_RPT_Result_Graph
 *
 * Used to add single result for current test.
 *
 * @see TECOM_RPT_Prepare_Graph_Result_Create , TECOM_RPT_Prepare_Graph_Result_Add_Trace
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in] iResultNumber (int) - Result Reference to Spec Index ( Based 1 )
 * @param[in] pResultDescription (char*) - Result Description.    
 * @param[in] pGraphItem (void*) - Graph Item.
 * @param[in] pDefaultDescription - Use for first creation of spec record.
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_RPT_Result_Graph_ByNumber( int handle , int iResultNumber , char *pResultDescription , void *pGraphItem , char *pDefaultDescription );

/**
 * @brief TECOM_RPT_Prepare_Graph_Result_Create
 *
 * Used to create graph item by current result index.
 *
 * @see TECOM_RPT_Prepare_Graph_Result_Create 
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in] iResultNumber (int) - Result Reference to Spec Index ( Based 1 )
 * @param[out] pGraphItem (void**) - New Graph Item.
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_RPT_Prepare_Graph_Result_Create_ByNumber( int handle , int iResultNumber , void **pGraphItem );

/**
 * @brief TECOM_RPT_Prepare_Graph_Result_Add_Trace
 *
 * Used to add new trace to graph item.
 *
 * @see TECOM_RPT_Prepare_Graph_Result_Create 
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in] iResultNumber (int) - Result Reference to Spec Index ( Based 1 )
 * @param[in] pGraphItem (void*) - Graph Item.
 * @param[in] pTraceBuffer (double*) - Trace Data
 * @param[in] buffer_size (unsigned int) - Size of Trace Data Buffer
 * @param[in] startFromIndex (unsigned int) - Srart from index in the buffer
 * @param[in] numberOfPoints (unsigned int) - Number of points to get from buffer.
 * @param[in] StartX (double) - Start X axis value of Trace data.
 * @param[in] StopX (double) - Stop X axis value of Trace data.
 * @param[in] pszTraceName (char*) - Trace Name for Legend
 * @param[in] color (int) - trace colot (RRGGBB)
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_RPT_Prepare_Graph_Result_Add_Trace_ByNumber( int handle , int iResultNumber , void *pGraphItem , double *pTraceBuffer , unsigned int buffer_size , unsigned int startFromIndex , unsigned int numberOfPoints , double StartX , double StopX , char *pszTraceName  , int color );

/**
 * @brief TECOM_TST_Delay
 *
 * Used to Delay Testing Sequence.
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in] pMessage (char*) - Not in Use ( Put NULL )
 * @param[in] lfDelayValue (double) - Delay Value in Seconds.
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_TST_Delay( int handle , char *pMessage , double lfDelayValue );

/**
 * @brief TECOM_TST_Timeout
 *
 * Used to Start or Stop Timeout Progress.
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in] pMessage (char*) - Not in Use ( Put NULL )
 * @param[in] lfTimeoutValue (double) - Timeout Value in Seconds.
 * @param[in] bStartOrStop (int) - 1 = Start , 0 = Stop
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_TST_Timeout( int handle , char *pMessage , double lfTimeoutValue , int bStartOrStop );

/**
 * @brief TECOM_TST_Check_For_Break
 *
 * Used to Check for Test Executive Break Request from User.
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[out] pbBreakRequered (int*) - if value is '1' break current testing immediately.
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_TST_Check_For_Break( int handle , int *pbBreakRequered );

/**
 * @brief TECOM_TST_Instruction
 *
 * Used to display instruction window.
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in] pTextMessage (char*) - Instruction Text.
 * @param[in] pPicturePath (char*) - Paicture Path ( Can be NULL ).
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_TST_Instruction( int handle , char *pTextMessage , char *pPicturePath );

/**
 * @brief TECOM_TST_ConfirmInstruction
 *
 * Used to display instruction window with Yes / No buttons.
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[in] pTextMessage (char*) - Instruction Text.
 * @param[in] pPicturePath (char*) - Paicture Path ( Can be NULL ).
 * @param[in] pbFeedback (int*) - Ponter to beedback value.
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_TST_ConfirmInstruction( int handle , char *pTextMessage , char *pPicturePath , int *pbFeedback  );

/**
 * @brief TECOM_TST_IsCurrentRunModeCalibration
 *
 * Used to get Current Running Mode.
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[out] pbFeedback (int*) - Ponter to beedback value ( 1 = Calibration Mode ).
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_TST_IsCurrentRunModeCalibration( int handle , int *pbFeedback  );

/**
 * @brief TECOM_TST_IsCurrentRunModeOperational
 *
 * Used to get Current Running Mode.
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[out] pbFeedback (int*) - Ponter to beedback value ( 1 = Testing Mode ).
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_TST_IsCurrentRunModeOperational( int handle , int *pbFeedback  );

/**
 * @brief TECOM_TST_WaitForLastResultStatus
 *
 * Used to get Last Result Status.
 *
 * @param[in]  handle (int) - Handle for Current session
 * @param[out] piResultStatus (int*) - Result Status ( 1 = Pass , 0 = Fail , -1 = Spec Missed ).
 *
 * @return an Error code.
 */
int	DLLEXPORT	TECOM_TST_WaitForLastResultStatus( int handle , int *piResultStatus  );

/**
 * @brief TECOM_MEM_Free
 *
 * Used for Memory Release.
 *
 * @param[in] pPointer (void*) - Ponter to be freed.
 *
 * @return none.
 */
void	DLLEXPORT	TECOM_MEM_Free( void *pPointer );

/**
 * @brief TECOM_MEM_FreeList
 *
 * Used for Memory List Release.
 *
 * @param[in] pPointer (void**) - Ponter of Items List.
 * @param[in] iNumberOfItems - Number of Items in List.
 *
 * @return none.
 */
void	DLLEXPORT	TECOM_MEM_FreeList( void **pPointer , int iNumberOfItems );

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __TestExecutiveCommon_H__ */
