#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

typedef struct sem_t
{
	char* name;
	int value;
	int id;	
}sem_t;

typedef struct sem_t* semADT;

int sem_open(char *name);
int sem_post(int id);
int sem_wait(int id);
int semaphoresListSize();
int sem_close(int id);
void freeSemaphoresList();

#endif
