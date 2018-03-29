/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                        Evaluation Board
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : FT
*                 DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#ifndef __KEY_CODE_H__
#define __KEY_CODE_H__

#include "key.h"

#define KEY_NUM		32
#define LED_NUM   24

static const tKeyList KeyList[KEY_NUM]={
	{
		.code = 0x1D,
		.row	= 2,
		.col 	= 0
	},//紧急制动 0
	{
		.code = 0x05,
		.row	= 2,
		.col 	= 4
	},//右   1
	{
		.code = 0x15,
		.row	= 2,
		.col 	= 4
	},//空  2
	{
		.code = 0x0D,
		.row	= 2,
		.col 	= 3
	},//空  3
	{
		.code = 0x04,
		.row	= 2,
		.col 	= 5
	},//连续放矿 4
	{
		.code = 0x14, 
		.row	= 2,
		.col 	= 1
	},//左	5
	{
		.code = 0x1C, 
		.row	= 2,
		.col 	= 5
	},//右 6
	{	 
		.code = 0x0C, 
		.row	= 5,
		.col 	= 1
	},//空	7
	{
		.code = 0x07, 
		.row	= 4,
		.col 	= 0
	},//空  8
	{
		.code = 0x0F, 
		.row	= 2,
		.col 	= 2
	},//前 9
	{
		.code = 0x17, 
		.row	= 4,
		.col 	= 2
	},//空 10
	{
		.code = 0x1F, 
		.row	= 4,
		.col 	= 3
	},//空 11
	{
		.code = 0x06, 
		.row	= 2,
		.col 	= 6
	},//放矿 12
	{
		.code = 0x0E, 
		.row	= 2,
		.col 	= 3
	},//后 13
	{
		.code = 0x16, 
		.row	= 4,
		.col 	= 6
	},//空  14
	{
		.code = 0x25, 
		.row	= 2,
		.col 	= 4
	},//空 15
	{
		.code = 0x30, 
		.row	= 0,
		.col 	= 0
	},//遥控 16
	{
		.code = 0x28, 
		.row	= 0,
		.col 	= 1
	},//巡航 17
	{
		.code = 0x00, 
		.row	= 0,
		.col 	= 2
	},//驻车 18
	{
		.code = 0x08, 
		.row	= 0,
		.col 	= 3
	},//停用 19
	{
		.code = 0x10, 
		.row	= 0,
		.col 	= 4
	},//照明 20
	{
		.code = 0x18, 
		.row	= 0,
		.col 	= 5
	},//鸣笛 21 
	{
    .code = 0x01, 
		.row	= 0,	
		.col 	= 6
	},//撒沙 22
	{
		.code = 0x09, 
		.row	= 0,
		.col 	= 7
	},//蠕动 23
	{
		.code = 0x11, 
		.row	= 1,
		.col 	= 0
	},//前进 24
	{
		.code = 0x19, 
		.row	= 1,
		.col 	= 1
	},//后退 25
	{
		.code = 0x02, 
		.row	= 1,
		.col 	= 2
	},//升弓   26
	{
		.code = 0x12, 
		.row	= 1,
		.col 	= 3
	},//降弓 27
	{
		.code = 0x1A,
		.row	= 1,
		.col 	= 7
	},//解除 28
	{
		.code = 0x03,
		.row	= 1,
		.col 	= 4
	},//制动 29
	{
		.code = 0x0B, 
		.row	= 1,
		.col 	= 6
	},// 减速 30
	{
		.code = 0x13, 
		.row	= 1,
		.col 	= 5
	}//加速 31 

};
static const tLEDList LEDList[LED_NUM]={
	{
		.lrow = 0,
		.lcol = 0,
		.row	= 3,
		.col 	= 5
	},//遥控 0
	{
		.lrow = 2,
		.lcol = 0,
		.row	= 4,
		.col 	= 0
	},//巡航 1
	{
		.lrow = 3,
		.lcol = 0,
		.row	= 4,
		.col 	= 2
	},//驻车 2
	{
		.lrow = 1,
		.lcol = 0,
		.row	= 4,
		.col 	= 1
	},//停用 3
	{
		.lrow = 2,
		.lcol = 3,
		.row	= 3,
		.col 	= 3
	},//照明 4
	{
		.lrow = 3,
		.lcol = 3, 
		.row	= 3,
		.col 	= 2
	},//鸣笛 5
	{
		.lrow = 1,
		.lcol = 3, 
		.row	= 3,
		.col 	= 1
	},//撒沙 6
	{
		.lrow = 0,
		.lcol = 3, 
		.row	= 3,
		.col 	= 4
	},//蠕动 7
	{
		.lrow = 2,
		.lcol = 2, 
		.row	= 3,
		.col 	= 0
	},//前进 8 
	{
		.lrow = 3,
		.lcol = 2, 
		.row	= 2,
		.col 	= 5
	},//后退 9
	{
		.lrow = 0,
		.lcol = 1, 
		.row	= 2,
		.col 	= 6
	},//升弓 10
	{
		.lrow = 2,
		.lcol = 1, 
		.row	= 2,
		.col 	= 7
	},//降弓 11
	{
		.lrow = 3,
		.lcol = 1, 
		.row	= 2,
		.col 	= 2
	},//制动 12
	{
		.lrow = 1,
		.lcol = 7, 
		.row	= 2,
		.col 	= 3
	},//加速 13
	{
		.lrow = 0,
		.lcol = 7, 
		.row	= 2,
		.col 	= 4
	},//减速 14
	{
		.lrow = 2,
		.lcol = 7, 
		.row	= 2,
		.col 	= 0
	},//解除 15
	{
		.lrow = 3,
		.lcol = 7, 
		.row	= 2,
		.col 	= 1
	},//紧急制动 16
	{
		.lrow = 1,
		.lcol = 5, 
		.row	= 1,
		.col 	= 4
	},//左 17
	{
		.lrow = 0,
		.lcol = 5, 
		.row	= 1,
		.col 	= 3
	},//前 18
	{
		.lrow = 2,
		.lcol = 5, 
		.row	= 1,
		.col 	= 2
	},//后 19
	{
		.lrow = 3,
		.lcol = 5, 
		.row	= 1,
		.col 	= 1
	},//右 20
	{
		.lrow = 2,
		.lcol = 5, 
		.row	= 1,
		.col 	= 5
	},//连续放矿 21
	{
		.lrow = 2,
		.lcol = 6,
		.row	= 1,
		.col 	= 5
	},//放矿 22
	{
		.lrow = 3,
		.lcol = 6,
		.row	= 3,
		.col 	= 6
	}//报警 23
//	{
//		.lrow = 1,
//		.lcol = 4,
//		.row	= 1,
//		.col 	= 4
//	},//鸣笛
//	{
//		.lrow = 0,
//		.lcol = 4,
//		.row	= 1,
//		.col 	= 5
//	},//萨沙
//	{
//		.lrow = 2,
//		.lcol = 4,
//		.row	= 1,
//		.col 	= 6
//	},//驻车
//	{
//		.lrow = 3,
//		.lcol = 4,
//		.row	= 1,
//		.col 	= 7
//	},//点动
//	{
//		.lrow = 0,
//		.lcol = 6,
//		.row	= 1,
//		.col 	= 1
//	}//降弓
}; 

#endif
