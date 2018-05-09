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
  sysPrintString("Total items: ", 0,155,255);
  sysPrintInt(items,0,155,255);
  sysPrintString("\n", 0,155,255);
}

void removeItemFromBuffer()
{
  items--;
  sysPrintString("Removed an item\n",0,155,255);
  sysPrintString("Total items: ", 0,155,255);
  sysPrintInt(items,0,155,255);
  sysPrintString("\n", 0,155,255);
}


void producer() 
{
    sysSemWait(fullSem);  //if buffer is full: wait; else: pass
    sysMutexDown(buffer_mutex);

    if(items < BUFFER_SIZE)
     	putItemIntoBuffer();
    else
       	sysPrintString("Can't add anymore items, buffer is full\n",0,155,255);  //should never get here because fullSem allowed it to pass

    sysMutexUp(buffer_mutex);
    sysSemPost(emptySem); //alert: there's an item to consume
}

void consumer() 
{
    sysSemWait(emptySem); //if buffer is empty: wait; else: pass
    sysMutexDown(buffer_mutex);

    if(items != 0)
       	removeItemFromBuffer();
    else
      	sysPrintString("Can't remove anymore items, buffer is empty\n",0,155,255); //should never get here because fullSem allowed it to pass
    
    sysMutexUp(buffer_mutex);
    sysSemPost(fullSem);  //alert: there's space for one item
}

void runProdCons()
{
  int iterations = 0;
  int random;

  buffer_mutex = sysMutexInit("buffer_mutex");
  fullSem = sysSemOpen("fullSem");
  emptySem = sysSemOpen("emptySem");

  for(int i = 0; i < BUFFER_SIZE; i++)
  {
    sysSemPost(fullSem);
  }

  while(iterations < MAX_ITERATIONS)
  {
    random = rand() % 2; //generates 0s and 1s randomly 
    
    if (random == 0)
    {
      producer();
    }
    else
    {
      consumer();
    }

    iterations++;
  }

  sysMutexClose(buffer_mutex);
  sysSemClose(fullSem);
  sysSemClose(emptySem);

}