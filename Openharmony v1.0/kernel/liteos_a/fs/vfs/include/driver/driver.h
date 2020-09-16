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

#ifndef __FS_DRIVER_DRIVER_H
#define __FS_DRIVER_DRIVER_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "vfs_config.h"
#include "fs/fs.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
* Global Variables
****************************************************************************/

extern FAR struct inode *g_root_inode;

/**
 * @ingroup  disk
 * @brief Set usb mode.
 *
 * @par Description:
 * Set the corresponding bit of g_usbMode as usb host mode.
 *
 * @attention
 * <ul>
 * <li>diskId should be [0,SYS_MAX_DISK)</li>
 * </ul>
 *
 * @param  diskId      [IN]  Type # unsigned int  disk id.
 *
 * @par Dependency:
 * <ul><li>driver.h</li></ul>
 * @see OsClearUsbStatus
 *
 */
VOID OsSetUsbStatus(UINT32 diskId);

/**
 * @ingroup  disk
 * @brief Set usb mode.
 *
 * @par Description:
 * Clear the corresponding bit of g_usbMode as usb host mode.
 *
 * @attention
 * <ul>
 * <li>diskId should be [0,SYS_MAX_DISK)</li>
 * </ul>
 *
 * @param  diskId      [IN]  Type # unsigned int  disk id.
 *
 * @par Dependency:
 * <ul><li>driver.h</li></ul>
 * @see OsSetUsbStatus
 *
 */
VOID OsClearUsbStatus(UINT32 diskId);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
#endif /* __FS_DRIVER_DRIVER_H */
