#ifndef MUTEX_H_
#define MUTEX_H_

typedef struct mutex_t
{
	char* name;
	int value;
	int id;	
} mutex_t;

typedef struct mutex_t* mutexADT;

mutex_t* mutexInit(char *name);
int mutexLock(mutex_t * mut);
int mutexUnlock(mutex_t * mut);
int mutexListSize();
int mutexClose(mutex_t* mut);
void closeAllMutex();
void freeMutexList();

#endif
