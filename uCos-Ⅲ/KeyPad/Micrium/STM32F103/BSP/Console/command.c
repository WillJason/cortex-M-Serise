/*
 * vivi/lib/command.c: 
 *   - to support user commands on the boot loader
 *
 * Copyright (C) 2001 MIZI Research, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 * Author: Janghoon Lyu <nandy@mizi.com>
 * Date  : $Date: 2004/02/04 06:22:25 $
 *
 * $Revision: 1.1.1.1 $
 *
 * 
 * History
 * 
 * 2001-12-23: Janghoon Lyu <nandy@mizi.com>
 *    - Initial code
 *    - Base on bootldr/bootldr.c 
 *
 * 2002-02-23: Janghoon Lyu <nandy@mizi.com>
 *    -  Add flash commands
 *
 * 2002-07-13: Janghoon Lyu <nandy@mizi.com>
 *
 */

#include "includes.h"
//#include "app.h"

#define MAX_PROMPT_LEN	12
char prompt[MAX_PROMPT_LEN] = "V1.0";

enum ParseState {
	PS_WHITESPACE,
	PS_TOKEN,
	PS_STRING,
	PS_ESCAPE
};

enum ParseState stackedState;

static user_command_t *head_cmd = NULL;
static user_command_t *tail_cmd = NULL;
/**************************移植部分**************************/
unsigned char userdata[sizeof(user_data_t)];
const char *CanBaudStr[]={
        "1000K",
        "800K",
        "500K",
        "250K",
        "100K",
        "80K",
        "60K",
        "50K",
        "40K",
        "30K",
        "20K",
        "10K",
        "5K"
        };
/***********************************************************/
/*
 * Parse user command line
 */
 /*********************************************************************************************************
** 函数名称: parseargs
** 功能描述: 解析用户命令。
** 输　入: 用户字符串
** 输　出: 无
** 全局变量: 无
** 调用模块: 
**
** 作　者: 
** 日　期: 
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

void parseargs(char *argstr, int *argc_p, char **argv, char** resid)
{
	int argc = 0;
	char c;
	enum ParseState lastState = PS_WHITESPACE;

	/* tokenize the argstr */
	while ((c = *argstr) != 0) {
		enum ParseState newState;

		if (c == ';' && lastState != PS_STRING && lastState != PS_ESCAPE)
			break;

		if (lastState == PS_ESCAPE) {
			newState = stackedState;
		} else if (lastState == PS_STRING) {
			if (c == '"') {
				newState = PS_WHITESPACE;
				*argstr = 0;
			} else {
				newState = PS_STRING;
			}
		} else if ((c == ' ') || (c == '\t')) {
			/* whitespace character */
			*argstr = 0;
			newState = PS_WHITESPACE;
		} else if (c == '"') {
			newState = PS_STRING;
			*argstr++ = 0;
			argv[argc++] = argstr;
		} else if (c == '\\') {
			stackedState = lastState;
			newState = PS_ESCAPE;
		} else {
			/* token */
			if (lastState == PS_WHITESPACE) {
				argv[argc++] = argstr;
			}
			newState = PS_TOKEN;
		}

		lastState = newState;
		argstr++;
	}

#if 0 /* for debugging */
	{
		int i;
		//putLabeledWord("parseargs: argc=", argc);
		for (i = 0; i < argc; i++) {
			putstr("   ");
			putstr(argv[i]);
			putstr("\r\n");
		}
	}
#endif
	
	argv[argc] = NULL;
	if (argc_p != NULL)
		*argc_p = argc;

	if (*argstr == ';') {
		*argstr++ = '\0';
	}
	*resid = argstr;
	//printk("argc is %d\n",argc);
}

 /*********************************************************************************************************
** 函数名称: parseargs
** 功能描述: 解析用户命令。
** 输　入: cp		要发送数据的缓冲区指针
** 输　出: 无
** 全局变量: 无
** 调用模块: 
**
** 作　者: 
** 日　期: 
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

void unparseargs(char *argstr, int argc, const char **argv)
{
	int i;
	for (i = 0; i < argc; i++) {
		if (argv[i] != NULL) {
			STRCAT(argstr, " ");
			STRCAT(argstr, argv[i]);
		}
	}
}

/*
 * Genernal interface
 */

/*
 * For (main) commands
 */

/* add user command */
 /*********************************************************************************************************
** 函数名称: add_command
** 功能描述:注册用户命令。
** 输　入: cp		要发送数据的缓冲区指针
** 输　出: 无
** 全局变量: 无
** 调用模块: 
**
** 作　者: 
** 日　期: 
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

void add_command(user_command_t *cmd)
{
	if (head_cmd == NULL) {
		head_cmd = tail_cmd = cmd;
	} else {
		tail_cmd->next_cmd = cmd;
		tail_cmd = cmd;
	}
//	printk("Registered '%s' command\n", cmd->name);
//	printk("\n");
}

/* find command */
 /*********************************************************************************************************
** 函数名称: find_cmd
** 功能描述: 搜索用户命令。
** 输　入: cp		要发送数据的缓冲区指针
** 输　出: 无
** 全局变量: 无
** 调用模块: 
**
** 作　者: 
** 日　期: 
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

user_command_t *find_cmd(const char *cmdname)
{
	user_command_t *curr;

	/* do da string compare for the first offset character of cmdstr
	  against each number of the cmdlist */
	curr = head_cmd;
	while(curr != NULL) {
//		printk("%s\n",curr->name);
		if (STRNCMP(curr->name, cmdname, STRLEN(cmdname)) == 0)
			return curr;
		curr = curr->next_cmd;
	}
	return NULL;
}

/* execute a function */
 /*********************************************************************************************************
** 函数名称: execcmd
** 功能描述: 解析用户命令。
** 输　入: cp		要发送数据的缓冲区指针
** 输　出: 无
** 全局变量: 无
** 调用模块: 
**
** 作　者: 
** 日　期: 
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

void execcmd(int argc, const char **argv)
{
	user_command_t *cmd = find_cmd(argv[0]);

	if (cmd == NULL) {
		printk("\t找不到 '%s' 命令\n", argv[0]);
		printk("\t查询有效命令，请键入'help'\n"); 
		return;
	}
	/*printk("execcmd: cmd=%s, argc=%d\n", argv[0], argc);*/

	cmd->cmdfunc(argc, argv);
}

/* parse and execute a string */
 /*********************************************************************************************************
** 函数名称: exec_string
** 功能描述: 解析用户命令。
** 输　入: cp		要发送数据的缓冲区指针
** 输　出: 无
** 全局变量: 无
** 调用模块: 
**
** 作　者: 
** 日　期: 
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

void exec_string(char *buf)
{
	int argc;
	char *argv[128];
	char *resid;

	while (*buf) {
		MEMSET(argv, 0, sizeof(argv));
		parseargs(buf, &argc, argv, &resid); //解析用户命令及参数
		if (argc > 0)  
			execcmd(argc, (const char **)argv);
		buf = resid;
	}
}

/*
 * For sub-commands
 */
  /*********************************************************************************************************
** 函数名称: parseargs
** 功能描述: 解析用户命令。
** 输　入: cp		要发送数据的缓冲区指针
** 输　出: 无
** 全局变量: 无
** 调用模块: 
**
** 作　者: 
** 日　期: 
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

void execsubcmd(user_subcommand_t *cmds, int argc, const char **argv)
{

	while (cmds->name != NULL) {
		if (STRNCMP(argv[0], cmds->name, STRLEN(argv[0])) == 0) {
			/*printk("subexeccmd: cmd=%s, argc=%d\n", argv[0], argc);*/
			cmds->cmdfunc(argc, argv);
			return;
		}
		cmds++;
	}
	printk("Could not found '%s' sub-command\n", argv[0]);
}
 /*********************************************************************************************************
** 函数名称: parseargs
** 功能描述: 解析用户命令。
** 输　入: cp		要发送数据的缓冲区指针
** 输　出: 无
** 全局变量: 无
** 调用模块: 
**
** 作　者: 
** 日　期: 
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

void print_usage(char *strhead, user_command_t *cmds)
{
	printk("用法:\n");
	if (cmds->name != NULL) {
		if (strhead)
			printk("%s ", strhead);
		if (*cmds->helpstr)
			printk("%s\n", cmds->helpstr);
	}
}
 /*********************************************************************************************************
** 函数名称: parseargs
** 功能描述: 解析用户命令。
** 输　入: cp		要发送数据的缓冲区指针
** 输　出: 无
** 全局变量: 无
** 调用模块: 
**
** 作　者: 
** 日　期: 
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

void invalid_cmd(const char *cmd_name)
{
    user_command_t *curr;
    curr=find_cmd(cmd_name);
	printk("无效 '%s' 命令: 参数错误\n", curr->name);	
	print_usage("  ", curr);
}


/*
 * Define (basic) built-in commands
 */
#if 0

	"help [{cmds}] 					-- Help about help?"
	"save [{cmds}] 					-- 保存系统参数"
	"baseid <addr> <args>			-- 修改分站ID"
	"dump <addr> <length> 			-- Display (hex dump) a range of memory."
	"info 							-- 显示系统参数"
	"canbaud [{通道}] [{波特率}] 	-- 设置can波特率"
	"pollinglist <通道> <id>		-- 设置分站轮询列表"
	"prompt <string>\t\t\t			-- 修改用户名"
	"reset 							-- 重启系统"
	"test 							-- Test items" 
#endif

/* help command */
 /*********************************************************************************************************
** 函数名称: parseargs
** 功能描述: 解析用户命令。
** 输　入: cp		要发送数据的缓冲区指针
** 输　出: 无
** 全局变量: 无
** 调用模块: 
**
** 作　者: 
** 日　期: 
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

void command_help(int argc, const char **argv)
{
	user_command_t *curr;

	/* help <command>. invoke <command> with 'help' as an argument */
	if (argc == 2) {
		if (STRNCMP(argv[1], "help", STRLEN(argv[1])) == 0) {
			printk("Are you kidding?\n");
			return;
		}
		argv[0] = argv[1];
		argv[1] = "help";
		execcmd(argc, argv);
		return;
	}

	printk("用法:\n");
	curr = head_cmd;
	while(curr != NULL) {
		printk("   %s\n", curr->helpstr);
		curr = curr->next_cmd;
	}
}

user_command_t help_cmd = {
	"help",
	command_help,
	NULL,
	"\thelp  \t\t\t\t--命令帮助"
};
 /*********************************************************************************************************
** 函数名称: parseargs
** 功能描述: 解析用户命令。
** 输　入: cp		要发送数据的缓冲区指针
** 输　出: 无
** 全局变量: 无
** 调用模块: 
**
** 作　者: 
** 日　期: 
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

/* save command */
void command_save(int argc,const char *argv[]){

//	 SSTF016B_Erase(SYSPARAMADDR,SYSPARAMADDR);
//     SSTF016B_WR(SYSPARAMADDR, userdata, sizeof(user_data_t));
//     I2C_WriteNByte(FM24CL16, ONE_BYTE_SUBA, 0x00, userdata, sizeof(user_data_t));
     printk("\t参数保存成功，请用reset命令重启设备！\n");
}
user_command_t save_cmd = {
	"save",
	command_save,
	NULL,
	"\tsave  \t\t\t\t--保存系统参数"
};
 /*********************************************************************************************************
** 函数名称: parseargs
** 功能描述: 解析用户命令。
** 输　入: cp		要发送数据的缓冲区指针
** 输　出: 无
** 全局变量: 无
** 调用模块: 
**
** 作　者: 
** 日　期: 
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

#ifdef SUBID
/* subid command */
void command_subid(int argc,const char *argv[]){

     int ret;
	 int dat;
     user_data_t *p=(user_data_t *)userdata;
      if(argc!=2)      
      	invalid_cmd(argv[0]);
      else{
	     dat=stringtoul(argv[1],&ret);
         if(dat<166&&dat>160){
		   p->subid=dat;
           printk("\t矿用一般型CAN传输接口地址修改为%d\n",p->subid);
		   }
            else
           {
             p->subid=161;
             invalid_cmd(argv[0]);
           }
      }
        
    
}
user_command_t subid_cmd = {
	"subid",
	command_subid,
	NULL,
	"\tsubid   <地址161-165> \t\t--设置CAN传输接口地址"
};
#endif
 /*********************************************************************************************************
** 函数名称: parseargs
** 功能描述: 解析用户命令。
** 输　入: cp		要发送数据的缓冲区指针
** 输　出: 无
** 全局变量: 无
** 调用模块: 
**
** 作　者: 
** 日　期: 
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

#ifdef INFO
/* info command */
void command_info(int argc,const char *argv[]){
}
user_command_t info_cmd = {
	"info",
	command_info,
	NULL,
	"\tinfo  \t\t\t\t--打印系统参数"
};
#endif
 /*********************************************************************************************************
** 函数名称: command_reset
** 功能描述: 系统软复位。
** 输　入: cp		要发送数据的缓冲区指针
** 输　出: 无
** 全局变量: 无
** 调用模块: 
**
** 作　者: 
** 日　期: 
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

/* reset command */
void command_reset(int argc,const char *argv[]){
  printk("System Reset...\n");
	NVIC_SystemReset();
}
user_command_t reset_cmd = {
	"reset",
	command_reset,
	NULL,
	"\treset 				--重启系统"
};
 /*********************************************************************************************************
** 函数名称: command_dump
** 功能描述: 解析用户命令。
** 输　入: cp		要发送数据的缓冲区指针
** 输　出: 无
** 全局变量: 无
** 调用模块: 
**
** 作　者: 
** 日　期: 
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

/* dump command */
#ifdef DUMP 
void command_dump(int argc, const char *argv[])
{
	size_t num;
	unsigned char *p;

	if (argc == 3)	/* size spcified */
		num = stringtoul(argv[2], NULL);
	else
		num = 16;

	p = (unsigned char *)stringtoul(argv[1], NULL);

	hex_dump(p, num);
}

