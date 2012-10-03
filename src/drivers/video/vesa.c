/**
 * drivers/video/vesa.c
 * Restore core of vesa.
 * Copyright(C) 2012 Liu Chang
 */
#include "video.h"
/**
 * @offset The offset of video(y*SCREEN_WIDTH+x).
 * @color The color of the point(using 5:6:5 format).
 */
void sys_drawPoint(int x, int y, short color) {
	unsigned short *video = (unsigned short *) (*((unsigned int *) VESA_ADDR));
	unsigned int offset = y * SCREEN_WIDTH + x;
	*(video + offset) = color;
}
