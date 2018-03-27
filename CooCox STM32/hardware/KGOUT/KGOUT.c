#define	KGOUT_GLOBLES
#include	"config.h"

u8  outputstate[KGOUTNUM];
u8  outputstateM[KGOUT_ByteNUM];
u8  Dula_Wela_I2c_Outputstate[2];

void DO_MeInit()
{
	u8  i;
	for(i=0;i<KGOUTNUM;i++)
	{
		outputstate[i] = 0X00;
	}
	i= 0 ;
	for(i=0;i<KGOUT_ByteNUM;i++)
	{
		outputstateM[i] = 0x00;
	}

}

void KGOUT_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	//	PA0/1/5/6/7
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//	PB0/1/8/9
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );//	PC0/1/2/3/4/5/13/14/15
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOE, ENABLE );//	PE0/1/2/3/4/5/6/7/8
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOF, ENABLE );//	PF ALL
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOG, ENABLE );//	PG0/1
//PA
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7); 	//
//PB
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8|GPIO_Pin_9); 	//
//PC
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); 	//
//PE
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_SetBits(GPIOE,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8); 	//
//PF
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_SetBits(GPIOF,GPIO_Pin_All); 	//
//PG
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_SetBits(GPIOG,GPIO_Pin_0|GPIO_Pin_1); 	//
}

static void test_on(uint8 id)
{
	switch(id)
	{
		case 0:KGOUT35_ON();
			break;
		case 1:KGOUT45_ON();
			break;
		case 2:KGOUT46_ON();
			break;
		case 3:COLDING2_ON();
			break;
		case 4:HEATING_ON();
			break;

		case 5:BDQYOUT1_ON();
			break;
		case 6:BDQYOUT2_ON();
			break;
		case 7:KGOUT17_ON();
			break;
		case 8:KGOUT18_ON();
			break;

		case 9:KGOUT33_ON();
			break;
		case 10:KGOUT43_ON();
			break;
		case 11:KGOUT44_ON();
			break;
		case 12:KGOUT36_ON();
			break;
		case 13:KGOUT48_ON();
			break;
		case 14:KGOUT47_ON();
			break;
		case 15:KGOUT26_ON();
			break;
		case 16:KGOUT28_ON();
			break;
		case 17:KGOUT27_ON();
			break;

		case 18:KGOUT19_ON();
			break;
		case 19:KGOUT20_ON();
			break;
		case 20:KGOUT21_ON();
			break;
		case 21:KGOUT22_ON();
			break;
		case 22:KGOUT23_ON();
			break;
		case 23:KGOUT24_ON();
			break;
		case 24:KGOUT25_ON();
			break;
		case 25:COLDING1_ON();
			break;
		case 26:BZP_ON();
			break;

		case 27:KGOUT37_ON();
			break;
		case 28:KGOUT38_ON();
			break;
		case 29:KGOUT30_ON();
			break;
		case 30:KGOUT29_ON();
			break;
		case 31:KGOUT39_ON();
			break;
		case 32:KGOUT40_ON();
			break;
		case 33:KGOUT32_ON();
			break;
		case 34:KGOUT31_ON();
			break;
		case 35:KGOUT42_ON();
			break;
		case 36:KGOUT41_ON();
			break;
		case 37:KGOUT34_ON();
			break;
		case 38:KGOUT50_ON();
			break;
		case 39:KGOUT49_ON();
			break;
		case 40:KGOUT52_ON();
			break;
		case 41:KGOUT51_ON();
			break;
		case 42:SHUTDOWN_ON();
			break;

		case 43:KGOUT54_ON();
			break;
		case 44:KGOUT53_ON();
			break;


		default:
			break;
	}
}
//******************************************************//
static void test_off(uint8 ie)
{
	switch(ie)
	{
		case 0:KGOUT35_OFF();
			break;
		case 1:KGOUT45_OFF();
			break;
		case 2:KGOUT46_OFF();
			break;
		case 3:COLDING2_OFF();
			break;
		case 4:HEATING_OFF();
			break;

		case 5:BDQYOUT1_OFF();
			break;
		case 6:BDQYOUT2_OFF();
			break;
		case 7:KGOUT17_OFF();
			break;
		case 8:KGOUT18_OFF();
			break;

		case 9:KGOUT33_OFF();
			break;
		case 10:KGOUT43_OFF();
			break;
		case 11:KGOUT44_OFF();
			break;
		case 12:KGOUT36_OFF();
			break;
		case 13:KGOUT48_OFF();
			break;
		case 14:KGOUT47_OFF();
			break;
		case 15:KGOUT26_OFF();
			break;
		case 16:KGOUT28_OFF();
			break;
		case 17:KGOUT27_OFF();
			break;

		case 18:KGOUT19_OFF();
			break;
		case 19:KGOUT20_OFF();
			break;
		case 20:KGOUT21_OFF();
			break;
		case 21:KGOUT22_OFF();
			break;
		case 22:KGOUT23_OFF();
			break;
		case 23:KGOUT24_OFF();
			break;
		case 24:KGOUT25_OFF();
			break;
		case 25:COLDING1_OFF();
			break;
		case 26:BZP_OFF();
			break;

		case 27:KGOUT37_OFF();
			break;
		case 28:KGOUT38_OFF();
			break;
		case 29:KGOUT30_OFF();
			break;
		case 30:KGOUT29_OFF();
			break;
		case 31:KGOUT39_OFF();
			break;
		case 32:KGOUT40_OFF();
			break;
		case 33:KGOUT32_OFF();
			break;
		case 34:KGOUT31_OFF();
			break;
		case 35:KGOUT42_OFF();
			break;
		case 36:KGOUT41_OFF();
			break;
		case 37:KGOUT34_OFF();
			break;
		case 38:KGOUT50_OFF();
			break;
		case 39:KGOUT49_OFF();
			break;
		case 40:KGOUT52_OFF();
			break;
		case 41:KGOUT51_OFF();
			break;
		case 42:SHUTDOWN_OFF();
			break;

		case 43:KGOUT54_OFF();
			break;
		case 44:KGOUT53_OFF();
			break;

		default:
			break;
	}
}

void AckToPc(uint8 mask)
{
	CMD_tx_malloc(CMD_TX_ACK_PC_BUF_LEN);

	XCSFrameData.SendBuf[INDX_START1]=START1;
	XCSFrameData.SendBuf[INDX_START2]=START2;
	XCSFrameData.SendBuf[INDX_LEN]=CMD_TX_ACK_PC_BUF_LEN;
	XCSFrameData.SendBuf[INDX_CMD]=0xa9;
	XCSFrameData.SendBuf[4]=*XCSFrameData.Cmd|mask;

	XCSSendFrameData();

	CMD_tx_free();
}

//******************************************************// 转换接收到的数据。经转换，查询，输出
void DO_Me(void)
{
	uint8 i,j,k;
	u16 sum16=0;
	u16 sumre=0;
	j = 0;
	i=0;
	k=0;
	for(k=0;k<KGOUT_ByteNUM;k++)
	{
		outputstateM[k] = XCSFrameData.RecBuf[k];
		sum16 = sum16 + XCSFrameData.RecBuf[k];
	}
	IWDG_Feed();
	sumre = XCSFrameData.RecBuf[k]*256 + XCSFrameData.RecBuf[k+1];//校验和
	if(sum16 == sumre)
	{
		AckToPc(ACK_CMD_OK_MASK);
		for(i=0;i<8;i++)
		{
			  outputstate[i] = ((outputstateM[0]>>i)&0x01);
			  outputstate[i+8] = ((outputstateM[1]>>i)&0x01);
			  outputstate[i+16] = ((outputstateM[2]>>i)&0x01);
			  outputstate[i+24] = ((outputstateM[3]>>i)&0x01);
			  outputstate[i+32] = ((outputstateM[4]>>i)&0x01);
			  outputstate[i+40] = ((outputstateM[5]>>i)&0x01);
//			  outputstate[i+48] = ((outputstateM[6]>>i)&0x01);
//			  outputstate[i+56] = ((outputstateM[7]>>i)&0x01);
//			  outputstate[i+64] = ((outputstateM[8]>>i)&0x01);
//			  outputstate[i+72] = ((outputstateM[9]>>i)&0x01);
		}

		for(j=0;j<KGOUTNUM;j++)
		{
			if(outputstate[j] == 0x01)
			{
				test_on(j);
				IWDG_Feed();
			}
			else
			if(outputstate[j] == 0x00)
			{
				test_off(j);
				IWDG_Feed();
			}
		}

		CAT9555_Write_OneByte(CAT9555_ADDR1,~outputstateM[6],~outputstateM[7]);        //I2C端口控制输出，2015.09
		CAT9555_Write_OneByte(CAT9555_ADDR0,~outputstateM[8],~outputstateM[9]);        //I2C端口控制输出，2015.09

	}
	else
	{
		AckToPc(ACK_CMD_ERR_MASK);
	}
}




static void Test_On_Dula_Wela(uint8 id)
{
	switch(id)
	{
		case 0:KGOUT17_ON();
			break;
		case 1:KGOUT18_ON();
			break;
		case 2:KGOUT19_ON();
			break;
		case 3:KGOUT20_ON();
			break;
		case 4:KGOUT21_ON();
			break;

		case 5:KGOUT22_ON();
			break;
		case 6:KGOUT23_ON();
			break;
		case 7:KGOUT24_ON();
			break;
		case 8:KGOUT25_ON();
			break;

		case 9:KGOUT26_ON();
			break;
		case 10:KGOUT28_ON();
			break;
		case 11:KGOUT27_ON();
			break;
		case 12:KGOUT30_ON();
			break;
		case 13:KGOUT29_ON();
			break;
		case 14:KGOUT32_ON();
			break;
		case 15:KGOUT31_ON();
			break;
		case 16:KGOUT34_ON();
			break;
		case 17:KGOUT33_ON();
			break;

		case 18:KGOUT36_ON();
			break;
		case 19:KGOUT35_ON();
			break;
		case 20:KGOUT37_ON();
			break;
		case 21:KGOUT38_ON();
			break;
		case 22:KGOUT39_ON();
			break;
		case 23:KGOUT40_ON();
			break;
		case 24:KGOUT41_ON();
			break;
		case 25:KGOUT42_ON();
			break;
		case 26:KGOUT43_ON();
			break;

		case 27:KGOUT44_ON();
			break;
		case 28:KGOUT45_ON();
			break;
		case 29:KGOUT46_ON();
			break;
		case 30:KGOUT48_ON();
			break;
		case 31:KGOUT47_ON();
			break;
		case 32:KGOUT50_ON();
			break;
		case 33:KGOUT49_ON();
			break;
		case 34:KGOUT52_ON();
			break;
		case 35:KGOUT51_ON();
			break;
		case 36:KGOUT54_ON();
			break;
		case 37:KGOUT53_ON();
			break;
		case 38:COLDING1_ON();
			break;
		case 39:BZP_ON();
			break;
		case 40:COLDING2_ON();
			break;
		case 41:HEATING_ON();//
			break;
		case 42:BDQYOUT1_ON();
			break;

		case 43:BDQYOUT2_ON();
			break;
		case 44:SHUTDOWN_ON();
			break;


		default:
			break;
	}
}
//******************************************************//
static void Test_Off_Dula_Wela(uint8 ie)
{
	switch(ie)
	{
		case 0:KGOUT17_OFF();
			break;
		case 1:KGOUT18_OFF();
			break;
		case 2:KGOUT19_OFF();
			break;
		case 3:KGOUT20_OFF();
			break;
		case 4:KGOUT21_OFF();
			break;

		case 5:KGOUT22_OFF();
			break;
		case 6:KGOUT23_OFF();
			break;
		case 7:KGOUT24_OFF();
			break;
		case 8:KGOUT25_OFF();
			break;

		case 9:KGOUT26_OFF();
			break;
		case 10:KGOUT28_OFF();
			break;
		case 11:KGOUT27_OFF();
			break;
		case 12:KGOUT30_OFF();
			break;
		case 13:KGOUT29_OFF();
			break;
		case 14:KGOUT32_OFF();
			break;
		case 15:KGOUT31_OFF();
			break;
		case 16:KGOUT34_OFF();
			break;
		case 17:KGOUT33_OFF();
			break;

		case 18:KGOUT36_OFF();
			break;
		case 19:KGOUT35_OFF();
			break;
		case 20:KGOUT37_OFF();
			break;
		case 21:KGOUT38_OFF();
			break;
		case 22:KGOUT39_OFF();
			break;
		case 23:KGOUT40_OFF();
			break;
		case 24:KGOUT41_OFF();
			break;
		case 25:KGOUT42_OFF();
			break;
		case 26:KGOUT43_OFF();
			break;

		case 27:KGOUT44_OFF();
			break;
		case 28:KGOUT45_OFF();
			break;
		case 29:KGOUT46_OFF();
			break;
		case 30:KGOUT48_OFF();
			break;
		case 31:KGOUT47_OFF();
			break;
		case 32:KGOUT50_OFF();
			break;
		case 33:KGOUT49_OFF();
			break;
		case 34:KGOUT52_OFF();
			break;
		case 35:KGOUT51_OFF();
			break;
		case 36:KGOUT54_OFF();
			break;
		case 37:KGOUT53_OFF();
			break;
		case 38:COLDING1_OFF();//
			break;
		case 39:BZP_OFF();
			break;
		case 40:COLDING2_OFF();
			break;
		case 41:HEATING_OFF();
			break;
		case 42:BDQYOUT1_OFF();
			break;

		case 43:BDQYOUT2_OFF();
			break;
		case 44:SHUTDOWN_OFF();
			break;

		default:
			break;
	}
}

