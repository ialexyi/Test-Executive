//==============================================================================
// Include files
#include "Windows.h"
#include <userint.h>

#include <ansi_c.h>
#include <analysis.h>
#include <utility.h>
#include "GraphBuilder.h"
#include "GlobalDefines.h"
#include "toolbox.h"
#include "GraphBuilderAPI.h"
//==============================================================================
// Constants
//#define			MODULE_NAME			"GraphBuilder"
//==============================================================================
// Types
#pragma pack(1)
typedef struct LABEL_ITEM
{
	int					controlID,
						left,
						top,
						right,
						bottom,
						color;
	
	double				X_Position,
						Y_Position;
	
	char				szLabelText[128];
	
	int					label_type;
	
	struct LABEL_ITEM	*pNextLabel;
	
} tsLabelItem;

typedef struct
{
	unsigned int		buffer_size;
					
	double				*Trace;
	
	unsigned int		startTraceFromIndex,
						numberOfPoints;
	
	int					trace_color;
	
	char				szTraceName[128];
	
	double				start_x;
	
	int					iThickness,
						iStyle;
	
} tsSingleTrace;


typedef struct
{
	int					panel,
						control,
						bExtUse;
	
	int					numberOfTraces,
						numberOfPoints;
	
	tsSingleTrace		*TraceList;
	
	double				start_x,
						stop_x;
	
	double				y_axis_max,
						y_axis_min;
	
	char				szY_AxisName[128],
						szX_AxisName[128];
		
	tsLabelItem			Labels;
	
} tsPlotGraphData;


typedef struct
{
	union
	{
		struct
		{
			int			numberOfTraces,
						numberOfLabels,
						//----------------//
						numberOfPoints;
			
			double		startX,
						stopX,
						maxY,
						minY;
			
			char		nameY[128],
						nameX[128];
		} frame;
		
		char			pBuffer[300]; 
	};
	
} tsMainFrame;


typedef struct
{
	union
	{
		struct
		{
			int			blockSize,
						nextIndex,
						dataItemsSize,
						dataStartIndex,
						numberOfPoints,
						dataTraceColor;

			double		startX;
			
			char		name[120];

			int			thickness,
						style;
			
		} frame;
		
		char			pBuffer[130];  
	};
	
} tsTraceFrame;

typedef struct
{
	union
	{
		struct
		{
			int					color;
	
			double				X_Position,
								Y_Position;
	
			int					label_type; 
			
			char				szLabelText[128];
			
		} frame;
		
		char					pBuffer[152];  
	};
	
} tsLabelFrame;

typedef union
{
	char		*pcBuffer;
	double		*plfBuffer;
	
} tuConvertBuffer;

#pragma pack()
//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions


//==============================================================================
// DLL main entry-point functions

int __stdcall DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            if (InitCVIRTE (hinstDLL, 0, 0) == 0)
                return 0;     /* out of memory */
            break;
        case DLL_PROCESS_DETACH:
            CloseCVIRTE ();
            break;
    }
    
    return 1;
}

int __stdcall DllEntryPoint (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    /* Included for compatibility with Borland */

    return DllMain (hinstDLL, fdwReason, lpvReserved);
}

//int main (int argc, char *argv[])
//{
//	STD_ERROR		StdError			=	{0};  
//	
//	tsPlotGraphData				data				=	{0},
//								recieve				=	{0};
//	
//	double 						TraceBuffer[1001]	=	{0.0};
//	
//	double						temp				=	0.0;
//	
//	int							count				=	0;
//	
//	char						*pTransferBuffer	=	NULL;
//    /* initialize and load resources */
//    if ( InitCVIRTE (0, argv, 0) == 0 )
//		return 0;
//    
//	SineWave (601, 5.0, 7.8125e-3, &temp, TraceBuffer);
//	
//	GRAPH_CreateItem( "GraphBuilder.uir" , PANEL , PANEL_STRIPCHART , &data , 1 , 601 , 0 , 360.0 , 10.0 , -10.0 , "Frequency" , "Power" , 1);
//		
//	GRAPH_AddTrace( &data , TraceBuffer , 1001 , 0 , 601 , 0 , "Spart"  , VAL_RED );
//		
//	GRAPH_AddLabel( &data , 72.0 , -2.0 , "180Hz 5.0V"  , VAL_RED , 1 );
//
//	StdError = GRAPH_CompressBuffer( &data , &pTransferBuffer , &count ); 
//		
//	StdError = GRAPH_ExtractBuffer( "GraphBuilder.uir", PANEL , PANEL_STRIPCHART , &recieve , pTransferBuffer , count , 1 ); 
//		
//	GRAPH_PlotToFile( &recieve , NULL );
//	
//	GRAPH_FreeItem( &recieve ); 
//	
//	GRAPH_PlotToFile( &data , NULL ); 
//	
//	GRAPH_FreeItem( &data ); 
//	
//	return 0;
//}


int	DLLEXPORT	GRAPH_GetNumberOfTraces( void *pItemData )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	int					value		=	0;
	
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	value = pData->numberOfTraces;
	
Error:	
	
	return value;
	
}

int	DLLEXPORT	GRAPH_GetNumberOfPoints( void *pItemData )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	int					value		=	0;
	
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	value = pData->numberOfPoints;
	
Error:	
	
	return value;
	
}

int	DLLEXPORT	GRAPH_UpdateNumberOfPoints( void *pItemData , int value ) 
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	pData->numberOfPoints = value;
	
Error:	
	
	return value;
	
}

double	DLLEXPORT	GRAPH_GetNumberOfStartX( void *pItemData )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	double				value		=	0;
	
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	value = pData->start_x;
	
Error:	
	
	return value;
	
}

double	DLLEXPORT	GRAPH_GetNumberOfStopX( void *pItemData )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	double				value		=	0;
	
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	value = pData->stop_x;
	
Error:	
	
	return value;
	
}

double	DLLEXPORT	GRAPH_UpdateNumberOfStartX( void *pItemData , double value )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	pData->start_x = value;
	
Error:	
	
	return value;
	
}

double	DLLEXPORT	GRAPH_UpdateNumberOfStopX( void *pItemData , double value ) 
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	pData->stop_x = value;

Error:	
	
	return value;
	
}

double	DLLEXPORT	GRAPH_GetStep( void *pItemData )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	double				value		=	0;
	
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	value = ( pData->stop_x - pData->start_x ) / ( pData->numberOfPoints - 1 );  
	
Error:	
	
	return value;
	
}

double	DLLEXPORT	GRAPH_GetNumberOfMaxY( void *pItemData )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	double				value		=	0;
	
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	value = pData->y_axis_max;
	
