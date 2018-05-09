#include "pageAllocatorTest.h"
#include "semaphoreTests.h"
#include "mutexTests.h"
#include "videoDriver.h"
#include "genericQueueTests.h"
#include "messageQueueTests.h"

void runTests()
{
    printString("Running tests...\n", 128, 128, 128);
    runPageAllocatorTests();
	runSemaphoreTests();
	runMutexTests();
    runGenericQueueTests();
    runMessageQueueTests();
    printString("Finished testing\n", 128, 128, 128);
}