#ifndef COMMANDS_H
#define COMMANDS_H

#define CMD_SIZE 15

int help(int argc,char* argv[]);
int echo(int argc,char* argv[]);
int displayTime(int argc,char* argv[]);
int setTimeZone(int argc,char* argv[]);
int setFontColor(int argc,char* argv[]);
int clear(int argc,char* argv[]);
int calculate(int argc,char* argv[]);
int plot(int argc,char* argv[]);
void exit(int argc,char* argv[]);
int opcode(int argc,char* argv[]);
int prodcons(int argc,char* argv[]);
int ps(int argc, char* argv[]);


typedef struct{
	char* name;
	int (*function)(int argc,char* argv[]);
} command;

#endif