Error:	
	
	return value;
	
}

double	DLLEXPORT	GRAPH_GetNumberOfMinY( void *pItemData )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	double				value		=	0;
	
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	value = pData->y_axis_min;
	
Error:	
	
	return value;
	
}

double	DLLEXPORT	GRAPH_UpdateNumberOfMaxY( void *pItemData , double value )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	pData->y_axis_max = value;
	
Error:	
	
	return value;
	
}

double	DLLEXPORT	GRAPH_UpdateNumberOfMinY( void *pItemData , double value ) 
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	pData->y_axis_min = value;

Error:	
	
	return value;
	
}

STD_ERROR	DLLEXPORT	GRAPH_GetNumberOfX_AxisName( void *pItemData , char *szX_AxisName )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	strcpy( szX_AxisName , pData->szX_AxisName );
	
Error:	
	
	return StdError;
	
}

STD_ERROR	DLLEXPORT	GRAPH_GetNumberOfY_AxisName( void *pItemData , char *szY_AxisName )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	strcpy( szY_AxisName , pData->szY_AxisName );
	
Error:	
	
	return StdError;
	
}

STD_ERROR	DLLEXPORT	GRAPH_CreateItem( char *szUIRfilename , int panel_const , int control_const , void **pItemData , unsigned int numberOfPoints , double StartX , double StopX , double MaxY , double MinY , char *szX_AxisName , char *szY_AxisName  , int bDisplayGraph , int *piGraphPanelHandle )
{
	STD_ERROR				StdError					=	{0};
	
	tsPlotGraphData			*pData				=	NULL;

	CALLOC_ERR( pData , 1 , sizeof(tsPlotGraphData));
	
	IF (( pItemData == NULL ) , "Item data can't be NULL");
	
	NO_CHK_STDERR(GRAPH_FreeItem( pItemData , 0 ));
	
	*pItemData = pData;
		
	pData->numberOfTraces = 0;
	pData->numberOfPoints = numberOfPoints;
		
	pData->start_x = StartX;
	pData->stop_x = StopX;
	pData->y_axis_max = MaxY;
	pData->y_axis_min = MinY;
	
	if (szUIRfilename != NULL)
	{
		if ( piGraphPanelHandle && ( *piGraphPanelHandle ))
		{
			pData->panel = *piGraphPanelHandle;
		}
		else
		{
			pData->panel = LoadPanelEx (0, szUIRfilename , panel_const , __CVIUserHInst ); 

			if ( piGraphPanelHandle )
				*piGraphPanelHandle = pData->panel;
		}

		if ( bDisplayGraph )
			DisplayPanel( pData->panel );
		
		pData->bExtUse = 0;
	}
	else
	{
		pData->panel = panel_const;
		pData->bExtUse = 1;
	}
	
	pData->control = control_const;
		
	if ( szX_AxisName )
		strcpy( pData->szX_AxisName , szX_AxisName );
	
	if ( szY_AxisName )
		strcpy( pData->szY_AxisName , szY_AxisName );
Error:	
	
	return StdError;
	
}

void	free_recursive_labels( tsPlotGraphData data , tsLabelItem *pCurrentLabel )
{
	if ( pCurrentLabel == NULL )
		return;
	
	free_recursive_labels(data,pCurrentLabel->pNextLabel);
	
	DiscardCtrl ( data.panel , pCurrentLabel->controlID );
		
	free(pCurrentLabel);
	
	return;
}

STD_ERROR	DLLEXPORT	GRAPH_FreeItem( void **Data , int bDiscardPanel )
{
	STD_ERROR				StdError						=	{0};

	int					index					=	0;
	
	tsPlotGraphData		*pData					=	NULL,
						**pDataInput			=	NULL;
	
	pDataInput = (tsPlotGraphData**)Data;
	
	IF ( (pDataInput == NULL) , "Pointer passed NULL");
	
	pData = *pDataInput; 
	
	IF ( (pData == NULL) , "Pointer passed NULL");
	
	*pDataInput = NULL;
	
	if ( pData->TraceList )
	{
		for ( index = 0 ; index < pData->numberOfTraces  ; index++ )
			if ( pData->TraceList[index].buffer_size ) 
				if ( pData->TraceList[index].Trace )
					free( pData->TraceList[index].Trace );
		
		free ( pData->TraceList );
		
		pData->TraceList = NULL;
	}
	
	free_recursive_labels( *pData , pData->Labels.pNextLabel );
	pData->Labels.pNextLabel = 0;
	
	if ( bDiscardPanel )
	{
		if (( pData->panel ) && ( pData->bExtUse == 0 ))
			DiscardPanel( pData->panel );
	}
	
Error:	
	
	FREE(pData);
	
	return StdError;
	
}

STD_ERROR	DLLEXPORT	GRAPH_FreeTraceItems( void *Data )
{
	STD_ERROR				StdError						=	{0};

	int					index					=	0;
	
	tsPlotGraphData		*pData					=	NULL;
	
	IF ( (Data == NULL) , "Pointer passed NULL");
	
	pData = (tsPlotGraphData*)Data;
	
	if ( pData->TraceList )
	{
		for ( index = 0 ; index < pData->numberOfTraces  ; index++ )
			if ( pData->TraceList[index].buffer_size ) 
				if ( pData->TraceList[index].Trace )
					free( pData->TraceList[index].Trace );
		
		free ( pData->TraceList );
		
		pData->TraceList = NULL;
		pData->numberOfTraces = 0;
	}
	
Error:	
	
	return StdError;
	
}

STD_ERROR	DLLEXPORT	GRAPH_TRACE_CatTraces( void *pDestinationItemData , void *pSourceItemData )
{
	STD_ERROR				StdError						=	{0};
	
	tsPlotGraphData		*pSourceData			=	NULL;
		
	int					index					=	0;
	
	IF (( pSourceItemData == NULL ) , "NULL Pointer.");   
	
	pSourceData = pSourceItemData;
	
	for ( index = 0 ; index < pSourceData->numberOfTraces ; index++ )  
		GRAPH_AddTrace( pDestinationItemData , pSourceData->TraceList[index].Trace , pSourceData->TraceList[index].buffer_size , pSourceData->TraceList[index].startTraceFromIndex , pSourceData->TraceList[index].numberOfPoints , pSourceData->TraceList[index].start_x , pSourceData->TraceList[index].szTraceName  , pSourceData->TraceList[index].trace_color , pSourceData->TraceList[index].iThickness , pSourceData->TraceList[index].iStyle );
	
Error:	
	
	return StdError;
	
}


