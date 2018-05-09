#include "processes.h"
#include "interrupts.h"
#include "videoDriver.h"
#include "time.h"
#include "keyboardDriver.h"
#include "memorymanager.h"
#include "mutex.h"
#include "semaphore.h"
#include "scheduler.h"
#include "processes.h"

#define ERROR 1
#define SUCCESS 0

uint64_t mallocMemory(uint64_t size)
{
  void *page = (void *)malloc(size);
  add_data_page(get_current_process(), page);
  //add Process to scheduler
  return (uint64_t)page;
}

void freeMemory(uint64_t page)
{
  //remove process from scheduler
  free((void *)page);
}
  
uint64_t sysCallHandler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
  switch (rdi)
  {
  case 1:
    getTimeRTC(rsi);
    return SUCCESS;
  case 2:
    getChar((char *)rsi);
    return SUCCESS;
  case 3:
    clearScreen();
    return SUCCESS;
  case 4:
    writeChar((char)rsi, rdx, rcx, r8);
    return SUCCESS;
  case 5:
    paintPixel(rsi, rdx, (char)rcx, (char)r8, (char)r9);
    return SUCCESS;
  case 6:
    return mallocMemory(rsi);
  case 7:
    freeMemory(rsi);
    return SUCCESS;
  case 8:
    mutex_unlock((mutex_t*)rsi);
    break;
  case 9:
    mutex_lock((mutex_t*)rsi);
    break;
  case 10:
    return (uint64_t)mutex_init((char*)rsi);
    break;
  case 11:
    return (uint64_t)mutex_close((mutex_t*)rsi);
    break;
  case 12:
    return sem_open((char*)rsi);    
  case 13:
    return sem_close((int)rsi);    
  case 14:
    return sem_wait((int)rsi);    
  case 15:
    return sem_post((int)rsi);
  case 16:
    return semaphoresListSize();
  case 17:
    freeSemaphoresList();
    return SUCCESS;
  case 18:
    exec_process(createProcess(rsi, rdx, (char *) rcx));
  }
  return ERROR;
}
