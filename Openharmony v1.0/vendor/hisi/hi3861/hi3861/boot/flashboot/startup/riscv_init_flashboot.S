/*
 * @file entry.S
 *
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @brief RISC-V trap handling and startup code.
 *
 */
#ifndef ENTRY_S
#define ENTRY_S

.extern __stack_top

#define LREG lw
#define SREG sw
#define REGBYTES 4

#define INT_SIZE_ON_STACK  (16 * REGBYTES)

#define MSTATUS_MPP_MACHINE       0x00001800
#define MCAULSE_ECALL_FROM_MMODE  11
#define MCAULSE_ECALL_FROM_UMODE  8

    .extern trap_entry
    .section      .text.entry
    .global _start
    .option norvc
_start:
    j handle_reset

.macro push_reg
    addi  sp, sp, -(INT_SIZE_ON_STACK)
    SREG x1, 0 * REGBYTES(sp)
    SREG x5, 1 * REGBYTES(sp)
    SREG x6, 2 * REGBYTES(sp)
    SREG x7, 3 * REGBYTES(sp)
    SREG x10, 4 * REGBYTES(sp)
    SREG x11, 5 * REGBYTES(sp)
    SREG x12, 6 * REGBYTES(sp)
    SREG x13, 7 * REGBYTES(sp)
    SREG x14, 8 * REGBYTES(sp)
    SREG x15, 9 * REGBYTES(sp)
    SREG x16, 10 * REGBYTES(sp)
    SREG x17, 11 * REGBYTES(sp)
    SREG x28, 12 * REGBYTES(sp)
    SREG x29, 13 * REGBYTES(sp)
    SREG x30, 14 * REGBYTES(sp)
    SREG x31, 15 * REGBYTES(sp)
    addi  sp, sp, -(INT_SIZE_ON_STACK)
.endm

.macro pop_reg
    addi  sp, sp, INT_SIZE_ON_STACK
    LREG x1, 0 * REGBYTES(sp)
    LREG x5, 1 * REGBYTES(sp)
    LREG x6, 2 * REGBYTES(sp)
    LREG x7, 3 * REGBYTES(sp)
    LREG x10, 4 * REGBYTES(sp)
    LREG x11, 5 * REGBYTES(sp)
    LREG x12, 6 * REGBYTES(sp)
    LREG x13, 7 * REGBYTES(sp)
    LREG x14, 8 * REGBYTES(sp)
    LREG x15, 9 * REGBYTES(sp)
    LREG x16, 10 * REGBYTES(sp)
    LREG x17, 11 * REGBYTES(sp)
    LREG x28, 12 * REGBYTES(sp)
    LREG x29, 13 * REGBYTES(sp)
    LREG x30, 14 * REGBYTES(sp)
    SREG x31, 15 * REGBYTES(sp)
    addi  sp, sp, INT_SIZE_ON_STACK
.endm

trap_entry_wrapper:
    j trap_entry

trap_entry:
    push_reg
    csrr t0, mcause
#ecall from M-mode
    li t1, MCAULSE_ECALL_FROM_MMODE
    bne t0, t1, 1f
    li t2, MSTATUS_MPP_MACHINE
    csrc mstatus, t2
    csrr t0, mepc
    addi t0, t0, 4
    csrw mepc, t0
    pop_reg
    mret
#ecall from U-mode
1:
    li t1, MCAULSE_ECALL_FROM_UMODE
    bne t0, t1, 2f
    li t2, MSTATUS_MPP_MACHINE
    csrs mstatus, t2
    csrr t0, mepc
    addi t0, t0, 4
    csrw mepc, t0
    pop_reg
    mret
#Other exception. //TODO: reg reset.
2:
    pop_reg
    j trap_entry

handle_reset:
    csrwi mstatus, 0
    csrwi mie, 0
    csrci mstatus, 0x08

/* initialize global pointer */
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop

/* initialize stack pointer */
    la sp, __stack_top

/* perform the rest of initialization in C */
clear_bss:
    la t0, __bss_begin__
    la t1, __bss_end__
    li t2, 0x00000000

clear_bss_loop:
    sw      t2, (t0)        /* clear BSS location */
    addi t0, t0, 4          /* increment clear index pointer */
    blt     t0, t1, clear_bss_loop  /* are we at the end yet, if not , contiue till the end */

clear_rom_bss:
    la t0, __rom_bss_start
    la t1, __rom_bss_end
    li t2, 0x00000000

