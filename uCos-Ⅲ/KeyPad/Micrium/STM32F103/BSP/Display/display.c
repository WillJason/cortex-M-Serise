/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#include "includes.h"
#include  "display.h"
//#include  <stddef.h>

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/
static void CallBack_fire_force(void);
static void CallBack_nofire_force(void);
static void CallBack_frelay_force(void);
static void CallBack_error_force(void);
static void CallBack_noerr_force(void);
static void CallBack_erelay_force(void);
static void CallBack_reset_para(void);
static void CallBack_self_test(void);
static void CallBack_threhold_freq(void);
static void CallBack_threhold_strength(void);
static void CallBack_offset_freq(void);
static void CallBack_offset_strength(void);
static void CallBack_adjust_4mA(void);
static void CallBack_adjust_20mA(void);
static void CallBack_nofire_delay(void);
static void CallBack_dev_addr(void);
static void CallBack_output_add(void);
static void CallBack_output_minus(void);
static void CallBack_output_ok(void);
static void CallBack_add(void);
static void CallBack_minus(void);
static void CallBack_ok(void);
static void CallBack_out_freq(void);
static void CallBack_out_quality(void);
static void CallBack_out_strength(void);
static void CallBack_out_test(void);
static void CallBack_change(uint8_t img);
static void CallBack_opt3_add(void);
static void CallBack_opt3_minus(void);
static void CallBack_opt3_ok(void);
static void CallBack_freq_mode(void);
static void CallBack_freq_gain(void);
static void CallBack_param_A(void);
static void CallBack_param_B(void);

/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/

 MENU_BUTTON   btn_fire_force ={110,96,138,124,0,NULL,CallBack_fire_force,0,"强制有火"}; 
 MENU_BUTTON	 btn_nofire_force ={110,136,138,164,0,&btn_fire_force,CallBack_nofire_force,0,"强制无火"};
 MENU_BUTTON	 btn_error_force ={260,96,288,124,0,&btn_nofire_force,CallBack_error_force,0,"强制故障"};
 MENU_BUTTON	 btn_noerr_force ={260,136,288,164,0,&btn_error_force,CallBack_noerr_force,0,"强制无障"};
 MENU_BUTTON	 btn_reset_para ={260,96,288,124,0,NULL,CallBack_reset_para,0,"恢复初值"};
 MENU_BUTTON	 btn_self_test ={110,96,138,124,0,&btn_reset_para,CallBack_self_test,0,"执行自检"};
 MENU_BUTTON	 btn_frelay_force ={110,136,138,164,0,&btn_self_test,CallBack_frelay_force,0,"火焰NB/A"};
 MENU_BUTTON	 btn_erelay_force ={260,136,288,164,0,&btn_frelay_force,CallBack_erelay_force,0,"故障NB/A"};
 
 MENU_BUTTON   btn_out_freq ={110,96,138,124,0,NULL,CallBack_out_freq,0,"频率输出"}; 
 MENU_BUTTON	 btn_out_quality ={110,136,138,164,0,&btn_out_freq,CallBack_out_quality,0,"质量输出"};
 MENU_BUTTON	 btn_out_strength ={260,96,288,124,0,&btn_out_quality,CallBack_out_strength,0,"强度输出"};
 MENU_BUTTON	 btn_out_test ={260,136,288,164,0,&btn_out_strength,CallBack_out_test,0,"测试输出"};

const MENU_BUTTON	 btn_left = {54,152,114,182,0,NULL,CallBack_add,0,"数值自加"};
const MENU_BUTTON	 btn_right ={136,152,196,182,0,&btn_left,CallBack_minus,0,"数值自减"};
const MENU_BUTTON	 btn_ok ={216,152,276,182,0,&btn_right,CallBack_ok,0,"数值确定"};
const MENU_BUTTON	 btn_add = {75,154,110,187,0,NULL,CallBack_output_add,0,"数值自加"};
const MENU_BUTTON	 btn_minus ={142,154,178,187,0,&btn_add,CallBack_output_minus,0,"数值自减"};
const MENU_BUTTON	 btn_enter ={210,154,245,187,0,&btn_minus,CallBack_output_ok,0,"数值确定"};
const MENU_BUTTON	 btn_opt3_add = {75,154,110,187,0,NULL,CallBack_opt3_add,0,"数值自加"};
const MENU_BUTTON	 btn_opt3_minus ={142,154,178,187,0,&btn_opt3_add,CallBack_opt3_minus,0,"数值自减"};
const MENU_BUTTON	 btn_opt3_enter ={210,154,245,187,0,&btn_opt3_minus,CallBack_opt3_ok,0,"数值确定"};

 MENU_TEXT	 	text_sthrehold ={94,60,156,92,0,NULL,CallBack_threhold_strength,0,"强度阀值"};
 MENU_TEXT	 	text_fthrehold ={244,60,304,92,0,&text_sthrehold,CallBack_threhold_freq,0,"频率阀值"};
 MENU_TEXT	 	text_soffset ={94,106,156,136,0,&text_fthrehold,CallBack_offset_strength,0,"强度回差"};
 MENU_TEXT	 	text_foffset ={244,106,304,136,0,&text_soffset,CallBack_offset_freq,0,"频率回差"};
 MENU_TEXT	 	text_adjust4mA ={75,78,138,111,0,NULL,CallBack_adjust_4mA,0,"4mA调零"};
 MENU_TEXT	 	text_adjust20mA ={182,78,245,111,0,&text_adjust4mA,CallBack_adjust_20mA,0,"20mA调零"};
 MENU_TEXT	 	text_delaynofire ={75,116,138,149,0,&text_adjust20mA,CallBack_nofire_delay,0,"无火延迟"};
 MENU_TEXT	 	text_devaddr ={182,116,245,149,0,&text_delaynofire,CallBack_dev_addr,0,"设备地址"};
 MENU_TEXT	 	text_opt3_fmode ={75,78,138,111,0,NULL,CallBack_freq_mode,0,"频段模式"};
 MENU_TEXT	 	text_opt3_fgain ={182,78,245,111,0,&text_opt3_fmode,CallBack_freq_gain,0,"频率增益"};
 MENU_TEXT	 	text_opt3_parA ={75,116,138,149,0,&text_opt3_fgain,CallBack_param_A,0,"参数A"};
 MENU_TEXT	 	text_opt3_parB ={182,116,245,149,0,&text_opt3_parA,CallBack_param_B,0,"参数B"};

const MENU_ITEM   item_threhold_opt3={166,46,246,72,NULL,NULL,NULL,CallBack_change,0,"选项三"};
const MENU_ITEM   item_threhold_opt2={86,46,166,72,NULL,NULL,&item_threhold_opt3,CallBack_change,0,"选项二"};
const MENU_ITEM   item_threhold_opt1={6,46,86,72,&text_foffset,&btn_ok,NULL,CallBack_change,0,"选项一"};

const MENU_ITEM   item_operate_opt3={166,46,246,72,&text_opt3_parB,&btn_opt3_enter,NULL,CallBack_change,0,"选项三"};
const MENU_ITEM   item_operate_opt2={86,46,166,72,NULL,&btn_erelay_force,&item_operate_opt3,CallBack_change,0,"选项二"};
const MENU_ITEM   item_operate_opt1={6,46,86,72,NULL,&btn_noerr_force,&item_operate_opt2,CallBack_change,0,"选项一"};

const MENU_ITEM   item_output_opt3={166,46,246,72,NULL,NULL,NULL,CallBack_change,0,"选项三"};
const MENU_ITEM   item_output_opt2={86,46,166,72,&text_devaddr,&btn_enter,NULL,CallBack_change,0,"选项二"};
const MENU_ITEM   item_output_opt1={6,46,86,72,NULL,&btn_out_test,&item_output_opt2,CallBack_change,0,"选项一"};
 
const MENU_CLASS   class_display ={6,206,66,234,NULL,NULL,CallBack_change,0,"显示"};
const MENU_CLASS   class_threhold ={68,206,126,234,&item_threhold_opt1,NULL,CallBack_change,0,"阀值"}; 
const MENU_CLASS   class_operate ={132,206,190,234,&item_operate_opt1,NULL,CallBack_change,0,"操作"};
const MENU_CLASS   class_output ={194,206,252,234,&item_output_opt1,NULL,CallBack_change,0,"输出"};
const MENU_CLASS   class_help ={256,206,316,234,NULL,NULL,CallBack_change,0,"帮助"}; 

