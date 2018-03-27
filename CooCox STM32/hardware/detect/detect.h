
#ifdef	DETECT_GLOBLES
#define	DETECT_EXT
#else
#define DETECT_EXT	extern

#endif

extern  void    detectint();
extern	void WinTestOut(void);
extern	void Detect(void);
extern	void Detect_Dula_Wela(void);

//检测部分
#define TESTWINNUM 30                  //检测探头保护窗口时，连续检测到问题标志的次数
#define TESTWINNUMCOP (TESTWINNUM - 20) //检测探头保护窗口时，报警的比较值，即检测到TESTNUMCOP次问题就报警
#define	TESTWIN_TEMNUM	10				//检测探头温度，报警的比较值
#define	INPUTDETECT_NUM	12				//其他IO口状态比较值      原为10，  2015.09

#define DNKGOUT(x)    PEout(12)=GPIO(x) //
#define PNKGOUT(x)    PEout(11)=GPIO(x)//
#define	RD_WINKGIN()	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)
#define	RD_TEMKGIN()	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_13)
#define	RD_KGIN39()		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)
//#define	WIN_OUT(x)	PFout(14)=GPIO(x)
//#define	WINTEM_OUT(x)	PFout(13)=GPIO(x)
#define	SHUTDOWN(x)	PFout(15)=GPIO(x)
//通信
#define	INPUT_PORT_NUM	42

//输入口对应
#define	KGIN5	PAin(8)
#define	KGIN6	PAin(11)
#define	KGIN28	PAin(12)
#define	KGIN27	PAin(13)
#define	KGIN17	PAin(14)
#define	KGIN18	PAin(15)

#define	KGIN8	PBin(10)
#define	KGIN7	PBin(11)

#define	KGIN3	PCin(6)
#define	KGIN4	PCin(7)
#define	KGIN16	PCin(8)
#define	KGIN15	PCin(9)
#define	KGIN30	PCin(10)
#define	KGIN29	PCin(11)
#define	KGIN19	PCin(12)

#define	KGIN20	PDin(0)
#define	KGIN32	PDin(1)
#define	KGIN31	PDin(2)
#define	KGIN21	PDin(3)
#define	KGIN22	PDin(4)
#define	KGIN34	PDin(5)
#define	KGIN33	PDin(6)
#define	KGIN23	PDin(7)
#define	BDQYIN1	PDin(11)
#define	BDQYIN2	PDin(12)
#define	KGIN10	PDin(13)
#define	KGIN9	PDin(14)
#define	DGPREIN	PDin(15)

#define	KGIN37	PEin(14)
#define	KGIN38	PEin(15)

#define	QYIN	PGin(2)
#define	KGIN12	PGin(3)
#define	KGIN11	PGin(4)
#define	KGIN1	PGin(5)
#define	KGIN2	PGin(6)
#define	KGIN14	PGin(7)
#define	KGIN13	PGin(8)
#define	KGIN24	PGin(9)
#define	KGIN36	PGin(10)
#define	KGIN35	PGin(11)
#define	KGIN25	PGin(12)
#define	KGIN26	PGin(13)



