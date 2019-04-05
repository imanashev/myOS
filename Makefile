all:
	nasm -fbin bootblock.asm

	nasm -felf -o protected_mode.o protected_mode.asm

	g++ -ffreestanding -nostdlib -fno-rtti -fno-exceptions -fno-builtin -m32 -fno-pie -c -o print.o print.cpp
	g++ -ffreestanding -nostdlib -fno-rtti -fno-exceptions -fno-builtin -m32 -fno-pie -c -o panic.o panic.cpp
	g++ -ffreestanding -nostdlib -fno-rtti -fno-exceptions -fno-builtin -m32 -fno-pie -c -o interrupts_handler.o interrupts_handler.cpp
	g++ -ffreestanding -nostdlib -fno-rtti -fno-exceptions -fno-builtin -m32 -fno-pie -c -o main.o main.cpp

	ld -T linker.ld -melf_i386 -o protected_mode protected_mode.o print.o panic.o main.o

	# create disk
	dd if=/dev/zero of=disk.img bs=1M count=1

	# write on disk
	dd if=bootblock of=disk.img bs=512 count=1 conv=notrunc
	dd if=protected_mode of=disk.img conv=notrunc seek=1
	
run:	
	echo 'c' | bochs -qf bochsrc

clean:
	rm -rf bootblock print.o protected_mode.o protected_mode
	rm -rf disk.img