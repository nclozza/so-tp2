#include "messageQueue.h"

typedef struct messageCDT
{
	char* name;
	int id;
	char* buffer;
	int contentCount;
	int messageSize;
}messageCDT;

static int id = 0;
static int messagesCount = 0;
static messageADT* messages;
//static messageOperation messageOperations[MESSAGE_OPERATIONS];
static queueADT rMsgQueues[MAX_QUEUES], wMsgQueues[MAX_QUEUES];

uint8_t initMsg(int msgId)
{
  if(openQueue(msgId,rMsgQueues)==SUCCESS && openQueue(msgId,wMsgQueues)==SUCCESS)
    return SUCCESS;
  return FAIL;
}

void msgString(char* buffer)
{
	strcatKernel(buffer, "Messages: ");
	for(int i = 0; i < messagesCount ; i++)
	{
		strcatKernel(buffer,messages[i]->name);
		if(i != messagesCount -1)
			strcatKernel(buffer, ", ");
	}
}

void initMessages()
{
	messages = (messageADT*)malloc(sizeof(messageADT));
}

int createMessage(char* name, int messageSize)
{
	if(id == 0)
		initMessages();

	messageADT newMessage = (messageADT)malloc(sizeof(messageCDT));
	strcpyKernel(newMessage->name, name);
	newMessage->id = id;
	newMessage->messageSize = messageSize;
	id++;
	newMessage->buffer =(char*)malloc(messageSize*MAX_SIZE_BUFFER+1);

	for(int j=0; j<=((newMessage->messageSize)*MAX_SIZE_BUFFER); j++)
				newMessage->buffer[j] = 0;

	newMessage->contentCount = 0;
	messagesCount++;
	messages = realloc(messages, messagesCount * sizeof(messageADT));
	messages[messagesCount-1] = newMessage;
	initMsg(newMessage->id); //creates queue
	return newMessage->id;
}

int openMessage(char* name, int arg2)
{
	for (int i = 0; i < messagesCount; i++)
	{
		if(strcmpKernel(messages[i]->name, name) == 0)
			return messages[i]->id;
	}
	return -1;
}

int readMessage(char* buffer, int id)
{
	for (int i = 0; i < messagesCount; i++)
	{
		if(messages[i]->id == id)
		{
			if(messages[i]->contentCount <= 0)
				//block(id, READ);													//preguntarle a nico (se deberia bloquear porque no hay nada que leer, espera que alguien haga un write)

			strcpyKernel(buffer, messages[i]->buffer);
			messages[i]->contentCount = 0;

			for(int j=0; j<=((messages[i]->messageSize)*MAX_SIZE_BUFFER); j++)
				messages[i]->buffer[j] = 0;

			//unblock(messages[i]->id, WRITE);										//preguntarle a nico (avisa que ya termino de leer y que hay lugar para escribir)
			return SUCCESS;
		}
	}
	return FAIL;
}

int writeMessage(char* content, int id)
{
	for (int i = 0; i < messagesCount; i++)
	{
		if(messages[i]->id == id)
		{
			if(strlenKernel(content) > messages[i]->messageSize)
				return FAIL;

			if(messages[i]->contentCount >= MAX_SIZE_BUFFER)
				//block(messages[i]->id, WRITE);					//preguntarle a nico (se deberia bloquear porque no hay lugar para escribir, espera que alguien haga un read)

			messages[i]->contentCount++;
			strcatKernel(messages[i]->buffer, content);
			//unblock(messages[i]->id, READ);						//preguntarle a nico (avisa que ya termino de escribir y que hay algo para leer)
			return SUCCESS;
		}
	}
	return FAIL;
}

int closeMessage(char*arg1, int id)
{
	for (int i = 0; i < messagesCount; i++)
	{
		if(messages[i]->id == id)
		{
			destroyMsg(messages[i]->id); \
			free(messages[i]);

			for(int j = i; j < messagesCount-1; j++)
				messages[j] = messages[j+1];

			messagesCount--;
			return SUCCESS;
		}
	}
	return FAIL;
}

/*
int executeMessage(int operation, char* arg1, int arg2)
{
	if(operation < 0 || operation > MESSAGE_OPERATIONS)
		return -1;

	return (messageOperations[operation])(arg1, arg2);
}

void setupMessages()
{
	messageOperations[OPEN] = &openMessage;
	messageOperations[CLOSE] = &closeMessage;
	messageOperations[INIT] = &createMessage;
	messageOperations[READ] = &readMessage;
	messageOperations[WRITE] = &writeMessage;
}
*/

void destroyMsg(int msgId)
{
  if(msgId < MAX_QUEUES || msgId >= 0)
  {
    free(rMsgQueues[msgId]);
    rMsgQueues[msgId] = NULL;
    free(wMsgQueues[msgId]);
    wMsgQueues[msgId] = NULL;
  }
}

uint8_t openQueue(int i, queueADT * array)
{
  if(array[i] != NULL)
    return FAIL;

  array[i] = createQueue();

  if(array[i] == NULL)
    return FAIL;

  return SUCCESS;
}
