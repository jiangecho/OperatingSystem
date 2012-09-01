#include "kernel.h"
#include "asm/io.h"

struct IDT {
	unsigned short offset0015;
	unsigned short segSelector;
	unsigned char unused0;
	unsigned char saved110 :3;
	unsigned char d :1;
	unsigned char saved0 :1;
	unsigned char dpl :2;
	unsigned char p :1;
	unsigned short offset1631;
};

struct IDTDescriptor {
	unsigned short length;
	struct IDT *addr;
};

static void interruptInit8259A();
static void interruptInitIdt();
void interruptDefaultHandler();

static struct IDTDescriptor idtDesc;
static struct IDT idt[256];

void initInterrupt() {
	interruptInit8259A();
	interruptInitIdt();
}

static void interruptInit8259A() {
	outb(0x20, 0x11);
	outb(0xa0, 0x11);
	outb(0x21, 0x20);
	outb(0xa1, 0x28);
	outb(0x21, 0x4);
	outb(0xa1, 0x2);
	outb(0x21, 0x1);
	outb(0xa1, 0x1);
	outb(0x21, 0xfb);
	outb(0xa1, 0xff);
}

static void interruptInitIdt() {
	struct IDT p;
	p.d = 1;
	p.dpl = 0;
	p.offset0015 = (unsigned int) interruptDefaultHandler;
	p.offset1631 = (unsigned int) interruptDefaultHandler;
	p.p = 1;
	p.saved0 = 0;
	p.saved110 = 6;
	p.segSelector = 0x8;
	p.unused0 = 0;

	for (int i = 0; i < 256; ++i) {
		idt[i] = p;
	}

	idtDesc.addr = idt;
	idtDesc.length = 256 * 8;

	__asm__("lidt %0" : "=m"(idtDesc));
}

void sti() {
	__asm__( "sti" );
}

void cli() {
	__asm__( "cli" );
}

void setInterruptHandler(unsigned char number, void *handler) {
	cli();
	idt[number].offset0015 = (unsigned int) handler;
	idt[number].offset1631 = (unsigned int) handler >> 16;
}

void installInterruptHandler(unsigned char irq, void *handler) {
	setInterruptHandler(0x20 + irq, handler);
	setInterruptMaskWord(irq, 1);
}

void setInterruptMaskWord(unsigned int irq, int enable) {
	cli();
	if (irq < 0 || irq > 15) {
		return;
	} else {
		unsigned char maskWord;
		if (irq < 8) {
			maskWord = inb(0x21);
		} else {
			maskWord = inb(0xa1);
		}
		switch (irq) {
		case 0:
		case 8:
			if (enable) {
				maskWord &= 0xfe; // 0xfe = 1111 1110
			} else {
				maskWord |= 0x01; // 0x00 = 0000 0001
			}
			break;
		case 1:
		case 9:
			if (enable) {
				maskWord &= 0xfd; // 0xfd = 1111 1101
			} else {
				maskWord |= 0x02; // 0x01 = 0000 0010
			}
			break;
		case 2:
		case 10:
			if (enable) {
				maskWord &= 0xfb; // 0xfb = 1111 1011
			} else {
				maskWord |= 0x04; // 0x04 = 0000 0100
			}
			break;
		case 3:
		case 11:
			if (enable) {
				maskWord &= 0xf7; // 0xf7 = 1111 0111
			} else {
				maskWord |= 0x08; // 0x08 = 0000 1000
			}
			break;
		case 4:
		case 12:
			if (enable) {
				maskWord &= 0xef; // 0xef = 1110 1111
			} else {
				maskWord |= 0x10; // 0x10 = 0001 0000
			}
			break;
		case 5:
		case 13:
			if (enable) {
				maskWord &= 0xdf; // 0xdf = 1101 1111
			} else {
				maskWord |= 0x20; // 0x20 = 0010 0000
			}
			break;
		case 6:
		case 14:
			if (enable) {
				maskWord &= 0xbf; // 0xbf = 1011 1111
			} else {
				maskWord |= 0x40; // 0x40 = 0100 0000
			}
			break;
		case 7:
		case 15:
			if (enable) {
				maskWord &= 0x7f; // 0x7f = 0111 1111
			} else {
				maskWord |= 0x80; // 0x80 = 1000 0000
			}
			break;
		}
		if (irq < 8) {
			outb(0x21, maskWord);
		} else {
			outb(0xa1, maskWord);
		}
	}
}
