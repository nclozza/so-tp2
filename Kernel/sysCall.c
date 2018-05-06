#include "interrupts.h"
#include "videoDriver.h"
#include "time.h"
#include "keyboardDriver.h"
#include "memorymanager.h"
uint64_t mallocMemory(uint64_t size)
{
  void *page = (void *)malloc(size);
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
    break;
  case 2:
    getChar((char *)rsi);
    break;
  case 3:
    clearScreen();
    break;
  case 4:
    writeChar((char)rsi, rdx, rcx, r8);
    break;
  case 5:
    paintPixel(rsi, rdx, (char)rcx, (char)r8, (char)r9);
    break;
  case 6:
    return mallocMemory(rsi);
    break;
  case 7:
    freeMemory(rsi);
    break;
  }
  return 0;
}
