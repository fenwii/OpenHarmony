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
 */

#include <common.h>
#include <command.h>

#ifdef CONFIG_GODNET
#include <godnet_vo.h>
#endif

#ifdef CONFIG_GODARM
#include <godarm_vo.h>
#endif

#ifdef CONFIG_HI3535
#include <hi3535_vo.h>
#endif

#ifdef CONFIG_HI3520D
#include <hi3520d_vo.h>
#endif

#ifdef CONFIG_HI3516A
#include <hi3516a_vo.h>
#endif

#ifdef CONFIG_HI3536
#include <hi3536_vo.h>
#endif

#ifdef CONFIG_HI3521A
#include <hi3521a_vo.h>
#endif

#ifdef CONFIG_HI3531A
#include <hi3531a_vo.h>
#endif

// must be related to a chip
#include <hi3559av100_vo.h>

extern int load_jpeg(void);
extern int jpeg_decode(unsigned int format);

int do_jpgd(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	int ret;
	unsigned int format;

	if (argc < 2) {
		printf("Insufficient parameter!\n");
		printf("Usage:\n%s\n", cmdtp->usage);
		return -1;
	}

	format  = (unsigned int)simple_strtoul(argv[1], NULL, 10);
#ifdef RGB_OUTPUT_ENABLE
	if (format > 2) {
#else
	if (format != 0) {
#endif
		printf("Invalid parameter!\n");
		return -1;
	}

#ifdef CONFIG_SYS_LONGHELP
	printf("you should first set:\n%s\n", cmdtp->help);
#endif

	ret = load_jpeg();
	if (ret != 0) {
		printf("load jpeg err. \n");
		//todo return 0 or ret?
		return 0;
	}
	jpeg_decode(format);

	printf("decode jpeg!\n");

	return 0;
}

U_BOOT_CMD(
	decjpg,    CFG_MAXARGS, 1,  do_jpgd,
	"jpgd   - decode jpeg picture.\n"
	"decjpg [format]",
	"\nargs: [format]\n"
#ifdef RGB_OUTPUT_ENABLE
	"\t-<format> : 0: semi-plannar yvu420, 1: ARGB1555, 2: ARGB8888\n"
#else
	"\t-<format> : 0: semi-plannar yvu420\n"
#endif
	"\t- setenv jpeg_addr     0x--------\n"
	"\t- setenv jpeg_size     0x--------\n"
	"\t- setenv vobuf         0x--------\n"
	"\t- setenv jpeg_emar_buf 0x--------\n"
);


