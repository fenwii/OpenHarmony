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

HDF_ROOT_DIR = $(LITEOSTOPDIR)/../../drivers/hdf/lite

HDF_CFLAGS := -fstack-protector-strong -fno-common -fsigned-char -fno-strict-aliasing

HDF_INCLUDE += -I $(HDF_ROOT_DIR)/../frameworks/include
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/../frameworks/include/osal
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/../frameworks/include/utils
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/../frameworks/utils/include
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/../frameworks/include/platform
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/../frameworks/include/core
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/../frameworks/include/net
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/../frameworks/include/wifi
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/../frameworks/model/network/wifi/netdevice
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/../frameworks/ability/sbuf/include
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/../frameworks/support/platform/include
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/../frameworks/core/host/include
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/../frameworks/core/manager/include
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/../frameworks/core/shared/include
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/adapter/network/include
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/adapter/osal/include
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/adapter/vnode/include
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/adapter/syscall/include
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/include/manager
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/include/host
HDF_INCLUDE += -I $(LITEOSTOPDIR)/bsd/compat/linuxkpi/include
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/../frameworks/include/config
HDF_INCLUDE += -I $(HDF_ROOT_DIR)/../frameworks/ability/config/hcs_parser/include
LOCAL_CFLAGS += $(HDF_INCLUDE)
LOCAL_CFLAGS += $(HDF_CFLAGS)

HDF_DRIVER = $(HDF_ROOT_DIR)/hdf_driver.mk
