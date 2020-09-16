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

#ifndef __HI_WIFI_NAN_API_H__
#define __HI_WIFI_NAN_API_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef enum {
    WIFI_SDP_PUBLISH            = 0x01,
    WIFI_SDP_SUBSCRIBE          = 0x02,
    WIFI_SDP_BUTT
}wifi_sdp_type_enum;

typedef enum {
    WIFI_SDP_SYNC_MODE_PRIVATE,
    WIFI_SDP_SYNC_MODE_STANDARD,
    WIFI_SDP_SYNC_MODE_BOTH,
    WIFI_SDP_SYNC_MODE_BUTT
}wifi_sdp_sync_enum;

typedef int (*hi_wifi_sdp_recv_cb)(unsigned char* mac, unsigned char peer_handle, unsigned char local_handle,
    unsigned char* msg, unsigned char len);
int hi_wifi_sdp_init(const char* ifname);
int hi_wifi_sdp_deinit(void);
int hi_wifi_sdp_start_service(const char* service_name, unsigned char local_handle,
    hi_wifi_sdp_recv_cb recv_cb, unsigned char role);
int hi_wifi_sdp_stop_service(unsigned char local_handle, unsigned char role);
int hi_wifi_sdp_send(unsigned char* mac_addr, unsigned char peer_handle, unsigned char local_handle,
    unsigned char* msg, int len);
int hi_wifi_sdp_adjust_tx_power(const char *ifname, signed char power);
int hi_wifi_sdp_restore_tx_power(const char *ifname);
int hi_wifi_sdp_adjust_rx_param(const char *ifname, signed char rssi);
int hi_wifi_sdp_restore_rx_param(const char *ifname);
int hi_wifi_sdp_beacon_switch(const char *ifname, unsigned char enable);
int hi_wifi_sdp_set_retry_times(hi_u32 retries);
int hi_wifi_sdp_get_sync_mode(void);
#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif /* end __HI_WIFI_VLWIP_API_H__ */

