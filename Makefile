CPP_FLAGS=-ffreestanding -nostdlib -nodefaultlibs -nostartfiles -Wno-int-to-pointer-cast  -march=i386 -fno-rtti -fno-exceptions -fno-builtin -m32 -fno-pie

all:
	nasm -fbin bootblock.asm -o ./build/bootblock

	nasm -felf protected_mode.asm -o ./build/protected_mode.o
	nasm -felf interrupts.asm -o ./build/interrupts.o

	g++ $(CPP_FLAGS) -T linker.ld ./build/interrupts.o print.cpp panic.cpp isr.cpp idt.cpp main.cpp  -o ./build/kernel

	# create disk
	dd if=/dev/zero of=./build/disk.img bs=1M count=1

	# write on disk
	dd if=./build/bootblock of=./build/disk.img bs=512 count=1 conv=notrunc
	dd if=./build/kernel of=./build/disk.img conv=notrunc seek=1
	
run:	
	bochs -qf boch.conf

r:
	echo 'c' | bochs -qf bochs.conf

clean:
	rm -f ./build/*
