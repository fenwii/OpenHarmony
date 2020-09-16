/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef HDF_NET_DEVICE_IMPL_MODULE_H
#define HDF_NET_DEVICE_IMPL_MODULE_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "net_device.h"

#define MAX_NETDEVICE_COUNT 20

struct NetDeviceImpl {
    struct NetDevice *netDevice;
    struct NetDeviceImplOp *interFace;
    void *osPrivate;
};
typedef enum {
    NO_IN_INTERRUPT,
    IN_INTERRUPT,
    MAX_RECEIVE_FLAGE
} ReceiveFlage;

struct NetDeviceImplOp {
    int32_t (*init)(struct NetDeviceImpl *netDevice);
    int32_t (*deInit)(struct NetDeviceImpl *netDevice);
    int32_t (*add)(struct NetDeviceImpl *netDevice, Protocol80211IfType ifType);
    int32_t (*delete)(struct NetDeviceImpl *netDevice);
    int32_t (*setStatus)(struct NetDeviceImpl *netDevice, NetIfStatus status);
    int32_t (*setLinkStatus)(struct NetDeviceImpl *netDevice, NetIfLinkStatus status);
    int32_t (*receive)(struct NetDeviceImpl *netDevice, struct NetBuf *buff, ReceiveFlage flage);
    int32_t (*setIpAddr)(struct NetDeviceImpl *netDevice, const IpV4Addr *ipAddr, const IpV4Addr *netMask,
        const IpV4Addr *gw);
    int32_t (*dhcpsStart)(struct NetDeviceImpl *netDevice, char *ip, uint16_t ipNum);
    int32_t (*dhcpsStop)(struct NetDeviceImpl *netDevice);
    int32_t (*dhcpStart)(struct NetDeviceImpl *netDevice);
    int32_t (*dhcpStop)(struct NetDeviceImpl *netDevice);
    int32_t (*dhcpIsBound)(struct NetDeviceImpl *netDevice);
};

#endif /* HDF_NET_DEVICE_IMPL_MODULE_H */