STD_ERROR	DLLEXPORT	GRAPH_TRACE_GetTrace( void *pItemData , int iTraceIndex , double **pTrace )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	double				*trace		=	NULL;
	
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	CALLOC_COPY( trace , pData->TraceList[iTraceIndex].buffer_size , sizeof(double) , pData->TraceList[iTraceIndex].Trace , ( pData->TraceList[iTraceIndex].buffer_size * sizeof(double) ));
	
	if ( pTrace ) 
	{
		FREE(*pTrace);
		*pTrace = trace;
	}
	
Error:	
	
	return StdError;
	
}

STD_ERROR	DLLEXPORT	GRAPH_TRACE_UpdateTrace( void *pItemData , int iTraceIndex , double *pTrace )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	IF (( pTrace == NULL ) , "NULL Pointer.");
	
	pData = pItemData;
	
	if ( pData->TraceList[iTraceIndex].Trace )
		free ( pData->TraceList[iTraceIndex].Trace );
	
	pData->TraceList[iTraceIndex].Trace = calloc( pData->TraceList[iTraceIndex].buffer_size+1 , sizeof(double) );
	
	if ( pData->TraceList[iTraceIndex].Trace )
		memcpy( pData->TraceList[iTraceIndex].Trace , pTrace , ( pData->TraceList[iTraceIndex].buffer_size * sizeof(double) ));
	
Error:	
	
	return StdError;
}

double	DLLEXPORT	GRAPH_TRACE_GetTraceValue( void *pItemData , int iTraceIndex , int iPointIndex )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	double				value		=	0;
	
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	value = pData->TraceList[iTraceIndex].Trace[iPointIndex];
	
Error:	
	
	return value;
	
}

STD_ERROR	DLLEXPORT	GRAPH_TRACE_SetTraceThickness( void *pItemData , int iTraceIndex , int iThickness )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData			*pData				=	NULL;
		
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	pData->TraceList[iTraceIndex].iThickness = iThickness;
	
Error:	
	
	return StdError;
}

int	DLLEXPORT	GRAPH_TRACE_GetBufferSize( void *pItemData , int iTraceIndex )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	int					value		=	0;
	
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	value = pData->TraceList[iTraceIndex].buffer_size;
	
Error:	
	
	return value;
	
}


int	DLLEXPORT	GRAPH_TRACE_GetStartFromIndex( void *pItemData , int iTraceIndex )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	int					value		=	0;
	
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	value = pData->TraceList[iTraceIndex].startTraceFromIndex;
	
Error:	
	
	return value;
	
}

int	DLLEXPORT	GRAPH_TRACE_GetNumberOfPoints( void *pItemData , int iTraceIndex )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	int					value		=	0;
	
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	value = pData->TraceList[iTraceIndex].numberOfPoints;
	
Error:	
	
	return value;
	
}

double	DLLEXPORT	GRAPH_TRACE_GetStartX( void *pItemData , int iTraceIndex )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	double				value		=	0;
	
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	value = pData->TraceList[iTraceIndex].start_x;
	
Error:	
	
	return value;
	
}

int	DLLEXPORT	GRAPH_TRACE_GetColor( void *pItemData , int iTraceIndex )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	int					value		=	0;
	
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	value = pData->TraceList[iTraceIndex].trace_color;
	
Error:	
	
	return value;
	
}

STD_ERROR	DLLEXPORT	GRAPH_TRACE_GetTraceName( void *pItemData , int iTraceIndex , char *szTraceName )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData		*pData		=	NULL;
		
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	strcpy( szTraceName , pData->TraceList[iTraceIndex].szTraceName );
	
Error:	
	
	return StdError;
	
}

STD_ERROR	DLLEXPORT	GRAPH_AddTrace( void *Data , double *pTraceBuffer , unsigned int buffer_size , unsigned int startFromIndex , unsigned int numberOfPoints , double StartX , char *szTraceName  , int color , int iThickness , int iStyle )
{
	STD_ERROR				StdError						=	{0};
	
	tsPlotGraphData		*pData					=	NULL;
	
	tsSingleTrace		*pTempTrace				=	NULL;
	
	int					STR_COLORS[64] 			= { VAL_RED, VAL_GREEN , VAL_BLUE, VAL_CYAN , VAL_MAGENTA , VAL_YELLOW , VAL_DK_RED , VAL_DK_BLUE , VAL_DK_GREEN , VAL_DK_CYAN , VAL_DK_MAGENTA ,VAL_DK_YELLOW , VAL_LT_GRAY , VAL_DK_GRAY , VAL_BLACK };
	
	int					index					=	0;
	
	IF ( (Data == NULL) , "Pointer passed NULL");
	
	pData = (tsPlotGraphData*)Data;
	
	IF (( pTraceBuffer == NULL ) , "Passed NULL pointer of Trace Buffer.");
	IF ((( startFromIndex + numberOfPoints ) > buffer_size ) , "Number of points is too big.");     
	
	CALLOC_ERR( pTempTrace , pData->numberOfTraces + 1 , sizeof(tsSingleTrace));
	
	for( index = 0 ; index < pData->numberOfTraces ; index++ )
		memcpy( &(pTempTrace[index]) , &(pData->TraceList[index]) , sizeof(tsSingleTrace));    
		
	CALLOC_ERR( pTempTrace[index].Trace , buffer_size , sizeof( double ));
		
	IF (( pTempTrace[index].Trace == NULL ), "Can't allocate Memory.");
	
	memcpy( pTempTrace[index].Trace , (pTraceBuffer+startFromIndex) , (sizeof( double )*numberOfPoints) );
	
	pTempTrace[index].numberOfPoints = numberOfPoints;
	pTempTrace[index].buffer_size = numberOfPoints;
	//pTempTrace[index].startTraceFromIndex = startFromIndex;
	pTempTrace[index].start_x = StartX;
	pTempTrace[index].iThickness = iThickness;
	
	if ( color )
		pTempTrace[index].trace_color = color;
	else
		pTempTrace[index].trace_color = STR_COLORS[index];
		
	if ( szTraceName )
		strcpy ( pTempTrace[index].szTraceName , szTraceName );
	
	FREE(pData->TraceList);
	pData->TraceList = pTempTrace;
	
	pData->numberOfTraces++;
	
Error:
	
	return StdError;
}


