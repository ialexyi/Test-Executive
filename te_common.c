#include <ansi_c.h>
#include "var.h"
#include "dblayer.h"
#include <userint.h>
#include <utility.h>
#include "clb.h"
#include "GlobalDefines.h"
#include "TE_GlobalDefines.h"
#include "toolbox.h"
#include "GUI_UI.h"
#include "GUI.h"
#include "defines.h"

int	_GetVarInt( int handle, int vartype, char *name , va_list arguments )
{
	int								reply												=	0;
	int								result												=	0;
	char							tmp[1024]											=	{0};
	
	STD_ERROR						StdError											=	{0};
	
	tsSlotStore						*ptCurrentSlote										=	NULL;
	
	tsMainStore						*pMainStore											=	NULL;
		
	char							szResponseBuffer[128]								=	{0};
	
	int								*piGetIntValue										=	0; 

	int								iSpecGroup											=	0;
	
	int								hMainStoreHandle									=	0;
	
	int								iEquipmentHandle									=	0;
	
	unsigned long long				ullLinkedID											=	0;
	
	int								iSelectedTestIndex									=	0,
									iEquipmentUseIndex									=	0; 
										
	char							*pAlias												=	NULL;
	int								iNumber												=	0;
	
	IF (( handle == 0 ) , "Handle is NULL");
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote )); 
	iSpecGroup = ptCurrentSlote->iSpecGroup;
	hMainStoreHandle = ptCurrentSlote->hMainStoreHandle;
	iSelectedTestIndex = ptCurrentSlote->iCurrentTestIndex;  
	CHK_CMT(CmtReleaseTSVPtr ( handle ));
	
	if (( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) 
	{
		iEquipmentHandle = va_arg( arguments , int );
			
		if ( iEquipmentHandle == 0 )
		{
			RETURN;
		}
		
		if ( CmtGetTSVPtr ( hMainStoreHandle , &pMainStore ) == 0 )
		{	   
			for ( iEquipmentUseIndex = 0 ; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
				if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle == iEquipmentHandle )
				{
					if ( vartype == VARTYPE_EQUIPMENT_USE )
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;	
					else
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].equipment_id;	
					
					pAlias = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias;
					iNumber = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].nr;
					
					break;
				}
			
			CmtReleaseTSVPtr ( hMainStoreHandle );	
		}
	}	

	if (( iSpecGroup == CALIBRATION_SPEC_GROUP ) && ( vartype != VARTYPE_EQUIPMENT_USE ))
		vartype += VARTYPE_CONFIG_OFFSET;
		
	reply = VarGetInt( hMainStoreHandle , vartype , ullLinkedID , name , 0 );
	if (!reply || reply!=1)
	{
		if ((( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) && ( pAlias ))
		{
			sprintf(tmp,"Equipment's (\"%s %d\")\nVariable [%s] does not exists\nDo you want to create?", pAlias , iNumber , name);  
		}
		else
			sprintf(tmp,"Variable [%s] does not exists\nDo you want to create?",name);  
		
		if ( InputMessage("Variable Error.", tmp , szResponseBuffer ) == 0 )
		{
			result = atoi(szResponseBuffer);
			
			VarSetInt( hMainStoreHandle , vartype , ullLinkedID , name,1,&result); 
		}
		else
		{
			sprintf(tmp,"Error reading variable: %s",name);
			
			GUI_Line_To_Window ( handle  , CLB_LINE_WARNING,tmp);
		
			result = 0;
			
			RETURN;
		}
	}
	
	VarGetInt( hMainStoreHandle , vartype , ullLinkedID , name,&piGetIntValue);
	
	if ( piGetIntValue )
	{
		result = *piGetIntValue;
		FREE(piGetIntValue);
	}
	
Error:
	
	return result;
}

//make sure you FREE the result array after use!!!!!!
int _GetVarIntArray( int handle, int vartype, char *name,int** result , va_list arguments )
{
	char							tmp[1024]											=	{0};
	
	STD_ERROR						StdError											=	{0};
	
	tsSlotStore						*ptCurrentSlote										=	NULL;
	
	tsMainStore						*pMainStore											=	NULL;
		
	char							szResponseBuffer[1024]								=	{0},
									*pTemp												=	NULL,
									*pNext												=	NULL;
										
	int								*pArray												=	NULL;
	
	int								count												=	0,
									index												=	0;

	int								iSpecGroup											=	0;
	
	int								hMainStoreHandle									=	0;

	int								iEquipmentHandle									=	0;
	
	unsigned long long				ullLinkedID											=	0;
	
	int								iSelectedTestIndex									=	0,
									iEquipmentUseIndex									=	0; 
	
	char							*pAlias												=	NULL;
	int								iNumber												=	0;
	
	IF (( handle == 0 ) , "Handle is NULL");
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote )); 
	iSpecGroup = ptCurrentSlote->iSpecGroup;
	hMainStoreHandle = ptCurrentSlote->hMainStoreHandle;
	iSelectedTestIndex = ptCurrentSlote->iCurrentTestIndex;  
	CHK_CMT(CmtReleaseTSVPtr ( handle ));
	
	if (( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) 
	{
		iEquipmentHandle = va_arg( arguments , int );
		
		if ( iEquipmentHandle == 0 )
		{
			RETURN;
		}
		
		if ( CmtGetTSVPtr ( hMainStoreHandle , &pMainStore ) == 0 )
		{	   
			for ( iEquipmentUseIndex = 0 ; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
				if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle == iEquipmentHandle )
				{
					if ( vartype == VARTYPE_EQUIPMENT_USE )
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;	
					else
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].equipment_id;	
					
					pAlias = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias;
					iNumber = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].nr;
					
					break;
				}
			
			CmtReleaseTSVPtr ( hMainStoreHandle );	
		}
	}
	
	if (( iSpecGroup == CALIBRATION_SPEC_GROUP ) && ( vartype != VARTYPE_EQUIPMENT_USE ))
		vartype += VARTYPE_CONFIG_OFFSET;
	
	count = VarGetInt( hMainStoreHandle ,  vartype , ullLinkedID ,name,0);
	
	if (!count)
	{
		if ((( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) && ( pAlias ))
		{
			sprintf(tmp,"Equipment's (\"%s %d\")\nVariable [%s] does not exists\nDo you want to create?", pAlias , iNumber , name);  
		}
		else
			sprintf(tmp,"Variable [%s] does not exists\nDo you want to create?",name);  
		
		if ( InputMessage("Variable Error.", tmp , szResponseBuffer ) == 0 )
		{
			pNext = szResponseBuffer;
			
			while(pNext)
			{
				count++;
				
				pTemp = strchr( pNext , ',' );
			
				pNext = pTemp;
				
				if ( pNext )
					pNext++;
			}
				
			CALLOC_ERR( pArray , count , sizeof(int));
			
			pNext = szResponseBuffer; 
			
			for ( index=0 ; index < count; index++ )
				if ( pNext )
				{
					pTemp = strchr( pNext , ',' ); 
				
					if ( pTemp )
						*pTemp = 0;
					
					pArray[index] = atoi(pNext);
					
					pNext = pTemp;
						
					if ( pNext )
						pNext++;
				}
					
			VarSetInt( hMainStoreHandle ,  vartype , ullLinkedID ,name,count,pArray); 
		}
		else
		{
			sprintf(tmp,"Error reading variable: %s",name);
			GUI_Line_To_Window ( handle  , CLB_LINE_WARNING,tmp);
			
			count = 0; 
			
			RETURN;
		}
	}
	
	//CALLOC_ERR( *result , count , sizeof(int));
	VarGetInt( hMainStoreHandle ,  vartype , ullLinkedID ,name,result);

Error:
	
	FREE(pArray);
	
	return count;
}

