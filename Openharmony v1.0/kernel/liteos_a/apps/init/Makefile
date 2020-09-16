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

INIT_DIR := $(dir $(shell pwd))/init/

ifeq ($(APPSTOPDIR), )
APPSTOPDIR := $(shell pwd)/../
LITEOSTOPDIR = $(APPSTOPDIR)/../
endif
include $(INIT_DIR)/../config.mk

APPS_OUT := $(OUT)/bin
LOCAL_SRCS := src/init.c
LOCAL_OBJ := src/init.o

ifeq ($(LOSCFG_COMPILER_CLANG_LLVM), y)
LOCAL_FLAGS += -Wno-shift-op-parentheses -Wno-bitwise-op-parentheses -Wnonnull $(LLVM_SYSROOT)
LDCFLAGS += $(LLVM_EXTRA_LD_OPTS) $(LLVM_SYSROOT)
endif
INITNAME := init

all: $(INITNAME)

$(LOCAL_OBJ): %.o : %.c
	$(HIDE) $(CC) $(CFLAGS) $(LOCAL_FLAGS) -fPIE $(LOCAL_INCLUDE) -c $< -o $@

$(INITNAME):$(LOCAL_OBJ)
	$(HIDE) $(CC) -pie -s $(LDPATH) $(BASE_OPTS) -o $(INITNAME) $^ $(LDCFLAGS)
	$(HIDE) mkdir -p $(APPS_OUT)
	$(HIDE) $(MV) $(INITNAME) $(APPS_OUT)
	$(HIDE) $(RM) $(LOCAL_OBJ)

clean:
	$(HIDE) $(RM) $(LOCAL_OBJ)
	$(HIDE) $(RM) $(INITNAME)

.PHONY: all $(INITNAME) clean
