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

-include $(LITEOSTOPDIR)/.config
ifeq ($(LOSCFG_COMPILER_HIMIX_32), y)
CROSS_COMPILE := arm-linux-ohoseabi-
else ifeq ($(LOSCFG_COMPILER_CLANG_LLVM), y)
CROSS_COMPILE := llvm-
endif

HIDE := @
CC  :=
AS  :=
AR  :=
LD  :=
GPP :=
OBJCOPY :=
OBJDUMP :=
SIZE :=
NM :=
MKDIR = mkdir
OBJ_MKDIR = if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
RM = -rm -rf
ECHO = echo
ifeq ($(OS),)
OS = $(shell uname -s)
export OS
endif
COMPILE_NAME := $(patsubst %-,%,$(CROSS_COMPILE))
VERSION_NUM :=

ARFLAGS  := cr

## platform relative ##
LITEOS_ARM_ARCH :=
LITEOS_CPU_TYPE :=
## c as cxx ld options ##
LITEOS_ASOPTS :=
LITEOS_COPTS_BASE :=
LITEOS_COPTS_EXTRA :=
LITEOS_COPTS_EXTRA_INTERWORK :=
LITEOS_COPTS_DEBUG :=
LITEOS_COPTS_NODEBUG :=
LITEOS_INTERWORK :=
LITEOS_CXXOPTS :=
LITEOS_CXXOPTS_BASE :=
LITEOS_LD_OPTS :=
LITEOS_GCOV_OPTS :=
## dynload ld options ##
LITEOS_DYNLOADOPTS :=
## macro define ##
LITEOS_CMACRO :=
LITEOS_CXXMACRO :=
## head file path and ld path ##
LITEOS_PLATFORM_INCLUDE :=
LITEOS_CXXINCLUDE :=
LITEOS_LD_PATH :=
LITEOS_LD_SCRIPT :=
LITEOS_MK_PATH :=
## c as cxx ld flags ##
LITEOS_ASFLAGS :=
LITEOS_CFLAGS :=
LITEOS_CFLAGS_INTERWORK :=
LITEOS_LDFLAGS :=
LITEOS_CXXFLAGS :=
## depended lib ##
LITEOS_BASELIB :=
LITEOS_LIBDEP :=
## directory ##
LIB_BIGODIR :=
LIB_SUBDIRS :=
##compiler##
LITEOS_COMPILER_CXX_PATH :=
LITEOS_COMPILER_CXXLIB_PATH :=
LITEOS_COMPILER_GCCLIB_PATH  :=
LITEOS_COMPILER_GCC_INCLUDE  :=
LITEOS_DRIVERS_BASE_PATH :=
LITEOS_VENDOR_DRIVERS_BASE_PATH :=

## variable define ##
ifeq ($(LITEOSTHIRDPARTY),)
LITEOSTHIRDPARTY := $(LITEOSTOPDIR)/../../third_party
endif
ifeq ($(OUTDIR),)
OUT  = $(LITEOSTOPDIR)/out/$(LITEOS_PLATFORM)
LITEOS_TARGET_DIR = $(OUT)
else
OUT = $(OUTDIR)
LITEOS_TARGET_DIR = $(OUT)/../../../
endif
BUILD  = $(OUT)/obj
MK_PATH  = $(LITEOSTOPDIR)/tools/build/mk
CXX_PATH  = $(LITEOSTOPDIR)/lib/cxxstl
JFFS_PATH  = $(LITEOSTOPDIR)/fs/jffs2
LITEOS_SCRIPTPATH ?= $(LITEOSTOPDIR)/tools/scripts
LITEOS_LIB_BIGODIR  = $(OUT)/lib/obj
LOSCFG_ENTRY_SRC    = $(LITEOSTOPDIR)/kernel/common/los_config.c

### include variable
MODULE = $(MK_PATH)/module.mk
ifeq ($(LOSCFG_COMPILER_HIMIX_32), y)
LITEOS_CMACRO      += -D__COMPILER_HUAWEILITEOS__
else ifeq ($(LOSCFG_COMPILER_CLANG_LLVM), y)
LITEOS_CMACRO      += -D__COMPILER_HUAWEILITEOS__
else ifeq ($(LOSCFG_COMPILER_HIMIX100_64), y)
LITEOS_CMACRO      += -D__COMPILER_HUAWEILITEOS__
else ifeq ($(LOSCFG_COMPILER_HCC_64), y)
LITEOS_CMACRO      += -D__COMPILER_HUAWEILITEOS__
endif
LITEOS_CMACRO      += -D__LITEOS__ -DSECUREC_IN_KERNEL=0
ifeq ($(LOSCFG_COMPILER_CLANG_LLVM), y)
LITEOS_BASELIB     += -lclang_rt.builtins
LITEOS_BASELIB     += -lunwind --no-dependent-libraries
else
LITEOS_BASELIB     += -lgcc
LITEOS_BASELIB     += -lgcc_eh
endif
AS_OBJS_LIBC_FLAGS  = -D__ASSEMBLY__

WARNING_AS_ERROR   := -Wall -Werror

####################################### CPU Option Begin #########################################
include $(LITEOSTOPDIR)/arch/cpu.mk
####################################### CPU Option End #########################################