double _GetVarDouble( int handle, int vartype, char *name , va_list arguments )
{
	int								reply												=	0;
	double							result												=	0.0;
	char							tmp[1024]											=	{0};
	
	STD_ERROR						StdError											=	{0};
	
	tsSlotStore						*ptCurrentSlote										=	NULL;
	
	tsMainStore						*pMainStore											=	NULL;

	char							szResponseBuffer[128]								=	{0};
	
	double							*piGetDoubleValue									=	NULL;

	int								iSpecGroup											=	0;
	
	int								hMainStoreHandle									=	0;
	
	int								iEquipmentHandle									=	0;
	
	unsigned long long				ullLinkedID											=	0;
	
	int								iSelectedTestIndex									=	0,
									iEquipmentUseIndex									=	0; 
	
	char							*pAlias												=	NULL;
	int								iNumber												=	0;
	
	IF (( handle == 0 ) , "Handle is NULL");
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote )); 
	iSpecGroup = ptCurrentSlote->iSpecGroup;
	hMainStoreHandle = ptCurrentSlote->hMainStoreHandle;
	iSelectedTestIndex = ptCurrentSlote->iCurrentTestIndex;  
	CHK_CMT(CmtReleaseTSVPtr ( handle ));
	
	if (( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) 
	{
		iEquipmentHandle = va_arg( arguments , int );
		
		if ( iEquipmentHandle == 0 )
		{
			RETURN;
		}
		
		if ( CmtGetTSVPtr ( hMainStoreHandle , &pMainStore ) == 0 )
		{	   
			for ( iEquipmentUseIndex = 0 ; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
				if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle == iEquipmentHandle )
				{
					if ( vartype == VARTYPE_EQUIPMENT_USE )
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;	
					else
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].equipment_id;	
					
					pAlias = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias;
					iNumber = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].nr;
					
					break;
				}
			
			CmtReleaseTSVPtr ( hMainStoreHandle );	
		}
	}
	
	if (( iSpecGroup == CALIBRATION_SPEC_GROUP ) && ( vartype != VARTYPE_EQUIPMENT_USE ))
		vartype += VARTYPE_CONFIG_OFFSET;
	
	reply = VarGetDouble( hMainStoreHandle ,  vartype , ullLinkedID ,name,0);
	if (!reply || reply!=1)
	{
		if ((( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) && ( pAlias ))
		{
			sprintf(tmp,"Equipment's (\"%s %d\")\nVariable [%s] does not exists\nDo you want to create?", pAlias , iNumber , name);  
		}
		else
			sprintf(tmp,"Variable [%s] does not exists\nDo you want to create?",name);  
		
		if ( InputMessage("Variable Error.", tmp , szResponseBuffer ) == 0 )
		{
			//if ( strchr( szResponseBuffer , 'e' ) || strchr( szResponseBuffer , 'E' ))
			//	sscanf( szResponseBuffer , "%e" , &result );
			//else
				result = atof(szResponseBuffer);
			
			VarSetDouble( hMainStoreHandle ,  vartype , ullLinkedID ,name,1,&result); 
		}
		else
		{
			sprintf(tmp,"Error reading variable: %s",name);
			GUI_Line_To_Window ( handle  , CLB_LINE_WARNING,tmp);
			
			result = 0; 
			
			RETURN;
		}
	}
	
	VarGetDouble( hMainStoreHandle ,  vartype , ullLinkedID ,name,&piGetDoubleValue);

	if ( piGetDoubleValue )
	{
		result = *piGetDoubleValue;
		FREE(piGetDoubleValue);
	}
	
Error:
	
	return result;
	
}

//make sure you FREE the result array after use!!!!!!
int _GetVarDoubleArray( int handle, int vartype, char *name,double** result , va_list arguments )
{
	char							tmp[1024]											=	{0};
	
	STD_ERROR						StdError											=	{0};
	
	tsSlotStore						*ptCurrentSlote										=	NULL;
	
	tsMainStore						*pMainStore											=	NULL;
		
	char							szResponseBuffer[1024]								=	{0},
									*pTemp												=	NULL,
									*pNext												=	NULL;
										
	double							*pArray												=	NULL;
	
	int								count												=	0,
									index												=	0;

	int								iSpecGroup											=	0;
	
	int								hMainStoreHandle									=	0;
	
	int								iEquipmentHandle									=	0;
	
	unsigned long long				ullLinkedID											=	0;
	
	int								iSelectedTestIndex									=	0,
									iEquipmentUseIndex									=	0; 
	
	char							*pAlias												=	NULL;
	int								iNumber												=	0;
	
	IF (( handle == 0 ) , "Handle is NULL");
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote )); 
	iSpecGroup = ptCurrentSlote->iSpecGroup;
	hMainStoreHandle = ptCurrentSlote->hMainStoreHandle;
	iSelectedTestIndex = ptCurrentSlote->iCurrentTestIndex;  
	CHK_CMT(CmtReleaseTSVPtr ( handle ));
	
	if (( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) 
	{
		iEquipmentHandle = va_arg( arguments , int );
		
		if ( iEquipmentHandle == 0 )
		{
			RETURN;
		}
		
		if ( CmtGetTSVPtr ( hMainStoreHandle , &pMainStore ) == 0 )
		{	   
			for ( iEquipmentUseIndex = 0 ; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
				if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle == iEquipmentHandle )
				{
					if ( vartype == VARTYPE_EQUIPMENT_USE )
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;	
					else
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].equipment_id;	
					
					pAlias = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias;
					iNumber = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].nr;
					
					break;
				}
			
			CmtReleaseTSVPtr ( hMainStoreHandle );	
		}
	}
	
	if (( iSpecGroup == CALIBRATION_SPEC_GROUP ) && ( vartype != VARTYPE_EQUIPMENT_USE ))
		vartype += VARTYPE_CONFIG_OFFSET;
	
	count = VarGetDouble( hMainStoreHandle ,  vartype , ullLinkedID ,name,0);
	
	if (!count)
	{
		if (( vartype == VARTYPE_MEASURE_STORE ) || ( vartype == ( VARTYPE_CONFIG_OFFSET + VARTYPE_MEASURE_STORE)))
		{
			RETURN;	
		}
		
		if ((( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) ||
				(( vartype == ( VARTYPE_CONFIG_OFFSET + VARTYPE_EQUIPMENT )) || ( vartype == ( VARTYPE_CONFIG_OFFSET + VARTYPE_EQUIPMENT_USE ))))
		{
			if ( pAlias )
				sprintf(tmp,"Equipment's (\"%s %d\")\nVariable [%s] does not exists\nDo you want to create?", pAlias , iNumber , name);  
			else
				sprintf(tmp,"Equipment's\nVariable [%s] does not exists\nDo you want to create?", name);  
		}
		else
			sprintf(tmp,"Variable [%s] does not exists\nDo you want to create?",name);  
		
		if ( InputMessage("Variable Error.", tmp , szResponseBuffer ) == 0 )
		{
			pNext = szResponseBuffer;
			
			while(pNext)
			{
				count++;
				
				pTemp = strchr( pNext , ',' );
			
				pNext = pTemp;
				
				if ( pNext )
					pNext++;
			}
				
			CALLOC_ERR( pArray , count+1 , sizeof(double));
			
			pNext = szResponseBuffer; 
			
			for ( index=0 ; index < count; index++ )
				if ( pNext )
				{
					pTemp = strchr( pNext , ',' ); 
				
					if ( pTemp )
						*pTemp = 0;
					
					//if ( strchr( pNext , 'E' ) || strchr( pNext , 'e' ))
						//sscanf( pNext , "%e" , &(pArray[index]));
					//else
						//sscanf( pNext , "%lf" , &(pArray[index]));
					
					pArray[index] = atof(pNext);
					
					pNext = pTemp;
						
					if ( pNext )
						pNext++;
				}
					
			VarSetDouble( hMainStoreHandle ,  vartype , ullLinkedID ,name,count,pArray); 
		}
		else
		{
			sprintf(tmp,"Error reading variable: %s",name);
			GUI_Line_To_Window ( handle  , CLB_LINE_WARNING,tmp);
			
			count = 0; 
			
			RETURN;
		}
	}
	
	//CALLOC_ERR( *result , count , sizeof(double));
	VarGetDouble( hMainStoreHandle ,  vartype , ullLinkedID ,name,result);
	
Error:
	
	return count;
}

