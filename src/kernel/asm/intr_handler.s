.globl timer_interrupt, system_call

timer_interrupt:
	push %ds # save ds and put kernel data space into it.
	pushl %edx # save eax,ebx,ecx,edx because gcc doesn't
	pushl %ecx # save them across function calls
	pushl %ebx
	pushl %eax
	movl $0x10, %eax # push kernel data space into ds
	mov %ax, %ds # hopefully no error
    movb $0x20, %al # EOI to interrupt controller
    outb %al, $0x20
    call doTimer # call C procedure
    popl %eax # pop something
    popl %ebx
    popl %ecx
    popl %edx
    pop %ds
    iret

system_call:
	push %ds
	pushl %edx
	pushl %ecx
	pushl %ebx
	movl $0x10, %edx
	mov %dx, %ds
	call *system_call_table(,%eax,4)
1:
	popl %ebx
	popl %ecx
	popl %edx
	pop %ds
	iret

system_call_table:
	.long fork
	.long exit
	.long pause
