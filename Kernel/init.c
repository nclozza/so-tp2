#include "init.h"
#include "scheduler.h"
#include "videoDriver.h"
#include "processes.h"
#include "memorymanager.h"

static void *const sampleCodeModuleAddress = (void *)0x400000;

void _hlt();
void _sti();

void init()
{
  _sti();
  // printString("\n", 0, 155, 255);
  // printInt(shell->pid, 0, 155, 255);
  // printString("\n", 0, 155, 255);
  exec_process(createProcess((uint64_t)sampleCodeModuleAddress, 0, "shell"));
  // printString("\n", 0, 155, 255);
  // printString("ASDASD", 0, 155, 255);
  // printString("\n", 0, 155, 255);
  set_foreground_process(get_process_by_pid(1));

  /*
	while (1) {
		_hlt();
	}
  */
}
