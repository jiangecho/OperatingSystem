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

#define _set_tssldt_desc(n,addr,type) \
		__asm__ ("movw $104,%1\n\t" \
				"movw %%ax,%2\n\t" \
				"rorl $16,%%eax\n\t" \
				"movb %%al,%3\n\t" \
				"movb $" type ",%4\n\t" \
				"movb $0x00,%5\n\t" \
				"movb %%ah,%6\n\t" \
				"rorl $16,%%eax" \
				::"a" (addr), "m" (*(n)), "m" (*(n+2)), "m" (*(n+4)), \
				 "m" (*(n+5)), "m" (*(n+6)), "m" (*(n+7)) \
		)

#define setTSSDesc(n,addr) _set_tssldt_desc(((char *) (n)),addr,"0x89")
#define setLDTDesc(n,addr) _set_tssldt_desc(((char *) (n)),addr,"0x82")

#endif
