#ifndef SCHED_H_
#define SCHED_H_

// These codes is copied from linux 0.11.
struct TSS {
	long back_link; /* 16 high bits zero */
	long esp0;
	long ss0; /* 16 high bits zero */
	long esp1;
	long ss1; /* 16 high bits zero */
	long esp2;
	long ss2; /* 16 high bits zero */
	long cr3;
	long eip;
	long eflags;
	long eax, ecx, edx, ebx;
	long esp;
	long ebp;
	long esi;
	long edi;
	long es; /* 16 high bits zero */
	long cs; /* 16 high bits zero */
	long ss; /* 16 high bits zero */
	long ds; /* 16 high bits zero */
	long fs; /* 16 high bits zero */
	long gs; /* 16 high bits zero */
	long ldt; /* 16 high bits zero */
	long trace_bitmap; /* bits: trace 0, bitmap 16-31 */
};
struct Task {
	struct {long a,b;} ldt[3];
	struct TSS tss;
};

#define INIT_TASK \
{ \
	{ \
		{0,0}, \
		{0x9f,0xc0fa00}, \
		{0x9f,0xc0f200}, \
	}, \
	{ \
		0,(long) &task0_stack,0x10,0,0,0,0,0, \
		0,0,0,0,0,0,0,0, \
		0,0,0x17,0x17,0x17,0x17,0x17,0x17, \
		_LDT(0),0x80000000, \
	} \
}

#define FIRST_TSS_ENTRY 4
#define FIRST_LDT_ENTRY (FIRST_TSS_ENTRY+1)
#define _TSS(n) ((((unsigned long) n)<<4)+(FIRST_TSS_ENTRY<<3))
#define _LDT(n) ((((unsigned long) n)<<4)+(FIRST_LDT_ENTRY<<3))
#define ltr(n) __asm__("ltr %%ax"::"a" (_TSS(n)))
#define lldt(n) __asm__("lldt %%ax"::"a" (_LDT(n)))

#endif
