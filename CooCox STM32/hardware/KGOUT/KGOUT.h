#ifndef	_KGOUT_H
#define	_KGOUT_H

#ifdef	KGOUT_GLOBLES
#define	KGOUT_EXT
#else
#define KGOUT_EXT	extern
#endif


// KGOUT使用的接口初始化
extern	void DO_MeInit();
extern	void KGOUT_Init(void);
extern	void DO_Me(void);
extern  void DO_Me_Dula_Wela(void);
extern	void AckToPc(uint8 mask);
//段，位操作IO相关发送参数2015.09

#define Dula_num        0
#define Wela_num        1
#define Switc_num       2
#define DulaNumMin      3
#define DulaNumMax      6
#define WelaNumMin      1
#define WelaNumMax      20
#define	Dula_Wela_ByteNUM 	3

//相关发送参数
#define	KGOUTNUM 		45  //暂时定为44，原为75  2015.09
#define	KGOUT_ByteNUM 	10

//直接操作IO,ON
#define	KGOUT35_ON()		PAout(0)=0
#define	KGOUT45_ON()		PAout(1)=0
#define	KGOUT46_ON()		PAout(5)=0
#define	COLDING2_ON() 		PAout(6)=0
#define	HEATING_ON()		PAout(7)=0

#define	BDQYOUT1_ON() 		PBout(0)=0
#define	BDQYOUT2_ON() 		PBout(1)=0
#define	KGOUT17_ON()		PBout(8)=0
#define	KGOUT18_ON()		PBout(9)=0

#define	KGOUT33_ON()		PCout(0)=0
#define	KGOUT43_ON()		PCout(1)=0
#define	KGOUT44_ON()		PCout(2)=0
#define	KGOUT36_ON()		PCout(3)=0
#define	KGOUT48_ON()		PCout(4)=0
#define	KGOUT47_ON()		PCout(5)=0
#define	KGOUT26_ON()		PCout(13)=0
#define	KGOUT28_ON()		PCout(14)=0
#define	KGOUT27_ON()		PCout(15)=0

#define	KGOUT19_ON()		PEout(0)=0
#define	KGOUT20_ON()		PEout(1)=0
#define	KGOUT21_ON()		PEout(2)=0
#define	KGOUT22_ON()		PEout(3)=0
#define	KGOUT23_ON()		PEout(4)=0
#define	KGOUT24_ON()		PEout(5)=0
#define	KGOUT25_ON()		PEout(6)=0
#define	COLDING1_ON() 		PEout(7)=0
#define	BZP_ON()			PEout(8)=0

#define	KGOUT37_ON()		PFout(0)=0
#define	KGOUT38_ON()		PFout(1)=0
#define	KGOUT30_ON()		PFout(2)=0
#define	KGOUT29_ON()		PFout(3)=0
#define	KGOUT39_ON()		PFout(4)=0
#define	KGOUT40_ON()		PFout(5)=0
#define	KGOUT32_ON()		PFout(6)=0
#define	KGOUT31_ON() 		PFout(7)=0
#define	KGOUT41_ON()		PFout(8)=0
#define	KGOUT42_ON()		PFout(9)=0
#define	KGOUT34_ON()		PFout(10)=0
#define	KGOUT50_ON()		PFout(11)=0
#define	KGOUT49_ON()		PFout(12)=0
#define	KGOUT52_ON()		PFout(13)=0
#define	KGOUT51_ON()		PFout(14)=0
#define	SHUTDOWN_ON() 		PFout(15)=0

#define	KGOUT54_ON()		PGout(0)=0
#define	KGOUT53_ON()		PGout(1)=0
//直接操作IO,OFF
#define	KGOUT35_OFF()		PAout(0)=1
#define	KGOUT45_OFF()		PAout(1)=1
#define	KGOUT46_OFF()		PAout(5)=1
#define	COLDING2_OFF() 		PAout(6)=1
#define	HEATING_OFF()		PAout(7)=1

#define	BDQYOUT1_OFF() 		PBout(0)=1
#define	BDQYOUT2_OFF() 		PBout(1)=1
#define	KGOUT17_OFF()		PBout(8)=1
#define	KGOUT18_OFF()		PBout(9)=1

