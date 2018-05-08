#include "messageQueue.h"
#include "testlib.h"
#include <stdio.h>
#include <stdlib.h>

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

void givenASize(){
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

int main(int argc, char const *argv[])
{
	printf("Testing if messageQueue is created...\n");
	testMessageQueueIsCreated();

	printf("Testing if messageQueue is opened...\n");
	testMessageQueueIsOpened();

	printf("Testing if messageQueue is written...\n");
	testMessageQueueIsWritten();


	printf("Testing if messageQueue is read...\n");
	testMessageQueueIsRead();

	printf("Testing if messageQueue is closed...\n");
	testMessageQueueIsClosed();

	//finishedTesting();

	return 0;
}

