#include "semaphore.h"
#include "testlib.h"
#include <stdio.h>
#include <stdlib.h>

char* name;
semADT openedSemaphore = NULL;
semADT testingSemaphore = NULL;
int testingSemaphoreValue;
int listSize = 0;
int size = 0;

void givenAName();
void whenNameIsPassedToOpen();
void thenSemaphoreIsReturned();
void givenASemaphore();
void whenSemaphoreIsPosted();
void thenValueOfSemaphoreIncreases();
void thenSizeOfSemaphoreListRemainsTheSame();
void thenSizeOfSemaphoreListIncreases();
void whenSemaphoreIsClosed();
void thenSizeOfSemaphoreListDecreases();

void testSemaphoreIsCreated()
{
	givenAName();
	whenNameIsPassedToOpen();
	thenSemaphoreIsReturned();
	thenSizeOfSemaphoreListIncreases();
}

void testSemaphoreValueIncreasesWhenPostedTo()
{
	givenASemaphore();
	whenSemaphoreIsPosted();
	thenValueOfSemaphoreIncreases();
}

void testIfSemaphoreAlreadyCreatedDoesNotCreateNewOne()
{
	givenAName();
	whenNameIsPassedToOpen();
	thenSizeOfSemaphoreListRemainsTheSame();
	thenSemaphoreIsReturned();
}

void testSemaphoreIsClosed()
{
	givenASemaphore();
	whenSemaphoreIsClosed();
	thenSizeOfSemaphoreListDecreases();
}


void givenAName()
{
	name = "SemNameForTest";
}

void whenNameIsPassedToOpen()
{
	openedSemaphore = sem_open(name);
}

void thenSemaphoreIsReturned()
{
	checkIsNotNull((void*)openedSemaphore);
}

void givenASemaphore()
{
	if(testingSemaphore ==NULL)
		testingSemaphore = openedSemaphore;
}

void whenSemaphoreIsPosted()
{
	testingSemaphoreValue = sem_post(testingSemaphore);
}

void thenValueOfSemaphoreIncreases()
{
	checkIsNotZero(testingSemaphoreValue);
}

void thenSizeOfSemaphoreListRemainsTheSame()
{
	size = semaphoresListSize();
	checkSizeOfSemaphoreList(listSize,size);	
}

void thenSizeOfSemaphoreListIncreases()
{
	size = semaphoresListSize();
	listSize++;
	checkSizeOfSemaphoreList(listSize,size);
}

void whenSemaphoreIsClosed()
{
	if(testingSemaphore!=NULL)
		sem_close(testingSemaphore);
}
void thenSizeOfSemaphoreListDecreases()
{
	listSize--;
	size = semaphoresListSize();
	checkSizeOfSemaphoreList(listSize,size);
}

void finishedTesting()
{
	sem_close(openedSemaphore);
	freeSemaphoresList();
}

int main(int argc, char const *argv[])
{
	printf("Testing semaphore is created...\n");
	testSemaphoreIsCreated();

	printf("Testing semaphore value increases when posted...\n");
	testSemaphoreValueIncreasesWhenPostedTo();

	printf("Testing if semaphore already exists, none is created\n");
	testIfSemaphoreAlreadyCreatedDoesNotCreateNewOne();

	printf("Testing closing a semaphore...\n");
	testSemaphoreIsClosed();

	finishedTesting();

	return 0;
}