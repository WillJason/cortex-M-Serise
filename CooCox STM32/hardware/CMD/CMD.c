#define	CMD_GLOBLES
#include	"config.h"

globle void CMD_Init(void)
{
	XCSFrameData.SendFunc = Uart2Send;
	XCSFrameData.Cmd=&Uart2FrameData.Cmd;//
	XCSFrameData.RecNewFlag=&Uart2FrameData.RecNewFlag;
	XCSFrameData.RecBuf=Uart2FrameData.RecBuf;
}

static void Read_Tempreture(void)
{
	u16 r0,r1,r2,r3;
	r0=0;
	r1=0;
	r2=0;
	r3=0;

	r0=AD974_ReadData(route0);
	r1=AD974_ReadData(route1);
	r2=AD974_ReadData(route2);
	r3=AD974_ReadData(route3);

	XCSFrameData.SendBuf[INDX_TEMPRETURE]=r0>>8;
	XCSFrameData.SendBuf[INDX_TEMPRETURE+1]=r0;
	XCSFrameData.SendBuf[INDX_TEMPRETURE+2]=r1>>8;
	XCSFrameData.SendBuf[INDX_TEMPRETURE+3]=r1;
	XCSFrameData.SendBuf[INDX_TEMPRETURE+4]=r2>>8;
	XCSFrameData.SendBuf[INDX_TEMPRETURE+5]=r2;
	XCSFrameData.SendBuf[INDX_TEMPRETURE+6]=r3>>8;
	XCSFrameData.SendBuf[INDX_TEMPRETURE+7]=r3;

	r0=0;
	r1=0;
	r2=0;
	r3=0;
	IWDG_Feed();
}

static void Report(void)
{
	u8 i=0;
	u16 sum16=0;

	CMD_tx_malloc(OUTPUT_FRAME_NUM);//动态分配内存

	XCSFrameData.SendBuf[INDX_START1]=START1;
	XCSFrameData.SendBuf[INDX_START2]=START2;
	XCSFrameData.SendBuf[INDX_LEN]=OUTPUT_FRAME_NUM;
	XCSFrameData.SendBuf[INDX_CMD]=*XCSFrameData.Cmd|0x80;
	XCSFrameData.SendBuf[INDX_FIRMWARE_VER]=MCU_FIRMWARE_VER;


	WinTestOut();//读取窗口状态
	Detect();//读取普通IO状态
	Read_Tempreture();//读取温度，4路
	for(i=0;i<INDX_CHECK;i++)
	{
		sum16 = sum16 + XCSFrameData.SendBuf[i];
	}
	XCSFrameData.SendBuf[i] = sum16>>8;
	XCSFrameData.SendBuf[i+1] = sum16;//和校验

	XCSSendFrameData();//发送
	CMD_tx_free();
	IWDG_Feed();
}


static void Report_Dula_Wela(void)
{
	u8 i=0;
	u16 sum16=0;

	CMD_tx_malloc(OUTPUT_FRAME_NUM);//动态分配内存

	XCSFrameData.SendBuf[INDX_START1]=START1;
	XCSFrameData.SendBuf[INDX_START2]=START2;
	XCSFrameData.SendBuf[INDX_LEN]=OUTPUT_FRAME_NUM;
	XCSFrameData.SendBuf[INDX_CMD]=*XCSFrameData.Cmd|0x80;
	XCSFrameData.SendBuf[INDX_FIRMWARE_VER]=MCU_FIRMWARE_VER;


	WinTestOut();//读取窗口状态
	Detect_Dula_Wela();//读取普通IO状态
	Read_Tempreture();//读取温度，4路
	for(i=5;i<INDX_CHECK;i++)
	{
		sum16 = sum16 + XCSFrameData.SendBuf[i];     //校验和从窗口检测标志开始往后计算   2015.09
	}
	XCSFrameData.SendBuf[i] = sum16>>8;
	XCSFrameData.SendBuf[i+1] = sum16;//和校验

	XCSSendFrameData();//发送
	CMD_tx_free();
	IWDG_Feed();
}


static void Port_out(void)
{
	IWDG_Feed();
	DO_Me();
}

static void Port_out_Dula_Wela(void)
{
	IWDG_Feed();
	DO_Me_Dula_Wela();
}

// PC命令解析
void CmdParse(uint8 cmd)
{
	switch(cmd)
	{
	  case 0x51:Report();break;
	  case 0x52:Port_out();break;
	  case 0x53:Report_Dula_Wela();break;
	  case 0x54:Port_out_Dula_Wela();break;
	  default: break;
	}
}



