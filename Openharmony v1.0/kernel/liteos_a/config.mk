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

############### this is a makefile that you can config it ###############
-include $(LITEOSTOPDIR)/tools/build/mk/los_config.mk

TOP_LD_PATH      = $(LITEOSTOPDIR)
SCRIPTS_PATH     = $(LITEOS_SCRIPTPATH)
LITEOS_MK_PATH   = $(MK_PATH)
LITEOS_SUBDIRS   = $(LIB_SUBDIRS)
LIB_BIGODIR      = $(LITEOS_LIB_BIGODIR)

##### liteos tables -u ldflags #####
-include $(LITEOS_MK_PATH)/liteos_tables_ldflags.mk


LITEOS_COPTS   := $(LITEOS_COPTS_DEBUG) $(LITEOS_COPTS_BASE)  \
                  $(LITEOS_COPTS_EXTRA) $(LITEOS_CORE_COPTS)
LITEOS_CXXOPTS  := $(LITEOS_CXXOPTS_BASE)
LITEOS_INCLUDE  := $(LITEOS_KERNEL_INCLUDE)  $(LITEOS_EXTKERNEL_INCLUDE) \
                   $(LITEOS_COMPAT_INCLUDE)  $(LITEOS_FS_INCLUDE) \
                   $(LITEOS_NET_INCLUDE)     $(LITEOS_LIB_INCLUDE) \
                   $(LITEOS_DRIVERS_INCLUDE) $(LOSCFG_TOOLS_DEBUG_INCLUDE) \
                   $(LITEOS_PLATFORM_INCLUDE) $(LITEOS_DFX_INCLUDE) \
                   $(LITEOS_SECURITY_INCLUDE)
LITEOS_LIBDEP   := $(LITEOS_BASELIB)
LITEOS_ASFLAGS  := $(LITEOS_ASOPTS)      $(LITEOS_INCLUDE)
LITEOS_CFLAGS   := $(LITEOS_COPTS)       $(LITEOS_CMACRO) \
                   $(LITEOS_CMACRO_TEST) $(LITEOS_IMAGE_MACRO) \
                   $(LITEOS_INCLUDE)
LITEOS_CXXFLAGS := $(LITEOS_CXXOPTS)     $(LITEOS_CXXMACRO) \
                   $(LITEOS_CMACRO)      $(LITEOS_CXXINCLUDE)
LITEOS_LDFLAGS  := $(LITEOS_LD_OPTS)     $(LITEOS_LD_PATH) \
                   $(LITEOS_LD_SCRIPT)

