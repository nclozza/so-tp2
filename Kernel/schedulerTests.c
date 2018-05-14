#include "scheduler.h"
#include "processes.h"
#include "testlib.h"
#include "videoDriver.h"

process* testProcess = NULL;
char* processName;
int newProcessRIP;
int argc;
int argv;
int testAux;
int testPid;

void givenAProcess();
void whenProcessIsCreated();
void thenProcessIsNotNull();
void givenACreatedProcess();
void whenProcessIsRemoved();
void thenProcessIsNull();
void whenProcessIsBlocked();
void thenProcesStatusIsBlocked();
void givenABlockedProcess();
void whenAProcessIsUnblocked();
void thenProcessStatusIsReady();
//void whenProcessIsRunning();
//void thenPidIsNotZero();
//void givenARunningProcess();
//void whenProcessIsKilled();
//void thenPrintOk();

void testCreateProcess()
{
    givenAProcess();
    whenProcessIsCreated();
    thenProcessIsNotNull();
}

void testRemoveProcess()
{
    givenACreatedProcess();
    whenProcessIsRemoved();
    thenProcessIsNull();
}

void testBlockProcess()
{
    givenACreatedProcess();
    whenProcessIsBlocked();
    thenProcesStatusIsBlocked();
}
/*
void testRunProcess()
{
    givenACreatedProcess();
    whenProcessIsRunning();
    thenPidIsNotZero();
}

void testKillProcess()
{
    givenARunningProcess();
    whenProcessIsKilled();
    thenPrintOk();
}
*/
void testUnblockProcess()
{
    givenABlockedProcess();
    whenAProcessIsUnblocked();
    thenProcessStatusIsReady();
}


void givenAProcess()
{
    processName = "processTesting";
    newProcessRIP = 10;
    argc = 0;
    argv = 0;
}

void whenProcessIsCreated()
{
    testProcess = createProcess((uint64_t) newProcessRIP, (uint64_t) argc, (uint64_t) argv, processName);
}

void thenProcessIsNotNull()
{
    checkIsNotNull((void*)testProcess);
}

void givenACreatedProcess()
{
    if (testProcess == NULL)
    {
        givenAProcess();
        whenProcessIsCreated();
    }        
}

void whenProcessIsRemoved()
{
    deleteProcess(testProcess);
    removeProcess(testProcess);
    testAux = isProcessDeleted(testProcess);
}

void thenProcessIsNull()
{
    checkIsZero(testAux);
}

void whenProcessIsBlocked()
{
    blockProcess(testProcess);
}

void thenProcesStatusIsBlocked()
{
    if (testProcess->status == BLOCKED)
    {
        testAux = 0;
        checkIsZero(testAux);
    }
    else
    {
        testAux = 1;
        checkIsZero(testAux);
    }
}

void givenABlockedProcess()
{
    if (testProcess->status != BLOCKED)
    {
        givenACreatedProcess();
        whenProcessIsBlocked();
    }
}


void whenAProcessIsUnblocked()
{
    unblockProcess(testProcess);
}

void thenProcessStatusIsReady()
{
    if (testProcess->status == READY)
    {
        testAux = 0;
        checkIsZero(testAux);
    }
    else
    {
        testAux = 1;
        checkIsZero(testAux);
    }
}

void whenProcessIsRunning()
{
    testPid =(int) runProcess(testProcess);
}

void thenPidIsNotZero()
{
    checkIsNotZero(testPid);
}



void runSchedulerTests()
{
    printString("Testing Process is created...\n", 128, 128, 128);
    testCreateProcess();

    printString("Testing Process is blocked...\n", 128, 128, 128);    
    testBlockProcess();
    
    printString("Testing Process is unblocked...\n", 128, 128, 128);    
    testUnblockProcess();
/*   
    printString("Testing Process is running...\n", 128, 128, 128);    
    testRunProcess();
*/
    printString("Testing Process is removed...\n", 128, 128, 128);
    testRemoveProcess();

}