/*-----kernel.h--------------------------------*
 * Include some methods.
 *---------------------------------------------*/
#ifndef KERNEL_H_
#define KERNEL_H_

#define ASM_FUNC
#define MOUSE_WIDTH 10
#define MOUSE_HEIGHT 20
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void initKeyboard();
void initMouse();
void initSchedule();

unsigned short rgb565(unsigned char r, unsigned char g, unsigned char b);

void initInterrupt();
void sti();
void cli();
void setInterruptHandler(unsigned char number, void *handler);
void setInterruptMaskWord(unsigned int irq, int enable);
void installInterruptHandler(unsigned char irq, void *handler);

void initGUI();

void moveMouseTo(int x, int y);
void moveMouse(int x, int y);

void drawPoint(unsigned int x, unsigned int y, unsigned short color);
unsigned short getPoint(unsigned int x, unsigned int y);
void fillRect(unsigned int x1, unsigned int y1, unsigned int x2,
		unsigned int y2, unsigned int color);
void cleanScreen(unsigned short color);
void drawXLine(unsigned int y, unsigned int x1, unsigned int x2,
		unsigned short color);
void drawYLine(unsigned int x, unsigned int y1, unsigned int y2,
		unsigned short color);
void drawRect(unsigned int x1, unsigned int y1, unsigned int x2, unsigned y2,
		unsigned short color);
void getScreenImage(unsigned int x, unsigned int y, unsigned int width,
		unsigned int height, unsigned short *addr);
void drawImage(unsigned int x, unsigned int y, unsigned int width,
		unsigned int height, unsigned short *addr);

#endif
