//==============================================================================
// Include files

#include "TestExecutiveCommon.h"
#include "GlobalDefines.h"
#include <ansi_c.h>
#include <utility.h>
#include "clb.h"
#include "common.h"

//==============================================================================
// Constants

//==============================================================================
// Types

typedef struct
{
	sClb							*pClb;
	
	
	STD_ERROR						*pLastError


} tsLocalStorage;

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

int	DLLEXPORT	TECOM_Init( void *pTE_Context , int *pHandle )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	int								handle										=	0;
	
	IF (( pTE_Context == NULL ) , "The Function ( TECOM_Init ) has recieved NULL argument of \"pTE_Context\"." );
	IF (( pHandle == NULL )  , "The Function ( TECOM_Init ) has recieved NULL argument of \"pHandle\"." );   

	CHK_CMT(CmtNewTSV ( sizeof(tsLocalStorage) , &handle ));
	
	*pHandle = handle;

	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));
	
	pLocalStorage->pClb = pTE_Context;
	
Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_Close( int *pHandle )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	int								handle										=	0;
	
	IF (( pHandle == NULL )  , "The Function ( TECOM_Close ) has recieved NULL argument of \"pHandle\"." );   

	handle = *pHandle;
	*pHandle = 0;

	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));
	
	FREE_STDERR_POINTER(pLocalStorage->pLastError); 
	
Error:
	
	if ( handle )
	{
		CmtReleaseTSVPtr (handle);
		CmtDiscardTSV (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_GetLastError( int handle , int *piErrorCode ,  char **pszErrorDiscription ,  char **pszErrorFromFunction , int *piLineNumber , int *piThreadId )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) function before this." );   

	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));
	
	if ( pLocalStorage->pLastError )
	{
		if ( piErrorCode )
			*piErrorCode = pLocalStorage->pLastError->error;
		
		if ( pszErrorDiscription )
			*pszErrorDiscription = pLocalStorage->pLastError->pszErrorDescription;
		
		if ( piLineNumber )
			*piLineNumber = pLocalStorage->pLastError->line;
		
		if ( piThreadId )
			*piThreadId = pLocalStorage->pLastError->threadID;	
		
		if ( pszErrorFromFunction )
			*pszErrorFromFunction = pLocalStorage->pLastError->pszFunction;
	
		FREE(pLocalStorage->pLastError->pszErrorFrom);
		FREE(pLocalStorage->pLastError->pszFile);
		FREE(pLocalStorage->pLastError);
	}
	
Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

///======================================== Database Variables =========================================================================//
int	DLLEXPORT	TECOM_DB_Variables_GetIntegerValue( int handle , int vartype , char *name , int *piIntegerValue , int hEquipmentHandle )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( name == NULL )  , "The function ( TECOM_DB_Variables_GetIntegerValue ) has recieved NULL argument of variable name." );
	IF (( piIntegerValue == NULL )  , "The function ( TECOM_DB_Variables_GetIntegerValue ) has recieved NULL argument of variable value pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	*piIntegerValue = GetVarInt( pLocalStorage->pClb , vartype, name , hEquipmentHandle );
	
Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_DB_Variables_GetIntegerArrayOfValues( int handle , int vartype , char *name , int **piIntegerValuesArray , int *piNumberOfValues , int hEquipmentHandle )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( name == NULL )  , "The function ( TECOM_DB_Variables_GetIntegerArrayOfValues ) has recieved NULL argument of variable name." );
	IF (( piNumberOfValues == NULL )  , "The function ( TECOM_DB_Variables_GetIntegerArrayOfValues ) has recieved NULL argument of number of values pointer." );
	IF (( piIntegerValuesArray == NULL )  , "The function ( TECOM_DB_Variables_GetIntegerArrayOfValues ) has recieved NULL argument of values double pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	*piNumberOfValues = GetVarIntArray( pLocalStorage->pClb , vartype, name , piIntegerValuesArray , hEquipmentHandle );
	
Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}


int	DLLEXPORT	TECOM_DB_Variables_GetDoubleValue( int handle , int vartype , char *name , double *plfDoubleValue , int hEquipmentHandle )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( name == NULL )  , "The function ( TECOM_DB_Variables_GetDoubleValue ) has recieved NULL argument of variable name." );
	IF (( plfDoubleValue == NULL )  , "The function ( TECOM_DB_Variables_GetDoubleValue ) has recieved NULL argument of variable value pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	*plfDoubleValue = GetVarDouble( pLocalStorage->pClb , vartype, name , hEquipmentHandle );
	
Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_DB_Variables_GetDoubleArrayOfValues( int handle , int vartype , char *name , double **plfDoubleValuesArray , int *piNumberOfValues , int hEquipmentHandle )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( name == NULL )  , "The function ( TECOM_DB_Variables_GetDoubleArrayOfValues ) has recieved NULL argument of variable name." );
	IF (( piNumberOfValues == NULL )  , "The function ( TECOM_DB_Variables_GetDoubleArrayOfValues ) has recieved NULL argument of number of values pointer." );
	IF (( plfDoubleValuesArray == NULL )  , "The function ( TECOM_DB_Variables_GetDoubleArrayOfValues ) has recieved NULL argument of values double pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	*piNumberOfValues = GetVarDoubleArray( pLocalStorage->pClb , vartype, name , plfDoubleValuesArray , hEquipmentHandle );
	
Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}


