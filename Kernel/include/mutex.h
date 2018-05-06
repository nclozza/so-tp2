#ifndef MUTEX_H_
#define MUTEX_H_

typedef struct mutex_t
{
	char* name;
	int value;
	int id;	
} mutex_t;

typedef struct mutex_t* mutexADT;

mutex_t* mutex_init(char *name);
int mutex_lock(mutex_t * mut);
int mutex_unlock(mutex_t * mut);
int mutexListSize();
int mutex_close(mutex_t* mut);
void closeAllMutex();
void freeMutexList();

#endif
