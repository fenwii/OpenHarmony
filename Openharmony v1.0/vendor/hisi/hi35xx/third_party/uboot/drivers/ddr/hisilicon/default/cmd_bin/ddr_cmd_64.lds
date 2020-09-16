
OUTPUT_FORMAT("elf64-littleaarch64", "elf64-littleaarch64", "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
ENTRY(_start)
SECTIONS
{
	. = 0x00000000;

	. = ALIGN(8);
	.text	: {
		cmd_entry_64.o (.text)
		*(.text)
		}

	. = ALIGN(8);
	.rodata : { *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*))) }

	. = ALIGN(8);
	.data : { *(.data) }

	. = ALIGN(8);
	.got : { *(.got) }

	. = ALIGN(8);
	__bss_start = .;
	.bss : { *(.bss) }
	_end = .;
}
