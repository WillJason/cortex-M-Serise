#include <config.h>




int main(void)
{
	delay_init();	    	 //��ʱ������ʼ��
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	//uart1_init(115200);	 //���ڳ�ʼ��
	uart2_init(57600);
 	LED_Init();			     //LED�˿ڳ�ʼ��
	TIM3_Int_Init(MS(100));//10Khz�ļ���Ƶ�ʣ�������1000Ϊ100ms
	uart2_Printf("\r\nϵͳ������\r\n");
	delay_ms(1000);
	IWDG_Init(4,625);    //���Ƶ��Ϊ64,����ֵΪ625,���ʱ��Ϊ1s
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
     	if (*XCSFrameData.RecNewFlag == TRUE)	          			   				// ������յ��µ�����
     	{
     		CmdParse(*XCSFrameData.Cmd);
     		*XCSFrameData.RecNewFlag = FALSE;
     	}
    	//uart2Putc(0x01);
    	IWDG_Feed();//ι��


    }
}
