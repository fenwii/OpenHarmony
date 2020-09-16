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

#ifndef __APP_DEMO_TIMER_SYSTICK_H__
#define __APP_DEMO_TIMER_SYSTICK_H__

#include <hi_types_base.h>
#include <hi_hrtimer.h>
#include <hi_early_debug.h>
#include <hi_systick.h>
#include <hi_task.h>
#include <hi_time.h>
#include <hi_timer.h>

#define NO_CALLBACK 0xffff
#define HRTIMER_EXPIRE 2000       /* expire timer is 2000us */
#define WORK_TICK_DELAY_US 31     /* 1/32K */
#define APP_DEMO_TIMER_WAIT 10000 /* wait 10s */

hi_void hr_timer_callback(hi_u32 data);
hi_void app_demo_hrtimer(hi_void);
hi_void app_demo_systick(hi_void);
static hi_void app_demo_timer_handle(hi_u32 data);
hi_void app_demo_timer(hi_void);
#endif