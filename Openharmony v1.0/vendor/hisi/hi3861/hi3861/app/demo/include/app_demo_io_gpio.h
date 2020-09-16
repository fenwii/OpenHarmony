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

#ifndef __APP_DEMO_IO_GPIO_H__
#define __APP_DEMO_IO_GPIO_H__

#include <hi_types_base.h>
#include <hi_io.h>
#include <hi_early_debug.h>
#include <hi_gpio.h>
#include <hi_task.h>

/* gpio callback func */
hi_void gpio_isr_func(hi_void *arg);
hi_void io_gpio_demo(hi_void);
/* gpio callback demo */
hi_void gpio_isr_demo(hi_void);
hi_void app_demo_custom_io_gpio(hi_void);
#endif