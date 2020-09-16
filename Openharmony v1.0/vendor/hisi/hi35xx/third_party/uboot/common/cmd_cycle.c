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
#include <compiler.h>

typedef unsigned char           hi_u8;
typedef unsigned char           hi_uchar;
typedef unsigned short          hi_u16;
typedef unsigned int            hi_u32;
typedef unsigned long           hi_ul;

typedef char                    hi_s8;
typedef short                   hi_s16;
typedef int                     hi_s32;

typedef char                    hi_char;
typedef char                   *hi_pchar;


#define CYCLE_MAGIC_HEAD        0x6379636c

#define CYCLE_MAGIC_ITEM_START  0x63796373

#define CYCLE_MAGIC_ITEM_END    0x63796365

/** Cycle Head Infomation */
typedef struct hicycle_head_s {
	hi_u32 u32magichead;
	hi_u32 u32cycleflashsize; /**<include cycle_head size */
	hi_u32 u32compress: 2;
	hi_u32 u32writeflag: 3;
	hi_u32 u32reserved: 27;
	hi_u32 u32alignsize;
} hi_cycle_head_s;

/** Cycle Item Infomation */
typedef struct hicycle_item_start_s {
	hi_u32 u32magicitemstart;
	hi_u32 u32itemlen;
	hi_u32 u32itemalllen;
	hi_u32 u32itemoriginlen;
} hi_cycle_item_start_s;

#define DIVIDE 3
#define BYTE_ALIGN ((hi_u32)16)  /**<needed by decompress */

extern unsigned int hw_dec_type;
extern void hw_dec_init(void);
#if (defined CONFIG_TARGET_HI3559AV100) || (defined CONFIG_HI3559AV100) ||\
    (defined CONFIG_TARGET_HI3556AV100) || (defined CONFIG_TARGET_HI3519AV100) ||\
    (defined CONFIG_TARGET_HI3569V100) || (defined CONFIG_HI3569V100)
extern int hw_dec_decompress(unsigned char *dst_h32, unsigned char *dst_l32,
				int *dstlen,
				unsigned char *src_h32, unsigned char *src_l32,
				int srclen, void *unused);
#endif
#if ((defined CONFIG_TARGET_HI3559V200) || (defined CONFIG_TARGET_HI3556V200) ||\
	(defined CONFIG_TARGET_HI3516DV300) || (defined CONFIG_TARGET_HI3516AV300) ||\
	(defined CONFIG_TARGET_HI3516CV500) || (defined CONFIG_TARGET_HI3516EV200) ||\
	(defined CONFIG_TARGET_HI3516EV300) || (defined CONFIG_TARGET_HI3518EV300) ||\
	(defined CONFIG_TARGET_HI3516DV200) || (defined CONFIG_TARGET_HI3562V100)  ||\
	(defined CONFIG_TARGET_HI3566V100))
extern int hw_dec_decompress(unsigned char *dst, int *dstlen,
							 unsigned char *src, int srclen,
							 void *unused);
#endif
extern void hw_dec_uinit(void);

#define cycle_err(fmt, args...) printf("ERR: <%s:%d> "fmt, __FUNCTION__,\
							     __LINE__, ##args)
#define cycle_dbg(fmt, args...) printf("DBG: <%s:%d> "fmt, __FUNCTION__,\
							     __LINE__, ##args)

