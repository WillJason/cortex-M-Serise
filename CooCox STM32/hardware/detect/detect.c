#define	DETECT_GLOBLES
#include	"config.h"
u8 flag_t=0;
u8 flag_p=0;
u8 flag_n=0;
u8  inputstate[INPUT_PORT_NUM];

/*******************************************************************************
** 函数名称 ：detectint()
** 函数功能 ：初始化
** 入口参数 ：无
** 出口参数 ：无
********************************************************************************/
void detectint(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOD, ENABLE );
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOE, ENABLE );
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOF, ENABLE );

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   //上拉输入
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   //上拉输入
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   //上拉输入
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_11	\
								|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   //上拉输入
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   //上拉输入
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOE,GPIO_Pin_11|GPIO_Pin_12); 	//

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11	\
								|GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   //上拉输入
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

}

 uint8 WinOpenFlag;               //检测电路开路次数标志
 uint8 WinBreakFlag;              //检测到窗口破裂次数标志
 uint8 WinTOVERFlag;
 /*******************************************************************************
** 函数名称 ：WinPTest()
** 函数功能 ：查看窗口是否开路
** 入口参数 ：无
** 出口参数 ：返回值01时，窗口开路。返回值00时，窗口完好。
********************************************************************************/
extern void WinPTest(void)
{
   uint8 i;
   DNKGOUT(0);                             //加正向电压
   PNKGOUT(1);
   WinOpenFlag = 0;
   delay_ms(50);                           //要有足够的延时，保证光耦的动作时间
   for (i = 0;i < TESTWINNUM;i++)
   {
      if (RD_WINKGIN() == 0)
	  WinOpenFlag = (WinOpenFlag + 1);//检测电路开路次数标志加1
      delay_us(100);
      WdogFeed();
   }
   if (WinOpenFlag >= TESTWINNUM)
   {
	 // LED0=0; 	 //	开指示灯D3
	  flag_t=1;
	  WdogFeed();
   }
   else	if ((flag_t==0)&&(RD_WINKGIN()==1))
   {
	 //  LED0=1; 	 //	关指示灯D3
	   WdogFeed();
   }
   else
   {
	  // LED0=0; 	 //	开指示灯D3
   }

}

/*******************************************************************************
** 函数名称 ：WinNTest()
** 函数功能 ：查看窗口是否短路
** 入口参数 ：无
** 出口参数 ：返回值01时，窗口短路。返回值00时，窗口完好。
********************************************************************************/
static void WinNTest(void)
{
   uint8 i;
   DNKGOUT(1);                              //加反向电压
   PNKGOUT(0);
   WinBreakFlag=0;
   delay_ms(50);//要有足够的延时，保证光耦的动作时间
   for (i = 0;i < TESTWINNUMCOP;i++)
   {
      if (RD_WINKGIN() == 0)
	  WinBreakFlag = (WinBreakFlag + 1);//检测窗口破裂次数标志加1
      delay_us(100);
      WdogFeed();
   }
   if (WinBreakFlag >= TESTWINNUMCOP)
   {
	 // LED1=0;	//开指示灯D4
	  flag_p=1;
	  WdogFeed();
   }
   else if((flag_p==0)&&(RD_WINKGIN()==1))
   {
	 //  LED1=1;	  //  关指示灯D4
	   WdogFeed();
   }
   else
   {
	 //  LED1=0;	//开指示灯D4
   }
}
/*******************************************************************************
** 函数名称 ：WinTTest()
** 函数功能 ：查看是否超温
** 入口参数 ：无
** 出口参数 ：返回值01时，超温。返回值00时，正常。
********************************************************************************/
static void WinTTest(void)
{
   uint8 i;
   WinTOVERFlag = 0;
   delay_us(50);                            //要有足够的延时，保证光耦的动作时间
   for (i = 0;i < TESTWIN_TEMNUM;i++)
   {
   if (RD_TEMKGIN() == 0)
   	  WinTOVERFlag = (WinTOVERFlag + 1);//检测电路开路次数标志加1
   	  delay_us(100);
   	  WdogFeed();
   }
   if (WinTOVERFlag >= TESTWIN_TEMNUM)
   {
	 // LED2=0;//	   开指示灯D5
	  flag_n=1;
	  WdogFeed();
   }
   else	if ((flag_n==0)&&(RD_TEMKGIN() == 1))
   {
	 // LED2=1; 	  //	 关指示灯D5
	  WdogFeed();
   }
   else
   	 {
	 //  LED2=0;//	   开指示灯D5//不正常
	 }
}

