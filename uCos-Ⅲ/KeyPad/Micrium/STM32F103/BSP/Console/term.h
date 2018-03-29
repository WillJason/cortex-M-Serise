#ifndef _TERM_H_
#define _TERM_H_

#include "stdio.h"
#include "getcmd.h"


#define ISDIGIT     ASCII_IsDig
#define STRLEN      Str_Len
#define MEMINIT     Mem_Init
#define MEMSET      Mem_Set
#define MEMCPY      Mem_Copy
#define STRNCMP     Str_Cmp_N
#define STRCMP      Str_Cmp
#define STRCAT      Str_Cat
#define STRCPY			Str_Copy

static FILE *file=NULL;

#define PUTCC(x)     fputc(x,file)						  
#define GETCC()      fgetc(file) 
//#define printk       printf

extern char cmd_buf[MAX_CMDBUF_SIZE];
extern void serial_terminal(void);
#endif

