#ifndef __defines_H__
#define __defines_H__
#include "Windows.h"

#include <utility.h>
#include "toolbox.h"
#include "pwctrl.h"
#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>
#include "database.h"
#include "dblayer.h"
#include "GlobalDefines.h"
#include "TE_GlobalDefines.h"

#define		MAIN_COLOR							0x7C378AL
// 1-based column index of variables panel
#define 	VAR_COL_NAME 						1
#define 	VAR_COL_TYPE 						2
#define 	VAR_COL_VAL 						3
#define 	VAR_COL_ID 							4

// var types of variables (linked to) for variables panel
#define 	VAR_LINK_MEASURE_STORE				1
#define 	VAR_LINK_GLOBAL 					2
#define 	VAR_LINK_UUT 						3
#define 	VAR_LINK_UUTVER 					4
#define 	VAR_LINK_TEST 						5
#define 	VAR_LINK_USER 						6
#define 	VAR_LINK_STATION 					7
#define 	VAR_LINK_EQUIPMENT 					8
#define 	VAR_LINK_EQUIPMENT_USE				9

// var types of variables (linked to) for configuration panel
#define 	VAR_CONFIG_MEASURE_STORE			11
#define 	VAR_CONFIG_GLOBAL 					12
#define 	VAR_CONFIG_UUT 						13
#define 	VAR_CONFIG_UUTVER 					14
#define 	VAR_CONFIG_TEST 					15
#define 	VAR_CONFIG_USER 					16
#define 	VAR_CONFIG_STATION 					17
#define 	VAR_CONFIG_EQUIPMENT 				18
#define 	VAR_CONFIG_EQUIPMENT_USE			19

// 0-based index for var type ring
#define 	VAR_TYPE_ARRAY_INT 					0
#define 	VAR_TYPE_ARRAY_DOUBLE 				1
#define 	VAR_TYPE_STRING 					2
#define 	VAR_TYPE_ARRAY_STRING 				3
#define 	VAR_TYPE_INT 						4
#define 	VAR_TYPE_DOUBLE 					5

// constance string to display 
#define 	VAR_RING_INT_ARRAY 					"Integer[]"
#define 	VAR_RING_DOUBLE_ARRAY 				"Real[]"
#define 	VAR_RING_STRING 					"String"
#define 	VAR_RING_STRING_ARRAY 				"String[]"
#define 	VAR_RING_INT 						"Integer"
#define 	VAR_RING_DOUBLE 					"Real"

#define 	VAR_RING_ARRAY						"Array"

// 1-based column index of specs panel
#define 	SPEC_COL_MIN 						1
#define 	SPEC_COL_MAX 						2
#define 	SPEC_COL_MULT 						3
#define 	SPEC_COL_UNIT 						4
#define 	SPEC_COL_TYPE 						5
#define 	SPEC_COL_CTGR 						6
#define 	SPEC_COL_ALOW 						7 
#define 	SPEC_COL_ACC 						8
#define 	SPEC_COL_DISC 						9
#define 	SPEC_COL_ID 						10
#define 	SPEC_COL_NR 						11

// 1-based column index of specs panel
#define 	REPORT_COL_NR 						1
#define 	REPORT_COL_UUT 						2
#define 	REPORT_COL_VERSION 					3
#define 	REPORT_COL_SN 						4
#define 	REPORT_COL_STATUS 					5
#define 	REPORT_COL_FULL 					6
#define 	REPORT_COL_SLOT 					7
#define 	REPORT_COL_TEMP 					8  
#define 	REPORT_COL_USER 					9  
#define 	REPORT_COL_TIME 					10  
#define 	REPORT_COL_STATION 					11 
#define 	REPORT_COL_NOTE 					12 
#define 	REPORT_COL_ID 						13

// 1-based column index of specs array panel
#define 	GRAPH_TRACE_COL_X 					1
#define 	GRAPH_TRACE_COL_MIN 				2
#define 	GRAPH_TRACE_COL_MAX 				3

#define		SPEC_MULT_ZERO_NAME					"none    -  "
#define 	SPEC_MULT_ZERO_INDEX				10

#define		SPEC_GRAPH_MIN_Y_DEF				0.0
#define		SPEC_GRAPH_MAX_Y_DEF				10.0
#define		SPEC_GRAPH_MIN_X_DEF				0.0
#define		SPEC_GRAPH_MAX_X_DEF				1024.0

