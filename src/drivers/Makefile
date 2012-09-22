# Makefile
OBJS = video/video.o
TARGET = drivers.o

LD = ld

${TARGET} : ${OBJS}
	${LD} -r -o ${TARGET} ${OBJS}

video/video.o :
	(cd video; make)

clean :
	-rm ${OBJS}
	(cd video; make clean)
	
dep :
	(cd video; make dep)
	
### Dependencies:
