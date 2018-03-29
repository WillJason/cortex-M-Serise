/*
 * vivi/drivers/serial/term.c: It's a simple serial termial.
 *
 * Copyright (C) 2002 MIZI Research, Inc.
 *
 * This code is GPL.
 *
 * Author: Janghoon Lyu <nandy@mizi.com>
 * Date  : $Date: 2004/02/04 06:22:25 $
 *
 * $Revision: 1.1.1.1 $
 */


#include "includes.h"

extern char prompt[];
const char verst[]=__TIME__;
const char versd[]=__DATE__;
const char password[]="txdh";
const char iappassword[]="iapprogram";
char cmd_buf[MAX_CMDBUF_SIZE];
void serial_terminal(void)
{
		printk("\n**********************DFMC************************\n");
    printk(APP_NAME);
    printk("¹Ì¼þ°æ±¾£ºv1.0  							      \n");
    printk("±àÐ´£ºhwc                                         \n");
    printk("°æ±¾ÈÕÆÚ:");
		printk("  %s",versd);
    printk("  %s\n",verst);
    printk("**************************************************\n");    
    for(;;){
         printk("ÇëÊäÈëÃÜÂë:");
         getcmd(cmd_buf,MAX_CMDBUF_SIZE);        
         	if(STRNCMP(password,cmd_buf,STRLEN(password))==0)
            	break; 
         	else
           		printk("ÃÜÂë´íÎó£¬ÇëÖØÐÂÊäÈë!\n");
           }  
          
	for (;;) {
		printk("%s > ", prompt);
		getcmd(cmd_buf, MAX_CMDBUF_SIZE);

		/* execute a user command */
		if (cmd_buf[0])
			exec_string(cmd_buf);
	}
}
