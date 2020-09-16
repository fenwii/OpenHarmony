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

#include "net_device.h"

#include <stdlib.h>
#include <string.h>
#include "securec.h"

#include "osal_mem.h"
#include "net_device_impl.h"
#include "net_device_adapter.h"

#define HDF_LOG_TAG "NetDevice"

static struct NetDeviceImpl *g_netDeviceImplTable[MAX_NETDEVICE_COUNT] = {NULL};

static bool FindAvailableTable(int32_t *index)
{
    if (index == NULL) {
        HDF_LOGE("Find Available table index error!");
        return false;
    }
    for (int32_t i = 0; i < MAX_NETDEVICE_COUNT; i++) {
        if (g_netDeviceImplTable[i] == NULL) {
            *index = i;
            return true;
        }
    }
    return false;
}

static bool AddNetDeviceImplToTable(int32_t index, struct NetDeviceImpl *netDeviceImpl)
{
    if (index >= MAX_NETDEVICE_COUNT) {
        HDF_LOGE("%s error because of not enough space!", __func__);
        return false;
    }
    g_netDeviceImplTable[index] = netDeviceImpl;
    return true;
}

static void DeleteNetDeviceImplFromTable(const struct NetDeviceImpl *netDeviceImpl)
{
    for (int32_t i = 0; i < MAX_NETDEVICE_COUNT; i++) {
        if (g_netDeviceImplTable[i] == netDeviceImpl) {
            g_netDeviceImplTable[i] = NULL;
            return;
        }
    }
    return;
}

static struct NetDeviceImpl *InitNetDeviceImpl(NetDevice *nd, NetIfCategory ifCategory)
{
    struct NetDeviceImpl *ndImpl = NULL;
    if (nd == NULL) {
        return NULL;
    }
    ndImpl = (struct NetDeviceImpl *)OsalMemCalloc(sizeof(struct NetDeviceImpl));
    if (ndImpl == NULL) {
        HDF_LOGE("%s fail: OsalMemCalloc fail!", __func__);
        return NULL;
    }
    (void)memset_s(ndImpl, sizeof(struct NetDeviceImpl), 0, sizeof(struct NetDeviceImpl));

    ndImpl->netDevice = nd;
    if (ifCategory == LITE_OS) {
        if (RegisterLiteNetDeviceImpl(ndImpl) != HDF_SUCCESS) {
            HDF_LOGE("%s fail: resiter lite impl fail!", __func__);
            OsalMemFree(ndImpl);
            ndImpl = NULL;
        }
    } else {
        HDF_LOGE("%s fail: resister not support!", __func__);
        OsalMemFree(ndImpl);
        ndImpl = NULL;
    }
    return ndImpl;
}

static void DeInitNetDeviceImpl(struct NetDeviceImpl *netDeviceImpl)
{
    if (netDeviceImpl == NULL) {
        HDF_LOGE("%s success : already free!", __func__);
        return;
    }

    /* release osPrivate */
    if (netDeviceImpl->interFace != NULL && netDeviceImpl->interFace->deInit != NULL) {
        netDeviceImpl->interFace->deInit(netDeviceImpl);
    }

    /* step 1 : release interFace. step 2 : release netdevice */
    if (netDeviceImpl->netDevice != NULL) {
        if (netDeviceImpl->netDevice->netifCateg == LITE_OS) {
            UnRegisterLiteNetDeviceImpl(netDeviceImpl);
        } else {
            HDF_LOGE("%s fail: unregister not support!", __func__);
        }
        OsalMemFree(netDeviceImpl->netDevice);
        netDeviceImpl->netDevice = NULL;
    }

    /* last release netDeviceImpl */
    OsalMemFree(netDeviceImpl);
    HDF_LOGI("%s success!", __func__);
    return;
}

static struct NetDeviceImpl *GetImplByNetDevice(const struct NetDevice *netDevice)
{
    struct NetDeviceImpl *ndImpl = NULL;
    for (int32_t i = 0; i < MAX_NETDEVICE_COUNT; i++) {
        if (g_netDeviceImplTable[i] != NULL && g_netDeviceImplTable[i]->netDevice != NULL) {
            if (netDevice == g_netDeviceImplTable[i]->netDevice) {
                ndImpl = g_netDeviceImplTable[i];
                return ndImpl;
            }
        }
    }
    HDF_LOGE("Don't Get Impl by netdevice");
    return ndImpl;
}