clear_rom_bss_loop:
    sw      t2, (t0)        /* clear ROM_BSS location */
    addi    t0, t0, 4       /* increment clear index pointer */
    blt     t0, t1, clear_rom_bss_loop /* are we at the end yet, if not , contiue till the end */

clear_code_rom_bss:
    la t0, __code_rom_bss_start
    la t1, __code_rom_bss_end
    li t2, 0x00000000

clear_code_rom_bss_loop:
    sw      t2, (t0)        /* clear ROM_BSS location */
    addi    t0, t0, 4       /* increment clear index pointer */
    blt     t0, t1, clear_code_rom_bss_loop /* are we at the end yet, if not , contiue till the end */

/* copy .data .sdata section  from  FIX_ROM to SRAM */
    la t0, __rom_copy_ram_start /* SRAM addr */
    la t1, __rom_copy_start     /* ROM addr  */
    la t2, __rom_copy_size
    add t2, t2, t1

start_fixrom_data_loop:
    lw t3, (t1)
    sw t3, (t0)
    addi t0, t0, 4
    addi t1, t1, 4
    blt t1, t2, start_fixrom_data_loop /* are we at the end yet, if not , contiue till the end */
end_fixrom_data_loop:

/* copy .data .sdata section  from  CODE_ROM to SRAM */
    la t0, __code_rom_copy_ram_start /* SRAM addr */
    la t1, __code_rom_copy_start     /* ROM addr  */
    la t2, __code_rom_copy_size
    add t2, t2, t1

start_coderom_data_loop:
    lw t3, (t1)
    sw t3, (t0)
    addi t0, t0, 4
    addi t1, t1, 4
    blt t1, t2, start_coderom_data_loop /* are we at the end yet, if not , contiue till the end */
end_coderom_data_loop:


/* pmp init */
pmp_init:
    li t0, 0xB00
    csrw pmpaddr0, t0
    li t0,0x2000
    csrw pmpaddr1, t0 /* (1)11-32K(0x8000) fixrom: disable w;non-cacheable */
#ifdef HI_BOARD_ASIC
    li t0,0x477f0
    csrw pmpaddr2, t0 /* (2)32k(0x8000) - 0x11DFC0 RAM: disable x;non-cacheable */
    li t0,0x47800
    csrw pmpaddr3, t0 /* (3)0x11DFC0 - 0x11E000 checkinfo: disable w x;non-cacheable */
#else
    li t0,0x7fff0
    csrw pmpaddr2, t0 /* (2)32k(0x8000) - 0x1FFFC0 RAM: non-cacheable */
    li t0,0x80000
    csrw pmpaddr3, t0 /* (3)0x1FFFC0 - 0x200000 checkinfo: disable w x;non-cacheable */
#endif
    li t0,0xEE000
    csrw pmpaddr4, t0 /* (4)0x11E000 - 0x3B8000 another romboot: disable r-w-x;non-cacheable */
    li t0,0xFF600
    csrw pmpaddr5, t0 /* (5)0x3B8000 - 0x3FD800 kernel_rombin: diasble r-w-x;non-cacheable */
    li t0,0x100000
    csrw pmpaddr6, t0 /* (6)0x3FD800 - 0x400000 code_rombin(9K): diasble w;non-cacheable */
    li t0,0x18000000
    csrw pmpaddr7, t0 /* (7)0x400000 -> 0x60000000 REG: disable x;non-cacheable */

    li t0,0xf3333333  /* f:Write-back Read and Write-allocate; 3:Normal Non-cacheable Bufferable */
    csrw 0x7d8,t0

    li t0,0x090f0d88  /* 0x0d:TOR-R-X; 0x0b:TOR-R-W; 0x08:TOR; 0x0c:TOR-x; 0x09:TOR-R */
    csrw pmpcfg0,t0
    li t0,0x0b0d0808
    csrw pmpcfg1,t0

/* disable Icache */
    csrwi  0x7C0, 0x0 /* disable ICACHE */
    fence

/* disable Dcache */
    csrwi  0x7C1, 0x0 /* disable DCACHE */
    fence

    csrwi mstatus, 0
    csrwi mie, 0
    la t0, trap_entry_wrapper
    addi t0, t0, 1
    csrw mtvec, t0
    ecall        /* ecall: M-mode -> U-mode */

/* jump to C func. */
    tail start_fastboot
#endif
