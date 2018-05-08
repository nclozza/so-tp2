#include <stdint.h>
#include "shell.h"
#include "stdLib.h"
#include "stdio.h"
#include "plotLib.h"
#include "mathLib.h"
#include "prodcons.h"


uint64_t buffer_mutex = 0;
static int items = 0;
int fullSem = 0;
int emptySem = 0;


void putItemIntoBuffer()
{
  items++;
  sysPrintString("Added an item\n",0,155,255);
  sysPrintString("Total items: \n", 0,155,255);
  sysPrintInt(items,0,155,255);
}

void removeItemFromBuffer()
{
  items--;
  sysPrintString("Removed an item\n",0,155,255);
  sysPrintString("Total items: \n", 0,155,255);
  sysPrintInt(items,0,155,255);
}


void producer() 
{
    sysSemWait(fullSem);
    sysMutexDown(buffer_mutex);

    if(items < BUFFER_SIZE)
     	putItemIntoBuffer();
    else
       	sysPrintString("Can't add anymore items, buffer is full\n",0,155,255);

    sysMutexUp(buffer_mutex);
    sysSemPost(emptySem);
    
}

void consumer() 
{
    sysSemWait(emptySem);
    sysMutexDown(buffer_mutex);

    removeItemFromBuffer();
    if(items != 0)
       	removeItemFromBuffer();
    else
      	sysPrintString("Can't remove anymore items, buffer is empty\n",0,155,255);
    
    sysMutexUp(buffer_mutex);
    sysSemPost(emptySem);    
}

void runProdCons()
{
  buffer_mutex = sysMutexInit("buffer_mutex");
  fullSem = sysSemOpen("fullSem");
  emptySem = sysSemOpen("emptySem");

  for(int i = 0; i < BUFFER_SIZE; i++)
  {
    sysSemPost(fullSem);
  }

  sysMutexClose(buffer_mutex);
  sysSemClose(fullSem);
  sysSemClose(emptySem);

}