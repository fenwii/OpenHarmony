/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Description: ufs.c
 */

#include <common.h>
#include <command.h>
#include <env_internal.h>
#include <fdtdec.h>
#include <linux/stddef.h>
#include <malloc.h>
#include <memalign.h>
#include <ufs.h>
#include <part.h>
#include <search.h>
#include <errno.h>

DECLARE_GLOBAL_DATA_PTR;

#if !defined(CONFIG_ENV_OFFSET)
#define CONFIG_ENV_OFFSET 0
#endif

#define UFS_BLK_LEN 4096

static inline s64 ufs_offset(void)
{
	return CONFIG_ENV_OFFSET;
}

__weak int ufs_get_env_addr(u32 *env_addr)
{
	s64 offset = ufs_offset();

	*env_addr = offset;

	return 0;
}

#if defined(CONFIG_CMD_SAVEENV) && !defined(CONFIG_SPL_BUILD)
static int write_env(unsigned long size, unsigned long offset, const void *buffer)
{
	uint start, cnt, n;

	start = ALIGN(offset, UFS_BLK_LEN);
	cnt = ALIGN(size, UFS_BLK_LEN);

	n = ufs_write_storage((uint64_t)(uintptr_t)buffer, start, cnt);

	return (n == 0) ? 0 : -1;
}

static int env_ufs_save(void)
{
	ALLOC_CACHE_ALIGN_BUFFER(env_t, env_new, 1);
	u32	offset;
	int	ret;

	ufs_storage_init();

	ret = env_export(env_new);
	if (ret)
		goto err;

	if (ufs_get_env_addr(&offset)) {
		ret = 1;
		goto err;
	}

	printf("Writing to UFS... ");
	if (write_env(CONFIG_ENV_SIZE, offset, (u_char *)env_new)) {
		puts("failed\n");
		ret = 1;
		goto err;
	}

	ret = 0;

err:
	return ret;
}
#endif /* CONFIG_CMD_SAVEENV && !CONFIG_SPL_BUILD */

static int read_env(unsigned long size, unsigned long offset, const void *buffer)
{
	uint start, cnt, n;

	start = ALIGN(offset, UFS_BLK_LEN);
	cnt = ALIGN(size, UFS_BLK_LEN);

	n = ufs_read_storage((uint64_t)(uintptr_t)buffer, start, cnt);

	return (n == 0) ? 0 : -1;
}

static int env_ufs_load(void)
{
#if !defined(ENV_IS_EMBEDDED)
	ALLOC_CACHE_ALIGN_BUFFER(char, buf, CONFIG_ENV_SIZE);
	u32 offset;
	int ret;
	char *errmsg = NULL;

	ufs_storage_init();

	if (ufs_get_env_addr(&offset)) {
		ret = -EIO;
		goto err;
	}

	if (read_env(CONFIG_ENV_SIZE, offset, buf)) {
		errmsg = "!read failed";
		ret = -EIO;
		goto err;
	}

	ret = env_import(buf, 1);

err:
	if (ret)
		env_set_default(errmsg, 0);
#endif
	return ret;
}

U_BOOT_ENV_LOCATION(ufs) = {
	.location	= ENVL_UFS,
	ENV_NAME("UFS")
	.load		= env_ufs_load,
#ifndef CONFIG_SPL_BUILD
	.save		= env_save_ptr(env_ufs_save),
#endif
};
