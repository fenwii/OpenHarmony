/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "errno.h"
#include "fatfs.h"
#include "unistd.h"
#include "stdio.h"
#include "string.h"
#include "errcode_fat.h"
#include "integer.h"
#ifdef LOSCFG_FS_FAT

#define DEV_NAME_SIZE	4
int format(const char *dev, int sectors, int option)
{
	INT err;
	if (dev == NULL) {
		set_errno(EINVAL);
		return -1;
	}

	if (strncmp(dev, "/dev", DEV_NAME_SIZE) != 0) {
		PRINTK("Usage  :\n");
		PRINTK("        format <dev_inodename> <sectors> <option> <label>\n");
		PRINTK("        dev_inodename : the name of dev\n");
		PRINTK("        sectors       : Size of allocation unit in unit of byte or sector, ");
		PRINTK("0 instead of default size\n");
		PRINTK("        options       : Index of filesystem. 1 for FAT filesystem, 2 for FAT32 filesystem, ");
		PRINTK("7 for any, 8 for erase\n");
		PRINTK("        label         : The volume of device. It will be emptyed when this parameter is null\n");
		PRINTK("Example:\n");
		PRINTK("        format /dev/mmcblk0 128 2\n");

		set_errno(EINVAL);
		return -1;
	}
	err = fatfs_mkfs(dev, sectors, option);
	if (err < 0) {
		set_errno(-err);
		return -1;
	}
#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION
	else if (err >= VIRERR_BASE) {
		set_errno(err);
	}
#endif
	return 0;
}

void set_label(const char *name)
{
	INT len;
	INT err;

	(void)memset_s(FatLabel, LABEL_LEN, 0, LABEL_LEN);

	if (name == NULL || *name == '\0') {
		return;
	}

	len = strlen(name);
	if (len >= LABEL_LEN) {
		len = LABEL_LEN - 1;
	}

	err = strncpy_s(FatLabel, LABEL_LEN, name, len);
	if (err != EOK) {
		PRINT_ERR("Fat set_label error");
	}
}
#endif	/* #ifdef CONFIG_FS_FAT */
