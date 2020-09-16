/*
 * (C) Copyright 2013
 * David Feng <fenghua@phytium.com.cn>
 *
 * (C) Copyright 2002
 * Gary Jennejohn, DENX Software Engineering, <garyj@denx.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

OUTPUT_FORMAT("elf64-littleaarch64", "elf64-littleaarch64", "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
ENTRY(_start)
SECTIONS
{
	. = 0x48700000;
	__image_copy_start =.;
	. = ALIGN(8);
	.text :
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
		div0.o (.text*)
		cache.o (.text*)
		cache_v8_hi3535av100.o (.text*)
		sdhci_boot.o (.text*)
		reset.o(.text*)
	__init_end = .;
	ASSERT(((__init_end - __text_start) < 0x7800), "init sections too big!");
		*(.text*)
	}

	. = ALIGN(8);
	.image : { *(.image) }

	. = ALIGN(8);
	.rodata : { *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*))) }

	. = ALIGN(8);
	.data : {
		*(.data*)
	}

	. = ALIGN(8);

	.got : { *(.got) }

	. = ALIGN(8);
	__image_copy_end =.;
	__bss_start = .;
	.bss :
	{
		*(.bss)
	}
	__bss_end = .;


	_end = .;
}
