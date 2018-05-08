#include <stdint.h>
//#include <stdio.h>
#include "semaphore.h"
#include "memorymanager.h"
#include "lib.h"
#define NULL ((void *)0)

static semADT* semaphores;
static int id = 0;
static int numberOfSemaphores = 0;

int sem_open(char *name)
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
	newSemaphore->value = 0;
	newSemaphore->id = id;
	id++;
	numberOfSemaphores++;
	semaphores = (semADT *)malloc(numberOfSemaphores  * sizeof(semADT)); // realloc
	semaphores[numberOfSemaphores - 1] = newSemaphore;
	return newSemaphore->id;
}

int sem_post(int id)
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
	//TODO: SCHEDULER ADDS
	sem->value++;
	return sem->value;
}

int sem_wait(int id)
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
	if(sem->value <=0)
	{
		while(1);
		//TODO: SCHEDULER REMOVES	
	}
	return 0;
}

int semaphoresListSize()
{
	return numberOfSemaphores;
}

int sem_close(int id)
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
