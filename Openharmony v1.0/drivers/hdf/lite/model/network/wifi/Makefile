# Copyright (c) 2020 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

include $(LITEOSTOPDIR)/config.mk
include $(LITEOSTOPDIR)/../../drivers/hdf/lite/lite.mk

MODULE_NAME := hdf_wifi_model
HDM_WIFI_ROOT = $(LITEOSTOPDIR)/../../drivers/hdf/frameworks/model/network/wifi

##################path of compile file :start###############
##### hdm #####
#WPHY_PATH := $(HDM_WIFI_ROOT)/compoments/wphy
#WMAC_PATH := $(HDM_WIFI_ROOT)/compoments/wmac
WAP_PATH := $(HDM_WIFI_ROOT)/compoments/softap
WSTA_PATH := $(HDM_WIFI_ROOT)/compoments/sta
WEAPOL_PATH := $(HDM_WIFI_ROOT)/compoments/eapol
NETDEV_PATH := $(HDM_WIFI_ROOT)/netdevice
MODULE_PATH := $(HDM_WIFI_ROOT)/module
INC_PATH := $(HDM_WIFI_ROOT)/include
INC_WIFI_PATH := $(LITEOSTOPDIR)/../../drivers/hdf/frameworks/include/wifi
##################path of compile file :end###############


WIFI_CFLAGS += -I $(INC_PATH) \
		-I $(WSTA_PATH) \
		-I $(WAP_PATH) \
		-I $(WEAPOL_PATH) \
		-I $(NETDEV_PATH) \
		-I $(MODULE_PATH) \
		-I $(INC_WIFI_PATH)


LOCAL_SRCS += $(WAP_PATH)/ap.c \
			$(WEAPOL_PATH)/eapol.c \
			$(WSTA_PATH)/sta.c \
			$(NETDEV_PATH)/net_device.c \
			$(MODULE_PATH)/wifi_module.c \
			$(MODULE_PATH)/wifi_base.c \
			$(MODULE_PATH)/wifi_feature.c

LOCAL_CFLAGS += $(WIFI_CFLAGS)

LOCAL_CFLAGS += -fstack-protector-strong -fno-common -fsigned-char -fno-strict-aliasing

include $(HDF_DRIVER)

