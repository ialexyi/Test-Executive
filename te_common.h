#ifndef __te_common_H__
#define __te_common_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions

int		_GetVarInt(int handle, int vartype, char *name, va_list arguments );
int 	_GetVarIntArray(int handle, int vartype, char *name, int **result, va_list arguments );
double 	_GetVarDouble(int handle, int vartype, char *name, va_list arguments );
int 	_GetVarDoubleArray(int handle, int vartype, char *name, double **result, va_list arguments );
char 	*_GetVarString(int handle, int vartype, char *name, va_list arguments );
char 	**_GetVarStringArray(int handle, int vartype, char *name, int *pNumberOfItems, va_list arguments );
int 	_SetVarString(int handle, int vartype, char *name, char *string, va_list arguments );
int 	_SetVarStringArray(int handle, int vartype, char *name, char **string, int iNumberOfItems, va_list arguments );
int		_SetVarInt(int handle, int vartype, char *name, int value, va_list arguments );
int		_SetVarIntArray(int handle, int vartype, char *name, int *pArrayValues, int Count, va_list arguments );
int		_SetVarDouble(int handle, int vartype, char *name, double value, va_list arguments );
int		_SetVarDoubleArray(int handle, int vartype, char *name, double *pArrayValues, int Count, va_list arguments );
int		_SetVarCalibration(int handle, int vartype, int iRange, int bCleanBefore, char *name, double *frequency, double *factor, int iNumOfPoints, va_list arguments );
int		_GetVarCalibration(int handle, int vartype, int iRange, char *name, double **frequency, double **factor, int *piNumOfPoints, double *plfCalibrationDate, va_list arguments );
int		_SetVarCurrentCalibration(int handle, int iRange, int bCleanBefore, double *frequency, double *factor, int iNumOfPoints, va_list arguments );
int		_GetVarCurrentCalibration(int handle, int iRange, double **frequency, double **factor, int *piNumOfPoints, double *plfCalibrationDate, va_list arguments );
int		_GetVarCalibrationByName(int handle, char *pszName, int iRange, double **frequency, double **factor, int *piNumOfPoints, double *plfCalibrationDate, va_list arguments );

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __te_common_H__ */
