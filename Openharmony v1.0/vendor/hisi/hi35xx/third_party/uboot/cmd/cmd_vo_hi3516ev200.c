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
#include "hi3516ev200_vo.h"

#define CMD_VO_ARGS_BASE10 10
#define CMD_VO_ARGS_BASE16 16
#define CMD_VO_ARGS_BASE_ALL 0

extern int set_vobg(unsigned int dev, unsigned int rgb);
extern int start_vo(unsigned int dev, unsigned int type, unsigned int sync);
extern int stop_vo(unsigned int dev);
extern int start_videolayer(unsigned int layer, unsigned long addr, unsigned int strd, hi_vo_rect layer_rect);
extern int stop_videolayer(unsigned int layer);
extern int start_gx(unsigned int layer, unsigned long addr, unsigned int strd, hi_vo_rect gx_rect);
extern int stop_gx(unsigned int layer);

static int check_vo_support(unsigned int dev, unsigned int type, unsigned int sync)
{
    /* check interface type, ONLY VGA & HDMI interface is supported. */
    if (dev == VO_DEV_DHD0) {
        if ((type & (~(VO_INTF_BT1120 | VO_INTF_BT656 | VO_INTF_LCD_6BIT | VO_INTF_LCD_8BIT | VO_INTF_LCD_16BIT))) ||
            (type == 0)) {
            printf("hd%u only supports BT.656,BT.1120,LCD_6BIT/8BIT/16BIT intftype, intf %u is illegal!\n",
                   dev, type);
            return -1;
        }
    } else {
        printf("unknow dev(%u)!\n", dev);
        return -1;
    }

    if (sync == VO_OUTPUT_USER) {
        return 0;
    }

    if (VO_INTF_BT1120 & type) {
        if ((((sync < VO_OUTPUT_1080P24) && (sync > VO_OUTPUT_1080I60)) ||
             ((sync < VO_OUTPUT_576P50) && (sync > VO_OUTPUT_1024x768_60))) &&
            (sync != VO_OUTPUT_640x480_60)) {
            printf("vo%u's intfsync %u illegal!\n", dev, sync);
            return -1;
        }
    }

    if (VO_INTF_BT656 & type) {
        if ((sync != VO_OUTPUT_PAL) && (sync != VO_OUTPUT_NTSC)) {
            printf("vo%u's intfsync %u illegal!\n", dev, sync);
            return -1;
        }
    }

    if (VO_INTF_LCD_8BIT & type) {
        if (VO_OUTPUT_320x240_60 != sync) {
            printf("vo%u's intfsync %u illegal!\n", dev, sync);
            return -1;
        }
    }

    if (VO_INTF_LCD_6BIT & type) {
        if ((sync < VO_OUTPUT_320x240_50) || (sync > VO_OUTPUT_240x320_50)) {
            printf("vo%u's intfsync %u illegal!\n", dev, sync);
            return -1;
        }
    }

    if (VO_INTF_LCD_16BIT & type) {
        if (VO_OUTPUT_240x320_60 != sync) {
            printf("vo%u's intfsync %u illegal!\n", dev, sync);
            return -1;
        }
    }

    return 0;
}

static int do_vobg(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    unsigned int dev, rgb;

    if (argc < 3) {
        printf("insufficient parameter!\n");
        printf("usage:\n%s\n", cmdtp->usage);
        return -1;
    }

    dev = (unsigned int)simple_strtoul(argv[1], NULL, CMD_VO_ARGS_BASE10);
    rgb = (unsigned int)simple_strtoul(argv[2], NULL, CMD_VO_ARGS_BASE_ALL);
    if (dev >= VO_DEV_BUTT) {
        printf("invalid parameter!\n");
        return -1;
    }

    set_vobg(dev, rgb);

    printf("dev %u set background color!\n", dev);

    return 0;
}

static int do_startvo(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    unsigned int dev, intftype, sync;

    if (argc < 4) {
        printf("insufficient parameter!\n");
        printf("usage:\n%s\n", cmdtp->usage);
        return -1;
    }

    dev = (unsigned int)simple_strtoul(argv[1], NULL, CMD_VO_ARGS_BASE10);
    intftype = (unsigned int)simple_strtoul(argv[2], NULL, CMD_VO_ARGS_BASE10);
    sync = (unsigned int)simple_strtoul(argv[3], NULL, CMD_VO_ARGS_BASE10);
    if ((dev >= VO_DEV_BUTT) || (sync >= VO_OUTPUT_BUTT)) {
        printf("invalid parameter!\n");
        return -1;
    }

    if (check_vo_support(dev, intftype, sync)) {
        printf("unsupport parameter!\n");
        return -1;
    }

    start_vo(dev, intftype, sync);

    printf("dev %u opened!\n", dev);

    return 0;
}

