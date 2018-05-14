#include "memorymanager.h"
#include "scheduler.h"
#include "dirs.h"
#include "videoDriver.h"
#include "mutex.h"
#include "processes.h"
#include "defs.h"
#include "interrupts.h"

static void addProcess(process *p);
static void setNextCurrent();

/* Proceso actualmente corriendo */
static nodeList *current = NULL;
static nodeList *prev = NULL;

process *getCurrentProcess()
{
	return current->p;
}

uint64_t nextProcess(uint64_t current_rsp)
{
	if (current == NULL)
	{
		return current_rsp;
	}

	decreaseQuantum();

	if (current->quantum > 0)
		return current_rsp;

	current->quantum = QUANTUM;

	setProcessRsp(current->p, current_rsp);

	prev = current;
	current = current->next;

	setNextCurrent();

	return getProcessRsp(current->p);
}

uint64_t runProcess(process *new_process)
{
	int pid;

	addProcess(new_process);

	pid = getProcessPid(new_process);

	if (pid == 0)
		_changeProcess(getProcessRsp(current->p));

	return pid;
}

static void addProcess(process *p)
{
	nodeList *new_node = (nodeList *)malloc(sizeof(*new_node));

	new_node->p = p;
	new_node->quantum = QUANTUM;

	if (current == NULL)
	{
		current = new_node;
		current->next = current;
		prev = current;
	}
	else
	{
		new_node->next = current->next;
		current->next = new_node;
	}
}

/* Se avanza con el proceso que está delante */
void killProcess()
{

	nodeList *n = current;

	removeProcess(n->p);

	prev->next = current->next;

	current = current->next;

	setNextCurrent();

	free((void *)n);

	increaseQuantum(); /* Se le da un quantum al nuevo proceso */

	_changeProcess(getProcessRsp(current->p));
}

static void setNextCurrent()
{
	while (isProcessBlocked(current->p) || isProcessDeleted(current->p))
	{
		nodeList *next = current->next;

		if (isProcessDeleted(current->p))
		{
			prev->next = next;
			removeProcess(current->p);
			free((void *)current);
		}
		else
			prev = current;

		current = next;
	}
}

void increaseQuantum()
{
	current->quantum += 1;
}

void decreaseQuantum()
{
	current->quantum -= 1;
}
