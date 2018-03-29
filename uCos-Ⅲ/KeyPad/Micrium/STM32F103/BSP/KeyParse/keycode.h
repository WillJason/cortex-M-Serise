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
	},//�����ƶ� 0
	{
		.code = 0x05,
		.row	= 2,
		.col 	= 4
	},//��   1
	{
		.code = 0x15,
		.row	= 2,
		.col 	= 4
	},//��  2
	{
		.code = 0x0D,
		.row	= 2,
		.col 	= 3
	},//��  3
	{
		.code = 0x04,
		.row	= 2,
		.col 	= 5
	},//�����ſ� 4
	{
		.code = 0x14, 
		.row	= 2,
		.col 	= 1
	},//��	5
	{
		.code = 0x1C, 
		.row	= 2,
		.col 	= 5
	},//�� 6
	{	 
		.code = 0x0C, 
		.row	= 5,
		.col 	= 1
	},//��	7
	{
		.code = 0x07, 
		.row	= 4,
		.col 	= 0
	},//��  8
	{
		.code = 0x0F, 
		.row	= 2,
		.col 	= 2
	},//ǰ 9
	{
		.code = 0x17, 
		.row	= 4,
		.col 	= 2
	},//�� 10
	{
		.code = 0x1F, 
		.row	= 4,
		.col 	= 3
	},//�� 11
	{
		.code = 0x06, 
		.row	= 2,
		.col 	= 6
	},//�ſ� 12
	{
		.code = 0x0E, 
		.row	= 2,
		.col 	= 3
	},//�� 13
	{
		.code = 0x16, 
		.row	= 4,
		.col 	= 6
	},//��  14
	{
		.code = 0x25, 
		.row	= 2,
		.col 	= 4
	},//�� 15
	{
		.code = 0x30, 
		.row	= 0,
		.col 	= 0
	},//ң�� 16
	{
		.code = 0x28, 
		.row	= 0,
		.col 	= 1
	},//Ѳ�� 17
	{
		.code = 0x00, 
		.row	= 0,
		.col 	= 2
	},//פ�� 18
	{
		.code = 0x08, 
		.row	= 0,
		.col 	= 3
	},//ͣ�� 19
	{
		.code = 0x10, 
		.row	= 0,
		.col 	= 4
	},//���� 20
	{
		.code = 0x18, 
		.row	= 0,
		.col 	= 5
	},//���� 21 
	{
    .code = 0x01, 
		.row	= 0,	
		.col 	= 6
	},//��ɳ 22
	{
		.code = 0x09, 
		.row	= 0,
		.col 	= 7
	},//�䶯 23
	{
		.code = 0x11, 
		.row	= 1,
		.col 	= 0
	},//ǰ�� 24
	{
		.code = 0x19, 
		.row	= 1,
		.col 	= 1
	},//���� 25
	{
		.code = 0x02, 
		.row	= 1,
		.col 	= 2
	},//����   26
	{
		.code = 0x12, 
		.row	= 1,
		.col 	= 3
	},//���� 27
	{
		.code = 0x1A,
		.row	= 1,
		.col 	= 7
	},//��� 28
	{
		.code = 0x03,
		.row	= 1,
		.col 	= 4
	},//�ƶ� 29
	{
		.code = 0x0B, 
		.row	= 1,
		.col 	= 6
	},// ���� 30
	{
		.code = 0x13, 
		.row	= 1,
		.col 	= 5
	}//���� 31 

};
static const tLEDList LEDList[LED_NUM]={
	{
		.lrow = 0,
		.lcol = 0,
		.row	= 3,
		.col 	= 5
	},//ң�� 0
	{
		.lrow = 2,
		.lcol = 0,
		.row	= 4,
		.col 	= 0
	},//Ѳ�� 1
	{
		.lrow = 3,
		.lcol = 0,
		.row	= 4,
		.col 	= 2
	},//פ�� 2
	{
		.lrow = 1,
		.lcol = 0,
		.row	= 4,
		.col 	= 1
	},//ͣ�� 3
	{
		.lrow = 2,
		.lcol = 3,
		.row	= 3,
		.col 	= 3
	},//���� 4
	{
		.lrow = 3,
		.lcol = 3, 
		.row	= 3,
		.col 	= 2
	},//���� 5
	{
		.lrow = 1,
		.lcol = 3, 
		.row	= 3,
		.col 	= 1
	},//��ɳ 6
	{
		.lrow = 0,
		.lcol = 3, 
		.row	= 3,
		.col 	= 4
	},//�䶯 7
	{
		.lrow = 2,
		.lcol = 2, 
		.row	= 3,
		.col 	= 0
	},//ǰ�� 8 
	{
		.lrow = 3,
		.lcol = 2, 
		.row	= 2,
		.col 	= 5
	},//���� 9
	{
		.lrow = 0,
		.lcol = 1, 
		.row	= 2,
		.col 	= 6
	},//���� 10
	{
		.lrow = 2,
		.lcol = 1, 
		.row	= 2,
		.col 	= 7
	},//���� 11
	{
		.lrow = 3,
		.lcol = 1, 
		.row	= 2,
		.col 	= 2
	},//�ƶ� 12
	{
		.lrow = 1,
		.lcol = 7, 
		.row	= 2,
		.col 	= 3
	},//���� 13
	{
		.lrow = 0,
		.lcol = 7, 
		.row	= 2,
		.col 	= 4
	},//���� 14
	{
		.lrow = 2,
		.lcol = 7, 
		.row	= 2,
		.col 	= 0
	},//��� 15
	{
		.lrow = 3,
		.lcol = 7, 
		.row	= 2,
		.col 	= 1
	},//�����ƶ� 16
	{
		.lrow = 1,
		.lcol = 5, 
		.row	= 1,
		.col 	= 4
	},//�� 17
	{
		.lrow = 0,
		.lcol = 5, 
		.row	= 1,
		.col 	= 3
	},//ǰ 18
	{
		.lrow = 2,
		.lcol = 5, 
		.row	= 1,
		.col 	= 2
	},//�� 19
	{
		.lrow = 3,
		.lcol = 5, 
		.row	= 1,
		.col 	= 1
	},//�� 20
	{
		.lrow = 2,
		.lcol = 5, 
		.row	= 1,
		.col 	= 5
	},//�����ſ� 21
	{
		.lrow = 2,
		.lcol = 6,
		.row	= 1,
		.col 	= 5
	},//�ſ� 22
	{
		.lrow = 3,
		.lcol = 6,
		.row	= 3,
		.col 	= 6
	}//���� 23
//	{
//		.lrow = 1,
//		.lcol = 4,
//		.row	= 1,
//		.col 	= 4
//	},//����
//	{
//		.lrow = 0,
//		.lcol = 4,
//		.row	= 1,
//		.col 	= 5
//	},//��ɳ
//	{
//		.lrow = 2,
//		.lcol = 4,
//		.row	= 1,
//		.col 	= 6
//	},//פ��
//	{
//		.lrow = 3,
//		.lcol = 4,
//		.row	= 1,
//		.col 	= 7
//	},//�㶯
//	{
//		.lrow = 0,
//		.lcol = 6,
//		.row	= 1,
//		.col 	= 1
//	}//����
}; 

#endif
