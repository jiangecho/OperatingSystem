# Makefile
OBJS = intr_handler.o
TARGET = asm.o

AS = as
LD = ld
CPP = cpp -nostdinc -I../include

%.o : %.s
	$(AS) $< -o $*.o

$(TARGET) : $(OBJS)
	$(LD) -r -o $(TARGET) $(OBJS)

clean :
	-rm $(OBJS)