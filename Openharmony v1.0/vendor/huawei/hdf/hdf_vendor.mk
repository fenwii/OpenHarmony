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


    LITEOS_BASELIB += -lhdf_config
    LIB_SUBDIRS += $(LITEOS_SOURCE_ROOT)/vendor/hisi/hi35xx/$(LITEOS_PLATFORM)/config


VENDOR_HDF_DRIVERS_PLATFORM_ROOT := $(LITEOSTOPDIR)/../../vendor/hisi/hi35xx/platform
VENDOR_HDF_DRIVERS_ROOT := $(LITEOSTOPDIR)/../../vendor/huawei/hdf

ifeq ($(LOSCFG_DRIVERS_HDF_PLATFORM_I2C), y)
    LITEOS_BASELIB += -lhdf_i2c
endif

ifeq ($(LOSCFG_DRIVERS_HDF_PLATFORM_SPI), y)
    LITEOS_BASELIB += -lhdf_spi
endif

ifeq ($(LOSCFG_DRIVERS_HDF_PLATFORM_GPIO), y)
    LITEOS_BASELIB += -lhdf_gpio
endif

ifeq ($(LOSCFG_DRIVERS_HDF_PLATFORM_WATCHDOG), y)
    LITEOS_BASELIB += -lhdf_watchdog
endif

ifeq ($(LOSCFG_DRIVERS_HDF_PLATFORM_SDIO), y)
    LITEOS_BASELIB += -lhdf_sdio
endif

ifeq ($(LOSCFG_DRIVERS_HDF_PLATFORM_RTC), y)
    LITEOS_BASELIB += -lhdf_rtc
endif

ifeq ($(LOSCFG_DRIVERS_HDF_PLATFORM_UART), y)
    LITEOS_BASELIB += -lhdf_uart
endif

ifeq ($(LOSCFG_DRIVERS_HDF_PLATFORM_HISI_SDK), y)
    LITEOS_BASELIB += -lhdf_hisi_sdk
endif

ifeq ($(LOSCFG_DRIVERS_HDF_WIFI), y)
    LITEOS_BASELIB += -lhdf_vendor_wifi

ifeq ($(LOSCFG_DRIVERS_HI3881), y)
    LITEOS_BASELIB += -lhi3881
endif
endif

ifeq ($(LOSCFG_DRIVERS_HDF_INPUT), y)
    LITEOS_BASELIB += -lhdf_input_driver
endif

ifeq ($(LOSCFG_DRIVERS_HDF_LCD), y)
    LITEOS_BASELIB += -lhdf_lcd_driver
endif

# lib path
LITEOS_LD_PATH += -L$(VENDOR_HDF_DRIVERS_PLATFORM_ROOT)/libs/$(LITEOS_PLATFORM)
LITEOS_LD_PATH += -L$(VENDOR_HDF_DRIVERS_ROOT)/libs/$(LITEOS_PLATFORM)

