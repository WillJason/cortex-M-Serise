/*
*********************************************************************************************************
*
*                                        BOARD SUPPORT PACKAGE
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                        Evaluation Board
*
* Filename      : display.h
* Version       : V1.00
* Programmer(s) : HWC
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  __DISPLAY_H__
#define  __DISPLAY_H__
/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/

//#include  <stdarg.h>
#include  <stdint.h>

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/ 
#define MAIN_MENU_SIZE			5
#define MAIN_MENU_DISPLAY			"Display"
#define MAIN_MENU_THREHOLD		"Threhold"
#define MAIN_MENU_OPERATE			"Operate"
#define MAIN_MENU_OUTPUT			"Output"
#define MAIN_MENU_HELP     		"Help"

/* ¶¨Òå¼üÖµ */
#define  KEY_LEFT           0x80
#define  KEY_RIGHT          0x40
#define  KEY_OK             0x20
#define  KEY_ESC            0x10
#define  KEY_FOCUS					0x18
#define  KEY_DISP						0x14
#define  KEY_THREHOLD       0x12
#define  KEY_OPERATE				0x11
#define  KEY_OUTPUT         0x28
#define  KEY_HELP						0x24

#define  MENU_OUT_FREQ      0x01
#define  MENU_OUT_STRH      0x02
#define  MENU_OUT_QUAL      0x04
#define  MENU_OUT_TEST      0x08

#define  MENU_OPT_NOFIRE    0x01
#define  MENU_OPT_FIRE      0x02
#define  MENU_OPT_NOERR     0x04
#define  MENU_OPT_ERR       0x08
#define  MENU_OPT_SELFT     0x10
#define  MENU_OPT_RESTORE   0x20
#define  MENU_OPT_FIRERELAY 0x40
#define  MENU_OPT_ERRRELAY  0x80

#define  MENU_THD_FREQ      0x01
#define  MENU_THD_STRH      0x00
#define  MENU_OFF_FREQ      0x03
#define  MENU_OFF_STRH      0x02

#define  MENU_ADJUST_4MA    0x00
#define  MENU_ADJUST_20MA   0x01
#define  MENU_NOFIRE_DELAY  0x02
#define  MENU_DEV_ADDR      0x03

#define MENU_FREQ_MODE			0x00
#define MENU_FREQ_GAIN			0x01
#define MENU_PARM_A					0x02
#define MENU_PARM_B					0x03

//#define GUI_DEBUG  
#ifdef GUI_DEBUG
	#define GUI_TRACE     printk
#else
	#define GUI_TRACE			
#endif

/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/
typedef struct _menu_text{
	uint16_t x_start;
	uint16_t y_start;
	uint16_t x_stop;
	uint16_t y_stop;
	int16_t  data;
	const struct _menu_text *netx_text;
	void (*pfun)(void);
	uint8_t my_NO;
	uint8_t *pname;
}MENU_TEXT;
typedef struct _menu_button{
	uint16_t x_start;
	uint16_t y_start;
	uint16_t x_stop;
	uint16_t y_stop;
	int16_t  data;
	const struct _menu_button *netx_button;
	void (*pfun)(uint8_t);
	uint8_t my_NO;
	uint8_t *pname;
}MENU_BUTTON;

typedef struct _menu_item{
	uint16_t x_start;
	uint16_t y_start;
	uint16_t x_stop;
	uint16_t y_stop;
	const MENU_TEXT *txt;
	const MENU_BUTTON *btn;
	const struct _menu_item *next_item;
	void (*pfun)(uint8_t);
	uint8_t my_NO;
	uint8_t *pname;
}MENU_ITEM;

typedef struct _menu_class{
	uint16_t x_start;
	uint16_t y_start;
	uint16_t x_stop;
	uint16_t y_stop;
	const MENU_ITEM *item;
	const struct _menu_class *next_class;
	void (*pfun)(uint8_t);
	uint8_t my_NO;
	uint8_t *pname;
}MENU_CLASS;

typedef struct {
	const MENU_CLASS *class_pos;
	const MENU_ITEM  *item_pos;
  const MENU_TEXT *txt_pos;
	const MENU_BUTTON *btn_pos;	
}MENU_POS;

typedef struct{
	uint8_t class_index;
	uint8_t item_index;
	uint8_t btn_index;
	uint8_t txt_index;
}MENU_INDEX;

uint8_t GUI_Proc(uint32_t pos);
void GUI_Show_Graph(void);
void GUI_Env_Set(uint8_t strh,uint8_t freq,uint8_t qual);
void GUI_Fpu_State(uint8_t state);
void GUI_Sensor_State(uint8_t state);
void GUI_ThreholdTemp_Set(uint8_t s,uint8_t f);
void  GUI_Init(void);
uint8_t GUI_OutputType_Get(void);
void GUI_OutputType_Set(uint8_t type);
void GUI_Threhold_Set(uint8_t s,uint8_t f);
void GUI_Threhold_Get(uint8_t *s,uint8_t *f);
void GUI_Offset_Set(uint8_t s,uint8_t f);
void GUI_Offset_Get(uint8_t *s,uint8_t *f);
void GUI_Relay_Set(uint8_t fire,uint8_t err);
void GUI_Relay_Restore(uint8_t dat);
void GUI_Relay_Get(uint8_t *fire,uint8_t *err);
void GUI_FreqMode_Restore(uint8_t mode,uint8_t gain);
void GUI_ParamAB_Restore(uint8_t pA,uint8_t pB);
void GUI_DelayTriger_Set(uint8_t dly);
uint8_t GUI_DelayTriger_Get(void);
void GUI_DisType_Set(uint8_t type);
uint8_t GUI_DisType_Get(void);
/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/


#endif       