user_command_t dump_cmd = {
	"dump",
	command_dump,
	NULL,
	"\tdump <addr> <length> \t\t--显示转存内存内容"
};
#endif
 /*********************************************************************************************************
** 函数名称: command_prompt
** 功能描述: 修改用户名称。
** 输　入: cp		要发送数据的缓冲区指针
** 输　出: 无
** 全局变量: 无
** 调用模块: 
**
** 作　者: 
** 日　期: 
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

/*  change username command */
//#define CONFIG_CMD_PROMPT
#ifdef CONFIG_CMD_PROMPT
void command_prompt(int argc, const char **argv)
{
	unsigned int len;

	switch (argc) {
	case 2:
		len = STRLEN(argv[1]);
		if (len >= MAX_PROMPT_LEN) {
			printk("Too long string...!\n");
			break;
		}
		memcpy(prompt, argv[1], 16);
		printk("用户名更改为： \"%s\"\n", prompt);
		break;
	default:
		printk("invalid 'prompt' command: too few or many arguments\n");
		printk("用法:\n");
		printk("  prompt <string>\n");
		break;
	}
}

user_command_t prompt_cmd = {
	"prompt",
	command_prompt,
	NULL,
	"\tprompt <string>\t\t\t--修改用户名"
};
#endif


/*任务堆栈检查，用来确定任务占用堆栈多少*/
//#define STKCHK
#ifdef STKCHK
void command_stackcheck(int argc,const char *argv[]){
   
   extern uint8 PriTable[TASK_NUM];
   uint8 temp[OS_TASK_NAME_SIZE];
   INT8U err,num;
   int ret;
   OS_STK_DATA data;
   if(argc!=2)      
      	invalid_cmd(argv[0]);
   else{
         num=stringtoul(argv[1],&ret);
         if(num>sizeof(PriTable))
           invalid_cmd(argv[0]);
         else{
            err=OSTaskStkChk(PriTable[num-1],&data);
			OSTaskNameGet(PriTable[num-1],temp,&err); 
            if(err==OS_NO_ERR)
              printk("\t%s:空闲堆栈：%d,已使用堆栈:%d\n",temp,data.OSFree,data.OSUsed);     
            else
              printk("\t堆栈检查未开启!\n");
           }
        }
}
user_command_t stackcheck_cmd = {
	"stackcheck",
	command_stackcheck,
	NULL,
	"\tstackcheck  <tid>\t\t-- 任务堆栈统计"
};
#endif

