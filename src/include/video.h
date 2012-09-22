#ifndef VIDEO_H
#define VIDEO_H

// Human Screen Size(from 1 to (800|600))
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Computer Screen Size(from 0 to (Human Screen Size - 1)).
#define C_SCREEN_WIDTH (SCREEN_WIDTH - 1)
#define C_SCREEN_HEIGHT (SCREEN_HEIGHT - 1)

#define VESA_ADDR 0x80001

#define RGB(r,g,b) RGB565(r,g,b)

#define RGB565(r,g,b)     \
   (((r & 31)) |          \
	((g & 63) << 5) |     \
	((b & 31) << 11))

extern void setColor(unsigned int x, unsigned int y, unsigned short color);
extern void fillRect(int x1, int x2, int y1, int y2, unsigned short color);

#endif
