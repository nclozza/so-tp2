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

void initialize_process_mutex();

process *createProcess(uint64_t rip, uint64_t params, const char *name);
void destroy_process(process *p);

void set_rsp_process(process *p, uint64_t rsp);
uint64_t get_rsp_process(process *p);

void block_process(process *p);
void unblock_process(process *p);
int is_blocked_process(process *p);
void unblock_read_process(process *p);
void block_read_process(process *p);
void block_foreground_process(process *p); /* Se desbloquea al hacer set_foreground */
uint64_t pid_process(process *p);
uint64_t ppid_process(process *p);
uint64_t number_processes();
mutexADT getTableMutexSingleton();
void lockTable();
void unlockTable();
uint64_t number_processes();
int insertProcess(process *p);
process *createProcess(uint64_t newProcessRIP, uint64_t params, const char *name);
void setNullAllProcessPages(process *process);
uint64_t createNewProcessStack(uint64_t rip, uint64_t stackPage, uint64_t params);
void exitShell();

process *get_process_by_pid(uint64_t pid);

/* Quizas no tengan que estar aca */
void set_foreground_process(process *p);
void set_foreground_force_process(process *p);
process *get_foreground_process();

/* kill settea que hay que borrar el proceso. No lo borra. is_delete devuelve 1 si hay que borrarlo. */
int kill_process(process *p);
int is_delete_process(process *p);

/* Archivos del proceso */
int set_file_open(process *p, int fd);
int set_file_closed(process *p, int fd);
int file_is_open(process *p, int fd);

/* Paginas de datos que devuelve el memory allocator */
void add_data_page(process *p, void *page);
void remove_data_page(process *p, void *page);

void *stack_page_process(process *p);
void data_pages_process(process *p, void *page_array[]);

int get_name_process(char *buffer, process *p);

/* Devuelve los pids actuales. Termina el arreglo con -1 */
int get_current_pids(int pid_array[]);

void printPIDS();

#endif