//#define USE_SPIFLASH  //测试SPI FLASH内容
#ifdef 	USE_SPIFLASH
#define FOSC         12000000
void command_useyspiflash(int argc,const char **argv){

  int i,num;
  unsigned endaddress=0;
  unsigned char dat;
  extern const char iappassword[];
#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
    OS_CPU_SR  cpu_sr = 0;
#endif
     if(argc > 3)      
      	invalid_cmd(argv[0]);
   else{
         num=stringtoul(argv[1],&i);
		  switch(num){
		  
		  case 1:
		       if(argv[2]!=NULL){
	         		if(STRNCMP(iappassword,argv[2],STRLEN(iappassword))==0){
	            		OS_ENTER_CRITICAL();//测试发现大于64K的块  64K之后的不能一次擦除 , 分多次进行擦除
						endaddress=USER_CODE_START_SEGMENT+USER_CODE_STOP_SEGMENT; //修改
						endaddress>>=1;
		      			SSTF016B_Erase(USER_CODE_START_SEGMENT,endaddress);	 
						SSTF016B_Erase(endaddress,USER_CODE_STOP_SEGMENT);
			  			OS_EXIT_CRITICAL();
			  			printk("\tFlash擦除成功!\n"); 				
					} 
	         		else
	           			printk("\t密码错误，请核对后重新输入!\n");
				 }
				else
				 invalid_cmd(argv[0]);	
			  break; 
		  case 2: 		     
			    if(argv[2]!=NULL){
	         		if(STRNCMP(iappassword,argv[2],STRLEN(iappassword))==0){
					  printk("\t文件校验进行中，请稍候..\n");
					  i= HexFileVerify(&endaddress);   //校验
					  if(i>0){
					     printk("\t文件校验正确，文件长度为%d byte \n\t开始进行IAP升级..\n",i);
						 dat=0xBB; //置位BB标志，防止更新出错恢复
			  		     SSTF016B_WR(STOPADDR-10+3,&dat,1);
						 OSTimeDly(100);
	            	     IAPInit (0,FOSC, 2);
					     IAPPrograming(OFFSET,endaddress);
					  }else{
					     printk("\t文件校验错误，请重新下载!\n");
					  }				
					} 
	         		else
	           			printk("\t密码错误，请核对后重新输入!\n");
				 }
				else
				 invalid_cmd(argv[0]);			  
			  break;
		  case 3:
		       printk("\t文件校验进行中，请稍候..\n");
		       i=HexFileVerify(&endaddress);
		      if(i>0)
			    printk("\t文件校验正确，文件长度为%d byte,用户代码结束地址为%04x \n",i,endaddress);
			  else
			    printk("\t文件校验错误，请重新下载!\n");
			  break;
		  case 4:
		      num=HexFileVerify(&endaddress);
		      for(i=0;i<num;i++){
			    SSTF016B_RD(i+OFFSET,1,&dat);
				printk(" %02x ",dat);
			  }	
		      break;
		 case 5:
		      if(argv[2]!=NULL){
	         	if(STRNCMP(iappassword,argv[2],STRLEN(iappassword))==0){				    
		      		dat=0x0B;
			  		SSTF016B_WR(STOPADDR-10+3,&dat,1);
			  		printk("\t用户程序更新成功标志置位!\n"); 				
				} 
	         	else
	           		printk("\t密码错误，请核对后重新输入!\n");
				 }
				else
				 invalid_cmd(argv[0]);	
		      break;
		  default:
		    invalid_cmd(argv[0]);
		    break;
		  }
        }
}
user_command_t usespiflash_cmd ={
   "Flash",
    command_useyspiflash,
    NULL,
    "\tFlash <1> <password>\t\t--FLASH擦除,下载程序前必须执行此操作\n"\
	"\tFlash <2> <password>\t\t--IAP在线升级程序\n"\
	"\tFlash <3-5>\t\t\t--用户程序校验/回读/更新成功标志置位"
};
#endif


//#define FLASH_RW
#ifdef FLASH_RW
void command_flash_read(int argc,const char **argv){
  extern tUserConfigInfo UserData;
	if(argc != 1)
		invalid_cmd(argv[0]);
	else{
    Flash_Read((INT32U*)&UserData,sizeof(tUserConfigInfo));
		printk("\tSys Info:%d,%d,%d,%d\n",UserData.data1,UserData.data2,UserData.data3,UserData.data4);
	}
}

user_command_t  flash_read_cmd = {
	 "fread",
	 command_flash_read,
	 NULL,
	 "\tfread \t\t\t\t--flash读取测试"
 }; 
void command_flash_write(int argc,const char **argv){
  extern tUserConfigInfo UserData;
	unsigned dat1,dat2;
	int ret;
	if(argc != 3)
		invalid_cmd(argv[0]);
	else{
		dat1=stringtoul(argv[1],&ret);
		if(dat1>3)
			invalid_cmd(argv[0]);
		else{
			dat2=stringtoul(argv[2],&ret);
			*((unsigned *)(&UserData.data1)+dat1)=dat2;
			Flash_Write((INT32U*)&UserData,sizeof(tUserConfigInfo)/4);//写入系统配置信息
			printk("\tSys Info:data%d has been writen %d\n",dat1,dat2);
		}
	}
}

user_command_t  flash_write_cmd = {
	 "fwrite",
	 command_flash_write,
	 NULL,
	 "\tfwrite <0-3><num>\t\t--flash写入测试"
 }; 
