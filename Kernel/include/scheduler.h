#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "processes.h"

#include "defs.h"

#define MAX_PROCESSES 128
#define QUANTUM 1

typedef struct node
{
	int quantum;
	process *p;
	struct node *next;
} nodeList;

typedef struct blockedProcess
{
	process* process;
	int semId;
} blockedProcess;

typedef struct blockedProcess* blockedProcessADT;
void addBlockedProcessToList(int semId, process* p);
void unblockProcessesFromList(int semId);

uint64_t nextProcess(uint64_t current_rsp);

uint64_t runProcess(process * new_process);
void killProcess();
void yieldProcess();

void _changeProcess(uint64_t rsp);
void _yieldProcess();

process * getCurrentProcess();

void increaseQuantum();
void decreaseQuantum();


#endif