//Make sure you FREE the string after use!!!!!
char* _GetVarString( int handle, int vartype, char *name , va_list arguments )
{
	int								reply												=	0;
	char							*result												=	NULL;
	char 							tmp[1024]											=	{0};
	
	STD_ERROR						StdError											=	{0};
	
	tsSlotStore						*ptCurrentSlote										=	NULL;
	
	tsMainStore						*pMainStore											=	NULL;

	char							szResponseBuffer[1024]								=	{0};

	int								iSpecGroup											=	0;
	
	int								hMainStoreHandle									=	0;
	
	int								iEquipmentHandle									=	0;
	
	unsigned long long				ullLinkedID											=	0;
	
	int								iSelectedTestIndex									=	0,
									iEquipmentUseIndex									=	0; 
	
	char							*pAlias												=	NULL;
	int								iNumber												=	0;
	
	IF (( handle == 0 ) , "Handle is NULL");
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote )); 
	iSpecGroup = ptCurrentSlote->iSpecGroup;
	hMainStoreHandle = ptCurrentSlote->hMainStoreHandle;
	iSelectedTestIndex = ptCurrentSlote->iCurrentTestIndex;   
	CHK_CMT(CmtReleaseTSVPtr ( handle ));
	
	if (( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) 
	{
		iEquipmentHandle = va_arg( arguments , int );
		
		if ( iEquipmentHandle == 0 )
		{
			RETURN;
		}
		
		if ( CmtGetTSVPtr ( hMainStoreHandle , &pMainStore ) == 0 )
		{	   
			for ( iEquipmentUseIndex = 0 ; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
				if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle == iEquipmentHandle )
				{
					if ( vartype == VARTYPE_EQUIPMENT_USE )
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;	
					else
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].equipment_id;	
					
					pAlias = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias;
					iNumber = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].nr;
					
					break;
				}
			
			CmtReleaseTSVPtr ( hMainStoreHandle );	
		}
	}
	
	if (( iSpecGroup == CALIBRATION_SPEC_GROUP ) && ( vartype != VARTYPE_EQUIPMENT_USE ))
		vartype += VARTYPE_CONFIG_OFFSET;
	
	reply = VarGetString( hMainStoreHandle ,  vartype , ullLinkedID ,name,0);
	
	if ( reply <= 0 )
	{
		if ((( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) && ( pAlias ))
		{
			sprintf(tmp,"Equipment's (\"%s %d\")\nVariable [%s] does not exists\nDo you want to create?", pAlias , iNumber , name);  
		}
		else
			sprintf(tmp,"Variable [%s] does not exists\nDo you want to create?",name);  
		
		if ( InputMessage("Variable Error.", tmp , szResponseBuffer ) == 0 )
		{
			VarSetString( hMainStoreHandle ,  vartype , ullLinkedID ,name,szResponseBuffer); 
			reply = strlen(szResponseBuffer)+1;
		}
		else
		{
			sprintf(tmp,"Error reading variable: %s",name);
			GUI_Line_To_Window ( handle  , CLB_LINE_WARNING,tmp);
			
			result = 0; 
			
			RETURN;
		}
	}
	
	if ( reply >= 0 )
		VarGetString( hMainStoreHandle ,  vartype , ullLinkedID ,name,&result);
	
Error:
	
	return result;
}



//Make sure you FREE the string after use!!!!!
char** _GetVarStringArray( int handle, int vartype, char *name , int *pNumberOfItems , va_list arguments )
{
	int								reply												=	0;
	char							*result												=	NULL;
	char 							tmp[1024]											=	{0};
	
	STD_ERROR						StdError											=	{0};
	
	tsSlotStore						*ptCurrentSlote										=	NULL;
	
	tsMainStore						*pMainStore											=	NULL;

	char							szResponseBuffer[1024]								=	{0},
									*pTemp												=	NULL,
									*pNext												=	NULL;

	int								count												=	0,
									index												=	0,
									characters											=	0;
	
	char							**pArray											=	NULL;
	
	int								iSpecGroup											=	0;
	
	int								hMainStoreHandle									=	0;
	
	int								iEquipmentHandle									=	0;
	
	unsigned long long				ullLinkedID											=	0;
	
	int								iSelectedTestIndex									=	0,
									iEquipmentUseIndex									=	0; 
	
	char							*pAlias												=	NULL;
	int								iNumber												=	0;
	
	IF (( handle == 0 ) , "Handle is NULL");
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote )); 
	iSpecGroup = ptCurrentSlote->iSpecGroup;
	hMainStoreHandle = ptCurrentSlote->hMainStoreHandle;
	iSelectedTestIndex = ptCurrentSlote->iCurrentTestIndex;  
	CHK_CMT(CmtReleaseTSVPtr ( handle ));
	
	if (( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) 
	{
		iEquipmentHandle = va_arg( arguments , int );
		
		if ( iEquipmentHandle == 0 )
		{
			RETURN;
		}
		
		if ( CmtGetTSVPtr ( hMainStoreHandle , &pMainStore ) == 0 )
		{	   
			for ( iEquipmentUseIndex = 0 ; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
				if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle == iEquipmentHandle )
				{
					if ( vartype == VARTYPE_EQUIPMENT_USE )
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;	
					else
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].equipment_id;	
					
					pAlias = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias;
					iNumber = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].nr;
					
					break;
				}
			
			CmtReleaseTSVPtr ( hMainStoreHandle );	
		}
	}
	
	if (( iSpecGroup == CALIBRATION_SPEC_GROUP ) && ( vartype != VARTYPE_EQUIPMENT_USE ))
		vartype += VARTYPE_CONFIG_OFFSET;
	
	reply = VarGetStringArray( hMainStoreHandle ,  vartype , ullLinkedID ,name,0);
	
	if ( reply <= 0 )
	{
		if ((( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) && ( pAlias ))
		{
			sprintf(tmp,"Equipment's (\"%s %d\")\nVariable [%s] does not exists\nDo you want to create?", pAlias , iNumber , name);  
		}
		else
			sprintf(tmp,"Variable [%s] does not exists\nDo you want to create?",name);  
		
		if ( InputMessage("Variable Error.", tmp , szResponseBuffer ) == 0 )
		{
			pNext = szResponseBuffer;
			
			while(pNext)
			{
				count++;
				
				pTemp = strchr( pNext , ',' );
			
				pNext = pTemp;
				
				if ( pNext )
					pNext++;
			}
				
			CALLOC_ERR( pArray , count+1 , sizeof(char*));
			
			pNext = szResponseBuffer; 
			
			for ( index=0 ; index < count; index++ )
				if ( pNext )
				{
					pTemp = strchr( pNext , ',' ); 
				
					if ( pTemp )
						*pTemp = 0;
					
					pArray[index] = StrDupWithoutSurrWhiteSpace (pNext);
					
					pNext = pTemp;
						
					if ( pNext )
						pNext++;
				}
				
			for ( index=0 ; index < count; index++ )
				characters += sprintf(( szResponseBuffer + characters ) , "%s\0" , pArray[index] ) + 1;
				
			if ( characters )
				characters--;
			
			VarSetBuffer( hMainStoreHandle ,  vartype , ullLinkedID ,name,szResponseBuffer,characters); 
			reply = characters;
			characters = 0;
		}
		else
		{
			sprintf(tmp,"Error reading variable: %s",name);
			GUI_Line_To_Window ( handle  , CLB_LINE_WARNING,tmp);
			
			result = 0; 
			
			RETURN;
		}
	}
	
	if ( reply >= 0 )
	{
		reply = VarGetStringArray( hMainStoreHandle ,  vartype , ullLinkedID ,name, &pArray );
	}
	
Error:
	
	FREE(result);
	
	if ( pNumberOfItems )
		*pNumberOfItems = reply;
	
	return pArray;
}

