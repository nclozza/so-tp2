#include <stdint.h>
#include "semaphore.h"
#include "memorymanager.h"
#include "lib.h"
#include "processes.h"
#include "scheduler.h"
#include "videoDriver.h"

static semADT* semaphores;
static int id = 0;
static int numberOfSemaphores = 0;

int semOpen(char *name)
{
	int i;
	for (i = 0; i < numberOfSemaphores; i++)
	{
		if (strcmpKernel(name, semaphores[i]->name) == 0)
		{
			return semaphores[i]->id;
		}
	}
	semADT newSemaphore = (semADT)malloc(sizeof(sem_t));
	newSemaphore->name = (char *)malloc(strlenKernel(name) + 1);
	strcpyKernel(newSemaphore->name, name);
	newSemaphore->value = 1;
	newSemaphore->id = id;
	id++;
	numberOfSemaphores++;
	semaphores = (semADT *)realloc(semaphores,numberOfSemaphores  * sizeof(semADT));
	semaphores[numberOfSemaphores - 1] = newSemaphore;
	return newSemaphore->id;
}

int semPost(int id)
{
	sem_t* sem = NULL;
	int i;
	for(i = 0; i < numberOfSemaphores; i++)
	{
		if(semaphores[i]->id == id)
		{			
			sem = semaphores[i];
		}
	}
	if(sem == NULL)
		return 1;
	
	if(sem->value<=0)
		unblockProcessesFromList(sem->id,0);	

	sem->value++;

	return sem->value;
}

int semWait(int id)
{
	sem_t* sem = NULL;
	int i;
	for(i = 0; i < numberOfSemaphores; i++)
	{
		if(semaphores[i]->id == id)
		{			
			sem = semaphores[i];
		}
	}
	if(sem == NULL)
		return 1;

	sem->value--;
	if(sem->value < 0)
	{
		process* p = getCurrentProcess();		
		blockProcess(p);
		addBlockedProcessToList(sem->id, p,0);

	}
	return 0;
}

int semaphoresListSize()
{
	return numberOfSemaphores;
}

int semClose(int id)
{
	int i;
	for (i = 0; i < numberOfSemaphores; i++)
	{
		if(semaphores[i]->id == id)
		{			
			free(semaphores[i]->name);
			free(semaphores[i]);

			int j;
			for (j = i; j < numberOfSemaphores - 1; j++)
			{
				semaphores[j] = semaphores[j + 1];
			}

			numberOfSemaphores--;

			return 0;
		}
	}
	return 1;
}

void freeSemaphoresList()
{
	free(semaphores);
}
