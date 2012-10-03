/**
 * drivers/video/vesa_util.c
 * Restore utility functions of drawing.
 * Copyright (C) 2012 Liu Chang
 */

#include "video.h"
#include "sys_call.h"
extern void sys_drawPoint(int x, int y, short color);
struct {int x, y;} cursor = {0,0};

/*0-15,*/
void sys_fillRect(int x, int y, short color) {
	for (int i = (x & 0xFFFF); i < (x >> 16); i++) {
		for (int j = (y & 0xFFFF); j < (y >> 16); j++) {
			sys_drawPoint(i, j, color);
		}
	}
}

// Return length of c.
int sys_drawString(int pos, char *c, short color) {
	int k;
	int x = pos & 0xFFFF;
	int y = pos >> 16;
	for (k = 0; c[k] != '\0'; k++) {
		unsigned char *font = (unsigned char *) FONT_ADDR + c[k] * 16;
		for (int i = 0; i < 16; i++) {
			char tmp = font[i];
			for (int j = 0; j < 8; j++) {
				if ((tmp >> j & 1) == 1)
					sys_drawPoint((x - j) + 8, y + i, color);
			}
		}
		x += 8;
	}
	return k;
}

void print(char *c) {
	cursor.x += drawString(((cursor.x*8) & 0xFFFF) | ((cursor.y*16) << 16), c, 0);
}

void println(char *c) {
	drawString(((cursor.x*8) & 0xFFFF) | ((cursor.y*16) << 16), c, 0);
	cursor.x = 0;
	cursor.y++;
}
