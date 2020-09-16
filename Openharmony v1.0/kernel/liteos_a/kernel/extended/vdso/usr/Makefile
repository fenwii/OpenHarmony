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

VDSO_SO = OHOS-vdso

VDSO_SRCS := los_vdso_sys.c
VDSO_INCLUDE := -I $(LITEOSTOPDIR)/kernel/extended/vdso/include \
                -I $(LITEOSTOPDIR)/kernel/include \
                -I $(LITEOSTOPDIR)/kernel/common \
                -I $(LITEOSTOPDIR)/bsd/compat/linuxkpi/include

VDSO_CCFLAGS := -nostdlib -fPIC $(LITEOS_SSP) $(LITEOS_CORE_COPTS) $(WARNING_AS_ERROR) $(LITEOS_COPTS_OPTMIZE)
ifeq ($(LOSCFG_COMPILER_CLANG_LLVM), y)
VDSO_CCFLAGS += $(LLVM_EXTRA_OPTS) --sysroot=$(LITEOSTOPDIR)/../../prebuilts/lite/sysroot/
endif

VDSO_LDFLAGS := -shared -s -Bsymbolic -T los_vdso.ld

all: $(VDSO_SO)
$(VDSO_SO):
	$(HIDE)$(CC) $(VDSO_INCLUDE) $(VDSO_CCFLAGS) -c -o $@.o $(VDSO_SRCS)
	$(HIDE)$(LD) $(VDSO_LDFLAGS) -o $@.so $@.o

clean:
	$(HIDE)$(RM) -rf *.o *.so
