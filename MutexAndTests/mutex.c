#include "mutex.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static mutexADT* mutex;
static int id = 0;
static int numberOfMutexes = 0;

mutex_t* mutex_init(char *name)
{
    int i;
	for (i = 0; i < numberOfMutexes; i++)
	{
		if(strcmp(name,mutex[i]->name)==0)
		{			
			return mutex[i];
		}
	}
	mutexADT newMutex = malloc(sizeof(mutex_t));
	newMutex->name = malloc(strlen(name)+1);
	strcpy(newMutex->name,name); 
	newMutex->value = 1;
	newMutex->id = id;
	id++;
	numberOfMutexes++;
	mutex = realloc(mutex,numberOfMutexes * sizeof(mutexADT));
	mutex[numberOfMutexes - 1] = newMutex;
	return newMutex;
}

int mutex_lock(mutex_t * mut)
{
    if(mut->value == 1)
    {
	    mut->value--;
    }        
	else
	{
		//TODO: SCHEDULER REMOVES	
	}
	return 0;
}

int mutex_unlock(mutex_t * mut)
{
    //TODO: SCHEDULER ADDS
	mut->value++;
	return mut->value;
}

int mutexListSize()
{
    return numberOfMutexes;
}


int mutex_close(mutex_t* mut)
{
	int i;
	for(i = 0; i < numberOfMutexes; i++)
	{
		if(mutex[i]->id == mut->id)
		{			
			free(mutex[i]->name);
			free(mutex[i]);

			int j;
			for(j = i; j < numberOfMutexes-1; j++)
			{
				mutex[j] = mutex[j+1];
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
    for (i=numberOfMutexes; i > 0; i--)
    {
        mutex_close(mutex[i]);
    }
}

void freeMutexList()
{
	free(mutex);
}