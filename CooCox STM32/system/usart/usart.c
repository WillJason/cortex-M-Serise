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
#define  UART2_GLOBLAS
#include "config.h"
#include  <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static volatile uint8 Timer2,TimerRxLed,TimerTxLed;    /* 100Hz decrement timer */
//////////////////////////////////////////////////////////////////////////////////
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos ʹ��
#endif


//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/8/18
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵��
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
//////////////////////////////////////////////////////////////////////////////////


#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���


void uart1_init(u32 bound){
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
     //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);

   //Usart1 NVIC ����

   /* NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���*/

   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART1, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���

    /*Uart1FrameData.RecDataNum = 0;
    Uart1FrameData.RecIrqNum  = 0;
    Uart1FrameData.Rindex     = 0;
    Uart1FrameData.RecNewFlag = FALSE;
    Uart1FrameData.Cmd        = 0;*/

}

//  ͨ��UART����һ���ַ�
void uart1Putc(const char c)
{
	while((USART1->SR&0X40)==0);//ѭ�����ͣ��ȴ�������ϡ�USART1->SR��λֵ0x00c0����USART1->SR��дUSART1->DR�����㡣����д��USART1->DR�󣬷�����ʱ�䣬����δ�����꣬�������ڴ˵ȴ���
	//TimerTxLed = UART1_TX_LED_TIMER_START;
	USART1->DR = (u8) c;
}

//  ͨ��UART�����ַ���
void uart1Puts(const char *s)
{
    while (*s != '\0') uart1Putc(*(s++));
}

void Uart1Send (char *Buffer,uint8  NByte)
{
	uint8 Num;
	Num = NByte;

    while (Num)
    {
    	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������
    	//TimerTxLed = UART1_TX_LED_TIMER_START;
    	USART1->DR = (u8)(*Buffer++);
    	Num--;
    }
}
//#pragma import(__use_no_semihosting)
// �򴮿ڸ�ʽ������ַ��������������vsnprintf()������ߴ罫����С��
void uart1_Printf(char *fmt,...)
{
	va_list ap;
	char string[256];

	va_start(ap,fmt);
	vsnprintf(string,sizeof(string),fmt,ap);
	uart1Puts(string);
	va_end(ap);
}
#endif

#ifdef EN_USART2_RX
void uart2_init(u32 bound){
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
     //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);

   //Usart1 NVIC ����

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART2, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
    USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���

    Uart2FrameData.RecDataNum = 0;
    Uart2FrameData.RecIrqNum  = 0;
    Uart2FrameData.Rindex     = 0;
    Uart2FrameData.RecNewFlag = FALSE;
    Uart2FrameData.Cmd        = 0;

}

