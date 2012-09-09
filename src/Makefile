# Makefile
OBJS = out/head.o out/main.o out/video.o \
	out/interrupts.o out/sched.o \

TARGET = floppy.img
AS = as
LD = ld
CC = gcc
CFLAGS = -fpack-struct -std=c99 -c -Iinclude \
-Wall -O -fstrength-reduce -fomit-frame-pointer -nostdinc

# Generate target file.
${TARGET} : ${OBJS} mkkernel font together out/bootsect.bin out/setup.bin
	ld -o out/kernel.ld -Ttext 0x90000 -e start ${OBJS}
	objcopy -R .note -R .comment -S -O binary out/kernel.ld out/kernel.bin
	./mkkernel ${TARGET} out/bootsect.bin out/setup.bin out/kernel.bin
	
# tools/
mkkernel : tools/mkkernel.cpp
	g++ tools/mkkernel.cpp -o mkkernel
font : tools/font.cpp
	g++ tools/font.cpp -o font
together : tools/together.cpp
	g++ tools/together.cpp -o together

# boot/
out/bootsect.bin : boot/bootsect.asm
	nasm boot/bootsect.asm -o out/bootsect.bin
out/setup.bin : boot/setup.asm
	nasm boot/setup.asm -o out/setup.bin
# Note!! head.asm is in kernel.bin
#out/head.o : boot/head.asm
#	nasm -f elf boot/head.asm -o out/head.o
out/head.o : boot/head.s
	${AS} boot/head.s -o out/head.o
	
# asm/
out/interrupts.o : asm/interrupts.asm
	nasm -f elf asm/interrupts.asm -o out/interrupts.o

# init/
out/main.o : init/main.c \
			 include/video.h include/asm/system.h
	${CC} ${CFLAGS} init/main.c -o out/main.o

# driver/
#       /video/
out/video.o : drivers/video/video.c \
			  include/video.h
	${CC} ${CFLAGS} drivers/video/video.c -o out/video.o
#       /mouse/
#out/mouse.o : drivers/mouse/mouse.c \
#			  include/asm/io.h include/interrupt.h
#	${CC} ${CFLAGS} drivers/mouse/mouse.c -o out/mouse.o
#       /keyboard/
#out/keyboard.o : drivers/keyboard/keyboard.c \
#				 include/asm/io.h include/interrupt.h
#	${CC} ${CFLAGS} drivers/keyboard/keyboard.c -o out/keyboard.o

# kernel/
out/sched.o : kernel/sched.c \
			  include/asm/io.h include/ksched.h include/asm/system.h \
			  include/video.h include/asm/head.h
	${CC} ${CFLAGS} kernel/sched.c -o out/sched.o

.PHONY : clean
clean :
	-rm ${OBJS} ${TARGET} mkkernel font together
