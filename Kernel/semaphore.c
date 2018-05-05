#include <stdint.h>
//#include <stdio.h>
#include "semaphore.h"
#include "memorymanager.h"
#include "lib.h"
static semADT* semaphores;
static int id = 0;
static int numberOfSemaphores = 0;

sem_t* sem_open(char *name)
{
	int i;
	for (i = 0; i < numberOfSemaphores; i++)
	{
		if(strcmp(name,semaphores[i]->name)==0)
		{			
			return semaphores[i];
		}
	}
	semADT newSemaphore = (semADT)malloc(sizeof(sem_t));
	newSemaphore->name = (char*)malloc(strlen(name)+1);
	strcpy(newSemaphore->name,name); 
	newSemaphore->value = 0;
	newSemaphore->id = id;
	id++;
	numberOfSemaphores++;
	semaphores = (semADT*)malloc(numberOfSemaphores * sizeof(semADT));
	semaphores[numberOfSemaphores - 1] = newSemaphore;
	return newSemaphore;
}

int sem_post(sem_t * sem)
{
	//TODO: SCHEDULER ADDS
	sem->value++;
	return sem->value;
}

int sem_wait(sem_t * sem)
{
	sem->value--;
	if(sem->value <0)
	{
		//TODO: SCHEDULER REMOVES	
	}
	return 0;
}

int semaphoresListSize()
{
	return numberOfSemaphores;
}

int sem_close(sem_t* sem)
{
	int i;
	for(i = 0; i < numberOfSemaphores; i++)
	{
		if(semaphores[i]->id == sem->id)
		{			
			free(semaphores[i]->name);
			free(semaphores[i]);

			int j;
			for(j = i; j < numberOfSemaphores-1; j++)
			{
				semaphores[j] = semaphores[j+1];
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
