#!/bin/bash

nasm -fbin bootblock.asm
dd if=bootblock of=disk.img bs=512 count=1 conv=notrunc
echo 'c' | bochs -qf bochsrc

# write file test on disk. seek=1 - skip 1 sektor
# dd if=test of=disk.img bs=512 count=1 conv=notrunc seek=1
