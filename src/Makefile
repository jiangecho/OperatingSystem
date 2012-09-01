# Makefile
objs = out/head.o out/main.o out/video.o \
	out/interrupt.o out/mouse.o out/impl.o \
	out/interrupts.o out/sched.o \
	out/keyboard.o out/gui.o

target = floppy.img

CC = gcc -fpack-struct -std=c99 -c -I . -I ./include

# Generate target file.
# First, we will link kernel module(using ld).
# Then get the binary of kernel module(using objcopy).
# Then generate floppy image.
# Finally generate font and add resource file.
${target} : ${objs} mkkernel font together out/bootsect.bin out/setup.bin
	ld -o out/kernel.ld -Ttext 0x90000 -e start ${objs}
	objcopy -R .note -R .comment -S -O binary out/kernel.ld out/kernel.bin
	./mkkernel ${target} out/bootsect.bin out/setup.bin out/kernel.bin
	./font res/asc16 res/en.font res/hzk16f res/ch.font
	
# Compile tools.
mkkernel : tools/mkkernel.cpp
	g++ tools/mkkernel.cpp -o mkkernel
font : tools/font.cpp
	g++ tools/font.cpp -o font
together : tools/together.cpp
	g++ tools/together.cpp -o together

# Compile boot module.
out/bootsect.bin : boot/bootsect.asm
	nasm boot/bootsect.asm -o out/bootsect.bin
out/setup.bin : boot/setup.asm
	nasm boot/setup.asm -o out/setup.bin

# Compile ASM files.
out/head.o : boot/head.asm
	nasm -f elf boot/head.asm -o out/head.o
out/interrupts.o : asm/interrupts.asm
	nasm -f elf asm/interrupts.asm -o out/interrupts.o

# Compile C files in init folder.
out/main.o : init/main.c include/kernel.h
	${CC} init/main.c -o out/main.o
# Compile C files in drivers folder.
out/video.o : drivers/video/video.c include/kernel.h
	${CC} drivers/video/video.c -o out/video.o
out/mouse.o : drivers/mouse/mouse.c include/kernel.h include/asm/io.h
	${CC} drivers/mouse/mouse.c -o out/mouse.o
out/keyboard.o : drivers/keyboard/keyboard.c include/kernel.h include/asm/io.h
	${CC} drivers/keyboard/keyboard.c -o out/keyboard.o
# Compile C files in kernel folder.
out/interrupt.o : kernel/interrupt.c include/kernel.h include/asm/io.h
	${CC} kernel/interrupt.c -o out/interrupt.o
out/gui.o : kernel/gui/gui.c include/kernel.h
	${CC} kernel/gui/gui.c -o out/gui.o
out/sched.o : kernel/sched.c include/kernel.h include/asm/io.h
	${CC} kernel/sched.c -o out/sched.o
# Compile C files in include folder.
out/impl.o : include/impl.c include/kernel.h
	gcc -I . -I ./include -fpack-struct -c include/impl.c -o out/impl.o

.PHONY : clean
clean :
	-rm ${objs} ${target} mkkernel font together res/en.font res/ch.font
