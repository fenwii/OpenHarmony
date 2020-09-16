OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)

SECTIONS
{
    . = SIZEOF_HEADERS;

    .hash       : { *(.hash) }          :text
    .dynsym     : { *(.dynsym) }
    .dynstr     : { *(.dynstr) }

    .dynamic    : { *(.dynamic) }       :text   :dynamic

    .rodata     : { *(.rodata*) }       :text

    .text       : { *(.text*) }         :text

    /DISCARD/   : {
        *(.data .data.* .sdata*)
        *(.bss .sbss .dynbss .dynsbss)
    }
}

PHDRS
{
    text        PT_LOAD     FLAGS(5) FILEHDR PHDRS;
    dynamic     PT_DYNAMIC  FLAGS(4);
}

VERSION
{
    OHOS {
    global:
        VdsoClockGettime;
    local: *;
    };
}