struct NetDevice *NetDeviceInit(const char *ifName, uint32_t len, NetIfCategory ifCategory)
{
    NetDevice *netDevice = NULL;
    int32_t index = 0;
    if ((ifName == NULL) || (strlen(ifName) != len) || (strlen(ifName) > IFNAMSIZ - 1)) {
        HDF_LOGE("%s fail: ifName = null or len not right!", __func__);
        return NULL;
    }
    netDevice = (NetDevice *)OsalMemCalloc(sizeof(NetDevice));
    if (netDevice == NULL) {
        HDF_LOGE("%s fail: OsalMemCalloc fail!", __func__);
        return NULL;
    }
    (void)memset_s(netDevice, sizeof(NetDevice), 0, sizeof(NetDevice));
    if (memcpy_s(netDevice->name, IFNAMSIZ, ifName, len + 1) != EOK) {
        HDF_LOGE("%s fail: memcpy_s fail!", __func__);
        OsalMemFree(netDevice);
        return NULL;
    }
    netDevice->netifCateg = ifCategory;
    struct NetDeviceImpl *ndImpl = InitNetDeviceImpl(netDevice, ifCategory);
    if (ndImpl == NULL) {
        HDF_LOGE("%s fail: InitNetDeviceImpl fail!", __func__);
        OsalMemFree(netDevice);
        return NULL;
    }
    if (FindAvailableTable(&index)) {
        AddNetDeviceImplToTable(index, ndImpl);
    } else {
        DeInitNetDeviceImpl(ndImpl);
        HDF_LOGE("%s fail: Not extra table.", __func__);
        return NULL;
    }
    /* INIT OSPrivate */
    int32_t ret = HDF_FAILURE;
    if (ndImpl->interFace != NULL && ndImpl->interFace->init != NULL) {
        ret = ndImpl->interFace->init(ndImpl);
    }
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("%s fail : interface->init fail!", __func__);
        DeleteNetDeviceImplFromTable(ndImpl);
        DeInitNetDeviceImpl(ndImpl);
        return NULL;
    }
    HDF_LOGI("Init Net Device suncess!");
    return netDevice;
}

int32_t NetDeviceDeInit(struct NetDevice *netDevice)
{
    if (netDevice == NULL) {
        HDF_LOGI("%s success: already deinit!", __func__);
        return HDF_SUCCESS;
    }
    struct NetDeviceImpl *ndImpl = GetImplByNetDevice(netDevice);
    if (ndImpl == NULL) {
        HDF_LOGI("%s success: already free.", __func__);
        OsalMemFree(netDevice);
        return HDF_SUCCESS;
    }
    DeleteNetDeviceImplFromTable(ndImpl);
    DeInitNetDeviceImpl(ndImpl);
    return HDF_SUCCESS;
}

