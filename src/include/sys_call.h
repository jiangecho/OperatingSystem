#ifndef SYS_CALL_H_
#define SYS_CALL_H_

#define _syscall0(type,name) \
type name(void) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
	: "=a" (__res) \
	: "0" (__NR_##name)); \
return (type) __res; \
}

#define _syscall1(type,name,atype) \
type name(atype a) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
	: "=a" (__res) \
	: "0" (__NR_##name),"b" ((long)(a))); \
return (type) __res; \
}

#define _syscall2(type,name,atype,btype) \
type name(atype a,btype b) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
	: "=a" (__res) \
	: "0" (__NR_##name),"b" ((long)(a)),"c" ((long)(b))); \
return (type) __res; \
}

#define _syscall3(type,name,atype,btype,ctype) \
type name(atype a,btype b,ctype c) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
	: "=a" (__res) \
	: "0" (__NR_##name),"b" ((long)(a)),"c" ((long)(b)),"d" ((long)(c))); \
return (type) __res; \
}

#define __NR_drawPoint 0
#define __NR_drawString 1
#define __NR_fillRect 2

static inline _syscall3(void, drawPoint, int, int, short)
static inline _syscall3(int, drawString, int, char *, short)
static inline _syscall3(void, fillRect, int, int, short)

#endif