static int do_stopvo(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    unsigned int dev;
    if (argc < 2) {
        printf("insufficient parameter!\n");
        printf("usage:\n%s\n", cmdtp->usage);
        return -1;
    }

    dev = (unsigned int)simple_strtoul(argv[1], NULL, CMD_VO_ARGS_BASE10);
    if (dev >= VO_DEV_BUTT) {
        printf("invalid parameter!\n");
        return -1;
    }

    stop_vo(dev);

    printf("dev %u closed!\n", dev);

    return 0;
}

static int do_startvl(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    unsigned int layer, strd, x, y, w, h;
    unsigned long addr;
    hi_vo_rect layer_rect;

    if (argc < 8) {
        printf("insufficient parameter!\n");
        printf("usage:\n%s\n", cmdtp->usage);
        return -1;
    }

    layer = (unsigned int)simple_strtoul(argv[1], NULL, CMD_VO_ARGS_BASE10);
    addr = (unsigned long)simple_strtoul(argv[2], NULL, CMD_VO_ARGS_BASE16);
    strd = (unsigned int)simple_strtoul(argv[3], NULL, CMD_VO_ARGS_BASE10);
    x = (unsigned int)simple_strtoul(argv[4], NULL, CMD_VO_ARGS_BASE10);
    y = (unsigned int)simple_strtoul(argv[5], NULL, CMD_VO_ARGS_BASE10);
    w = (unsigned int)simple_strtoul(argv[6], NULL, CMD_VO_ARGS_BASE10);
    h = (unsigned int)simple_strtoul(argv[7], NULL, CMD_VO_ARGS_BASE10);

    if ((layer != VO_LAYER_VHD0) ||
        (strd > (PIC_MAX_WIDTH * 2)) ||
        ((x > PIC_MAX_WIDTH) || (x & 0x1)) ||
        ((y > PIC_MAX_HEIGHT) || (y & 0x1)) ||
        ((w > PIC_MAX_WIDTH) || (w & 0x1) || (w < PIC_MIN_LENTH)) ||
        ((h > PIC_MAX_HEIGHT) || (h & 0x1) || (h < PIC_MIN_LENTH))) {
        printf("invalid parameter!\n");
        return -1;
    }

    layer_rect.x = x;
    layer_rect.y = y;
    layer_rect.w = w;
    layer_rect.h = h;

    start_videolayer(layer, addr, strd, layer_rect);

    printf("video layer %u opened!\n", layer);

    return 0;
}

static int do_stopvl(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    unsigned int layer;

    if (argc < 2) {
        printf("insufficient parameter!\n");
        printf("usage:\n%s\n", cmdtp->usage);
        return -1;
    }

    layer = (unsigned int)simple_strtoul(argv[1], NULL, CMD_VO_ARGS_BASE10);

    if (layer > VO_LAYER_VHD0) {
        printf("invalid parameter!\n");
        return -1;
    }

    stop_videolayer(layer);

    printf("video layer %u closed!\n", layer);

    return 0;
}

static int do_startgx(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    unsigned int layer, strd, x, y, w, h;
    unsigned long addr;
    hi_vo_rect gx_rect;
    if (argc < 8) {
        printf("insufficient parameter!\n");
        printf("usage:\n%s\n", cmdtp->usage);
        return -1;
    }

    layer = (unsigned int)simple_strtoul(argv[1], NULL, CMD_VO_ARGS_BASE10);
    addr = (unsigned long)simple_strtoul(argv[2], NULL, CMD_VO_ARGS_BASE16);
    strd = (unsigned int)simple_strtoul(argv[3], NULL, CMD_VO_ARGS_BASE10);
    x = (unsigned int)simple_strtoul(argv[4], NULL, CMD_VO_ARGS_BASE10);
    y = (unsigned int)simple_strtoul(argv[5], NULL, CMD_VO_ARGS_BASE10);
    w = (unsigned int)simple_strtoul(argv[6], NULL, CMD_VO_ARGS_BASE10);
    h = (unsigned int)simple_strtoul(argv[7], NULL, CMD_VO_ARGS_BASE10);

    if ((layer != VO_GRAPHC_G0) ||
        ((x > PIC_MAX_WIDTH) || (x & 0x1)) ||
        ((y > PIC_MAX_HEIGHT) || (y & 0x1)) ||
        ((w > PIC_MAX_WIDTH) || (w & 0x1) || (w < PIC_MIN_LENTH)) ||
        ((h > PIC_MAX_HEIGHT) || (h & 0x1) || (h < PIC_MIN_LENTH))) {
        printf("invalid parameter!\n");
        return -1;
    }

    gx_rect.x = x;
    gx_rect.y = y;
    gx_rect.w = w;
    gx_rect.h = h;

    start_gx(layer, addr, strd, gx_rect);

    printf("graphic layer %u opened!\n", layer);

    return 0;
}

static int do_stopgx(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    unsigned int layer;

    if (argc < 2) {
        printf("insufficient parameter!\n");
        printf("usage:\n%s\n", cmdtp->usage);
        return -1;
    }

    layer = (unsigned int)simple_strtoul(argv[1], NULL, CMD_VO_ARGS_BASE10);

    if (layer >= VO_GRAPHC_BUTT) {
        printf("invalid parameter!\n");
        return -1;
    }

    stop_gx(layer);

    printf("graphic layer %u closed!\n", layer);

    return 0;
}

U_BOOT_CMD(startvo, CFG_MAXARGS, 1, do_startvo,
       "startvo   - open vo device with a certain output interface.\n"
       "\t- startvo [dev intftype sync]",
       "\nargs: [dev, intftype, sync]\n"
       "\t-<dev> : 0: DHD0\n"
       "\t-<intftype>: 8(BT.656),16(BT.1120),512(LCD_6BIT),1024(LCD_8BIT),2048(LCD_16BIT)\n"
       "\t-<sync>: typical value:\n"
       "\t\tfor BT.656:\n"
       "\t\t\t0(PAL),           1(NTSC)\n"
       "\t\tfor BT.1120:\n"
       "\t\t\t2(1080P24),       3(1080P25),       4(1080P30),       5(720P50)\n"
       "\t\t\t6(720P60),        7(1080I50),       8(1080I60),       11(576P50)\n"
       "\t\t\t12(480P60),       13(800x600),      14(1024x768),     22(640x480)\n"
       "\t\tfor LCD:\n"
       "\t\t\t39(320x240P60),    40(320x240P50),   41(240x320P50), 42(240x320P60)\n");

U_BOOT_CMD(stopvo, CFG_MAXARGS, 1, do_stopvo,
       "stopvo   - close interface of vo device.\n"
       "\t- stopvo [dev]",
       "\nargs: [dev]\n"
       "\t-<dev> : 0(HD0)\n");

U_BOOT_CMD(startvl, CFG_MAXARGS, 1, do_startvl,
       "startvl   - open video layer.\n"
       "\t- startvl [layer addr stride x y w h]\n",
       "\nargs: [layer, addr, stride, x, y, w, h]\n"
       "\t-<layer>   : 0(V0)\n"
       "\t-<addr>    : picture address\n"
       "\t-<stride>  : picture stride\n"
       "\t-<x,y,w,h> : display area\n");

U_BOOT_CMD(stopvl, CFG_MAXARGS, 1, do_stopvl,
       "stopvl   - close video layer.\n"
       "\t- stopvl [layer]",
       "\nargs: [layer]\n"
       "\t-<layer> : 0(V0)\n");

U_BOOT_CMD(setvobg, CFG_MAXARGS, 1, do_vobg,
       "setvobg   - set vo backgroud color.\n"
       "\t- setvobg [dev color]",
       "\nargs: [dev, color]\n"
       "\t-<dev> : 0(HD0)\n"
       "\t-<color>: rgb color space\n");

U_BOOT_CMD(startgx, CFG_MAXARGS, 1, do_startgx,
       "startgx   - open graphics layer.\n"
       "\t- startgx [layer addr stride x y w h]\n",
       "\nargs: [layer, addr, stride, x, y, w, h]\n"
       "\t-<layer>   : 0(G0)\n"
       "\t-<addr>    : picture address\n"
       "\t-<stride>  : picture stride\n"
       "\t-<x,y,w,h> : display area\n");

U_BOOT_CMD(stopgx, CFG_MAXARGS, 1, do_stopgx,
       "stopgx   - close graphics layer.\n"
       "\t- stopgx [layer]",
       "\nargs: [layer]\n"
       "\t-<layer> : 0(G0)\n");
