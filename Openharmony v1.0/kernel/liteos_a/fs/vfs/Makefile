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

MODULE_NAME := $(notdir $(shell pwd))

LOCAL_SRCS := \
$(LITEOSTHIRDPARTY)/NuttX/fs/fs_initialize.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_close.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_dup2.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_dup.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_dupfd2.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_dupfd.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_fcntl.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_fsync.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_getfilep.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_ioctl.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_lseek.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_lseek64.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_mkdir.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_open.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_poll.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_pread.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_pread64.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_pwrite.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_pwrite64.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_read.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_rename.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_rmdir.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_select.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_sendfile.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_stat.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_statfs.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_truncate.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_truncate64.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_unlink.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/vfs/fs_write.c \
$(wildcard operation/*.c) \
\
$(LITEOSTHIRDPARTY)/NuttX/fs/inode/fs_files.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/inode/fs_foreachinode.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/inode/fs_inodeaddref.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/inode/fs_inode.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/inode/fs_inodefind.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/inode/fs_inoderelease.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/inode/fs_inoderemove.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/inode/fs_inodereserve.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/inode/fs_inodesearch.c \
\
$(LITEOSTHIRDPARTY)/NuttX/fs/dirent/fs_closedir.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/dirent/fs_opendir.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/dirent/fs_readdir.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/dirent/fs_rewinddir.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/dirent/fs_seekdir.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/dirent/fs_telldir.c \
\
$(LITEOSTHIRDPARTY)/NuttX/fs/mount/fs_foreachmountpoint.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/mount/fs_mount.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/mount/fs_umount.c \
\
$(LITEOSTHIRDPARTY)/NuttX/fs/driver/fs_blockproxy.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/driver/fs_closeblockdriver.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/driver/fs_devsyslog.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/driver/fs_findblockdriver.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/driver/fs_openblockdriver.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/driver/fs_registerblockdriver.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/driver/fs_registerdriver.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/driver/fs_unregisterblockdriver.c \
$(LITEOSTHIRDPARTY)/NuttX/fs/driver/fs_unregisterdriver.c \
\
$(wildcard vfs_cmd/*.c)

LOCAL_INCLUDE := \
	-I $(LITEOSTOPDIR)/fs/vfs/include \
	-I $(LITEOSTOPDIR)/fs/vfs/include/bcache\
	-I $(LITEOSTOPDIR)/fs/vfs/include/disk\
	-I $(LITEOSTOPDIR)/fs/vfs/include/driver\
	-I $(LITEOSTOPDIR)/fs/vfs/include/multi_partition\
	-I $(LITEOSTOPDIR)/fs/vfs/include/operation\
	-I $(LITEOSTOPDIR)/fs/include/inode\
	-I $(LITEOSTOPDIR)/syscall

ifeq ($(LOSCFG_FS_FAT), y)
LOCAL_INCLUDE += -I $(LITEOSTHIRDPARTY)/FatFs/source
endif

LOCAL_FLAGS := $(LOCAL_INCLUDE) $(LITEOS_GCOV_OPTS)

include $(MODULE)
