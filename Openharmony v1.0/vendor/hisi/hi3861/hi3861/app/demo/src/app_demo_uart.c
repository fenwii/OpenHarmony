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

#include <app_demo_uart.h>

hi_u32 g_uart_demo_task_id = 0;

static hi_void *uart_demo_task(hi_void *param)
{
    hi_u8 uart_buff[UART_BUFF_SIZE] = {0};
    hi_u8 *uart_buff_ptr = uart_buff;
    hi_unref_param(param);
    printf("Initialize uart demo successfully, please enter some datas via DEMO_UART_NUM port...\n");

    for (;;) {
        hi_s32 len = hi_uart_read(DEMO_UART_NUM, uart_buff_ptr, UART_BUFF_SIZE);
        if (len > 0) {
#ifdef WRITE_BY_INT
            hi_uart_write(DEMO_UART_NUM, uart_buff_ptr, len);
#else
            hi_uart_write_immediately(DEMO_UART_NUM, uart_buff_ptr, len);
#endif
        } else {
            printf("Read nothing!\n");
            hi_sleep(1000); /* sleep 1000ms */
        }
    }

    hi_task_delete(g_uart_demo_task_id);
    g_uart_demo_task_id = 0;

    return HI_NULL;
}

/*
 * This demo simply shows how to read datas from UART2 port and then echo back.
 */
hi_void uart_demo(hi_void)
{
    hi_u32 ret;
    hi_uart_attribute uart_attr = {
        .baud_rate = 115200, /* baud_rate: 115200 */
        .data_bits = 8,      /* data_bits: 8bits */
        .stop_bits = 1,
        .parity = 0,
    };

    /* Initialize uart driver */
    ret = hi_uart_init(DEMO_UART_NUM, &uart_attr, HI_NULL);
    if (ret != HI_ERR_SUCCESS) {
        printf("Failed to init uart! Err code = %d\n", ret);
        return;
    }

    /* Create a task to handle uart communication */
    hi_task_attr attr = {0};
    attr.stack_size = UART_DEMO_TASK_STAK_SIZE;
    attr.task_prio = UART_DEMO_TASK_PRIORITY;
    attr.task_name = (hi_char*)"uart_demo";
    ret = hi_task_create(&g_uart_demo_task_id, &attr, uart_demo_task, HI_NULL);
    if (ret != HI_ERR_SUCCESS) {
        printf("Falied to create uart demo task!\n");
    }
}
