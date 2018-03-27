/****************************************Copyright (c)**************************************************
**                                 Dandong Dongfang Measurement&Control Thechnology Co., Ltd,
**                                 ����������ؼ������޹�˾
**                                 http://www.dfmc.cc
**
**--------------�ļ���Ϣ-------------------------------------------------------------------------------
** �ļ����ƣ�              	 LED.c
** �����޸����ڣ�
** ���հ汾��            	 v1.0
** ������                	 Դ�ļ�
**
**------------------------------------------------------------------------------------------------------
** �����ߣ�                   �ں���
** �������ڣ�                2011/11/1
** �汾��                	 v1.0
** ������
**
**------------------------------------------------------------------------------------------------------
** �޸��ߣ�
** �޸����ڣ�
** �汾��
** ������
**
********************************************************************************************************/
#define LED_GLOBLAS
#include "config.h"

//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//////////////////////////////////////////////////////////////////////////////////

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��
//LED IO��ʼ��
void LED_Init(void)
{

 GPIO_InitTypeDef  GPIO_InitStructure;

 //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB,PE�˿�ʱ��

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz

 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOB,GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6); 						 //PE.5 �����
}

