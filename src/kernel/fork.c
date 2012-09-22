#include "ksched.h"
#include "asm/system.h"
#include "asm/head.h"

extern struct Task *current;
extern struct Task *task[NR_TASKS];

int fork() {
	int pid=0;
	return pid;
}
