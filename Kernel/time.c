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

static sleep_process *sleeping_processes = NULL;

static sleep_process *create_sleep_process(uint64_t ticks);
static void add_sleep_process(sleep_process *p);

/* Controla la cantidad de ticks del timer tick */
void timer_handler()
{
	printString("ESTOY EN EL TIMER HANDLER, HOLA CONI", 0, 155, 255);
	ticks++;
	sleep_process *current = sleeping_processes;
	sleep_process *prev = NULL;
	sleep_process *sp;

	while (current != NULL)
	{
		current->ticks -= 1;

		if (current->ticks <= 0)
		{
			sp = current;

			if (prev == NULL)
				sleeping_processes = current->next;
			else
				prev->next = current->next;

			current = current->next;
			free((void *)sp);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

/* Bloquea el proceso actual y lo pone en una lista con los ticks necesarios hasta despertar */
int sleep(uint64_t milliseconds)
{

	uint64_t wait_ticks = milliseconds / 55; // Hay 1 tick cada 55 milisegundos aproximadamente

	if (wait_ticks == 0)
		return 0;

	assign_quantum();

	sleep_process *new_sleep_p = create_sleep_process(wait_ticks);

	add_sleep_process(new_sleep_p);

	yield_process();

	return 1;
}

static sleep_process *create_sleep_process(uint64_t ticks)
{
	sleep_process *new_sleep_p = (sleep_process *)malloc(sizeof(*new_sleep_p));
	new_sleep_p->ticks = ticks;
	new_sleep_p->p = get_current_process();
	return new_sleep_p;
}

static void add_sleep_process(sleep_process *p)
{
	p->next = sleeping_processes;
	sleeping_processes = p;
}

int ticks_elapsed()
{
	return ticks;
}

int seconds_elapsed()
{
	return ticks / 18;
}
