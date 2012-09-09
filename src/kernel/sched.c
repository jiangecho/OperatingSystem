#include "asm/io.h"
#include "asm/system.h"
#include "asm/head.h"
#include "ksched.h"
#include "video.h"

#define TIMER_IRQ 0
#define LATCH (1193180/100)

extern void timer_interrupt();
unsigned short white = 0;
unsigned short black = 0;

struct Task task0 = INIT_TASK;

void scheduleInit() {
	white = rgb(255, 255, 255);

	setTSSDesc(gdt+FIRST_TSS_ENTRY, &(task0.tss));
	setLDTDesc(gdt+FIRST_LDT_ENTRY, &(task0.ldt));
	__asm__("pushfl ; andl $0xffffbfff,(%esp) ; popfl");
	ltr(0);
	lldt(0);

	/*outb(0x43, 0x36);
	 outb(0x40, LATCH & 0xff);
	 outb(0x40, LATCH >> 8);*/

	outb(0x36, 0x43);
	outb(LATCH & 0xff, 0x40);
	outb(LATCH >> 8, 0x40);

	setIntrGate(0x20, &timer_interrupt);
	outb(inb(0x21)&~0x01, 0x21); // unmask timer interrupt
}

void doTimer() {
	static int i = 0;
	if (i) {
		fillRect(0, 0, 20, 20, black);
		i = 0;
	} else {
		fillRect(0, 0, 20, 20, white);
		i = 1;
	}
}
