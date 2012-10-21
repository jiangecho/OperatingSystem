#ifndef SCHED_H_
#define SCHED_H_

#define NR_TASKS 64
#define NULL (void *) 0

#define HZ 100
#define LATCH (1193180/HZ)

struct task_struct {
	int sched_priority;
	int sched_ss_low_priority;
	struct timespec sched_ss_repl_period;
	struct timespec sched_ss_init_budget;
	int sched_ss_max_repl;
};
typedef struct task_struct task_t;
#define SCHED_OTHER		0
#define SCHED_FIFO		1
#define SCHED_RR		2
#define SCHED_SPORADIC  3

int    sched_get_priority_max(int);
int    sched_get_priority_min(int);
int    sched_getparam(pid_t, struct sched_param *);
int    sched_getscheduler(pid_t);
int    sched_rr_get_interval(pid_t, struct timespec *);
int    sched_setparam(pid_t, const struct sched_param *);
int    sched_setscheduler(pid_t, int, const struct sched_param *);
int    sched_yield(void);

#define INIT_LDT {0, 0xc0fa000000009f, 0xc0f2000000009f}

#define INIT_TASK \
{ \
}

#define TSS_ENTRY 3
#define LDT_ENTRY (TSS_ENTRY+1)
#define TSS_SEL (TSS_ENTRY<<3)
#define LDT_SEL (LDT_ENTRY<<3)

#endif