int	_SetVarString( int handle, int vartype, char *name , char *string  , va_list arguments )
{
	int								reply												=	0;
	char							tmp[1024]											=	{0};
	
	STD_ERROR						StdError											=	{0};
	
	tsSlotStore						*ptCurrentSlote										=	NULL;
	
	tsMainStore						*pMainStore											=	NULL;

	int								iSpecGroup											=	0;
	
	int								hMainStoreHandle									=	0;
	
	int								iEquipmentHandle									=	0;
	
	unsigned long long				ullLinkedID											=	0;
	
	int								iSelectedTestIndex									=	0,
									iEquipmentUseIndex									=	0; 
	
	char							*pAlias												=	NULL;
	int								iNumber												=	0;
		
	IF (( handle == 0 ) , "Handle is NULL");
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote )); 
	iSpecGroup = ptCurrentSlote->iSpecGroup;
	hMainStoreHandle = ptCurrentSlote->hMainStoreHandle;
	iSelectedTestIndex = ptCurrentSlote->iCurrentTestIndex;  
	CHK_CMT(CmtReleaseTSVPtr ( handle ));
	
	if (( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) 
	{
		iEquipmentHandle = va_arg( arguments , int );
		
		if ( iEquipmentHandle == 0 )
		{
			RETURN;
		}
		
		if ( CmtGetTSVPtr ( hMainStoreHandle , &pMainStore ) == 0 )
		{	   
			for ( iEquipmentUseIndex = 0 ; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
				if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle == iEquipmentHandle )
				{
					if ( vartype == VARTYPE_EQUIPMENT_USE )
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;	
					else
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].equipment_id;	
				
					pAlias = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias;
					iNumber = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].nr;
					
					break;
				}	
			
			CmtReleaseTSVPtr ( hMainStoreHandle );	
		}
	}
	
	if (( iSpecGroup == CALIBRATION_SPEC_GROUP ) && ( vartype != VARTYPE_EQUIPMENT_USE ))
		vartype += VARTYPE_CONFIG_OFFSET;
	
	reply = VarSetString(  hMainStoreHandle ,  vartype , ullLinkedID ,  name, string);
	
	if (reply)
	{
		sprintf(tmp,"Error writing variable: %s",name);
		GUI_Line_To_Window ( handle  , CLB_LINE_WARNING,tmp);
		
		reply = 0; 
		
		RETURN;
	}
	
Error:
	
	return reply;
}

int	_SetVarStringArray( int handle, int vartype, char *name , char **string  , int iNumberOfItems , va_list arguments )
{
	int								reply												=	0;
	char							tmp[1024]											=	{0};
																						
	STD_ERROR						StdError											=	{0};
	
	tsSlotStore						*ptCurrentSlote										=	NULL;
	
	tsMainStore						*pMainStore											=	NULL;

	int								iSpecGroup											=	0;
	
	int								hMainStoreHandle									=	0;

	int								iEquipmentHandle									=	0;
	
	unsigned long long				ullLinkedID											=	0;
	
	int								iSelectedTestIndex									=	0,
									iEquipmentUseIndex									=	0; 
		
	char							*pAlias												=	NULL;
	int								iNumber												=	0;
	
	IF (( handle == 0 ) , "Handle is NULL");
	IF (( string == NULL )  , "NULL pointer of string");
	IF (( iNumberOfItems == 0 )  , "String array is empty");  
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote )); 
	iSpecGroup = ptCurrentSlote->iSpecGroup;
	hMainStoreHandle = ptCurrentSlote->hMainStoreHandle;
	iSelectedTestIndex = ptCurrentSlote->iCurrentTestIndex;  
	CHK_CMT(CmtReleaseTSVPtr ( handle ));
	
	if (( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) 
	{
		iEquipmentHandle = va_arg( arguments , int );
		
		if ( iEquipmentHandle == 0 )
		{
			RETURN;
		}
		
		if ( CmtGetTSVPtr ( hMainStoreHandle , &pMainStore ) == 0 )
		{	   
			for ( iEquipmentUseIndex = 0 ; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
				if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle == iEquipmentHandle )
				{
					if ( vartype == VARTYPE_EQUIPMENT_USE )
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;	
					else
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].equipment_id;	
					
					pAlias = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias;
					iNumber = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].nr;
					
					break;
				}
			
			CmtReleaseTSVPtr ( hMainStoreHandle );	
		}
	}
	
	if (( iSpecGroup == CALIBRATION_SPEC_GROUP ) && ( vartype != VARTYPE_EQUIPMENT_USE ))
		vartype += VARTYPE_CONFIG_OFFSET;

	reply = VarSetStringArray( hMainStoreHandle , vartype , ullLinkedID , name, iNumberOfItems , string );
	
	if (reply)
	{
		sprintf(tmp,"Error writing variable: %s",name);
		GUI_Line_To_Window ( handle  , CLB_LINE_WARNING,tmp);
		
		reply = 0; 
		
		RETURN;
	}
	
Error:
	
	return reply;
}