############################# Platform Option Begin#################################
include $(LITEOSTOPDIR)/platform/bsp.mk

ifeq ($(LOSCFG_PLATFORM_ROOTFS), y)
    LITEOS_BASELIB  += -lrootfs
    LIB_SUBDIRS     += $(LITEOSTOPDIR)/kernel/common
endif
############################# Platform Option End #################################

####################################### Kernel Option Begin ###########################################
LITEOS_BASELIB += -lbase
LIB_SUBDIRS       += kernel/base
LITEOS_KERNEL_INCLUDE   := -I $(LITEOSTOPDIR)/kernel/include

LITEOS_BASELIB += -lhi35xx_bsp
LIB_SUBDIRS += $(LITEOSTOPDIR)/../../vendor/hisi/hi35xx/$(LITEOS_PLATFORM)/config/board/

ifeq ($(LOSCFG_KERNEL_CPUP), y)
    LITEOS_BASELIB   += -lcpup
    LIB_SUBDIRS         += kernel/extended/cpup
    LITEOS_CPUP_INCLUDE := -I $(LITEOSTOPDIR)/kernel/extended/cpup
endif

ifeq ($(LOSCFG_KERNEL_SCHED_STATISTICS), y)
    LITEOS_CMACRO += -DLOSCFG_KERNEL_SCHED_STATISTICS=1
else
    LITEOS_CMACRO += -DLOSCFG_KERNEL_SCHED_STATISTICS=0
endif

ifeq ($(LOSCFG_KERNEL_DYNLOAD), y)
    LITEOS_BASELIB   += -ldynload
    LIB_SUBDIRS      += kernel/extended/dynload
    LITEOS_DYNLOAD_INCLUDE   += -I $(LITEOSTOPDIR)/kernel/extended/dynload/include
endif

ifeq ($(LOSCFG_KERNEL_VDSO), y)
    LITEOS_BASELIB   += -lvdso
    LIB_SUBDIRS      += kernel/extended/vdso/usr
    LIB_SUBDIRS      += kernel/extended/vdso/src
    LITEOS_VDSO_INCLUDE   += -I $(LITEOSTOPDIR)/kernel/extended/vdso/include
endif

ifeq ($(LOSCFG_KERNEL_TICKLESS), y)
    LITEOS_BASELIB += -ltickless
    LIB_SUBDIRS       += kernel/extended/tickless
    LITEOS_TICKLESS_INCLUDE   += -I $(LITEOSTOPDIR)/kernel/extended/tickless
endif

ifeq ($(LOSCFG_KERNEL_TRACE), y)
    LITEOS_BASELIB += -ltrace
    LIB_SUBDIRS       += kernel/extended/trace
    LITEOS_TRACE_INCLUDE   += -I $(LITEOSTOPDIR)/kernel/extended/trace
endif

ifeq ($(LOSCFG_KERNEL_LITEIPC), y)
    LITEOS_BASELIB     += -lliteipc
    LIB_SUBDIRS           += kernel/extended/liteipc
    LITEOS_LITEIPC_INCLUDE   += -I $(LITEOSTOPDIR)/kernel/extended/liteipc
endif

ifeq ($(LOSCFG_KERNEL_PIPE), y)
    LITEOS_BASELIB     += -lpipes
    LIB_SUBDIRS           += kernel/extended/pipe
    LITEOS_PIPE_INCLUDE   += -I $(LITEOSTOPDIR)/kernel/extended/pipe
endif
################################### Kernel Option End ################################

#################################### Lib Option Begin ###############################
ifeq ($(LOSCFG_LIB_LIBC), y)
    LIB_SUBDIRS        += lib/libc
    LIB_SUBDIRS        += lib/libsec

    LITEOS_BASELIB  += -lc -lsec
    LITEOS_LIBC_INCLUDE   += \
        $(LITEOS_LIBSCREW_INCLUDE) \
        -I $(LITEOSTOPDIR)/lib/libc/musl/include \
        -I $(LITEOSTOPDIR)/lib/libc/musl/obj/include \
        -I $(LITEOSTOPDIR)/lib/libc/musl/arch/arm \
        -I $(LITEOSTOPDIR)/lib/libc/musl/arch/generic \
        -I $(LITEOSTHIRDPARTY)/bounds_checking_function/include
endif

    LITEOS_BASELIB   += -lscrew
    LIB_SUBDIRS         += lib/libscrew
    LITEOS_LIBSCREW_INCLUDE += -I $(LITEOSTOPDIR)/lib/libscrew/include

ifeq ($(LOSCFG_KERNEL_CPPSUPPORT), y)
ifeq ($(LOSCFG_COMPILER_CLANG_LLVM), y)
    LITEOS_BASELIB += -lc++ -lc++abi
    LITEOS_BASELIB += -lcppsupport
else
    LITEOS_BASELIB += -lsupc++
    LITEOS_BASELIB += -lcppsupport -lstdc++
endif
    LIB_SUBDIRS       += kernel/extended/cppsupport
    LITEOS_CPPSUPPORT_INCLUDE   += -I $(LITEOSTOPDIR)/kernel/extended/cppsupport
