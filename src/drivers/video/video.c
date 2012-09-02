#include "kernel.h"

//The size of screen.
unsigned int scrWidth = SCREEN_WIDTH - 1;
unsigned int scrHeight = SCREEN_HEIGHT - 1;

#define VESA_ADDR 0x80001

unsigned short rgb565(unsigned char r, unsigned char g, unsigned char b) {
	union {
		unsigned int color;
		struct {
			unsigned char b :5;
			unsigned char g :6;
			unsigned char r :5;
		};
	} u;
	u.r = r % 32;
	u.g = g % 64;
	u.b = b % 32;
	return u.color;
}

/**
 * Draw a point on screen.
 * The core method of video.
 * @x X position.
 * @y Y position.
 * @color The color of the point(using 5:6:5 format).
 */
void drawPoint(unsigned int x, unsigned int y, unsigned short color) {
	if (x > scrWidth || y > scrHeight)
		return;

	unsigned short *video = (unsigned short *) (*((unsigned int *) VESA_ADDR));
	unsigned int offset = y * SCREEN_WIDTH + x;
	*(video + offset) = color;
}

unsigned short getPoint(unsigned int x, unsigned int y) {
	if (x > scrWidth)
		x = scrWidth;
	if (y > scrHeight)
		y = scrHeight;

	unsigned short *video = (unsigned short *) (*((unsigned int *) VESA_ADDR));
	unsigned int offset = y * SCREEN_WIDTH + x;
	return *(video + offset);
}

/**
 * Draw a rect.
 * @sx Start X position of the rect.
 * @sy Start Y position of the rect.
 * @ex End X position of the rect.
 * @ey End Y position of the rect.
 * @color The color of the rect(using 5:6:5 format).
 */
void fillRect(unsigned int sx, unsigned int sy, unsigned int ex,
		unsigned int ey, unsigned int color) {
	for (int x = sx; x < ex; x++) {
		for (int y = sy; y < ey; y++) {
			drawPoint(x, y, color);
		}
	}
}

/**
 * Clean the screen.
 * @color The color of screen(using 5:6:5 format).
 */
void cleanScreen(unsigned short color) {
	fillRect(0, 0, scrWidth, scrHeight, color);
}

/**
 * Draw a horizontal line.
 * @y Y position.
 * @x1 Start X.
 * @x2 End X.
 */
void drawXLine(unsigned int y, unsigned int x1, unsigned int x2,
		unsigned short color) {
	for (int x = x1; x < x2; x++) {
		drawPoint(x, y, color);
	}
}

/**
 * Draw a Y line.
 * @x X position.
 * @y1 Start Y.
 * @y2 End Y.
 */
void drawYLine(unsigned int x, unsigned int y1, unsigned int y2,
		unsigned short color) {
	for (int y = y1; y < y2; y++) {
		drawPoint(x, y, color);
	}
}

/**
 * Draw a rect.
 * @x1 Start X.
 * @y1 Start Y.
 * @x2 End X.
 * @y2 End Y.
 * @color The color of line(565).
 */
void drawRect(unsigned int x1, unsigned int y1, unsigned int x2, unsigned y2,
		unsigned short color) {
	drawXLine(y1, x1, x2, color);
	drawXLine(y2, x1, x2, color);
	drawYLine(x1, y1, y2, color);
	drawYLine(x2, y1, y2, color);
}

/**
 * Get a image from screen.
 * @x X position.
 * @y Y position.
 * @width The width of image.
 * @height The height of image.
 * @addr The storing address.
 */
void getScreenImage(unsigned int x, unsigned int y, unsigned int width,
		unsigned int height, unsigned short *addr) {
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			*(addr + j * width + i) = getPoint(x + i, y + j);
		}
	}
}

/**
 * Draw a image from screen(The color must be 565 format).
 * @x X position.
 * @y Y position.
 * @width The width of image.
 * @height The height of image.
 * @addr Image address.
 */
void drawImage(unsigned int x, unsigned int y, unsigned int width,
		unsigned int height, unsigned short *addr) {
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			drawPoint(x + i, y + j, *(addr + j * width + i));
		}
	}
}
