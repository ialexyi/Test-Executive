#ifndef __PathSupport_H__
#define __PathSupport_H__

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

//==============================================================================
// External variables

//==============================================================================
// Global functions

STD_ERROR				PATH_SetPath( int handle , int iType , int iPathPartIndex , char *pDeviceAddress , char *pszForcePathName , int *pSkipThisPath , ... );			
STD_ERROR				PATH_Discard( int handle , int iSelectedTestIndex );
STD_ERROR				PATH_SetDirectCommand( int handle , char *pCommand , char **pRespondsString );			
STD_ERROR				PATH_Extract_Frequency_Ranges( char *pRangesString , double **pFrequencyList , int **pRangesList , int *piNumberOfPoints , int *piNumberOfRanges ); // sample "1E9,2E9-8E9:50"
STD_ERROR 				PATH_Devices_Apply_Post_Commands( int handle );
STD_ERROR 				PATH_Devices_Apply_Auto_Commands( int handle );			

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __PathSupport_H__ */
