# Makefile
OBJS = out/head.o out/main.o out/video.o \
	out/interrupt.o out/mouse.o \
	out/interrupts.o out/sched.o \
	out/keyboard.o out/gui.o out/gdt.o

TARGET = floppy.img

CC = gcc -fpack-struct -std=c99 -c -I . -I ./include

# Generate target file.
${TARGET} : ${OBJS} mkkernel font together out/bootsect.bin out/setup.bin
	ld -o out/kernel.ld -Ttext 0x90000 -e start ${OBJS}
	objcopy -R .note -R .comment -S -O binary out/kernel.ld out/kernel.bin
	./mkkernel ${TARGET} out/bootsect.bin out/setup.bin out/kernel.bin
	./font res/asc16 res/en.font res/hzk16f res/ch.font
	
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
out/head.o : boot/head.asm
	nasm -f elf boot/head.asm -o out/head.o
	
# asm/
out/interrupts.o : asm/interrupts.asm
	nasm -f elf asm/interrupts.asm -o out/interrupts.o

# init/
out/main.o : init/main.c include/kernel.h
	${CC} init/main.c -o out/main.o

# driver/
#       /video/
out/video.o : drivers/video/video.c include/kernel.h
	${CC} drivers/video/video.c -o out/video.o
#       /mouse/
out/mouse.o : drivers/mouse/mouse.c include/kernel.h include/asm/io.h
	${CC} drivers/mouse/mouse.c -o out/mouse.o
#       /keyboard/
out/keyboard.o : drivers/keyboard/keyboard.c include/kernel.h include/asm/io.h
	${CC} drivers/keyboard/keyboard.c -o out/keyboard.o

# kernel/
out/interrupt.o : kernel/interrupt.c include/kernel.h include/asm/io.h
	${CC} kernel/interrupt.c -o out/interrupt.o
out/sched.o : kernel/sched.c include/kernel.h include/asm/io.h
	${CC} kernel/sched.c -o out/sched.o
out/gdt.o : kernel/gdt.c
	${CC} kernel/gdt.c -o out/gdt.o
#       /gui
out/gui.o : kernel/gui/gui.c include/kernel.h
	${CC} kernel/gui/gui.c -o out/gui.o

.PHONY : clean
clean :
	-rm ${OBJS} ${TARGET} mkkernel font together res/en.font res/ch.font
