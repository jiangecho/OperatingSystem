# Makefile
OBJS = sched.o intr_handler.o
TARGET = kernel.o

AS = as
LD = ld
CC = gcc
CPP = gcc -E -nostdinc -I../include
CFLAGS = -fpack-struct -std=c99 -c -I../include \
-Wall -O -fstrength-reduce -fomit-frame-pointer -nostdinc

%.o : %.c
	$(CC) $(CFLAGS) $< -o $*.o
%.o : %.S
	$(CPP) $< -o _$*.s
	$(AS) _$*.s -o $*.o

$(TARGET) : $(OBJS)
	$(LD) -r -o $(TARGET) $(OBJS)

clean :
	-rm $(OBJS)

dep:
	sed '/\#\#\# Dependencies/q' < Makefile > tmp_make
	(for i in *.c;do $(CPP) -M $$i;done) >> tmp_make
	(for i in *.S;do $(CPP) -M $$i;done) >> tmp_make
	cp tmp_make Makefile
	rm tmp_make
	
### Dependencies:
sched.o: sched.c ../include/asm/io.h ../include/asm/system.h \
 ../include/asm/head.h ../include/ksched.h ../include/video.h \
 ../include/sys_call.h
intr_handler.o: intr_handler.S ../include/asm/macro.h
sys_call.o: sys_call.S
