#include "./include/memorymanager.h"
//#include "scheduler.h"
//#include "dirs.h"
#include "./include/videoDriver.h"
#include "./include/mutex.h"
#include "./include/processes.h"
#include "defs.h"
//#include "interrupts.h"

#define QUANTUM 1

static void add_process(process * p);
uint64_t exec_process(process * new_process);

typedef struct c_node {
	int quantum;
	process *p;
	struct c_node *next;
} list_node;

static list_node *current = NULL;
static list_node *prev = NULL;

uint64_t exec_process(process * new_process) {
	int pid;

	add_process(new_process);

	pid = pid_process(new_process);

  /*
	if (pid == 0)
		_change_process(get_rsp_process(current->p));
  */

	return pid;
}

static void add_process(process * p) {

	list_node *new_node = (list_node *) malloc(sizeof(*new_node));

	new_node->p = p;
	new_node->quantum = QUANTUM;

	//set_superlock();

	if (current == NULL) {
		current = new_node;
		current->next = current;
		prev = current;
	}
	else {
		new_node->next = current->next;
		current->next = new_node;
	}

	//unset_superlock();
}