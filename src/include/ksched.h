#ifndef SCHED_H_
#define SCHED_H_

#define NR_TASKS 64
#define NULL (void *) 0

#define HZ 100
#define LATCH (1193180/HZ)

struct TSS {
	long back_link; /* 16 high bits zero */
	long esp0;
	long ss0; /* 16 high bits zero */
	long esp1;
	long ss1; /* 16 high bits zero */
	long esp2;
	long ss2; /* 16 high bits zero */
	long cr3;
	long eip;
	long eflags;
	long eax, ecx, edx, ebx;
	long esp;
	long ebp;
	long esi;
	long edi;
	long es; /* 16 high bits zero */
	long cs; /* 16 high bits zero */
	long ss; /* 16 high bits zero */
	long ds; /* 16 high bits zero */
	long fs; /* 16 high bits zero */
	long gs; /* 16 high bits zero */
	long ldt; /* 16 high bits zero */
	long trace_bitmap; /* bits: trace 0, bitmap 16-31 */
};

struct TaskRegs {
	long esp;
	long eip;
	long eflags;
	long eax, ebx, ecx, edx;
	long ebp;
	long esi;
	long edi;
	long es, cs, ss, ds, fs, gs;
};

struct Task {
	int state;
	int counter;
	int goodness;
	struct TaskRegs reg;
};

#define INIT_TSS \
{ \
	0,(long) &init_task_stack_tail,0x10,0,0,0,0,0, \
	0,0,0,0,0,0,0,0, \
	0,0,0x17,0x17,0x17,0x17,0x17,0x17, \
	LDT_SEL,0x80000000, \
}

#define INIT_LDT {0, 0xc0fa000000009f, 0xc0f2000000009f}

#define INIT_TASK \
{ \
}

#define TSS_ENTRY 3
#define LDT_ENTRY (TSS_ENTRY+1)
#define TSS_SEL (TSS_ENTRY<<3)
#define LDT_SEL (LDT_ENTRY<<3)

#endif
