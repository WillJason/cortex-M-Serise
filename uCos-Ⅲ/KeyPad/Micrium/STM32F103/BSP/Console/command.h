/*
 * vivi/include/command.h
 *
 */
#ifndef _VIVI_COMMAND_H_
#define _VIVI_COMMAND_H_
typedef struct user_data{ 
    unsigned short baselist[6] ;    
    char canbaud[4] ;
	char subid      ;
	char cardnum;
	char baseindex;
	char fend;
	unsigned short cardbase;
	char rip[4];
	char lip[4];
	char msk[4];
	char gateway[4];
	unsigned short udprport;
	unsigned short udplport;
	char mac_addr[6];
	unsigned short ipport;
}user_data_t;
//struct user_command_t;

typedef struct user_command {
	const char *name;
	void (*cmdfunc)(int argc, const char **);
	struct user_command *next_cmd;
	const char *helpstr;
} user_command_t;

typedef struct user_subcommand {
	const char *name;
	void (*cmdfunc)(int argc, const char **);
	const char *helpstr;
} user_subcommand_t;
/* General interfaces */
extern void add_command(user_command_t *cmd);
void execcmd(int, const char **);
void exec_string(char *);
void execsubcmd(user_subcommand_t *, int, const char **);
void print_usage(char *strhead, user_command_t *);
void invalid_cmd(const char *cmd_name);
int init_builtin_cmds(void);

#endif /* _VIVI_COMMAND_H_ */


