/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2013. All Rights Reserved.          */
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
#define  PANEL_PART_1                     3       /* control type: string, callback function: clbInputCtrl */
#define  PANEL_SERIAL_1                   4       /* control type: string, callback function: clbInputCtrl */
#define  PANEL_ENABLE_1                   5       /* control type: radioButton, callback function: (none) */
#define  PANEL_RMA_1                      6       /* control type: radioButton, callback function: (none) */
#define  PANEL_PART_2                     7       /* control type: string, callback function: clbInputCtrl */
#define  PANEL_SERIAL_2                   8       /* control type: string, callback function: clbInputCtrl */
#define  PANEL_ENABLE_2                   9       /* control type: radioButton, callback function: (none) */
#define  PANEL_RMA_2                      10      /* control type: radioButton, callback function: (none) */
#define  PANEL_PART_3                     11      /* control type: string, callback function: clbInputCtrl */
#define  PANEL_SERIAL_3                   12      /* control type: string, callback function: clbInputCtrl */
#define  PANEL_ENABLE_3                   13      /* control type: radioButton, callback function: (none) */
#define  PANEL_RMA_3                      14      /* control type: radioButton, callback function: (none) */
#define  PANEL_PART_4                     15      /* control type: string, callback function: clbInputCtrl */
#define  PANEL_SERIAL_4                   16      /* control type: string, callback function: clbInputCtrl */
#define  PANEL_ENABLE_4                   17      /* control type: radioButton, callback function: (none) */
#define  PANEL_RMA_4                      18      /* control type: radioButton, callback function: (none) */
#define  PANEL_PART_5                     19      /* control type: string, callback function: clbInputCtrl */
#define  PANEL_SERIAL_5                   20      /* control type: string, callback function: clbInputCtrl */
#define  PANEL_ENABLE_5                   21      /* control type: radioButton, callback function: (none) */
#define  PANEL_RMA_5                      22      /* control type: radioButton, callback function: (none) */
#define  PANEL_PART_6                     23      /* control type: string, callback function: clbInputCtrl */
#define  PANEL_SERIAL_6                   24      /* control type: string, callback function: clbInputCtrl */
#define  PANEL_ENABLE_6                   25      /* control type: radioButton, callback function: (none) */
#define  PANEL_RMA_6                      26      /* control type: radioButton, callback function: (none) */
#define  PANEL_PART_7                     27      /* control type: string, callback function: clbInputCtrl */
#define  PANEL_SERIAL_7                   28      /* control type: string, callback function: clbInputCtrl */
#define  PANEL_ENABLE_7                   29      /* control type: radioButton, callback function: (none) */
#define  PANEL_RMA_7                      30      /* control type: radioButton, callback function: (none) */
#define  PANEL_PART_8                     31      /* control type: string, callback function: clbInputCtrl */
#define  PANEL_SERIAL_8                   32      /* control type: string, callback function: clbInputCtrl */
#define  PANEL_ENABLE_8                   33      /* control type: radioButton, callback function: (none) */
#define  PANEL_RMA_8                      34      /* control type: radioButton, callback function: (none) */
#define  PANEL_PART_9                     35      /* control type: string, callback function: clbInputCtrl */
#define  PANEL_SERIAL_9                   36      /* control type: string, callback function: clbInputCtrl */
#define  PANEL_ENABLE_9                   37      /* control type: radioButton, callback function: (none) */
#define  PANEL_RMA_9                      38      /* control type: radioButton, callback function: (none) */
#define  PANEL_PART_10                    39      /* control type: string, callback function: clbInputCtrl */
#define  PANEL_SERIAL_10                  40      /* control type: string, callback function: clbInputCtrl */
#define  PANEL_ENABLE_10                  41      /* control type: radioButton, callback function: (none) */
#define  PANEL_RMA_10                     42      /* control type: radioButton, callback function: (none) */
#define  PANEL_NOTE                       43      /* control type: textBox, callback function: clbNote */
#define  PANEL_RMA_NUM                    44      /* control type: textBox, callback function: clbRmaNum */
#define  PANEL_WORK_NUM                   45      /* control type: textBox, callback function: clbWorkNum */
#define  PANEL_OK_BUTTON                  46      /* control type: pictButton, callback function: clbOkButton */
#define  PANEL_CANCEL_BUTTON              47      /* control type: pictButton, callback function: (none) */
#define  PANEL_RING_PN_10                 48      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_PN_9                  49      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_PN_8                  50      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_PN_7                  51      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_PN_6                  52      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_PN_5                  53      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_PN_4                  54      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_PN_3                  55      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_PN_2                  56      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_PN_1                  57      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_LAST_BUTTON                58      /* control type: pictButton, callback function: clbLastBut */
#define  PANEL_RING_SN_1                  59      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_SN_2                  60      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_TEXTMSG_3                  61      /* control type: textMsg, callback function: (none) */
#define  PANEL_RING_SN_3                  62      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_SN_4                  63      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_SN_5                  64      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_SN_6                  65      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_SN_7                  66      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_SN_8                  67      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_SN_9                  68      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_RING_SN_10                 69      /* control type: ring, callback function: clbRingCtrl */
#define  PANEL_tbOPERATOR                 70      /* control type: textBox, callback function: (none) */
#define  PANEL_PICTURE                    71      /* control type: picture, callback function: (none) */
#define  PANEL_TEXTMSG_5                  72      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_4                  73      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_2                  74      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG                    75      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK clbInputCtrl(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clbLastBut(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clbNote(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clbNumber(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clbOkButton(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clbRingCtrl(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clbRmaNum(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clbWorkNum(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
