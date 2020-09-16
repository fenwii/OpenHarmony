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

#include <hi_boot_rom.h>
#include <hi_loaderboot_flash.h>
#include <cmd_loop.h>
#include "main.h"

hi_void boot_io_init(hi_void)
{
    hi_io_set_func(HI_IO_NAME_GPIO_3, HI_IO_FUNC_GPIO_3_UART0_TXD); /* uart0 tx */
    hi_io_set_func(HI_IO_NAME_GPIO_4, HI_IO_FUNC_GPIO_4_UART0_RXD); /* uart0 rx */
    hi_io_set_func(HI_IO_NAME_GPIO_13, HI_IO_FUNC_GPIO_13_SSI_DATA);
    hi_io_set_func(HI_IO_NAME_GPIO_14, HI_IO_FUNC_GPIO_14_SSI_CLK);
    hi_io_set_func(HI_IO_NAME_SFC_CLK, HI_IO_FUNC_SFC_CLK_SFC_CLK);
    hi_io_set_func(HI_IO_NAME_SFC_IO3, HI_IO_FUNC_SFC_IO_3_SFC_HOLDN);
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

/* the entry of C. */
hi_void start_loaderboot(hi_void)
{
    uart_ctx *cmd_ctx = HI_NULL;
    hi_malloc_func malloc_funcs = {0, };

    /* io config */
    boot_io_init();

    /* Heap registration and initialization */
    malloc_funcs.init = rom_boot_malloc_init;
    malloc_funcs.boot_malloc = rom_boot_malloc;
    malloc_funcs.boot_free = rom_boot_free;

    hi_register_malloc((uintptr_t)&__heap_begin__, &malloc_funcs);
    hi_u32 check_sum = (uintptr_t)(&__heap_begin__) ^ (uintptr_t)(&__heap_end__);
    boot_malloc_init((uintptr_t)&__heap_begin__, (uintptr_t)&__heap_end__, check_sum);

    /* Flash initialization */
    boot_flash_init();

    cmd_ctx = cmd_loop_init();
    if (cmd_ctx == HI_NULL) {
        boot_msg0("cmd init fail");
        reset();
        while (1) {}
    }

    /* Enter the waiting command cycle and disable the watchdog. */
    hi_watchdog_disable();
    loader_ack(ACK_SUCCESS);
    boot_msg0("Entry loader");

    hi_u32 ret = flash_protect_set_protect(0, HI_FALSE);
    if (ret != HI_ERR_SUCCESS) {
        boot_msg0("Unlock Fail!");
    }

    boot_msg0("============================================\n");
    cmd_loop(cmd_ctx);
    reset();
    while (1) {}
}
