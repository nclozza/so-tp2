#include "processes.h"
#include "defs.h"
#include "lib.h"
#include "pageallocator.h"
#include "mutex.h"
#include "memorymanager.h"
#include "scheduler.h"

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

static void unblock_foreground_process(process *p);
static void free_data_pages(process *p);

static process *processesTable[MAX_PROCESSES] = {NULL};
static process *foreground = NULL;

static uint64_t processesNumber = 0;

int insertProcess(process *p)
{
  int i;

  for (i = 0; i < MAX_PROCESSES; i++)
  {
    if (processesTable[i] == NULL)
    {
      processesNumber++;
      p->pid = i;
      processesTable[i] = p;
      return i;
    }
  }

  return -1;
}

process *createProcess(uint64_t newProcessRIP, uint64_t argc, uint64_t argv, const char *name)
{
  process *newProcess = (process *)malloc(sizeof(*newProcess));

  strcpyKernel(newProcess->name, name);

  newProcess->stackPage = getStackPage(); /* Pide al MemoryAllocator espacio para el stack */
  
  newProcess->status = READY;

  newProcess->rsp = createNewProcessStack(newProcessRIP, newProcess->stackPage, argc,argv);
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
    foreground = newProcess;
    newProcess->ppid = 0;
  }

  // printString("PID: ", 0, 155, 255);
  // printInt(newProcess->pid, 0, 155, 255);
  // printString("\nPPID: ", 0, 155, 255);
  // printInt(newProcess->ppid, 0, 155, 255);
  // printString("\n", 0, 155, 255);

  return newProcess;
}

process *get_process_by_pid(uint64_t pid)
{
  if (pid < MAX_PROCESSES && processesTable[pid] != NULL && !is_delete_process(processesTable[pid])){
    return processesTable[pid];
  }

  return NULL;
}

void setNullAllProcessPages(process *process)
{
  int i;

  for (i = 0; i < MAX_DATA_PAGES; i++)
  {
    process->dataPage[i] = NULL;
  }

  process->dataPageCount = 0;
}

void destroy_process(process *p)
{
  if (p != NULL)
  {
    processesNumber--;
    free_data_pages(p);
    if (foreground == p)
      set_foreground_process(processesTable[p->ppid]);
    processesTable[p->pid] = NULL;
    free((void *)p->stackPage);
    free((void *)p);
  }
}

/* Libera las páginas de datos usadas por el proceso. */
static void free_data_pages(process *p)
{
  int i;

  for (i = 0; i < MAX_DATA_PAGES && p->dataPageCount > 0; i++)
  {
    if (p->dataPage[i] != NULL)
    {
      free((void *)p->dataPage[i]);
      p->dataPageCount -= 1;
    }
  }
}

void add_data_page(process *p, void *page)
{
  int i = 0;

  while (i < MAX_DATA_PAGES && p->dataPage[i] != NULL)
    i++;

  if (i < MAX_DATA_PAGES)
  {
    p->dataPageCount += 1;
    p->dataPage[i] = page;
  }
}

int kill_process(process *p)
{
  if (p != NULL && p->pid != 1 && p->pid != 0)
    p->status = DELETE;

  return p != NULL;
}

int is_delete_process(process *p)
{
  if (p != NULL)
    return p->status == DELETE;
  return 0;
}

void set_rsp_process(process *p, uint64_t rsp)
{
  if (p != NULL)
    p->rsp = rsp;
}

uint64_t get_rsp_process(process *p)
{
  //printString("GET_RSP\n", 0, 155, 255);
  //printHex(p);
  if (p != NULL)
    return p->rsp;
  return -1;
}

uint64_t pid_process(process *p)
{
  if (p != NULL)
    return p->pid;
  return -1;
}

uint64_t ppid_process(process *p)
{
  if (p != NULL)
    return p->ppid;
  return -1;
}

void block_process(process *p)
{
  if (p != NULL && p->status != DELETE)
    p->status = BLOCKED;
}

void unblock_process(process *p)
{
  if (p != NULL && p->status != DELETE)
    p->status = READY;
}

int is_blocked_process(process *p)
{
  if (p != NULL)
    return p->status == BLOCKED || p->status == BLOCKED_READ || p->status == BLOCKED_FOREGROUND;
  return 1;
}

void unblock_read_process(process *p)
{
  if (p->status == BLOCKED_READ)
    unblock_process(p);
}

void block_read_process(process *p)
{
  p->status = BLOCKED_READ;
}

void set_foreground_process(process *p)
{
  if (foreground == get_current_process())
    set_foreground_force_process(p);
}

void set_foreground_force_process(process *p)
{
  if (p != NULL && p->pid != 0)
  {
    foreground = p;
    unblock_foreground_process(p);
  }
}

static void unblock_foreground_process(process *p)
{
  if (p != NULL && p->status == BLOCKED_FOREGROUND)
    p->status = READY;
}

void block_foreground_process(process *p)
{
  if (p != NULL)
    p->status = BLOCKED_FOREGROUND;
}

process *get_foreground_process()
{
  return foreground;
}

uint64_t number_processes()
{
  return processesNumber;
}

/* Llena el stack para que sea hookeado al cargar un nuevo proceso
** https://bitbucket.org/RowDaBoat/wyrm */

uint64_t createNewProcessStack(uint64_t rip, uint64_t stackPage, uint64_t argc, uint64_t argv)
{
  stackFrame *newStackFrame = (stackFrame *)stackPage - 1;

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
  newStackFrame->rsi = argv;
  newStackFrame->rdi = argc;
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
