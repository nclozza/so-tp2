#ifndef PROCESSES_H
#define PROCESSES_H

#define MAX_PROCESS_NAME 64
#define MAX_DATA_PAGES 64
#define MAX_PROCESSES 128

enum PROCESS_STATES {RUNNING, READY};

typedef struct process process;

static mutexADT getTableMutexSingleton();
static void lockTable();
static void unlockTable();
static uint64_t pid_process(process * p);
static int insertProcess(process *p);
process *createProcess(uint64_t newProcessRIP, uint64_t params, const char *name);
static void setNullAllProcessPages(process *process);
static uint64_t createNewProcessStack(uint64_t rip, uint64_t stackPage, uint64_t params);

#endif
