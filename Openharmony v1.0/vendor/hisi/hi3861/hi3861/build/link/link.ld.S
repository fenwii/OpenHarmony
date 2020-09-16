OUTPUT_ARCH( "riscv" )
ENTRY(_start)

#ifdef LOSCFG_DEBUG_KASAN
#define MAX_BIN_SIZE           3M
#else
#define MAX_BIN_SIZE           2M
#endif

#ifdef HI_BOARD_ASIC
#ifdef HI_ON_FLASH

#ifdef CONFIG_CHIP_PKT_48K
#define RAM_SIZE               264K /* PKT_B:48K */
#define RAM_START              0x000dc000 /* PKT_B:48K */
#else
#define RAM_SIZE               280K /* PKT_B:32K*/
#define RAM_START              0x000d8000 /* PKT_B:32K */
#endif

#else
#define RAM_SIZE               248K /* PKT_B:64K + NO DC */
#define RAM_START              0x000e0000 /* PKT_B:64K */
#endif
#else
#ifdef HI_ON_FLASH
#ifdef LOSCFG_DEBUG_KASAN
#define RAM_SIZE               896K
#else
#define RAM_SIZE               1M
#endif
#define RAM_START              0x00100000
#else
#define RAM_SIZE               248K /* PKT_B:64K + NO DC */
#define RAM_START              0x000e0000 /* PKT_B:64K */
#endif
#endif

#ifdef LOSCFG_DEBUG_KASAN
#define FLASH_SIZE             3M
#else
#define FLASH_SIZE             2M
#endif

#ifdef CONFIG_FLASH_ENCRYPT_SUPPORT
#define CRYPTO_RAM_LEN         4096
#endif

STACK_SIZE      = 2k;               /* needs to be calculated for your application */
IRQ_STACK_SIZE  = 3K;
EXC_STACK_SIZE  = 2K;
#if (defined CONFIG_TEE_HUKS_SUPPORT) || (defined CONFIG_TARGET_SIG_RSA_V15) || (defined CONFIG_TARGET_SIG_RSA_PSS) || (defined CONFIG_TARGET_SIG_ECC)
NMI_STACK_SIZE  = 2K;
#else
NMI_STACK_SIZE  = 0K;
#endif
DOWNLOAD_STACK_SIZE = 4K;
DOWNLOAD_IRQ_STACK_SIZE = 2K;

/* actually rom data0 size is 944 byte, when rom fixed, may all data can be placed in rom. */
#define ROM_DATA0_LEN          32     /* 32 bytes align */

#ifdef LOSCFG_DEBUG_KASAN
#define ROM_DATA1_LEN          5056   /* 32 bytes align */
#else
#define ROM_DATA1_LEN          2016   /* 32 bytes align */
#endif

#define ROM_BSS_LEN            11776  /* 32 bytes align */
#define PATCH_BSS_LEN          1024   /* 1024 bytes align */

#ifdef HI_ON_FLASH
#define SECURE_HEAD            0  /* iot has no Signature head */
#else
#define SECURE_HEAD            0x5A0  /* non-iot Signature lenth */
#endif

#define ROM_TEXT_LEN           (278K - ROM_DATA0_LEN)
#define CHECK_INFO_LEN         0x40
#if (defined HI_BOARD_ASIC) || (!defined HI_ON_FLASH)
#define STACK_LEN              (STACK_SIZE + IRQ_STACK_SIZE + EXC_STACK_SIZE + NMI_STACK_SIZE)
#endif

#define ROM_RAM_LEN            (ROM_DATA0_LEN + ROM_DATA1_LEN + ROM_BSS_LEN + CHECK_INFO_LEN)
#define ROM_RAM_START          (0x11DFFF - ROM_RAM_LEN + 1)
#define ROM_START              0x003b8000
#define FLASH_START            0x00400000
#define BIN_START              FLASH_FIRM_START /* The value of <FLASH_FIRM_START> macro is transfered by scons. And the value varies with the signature. */

#ifndef HI_BOARD_ASIC
/* only use in FPGA. */
#define RAM_FPGA_START         0x11E000
#define RAM_FPGA_LEN           (1M - 120K)
#endif

#if defined(ROM_BIN_TEST)
#define TEST_OFFSET            7
#else
#define TEST_OFFSET            0
#endif

#define ROM_TEXT_VMA           ROM_START