const MENU_CLASS *menu_root[MAIN_MENU_SIZE]={&class_display,&class_threhold,&class_operate,&class_output,&class_help};
//static uint16_t Main_Menu_State = KEY_DISP;
static MENU_POS Main_Menu_Pos={&class_display,NULL,NULL,NULL};
static uint8_t Menu_Index[]={1,0,0,0}; 		//菜单索引
static uint8_t Menu_Output=MENU_OUT_STRH;  //输出类型
static uint8_t NofireTrigerTime=1;
static uint8_t RelayOutputType=0x37;
static uint8_t Menu_Operate=0x00;
static int8_t Menu_Threhold[4]={0x00,0x00,0x00,0x00};
static int8_t Threhold_Temp[4]={0};
static uint8_t Menu_Threhold_Index=0;
static int8_t Menu_Output_Text[4]={0x00,0x00,0x00,0x00};
static int8_t Menu_Operate_Text[4]={0,0,0,0};
static int8_t Output_Text_Temp[4]={0};
static uint8_t Menu_Output_Text_Index=0;
static uint8_t Menu_OPT_Text_Index=0;
static uint8_t Strength=0;
static uint8_t Frequecy=0;
static uint8_t Quality=0;
static uint8_t Fpu_State=DEF_FALSE;
static uint8_t Sensor_State=DEF_TRUE;

