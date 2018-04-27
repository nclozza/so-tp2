#ifndef PAGEALLOCATOR_H_
#define PAGEALLOCATOR_H_

void initializePageAllocator();
uint64_t getAvailablePage();
void releasePage(uint64_t page);
uint64_t peekAvailablePage();
int getIndexInStack();

#endif