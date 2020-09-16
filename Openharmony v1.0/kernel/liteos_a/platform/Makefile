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

MODULE_NAME := bsp

LOCAL_SRCS = $(wildcard $(HWI_SRC)/*.c) \
            $(wildcard $(TIMER_SRC)/*.c) \
            $(wildcard $(HRTIMER_SRC)/*.c) \
            $(wildcard $(UART_SRC)/*.c) \
            $(wildcard ./main.c)

LOCAL_INCLUDE += -I $(LITEOSTOPDIR)/compat/posix/src \
                 -I $(LITEOSTOPDIR)/bsd/dev/random

ifeq ($(findstring y, $(LOSCFG_PLATFORM_HI3518EV300)$(LOSCFG_PLATFORM_HI3516DV300)), y)
LOCAL_SRCS += $(wildcard ../kernel/common/*.c)
LOCAL_SRCS := $(filter-out ../kernel/common/los_rootfs.c, $(LOCAL_SRCS))
ifneq ($(LOSCFG_FS_VFS), y)
LOCAL_SRCS := $(filter-out ../kernel/common/console.c ../kernel/common/virtual_serial.c, $(LOCAL_SRCS))
endif
else
LOCAL_SRCS += $(wildcard ../kernel/common/los_config.c)
LOCAL_SRCS += $(wildcard ../kernel/common/los_printf.c)
endif

ifeq ($(LOSCFG_DRIVERS_USB), y)
LOCAL_SRCS += $(wildcard $(USB_SRC)/*.c)
endif

ifeq ($(LOSCFG_KERNEL_TICKLESS), y)
LOCAL_INCLUDE += -I $(LITEOSTOPDIR)/kernel/extended/include
endif

ifeq ($(LOSCFG_KERNEL_TRACE), y)
LOCAL_INCLUDE += -I $(LITEOSTOPDIR)/kernel/extended/include
endif

ifeq ($(LOSCFG_KERNEL_CPUP), y)
LOCAL_INCLUDE += -I $(LITEOSTOPDIR)/kernel/extended/include
endif

ifeq ($(LOSCFG_KERNEL_VDSO), y)
LOCAL_INCLUDE += -I $(LITEOSTOPDIR)/kernel/extended/vdso/include
endif

ALL_ASSRCS := $(wildcard *.S)
ASSRCS := $(subst board.ld.S,,$(ALL_ASSRCS))

LOCAL_SRCS += $(ASSRCS)

LOCAL_FLAGS := $(LOCAL_INCLUDE) $(LITEOS_GCOV_OPTS)

include $(MODULE)
