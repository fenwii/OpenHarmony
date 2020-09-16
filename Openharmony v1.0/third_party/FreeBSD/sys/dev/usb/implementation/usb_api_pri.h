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

#ifndef _USB_API_H
#define	_USB_API_H

#include <los_config.h>
#include "sys/module.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/* extern struct module_data bsd_##name##_##busname##_driver_mod */
#ifdef LOSCFG_DRIVERS_USB_HOST_EHCI
/* host or device controller modules */
/* usb controller modules  link xxx-controller bus */
extern struct driver_module_data usbus_ehci_driver_mod;
#endif

#ifdef LOSCFG_DRIVERS_USB_HOST_XHCI
extern struct driver_module_data usbus_xhci_driver_mod;
#endif

#ifdef LOSCFG_DRIVERS_USB_HOST_DRIVER
/* root hub driver modules  link to usb bus */
extern struct driver_module_data uhub_usbus_driver_mod;
/* xxx class driver moudles  link to usb hub bus */
extern struct driver_module_data uhub_uhub_driver_mod;
#endif

#ifdef LOSCFG_DRIVERS_USB_4G_MODEM
extern struct driver_module_data cdce_uhub_driver_mod;
#endif

#if defined (LOSCFG_DRIVERS_USB_SERIAL) || defined (LOSCFG_DRIVERS_USB_4G_MODEM)
extern struct driver_module_data u3g_uhub_driver_mod;
#endif

#ifdef LOSCFG_DRIVERS_USB_ETHERNET
extern struct driver_module_data axe_uhub_driver_mod;
extern struct driver_module_data axge_uhub_driver_mod;
#endif

#ifdef LOSCFG_DRIVERS_USB_RNDIS_HOST
extern struct driver_module_data urndis_uhub_driver_mod;
#endif

#ifdef LOSCFG_DRIVERS_USB_MASS_STORAGE
extern struct driver_module_data umass_uhub_driver_mod;
#endif

#ifdef LOSCFG_DRIVERS_USB_WIRELESS
extern struct driver_module_data usb_linux_uhub_driver_mod;
#endif

#ifdef LOSCFG_DRIVERS_USB_HID_CLASS
extern struct driver_module_data uhid_uhub_driver_mod;
#endif

#ifdef LOSCFG_DRIVERS_USB_HOST_XHCI
int hixhci_init(void);
#endif

#ifdef LOSCFG_DRIVERS_USB_HOST_EHCI
int hiehci_init(void);
#endif

#ifdef LOSCFG_USB_DEBUG
void usb_debug_module_regsiter(void);
void usb_debug_module_unregsiter(void);
#endif

const char* fetach_usbversion(void);

volatile unsigned int userial_mask_get(void);
void userial_mask_set(unsigned int val);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* _USB_API_H */

