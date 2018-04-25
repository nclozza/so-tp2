#ifndef TESTLIB_H_
#define TESTLIB_H_

#include "semaphore.h"

void checkIsNotNull(void* value);
void checkIsNotZero(int value);
void checkSizeOfSemaphoreList(int mysize, int size);
void ok(char* success);
void fail(char* withError);

#endif
