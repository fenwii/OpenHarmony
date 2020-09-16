/*
 * Driver interaction with hdf wifi
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef _WPA_HAL_EVENT_H_
#define _WPA_HAL_EVENT_H_

#include <stdint.h>
#include "hdf_sbuf.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define EVENT_BUF_OFFSET 8
#define IFNAMSIZ 16

typedef enum {
    WPA_ELOOP_EVENT_NEW_STA = 0,
    WPA_ELOOP_EVENT_DEL_STA,
    WPA_ELOOP_EVENT_RX_MGMT,
    WPA_ELOOP_EVENT_TX_STATUS,
    WPA_ELOOP_EVENT_SCAN_DONE,
    WPA_ELOOP_EVENT_SCAN_RESULT = 5,
    WPA_ELOOP_EVENT_CONNECT_RESULT,
    WPA_ELOOP_EVENT_DISCONNECT,
    WPA_ELOOP_EVENT_MESH_CLOSE,
    WPA_ELOOP_EVENT_NEW_PEER_CANDIDATE,
    WPA_ELOOP_EVENT_REMAIN_ON_CHANNEL = 10,
    WPA_ELOOP_EVENT_CANCEL_REMAIN_ON_CHANNEL,
    WPA_ELOOP_EVENT_CHANNEL_SWITCH,
    WPA_ELOOP_EVENT_EAPOL_RECV,
    WPA_ELOOP_EVENT_TIMEOUT_DISCONN,
    WPA_ELOOP_EVENT_BUTT
} WpaEloopEventType;

int32_t WifiWpaDriverEventProcess(const char *ifname, uint32_t event, struct HdfSBuf *reqData);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of wpa_hal_event.h */
