#include "asm/io.h"
#include "asm/system.h"
#include "asm/head.h"
#include "ksched.h"
#include "video.h"
#include "sys_call.h"

extern void timer_interrupt();
extern void system_call();

struct Task initTask = INIT_TASK;
struct Task *current = &initTask;
struct Task *task[NR_TASKS] = {&initTask,};

struct TSS tss = INIT_TSS;
long long ldt[3] = INIT_LDT;

void scheduleInit() {
	/*for (int i = 1; i < NR_TASKS; i++) {
		task[i] = NULL;
	}*/
	setupTSS(&tss);
	setupLDT(&ldt);
	__asm__("pushfl ; andl $0xffffbfff,(%esp) ; popfl"); // clear nt
	__asm__("ltr %%ax"::"a" (TSS_SEL)); // load tss
	__asm__("lldt %%ax"::"a" (LDT_SEL)); // load ldt

	outb(0x36, 0x43); // setup 8253 chip
	outb(LATCH & 0xff, 0x40);
	outb(LATCH >> 8, 0x40);

	setIntrGate(0x20, &timer_interrupt);
	setSystemGate(0x80, &system_call);
	outb(inb(0x21)&~0x01, 0x21); // unmask timer interrupt
}

void doTimer() {
	/*if (--current->counter > 0) return;
	schedule();*/
	static int i = 0;
	if (i) {
		drawString((48 << 16), "timer1", 0);
		i=0;
	} else {
		drawString((48 << 16), "timer1", RGB(255,255,255));
		i=1;
	}
}

/*void schedule() {
	struct Task *next;
	// * get next
select_task:
	// * context switch: load all registers
	// * execute next
	tss.esp0 = 0; // set kernel stack
	__asm__("movl %%esp, %0\n\t"
			"movl %2, %%esp\n\t"
			"movl $1f, %1\n\t"
			"pushl %3\n\t"
			"ret\n\t"
			"1:\n\t"
	:"=m"(prev->esp), "=m"(prev->eip)
	 :"m"(next->esp),  "m"(next->eip));
}*/
