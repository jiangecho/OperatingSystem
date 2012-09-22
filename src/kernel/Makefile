# Makefile
OBJS = fork.o sched.o asm/asm.o
TARGET = kernel.o

AS = as
LD = ld
CC = gcc
CPP = cpp -nostdinc -I../include
CFLAGS = -fpack-struct -std=c99 -c -I../include \
-Wall -O -fstrength-reduce -fomit-frame-pointer -nostdinc

%.o : %.s
	$(AS) $< -o $*.o
%.o : %.c
	$(CC) $(CFLAGS) $< -o $*.o

$(TARGET) : $(OBJS)
	$(LD) -r -o $(TARGET) $(OBJS)

asm/asm.o :
	(cd asm; make)

clean :
	-rm $(OBJS)
	(cd asm; make clean)

dep:
	sed '/\#\#\# Dependencies/q' < Makefile > tmp_make
	(for i in *.c;do $(CPP) -M $$i;done) >> tmp_make
	cp tmp_make Makefile
	rm tmp_make
	
### Dependencies:
fork.o: fork.c ../include/ksched.h ../include/asm/system.h \
 ../include/asm/head.h
sched.o: sched.c ../include/asm/io.h ../include/asm/system.h \
 ../include/asm/head.h ../include/ksched.h ../include/video.h
