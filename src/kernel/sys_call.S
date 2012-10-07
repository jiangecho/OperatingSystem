/* kernel/asm/sys_call.S */
/*#include "asm/macro.h"

ENTRY(sys_call):
	pushl %ecx
	pushl %edx
	pushl %ebp
	movl %esp,%ebp
	sysenter

ENTRY(sys_return):
	popl %ebp
	popl %edx
	popl %ecx
	ret

ENTRY(sysenter_entry):
	call *sys_call_table(,%eax,4)
	movl EIP, %edx
	movl OLDESP, %ecx
	sysexit

sys_call_table:
	.long sys_drawPoint
	.long sys_drawString
	.long sys_fillRect
*/
