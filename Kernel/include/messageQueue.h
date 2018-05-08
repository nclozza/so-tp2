#ifndef BLOCKING_MESSAGE_H
#define BLOCKING_MESSAGE_H

#include "lib.h"
#include "genericQueue.h"
#include "memorymanager.h"

#define MESSAGE_OPERATIONS 5
#define MAX_QUEUES 10
#define MAX_SIZE_BUFFER 10

//operations
#define OPEN 0
#define CLOSE 1
#define INIT 2
#define READ 3
#define WRITE 4

typedef struct messageCDT* messageADT;
typedef int (messageOperation)(char, int);

void msgString(char* buffer);
int createMessage(char* name, int messageSize);
int openMessage(char* name, int arg2);
int readMessage(char* buffer, int id);
int writeMessage(char* content, int id);
int closeMessage(char*arg1, int id);
int executeMessage(int operation, char* arg1, int arg2);
void setupMessages();
uint8_t initMsg(int msgId);
uint8_t openQueue(int i, queueADT * array);
void destroyMsg(int msgId);
void initMessages();

#endif