// var types of files (linked to) for files panel
#define 	FILE_LINK_TEMPORARY_FILES			0 
#define 	FILE_LINK_MAIN_APPLICATION			1
#define 	FILE_LINK_PERIPHERAL				2

#define 	FILE_LINK_UUT	 					3
#define 	FILE_LINK_VERSION 					4
#define 	FILE_LINK_TEST 						5
#define 	FILE_LINK_CONFIG_FILES 				6
#define 	FILE_LINK_TE_MODULE 				7
#define 	FILE_LINK_UUTPIC 					8
#define 	FILE_LINK_STATIONPIC				9 
#define 	FILE_LINK_EQUIPMENT					10
#define 	FILE_LINK_SN_MODULE 				11
#define 	FILE_LINK_PARSE_MODULE 				12
#define 	FILE_LINK_INPUT_MODULE 				13
#define 	FILE_LINK_HEADER_PICTURES			14
#define 	FILE_LINK_AUTO_MODULE 				15
#define 	FILE_LINK_OVEN_MODULE 				16
#define 	FILE_LINK_CALIB_MODULE 				17
#define 	FILE_LINK_PATH_MODULE 				18
#define 	FILE_LINK_EXCEL_TEMPLATE			19
#define 	FILE_LINK_WORD_TEMPLATE				20
#define 	FILE_LINK_TEST_REFERENCE			21
#define 	FILE_LINK_EQUIPMENT_PICS			22
#define 	FILE_LINK_INSTRUCTION_PICS			23
#define		FILE_LINK_EQUIPMENT_STATES			24

//#define 	FILE_LINK_OVEN_MODULE 				50

#define		FILE_NOT_LINKED_MSSG				"<not linked>"

// equipment types

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

#define 	TRACE_NAME_MIN						"Min"
#define 	TRACE_NAME_MAX						"Max"

#define		NR_CTRL_POS_LEFT					60
#define		NR_CTRL_POS_WIDTH					40
#define		NR_CTRL_TEXT_SIZE					14

#define		PANEL_CUT_UNDER						20

#define		TEST_HEADER_SIZE					13
#define		HTML_PAGE_SIZE						54
	
#define		DEFAULT_ADMIN_USER					"root"

#define		DEFAULT_AUTHORIZATION_STRING		"xxx NOT AUTHORIZED xxx"

#define		GUID_STRING_LENGTH					16
#define		LICENSE_MAX_LENGTH					24
#define		ASCII_SMALL_TO_BIG					32
#define		AUTHOR_MAX_LENGTH					30

#define		PROGRESS_BAR_TABLES_NUM				26

#define		WAIT_MAX_BARS						9
#define		WAIT_BAR_START						30
#define		WAIT_BAR_STEP						70

#define		WAIT_BAR_ON_CONT					100

#define		LICENSE_SERVER_PORT					2016
#define		LICENSE_SERVER_ADDRESS				"10.0.1.1"

#define		REFERENCE_DB_NAME					""

#define 	INFO_VERSION_NAME					"Data Base Version"
#define 	INFO_STATION_UNIQUE_NAME			"Station Unique"

#define		TEST_EXECUTIVE_FILENAME				"Test Executive.exe"

#define		TEST_SET_SUB_DIRECTORY				"Test Set"

#define		ESC_KEY								768  

/************ Database Version **************************************************/
#define		DB_LOCAL_VERSION					"1.0.0"
/********************************************************************************/

typedef enum { DB_SQL_TYPE_SQLITE , DB_SQL_TYPE_MS_SQL_SERVER , DB_SQL_TYPE_SENTINEL } teDbSqlType; 

typedef enum {SCALE_TYPE_AUTO , SCALE_TYPE_PRESET , SCALE_TYPE_MARGEN , SCALE_TYPE_SENTINEL } teScale;
typedef enum {INTER_TYPE_NONE , INTER_TYPE_LINEAR , INTER_TYPE_COSINE , INTER_TYPE_CUBIC , INTER_TYPE_HERMITE , INTER_TYPE_SENTINEL } teInter;
typedef enum {FLOATING_TYPE_NONE , FLOATING_TYPE_PEAK , FLOATING_TYPE_TOP , FLOATING_TYPE_TOP_SKIP , FLOATING_TYPE_SENTINEL } teFloting;
typedef enum {LABEL_TYPE_GOOD , LABEL_TYPE_SENTINEL } teLabel;  
typedef enum {ALLOW_TYPE_ENABLE , ALLOW_TYPE_DISABLE , ALLOW_TYPE_NO_COMPARE , ALLOW_TYPE_COMPARE_HIGH , ALLOW_TYPE_COMPARE_LOW , ALLOW_TYPE_SENTINEL } teAllow;

/***************/
typedef struct 
{
	//int						iNumber;
	
	char						szText[1024];
	
	int							iExist;					// 0/1
	
	int							iPositionLeft,			// 1-990
								iPositionTop,			// 20-670
								iPositionWidth,			// 1-500
								iPositionHeight;		// 1-100
	
	int							iTextSize,				// 1-255
								iTextColor,				// ring
								iTextBold,				// 0/1
								iTextItalics,			// 0/1
								iTextUnderline,			// 0/1
								iTextJustification,		// ring
								iTextBackground;		// ring
	
	char						szTextFont[64];			// ring
	
	int							iImageFitMode;
	
	char						szProtect[64];
	
} tsControlData;

typedef struct 
{
	//int						iNumber;
	
	int							iDefCtrl;
	
	int							iType;
	
	unsigned long long			iImageID;
	
	int							iUnique; 
	
	int							iLeft;  
	
	int							iTop; 
	
	tsControlData				tLabel;
	
	tsControlData				tValue;
	
	char						szProtect[64];
	
} tsControls;
/***************/

/* DB */
int	VersionUpToDate( int hDatabaseHandle , int hPanelHandle , int *pbHasBeenCreatedFromScratch , unsigned long long *pStationUnique );

int DataBaseCleanUp(int hDatabaseHandle, int hProgressHandle, double lfStartTime);

int CheckAndUpdate_DataBase( int hMainStore , char *pszReferanceDataBaseName , int bUpdateStationParamsFromMaster );

int DataBaseMerge( int hMainStore , int bImportExport , char *szReferanceDataBaseName , int bBasicOnly , int bAutoUpdate );
int ClearCopyTemps (int hMainStore);

int GetTableCellIndex(int panel, int control, Point cell, int *index);

unsigned long long LoadFile( int handle , unsigned linktype, unsigned link, char* defExt, char* extList, char* title, char** outname);

unsigned ReLoadFile( int handle , unsigned long long ulFileID , unsigned linktype, unsigned link, char* defExt, char* extList, char* title, char** outname);
unsigned SaveFile( int handle , unsigned long long id, char* extList, char* title);

int ReLoadAllFiles( int hDatabaseHandle , unsigned long long dwOperatorPrivileges , int linktype );

int CleanupDuplicatedFiles ( int hDatabaseHandle , int linktype ); 

/* DB_Users */
void showUsers ( int hMainStore );

int IsPrivilegePermittedByName ( long long dwPrivileges , char *pPrivName );
int IsPrivilegePermittedByBitIndex ( long long dwPrivileges , int iBitIndex );

/* DB_Stations */
void showStations( int hMainHandle );

void showProjects( int hMainStore );

int stationShowPicture( int handle , int panelStation , unsigned long long id );

/* DB_UUTs */
void showUUTs ( int hMainStore );

int uutShowPicture( int handle , int panelUUT , unsigned long long id );

/* DB_Versions */
void showVersions ( int hMainStore );

int showTests (int hMainStore, int hPanelVer, unsigned long long iActiveVerID);

/* DB_Variables */
void showVariables ( int hMainStore , int iVarLinkType );

/* DB_Specs */
void showSpecs ( int hMainStore );

/* DB_Files */
void showFiles ( int hMainStore );

/* Reports */
void showReports( int hMainHandle , char* serial );

/* Configuration */
void showConfiguration ( int hMainHandle );

void showEquipment( int hMainStore , int bAutoScan );

void showUseEquipment( int hMainStore , int iType , char *pszAlias , int iNumber , int iTestMode , int *pNewEquipmentHandle );

void showUseEquipmentTable( int hMainStore ); 

void showFrequencies( int hMainStore );

