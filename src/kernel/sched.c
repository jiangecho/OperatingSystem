#include "kernel.h"
#include "asm/io.h"

#define TIMER_IRQ 8

ASM_FUNC void timerASMHandler();
void timerHandler();
unsigned short white = 0;
unsigned short black = 0;

void initSchedule() {
	white = rgb565(255, 255, 255);
	outb(0x70, 0x0B);
	char prev = inb(0x71);
	outb(0x70, 0x0B);
	outb(0x71, prev | 0x40);
	installInterruptHandler(8, timerASMHandler);
}

void timerHandler() {
	outb(0x70, 0x0C); // select register C
	inb(0x71); // just throw away contents.
	static int i = 0;
	if (i) {
		fillRect(0, 0, 20, 20, black);
		i = 0;
	} else {
		fillRect(0, 0, 20, 20, white);
		i = 1;
	}
}
