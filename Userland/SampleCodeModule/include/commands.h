#ifndef COMMANDS_H
#define COMMANDS_H

#define CMD_SIZE 9

int help(int argc,char* argv[]);
int echo(int argc,char* argv[]);
int displayTime(int argc,char* argv[]);
int setTimeZone(int argc,char* argv[]);
int setFontColor(int argc,char* argv[]);
int clear(int argc,char* argv[]);
int calculate(int argc,char* argv[]);
int plot(int argc,char* argv[]);
int exit(int argc,char* argv[]);
int opcode(int argc,char* argv[]);
int prodcons(int argc,char* argv[]);


typedef struct{
	char* name;
	int (*function)(int argc,char* argv[]);
} command;

static command commands[] = {
	{"help\n",help},
	{"echo\n",echo},
	{"displayTime\n",displayTime},
	{"setTimeZone\n",setTimeZone},
	{"setFontColor\n",setFontColor},
	{"clear\n",clear},
	{"calculate\n",calculate},
	{"plot\n",plot},	
	{"exit\n",exit},
	{"opcode\n",opcode},
	{"prodcons\n",prodcons}
};

#endif