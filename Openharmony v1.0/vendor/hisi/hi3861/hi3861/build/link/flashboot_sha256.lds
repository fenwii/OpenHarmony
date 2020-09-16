OUTPUT_ARCH( "riscv" )
ENTRY(_start)

MEMORY
{
    /* FlashBoot location on Flash */
    FLASH (rwx) : ORIGIN = 0x400000+0x40, LENGTH = 32K-0x040-0x3C0
    /* ram for stack */
    STACK(xrw) : ORIGIN = 0x100000,LENGTH = 8K
    /* ram for common bss and data */
    SRAM(xrw) : ORIGIN = 0x100000+8K,LENGTH = 8K
    /* ram for fix rom bss and data */
    ROM_BSS_DATA(rx): ORIGIN = 0x100000+16K,LENGTH = 2K
    /* ram for code rom bss and data */
    CODE_ROM_BSS_DATA(rx): ORIGIN = 0x100000+18K,LENGTH = 2K
    /* signature */
    SIGN(rx): ORIGIN = 0x100000+40K,LENGTH = 0x040
    /* ram for flashboot */
    FLASH_BOOT(rx): ORIGIN = 0x100000+40K+0x040,LENGTH = 80K-0x040
    /* ram for heap */
    HEAP(xrw): ORIGIN = 0xdc000,LENGTH = 144K
    /* rom for fixed rom */
    FIXED_ROM(rx): ORIGIN = 0x00000000+11K,LENGTH = 21K
    /* rom for code rom */
    CODE_ROM(rx): ORIGIN = 0x003b8000+278K,LENGTH = 10K
}

SECTIONS
{
      /* The startup code goes first into FLASH */
    .text.entry : ALIGN(4)
    {
        KEEP(*(.text.entry))
    } > FLASH_BOOT AT>FLASH

    .rom.text :
    {
        . = ALIGN(4);
        KEEP(SORT(libbase.o)(.text*))
        KEEP(SORT(libbase.o)(.rodata*))
        . = ALIGN(4);
    } > FIXED_ROM

    .rom.code.text :
    {
        . = ALIGN(4);
        KEEP(SORT(libcodebase.o)(.text*))
        KEEP(SORT(libcodebase.o)(.rodata*))
        . = ALIGN(4);
    } > CODE_ROM

    /* Stack in SRAM at Highest addresses */
    .stacks (NOLOAD) :
    {
        . = ALIGN(4);
        __SYSTEM_STACK_BEGIN__ = ORIGIN(STACK);
        KEEP(*(.stacks))
        __SYSTEM_STACK_END__ = ORIGIN(STACK) + LENGTH(STACK);
    } > STACK
    __SYSTEM_STACK_SIZE__ = __SYSTEM_STACK_END__ - __SYSTEM_STACK_BEGIN__;
    __stack_top = __SYSTEM_STACK_END__;

    .rom.data :
    {
        . = ALIGN(4);
        __rom_copy_start = LOADADDR(.rom.data);
        . = ALIGN(4);
        __rom_copy_ram_start = .;
        __global_pointer$ = .;
        KEEP(SORT(libbase.o) (.data*))
        . = ALIGN(4);
        __rom_copy_ram_end = .;
    } > ROM_BSS_DATA AT>FIXED_ROM
    __rom_copy_size = __rom_copy_ram_end - __rom_copy_ram_start;

    .rom.code.data :
    {
        . = ALIGN(4);
        __code_rom_copy_start = LOADADDR(.rom.code.data);
        . = ALIGN(4);
        __code_rom_copy_ram_start = .;
        KEEP(SORT(libcodebase.o) (.data*))
        . = ALIGN(4);
        __code_rom_copy_ram_end = .;
    }>CODE_ROM_BSS_DATA AT>CODE_ROM
    __code_rom_copy_size = __code_rom_copy_ram_end - __code_rom_copy_ram_start;

    .rom.bss :
    {
        . = ALIGN(4);
        __rom_bss_start = .;
        KEEP(libbase.o (.bss))
        KEEP(libbase.o (.bss*))
        KEEP(libbase.o (COMMON))
        . = ALIGN(4);
        __rom_bss_end = .;
    } > ROM_BSS_DATA AT>FIXED_ROM

    .rom.code.bss :
    {
        . = ALIGN(4);
        __code_rom_bss_start = .;
        KEEP(libcodebase.o (.bss))
        KEEP(libcodebase.o (.bss*))
        KEEP(libcodebase.o (COMMON))
        . = ALIGN(4);
        __code_rom_bss_end = .;
    }>CODE_ROM_BSS_DATA AT>CODE_ROM

    .text : ALIGN(4)
    {
        __start_addr = .;
        *(.text*)
        . = ALIGN(4);
        __rodata_start = .;
        *(.rodata*)
        . = ALIGN(4);
        __rodata_end = .;
        __text_end = .;
    } > FLASH_BOOT AT>FLASH

    /* data section */
    .data : ALIGN(4)
    {
        __data_load = LOADADDR(.data);
        __data_start = .;
        *(.data*)
        . = ALIGN(4);
        __data_end = .;
    } > FLASH_BOOT AT>FLASH

    /* bss section */
    .bss (NOLOAD) : ALIGN(4)
    {
        __bss_begin__ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > FLASH_BOOT
    __bss_size__ = __bss_end__ - __bss_begin__;

    .heap (NOLOAD) :
    {
        . = ALIGN(4);
        __heap_begin__ = ORIGIN(HEAP);
        KEEP(*(.heap))
        __heap_end__ =  __heap_begin__ + LENGTH(HEAP);
    } > HEAP
}