int	DLLEXPORT	TECOM_DB_Variables_GetStringValue( int handle , int vartype , char *name , char **pszStringValue , int hEquipmentHandle )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( name == NULL )  , "The function ( TECOM_DB_Variables_GetStringValue ) has recieved NULL argument of variable name." );
	IF (( pszStringValue == NULL )  , "The function ( TECOM_DB_Variables_GetStringValue ) has recieved NULL argument of variable value pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	*pszStringValue = GetVarString( pLocalStorage->pClb , vartype, name , hEquipmentHandle );
	
Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_DB_Variables_GetStringArrayOfValues( int handle , int vartype , char *name , char ***pszStringValuesArray , int *piNumberOfValues , int hEquipmentHandle )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( name == NULL )  , "The function ( TECOM_DB_Variables_GetIntegerArrayOfValues ) has recieved NULL argument of variable name." );
	IF (( piNumberOfValues == NULL )  , "The function ( TECOM_DB_Variables_GetIntegerArrayOfValues ) has recieved NULL argument of number of values pointer." );
	IF (( pszStringValuesArray == NULL )  , "The function ( TECOM_DB_Variables_GetIntegerArrayOfValues ) has recieved NULL argument of values double pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	*pszStringValuesArray = GetVarStringArray( pLocalStorage->pClb , vartype, name , piNumberOfValues , hEquipmentHandle );
	
Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_DB_Variables_SetIntegerValue( int handle , int vartype , char *name , int iIntegerValue , int hEquipmentHandle )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( name == NULL )  , "The function ( TECOM_DB_Variables_SetIntegerValue ) has recieved NULL argument of variable name." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	SetVarInt( pLocalStorage->pClb , vartype, name , iIntegerValue , hEquipmentHandle );
	
Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_DB_Variables_SetIntegerArrayOfValues( int handle , int vartype , char *name , int *piIntegerValuesArray , int iNumberOfValues , int hEquipmentHandle )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( name == NULL )  , "The function ( TECOM_DB_Variables_SetIntegerArrayOfValues ) has recieved NULL argument of variable name." );
	IF (( piIntegerValuesArray == NULL )  , "The function ( TECOM_DB_Variables_SetIntegerArrayOfValues ) has recieved NULL argument of values double pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	SetVarIntArray( pLocalStorage->pClb , vartype, name , piIntegerValuesArray , iNumberOfValues , hEquipmentHandle );
	
Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_DB_Variables_SetDoubleValue( int handle , int vartype , char *name , double lfDoubleValue , int hEquipmentHandle )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( name == NULL )  , "The function ( TECOM_DB_Variables_SetDoubleValue ) has recieved NULL argument of variable name." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	SetVarDouble( pLocalStorage->pClb , vartype, name , lfDoubleValue , hEquipmentHandle );
	
Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_DB_Variables_SetDoubleArrayOfValues( int handle , int vartype , char *name , double *plfDoubleValuesArray , int iNumberOfValues , int hEquipmentHandle )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( name == NULL )  , "The function ( TECOM_DB_Variables_SetDoubleArrayOfValues ) has recieved NULL argument of variable name." );
	IF (( plfDoubleValuesArray == NULL )  , "The function ( TECOM_DB_Variables_SetDoubleArrayOfValues ) has recieved NULL argument of values double pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	SetVarDoubleArray( pLocalStorage->pClb , vartype, name , plfDoubleValuesArray , iNumberOfValues , hEquipmentHandle );
	
Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_DB_Variables_SetStringValue( int handle , int vartype , char *name , char *pszStringValue , int hEquipmentHandle )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( name == NULL )  , "The function ( TECOM_DB_Variables_SetStringValue ) has recieved NULL argument of variable name." );
	IF (( pszStringValue == NULL )  , "The function ( TECOM_DB_Variables_SetStringValue ) has recieved NULL argument of variable value pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	SetVarString( pLocalStorage->pClb , vartype, name , pszStringValue , hEquipmentHandle );
	
Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_DB_Variables_SetStringArrayOfValues( int handle , int vartype , char *name , char **pszStringValuesArray , int iNumberOfValues , int hEquipmentHandle )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( name == NULL )  , "The function ( TECOM_DB_Variables_SetStringArrayOfValues ) has recieved NULL argument of variable name." );
	IF (( pszStringValuesArray == NULL )  , "The function ( TECOM_DB_Variables_SetStringArrayOfValues ) has recieved NULL argument of values double pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	SetVarStringArray( pLocalStorage->pClb , vartype, name , pszStringValuesArray , iNumberOfValues , hEquipmentHandle );
	
Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

///======================================== Database Calibration Variables ===============================================================//

int	DLLEXPORT	TECOM_DB_Variables_GetCalibrationFromVariable( int handle , int vartype , int range , char *name , double **plfFrequencies , double **plfFactors , int *piNumberOfValues , double *plfCalibrationDate , int hEquipmentHandle )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( name == NULL )  , "The function ( TECOM_DB_Variables_GetCalibrationFromVariable ) has recieved NULL argument of variable name." );
	IF (( plfFrequencies == NULL )  , "The function ( TECOM_DB_Variables_GetCalibrationFromVariable ) has recieved NULL argument of frequencies double pointer." );
	IF (( plfFactors == NULL )  , "The function ( TECOM_DB_Variables_GetCalibrationFromVariable ) has recieved NULL argument of factors double pointer." );
	IF (( piNumberOfValues == NULL )  , "The function ( TECOM_DB_Variables_GetCalibrationFromVariable ) has recieved NULL argument of num_of_values integer pointer." );
	IF (( plfCalibrationDate == NULL )  , "The function ( TECOM_DB_Variables_GetCalibrationFromVariable ) has recieved NULL argument of cal date double pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	GetVarCalibration( pLocalStorage->pClb , vartype , range , name , plfFrequencies , plfFactors , piNumberOfValues , plfCalibrationDate , hEquipmentHandle ); 
	
Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_DB_Variables_SetCalibrationFromVariable( int handle , int vartype , int range , int bCleanBefore , char *name , double *plfFrequencies , double *plfFactors , int iNumberOfValues , int hEquipmentHandle )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( name == NULL )  , "The function ( TECOM_DB_Variables_GetCalibrationFromVariable ) has recieved NULL argument of variable name." );
	IF (( plfFrequencies == NULL )  , "The function ( TECOM_DB_Variables_GetCalibrationFromVariable ) has recieved NULL argument of frequencies double pointer." );
	IF (( plfFactors == NULL )  , "The function ( TECOM_DB_Variables_GetCalibrationFromVariable ) has recieved NULL argument of factors double pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	SetVarCalibration( pLocalStorage->pClb , vartype , range, bCleanBefore , name , plfFrequencies , plfFactors , iNumberOfValues , hEquipmentHandle ); 
	
Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}


///======================================== Database Current Test Calibration ===============================================================//

