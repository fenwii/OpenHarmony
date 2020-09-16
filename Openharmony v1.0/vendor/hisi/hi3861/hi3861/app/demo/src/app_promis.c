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

#include "app_promis.h"

#include <stdio.h>
#include <stdlib.h>

#include <hi_wifi_api.h>
#include <hi_errno.h>
#include <hi_at.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/* Description: Packet receiving and reporting in promiscuous mode */
int hi_promis_recv(void* recv_buf, int frame_len, signed char rssi)
{
    hi_at_printf("resv buf: %u , len: %d , rssi: %c\r\n", *(unsigned int*)recv_buf, frame_len, rssi);

    return HI_ERR_SUCCESS;
}

/* Description: Enable the promiscuous mode */
unsigned int hi_promis_start(const char *ifname)
{
    int ret;
    hi_wifi_ptype_filter filter = {0};

    filter.mdata_en = 1;
    filter.udata_en = 1;
    filter.mmngt_en = 1;
    filter.umngt_en = 1;

    hi_wifi_promis_set_rx_callback(hi_promis_recv);

    ret = hi_wifi_promis_enable(ifname, 1, &filter);
    if (ret != HI_ERR_SUCCESS) {
        hi_at_printf("hi_wifi_promis_enable:: set error!\r\n");
        return ret;
    }

    hi_at_printf("start promis SUCCESS!\r\n");

    return HI_ERR_SUCCESS;
}

/* Description: Disable the promiscuous mode */
unsigned int hi_promis_stop(const char *ifname)
{
    int ret;
    hi_wifi_ptype_filter filter = {0};

    ret = hi_wifi_promis_enable(ifname, 0, &filter);
    if (ret != HI_ERR_SUCCESS) {
        hi_at_printf("hi_wifi_promis_enable:: set error!\r\n");
        return ret;
    }

    hi_at_printf("stop promis SUCCESS!\r\n");

    return HI_ERR_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif
