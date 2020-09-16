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

include $(LITEOSTOPDIR)/config.mk

MODULE_NAME := hi35xx_bsp

ifeq ($(LOSCFG_DEBUG_VERSION),y)
	RELEASE_TYPE := debug
else
	RELEASE_TYPE := release
endif

all:
	$(HIDE) if [ ! -d $(OUT)/lib ]; then mkdir -p $(OUT)/lib; fi
	$(HIDE) cp -rf libs/$(RELEASE_TYPE)/lib$(MODULE_NAME).a $(OUT)/lib

clean:
	$(HIDE) rm -rf $(OUT)/lib/lib$(MODULE_NAME).a

.PHONY: all clean
