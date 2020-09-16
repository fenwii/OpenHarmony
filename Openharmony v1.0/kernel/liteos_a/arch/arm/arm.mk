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

# strip quotation mark in configuration

LOSCFG_ARCH_CPU_STRIP   := $(subst $\",,$(LOSCFG_ARCH_CPU))
LOSCFG_ARCH_CPU          = $(LOSCFG_ARCH_CPU_STRIP)

LOSCFG_ARCH_FPU_STRIP   := $(subst $\",,$(LOSCFG_ARCH_FPU))
LOSCFG_ARCH_FPU          = $(LOSCFG_ARCH_FPU_STRIP)

ifeq ($(LOSCFG_ARCH_ARM_AARCH32), y)
LITEOS_ARCH_ARM         := arm
else ifeq ($(LOSCFG_ARCH_ARM_AARCH64), y)
LITEOS_ARCH_ARM         := 
endif

LITEOS_BASELIB          += -l$(LOSCFG_ARCH_CPU)
LIB_SUBDIRS             += arch/arm/$(LITEOS_ARCH_ARM)

# CPU compile options
ifeq ($(LOSCFG_ARCH_ARM_AARCH64), y)
ifeq ($(LOSCFG_ARCH_FPU_DISABLE), y)
EXTENSION               := +nofp
endif
endif
LITEOS_CPU_OPTS         := -mcpu=$(LOSCFG_ARCH_CPU)$(EXTENSION)

# FPU compile options
# -mfloat and -mfpu is ignored with AArch64 targets
ifeq ($(LOSCFG_ARCH_ARM_AARCH32), y)
LITEOS_FLOAT_OPTS       := -mfloat-abi=softfp
LITEOS_FPU_OPTS         := -mfpu=$(LOSCFG_ARCH_FPU)
# gcc libc folder style is combine with core and fpu
# for example, cortex-a7 with softfp abi and neon vfp4 is: a7_softfp_neon_vfp4
LITEOS_GCCLIB           := $(subst cortex-,,$(LOSCFG_ARCH_CPU))_softfp_$(LOSCFG_ARCH_FPU)
endif

LITEOS_CORE_COPTS        = $(LITEOS_CPU_OPTS) $(LITEOS_FLOAT_OPTS) $(LITEOS_FPU_OPTS)
LITEOS_INTERWORK        += $(LITEOS_CORE_COPTS)
LITEOS_NODEBUG          += $(LITEOS_CORE_COPTS)
LITEOS_ASOPTS           += $(LITEOS_CPU_OPTS)
LITEOS_CXXOPTS_BASE     += $(LITEOS_CORE_COPTS)

ARCH_INCLUDE            := -I $(LITEOSTOPDIR)/arch/arm/include \
                           -I $(LITEOSTOPDIR)/arch/arm/$(LITEOS_ARCH_ARM)/include \
                           -I $(LITEOSTOPDIR)/arch/arm/$(LITEOS_ARCH_ARM)/src/include

LITEOS_PLATFORM_INCLUDE += $(ARCH_INCLUDE)
LITEOS_CXXINCLUDE       += $(ARCH_INCLUDE)

# expose FPU info to assembly code
ifeq ($(LOSCFG_ARCH_FPU_DISABLE), y)
    LITEOS_CMACRO       += -DLOSCFG_ARCH_FPU_DISABLE
else ifeq ($(LOSCFG_ARCH_FPU_VFP_D16), y)
    LITEOS_CMACRO       += -DLOSCFG_ARCH_FPU_VFP_D16
else ifeq ($(LOSCFG_ARCH_FPU_VFP_D32), y)
    LITEOS_CMACRO       += -DLOSCFG_ARCH_FPU_VFP_D32
endif

# extra definition for other module
LITEOS_CPU_TYPE          = $(LOSCFG_ARCH_CPU)
LITEOS_ARM_ARCH         := -march=$(subst $\",,$(LOSCFG_ARCH_ARM_VER))

# linux style macros
LINUX_ARCH_$(LOSCFG_ARCH_ARM_V7A) = -D__LINUX_ARM_ARCH__=7
LINUX_ARCH_$(LOSCFG_ARCH_ARM_V7R) = -D__LINUX_ARM_ARCH__=7
LINUX_ARCH_$(LOSCFG_ARCH_ARM_V7M) = -D__LINUX_ARM_ARCH__=7
LINUX_ARCH_$(LOSCFG_ARCH_ARM_V8A) = -D__LINUX_ARM_ARCH__=8
LINUX_ARCH_$(LOSCFG_ARCH_ARM_V8R) = -D__LINUX_ARM_ARCH__=8
LINUX_ARCH_$(LOSCFG_ARCH_ARM_V8M) = -D__LINUX_ARM_ARCH__=8

AS_OBJS_LIBC_FLAGS      += $(LINUX_ARCH_y)
