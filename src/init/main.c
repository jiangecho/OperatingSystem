#include "video.h"
#include "asm/system.h"
#include "sys_call.h"

extern void scheduleInit();
extern void sys_fillRect(int x, int y, short color);

void main() {
	sys_fillRect(C_SCREEN_WIDTH << 16, C_SCREEN_HEIGHT << 16, RGB(255,255,255));
	scheduleInit();
	sti();
	moveToUserMode();
	while(1) {
		drawString(200 | (100 << 16), "init", 0);
		drawString(200 | (100 << 16), "init", RGB(0,255,0));
	}
}
