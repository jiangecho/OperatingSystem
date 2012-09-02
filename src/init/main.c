#include "video.h"
#include "interrupt.h"

extern void setupGDT();
extern void initKeyboard();
extern void initMouse();
extern void initSchedule();
extern void initInterrupt();

void main() {
	setupGDT();
	unsigned short c = rgb(255, 255, 255);
	cleanScreen(c);
	initInterrupt();
	initMouse(); // We use keyboard to emulate mouse now.
	initKeyboard();
	initSchedule();
	sti(); // Init OK, start interrupt.
}
