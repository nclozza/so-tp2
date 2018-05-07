#include "semaphore.h"
#include "testlib.h"
#include <stdio.h>
#include <stdlib.h>
#include "videoDriver.h"

char* name;
int openedSemaphore = -1;
int testingSemaphore = -1;
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
	checkIsNotMinusOne(openedSemaphore);
}

void givenASemaphore()
{
	if(testingSemaphore == -1 && openedSemaphore !=-1)
		testingSemaphore = openedSemaphore;
}

void whenSemaphoreIsPosted()
{
	testingSemaphoreValue = sem_post(testingSemaphore);
}

void thenValueOfSemaphoreIncreases()
{
	checkIsNotMinusOne(testingSemaphoreValue);
}

void thenSizeOfSemaphoreListRemainsTheSame()
{
	size = semaphoresListSize();
	checkSizeOfSemaphoreList(listSize, size);
}

void thenSizeOfSemaphoreListIncreases()
{
	size = semaphoresListSize();
	listSize++;
	checkSizeOfSemaphoreList(listSize, size);
}

void whenSemaphoreIsClosed()
{
	if(testingSemaphore!=-1)
		sem_close(testingSemaphore);
}
void thenSizeOfSemaphoreListDecreases()
{	
	listSize--;
	size = semaphoresListSize();
	checkSizeOfSemaphoreList(listSize, size);
}

void finishedTesting()
{
	sem_close(openedSemaphore);
	freeSemaphoresList();
}

void runSemaphoreTests()
{
	printString("Testing semaphore is created...\n", 128, 128, 128);
	testSemaphoreIsCreated();

	printString("Testing semaphore value increases when posted...\n", 128, 128, 128);
	testSemaphoreValueIncreasesWhenPostedTo();

	printString("Testing if semaphore already exists, none is created\n", 128, 128, 128);
	testIfSemaphoreAlreadyCreatedDoesNotCreateNewOne();

	printString("Testing closing a semaphore...\n", 128, 128, 128);
	testSemaphoreIsClosed();

	finishedTesting();
}