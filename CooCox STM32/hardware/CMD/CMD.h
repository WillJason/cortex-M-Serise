#ifndef	_CMD_H
#define	_CMD_H

#ifdef	CMD_GLOBLES
#define	CMD_EXT
#else
#define CMD_EXT	extern
#endif

typedef  struct
{
   volatile uint8  *Cmd;
   volatile uint8  *RecNewFlag;
   char            *SendBuf; 					// 发送缓冲区
   char  		   *RecBuf;   					// 接收缓冲区UARTFRAME;
   void 		   (*SendFunc)(char *,uint8);
}  UARTCMDFRAME;

CMD_EXT UARTCMDFRAME XCSFrameData;

#define INDX_START1 			0
#define INDX_START2 			1
#define INDX_LEN 				2
#define INDX_CMD 				3
#define INDX_FIRMWARE_VER 		4
#define INDX_WIN_TEST 			5
#define INDX_Detect 			6
#define INDX_TEMPRETURE 		12
#define INDX_CHECK				20



//数据包头 必须为2个
#define START1	  0xaa
#define START2    0x55

#define	OUTPUT_FRAME_NUM	20//除字头外要发送给上位机的字节数


//返回应答的状态
#define ACK_CMD_OK_MASK              	0xf0
#define ACK_CMD_ERR_MASK              	0x80
#define CMD_TX_ACK_PC_BUF_LEN            3

#define XCSSendFrameData() XCSFrameData.SendFunc(XCSFrameData.SendBuf,(XCSFrameData.SendBuf[INDX_LEN]+2))


// 动态内存分配，必须与free()成对使用

#define CMD_tx_malloc(len)	XCSFrameData.SendBuf = (char *)malloc(len+2); 	\
							if(XCSFrameData.SendBuf!=NULL)					\
							{												\
								memset(XCSFrameData.SendBuf,'\0',len+2);	\
							}//memset()内存空间初始化

#define CMD_tx_free()		free(XCSFrameData.SendBuf)


//相关函数
extern void CMD_Init(void);
extern void CmdParse(uint8 cmd);

#endif