/* Version Configuration */
void showVersionConfiguration ( int hMainStore );

int SortControls ( int panel , tsConfigControl *ptConfigControls );
int FillControlsPanel( int hMainStore, int hPanelConfig , long long lUutVersionID , int iSpecGroup , int *piUndergroundPosition , tsConfigControl **ptConfigControls );
int AddNewControl ( int panel , int hMainStore , tsControls tControlToAdd , tsConfigControl **ptConfigControls );

int DefaultControlsQuantity ( void );

//void showDocs(int doctype, int link);

//Updates predefinition
void UpdateDocsData( int panel );
void UpdateTestDocsData( int panel );

// Variables and Configuration Help Functions 
void fillTableByVarList(int hPanelVar, int iControlID, tlVar *varList);
void fillArrayTableByVar(int hPanelVar, int iArrayCtrlID, int iCountCtrlID, tVar *var);
void fillArrayTableByVarStringConvert(int hPanelVar, int iArrayCtrlID, int iCountCtrlID, int bEdit, tVar *var);

char *DateTimeToString ( double lfDateTime );
char *DateTimeDifferenceToString ( double lfStartDateTime , double lfEndDateTime , int bEnableMillisecond );
char *TimeToString ( double lfDateTime  );
char *DateOnlyToString ( double lfDateTime );

char *StringReplaceAll( char *szSourceString , char *szFindWhat , char *szReplaceWith , int *pCount ); 

int GetSystemPrivilegios ( void );

int ShutdownPC ( void );

int EraseFolderEntry ( char *pszFilePath );

int	GetFileVersion( char *szFileNamePath , char *szVersion );
int	GetFileDateTime( char *szFileNamePath , double *vlfDateTime );

int CVICALLBACK RUN_ExportReports ( void *pData ); 
int CVICALLBACK RUN_ImportNewFiles( void *pData ); 
int CVICALLBACK RUN_BuildReports ( void *pData );

/* WaitProgress */

int CreateProgressPanel ( char* szMainTitle , int iNumberOfBars );
void DiscardProgressPanel ( int hProgressHandle );
void UpdateProgressPanel ( int hProgressHandle , char* szNewMainTitle , int iNewNumberOfBars );

void UpdateBarTitle ( int hProgressHandle , int iBarNumber , char* szBarTitle );
int UpdateBarProgress ( int hProgressHandle , int iBreakAllowFromBarNumber , int iBarNumber , int iProgress , int iCount );

STD_ERROR DuplicateSingleTestItem( tsTestListItem *pTargetListItem , tsTestListItem *pSourceListItem ); 
STD_ERROR FreeTestListItem( tsTestListItem *ptTestListItem );

void	LoadDatabaseFromRegistry( char *pszOdbcName , tDatabase **pDatabaseItem );
void	SaveDatabaseToRegistry( tDatabase *pDatabaseInfo );

STD_ERROR GetDataBaseFileByID( int hDatabaseHandle, unsigned long long ulFileID , char *pReplacePath , char *pReplaceName , char **pFileName , char **pPath , char **pFileNamePath );

STD_ERROR GetDataBaseFileByName( int hDatabaseHandle, int iLinkType , char *pName , char *pReplacePath , char *pReplaceName , char **pFileName , char **pPath , char **pFileNamePath );

void	FreeDatabaseItem( tDatabase **pDatabaseItem );  
int 	CheckMainDatabaseConnection( int hMainStore );

int		RecursiveMakeDirectory( char *pPath );
int		RecursiveDeleteDirectory( char *pPath );

int		verPastSupport( int hDatabaseHandle , int hProgressHandle , int hProgressBarIndex , int tRunMode , unsigned long long  hCurrentStationId ,  unsigned long long hSourceUutID ,  unsigned long long hTargetUutID , tlUutVer *copyUUTversions );
int		testPastSupport( int hDatabaseHandle , int hProgressHandle , int hProgressBarIndex , int tRunMode , unsigned long long  hCurrentStationId ,  unsigned long long hSourceVersionID ,  unsigned long long hTargetVersionID , tlTest *copyTests );

unsigned __int64		ParseVersionString( char *pszVersionString );

int TemporaryRegestryCommands( int hMainStore );

#endif  /* ndef __defines_H__ */
