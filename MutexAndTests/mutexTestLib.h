#ifndef MUTEXTESTLIB_H_
#define MUTEXTESTLIB_H_

#include "mutex.h"

void checkIsNotNull(void* value);
void checkIsNotZero(int value);
void checkIsZero(int value);
void checkSizeOfMutexList(int mysize, int size);
void ok(char* success);
void fail(char* withError);

#endif
