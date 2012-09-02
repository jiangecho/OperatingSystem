#ifndef VIDEO_H
#define VIDEO_H

// The default format of RGB is 5:6:5 now,
// if change default format, OK when you change the next line.
#define rgb(r,g,b) rgb565(r,g,b)
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

extern unsigned short rgb565(unsigned char r, unsigned char g, unsigned char b);
extern void drawPoint(unsigned int x, unsigned int y, unsigned short color);
extern unsigned short getPoint(unsigned int x, unsigned int y);
extern void fillRect(unsigned int x1, unsigned int y1, unsigned int x2,
		unsigned int y2, unsigned int color);
extern void cleanScreen(unsigned short color);
extern void drawXLine(unsigned int y, unsigned int x1, unsigned int x2,
		unsigned short color);
extern void drawYLine(unsigned int x, unsigned int y1, unsigned int y2,
		unsigned short color);
extern void drawRect(unsigned int x1, unsigned int y1, unsigned int x2,
		unsigned y2, unsigned short color);
extern void getScreenImage(unsigned int x, unsigned int y, unsigned int width,
		unsigned int height, unsigned short *addr);
extern void drawImage(unsigned int x, unsigned int y, unsigned int width,
		unsigned int height, unsigned short *addr);

#endif