endif

ifeq ($(LOSCFG_LIB_ZLIB), y)
    LITEOS_BASELIB += -lz
    LIB_SUBDIRS    += lib/zlib
    LITEOS_ZLIB_INCLUDE += -I $(LITEOSTHIRDPARTY)/zlib
endif
################################### Lib Option End ######################################

####################################### Compat Option Begin #########################################
ifeq ($(LOSCFG_COMPAT_POSIX), y)
    LITEOS_BASELIB += -lposix
    LIB_SUBDIRS       += compat/posix
    LITEOS_POSIX_INCLUDE   += \
        -I $(LITEOSTOPDIR)/compat/posix/include
endif

ifeq ($(LOSCFG_COMPAT_BSD), y)
    LITEOS_BASELIB += -lbsd
    LIB_SUBDIRS    += bsd
    LITEOS_BSD_INCLUDE   += -I $(LITEOSTOPDIR)/bsd
    LITEOS_CMACRO += -DLOSCFG_COMPAT_LINUXKPI
    LITEOS_BASELIB += -llinuxkpi
    LIB_SUBDIRS       += bsd/compat/linuxkpi
    LITEOS_LINUX_INCLUDE += -I $(LITEOSTOPDIR)/bsd/compat/linuxkpi/include \
                            -I $(LITEOSTOPDIR)/bsd \
                            -I $(LITEOSTOPDIR)/bsd/kern
endif
######################################## Compat Option End ############################################


#################################### FS Option Begin ##################################
ifeq ($(LOSCFG_FS_VFS), y)
    LITEOS_BASELIB += -lvfs -lmulti_partition
ifeq ($(LOSCFG_FS_VFS_BLOCK_DEVICE), y)
    LITEOS_BASELIB += -lbch
    LIB_SUBDIRS       += fs/vfs fs/vfs/bch
endif
    LIB_SUBDIRS       += fs/vfs fs/vfs/multi_partition
    LITEOS_VFS_INCLUDE   += -I $(LITEOSTOPDIR)/fs/include
    LITEOS_VFS_INCLUDE   += -I $(LITEOSTOPDIR)/fs/vfs/include/driver
    LITEOS_VFS_INCLUDE   += -I $(LITEOSTOPDIR)/fs/vfs/include/operation
    LITEOS_VFS_MTD_INCLUDE := -I $(LITEOSTOPDIR)/fs/vfs/include/multi_partition
    LITEOS_VFS_DISK_INCLUDE := -I $(LITEOSTOPDIR)/fs/vfs/include/disk
endif

ifeq ($(LOSCFG_FS_FAT), y)
    LITEOS_BASELIB  += -lfat
    LIB_SUBDIRS     += fs/fat
    LITEOS_FAT_INCLUDE += -I $(LITEOSTHIRDPARTY)/FatFs/source
endif

ifeq ($(LOSCFG_FS_FAT_VIRTUAL_PARTITION), y)
    LITEOS_BASELIB += -lvirpart
    LIB_SUBDIRS += fs/fat/virpart
    LITEOS_FAT_VIRPART_INCLUDE += -I $(LITEOSTOPDIR)/fs/fat/virpart/include
endif

ifeq ($(LOSCFG_FS_FAT_DISK), y)
    LITEOS_BASELIB += -ldisk
    LIB_SUBDIRS += fs/vfs/disk
endif

ifeq ($(LOSCFG_FS_FAT_CACHE), y)
    LITEOS_BASELIB  += -lbcache
    LIB_SUBDIRS     += fs/vfs/bcache
    LITEOS_FAT_CACHE_INCLUDE += -I $(LITEOSTOPDIR)/fs/vfs/include/bcache
endif


ifeq ($(LOSCFG_FS_RAMFS), y)
    LITEOS_BASELIB  += -lramfs
    LIB_SUBDIRS     += fs/ramfs
endif

ifeq ($(LOSCFG_FS_NFS), y)
    LITEOS_BASELIB  += -lnfs
    LIB_SUBDIRS     += fs/nfs
endif

ifeq ($(LOSCFG_FS_PROC), y)
    LITEOS_BASELIB  += -lproc
    LIB_SUBDIRS     += fs/proc
    LITEOS_PROC_INCLUDE += -I $(LITEOSTOPDIR)/fs/proc/include
endif


ifeq ($(LOSCFG_FS_JFFS), y)
    LITEOS_BASELIB  += -ljffs2
    LIB_SUBDIRS     += fs/jffs2
endif
#################################### FS Option End ##################################


################################### Net Option Begin ###################################
ifeq ($(LOSCFG_NET_LWIP_SACK), y)
ifeq ($(LOSCFG_NET_LWIP_SACK_2_1), y)
    LWIPDIR := $(LITEOSTHIRDPARTY)/lwip/src
    LITEOS_BASELIB += -llwip
    LIB_SUBDIRS       += net/lwip-2.1
    LITEOS_LWIP_SACK_INCLUDE   += \
        -I $(LITEOSTOPDIR)/net/lwip-2.1/porting/include \
        -I $(LWIPDIR)/include \
        -I $(LITEOSTOPDIR)/net/mac

    LITEOS_CMACRO     +=  $(LWIP_MACROS)
