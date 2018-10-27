all:
	nasm -fbin bootblock.asm
	nasm -fbin protected_mode.asm
	dd if=/dev/zero of=disk.img bs=1M count=1
	dd if=bootblock of=disk.img bs=512 count=1 conv=notrunc

	dd if=protected_mode of=disk.img bs=512 count=1 conv=notrunc seek=1

run:	
	echo 'c' | bochs -qf bochsrc

clean:
	rm -rf bootblock
	rm -rf protected_mode
	rm -rf disk.img