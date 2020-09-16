/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2013-2016. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Description: declaration of link quality APIs
 * Author: none
 * Create: 2013-12-22
 */

#ifndef __LINK_QUALITY_H__
#define __LINK_QUALITY_H__

#include "lwip/opt.h"
#include "lwip/netif.h"

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif

#ifndef LWIP_RPL_USE_MACACK_FOR_NBR
#define LWIP_RPL_USE_MACACK_FOR_NBR 1
#endif

typedef unsigned char LQI_TYPE;
typedef signed char RSSI_TYPE;

struct netif;
struct linklayer_addr;

typedef struct _lwip_nbr_linkquality {
  /* Link Metric is derived from ETX */
  u16_t link_metric;
} lwip_nbr_linkquality_t;

void lwip_update_nbr_signal_quality
(
  const struct netif *linkiface,
  const struct linklayer_addr *sendermac,
  RSSI_TYPE link_rssi,
  LQI_TYPE link_lqi
);

typedef enum mac_status {
  MAC_STATUS_TX_ACK_OK = 0,
  MAC_STATUS_MAX_RETRIES,
  MAC_STATUS_ERR_FATAL,
  /*
   * case of wifi, beacon unavailability can be used to decide peer unreachability.
   * In this case if the peer is a parent, then the parent entry should be removed.
   */
  MAC_STATUS_PEER_UNREACHABLE,
  MAC_STATUS_DROP_POLICY,
  MAC_STATUS_BUTT
} mac_status_e;

int lwip_get_rssi(void);

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* __LINK_QUALITY_H__ */

