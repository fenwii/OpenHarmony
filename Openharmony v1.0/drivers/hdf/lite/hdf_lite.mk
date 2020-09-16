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

ifeq ($(LOSCFG_DRIVERS_HDF), y)
    LITEOS_BASELIB += --whole-archive
    LITEOS_DRIVERS_HDF := $(LITEOSTOPDIR)/../../drivers/hdf/lite
    LITEOS_SOURCE_ROOT := $(LITEOSTOPDIR)/../..
    LIB_SUBDIRS        += $(LITEOS_DRIVERS_HDF)
    HDF_FRAMEWORKS_PATH:= $(LITEOSTOPDIR)/../../drivers/hdf/frameworks
    LITEOS_BASELIB += -lhdf
    LITEOS_DRIVERS_HDF_INCLUDE += -I $(LITEOS_DRIVERS_HDF)/include/manager
    LITEOS_DRIVERS_HDF_INCLUDE += -I $(HDF_FRAMEWORKS_PATH)/support/platform/include
    LITEOS_DRIVERS_HDF_INCLUDE += -I $(HDF_FRAMEWORKS_PATH)/include/platform
    LITEOS_DRIVERS_HDF_INCLUDE += -I $(HDF_FRAMEWORKS_PATH)/include/utils

# models
ifeq ($(LOSCFG_DRIVERS_HDF_WIFI), y)
    LITEOS_BASELIB += -lhdf_wifi_model
    LIB_SUBDIRS    +=  $(LITEOS_DRIVERS_HDF)/model/network/wifi
endif

ifeq ($(LOSCFG_DRIVERS_HDF_USB), y)
    LITEOS_DRIVERS_HDF_INCLUDE += -I $(LITEOS_DRIVERS_HDF)/model/bus/usb/include
    LITEOS_BASELIB += -lhdf_usb
    LIB_SUBDIRS    +=  $(LITEOS_DRIVERS_HDF)/model/bus/usb
endif

# vendor lib
include $(LITEOSTOPDIR)/../../vendor/huawei/hdf/hdf_vendor.mk

    LITEOS_BASELIB += --no-whole-archive
endif

