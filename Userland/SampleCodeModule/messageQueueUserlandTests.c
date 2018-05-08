#include "stdLib.h"
#include "shell.h"
#include <stdint.h>

void testMessageQueueIsCreated();
void givenAMessageName();
void givenASize();
void whenNameAndSizeArePassedToCreate();
void thenIdIsReturned();
void testMessageQueueIsOpened();
void whenMessageNameIsPassedToOpen();
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
void runUserlandMessageQueueTests();

#define SUCCESS 0
#define FAIL 1

char* messageName;
char* messageBuffer;
char* messageContent;
int messageSize;
int messageId, messageId2;
int messageTest;

void testMessageQueueIsCreated()
{
	givenAMessageName();
	givenASize();
	whenNameAndSizeArePassedToCreate();
	thenIdIsReturned();
}

void givenAMessageName()
{
	messageName = "MessageQueueNameForTest";
}

void givenASize()
{
	messageSize = 10;
}

void whenNameAndSizeArePassedToCreate()
{
	messageId = sysCreateMessage(messageName, messageSize);
}

void thenIdIsReturned()
{
	checkIsZero(messageId);
}

void testMessageQueueIsOpened()
{
	givenAMessageName();
	whenMessageNameIsPassedToOpen();
	thenExistingIdIsReturned();
}

void whenMessageNameIsPassedToOpen()
{
	messageId2 = sysOpenMessage(messageName, 0);
}

void thenExistingIdIsReturned()
{
	checkAreEqual(messageId, messageId2);
}

void testMessageQueueIsWritten()
{
	givenContent();
	whenContentAndIdArePassedToWrite();
	thenTestIsASuccess();
}

void givenContent()
{
	messageContent = "content";
}

void whenContentAndIdArePassedToWrite()
{
	messageTest = sysWriteMessage(messageContent, messageId);
}

void thenTestIsASuccess()
{
	checkIsZero(messageTest);	//zero = success
}

void testMessageQueueIsRead()
{
	givenABuffer();
	whenBufferAndIdArePassedToRead();
	thenCheckIfBufferAndContentAreEqual();
}

void givenABuffer()
{
	messageBuffer = (char*) malloc(messageSize*MAX_SIZE_BUFFER+1);
}

void whenBufferAndIdArePassedToRead()
{
	messageTest = sysReadMessage(messageBuffer, messageId);
}

void thenCheckIfBufferAndContentAreEqual()
{	
	int testAux = -1;
	if(messageTest == 0)
	{	//success
		testAux = strcmpKernel(messageBuffer, messageContent);
	}
	checkIsZero(testAux);
}

void testMessageQueueIsClosed()
{
	whenIdIsPassedToClose();
	thenTestIsASuccess();
}

void whenIdIsPassedToClose()
{
	messageTest = sysCloseMessage("", messageId);
}

finishedMessageTesting(){
	sysFree(messageName);
	sysFree(messageBuffer);
	sysFree(messageContent);
}

void runUserlandMessageQueueTests()
{
	sysPrintString("Testing if messageQueue is created...\n", 128, 128, 128);
	testMessageQueueIsCreated();

	sysPrintString("Testing if messageQueue is opened...\n", 128, 128, 128);
	testMessageQueueIsOpened();

	sysPrintString("Testing if messageQueue is written...\n", 128, 128, 128);
	testMessageQueueIsWritten();

	sysPrintString("Testing if messageQueue is read...\n", 128, 128, 128);
	testMessageQueueIsRead();

	sysPrintString("Testing if messageQueue is closed...\n", 128, 128, 128);
	testMessageQueueIsClosed();

	finishedMessageTesting();
}

