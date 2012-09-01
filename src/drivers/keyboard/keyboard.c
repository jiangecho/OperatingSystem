#include "kernel.h"
#include "asm/io.h"

void keyboardASMHandler();
void keyboardHandler();

#define KEYBOARD_INTERRUPT_IRQ_NUMBER 1

void initKeyboard() {
	installInterruptHandler(KEYBOARD_INTERRUPT_IRQ_NUMBER, keyboardASMHandler);
}

void processKey(unsigned char key, int type) {

}

void keyboardHandler() {
	unsigned char ch = inb(0x60);

	if (ch == 0x0 || ch > 0x80) {
		return;
	} else {
		// Emulate mouse.
		switch (ch) {
		case 0x48:
			moveMouse(0, -5);
			break;
		case 0x4B:
			moveMouse(-5, 0);
			break;
		case 0x4D:
			moveMouse(5, 0);
			break;
		case 0x50:
			moveMouse(0, 5);
			break;
		case 0x34:
			break;
		}
	}
}
