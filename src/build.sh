#!/bin/sh
if [ $# != 1 ]; then
	current=$(pwd)
else 
	current=$1
fi
touch tmp_make
rm Makefile # remove old file
printf 'TARGET = target.o\n' >> Makefile
printf 'OBJS = ' >> Makefile
for file in *.c; do
	if [ $file != "*.c" ]; then
		printf "${file%.*}.o " >> Makefile
	fi
done
for file in *.S; do
	if [ $file != "*.S" ]; then
		printf "${file%.*}.o " >> Makefile
	fi
done
for file in *; do
	if [ -d $file ]; then
		if [ $file != "include" ]; then
			printf $file'/target.o ' >> Makefile
			printf $file'/target.o::\n' >> tmp_make
			printf '	(cd '$file';make dep;make)\n' >> tmp_make
			cd $file
			../build.sh $current
			cd ..
		fi
	fi
done
printf '\n' >> Makefile

echo 'AS = as' >> Makefile
echo 'LD = i586-elf-ld' >> Makefile
echo 'CC = i586-elf-gcc' >> Makefile
echo 'CPP = gcc -E -nostdinc -I'$current'/include' >> Makefile
echo 'CFLAGS = -fpack-struct -std=c99 -c -I'$current'/include \' >> Makefile
echo '-Wall -O -fstrength-reduce -fomit-frame-pointer \' >> Makefile
echo '-nostdinc -nostdlib -fno-builtin -nostartfiles \' >> Makefile
echo '-nodefaultlibs' >> Makefile
echo '%.o : %.c' >> Makefile
echo '	$(CC) $(CFLAGS) $< -o $*.o' >> Makefile
echo '%.o : %.S' >> Makefile
echo '	$(CPP) $< -o _$*.s' >> Makefile
echo '	$(AS) _$*.s -o $*.o' >> Makefile

echo '$(TARGET):$(OBJS)' >> Makefile
if [ $# != 1 ]; then
	echo '	$(LD) $(OBJS) -T linker.ld -o $(TARGET)' >> Makefile
else
	echo '	$(LD) -r -o $(TARGET) $(OBJS)' >> Makefile
fi

cat tmp_make >> Makefile
rm tmp_make

echo 'clean:' >> Makefile
echo '	-rm $(OBJS) $(TARGET)' >> Makefile
if [ $# != 1 ]; then
	echo '	-rm kernel.bin' >> Makefile
fi

echo 'dep:' >> Makefile
echo "	sed '/\#\#\# Dependencies/q' < Makefile > tmp_make" >> Makefile
echo '	(for i in *.c;do $(CPP) -M $$i;done) >> tmp_make' >> Makefile
echo '	(for i in *.S;do $(CPP) -M $$i;done) >> tmp_make' >> Makefile
echo '	cp tmp_make Makefile' >> Makefile
echo '	rm tmp_make' >> Makefile

echo '### Dependencies:' >> Makefile

make