#define ROM_BSS_VMA            ROM_RAM_START
#define ROM_DATA0_VMA          (ROM_RAM_START + ROM_BSS_LEN)
#define ROM_DATA1_VMA          (ROM_DATA0_VMA + ROM_DATA0_LEN)
#define CHECK_INFO_VMA         (ROM_DATA1_VMA + ROM_DATA1_LEN)
#define PATCH_BSS_START        RAM_START
#ifdef CONFIG_FLASH_ENCRYPT_SUPPORT
#define CRYPTO_RAM_START       (PATCH_BSS_START + PATCH_BSS_LEN + SECURE_HEAD)
#define NON_ROM_RAM_START      (CRYPTO_RAM_START + CRYPTO_RAM_LEN)
#else
#define NON_ROM_RAM_START      (PATCH_BSS_START + PATCH_BSS_LEN + SECURE_HEAD)
#endif
#if (defined HI_BOARD_ASIC) || (!defined HI_ON_FLASH)
#define STACK_VMA              ROM_RAM_START - STACK_LEN
#endif

#define ROM_TEXT_LMA           (BIN_START - ROM_TEXT_LEN - ROM_DATA0_LEN)
#define ROM_DATA0_LMA          (ROM_TEXT_LMA + ROM_TEXT_LEN)

#ifdef HI_ON_FLASH
#define NON_ROM_TEXT_REGION     FLASH
#else
#define NON_ROM_TEXT_REGION     RAM
#endif

#ifdef CONFIG_FLASH_ENCRYPT_SUPPORT
#define RAM_CRYPTO_TEXT_LMA     (ROM_DATA0_LMA + ROM_DATA0_LEN)
#define NON_ROM_TEXT_LMA        (RAM_CRYPTO_TEXT_LMA + CRYPTO_RAM_LEN)
#else
#define NON_ROM_TEXT_LMA        (ROM_DATA0_LMA + ROM_DATA0_LEN)
#endif

#define ZINIT_NO_ROM_TEXT_LMA   ((NON_ROM_TEXT_LMA + SIZEOF (.text_non_rom) + (0x20) - 1) & ~ ((0x20) - 1))
#define RAM_TEXT_LMA            ((ZINIT_NO_ROM_TEXT_LMA + SIZEOF (.zInit) + (0x20) - 1) & ~ ((0x20) - 1))
#define NON_ROM_DATA_LMA        ((RAM_TEXT_LMA + SIZEOF (.ram_text) + (0x20) -1) & ~ ((0x20) - 1))
#define ROM_DATA1_LMA           ((NON_ROM_DATA_LMA + SIZEOF(.data) + (0x20) - 1) & ~ ((0x20) - 1))

#if (defined HI_BOARD_ASIC) || (!defined HI_ON_FLASH)

#ifdef CONFIG_FLASH_ENCRYPT_SUPPORT
#define RAM_LEN (RAM_SIZE - ROM_RAM_LEN - PATCH_BSS_LEN - STACK_LEN- SECURE_HEAD - CRYPTO_RAM_LEN)
#else
#define RAM_LEN (RAM_SIZE - ROM_RAM_LEN - PATCH_BSS_LEN - STACK_LEN - SECURE_HEAD)
#endif

#else
#define RAM_LEN (RAM_SIZE - ROM_RAM_LEN - PATCH_BSS_LEN - SECURE_HEAD)
#endif

#define KEEP_SORT_GCC_TEXT(obj) KEEP(SORT(*libgcc.a:obj)(.text*))
#define KEEP_SORT_GCC_RODATA(obj) KEEP(SORT(*libgcc.a:obj)(.rodata*))
#define KEEP_SORT_GCC_DATA(obj) KEEP(SORT(*libgcc.a:obj)(.data*))
#define KEEP_SORT_GCC_BSS(obj) KEEP(SORT(*libgcc.a:obj)(.bss*))
#define LIBGCC_ROM_FUN(func) func(save-restore.o) func(_clzsi2.o) func(_umoddi3.o) func(_clz.o) func(_ashldi3.o) func(_lshrdi3.o) func(fixdfsi.o) func(_udivdi3.o)

