# Makefile
OBJS = init/head.o init/main.o drivers/drivers.o kernel/kernel.o
# kernel/kernel.o
TARGET = floppy.img

BUILD = tools/build
PUT =  tools/put
TOOLS = $(BUILD) $(PUT)

AS = as
IAS = nasm
LD = ld
CC = gcc
CPP = gcc -E -nostdinc -Iinclude
CFLAGS = -fpack-struct -std=c99 -c -Iinclude \
-Wall -O -fstrength-reduce -fomit-frame-pointer -nostdinc

# Generate target file.
$(TARGET) : $(OBJS) $(TOOLS) boot/bootsect.bin boot/setup.bin
	$(LD) -o kernel.ld -Ttext 0x90000 -e start $(OBJS)
	objcopy -R .note -R .comment -S -O binary kernel.ld kernel.bin
	$(BUILD) $(TARGET) boot/bootsect.bin boot/setup.bin kernel.bin
	$(PUT) $(TARGET) 36864 res/asc16
	
# tools/
tools/build : tools/build.cpp
	g++ tools/build.cpp -o tools/build
tools/put : tools/put.cpp
	g++ tools/put.cpp -o tools/put

init/head.o : init/head.S include/asm/macro.h
	$(CPP) init/head.S -o init/_head.s
	$(AS) init/_head.s -o init/head.o

%.o : %.s
	$(AS) $< -o $*.o
%.o : %.c
	$(CC) $(CFLAGS) $< -o $*.o

# boot/
boot/bootsect.bin : boot/bootsect.asm
	$(IAS) boot/bootsect.asm -o boot/bootsect.bin
boot/setup.bin : boot/setup.asm
	$(IAS) boot/setup.asm -o boot/setup.bin

kernel/kernel.o::
	(cd kernel; make)
drivers/drivers.o ::
	(cd drivers; make)

clean :
	-rm $(OBJS) $(TARGET)
	-rm boot/bootsect.bin boot/setup.bin
	-rm kernel.bin kernel.ld
	(cd kernel; make clean)
	(cd drivers; make clean)

dep :
	sed '/\#\#\# Dependencies/q' < Makefile > tmp_make
	(for i in init/*.c;do echo -n "init/";$(CPP) -M $$i;done) >> tmp_make
	cp tmp_make Makefile
	rm tmp_make
	(cd kernel; make dep)
	(cd drivers; make dep)

### Dependencies:
init/main.o: init/main.c include/video.h include/asm/system.h \
 include/sys_call.h
