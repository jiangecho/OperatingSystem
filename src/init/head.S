#include "asm/macro.h"
#define ASM_FILE
#include "multiboot.h"

# setting up the Multiboot header - see GRUB docs for details
/*.align 4
.long 0x1BADB002
.long 1|2
.long -(0x1BADB002 + (1|2))*/

# setting up the Multiboot header - see GRUB docs for details
#define MULTIBOOT_HEADER_FLAGS 0x00000003
.align 4
multiboot_header:
	.long MULTIBOOT_HEADER_MAGIC
	.long MULTIBOOT_HEADER_FLAGS
	.long -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

ENTRY(start):
	movl %eax, multiboot_magic
    movl %ebx, multiboot_mbd
# reprogram the interrupts
	movb $0x11, %al
	outb %al, $0x20
	outb %al, $0xa0
	movb $0x20, %al
	outb %al, $0x21
	movb $0x28, %al
	outb %al, $0xa1
	movb $0x04, %al
	outb %al, $0x21
	movb $0x02, %al
	outb %al, $0xa1
	movb $0x01, %al
	outb %al, $0x21
	outb %al, $0xa1
	movb $0xff, %al
	outb %al, $0x21 /* mask off all interrupt */
	outb %al, $0xa1
# setup idt desc
	movl $stack, %esp
	lea ignore_intr,%edx
	movl $0x00080000,%eax
	movw %dx,%ax		/* selector = 0x0008 = cs */
	movw $0x8E00,%dx	/* interrupt gate - dpl=0, present */
	lea idt,%edi
	mov $256,%ecx
rp_sidt:
	movl %eax,(%edi)
	movl %edx,4(%edi)
	addl $8,%edi
	dec %ecx
	jne rp_sidt
# load desc tables
	lidt idt_desc
	lgdt gdt_desc
# load segment registers
	movl $0x10, %eax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	movl $stack, %esp
# call main
	call start_kernel
1:	jmp 1b /* main should never return here */

idt_desc:
	.word 256*8-1
	.long idt
ENTRY(idt):
	.fill 256,8,0
ignore_intr:
	iret

gdt_desc:
	.word 5*8-1
	.long gdt
ENTRY(gdt):
	.quad 0x0000000000000000 /* NULL descriptor */
	.quad 0x00cf9a000000ffff /* 4g */
	.quad 0x00cf92000000ffff /* 4g */
	.quad 0x0000000000000000 /* tss */
	.quad 0x0000000000000000 /* ldt */

.fill 256,4,0
stack:

ENTRY(multiboot_magic):
	.long 0
ENTRY(multiboot_mbd):
	.long 0
