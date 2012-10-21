#include "asm/io.h"
/*#include "asm/system.h"
#include "asm/head.h"
#include "kernel/tss.h"
#include "sched.h"
#include "unistd.h"

typedef long long ldt_t;

extern void timer_interrupt();
extern void sys_call_int80();

task_t initTask = INIT_TASK;
task_t *next;
task_t *current = &initTask;
tss_t tss = INIT_TSS;
ldt_t ldt[3] = INIT_LDT;

#define switch_to() \
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

void __switch_to() {
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

void sched_init() {
	setup_tss(&tss);
	setup_ldt(&ldt);
	__asm__("pushfl ; andl $0xffffbfff,(%esp) ; popfl"); // clear nt
	__asm__("ltr %%ax"::"a" (TSS_SEL)); // load tss
	__asm__("lldt %%ax"::"a" (LDT_SEL)); // load ldt

	outb(0x36, 0x43); // setup 8253 chip
	outb(LATCH & 0xff, 0x40);
	outb(LATCH >> 8, 0x40);
	set_intr_gate(0x20, &timer_interrupt);
	set_system_gate(0x80, &sys_call_int80);
	outb(inb(0x21)&~0x01, 0x21); // unmask timer interrupt
}

void do_timer() {
}
*/