static uint16_t Strength_Xpos=0,Strength_Xpos_Old=0;
static uint16_t Freq_Xpos=0,Freq_Xpos_Old=0;
static uint16_t Qual_Xpos=0,Qual_Xpos_Old=0;
/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/
static const uint8_t GUI_Cmd_Set_Color[]={0xfd,0x05,0x00,0x04,0x93,0xA0,0x00,0x00,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Cmd_BackLight_On[]={0xfd,0x0A,0x00,0x00,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Cmd_BackLight_Off[]={0xfd,0x09,0x00,0x00,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Cmd_Set_String[]={0xfd,0x10,0x00,0x07,0x00,0xF6,0x00,0x9C,0x33,0x34,0x35,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Cmd_Image_Cut[]={0xfd,0x37,0x00,0x0e,0x00,0x00,0x00,0xc8,0x0a,0x00,0x00,0x00,0xc8,0x01,0x40,0x00,0x28,0x00,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Cmd_Touch_Mode[]={0xfd,0x52,0x00,0x01,0x02,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Cmd_Draw_Rect[]={0xfd,0x27,0x00,0x09,0x01,0x00,0xE0,0x00,0x3C,0x00,0xF0,0x00,0x84,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Cmd_Image_Disp[]={0xfd,0x30,0x00,0x01,0x01,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Cmd_Fill_Circle[]={0xfd,0x26,0x00,0x06,0x01,0x00,0x00,0x00,0x00,0x00,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Cmd_Draw_Circle[]={0xfd,0x26,0x00,0x12,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,
																						0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Cmd_Draw_Line[]={0xfd,0x23,0x00,0x08,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Cmd_Bar_Cut[]={0xfd,0x37,0x00,0x0e,0x00,0xD6,0x00,0x2C,0x01,0x00,0xD6,0x00,0x2C,0x00,0x68,0x00,0x9A,0x00,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Cmd_BarS_Cut[]={0xfd,0x37,0x00,0x0e,0x00,0xE0,0x00,0x2C,0x01,0x00,0xE0,0x00,0x2C,0x00,0x10,0x00,0x58,0x00,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Cmd_BarF_Cut[]={0xfd,0x37,0x00,0x0e,0x01,0x00,0x00,0x2C,0x01,0x01,0x00,0x00,0x2C,0x00,0x10,0x00,0x58,0x00,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Cmd_BarQ_Cut[]={0xfd,0x37,0x00,0x0e,0x01,0x20,0x00,0x2C,0x01,0x01,0x20,0x00,0x2C,0x00,0x10,0x00,0x58,0x00,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Cmd_BarN_Cut[]={0xfd,0x37,0x00,0x0e,0x00,0xF2,0x00,0x9A,0x01,0x00,0xF2,0x00,0x9A,0x00,0x42,0x00,0x28,0x00,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Cmd_Fire_Cut[]={0xfd,0x37,0x00,0x0e,0x00,0x82,0x00,0x3C,0x01,0x00,0x82,0x00,0x3C,0x00,0x4A,0x00,0x32,0x00,0xdd,0xcc,0xbb,0xaa};	
static const uint8_t GUI_Cmd_Err_Cut[]={0xfd,0x37,0x00,0x0e,0x00,0x82,0x00,0x82,0x01,0x00,0x82,0x00,0x82,0x00,0x4A,0x00,0x32,0x00,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Cmd_Strt_Cut[]={0xfd,0x37,0x00,0x0e,0x00,0x08,0x00,0x2C,0x01,0x00,0x08,0x00,0x2C,0x00,0x5A,0x00,0x31,0x00,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Cmd_Freq_Cut[]={0xfd,0x37,0x00,0x0e,0x00,0x08,0x00,0x60,0x01,0x00,0x08,0x00,0x60,0x00,0x5A,0x00,0x2C,0x00,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Cmd_Qual_Cut[]={0xfd,0x37,0x00,0x0e,0x00,0x08,0x00,0x8F,0x01,0x00,0x08,0x00,0x8F,0x00,0x5A,0x00,0x30,0x00,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Str_S[]={0xfd,0x12,0x00,0x05,0x00,0x76,0x00,0x3D,0x49,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Str_F[]={0xfd,0x12,0x00,0x05,0x00,0x76,0x00,0x60,0x46,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Str_T[]={0xfd,0x12,0x00,0x05,0x00,0x76,0x00,0x84,0x54,0xdd,0xcc,0xbb,0xaa};
static const uint8_t GUI_Str_U[]={0xfd,0x12,0x00,0x05,0x00,0x76,0x00,0xA6,0x55,0xdd,0xcc,0xbb,0xaa};
/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void GUI_Light_ON(void){
  USART2->DR = 0xFD;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x0B;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x00;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x01;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xFF;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xDD;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xCC;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xBB;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xAA;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
}
void GUI_Light_OFF(void){
  USART2->DR = 0xFD;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x0B;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x00;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x01;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x00;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xDD;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xCC;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xBB;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xAA;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
}
/****************************************************************************
* 名称:hex2str()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static uint32_t hex2str(uint8_t idat){
	uint32_t dat;
	dat=idat/100 + '0';
	dat<<=8;
	dat|=idat%100/10+'0';
	dat<<=8;
	dat|=idat%10+'0';
	return dat;
}
/****************************************************************************
* 名称:fill_rectang()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void fill_rectang(uint16_t xs,uint16_t ys,uint16_t xp,uint16_t yp, uint8_t type){
	USART2->DR = 0xFD;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x27;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x00;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x09;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = type;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = xs>>8;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = xs;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = ys>>8;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = ys;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = xp>>8;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = xp;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = yp>>8;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = yp;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xDD;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xCC;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xBB;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xAA;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
}
/****************************************************************************
* 名称:get_color()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void get_color(uint16_t x,uint16_t y){
	USART2->DR = 0xFD;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x07;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x00;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x04;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = x>>8;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = x;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = y>>8;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = y;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xDD;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xCC;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xBB;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xAA;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
}
/****************************************************************************
* 名称:set_color()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void set_color(uint16_t color){
	USART2->DR = 0xFD;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x05;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x00;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x04;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = color>>8;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = color;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xDD;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xCC;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xBB;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xAA;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
}
/****************************************************************************
* 名称:fill_circle()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void fill_circle(uint16_t x,uint16_t y,uint8_t type,uint8_t r){
	USART2->DR = 0xFD;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x26;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x00;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x06;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = type;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = x>>8;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = x;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = y>>8;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = y;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = r;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xDD;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xCC;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xBB;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xAA;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
}
/****************************************************************************
* 名称:fill_num()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void fill_num(uint16_t x,uint16_t y,uint8_t type,uint8_t data ){
	uint32_t dat;
	USART2->DR = 0xFD;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = type;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x00;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x07;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = x>>8;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = x;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = y>>8;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = y;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	dat=hex2str(data);
	USART2->DR = dat>>16;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = (uint8_t)(dat>>8);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = (uint8_t)(dat);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xDD;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xCC;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xBB;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xAA;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
}
/****************************************************************************
* 名称:fill_num()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void fill_float(uint16_t x,uint16_t y,uint8_t type,uint8_t data ){
	uint32_t dat;
	USART2->DR = 0xFD;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = type;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x00;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0x07;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = x>>8;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = x;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = y>>8;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = y;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = data/2 +'0';
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = '.';
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = (data%2) == 0?'0':'5';
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xDD;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xCC;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xBB;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART2->DR = 0xAA;
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
}
/****************************************************************************
* 名称:fill_line()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void fill_line(uint16_t xs,uint16_t ys,uint16_t xp,uint16_t yp){
 uint8_t i;
	for(i=0;i<sizeof(GUI_Cmd_Draw_Line);i++){
		switch(i){
			case 4:
				USART2->DR = xs>>8;
				break;
			case 5:
				USART2->DR = xs;
				break;
			case 6:
				USART2->DR =(ys>>8);
				break;
			case 7:
				USART2->DR =(ys);
				break;
			case 8:
				USART2->DR =(xp>>8);
				break;
			case 9:
				USART2->DR =(xp);
				break;
			case 10:
				USART2->DR =(yp>>8);
				break;
			case 11:
				USART2->DR =(yp);
				break;
			default:
				USART2->DR =GUI_Cmd_Draw_Line[i];
				break;
		}
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	}
}
/****************************************************************************
* 名称:fill_bar_graph()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void fill_bar_graph(uint8_t s,uint8_t f,uint8_t q){
  uint8_t i;
	uint16_t color[4]={0xF800,0x93A0,0x07E0};
  for(i=0;i<sizeof(GUI_Cmd_BarS_Cut);i++){
		USART2->DR = GUI_Cmd_BarS_Cut[i];
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	}
  set_color(color[s/34]);
  fill_rectang(224,s>87?45:132-s,239,132,1);
	for(i=0;i<sizeof(GUI_Cmd_BarF_Cut);i++){
		USART2->DR = GUI_Cmd_BarF_Cut[i];
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	}
  set_color(color[f/34]);
  fill_rectang(256,f>87?45:132-f,271,132,1);
	for(i=0;i<sizeof(GUI_Cmd_BarQ_Cut);i++){
		USART2->DR = GUI_Cmd_BarQ_Cut[i];
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	}
  set_color(color[q/34]);
  fill_rectang(288,q>87?45:132-q,303,132,1);
	for(i=0;i<sizeof(GUI_Cmd_BarN_Cut);i++){
		USART2->DR = GUI_Cmd_BarN_Cut[i];
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	}
  set_color(0xFFFF);
  fill_num(244,156,0x10,s);
  fill_num(244,170,0x10,f);
  fill_num(244,184,0x10,q);
  fill_num(286,156,0x10,Menu_Threhold[0]);
  fill_num(286,170,0x10,Menu_Threhold[1]);
  fill_num(286,184,0x10,10); 	
}
/****************************************************************************
* 名称:fill_fire_graph()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void fill_fire_graph(uint8_t s,uint8_t f){
	uint8_t i;
	uint16_t color[4]={0xF800,0x93A0,0x07E0};
  for(i=0;i<sizeof(GUI_Cmd_Fire_Cut);i++){
		USART2->DR = GUI_Cmd_Fire_Cut[i];
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	}
	set_color(0xFFFF);
#if 0
	fill_line(166,60,166,110);
	set_color(s>=Menu_Threhold[0]?0xF800:0x07E0);
	fill_line(130,68,166,68);
	fill_line(166,68,166,85);
	set_color(f>=Menu_Threhold[1]?0xF800:0x07E0);
	fill_line(130,102,166,102);
	fill_line(166,102,166,85);
	if(s<Menu_Threhold[0] || f<Menu_Threhold[1])
		set_color(0x07E0);
	else
		set_color(0xF800);
	fill_line(166,85,190,85);
#else
	fill_line(160,60,160,110);
	set_color(s>=Menu_Threhold[0]?0xF800:0x07E0);
	fill_line(130,68,160,68);
	fill_line(160,68,160,85);
	set_color(f>=Menu_Threhold[1]?0xF800:0x07E0);
	fill_line(130,102,160,102);
	fill_line(160,102,160,85);
	if(s<Menu_Threhold[0] || f<Menu_Threhold[1])
		set_color(0x07E0);
	else
		set_color(0xF800);
	fill_rectang(160,79,166,91,1);
	fill_line(166,85,190,85);
#endif
	fill_circle(190,85,1,10);
	set_color(0xFFFF);
	fill_circle(190,85,0,10);
	fill_circle(190,85,0,9);
}
/****************************************************************************
* 名称:fill_err_graph()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void fill_err_graph(uint8_t fpu,uint8_t sensor){
	uint8_t i;
	uint16_t color[4]={0xF800,0x93A0,0x07E0};
  for(i=0;i<sizeof(GUI_Cmd_Err_Cut);i++){
		USART2->DR = GUI_Cmd_Err_Cut[i];
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	}
#if 0
	set_color(0xFFFF);
	fill_line(166,130,166,180);
	set_color(sensor==DEF_TRUE?0x07E0:0xF800);
	fill_line(130,138,166,138);
	fill_line(166,138,166,155);
	set_color(fpu==DEF_TRUE?0x07E0:0xF800);
	fill_line(130,172,166,172);
	fill_line(166,172,166,155);
	if(sensor!=DEF_TRUE || fpu!=DEF_TRUE)
		set_color(0xF800);
	else
		set_color(0x07E0);
	fill_line(166,155,190,155);
#else
	set_color(0xFFFF);
	fill_line(160,130,160,180);
	set_color(sensor==DEF_TRUE?0x07E0:0xF800);
	fill_line(130,138,160,138);
	fill_line(160,138,160,155);
	set_color(fpu==DEF_TRUE?0x07E0:0xF800);
	fill_line(130,172,160,172);
	fill_line(160,172,160,155);
	if(sensor!=DEF_TRUE || fpu!=DEF_TRUE)
		set_color(0xF800);
	else
		set_color(0x07E0);
	fill_circle(164,155,1,4);
	fill_line(166,155,190,155);
#endif
	fill_circle(190,155,1,10);
	set_color(0xFFFF);
	fill_circle(190,155,0,10);
	fill_circle(190,155,0,9);
}
/****************************************************************************
* 名称:fill_strength_graph()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static fill_strength_graph(uint8_t strength){
	uint8_t i;
	set_color(0xFFFF);
	if(Strength_Xpos==90){
		for(i=0;i<sizeof(GUI_Cmd_Strt_Cut);i++){
			USART2->DR = GUI_Cmd_Strt_Cut[i];
			while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	  }
		Strength_Xpos=0;
	}
	if(Strength_Xpos>0){
		fill_line(7+Strength_Xpos,Strength_Xpos_Old,8+Strength_Xpos,strength>90?47:92-strength/2);
	}
	Strength_Xpos++;
	Strength_Xpos_Old=strength>90?47:92-strength/2;
}
/****************************************************************************
* 名称:fill_freq_graph()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static fill_freq_graph(uint8_t freq){
	uint8_t i;
	set_color(0xFFFF);
	if(Freq_Xpos==90){
		for(i=0;i<sizeof(GUI_Cmd_Freq_Cut);i++){
			USART2->DR = GUI_Cmd_Freq_Cut[i];
			while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	  }
		Freq_Xpos=0;
	}
	if(Freq_Xpos>0){
		fill_line(7+Freq_Xpos,Freq_Xpos_Old,8+Freq_Xpos,freq>80?96:139-freq/2);
	}
	Freq_Xpos++;
	Freq_Xpos_Old=freq>80?96:139-freq/2;
}
/****************************************************************************
* 名称:fill_qual_graph()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static fill_qual_graph(uint8_t qual){
	uint8_t i;
	set_color(0xFFFF);
	if(Qual_Xpos==90){
		for(i=0;i<sizeof(GUI_Cmd_Qual_Cut);i++){
			USART2->DR = GUI_Cmd_Qual_Cut[i];
			while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	  }
		Qual_Xpos=0;
	}
	if(Qual_Xpos>0){
		fill_line(7+Qual_Xpos,Qual_Xpos_Old,8+Qual_Xpos,qual>95?143:190-qual/2);
	}
	Qual_Xpos++;
	Qual_Xpos_Old=qual>95?143:190-qual/2;
}
/****************************************************************************
* 名称:fill_intent()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void fill_intent(uint8_t img){
	uint8_t i;
	switch(img){
		case 1:
			set_color(0xFFFF);
			for(i=0;i<sizeof(GUI_Str_S);i++){
				USART2->DR = GUI_Str_S[i];
				while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
			}
			for(i=0;i<sizeof(GUI_Str_F);i++){
				USART2->DR = GUI_Str_F[i];
				while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
			}
			for(i=0;i<sizeof(GUI_Str_T);i++){
				USART2->DR = GUI_Str_T[i];
				while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
			}
			for(i=0;i<sizeof(GUI_Str_U);i++){
				USART2->DR = GUI_Str_U[i];
				while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
			}
			break;
		case 2:
			set_color(0xF800);
		  if(Menu_Threhold_Index == 0)
				fill_rectang(94,60,156,92,0);
			if(Menu_Threhold_Index == 1)
				fill_rectang(244,60,304,92,0);
			if(Menu_Threhold_Index == 2)
				fill_rectang(94,106,156,136,0);
			if(Menu_Threhold_Index == 3)
				fill_rectang(244,106,304,136,0);
			set_color(0xFFFF);
			fill_num(98,62,0x13,Menu_Threhold[0]);
		  fill_num(248,62,0x13,Menu_Threhold[1]);
			fill_num(98,108,0x13,Menu_Threhold[2]);
			fill_num(248,108,0x13,Menu_Threhold[3]);
			break;
		case 3:
			break;
		case 4:
			set_color(0xF800);
      if(Menu_Operate&MENU_OPT_FIRERELAY)		
				fill_circle(123,149,0x01,8);	
			if(Menu_Operate&MENU_OPT_ERRRELAY)		
				fill_circle(273,149,0x01,8);
			break;
		case 5:
			set_color(0xF800);
      if(Menu_Output&MENU_OUT_FREQ)		
				fill_circle(123,109,0x01,8);
			if(Menu_Output&MENU_OUT_STRH)		
				fill_circle(273,109,0x01,8);
			if(Menu_Output&MENU_OUT_QUAL)		
				fill_circle(123,149,0x01,8);
			if(Menu_Output&MENU_OUT_TEST)		
				fill_circle(273,149,0x01,8);
			break;
		case 6:
			break;
		case 12:
			set_color(0xF800);
			if(Menu_Output_Text_Index == 0)
				fill_rectang(75,78,137,110,0);
			if(Menu_Output_Text_Index == 1)
				fill_rectang(182,78,244,110,0);
			if(Menu_Output_Text_Index == 2)
				fill_rectang(75,116,137,148,0);
			if(Menu_Output_Text_Index == 3)
				fill_rectang(182,116,244,148,0);
			set_color(0xFFFF);
			fill_num(81,80,0x13,Menu_Output_Text[0]);
		  fill_num(188,80,0x13,Menu_Output_Text[1]);
			fill_float(81,118,0x13,Menu_Output_Text[2]%16);
			fill_num(188,118,0x13,Menu_Output_Text[3]);
			break;
		case 13:
			set_color(0xF800);
			if(Menu_OPT_Text_Index == 0)
				fill_rectang(75,78,137,110,0);
			if(Menu_OPT_Text_Index == 1)
				fill_rectang(182,78,244,110,0);
			if(Menu_OPT_Text_Index == 2)
				fill_rectang(75,116,137,148,0);
			if(Menu_OPT_Text_Index == 3)
				fill_rectang(182,116,244,148,0);
			set_color(0xFFFF);
			fill_num(81,80,0x13,Menu_Operate_Text[0]);
		  fill_num(188,80,0x13,Menu_Operate_Text[1]);
			fill_num(81,118,0x13,Menu_Operate_Text[2]);
			fill_num(188,118,0x13,Menu_Operate_Text[3]);
			break;
		default :
			break;
	}
}
/****************************************************************************
* 名称:CallBack_out_freq()
* 功能:输出频率
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_out_freq(void){
	set_color(0xFFFF);
	if(Menu_Output&MENU_OUT_FREQ)		
		fill_circle(123,109,0x01,8);
	if(Menu_Output&MENU_OUT_STRH)		
		fill_circle(273,109,0x01,8);
	if(Menu_Output&MENU_OUT_QUAL)		
		fill_circle(123,149,0x01,8);
	if(Menu_Output&MENU_OUT_TEST)		
		fill_circle(273,149,0x01,8);
	Menu_Output = MENU_OUT_FREQ;
	set_color(0xF800);
	fill_circle(123,109,0x01,8);
	protocol_fun[PROTOCOL_INDEX_OUT_MODE_T](MENU_OUT_FREQ,MENU_OUT_FREQ);
}
/****************************************************************************
* 名称:CallBack_out_quality()
* 功能:输出质量
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_out_quality(void){
	set_color(0xFFFF);
	if(Menu_Output&MENU_OUT_FREQ)		
		fill_circle(123,109,0x01,8);
	if(Menu_Output&MENU_OUT_STRH)		
		fill_circle(273,109,0x01,8);
	if(Menu_Output&MENU_OUT_QUAL)		
		fill_circle(123,149,0x01,8);
	if(Menu_Output&MENU_OUT_TEST)		
		fill_circle(273,149,0x01,8);
	Menu_Output = MENU_OUT_QUAL;
	set_color(0xF800);
	fill_circle(123,149,0x01,8);
  protocol_fun[PROTOCOL_INDEX_OUT_MODE_T](MENU_OUT_QUAL,MENU_OUT_QUAL);
}
/****************************************************************************
* 名称:CallBack_out_strength()
* 功能:输出强度
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_out_strength(void){
	set_color(0xFFFF);
	if(Menu_Output&MENU_OUT_FREQ)		
		fill_circle(123,109,0x01,8);
	if(Menu_Output&MENU_OUT_STRH)		
		fill_circle(273,109,0x01,8);
	if(Menu_Output&MENU_OUT_QUAL)		
		fill_circle(123,149,0x01,8);
	if(Menu_Output&MENU_OUT_TEST)		
		fill_circle(273,149,0x01,8);
	Menu_Output = MENU_OUT_STRH;
	set_color(0xF800);
	fill_circle(273,109,0x01,8);
	protocol_fun[PROTOCOL_INDEX_OUT_MODE_T](MENU_OUT_STRH,MENU_OUT_STRH);
}
/****************************************************************************
* 名称:CallBack_out_test()
* 功能:输出测试
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_out_test(void){
	set_color(0xFFFF);
	if(Menu_Output&MENU_OUT_FREQ)		
		fill_circle(123,109,0x01,8);
	if(Menu_Output&MENU_OUT_STRH)		
		fill_circle(273,109,0x01,8);
	if(Menu_Output&MENU_OUT_QUAL)		
		fill_circle(123,149,0x01,8);
	if(Menu_Output&MENU_OUT_TEST)		
		fill_circle(273,149,0x01,8);
	Menu_Output = MENU_OUT_TEST;
	set_color(0xF800);
	fill_circle(273,149,0x01,8);
  protocol_fun[PROTOCOL_INDEX_OUT_MODE_T](MENU_OUT_TEST,MENU_OUT_TEST);
}
/****************************************************************************
* 名称:CallBack_fire_force()
* 功能:强制有火
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_fire_force(void){
	if(Menu_Operate & MENU_OPT_FIRE){
		Menu_Operate &= ~MENU_OPT_FIRE;
		set_color(0xFFFF);
		protocol_fun[PROTOCOL_INDEX_FIRE_FORCE_N](MENU_OPT_FIRE,MENU_OPT_FIRE);
	}else{
		Menu_Operate |=  MENU_OPT_FIRE;
		set_color(0xF800);
		protocol_fun[PROTOCOL_INDEX_FIRE_FORCE_T](MENU_OPT_FIRE,MENU_OPT_FIRE);
	}
	fill_circle(123,109,0x01,8);
}
/****************************************************************************
* 名称:CallBack_nofire_force()
* 功能:强制无火
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_nofire_force(void){
	if(Menu_Operate & MENU_OPT_NOFIRE){
		Menu_Operate &= ~MENU_OPT_NOFIRE;
		set_color(0xFFFF);
		protocol_fun[PROTOCOL_INDEX_NFIRE_FORCE_N](MENU_OPT_NOFIRE,MENU_OPT_NOFIRE);
	}else{
		Menu_Operate |=  MENU_OPT_NOFIRE;
		set_color(0xF800);
		protocol_fun[PROTOCOL_INDEX_NFIRE_FORCE_T](MENU_OPT_NOFIRE,MENU_OPT_NOFIRE);
	}
	fill_circle(123,149,0x01,8);
}
/****************************************************************************
* 名称:CallBack_frelay_force()
* 功能:强制无火
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_frelay_force(void){
	if(Menu_Operate & MENU_OPT_FIRERELAY){
		Menu_Operate &= ~MENU_OPT_FIRERELAY;
		set_color(0xFFFF);
		GUI_Relay_Set(1,1);
		protocol_fun[PROTOCOL_INDEX_RELAY_T](RelayOutputType,RelayOutputType);
	}else{
		Menu_Operate |=  MENU_OPT_FIRERELAY;
		set_color(0xF800);
		GUI_Relay_Set(1,0);
		protocol_fun[PROTOCOL_INDEX_RELAY_T](RelayOutputType,RelayOutputType);
	}
	fill_circle(123,149,0x01,8);
}
/****************************************************************************
* 名称:CallBack_error_force()
* 功能:强制故障
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_error_force(void){
	if(Menu_Operate & MENU_OPT_ERR){
		Menu_Operate &= ~MENU_OPT_ERR;
		set_color(0xFFFF);
		protocol_fun[PROTOCOL_INDEX_ERR_FORCE_N](MENU_OPT_ERR,MENU_OPT_ERR);
	}else{
		Menu_Operate |=  MENU_OPT_ERR;
		set_color(0xF800);
		protocol_fun[PROTOCOL_INDEX_ERR_FORCE_T](MENU_OPT_ERR,MENU_OPT_ERR);
	}
	fill_circle(273,109,0x01,8);
}
/****************************************************************************
* 名称:CallBack_noerr_force()
* 功能:故障NB/A
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_noerr_force(void){
	if(Menu_Operate & MENU_OPT_NOERR){
		Menu_Operate &= ~MENU_OPT_NOERR;
		set_color(0xFFFF);
		protocol_fun[PROTOCOL_INDEX_NERR_FORCE_N](MENU_OPT_NOERR,MENU_OPT_NOERR);
	}else{
		Menu_Operate |=  MENU_OPT_NOERR;
		set_color(0xF800);
		protocol_fun[PROTOCOL_INDEX_NERR_FORCE_T](MENU_OPT_NOERR,MENU_OPT_NOERR);
	}
	fill_circle(273,149,0x01,8);
}
/****************************************************************************
* 名称:CallBack_erelay_force()
* 功能:故障NB/A
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_erelay_force(void){
	if(Menu_Operate & MENU_OPT_ERRRELAY){
		Menu_Operate &= ~MENU_OPT_ERRRELAY;
		set_color(0xFFFF);
		GUI_Relay_Set(0,1);
		protocol_fun[PROTOCOL_INDEX_RELAY_T](RelayOutputType,RelayOutputType);
	}else{
		Menu_Operate |=  MENU_OPT_ERRRELAY;
		set_color(0xF800);
		GUI_Relay_Set(0,0);
		protocol_fun[PROTOCOL_INDEX_RELAY_T](RelayOutputType,RelayOutputType);
	}
	fill_circle(273,149,0x01,8);
}
/****************************************************************************
* 名称:CallBack_reset_para()
* 功能:恢复默认值
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_reset_para(void){
	if(Menu_Operate & MENU_OPT_RESTORE){
		Menu_Operate &= ~MENU_OPT_RESTORE;
		set_color(0xFFFF);
		protocol_fun[PROTOCOL_INDEX_RESTORE_N](MENU_OPT_RESTORE,MENU_OPT_RESTORE);
	}else{
		Menu_Operate |=  MENU_OPT_RESTORE;
		set_color(0xF800);
		protocol_fun[PROTOCOL_INDEX_RESTORE_T](MENU_OPT_RESTORE,MENU_OPT_RESTORE);
	}
	fill_circle(273,109,0x01,8);
}
/****************************************************************************
* 名称:CallBack_self_test()
* 功能:系统自检
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_self_test(void){
	if(Menu_Operate & MENU_OPT_SELFT){
		Menu_Operate &= ~MENU_OPT_SELFT;
		set_color(0xFFFF);
	}else{
		Menu_Operate |=  MENU_OPT_SELFT;
		set_color(0xF800);
		protocol_fun[PROTOCOL_INDEX_SELF_TEST_T](Menu_Threhold[2],Menu_Threhold[3]);
	}
	fill_circle(123,109,0x01,8);
}
/****************************************************************************
* 名称:CallBack_threhold_freq()
* 功能:频率阀值
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_threhold_freq(void){
	 set_color(0xFFFF);
	 if(Menu_Threhold_Index == 0)
			fill_rectang(94,60,156,92,0);
	 if(Menu_Threhold_Index == 1)
			fill_rectang(244,60,304,92,0);
	 if(Menu_Threhold_Index == 2)
			fill_rectang(94,106,156,136,0);
	 if(Menu_Threhold_Index == 3)
			fill_rectang(244,106,304,136,0);
   Menu_Threhold_Index = MENU_THD_FREQ;
	 set_color(0xF800);
	 fill_rectang(244,60,304,92,0);
}
/****************************************************************************
* 名称:CallBack_threhold_strength()
* 功能:强度阀值
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_threhold_strength(void){
	 set_color(0xFFFF);
	 if(Menu_Threhold_Index == 0)
			fill_rectang(94,60,156,92,0);
	 if(Menu_Threhold_Index == 1)
			fill_rectang(244,60,304,92,0);
	 if(Menu_Threhold_Index == 2)
			fill_rectang(94,106,156,136,0);
	 if(Menu_Threhold_Index == 3)
			fill_rectang(244,106,304,136,0);
	 Menu_Threhold_Index = MENU_THD_STRH;
	 set_color(0xF800);
	 fill_rectang(94,60,156,92,0);
}
/****************************************************************************
* 名称:CallBack_offset_freq()
* 功能:频率回差
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_offset_freq(void){
	 set_color(0xFFFF);
	 if(Menu_Threhold_Index == 0)
			fill_rectang(94,60,156,92,0);
	 if(Menu_Threhold_Index == 1)
			fill_rectang(244,60,304,92,0);
	 if(Menu_Threhold_Index == 2)
			fill_rectang(94,106,156,136,0);
	 if(Menu_Threhold_Index == 3)
			fill_rectang(244,106,304,136,0);
	 Menu_Threhold_Index = MENU_OFF_FREQ;
	 set_color(0xF800);
	 fill_rectang(244,106,304,136,0);
}
/****************************************************************************
* 名称:CallBack_offset_strength()
* 功能:强度回差
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_offset_strength(void){
	 set_color(0xFFFF);
	 if(Menu_Threhold_Index == 0)
			fill_rectang(94,60,156,92,0);
	 if(Menu_Threhold_Index == 1)
			fill_rectang(244,60,304,92,0);
	 if(Menu_Threhold_Index == 2)
			fill_rectang(94,106,156,136,0);
	 if(Menu_Threhold_Index == 3)
			fill_rectang(244,106,304,136,0);
	 Menu_Threhold_Index = MENU_OFF_STRH;
	 set_color(0xF800);
	 fill_rectang(94,106,156,136,0);
}
/****************************************************************************
* 名称:CallBack_add()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_add(void){
	Menu_Threhold[Menu_Threhold_Index]++;
	Menu_Threhold[Menu_Threhold_Index] = Menu_Threhold[Menu_Threhold_Index]>(Menu_Threhold_Index>1?15:99)?0:Menu_Threhold[Menu_Threhold_Index];
	get_color(96,62);
	switch(Menu_Threhold_Index){
		case 0:
			fill_rectang(98,62,152,90,1);
		  set_color(0xFFFF);
		  fill_num(98,62,0x13,Menu_Threhold[0]);
			break;
		case 1:
			fill_rectang(248,62,300,90,1);
		  set_color(0xFFFF);
		  fill_num(248,62,0x13,Menu_Threhold[1]);
			break;
		case 2:
			fill_rectang(98,108,152,134,1);
		  set_color(0xFFFF);
		  fill_num(98,108,0x13,Menu_Threhold[2]);
			break;
		case 3:
			fill_rectang(248,108,300,134,1);
		  set_color(0xFFFF);
		  fill_num(248,108,0x13,Menu_Threhold[3]);
			break;
		default:
			break;
	}
}
/****************************************************************************
* 名称:CallBack_minus()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_minus(void){
	Menu_Threhold[Menu_Threhold_Index]--;
	Menu_Threhold[Menu_Threhold_Index] = Menu_Threhold[Menu_Threhold_Index]<0?(Menu_Threhold_Index>1?15:99):Menu_Threhold[Menu_Threhold_Index];
	get_color(96,62);
	switch(Menu_Threhold_Index){
		case 0:
			fill_rectang(98,62,152,90,1);
		  set_color(0xFFFF);
		  fill_num(98,62,0x13,Menu_Threhold[0]);
			break;
		case 1:
			fill_rectang(248,62,300,90,1);
		  set_color(0xFFFF);
		  fill_num(248,62,0x13,Menu_Threhold[1]);
			break;
		case 2:
			fill_rectang(98,108,152,134,1);
		  set_color(0xFFFF);
		  fill_num(98,108,0x13,Menu_Threhold[2]);
			break;
		case 3:
			fill_rectang(248,108,300,134,1);
		  set_color(0xFFFF);
		  fill_num(248,108,0x13,Menu_Threhold[3]);
			break;
		default:
			break;
	}
}
/****************************************************************************
* 名称:CallBack_ok()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_ok(void){

	switch(Menu_Threhold_Index){
		case 0:
			protocol_fun[PROTOCOL_INDEX_STR_THD_T](Menu_Threhold[0]|0x80,Menu_Threhold[1]);
			break;
		case 1:
			protocol_fun[PROTOCOL_INDEX_STR_THD_T](Menu_Threhold[0],Menu_Threhold[1]|0x80);
			break;
		case 2:
		case 3:
			protocol_fun[PROTOCOL_INDEX_OFFSET_T](Menu_Threhold[2],Menu_Threhold[3]);
			break;
		default :
			break;
	}
}

/****************************************************************************
* 名称:CallBack_adjust_4mA()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_adjust_4mA(void){
	 set_color(0xFFFF);
	 if(Menu_Output_Text_Index == 0)
			fill_rectang(75,78,137,110,0);
	 if(Menu_Output_Text_Index == 1)
			fill_rectang(182,78,244,110,0);
	 if(Menu_Output_Text_Index == 2)
			fill_rectang(75,116,137,148,0);
	 if(Menu_Output_Text_Index == 3)
			fill_rectang(182,116,244,148,0);
	 Menu_Output_Text_Index = MENU_ADJUST_4MA;
	 set_color(0xF800);
	 fill_rectang(75,78,137,110,0);
}
/****************************************************************************
* 名称:CallBack_adjust_20mA()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_adjust_20mA(void){

	 set_color(0xFFFF);
	 if(Menu_Output_Text_Index == 0)
			fill_rectang(75,78,137,110,0);
	 if(Menu_Output_Text_Index == 1)
			fill_rectang(182,78,244,110,0);
	 if(Menu_Output_Text_Index == 2)
			fill_rectang(75,116,137,148,0);
	 if(Menu_Output_Text_Index == 3)
			fill_rectang(182,116,244,148,0);
	 Menu_Output_Text_Index = MENU_ADJUST_20MA;
	 set_color(0xF800);
	 fill_rectang(182,78,244,110,0);
}
/****************************************************************************
* 名称:CallBack_nofire_delay()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_nofire_delay(void){
	 set_color(0xFFFF);
	 if(Menu_Output_Text_Index == 0)
			fill_rectang(75,78,137,110,0);
	 if(Menu_Output_Text_Index == 1)
			fill_rectang(182,78,244,110,0);
	 if(Menu_Output_Text_Index == 2)
			fill_rectang(75,116,137,148,0);
	 if(Menu_Output_Text_Index == 3)
			fill_rectang(182,116,244,148,0);
	 Menu_Output_Text_Index = MENU_NOFIRE_DELAY;
	 set_color(0xF800);
	 fill_rectang(75,116,137,148,0);
}
/****************************************************************************
* 名称:CallBack_dev_addr()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_dev_addr(void){
	 set_color(0xFFFF);
	 if(Menu_Output_Text_Index == 0)
			fill_rectang(75,78,137,110,0);
	 if(Menu_Output_Text_Index == 1)
			fill_rectang(182,78,244,110,0);
	 if(Menu_Output_Text_Index == 2)
			fill_rectang(75,116,137,148,0);
	 if(Menu_Output_Text_Index == 3)
			fill_rectang(182,116,244,148,0);
	 Menu_Output_Text_Index = MENU_DEV_ADDR;
	 set_color(0xF800);
	 fill_rectang(182,116,244,148,0);
}
/****************************************************************************
* 名称:CallBack_output_add()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_output_add(void){

	Menu_Output_Text[Menu_Output_Text_Index]++;
	Menu_Output_Text[Menu_Output_Text_Index] = Menu_Output_Text[Menu_Output_Text_Index]>(Menu_Output_Text_Index>1?15:99)?0:Menu_Output_Text[Menu_Output_Text_Index];
	get_color(76,79);
	switch(Menu_Output_Text_Index){
		case 0:
			fill_rectang(76,79,136,109,1);
		  set_color(0xFFFF);
		  fill_num(81,80,0x13,Menu_Output_Text[0]);
		  protocol_fun[PROTOCOL_INDEX_ADJUST_N](1,1);
			break;
		case 1:
			fill_rectang(183,79,243,109,1);
		  set_color(0xFFFF);
		  fill_num(188,80,0x13,Menu_Output_Text[1]);
			protocol_fun[PROTOCOL_INDEX_ADJUST_N](0,1);
			break;
		case 2:
			fill_rectang(76,117,136,147,1);
		  set_color(0xFFFF);
		  fill_float(81,118,0x13,Menu_Output_Text[2]%16);
			break;
		case 3:
			fill_rectang(183,117,243,147,1);
		  set_color(0xFFFF);
		  fill_num(188,118,0x13,Menu_Output_Text[3]);
			break;
		default:
			break;
	}
}
/****************************************************************************
* 名称:CallBack_output_minus()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_output_minus(void){

	Menu_Output_Text[Menu_Output_Text_Index]--;
	Menu_Output_Text[Menu_Output_Text_Index] = Menu_Output_Text[Menu_Output_Text_Index]<0?(Menu_Output_Text_Index>1?15:99):Menu_Output_Text[Menu_Output_Text_Index];
	get_color(76,79);
	switch(Menu_Output_Text_Index){
		case 0:
			fill_rectang(76,79,136,109,1);
		  set_color(0xFFFF);
		  fill_num(81,80,0x13,Menu_Output_Text[0]);
		  protocol_fun[PROTOCOL_INDEX_ADJUST_N](1,0);//4mA
			break;
		case 1:
			fill_rectang(183,79,243,109,1);
		  set_color(0xFFFF);
		  fill_num(188,80,0x13,Menu_Output_Text[1]);
		  protocol_fun[PROTOCOL_INDEX_ADJUST_N](0,0);//20mA
			break;
		case 2:
			fill_rectang(76,117,136,147,1);
		  set_color(0xFFFF);
		  fill_float(81,118,0x13,Menu_Output_Text[2]%16);
			break;
		case 3:
			fill_rectang(183,117,243,147,1);
		  set_color(0xFFFF);
		  fill_num(188,118,0x13,Menu_Output_Text[3]);
			break;
		default:
			break;
	}
}
/****************************************************************************
* 名称:CallBack_output_ok()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_output_ok(void){

	switch(Menu_Output_Text_Index){
		case 0:
			protocol_fun[PROTOCOL_INDEX_ADJUST_T](1,1);//4mA
			break;
		case 1:
      protocol_fun[PROTOCOL_INDEX_ADJUST_T](0,1);//20mA
			break;
		case 2:
			  GUI_DelayTriger_Set(Menu_Output_Text[2]);//无火延时时间
				protocol_fun[PROTOCOL_INDEX_RELAY_T](RelayOutputType,RelayOutputType);
			break;
		case 3:
//			protocol_fun[PROTOCOL_INDEX_OFFSET_T](Menu_Threhold[2],Menu_Threhold[3]);
			break;
		default :
			break;
	}
}
/****************************************************************************
* 名称:CallBack_freq_mode()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_freq_mode(void){
	 set_color(0xFFFF);
	 if(Menu_OPT_Text_Index == 0)
			fill_rectang(75,78,137,110,0);
	 if(Menu_OPT_Text_Index == 1)
			fill_rectang(182,78,244,110,0);
	 if(Menu_OPT_Text_Index == 2)
			fill_rectang(75,116,137,148,0);
	 if(Menu_OPT_Text_Index == 3)
			fill_rectang(182,116,244,148,0);
	 Menu_OPT_Text_Index = MENU_FREQ_MODE;
	 set_color(0xF800);
	 fill_rectang(75,78,137,110,0);
}
/****************************************************************************
* 名称:CallBack_adjust_20mA()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_freq_gain(void){

	 set_color(0xFFFF);
	 if(Menu_OPT_Text_Index == 0)
			fill_rectang(75,78,137,110,0);
	 if(Menu_OPT_Text_Index == 1)
			fill_rectang(182,78,244,110,0);
	 if(Menu_OPT_Text_Index == 2)
			fill_rectang(75,116,137,148,0);
	 if(Menu_OPT_Text_Index == 3)
			fill_rectang(182,116,244,148,0);
	 Menu_OPT_Text_Index = MENU_FREQ_GAIN;
	 set_color(0xF800);
	 fill_rectang(182,78,244,110,0);
}
/****************************************************************************
* 名称:CallBack_nofire_delay()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_param_A(void){
	 set_color(0xFFFF);
	 if(Menu_OPT_Text_Index == 0)
			fill_rectang(75,78,137,110,0);
	 if(Menu_OPT_Text_Index == 1)
			fill_rectang(182,78,244,110,0);
	 if(Menu_OPT_Text_Index == 2)
			fill_rectang(75,116,137,148,0);
	 if(Menu_OPT_Text_Index == 3)
			fill_rectang(182,116,244,148,0);
	 Menu_OPT_Text_Index = MENU_PARM_A;
	 set_color(0xF800);
	 fill_rectang(75,116,137,148,0);
}
/****************************************************************************
* 名称:CallBack_dev_addr()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_param_B(void){
	 set_color(0xFFFF);
	 if(Menu_OPT_Text_Index == 0)
			fill_rectang(75,78,137,110,0);
	 if(Menu_OPT_Text_Index == 1)
			fill_rectang(182,78,244,110,0);
	 if(Menu_OPT_Text_Index == 2)
			fill_rectang(75,116,137,148,0);
	 if(Menu_OPT_Text_Index == 3)
			fill_rectang(182,116,244,148,0);
	 Menu_OPT_Text_Index = MENU_PARM_B;
	 set_color(0xF800);
	 fill_rectang(182,116,244,148,0);
}
/****************************************************************************
* 名称:CallBack_opt3_add()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_opt3_add(void){

	Menu_Operate_Text[Menu_OPT_Text_Index]++;
	switch(Menu_OPT_Text_Index){
		case 0:
			Menu_Operate_Text[Menu_OPT_Text_Index] =Menu_Operate_Text[Menu_OPT_Text_Index]>7?0:Menu_Operate_Text[Menu_OPT_Text_Index];
			break;
		case 1:
			Menu_Operate_Text[Menu_OPT_Text_Index] =Menu_Operate_Text[Menu_OPT_Text_Index]>7?1:Menu_Operate_Text[Menu_OPT_Text_Index];
			break;
		case 2:
			Menu_Operate_Text[Menu_OPT_Text_Index] =Menu_Operate_Text[Menu_OPT_Text_Index]&0x0F;
			break;
		case 3:
			Menu_Operate_Text[Menu_OPT_Text_Index] =Menu_Operate_Text[Menu_OPT_Text_Index]&0x0F;
			break;
		default :
			break;
	}
	get_color(76,79);
	switch(Menu_OPT_Text_Index){
		case 0:
			fill_rectang(76,79,136,109,1);
		  set_color(0xFFFF);
		  fill_num(81,80,0x13,Menu_Operate_Text[0]);
			break;
		case 1:
			fill_rectang(183,79,243,109,1);
		  set_color(0xFFFF);
		  fill_num(188,80,0x13,Menu_Operate_Text[1]);
			break;
		case 2:
			fill_rectang(76,117,136,147,1);
		  set_color(0xFFFF);
			fill_num(81,118,0x13,Menu_Operate_Text[2]);
			break;
		case 3:
			fill_rectang(183,117,243,147,1);
		  set_color(0xFFFF);
			fill_num(188,118,0x13,Menu_Operate_Text[3]);
			break;
		default:
			break;
	}
}
/****************************************************************************
* 名称:CallBack_opt3_minus()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_opt3_minus(void){

	Menu_Operate_Text[Menu_OPT_Text_Index]--;
	switch(Menu_OPT_Text_Index){
		case 0:
			Menu_Operate_Text[Menu_OPT_Text_Index] =Menu_Operate_Text[Menu_OPT_Text_Index]<0?7:Menu_Operate_Text[Menu_OPT_Text_Index];
			break;
		case 1:
			Menu_Operate_Text[Menu_OPT_Text_Index] =Menu_Operate_Text[Menu_OPT_Text_Index]<1?7:Menu_Operate_Text[Menu_OPT_Text_Index];
			break;
		case 2:
			Menu_Operate_Text[Menu_OPT_Text_Index] =Menu_Operate_Text[Menu_OPT_Text_Index]&0x0F;
			break;
		case 3:
			Menu_Operate_Text[Menu_OPT_Text_Index] =Menu_Operate_Text[Menu_OPT_Text_Index]&0x0F;
			break;
		default :
			break;
	}
	get_color(76,79);
	switch(Menu_OPT_Text_Index){
		case 0:
			fill_rectang(76,79,136,109,1);
		  set_color(0xFFFF);
		  fill_num(81,80,0x13,Menu_Operate_Text[0]);
			break;
		case 1:
			fill_rectang(183,79,243,109,1);
		  set_color(0xFFFF);
		  fill_num(188,80,0x13,Menu_Operate_Text[1]);
			break;
		case 2:
			fill_rectang(76,117,136,147,1);
		  set_color(0xFFFF);
			fill_num(81,118,0x13,Menu_Operate_Text[2]);
			break;
		case 3:
			fill_rectang(183,117,243,147,1);
		  set_color(0xFFFF);
			fill_num(188,118,0x13,Menu_Operate_Text[3]);
			break;
		default:
			break;
	}
}
/****************************************************************************
* 名称:CallBack_opt3_ok()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_opt3_ok(void){

	switch(Menu_OPT_Text_Index){
		case 0:
			protocol_fun[PROTOCOL_INDEX_FMODE_T](Menu_Operate_Text[0]&0x0F,Menu_Operate_Text[1]&0x0F);//Freq Mode
			break;
		case 1:
      protocol_fun[PROTOCOL_INDEX_FMODE_T](Menu_Operate_Text[0]&0x0F,Menu_Operate_Text[1]&0x0F);//Freq Gain
			break;
		case 2:
			protocol_fun[PROTOCOL_INDEX_PARAMAB_T](Menu_Operate_Text[2]&0x0F,Menu_Operate_Text[3]&0x0F);// Param A 
			break;
		case 3:
      protocol_fun[PROTOCOL_INDEX_PARAMAB_T](Menu_Operate_Text[2]&0x0F,Menu_Operate_Text[3]&0x0F);//Param  B
			break;
		default :
			break;
	}
}
/****************************************************************************
* 名称:CallBack_change()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
static void CallBack_change(uint8_t img){
	uint8_t i;
	uint8_t img_no,img_title;
	protocol_normal();
	if(Menu_Index[0]!=3){
			Menu_Operate &=(MENU_OPT_FIRERELAY | MENU_OPT_ERRRELAY); //清除操作菜单下的选中状态
	}
	switch(Menu_Index[0]){
		case 1:
			Qual_Xpos=0;
		  Qual_Xpos_Old=0;
		  Freq_Xpos=0;
		  Freq_Xpos_Old=0;
		  Strength_Xpos=0;
		  Strength_Xpos_Old=0;
			img_no=1;
		  img_title = 7;
			break;
		case 2:
			Menu_Threhold[0]=Threhold_Temp[0];
			Menu_Threhold[1]=Threhold_Temp[1];
//			Menu_Threhold[2]=Threhold_Temp[2];
//			Menu_Threhold[3]=Threhold_Temp[3];
			img_no=2;
		  img_title = 8;
			break;
		case 3:
			switch(Menu_Index[1]){
				case 1:
					img_no=3;
					break;
				case 2:
					img_no=4;
					break;
				case 3:
					img_no=13;
					break;
				default:
					img_no=3;
					break;
			}
			img_title = 9;
			break;
		case 4:
			switch(Menu_Index[1]){
				case 1:
					img_no=5;
					break;
				case 2:
					img_no=12;
					break;
				case 3:
					img_no=12;
					break;
				default:
					img_no=5;
					break;
			}
			img_title = 10;
			break;
		case 5:
			img_no=6;
		  img_title = 11;
			break;
		default:
			img_no=1;
			break;
	}	
  for(i=0;i<sizeof(GUI_Cmd_Image_Disp);i++){
		USART2->DR = i==4?img_no:GUI_Cmd_Image_Disp[i];
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	}
  for(i=0;i<sizeof(GUI_Cmd_Image_Cut);i++){
		USART2->DR = i==8?img_title:GUI_Cmd_Image_Cut[i];
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	}	
	fill_intent(img_no);
}
/****************************************************************************
* 名称:GUI_Init()
* 功能:
* 入口参数: ico			
*           sel			
* 出口参数:
****************************************************************************/
void  GUI_Init(void){
  OS_ERR err;
	uint8_t i;
	for(i=0;i<sizeof(GUI_Cmd_Image_Disp);i++){
		USART2->DR = GUI_Cmd_Image_Disp[i];
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	}
  set_color(0xFFFF);
	for(i=0;i<sizeof(GUI_Str_S);i++){
		USART2->DR = GUI_Str_S[i];
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	}
	for(i=0;i<sizeof(GUI_Str_F);i++){
		USART2->DR = GUI_Str_F[i];
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	}
	for(i=0;i<sizeof(GUI_Str_T);i++){
		USART2->DR = GUI_Str_T[i];
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	}
	for(i=0;i<sizeof(GUI_Str_U);i++){
		USART2->DR = GUI_Str_U[i];
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	}	
	OSTimeDly(50,OS_OPT_TIME_DLY,&err);
  for(i=0;i<sizeof(GUI_Cmd_Touch_Mode);i++){
		USART2->DR = GUI_Cmd_Touch_Mode[i];
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	}	
}
/****************************************************************************
* 名称:GUI_Proc()
* 功能:
* 入口参数: pos			
*           sel			
* 出口参数:
****************************************************************************/
uint8_t GUI_Proc(uint32_t pos){
	uint8_t i;
	uint16_t x,y;
	const MENU_ITEM *pitem;
	const MENU_BUTTON *pbtn;
	const MENU_TEXT   *ptxt;
	x=pos>>16;
	y=pos&0x0000FFFF;
	/*按键来自主菜单项*/
  for(i=0;i<MAIN_MENU_SIZE;i++){
		if(x>=menu_root[i]->x_start && x<menu_root[i]->x_stop && 
			 y>=menu_root[i]->y_start && y<menu_root[i]->y_stop){
			Main_Menu_Pos.class_pos = menu_root[i];
			Main_Menu_Pos.item_pos = menu_root[i]->item;
			Main_Menu_Pos.btn_pos = NULL;
			Main_Menu_Pos.txt_pos = NULL;
			GUI_TRACE("%s\n",menu_root[i]->pname);
			Menu_Index[0]=i+1;
			Menu_Index[1]=0;
			Menu_Index[2]=0;
			Menu_Index[3]=0;
			Main_Menu_Pos.class_pos->pfun(i);
			return 0;
		}
	}
	/*按键来自item项*/
	pitem = Main_Menu_Pos.class_pos->item;
	for(i=0;pitem!=NULL;i++){
		if(x >=pitem->x_start && x <pitem->x_stop &&
			 y >=pitem->y_start && y <pitem->y_stop){
			Main_Menu_Pos.item_pos = pitem;
			Menu_Index[1]=i+1;
			Menu_Index[2]=0;
			Menu_Index[3]=0;
			GUI_TRACE("%s->%s\n",Main_Menu_Pos.class_pos->pname,pitem->pname);
			pitem->pfun(i);
			return 0;
		}else{
			pitem = pitem->next_item;
		}
	}
	/*按键来自button项*/
	if(Main_Menu_Pos.item_pos !=NULL){
		pbtn = Main_Menu_Pos.item_pos->btn;
		for(i=0;pbtn!=NULL;i++){
			if(x>=pbtn->x_start && x<pbtn->x_stop &&
				 y>=pbtn->y_start && y<pbtn->y_stop){
				Main_Menu_Pos.btn_pos = pbtn;
				GUI_TRACE("%s->%s->%s\n",Main_Menu_Pos.class_pos->pname,Main_Menu_Pos.item_pos->pname,pbtn->pname);
				Menu_Index[3]=i+1;
				pbtn->pfun(pbtn->data);
				return 0;
			}else
				pbtn = pbtn->netx_button;
		}
	}
	/*按键来自text项*/
	if(Main_Menu_Pos.item_pos !=NULL){
		ptxt = Main_Menu_Pos.item_pos->txt;
		for(i=0;ptxt!=NULL;i++){
			if(x>=ptxt->x_start && x<ptxt->x_stop &&
				 y>=ptxt->y_start && y<ptxt->y_stop){
				Main_Menu_Pos.txt_pos = ptxt;
				GUI_TRACE("%s->%s->%s\n",Main_Menu_Pos.class_pos->pname,Main_Menu_Pos.item_pos->pname,ptxt->pname);
				Menu_Index[2]=i+1;
				Menu_Index[3]=0;
				ptxt->pfun();
				return 0;
			}else
				ptxt = ptxt->netx_text;
		}
	}
	return -1;
}
/****************************************************************************
* 名称:GUI_Show_Graph()
* 功能:
* 入口参数: pos			
*           sel			
* 出口参数:
****************************************************************************/
void GUI_Show_Graph(void){
	if(Menu_Index[0]==1){
		fill_bar_graph(Strength,Frequecy,Quality);
		fill_fire_graph(Strength,Frequecy);
		fill_err_graph(Fpu_State,Sensor_State);
		fill_strength_graph(Strength);
		fill_freq_graph(Frequecy);
		fill_qual_graph(Quality);
		Strength = 0;
		Frequecy = 0;
		Quality =  0;
	}
}
void GUI_Env_Set(uint8_t strh,uint8_t freq,uint8_t qual){

	Strength = strh;
	Frequecy = freq;
	Quality = qual;
}

void GUI_Fpu_State(uint8_t state){
	Fpu_State = state;
}
void GUI_Sensor_State(uint8_t state){
	Sensor_State = state;
}
void GUI_ThreholdTemp_Set(uint8_t s,uint8_t f){
	Threhold_Temp[0]=s;
	Threhold_Temp[1]=f;
}
void GUI_Threhold_Set(uint8_t s,uint8_t f){
	Menu_Threhold[0]=s;
	Menu_Threhold[1]=f;
}
void GUI_Threhold_Get(uint8_t *s,uint8_t *f){
	*s=Menu_Threhold[0];
	*f=Menu_Threhold[1];
}

void GUI_Offset_Set(uint8_t s,uint8_t f){
	Menu_Threhold[2]=s;
	Menu_Threhold[3]=f;
}
void GUI_Offset_Get(uint8_t *s,uint8_t *f){
	*s=Menu_Threhold[2];
	*f=Menu_Threhold[3];
}
void GUI_Relay_Restore(uint8_t dat){
	RelayOutputType = dat;
	Menu_Output_Text[2]=dat>>4;
  Menu_Operate = (dat & 0x01)?(Menu_Operate & (~MENU_OPT_FIRERELAY)):(Menu_Operate | MENU_OPT_FIRERELAY);	
	Menu_Operate = (dat & 0x02)?(Menu_Operate & (~MENU_OPT_ERRRELAY)):(Menu_Operate | MENU_OPT_ERRRELAY);	
}
void GUI_Relay_Set(uint8_t fire,uint8_t err){
	RelayOutputType &=fire==1?0xFE:0xFD;
	RelayOutputType |=fire==1?(err):(err<<1);
}
void GUI_Relay_Get(uint8_t *fire,uint8_t *err){
	*fire = RelayOutputType&0x01;
	*err  = (RelayOutputType&0x02)>>1;
}
void GUI_FreqMode_Restore(uint8_t mode,uint8_t gain){
	Menu_Operate_Text[0]=mode;
	Menu_Operate_Text[1]=gain;
}
void GUI_ParamAB_Restore(uint8_t pA,uint8_t pB){
	Menu_Operate_Text[2]=pA;
	Menu_Operate_Text[3]=pB;
}
void GUI_DelayTriger_Set(uint8_t dly){
	RelayOutputType &= 0x0F;
	RelayOutputType |= (dly&0x0F)<<4;
}
uint8_t GUI_DelayTriger_Get(void){
	return RelayOutputType>>4;
}

void GUI_DisType_Set(uint8_t type){
	RelayOutputType =type==1?(RelayOutputType&0x04):(RelayOutputType&0xFB);
}
uint8_t GUI_DisType_Get(void){
	return (RelayOutputType&0xFB)>>2;
}

void GUI_OutputType_Set(uint8_t type){
	switch(type){
		case 0:
			Menu_Output=MENU_OUT_STRH;
			break;
		case 1:
			Menu_Output=MENU_OUT_FREQ;
			break;
		case 2:
			Menu_Output=MENU_OUT_QUAL;
			break;
		default:
			break;
	}
}
uint8_t GUI_OutputType_Get(void){
	uint8_t result=0;
	switch(Menu_Output){
		case MENU_OUT_STRH:
			result=0;
			break;
		case MENU_OUT_FREQ:
			result=1;
			break;
		case MENU_OUT_QUAL:
			result=2;
			break;
		default:
			result=0;
			break;
	}
	return result;
}