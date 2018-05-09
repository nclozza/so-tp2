#include "stdLib.h"
#include "shell.h"
#define PAGE 0x1000
typedef int (*entry_point) (int, char **);
static void executer(void ** params);

int execProcess(void* function,char** argv, char* name, int foreground)
{
	int pid = sysExec(executer,argv,name);	
	if(foreground == 1)
	{
		sysSetForeground(pid);
	}
	return pid;
	return 1;
	
}

static void executer(void ** params) {
	void ** memory = sysMalloc(PAGE);
	entry_point function;
	char ** argv;
	int argc;
	/* int ret_value; */

	memcpy(memory, params, PAGE);

	function = memory[0];
	argv = (char **) memory + 1;
	argc = 0;

	while (argv[argc] != NULL)
		argc++;

	(*function)(argc, argv);

	sysFree(memory);
	sysSetForeground(sysPpid());
	sysEndProcess();
}