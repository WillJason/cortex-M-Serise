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
* Filename      : sensor_protocol.h
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

#ifndef  __PROTOCOL_H__
#define  __PROTOCOL_H__
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

#define PROTOCOL_INDEX_STR_THD_T  		0
#define PROTOCOL_INDEX_STR_THD_N			1
#define PROTOCOL_INDEX_OFFSET_T  			2
#define PROTOCOL_INDEX_OFFSET_N 			3
#define PROTOCOL_INDEX_FIRE_FORCE_T 	4
#define PROTOCOL_INDEX_FIRE_FORCE_N 	5
#define PROTOCOL_INDEX_NFIRE_FORCE_T 	6
#define PROTOCOL_INDEX_NFIRE_FORCE_N 	7
#define PROTOCOL_INDEX_ERR_FORCE_T 		8
#define PROTOCOL_INDEX_ERR_FORCE_N 		9
#define PROTOCOL_INDEX_NERR_FORCE_T 	10
#define PROTOCOL_INDEX_NERR_FORCE_N 	11
#define PROTOCOL_INDEX_SELF_TEST_T 		12
#define PROTOCOL_INDEX_SELF_TEST_N 		13
#define PROTOCOL_INDEX_RESTORE_T 			14
#define PROTOCOL_INDEX_RESTORE_N 			15
#define PROTOCOL_INDEX_RELAY_T 				16
#define PROTOCOL_INDEX_RELAY_N 				17
#define PROTOCOL_INDEX_OUT_MODE_T 		18
#define PROTOCOL_INDEX_OUT_MODE_N 		19
#define PROTOCOL_INDEX_ADJUST_T 			20
#define PROTOCOL_INDEX_ADJUST_N 			21
#define PROTOCOL_INDEX_FMODE_T 				22
#define PROTOCOL_INDEX_FMODE_N 				23
#define PROTOCOL_INDEX_PARAMAB_T 			24
#define PROTOCOL_INDEX_PARAMAB_N 			25



/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/
typedef  struct{
	uint32_t Head	:8;//0xFF
	uint32_t tri	:4;//8/0
	uint32_t type :4;//0/1/2/3
	uint32_t type1:4;//
	uint32_t type2:4;
	uint32_t type3:4;
	uint32_t type4:4;
}tPROTOCOL;


void Uart_Conn_Init(void);
uint8_t Uart_Conn_Write(const uint8_t *psrc,uint8_t *pdst,uint8_t len);
void protocol_Init(void);
void protocol_send(void);
void protocol_normal(void);
extern void (*protocol_fun[26])(uint8_t ,uint8_t);
/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/


#endif 
