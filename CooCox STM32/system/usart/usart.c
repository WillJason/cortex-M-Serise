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
#define  UART2_GLOBLAS
#include "config.h"
#include  <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static volatile uint8 Timer2,TimerRxLed,TimerTxLed;    /* 100Hz decrement timer */
//////////////////////////////////////////////////////////////////////////////////
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos 使用
#endif


//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口1初始化
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/8/18
//版本：V1.5
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
//V1.5修改说明
//1,增加了对UCOSII的支持
//////////////////////////////////////////////////////////////////////////////////


#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记


void uart1_init(u32 bound){
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
     //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);

   //Usart1 NVIC 配置

   /* NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器*/

   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART1, &USART_InitStructure); //初始化串口
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
    USART_Cmd(USART1, ENABLE);                    //使能串口

    /*Uart1FrameData.RecDataNum = 0;
    Uart1FrameData.RecIrqNum  = 0;
    Uart1FrameData.Rindex     = 0;
    Uart1FrameData.RecNewFlag = FALSE;
    Uart1FrameData.Cmd        = 0;*/

}

//  通过UART发送一个字符
void uart1Putc(const char c)
{
	while((USART1->SR&0X40)==0);//循环发送，等待发送完毕。USART1->SR复位值0x00c0；读USART1->SR、写USART1->DR后清零。数据写入USART1->DR后，发送需时间，本轮未发送完，下轮须在此等待。
	//TimerTxLed = UART1_TX_LED_TIMER_START;
	USART1->DR = (u8) c;
}

//  通过UART发送字符串
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
    	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕
    	//TimerTxLed = UART1_TX_LED_TIMER_START;
    	USART1->DR = (u8)(*Buffer++);
    	Num--;
    }
}
//#pragma import(__use_no_semihosting)
// 向串口格式化输出字符串，如果不适用vsnprintf()，代码尺寸将大大减小。
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
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
     //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);

   //Usart1 NVIC 配置

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART2, &USART_InitStructure); //初始化串口
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
    USART_Cmd(USART2, ENABLE);                    //使能串口

    Uart2FrameData.RecDataNum = 0;
    Uart2FrameData.RecIrqNum  = 0;
    Uart2FrameData.Rindex     = 0;
    Uart2FrameData.RecNewFlag = FALSE;
    Uart2FrameData.Cmd        = 0;

}

void USART2_IRQHandler(void)                	//串口1中断服务程序
{
	u8 c;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		TimerRxLed = UART2_RX_LED_TIMER_START;
		c =USART_ReceiveData(USART2);//(USART1->DR);	//读取接收到的数据
		if (Uart2FrameData.RecNewFlag == FALSE)                            	//  只有接收的数据处理完成才接收新的数据
			{

				Uart2FrameData.RecIrqNum++;
				Uart2FrameData.RecBuf[Uart2FrameData.Rindex++] = c;            	//  从接收FIFO里读取字符;
				if (Uart2FrameData.RecIrqNum == 1)
				{
					if (Uart2FrameData.RecBuf[0] != START1)
					{
						Uart2FrameData.Rindex     = 0;                        	// 若没有接收到包头，则清各标志 继续接收新的包
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
						Uart2FrameData.Rindex     = 0;                    	// 若没有接收到包头，则清各标志 继续接收新的包
						Uart2FrameData.RecIrqNum  = 0;
					}
					else
					{
						Timer2 = UART2_RX_WAIT_TIMER_START;
					}
				}
				else if (Uart2FrameData.RecIrqNum == 3)
				{
					Uart2FrameData.RecDataNum = c;							//数据个数
					Uart2FrameData.Rindex     = 0;                       	// 从索引0开始接收数据
					if ((Uart2FrameData.RecDataNum < Uart2RecFrameNumMin) || (Uart2FrameData.RecDataNum > Uart2RecFrameNumMax)) // 判断数据个数是否有效 若无效
				    {
						Uart2FrameData.Rindex     = 0;               		// 若数据个数错误，则清各标志 继续接收新的包
						Uart2FrameData.RecIrqNum  = 0;
					}
				}
				else if (Uart2FrameData.RecIrqNum == 4)
				{
					Uart2FrameData.Cmd = c;  							//  命令
					Uart2FrameData.Rindex     = 0;  					// 从索引0开始接收数据
					// if (CheckRecFrame(Uart0D.Cmd,Uart0D.RecDataNum) == FALSE) // 判断帧是否错误
					// {
					// Uart0D.Rindex     = 0;            				// 若有错误，则清各标志 继续接收新的包
					// Uart0D.RecIrqNum  = 0;
					// }
				}
				if (Uart2FrameData.RecIrqNum > 3)                        			// 根据帧中提供的有效数据个数判断数据是否接收完成
				{
					if (Uart2FrameData.Rindex == Uart2FrameData.RecDataNum-2)      	// 数据接收完毕 置接收新数据包标志 清其他标志
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
//  通过UART发送一个字符
void uart2Putc(const char c)
{
	RS485_CON = 0;
	while((USART2->SR&0X40)==0);//循环发送，等待发送完毕。USART1->SR复位值0x00c0；读USART1->SR、写USART1->DR后清零。数据写入USART1->DR后，发送需时间，本轮未发送完，下轮须在此等待。
	TimerTxLed = UART2_TX_LED_TIMER_START;
	USART2->DR = (u8) c;
	RS485_CON = 1;
}

//  通过UART发送字符串
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
    	while((USART2->SR&0X40)==0);//循环发送,直到发送完毕
    	TimerTxLed = UART2_TX_LED_TIMER_START;
    	USART2->DR = (u8)(*Buffer++);
    	Num--;
    }
    while((USART2->SR&0X40)==0);//等待最后一个字节的发送完成
    RS485_CON = 1;
}
//#pragma import(__use_no_semihosting)
// 向串口格式化输出字符串，如果不适用vsnprintf()，代码尺寸将大大减小。
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








