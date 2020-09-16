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

#ifndef __APP_DEMO_UART_H__
#define __APP_DEMO_UART_H__

#include <hi_types_base.h>
#include <hi_early_debug.h>
#include <hi_task.h>
#include <hi_uart.h>
#include <app_demo_uart.h>

#define WRITE_BY_INT
#define UART_DEMO_TASK_STAK_SIZE 2048
#define UART_DEMO_TASK_PRIORITY  25
#define DEMO_UART_NUM            HI_UART_IDX_2
#define UART_BUFF_SIZE           32

static hi_void *uart_demo_task(hi_void *param);
hi_void uart_demo(hi_void);
#endif