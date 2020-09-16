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
OBJOUT := $(OUT)/obj/kernel/user

MODULE_NAME := userinit
LIBA := $(OUT)/lib/lib$(MODULE_NAME).O

LOCAL_INCLUDE := \
    -I $(LITEOSTOPDIR)/kernel/base/include\
    -I $(LITEOSTOPDIR)/kernel/include \
    -I $(LITEOSTOPDIR)/kernel/extended/include \
    -I $(LITEOSTOPDIR)/syscall \
    -I $(LITEOSTOPDIR)/fs/vfs \
    -I $(LITEOSTHIRDPARTY)/FatFs/source \
    -I $(LITEOSTOPDIR)/fs/proc/include \
    -I $(LITEOSTOPDIR)/fs/jffs2/include\
    -I $(LITEOSTOPDIR)/fs/nfs/include\
    -I $(LITEOSTOPDIR)/bsd/compat/linuxkpi/include \
    -I $(LITEOSTOPDIR)/kernel/user/include

LOCAL_SRCS := $(wildcard src/*.c) \
              $(wildcard src/*.S)

LOCAL_CSRCS := $(filter %.c,$(LOCAL_SRCS))
LOCAL_ASMSRCS := $(filter %.S,$(LOCAL_SRCS))

LOCAL_COBJS := $(patsubst %.c,$(OBJOUT)/%.o,$(LOCAL_CSRCS))
LOCAL_ASMOBJS := $(patsubst %.S,$(OBJOUT)/%.o,$(LOCAL_ASMSRCS))
LOCAL_OBJS := $(LOCAL_COBJS) $(LOCAL_ASMOBJS)

LOCAL_FLAGS :=  $(LOCAL_INCLUDE)

all : $(LIBA)

$(LOCAL_COBJS): $(OBJOUT)/%.o: %.c
	$(HIDE)$(OBJ_MKDIR)
	$(HIDE)$(CC) $(LITEOS_CFLAGS) $(LOCAL_FLAGS) $(LOCAL_CFLAGS) -c $< -o $@

$(LOCAL_ASMOBJS): $(OBJOUT)/%.o: %.S
	$(HIDE)$(OBJ_MKDIR)
	$(HIDE)$(CC) $(LITEOS_CFLAGS) $(LOCAL_FLAGS) $(LOCAL_ASFLAGS) -c $< -o $@

$(LIBA): $(LOCAL_OBJS)
	$(HIDE) $(LD) -r -o $@ $^

clean:
	$(HIDE) rm -rf $(LOCAL_OBJS) $(LIBA)
