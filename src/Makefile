TARGET = target.o
OBJS = init/target.o kernel/target.o 
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
	$(LD) $(OBJS) -T linker.ld -o $(TARGET)
init/target.o::
	(cd init;make dep;make)
kernel/target.o::
	(cd kernel;make dep;make)
clean:
	-rm $(OBJS) $(TARGET)
	-rm kernel.bin
dep:
	sed '/\#\#\# Dependencies/q' < Makefile > tmp_make
	(for i in *.c;do $(CPP) -M $$i;done) >> tmp_make
	(for i in *.S;do $(CPP) -M $$i;done) >> tmp_make
	cp tmp_make Makefile
	rm tmp_make
### Dependencies:
