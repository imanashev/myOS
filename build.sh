#!/bin/bash

nasm -fbin bootblock.asm
dd if=bootblock of=disk.img bs=512 count=1 conv=notrunc
echo 'c' | bochs -qf bochsrc