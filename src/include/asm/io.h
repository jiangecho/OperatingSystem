#ifndef IO_H_
#define IO_H_

#define outb(port, value) \
	__asm__("outb %%al, %%dx" : : "a"(value) , "d"(port))

#define inb(port) ({ \
	unsigned char _v; \
	__asm__("inb %%dx, %%al" : "=a"(_v) : "d"(port)); \
	_v; \
})

#endif