#ifndef __Select_SN_RMA_Defines_H__
#define __Select_SN_RMA_Defines_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "GlobalDefines.h"
#include "TE_GlobalDefines.h"
#include "inifile.h"

//==============================================================================
// Constants
		
#define		MAX_SN_NUM			10
		
#define		MAX_HISTORY_NUM		12		
		
#define		INI_HISTORY_FILE_NAME		"SN_History_list.ini"		
#define		INI_SEC_SN_HISTORYS			"SN_HISTORYS"
#define		INI_SEC_PN_HISTORYS			"PN_HISTORYS"  
#define		INI_SEC_LAST_CONFIG			"LAST_CONFIGURATION"
		
#define		SN_STEP						40
#define		START_POSITION_NOTE			260
#define		START_POSITION_BUTTONS		350		
#define		START_POSITION_P_DOWN		440

#define		START_POSITION_RMA_NUM		260
#define		START_POSITION_WORK_NUM		320
		
//==============================================================================
// Types

enum
{
	ERROR_SLOTS_NUM_OUT_OF_RANGE 		= 	-1651,
	ERROR_CREATE_HANDLE					=	-1652,
	ERROR_GET_VARIABLE					=	-1653,
	ERROR_GUI_SN						=	-1654,
	ERROR_LOAD_LAST						=	-1655,
	
	ATTENTION_CANCEL					=	0,
	ATTENTION_OK						=	1
};

		
/*************************************************************************/

//typedef struct
//{
//	char				szHistoryNumber[256];
//	
//}tsSnHistoryList;			

typedef int		(*tfSN_Parsing)( char *pSerialNumber , int iStartIndex , tsExtraParamsList tListParameters );

typedef int		(*tfAUTO_Selection)( char *pPartNumber , char *pSerialNumber , unsigned int *piUUT_Index , unsigned int *piVerion_Index , void **piExtraData , int *piExtraDataLength );

typedef struct
{
	int							sn_contorlID,
								pn_contorlID, 
								ring_sn_ID,
								ring_pn_ID, 
								enableID,
								rmaID;
	
	char						*pszSerialNumber,
								*pszPartNumber,
								*pszNote;
	
	char						szRMANumber[512],
								szWorkNumber[512];
	
	int							bEnableRun,
								bRMA;
	
	unsigned int				iAutoSelect_UUT_Index,
								iAutoSelect_Verion_Index;
	
	void						*piAutoSelect_ExtraData;
	
	int							iAutoSelect_ExtraDataLength;
	
	tsExtraParamsList			extraParameters; 
	
	char						szProtect[64];

}tsSnControl;			// CONTROL

		
typedef struct
{
	int							hPanelHandle;
	
	int							iPanelTopAttr;
	
	int							iActiveSnIndex;
	
	int							iSelectedSnQuantity,
								iMaxSnQuantity;			
	
	tsSnControl					*SnControlsList;		

	IniText						hIniBuffer;
	
	tfSN_Parsing				fSN_Parsing;
	
	tfAUTO_Selection			fAUTO_Selection;
	
	char						szProtect[64];

}tsMainGuiInfo;			// MAIN PANEL			
		
//==============================================================================
// External variables

//==============================================================================
// Global functions
	
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Select_SN_RMA_Defines_H__ */