int32_t NetDeviceAdd(struct NetDevice *netDevice, Protocol80211IfType ifType)
{
    struct NetDeviceImplOp *op = NULL;
    struct NetDeviceImpl *ndImpl = GetImplByNetDevice(netDevice);
    if (ndImpl == NULL) {
        HDF_LOGE("%s fail: netDevice not exist!", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    op = ndImpl->interFace;
    if (op == NULL || op->add == NULL) {
        HDF_LOGE("%s fail: Impl Add not exist.", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    return op->add(ndImpl, ifType);
}

int32_t NetDeviceDelete(struct NetDevice *netDevice)
{
    struct NetDeviceImplOp *op = NULL;
    struct NetDeviceImpl *ndImpl = GetImplByNetDevice(netDevice);
    if (ndImpl == NULL) {
        HDF_LOGE("%s fail: netDevice not exist!", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    op = ndImpl->interFace;
    if (op == NULL || op->delete == NULL) {
        HDF_LOGE("%s fail: Impl op Delete exist.", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    return op->delete(ndImpl);
}

struct NetDevice *NetDeviceGetInstByName(const char *name)
{
    if (name == NULL) {
        HDF_LOGE("%s fail: name = NULL.", __func__);
        return NULL;
    }
    for (int32_t i = 0; i < MAX_NETDEVICE_COUNT; i++) {
        if (g_netDeviceImplTable[i] != NULL && g_netDeviceImplTable[i]->netDevice != NULL) {
            if (strcmp(g_netDeviceImplTable[i]->netDevice->name, name) == 0) {
                return g_netDeviceImplTable[i]->netDevice;
            }
        }
    }
    HDF_LOGE("%s fail: name not exist.", __func__);
    return NULL;
}

bool NetDeviceIsAnyInstRunning(void)
{
    struct NetDevice *netDev = NULL;
    for (int32_t i = 0; i < MAX_NETDEVICE_COUNT; i++) {
        if (g_netDeviceImplTable[i] != NULL && g_netDeviceImplTable[i]->netDevice != NULL) {
            netDev = g_netDeviceImplTable[i]->netDevice;
            if ((GET_NET_DEV_FLAGS(netDev) & NET_DEVICE_IFF_RUNNING) != 0) {
                return true;
            }
        }
    }
    return false;
}

bool NetDeviceIsInstRunning(const struct NetDevice *netDevice)
{
    if (netDevice == NULL) {
        return false;
    }
    if ((GET_NET_DEV_FLAGS(netDevice) & NET_DEVICE_IFF_RUNNING) != 0) {
        return true;
    }
    return false;
}

uint32_t NetDevGetRegisterCount(void)
{
    uint32_t count = 0;
    for (int32_t i = 0; i < MAX_NETDEVICE_COUNT; i++) {
        if (g_netDeviceImplTable[i] != NULL && g_netDeviceImplTable[i]->netDevice != NULL) {
            count++;
        }
    }
    return count;
}

uint32_t NetDeviceGetCap(void)
{
    return MAX_NETDEVICE_COUNT;
}

struct NetDevice *NetDeviceGetInstByIndex(uint32_t index)
{
    if (index < MAX_NETDEVICE_COUNT) {
        if (g_netDeviceImplTable[index] != NULL) {
            return g_netDeviceImplTable[index]->netDevice;
        } else {
            return NULL;
        }
    }
    return NULL;
}

int32_t NetIfSetAddr(const struct NetDevice *netDevice, const IpV4Addr *ipAddr, const IpV4Addr *netMask,
    const IpV4Addr *gw)
{
    struct NetDeviceImpl *ndImpl = GetImplByNetDevice(netDevice);
    if (ndImpl != NULL && ndImpl->interFace != NULL && ndImpl->interFace->setIpAddr != NULL) {
        return ndImpl->interFace->setIpAddr(ndImpl, ipAddr, netMask, gw);
    }
    HDF_LOGE("%s: netDevice not init or already free.", __func__);
    return HDF_ERR_INVALID_PARAM;
}

static int32_t NetIfRxImpl(const struct NetDevice *netDevice, struct NetBuf *buff, ReceiveFlage flage)
{
    struct NetDeviceImpl *ndImpl = GetImplByNetDevice(netDevice);
    if (ndImpl == NULL || ndImpl->interFace == NULL || ndImpl->interFace->receive == NULL) {
        HDF_LOGE("NetIfRxImpl fail : netdevice not exist!");
        return HDF_ERR_INVALID_PARAM;
    }
    ProcessingResult ret = PROCESSING_CONTINUE;

    /* to do driver special process */
#if LOSCFG_NET_LWIP_SACK
    if (netDevice->netDeviceIf != NULL && netDevice->netDeviceIf->specialEtherTypeProcess != NULL) {
        ret = netDevice->netDeviceIf->specialEtherTypeProcess(netDevice, buff);
    }
#endif
    /* Sent to TCP/IP Stack. */
    if (ret == PROCESSING_CONTINUE) {
        return ndImpl->interFace->receive(ndImpl, buff, flage);
    } else if (ret == PROCESSING_COMPLETE) {
        HDF_LOGI("NetIfRxImpl specialEtherType Process not need TCP/IP stack!");
        return HDF_SUCCESS;
    } else {
        HDF_LOGE("NetIfRxImpl specialEtherType Process error");
        return HDF_FAILURE;
    }
}

int32_t NetIfRx(const struct NetDevice *netDevice, struct NetBuf *buff)
{
    return NetIfRxImpl(netDevice, buff, NO_IN_INTERRUPT);
}

int32_t NetIfRxNi(const struct NetDevice *netDevice, struct NetBuf *buff)
{
    return NetIfRxImpl(netDevice, buff, IN_INTERRUPT);
}

int32_t NetIfSetStatus(const struct NetDevice *netDevice, NetIfStatus status)
{
    struct NetDeviceImpl *ndImpl = GetImplByNetDevice(netDevice);
    if (ndImpl != NULL && ndImpl->interFace != NULL && ndImpl->interFace->setStatus != NULL) {
        return ndImpl->interFace->setStatus(ndImpl, status);
    }
    HDF_LOGE("%s: netDevice not init or already free.", __func__);
    return HDF_ERR_INVALID_PARAM;
}

int32_t NetIfSetLinkStatus(const struct NetDevice *netDevice, NetIfLinkStatus status)
{
    struct NetDeviceImpl *ndImpl = GetImplByNetDevice(netDevice);
    if (ndImpl != NULL && ndImpl->interFace != NULL && ndImpl->interFace->setLinkStatus != NULL) {
        return ndImpl->interFace->setLinkStatus(ndImpl, status);
    }
    HDF_LOGE("%s: netDevice not init or already free.", __func__);
    return HDF_ERR_INVALID_PARAM;
}

int32_t NetIfDhcpsStart(const struct NetDevice *netDevice, char *ip, uint16_t ipNum)
{
    struct NetDeviceImpl *ndImpl = GetImplByNetDevice(netDevice);
    if (ndImpl != NULL && ndImpl->interFace != NULL && ndImpl->interFace->dhcpsStart != NULL) {
        return ndImpl->interFace->dhcpsStart(ndImpl, ip, ipNum);
    }
    HDF_LOGE("%s: netDevice not init or already free.", __func__);
    return HDF_ERR_INVALID_PARAM;
}

int32_t NetIfDhcpsStop(const struct NetDevice *netDevice)
{
    struct NetDeviceImpl *ndImpl = GetImplByNetDevice(netDevice);
    if (ndImpl != NULL && ndImpl->interFace != NULL && ndImpl->interFace->dhcpsStop != NULL) {
        return ndImpl->interFace->dhcpsStop(ndImpl);
    }
    HDF_LOGE("%s: netDevice not init or already free.", __func__);
    return HDF_ERR_INVALID_PARAM;
}

int32_t NetIfDhcpStart(const struct NetDevice *netDevice)
{
    struct NetDeviceImpl *ndImpl = GetImplByNetDevice(netDevice);
    if (ndImpl != NULL && ndImpl->interFace != NULL && ndImpl->interFace->dhcpStart != NULL) {
        return ndImpl->interFace->dhcpStart(ndImpl);
    }
    HDF_LOGE("%s: netDevice not init or already free.", __func__);
    return HDF_ERR_INVALID_PARAM;
}

int32_t NetIfDhcpStop(const struct NetDevice *netDevice)
{
    struct NetDeviceImpl *ndImpl = GetImplByNetDevice(netDevice);
    if (ndImpl != NULL && ndImpl->interFace != NULL && ndImpl->interFace->dhcpStop != NULL) {
        return ndImpl->interFace->dhcpStop(ndImpl);
    }
    HDF_LOGE("%s: netDevice not init or already free.", __func__);
    return HDF_ERR_INVALID_PARAM;
}

int32_t NetIfDhcpIsBound(const struct NetDevice *netDevice)
{
    struct NetDeviceImpl *ndImpl = GetImplByNetDevice(netDevice);
    if (ndImpl != NULL && ndImpl->interFace != NULL && ndImpl->interFace->dhcpIsBound != NULL) {
        return ndImpl->interFace->dhcpIsBound(ndImpl);
    }
    HDF_LOGE("%s: netDevice not init or already free.", __func__);
    return HDF_ERR_INVALID_PARAM;
}

/*
 * Alloc a net buffer for the net device and reserve headroom depended on net device setting
 *
 * @param  : dev The net device
 *           size The net buffer size
 * @return : A new net buffer on success or NULL on fail
 */
struct NetBuf *NetBufDevAlloc(const struct NetDevice *dev, uint32_t size)
{
    uint32_t reserve = 0;
    struct NetBuf *nb = NULL;

    if (dev != NULL) {
        reserve = dev->neededHeadRoom + dev->neededTailRoom;
    }

    size += reserve;

    nb = NetBufAlloc(size);
    if (nb == NULL) {
        return NULL;
    }

    if (dev != NULL) {
        nb->dev = (void *)dev;
        NetBufPop(nb, E_TAIL_BUF, dev->neededHeadRoom);
        NetBufPop(nb, E_DATA_BUF, dev->neededHeadRoom);
    }

    return nb;
}