int	DLLEXPORT	TECOM_DB_Variables_GetCurrentPathCalibration( int handle , int range , double **plfFrequencies , double **plfFactors , int *piNumberOfValues , double *plfCalibrationDate )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( plfFrequencies == NULL )  , "The function ( TECOM_DB_Variables_GetCalibrationFromVariable ) has recieved NULL argument of frequencies double pointer." );
	IF (( plfFactors == NULL )  , "The function ( TECOM_DB_Variables_GetCalibrationFromVariable ) has recieved NULL argument of factors double pointer." );
	IF (( piNumberOfValues == NULL )  , "The function ( TECOM_DB_Variables_GetCalibrationFromVariable ) has recieved NULL argument of num_of_values integer pointer." );
	IF (( plfCalibrationDate == NULL )  , "The function ( TECOM_DB_Variables_GetCalibrationFromVariable ) has recieved NULL argument of cal date double pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	GetVarCurrentCalibration( pLocalStorage->pClb , range , plfFrequencies , plfFactors , piNumberOfValues , plfCalibrationDate ); 
	
Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_DB_Variables_SetCurrentPathCalibration( int handle , int range , int bCleanBefore , double *plfFrequencies , double *plfFactors , int iNumberOfValues )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( plfFrequencies == NULL )  , "The function ( TECOM_DB_Variables_GetCalibrationFromVariable ) has recieved NULL argument of frequencies double pointer." );
	IF (( plfFactors == NULL )  , "The function ( TECOM_DB_Variables_GetCalibrationFromVariable ) has recieved NULL argument of factors double pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	SetVarCurrentCalibration( pLocalStorage->pClb , range , bCleanBefore , plfFrequencies , plfFactors , iNumberOfValues ); 
	
Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_DB_Variables_GetPathCalibrationByName( int handle , int range , char *name , double **plfFrequencies , double **plfFactors , int *piNumberOfValues , double *plfCalibrationDate )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( name == NULL )  , "The function ( TECOM_DB_Variables_GetPathCalibrationByName ) has recieved NULL argument of variable name." );
	IF (( plfFrequencies == NULL )  , "The function ( TECOM_DB_Variables_GetPathCalibrationByName ) has recieved NULL argument of frequencies double pointer." );
	IF (( plfFactors == NULL )  , "The function ( TECOM_DB_Variables_GetPathCalibrationByName ) has recieved NULL argument of factors double pointer." );
	IF (( piNumberOfValues == NULL )  , "The function ( TECOM_DB_Variables_GetPathCalibrationByName ) has recieved NULL argument of num_of_values integer pointer." );
	IF (( plfCalibrationDate == NULL )  , "The function ( TECOM_DB_Variables_GetPathCalibrationByName ) has recieved NULL argument of cal date double pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	GetVarCalibrationByName( pLocalStorage->pClb , name , range , plfFrequencies , plfFactors , piNumberOfValues , plfCalibrationDate ); 
	
Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

///======================================== Database Reporting =========================================================================//
int	DLLEXPORT	TECOM_RPT_AttachFileToReport( int handle , char *pFileNamePath )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pFileNamePath == NULL )  , "The function ( TECOM_DB_AttachFileToReport ) has recieved NULL argument of File Name Path pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	pLocalStorage->pClb->StoreFile ( pLocalStorage->pClb->handle , 0 , pFileNamePath );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_RPT_Log( int handle , int iMessageType , char *pMessageText )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pMessageText == NULL )  , "The function ( TECOM_DB_AttachFileToReport ) has recieved NULL argument of Message Test pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	pLocalStorage->pClb->Log ( pLocalStorage->pClb->handle , iMessageType , pMessageText );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_RPT_Result_Double( int handle , char *pResultDescription , double lfResult , char *pDefaultDescription )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	char							szDefaultDescription[LOW_STRING]			=	{0};
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pResultDescription == NULL )  , "The function ( TECOM_RPT_Result_Double ) has recieved NULL argument of Result Description pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	if ( pDefaultDescription )
		strcpy( szDefaultDescription , pDefaultDescription );
	
	pLocalStorage->pClb->Result ( pLocalStorage->pClb->handle , CLB_RESULT_DOUBLE , pResultDescription , lfResult , szDefaultDescription );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_RPT_Result_Int( int handle , char *pResultDescription , int iResult , char *pDefaultDescription )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	char							szDefaultDescription[LOW_STRING]			=	{0};
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pResultDescription == NULL )  , "The function ( TECOM_RPT_Result_Int ) has recieved NULL argument of Result Description pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	if ( pDefaultDescription )
		strcpy( szDefaultDescription , pDefaultDescription );
	
	pLocalStorage->pClb->Result ( pLocalStorage->pClb->handle , CLB_RESULT_INT , pResultDescription , iResult , szDefaultDescription );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_RPT_Result_String( int handle , char *pResultDescription , char *pResult , char *pDefaultDescription )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	char							szDefaultDescription[LOW_STRING]			=	{0};
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pResultDescription == NULL )  , "The function ( TECOM_RPT_Result_String ) has recieved NULL argument of Result Description pointer." );
	IF (( pResult == NULL )  , "The function ( TECOM_RPT_Result_String ) has recieved NULL argument of Result pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	if ( pDefaultDescription )
		strcpy( szDefaultDescription , pDefaultDescription );
	
	pLocalStorage->pClb->Result ( pLocalStorage->pClb->handle , CLB_RESULT_STRING , pResultDescription , pResult , szDefaultDescription );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_RPT_Result_Picture( int handle , char *pResultDescription , char *pPicturePath , char *pDefaultDescription )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	char							szDefaultDescription[LOW_STRING]			=	{0};
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pResultDescription == NULL )  , "The function ( TECOM_RPT_Result_Int ) has recieved NULL argument of Result Description pointer." );
	IF (( pPicturePath == NULL )  , "The function ( TECOM_RPT_Result_String ) has recieved NULL argument of Result pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	if ( pDefaultDescription )
		strcpy( szDefaultDescription , pDefaultDescription );
	
	pLocalStorage->pClb->Result ( pLocalStorage->pClb->handle , CLB_RESULT_PICTURE , pResultDescription , pPicturePath , szDefaultDescription );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_RPT_Result_Graph( int handle , char *pResultDescription , void *pGraphItem , char *pDefaultDescription )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	char							szDefaultDescription[LOW_STRING]			=	{0};
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pResultDescription == NULL )  , "The function ( TECOM_RPT_Result_Int ) has recieved NULL argument of Result Description pointer." );
	IF (( pGraphItem == NULL )  , "The function ( TECOM_RPT_Result_String ) has recieved NULL argument of Graph Item pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	if ( pDefaultDescription )
		strcpy( szDefaultDescription , pDefaultDescription );
	
	pLocalStorage->pClb->Result ( pLocalStorage->pClb->handle , CLB_RESULT_GRAPH , pResultDescription , pGraphItem , szDefaultDescription );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_RPT_Prepare_Graph_Result_Create( int handle , void **pGraphItem )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pGraphItem == NULL )  , "The function ( TECOM_RPT_Prepare_Graph_Result ) has recieved NULL argument of Graph Item pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	pLocalStorage->pClb->GetCurrentResultGraphItem ( pLocalStorage->pClb->handle , -1 , pGraphItem );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_RPT_Prepare_Graph_Result_Add_Trace( int handle , void *pGraphItem , double *pTraceBuffer , unsigned int buffer_size , unsigned int startFromIndex , unsigned int numberOfPoints , double StartX , double StopX , char *pszTraceName  , int color )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pGraphItem == NULL )  , "The function ( TECOM_RPT_Prepare_Graph_Result_Add_Trace_ByNumber ) has recieved NULL argument of Graph Item pointer." );
	IF (( pTraceBuffer == NULL )  , "The function ( TECOM_RPT_Prepare_Graph_Result_Add_Trace_ByNumber ) has recieved NULL argument of Trace Data pointer." );
	IF (( pszTraceName == NULL )  , "The function ( TECOM_RPT_Prepare_Graph_Result_Add_Trace_ByNumber ) has recieved NULL argument of Trace Name pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	pLocalStorage->pClb->AddTraceToCurrentResultGraph ( pLocalStorage->pClb->handle , -1 , pGraphItem , pTraceBuffer , buffer_size , startFromIndex , numberOfPoints , StartX , StopX , pszTraceName  , color  );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_RPT_Result_Double_ByNumber( int handle , int iResultNumber , char *pResultDescription , double lfResult , char *pDefaultDescription )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	char							szDefaultDescription[LOW_STRING]			=	{0};
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pResultDescription == NULL )  , "The function ( TECOM_RPT_Result_Double ) has recieved NULL argument of Result Description pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	if ( pDefaultDescription )
		strcpy( szDefaultDescription , pDefaultDescription );
	
	pLocalStorage->pClb->ResultConst ( pLocalStorage->pClb->handle , iResultNumber , CLB_RESULT_DOUBLE , pResultDescription , lfResult , szDefaultDescription );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_RPT_Result_Int_ByNumber( int handle , int iResultNumber , char *pResultDescription , int iResult , char *pDefaultDescription )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	char							szDefaultDescription[LOW_STRING]			=	{0};
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pResultDescription == NULL )  , "The function ( TECOM_RPT_Result_Int ) has recieved NULL argument of Result Description pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	if ( pDefaultDescription )
		strcpy( szDefaultDescription , pDefaultDescription );
	
	pLocalStorage->pClb->ResultConst ( pLocalStorage->pClb->handle , iResultNumber , CLB_RESULT_INT , pResultDescription , iResult , szDefaultDescription );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_RPT_Result_String_ByNumber( int handle , int iResultNumber , char *pResultDescription , char *pResult , char *pDefaultDescription )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	char							szDefaultDescription[LOW_STRING]			=	{0};
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pResultDescription == NULL )  , "The function ( TECOM_RPT_Result_String ) has recieved NULL argument of Result Description pointer." );
	IF (( pResult == NULL )  , "The function ( TECOM_RPT_Result_String ) has recieved NULL argument of Result pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	if ( pDefaultDescription )
		strcpy( szDefaultDescription , pDefaultDescription );
	
	pLocalStorage->pClb->ResultConst ( pLocalStorage->pClb->handle , iResultNumber , CLB_RESULT_STRING , pResultDescription , pResult , szDefaultDescription );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_RPT_Result_Picture_ByNumber( int handle , int iResultNumber , char *pResultDescription , char *pPicturePath , char *pDefaultDescription )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	char							szDefaultDescription[LOW_STRING]			=	{0};
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pResultDescription == NULL )  , "The function ( TECOM_RPT_Result_Int ) has recieved NULL argument of Result Description pointer." );
	IF (( pPicturePath == NULL )  , "The function ( TECOM_RPT_Result_String ) has recieved NULL argument of Result pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	if ( pDefaultDescription )
		strcpy( szDefaultDescription , pDefaultDescription );
	
	pLocalStorage->pClb->ResultConst ( pLocalStorage->pClb->handle , iResultNumber , CLB_RESULT_PICTURE , pResultDescription , pPicturePath , szDefaultDescription );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_RPT_Result_Graph_ByNumber( int handle , int iResultNumber , char *pResultDescription , void *pGraphItem , char *pDefaultDescription )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	char							szDefaultDescription[LOW_STRING]			=	{0};
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pResultDescription == NULL )  , "The function ( TECOM_RPT_Result_Int ) has recieved NULL argument of Result Description pointer." );
	IF (( pGraphItem == NULL )  , "The function ( TECOM_RPT_Result_String ) has recieved NULL argument of Graph Item pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	if ( pDefaultDescription )
		strcpy( szDefaultDescription , pDefaultDescription );
	
	pLocalStorage->pClb->ResultConst ( pLocalStorage->pClb->handle , iResultNumber , CLB_RESULT_GRAPH , pResultDescription , pGraphItem , szDefaultDescription );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}


