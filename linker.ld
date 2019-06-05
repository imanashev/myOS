OUTPUT_FORMAT(binary)
OUTPUT_ARCH(i386)

SECTIONS
{
    . = 0x7e00;
	.text  .  : {
	    ./build/protected_mode.o(.text) 
		*(EXCLUDE_FILE(./build/protected_mode.o) .text)
    }
	.data : {
        *(.data)
	    *(.rodata)
    }
	.bss : {
        *(.bss)
    }
}