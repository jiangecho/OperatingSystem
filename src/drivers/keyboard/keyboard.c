#include "asm/io.h"
#include "interrupt.h"

extern void keyboardASMHandler();

#define KEYBOARD_INTERRUPT_IRQ_NUMBER 1

void initKeyboard() {
	installInterruptHandler(KEYBOARD_INTERRUPT_IRQ_NUMBER, keyboardASMHandler);
}

void keyboardHandler() {
	unsigned char ch = inb(0x60);

	if (ch == 0x0 || ch > 0x80) {
		return;
	} else {
	}
}
