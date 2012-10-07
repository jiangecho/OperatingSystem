#include "asm/io.h"
#include "asm/system.h"
#include "asm/head.h"
#include "ksched.h"
#include "video.h"
#include "sys_call.h"

extern void timer_interrupt();
extern void sys_call_int80();

struct Task initTask = INIT_TASK;
struct Task testTask = INIT_TASK;
struct Task *next;
struct Task *current = &initTask;

struct TSS tss = INIT_TSS;
long long ldt[3] = INIT_LDT;

#define switchTo() \
	__asm__ __volatile__ ( \
			"pushl %%esi\n\t" \
			"pushl %%edi\n\t" \
			"pushl %%ebp\n\t" \
			"movl %%esp, %0\n\t" \
			"movl %2, %%esp\n\t" \
			"movl $1f, %1\n\t" \
			"pushl %3\n\t" \
			"jmp __switchTo\n\t" \
			"1:\n\t" \
			"popl %%ebp\n\t" \
			"popl %%edi\n\t" \
			"popl %%esi\n\t" \
		:"=m"(current->esp), "=m"(current->eip) \
		 :"m"(next->esp),     "m"(next->eip));

void __switchTo() {
	__asm__ __volatile__ (
			"movl %%eax, %0\n\t"
			"movl %%ebx, %1\n\t"
			"movl %%ecx, %2\n\t"
			"movl %%edx, %3\n\t"
			"movl %4, %%eax\n\t"
			"movl %5, %%ebx\n\t"
			"movl %6, %%ecx\n\t"
			"movl %7, %%edx\n\t"
			:"=m"(current->eax), "=m"(current->ebx),
			 "=m"(current->ecx), "=m"(current->edx)
			 :"m"(next->eax),     "m"(next->ebx),
			  "m"(next->ecx),     "m"(next->edx));
	current = next;
}

void testT() {
	while (1) {
		drawString(200 | (120 << 16), "test", RGB(255,0,0));
		drawString(200 | (120 << 16), "test", RGB(255,255,0));
	}
}

void scheduleInit() {
	setupTSS(&tss);
	setupLDT(&ldt);
	__asm__("pushfl ; andl $0xffffbfff,(%esp) ; popfl"); // clear nt
	__asm__("ltr %%ax"::"a" (TSS_SEL)); // load tss
	__asm__("lldt %%ax"::"a" (LDT_SEL)); // load ldt

	testTask.cs = 0x0f;
	testTask.ds = 0x17;
	testTask.fs = 0x17;
	testTask.gs = 0x17;
	testTask.ss = 0x17;
	testTask.es = 0x17;
	testTask.esp = 0x6ffff;
	testTask.eip = (long) &testT;
	testTask.esp0 = (long) &test_task_stack_tail;

	outb(0x36, 0x43); // setup 8253 chip
	outb(LATCH & 0xff, 0x40);
	outb(LATCH >> 8, 0x40);
	setIntrGate(0x20, &timer_interrupt);
	setSystemGate(0x80, &sys_call_int80);
	outb(inb(0x21)&~0x01, 0x21); // unmask timer interrupt
}

void doTimer() {
	static int i = 0;
	if (i) {
		i=0;
		next = &initTask;
		switchTo();
	} else {
		i=1;
		next = &testTask;
		switchTo();
	}
}

void schedule() {
}