else
    $(error "unknown lwip version")
endif
endif

#################################### Net Option End####################################
LITEOS_DRIVERS_BASE_PATH := $(LITEOSTOPDIR)/../../drivers/liteos
LITEOS_VENDOR_DRIVERS_BASE_PATH := $(LITEOSTOPDIR)/../../vendor/hisi/hi35xx/platform
################################## Driver Option Begin #################################
ifeq ($(LOSCFG_DRIVERS_HDF), y)
include $(LITEOSTOPDIR)/../../drivers/hdf/lite/hdf_lite.mk
endif

ifeq ($(LOSCFG_DRIVERS_HIEVENT), y)
    LITEOS_BASELIB     += -lhievent
    LIB_SUBDIRS           += $(LITEOS_DRIVERS_BASE_PATH)/hievent
    LITEOS_HIEVENT_INCLUDE   += -I $(LITEOS_DRIVERS_BASE_PATH)/hievent/include
endif

ifeq ($(LOSCFG_DRIVERS_HIEDMAC), y)
    LITEOS_BASELIB    += -lhiedmac
    LITEOS_HIDMAC_INCLUDE   += -I $(LITEOS_VENDOR_DRIVERS_BASE_PATH)/hiedmac/include
endif

ifeq ($(LOSCFG_DRIVERS_HIETH_SF), y)
    LITEOS_BASELIB    += -lhieth-sf
    LITEOS_HIETH_SF_INCLUDE += -I $(LITEOS_VENDOR_DRIVERS_BASE_PATH)/hieth-sf/include
endif

ifeq ($(LOSCFG_DRIVERS_TZDRIVER), y)
    LITEOS_BASELIB   += -ltzdriver -lmbedtls
    LIB_SUBDIRS         += $(LITEOS_DRIVERS_BASE_PATH)/tzdriver  $(LITEOSTOPDIR)/lib/libmbedtls
    LITEOS_TZDRIVER_INCLUDE += -I $(LITEOS_DRIVERS_BASE_PATH)/tzdriver/include
endif

ifeq ($(LOSCFG_DRIVERS_MEM), y)
    LITEOS_BASELIB += -lmem
    LIB_SUBDIRS       += $(LITEOS_DRIVERS_BASE_PATH)/mem
endif

ifeq ($(LOSCFG_DRIVERS_MMC), y)
    MMC_HOST_DIR := himci
    LITEOS_BASELIB  += -lmmc
    LITEOS_MMC_INCLUDE += -I $(LITEOS_VENDOR_DRIVERS_BASE_PATH)/mmc/include
endif

ifeq ($(LOSCFG_DRIVERS_MTD), y)
    LITEOS_BASELIB    += -lmtd_common
    LITEOS_MTD_SPI_NOR_INCLUDE  +=  -I $(LITEOS_VENDOR_DRIVERS_BASE_PATH)/mtd/common/include

    ifeq ($(LOSCFG_DRIVERS_MTD_SPI_NOR), y)
        ifeq ($(LOSCFG_DRIVERS_MTD_SPI_NOR_HISFC350), y)
            NOR_DRIVER_DIR := hisfc350
    else ifeq ($(LOSCFG_DRIVERS_MTD_SPI_NOR_HIFMC100), y)
            NOR_DRIVER_DIR := hifmc100
    endif

    LITEOS_BASELIB   += -lspinor_flash
    LITEOS_MTD_SPI_NOR_INCLUDE  +=  -I $(LITEOS_VENDOR_DRIVERS_BASE_PATH)/mtd/spi_nor/include

    endif
endif

ifeq ($(LOSCFG_DRIVERS_RANDOM), y)
    LITEOS_BASELIB += -lrandom
    LIB_SUBDIRS    += $(LITEOS_DRIVERS_BASE_PATH)/random
    LITEOS_RANDOM_INCLUDE += -I $(LITEOS_DRIVERS_BASE_PATH)/random/include
endif

ifeq ($(LOSCFG_DRIVERS_USB), y)
    LITEOS_BASELIB  += -lusb_base
    LIB_SUBDIRS     += $(LITEOSTOPDIR)/bsd/dev/usb
    LITEOS_USB_INCLUDE += -I $(LITEOSTOPDIR)/bsd/dev/usb
ifeq ($(LOSCFG_USB_DEBUG), y)
    LITEOS_CMACRO   += -DLOSCFG_USB_DEBUG
endif
endif

ifeq ($(LOSCFG_DRIVERS_VIDEO), y)
    LITEOS_BASELIB += -lvideo
    LIB_SUBDIRS       += $(LITEOS_DRIVERS_BASE_PATH)/video
    LITEOS_VIDEO_INCLUDE += -I $(LITEOSTOPDIR)/../../third_party/NuttX/include/nuttx/video
endif

############################## Driver Option End #######################################

############################## Dfx Option Begin#######################################
ifeq ($(LOSCFG_BASE_CORE_HILOG), y)
    LITEOS_BASELIB     += -lhilog
    LIB_SUBDIRS           += $(LITEOSTOPDIR)/../../base/hiviewdfx/frameworks/hilog_lite/featured
    LITEOS_HILOG_INCLUDE  += -I $(LITEOSTOPDIR)/../../base/hiviewdfx/interfaces/kits/hilog
    LITEOS_CMACRO += -DLOSCFG_BASE_CORE_HILOG
endif
############################## Dfx Option End #######################################

############################# Tools && Debug Option Begin ##############################
ifeq ($(LOSCFG_COMPRESS), y)
    LITEOS_BASELIB    += -lcompress
    LIB_SUBDIRS       += tools/compress
endif

ifeq ($(LOSCFG_COMPILE_DEBUG), y)
    LITEOS_COPTS_OPTMIZE = -O0
    LITEOS_COPTS_OPTION  = -g -gdwarf-2
else
    ifeq ($(LOSCFG_COMPILER_CLANG_LLVM), y)
        LITEOS_COPTS_OPTMIZE = -Oz -flto
    else
        LITEOS_COPTS_OPTMIZE = -O2
    endif
    LITEOS_COPTS_OPTMIZE_NODEBUG = -O0
endif
    LITEOS_COPTS_DEBUG  += $(LITEOS_COPTS_OPTION) $(LITEOS_COPTS_OPTMIZE)
    LITEOS_INTERWORK += $(LITEOS_COPTS_OPTION) $(LITEOS_COPTS_OPTMIZE)
    LITEOS_CXXOPTS_BASE += $(LITEOS_COPTS_OPTION) $(LITEOS_COPTS_OPTMIZE)
    LITEOS_ASOPTS   += $(LITEOS_COPTS_OPTION)
    LITEOS_NODEBUG  += $(LITEOS_COPTS_OPTMIZE_NODEBUG)

ifeq ($(LOSCFG_SHELL), y)
    LITEOS_BASELIB += -lshell
    LIB_SUBDIRS       += shell
    LITEOS_SHELL_INCLUDE  += -I $(LITEOSTOPDIR)/shell/full/include
endif


ifeq ($(LOSCFG_NET_TELNET), y)
    LITEOS_BASELIB += -ltelnet
    LIB_SUBDIRS       += net/telnet
    LITEOS_TELNET_INCLUDE   += \
        -I $(LITEOSTOPDIR)/net/telnet/include
endif

ifeq ($(LOSCFG_3RDPARTY), y)
    -include $(LITEOSTOPDIR)/3rdParty/3rdParty.mk
endif

ifeq ($(LOSCFG_NULL_ADDRESS_PROTECT), y)
    LITEOS_CMACRO += -DLOSCFG_NULL_ADDRESS_PROTECT
endif

LITEOS_BASELIB += -lsyscall
LIB_SUBDIRS += syscall
LIB_SUBDIRS += kernel/user

############################# Tools && Debug Option End #################################

############################# Security Option Begin ##############################
LITEOS_SSP = -fno-stack-protector
ifeq ($(LOSCFG_CC_STACKPROTECTOR), y)
    LITEOS_SSP = -fstack-protector --param ssp-buffer-size=4
endif

ifeq ($(LOSCFG_CC_STACKPROTECTOR_STRONG), y)
    LITEOS_SSP = -fstack-protector-strong
endif

ifeq ($(LOSCFG_CC_STACKPROTECTOR_ALL), y)
    LITEOS_SSP = -fstack-protector-all
endif

ifeq ($(LOSCFG_SECURITY), y)
LIB_SUBDIRS += security
LITEOS_BASELIB += -lsecurity
ifeq ($(LOSCFG_SECURITY_CAPABILITY), y)
LITEOS_SECURITY_CAP_INC := -I $(LITEOSTOPDIR)/security/cap
endif
ifeq ($(LOSCFG_SECURITY_VID), y)
LITEOS_SECURITY_VID_INC := -I $(LITEOSTOPDIR)/security/vid
endif
endif

############################# Security Option End ##############################

ifeq ($(LOSCFG_COMPILER_CLANG_LLVM), y)
ifeq ($(LITEOS_COMPILER_PATH),)
LITEOS_COMPILER_PATH := $(shell $(LITEOSTOPDIR)/tools/build/mk/get_llvm_compiler_path.sh  $(CROSS_COMPILE) $(LITEOSTOPDIR))
export LITEOS_COMPILER_PATH
endif
CC  = $(LITEOS_COMPILER_PATH)/bin/clang
AS  = $(LITEOS_COMPILER_PATH)/bin/$(CROSS_COMPILE)as
AR  = $(LITEOS_COMPILER_PATH)/bin/$(CROSS_COMPILE)ar
LD  = $(LITEOS_COMPILER_PATH)/bin/ld.lld
GPP = $(LITEOS_COMPILER_PATH)/bin/clang++
OBJCOPY = $(LITEOS_COMPILER_PATH)/bin/$(CROSS_COMPILE)objcopy -R .bss
OBJDUMP = $(LITEOS_COMPILER_PATH)/bin/$(CROSS_COMPILE)objdump
SIZE = $(LITEOS_COMPILER_PATH)/bin/$(CROSS_COMPILE)size
NM = $(LITEOS_COMPILER_PATH)/bin/$(CROSS_COMPILE)nm
STRIP = $(LITEOS_COMPILER_PATH)/bin/$(CROSS_COMPILE)strip

