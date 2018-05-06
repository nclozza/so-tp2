#ifndef MEMORYMANAGER_H_
#define MEMORYMANAGER_H_

#include <stdint.h>

uint64_t malloc(uint64_t size);
void free(void* page);

#endif