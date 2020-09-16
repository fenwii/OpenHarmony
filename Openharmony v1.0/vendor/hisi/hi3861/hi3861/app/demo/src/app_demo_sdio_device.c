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
 *
 * Description: app sdio slave demo: shows send and receive data with sdio.
 */

#include <hi_early_debug.h>
#include <hi_watchdog.h>
#include <hi_sdio_device.h>
#include <hi_cipher.h>
#include <hi_cpu.h>

#define  DATA_BLOCK         32768 /* sdio data block size:32768 */
#define SEND_RCV_DATA_SIZE  1024  /* send/recv 1024 byte per cycle */
hi_u32 g_sdio_send_data[SEND_RCV_DATA_SIZE] = {0}; /* data array of data to be send */
hi_u32* g_sdio_send_data_addr = NULL;

hi_s32 app_demo_sdio_read_over_callback(hi_void)
{
    printf("app_demo_sdio_read_over_callback\r\n");
    return HI_ERR_SUCCESS;
}

hi_s32 app_demo_sdio_read_start_callback(hi_u32 len, hi_u8* admatable)
{
    hi_watchdog_feed();

    hi_u32 i;
    hi_u32 remain;
    hi_u32 index = 0;
    hi_u32* addr = NULL;
    g_sdio_send_data_addr = &g_sdio_send_data[0];

    for (i = 0; i < (len / DATA_BLOCK); i++) {
        addr = g_sdio_send_data_addr + ((DATA_BLOCK >> 2) * i); /* 2 bits for g_download_addr is hi_u32 */
        if (hi_sdio_set_admatable(admatable, index++, addr, DATA_BLOCK) != 0) {
            return HI_ERR_FAILURE;
        }
    }

    remain = len % DATA_BLOCK;
    if (remain != 0) {
        addr = g_sdio_send_data_addr + ((DATA_BLOCK >> 2) * i); /* 2 bits for g_download_addr is hi_u32 */
        if (hi_sdio_set_admatable(admatable, index++, addr, remain) != 0) {
            return HI_ERR_FAILURE;
        }
    }

    if (hi_sdio_complete_send(admatable, index) != 0) {
        return  HI_ERR_FAILURE;
    }

    hi_cache_flush();
    return (hi_s32) index;
}

hi_u32 g_receive_data[SEND_RCV_DATA_SIZE] = {0}; /* data array to receive data */
hi_u32* g_receive_data_addr = NULL;
hi_u32 g_recevei_data_len = 0;
hi_s32 app_demo_sdio_write_start_callback(hi_u32 len, hi_u8* admatable)
{
    printf("app_demo_sdio_write_start_callback,len: %d\n",  len);
    hi_watchdog_feed();
    g_receive_data_addr = &g_receive_data[0];
    g_recevei_data_len = len;

    hi_u32 i;
    hi_u32 remain;
    hi_u32 index = 0;
    hi_u32* addr = NULL;

    for (i = 0; i < (len / DATA_BLOCK); i++) {
        addr = g_receive_data_addr + ((DATA_BLOCK >> 2) * i); /* shift 2bits is for hi_u32* reason. */
        if (hi_sdio_set_admatable(admatable, index++, addr, DATA_BLOCK) != 0) {
            return HI_ERR_FAILURE;
        }
    }

    remain = len % DATA_BLOCK;

    if (remain != 0) {
        addr = g_receive_data_addr + ((DATA_BLOCK >> 2) * i); /* shift 2bits is for hi_u32* reason. */
        if (hi_sdio_set_admatable(admatable, index++, addr, remain) != 0) {
            return HI_ERR_FAILURE;
        }
    }

    if (hi_sdio_complete_send(admatable, index) != 0) {
        return HI_ERR_FAILURE;
    }

    hi_cache_flush();
    return (hi_s32) index;
}

hi_s32 app_demo_sdio_write_over_callback(hi_void)
{
    printf("app_demo_sdio_write_over_callback, len:%d\n", g_recevei_data_len);

    hi_u8* received_data = (hi_u8*)(&g_receive_data[0]);
    for (hi_u32 i = 0; i < g_recevei_data_len; i++) {
        if (i % 8 == 0) { /* 8:Newline */
            printf ("\r\n");
        }
        printf("0x%x ", received_data[i]);
    }
    return HI_ERR_SUCCESS;
}

hi_void app_demo_sdio_receive_msg_callback(hi_u32 msg)
{
    printf("app_demo_sdio_receive_msg_callback:0x%x\n", msg);
}

hi_void app_demo_sdio_read_err_callback(hi_void)
{
    printf("app_demo_sdio_read_err_callback\n");
}

hi_void app_demo_sdio_soft_rst_callback(hi_void)
{
    printf("app_demo_sdio_soft_rst_callback\r\n");
}

hi_void app_demo_sdio_send_data(hi_void)
{
    printf("app demo sdio start send data\r\n");

    hi_u8* send_data = (hi_u8*)&g_sdio_send_data[0];
    hi_cipher_trng_get_random_bytes(send_data, SEND_RCV_DATA_SIZE);
    hi_sdio_send_data(SEND_RCV_DATA_SIZE);

    return;
}

hi_void app_demo_sdio_send_msg(hi_void)
{
    hi_sdio_send_sync_msg(0);
    return;
}

hi_void app_demo_sdio_callback_init(hi_void)
{
    hi_sdio_intcallback callback;

    callback.rdover_callback     = app_demo_sdio_read_over_callback;
    callback.rdstart_callback    = app_demo_sdio_read_start_callback;
    callback.wrstart_callback    = app_demo_sdio_write_start_callback;
    callback.wrover_callback     = app_demo_sdio_write_over_callback;
    callback.processmsg_callback = app_demo_sdio_receive_msg_callback;
    callback.rderr_callback      = app_demo_sdio_read_err_callback;
    callback.soft_rst_callback   = app_demo_sdio_soft_rst_callback;
    (hi_void)hi_sdio_register_callback(&callback);

    printf("app_demo_sdio_callback_init success\r\n");
}

hi_void app_demo_sdio(hi_void)
{
    hi_u32 ret;
    /* init sdio */
    /* should config io in app_io_init first. */
    ret = hi_sdio_init();
    if (ret != HI_ERR_SUCCESS) {
        printf("app demo sdio init fail\r\n");
        return;
    }

    /* register sdio interrupt callbak. */
    app_demo_sdio_callback_init();

    /* sdio send and receive msg */
    /* when host send msg to device, device will receive msg in
     * app_demo_sdio_receive_msg_callback
     */
    app_demo_sdio_send_msg();

    /* sdio send data */
    app_demo_sdio_send_data();

    /* sdio receive data */
    /*
     * when host send data to device, device will receive data in
     * app_demo_sdio_write_start_callback, app_demo_sdio_write_over_callback
     */
}