VERSION_NUM := v1
LITEOS_COMPILER_CXX_PATH = $(LITEOS_COMPILER_PATH)/include

LLVM_TARGET := arm-liteos
LLVM_EXTRA_OPTS := -target $(LLVM_TARGET) -fms-extensions -Wno-address-of-packed-member
LLVM_EXTRA_LD_OPTS := -fuse-ld=lld --rtlib=compiler-rt
else
ifeq ($(LITEOS_COMPILER_PATH),)
LITEOS_COMPILER_PATH := $(shell $(LITEOSTOPDIR)/tools/build/mk/get_compiler_path.sh  $(CROSS_COMPILE) $(LITEOSTOPDIR))
export LITEOS_COMPILER_PATH
endif
CC  = $(LITEOS_COMPILER_PATH)/bin/$(CROSS_COMPILE)gcc
AS  = $(LITEOS_COMPILER_PATH)/bin/$(CROSS_COMPILE)as
AR  = $(LITEOS_COMPILER_PATH)/bin/$(CROSS_COMPILE)ar
LD  = $(LITEOS_COMPILER_PATH)/bin/$(CROSS_COMPILE)ld
GPP = $(LITEOS_COMPILER_PATH)/bin/$(CROSS_COMPILE)g++
OBJCOPY = $(LITEOS_COMPILER_PATH)/bin/$(CROSS_COMPILE)objcopy
OBJDUMP = $(LITEOS_COMPILER_PATH)/bin/$(CROSS_COMPILE)objdump
SIZE = $(LITEOS_COMPILER_PATH)/bin/$(CROSS_COMPILE)size
NM = $(LITEOS_COMPILER_PATH)/bin/$(CROSS_COMPILE)nm
STRIP = $(LITEOS_COMPILER_PATH)/bin/$(CROSS_COMPILE)strip

ifeq ($(VERSION_NUM),)
VERSION_NUM := $(shell $(CC) -dumpversion)
export VERSION_NUM
endif

LITEOS_COMPILER_CXX_PATH = $(LITEOS_COMPILER_PATH)/$(COMPILE_NAME)/include
endif

ifeq ($(LOSCFG_COMPILER_CLANG_LLVM), y)
LITEOS_COMPILER_CXXLIB_PATH = $(LITEOS_COMPILER_PATH)/lib/$(LLVM_TARGET)/c++/a7_softfp_neon-vfpv4
LITEOS_COMPILER_GCCLIB_PATH = $(LITEOS_COMPILER_PATH)/lib/clang/9.0.0/lib/$(LLVM_TARGET)/a7_softfp_neon-vfpv4
LITEOS_COMPILER_GCC_INCLUDE = -I $(LITEOS_COMPILER_PATH)/lib/clang/9.0.0/include
else ifeq ($(LOSCFG_COMPILER_HIMIX_32), y)
LITEOS_COMPILER_CXXLIB_PATH = $(LITEOS_COMPILER_PATH)/$(COMPILE_NAME)/lib
LITEOS_COMPILER_GCCLIB_PATH = $(LITEOS_COMPILER_PATH)/lib/gcc/$(COMPILE_NAME)/$(VERSION_NUM)
LITEOS_COMPILER_GCC_INCLUDE = -I $(LITEOS_COMPILER_PATH)/lib/gcc/arm-linux-ohoseabi/$(VERSION_NUM)/include
else ifeq ($(LOSCFG_COMPILER_HIMIX100_64), y)
LITEOS_COMPILER_CXXLIB_PATH = $(LITEOS_COMPILER_PATH)/$(COMPILE_NAME)/lib64
LITEOS_COMPILER_GCCLIB_PATH = $(LITEOS_COMPILER_PATH)/lib/gcc/$(COMPILE_NAME)/$(VERSION_NUM)
LITEOS_COMPILER_GCC_INCLUDE = -I $(LITEOS_COMPILER_PATH)/lib/gcc/aarch64-linux-android/$(VERSION_NUM)/include
else ifeq ($(LOSCFG_COMPILER_HCC_64), y)
LITEOS_COMPILER_CXXLIB_PATH = $(LITEOS_COMPILER_PATH)/$(COMPILE_NAME)/lib64
LITEOS_COMPILER_GCCLIB_PATH = $(LITEOS_COMPILER_PATH)/lib64/gcc/$(COMPILE_NAME)/$(VERSION_NUM)
LITEOS_COMPILER_GCC_INCLUDE = -I $(LITEOS_COMPILER_PATH)/lib64/gcc/aarch64-linux-gnu/$(VERSION_NUM)/include
endif

LITEOS_CXXINCLUDE += \
    -I $(LITEOS_COMPILER_CXX_PATH)/c++/$(VERSION_NUM) \
    -I $(LITEOS_COMPILER_CXX_PATH)/c++/$(VERSION_NUM)/ext \
    -I $(LITEOS_COMPILER_CXX_PATH)/c++/$(VERSION_NUM)/backward \
    -I $(LITEOSTOPDIR)/compat/posix/include \
    -I $(LITEOSTOPDIR)/lib/libc/musl/include \
    -I $(LITEOSTOPDIR)/fs/include \
    -I $(LITEOSTOPDIR)/kernel/include \
    $(LITEOS_LIBC_INCLUDE)