//******************************************************// 转换接收到的数据。经转换，查询，输出2015.09

void DO_Me_Dula_Wela(void)
{
	uint8 Dula=XCSFrameData.RecBuf[Dula_num];
	uint8 Wela=XCSFrameData.RecBuf[Wela_num];
	uint8 On_or_of=XCSFrameData.RecBuf[Switc_num];
	u16  Port_Number=0,Sum_Dula_Wela=0,t=0;
	u16  Check_Sum=0,Integer_Dula,Remainder_Dula;

	for(t=0;t<Dula_Wela_ByteNUM;t++)
	{
		Sum_Dula_Wela = Sum_Dula_Wela + XCSFrameData.RecBuf[t];
	}
	IWDG_Feed();
	Check_Sum = XCSFrameData.RecBuf[t]*256 + XCSFrameData.RecBuf[t+1];//校验和

	if(Check_Sum == Sum_Dula_Wela)
	{
		if((Dula >= DulaNumMin) && (Dula <= DulaNumMax))
		{
			if((Wela >= WelaNumMin) && (Wela <= WelaNumMax))
			{
				Port_Number=(Dula-3)*20+Wela;
				IWDG_Feed();
//由STM32直接控制的端口.。
				if(Port_Number>30)
				{
					if(On_or_of)
					{
						Test_On_Dula_Wela(Port_Number-31);
						IWDG_Feed();
					}
					else
					{
						Test_Off_Dula_Wela(Port_Number-31);
						IWDG_Feed();
					}
					AckToPc(ACK_CMD_OK_MASK);
				}
//由STM32的I2C接口控制的CAT9555扩展端口。
				else
				{
					Port_Number=Port_Number-1;
					Integer_Dula=Port_Number/8;
					Remainder_Dula=Port_Number%8;
					IWDG_Feed();
					switch(Integer_Dula)
					{
						case 0:if(On_or_of){Dula_Wela_I2c_Outputstate[0]=(Dula_Wela_I2c_Outputstate[0]|(0x01<<Remainder_Dula));}else
										   {Dula_Wela_I2c_Outputstate[0]=(Dula_Wela_I2c_Outputstate[0]&(~(0x01<<Remainder_Dula)));}
							break;
						case 1:if(On_or_of){Dula_Wela_I2c_Outputstate[1]=(Dula_Wela_I2c_Outputstate[1]|(0x01<<(7-Remainder_Dula)));}else
										   {Dula_Wela_I2c_Outputstate[1]=(Dula_Wela_I2c_Outputstate[1]&(~(0x01<<(7-Remainder_Dula))));}
							break;
						case 2:if(On_or_of){Dula_Wela_I2c_Outputstate[2]=(Dula_Wela_I2c_Outputstate[2]|(0x01<<Remainder_Dula));}else
										   {Dula_Wela_I2c_Outputstate[2]=(Dula_Wela_I2c_Outputstate[2]&(~(0x01<<Remainder_Dula)));}
							break;
						case 3:if(On_or_of){Dula_Wela_I2c_Outputstate[3]=(Dula_Wela_I2c_Outputstate[3]|(0x01<<(7-Remainder_Dula)));}else
										   {Dula_Wela_I2c_Outputstate[3]=(Dula_Wela_I2c_Outputstate[3]&(~(0x01<<(7-Remainder_Dula))));}
							break;
						default:
							break;
					}
					CAT9555_Write_OneByte(CAT9555_ADDR1,~Dula_Wela_I2c_Outputstate[0],~Dula_Wela_I2c_Outputstate[1]);        //I2C端口控制输出，2015.09
					CAT9555_Write_OneByte(CAT9555_ADDR0,~Dula_Wela_I2c_Outputstate[2],~Dula_Wela_I2c_Outputstate[3]);        //I2C端口控制输出，2015.09
					AckToPc(ACK_CMD_OK_MASK);
					IWDG_Feed();
				}
			}
			else{AckToPc(ACK_CMD_ERR_MASK);}
		}
		else{AckToPc(ACK_CMD_ERR_MASK);}
	}
	else {AckToPc(ACK_CMD_ERR_MASK);}
}













