CPP_FLAGS=-ffreestanding -nostdlib -nodefaultlibs -nostartfiles -Wno-int-to-pointer-cast  -march=i386 -fno-rtti -fno-exceptions -fno-builtin -m32 -fno-pie -g

all:
	nasm -fbin bootblock.asm -o ./build/bootblock

	nasm -felf protected_mode.asm -o ./build/protected_mode.o
	nasm -felf interrupts.asm -o ./build/interrupts.o

	# g++ $(CPP_FLAGS) print.cpp -o ./build/print.o
	# g++ $(CPP_FLAGS) panic.cpp -o ./build/panic.o 
	# g++ $(CPP_FLAGS) isr.cpp -o ./build/isr.o
	# g++ $(CPP_FLAGS) idt.cpp ./build/interrupts.o -o ./build/idt.o	
	# g++ $(CPP_FLAGS) main.cpp -o ./build/main.o

	g++ $(CPP_FLAGS) -T linker.ld ./build/interrupts.o print.cpp panic.cpp isr.cpp idt.cpp main.cpp  -o ./build/kernel


	# ld -T linker.ld -melf_i386 ./build/protected_mode.o ./build/interrupts.o ./build/isr.o ./build/idt.o ./build/print.o ./build/panic.o ./build/main.o -o ./build/kernel
	# ld -T linker.ld -melf_i386 ./build/*.o -o ./build/kernel

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