STD_ERROR	DLLEXPORT	GRAPH_TRACE_ApplyMultiplierForTraceValues( void *pItemData , int iTraceIndex , double lfMultiplier )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData			*pData				=	NULL;
		
	int						iPointIndex			=	0;
	
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	if (( lfMultiplier != 0.0 ) && ( lfMultiplier != 1.0 ))
	{
		for( iPointIndex = 0; iPointIndex < pData->TraceList[iTraceIndex].numberOfPoints; iPointIndex++ )
			pData->TraceList[iTraceIndex].Trace[iPointIndex] *= lfMultiplier;
	}
	
Error:	
	
	return StdError;
}

STD_ERROR	DLLEXPORT	GRAPH_TRACE_ApplyMultiplierForAllTracesValues( void *pItemData , double lfMultiplier )
{
	STD_ERROR				StdError			=	{0};

	tsPlotGraphData			*pData				=	NULL;
	
	int						iTraceIndex			=	0;
	
	IF (( pItemData == NULL ) , "NULL Pointer.");    

	pData = pItemData;
	
	for( iTraceIndex = 0; iTraceIndex < pData->numberOfTraces; iTraceIndex++ )
	{
		GRAPH_TRACE_ApplyMultiplierForTraceValues( pItemData , iTraceIndex , lfMultiplier ); 
	}
	
Error:	
	
	return StdError;
}
 
STD_ERROR	DLLEXPORT	GRAPH_TRACE_ApplyMaxMinForTrace( void *pItemData , int iTraceIndex , double lfMaximumMargenOffset , double lfMinimumMargenOffset )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData			*pData				=	NULL;
		
	int						iPointIndex			=	0;
	
	double					lfMaximum			=	0.0,
							lfMinimum			=	0.0;
	
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	
	pData = pItemData;
	
	for( iPointIndex = 0; iPointIndex < pData->TraceList[iTraceIndex].numberOfPoints; iPointIndex++ )
	{
		if (( pData->TraceList[iTraceIndex].Trace[iPointIndex] > lfMaximum ) || ( iPointIndex == 0 ))
			lfMaximum = pData->TraceList[iTraceIndex].Trace[iPointIndex];

		if (( pData->TraceList[iTraceIndex].Trace[iPointIndex] < lfMinimum ) || ( iPointIndex == 0 ))
			lfMinimum = pData->TraceList[iTraceIndex].Trace[iPointIndex];
	}
	
	pData->y_axis_max = lfMaximum + lfMaximumMargenOffset;
	pData->y_axis_min = lfMinimum + lfMinimumMargenOffset;
	
Error:	
	
	return StdError;
}

STD_ERROR	DLLEXPORT	GRAPH_TRACE_ApplyMaxMinForAllTraces( void *pItemData , double lfMaximumMargenOffset , double lfMinimumMargenOffset )
{
	STD_ERROR				StdError			=	{0};

	tsPlotGraphData			*pData				=	NULL;
	
	int						iTraceIndex			=	0;
	
	IF (( pItemData == NULL ) , "NULL Pointer.");    

	pData = pItemData;
	
	for( iTraceIndex = 0; iTraceIndex < pData->numberOfTraces; iTraceIndex++ )
	{
		GRAPH_TRACE_ApplyMaxMinForTrace( pItemData , iTraceIndex , lfMaximumMargenOffset , lfMinimumMargenOffset );
	}
	
Error:	
	
	return StdError;
}

STD_ERROR	DLLEXPORT	GRAPH_Plot( void *Data , int iYAxisPrecision )
{
	STD_ERROR		StdError			=	{0};

	int			panel				=	0;
	
	int			numberOfPoints		=	0,
				numberOfTraces		=	0,
				maxNumberOfPoints	=	0;
	
	int			index				=	0,
				tempIndex			=	0, 
				totalIndex			=	0, 
				PlotIndex			=	0;
	
	int			*pPointCounter		=	NULL;
				
	double		*pSinglePlot		=	NULL;
	
	double		lfCurrentX			=	0.0,
				lfStepX				=	0.0;
	
	double		lfY_axis_min		=	0.0,
				lfY_axis_max		=	0.0;
	
	tsPlotGraphData		*pData					=	NULL;
	
	IF ( (Data == NULL) , "Pointer passed NULL");
	
	pData = (tsPlotGraphData*)Data;
	
	IF( ( pData->TraceList == NULL ) , "No traces added.");
	IF( ( pData->numberOfTraces == 0 ) , "No traces added.");

	panel = pData->panel;
	
	numberOfTraces = pData->numberOfTraces;
	
	lfCurrentX = pData->start_x;
	
	if ( pData->numberOfPoints )
		lfStepX = ( pData->stop_x - pData->start_x ) / (double)(pData->numberOfPoints-1);  
	else
		lfStepX = pData->stop_x - pData->start_x;
	
	ProcessDrawEvents();
	
	numberOfPoints = pData->numberOfPoints;
	
	if ( numberOfPoints == 0 )
	{
		for ( index = 0 ; index < numberOfTraces  ; index++ ) 
			if ( pData->TraceList[index].numberOfPoints > numberOfPoints )
				numberOfPoints = pData->TraceList[index].numberOfPoints;
		
	}
	
	maxNumberOfPoints = numberOfPoints * numberOfTraces;
	
	CALLOC_ERR( pSinglePlot , maxNumberOfPoints+128 , sizeof(double));
	CALLOC_ERR( pPointCounter , numberOfTraces+1 , sizeof(int));
		
	IF (( pSinglePlot == NULL ), "Can't allocate Memory.");    
	IF (( pPointCounter == NULL ), "Can't allocate Memory.");  
	
	SetCtrlAttribute ( panel , pData->control , ATTR_NUM_TRACES , numberOfTraces ); 
	
	SetCtrlAttribute ( panel , pData->control , ATTR_SCROLL_MODE , VAL_CONTINUOUS );	
	SetCtrlAttribute (panel, pData->control, ATTR_GRID_COLOR, VAL_BLACK);
		
	SetCtrlAttribute ( panel , pData->control , ATTR_POINTS_PER_SCREEN , numberOfPoints );
	
	lfY_axis_min = pData->y_axis_min;
	lfY_axis_max = pData->y_axis_max;
	
	if (( IsNotANumber (lfY_axis_min) == 0 ) && ( IsNotANumber (lfY_axis_max) == 0 ) && ( fabs( lfY_axis_min ) > 1E-20 ) && ( fabs( lfY_axis_max ) > 1E-20 ))
	{
		SetAxisScalingMode (panel, pData->control, VAL_LEFT_YAXIS,VAL_MANUAL, lfY_axis_min , lfY_axis_max); 
	}
	
	SetAxisScalingMode (panel, pData->control, VAL_BOTTOM_XAXIS ,VAL_MANUAL, pData->start_x , lfStepX ); 

	SetCtrlAttribute (panel, pData->control, ATTR_YPRECISION , iYAxisPrecision );
		
	if ( pData->szY_AxisName )
		SetCtrlAttribute  ( panel , pData->control , ATTR_YNAME , pData->szY_AxisName );
	
	if ( pData->szX_AxisName ) 
		SetCtrlAttribute  (panel, pData->control , ATTR_XNAME , pData->szX_AxisName );
	
	SetCtrlAttribute ( panel , pData->control , ATTR_LEGEND_NUM_VISIBLE_ITEMS , numberOfTraces );
	
	for ( index = 0 ; index < numberOfTraces  ; index++ ) 
	{
		SetTraceAttribute ( panel , pData->control , index+1 , ATTR_TRACE_COLOR , pData->TraceList[index].trace_color );
		SetTraceAttributeEx ( panel , pData->control , index+1 , ATTR_TRACE_LG_TEXT , pData->TraceList[index].szTraceName ); 
	
		SetTraceAttribute ( panel , pData->control , index+1 , ATTR_TRACE_LG_TEXT_COLOR , VAL_BLACK );
		SetTraceAttribute ( panel , pData->control , index+1 , ATTR_TRACE_LG_VISIBLE , 1 );
		
		if ( pData->TraceList[index].iThickness > 0 )
			SetTraceAttribute (panel, pData->control, index+1 ,ATTR_TRACE_THICKNESS, pData->TraceList[index].iThickness );
		
		SetTraceAttribute ( panel , pData->control , index+1 , ATTR_TRACE_VISIBLE , 1 );
	}
	
	for ( PlotIndex = 0 ; PlotIndex < numberOfPoints  ; PlotIndex++ ) 
	{
		for ( index = 0 ; index < numberOfTraces  ; index++ ) 
		{
			if ( ( lfCurrentX >= pData->TraceList[index].start_x ) && ( pPointCounter[index] < pData->TraceList[index].numberOfPoints ) && ( pPointCounter[index] < numberOfPoints ))
			{
				tempIndex = pPointCounter[index] + pData->TraceList[index].startTraceFromIndex;
				
				pSinglePlot[totalIndex++] = pData->TraceList[index].Trace[tempIndex];
				
				pPointCounter[index]++;
			}
			else
			{
				tempIndex = pData->TraceList[index].startTraceFromIndex;
				
				pSinglePlot[totalIndex++] = pData->TraceList[index].Trace[tempIndex];
				
				pPointCounter[index]++;
			}
		}
		
		lfCurrentX += lfStepX;
	}
	
	PlotStripChart ( panel , pData->control , pSinglePlot , totalIndex , 0 , 0 , VAL_DOUBLE );
	
Error:
	
	if ( pSinglePlot )
		free(pSinglePlot);
	
	if ( pPointCounter )
		free( pPointCounter );
	
	ProcessDrawEvents();  
	
	return StdError;
}