int	DLLEXPORT	TECOM_RPT_Prepare_Graph_Result_Create_ByNumber( int handle , int iResultNumber , void **pGraphItem )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	char							szDefaultDescription[LOW_STRING]			=	{0};
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pGraphItem == NULL )  , "The function ( TECOM_RPT_Result_String ) has recieved NULL argument of Graph Item pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	pLocalStorage->pClb->GetCurrentResultGraphItem ( pLocalStorage->pClb->handle , iResultNumber , pGraphItem );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_RPT_Prepare_Graph_Result_Add_Trace_ByNumber( int handle , int iResultNumber , void *pGraphItem , double *pTraceBuffer , unsigned int buffer_size , unsigned int startFromIndex , unsigned int numberOfPoints , double StartX , double StopX , char *pszTraceName  , int color )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pGraphItem == NULL )  , "The function ( TECOM_RPT_Prepare_Graph_Result_Add_Trace_ByNumber ) has recieved NULL argument of Graph Item pointer." );
	IF (( pTraceBuffer == NULL )  , "The function ( TECOM_RPT_Prepare_Graph_Result_Add_Trace_ByNumber ) has recieved NULL argument of Trace Data pointer." );
	IF (( pszTraceName == NULL )  , "The function ( TECOM_RPT_Prepare_Graph_Result_Add_Trace_ByNumber ) has recieved NULL argument of Trace Name pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	pLocalStorage->pClb->AddTraceToCurrentResultGraph ( pLocalStorage->pClb->handle , iResultNumber , pGraphItem , pTraceBuffer , buffer_size , startFromIndex , numberOfPoints , StartX , StopX , pszTraceName  , color  );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

///======================================== Testing  =========================================================================//

int	DLLEXPORT	TECOM_TST_Delay( int handle , char *pMessage , double lfDelayValue )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	pLocalStorage->pClb->Wait ( pLocalStorage->pClb->handle , pMessage , lfDelayValue );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}


