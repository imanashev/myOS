all:
	nasm -fbin bootblock.asm
	dd if=/dev/zero of=disk.img bs=1M count=1
	dd if=bootblock of=disk.img bs=512 count=1 conv=notrunc

	dd if=sector1 of=disk.img bs=512 count=1 conv=notrunc seek=1
	dd if=sector2 of=disk.img bs=512 count=1 conv=notrunc seek=2
	dd if=sector3 of=disk.img bs=512 count=1 conv=notrunc seek=3

run:	
	echo 'c' | bochs -qf bochsrc

clean:
	rm -rf bootblock
	rm -rf disk.img