STD_ERROR	DLLEXPORT	GRAPH_PlotToFile( void *Data , char *szPathFileName , int iYAxisPrecision )
{
	STD_ERROR		StdError			=	{0};

	int			panel				=	0;
	
	int			hBitmapID			=	0;
	
	char		szOutput[1024]		=	{0},
				*pExtantion			=	NULL;
	
	tsPlotGraphData		*pData					=	NULL;
	
	IF ( (Data == NULL) , "Pointer passed NULL");
	
	pData = (tsPlotGraphData*)Data;
	
	IF( ( pData->TraceList == NULL ) , "No traces added.");
	IF( ( pData->numberOfTraces == 0 ) , "No traces added.");

	panel = pData->panel;
	
	if ( szPathFileName )
	{
		pExtantion = strrchr( szPathFileName , '.' );
	
		if ( pExtantion )
		{
			if (( strlen( szPathFileName ) - ( pExtantion - szPathFileName ) ) < 5 )
				*pExtantion = 0;
		}
	
		sprintf( szOutput , "%s.jpg" , szPathFileName );
	}
	else
	{
		strcpy( szOutput , "graph.jpg" );	
	}
	
	strcpy( szPathFileName , szOutput );
	
	StdError = GRAPH_Plot( Data , iYAxisPrecision );
	
	StdError.error = GetPanelDisplayBitmap ( panel , VAL_FULL_PANEL, VAL_ENTIRE_OBJECT , &hBitmapID );
	
	StdError.error = SaveBitmapToJPEGFile ( hBitmapID , szOutput , 0 , 100 );
	
	DiscardBitmap ( hBitmapID );
	
Error:
	
	return StdError;
}


int		marge_protection( int *derection , tsLabelItem *pNewLabel , tsLabelItem *pOldLabel , int max_x_value )
{
	int		newCenterX				=	0,
			newCenterY				=	0, 
			newVerticalSigment		=	0,
			newHorizontalSigment	=	0;

	int		oldCenterX				=	0,
			oldCenterY				=	0, 
			oldVerticalSigment		=	0,
			oldHorizontalSigment	=	0;

	int		verticalIsolation		=	0,
			horizontalIsolation		=	0;
	
	if ( derection == NULL )
		return -1;
	
	if ( pNewLabel == NULL )
		return -1;
	
	if ( pOldLabel == NULL )
		return -1;
	
	newCenterX = ( pNewLabel->right + pNewLabel->left ) / 2;
	oldCenterX = ( pOldLabel->right + pOldLabel->left ) / 2;
	newCenterY = ( pNewLabel->top + pNewLabel->bottom ) / 2;
	oldCenterY = ( pOldLabel->top + pOldLabel->bottom ) / 2;
	
	newVerticalSigment = ( pNewLabel->bottom - pNewLabel->top ) / 2;
	oldVerticalSigment = ( pOldLabel->bottom - pOldLabel->top ) / 2;
	newHorizontalSigment = ( pNewLabel->right - pNewLabel->left ) / 2;
	oldHorizontalSigment = ( pOldLabel->right - pOldLabel->left ) / 2;
	
	verticalIsolation = newVerticalSigment + oldVerticalSigment + 3;
	horizontalIsolation = newHorizontalSigment + oldHorizontalSigment + 3;  

	//-------- Checking -----------------------------------------------//
	if (((( newCenterY < ( oldCenterY - verticalIsolation)) || ( newCenterY > ( oldCenterY + verticalIsolation))))
		&& (( newCenterX > ( oldCenterX + horizontalIsolation )) || ( newCenterX < ( oldCenterX - horizontalIsolation ))))
		return 0;

	//------ Replase Axis Y ----------//
	if (!((( newCenterY < ( oldCenterY - verticalIsolation)) || ( newCenterY > ( oldCenterY + verticalIsolation)))))
	{
		
		if ( *derection == 0 )
		{
			newCenterY = newCenterY - verticalIsolation;
			
			if ( newCenterY < 1 )
			{
				*derection = !*derection;
				return 1;
			}
			
			pNewLabel->top -= verticalIsolation;
		
			return 1; 
		}
		else
		{
			pNewLabel->top += verticalIsolation;
		
			return 1; 
		}	

	}
	
	if ( *derection == 0 )
	{
		newCenterX = newCenterX + horizontalIsolation;
		
		if ( newCenterX > max_x_value )
		{
			*derection = !*derection;
			return 1;
		}
		
		pNewLabel->left += horizontalIsolation;
	
	}
	else
		pNewLabel->left -= horizontalIsolation;
		
	return 1;
}


STD_ERROR	DLLEXPORT	GRAPH_AddLabel( void *Data , double X_Position , double Y_Position , char *szLabelText  , int color , int label_type )
{
	STD_ERROR				StdError						=	{0};

	int					iStart_Y  				=	0,
						iStart_X  				=	0,
						iStop_Y   				=	0,
						iStop_X   				=	0,
						iPointLeft				=	0,
						iPointTop				=	0; 
	
	tsLabelItem			*pCurrentLabel			=	NULL,
						*pReferenceLabel		=	NULL; 
	
	int					derection				=	0,
						temp					=	0;
	
	int					min_digits				=	0,
						min_digits_counts		=	0,
						max_digits				=	0, 
						max_digits_counts		=	0,
						x_offset				=	0;
	
	double				xPosition				=	0.0,
						yPosition				=	0.0;
	
	tsPlotGraphData		*pData					=	NULL;
	
	SetBreakOnLibraryErrors (0);
	
	IF ( (Data == NULL) , "Pointer passed NULL");
	
	pData = (tsPlotGraphData*)Data;
	
	IF (( pData->panel == 0 ) , "No Graph Data Created.");  
	IF (( szLabelText == 0 ) , "Label Text is NULL pointer."); 
	
	xPosition = X_Position;
	yPosition = Y_Position;
	
	pCurrentLabel = &pData->Labels;
		
	if ( pCurrentLabel->controlID )
		do
		{
			if ( pCurrentLabel->pNextLabel == NULL )
			{
				CALLOC_ERR( pCurrentLabel->pNextLabel , 1 , sizeof(tsLabelItem));
				
				pCurrentLabel = pCurrentLabel->pNextLabel;
				break;
			}
			else
			{
				pCurrentLabel = pCurrentLabel->pNextLabel;	
			}
			
		} while(pCurrentLabel);
	
	switch(label_type)
	{
		case 1:
			
			pCurrentLabel->controlID = DuplicateCtrl ( pData->panel , GRAPH_BUIL_RIGHT_LABEL , pData->panel , szLabelText , 0 , 0 );
			
			break;
			
		default:
			
			pCurrentLabel->controlID = DuplicateCtrl ( pData->panel , GRAPH_BUIL_UP_LABEL , pData->panel , szLabelText , 0 , 0 );

			break;
	}
	
	GetCtrlAttribute ( pData->panel , GRAPH_BUIL_UP_LABEL , ATTR_TOP , &iStop_Y );
	GetCtrlAttribute ( pData->panel , GRAPH_BUIL_UP_LABEL , ATTR_LEFT , &iStart_X );
	GetCtrlAttribute ( pData->panel , GRAPH_BUIL_RIGHT_LABEL , ATTR_TOP , &iStart_Y );
	GetCtrlAttribute ( pData->panel , GRAPH_BUIL_RIGHT_LABEL , ATTR_LEFT , &iStop_X );
	
	GetCtrlAttribute ( pData->panel , pData->control , ATTR_POINTS_PER_SCREEN, &temp );
		
	X_Position = ( X_Position - pData->start_x ) / ( pData->stop_x - pData->start_x );
	Y_Position = ( Y_Position - pData->y_axis_min ) / ( pData->y_axis_max - pData->y_axis_min ); 
	
	Y_Position = 1.0 - Y_Position;
	
	min_digits = pData->y_axis_min; 
	min_digits_counts = 0;
	max_digits = pData->y_axis_max; 
	max_digits_counts = 0;
	
	do
	{
		min_digits /= 10;
		min_digits_counts++;
	}while(min_digits);
	do
	{
		max_digits /= 10;
		max_digits_counts++;
	}while(max_digits);

	if (( max_digits_counts > min_digits_counts ) || ( pData->y_axis_min >= 0.0 ))
	{
		max_digits_counts--;
		
		x_offset = max_digits_counts * 6; // 6 digit points
	}
	else
	{
		min_digits_counts--;
		
		x_offset = min_digits_counts * 6; // 6 digit points
		x_offset += 3; // - points
	}
	
	iPointLeft = (( iStop_X - iStart_X ) * X_Position ) + iStart_X + x_offset;
	iPointTop = (( iStop_Y - iStart_Y ) * Y_Position ) + iStart_Y; 
	
	SetCtrlAttribute ( pData->panel , pCurrentLabel->controlID , ATTR_TOP , iPointTop );
	SetCtrlAttribute ( pData->panel , pCurrentLabel->controlID , ATTR_LEFT , iPointLeft );
	
	if ( color )
	{
		SetCtrlAttribute ( pData->panel , pCurrentLabel->controlID , ATTR_OFF_COLOR , color );
		SetCtrlAttribute ( pData->panel , pCurrentLabel->controlID , ATTR_LABEL_BGCOLOR , color );
	}
	
	GetCtrlAttribute ( pData->panel , pCurrentLabel->controlID , ATTR_LABEL_LEFT , &pCurrentLabel->left );  
	GetCtrlAttribute ( pData->panel , pCurrentLabel->controlID , ATTR_LABEL_TOP , &pCurrentLabel->top );
	GetCtrlAttribute ( pData->panel , pCurrentLabel->controlID , ATTR_LABEL_HEIGHT , &pCurrentLabel->bottom );  
	GetCtrlAttribute ( pData->panel , pCurrentLabel->controlID , ATTR_LABEL_WIDTH , &pCurrentLabel->right );
	
	pCurrentLabel->bottom += pCurrentLabel->top;
	pCurrentLabel->right += pCurrentLabel->left;
	
	pCurrentLabel->X_Position = xPosition; 
	pCurrentLabel->Y_Position = yPosition;
	
	if (szLabelText)
		strcpy(pCurrentLabel->szLabelText , szLabelText);
	
	pCurrentLabel->label_type = label_type;
	
	pReferenceLabel = &pData->Labels;
		
	if ( pReferenceLabel->controlID )
		do
		{
			if ( pCurrentLabel != pReferenceLabel )
			{
				if ( marge_protection( &derection , pCurrentLabel , pReferenceLabel , iStop_X ))
				{
					SetCtrlAttribute ( pData->panel , pCurrentLabel->controlID , ATTR_LABEL_LEFT , pCurrentLabel->left );  
					SetCtrlAttribute ( pData->panel , pCurrentLabel->controlID , ATTR_LABEL_TOP , pCurrentLabel->top );
	
					// chack again
					pReferenceLabel = &pData->Labels;
				}
			}
			
			pReferenceLabel = pReferenceLabel->pNextLabel;	
			
		} while(pReferenceLabel);
	
	
	SetCtrlAttribute ( pData->panel , pCurrentLabel->controlID , ATTR_VISIBLE , 1 ); 
	
	ProcessDrawEvents();
	
Error:											   
	
	SetBreakOnLibraryErrors (1);
	
	return StdError;									   
}												   