int	DLLEXPORT	TECOM_TST_Timeout( int handle , char *pMessage , double lfTimeoutValue , int bStartOrStop )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	pLocalStorage->pClb->GUI_Timeout ( pLocalStorage->pClb->handle , pMessage , lfTimeoutValue , bStartOrStop );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_TST_Check_For_Break( int handle , int *pbBreakRequered )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pbBreakRequered == NULL )  , "The function ( TECOM_TST_Check_For_Break ) has recieved NULL argument of BreakRequered pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	*pbBreakRequered = pLocalStorage->pClb->GUI_Check_Break ( pLocalStorage->pClb->handle );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_TST_Instruction( int handle , char *pTextMessage , char *pPicturePath )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	pLocalStorage->pClb->Instruction ( pLocalStorage->pClb->handle , INSTR_TYPE_CONTINUE , pTextMessage , pPicturePath );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_TST_ConfirmInstruction( int handle , char *pTextMessage , char *pPicturePath , int *pbFeedback  )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pbFeedback == NULL )  , "The function ( TECOM_TST_ConfirmInstruction ) has recieved NULL argument of Feedback pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	*pbFeedback = pLocalStorage->pClb->Instruction ( pLocalStorage->pClb->handle , INSTR_TYPE_YES_NO , pTextMessage , pPicturePath );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}


