#ifndef PROCESSES_H
#define PROCESSES_H

#include <stdint.h>

#include "defs.h"
#include "mutex.h"

#define RUNNING 0
#define READY 1
#define BLOCKED 2
#define BLOCKED_READ 3
#define DELETE 4
#define BLOCKED_FOREGROUND 5

#define MAX_FDS 64
#define MAX_DATA_PAGES 64
#define MAX_PROCESS_NAME 64

typedef struct
{
  char status;
  char name[MAX_PROCESS_NAME];
  uint64_t rsp;
  uint64_t stackPage;
  uint64_t dataPageCount;
  void *dataPage[MAX_DATA_PAGES];
  uint64_t pid;
  uint64_t ppid;
} process;

//typedef struct c_process process;
typedef char status;

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

void initialize_process_mutex();

process *createProcess(uint64_t rip, uint64_t argc, uint64_t argv, const char *name);
void removeProcess(process *p);

void setProcessRsp(process *p, uint64_t rsp);
uint64_t getProcessRsp(process *p);

void blockProcess(process *p);
void unblockProcess(process *p);
int isProcessBlocked(process *p);
void unblockReadProcess(process *p);
void blockReadProcess(process *p);
void blockProcessForeground(process *p); /* Se desbloquea al hacer set_foreground */
uint64_t getProcessPid(process *p);
uint64_t getProcessPpid(process *p);
uint64_t getProcessesNumber();
mutexADT getTableMutexSingleton();
void lockTable();
void unlockTable();
uint64_t getProcessesNumber();
int insertProcess(process *p);
void setNullAllProcessPages(process *process);
uint64_t createNewProcessStack(uint64_t rip, uint64_t stackPage, uint64_t argc, uint64_t argv);
void exitShell();
process *getProcessByPid(uint64_t pid);

/* Quizas no tengan que estar aca */
void setProcessForeground(process *p);
void setProcessForegroundForce(process *p);
process *getProcessForeground();

/* kill settea que hay que borrar el proceso. No lo borra. is_delete devuelve 1 si hay que borrarlo. */
int deleteProcess(process *p);
int isProcessDeleted(process *p);

/* Archivos del proceso */
int set_file_open(process *p, int fd);
int set_file_closed(process *p, int fd);
int file_is_open(process *p, int fd);

/* Paginas de datos que devuelve el memory allocator */
void addDataPage(process *p, void *page);
void remove_data_page(process *p, void *page);

void *stack_page_process(process *p);
void data_pages_process(process *p, void *page_array[]);

int get_name_process(char *buffer, process *p);

/* Devuelve los pids actuales. Termina el arreglo con -1 */
int get_current_pids(int pid_array[]);

void printPIDS();

#endif