MEMORY
{
    BIN(rx) :          ORIGIN = BIN_START,           LENGTH = MAX_BIN_SIZE
    ROM_TEXT(rx) :     ORIGIN = ROM_TEXT_VMA,        LENGTH = ROM_TEXT_LEN        /* code and rodata of download,kernel,lib,bsp,wifi... */
    ROM_DATA0(rwx) :   ORIGIN = ROM_DATA0_VMA,       LENGTH = ROM_DATA0_LEN       /* data used by download rom code */
    ROM_DATA1(rwx) :   ORIGIN = ROM_DATA1_VMA,       LENGTH = 1768                /* data used by other rom code:1768 byte */
    ROM_BSS(rwx) :     ORIGIN = ROM_BSS_VMA,         LENGTH = ROM_BSS_LEN         /* bss used by rom code */
#if (defined HI_BOARD_ASIC) || (!defined HI_ON_FLASH)
    STACK(rw) :        ORIGIN = STACK_VMA,           LENGTH = STACK_LEN           /* stack */
#endif
    CHECK_INFO(rw) :   ORIGIN = CHECK_INFO_VMA,      LENGTH = CHECK_INFO_LEN      /* check info used by rom code */
#ifdef CONFIG_FLASH_ENCRYPT_SUPPORT
    FLASH(rwx) :       ORIGIN = FLASH_FIRM_START + CRYPTO_RAM_LEN,    LENGTH = FLASH_START + FLASH_SIZE - FLASH_FIRM_START - CRYPTO_RAM_LEN
#else
    FLASH(rwx) :       ORIGIN = FLASH_FIRM_START,    LENGTH = FLASH_START + FLASH_SIZE - FLASH_FIRM_START
#endif
    PATCH_BSS(rwx) :   ORIGIN = PATCH_BSS_START,     LENGTH = PATCH_BSS_LEN       /* flash patch remap */
#ifdef CONFIG_FLASH_ENCRYPT_SUPPORT
    CRYPTO_RAM(rwx) :  ORIGIN = CRYPTO_RAM_START,    LENGTH = CRYPTO_RAM_LEN      /* 4K kernel crypto */
#endif
    RAM(rwx) :         ORIGIN = NON_ROM_RAM_START,   LENGTH = RAM_LEN             /* non rom data,bss,stack,heap */
    EXTERN_ROM_DATA1_BSS(rwx) :        ORIGIN = 0x11dec8,   LENGTH = ROM_DATA1_LEN-1768    /* use extern rom data 1 as non_rom bss */
#if (defined HI_BOARD_FPGA) && (defined HI_ON_FLASH)
    RAM_FPGA(rwx) :    ORIGIN = RAM_FPGA_START,      LENGTH = RAM_FPGA_LEN        /* FPGA stack and heap */
#endif
}

