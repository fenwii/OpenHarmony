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
include ./lite.mk

MODULE_NAME := hdf

HDF_FRAMEWORKS = ../frameworks
HDF_OSAL = osal
HDF_ADAPTER = adapter

LOCAL_SRCS := $(HDF_ADAPTER)/osal/src/osal_timer.c  \
              $(HDF_ADAPTER)/osal/src/osal_time.c  \
              $(HDF_ADAPTER)/osal/src/osal_thread.c  \
              $(HDF_ADAPTER)/osal/src/osal_spinlock.c  \
              $(HDF_ADAPTER)/osal/src/osal_irq.c  \
              $(HDF_ADAPTER)/osal/src/osal_firmware.c \
              $(HDF_ADAPTER)/osal/src/osal_file.c \
              $(HDF_ADAPTER)/osal/src/osal_atomic.c \
              $(HDF_ADAPTER)/osal/src/osal_workqueue.c \
              $(HDF_FRAMEWORKS)/utils/src/hdf_cstring.c \
              $(HDF_FRAMEWORKS)/utils/src/hdf_slist.c \
              $(HDF_FRAMEWORKS)/utils/src/hdf_sref.c \
              $(HDF_FRAMEWORKS)/ability/sbuf/src/hdf_sbuf.c \
              $(HDF_ADAPTER)/osal/src/osal_mem.c \
              $(HDF_ADAPTER)/osal/src/osal_mutex.c \
              $(HDF_ADAPTER)/osal/src/osal_sem.c \
              $(HDF_ADAPTER)/network/src/hdf_netbuf.c \
              $(HDF_FRAMEWORKS)/core/host/src/devhost_service.c \
              $(HDF_FRAMEWORKS)/core/host/src/devmgr_service_clnt.c \
              $(HDF_FRAMEWORKS)/core/host/src/devsvc_manager_clnt.c \
              $(HDF_FRAMEWORKS)/core/host/src/hdf_device.c \
              $(HDF_FRAMEWORKS)/core/host/src/hdf_device_node.c \
              $(HDF_FRAMEWORKS)/core/host/src/hdf_device_token.c \
              $(HDF_FRAMEWORKS)/core/host/src/hdf_driver_loader.c \
              $(HDF_FRAMEWORKS)/core/host/src/hdf_observer_record.c \
              $(HDF_FRAMEWORKS)/core/host/src/hdf_service_subscriber.c \
              $(HDF_FRAMEWORKS)/core/host/src/hdf_device_object.c \
              $(HDF_FRAMEWORKS)/core/host/src/hdf_service_observer.c \
              $(HDF_FRAMEWORKS)/core/host/src/power_state_token.c \
              $(HDF_FRAMEWORKS)/core/manager/src/devhost_service_clnt.c \
              $(HDF_FRAMEWORKS)/core/manager/src/device_token_clnt.c \
              $(HDF_FRAMEWORKS)/core/manager/src/devmgr_service.c \
              $(HDF_FRAMEWORKS)/core/manager/src/devsvc_manager.c \
              $(HDF_FRAMEWORKS)/core/manager/src/hdf_driver_installer.c \
              $(HDF_FRAMEWORKS)/core/manager/src/hdf_host_info.c \
              $(HDF_FRAMEWORKS)/core/manager/src/power_state_manager.c \
              $(HDF_FRAMEWORKS)/core/manager/src/power_state_token_clnt.c \
              $(HDF_FRAMEWORKS)/core/shared/src/hdf_service_record.c \
              $(HDF_FRAMEWORKS)/core/shared/src/hdf_device_info.c \
              $(HDF_FRAMEWORKS)/core/shared/src/hdf_object_manager.c \
              $(HDF_FRAMEWORKS)/core/shared/src/hdf_io_service.c \
              ./adapter/vnode/src/hdf_vnode_adapter.c \
              ./manager/src/devlite_object_config.c \
              ./manager/src/hdf_attribute_manager.c \
              ./manager/src/lite_driver_loader.c \
              ./manager/src/devmgr_service_start.c \
              ./manager/src/hdf_device_node_ext.c \
              $(HDF_FRAMEWORKS)/support/platform/src/i2c_if.c \
              $(HDF_FRAMEWORKS)/support/platform/src/i2c_core.c \
              $(HDF_FRAMEWORKS)/support/platform/src/gpio_if.c \
              $(HDF_FRAMEWORKS)/support/platform/src/gpio_core.c \
              $(HDF_FRAMEWORKS)/support/platform/src/watchdog_if.c \
              $(HDF_FRAMEWORKS)/support/platform/src/watchdog_core.c \
              $(HDF_FRAMEWORKS)/support/platform/src/spi_core.c \
              $(HDF_FRAMEWORKS)/support/platform/src/spi_if.c \
              $(HDF_FRAMEWORKS)/support/platform/src/sdio_if.c \
              $(HDF_FRAMEWORKS)/support/platform/src/sdio_core.c \
              $(HDF_FRAMEWORKS)/support/platform/src/rtc_core.c \
              $(HDF_FRAMEWORKS)/support/platform/src/rtc_base.c \
              $(HDF_FRAMEWORKS)/support/platform/src/rtc_if.c \
              $(HDF_FRAMEWORKS)/ability/config/hcs_parser/src/hcs_blob_if.c \
              $(HDF_FRAMEWORKS)/ability/config/hcs_parser/src/hcs_parser.c \
              $(HDF_FRAMEWORKS)/ability/config/hcs_parser/src/hcs_generate_tree.c \
              $(HDF_FRAMEWORKS)/ability/config/hcs_parser/src/hcs_tree_if.c \
              $(HDF_FRAMEWORKS)/ability/config/device_resource_if.c

ifeq ($(LOSCFG_DRIVERS_HDF_PLATFORM_UART), y)
              LOCAL_SRCS += $(HDF_FRAMEWORKS)/support/platform/src/uart_if.c \
              $(HDF_FRAMEWORKS)/support/platform/src/uart_core.c
endif
ifeq ($(LOSCFG_DRIVERS_HDF_WIFI), y)
              LOCAL_SRCS += $(HDF_ADAPTER)/network/src/net_device_adapter.c
endif

LOCAL_FLAGS += $(LITEOS_GCOV_OPTS)

include $(HDF_DRIVER)
