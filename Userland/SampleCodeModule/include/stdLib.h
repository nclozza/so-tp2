#ifndef STDLIB_H_
#define STDLIB_H_

#include <stdint.h>

#define IS_DIGIT(c) ((c - '0') >= 0 && (c - '0') <= 9)
#define DECIMAL_PLACES 4
void *memcpy(void *destination, const void *source, uint64_t length);
void reset(char *string, int size);
int strleng(const char *s);
void sysPrintString(char *string, int R, int G, int B);
void sysPrintInt(int num, int B, int G, int R);
void sysPrintFloat(float num, int B, int G, int R);
void sysGetTime(int *buffer);
void sysNewLine();
void sysReadInput(char *buffer);
void sysClear();
int countDigits(int num);
void sysPaintPixel(int x, int y, char R, char G, char B);
void sysWriteChar(char ch, unsigned char color_blue, unsigned char color_green, unsigned char color_red);
void sysGetChar(char *ch);
void copy(char *copy, char *original, int len);
int subStrleng(const char *s, const char c);
uint64_t sysMalloc(uint64_t bytes);
void sysFree(uint64_t address);
int sysExec(void* function,int argc, char** argv,char*name);
void sysEndProcess();
int sysPpid();
void sysSetForeground(int pid);
uint64_t sysGetPage();
void sysExitShell();

void sysMutexUp(uint64_t mut);
void sysMutexDown(uint64_t mut);
uint64_t sysMutexInit(char* name);
uint64_t sysMutexClose(uint64_t mut);

void checkIsNotNull(void* value);
void checkIsNull(void* value);
void checkAreEqual(uint64_t value1, uint64_t value2);
void checkAreNotEqual(uint64_t value1, uint64_t value2);
void checkIsNotZero(int value);
void checkIsNotMinusOne(int value);
void checkSizeOfSemaphoreList(int mysize, int size);
void ok();
void fail();
int rand();

int sysSemOpen(char* name);
int sysSemClose(int id);
int sysSemWait(int id);
int sysSemPost(int id);
int sysSemaphoresListSize();
void sysFreeSemaphoresList();

int sysCreateMessage(uint64_t name, uint64_t messageSize);
int sysOpenMessage(uint64_t name, uint64_t arg2);
int sysReadMessage(uint64_t buffer, uint64_t id);
int sysWriteMessage(uint64_t content, uint64_t id);
int closeMessage(uint64_t arg1, uint64_t id);
void sysPrintPIDS();

#endif
