/*#include "video.h"
#include "asm/system.h"
#include "sys_call.h"*/
#include "multiboot.h"

/*extern void scheduleInit();
extern void sys_fillRect(int x, int y, short color);*/

extern int multiboot_magic;
extern void *multiboot_mbd;
void start_kernel() {
	if (multiboot_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
	}

	/* Print a letter to screen to see everything is working: */
	unsigned char *videoram = (unsigned char *)0xB8000;
	videoram[0] = 65; /* character 'A' */
	videoram[1] = 0x07; /* light grey (7) on black (0). */
	while(1);
}
