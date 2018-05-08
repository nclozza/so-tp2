#include "./include/defs.h"
#include "./include/lib.h"
#include "./include/processes.h"
#include "./include/pageallocator.h"
#include "./include/mutex.h"
#include "./include/memorymanager.h"

/* El stack newStackFrame y el llenado del mismo se tomó de
** https://bitbucket.org/RowDaBoat/wyrm
*/
typedef struct
{
  // Registers restore context
  uint64_t gs;
  uint64_t fs;
  uint64_t r15;
  uint64_t r14;
  uint64_t r13;
  uint64_t r12;
  uint64_t r11;
  uint64_t r10;
  uint64_t r9;
  uint64_t r8;
  uint64_t rsi;
  uint64_t rdi;
  uint64_t rbp;
  uint64_t rdx;
  uint64_t rcx;
  uint64_t rbx;
  uint64_t rax;

  // iretq hook
  uint64_t rip;
  uint64_t cs;
  uint64_t eflags;
  uint64_t rsp;
  uint64_t ss;
  uint64_t base;
} stackFrame;

struct process
{
  char status;
  char name[MAX_PROCESS_NAME];
  uint64_t instructionPointer;
  uint64_t rsp;
  uint64_t stackPage;
  uint64_t dataPageCount;
  void *dataPage[MAX_DATA_PAGES];
  uint64_t pid;
  uint64_t ppid;
  uint64_t open_fds; /* bit map */
};

static mutexADT getTableMutexSingleton();
static void lockTable();
static void unlockTable();
static uint64_t pid_process(process * p);
static int insertProcess(process *p);
process *createProcess(uint64_t newProcessRIP, uint64_t params, const char *name);
static void setNullAllProcessPages(process *process);
static uint64_t createNewProcessStack(uint64_t rip, uint64_t stackPage, uint64_t params);

static process *processesTable[MAX_PROCESSES] = {NULL};
static process *foreground = NULL;

static uint64_t processesNumber = 0;
static mutexADT mutexTable = NULL;

static mutexADT getTableMutexSingleton()
{
  if (mutexTable == NULL)
  {
    mutexTable = mutex_init("mutexTable");
  }

  return mutexTable;
}

static void lockTable()
{
  mutex_lock(getTableMutexSingleton());
}

static void unlockTable()
{
  mutex_unlock(getTableMutexSingleton());
}

static uint64_t pid_process(process * p)
{
	if (p != NULL)
		return p->pid;
	return -1;
}

static int insertProcess(process *p)
{
  int i;

  lockTable();

  for (i = 0; i < MAX_PROCESSES; i++)
  {
    if (processesTable[i] == NULL)
    {
      processesNumber++;
      p->pid = i;
      processesTable[i] = p;
      unlockTable();
      return i;
    }
  }

  unlockTable();

  return -1;
}

process *createProcess(uint64_t newProcessRIP, uint64_t params, const char *name)
{
  uint64_t newstackPage = getStackPage();

  process *newProcess = (process *)malloc(sizeof(*newProcess));

  strcpyKernel(newProcess->name, name);

                                        /* DUDA EXISTENCIAL */
  newProcess->stackPage = newstackPage + sizeof(stackFrame); /* Pide al MemoryAllocator espacio para el stack */

  newProcess->instructionPointer = newProcessRIP;

  newProcess->status = READY;

  newProcess->rsp = createNewProcessStack(newProcessRIP, newstackPage, params);

  setNullAllProcessPages(newProcess);

  /* Agerga proceso a la tabla de procesos. Adentro usa un lock. */
  insertProcess(newProcess);

  /* No es el primer proceso */
  if (newProcess->pid != 0)
  {
    newProcess->ppid = pid_process(get_current_process());
  }
  else
  {
    /* Pone en foreground al primer proceso */
    /* Como vamos a manejar esto????  */
    // foreground = newProcess;
  }

  newProcess->open_fds = 0;

  return newProcess;
}

static void setNullAllProcessPages(process *process)
{
  int i;

  for (i = 0; i < MAX_DATA_PAGES; i++)
  {
    process->dataPage[i] = NULL;
  }

  process->dataPageCount = 0;
}

/* Llena el stack para que sea hookeado al cargar un nuevo proceso
** https://bitbucket.org/RowDaBoat/wyrm */

static uint64_t createNewProcessStack(uint64_t rip, uint64_t stackPage, uint64_t params)
{
  stackFrame *newStackFrame = (stackFrame *)stackPage;

  newStackFrame->gs = 0x001;
  newStackFrame->fs = 0x002;
  newStackFrame->r15 = 0x003;
  newStackFrame->r14 = 0x004;
  newStackFrame->r13 = 0x005;
  newStackFrame->r12 = 0x006;
  newStackFrame->r11 = 0x007;
  newStackFrame->r10 = 0x008;
  newStackFrame->r9 = 0x009;
  newStackFrame->r8 = 0x00A;
  newStackFrame->rsi = 0x00B;
  newStackFrame->rdi = params;
  newStackFrame->rbp = 0x00D;
  newStackFrame->rdx = 0x00E;
  newStackFrame->rcx = 0x00F;
  newStackFrame->rbx = 0x010;
  newStackFrame->rax = 0x011;
  newStackFrame->rip = rip;
  newStackFrame->cs = 0x008;
  newStackFrame->eflags = 0x202;
  newStackFrame->rsp = (uint64_t) & (newStackFrame->base);
  newStackFrame->ss = 0x000;
  newStackFrame->base = 0x000;

  return (uint64_t)&newStackFrame->gs;
}
