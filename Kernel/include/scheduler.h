#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "processes.h"

static void add_process(process * p);
unsigned long int exec_process(process * new_process);

#endif
