#include "mutex.h"
#include "mutexTestLib.h"
#include <stdio.h>
#include <stdlib.h>

char* name;
mutexADT openedMutex = NULL;
mutexADT testingMutex = NULL;
int testingMutexValue;
int listSize = 0;
int size = 0;

void givenAName();
void whenNameIsPassedToOpen();
void thenMutexIsReturned();
void givenAMutex();
void givenAMutexLocked();
void whenMutexIsLocked();
void thenValueOfMutexDecreases();
void whenUnlockedMutex();
void thenValueOfMutexIncreases();
void thenSizeOfMutexListRemainsTheSame();
void thenSizeOfMutexListIncreases();
void whenMutexIsClosed();
void thenSizeOfMutexListDecreases();

void testMutexIsCreated()
{
	givenAName();
	whenNameIsPassedToOpen();
	thenMutexIsReturned();
	thenSizeOfMutexListIncreases();
}

void testMutexValueDecreasesWhenLock()
{
	givenAMutex();
	whenMutexIsLocked();
	thenValueOfMutexDecreases();
}

void testMutexValueIncreasesWhenUnlock()
{
	givenAMutexLocked();
    whenUnlockedMutex();
	thenValueOfMutexIncreases();
}

void testIfMutexAlreadyCreatedDoesNotCreateNewOne()
{
	givenAName();
	whenNameIsPassedToOpen();
	thenSizeOfMutexListRemainsTheSame();
	thenMutexIsReturned();
}

void testMutexIsClosed()
{
	givenAMutex();
	whenMutexIsClosed();
	thenSizeOfMutexListDecreases();
}


void givenAName()
{
	name = "MutNameForTest";
}

void whenNameIsPassedToOpen()
{
	openedMutex = mutex_init(name);
}

void thenMutexIsReturned()
{
	checkIsNotNull((void*)openedMutex);
}

void givenAMutex()
{
	if(testingMutex == NULL)
		testingMutex = openedMutex;
}

void whenMutexIsLocked()
{
	testingMutexValue = mutex_lock(testingMutex);
}

void thenValueOfMutexDecreases()
{
	checkIsZero(testingMutexValue);
}

void givenAMutexLocked()
{

}

void whenUnlockedMutex()
{
    testingMutexValue = mutex_unlock(testingMutex);
}

void thenValueOfMutexIncreases()
{
    checkIsNotZero(testingMutexValue);
}

void thenSizeOfMutexListRemainsTheSame()
{
	size = mutexListSize();
	checkSizeOfMutexList(listSize,size);	
}

void thenSizeOfMutexListIncreases()
{
	size = mutexListSize();
	listSize++;
	checkSizeOfMutexList(listSize,size);
}

void whenMutexIsClosed()
{
	if(testingMutex!=NULL)
		mutex_close(testingMutex);
}
void thenSizeOfMutexListDecreases()
{
	listSize--;
	size = mutexListSize();
	checkSizeOfMutexList(listSize,size);
}

void finishedTesting()
{
	mutex_close(openedMutex);
	freeMutexList();
}

int main(int argc, char const *argv[])
{
	printf("Testing Mutex is created...\n");
	testMutexIsCreated();

	printf("Testing Mutex value decreases when lock...\n");
	testMutexValueDecreasesWhenLock();

	printf("Testing Mutex value increases when unlock...\n");
	testMutexValueIncreasesWhenUnlock();

	printf("Testing if Mutex already exists, none is created\n");
	testIfMutexAlreadyCreatedDoesNotCreateNewOne();

	printf("Testing closing a Mutex...\n");
	testMutexIsClosed();

	finishedTesting();

	return 0;
}