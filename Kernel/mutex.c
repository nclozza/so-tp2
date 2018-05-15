#include <stdint.h>
#include "mutex.h"
#include "memorymanager.h"
#include "lib.h"
#include "processes.h"
#include "scheduler.h"

static mutexADT *mutex;
static int id = 0;
static int numberOfMutexes = 0;

mutex_t *mutexInit(char *name)
{
	int i;
	for (i = 0; i < numberOfMutexes; i++)
	{
		if (strcmpKernel(name, mutex[i]->name) == 0)
		{
			return mutex[i];
		}
	}
	mutexADT newMutex = (mutexADT)malloc(sizeof(mutex_t));
	newMutex->name = (char *)malloc(strlenKernel(name) + 1);
	strcpyKernel(newMutex->name, name);
	newMutex->value = 1;
	newMutex->id = id;
	id++;
	numberOfMutexes++;
	mutex = (mutexADT *)malloc(numberOfMutexes * sizeof(mutexADT));
	mutex[numberOfMutexes - 1] = newMutex;
	return newMutex;
}

int mutexLock(mutex_t *mut)
{
	if (mut->value == 1)
	{
		mut->value--;
	}
	else
	{
		process *p = getCurrentProcess();
		blockProcess(p);
		addBlockedProcessToList(mut->id, p, 1);
	}
	return 0;
}

int mutexUnlock(mutex_t *mut)
{
	if (mut->value == 0)
	{
		unblockProcessesFromList(mut->id, 1);

		mut->value++;
	}
	return mut->value;
}

int mutexListSize()
{
	return numberOfMutexes;
}

int mutexClose(mutex_t *mut)
{
	int i;
	for (i = 0; i < numberOfMutexes; i++)
	{
		if (mutex[i]->id == mut->id)
		{
			free(mutex[i]->name);
			free(mutex[i]);

			int j;
			for (j = i; j < numberOfMutexes - 1; j++)
			{
				mutex[j] = mutex[j + 1];
			}

			numberOfMutexes--;

			return 0;
		}
	}
	return 1;
}

void closeAllMutex()
{
	int i;
	for (i = numberOfMutexes; i > 0; i--)
	{
		mutexClose(mutex[i]);
	}
}

void freeMutexList()
{
	free(mutex);
}