# "*.s" will compile with "gas".

.globl start, gdt, idt, init_task_stack_tail

start:
	movl $0x10, %eax /* load segment registers */
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	movl $0x8ffff, %esp
	movb $0x11, %al /* reprogram the interrupts */
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
	call setup_idt /* setup desc tables */
	call setup_gdt
	call main
EL:
	jmp EL /* main should never return here */

setup_idt:
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
	lidt idt_desc
	ret
idt_desc:
	.word 256*8-1
	.long idt
idt:
	.fill 256,8,0
ignore_intr:
	movb $0x20, %al
	outb %al, $0x20
	outb %al, $0xa0
	iret

setup_gdt:
	lgdt gdt_desc
	ret
gdt_desc:
	.word 5*8-1
	.long gdt
gdt:
	.quad 0x0000000000000000 /* NULL descriptor */
	.quad 0x00cf9a000000ffff /* 16Mb */
	.quad 0x00cf92000000ffff /* 16Mb */
	.quad 0x0000000000000000 /* tss */
	.quad 0x0000000000000000 /* ldt */

init_task_stack_head:
	.fill 128,4,0
init_task_stack_tail:
