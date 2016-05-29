#ifndef __GraphBuilderAPI_H__
#define __GraphBuilderAPI_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
		
#ifndef				__TEST_EXECUTIVE__ 
#include "GlobalDefines.h" 
#else
#include "clb.h" 
#endif

#include "GraphBuilder.h"

		
//==============================================================================
// Constants

#define					GRAPH_DEFAULT_PANEL_FILE				"GraphBuilder.uir"
//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions

STD_ERROR	DLLEXPORT		GRAPH_CreateItem(  char *szUIRfilename , int panel_const , int control_const , void **pData , unsigned int numberOfPoints , double StartX , double StopX , double MaxY , double MinY , char *szX_AxisName , char *szY_AxisName  , int bDisplayGraph , int *piGraphPanelHandle );
STD_ERROR	DLLEXPORT		GRAPH_FreeItem( void **Data , int bDiscardPanel );
STD_ERROR	DLLEXPORT		GRAPH_FreeTraceItems( void *Data ); 

STD_ERROR	DLLEXPORT		GRAPH_AddTrace( void *Data , double *pTraceBuffer , unsigned int buffer_size , unsigned int startFromIndex , unsigned int numberOfPoints , double StartX , char *szTraceName  , int color , int iThickness , int iStyle );
STD_ERROR	DLLEXPORT		GRAPH_AddLabel( void *Data , double X_Position , double Y_Position , char *szLabelText  , int color , int label_type );

STD_ERROR	DLLEXPORT		GRAPH_Plot( void *Data , int iYAxisPrecision );
STD_ERROR	DLLEXPORT		GRAPH_PlotToFile( void *Data , char *szPathFileName , int iYAxisPrecision );

STD_ERROR	DLLEXPORT		GRAPH_CompressBuffer( void *Data , char **pTransferBuffer , unsigned long *pBufferCount ); 
STD_ERROR	DLLEXPORT		GRAPH_ExtractBuffer(  char *szUIRfilename , int panel_const , int control_const , void **pData , char *pTransferBuffer , int iBufferCount , int bDisplayGraph , int *piGraphPanelHandle );
																   
int			DLLEXPORT		GRAPH_GetNumberOfTraces( void *pItemData );
int			DLLEXPORT		GRAPH_GetNumberOfPoints( void *pItemData );
double		DLLEXPORT		GRAPH_GetNumberOfStartX( void *pItemData );
double		DLLEXPORT		GRAPH_GetNumberOfStopX( void *pItemData );
double		DLLEXPORT		GRAPH_GetStep( void *pItemData ); 
double		DLLEXPORT		GRAPH_GetNumberOfMaxY( void *pItemData );
double		DLLEXPORT		GRAPH_GetNumberOfMinY( void *pItemData );
STD_ERROR	DLLEXPORT		GRAPH_GetNumberOfX_AxisName( void *pItemData , char *szX_AxisName );
STD_ERROR	DLLEXPORT		GRAPH_GetNumberOfY_AxisName( void *pItemData , char *szY_AxisName );
	
STD_ERROR	DLLEXPORT		GRAPH_TRACE_CatTraces( void *pDestinationItemData , void *pSourceItemData ); 
STD_ERROR	DLLEXPORT		GRAPH_TRACE_GetTrace( void *pItemData , int iTraceIndex , double **pTrace );
double		DLLEXPORT		GRAPH_TRACE_GetTraceValue( void *pItemData , int iTraceIndex , int iPointIndex );
int			DLLEXPORT		GRAPH_TRACE_GetBufferSize( void *pItemData , int iTraceIndex );
STD_ERROR	DLLEXPORT		GRAPH_TRACE_SetTraceThickness( void *pItemData , int iTraceIndex , int iThickness );
int			DLLEXPORT		GRAPH_TRACE_GetStartFromIndex( void *pItemData , int iTraceIndex );
int			DLLEXPORT		GRAPH_TRACE_GetNumberOfPoints( void *pItemData , int iTraceIndex );
double		DLLEXPORT		GRAPH_TRACE_GetStartX( void *pItemData , int iTraceIndex );
int			DLLEXPORT		GRAPH_TRACE_GetColor( void *pItemData , int iTraceIndex );
STD_ERROR	DLLEXPORT		GRAPH_TRACE_GetTraceName( void *pItemData , int iTraceIndex , char *szTraceName );

STD_ERROR	DLLEXPORT		GRAPH_TRACE_UpdateTrace( void *pItemData , int iTraceIndex , double *pTrace );  

double		DLLEXPORT		GRAPH_UpdateNumberOfMaxY( void *pItemData , double value );
double		DLLEXPORT		GRAPH_UpdateNumberOfMinY( void *pItemData , double value );
double		DLLEXPORT		GRAPH_UpdateNumberOfStartX( void *pItemData , double value );
double		DLLEXPORT		GRAPH_UpdateNumberOfStopX( void *pItemData , double value );
int			DLLEXPORT		GRAPH_UpdateNumberOfPoints( void *pItemData , int value ); 

STD_ERROR	DLLEXPORT		GRAPH_TRACE_ApplyMultiplierForTraceValues( void *pItemData , int iTraceIndex , double lfMultiplier );
STD_ERROR	DLLEXPORT		GRAPH_TRACE_ApplyMultiplierForAllTracesValues( void *pItemData , double lfMultiplier );

STD_ERROR	DLLEXPORT		GRAPH_TRACE_ApplyMaxMinForTrace( void *pItemData , int iTraceIndex , double lfMaximumMargenOffset , double lfMinimumMargenOffset );
STD_ERROR	DLLEXPORT		GRAPH_TRACE_ApplyMaxMinForAllTraces( void *pItemData , double lfMaximumMargenOffset , double lfMinimumMargenOffset );

int			DLLEXPORT		GRAPH_Extra_Set_SN_Field( void *pItemData , char *pszSerialNumber );
int			DLLEXPORT		GRAPH_Extra_Set_PN_Field( void *pItemData , char *pszPartNumber );
int			DLLEXPORT		GRAPH_Extra_Set_Date_Field( void *pItemData , char *pszDate );

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __GraphBuilderAPI_H__ */
