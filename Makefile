CPP_FLAGS=-ffreestanding -nostdlib -fno-rtti -fno-exceptions -fno-builtin -m32 -fno-pie -c

all:
	nasm -fbin bootblock.asm -o ./build/bootblock

	nasm -felf protected_mode.asm -o ./build/protected_mode.o

	g++ $(CPP_FLAGS) print.cpp -o ./build/print.o
	g++ $(CPP_FLAGS) panic.cpp -o ./build/panic.o 
	g++ $(CPP_FLAGS) interrupts_handler.cpp -o ./build/interrupts_handler.o
	g++ $(CPP_FLAGS) main.cpp -o ./build/main.o

	ld -T linker.ld -melf_i386 ./build/protected_mode.o ./build/print.o ./build/panic.o ./build/main.o -o ./build/kernel

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