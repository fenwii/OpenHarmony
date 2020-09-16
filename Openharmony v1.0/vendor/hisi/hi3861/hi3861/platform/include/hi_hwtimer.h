/*
 * @file hi_hwtimer.h
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

#ifndef __HI_HWTIMER_H__
#define __HI_HWTIMER_H__

#include <hi_types_base.h>


typedef enum {
    HI_RTC_CLK_32K = 32,
    HI_RTC_CLK_24M = 24,
    HI_RTC_CLK_40M = 40,
} hi_rtc_clk; /**< In low-power deep sleep mode, the 24 MHz or 40 MHz clock is unavailable. */

typedef void (*hi_hwtimer_callback)(hi_u32 data);

typedef void (*hi_hwrtc_callback)(hi_u32 data);

typedef void (*hwtimer_clken_callback)(hi_void);

/**
 * @ingroup hw_timer
 *
 * Timer mode control. CNcomment:定时器模式控制。CNend
 */
typedef enum {
    TIMER_MODE_FREE = 0,
    TIMER_MODE_CYCLE = 1,
} timer_mode;

/**
 * @ingroup hw_timer
 *
 * Timer interrupt mask control. CNcomment:定时器中断模式控制。CNend
 */
typedef enum {
    TIMER_INT_UNMASK = 0,  /**< Not masked */
    TIMER_INT_MASK = 1,    /**< Masked */
} timer_int_mask;

/**
 * @ingroup hw_timer
 *
 * hwtimer ID. CNcomment:硬件定时器ID。CNend
 */
typedef enum {
    HI_TIMER_ID_0,
    HI_TIMER_ID_1,
    HI_TIMER_ID_2,
    HI_TIMER_ID_MAX, /* Invalid value. */
} hi_timer_id;

/**
 * @ingroup hw_timer
 *
 * hwrtc ID. CNcomment:硬件RTC ID。CNend
 */
typedef enum {
    HI_RTC_ID_0 = HI_TIMER_ID_MAX,
    HI_RTC_ID_1,
    HI_RTC_ID_2,
    HI_RTC_ID_3,
    HI_RTC_ID_MAX, /* Invalid value. */
} hi_rtc_id;

/**
 * @ingroup hw_timer
 *
 * hwtimer working mode. CNcomment:硬件定时器工作模式。CNend
 */
typedef enum {
    HI_HWTIMER_MODE_ONCE,
    HI_HWTIMER_MODE_PERIOD,
    HI_HWTIMER_MODE_INVALID,
} hi_hwtimer_mode;

/**
 * @ingroup hw_timer
 *
 * hwrtc working mode. CNcomment:硬件RTC工作模式。CNend
 */
typedef enum {
    HI_HWRTC_MODE_ONCE,
    HI_HWRTC_MODE_PERIOD,
    HI_HWRTC_MODE_INVALID,
} hi_hwrtc_mode;

/**
 * @ingroup hw_timer
 *
 * hwtimer handle structure. CNcomment:硬件定时器句柄结构。CNend
 */
typedef struct {
    hi_hwtimer_mode mode;
    hi_u32 expire;
    hi_u32 data;
    hi_hwtimer_callback func;
    hi_timer_id timer_id;
} hi_hwtimer_ctl;

/**
 * @ingroup hw_timer
 *
 * hwrtc handle structure. CNcomment:硬件RTC句柄结构。CNend
 */
typedef struct {
    hi_hwrtc_mode mode;
    hi_u32 expire;
    hi_u32 data;
    hi_hwrtc_callback func;
    hi_rtc_id rtc_id;
} hi_hwrtc_ctl;

hi_void hi_hwrtc_set_clk(hi_rtc_clk clk);

hi_u32 hi_hwtimer_init_new(hi_timer_id timer_id);
hi_u32 hi_hwtimer_start(const hi_hwtimer_ctl *timer);
hi_u32 hi_hwtimer_stop(hi_timer_id timer_id);
hi_u32 hi_hwtimer_destroy_new(hi_timer_id timer_id);
hi_u32 hi_hwtimer_get_cur_val(hi_timer_id timer_id, hi_u32 *val);
hi_u32 hi_hwtimer_get_load(hi_timer_id timer_id, hi_u32 *load);

hi_u32 hi_hwrtc_start(const hi_hwrtc_ctl *rtc);
hi_u32 hi_hwrtc_init(hi_rtc_id timer_id);
hi_u32 hi_hwrtc_stop(hi_rtc_id rtc_id);
hi_u32 hi_hwrtc_destroy(hi_rtc_id rtc_id);
hi_u32 hi_hwrtc_get_cur_val(hi_rtc_id rtc_id, hi_u32 *val);
hi_u32 hi_hwrtc_get_load(hi_rtc_id rtc_id, hi_u32 *load);
hi_u32 hwtimer_start(hi_u32 tick_cnt, const hi_hwtimer_ctl *timer);

#endif