SECTIONS
{
    .text_rom : AT (ROM_TEXT_LMA)
    {
        . = ALIGN(0x20);
        __rom_text_begin__ = .;
        __text_cache_start1_ = .;
        _rom_size_download_start = .;
        KEEP(SORT(*)(.text.download_entry))
        . = ALIGN(0x4);
        KEEP(SORT(*)(.text.trap_download_vector))
        KEEP(SORT(*)(.text.download_assemble))
        . = ALIGN(0x4);
        _rom_size_download_end = .;
        _rom_size_download = _rom_size_download_end - _rom_size_download_start;
        KEEP(SORT(libwifi_base.o)(.text*))
        KEEP(SORT(*)(.wifi.rom.text*))
        . = ALIGN(0x20);
        _rom_wifi_rom_end = .;
        _rom_size_libwifi = _rom_wifi_rom_end - _rom_size_download;
        KEEP(SORT(libbsp_base.o)(.text*))
        _rom_bsp_rom_end = .;
        _rom_size_libbsp = _rom_bsp_rom_end - _rom_wifi_rom_end;
        KEEP(SORT(liblitekernel_base.o)(.text*))
        _rom_kernel_rom_end = .;
        _rom_size_kernel = _rom_kernel_rom_end - _rom_bsp_rom_end;
        LIBGCC_ROM_FUN(KEEP_SORT_GCC_TEXT)
        _rom_libgcc_end = .;
        _rom_size_libgcc = _rom_libgcc_end - _rom_kernel_rom_end;
        KEEP(SORT(libc_base.o)(.text*))
        _rom_libc_rom_end = .;
        _rom_size_libc = _rom_libc_rom_end - _rom_libgcc_end;
        KEEP(SORT(libsec_base.o)(.text*))
        _rom_sec_rom_end = .;
        _rom_size_libsec = _rom_sec_rom_end - _rom_libc_rom_end;
        __text_cache_end1_ = .;
        KEEP(SORT(libwifi_base.o)(.rodata*))
        KEEP(SORT(*)(.wifi.rom.rodata*))
        . = ALIGN(0x4);
        _rom_hi1131_wifi_rom_rodata_end = .;
        _rom_size_rodata_wifi = _rom_hi1131_wifi_rom_rodata_end - _rom_sec_rom_end;
        KEEP(SORT(libbsp_base.o)(.rodata*))
        KEEP(SORT(*)(.bsp.rom.rodata))
        _rom_libbsp_rom_rodata_end = .;
        _rom_size_rodata_bsp = _rom_libbsp_rom_rodata_end - _rom_hi1131_wifi_rom_rodata_end;
        KEEP(SORT(liblitekernel_base.o)(.rodata*))
        _rom_litekenel_rom_rodata_end = .;
        _rom_size_rodata_kernel = _rom_litekenel_rom_rodata_end - _rom_size_rodata_bsp;
        LIBGCC_ROM_FUN(KEEP_SORT_GCC_RODATA)
        _rom_libgcc_rodata_end = .;
        _rom_size_rodata_libgcc = _rom_libgcc_rodata_end - _rom_litekenel_rom_rodata_end;
        KEEP(SORT(libc_base.o)(.rodata*))
        _rom_libcrom_rodata_end = .;
        _rom_size_rodata_libc = _rom_libcrom_rodata_end - _rom_libgcc_rodata_end;
        KEEP(SORT(libsec_base.o)(.rodata*))
        _rom_libsec_rom_rodata_end = .;
        _rom_size_rodata_sec = _rom_libsec_rom_rodata_end - _rom_libcrom_rodata_end;
        __rom_text_end__ = .;
    } > ROM_TEXT
    __rom_text_size__ = __rom_text_end__ - __rom_text_begin__;

    .data_rom0 : AT (ROM_DATA0_LMA)
    {
        . = ALIGN(0x20);
        __rom_data0_begin__ = .;
        KEEP(SORT(liblitekernel_base.o) (.data.kernel.rom*))
        KEEP(SORT(*)(.bsp.rom.data0))
        . = ALIGN(0x4);
        __rom_data0_end__ = .;
    } > ROM_DATA0
    __rom_data0_size__ = __rom_data0_end__ - __rom_data0_begin__;
    _rom_size_total = __rom_data0_size__ + __rom_text_size__;
    __rom_data0_load = ROM_TEXT_VMA + ROM_TEXT_LEN;

#if defined(CONFIG_FLASH_ENCRYPT_SUPPORT)
    .crypto_ram_text : AT (RAM_CRYPTO_TEXT_LMA)
    {
        __crypto_ram_text_load = LOADADDR(.crypto_ram_text);
        __crypto_ram_text_start = .;
        . = ALIGN(0x20);
        KEEP(*(.crypto.ram.text))
        . = ALIGN(0x20);
        __crypto_ram_text_end = .;
    } > CRYPTO_RAM
    __crypto_ram_text_size = __crypto_ram_text_end - __crypto_ram_text_start;
#endif

    .text_non_rom : AT (NON_ROM_TEXT_LMA)
    {
        . = ALIGN(0x20);
        __text_cache_start2_ = .;
        KEEP(*(.entry.text))
        . = ALIGN(0x20);
        #if defined(ROM_BIN_TEST)
        . += TEST_OFFSET;
        #endif
        SORT(*)(.init*)
        SORT(*)(.rom.text.patch)
        SORT(*)(EXCLUDE_FILE(*libasm_flash.o) .text*)
        /* temply add the following for hks. */
        SORT(*)(EXCLUDE_FILE(*libasm_flash.o) .got*)
        . = ALIGN(0x20);
        __text_cache_end2_ = .;
        SORT(*)(.rodata*)
        . = ALIGN(0x20);
        __text_rodata_end_ = .;
        . = ALIGN(0x20);
    } > NON_ROM_TEXT_REGION

    /* zInit code and data - will be freed after init */
    .zInit : AT (ADDR(.text_non_rom) + SIZEOF(.text_non_rom))
    {
       __zinitcall_bsp_start = .;
       KEEP (*(.zinitcall.bsp0.init))
       KEEP (*(.zinitcall.bsp1.init))
       KEEP (*(.zinitcall.bsp2.init))
       KEEP (*(.zinitcall.bsp3.init))
       KEEP (*(.zinitcall.bsp4.init))
       __zinitcall_bsp_end = .;
       __zinitcall_device_start = .;
       KEEP (*(.zinitcall.device0.init))
       KEEP (*(.zinitcall.device1.init))
       KEEP (*(.zinitcall.device2.init))
       KEEP (*(.zinitcall.device3.init))
       KEEP (*(.zinitcall.device4.init))
       __zinitcall_device_end = .;
       __zinitcall_core_start = .;
       KEEP (*(.zinitcall.core0.init))
       KEEP (*(.zinitcall.core1.init))
       KEEP (*(.zinitcall.core2.init))
       KEEP (*(.zinitcall.core3.init))
       KEEP (*(.zinitcall.core4.init))
       __zinitcall_core_end = .;
       __zinitcall_sys_service_start = .;
       KEEP (*(.zinitcall.sys.service0.init))
       KEEP (*(.zinitcall.sys.service1.init))
       KEEP (*(.zinitcall.sys.service2.init))
       KEEP (*(.zinitcall.sys.service3.init))
       KEEP (*(.zinitcall.sys.service4.init))
       __zinitcall_sys_service_end = .;
       __zinitcall_sys_feature_start = .;
       KEEP (*(.zinitcall.sys.feature0.init))
       KEEP (*(.zinitcall.sys.feature1.init))
       KEEP (*(.zinitcall.sys.feature2.init))
       KEEP (*(.zinitcall.sys.feature3.init))
       KEEP (*(.zinitcall.sys.feature4.init))
       __zinitcall_sys_feature_end = .;
       __zinitcall_run_start = .;
       KEEP (*(.zinitcall.run0.init))
       KEEP (*(.zinitcall.run1.init))
       KEEP (*(.zinitcall.run2.init))
       KEEP (*(.zinitcall.run3.init))
       KEEP (*(.zinitcall.run4.init))
       __zinitcall_run_end = .;
       __zinitcall_app_service_start = .;
       KEEP (*(.zinitcall.app.service0.init))
       KEEP (*(.zinitcall.app.service1.init))
       KEEP (*(.zinitcall.app.service2.init))
       KEEP (*(.zinitcall.app.service3.init))
       KEEP (*(.zinitcall.app.service4.init))
       __zinitcall_app_service_end = .;
       __zinitcall_app_feature_start = .;
       KEEP (*(.zinitcall.app.feature0.init))
       KEEP (*(.zinitcall.app.feature1.init))
       KEEP (*(.zinitcall.app.feature2.init))
       KEEP (*(.zinitcall.app.feature3.init))
       KEEP (*(.zinitcall.app.feature4.init))
       __zinitcall_app_feature_end = .;
       __zinitcall_test_start = .;
       KEEP (*(.zinitcall.test0.init))
       KEEP (*(.zinitcall.test1.init))
       KEEP (*(.zinitcall.test2.init))
       KEEP (*(.zinitcall.test3.init))
       KEEP (*(.zinitcall.test4.init))
       __zinitcall_test_end = .;
       __zinitcall_exit_start = .;
       KEEP (*(.zinitcall.exit0.init))
       KEEP (*(.zinitcall.exit1.init))
       KEEP (*(.zinitcall.exit2.init))
       KEEP (*(.zinitcall.exit3.init))
       KEEP (*(.zinitcall.exit4.init))
       __zinitcall_exit_end = .;
    } > NON_ROM_TEXT_REGION

    .ram_text : AT (RAM_TEXT_LMA)
    {
        __ram_text_load = LOADADDR(.ram_text);
        __ram_text_start = .;
        . = ALIGN(0x20);
        #if defined(ROM_BIN_TEST)
        . += TEST_OFFSET;
        #endif
        #if defined(HI1131TEST)
        KEEP(*(.trap_vector.text))
        KEEP(*(.kernel.ram.text))
        KEEP(*(.ram.kernel))
        KEEP(*(.bsp.ram.text))
        KEEP(SORT(libasm_flash.o)(.text*))
        #else
        SORT(*)(.trap_vector.text)
        SORT(*)(.kernel.ram.text)
        SORT(*)(.ram.kernel)
        SORT(*)(.bsp.ram.text)
        SORT(libasm_flash.o)(.text*)
        #endif
        . = ALIGN(0x20);
        __ram_text_end = .;
    } > RAM
    __ram_text_size = __ram_text_end - __ram_text_start;

    /* data section */
    .data : AT (NON_ROM_DATA_LMA)
    {
#if defined(HI_ON_FLASH)
        __data_load = LOADADDR(.data);
#else
        __data_load = LOADADDR(.data) - ORIGIN(FLASH) + ORIGIN(RAM);
#endif
       . = ALIGN(0x20);
        __data_start = .;
        #if defined(ROM_BIN_TEST)
        . += TEST_OFFSET;
        #endif
        SORT(*)(EXCLUDE_FILE(*liblitekernel_base.o *libc_base.o *libsec_base.o *libwifi_base.o *libbsp_base.o) .data*)
        SORT(*)(EXCLUDE_FILE(*.o) .wifi.rom.data*)
        SORT(*)(EXCLUDE_FILE(*.o) .data.system.rom*)
        SORT(*)(.rom.data.patch)
        SORT(*)(.sdata*)
        . = ALIGN(4);
        INCLUDE system_config.ld
        . = ALIGN(0x20);
        __data_end = .;
    } > RAM
    __data_size = __data_end - __data_start;

    .data_rom1 : AT (ROM_DATA1_LMA)
    {
#if defined(HI_ON_FLASH)
        __rom_data1_load = LOADADDR(.data_rom1);
#else
        __rom_data1_load = LOADADDR(.data_rom1) - ORIGIN(FLASH) + ORIGIN(RAM);
#endif
        . = ALIGN(0x20);
        __rom_data1_begin__ = .;
        LIBGCC_ROM_FUN(KEEP_SORT_GCC_DATA)
        KEEP(SORT(liblitekernel_base.o) (.data*))
        KEEP(SORT(libbsp_base.o) (.data*))
        KEEP(SORT(*)(.data.system.rom*))
        KEEP(SORT(libc_base.o) (.data*))
        KEEP(SORT(libsec_base.o) (.data*))
        KEEP(SORT(libwifi_base.o) (.data*))
        KEEP(SORT(*)(.wifi.rom.data*))
        . = ALIGN(4);
        __rom_data1_end__ = .;
    } > ROM_DATA1
    __rom_data1_size__ = __rom_data1_end__ - __rom_data1_begin__;

    /* used for fpb remap table g_fpbRemap declaration in los_fpb.c */
    .patch_bss (NOLOAD) :
    {
        __patch_bss_start = .;
        KEEP(SORT(*)(.fpb.remap))
        . = ALIGN(4);
        __patch_bss_end__ = .;
    } > PATCH_BSS

    .bss_rom (NOLOAD) :
    {
        . = ALIGN(0x20);
        __rom_bss_begin__ = .;
        __global_pointer$ = .;
        LIBGCC_ROM_FUN(KEEP_SORT_GCC_BSS)
        KEEP(SORT(liblitekernel_base.o )(.bss*))
        KEEP(SORT(libc_base.o)(.bss*))
        KEEP(SORT(libsec_base.o)(.bss*))
        KEEP(SORT(libbsp_base.o)(.bss*))
        KEEP(SORT(libwifi_base.o) (.bss*))
        KEEP(SORT(*)(.wifi.rom.bss*))
        . = ALIGN(4);
        __rom_bss_end__ = .;
        /* 原rom_bss未装满，额外添加非rom bss(1568 byte:1.53K) */
        SORT(*)(.extern.rom.bss*)
        . = ALIGN(4);
        __extern_rom_bss_end__ = .;
    } > ROM_BSS
    __rom_bss_size__ = __extern_rom_bss_end__ - __rom_bss_begin__;

    /* rom_data_extern1 section */
    .extern_rom_data1_bss (NOLOAD) :
    {
	   . = ALIGN(0x20);
       __extern_rom_data1_bss_begin__ = .;
        #if defined(ROM_BIN_TEST)
        . += TEST_OFFSET;
        #endif
        SORT(*)(.extern.rom.data1.bss*)
        . = ALIGN(4);
        __extern_rom_data1_bss_end__ = .;
    } > EXTERN_ROM_DATA1_BSS
    __extern_rom_data1_bss_size__ = __extern_rom_data1_bss_end__ - __extern_rom_data1_bss_begin__;

    __RAM_BEGIN__ = ORIGIN(RAM);
    __RAM_SIZE__ = LENGTH(RAM);
    __DOWNLOAD_IRQ_STACK = ORIGIN(ROM_BSS) - DOWNLOAD_STACK_SIZE; /* overlap with STACK*/
    __DOWNLOAD_STACK_END = ORIGIN(ROM_BSS); /* relate to KERNEL_MALLOC_STAR_ADDR and KERNEL_MALLOC_END_ADDR */

    /* bss section */
#ifdef LOSCFG_DEBUG_KASAN
    .bss (NOLOAD) : ALIGN(0x20)
    {
        . = ALIGN(0x20);
        __bss_begin = .;
        #if defined(ROM_BIN_TEST)
        . += TEST_OFFSET;
        #endif
        SORT(*)(.bss*)
        SORT(*)(.rom.bss.patch)
        SORT(*)(.sbss*)
        . = ALIGN(0x20);
        __bss_end = .;
    } > RAM_FPGA
#else
    .bss (NOLOAD) : ALIGN(0x20)
    {
        . = ALIGN(0x20);
        __bss_begin = .;
        #if defined(ROM_BIN_TEST)
        . += TEST_OFFSET;
        #endif
        SORT(*)(.bss*)
        SORT(*)(.rom.bss.patch)
        SORT(*)(.sbss*)
        . = ALIGN(0x20);
        __bss_end = .;
    } > RAM
#endif
    __bss_size__ = __bss_end - __bss_begin;

    /* End of uninitialized data segment */
    _end = .;
#if (defined HI_BOARD_ASIC) || (!defined HI_ON_FLASH)
    .heap (NOLOAD) :
    {
        . = ALIGN(64);
        __HEAP_BEGIN__ = ABSOLUTE(.);
    } > RAM
    __HEAP_SIZE__  = (__RAM_BEGIN__ + __RAM_SIZE__) - __HEAP_BEGIN__;

    .stack (NOLOAD) : ALIGN(0x20)
    {
        __SYSTEM_STACK_BEGIN__ = .;
        . += STACK_SIZE;
        __SYSTEM_STACK_END__ = .;
        . = ALIGN(0x20);
        __irq_stack_bottom = .;
        . += IRQ_STACK_SIZE;
        __irq_stack_top = .;
	. = ALIGN(0x20);
        __nmi_stack_bottom = .;
        . += NMI_STACK_SIZE;
        __nmi_stack_top = .;
        . = ALIGN(0x20);
        __exc_stack_bottom = .;
        . += EXC_STACK_SIZE;
        __exc_stack_top = .;
    } > STACK
    __SYSTEM_STACK_SIZE__ = __SYSTEM_STACK_END__ - __SYSTEM_STACK_BEGIN__;

    .check_info (NOLOAD) :
    {
        __check_info_addr = .;
        KEEP(SORT(*)(.lowpower.ram.bss*))
    } > CHECK_INFO
#else
    .stack (NOLOAD) : ALIGN(0x20)
    {
        __SYSTEM_STACK_BEGIN__ = .;
        . += STACK_SIZE;
        __SYSTEM_STACK_END__ = .;
        . = ALIGN(0x20);
        __irq_stack_bottom = .;
        . += IRQ_STACK_SIZE;
        __irq_stack_top = .;
        . = ALIGN(0x20);
        __nmi_stack_bottom = .;
        . += NMI_STACK_SIZE;
        __nmi_stack_top = .;
        __exc_stack_bottom = .;
        . += EXC_STACK_SIZE;
        __exc_stack_top = .;
        . = ALIGN(0x20);
    } > RAM_FPGA
    __SYSTEM_STACK_SIZE__ = __SYSTEM_STACK_END__ - __SYSTEM_STACK_BEGIN__;

    .heap (NOLOAD) :
    {
        . = ALIGN(64);
        __HEAP_BEGIN__ = ABSOLUTE(.);
    } > RAM_FPGA
    __HEAP_SIZE__  = (RAM_FPGA_START + RAM_FPGA_LEN) - __HEAP_BEGIN__;

    .check_info (NOLOAD) :
    {
        __check_info_addr = .;
        KEEP(SORT(*)(.lowpower.ram.bss*))
    } > CHECK_INFO
#endif
    __ram_start = RAM_START;
    __ram_end = RAM_START + RAM_SIZE;
    . = ALIGN(4);
    end = . ;
}