ifneq ($(LOSCFG_COMPILER_CLANG_LLVM), y)
LITEOS_CXXINCLUDE +=  -I $(LITEOS_COMPILER_CXX_PATH)/c++/$(VERSION_NUM)/backward
endif

ifeq ($(LOSCFG_COMPILER_HIMIX_32), y)
    LITEOS_CXXINCLUDE += \
        -I $(LITEOS_COMPILER_CXX_PATH)/c++/$(VERSION_NUM)/arm-linux-ohoseabi
    LITEOS_CXXMACRO   += -DLOSCFG_KERNEL_CPP_EXCEPTIONS_SUPPORT
    LITEOS_CMACRO     += -DLOSCFG_KERNEL_CPP_EXCEPTIONS_SUPPORT
else ifeq ($(LOSCFG_COMPILER_HIMIX100_64), y)
    LITEOS_CXXINCLUDE += \
        -I $(LITEOS_COMPILER_CXX_PATH)/c++/$(VERSION_NUM)/aarch64-linux-android
    LITEOS_CXXMACRO   += -DLOSCFG_KERNEL_CPP_EXCEPTIONS_SUPPORT
    LITEOS_CMACRO     += -DLOSCFG_KERNEL_CPP_EXCEPTIONS_SUPPORT
else ifeq ($(LOSCFG_COMPILER_HCC_64), y)
    LITEOS_CXXINCLUDE += \
        -I $(LITEOS_COMPILER_CXX_PATH)/c++/$(VERSION_NUM)/aarch64-linux-gnu
    LITEOS_CXXMACRO   += -DLOSCFG_KERNEL_CPP_EXCEPTIONS_SUPPORT
    LITEOS_CMACRO     += -DLOSCFG_KERNEL_CPP_EXCEPTIONS_SUPPORT
endif

LITEOS_CXXINCLUDE +=  $(LITEOS_COMPILER_GCC_INCLUDE)

LITEOS_CXXOPTS_BASE  += -std=c++11 -nostdlib -nostdinc -nostdinc++ -fexceptions -fpermissive -fno-use-cxa-atexit \
                        -fno-builtin -frtti -fno-pic -Winvalid-pch $(WARNING_AS_ERROR) $(LLVM_EXTRA_OPTS)


LITEOS_EXTKERNEL_INCLUDE   := $(LITEOS_CPPSUPPORT_INCLUDE) $(LITEOS_DYNLOAD_INCLUDE) \
                              $(LITEOS_TICKLESS_INCLUDE)   $(LITEOS_TRACE_INCLUDE) \
                              $(LITEOS_VDSO_INCLUDE)       $(LITEOS_LITEIPC_INCLUDE) \
                              $(LITEOS_PIPE_INCLUDE)
LITEOS_COMPAT_INCLUDE      := $(LITEOS_POSIX_INCLUDE) $(LITEOS_LINUX_INCLUDE) \
                              $(LITEOS_BSD_INCLUDE)
LITEOS_FS_INCLUDE          := $(LITEOS_VFS_INCLUDE)        $(LITEOS_FAT_CACHE_INCLUDE) \
                              $(LITEOS_VFS_MTD_INCLUDE)    $(LITEOS_VFS_DISK_INCLUDE) \
                              $(LITEOS_PROC_INCLUDE)       $(LITEOS_FAT_VIRPART_INCLUDE) \
                              $(LITEOS_FAT_INCLUDE)
LITEOS_NET_INCLUDE         := $(LITEOS_LWIP_SACK_INCLUDE)
LITEOS_LIB_INCLUDE       := $(LITEOS_LIBC_INCLUDE)       $(LITEOS_LIBM_INCLUDE) \
                              $(LITEOS_ZLIB_INCLUDE)       $(LITEOS_COMPILER_GCC_INCLUDE) \
                              $(LITEOS_LIBSCREW_INCLUDE)
LITEOS_DRIVERS_INCLUDE     := $(LITEOS_CELLWISE_INCLUDE)   $(LITEOS_GPIO_INCLUDE) \
                              $(LITEOS_HIDMAC_INCLUDE)     $(LITEOS_HIETH_SF_INCLUDE) \
                              $(LITEOS_HIGMAC_INCLUDE)     $(LITEOS_I2C_INCLUDE) \
                              $(LITEOS_LCD_INCLUDE)        $(LITEOS_MMC_INCLUDE) \
                              $(LITEOS_MTD_SPI_NOR_INCLUDE) \
                              $(LITEOS_RANDOM_INCLUDE)     $(LITEOS_RTC_INCLUDE) \
                              $(LITEOS_SPI_INCLUDE)        $(LITEOS_USB_INCLUDE) \
                              $(LITEOS_WTDG_INCLUDE)       $(LITEOS_DBASE_INCLUDE) \
                              $(LITEOS_CPUFREQ_INCLUDE)    $(LITEOS_DEVFREQ_INCLUDE) \
                              $(LITEOS_REGULATOR_INCLUDE)  $(LITEOS_VIDEO_INCLUDE) \
                              $(LITEOS_DRIVERS_HDF_INCLUDE) $(LITEOS_TZDRIVER_INCLUDE) \
                              $(LITEOS_HIEVENT_INCLUDE)