int	_SetVarInt( int handle, int vartype, char *name, int value , va_list arguments )
{
	int									result														=	0;
	int									reply														=	0;
	char								tmp[1024]													=	{0};
	
	STD_ERROR							StdError													=	{0};
	
	tsSlotStore							*ptCurrentSlote												=	NULL;
	
	tsMainStore						*pMainStore											=	NULL;

	int								iSpecGroup											=	0;
	
	int								hMainStoreHandle									=	0;
	
	int								iEquipmentHandle									=	0;
	
	unsigned long long				ullLinkedID											=	0;
	
	int								iSelectedTestIndex									=	0,
									iEquipmentUseIndex									=	0; 
	
	char							*pAlias												=	NULL;
	int								iNumber												=	0;
		
	IF (( handle == 0 ) , "Handle is NULL");
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote )); 
	iSpecGroup = ptCurrentSlote->iSpecGroup;
	hMainStoreHandle = ptCurrentSlote->hMainStoreHandle;
	iSelectedTestIndex = ptCurrentSlote->iCurrentTestIndex;  
	CHK_CMT(CmtReleaseTSVPtr ( handle ));
	
	if (( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) 
	{
		iEquipmentHandle = va_arg( arguments , int );
		
		if ( iEquipmentHandle == 0 )
		{
			RETURN;
		}
		
		if ( CmtGetTSVPtr ( hMainStoreHandle , &pMainStore ) == 0 )
		{	   
			for ( iEquipmentUseIndex = 0 ; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
				if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle == iEquipmentHandle )
				{
					if ( vartype == VARTYPE_EQUIPMENT_USE )
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;	
					else
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].equipment_id;	
					
					pAlias = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias;
					iNumber = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].nr;
					
					break;
				}
			
			CmtReleaseTSVPtr ( hMainStoreHandle );	
		}
	}
	
	if (( iSpecGroup == CALIBRATION_SPEC_GROUP ) && ( vartype != VARTYPE_EQUIPMENT_USE ))
		vartype += VARTYPE_CONFIG_OFFSET;
	
	reply = VarSetInt( hMainStoreHandle ,  vartype , ullLinkedID ,name,1,&value);
	
	if (reply)
	{
		sprintf(tmp,"Error writing variable: %s",name);
		GUI_Line_To_Window ( handle  , CLB_LINE_WARNING,tmp);
		
		result = 0; 
		
		RETURN;
	}
	
Error:	
	
	return result;
}

int	_SetVarIntArray( int handle, int vartype, char *name, int *pArrayValues , int Count  , va_list arguments )
{
	int								result												=	0;
	int								reply												=	0;
	char							tmp[1024]											=	{0};
	
	STD_ERROR						StdError											=	{0};
	
	tsSlotStore						*ptCurrentSlote										=	NULL;
	
	tsMainStore						*pMainStore											=	NULL;

	int								iSpecGroup											=	0;
	
	int								hMainStoreHandle									=	0;
	
	int								iEquipmentHandle									=	0;
	
	unsigned long long				ullLinkedID											=	0;
	
	int								iSelectedTestIndex									=	0,
									iEquipmentUseIndex									=	0; 
	
	char							*pAlias												=	NULL;
	int								iNumber												=	0;
	
	IF (( handle == 0 ) , "Handle is NULL");
	IF (( Count < 1 ) , "Count is too small");
		
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote )); 
	iSpecGroup = ptCurrentSlote->iSpecGroup;
	hMainStoreHandle = ptCurrentSlote->hMainStoreHandle;
	iSelectedTestIndex = ptCurrentSlote->iCurrentTestIndex;  
	CHK_CMT(CmtReleaseTSVPtr ( handle ));
	
	if (( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) 
	{
		iEquipmentHandle = va_arg( arguments , int );
		
		if ( iEquipmentHandle == 0 )
		{
			RETURN;
		}
		
		if ( CmtGetTSVPtr ( hMainStoreHandle , &pMainStore ) == 0 )
		{	   
			for ( iEquipmentUseIndex = 0 ; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
				if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle == iEquipmentHandle )
				{
					if ( vartype == VARTYPE_EQUIPMENT_USE )
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;	
					else
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].equipment_id;	
					
					pAlias = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias;
					iNumber = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].nr;
					
					break;
				}
			
			CmtReleaseTSVPtr ( hMainStoreHandle );	
		}
	}
	
	if (( iSpecGroup == CALIBRATION_SPEC_GROUP ) && ( vartype != VARTYPE_EQUIPMENT_USE ))
		vartype += VARTYPE_CONFIG_OFFSET;
	
	reply = VarSetInt( hMainStoreHandle ,  vartype , ullLinkedID , name , Count , pArrayValues );
	
	if (reply)
	{
		sprintf(tmp,"Error writing variable: %s",name);
		GUI_Line_To_Window ( handle  , CLB_LINE_WARNING,tmp);
		
		result = 0; 
		
		RETURN;
	}
	
Error:	
	
	return result;
}

int _SetVarDouble(  int handle , int vartype, char *name , double value  , va_list arguments )
{
	int								result												=	0;
	int								reply												=	0;
	char							tmp[1024]											=	{0};
	
	STD_ERROR						StdError											=	{0};
	
	tsSlotStore						*ptCurrentSlote										=	NULL;
	
	tsMainStore						*pMainStore											=	NULL;

	int								iSpecGroup											=	0;
	
	int								hMainStoreHandle									=	0;
	
	int								iEquipmentHandle									=	0;
	
	unsigned long long				ullLinkedID											=	0;
	
	int								iSelectedTestIndex									=	0,
									iEquipmentUseIndex									=	0; 
	
	char							*pAlias												=	NULL;
	int								iNumber												=	0;
	
	IF (( handle == 0 ) , "Handle is NULL");
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote )); 
	iSpecGroup = ptCurrentSlote->iSpecGroup;
	hMainStoreHandle = ptCurrentSlote->hMainStoreHandle;
	iSelectedTestIndex = ptCurrentSlote->iCurrentTestIndex;  
	CHK_CMT(CmtReleaseTSVPtr ( handle ));
	
	if (( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) 
	{
		iEquipmentHandle = va_arg( arguments , int );
		
		if ( iEquipmentHandle == 0 )
		{
			RETURN;
		}
		
		if ( CmtGetTSVPtr ( hMainStoreHandle , &pMainStore ) == 0 )
		{	   
			for ( iEquipmentUseIndex = 0 ; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
				if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle == iEquipmentHandle )
				{
					if ( vartype == VARTYPE_EQUIPMENT_USE )
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;	
					else
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].equipment_id;	
					
					pAlias = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias;
					iNumber = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].nr;
					
					break;
				}
			
			CmtReleaseTSVPtr ( hMainStoreHandle );	
		}
	}
	
	if (( iSpecGroup == CALIBRATION_SPEC_GROUP ) && ( vartype != VARTYPE_EQUIPMENT_USE ))
		vartype += VARTYPE_CONFIG_OFFSET;
	
	reply = VarSetDouble( hMainStoreHandle ,  vartype , ullLinkedID ,name,1,&value);
	
	if (reply)
	{
		sprintf(tmp,"Error writing variable: %s",name);
		GUI_Line_To_Window ( handle  , CLB_LINE_WARNING,tmp);
		
		result = 0; 
		
		RETURN;
	}

Error:
	
	return result;
}