//=======================================//
STD_ERROR	DLLEXPORT	GRAPH_CompressBuffer( void *Data , char **pTransferBuffer , unsigned long *pBufferCount )
{
	STD_ERROR				StdError								=	{0};

	int					numberOfLabels					=	0,
						numberOfTraces					=	0;
	
	int					fillIndex						=	0,
						sizeOfEmptyTrace				=	0,
						sizeOfFullBuffer				=	0,
						calcTracesSize					=	0,
						finalBufferSize					=	0; 
					
	
	tsPlotGraphData		*pData							=	NULL;
	
	tsTraceFrame		*pTraces						=	NULL;
	
	tsLabelFrame		*pLabels						=	NULL;
	
	tsLabelItem			*pCurrentLabel					=	NULL; 
	
	tsMainFrame			tMainFrame;
	
	char				*pDynamicPosition				=	NULL;
	
	tuConvertBuffer		convertBuffer					=	{NULL};
	
	memset( &tMainFrame , 0 , sizeof(tsMainFrame));
	
	IF ( (Data == NULL) , "Pointer passed NULL");
	IF ( (pTransferBuffer == NULL) , "Pointer passed NULL");  
	
	pData = (tsPlotGraphData*)Data;
	
	IF( ( pData->TraceList == NULL ) , "No traces added.");
	IF( ( pData->numberOfTraces == 0 ) , "No traces added.");

	numberOfTraces = pData->numberOfTraces;

	CALLOC_ERR ( pTraces , numberOfTraces ,sizeof(tsTraceFrame));
	
	pCurrentLabel = &pData->Labels;
		
	do
	{
		if ( pCurrentLabel == NULL ) 
			break;
			
		pCurrentLabel = pCurrentLabel->pNextLabel;	
		
		if ( pCurrentLabel == NULL )
			break;
		
		numberOfLabels++;
			
	} while(pCurrentLabel);
	
	//---------------- Filling Labels ------------------------//

	if ( numberOfLabels )
	{
		CALLOC_ERR ( pLabels , numberOfLabels , sizeof(tsLabelFrame));
	
		pCurrentLabel = &pData->Labels;
		fillIndex = 0;
	
		do
		{
			if ( pCurrentLabel == NULL ) 
				break;
			
			pLabels[fillIndex].frame.color = pCurrentLabel->color;
			pLabels[fillIndex].frame.X_Position = pCurrentLabel->X_Position;
			pLabels[fillIndex].frame.Y_Position = pCurrentLabel->Y_Position;
			pLabels[fillIndex].frame.label_type = pCurrentLabel->label_type;
			strcpy( pLabels[fillIndex].frame.szLabelText , pCurrentLabel->szLabelText );
			
			pCurrentLabel = pCurrentLabel->pNextLabel;	
		
			fillIndex++;
			
		} while(pCurrentLabel);
	}
	//---------------- Filling Traces ------------------------// 
	sizeOfEmptyTrace = sizeof(tsTraceFrame);
	calcTracesSize = 0;
	
	for ( fillIndex = 0 ; fillIndex < numberOfTraces ; fillIndex++ )
	{
		sizeOfFullBuffer = ( pData->TraceList[fillIndex].buffer_size * sizeof(double) ) + sizeOfEmptyTrace; 
		
		calcTracesSize += sizeOfFullBuffer;
		
		pTraces[fillIndex].frame.nextIndex = 0;
		pTraces[fillIndex].frame.blockSize = sizeOfFullBuffer;
		pTraces[fillIndex].frame.dataItemsSize = pData->TraceList[fillIndex].buffer_size;
		pTraces[fillIndex].frame.dataStartIndex = pData->TraceList[fillIndex].startTraceFromIndex;
		pTraces[fillIndex].frame.numberOfPoints = pData->TraceList[fillIndex].numberOfPoints; 
		pTraces[fillIndex].frame.dataTraceColor = pData->TraceList[fillIndex].trace_color;   
		pTraces[fillIndex].frame.startX = pData->TraceList[fillIndex].start_x;
		strcpy( pTraces[fillIndex].frame.name , pData->TraceList[fillIndex].szTraceName );
	}
	
	finalBufferSize = ( numberOfLabels * sizeof(tsLabelFrame) ) + calcTracesSize + sizeof(tsMainFrame);

	if ( pBufferCount )
		*pBufferCount = finalBufferSize;
	
	CALLOC_ERR( *pTransferBuffer , finalBufferSize , 1 ); 
	
	//--------------- Filling Main Frame -------------------------//
	tMainFrame.frame.numberOfTraces = numberOfTraces;
	tMainFrame.frame.numberOfLabels = numberOfLabels;
	tMainFrame.frame.numberOfPoints = pData->numberOfPoints;
	tMainFrame.frame.startX = pData->start_x;
	tMainFrame.frame.stopX = pData->stop_x;
	tMainFrame.frame.maxY = pData->y_axis_max;
	tMainFrame.frame.minY = pData->y_axis_min;
	strcpy( tMainFrame.frame.nameY , pData->szY_AxisName );
	strcpy( tMainFrame.frame.nameX , pData->szX_AxisName );
	
	pDynamicPosition = *pTransferBuffer; 
	
	memcpy( pDynamicPosition , tMainFrame.pBuffer , sizeof(tsMainFrame)); 
	
	pDynamicPosition += sizeof(tsMainFrame);
	
	//------------------------- Copy Traces --------------------------------//
	for ( fillIndex = 0 ; fillIndex < numberOfTraces ; fillIndex++ ) 
	{
		pTraces[fillIndex].frame.nextIndex = ( pDynamicPosition - *pTransferBuffer ) + pTraces[fillIndex].frame.blockSize;  
		
		memcpy( pDynamicPosition , pTraces[fillIndex].pBuffer , sizeof(tsTraceFrame) );
		
		pDynamicPosition += sizeof(tsTraceFrame);
		
		FREE_CALLOC_COPY_ERR( convertBuffer.plfBuffer , pData->TraceList[fillIndex].buffer_size , sizeof(double) , pData->TraceList[fillIndex].Trace , pData->TraceList[fillIndex].buffer_size * sizeof(double) );
		
		memcpy( pDynamicPosition , convertBuffer.pcBuffer , pData->TraceList[fillIndex].buffer_size * sizeof(double) ); 
		
		pDynamicPosition += pData->TraceList[fillIndex].buffer_size * sizeof(double);
	}
	
	for ( fillIndex = 0 ; fillIndex < numberOfLabels ; fillIndex++ ) 
	{
		memcpy( pDynamicPosition , pLabels[fillIndex].pBuffer , sizeof(tsLabelFrame) ); 
		
		pDynamicPosition += sizeof(tsLabelFrame);
	}
		
Error:

	FREE(pLabels); 
	
	FREE(convertBuffer.plfBuffer);
	
	FREE(pTraces);
	
	return StdError;
}

