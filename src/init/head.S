/* Copyright(C) 2012 Xiaoqie
 * This file is part of <OS>.
 *
 * <OS> is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * <OS> is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with <OS>.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "asm/macro.h"
#define ASM_FILE
#include "kernel/multiboot.h"

# setting up the Multiboot header - see GRUB docs for details
#define MULTIBOOT_HEADER_FLAGS 0x00000003
.align 4
.long MULTIBOOT_HEADER_MAGIC
.long MULTIBOOT_HEADER_FLAGS
.long -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

ENTRY(startup_32):
	movl %eax, multiboot_magic
	movl %ebx, multiboot_mbi
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

ignore_intr:
	iret

.align 4
.word 0
idt_desc:
	.word 256*8-1
	.long idt
.align 4
.word 0
gdt_desc:
	.word 5*8-1
	.long gdt

.align 8
ENTRY(idt):
	.fill 256,8,0
ENTRY(gdt):
	.quad 0x0000000000000000 /* NULL descriptor */
	.quad 0x00cf9a000000ffff /* 4g */
	.quad 0x00cf92000000ffff /* 4g */
	.quad 0x0000000000000000 /* tss */
	.quad 0x0000000000000000 /* ldt */

____stack_start____:
	.fill 256,4,0
stack:

ENTRY(multiboot_magic):
	.long 0
ENTRY(multiboot_mbi):
	.long 0
