
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
	. = 0x40700000;
	__image_copy_start =.;
	. = ALIGN(4);
	.text	:
	{
        __text_start = .;
		start.o (.text*)
		init_registers.o (.text*)
		lowlevel_init_v300.o (.text*)
		ddr_training_impl.o (.text*)
		ddr_training_console.o (.text*)
		ddr_training_ctl.o (.text*)
		ddr_training_boot.o (.text*)
		ddr_training_custom.o (.text*)
		uart.o (.text*)
		image_data.o (.text*)
        	startup.o(.text*)
        	reset.o(.text*)
        __init_end = .;
        ASSERT(((__init_end - __text_start) < 0x6000), "init sections too big!");
		*(.text*)
	}
	__text_end = .;

	. = ALIGN(4);
	.image : { *(.image) }

	. = ALIGN(4);
	.rodata : { *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*))) }

	. = ALIGN(4);
	.data : { *(.data) }

	. = ALIGN(4);
	.got : { *(.got) }

	. = ALIGN(4);
	__image_copy_end =.;
	__bss_start = .;
	.bss : { *(.bss) }
	__bss_end = .;
	_end = .;
}
