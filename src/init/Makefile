TARGET = target.o
OBJS = main.o head.o 
AS = as
LD = i586-elf-ld
CC = i586-elf-gcc
CPP = gcc -E -nostdinc -I/home/xiaoqie/workbench/OS/src/include
CFLAGS = -fpack-struct -std=c99 -c -I/home/xiaoqie/workbench/OS/src/include \
-Wall -O -fstrength-reduce -fomit-frame-pointer \
-nostdinc -nostdlib -fno-builtin -nostartfiles \
-nodefaultlibs
%.o : %.c
	$(CC) $(CFLAGS) $< -o $*.o
%.o : %.S
	$(CPP) $< -o _$*.s
	$(AS) _$*.s -o $*.o
$(TARGET):$(OBJS)
	$(LD) -r -o $(TARGET) $(OBJS)
clean:
	-rm $(OBJS) $(TARGET)
dep:
	sed '/\#\#\# Dependencies/q' < Makefile > tmp_make
	(for i in *.c;do $(CPP) -M $$i;done) >> tmp_make
	(for i in *.S;do $(CPP) -M $$i;done) >> tmp_make
	cp tmp_make Makefile
	rm tmp_make
### Dependencies:
main.o: main.c /home/xiaoqie/workbench/OS/src/include/kernel/multiboot.h \
 /home/xiaoqie/workbench/OS/src/include/asm/head.h
head.o: head.S /home/xiaoqie/workbench/OS/src/include/asm/macro.h \
 /home/xiaoqie/workbench/OS/src/include/kernel/multiboot.h
