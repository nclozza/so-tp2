#include "init.h"
#include "scheduler.h"
#include "videoDriver.h"
#include "processes.h"
#include "memorymanager.h"

static void *const sampleCodeModuleAddress = (void *)0x400000;

void init()
{
	runProcess(createProcess((uint64_t)sampleCodeModuleAddress, 0,0, "shell"));
	//setProcessForeground(getProcessByPid(1));

	while (1)
	{
		_hlt();
	}
}
