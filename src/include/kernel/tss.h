#ifndef TSS_H_
#define TSS_H_

struct tss_struct {
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
typedef struct tss_struct tss_t;

#define INIT_TSS \
{ \
	0,(long) &0/*esp*/,0x10,0,0,0,0,0, \
	0,0,0,0,0,0,0,0, \
	0,0,0x17,0x17,0x17,0x17,0x17,0x17, \
	LDT_SEL,0x80000000, \
}

#endif