STD_ERROR	DLLEXPORT	GRAPH_ExtractBuffer( char *szUIRfilename , int panel_const , int control_const , void **pItemData , char *pTransferBuffer , int iBufferCount , int bDisplayGraph , int *piGraphPanelHandle )
{
	STD_ERROR				StdError								=	{0};

	int					numberOfLabels					=	0,
						numberOfTraces					=	0;
	
	int					fillIndex						=	0; 
	
	tsTraceFrame		tTraces;
	
	tsLabelFrame		tLabels;
	
	tsMainFrame			tMainFrame;
	
	char				*pDynamicPosition				=	NULL;
	
	tuConvertBuffer		convertBuffer					=	{NULL}; 
	
	memset( &tMainFrame , 0 , sizeof(tsMainFrame)); 
	memset( &tLabels , 0 , sizeof(tsLabelFrame)); 
	memset( &tTraces , 0 , sizeof(tsTraceFrame)); 
	
	IF ( (pTransferBuffer == NULL) , "Pointer passed NULL");  
	
	memcpy( tMainFrame.pBuffer , pTransferBuffer , sizeof(tsMainFrame) );
	
	GRAPH_CreateItem( szUIRfilename , panel_const , control_const , pItemData , tMainFrame.frame.numberOfPoints , tMainFrame.frame.startX , tMainFrame.frame.stopX , tMainFrame.frame.maxY , tMainFrame.frame.minY , tMainFrame.frame.nameX , tMainFrame.frame.nameY , bDisplayGraph , piGraphPanelHandle );
	
	numberOfLabels = tMainFrame.frame.numberOfLabels;
	numberOfTraces = tMainFrame.frame.numberOfTraces;
	
	pDynamicPosition = pTransferBuffer + sizeof(tsMainFrame);
	
	//------------------------- Copy Traces --------------------------------//
	for ( fillIndex = 0 ; fillIndex < numberOfTraces ; fillIndex++ ) 
	{
		memcpy( tTraces.pBuffer , pDynamicPosition , sizeof(tsTraceFrame) );
		
		pDynamicPosition += sizeof(tsTraceFrame);
		
		FREE_CALLOC_ERR( convertBuffer.pcBuffer , tTraces.frame.dataItemsSize * sizeof(double) , sizeof(char) );
		
		memcpy( convertBuffer.pcBuffer , pDynamicPosition , tTraces.frame.dataItemsSize * sizeof(double) ); 
			
		pDynamicPosition += tTraces.frame.dataItemsSize * sizeof(double);
		
		GRAPH_AddTrace( *pItemData , convertBuffer.plfBuffer , tTraces.frame.dataItemsSize , tTraces.frame.dataStartIndex , tTraces.frame.numberOfPoints ,  tTraces.frame.startX , tTraces.frame.name , tTraces.frame.dataTraceColor , tTraces.frame.thickness , tTraces.frame.style );
	}
	
	for ( fillIndex = 0 ; fillIndex < numberOfLabels ; fillIndex++ ) 
	{
		memcpy( tLabels.pBuffer , pDynamicPosition , sizeof(tsLabelFrame) ); 
	
		pDynamicPosition += sizeof(tsLabelFrame);
	
		GRAPH_AddLabel( *pItemData , tLabels.frame.X_Position , tLabels.frame.Y_Position , tLabels.frame.szLabelText  , tLabels.frame.color , tLabels.frame.label_type );
	}
	
Error:
	
	FREE( convertBuffer.pcBuffer  );
	
	return StdError;
}


//==================== Extra Data ===================================//

int	DLLEXPORT	GRAPH_Extra_Set_SN_Field( void *pItemData , char *pszSerialNumber )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData			*pData				=	NULL;
		
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	IF (( pszSerialNumber == NULL ) , "NULL Pointer.");    	
	
	pData = pItemData;
	
	SetCtrlVal( pData->panel , GRAPH_BUIL_SN , pszSerialNumber );
	SetCtrlAttribute( pData->panel , GRAPH_BUIL_SN , ATTR_VISIBLE , 1 );
	
Error:	
	
	return 0;
}

int	DLLEXPORT	GRAPH_Extra_Set_PN_Field( void *pItemData , char *pszPartNumber )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData			*pData				=	NULL;
		
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	IF (( pszPartNumber == NULL ) , "NULL Pointer.");    	
	
	pData = pItemData;
	
	SetCtrlVal( pData->panel , GRAPH_BUIL_PN , pszPartNumber );
	SetCtrlAttribute( pData->panel , GRAPH_BUIL_PN , ATTR_VISIBLE , 1 );
	
Error:	
	
	return 0;
}

int	DLLEXPORT	GRAPH_Extra_Set_Date_Field( void *pItemData , char *pszDate )
{
	STD_ERROR				StdError			=	{0};
	
	tsPlotGraphData			*pData				=	NULL;
		
	IF (( pItemData == NULL ) , "NULL Pointer.");    
	IF (( pszDate == NULL ) , "NULL Pointer.");    	
	
	pData = pItemData;
	
	SetCtrlVal( pData->panel , GRAPH_BUIL_DATE , pszDate );
	SetCtrlAttribute( pData->panel , GRAPH_BUIL_DATE , ATTR_VISIBLE , 1 );
	
Error:	
	
	return 0;
}
