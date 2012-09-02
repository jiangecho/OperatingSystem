#include "asm/io.h"
#include "interrupt.h"

extern void mouseASMHandler();

#define MOUSE_INTERRUPT_NUMBER 0x2c
#define MOUSE_INTERRUPT_IRQ_NUMBER 12

void enableMouse() {
	outb(0x64, 0xa8);
	outb(0x64, 0xd4);
	outb(0x60, 0xf4);
	outb(0x64, 0x60);
	outb(0x60, 0x47);
}

void initMouse() {
	enableMouse();
	setInterruptHandler(MOUSE_INTERRUPT_NUMBER, mouseASMHandler);
	setInterruptMaskWord(MOUSE_INTERRUPT_IRQ_NUMBER, 1);
}

void mouseHandler() {
	// Some error has happened.
	// I will using keyboard to simulate mouse.
	inb(0x60);
}
