
ENTRY(reset_vector)
INCLUDE board.ld
INPUT(libuserinit.O)
SECTIONS
{
     _start = .;
    .set_sysinit_set : {
        __start_set_sysinit_set = ABSOLUTE(.);
        KEEP (*(.set_sysinit_set))
        __stop_set_sysinit_set = ABSOLUTE(.);
    } > ram

    .got ALIGN(0x4) : { *(.got.plt) *(.got) } > ram

    .ctors : ALIGN(0x4) {
        __ctor_list__ = .;
        KEEP (*(.ctors .init_array))
        __ctor_end__ = .;
    } > ram
    .dtors : ALIGN(0x4) {
        __dtor_list__ = .;
        KEEP (*(.dtors .fini_array))
        __dtor_end__ = .;
    } > ram

    .gcc_except_table ALIGN (0x8) : { . = .; } > ram  .gcc_except_table : { KEEP(*(.gcc_except_table*)) }
    .exception_ranges ALIGN (0x8) : ONLY_IF_RW { *(.exception_ranges .exception_ranges*) } > ram

    .ARM.extab ALIGN(0x4) : { *(.ARM.extab* .gnu.linkonce.armextab.*) } > ram

    /* .ARM.exidx is sorted, so has to go in its own output section.  */
    /*.ARM.exidx ALIGN(0x8) : { __exidx_start = .; *(.ARM.exidx* .gnu.linkonce.armexidx.*) ;__exidx_end = .;} > ram*/
    .ARM.exidx ALIGN(0x8) : { __exidx_start = .; __exidx_end = .;} > ram

     .eh_frame ALIGN (0x8) : { KEEP (*(.eh_frame)) *(.eh_frame.*);  } > ram

    /* text/read-only data */
    .text : ALIGN(0x1000) {
        __text_start = .;
        *(.text* .sram.text.glue_7* .gnu.linkonce.t.*)
    } > ram

    .rel.text : { *(.rel.text) *(.rel.text.*) *(.rel.gnu.linkonce.t*) } > ram
    .rela.text : { *(.rela.text) *(.rela.text.*) *(.rela.gnu.linkonce.t*) } > ram
    .rel.data : { *(.rel.data) *(.rel.data.*) *(.rel.gnu.linkonce.d*) } > ram
    .rela.data : { *(.rela.data) *(.rela.data.*) *(.rela.gnu.linkonce.d*) } > ram
    .rel.rodata : { *(.rel.rodata) *(.rel.rodata.*) *(.rel.gnu.linkonce.r*) } > ram
    .rela.rodata : { *(.rela.rodata) *(.rela.rodata.*) *(.rela.gnu.linkonce.r*) } > ram
    .rel.got : { *(.rel.got) } > ram
    .rela.got : { *(.rela.got) } > ram
    .rel.ctors : { *(.rel.ctors) } > ram
    .rela.ctors : { *(.rela.ctors) } > ram
    .rel.dtors : { *(.rel.dtors) } > ram
    .rela.dtors : { *(.rela.dtors) } > ram
    .rel.init : { *(.rel.init) } > ram
    .rela.init : { *(.rela.init) } > ram
    .rel.fini : { *(.rel.fini) } > ram
    .rela.fini : { *(.rela.fini) } > ram
    .rel.bss : { *(.rel.bss) } > ram
    .rela.bss : { *(.rela.bss) } > ram
    .rel.plt : { *(.rel.plt) } > ram
    .rela.plt : { *(.rela.plt) } > ram
    .rel.dyn : { *(.rel.dyn) } > ram

    .dummy_post_text : {
        __text_end = .;
    } > ram

    .rodata : ALIGN(0x1000) {
        __rodata_start = .;
        *(.rodata .rodata.* .gnu.linkonce.r.*)
        __exc_table_start = .;
        KEEP(*(__exc_table))
        __exc_table_end = .;
    } > ram

    /*
     * extra linker scripts tend to insert sections just after .rodata,
     * so we want to make sure this symbol comes after anything inserted above,
     * but not aligned to the next section necessarily.
     */
    .dummy_post_rodata : {
        _hdf_drivers_start = .;
        KEEP(*(.hdf.driver))
        _hdf_drivers_end = .;
        __rodata_end = .;
    } > ram

    .data : ALIGN(0x1000) {
        /* writable data  */
        __ram_data_start = .;
        __vdso_data_start = LOADADDR(.data);
        KEEP(*(.data.vdso.datapage))
        . = ALIGN(0x1000);
        KEEP(*(.data.vdso.text))
        . = ALIGN(0x1000);
        __vdso_text_end = .;
        *(.data .data.* .gnu.linkonce.d.*)
        . = ALIGN(0x4);
        KEEP(*( SORT (.liteos.table.*)));
    } > ram

    /*
     * extra linker scripts tend to insert sections just after .data,
     * so we want to make sure this symbol comes after anything inserted above,
     * but not aligned to the next section necessarily.
     */
    .dummy_post_data : {
        __ram_data_end = .;
    } > ram

    .user_init : ALIGN(0x1000) {
        . = ALIGN(0x4);
        __user_init_load_addr = LOADADDR(.user_init);
        __user_init_entry = .;
        KEEP(*(.user.entry))
        KEEP(*(.user.text))
        KEEP(*(.user.rodata))
        . = ALIGN(0X4);
        __user_init_data = .;
        KEEP(*(.user.data))
        . = ALIGN(0X4);
        __user_init_bss = .;
        KEEP(*(.user.bss))
        . = ALIGN(0x1000);
        __user_init_end = .;
    } > user_ram AT > ram

    __user_init_size = __user_init_end - __user_init_entry;

    /* unintialized data (in same segment as writable data) */
    .bss : {
        . = ALIGN(0x800);
        __int_stack_start = .;
        *(.int_stack);
        . = ALIGN(0x4);
        KEEP(*(.bss.prebss.*))
        . = ALIGN(0x8);
        __bss_start = .;
        *(.bss .bss.*)
        *(.gnu.linkonce.b.*)
        *(COMMON)
        . = ALIGN(0x8);
        __bss_end = .;
    } > ram

    . = ALIGN(0x1000);
    _end = .;
    /* mmu temp page table(sys aviliable mem is start with __bss_end) */
    . = ALIGN(0x4000);
    __mmu_ttlb_begin = .;

    /* Strip unnecessary stuff */
    /DISCARD/ 0 : { *(.comment .note .ARM.exidx* .gnu.linkonce.armexidx.*) } > ram
}
