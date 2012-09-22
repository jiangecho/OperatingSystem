/**
 * drivers/video/vesa_util.c
 * Restore utility functions of drawing.
 * Copyright (C) 2012 Liu Chang
 */

#include "video.h"

void fillRect(int x1, int x2, int y1, int y2, unsigned short color) {
	for (int i = x1; i < x2 + 1; i++) {
		for (int j = y1; j < y2 + 1; j++) {
			setColor(i, j, color);
		}
	}
}
