# Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
# Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this list of
#    conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice, this list
#    of conditions and the following disclaimer in the documentation and/or other materials
#    provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its contributors may be used
#    to endorse or promote products derived from this software without specific prior written
#    permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

include $(LITEOSTOPDIR)/config.mk

MODULE_NAME := usb_base

CONTROLLER_HOST_SRC = controller
CORE_SRC = .
IMPLEMENTATION_SRC = implementation
Net_SRC = net
QUIRK_SRC = quirk
SERIAL_SRC = serial
STORAGE_SRC = storage
INPUT_SRC = input
LOCAL_SRCS := $(CORE_SRC)/usb_debug.c  \
              $(IMPLEMENTATION_SRC)/bsd_busspace.c  \
              $(IMPLEMENTATION_SRC)/usb_busdma_loader.c  \
              $(IMPLEMENTATION_SRC)/bsd_kernel.c \
              $(IMPLEMENTATION_SRC)/usb_init.c  \
              $(IMPLEMENTATION_SRC)/usb_version.c \
              $(IMPLEMENTATION_SRC)/usb_btree.c

ifeq ($(LOSCFG_DRIVERS_USB), y)
LOCAL_SRCS += $(CORE_SRC)/usb_dynamic.c  \
              $(CORE_SRC)/usb_parse.c  \
              $(CORE_SRC)/usb_error.c  \
              $(CORE_SRC)/usb_handle_request.c  \
              $(CORE_SRC)/usb_util.c  \
              $(CORE_SRC)/usb_lookup.c  \
              $(CONTROLLER_HOST_SRC)/usb_controller.c  \
              $(QUIRK_SRC)/usb_quirk.c \
              $(CORE_SRC)/usb_device.c  \
              $(CORE_SRC)/usb_process.c  \
              $(CORE_SRC)/usb_hub.c  \
              $(CORE_SRC)/usb_request.c  \
              $(CORE_SRC)/usb_transfer.c  \
              $(CORE_SRC)/usb_dev.c  \
              $(CORE_SRC)/usb_mbuf.c  \
              $(CORE_SRC)/usb_generic.c \
              $(CORE_SRC)/usb_if.c
endif

ifeq ($(LOSCFG_DRIVERS_USB_4G_MODEM), y)
LOCAL_SRCS += $(Net_SRC)/if_cdce.c
endif

ifeq ($(LOSCFG_DRIVERS_USB_ETHERNET), y)
LOCAL_SRCS += $(Net_SRC)/if_axe.c \
              $(Net_SRC)/if_axge.c
endif

ifeq ($(LOSCFG_DRIVERS_USB_RNDIS_HOST), y)
LOCAL_SRCS += $(Net_SRC)/if_urndis.c
endif

ifeq ($(LOSCFG_DRIVERS_USB_4G_MODEM), y)
LOCAL_SRCS += $(Net_SRC)/usb_eth_drv.c \
              $(Net_SRC)/usb_ethernet.c
else ifeq ($(LOSCFG_DRIVERS_USB_ETHERNET), y)
LOCAL_SRCS += $(Net_SRC)/usb_eth_drv.c \
              $(Net_SRC)/usb_ethernet.c
else ifeq ($(LOSCFG_DRIVERS_USB_RNDIS_HOST), y)
LOCAL_SRCS += $(Net_SRC)/usb_eth_drv.c\
              $(Net_SRC)/usb_ethernet.c
endif

ifeq ($(LOSCFG_DRIVERS_USB_4G_MODEM), y)
LOCAL_SRCS += $(SERIAL_SRC)/usb_serial.c  \
              $(SERIAL_SRC)/u3g.c
else ifeq ($(LOSCFG_DRIVERS_USB_SERIAL), y)
LOCAL_SRCS += $(SERIAL_SRC)/usb_serial.c  \
              $(SERIAL_SRC)/u3g.c
endif

ifeq ($(LOSCFG_DRIVERS_USB_HOST_EHCI), y)
LOCAL_SRCS += $(CONTROLLER_HOST_SRC)/ehci_pci.c  \
              $(CONTROLLER_HOST_SRC)/ehci.c
endif

ifeq ($(LOSCFG_DRIVERS_USB_HOST_XHCI), y)
LOCAL_SRCS += $(CONTROLLER_HOST_SRC)/xhci.c  \
              $(CONTROLLER_HOST_SRC)/xhci_pci.c
else ifeq ($(LOSCFG_DRIVERS_USB_HOST_XHCI_FOR_PORT2), y)
LOCAL_SRCS += $(CONTROLLER_HOST_SRC)/xhci.c  \
              $(CONTROLLER_HOST_SRC)/xhci_pci.c
endif

ifeq ($(LOSCFG_DRIVERS_USB_WIRELESS), y)
LOCAL_SRCS += $(CORE_SRC)/linux_usb.c
endif

ifeq ($(LOSCFG_DRIVERS_USB_MASS_STORAGE), y)
LOCAL_SRCS += $(STORAGE_SRC)/umass.c
endif

ifeq ($(LOSCFG_DRIVERS_USB_HID_CLASS), y)
LOCAL_SRCS += $(INPUT_SRC)/uhid.c  \
              $(CORE_SRC)/usb_hid.c
endif

LOCAL_FLAGS += $(LITEOS_GCOV_OPTS)

include $(MODULE)