#define	KGOUT33_OFF()		PCout(0)=1
#define	KGOUT43_OFF()		PCout(1)=1
#define	KGOUT44_OFF()		PCout(2)=1
#define	KGOUT36_OFF()		PCout(3)=1
#define	KGOUT48_OFF()		PCout(4)=1
#define	KGOUT47_OFF()		PCout(5)=1
#define	KGOUT26_OFF()		PCout(13)=1
#define	KGOUT28_OFF()		PCout(14)=1
#define	KGOUT27_OFF()		PCout(15)=1

#define	KGOUT19_OFF()		PEout(0)=1
#define	KGOUT20_OFF()		PEout(1)=1
#define	KGOUT21_OFF()		PEout(2)=1
#define	KGOUT22_OFF()		PEout(3)=1
#define	KGOUT23_OFF()		PEout(4)=1
#define	KGOUT24_OFF()		PEout(5)=1
#define	KGOUT25_OFF()		PEout(6)=1
#define	COLDING1_OFF() 		PEout(7)=1
#define	BZP_OFF()			PEout(8)=1

#define	KGOUT37_OFF()		PFout(0)=1
#define	KGOUT38_OFF()		PFout(1)=1
#define	KGOUT30_OFF()		PFout(2)=1
#define	KGOUT29_OFF()		PFout(3)=1
#define	KGOUT39_OFF()		PFout(4)=1
#define	KGOUT40_OFF()		PFout(5)=1
#define	KGOUT32_OFF()		PFout(6)=1
#define	KGOUT31_OFF() 		PFout(7)=1
#define	KGOUT41_OFF()		PFout(8)=1
#define	KGOUT42_OFF()		PFout(9)=1
#define	KGOUT34_OFF()		PFout(10)=1
#define	KGOUT50_OFF()		PFout(11)=1
#define	KGOUT49_OFF()		PFout(12)=1
#define	KGOUT52_OFF()		PFout(13)=1
#define	KGOUT51_OFF()		PFout(14)=1
#define	SHUTDOWN_OFF() 		PFout(15)=1

#define	KGOUT54_OFF()		PGout(0)=1
#define	KGOUT53_OFF()		PGout(1)=1
//操作I2C，ON
#define WINBREAK_LED_ON		CAT9555Mirror0=CAT9555Mirror0&(~0x0001);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define WINOPEN_LED_ON		CAT9555Mirror0=CAT9555Mirror0&(~0x0002);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define MEASURING_LED_ON	CAT9555Mirror0=CAT9555Mirror0&(~0x0004);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define WASHING_LED_ON		CAT9555Mirror0=CAT9555Mirror0&(~0x0008);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define QY_LED_ON			CAT9555Mirror0=CAT9555Mirror0&(~0x0010);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define TEM_LED_ON			CAT9555Mirror0=CAT9555Mirror0&(~0x0020);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define POWER_LED_ON		CAT9555Mirror0=CAT9555Mirror0&(~0x0040);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define HV_LED_ON			CAT9555Mirror0=CAT9555Mirror0&(~0x0080);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define KGOUT56_ON			CAT9555Mirror0=CAT9555Mirror0&(~0x8000);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define KGOUT55_ON			CAT9555Mirror0=CAT9555Mirror0&(~0x4000);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define KGOUT58_ON			CAT9555Mirror0=CAT9555Mirror0&(~0x2000);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define KGOUT57_ON			CAT9555Mirror0=CAT9555Mirror0&(~0x1000);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define KGOUT60_ON			CAT9555Mirror0=CAT9555Mirror0&(~0x0800);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define KGOUT59_ON			CAT9555Mirror0=CAT9555Mirror0&(~0x0400);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))

#define KGOUT2_ON			CAT9555Mirror1=CAT9555Mirror1&(~0x0001);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT1_ON			CAT9555Mirror1=CAT9555Mirror1&(~0x0002);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT4_ON			CAT9555Mirror1=CAT9555Mirror1&(~0x0004);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT3_ON			CAT9555Mirror1=CAT9555Mirror1&(~0x0008);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT6_ON			CAT9555Mirror1=CAT9555Mirror1&(~0x0010);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT5_ON			CAT9555Mirror1=CAT9555Mirror1&(~0x0020);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT8_ON			CAT9555Mirror1=CAT9555Mirror1&(~0x0040);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT7_ON			CAT9555Mirror1=CAT9555Mirror1&(~0x0080);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT10_ON			CAT9555Mirror1=CAT9555Mirror1&(~0x8000);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT9_ON			CAT9555Mirror1=CAT9555Mirror1&(~0x4000);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT11_ON			CAT9555Mirror1=CAT9555Mirror1&(~0x2000);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT12_ON			CAT9555Mirror1=CAT9555Mirror1&(~0x1000);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT13_ON			CAT9555Mirror1=CAT9555Mirror1&(~0x0800);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT14_ON			CAT9555Mirror1=CAT9555Mirror1&(~0x0400);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT15_ON			CAT9555Mirror1=CAT9555Mirror1&(~0x0200);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT16_ON			CAT9555Mirror1=CAT9555Mirror1&(~0x0100);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
//操作I2C,OFF
#define WINBREAK_LED_OFF	CAT9555Mirror0=CAT9555Mirror0|(0x0001);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define WINOPEN_LED_OFF		CAT9555Mirror0=CAT9555Mirror0|(0x0002);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define MEASURING_LED_OFF	CAT9555Mirror0=CAT9555Mirror0|(0x0004);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define WASHING_LED_OFF		CAT9555Mirror0=CAT9555Mirror0|(0x0008);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define QY_LED_OFF			CAT9555Mirror0=CAT9555Mirror0|(0x0010);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define TEM_LED_OFF			CAT9555Mirror0=CAT9555Mirror0|(0x0020);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define POWER_LED_OFF		CAT9555Mirror0=CAT9555Mirror0|(0x0040);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define HV_LED_OFF			CAT9555Mirror0=CAT9555Mirror0|(0x0080);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define KGOUT56_OFF			CAT9555Mirror0=CAT9555Mirror0|(0x8000);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define KGOUT55_OFF			CAT9555Mirror0=CAT9555Mirror0|(0x4000);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define KGOUT58_OFF			CAT9555Mirror0=CAT9555Mirror0|(0x2000);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define KGOUT57_OFF			CAT9555Mirror0=CAT9555Mirror0|(0x1000);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define KGOUT60_OFF			CAT9555Mirror0=CAT9555Mirror0|(0x0800);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))
#define KGOUT59_OFF			CAT9555Mirror0=CAT9555Mirror0|(0x0400);CAT9555_Write_OneByte(CAT9555_ADDR0,CAT9555Mirror0,(CAT9555Mirror0>>8))

#define KGOUT2_OFF			CAT9555Mirror1=CAT9555Mirror1|(0x0001);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT1_OFF			CAT9555Mirror1=CAT9555Mirror1|(0x0002);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT4_OFF			CAT9555Mirror1=CAT9555Mirror1|(0x0004);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT3_OFF			CAT9555Mirror1=CAT9555Mirror1|(0x0008);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT6_OFF			CAT9555Mirror1=CAT9555Mirror1|(0x0010);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT5_OFF			CAT9555Mirror1=CAT9555Mirror1|(0x0020);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT8_OFF			CAT9555Mirror1=CAT9555Mirror1|(0x0040);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT7_OFF			CAT9555Mirror1=CAT9555Mirror1|(0x0080);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT10_OFF			CAT9555Mirror1=CAT9555Mirror1|(0x8000);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT9_OFF			CAT9555Mirror1=CAT9555Mirror1|(0x4000);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT11_OFF			CAT9555Mirror1=CAT9555Mirror1|(0x2000);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT12_OFF			CAT9555Mirror1=CAT9555Mirror1|(0x1000);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT13_OFF			CAT9555Mirror1=CAT9555Mirror1|(0x0800);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT14_OFF			CAT9555Mirror1=CAT9555Mirror1|(0x0400);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT15_OFF			CAT9555Mirror1=CAT9555Mirror1|(0x0200);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))
#define KGOUT16_OFF			CAT9555Mirror1=CAT9555Mirror1|(0x0100);CAT9555_Write_OneByte(CAT9555_ADDR1,CAT9555Mirror1,(CAT9555Mirror1>>8))

#endif
