/*******************************************************************************
** 函数名称 ：WinTestOut()
** 函数功能 ：对窗口标志位进行检测，并执行相应操作，常闭
** 入口参数 ：无
** 出口参数 ：
********************************************************************************/
void WinTestOut(void)
{
	WinPTest();
	WinNTest();
	WinTTest();
	if ( (flag_t)|| (flag_p)|| (flag_n)) // 任何一个报警
	{
	  SHUTDOWN(0);
	  if((flag_t)|| (flag_p))
	  	{
		  	//WIN_OUT(0);
		  	//WINTEM_OUT(1);
			WdogFeed();
			if(flag_t)
			{
				XCSFrameData.SendBuf[INDX_WIN_TEST]|=(0x01<<0);//	WIN_OPEN;
			}
			else
			{
				XCSFrameData.SendBuf[INDX_WIN_TEST]|=(0x01<<1);  //	WIN_BREAK;
				//XCSFrameData.SendBuf[INDX_WIN_TEST]=0x01;
			}
		}
	else
		{
			//WIN_OUT(1);
			//WINTEM_OUT(0);
			WdogFeed();
			XCSFrameData.SendBuf[INDX_WIN_TEST]|=(0x01<<2);  //WinT_over;
			//XCSFrameData.SendBuf[INDX_WIN_TEST]=0x01;
		}
   }
   else                                                    // 都没有报警
   {
	   SHUTDOWN(1);
	   //WINTEM_OUT(1);
	  // WIN_OUT(1);
	   WdogFeed();
	   XCSFrameData.SendBuf[INDX_WIN_TEST]=0x00; //	WIN_NORMAL;
	  // XCSFrameData.SendBuf[INDX_WIN_TEST]=0x01;
   }
}

/*******************************************************************************
** 函数名称 ：InputTest()
** 函数功能 ：查看是否为高
** 入口参数 ：PORT_IN
** 出口参数 ：返回值01时，不正常。返回值00时，正常。
********************************************************************************/
static  u8 InputDetect(u8 PORT_IN)
{
   uint8 i;
   u8 DETECT_FLAG = 0;
   for (i = 0;i < INPUTDETECT_NUM;i++)
   {
	   if (PORT_IN == 1)
		   DETECT_FLAG = (DETECT_FLAG + 1);//标志加1
		   delay_us(1);
		   WdogFeed();
   }
   if (DETECT_FLAG >= (INPUTDETECT_NUM-2))
   {
	  WdogFeed();
	  return 0x01;
   }
   else
   {
	  WdogFeed();
	  return 0x00;
   }
}

void Detect(void)
{
	u8 i = 8,t=0;

	inputstate[0] = InputDetect(KGIN5);
	inputstate[1] = InputDetect(KGIN6);
	inputstate[2] = InputDetect(KGIN28);
	inputstate[3] = InputDetect(KGIN27);
	inputstate[4] = InputDetect(KGIN17);
	inputstate[5] = InputDetect(KGIN18);
	inputstate[6] = InputDetect(KGIN8);
	inputstate[7] = InputDetect(KGIN7);
	inputstate[8] = InputDetect(KGIN3);
	inputstate[9] = InputDetect(KGIN4);
	inputstate[10] = InputDetect(KGIN16);
	inputstate[11] = InputDetect(KGIN15);
	inputstate[12] = InputDetect(KGIN30);
	inputstate[13] = InputDetect(KGIN29);
	inputstate[14] = InputDetect(KGIN19);
	inputstate[15] = InputDetect(KGIN20);
	inputstate[16] = InputDetect(KGIN32);
	inputstate[17] = InputDetect(KGIN31);
	inputstate[18] = InputDetect(KGIN21);
	inputstate[19] = InputDetect(KGIN22);
	inputstate[20] = InputDetect(KGIN34);
	inputstate[21] = InputDetect(KGIN33);
	inputstate[22] = InputDetect(KGIN23);
	inputstate[23] = InputDetect(BDQYIN1);
	inputstate[24] = InputDetect(BDQYIN2);
	inputstate[25] = InputDetect(KGIN10);
	inputstate[26] = InputDetect(KGIN9);
	inputstate[27] = InputDetect(DGPREIN);
	inputstate[28] = InputDetect(KGIN37);
	inputstate[29] = InputDetect(KGIN38);
	inputstate[30] = InputDetect(QYIN);
	inputstate[31] = InputDetect(KGIN12);
	inputstate[32] = InputDetect(KGIN11);
	inputstate[33] = InputDetect(KGIN1);
	inputstate[34] = InputDetect(KGIN2);
	inputstate[35] = InputDetect(KGIN14);
	inputstate[36] = InputDetect(KGIN13);
	inputstate[37] = InputDetect(KGIN24);
	inputstate[38] = InputDetect(KGIN36);
	inputstate[39] = InputDetect(KGIN35);
	inputstate[40] = InputDetect(KGIN25);
	inputstate[41] = InputDetect(KGIN26);

	for(i=8;i>0;i--)
	{
		t=i-1;
		if(inputstate[t]==0x01)
		{
			XCSFrameData.SendBuf[INDX_Detect]|=(0x01<<t);
		}
		else
		if(inputstate[t]==0x00)
		{
			XCSFrameData.SendBuf[INDX_Detect]&=~(0x01<<t);
			//XCSFrameData.SendBuf[INDX_Detect]=0x02;
		}
	}
	i=8,t=0;
	for(i=8;i>0;i--)
	{
		t=i-1;
		if(inputstate[t+8]==0x01)
		{
			XCSFrameData.SendBuf[INDX_Detect+1]|=(0x01<<t);
		}
		else
		if(inputstate[t+8]==0x00)
		{
			XCSFrameData.SendBuf[INDX_Detect+1]&=~(0x01<<t);
			//XCSFrameData.SendBuf[INDX_Detect+1]=0x02;
		}
	}
	i=8,t=0;
	for(i=8;i>0;i--)
	{
		t=i-1;
		if(inputstate[t+16]==0x01)
		{
			XCSFrameData.SendBuf[INDX_Detect+2]|=(0x01<<t);
		}
		else
		if(inputstate[t+16]==0x00)
		{
			XCSFrameData.SendBuf[INDX_Detect+2]&=~(0x01<<t);
			//XCSFrameData.SendBuf[INDX_Detect+2]=0x02;
		}
	}
	i=8,t=0;
	for(i=8;i>0;i--)
	{
		t=i-1;
		if(inputstate[t+24]==0x01)
		{
			XCSFrameData.SendBuf[INDX_Detect+3]|=(0x01<<t);
		}
		else
		if(inputstate[t+24]==0x00)
		{
			XCSFrameData.SendBuf[INDX_Detect+3]&=~(0x01<<t);
			//XCSFrameData.SendBuf[INDX_Detect+3]=0x02;
		}
	}
	i=8,t=0;
	for(i=8;i>0;i--)
	{
		t=i-1;
		if(inputstate[t+32]==0x01)
		{
			XCSFrameData.SendBuf[INDX_Detect+4]|=(0x01<<t);
		}
		else
		if(inputstate[t+32]==0x00)
		{
			XCSFrameData.SendBuf[INDX_Detect+4]&=~(0x01<<t);
			//XCSFrameData.SendBuf[INDX_Detect+4]=0x02;
		}
	}
	i=8,t=0;
	for(i=8;i>0;i--)
	{
		t=i-1;
		if(inputstate[t+40]==0x01)
		{
			XCSFrameData.SendBuf[INDX_Detect+5]|=(0x01<<t);
		}
		else
		if(inputstate[t+40]==0x00)
		{
			XCSFrameData.SendBuf[INDX_Detect+5]&=~(0x01<<t);
			//XCSFrameData.SendBuf[INDX_Detect+5]=0x02;
		}
	}
	i=8;
}


