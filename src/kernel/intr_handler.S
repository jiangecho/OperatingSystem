#include "asm/macro.h"

ENTRY(timer_interrupt):
	push %ds /* save ds and put kernel data space into it. */
	pushl %edx /* save eax,ebx,ecx,edx because gcc doesn't */
	pushl %ecx /* save them across function calls */
	pushl %ebx
	pushl %eax
	movl $0x10, %eax /* push kernel data space into ds */
	mov %ax, %ds
    movb $0x20, %al /* EOI to interrupt controller */
    outb %al, $0x20
    call doTimer
    popl %eax
    popl %ebx
    popl %ecx
    popl %edx
    pop %ds
    iret

ENTRY(sys_call_int80):
	push %ds
	pushl %edx
	pushl %ecx
	pushl %ebx
	movl $0x10, %edx
	mov %dx, %ds
	call *sys_call_table(,%eax,4)
	popl %ebx
	popl %ecx
	popl %edx
	pop %ds
	iret

sys_call_table:
	.long sys_drawPoint
	.long sys_drawString
	.long sys_fillRect
