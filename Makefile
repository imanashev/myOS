# all:
# 	nasm -fbin bootblock.asm

# 	# nasm -fbin protected_mode.asm

# 	nasm -felf -o protected_mode.o protected_mode.asm
# 	gcc -m32 -fno-pie -nostdlib -nodefaultlibs -nostartfiles -fno-builtin -Wno-int-to-pointer-cast -march=i386 -c -o print.o print.c
# 	ld -T linker.ld -o protected_mode protected_mode.o print.o

# 	dd if=/dev/zero of=disk.img bs=1M count=1
	
# 	dd if=bootblock of=disk.img bs=512 count=1 conv=notrunc
# 	dd if=protected_mode of=disk.img bs=512 count=1 conv=notrunc seek=1

# run:	
# 	echo 'c' | bochs -qf bochsrc

# clean:
# 	rm -rf bootblock print.o protected_mode.o protected_mode
# 	rm -rf disk.img

all:
	nasm -fbin bootblock.asm

	nasm -felf -o protected_mode.o protected_mode.asm


	g++ -ffreestanding -nostdlib -fno-rtti -fno-exceptions -fno-builtin -m32 -c -o print.o print.cpp
	ld -T linker.ld -melf_i386 -o protected_mode protected_mode.o print.o


	# gcc -m32 -fno-pie -nostdlib -nodefaultlibs -nostartfiles -fno-builtin -Wno-int-to-pointer-cast -march=i386 -c -o print.o print.c
	# ld -T linker.ld -melf_i386 -o protected_mode protected_mode.o print.o



	dd if=/dev/zero of=disk.img bs=1M count=1

	dd if=bootblock of=disk.img bs=512 count=1 conv=notrunc
	dd if=protected_mode of=disk.img conv=notrunc seek=1
	# dd if=protected_mode of=disk.img skip=512 bs=512 count=1 conv=notrunc seek=2

run:	
	echo 'c' | bochs -qf bochsrc

clean:
	rm -rf bootblock print.o protected_mode.o protected_mode
	rm -rf disk.img