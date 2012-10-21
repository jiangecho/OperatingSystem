#ifndef HEAD_H_
#define HEAD_H_
typedef long long desc_t;

extern desc_t idt[256],gdt[5];
extern long multiboot_magic;
extern long multiboot_mbi;

#endif
