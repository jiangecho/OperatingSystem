#include "kernel.h"

extern void setupGDT();

void main() {
	setupGDT();
	initInterrupt();
	initMouse(); // We use keyboard to emulate mouse now.
	initKeyboard();
	initGUI();
	initSchedule();
	sti(); // Init OK, start interrupt.
}
