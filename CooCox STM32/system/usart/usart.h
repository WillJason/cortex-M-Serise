#ifndef __USART_H
#define __USART_H
//UART1���

extern void Uart1Send (char *Buffer,uint8  NByte);

#define USART_REC_LEN  			200  	//�����������ֽ��� 200
//#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

extern void uart1_init(u32 bound);

extern void uart1Puts(const char *s);

extern void uart1Putc(const char c);

extern void uart1_Printf(char *fmt,...);


//UART2���
#define LED_TX2 LED0
#define LED_RX2 LED1

#define RS485_CON PAout(4)

#define RX2Led_On()  LED_On(LED_RX2)
#define RX2Led_Off() LED_Off(LED_RX2)
#define TX2Led_On()  LED_On(LED_TX2)
#define TX2Led_Off() LED_Off(LED_TX2)
/**********************************************************************************/
////////////////////////////////UART�ĺ궨��///////////////////////////////////////
/**********************************************************************************/
#define Uart2RecFrameBufNum    128               //���ջ������ֽ���
#define Uart2RecFrameNumMin    2               //��������֡��������Сֵ
#define Uart2RecFrameNumMax    Uart2RecFrameBufNum  //��������֡���������ֵ

#define UART2_BPS 9600

// uart���ճ�ʱ��������
#define UART2_RX_WAIT_TIME     50 // 50*10ms
#define UART2_RX_WAIT_TIME_OUT 1 //
#define UART2_RX_WAIT_TIMER_START (UART2_RX_WAIT_TIME + UART2_RX_WAIT_TIME_OUT)
#define UART2_RX_WAIT_TIMER_STOP 0

// uart_RXled��ʱ��������
#define UART2_RX_LED_TIME     2 // 2*10ms
#define UART2_RX_LED_TIME_OUT 1 //
#define UART2_RX_LED_TIMER_START (UART2_RX_LED_TIME + UART2_RX_LED_TIME_OUT)
#define UART2_RX_LED_TIMER_STOP 0

// uart_TXled��ʱ��������
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
   volatile uint8  RecDataNum;     									//����֡�����ݵĸ�������
   volatile uint8  RecIrqNum;
   volatile uint8  Cmd;
   volatile uint8  Rindex;         									//ͨ�����ݻ���������ָ��
   volatile uint8  RecNewFlag;
   char  		   RecBuf[Uart2RecFrameBufNum];   					//���ջ�����UARTFRAME;

}  UART2FRAME;

UART2_EXT UART2FRAME Uart2FrameData;

extern void Uart2Send (char *Buffer,uint8  NByte);

extern void uart2_wait_timerproc (void);

#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART2_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
extern u16 USART_RX_STA;         		//����״̬���
//����봮���жϽ��գ��벻Ҫע�����º궨��
extern void uart2_init(u32 bound);

extern void uart2Puts(const char *s);

extern void uart2Putc(const char c);

extern void uart2_Printf(char *fmt,...);


#endif


