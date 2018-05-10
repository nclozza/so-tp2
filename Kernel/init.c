#include "init.h"
#include "scheduler.h"
#include "videoDriver.h"
#include "processes.h"
#include "memorymanager.h"

static void *const sampleCodeModuleAddress = (void *)0x400000;

void _hlt();

void init()
{
	exec_process(createProcess((uint64_t)sampleCodeModuleAddress, 0,0, "shell"));
	//set_foreground_process(get_process_by_pid(1));

	while (1)
	{
		_hlt();
	}
}
