#include "kernel.h"

void main() {
	initInterrupt();
	initMouse(); // We use keyboard to emulate mouse now.
	initKeyboard();
	initGUI();
	initSchedule();
	sti(); // Init OK, start interrupt.
}