int _SetVarDoubleArray( int handle, int vartype, char *name, double *pArrayValues , int Count  , va_list arguments ) 
{
	int								result												=	0;
	int								reply												=	0;
	char							tmp[1024]											=	{0};
	
	STD_ERROR						StdError											=	{0};
	
	tsSlotStore						*ptCurrentSlote										=	NULL;
	
	tsMainStore						*pMainStore											=	NULL;

	int								iSpecGroup											=	0;
	
	int								hMainStoreHandle									=	0;
	
	int								iEquipmentHandle									=	0;
	
	unsigned long long				ullLinkedID											=	0;
	
	int								iSelectedTestIndex									=	0,
									iEquipmentUseIndex									=	0; 
	
	char							*pAlias												=	NULL;
	int								iNumber												=	0;
		
	IF (( handle == 0 ) , "Handle is NULL");
	IF (( Count < 1 ) , "Count is too small");   
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote )); 
	iSpecGroup = ptCurrentSlote->iSpecGroup;
	hMainStoreHandle = ptCurrentSlote->hMainStoreHandle;
	iSelectedTestIndex = ptCurrentSlote->iCurrentTestIndex;  
	CHK_CMT(CmtReleaseTSVPtr ( handle ));
	
	if (( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) 
	{
		iEquipmentHandle = va_arg( arguments , int );
		
		if ( iEquipmentHandle == 0 )
		{
			RETURN;
		}
		
		if ( CmtGetTSVPtr ( hMainStoreHandle , &pMainStore ) == 0 )
		{	   
			for ( iEquipmentUseIndex = 0 ; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
				if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle == iEquipmentHandle )
				{
					if ( vartype == VARTYPE_EQUIPMENT_USE )
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;	
					else
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].equipment_id;	
					
					pAlias = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias;
					iNumber = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].nr;
					
					break;
				}
			
			CmtReleaseTSVPtr ( hMainStoreHandle );	
		}
	}
	
	if (( iSpecGroup == CALIBRATION_SPEC_GROUP ) && ( vartype != VARTYPE_EQUIPMENT_USE ))
		vartype += VARTYPE_CONFIG_OFFSET;
	
	reply = VarSetDouble( hMainStoreHandle ,  vartype , ullLinkedID , name , Count , pArrayValues );
	
	if (reply)
	{
		sprintf(tmp,"Error writing variable: %s",name);
		GUI_Line_To_Window ( handle  , CLB_LINE_WARNING,tmp);
		
		result = 0;
		
		RETURN;
	}

Error:
	
	return result;
}

/*****************************************************************/
int	_SetVarCalibration( int handle, int vartype, int iRange , int bCleanBefore , char *name , double *frequency , double *factor , int iNumOfPoints , va_list arguments )
{
	int								reply												=	0;
	char							tmp[1024]											=	{0};
	
	STD_ERROR						StdError											=	{0};
	
	tsSlotStore						*ptCurrentSlote										=	NULL;
	
	tsMainStore						*pMainStore											=	NULL;

	int								iSpecGroup											=	0;
	
	int								hMainStoreHandle									=	0;
	
	int								iEquipmentHandle									=	0;
	
	unsigned long long				ullLinkedID											=	0;
	
	int								iSelectedTestIndex									=	0,
									iEquipmentUseIndex									=	0; 
	
	char							*pAlias												=	NULL;
	int								iNumber												=	0;
		
	IF (( handle == 0 ) , "Handle is NULL");
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote )); 
	iSpecGroup = ptCurrentSlote->iSpecGroup;
	hMainStoreHandle = ptCurrentSlote->hMainStoreHandle;
	iSelectedTestIndex = ptCurrentSlote->iCurrentTestIndex;  
	CHK_CMT(CmtReleaseTSVPtr ( handle ));
	
	if (( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) 
	{
		iEquipmentHandle = va_arg( arguments , int );
		
		if ( iEquipmentHandle == 0 )
		{
			RETURN;
		}
		
		if ( CmtGetTSVPtr ( hMainStoreHandle , &pMainStore ) == 0 )
		{	   
			for ( iEquipmentUseIndex = 0 ; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
				if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle == iEquipmentHandle )
				{
					if ( vartype == VARTYPE_EQUIPMENT_USE )
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;	
					else
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].equipment_id;	
					
					pAlias = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias;
					iNumber = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].nr;
					
					break;
				}
			
			CmtReleaseTSVPtr ( hMainStoreHandle );	
		}
	}
	
	//if ( iSpecGroup == CALIBRATION_SPEC_GROUP )
		if ( vartype != VARTYPE_EQUIPMENT_USE )
			vartype += VARTYPE_CONFIG_OFFSET;
	
	reply = VarSetCalibration(  hMainStoreHandle ,  vartype , ullLinkedID , iRange ,  name, frequency , factor , iNumOfPoints , 1 , bCleanBefore );
	
	if (reply)
	{
		sprintf(tmp,"Error writing variable: %s",name);
		GUI_Line_To_Window ( handle  , CLB_LINE_WARNING,tmp);
		
		reply = 0;
		
		RETURN;
	}
	
Error:
	
	return reply;
}

int	_GetVarCalibration( int handle, int vartype, int iRange , char *name , double **frequency , double **factor , int *piNumOfPoints , double *plfCalibrationDate , va_list arguments )
{
	int								reply												=	0;
	char							tmp[1024]											=	{0};
	
	STD_ERROR						StdError											=	{0};
	
	tsSlotStore						*ptCurrentSlote										=	NULL;
	
	tsMainStore						*pMainStore											=	NULL;

	int								iSpecGroup											=	0;
	
	int								hMainStoreHandle									=	0;
	
	int								iEquipmentHandle									=	0;
	
	unsigned long long				ullLinkedID											=	0;
	
	int								iSelectedTestIndex									=	0,
									iEquipmentUseIndex									=	0; 
	
	char							*pAlias												=	NULL;
	int								iNumber												=	0;
		
	IF (( handle == 0 ) , "Handle is NULL");
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote )); 
	iSpecGroup = ptCurrentSlote->iSpecGroup;
	hMainStoreHandle = ptCurrentSlote->hMainStoreHandle;
	iSelectedTestIndex = ptCurrentSlote->iCurrentTestIndex;  
	CHK_CMT(CmtReleaseTSVPtr ( handle ));
	
	if (( vartype == VARTYPE_EQUIPMENT ) || ( vartype == VARTYPE_EQUIPMENT_USE )) 
	{
		iEquipmentHandle = va_arg( arguments , int );
			
		if ( iEquipmentHandle == 0 )
		{
			RETURN;
		}
		
		if ( CmtGetTSVPtr ( hMainStoreHandle , &pMainStore ) == 0 )
		{	   
			for ( iEquipmentUseIndex = 0 ; iEquipmentUseIndex < pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->count  ; iEquipmentUseIndex++ )  
				if ( pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].handle == iEquipmentHandle )
				{
					if ( vartype == VARTYPE_EQUIPMENT_USE )
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].id;	
					else
						ullLinkedID = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].equipment_id;	
					
					pAlias = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].alias;
					iNumber = pMainStore->tCurrentRunTestSeq.pCurrentRunTestSeq[iSelectedTestIndex].ptlDB_EquipmentList->equipment[iEquipmentUseIndex].nr;
					
					break;
				}
			
			CmtReleaseTSVPtr ( hMainStoreHandle );	
		}
	}
	
	//if ( iSpecGroup == CALIBRATION_SPEC_GROUP )
		if ( vartype != VARTYPE_EQUIPMENT_USE )
			vartype += VARTYPE_CONFIG_OFFSET;
	
	reply = VarGetCalibration(  hMainStoreHandle ,  vartype , ullLinkedID , iRange , name, frequency , factor , piNumOfPoints , plfCalibrationDate );
	
	if (reply)
	{
		sprintf(tmp,"Error reading variable: %s",name);
		GUI_Line_To_Window ( handle  , CLB_LINE_WARNING,tmp);
		
		reply = 0;
		
		RETURN;
	}
	
Error:
	
	return reply;
}