#endif

//#define USE_PROTOCOL_TEST_EN
#ifdef USE_PROTOCOL_TEST_EN
static const uint8_t normal0[]={0xff,0xF0,0xAA,0x03,0xdd};
static const uint8_t normal1[]={0xff,0x00,0x00,0x45,0x56,0x67,0x00,0x00,0xdd};
static const uint8_t normal2[]={0xff,0x10,0x00,0xC3,0xC5,0x51,0x24,0x61,0xdd};
static const uint8_t normal3[]={0xff,0x20,0x00,0x07,0x81,0x9D,0xA7,0x75,0xdd};
static const uint8_t normal4[]={0xff,0x30,0x00,0x52,0x55,0x9D,0x77,0x7E,0xdd};

static const uint8_t sensor_threhold[]={0xff,0x08,0x02,0x14,0x05,0x02,0x00,0x04,0xdd};
static const uint8_t sensor_offset[]={0xff,0x28,0x02,0x02,0x34,0xdd,0xff,0x7d,0xdd};
static const uint8_t sensor_force[]={0xff,0x08,0x00,0x14,0x05,0x02,0x80,0x04,0xdd};
static const uint8_t sensor_adjust[]={0xff,0x08,0x20,0x14,0x05,0x02,0x40,0x00,0xdd};
static const uint8_t sensor_control[]={0xff,0x18,0x01,0x37,0x30,0x07,0xa5,0xf7,0xdd};
static const uint8_t sensor_output[]={0xff,0x28,0x01,0x01,0x33,0xdd,0xff,0x7d,0xdd};

void command_protocol_test(int argc,const char **argv){
	unsigned dat,len;
	static uint8_t buff[9];
	int ret;
	if(argc != 2)
		invalid_cmd(argv[0]);
	else{
		dat=stringtoul(argv[1],&ret);
		if(dat>0xFF)
			invalid_cmd(argv[0]);
		else{
			const uint8_t *p=NULL;
			printk("\t发送%d号指令数据\n",dat);
			switch(dat){
				case 0:		
						p=normal0;
				    len = 5;
					break;
				case 1:
						p=normal1;
				    len = 9;
					break;
				case 2:
						p=normal2;
				    len = 9;
					break;
				case 3:
						p=normal3;
				    len = 9;
				  break;
				case 4:
					  p=normal4;
					  len = 9;
					break;
				case 5:
						p=sensor_threhold;
					  len = 9;
					break;
				case 6:
					p=sensor_offset;
					len = 9;
					break;
				case 7:
					p=sensor_force;
				  len=9;
					break;
				case 8:
					p=sensor_control;
					len=9;
					break;
				case 9:
					p=sensor_output;
				  len=9;
					break;
				case 10:
					p=sensor_adjust;
					len=9;
					break;
				default:
					break;			
			}
			printk("Err:%d\n",Uart_Conn_Write(p,buff,len));
			for(dat=0;dat<len;dat++)
				printk("%02x ",buff[dat]);
			printk("\n");
		}
	}
}

user_command_t  protocol_test_cmd = {
	 "protocol",
	 command_protocol_test,
	 NULL,
	 "\tprotocol <0-91>\t\t\t--通讯协议测试"
 }; 
