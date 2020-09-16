/*
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
 */

#include <hi_flashboot.h>
#include <boot_start.h>
#include <hi_boot_rom.h>
#include "main.h"
#ifdef CONFIG_FLASH_ENCRYPT_SUPPORT
#include <crypto.h>
#endif

#define KERNEL_START_ADDR   0x40D3C0

hi_u32 g_uart_auth;
#define FLASHBOOT_UART_DEFAULT_PARAM    {115200, 8, 1, 0, 0, 0, 2, 1, 4}

hi_void boot_kernel(uintptr_t kaddr)
{
    __asm__ __volatile__("ecall");  /* switch U-MODE -> M-MODE */
    hi_void (*entry)(hi_void) = (hi_void*)(kaddr);
    entry();
}

hi_void boot_io_init(hi_void)
{
    hi_io_set_func(HI_IO_NAME_GPIO_3, HI_IO_FUNC_GPIO_3_UART0_TXD); /* uart0 tx */
    hi_io_set_func(HI_IO_NAME_GPIO_4, HI_IO_FUNC_GPIO_4_UART0_RXD); /* uart0 rx */
}

hi_void boot_flash_init(hi_void)
{
    hi_flash_cmd_func flash_funcs = {0};
    flash_funcs.init = hi_flash_init;
    flash_funcs.read = hi_flash_read;
    flash_funcs.write = hi_flash_write;
    flash_funcs.erase = hi_flash_erase;
    hi_cmd_regist_flash_cmd(&flash_funcs);
    (hi_void) hi_flash_init();
}
#define XTAL_DS     0x7
#define OSC_DRV_CTL 0x2

hi_void boot_extern_32k(hi_void)
{
    hi_u16 chip_id, chip_id_bk;
    hi_u32 ret;
    ret = hi_efuse_read(HI_EFUSE_CHIP_RW_ID, (hi_u8 *)&chip_id, (hi_u8)sizeof(hi_u8));
    if (ret != HI_ERR_SUCCESS) {
        return;
    }
    ret = hi_efuse_read(HI_EFUSE_CHIP_BK_RW_ID, (hi_u8 *)&chip_id_bk, (hi_u8)sizeof(hi_u8));
    if (ret != HI_ERR_SUCCESS) {
        return;
    }
    hi_u8 chip_ver = (chip_id >> OFFSET_4_B) & MSK_3_B; /* chip_id bit[4:7] is chip_ver. */
    hi_u8 chip_ver_bk = (chip_id_bk >> OFFSET_4_B) & MSK_3_B; /* chip_id bit[4:7] is chip_ver. */
    if (chip_ver != HI_CHIP_VER_HI3861L) {
        if (chip_ver_bk != HI_CHIP_VER_HI3861L) {
            return;
        }
    }
    hi_u32 reg_val;
    hi_reg_read(HI_IOCFG_REG_BASE + IO_CTRL_REG_BASE_ADDR, reg_val);
    reg_val &= ~(MSK_2_B << OFFSET_4_B); /* Maximum drive capability */
    reg_val |= (MSK_2_B << OFFSET_22_B); /* external xtal, osc enable */
    reg_val &= ~(MSK_3_B << OFFSET_25_B);
    reg_val |= XTAL_DS << OFFSET_25_B;   /* 1.6ua */
    reg_val &= ~(MSK_2_B << OFFSET_28_B);
    reg_val |= OSC_DRV_CTL << OFFSET_28_B;   /* 4Mohm */
    hi_reg_write(HI_IOCFG_REG_BASE + IO_CTRL_REG_BASE_ADDR, reg_val);
}

/* the entry of C. */
hi_void start_fastboot(hi_void)
{
#ifndef CONFIG_QUICK_SEND_MODE
    hi_u32 ret;
    hi_malloc_func malloc_funcs = {0, };
    uart_param_stru default_uart_param = FLASHBOOT_UART_DEFAULT_PARAM;
    hi_watchdog_disable();
    hi_watchdog_enable(WDG_TIME_US);

    /* io config */
    boot_io_init();

    /* Registering and Initializing the Heap Area */
    malloc_funcs.init = rom_boot_malloc_init;
    malloc_funcs.boot_malloc = rom_boot_malloc;
    malloc_funcs.boot_free = rom_boot_free;

    hi_register_malloc((uintptr_t)&__heap_begin__, &malloc_funcs);
    hi_u32 check_sum = ((uintptr_t)&__heap_begin__) ^ ((uintptr_t)&__heap_end__);
    boot_malloc_init((uintptr_t)&__heap_begin__, (uintptr_t)&__heap_end__, check_sum);

    /* Initializing the Debugging Serial Port */
    ret = serial_init(UART0, default_uart_param);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg0("uart err"); /* Use the serial port of the romboot to configure the printing. */
    }

    boot_extern_32k();
    /* Initializing the Flash Driver */
    boot_flash_init();
    /* NV initialization */
    ret = hi_factory_nv_init(HI_FNV_DEFAULT_ADDR, HI_NV_DEFAULT_TOTAL_SIZE, HI_NV_DEFAULT_BLOCK_SIZE);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg0("fnv err");
    }

    ret = hi_flash_partition_init();
    if (ret != HI_ERR_SUCCESS) {
        boot_msg0("parti err");
    }

    execute_upg_boot();
#else

#ifdef CHIP_HI3861L
    boot_extern_32k();
#endif
    hi_flash_init();
    boot_kernel(KERNEL_START_ADDR);
#endif
    mdelay(RESET_DELAY_MS);
    global_reset();
}
