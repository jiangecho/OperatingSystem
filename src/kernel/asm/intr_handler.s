.globl timer_interrupt, system_call

timer_interrupt:
	push %ds /* save ds and put kernel data space into it. */
	pushl %edx /* save eax,ebx,ecx,edx because gcc doesn't */
	pushl %ecx /* save them across function calls */
	pushl %ebx
	pushl %eax
	movl $0x10, %eax /* push kernel data space into ds */
	mov %ax, %ds /* hopefully no error */
    movb $0x20, %al /* EOI to interrupt controller*/
    outb %al, $0x20
    call doTimer /* call C procedure*/
    popl %eax /* pop something*/
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
	popl %ebx
	popl %ecx
	popl %edx
	pop %ds
	iret

system_call_table:
	.long sys_drawPoint /* x, y */
	.long sys_drawString /* x, y, string */
	.long sys_fillRect /* p1(0-15=x1,16-31=x2) p2(0-15=y1,16-31=y2)*/