#endif

 
//#define USE_GUI_TEST_EN
#ifdef USE_GUI_TEST_EN 
const uint8_t handshack[]={0xfd,0x00,0x00,0x00,0xdd,0xcc,0xbb,0xaa};
const uint8_t touchmode[]={0xfd,0x52,0x00,0x01,0x02,0xdd,0xcc,0xbb,0xaa};
const uint8_t image_disp[]={0xfd,0x30,0x00,0x01,0x01,0xdd,0xcc,0xbb,0xaa};
const uint8_t image_cut[]={0xfd,0x37,0x00,0x0e,0x00,0x00,0x00,0xc8,0x0a,0x00,0x00,0x00,0xc8,0x01,0x40,0x00,0x28,0x00,0xdd,0xcc,0xbb,0xaa};
const uint8_t draw_rect[]={0xfd,0x27,0x00,0x09,0x01,0x00,0xE0,0x00,0x3C,0x00,0xF0,0x00,0x84,0xdd,0xcc,0xbb,0xaa};
const uint8_t draw_txt[]={0xfd,0x10,0x00,0x07,0x00,0xF6,0x00,0x9C,0x33,0x34,0x35,0xdd,0xcc,0xbb,0xaa};
const uint8_t set_color[]={0xfd,0x05,0x00,0x04,0x93,0xA0,0x00,0x00,0xdd,0xcc,0xbb,0xaa};
const uint8_t set_strmode[]={0xfd,0x08,0x00,0x03,0x00,0xFF,0xFF,0xdd,0xcc,0xbb,0xaa};
	void command_lcd_test(int argc,const char **argv){
	unsigned dat;
	int ret;
	if(argc != 2)
		invalid_cmd(argv[0]);
	else{
		dat=stringtoul(argv[1],&ret);
		if(dat>0xFF)
			invalid_cmd(argv[0]);
		else{
			const uint8_t *p=NULL;
			unsigned len=0;
			printk("\t发送%d号指令数据\n",dat);
			FLASH_ErasePage(USER_CONFIG_AREA);	
			switch(dat){
				case 0:		
						p=touchmode;
						len = 9;
					break;
				case 1:
						p=image_disp;
						len = 9;
					break;
				case 2:
						p=image_cut;
						len=22;
					break;
				case 3:
						p=draw_rect;
				    len=17;
				  break;
				case 4:
					  p=draw_txt;
				    len=15;
					break;
				case 5:
					p=set_color;
				    len=12;
					break;
				case 6:
					p=set_strmode;
				  len=11;
					break;
				default:
					break;			
			}
			for(dat=0;dat<len;dat++){
				USART2->DR = p[dat];
				while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
			}		
		}
	}
}

user_command_t  gui_test_cmd = {
	 "gui",
	 command_lcd_test,
	 NULL,
	 "\tgui <0-91>\t\t\t--GUI测试"
 }; 
#endif
//#define USE_GUI_EN
#ifdef USE_GUI_EN 
  static unsigned gui_dat[256];
	void command_gui_enable(int argc,const char **argv){
	int ret,i;
	if(argc != 2)
		invalid_cmd(argv[0]);
	else{
		if(STRNCMP("ON",argv[1],STRLEN("ON"))==0){
			FLASH_Unlock();
			for(i=0;i<256;i++){
				gui_dat[i]=*(volatile unsigned*)(USER_CONFIG_AREA+i*4);
			}
			FLASH_ErasePage(USER_CONFIG_AREA);
			gui_dat[3]=0x00000000;
			for(i=0;i<256;i++){
				FLASH_ProgramWord(USER_CONFIG_AREA+i*4,   gui_dat[i]);
			}
			printk("\tGUI 开启...\n");
		}
    else if(STRNCMP("OFF",argv[1],STRLEN("OFF"))==0){
			FLASH_Unlock();
			for(i=0;i<256;i++){
				gui_dat[i]=*(volatile unsigned*)(USER_CONFIG_AREA+i*4);
			}
			FLASH_ErasePage(USER_CONFIG_AREA);
			gui_dat[3]=0xFFFFFFFF;
			for(i=0;i<256;i++){
				FLASH_ProgramWord(USER_CONFIG_AREA+i*4,   gui_dat[i]);
			}
			printk("\tGUI 关闭...\n");
		}
		else
			invalid_cmd(argv[0]);				
	}
}

user_command_t  gui_enable_cmd = {
	 "gui",
	 command_gui_enable,
	 NULL,
	 "\tgui <--/-->\t\t\t--GUI开启/关闭"
 }; 
#endif
 
#define BC7281B_TEST
#ifdef BC7281B_TEST
void command_bc7281_opt(int argc,const char **argv){
	unsigned dat1,dat2;
	int ret;
	if(argc != 3 && argc != 4)
		invalid_cmd(argv[0]);
	else{
		switch(argc)
		{
			case 3:
				if(STRNCMP("read",argv[1],STRLEN("read"))==0){
					dat1=stringtoul(argv[2],&ret);
					printk("\t显示地址:%02x 数据:%02x\n",dat1,Disp_Read(dat1));
				}else
					invalid_cmd(argv[0]);
				break;
			case 4:
				if(STRNCMP("write",argv[1],STRLEN("write"))==0){
					dat1=stringtoul(argv[2],&ret);
					dat2=stringtoul(argv[3],&ret);
					Disp_Write(dat1,dat2);
					printk("\t显示地址:%02x 写入数据:%02x\n",dat1,dat2);
				}
				else if(STRNCMP("config",argv[1],STRLEN("config"))==0){
					dat1=stringtoul(argv[2],&ret);
					dat2=stringtoul(argv[3],&ret);
					char led[4]={0xFF,0xFF,0xFF,0xFF};
					led[dat1]&=(1<<dat2)^0xFF;
					for(unsigned i=0;i<4;i++)
						Disp_Write(i,led[i]);
					printk("\t显示地址:%02x 写入数据:%02x\n",dat1,led[dat1]);
				}
				else
					invalid_cmd(argv[0]);
				break;
			default:
				invalid_cmd(argv[0]);
				break;
		}
	}
}

