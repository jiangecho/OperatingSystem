#include "video.h"
#include "asm/system.h"

extern void scheduleInit();

void main() {
	unsigned short c = rgb(255, 255, 255);
	cleanScreen(c);
	/*unsigned short *video = (unsigned short *) (*((unsigned int *) 0x80001));
	unsigned int offset2 = 40 * SCREEN_WIDTH + 40;
	*(video + offset2) = 0;*/
	scheduleInit();
	sti();
	/*unsigned int offset1 = 20 * SCREEN_WIDTH + 20;
	*(video + offset1) = 0;*/
	moveToUserMode();
	/*unsigned int offset = 10 * SCREEN_WIDTH + 10;
	*(video + offset) = 0;*/
	for (;;)
		;
}
