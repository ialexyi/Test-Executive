//==============================================================================
// Include files

#include <userint.h>

#include "database.h"
#include "defines.h"

//==============================================================================
// Constants

#define			USER_REQUEST_BREAK				1111

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

int CreateProgressPanel ( char* szMainTitle , int iNumberOfBars )
{
	int					hPanelWait					=	0; 
	
	if (( iNumberOfBars > WAIT_MAX_BARS ) || ( iNumberOfBars < 1 ))
		return -1;
	
	hPanelWait = LoadPanel ( 0 , "database.uir" , PROGRESS );
	
	if ( hPanelWait < 1 )
		return -1;
	
	if ( szMainTitle != NULL )
		SetPanelAttribute ( hPanelWait , ATTR_TITLE , szMainTitle );
	
	SetPanelAttribute ( hPanelWait , ATTR_HEIGHT , WAIT_BAR_START + ( WAIT_BAR_STEP * iNumberOfBars ) );
		
	InstallPopup (hPanelWait);
	
	MakeApplicationActive ();
	SetActivePanel ( hPanelWait );
	ProcessDrawEvents();

	return hPanelWait;
}

void DiscardProgressPanel ( int hProgressHandle )
{
	if ( hProgressHandle > 0 )
	{
		RemovePopup (0);
		DiscardPanel ( hProgressHandle ); 
	}
}
   
void UpdateProgressPanel ( int hProgressHandle , char* szNewMainTitle , int iNewNumberOfBars )
{
	if ( hProgressHandle < 1 )
		return;

	if (( iNewNumberOfBars > WAIT_MAX_BARS ) || ( iNewNumberOfBars < 1 ))
		return;
	
	if ( szNewMainTitle != NULL )
		SetPanelAttribute ( hProgressHandle , ATTR_TITLE , szNewMainTitle );
	
	SetPanelAttribute ( hProgressHandle , ATTR_HEIGHT , WAIT_BAR_START + ( WAIT_BAR_STEP * iNewNumberOfBars ) );

	ProcessDrawEvents();
}

void UpdateBarTitle ( int hProgressHandle , int iBarNumber , char* szBarTitle )
{
	if ( hProgressHandle < 1 )
		return;
	
	if ( szBarTitle == NULL )
		return;
	
	switch (iBarNumber)
	{
		case 1: SetCtrlAttribute ( hProgressHandle , PROGRESS_BAR_1 , ATTR_LABEL_TEXT , szBarTitle ); break;
		case 2: SetCtrlAttribute ( hProgressHandle , PROGRESS_BAR_2 , ATTR_LABEL_TEXT , szBarTitle ); break;
		case 3: SetCtrlAttribute ( hProgressHandle , PROGRESS_BAR_3 , ATTR_LABEL_TEXT , szBarTitle ); break;
		case 4: SetCtrlAttribute ( hProgressHandle , PROGRESS_BAR_4 , ATTR_LABEL_TEXT , szBarTitle ); break;
		case 5: SetCtrlAttribute ( hProgressHandle , PROGRESS_BAR_5 , ATTR_LABEL_TEXT , szBarTitle ); break;
		case 6: SetCtrlAttribute ( hProgressHandle , PROGRESS_BAR_6 , ATTR_LABEL_TEXT , szBarTitle ); break;
		case 7: SetCtrlAttribute ( hProgressHandle , PROGRESS_BAR_7 , ATTR_LABEL_TEXT , szBarTitle ); break;
		case 8: SetCtrlAttribute ( hProgressHandle , PROGRESS_BAR_8 , ATTR_LABEL_TEXT , szBarTitle ); break;
		case 9: SetCtrlAttribute ( hProgressHandle , PROGRESS_BAR_9 , ATTR_LABEL_TEXT , szBarTitle ); break;
		
		default: break;
	}
	
	ProcessDrawEvents();
}

int UpdateBarProgress ( int hProgressHandle , int iBreakAllowFromBarNumber , int iBarNumber , int iProgress , int iCount )
{  
	int				iBarCtrlID				=	0,
					iCountCtrlID			=	0;
	
	int				iGetPanel				=	0,   
					iGetControl				=	0,
					event					=	0;
						
	char			szCount[32]				=	{0};
	
	if ( hProgressHandle < 1 )
		return 0;
	
	if ( iProgress < 0 )
		iProgress = 0;
	
	if ( iProgress > 100 )
		iProgress = 100;
	
	if ( iCount > 0 )
		sprintf ( szCount , "%d" , iCount );
	else
		strcpy ( szCount , "" );
	
	switch (iBarNumber)
	{
		case 1: iBarCtrlID = PROGRESS_BAR_1; iCountCtrlID = PROGRESS_COUNT_1; break;
		case 2: iBarCtrlID = PROGRESS_BAR_2; iCountCtrlID = PROGRESS_COUNT_2; break;
		case 3: iBarCtrlID = PROGRESS_BAR_3; iCountCtrlID = PROGRESS_COUNT_3; break;
		case 4: iBarCtrlID = PROGRESS_BAR_4; iCountCtrlID = PROGRESS_COUNT_4; break;
		case 5: iBarCtrlID = PROGRESS_BAR_5; iCountCtrlID = PROGRESS_COUNT_5; break;
		case 6: iBarCtrlID = PROGRESS_BAR_6; iCountCtrlID = PROGRESS_COUNT_6; break;
		case 7: iBarCtrlID = PROGRESS_BAR_7; iCountCtrlID = PROGRESS_COUNT_7; break;
		case 8: iBarCtrlID = PROGRESS_BAR_8; iCountCtrlID = PROGRESS_COUNT_8; break;
		case 9: iBarCtrlID = PROGRESS_BAR_9; iCountCtrlID = PROGRESS_COUNT_9; break;
		
		default: break;
	}
	
	SetCtrlVal ( hProgressHandle , iBarCtrlID , iProgress );
	SetCtrlVal ( hProgressHandle , iCountCtrlID , szCount );
	
	ProcessDrawEvents();
	
	if (( iBarNumber != 0 ) && ( iBarNumber <= iBreakAllowFromBarNumber ))
	{
		event = GetUserEvent ( 0 , &iGetPanel , &iGetControl );   
		
		if ( iGetPanel == hProgressHandle )
			if ( event == USER_REQUEST_BREAK )
				return 1;	
	}
	
	return 0;
}


int CVICALLBACK clbProgressBar (int panel, int event, void *callbackData, int eventData1, int eventData2)  
{
	if ( event == EVENT_CLOSE )
		QueueUserEvent ( USER_REQUEST_BREAK , panel , 0 );
	
	return 0;
}