void Detect_Dula_Wela(void)
{
	u8 i = 8,t=0;

	inputstate[0] = InputDetect(BDQYIN1);
	inputstate[1] = InputDetect(BDQYIN2);
	inputstate[2] = InputDetect(DGPREIN);
	inputstate[3] = InputDetect(QYIN);
	inputstate[4] = InputDetect(KGIN1);
	inputstate[5] = InputDetect(KGIN2);
	inputstate[6] = InputDetect(KGIN3);
	inputstate[7] = InputDetect(KGIN4);
	inputstate[8] = InputDetect(KGIN5);
	inputstate[9] = InputDetect(KGIN6);
	inputstate[10] = InputDetect(KGIN8);
	inputstate[11] = InputDetect(KGIN7);
	inputstate[12] = InputDetect(KGIN10);
	inputstate[13] = InputDetect(KGIN9);
	inputstate[14] = InputDetect(KGIN12);
	inputstate[15] = InputDetect(KGIN11);
	inputstate[16] = InputDetect(KGIN14);
	inputstate[17] = InputDetect(KGIN13);
	inputstate[18] = InputDetect(KGIN16);
	inputstate[19] = InputDetect(KGIN15);
	inputstate[20] = InputDetect(KGIN17);
	inputstate[21] = InputDetect(KGIN18);
	inputstate[22] = InputDetect(KGIN19);
	inputstate[23] = InputDetect(KGIN20);
	inputstate[24] = InputDetect(KGIN21);
	inputstate[25] = InputDetect(KGIN22);
	inputstate[26] = InputDetect(KGIN23);
	inputstate[27] = InputDetect(KGIN24);
	inputstate[28] = InputDetect(KGIN25);
	inputstate[29] = InputDetect(KGIN26);
	inputstate[30] = InputDetect(KGIN28);
	inputstate[31] = InputDetect(KGIN27);
	inputstate[32] = InputDetect(KGIN30);
	inputstate[33] = InputDetect(KGIN29);
	inputstate[34] = InputDetect(KGIN32);
	inputstate[35] = InputDetect(KGIN31);
	inputstate[36] = InputDetect(KGIN34);
	inputstate[37] = InputDetect(KGIN33);
	inputstate[38] = InputDetect(KGIN36);
	inputstate[39] = InputDetect(KGIN35);
	inputstate[46] = InputDetect(KGIN37);
	inputstate[47] = InputDetect(KGIN38);

	for(i=8;i>0;i--)
	{
		t=i-1;
		if(inputstate[t]==0x01)
		{
			XCSFrameData.SendBuf[INDX_Detect]|=(0x01<<t);
		}
		else
		if(inputstate[t]==0x00)
		{
			XCSFrameData.SendBuf[INDX_Detect]&=~(0x01<<t);
			//XCSFrameData.SendBuf[INDX_Detect]=0x02;
		}
	}
	i=8,t=0;
	for(i=8;i>0;i--)
	{
		t=i-1;
		if(inputstate[t+8]==0x01)
		{
			XCSFrameData.SendBuf[INDX_Detect+1]|=(0x01<<t);
		}
		else
		if(inputstate[t+8]==0x00)
		{
			XCSFrameData.SendBuf[INDX_Detect+1]&=~(0x01<<t);
			//XCSFrameData.SendBuf[INDX_Detect+1]=0x02;
		}
	}
	i=8,t=0;
	for(i=8;i>0;i--)
	{
		t=i-1;
		if(inputstate[t+16]==0x01)
		{
			XCSFrameData.SendBuf[INDX_Detect+2]|=(0x01<<t);
		}
		else
		if(inputstate[t+16]==0x00)
		{
			XCSFrameData.SendBuf[INDX_Detect+2]&=~(0x01<<t);
			//XCSFrameData.SendBuf[INDX_Detect+2]=0x02;
		}
	}
	i=8,t=0;
	for(i=8;i>0;i--)
	{
		t=i-1;
		if(inputstate[t+24]==0x01)
		{
			XCSFrameData.SendBuf[INDX_Detect+3]|=(0x01<<t);
		}
		else
		if(inputstate[t+24]==0x00)
		{
			XCSFrameData.SendBuf[INDX_Detect+3]&=~(0x01<<t);
			//XCSFrameData.SendBuf[INDX_Detect+3]=0x02;
		}
	}
	i=8,t=0;
	for(i=8;i>0;i--)
	{
		t=i-1;
		if(inputstate[t+32]==0x01)
		{
			XCSFrameData.SendBuf[INDX_Detect+4]|=(0x01<<t);
		}
		else
		if(inputstate[t+32]==0x00)
		{
			XCSFrameData.SendBuf[INDX_Detect+4]&=~(0x01<<t);
			//XCSFrameData.SendBuf[INDX_Detect+4]=0x02;
		}
	}
	i=8,t=0;
	for(i=8;i>0;i--)
	{
		t=i-1;
		if(inputstate[t+40]==0x01)
		{
			XCSFrameData.SendBuf[INDX_Detect+5]|=(0x01<<t);
		}
		else
		if(inputstate[t+40]==0x00)
		{
			XCSFrameData.SendBuf[INDX_Detect+5]&=~(0x01<<t);
			//XCSFrameData.SendBuf[INDX_Detect+5]=0x02;
		}
	}
	i=8;
}

