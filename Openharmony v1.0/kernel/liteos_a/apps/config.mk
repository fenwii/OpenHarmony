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

# common dir config
include $(LITEOSTOPDIR)/config.mk

# output dir config
OBJOUT := $(APPSTOPDIR)/out
APPSOUT := $(OBJOUT)/apps
LIBSOUT := $(OBJOUT)/libs
IMGOUT  := $(OUT)

# common flags config
BASE_OPTS := -ffunction-sections -fdata-sections -fno-omit-frame-pointer -D_GNU_SOURCE \
             $(LITEOS_SSP) $(LITEOS_CORE_COPTS) $(WARNING_AS_ERROR) $(LLVM_EXTRA_OPTS) $(LITEOS_GCOV_OPTS)

CFLAGS := -std=c99 -fno-exceptions $(BASE_OPTS) $(LITEOS_COPTS_OPTMIZE)
CXXFLAGS := -std=c++11 -fexceptions -fpermissive -frtti $(BASE_OPTS) $(LITEOS_COPTS_OPTMIZE)
LDCFLAGS  := -lc
ifeq ($(LOSCFG_COMPILER_CLANG_LLVM), y)
LLVM_SYSROOT := --sysroot=$(LITEOSTOPDIR)/../../prebuilts/lite/sysroot/
LDCXXFLGS := -lc++ -lc++abi -lc
else
BASE_OPTS += -Wl,-z,relro,-z,now
LDCXXFLGS := -lstdc++ -lsupc++ -lc
endif
COMMON_INCLUDE := -I $(LITEOSTHIRDPARTY)/bounds_checking_function/include

# alias variable config
HIDE := @
MAKE := make
RM := -rm -rf
CP := -cp -rf
MV := -mv
