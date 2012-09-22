#include "video.h"
#include "asm/system.h"

extern void scheduleInit();

void main() {
	fillRect(0, C_SCREEN_WIDTH, 0, C_SCREEN_HEIGHT, RGB(255, 255, 255));
	scheduleInit();
	sti();
	//moveToUserMode();
	for (;;)
		pause();
}
