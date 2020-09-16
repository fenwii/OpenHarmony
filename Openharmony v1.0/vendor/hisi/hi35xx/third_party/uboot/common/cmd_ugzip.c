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

/*
 * Command for compress.
 */

#include <common.h>

#define HEAD_SIZE   0X10
#define COMPRESSED_SIZE_OFFSET      0X0

#define HEAD_MAGIC_NUM0 0X70697A67/*'g''z''i''p'*/
#define HEAD_MAGIC_NUM0_OFFSET 0X8
#define HEAD_MAGIC_NUM1 0X64616568/*'h''e''a''d'*/
#define HEAD_MAGIC_NUM1_OFFSET 0XC
extern unsigned int hw_dec_type;
extern void hw_dec_init(void);
extern void hw_dec_uinit(void);
#if (defined CONFIG_TARGET_HI3559AV100) || (defined CONFIG_HI3559AV100) || \
    (defined CONFIG_TARGET_HI3556AV100) || (defined CONFIG_TARGET_HI3519AV100) ||\
    (defined CONFIG_TARGET_HI3569V100)  || (defined CONFIG_HI3569V100)
extern int hw_dec_decompress(unsigned char *dst_h32, unsigned char *dst_l32,
				int *dstlen, unsigned char *src_h32,
				unsigned char *src_l32, int srclen, void *unused);
#endif
#if ((defined CONFIG_TARGET_HI3559V200) || (defined CONFIG_TARGET_HI3556V200) || \
	(defined CONFIG_TARGET_HI3516DV300) || (defined CONFIG_TARGET_HI3516AV300) || \
	(defined CONFIG_TARGET_HI3516CV500) || (defined CONFIG_TARGET_HI3516EV200) || \
	(defined CONFIG_TARGET_HI3516EV300) || (defined CONFIG_TARGET_HI3518EV300) || \
	(defined CONFIG_TARGET_HI3516DV200) || (defined CONFIG_TARGET_HI3562V100)  || \
	(defined CONFIG_TARGET_HI3566V100))
extern int hw_dec_decompress(unsigned char *dst, int *dstlen,
				unsigned char *src, int srclen,
				void *unused);
#endif

static int do_ugzip(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	uintptr_t  src, dst;
	int size_comparessed, size_uncomparessed;
	unsigned int magic_num0, magic_num1;
	int ret = 0;
	/* need two arguments */
	if (argc != 3)
		goto usage;

	src = simple_strtoul(argv[1], NULL, 16);
	dst = simple_strtoul(argv[2], NULL, 16);

	if (src & 0XF) {
		printf("ERR:\n    src[0X%08lx] is not 16Byte-aligned!\n", src);
		return 1;
	}
	if (dst & 0XF) {
		printf("ERR:\n    dst[0X%08lx] is not 16Byte-aligned!\n", dst);
		return 1;
	}

	magic_num0 = *(unsigned int *)(src + HEAD_MAGIC_NUM0_OFFSET);
	magic_num1 = *(unsigned int *)(src + HEAD_MAGIC_NUM1_OFFSET);
	if ((magic_num0 != HEAD_MAGIC_NUM0) || (magic_num1 != HEAD_MAGIC_NUM1)) {
		printf("ERR:\n    The magic numbers are not correct!\n"\
			   "    Please check the source data!\n");
		return 1;
	}
	size_comparessed = *(int *)(src + COMPRESSED_SIZE_OFFSET);
	size_uncomparessed = *(int *)(src + UNCOMPRESSED_SIZE_OFFSET);
	/*use direct address mode*/
	hw_dec_type = 0;
	/*init hw decompress IP*/
	hw_dec_init();
	/*start decompress*/
#if (defined CONFIG_TARGET_HI3559AV100) || (defined CONFIG_HI3559AV100) || \
    (defined CONFIG_TARGET_HI3556AV100) || (defined CONFIG_TARGET_HI3519AV100) ||\
    (defined CONFIG_TARGET_HI3569V100)  || (defined CONFIG_HI3569V100)
	ret = hw_dec_decompress(NULL, (unsigned char *)dst, \
				&size_uncomparessed, NULL, \
				(unsigned char *)(src + HEAD_SIZE), \
				size_comparessed, NULL);
#endif
#if ((defined CONFIG_TARGET_HI3559V200) || (defined CONFIG_TARGET_HI3556V200) || \
	(defined CONFIG_TARGET_HI3516DV300) || (defined CONFIG_TARGET_HI3516AV300) || \
	(defined CONFIG_TARGET_HI3516CV500) || (defined CONFIG_TARGET_HI3516EV200) || \
	(defined CONFIG_TARGET_HI3516EV300) || (defined CONFIG_TARGET_HI3518EV300) || \
	(defined CONFIG_TARGET_HI3516DV200) || (defined CONFIG_TARGET_HI3562V100)  || \
	(defined CONFIG_TARGET_HI3566V100))
	ret = hw_dec_decompress((unsigned char *)dst, &size_uncomparessed, \
					(unsigned char *)(src + HEAD_SIZE), \
					size_comparessed, NULL);
#endif
	if (ret)
		printf("ERR:\n    decompress fail!\n");
	else
		printf("decompress ok!\n");
	/*uinit hw decompress IP*/
	hw_dec_uinit();

	return 1;

usage:
	cmd_usage(cmdtp);
	return 1;
}

U_BOOT_CMD(
	ugzip,  3,  1,  do_ugzip,
	"Compress gzipfile with hardware IP",
	"ugzip <src> <dst>\n"
	"src and dst must be 16Byte-aligned"
);

