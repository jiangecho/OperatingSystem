# Makefile
OBJS = vesa.o vesa_util.o
TARGET = video.o

AS = as
LD = ld
CC = gcc
CPP = cpp -nostdinc -I../../include
CFLAGS = -fpack-struct -std=c99 -c -I../../include \
-Wall -O -fstrength-reduce -fomit-frame-pointer -nostdinc

.s.o:
	${AS} $< -o $*.o
.c.o:
	${CC} ${CFLAGS} $< -o $*.o

${TARGET} : ${OBJS}
	${LD} -r -o ${TARGET} ${OBJS}

clean :
	-rm ${OBJS}

dep:
	sed '/\#\#\# Dependencies/q' < Makefile > tmp_make
	(for i in *.c;do ${CPP} -M $$i;done) >> tmp_make
	cp tmp_make Makefile
	rm tmp_make
	
### Dependencies:
vesa.o: vesa.c ../../include/video.h
vesa_util.o: vesa_util.c ../../include/video.h
