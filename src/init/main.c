#include "video.h"
#include "asm/system.h"
#include "sys_call.h"
extern void scheduleInit();
extern void sys_fillRect(int x, int y, short color);
void main() {
	sys_fillRect(C_SCREEN_WIDTH << 16, C_SCREEN_HEIGHT << 16, RGB(255,255,255));
	scheduleInit();
	print("Schedule init.");
	println("Now 40%.");
	sti();
	println("Opened interrupt.");
	moveToUserMode();
	println("Now Entered init_task");
	while(1);
}