static hi_s32 cycle_get_initdata(hi_ul ulsrc, hi_u32 u32srclen,
				hi_cycle_item_start_s **ppstItem,
				hi_u32 *pu32Compress)
{
	hi_cycle_head_s *psthead = NULL;
	hi_cycle_item_start_s *pstitem = NULL;
	hi_u32 u32itemmagicend;
	hi_ul ulbuffer = ulsrc;

	/* Cycle Head */
	psthead = (hi_cycle_head_s *)ulsrc;

	if ((CYCLE_MAGIC_HEAD != psthead->u32magichead) ||
			(u32srclen < psthead->u32cycleflashsize) ||
			(0 == psthead->u32alignsize)) {
		cycle_err("psthead->u32magichead: %#x\n",
				  psthead->u32magichead);
		cycle_err("SrcLen[%u] CycleFlashSize[%u]\n", u32srclen,
				  psthead->u32cycleflashsize);
		return -1;
	}

	/* Compress Type */
	*pu32Compress = psthead->u32compress;
	cycle_dbg("Compress[%u]\n", *pu32Compress);

	/* First Item */
	ulbuffer += sizeof(hi_cycle_head_s);
	ulbuffer = (ulbuffer + psthead->u32alignsize - 1) &
			   ~(psthead->u32alignsize - 1);

	pstitem = (hi_cycle_item_start_s *)ulbuffer;
	if ((pstitem->u32itemlen == 0) ||
		((pstitem->u32itemlen % BYTE_ALIGN) != 0)) {
		cycle_err("pstitem->u32itemlen: %#x\n", pstitem->u32itemlen);
		return -1;
	}

	u32itemmagicend = *(hi_u32 *)(uintptr_t)(ulbuffer +
				(pstitem->u32itemlen + sizeof(hi_cycle_item_start_s)));

	if ((CYCLE_MAGIC_ITEM_START != pstitem->u32magicitemstart) ||
		(pstitem->u32itemalllen >= (psthead->u32cycleflashsize / DIVIDE)) ||
		(CYCLE_MAGIC_ITEM_END != u32itemmagicend)) {
		cycle_err(
			"Item MagicStart[%#x] Len[%u] MagicEnd[%#x] CycleFlashSize[%u]\n",
			pstitem->u32magicitemstart, pstitem->u32itemlen, u32itemmagicend,
			psthead->u32cycleflashsize);
		return -1;
	}

	while (1) {
		/* update item to last valid one */
		*ppstItem = (hi_cycle_item_start_s *)ulbuffer;

		/* check next item valid or not */
		ulbuffer += pstitem->u32itemalllen;

		pstitem = (hi_cycle_item_start_s *)ulbuffer;

		/* <check buffer finish */
		if (ulbuffer - ulsrc >= psthead->u32cycleflashsize)
			return 0;

		if (CYCLE_MAGIC_ITEM_START != pstitem->u32magicitemstart) {
			/* <unused zone, use previous item */
			if (pstitem->u32magicitemstart ==
				0xffffffff) {
				return 0;
			} else {
				cycle_err(
					"pstitem->u32magicitemstart(0x%x) wrong!\n",
					pstitem->u32magicitemstart);
				return -1;
			}
		}

		u32itemmagicend = *(hi_u32 *)(uintptr_t)(ulbuffer +
					(pstitem->u32itemlen + sizeof(hi_cycle_item_start_s)));

		/* <item data damaged */
		if ((pstitem->u32itemlen >=
			 (psthead->u32cycleflashsize / DIVIDE)) ||
			(CYCLE_MAGIC_ITEM_END != u32itemmagicend)) {
			cycle_err("\n");
			return -1;
		}
	}

	return -1;
}

