/* Copyright 2020 Huawei Device Co., Ltd.
 *
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

#include "uart_dev_sample.h"
#include "fs/fs.h"
#include "securec.h"
#include "user_copy.h"
#include "hdf_log.h"
#include "osal_mem.h"
#include "uart_pl011_sample.h"

#define HDF_LOG_TAG hdf_uart_dev
#define HDF_UART_FS_MODE 0660

static int32_t UartSampleDevOpen(FAR struct file *filep)
{
    struct inode *inode = NULL;
    struct UartHost *host = NULL;

    if (filep == NULL || filep->f_inode == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    inode = (struct inode *)filep->f_inode;
    host = (struct UartHost *)inode->i_private;
    if (host == NULL) {
        HDF_LOGE("%s: host is NULL", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    HDF_LOGI("%s: open uart%d success", __func__, host->num);
    return HDF_SUCCESS;
}
static int32_t UartSampleRelease(FAR struct file *filep)
{
    struct inode *inode = NULL;
    struct UartHost *host = NULL;

    if (filep == NULL || filep->f_inode == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    inode = (struct inode *)filep->f_inode;
    host = (struct UartHost *)inode->i_private;
    if (host == NULL) {
        HDF_LOGE("%s: host is NULL", __func__);
        return HDF_ERR_INVALID_PARAM;
    }
    HDF_LOGI("%s: close uart%d success", __func__, host->num);
    return HDF_SUCCESS;
}

static ssize_t UartSampleRead(FAR struct file *filep, FAR char *buf, size_t count)
{
    int32_t ret;
    uint8_t *tmpBuf = NULL;
    struct inode *inode = NULL;
    struct UartHost *host = NULL;

    if (filep == NULL || filep->f_inode == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    inode = (struct inode *)filep->f_inode;
    host = (struct UartHost *)inode->i_private;
    if (LOS_IsUserAddressRange((vaddr_t)buf, count)) {
        tmpBuf = (uint8_t *)OsalMemCalloc(count);
        if (tmpBuf == NULL) {
            HDF_LOGE("%s: OsalMemCalloc error", __func__);
            return HDF_ERR_MALLOC_FAIL;
        }
        ret = UartHostRead(host, tmpBuf, count);
        if (ret == HDF_SUCCESS) {
            ret = LOS_ArchCopyToUser(buf, tmpBuf, count);
        }
        OsalMemFree(tmpBuf);
        return ret;
    } else {
        return UartHostRead(host, (uint8_t *)buf, count);
    }
}

static ssize_t UartSampleWrite(struct file *filep, const char *buf, size_t count)
{
    int32_t ret;
    uint8_t *tmpBuf = NULL;
    struct inode *inode = NULL;
    struct UartHost *host = NULL;

    if (filep == NULL || filep->f_inode == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    inode = (struct inode *)filep->f_inode;
    host = (struct UartHost *)inode->i_private;
    if (LOS_IsUserAddressRange((vaddr_t)buf, count)) {
        tmpBuf = (uint8_t *)OsalMemCalloc(count);
        if (tmpBuf == NULL) {
            HDF_LOGE("%s: OsalMemCalloc error", __func__);
            return HDF_ERR_MALLOC_FAIL;
        }
        ret = LOS_ArchCopyFromUser(tmpBuf, buf, count);
        if (ret != LOS_OK) {
            OsalMemFree(tmpBuf);
            return ret;
        }
        ret = UartHostWrite(host, tmpBuf, count);
        OsalMemFree(tmpBuf);
        return ret;
    } else {
        return UartHostWrite(host, (uint8_t *)buf, count);
    }
}

static int32_t UartSampleDevIoctl(FAR struct file *filep, int32_t cmd, unsigned long arg)
{
    int32_t ret = HDF_FAILURE;
    struct UartHost *host = NULL;
    struct inode *inode = NULL;
    if (filep == NULL || filep->f_inode == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    inode = (struct inode *)filep->f_inode;
    if (inode->i_private == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    host = (struct UartHost *)inode->i_private;
    if (host->priv == NULL) {
        return HDF_ERR_INVALID_PARAM;
    }
    HDF_LOGE("%s: num %d", __func__, host->num);
    switch (cmd) {
        case UART_CFG_BAUDRATE:
            ret = UartHostSetBaud(host, arg);
            break;
        default:
            HDF_LOGE("%s cmd %d not support", __func__, cmd);
            ret = HDF_ERR_NOT_SUPPORT;
            break;
    }
    return ret;
}

const struct file_operations_vfs g_uartSampleDevFops = {
    .open   = UartSampleDevOpen,
    .close  = UartSampleRelease,
    .read   = UartSampleRead,
    .write  = UartSampleWrite,
    .ioctl  = UartSampleDevIoctl,
};

#define MAX_DEV_NAME_SIZE 32
static void UartSampleAddRemoveDev(struct UartHost *host, bool add)
{
    int32_t ret;
    char *devName = NULL;

    if (host == NULL || host->priv == NULL) {
        HDF_LOGE("%s invalid parameter", __func__);
        return;
    }
    devName = (char *)OsalMemCalloc(sizeof(char) * (MAX_DEV_NAME_SIZE + 1));
    if (devName == NULL) {
        HDF_LOGE("%s: OsalMemCalloc error", __func__);
        return;
    }
    ret = snprintf_s(devName, MAX_DEV_NAME_SIZE + 1, MAX_DEV_NAME_SIZE, "/dev/uartdev-%d", host->num);
    if (ret < 0) {
        HDF_LOGE("%s snprintf_s failed", __func__);
        OsalMemFree(devName);
        return;
    }
    if (add) {
        if (register_driver(devName, &g_uartSampleDevFops, HDF_UART_FS_MODE, host)) {
            HDF_LOGE("%s: gen /dev/uartdev-%d fail!", __func__, host->num);
            OsalMemFree(devName);
            return;
        }
    } else {
        if (unregister_driver(devName)) {
            HDF_LOGE("%s: remove /dev/uartdev-%d fail!", __func__, host->num);
            OsalMemFree(devName);
            return;
        }
    }
    OsalMemFree(devName);
}

void UartSampleAddDev(struct UartHost *host)
{
    UartSampleAddRemoveDev(host, true);
}

void UartSampleRemoveDev(struct UartHost *host)
{
    UartSampleAddRemoveDev(host, false);
}
