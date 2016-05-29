/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2011. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  pSERIAL                          1
#define  pSERIAL_OK_BUTTON                2       /* control type: pictButton, callback function: clbOkBut */
#define  pSERIAL_NOTE                     3       /* control type: textBox, callback function: clbNote */
#define  pSERIAL_tbOPERATOR               4       /* control type: textBox, callback function: (none) */
#define  pSERIAL_CANCEL_BUTTON            5       /* control type: pictButton, callback function: clbCancelBut */
#define  pSERIAL_SN_1                     6       /* control type: textBox, callback function: clbSnCtrl */
#define  pSERIAL_PICTURE                  7       /* control type: picture, callback function: (none) */
#define  pSERIAL_TEXTMSG                  8       /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK clbCancelBut(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clbNote(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clbOkBut(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clbSnCtrl(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
