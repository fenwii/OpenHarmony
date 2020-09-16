/*
 * Driver interaction with hdf wifi
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef _WPA_MSG_SERVICE_H_
#define _WPA_MSG_SERVICE_H_

#include <stdlib.h>
#include "hdf_sbuf.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define WPA_MSG_SERVICE_ID 0x3
#define WAL_MSG_SERVICE_ID 0x4

#define WIFI_WPA_EVENT_MSG 0

int32_t WpaMsgServiceInit(void);
void WpaMsgServiceDeinit(void);
int32_t WifiWpaCmdBlockSyncSend(const uint32_t cmd, struct HdfSBuf *data, struct HdfSBuf *respData);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif /* end of wpa_msg_sevice.h */
