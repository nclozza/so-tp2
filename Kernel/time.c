#include "time.h"
#include "scheduler.h"
#include "defs.h"
#include "memorymanager.h"
#include "videoDriver.h"
#include "interrupts.h"

static unsigned long ticks = 0;

typedef struct c_sleep_process
{
	process *p;
	uint64_t ticks;
	struct c_sleep_process *next;
} sleep_process;


/* Controla la cantidad de ticks del timer tick */
void timer_handler()
{
	ticks++;
}

int ticks_elapsed()
{
	return ticks;
}

int seconds_elapsed()
{
	return ticks / 18;
}
