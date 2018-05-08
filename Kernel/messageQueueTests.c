#include "messageQueue.h"
#include "testlib.h"
#include <stdio.h>
#include <stdlib.h>
#include "videoDriver.h"

void testMessageQueueIsCreated();
void givenAName();
void givenASize();
void whenNameAndSizeArePassedToCreate();
void thenIdIsReturned();
void testMessageQueueIsOpened();
void whenNameIsPassedToOpen();
void thenExistingIdIsReturned();
void testMessageQueueIsWritten();
void givenContent();
void whenContentAndIdArePassedToWrite();
void thenTestIsASuccess();
void testMessageQueueIsRead();
void givenABuffer();
void whenBufferAndIdArePassedToRead();
void thenCheckIfBufferAndContentAreEqual();
void testMessageQueueIsClosed();
void whenIdIsPassedToClose();
int runMessageQueueTests();


#define SUCCESS 0
#define FAIL 1

char* name;
char* content;
int size;
int id, id2;
int test;

void testMessageQueueIsCreated()
{
	givenAName();
	givenASize();
	whenNameAndSizeArePassedToCreate();
	thenIdIsReturned();
}

void givenAName()
{
	name = "MessageQueueNameForTest";
}

void givenASize()
{
	size = 10;
}

void whenNameAndSizeArePassedToCreate()
{
	id = createMessage(name, size);
}

void thenIdIsReturned()
{
	checkIsZero(id);
}

void testMessageQueueIsOpened()
{
	givenAName();
	whenNameIsPassedToOpen();
	thenExistingIdIsReturned();
}

void whenNameIsPassedToOpen()
{
	id2 = openMessage(name, 0);
}

void thenExistingIdIsReturned()
{
	checkAreEqual(id, id2);
}

void testMessageQueueIsWritten()
{
	givenContent();
	whenContentAndIdArePassedToWrite();
	thenTestIsASuccess();
}

void givenContent()
{
	content = "content"
}

void whenContentAndIdArePassedToWrite()
{
	test = writeMessage(content, id);
}

void thenTestIsASuccess()
{
	checkIsZero(test);	//zero = success
}

void testMessageQueueIsRead()
{
	givenABuffer();
	whenBufferAndIdArePassedToRead();
	thenCheckIfBufferAndContentAreEqual();
}

void givenABuffer()
{
	buffer = malloc(size*MAX_SIZE_BUFFER+1);
}

void whenBufferAndIdArePassedToRead()
{
	test = readMessage(buffer, id);
}

void thenCheckIfBufferAndContentAreEqual()
{
	if(test == 0)	//success
		checkAreEqual(buffer, content);

	checkIsZero(test);
}

void testMessageQueueIsClosed()
{
	whenIdIsPassedToClose();
	thenTestIsASuccess();
}

void whenIdIsPassedToClose()
{
	test = closeMessage("", id);
}

int runMessageQueueTests()
{
	printString("Testing if messageQueue is created...\n", 128, 128, 128);
	testMessageQueueIsCreated();

	printString("Testing if messageQueue is opened...\n", 128, 128, 128);
	testMessageQueueIsOpened();

	printString("Testing if messageQueue is written...\n", 128, 128, 128);
	testMessageQueueIsWritten();

	printString("Testing if messageQueue is read...\n", 128, 128, 128);
	testMessageQueueIsRead();

	printString("Testing if messageQueue is closed...\n", 128, 128, 128);
	testMessageQueueIsClosed();

	//finishedTesting();

	return 0;
}

