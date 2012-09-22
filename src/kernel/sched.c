#include "asm/io.h"
#include "asm/system.h"
#include "asm/head.h"
#include "ksched.h"
#include "video.h"

extern void timer_interrupt();

struct Task init_task = INIT_TASK;
struct Task *current = &init_task;
struct Task *task[NR_TASKS] = { &init_task, };
struct TSS tss = INIT_TSS;
struct {
	long a, b;
} ldt[3] = INIT_LDT;

void scheduleInit() {
	for (int i = 1; i < NR_TASKS; i++) {
		task[i] = NULL;
	}

	setupTSS(tss);
	setupLDT(ldt);
	__asm__("pushfl ; andl $0xffffbfff,(%esp) ; popfl"); // clear nt
	__asm__("ltr %%ax"::"a" (TSS_SEL)); // load tss
	__asm__("lldt %%ax"::"a" (LDT_SEL)); // load ldt

	outb(0x36, 0x43);
	outb(LATCH & 0xff, 0x40);
	outb(LATCH >> 8, 0x40);

	setIntrGate(0x20, &timer_interrupt);
	outb(inb(0x21)&~0x01, 0x21); // unmask timer interrupt
}

void doTimer() {
	// using software-switching
	__asm__("movl %%esp, !!prev.esp\n\t"
			"movl !!next.esp, %%esp\n\t"
			"movl $1f, !!prev.eip\n\t"
			"pushl !!next.eip\n\t"
			"ret\n\t"
			"1:\n\t"
	:"=a"(prev->esp), "=a"(prev->eip)
	 :"a"(next->esp),  "a"(next->eip));
}
