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

#define  PANEL                            1       /* callback function: panelCB */
#define  PANEL_NUMBER                     2       /* control type: ring, callback function: clbNumber */
#define  PANEL_SN_1                       3       /* control type: string, callback function: clbSnCtrl */
#define  PANEL_SN_2                       4       /* control type: string, callback function: clbSnCtrl */
#define  PANEL_SN_3                       5       /* control type: string, callback function: clbSnCtrl */
#define  PANEL_SN_4                       6       /* control type: string, callback function: clbSnCtrl */
#define  PANEL_SN_5                       7       /* control type: string, callback function: clbSnCtrl */
#define  PANEL_SN_6                       8       /* control type: string, callback function: clbSnCtrl */
#define  PANEL_SN_7                       9       /* control type: string, callback function: clbSnCtrl */
#define  PANEL_SN_8                       10      /* control type: string, callback function: clbSnCtrl */
#define  PANEL_SN_9                       11      /* control type: string, callback function: clbSnCtrl */
#define  PANEL_SN_10                      12      /* control type: string, callback function: clbSnCtrl */
#define  PANEL_ENABLE_1                   13      /* control type: radioButton, callback function: (none) */
#define  PANEL_ENABLE_2                   14      /* control type: radioButton, callback function: (none) */
#define  PANEL_ENABLE_3                   15      /* control type: radioButton, callback function: (none) */
#define  PANEL_ENABLE_4                   16      /* control type: radioButton, callback function: (none) */
#define  PANEL_ENABLE_5                   17      /* control type: radioButton, callback function: (none) */
#define  PANEL_ENABLE_6                   18      /* control type: radioButton, callback function: (none) */
#define  PANEL_ENABLE_7                   19      /* control type: radioButton, callback function: (none) */
#define  PANEL_ENABLE_8                   20      /* control type: radioButton, callback function: (none) */
#define  PANEL_ENABLE_9                   21      /* control type: radioButton, callback function: (none) */
#define  PANEL_ENABLE_10                  22      /* control type: radioButton, callback function: (none) */
#define  PANEL_NOTE                       23      /* control type: textBox, callback function: clbNote */
#define  PANEL_OK_BUTTON                  24      /* control type: pictButton, callback function: (none) */
#define  PANEL_CANCEL_BUTTON              25      /* control type: pictButton, callback function: (none) */
#define  PANEL_LAST_BUTTON                26      /* control type: pictButton, callback function: clbLastBut */
#define  PANEL_RING_1                     27      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_2                     28      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_3                     29      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_4                     30      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_5                     31      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_6                     32      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_7                     33      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_8                     34      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_9                     35      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_10                    36      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_tbOPERATOR                 37      /* control type: textBox, callback function: (none) */
#define  PANEL_PICTURE                    38      /* control type: picture, callback function: (none) */
#define  PANEL_TEXTMSG                    39      /* control type: textMsg, callback function: (none) */

#define  PANEL2                           2       /* callback function: panelCB */
#define  PANEL2_NUMBER                    2       /* control type: ring, callback function: clbNumber */
#define  PANEL2_SN_1                      3       /* control type: string, callback function: clbSnCtrl */
#define  PANEL2_SN_2                      4       /* control type: string, callback function: clbSnCtrl */
#define  PANEL2_SN_3                      5       /* control type: string, callback function: clbSnCtrl */
#define  PANEL2_SN_4                      6       /* control type: string, callback function: clbSnCtrl */
#define  PANEL2_SN_5                      7       /* control type: string, callback function: clbSnCtrl */
#define  PANEL2_SN_6                      8       /* control type: string, callback function: clbSnCtrl */
#define  PANEL2_SN_7                      9       /* control type: string, callback function: clbSnCtrl */
#define  PANEL2_SN_8                      10      /* control type: string, callback function: clbSnCtrl */
#define  PANEL2_SN_9                      11      /* control type: string, callback function: clbSnCtrl */
#define  PANEL2_SN_10                     12      /* control type: string, callback function: clbSnCtrl */
#define  PANEL2_NOTE                      13      /* control type: textBox, callback function: clbNote */
#define  PANEL2_OK_BUTTON                 14      /* control type: command, callback function: clbOkBut */
#define  PANEL2_CANCEL_BUTTON             15      /* control type: command, callback function: clbCancelBut */
#define  PANEL2_MAIN_MESSAGE              16      /* control type: textMsg, callback function: (none) */
#define  PANEL2_PICTURE                   17      /* control type: picture, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK clbCancelBut(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clbLastBut(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clbNote(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clbNumber(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clbOkBut(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clbRingCtrl(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clbSnCtrl(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
