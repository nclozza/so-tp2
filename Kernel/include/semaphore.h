#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

typedef struct sem_t
{
	char *name;
	int value;
	int id;
} sem_t;

typedef struct sem_t *semADT;

sem_t *sem_open(char *name);
int sem_post(sem_t *sem);
int sem_wait(sem_t *sem);
int semaphoresListSize();
int sem_close(sem_t *sem);
void freeSemaphoresList();

#endif
