/*
 * cmd_tzasc.c
 *
 * Adding a enable_tzasc command for optee DDR partition.
 *
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
 */

#include <common.h>

#define writel(addr, value) ((*(volatile unsigned int *)(addr)) = (value))

#define io_address(x)             (x)
#define TZASC_BASE_ADDR           io_address(0x04601000)

#define SEC_BYPASS                ((TZASC_BASE_ADDR) + (0x4))
#define SEC_INTEN                 ((TZASC_BASE_ADDR) + (0x20))
#define sec_rgn_map(n)            ((TZASC_BASE_ADDR) + (0x100) + (0x10 * (n)))
#define sec_rgn_map_ext(n)        ((TZASC_BASE_ADDR) + (0x200) + (0x10 * (n)))
#define sec_rgn_attrib(n)         ((TZASC_BASE_ADDR) + (0x104) + (0x10 * (n)))

typedef struct {
	unsigned int index;

	unsigned int start_addr;
	unsigned int size;

	unsigned int secure_mode;
#define NON_SECURE_W    0x1 << 0
#define NON_SECURE_R    0x1 << 1
#define SECURE_W        0x1 << 2
#define SECURE_R        0x1 << 3
} region_attr_t;

static const region_attr_t g_bsp_regions[] = {
	{1, 0x20000000, 0x12400000, NON_SECURE_W | NON_SECURE_R | SECURE_W | SECURE_R },
	{2, 0x32400000, 0x01200000, SECURE_W | SECURE_R },
	{3, 0x33600000, 0x0CA00000, NON_SECURE_W | NON_SECURE_R | SECURE_W | SECURE_R },
};

static void creat_region(const region_attr_t *region_attr)
{
	/* bit31: enable; bit23~bit0: start addr */
	writel(sec_rgn_map(region_attr->index),
		   (0x1 << 31) + (region_attr->start_addr >> 16));

	/* bit23~bit0: addr size */
	writel(sec_rgn_map_ext(region_attr->index), (region_attr->size >> 16) - 1);

	writel(sec_rgn_attrib(region_attr->index), 0x10 + region_attr->secure_mode);
}

static void tzasc_enable(void)
{
	writel(SEC_INTEN, 0x0);
	writel(SEC_BYPASS, 0xff);
}

static void config_rgn0(void)
{
	writel(sec_rgn_attrib(0), 0x1f);
}

static int do_enable_tzasc(cmd_tbl_t *cmdtp, int flag, int argc,
						   char *const argv[])
{
	int i;

	config_rgn0();

	for (i = 0; i < sizeof(g_bsp_regions) / sizeof(region_attr_t); i++)
		creat_region(&g_bsp_regions[i]);

	tzasc_enable();

	return 0;
}

U_BOOT_CMD(enable_tzasc, 1, 1, do_enable_tzasc, "Enable tzasc",
		   "For example: enable tzasc function");