LITEOS_DFX_INCLUDE    := $(LITEOS_HILOG_INCLUDE)

LITEOS_SECURITY_INCLUDE    := $(LITEOS_SECURITY_CAP_INC) $(LITEOS_SECURITY_VID_INC)
LOSCFG_TOOLS_DEBUG_INCLUDE := $(LITEOS_SHELL_INCLUDE)  $(LITEOS_UART_INCLUDE) \
                              $(LITEOS_TELNET_INCLUDE)


FP = -fno-omit-frame-pointer
LITEOS_COPTS_BASE  := -fno-pic -fno-builtin -nostdinc -nostdlib $(WARNING_AS_ERROR) $(LITEOS_SSP) $(LLVM_EXTRA_OPTS) -fno-strict-aliasing -fno-common -fsigned-char
ifneq ($(LOSCFG_COMPILER_CLANG_LLVM), y)
LITEOS_COPTS_BASE += -fno-aggressive-loop-optimizations
endif
LITEOS_COPTS_EXTRA := -std=c99 -Wpointer-arith -Wstrict-prototypes -Winvalid-pch \
                      -ffunction-sections -fdata-sections -fno-exceptions $(FP)
ifneq ($(LOSCFG_ARCH_ARM_AARCH64), y)
ifneq ($(LOSCFG_COMPILER_CLANG_LLVM), y)
LITEOS_COPTS_BASE += -mno-unaligned-access
LITEOS_COPTS_EXTRA += -mthumb-interwork
endif
endif
LITEOS_COPTS_EXTRA += -fno-short-enums
ifeq ($(LOSCFG_THUMB), y)
LITEOS_COPTS_EXTRA_INTERWORK := $(LITEOS_COPTS_EXTRA) -mthumb
LITEOS_CMACRO     += -DLOSCFG_INTERWORK_THUMB
else
LITEOS_COPTS_EXTRA_INTERWORK := $(LITEOS_COPTS_EXTRA)
#-fno-inline
endif

ifneq ($(LOSCFG_COMPILER_CLANG_LLVM), y)
LITEOS_LD_OPTS += -nostartfiles
endif
LITEOS_LD_OPTS += -static --gc-sections
LITEOS_LD_OPTS += $(LITEOS_DYNLOADOPTS)
LITEOS_LD_PATH += -L$(LITEOS_SCRIPTPATH)/ld -L$(LITEOSTOPDIR)/platform -L$(OUT)/lib -L$(LITEOS_LIB_BIGODIR) -L$(LITEOSTOPDIR)/tools/build
LITEOS_LD_PATH += -L$(LITEOS_COMPILER_GCCLIB_PATH) -L$(LITEOS_COMPILER_CXXLIB_PATH)
ifeq ($(LOSCFG_VENDOR) ,y)
LITEOS_LD_PATH +=  -L$(OUT)/lib/rdk -L$(OUT)/lib/sdk \
                   -L$(OUT)/lib/main_server
endif

ifeq ($(LOSCFG_COMPILER_CLANG_LLVM), y)
LITEOS_LD_SCRIPT := -T$(LITEOSTOPDIR)/tools/build/liteos_llvm.ld
else
LITEOS_LD_SCRIPT := -T$(LITEOSTOPDIR)/tools/build/liteos.ld
endif

# temporary
LITEOS_PLATFORM_INCLUDE += \
        -I $(LITEOSTOPDIR)/kernel/base/include
LITEOS_CXXINCLUDE += \
        $(LITEOS_NET_INCLUDE) \
        -I $(LITEOSTOPDIR)/kernel/base/include

LITEOS_COPTS_NODEBUG    := $(LITEOS_NODEBUG) $(LITEOS_COPTS_BASE) $(LITEOS_COPTS_EXTRA)
LITEOS_COPTS_INTERWORK  := $(LITEOS_INTERWORK) $(LITEOS_COPTS_BASE) $(LITEOS_COPTS_EXTRA_INTERWORK)
LITEOS_BASE_INCLUDE := $(LITEOS_KERNEL_INCLUDE) $(LITEOS_PLATFORM_INCLUDE) \
                       $(LITEOS_LIB_INCLUDE) $(LITEOS_FS_INCLUDE) \
                       $(LITEOS_EXTKERNEL_INCLUDE) \
                       $(LITEOS_COMPAT_INCLUDE) $(LITEOS_DRIVERS_INCLUDE) \
                       $(LOSCFG_TOOLS_DEBUG_INCLUDE) $(LITEOS_NET_INCLUDE)
LITEOS_CFLAGS_INTERWORK := $(LITEOS_COPTS_INTERWORK) $(LITEOS_CMACRO) \
                           $(LITEOS_IMAGE_MACRO) $(LITEOS_BASE_INCLUDE)
LITEOS_CFLAGS_NODEBUG := $(LITEOS_COPTS_NODEBUG) $(LITEOS_CMACRO) \
                         $(LITEOS_IMAGE_MACRO) $(LITEOS_BASE_INCLUDE)
