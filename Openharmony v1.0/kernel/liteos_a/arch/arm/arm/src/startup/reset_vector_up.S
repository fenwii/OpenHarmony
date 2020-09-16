/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define  ASSEMBLY
#include "arch_config.h"
#include "los_vm_boot.h"
#include "los_vm_zone.h"
#include "los_mmu_descriptor_v6.h"
#undef ASSEMBLY


    .global __exc_stack_top
    .global __irq_stack_top
    .global __fiq_stack_top
    .global __svc_stack_top
    .global __abt_stack_top
    .global __undef_stack_top
    .global __exc_stack
    .global __irq_stack
    .global __fiq_stack
    .global __svc_stack
    .global __abt_stack
    .global __undef_stack

    .extern __bss_start
    .extern __bss_end
    .extern hal_clock_initialize_start
    .extern los_bss_init
    .extern _osExceptFiqHdl
    .extern _osExceptAddrAbortHdl
    .extern _osExceptDataAbortHdl
    .extern _osExceptPrefetchAbortHdl
    .extern _osExceptSwiHdl
    .extern _osExceptUndefInstrHdl
    .extern __stack_chk_guard_setup
    .extern g_firstPageTable
    .extern g_mmuJumpPageTable

    .equ MPIDR_CPUID_MASK, 0xffU

    .fpu vfpv4
    .arm

/* param0 is stack bottom, param1 is stack size, r11 hold cpu id */
.macro EXC_SP_SET param0, param1
    ldr    r1, =\param0
    mov    r0, \param1
    bl     sp_set
.endm

/* param0 is stack top, param1 is stack size, param2 is magic num */
.macro STACK_MAGIC_SET param0, param1, param2
    ldr     r0, =\param0
    mov     r1, \param1
    ldr     r2, =\param2
    bl      excstack_magic
.endm

/* param0 is physical address, param1 virtual address, param2 is sizes, param3 is flag */
.macro PAGE_TABLE_SET param0, param1, param2, param3
    ldr     r6, =\param0
    ldr     r7, =\param1
    ldr     r8, =\param2
    ldr     r10, =\param3
    bl      page_table_build
.endm
    .code   32
    .section ".vectors","ax"

__exception_handlers:
    /*
    *Assumption:  ROM code has these vectors at the hardware reset address.
    *A simple jump removes any address-space dependencies [i.e. safer]
    */
    b   reset_vector
    b   _osExceptUndefInstrHdl
    b   _osExceptSwiHdl
    b   _osExceptPrefetchAbortHdl
    b   _osExceptDataAbortHdl
    b   _osExceptAddrAbortHdl
    b   OsIrqHandler
    b   _osExceptFiqHdl

    /* Startup code which will get the machine into supervisor mode */
    .global reset_vector
    .type   reset_vector,function
reset_vector:
    /* do some early cpu setup: i/d cache disable, mmu disabled */
    mrc     p15, 0, r0, c1, c0, 0
    bic     r0, #(1<<12)
    bic     r0, #(1<<2 | 1<<0)
    mcr     p15, 0, r0, c1, c0, 0

    /* r11: delta of physical address and virtual address */
    adr     r11, pa_va_offset
    ldr     r0, [r11]
    sub     r11, r11, r0

    /* if we need to relocate to proper location or not */
    adr     r4, __exception_handlers            /* r4: base of load address */
    ldr     r5, =SYS_MEM_BASE                   /* r5: base of physical address */
    subs    r12, r4, r5                         /* r12: delta of load address and physical address */
    beq     reloc_img_to_bottom_done            /* if we load image at the bottom of physical address */

    /* we need to relocate image at the bottom of physical address */
    ldr     r7, =__exception_handlers           /* r7: base of linked address (or vm address) */
    ldr     r6, =__bss_start                    /* r6: end of linked address (or vm address) */
    sub     r6, r7                              /* r6: delta of linked address (or vm address) */
    add     r6, r4                              /* r6: end of load address */

reloc_img_to_bottom_loop:
    ldr     r7, [r4], #4
    str     r7, [r5], #4
    cmp     r4, r6
    bne     reloc_img_to_bottom_loop
    sub     pc, r12
    nop
    sub     r11, r11, r12                       /* r11: eventual address offset */

reloc_img_to_bottom_done:
    ldr     r4, =g_firstPageTable               /* r4: physical address of translation table and clear it */
    add     r4, r4, r11
    bl      page_table_clear

    PAGE_TABLE_SET SYS_MEM_BASE, KERNEL_VMM_BASE, KERNEL_VMM_SIZE, MMU_DESCRIPTOR_KERNEL_L1_PTE_FLAGS
    PAGE_TABLE_SET SYS_MEM_BASE, UNCACHED_VMM_BASE, UNCACHED_VMM_SIZE, MMU_INITIAL_MAP_STRONGLY_ORDERED
    PAGE_TABLE_SET PERIPH_PMM_BASE, PERIPH_DEVICE_BASE, PERIPH_DEVICE_SIZE, MMU_INITIAL_MAP_DEVICE
    PAGE_TABLE_SET PERIPH_PMM_BASE, PERIPH_CACHED_BASE, PERIPH_CACHED_SIZE, MMU_DESCRIPTOR_KERNEL_L1_PTE_FLAGS
    PAGE_TABLE_SET PERIPH_PMM_BASE, PERIPH_UNCACHED_BASE, PERIPH_UNCACHED_SIZE, MMU_INITIAL_MAP_STRONGLY_ORDERED

    orr     r8, r4, #MMU_TTBRx_FLAGS            /* r8 = r4 and set cacheable attributes on translation walk */
    ldr     r4, =g_mmuJumpPageTable             /* r4: jump pagetable vaddr */
    add     r4, r4, r11
    ldr     r4, [r4]
    add     r4, r4, r11                         /* r4: jump pagetable paddr */
    bl      page_table_clear

    /* build 1M section mapping, in order to jump va during turing on mmu:pa == pa, va == pa */
    mov     r6, pc
    mov     r7, r6                              /* r7: pa (MB aligned)*/
    lsr     r6, r6, #20                         /* r6: va l1 index */
    ldr     r10, =MMU_DESCRIPTOR_KERNEL_L1_PTE_FLAGS
    add     r12, r10, r6, lsl #20               /* r12: pa |flags */
    str     r12, [r4, r7, lsr #(20 - 2)]        /* jumpTable[paIndex] = pt entry */
    rsb     r7, r11, r6, lsl #20                /* r7: va */
    str     r12, [r4, r7, lsr #(20 - 2)]        /* jumpTable[vaIndex] = pt entry */

    bl      mmu_setup                           /* set up the mmu */

    /* get cpuid and keep it in r11 */
    mrc     p15, 0, r11, c0, c0, 5
    and     r11, r11, #MPIDR_CPUID_MASK
    cmp     r11, #0
    bne     excstatck_loop_done

excstatck_loop:
    /* clear out the interrupt and exception stack and set magic num to check the overflow */
    ldr     r0, =__undef_stack
    ldr     r1, =__exc_stack_top
    bl      stack_init

    STACK_MAGIC_SET __undef_stack, #OS_EXC_UNDEF_STACK_SIZE, OS_STACK_MAGIC_WORD
    STACK_MAGIC_SET __abt_stack, #OS_EXC_ABT_STACK_SIZE, OS_STACK_MAGIC_WORD
    STACK_MAGIC_SET __irq_stack, #OS_EXC_IRQ_STACK_SIZE, OS_STACK_MAGIC_WORD
    STACK_MAGIC_SET __fiq_stack, #OS_EXC_FIQ_STACK_SIZE, OS_STACK_MAGIC_WORD
    STACK_MAGIC_SET __svc_stack, #OS_EXC_SVC_STACK_SIZE, OS_STACK_MAGIC_WORD
    STACK_MAGIC_SET __exc_stack, #OS_EXC_STACK_SIZE, OS_STACK_MAGIC_WORD

excstatck_loop_done:
warm_reset:
    /* initialize interrupt/exception environments */
    mov    r0, #(CPSR_IRQ_DISABLE |CPSR_FIQ_DISABLE|CPSR_IRQ_MODE)
    msr    cpsr, r0
    EXC_SP_SET __irq_stack_top, #OS_EXC_IRQ_STACK_SIZE

    mov    r0, #(CPSR_IRQ_DISABLE|CPSR_FIQ_DISABLE|CPSR_UNDEF_MODE)
    msr    cpsr, r0
    EXC_SP_SET __undef_stack_top, #OS_EXC_UNDEF_STACK_SIZE

    mov    r0, #(CPSR_IRQ_DISABLE|CPSR_FIQ_DISABLE|CPSR_ABT_MODE)
    msr    cpsr, r0
    EXC_SP_SET __abt_stack_top, #OS_EXC_ABT_STACK_SIZE

    mov    r0, #(CPSR_IRQ_DISABLE|CPSR_FIQ_DISABLE|CPSR_FIQ_MODE)
    msr    cpsr, r0
    EXC_SP_SET __fiq_stack_top, #OS_EXC_FIQ_STACK_SIZE

    /* initialize CPSR (machine state register) */
    mov    r0, #(CPSR_IRQ_DISABLE|CPSR_FIQ_DISABLE|CPSR_SVC_MODE)
    msr    cpsr, r0

    /* Note: some functions in LIBGCC1 will cause a "restore from SPSR"!! */
    msr    spsr, r0

    /* set svc stack, every cpu has OS_EXC_SVC_STACK_SIZE stack */
    ldr    r0, =__svc_stack_top
    mov    r2, #OS_EXC_SVC_STACK_SIZE
    mul    r2, r2, r11
    sub    r0, r0, r2
    mov    sp, r0

    /* enable fpu+neon */
    MRC    p15, 0, r0, c1, c1, 2
    ORR    r0, r0, #0xC00
    BIC    r0, r0, #0xC000
    MCR    p15, 0, r0, c1, c1, 2

    LDR    r0, =(0xF << 20)
    MCR    p15, 0, r0, c1, c0, 2

    MOV    r3, #0x40000000
    VMSR   FPEXC, r3

    LDR    r0, =__exception_handlers
    MCR    p15, 0, r0, c12, c0, 0

    cmp    r11, #0
    bne    cpu_start

clear_bss:
    ldr    r1, =__bss_start
    ldr    r2, =__bss_end
    mov    r0, #0

bss_loop:
    cmp    r1, r2
    strlo  r0, [r1], #4
    blo    bss_loop

#if defined(LOSCFG_CC_STACKPROTECTOR_ALL) || \
    defined(LOSCFG_CC_STACKPROTECTOR_STRONG) || \
    defined(LOSCFG_CC_STACKPROTECTOR)
    bl     __stack_chk_guard_setup
#endif

#ifdef LOSCFG_GDB_DEBUG
    /* GDB_START - generate a compiled_breadk,This function will get GDB stubs started, with a proper environment */
    bl     GDB_START
    .word  0xe7ffdeff
#endif

    bl     main

_start_hang:
    b      _start_hang

mmu_setup:
    mov     r12, #0
    mcr     p15, 0, r12, c8, c7, 0              /* Set c8 to control the TLB and set the mapping to invalid */
    isb

    mcr     p15, 0, r12, c2, c0, 2              /* Initialize the c2 register */
    isb

    orr     r12, r4, #MMU_TTBRx_FLAGS
    mcr     p15, 0, r12, c2, c0, 0              /* Set attributes and set temp page table */
    isb

    mov     r12, #0x7                           /* 0b0111 */
    mcr     p15, 0, r12, c3, c0, 0              /* Set DACR with 0b0111, client and manager domian */
    isb

    mrc     p15, 0, r12, c1, c0, 0
    bic     r12, #(1 << 29 | 1 << 28)
    orr     r12, #(1 << 0)
    bic     r12, #(1 << 1)
    orr     r12, #(1 << 2)
    orr     r12, #(1 << 12)
    mcr     p15, 0, r12, c1, c0, 0              /* Set SCTLR with r12: Turn on the MMU, I/D cache Disable TRE/AFE */
    isb

    ldr     pc,  =1f                            /* Convert to VA */
1:
    mcr     p15, 0, r8, c2, c0, 0               /* Go to the base address saved in C2: Jump to the page table */
    isb

    mov     r12, #0
    mcr     p15, 0, r12, c8, c7, 0
    isb

    sub     lr,  r11                            /* adjust lr with delta of physical address and virtual address */
    bx      lr

    .code  32

    .global reset_platform
    .type   reset_platform,function
reset_platform:
#ifdef A7SEM_HAL_ROM_MONITOR
    /* initialize CPSR (machine state register) */
    mov    r0, #(CPSR_IRQ_DISABLE|CPSR_FIQ_DISABLE|CPSR_SVC_MODE)
    msr    cpsr, r0
    b      warm_reset
#else
    mov    r0, #0
    mov    pc, r0   // Jump to reset vector
#endif
cpu_start:
    bl     secondary_cpu_start
    b      .



/*
 * set sp for current cpu
 * r1 is stack bottom, r0 is stack size, r11 hold cpu id
 */
sp_set:
    mul    r3, r0, r11
    sub    r2, r1, r3
    mov    sp, r2
    bx     lr          /* set sp */

/*
 * r4: page table base address
 * r5 and r6 will be used as variable
 */
page_table_clear:
    mov     r5, #0
    mov     r6, #0
0:
    str     r5, [r4, r6, lsl #2]
    add     r6, #1
    cmp     r6, #0x1000                         /* r6 < 4096 */
    blt     0b
    bx      lr

/*
 * r4: page table base address
 * r6: physical address
 * r7: virtual address
 * r8: sizes
 * r10: flags
 * r9 and r12 will be used as variable
 */
page_table_build:
    mov     r9, r6
    bfc     r9, #20, #12                        /* r9: pa % MB */
    add     r8, r8, r9
    add     r8, r8, #(1 << 20)
    sub     r8, r8, #1
    lsr     r6, #20                             /* r6 = physical address / MB */
    lsr     r7, #20                             /* r7 = virtual address / MB */
    lsr     r8, #20                             /* r8 = roundup(size, MB) */

page_table_build_loop:
    orr     r12, r10, r6, lsl #20               /* r12: flags | physAddr */
    str     r12, [r4, r7, lsl #2]               /* gPgTable[l1Index] = physAddr | flags */
    add     r6, #1                              /* physAddr+ */
    add     r7, #1                              /* l1Index++ */
    subs    r8, #1                              /* sizes-- */
    bne     page_table_build_loop
    bx      lr

/*
 * init stack to initial value
 * r0 is stack mem start, r1 is stack mem end
 */
stack_init:
    ldr     r2, =OS_STACK_INIT
    ldr     r3, =OS_STACK_INIT
    /* Main loop sets 32 bytes at a time. */
stack_init_loop:
    .irp    offset, #0, #8, #16, #24
    strd    r2, r3, [r0, \offset]
    .endr
    add     r0, #32
    cmp     r0, r1
    blt     stack_init_loop
    bx      lr

pa_va_offset:
    .word   .

/*
 * set magic num to stack top for all cpu
 * r0 is stack top, r1 is stack size, r2 is magic num
 */
excstack_magic:
    mov     r3, #0
excstack_magic_loop:
    str     r2, [r0]
    add     r0, r0, r1
    add     r3, r3, #1
    cmp     r3, #CORE_NUM
    blt     excstack_magic_loop
    bx      lr

/*
 * 0xe51ff004 = "ldr  pc, [pc, #-4]"
 * next addr value will be the real booting addr
 */
_bootaddr_setup:
    mov     r0, #0
    ldr     r1, =0xe51ff004
    str     r1, [r0]

    add     r0, r0, #4
    ldr     r1, =SYS_MEM_BASE
    str     r1, [r0]

    dsb
    isb

    bx      lr

init_done:
    .long  0xDEADB00B

    .code  32
    .data

init_flag:
    .balign 4
    .long   0

    /*
    * Temporary interrupt stack
    */
    .section ".int_stack", "wa", %nobits
    .align  3

__undef_stack:
    .space OS_EXC_UNDEF_STACK_SIZE * CORE_NUM
__undef_stack_top:

__abt_stack:
    .space OS_EXC_ABT_STACK_SIZE * CORE_NUM
__abt_stack_top:

__irq_stack:
    .space OS_EXC_IRQ_STACK_SIZE * CORE_NUM
__irq_stack_top:

__fiq_stack:
    .space OS_EXC_FIQ_STACK_SIZE * CORE_NUM
__fiq_stack_top:

__svc_stack:
    .space OS_EXC_SVC_STACK_SIZE * CORE_NUM
__svc_stack_top:

__exc_stack:
    .space OS_EXC_STACK_SIZE * CORE_NUM
__exc_stack_top:
