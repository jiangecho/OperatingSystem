#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#define sti() __asm__("sti");
#define cli() __asm__("cli");

extern void setInterruptHandler(unsigned char number, void *handler);
extern void setInterruptMaskWord(unsigned int irq, int enable);
extern void installInterruptHandler(unsigned char irq, void *handler);

#endif
