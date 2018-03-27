#ifndef __USART_H
#define __USART_H
//UART1相关

extern void Uart1Send (char *Buffer,uint8  NByte);

#define USART_REC_LEN  			200  	//定义最大接收字节数 200
//#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

extern void uart1_init(u32 bound);

extern void uart1Puts(const char *s);

extern void uart1Putc(const char c);

extern void uart1_Printf(char *fmt,...);


//UART2相关
#define LED_TX2 LED0
#define LED_RX2 LED1

#define RS485_CON PAout(4)

#define RX2Led_On()  LED_On(LED_RX2)
#define RX2Led_Off() LED_Off(LED_RX2)
#define TX2Led_On()  LED_On(LED_TX2)
#define TX2Led_Off() LED_Off(LED_TX2)
/**********************************************************************************/
////////////////////////////////UART的宏定义///////////////////////////////////////
/**********************************************************************************/
#define Uart2RecFrameBufNum    128               //接收缓冲区字节数
#define Uart2RecFrameNumMin    2               //接收数据帧个数的最小值
#define Uart2RecFrameNumMax    Uart2RecFrameBufNum  //接收数据帧个数的最大值

#define UART2_BPS 9600

// uart接收超时参数定义
#define UART2_RX_WAIT_TIME     50 // 50*10ms
#define UART2_RX_WAIT_TIME_OUT 1 //
#define UART2_RX_WAIT_TIMER_START (UART2_RX_WAIT_TIME + UART2_RX_WAIT_TIME_OUT)
#define UART2_RX_WAIT_TIMER_STOP 0

// uart_RXled超时参数定义
#define UART2_RX_LED_TIME     2 // 2*10ms
#define UART2_RX_LED_TIME_OUT 1 //
#define UART2_RX_LED_TIMER_START (UART2_RX_LED_TIME + UART2_RX_LED_TIME_OUT)
#define UART2_RX_LED_TIMER_STOP 0

// uart_TXled超时参数定义
#define UART2_TX_LED_TIME     1 // 2*10ms
#define UART2_TX_LED_TIME_OUT 1 //
#define UART2_TX_LED_TIMER_START (UART2_TX_LED_TIME + UART2_TX_LED_TIME_OUT)
#define UART2_TX_LED_TIMER_STOP 0


#ifdef  UART2_GLOBLAS
#define UART2_EXT
#else
#define UART2_EXT extern
#endif

typedef  struct
{
   volatile uint8  RecDataNum;     									//数据帧中数据的个数变量
   volatile uint8  RecIrqNum;
   volatile uint8  Cmd;
   volatile uint8  Rindex;         									//通信数据缓冲区接受指针
   volatile uint8  RecNewFlag;
   char  		   RecBuf[Uart2RecFrameBufNum];   					//接收缓冲区UARTFRAME;

}  UART2FRAME;

UART2_EXT UART2FRAME Uart2FrameData;

extern void Uart2Send (char *Buffer,uint8  NByte);

extern void uart2_wait_timerproc (void);

#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART2_RX 			1		//使能（1）/禁止（0）串口1接收

extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u16 USART_RX_STA;         		//接收状态标记
//如果想串口中断接收，请不要注释以下宏定义
extern void uart2_init(u32 bound);

extern void uart2Puts(const char *s);

extern void uart2Putc(const char c);

extern void uart2_Printf(char *fmt,...);


#endif