/*****************************************************************/
int	_SetVarCurrentCalibration( int handle, int iRange , int bCleanBefore , double *frequency , double *factor , int iNumOfPoints , va_list arguments )
{
	int								reply												=	0;
	char							tmp[1024]											=	{0};
	
	STD_ERROR						StdError											=	{0};
	
	tsSlotStore						*ptCurrentSlote										=	NULL;

	int								iSpecGroup											=	0;
	
	int								hMainStoreHandle									=	0;
	
	char							*pszCurrentPathName									=	0;

	char							szPathNameFormated[STD_STRING]						=	{0};
	
	int								iSlotIndex											=	0;
	
	IF (( handle == 0 ) , "Handle is NULL");
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote )); 
	iSpecGroup = ptCurrentSlote->iSpecGroup;
	hMainStoreHandle = ptCurrentSlote->hMainStoreHandle;
	CALLOC_COPY_STRING( pszCurrentPathName , ptCurrentSlote->pszCurrentPathName );
	iSlotIndex = ptCurrentSlote->iSlotIndex;
	CHK_CMT(CmtReleaseTSVPtr ( handle ));
	
	if ( strstr( pszCurrentPathName , "%d" ))
	{
		sprintf( szPathNameFormated , pszCurrentPathName , ( iSlotIndex+1 ));
		strcpy( pszCurrentPathName , szPathNameFormated );                
	}														 
	
	reply = VarSetCalibration(  hMainStoreHandle ,  (VARTYPE_STATION+VARTYPE_CONFIG_OFFSET) , 0 , iRange ,  pszCurrentPathName , frequency , factor , iNumOfPoints , 1 , bCleanBefore );
	
	if (reply)
	{
		if ( pszCurrentPathName )
			sprintf(tmp,"Error writing variable: %s",pszCurrentPathName);
		else
			sprintf(tmp,"Error writing variable pointer");
			
		GUI_Line_To_Window ( handle  , CLB_LINE_WARNING,tmp);
		
		reply = 0;
		
		RETURN;
	}
	
Error:
	
	FREE(pszCurrentPathName);
	
	return reply;
}

int	_GetVarCurrentCalibration( int handle, int iRange , double **frequency , double **factor , int *piNumOfPoints , double *plfCalibrationDate  , va_list arguments )
{
	int								reply												=	0;
	char							tmp[1024]											=	{0};
	
	STD_ERROR						StdError											=	{0};
	
	tsSlotStore						*ptCurrentSlote										=	NULL;

	int								iSpecGroup											=	0;
	
	int								hMainStoreHandle									=	0;

	char							*pszCurrentPathName									=	0;
	
	char							szPathNameFormated[STD_STRING]						=	{0};
	
	int								iSlotIndex											=	0;
	
	IF (( handle == 0 ) , "Handle is NULL");
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote )); 
	iSpecGroup = ptCurrentSlote->iSpecGroup;
	hMainStoreHandle = ptCurrentSlote->hMainStoreHandle;
	CALLOC_COPY_STRING( pszCurrentPathName , ptCurrentSlote->pszCurrentPathName );
	iSlotIndex = ptCurrentSlote->iSlotIndex;
	CHK_CMT(CmtReleaseTSVPtr ( handle ));
	
	if ( strstr( pszCurrentPathName , "%d" ))
	{
		sprintf( szPathNameFormated , pszCurrentPathName , ( iSlotIndex+1 ));
		strcpy( pszCurrentPathName , szPathNameFormated );                
	}	
	
	reply = VarGetCalibration(  hMainStoreHandle ,  (VARTYPE_STATION+VARTYPE_CONFIG_OFFSET) , 0 , iRange ,  pszCurrentPathName , frequency , factor , piNumOfPoints , plfCalibrationDate );
	
	if (reply)
	{
		if ( pszCurrentPathName )
			sprintf(tmp,"Error reading variable: %s",pszCurrentPathName);
		else
			sprintf(tmp,"Error writing variable pointer");
		
		GUI_Line_To_Window ( handle  , CLB_LINE_WARNING,tmp);
		
		reply = 0;
		
		RETURN;
	}
	
Error:

	FREE(pszCurrentPathName);
	
	return reply;
}


int	_GetVarCalibrationByName( int handle, char *pszName , int iRange , double **frequency , double **factor , int *piNumOfPoints , double *plfCalibrationDate  , va_list arguments )
{
	int								reply												=	0;
	char							tmp[1024]											=	{0};
	
	STD_ERROR						StdError											=	{0};
	
	tsSlotStore						*ptCurrentSlote										=	NULL;

	int								iSpecGroup											=	0;
	
	int								hMainStoreHandle									=	0;

	IF (( handle == 0 ) , "Handle is NULL");
	
	IF (( pszName == NULL ), "Name is empty" );	
	
	CHK_CMT( CmtGetTSVPtr ( handle , &ptCurrentSlote )); 
	iSpecGroup = ptCurrentSlote->iSpecGroup;
	hMainStoreHandle = ptCurrentSlote->hMainStoreHandle;
	CHK_CMT(CmtReleaseTSVPtr ( handle ));

	reply = VarGetCalibration(  hMainStoreHandle ,  (VARTYPE_STATION+VARTYPE_CONFIG_OFFSET) , 0 , iRange ,  pszName , frequency , factor , piNumOfPoints , plfCalibrationDate );
	
	if (reply)
	{
		if ( pszName )
			sprintf(tmp,"Error reading variable: %s",pszName);
		else
			sprintf(tmp,"Error writing variable pointer");
		
		GUI_Line_To_Window ( handle  , CLB_LINE_WARNING,tmp);
		
		reply = 0;
		
		RETURN;
	}
	
Error:

	return reply;
}

char		*StringReplaceAll( char *szSourceString , char *szFindWhat , char *szReplaceWith , int *pCount )
{
	STD_ERROR				StdError							=	{0};
	
	char				*pOutputString				=	NULL,
						*pInputString				=	NULL,
						*pPointer					=	NULL;
	
	int					count						=	0,
						index						=	0,
						iCountIndex					=	0,
						next_index					=	0,
						newLength					=	0,
						dynamicSize					=	0;
	
	int					*piLocationList				=	NULL,
						*piTemp						=	NULL;
	
	IF (( szSourceString == NULL ) , "Pointer can't be null.");
	IF (( szFindWhat == NULL ) , "Pointer can't be null.");
	IF (( szReplaceWith == NULL ) , "Pointer can't be null.");
	
	FREE_CALLOC_COPY_STRING_ERR( pInputString , szSourceString );
	dynamicSize = 1024;
	CALLOC_ERR( piLocationList , dynamicSize + 1 , sizeof(int));
	
	do 
	{
		pPointer = strstr( pInputString + index , szFindWhat ); 
		
		if ( pPointer )
		{
			index = pPointer - pInputString + strlen(szFindWhat);
			count++;
			*pPointer = 0;
			
			if ( count > dynamicSize )
			{
				dynamicSize *= 2;
				
				if ( dynamicSize < count)
					dynamicSize += count;
				
				CALLOC_COPY_ERR( piTemp , dynamicSize + 1 , sizeof(int) , piLocationList , count ); 
				FREE( piLocationList );
				piLocationList = piTemp;
			}
			
			piLocationList[count] = index;
		}
		
	}while(pPointer);
	
	if ( pCount )
		*pCount = count;
	
	newLength = strlen(szSourceString) + (( count + 1 ) * strlen(szReplaceWith));
	
	if ( count )
	{
		CALLOC_ERR( pOutputString , newLength , sizeof(char));
	
		for ( iCountIndex = 0 ; iCountIndex < count ; iCountIndex++ )
		{
			index = piLocationList[iCountIndex];
			next_index += sprintf ( pOutputString + next_index , "%s%s" , pInputString + index , szReplaceWith );
		}

		index = piLocationList[iCountIndex];
		sprintf ( pOutputString + next_index , "%s" , pInputString + index );   
	}
	
Error:
	
	if ( pOutputString == NULL )
	{
		CALLOC_COPY_STRING(pOutputString,szSourceString);
	}
	
	FREE(pInputString);
	FREE(piLocationList);
	
	return pOutputString;
}
  