user_command_t  bc7281b_opt_cmd = {
	 "disp",
	 command_bc7281_opt,
	 NULL,
	 "\tdisp \t\t\t\t--显示操作测试"
 }; 
#endif

#define  FIRE_CONFIG
#ifdef FIRE_CONFIG
void command_fire_config(int argc,const char **argv){
	unsigned dat1,dat2;
	static unsigned counter = 0;
	int ret;
	if(argc != 3 && argc != 2 && argc != 4)
		invalid_cmd(argv[0]);
	else{
		switch(argc)
		{
			case 2:
				if(STRNCMP("info",argv[1],STRLEN("info"))==0){
					printk("\tinfo:1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,2016,1,13,8,58,");
					printk("%d\n",counter++);
				}else
					invalid_cmd(argv[0]);
				break;
			case 3:
				if(STRNCMP("read",argv[1],STRLEN("read"))==0){
					dat1=stringtoul(argv[2],&ret);
					printk("\t显示地址:%02x 数据:%02x\n",dat1,Disp_Read(dat1));
				}
				else
					invalid_cmd(argv[0]);
				break;
			case 4:
				if(STRNCMP("write",argv[1],STRLEN("write"))==0){
					dat1=stringtoul(argv[2],&ret);
					dat2=stringtoul(argv[3],&ret);
					Disp_Write(dat1,dat2);
					printk("\t显示地址:%02x 写入数据:%02x\n",dat1,dat2);
				}
				else if(STRNCMP("config",argv[1],STRLEN("config"))==0){
					dat1=stringtoul(argv[2],&ret);
					dat2=stringtoul(argv[3],&ret);
					char led[4]={0xFF,0xFF,0xFF,0xFF};
					led[dat1]&=(1<<dat2)^0xFF;
					for(unsigned i=0;i<4;i++)
						Disp_Write(i,led[i]);
					printk("\t显示地址:%02x 写入数据:%02x\n",dat1,led[dat1]);
				}
				else
					invalid_cmd(argv[0]);
				break;
			default:
				invalid_cmd(argv[0]);
				break;
		}
	}
}

user_command_t  fire_config_cmd = {
	 "fire",
	 command_fire_config,
	 NULL,
	 "\tfire \t\t\t\t--WIFI 测试"
 }; 
#endif
 /*********************************************************************************************************
** 函数名称: parseargs
** 功能描述: 解析用户命令。
** 输　入: cp		要发送数据的缓冲区指针
** 输　出: 无
** 全局变量: 无
** 调用模块: 
**
** 作　者: 
** 日　期: 
**-------------------------------------------------------------------------------------------------------
** 修改人: 
** 日　期: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
/* Register basic user commands */
int init_builtin_cmds(void)
{
#ifdef FIRE_CONFIG
	add_command(&fire_config_cmd);
#endif
#ifdef BC7281B_TEST			
	
	add_command(&bc7281b_opt_cmd);
#endif
#ifdef USE_GUI_TEST_EN 
	add_command(&gui_test_cmd);
#endif
#ifdef USE_PROTOCOL_TEST_EN
	add_command(&protocol_test_cmd);
#endif
#ifdef USE_GUI_EN
	add_command(&gui_enable_cmd);
#endif
#ifdef FLASH_RW
	add_command(&flash_read_cmd);
	add_command(&flash_write_cmd);
#endif
#ifdef STKCHK
	add_command(&stackcheck_cmd);
#endif
#ifdef CONFIG_CMD_PROMPT
	add_command(&prompt_cmd );
#endif
#ifdef USE_SPIFLASH
add_command(&usespiflash_cmd);
#endif
#ifdef SUBID
	add_command(&subid_cmd);
#endif 
	add_command(&reset_cmd );
#ifdef INFO
	add_command(&info_cmd );
#endif
	add_command(&save_cmd);
#ifdef DUMP
	add_command(&dump_cmd);
#endif
	add_command(&help_cmd);
	return 0;
}


