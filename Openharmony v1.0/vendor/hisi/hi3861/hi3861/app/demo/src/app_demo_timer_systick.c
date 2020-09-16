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

#include <app_demo_timer_systick.h>

hi_u64 g_time1;
hi_u64 g_time2;
hi_u32 g_hrtimer_handle;       /* hr timer handle */
hi_u32 g_timer_handle;         /* timer handle */

/* hrtimer callback func */
hi_void hr_timer_callback(hi_u32 data)
{
    g_time2 = hi_systick_get_cur_tick();

    printf("----- hrtimer_callback data:%d\r\n", data);

    printf("----- hrtimer_callback, g_time1:%lld\r\n", g_time1);
    printf("----- hrtimer_callback, g_time2:%lld\r\n", g_time2);
    printf("----- hrtimer_callback, cha:%lld\r\n", g_time2 - g_time1);

    printf("***** sleep 50000us ******\r\n");
}

/*
 * This demo simply shows how to create and start hrtimer.
 */
hi_void app_demo_hrtimer(hi_void)
{
    hi_u32 ret;

    /* create timer handle */
    ret = hi_hrtimer_create(&g_hrtimer_handle);
    if (ret != HI_ERR_SUCCESS) {
        printf("=====ERROR===== hrtimer handle create ret is: %d !!\r\n", ret);
        return;
    }
    printf("----- hrtimer handle create success -----\n");

    g_time1 = hi_systick_get_cur_tick();

    ret = hi_hrtimer_start(g_hrtimer_handle, HRTIMER_EXPIRE, hr_timer_callback, 0);
    if (ret != HI_ERR_SUCCESS) {
        printf("=====ERROR=====hrtimer start error, ret is: %d !!\n", ret);
        return;
    }
    printf("----- hrtimer start success -----\n");

    hi_sleep(1000); /* sleep 1000 to prevent the timer from being destroyed before the callback function is completed */
    ret = hi_hrtimer_stop(g_hrtimer_handle);
    if (ret != HI_ERR_SUCCESS) {
        printf("=====ERROR===== hrtimer stop error, ret is: %d !!\r\n", ret);
    }
    printf("----- hrtimer stop success -----\n");

    /* delete timer */
    ret = hi_hrtimer_delete(g_hrtimer_handle);
    if (ret != HI_ERR_SUCCESS) {
        printf("=====ERROR===== hrtimer delete error, ret is: %d !!\r\n", ret);
    }
    printf("----- hrtimer handle delete success -----\n");
}

/*
 * This demo simply shows how to use systick.
 */
hi_void app_demo_systick(hi_void)
{
    hi_u64 cnt1;
    hi_u64 cnt2;

    /* Get the current tick value, then clear the tick and get the tick value again */
    cnt1 = hi_systick_get_cur_tick();
    printf("----- get current tick cnt1 is %llu -----\r\n", cnt1);
    hi_systick_clear();
    hi_udelay(WORK_TICK_DELAY_US * 3); /* systick waits for 3 tick before clearing */
    cnt2 = hi_systick_get_cur_tick();
    printf("----- get current tick cnt2 is %llu -----\r\n", cnt2);

    /* Because of the error, the number read immediately after clearing cannot be guaranteed to be 0,
        so cnt2 which less than 20us is qualified */
    if (cnt2 < 20) { /* 20us */
        printf("----- systick clear success -----\r\n");
    } else {
        printf("======ERROR===== systick clear error, cnt2 = %llu\r\n", cnt2);
    }
}

static hi_void app_demo_timer_handle(hi_u32 data)
{
    hi_unref_param(data);
    printf("app demo timer timeout\r\n");
}

/*
 * This demo simply shows how to create and start os timer.
 */
hi_void app_demo_timer(hi_void)
{
    hi_u32 ret;
    ret = hi_timer_create(&g_timer_handle);
    if (ret != HI_ERR_SUCCESS) {
        printf("timer create fail\r\n");
    }
    printf("timer create success\r\n");

    ret = hi_timer_start(g_timer_handle, HI_TIMER_TYPE_ONCE, APP_DEMO_TIMER_WAIT, app_demo_timer_handle, 0);
    if (ret != HI_ERR_SUCCESS) {
        printf("timer start fail\r\n");
    }
    printf("timer start success\r\n");

    hi_sleep(20000);    /* 20000: sleep 20s */

    ret = hi_timer_stop(g_timer_handle);
    if (ret != HI_ERR_SUCCESS) {
        printf("timer stop fail\r\n");
    }
    printf("timer stop success\r\n");
}