int  ShowMessage ( int hDatabaseHandle , int type , char *pTitle , char *pText, char *pPicture )
{
	STD_ERROR						StdError											=	{0};

	int  							setupHandle											=	0;
	int 							pan													=	0,
									ctl													=	0;
	
	int								iStatus												=	0,
									iTextLength											=	0;
										
	char							*pTemp												=	NULL,
									*pInstructionText									=	NULL,
									*pFileNamePath										=	NULL;
	
	char							szPicLocation[STD_STRING]							=	{0};
										
	double							lfStartTime											=	0.0, 
									lfCurrentTime										=	0.0;
	
	if ( pText == NULL )
		return 0;
	
	if ( pText )
		iTextLength = strlen(pText);
	
	CALLOC_ERR( pInstructionText , iTextLength + 10 , sizeof(char));
		
	if ( pText )
		strcpy( pInstructionText , pText );

	setupHandle=LoadPanel( 0 , "Gui_UI.Uir" ,SETUP_MSG );

	switch (type)
	{
		case INSTR_TYPE_CONTINUE:
			
			SetCtrlAttribute(setupHandle,SETUP_MSG_CONTINUE,ATTR_VISIBLE,1);
			
			break;
			
		case INSTR_TYPE_YES_NO:
			
			SetCtrlAttribute(setupHandle,SETUP_MSG_YES,ATTR_VISIBLE,1);
			SetCtrlAttribute(setupHandle,SETUP_MSG_NO,ATTR_VISIBLE,1);
			
			break;
	}
	
	if ( iTextLength )
	{
		pTemp = StringReplaceAll( pInstructionText , "\\n" , "\n" , NULL); 
		
		if ( pTemp )
		{
			strcpy( pInstructionText , pTemp );
			FREE(pTemp);
		}
		
		SetCtrlVal( setupHandle , SETUP_MSG_INSTRACTION_TEXT , pInstructionText );
	}
	
	if (pPicture)
	{
		if ( strlen(pPicture) > 5 )
		{
			if ( FileExists(pPicture,NULL) )  
			{
				strcpy( szPicLocation , pPicture );   
			}
			else
			{
				pTemp = strrchr( pPicture , '\\' );
			
				if ( pTemp )
				{
					pTemp++;
					
					strcpy( szPicLocation , pTemp );  
				}
				else
				{
					strcpy( szPicLocation , pPicture );   	
				}
					
				if ( hDatabaseHandle )
				{
					GetDataBaseFileByName( hDatabaseHandle , FILE_LINK_INSTRUCTION_PICS , szPicLocation , NULL , NULL , NULL , NULL , &pFileNamePath );	
				}
				
				if ( pFileNamePath )
				{
					strcpy( szPicLocation , pFileNamePath );  	
					FREE(pFileNamePath);
				}
			}
			
			if (( strlen(szPicLocation) > 5 ) && (FileExists(szPicLocation,NULL)))
				DisplayImageFile (setupHandle, SETUP_MSG_INSTRACTION_PICTURE, szPicLocation);
		}
	}
	
	if ( strlen(szPicLocation) == 0 )
	{
		SetCtrlAttribute( setupHandle , SETUP_MSG_INSTRACTION_TEXT , ATTR_WIDTH , 890 );
		SetCtrlAttribute( setupHandle , SETUP_MSG_INSTRACTION_TEXT , ATTR_HEIGHT , 485 ); 	
	}
	
	iStatus = 1;

	SetPanelPos ( setupHandle , VAL_AUTO_CENTER , VAL_AUTO_CENTER );
	InstallPopup (setupHandle);
	
	if ( pTitle )
		SetPanelAttribute( setupHandle , ATTR_TITLE , pTitle );    
		
	while(1)
	{
		GetCurrentDateTime(&lfCurrentTime); 
			
		if (( lfCurrentTime - lfStartTime ) > 10.0 )
		{																			   
			MakeApplicationActive ();   
			SetActivePanel( setupHandle ); 
			
			GetCurrentDateTime(&lfStartTime);  
		}
		
		ProcessSystemEvents();
		
		GetUserEvent (0, &pan, &ctl);
	    
	  	if (ctl == SETUP_MSG_CONTINUE)
	    	break;
  
	  	if (ctl == SETUP_MSG_YES)
	    	break;
  
	  	if (ctl == SETUP_MSG_NO)
	  	{
		  	iStatus = 0;
		  	break;
	  	}
	}
	
Error:
	
	RemovePopup (0);

	DiscardPanel(setupHandle);
	
	FREE(pInstructionText);
	
	return iStatus;
}
  
int  InputMessage ( char *pTitle , char *pText, char *pInputMessage )
{
	STD_ERROR						StdError											=	{0};

	int  							panelHandle											=	0;
	int 							pan													=	0,
									ctl													=	0;
	
	int								iStatus												=	0,
									iTextLength											=	0;
										
	char							*pTemp												=	NULL,
									*pInstructionText									=	NULL;
	
	double							lfStartTime											=	0.0, 
									lfCurrentTime										=	0.0;
	
	if ( pText == NULL )
		return 0;
	
	if ( pText )
		iTextLength = strlen(pText);
	
	CALLOC_ERR( pInstructionText , iTextLength + 10 , sizeof(char));
		
	if ( pText )
		strcpy( pInstructionText , pText );

	panelHandle=LoadPanel( 0 , "Gui_UI.Uir" , INPUT );

	if ( iTextLength )
	{
		pTemp = StringReplaceAll( pInstructionText , "\\n" , "\n" , NULL); 
		
		if ( pTemp )
		{
			strcpy( pInstructionText , pTemp );
			FREE(pTemp);
		}
		
		SetCtrlVal( panelHandle , INPUT_TEXT , pInstructionText );
	}

	iStatus = 1;

	SetPanelPos ( panelHandle , VAL_AUTO_CENTER , VAL_AUTO_CENTER );
	InstallPopup (panelHandle);
	
	if ( pTitle )
		SetPanelAttribute( panelHandle , ATTR_TITLE , pTitle );    
		
	while(1)
	{
		GetCurrentDateTime(&lfCurrentTime); 
			
		if (( lfCurrentTime - lfStartTime ) > 1.0 )
		{																			   
			MakeApplicationActive ();   
			SetActivePanel( panelHandle ); 
			
			GetCurrentDateTime(&lfStartTime);  
		}
		
		ProcessSystemEvents();
		
		GetUserEvent (0, &pan, &ctl);
  
	  	if (ctl == INPUT_YES)
	    {
			GetCtrlVal( panelHandle , INPUT_INPUT , pInputMessage );
			iStatus = 0;  
			break;
		}
		
	  	if (ctl == INPUT_NO)
		  	break;
	}
	
Error:
	
	RemovePopup (0);

	DiscardPanel(panelHandle);
	
	FREE(pInstructionText);
	
	return iStatus;
}
