#include <config.h>




int main(void)
{
	delay_init();	    	 //延时函数初始化
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	//uart1_init(115200);	 //串口初始化
	uart2_init(57600);
 	LED_Init();			     //LED端口初始化
	TIM3_Int_Init(MS(100));//10Khz的计数频率，计数到1000为100ms
	uart2_Printf("\r\n系统启动！\r\n");
	delay_ms(1000);
	IWDG_Init(4,625);    //与分频数为64,重载值为625,溢出时间为1s
	EXTIX_Init();
	detectint();
	AD974_Init();

	IIC_Init();
	CAT9555_WriteCFG(CAT9555_ADDR0,0x00,0x00);
	CAT9555_WriteCFG(CAT9555_ADDR1,0x00,0x00);

	CMD_Init();
	KGOUT_Init();
	DO_MeInit();

    while(1)
    {
    	//WinPTest();
    	//CAT9555_Write_OneByte(CAT9555_ADDR1,0x00,0x00);
    	//CAT9555_Write_OneByte(CAT9555_ADDR0,0x00,0x00);
     	if (*XCSFrameData.RecNewFlag == TRUE)	          			   				// 如果接收到新的数据
     	{
     		CmdParse(*XCSFrameData.Cmd);
     		*XCSFrameData.RecNewFlag = FALSE;
     	}
    	//uart2Putc(0x01);
    	IWDG_Feed();//喂狗


    }
}