static hi_s32 cycle_get_data(hi_ul ulsrc, hi_u32 u32srclen, hi_ul uldst)
{
	hi_s32 s32ret = -1;

	hi_cycle_item_start_s *pstitem = NULL;
	hi_ul  ulitemdata = 0;
	hi_u32 ncompressed = 0;

	s32ret = cycle_get_initdata(ulsrc, u32srclen, &pstitem, &ncompressed);
	if ((s32ret == 0) && pstitem) {
		ulitemdata += (uintptr_t)pstitem + sizeof(hi_cycle_item_start_s);

		if (ncompressed) {
			hw_dec_type = 0; /**<use direct address mode*/
			hw_dec_init(); /**<init hw decompress IP*/

			hi_s32 s32sizecompressed = pstitem->u32itemoriginlen;
#if (defined CONFIG_TARGET_HI3559AV100) || (defined CONFIG_HI3559AV100) || \
    (defined CONFIG_TARGET_HI3556AV100) || (defined CONFIG_TARGET_HI3519AV100) ||\
    (defined CONFIG_TARGET_HI3569V100) || (defined CONFIG_HI3569V100)
			s32ret = hw_dec_decompress(NULL, (hi_u8 *)(uintptr_t)uldst, &s32sizecompressed,
						NULL, (hi_u8 *)ulitemdata, pstitem->u32itemlen, NULL);
#endif
#if ((defined CONFIG_TARGET_HI3559V200) || (defined CONFIG_TARGET_HI3556V200) || \
	(defined CONFIG_TARGET_HI3516DV300) || (defined CONFIG_TARGET_HI3516AV300) || \
	(defined CONFIG_TARGET_HI3516CV500) || (defined CONFIG_TARGET_HI3516EV200) || \
	(defined CONFIG_TARGET_HI3516EV300) || (defined CONFIG_TARGET_HI3518EV300) || \
	(defined CONFIG_TARGET_HI3516DV200) || (defined CONFIG_TARGET_HI3562V100)   || \
	(defined CONFIG_TARGET_HI3566V100))
			s32ret = hw_dec_decompress((hi_u8 *)(uintptr_t)uldst, &s32sizecompressed,
						(hi_u8 *)ulitemdata, pstitem->u32itemlen, NULL);
#endif
			if (s32ret == 0 &&
					s32sizecompressed == pstitem->u32itemoriginlen) {
				cycle_dbg("decompress ok!\n");
				s32ret = 0;
			} else {
				memset((void *)(uintptr_t)uldst, 0, 16);
				cycle_err(
					"decompress fail[%#x]! uncompress size[%#x]\n",
					s32ret, s32sizecompressed);
				s32ret = -1;
			}

			hw_dec_uinit(); /**<uinit hw decompress IP*/
		} else {
			memcpy((void *)(uintptr_t)uldst, (void *)(uintptr_t)ulitemdata,
				   pstitem->u32itemlen);
			s32ret = 0;
		}
	} else {
		memset((void *)(uintptr_t)uldst, 0, 16);
		cycle_err("Failed to get cycle data. dst: 0x%lx\n", uldst);
		s32ret = -1;
	}

	return s32ret;
}

static hi_s32 getcycledata(hi_ul ulsrc, hi_ul ulsrcbak, hi_u32 u32srclen,
						   hi_ul uldst)
{
	hi_s32 s32ret = cycle_get_data(ulsrc, u32srclen, uldst);
	if (s32ret == -1 && ulsrcbak != 0)
		s32ret = cycle_get_data(ulsrcbak, u32srclen, uldst);

	return s32ret;
}

static int do_cycle(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	hi_ul  ulsrc;
	hi_ul  ulsrcbak;
	hi_ul  uldst;
	hi_u32 u32srclen;

	/* Check Input Args Count : four arguments needed */
	if (argc != 5)
		goto usage;

	ulsrc     = simple_strtoul(argv[1], NULL, 16);
	ulsrcbak  = simple_strtoul(argv[2], NULL, 16);
	u32srclen = simple_strtoul(argv[3], NULL, 16);
	uldst     = simple_strtoul(argv[4], NULL, 16);

	if (ulsrc & 0XF) {
		printf("ERR:\n  src[0X%08lx] is not 16Byte-aligned!\n", ulsrc);
		return 1;
	}

	if (ulsrcbak & 0XF) {
		printf("ERR:\n  src_backup[0X%08lx] is not 16Byte-aligned!\n",
			   ulsrcbak);
		return 1;
	}

	if (u32srclen & 0XFFFF) {
		printf("ERR:\n  src_len[0X%08x] is not 0x10000Byte-aligned!\n",
			   u32srclen);
		return 1;
	}

	if (uldst & 0XF) {
		printf("ERR:\n  dst[0X%08lx] is not 16Byte-aligned!\n", uldst);
		return 1;
	}

	return getcycledata(ulsrc, ulsrcbak, u32srclen, uldst);

usage:
	cmd_usage(cmdtp);
	return 1;
}

U_BOOT_CMD(
	cread,  5,  1,  do_cycle,
	"get valid data from cycle_data buffer. 'cycle <src> <src_backup>  <src_len> <dst>'",
	"1. src_backup can be 0.  2. if src and src_backup are wrong, "
	"dst head (16 byte) will be set to 0.  3. src and dst must be 16Byte-aligned"
);

