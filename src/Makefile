# Makefile
OBJS = init/head.o init/main.o
# kernel/kernel.o
TARGET = kernel.bin

AS = as
IAS = nasm
LD = ld
CC = gcc
CPP = gcc -E -nostdinc -Iinclude
CFLAGS = -fpack-struct -std=c99 -c -Iinclude \
-Wall -O -fstrength-reduce -fomit-frame-pointer -nostdinc

# Generate target file.
$(TARGET) : $(OBJS)
	$(LD) -T linker.ld  $(OBJS) -o $(TARGET)

init/head.o : init/head.S include/asm/macro.h
	$(CPP) init/head.S -o init/_head.s
	$(AS) init/_head.s -o init/head.o

%.o : %.s
	$(AS) $< -o $*.o
%.o : %.c
	$(CC) $(CFLAGS) $< -o $*.o

clean :
	-rm $(OBJS) $(TARGET)
	-rm kernel.bin

dep :
	sed '/\#\#\# Dependencies/q' < Makefile > tmp_make
	(for i in init/*.c;do echo -n "init/";$(CPP) -M $$i;done) >> tmp_make
	cp tmp_make Makefile
	rm tmp_make

### Dependencies:
init/main.o: init/main.c include/video.h include/asm/system.h \
 include/sys_call.h
