# Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
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

ALL_LIBS := demo
demo_srcs := init src
CCFLAGS +=
CCFLAGS += -D_PRE_WLAN_FEATURE_CSI -D_PRE_WLAN_FEATURE_P2P -DLWIP_ENABLE_DIAG_CMD=0
CCFLAGS += -I$(MAIN_TOPDIR)/components/iperf2/include -I$(MAIN_TOPDIR)/app/demo/include -I$(MAIN_TOPDIR)/app/demo/init -I$(MAIN_TOPDIR)/app/demo/src -I$(MAIN_TOPDIR)/config/app -I$(MAIN_TOPDIR)/config/diag -I$(MAIN_TOPDIR)/platform/os/Huawei_LiteOS/net/ripple/exports -I$(MAIN_TOPDIR)/components/ripple/exports -I$(MAIN_TOPDIR)/components/hilink/include
CCFLAGS += -I$(MAIN_TOPDIR)/third_party/mbedtls/include/mbedtls
