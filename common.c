#include "Windows.h"
#include <utility.h>
#include <userint.h>
#include <ansi_c.h>
#include <common.h>
#include "GlobalDefines.h"
#include "toolbox.h"

//==============================================================================
//==============================================================================
// DLL main entry-point functions

#ifndef _CVI_EXE_
int __stdcall DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
          
			if (InitCVIRTE (hinstDLL, 0, 0) == 0)
                return 0;     /* out of memory */

            break;
			
        case DLL_PROCESS_DETACH:

            break;
    }
    
    return 1;
}

int __stdcall DllEntryPoint (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    /* Included for compatibility with Borland */

    return DllMain (hinstDLL, fdwReason, lpvReserved);
}
#endif

TSTE_TEST ( STD_EMPTY_TEST ) { return 0; }

TSTE_TEST ( STD_DELAY_TEST ) 
{
	STD_ERROR						StdError										=	{0};   
	
	int								iTestError										=	0;
	
	double							lfDB_Delay										=	0.0;
	
	LOG(CLB_LINE_HEADER_TEST, "Delay.");

	lfDB_Delay = GetVarDouble( clb, VARTYPE_TEST , "Delay" );

	WAIT("",lfDB_Delay);  	
	
CATCH

	UPDATE_ERROR(StdError);
	
	if ( StdError.pszErrorDescription )
	{
		LOG_END(CLB_LINE_WARNING, (char*)StdError.pszErrorDescription );
	}
	
	iTestError = -1;
	
FINALLY	

	LOG_END(CLB_LINE_NORMAL, "Finalizing Test." );
	
	return iTestError; 
}

//==============================================================================
//==============================================================================

int	GetVarInt( sClb* clb, int vartype, char *name , ... )
{
	va_list				arguments				=	{0};
	
	int					iValue					=	0;
	
	va_start( arguments , name );
	
	iValue = clb->GetVarInt( clb->handle , vartype, name , arguments );
	
	va_end( arguments );
	
	return iValue;
}

int GetVarIntArray( sClb* clb, int vartype, char *name,int** result , ... )
{
	va_list				arguments				=	{0};
	
	int					iValue					=	0;
	
	va_start( arguments , result );
	
	iValue = clb->GetVarIntArray( clb->handle, vartype, name, result , arguments );

	va_end( arguments );
	
	return iValue;
	
}

double GetVarDouble( sClb* clb, int vartype, char *name , ... )
{
	va_list				arguments				=	{0};
	
	double				lfValue					=	0;
	
	va_start( arguments , name );
	
	lfValue = clb->GetVarDouble( clb->handle, vartype, name , arguments );
	
	va_end( arguments );
	
	return lfValue;
	
}

int GetVarDoubleArray( sClb* clb, int vartype, char *name,double** result , ... )
{
	va_list				arguments				=	{0};
	
	int					iValue					=	0;
	
	va_start( arguments , result );
	
	iValue = clb->GetVarDoubleArray( clb->handle, vartype, name, result , arguments );
	
	va_end( arguments );
	
	return iValue;
	
}

char* GetVarString( sClb* clb, int vartype, char *name , ... )
{
	va_list				arguments				=	{0};
	
	char				*pValue					=	NULL;
	
	va_start( arguments , name );
	
	pValue = clb->GetVarString( clb->handle, vartype, name , arguments );
	
	va_end( arguments );
	
	return pValue;
}

char** GetVarStringArray( sClb* clb, int vartype, char *name , int *pNumberOfItems , ... )
{
	va_list				arguments				=	{0};
	
	char				**pValue				=	NULL;
	
	va_start( arguments , pNumberOfItems );
	
	pValue = clb->GetVarStringArray( clb->handle , vartype, name , pNumberOfItems , arguments );
	
	va_end( arguments );
	
	return pValue;
}

int	SetVarString( sClb* clb, int vartype, char *name , char *string  , ... )
{
	va_list				arguments				=	{0};

	int					iValue					=	0;
	
	va_start( arguments , string );
	
	iValue = clb->SetVarString( clb->handle, vartype, name , string  , arguments );
	
	va_end( arguments );
	
	return iValue;
}

