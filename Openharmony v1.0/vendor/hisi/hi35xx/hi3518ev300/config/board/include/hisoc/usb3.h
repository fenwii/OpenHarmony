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

#ifndef __HISOC_USB3_H__
#define __HISOC_USB3_H__

#include "los_base.h"
#include "board.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define CONFIG_HIUSB_XHCI_IOBASE    0x10030000
#define CONFIG_HIUSB_XHCI_IOSIZE    0x10000

#define DWC_USB3_PORT1_BASE_ADDR    CONFIG_HIUSB_XHCI_IOBASE
#define DWC_USB3_PORT1_ADDR_OFFSET  0xc000

#define USB_CACHE_ALIGN_SIZE        64
#define ALIGNBYTES                  3
#define SKB_DATA_ALIGN(X)           ALIGN(X, USB_CACHE_ALIGN_SIZE)
#define UVC_USE_CTRL_EP             1

#define FMASS_DEV_PATH              "/dev/mmcblk0p"

extern VOID HiUsb3StartHcd(VOID);
extern VOID HiUsb3StopHcd(VOID);
extern VOID HiUsb3Host2Device(VOID);
extern BOOL HiUsbIsDeviceMode(VOID);
extern VOID UsbOtgSwSetDeviceState(VOID);
extern VOID UsbOtgSwClearDeviceState(VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif
