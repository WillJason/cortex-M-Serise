/****************************************Copyright (c)**************************************************
**                                 Dandong Dongfang Measurement&Control Thechnology Co., Ltd,
**                                 丹东东方测控技术有限公司
**                                 http://www.dfmc.cc
**
**--------------文件信息-------------------------------------------------------------------------------
** 文件名称：              	 LED.c
** 最终修改日期：
** 最终版本：            	 v1.0
** 描述：                	 源文件
**
**------------------------------------------------------------------------------------------------------
** 创建者：                   于海明
** 创建日期：                2011/11/1
** 版本：                	 v1.0
** 描述：
**
**------------------------------------------------------------------------------------------------------
** 修改者：
** 修改日期：
** 版本：
** 描述：
**
********************************************************************************************************/
#define LED_GLOBLAS
#include "config.h"

//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//
//////////////////////////////////////////////////////////////////////////////////

//初始化PB5和PE5为输出口.并使能这两个口的时钟
//LED IO初始化
void LED_Init(void)
{

 GPIO_InitTypeDef  GPIO_InitStructure;

 //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz

 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOB,GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6); 						 //PE.5 输出高
}