int	SetVarStringArray( sClb* clb, int vartype, char *name , char **string  , int iNumberOfItems , ... )
{
	va_list				arguments				=	{0};

	int					iValue					=	0;
	
	va_start( arguments , iNumberOfItems );
	
	iValue = clb->SetVarStringArray( clb->handle, vartype, name , string  , iNumberOfItems , arguments );
	
	va_end( arguments );
	
	return iValue;
}

int	SetVarInt( sClb* clb, int vartype, char *name, int value , ... )
{
	va_list				arguments				=	{0};
	
	int					iValue					=	0;
	
	va_start( arguments , value );
	
	iValue = clb->SetVarInt( clb->handle , vartype, name, value , arguments );
	
	va_end( arguments );
	
	return iValue;
}

int	SetVarIntArray( sClb* clb, int vartype, char *name, int *pArrayValues , int Count  , ... )
{
	va_list				arguments				=	{0};
	
	int					iValue					=	0;
	
	va_start( arguments , Count );
	
	iValue = clb->SetVarIntArray( clb->handle, vartype, name, pArrayValues , Count  , arguments );
	
	va_end( arguments );
	
	return iValue;
}

int SetVarDouble(  sClb* clb , int vartype, char *name , double value  , ... )
{
	va_list				arguments				=	{0};
	
	int					iValue					=	0;
	
	va_start( arguments , value );
	
	iValue = clb->SetVarDouble( clb->handle , vartype, name , value , arguments );
	
	va_end( arguments );
	
	return iValue;
}

int SetVarDoubleArray( sClb* clb, int vartype, char *name, double *pArrayValues , int Count  , ... ) 
{
	va_list				arguments				=	{0};
	
	int					iValue					=	0;
	
	va_start( arguments , Count );
	
	iValue = clb->SetVarDoubleArray( clb->handle , vartype, name, pArrayValues , Count , arguments );
	
	va_end( arguments );
	
	return iValue;
}

int	SetVarCalibration( sClb* clb, int vartype, int iRange , int bCleanBefore , char *name , double *frequency , double *factor , int iNumOfPoints , ... )
{
	va_list				arguments				=	{0};
	
	int					iValue					=	0;
	
	va_start( arguments , iNumOfPoints );
	
	iValue = clb->SetVarCalibration( clb->handle , vartype, iRange , bCleanBefore , name , frequency , factor , iNumOfPoints , arguments );
	
	va_end( arguments );
	
	return iValue;
}

int	GetVarCalibration( sClb* clb, int vartype, int iRange , char *name , double **frequency , double **factor , int *piNumOfPoints , double *plfCalibrationDate , ... )
{
	va_list				arguments				=	{0};
	
	int					iValue					=	0;
	
	va_start( arguments , plfCalibrationDate );
	
	iValue = clb->GetVarCalibration( clb->handle , vartype, iRange , name , frequency , factor , piNumOfPoints , plfCalibrationDate , arguments );
	
	va_end( arguments );
	
	return iValue;
}

int	SetVarCurrentCalibration( sClb* clb, int iRange , int bCleanBefore , double *frequency , double *factor , int iNumOfPoints , ... )
{
	va_list				arguments				=	{0};
	
	int					iValue					=	0;
	
	va_start( arguments , iNumOfPoints );
	
	iValue = clb->SetVarCurrentCalibration( clb->handle, iRange , bCleanBefore , frequency , factor , iNumOfPoints , arguments );
	
	va_end( arguments );
	
	return iValue;
}

int	GetVarCurrentCalibration( sClb* clb, int iRange , double **frequency , double **factor , int *piNumOfPoints , double *plfCalibrationDate  , ... )
{
	va_list				arguments				=	{0};
	
	int					iValue					=	0;
	
	va_start( arguments , plfCalibrationDate );
	
	iValue = clb->GetVarCurrentCalibration( clb->handle , iRange , frequency , factor , piNumOfPoints , plfCalibrationDate  , arguments );
	
	va_end( arguments );
	
	return iValue;
}

int	GetVarCalibrationByName( sClb* clb, char *pszName , int iRange , double **frequency , double **factor , int *piNumOfPoints , double *plfCalibrationDate  , ... )
{
	va_list				arguments				=	{0};
	
	int					iValue					=	0;
	
	va_start( arguments , plfCalibrationDate );
	
	iValue = clb->GetVarCalibrationByName( clb->handle , pszName , iRange , frequency , factor , piNumOfPoints , plfCalibrationDate  , arguments );
	
	va_end( arguments );
	
	return iValue;
}


