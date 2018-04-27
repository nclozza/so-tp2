#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "videoDriver.h"
//#include "pageallocator.h"

#define AVOID_BSS 1
#define KERNEL 0x0
#define KERNEL_HEAP 0x200000
#define KERNEL_STACK 0x400000
#define SYSTEM_RAM_ADDRESS 0x5020
#define MB 0x100000
#define PAGESIZE 0x1000
#define PAGEQTY 1024 

static uint64_t size = 1;
static uint64_t availablePage = 0;
static uint64_t pageStack[PAGEQTY];
static int indexInStack = 0;
extern uint8_t endOfKernel;

void initializePageAllocator()
{	
	uint64_t ram = *((uint64_t*)SYSTEM_RAM_ADDRESS);
	size = (ram * MB)/ PAGESIZE;	
	uint64_t reserved = (uint64_t)&endOfKernel / (PAGESIZE);
	availablePage = (reserved + 1);

}

uint64_t getAvailablePage()
{
	if(indexInStack != 0)
	{
		uint64_t page = pageStack[indexInStack];
		indexInStack--;
		return page;
	}
	else if( availablePage < size)
	{
		uint64_t page = availablePage * PAGESIZE;
		availablePage++;
		return page;
	}
	else
	{
		printString("OUT OF MEMORY\n",0, 155, 255);
		while(1);
	}
	
}
uint64_t peekAvailablePage()
{	
	if(indexInStack != 0)
	{
		uint64_t page = pageStack[indexInStack];		
		return page;
	}
	else if( availablePage < size)
	{
		uint64_t page = availablePage * PAGESIZE;		
		return page;
	}
	else
	{
		printString("OUT OF MEMORY\n",0, 155, 255);
		while(1);
	}
}
void releasePage(uint64_t page)
{	
	indexInStack++;	
	if(indexInStack < PAGEQTY)
	{		
		pageStack[indexInStack] = page;
	}
	else
	{
		printString("OUT OF PAGESTACK SPACE\n",0, 155, 255);
		while(1);
	}
}
int getIndexInStack()
{
	return indexInStack;
}