int	DLLEXPORT	TECOM_TST_IsCurrentRunModeCalibration( int handle , int *pbFeedback  )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pbFeedback == NULL )  , "The function ( TECOM_TST_IsCurrentRunModeCalibration ) has recieved NULL argument of Feedback pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	*pbFeedback = pLocalStorage->pClb->IsRunningModeCalibration ( pLocalStorage->pClb->handle );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_TST_IsCurrentRunModeOperational( int handle , int *pbFeedback  )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( pbFeedback == NULL )  , "The function ( TECOM_TST_IsCurrentRunModeOperational ) has recieved NULL argument of Feedback pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	*pbFeedback = pLocalStorage->pClb->IsRunningModeOperational ( pLocalStorage->pClb->handle );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

int	DLLEXPORT	TECOM_TST_WaitForLastResultStatus( int handle , int *piResultStatus  )
{
	STD_ERROR						StdError									=	{0};
	
	tsLocalStorage					*pLocalStorage								=	NULL;			
	
	IF (( handle == 0 )  , "The Module is not initialized yet. Please run ( TECOM_Init ) Function before that." );   
	IF (( piResultStatus == NULL )  , "The function ( TECOM_TST_WaitForLastResultStatus ) has recieved NULL argument of ResultStatus pointer." );
	
	CHK_CMT( CmtGetTSVPtr ( handle , &pLocalStorage ));

	pLocalStorage->pClb->GetLastResultStatus ( pLocalStorage->pClb->handle , piResultStatus );  

Error:
	
	if ( handle )
	{
		if ( IS_NOT_OK )
		{
			FREE_STDERR_POINTER(pLocalStorage->pLastError);
			GET_STDERR_CLEAR(pLocalStorage->pLastError);
		}
	
		CmtReleaseTSVPtr (handle);
	}
	
	return StdError.error;
}

void	DLLEXPORT	TECOM_MEM_Free( void *pPointer )
{
	FREE(pPointer);
	
	return;
}

void	DLLEXPORT	TECOM_MEM_FreeList( void **pPointer , int iNumberOfItems )
{
	FREE_LIST(pPointer,iNumberOfItems);
	
	return;
}
