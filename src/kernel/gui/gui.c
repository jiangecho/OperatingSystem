#include "kernel.h"

// The position of mouse.
int mouseX = 400;
int mouseY = 300;
// The picture behind mouse.
static const unsigned short behindMouse[MOUSE_WIDTH * MOUSE_HEIGHT];

// Init desktop, use white to clean it.
void initGUI() {
	unsigned short c = rgb565(255, 255, 255);
	cleanScreen(c);
	unsigned short *addr = (unsigned short *) behindMouse;
	for (int j = 0; j < MOUSE_HEIGHT; j++) {
		for (int i = 0; i < MOUSE_WIDTH; i++) {
			*(addr + j * MOUSE_WIDTH + i) = c;
		}
	}
}

/**
 * Move mouse to a position.
 * @x X position.
 * @y Y position.
 */
void moveMouseTo(int x, int y) {
	// Restore picture behind old mouse position.
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > 784)
		x = 784;
	if (y > 579)
		y = 579;
	drawImage(mouseX, mouseY, MOUSE_WIDTH, MOUSE_HEIGHT,
			(unsigned short *) behindMouse);

	// Move mouse position.
	mouseX = x;
	mouseY = y;
	// Draw mouse.
	fillRect(x, y, x + MOUSE_WIDTH, y + MOUSE_HEIGHT, 0);
	/*getScreenImage(mouseX, mouseY, MOUSE_WIDTH, MOUSE_HEIGHT,
	 (unsigned short *) behindMouse);*/
}

/**
 * Move mouse.
 * If you want to up mouse 5 pixels, you can call it like this:
 * moveMouse(0, -5);
 * If you want to down mouse 5 pixels, you can call it like this:
 * moveMouse(0, 5);
 * @x X movement.
 * @y Y movement.
 */
void moveMouse(int x, int y) {
	moveMouseTo(mouseX + x, mouseY + y);
}