void USART2_IRQHandler(void)                	//����1�жϷ������
{
	u8 c;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		TimerRxLed = UART2_RX_LED_TIMER_START;
		c =USART_ReceiveData(USART2);//(USART1->DR);	//��ȡ���յ�������
		if (Uart2FrameData.RecNewFlag == FALSE)                            	//  ֻ�н��յ����ݴ�����ɲŽ����µ�����
			{

				Uart2FrameData.RecIrqNum++;
				Uart2FrameData.RecBuf[Uart2FrameData.Rindex++] = c;            	//  �ӽ���FIFO���ȡ�ַ�;
				if (Uart2FrameData.RecIrqNum == 1)
				{
					if (Uart2FrameData.RecBuf[0] != START1)
					{
						Uart2FrameData.Rindex     = 0;                        	// ��û�н��յ���ͷ���������־ ���������µİ�
						Uart2FrameData.RecIrqNum  = 0;
					}
					else
					{
						Timer2 = UART2_RX_WAIT_TIMER_START;
					}
				}
				else if (Uart2FrameData.RecIrqNum == 2)
				{
					if (Uart2FrameData.RecBuf[1] != START2)
					{
						Uart2FrameData.Rindex     = 0;                    	// ��û�н��յ���ͷ���������־ ���������µİ�
						Uart2FrameData.RecIrqNum  = 0;
					}
					else
					{
						Timer2 = UART2_RX_WAIT_TIMER_START;
					}
				}
				else if (Uart2FrameData.RecIrqNum == 3)
				{
					Uart2FrameData.RecDataNum = c;							//���ݸ���
					Uart2FrameData.Rindex     = 0;                       	// ������0��ʼ��������
					if ((Uart2FrameData.RecDataNum < Uart2RecFrameNumMin) || (Uart2FrameData.RecDataNum > Uart2RecFrameNumMax)) // �ж����ݸ����Ƿ���Ч ����Ч
				    {
						Uart2FrameData.Rindex     = 0;               		// �����ݸ��������������־ ���������µİ�
						Uart2FrameData.RecIrqNum  = 0;
					}
				}
				else if (Uart2FrameData.RecIrqNum == 4)
				{
					Uart2FrameData.Cmd = c;  							//  ����
					Uart2FrameData.Rindex     = 0;  					// ������0��ʼ��������
					// if (CheckRecFrame(Uart0D.Cmd,Uart0D.RecDataNum) == FALSE) // �ж�֡�Ƿ����
					// {
					// Uart0D.Rindex     = 0;            				// ���д����������־ ���������µİ�
					// Uart0D.RecIrqNum  = 0;
					// }
				}
				if (Uart2FrameData.RecIrqNum > 3)                        			// ����֡���ṩ����Ч���ݸ����ж������Ƿ�������
				{
					if (Uart2FrameData.Rindex == Uart2FrameData.RecDataNum-2)      	// ���ݽ������ �ý��������ݰ���־ ��������־
					{
						Uart2FrameData.Rindex     = 0;
						Uart2FrameData.RecIrqNum  = 0;
						Uart2FrameData.RecNewFlag = TRUE;
						Timer2 = 0;
					}
				}
			}
		}

}
//  ͨ��UART����һ���ַ�
void uart2Putc(const char c)
{
	RS485_CON = 0;
	while((USART2->SR&0X40)==0);//ѭ�����ͣ��ȴ�������ϡ�USART1->SR��λֵ0x00c0����USART1->SR��дUSART1->DR�����㡣����д��USART1->DR�󣬷�����ʱ�䣬����δ�����꣬�������ڴ˵ȴ���
	TimerTxLed = UART2_TX_LED_TIMER_START;
	USART2->DR = (u8) c;
	RS485_CON = 1;
}

//  ͨ��UART�����ַ���
void uart2Puts(const char *s)
{
	RS485_CON = 0;
    while (*s != '\0') uart2Putc(*(s++));
    RS485_CON = 1;
}

void Uart2Send (char *Buffer,uint8  NByte)
{
	uint8 Num;
	Num = NByte;

	RS485_CON = 0;

    while (Num)
    {
    	while((USART2->SR&0X40)==0);//ѭ������,ֱ���������
    	TimerTxLed = UART2_TX_LED_TIMER_START;
    	USART2->DR = (u8)(*Buffer++);
    	Num--;
    }
    while((USART2->SR&0X40)==0);//�ȴ����һ���ֽڵķ������
    RS485_CON = 1;
}
//#pragma import(__use_no_semihosting)
// �򴮿ڸ�ʽ������ַ��������������vsnprintf()������ߴ罫����С��
void uart2_Printf(char *fmt,...)
{
	va_list ap;
	char string[256];

	RS485_CON = 0;

	va_start(ap,fmt);
	vsnprintf(string,sizeof(string),fmt,ap);
	uart2Puts(string);
	va_end(ap);

	RS485_CON = 1;
}


void uart2_wait_timerproc (void)
{
    uint8 n2,nrx,ntx;

    n2 = Timer2;                        /* 100Hz decrement timer */
    if (n2 > UART2_RX_WAIT_TIME_OUT)
    {
    	Timer2 = --n2;
    }
    else if(n2 == UART2_RX_WAIT_TIME_OUT)
    {
    	Uart2FrameData.Rindex     = 0;
    	Uart2FrameData.RecIrqNum  = 0;
    	Uart2FrameData.RecNewFlag = FALSE;
    	Timer2 = UART2_RX_WAIT_TIMER_STOP;
    }

    nrx = TimerRxLed;                        /* 100Hz decrement timer */
    if (nrx > UART2_RX_LED_TIME_OUT)
    {
    	RX2Led_On();
    	TimerRxLed = --nrx;
    }
    else if(nrx == UART2_RX_LED_TIME_OUT)
    {
    	RX2Led_Off();
    	TimerRxLed = UART2_RX_LED_TIMER_STOP;
    }

    ntx = TimerTxLed;                        /* 100Hz decrement timer */
    if (ntx > UART2_TX_LED_TIME_OUT)
    {
    	TX2Led_On();
    	TimerTxLed = --ntx;
    }
    else if(ntx == UART2_TX_LED_TIME_OUT)
    {
    	TX2Led_Off();
    	TimerTxLed = UART2_TX_LED_TIMER_STOP;
    }

}

#endif








