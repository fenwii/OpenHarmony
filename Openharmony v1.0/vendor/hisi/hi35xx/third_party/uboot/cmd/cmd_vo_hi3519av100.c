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
#include "hi3519av100_vo.h"

#define CMD_VO_ARGS_BASE10 10
#define CMD_VO_ARGS_BASE16 16
#define CMD_VO_ARGS_BASE_ALL 0

extern int set_vobg(unsigned int dev, unsigned int rgb);
extern int start_vo(unsigned int dev, unsigned int type, unsigned int sync);
extern int stop_vo(unsigned int dev);
extern int start_videolayer(unsigned int layer, unsigned long addr, unsigned int strd, hi_vo_rect layer_rect);
extern int stop_videolayer(unsigned int layer);

extern int hdmi_display(unsigned int vosync, unsigned int input, unsigned int output);
extern void hdmi_stop(void);

extern int mipi_tx_display(unsigned int vosync);
extern int mipi_tx_stop(void);

extern int start_gx(unsigned int layer, unsigned long addr, unsigned int strd, hi_vo_rect gx_rect);
extern int stop_gx(unsigned int layer);

#define VO_DEV_MAX_NUM         3
static unsigned int g_a_interface_type[VO_DEV_MAX_NUM] = {[0 ... (VO_DEV_MAX_NUM - 1)] = 0};

static int check_vo_support(unsigned int dev, unsigned int type, unsigned int sync)
{
    /* check interface type, ONLY VGA & HDMI interface is supported. */
    if (dev == VO_DEV_DHD0) {
        if ((type & ~(VO_INTF_HDMI | VO_INTF_BT1120 | VO_INTF_BT656 | VO_INTF_MIPI | VO_INTF_MIPI_SLAVE)) ||
            (type == 0)) {
            printf("hd%u only supports HDMI, BT.656, BT.1120, mipi_tx intftype, intf %u is illegal!\n", dev, type);
            return -1;
        }
        /* just one interface at the the time for a dev. */
        if (type & ~(VO_INTF_HDMI | VO_INTF_BT1120) &&
            (type & ~(VO_INTF_HDMI | VO_INTF_MIPI)) &&
            (type & ~VO_INTF_BT656) &&
            (type & ~VO_INTF_MIPI_SLAVE)) {
            printf("for VO %u, only HDMI and BT.1120 can be used at the same time!\n", dev);
            return -1;
        }
    } else if (dev == VO_DEV_DHD1) {
        if ((type
             & ~(VO_INTF_BT1120 | VO_INTF_BT656 | VO_INTF_MIPI |
             VO_INTF_MIPI_SLAVE | VO_INTF_LCD_6BIT | VO_INTF_LCD_8BIT |
             VO_INTF_LCD_16BIT | VO_INTF_LCD_18BIT | VO_INTF_LCD_24BIT)) ||
            (type == 0)) {
            printf("hd%u only supports BT.656, BT.1120, mipi_tx, LCD intftype, intf %u is illegal!\n", dev, type);
            return -1;
        }
        /* just one interface at the the time for a dev. */
        if (
            (type & ~VO_INTF_BT1120) && (type & ~VO_INTF_BT656) &&
            (type & ~VO_INTF_MIPI) && (type & ~VO_INTF_MIPI_SLAVE) &&
            (type & ~VO_INTF_LCD_6BIT) && (type & ~VO_INTF_LCD_8BIT) &&
            (type & ~VO_INTF_LCD_16BIT) && (type & ~VO_INTF_LCD_18BIT) &&
            (type & ~VO_INTF_LCD_24BIT)
        ) {
            printf("vo(%u), none of (BT.1120,BT.656,MIPI,LCD) can use at the same time!\n", dev);
            return -1;
        }
    } else {
        printf("unknow dev(%u)!\n", dev);
        return -1;
    }

    if (VO_INTF_HDMI & type) {
        if (!(((sync >= VO_OUTPUT_1080P24) && (sync <= VO_OUTPUT_640x480_60))  ||
              ((sync >= VO_OUTPUT_1920x2160_30) && (sync <= VO_OUTPUT_4096x2160_60)))) {
            printf("vo%u's intfsync %u illegal!\n", dev, sync);
            return -1;
        }
    }

    if (VO_INTF_BT1120 & type) {
        if ((sync < VO_OUTPUT_1080P24) ||
            (sync > VO_OUTPUT_7680x4320_30)) {
            printf("vo%u's intfsync %u illegal!\n", dev, sync);
            return -1;
        }
    }

    if ((VO_INTF_MIPI & type) || (VO_INTF_MIPI_SLAVE & type)) {
        if (dev == VO_DEV_DHD0) {
            if ((sync != VO_OUTPUT_576P50) &&
                (sync != VO_OUTPUT_720P50) &&
                (sync != VO_OUTPUT_720P60) &&
                (sync != VO_OUTPUT_1024x768_60) &&
                (sync != VO_OUTPUT_1280x1024_60) &&
                (sync != VO_OUTPUT_720x1280_60) &&
                (sync != VO_OUTPUT_1080x1920_60) &&
                (sync != VO_OUTPUT_1080P60) &&
                (sync != VO_OUTPUT_3840x2160_30) &&
                (sync != VO_OUTPUT_3840x2160_60)) {
                printf("for MIPI(mipi_tx) intface, vo%u's intfsync %u illegal!\n", dev, sync);
                return -1;
            }
        } else if (dev == VO_DEV_DHD1) {
            if ((sync != VO_OUTPUT_576P50) &&
                (sync != VO_OUTPUT_720P50) &&
                (sync != VO_OUTPUT_720P60) &&
                (sync != VO_OUTPUT_1024x768_60) &&
                (sync != VO_OUTPUT_1280x1024_60) &&
                (sync != VO_OUTPUT_720x1280_60) &&
                (sync != VO_OUTPUT_1080x1920_60) &&
                (sync != VO_OUTPUT_1080P60)) {
                printf("for MIPI(mipi_tx) intface, vo%u's intfsync %u illegal! \n", dev, sync);
                return -1;
            }
        }
    }

    if (type == (VO_INTF_HDMI | VO_INTF_MIPI)) {
        if ((sync == VO_OUTPUT_576P50) ||
            (sync == VO_OUTPUT_1024x768_60)) {
            printf("when HDMI+MIPI, not support 576P50 or 1024x768_60\n");
            return -1;
        }
    }

    return 0;
}

static int do_vobg(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    unsigned int dev, rgb;

    if (argc < 3) {
        printf("insufficient parameter!\n");
        printf ("usage:\n%s\n", cmdtp->usage);
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

static int do_startvo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    unsigned int dev, intftype, sync;

    if (argc < 4) {
        printf("insufficient parameter!\n");
        printf ("usage:\n%s\n", cmdtp->usage);
        return -1;
    }

    dev      = (unsigned int)simple_strtoul(argv[1], NULL, CMD_VO_ARGS_BASE10);
    intftype = (unsigned int)simple_strtoul(argv[2], NULL, CMD_VO_ARGS_BASE10);
    sync     = (unsigned int)simple_strtoul(argv[3], NULL, CMD_VO_ARGS_BASE10);
    if ((dev >= VO_DEV_BUTT) || (sync >= VO_OUTPUT_BUTT)) {
        printf("invalid parameter!\n");
        return -1;
    }

    if (check_vo_support(dev, intftype, sync)) {
        printf("unsupport parameter!\n");
        return -1;
    }

    start_vo(dev, intftype, sync);

    g_a_interface_type[dev] =  intftype;

    if (intftype & VO_INTF_HDMI) {
        if (intftype == (VO_INTF_HDMI | VO_INTF_MIPI)) {
            hdmi_display(sync, 0, 2);
        } else {
            hdmi_display(sync, 2, 2);
        }
    }

    if (intftype & VO_INTF_MIPI) {
        /* to call mipi_display. */
        mipi_tx_display(sync);
    }

    printf("dev %u opened!\n", dev);

    return 0;
}

static int do_stopvo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    unsigned int dev;
    if (argc < 2) {
        printf("insufficient parameter!\n");
        printf ("usage:\n%s\n", cmdtp->usage);
        return -1;
    }

    dev = (unsigned int)simple_strtoul(argv[1], NULL, CMD_VO_ARGS_BASE10);
    if (dev >= VO_DEV_BUTT) {
        printf("invalid parameter!\n");
        return -1;
    }

    if (g_a_interface_type[dev] & VO_INTF_HDMI) {
        g_a_interface_type[dev] = 0;
        hdmi_stop();
    }

    if (g_a_interface_type[dev] & VO_INTF_MIPI) {
        mipi_tx_stop();
    }

    stop_vo(dev);

    printf("dev %u closed!\n", dev);

    return 0;
}

static int do_startvl(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    unsigned int layer, strd, x, y, w, h;
    unsigned long addr;
    hi_vo_rect layer_rect;
    int max_x, max_y, layer_max_w, layer_max_h;

    if (argc < 8) {
        printf("insufficient parameter!\n");
        printf ("usage:\n%s\n", cmdtp->usage);
        return -1;
    }

    layer = (unsigned int)simple_strtoul(argv[1], NULL, CMD_VO_ARGS_BASE10);
    addr  = (unsigned long)simple_strtoul(argv[2], NULL, CMD_VO_ARGS_BASE16);
    strd  = (unsigned int)simple_strtoul(argv[3], NULL, CMD_VO_ARGS_BASE10);
    x     = (unsigned int)simple_strtoul(argv[4], NULL, CMD_VO_ARGS_BASE10);
    y     = (unsigned int)simple_strtoul(argv[5], NULL, CMD_VO_ARGS_BASE10);
    w     = (unsigned int)simple_strtoul(argv[6], NULL, CMD_VO_ARGS_BASE10);
    h     = (unsigned int)simple_strtoul(argv[7], NULL, CMD_VO_ARGS_BASE10);

    if (layer == VO_LAYER_VHD0) {
        max_x = VHD0_PIC_MAX_WIDTH;
        max_y = VHD0_PIC_MAX_HEIGHT;
        layer_max_w = VHD0_PIC_MAX_WIDTH;
        layer_max_h = VHD0_PIC_MAX_HEIGHT;
    } else if (layer == VO_LAYER_VHD1) {
        max_x =VHD1_PIC_MAX_WIDTH;
        max_y = VHD1_PIC_MAX_HEIGHT;
        layer_max_w = VHD1_PIC_MAX_WIDTH;
        layer_max_h = VHD1_PIC_MAX_HEIGHT;
    } else {
        printf("invalid parameter!\n");
        return -1;
    }

    if((strd > (layer_max_w * 2)) ||
        (x > max_x) || (x & 0x1) ||
        (y > max_y) || (y & 0x1) ||
        (w > layer_max_w) || (w & 0x1) || (w < PIC_MIN_LENTH) ||
        (h > layer_max_h) || (h & 0x1) || (h < PIC_MIN_LENTH)) {
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

static int do_stopvl(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    unsigned int layer;

    if (argc < 2) {
        printf("insufficient parameter!\n");
        printf ("usage:\n%s\n", cmdtp->usage);
        return -1;
    }

    layer = (unsigned int)simple_strtoul(argv[1], NULL, CMD_VO_ARGS_BASE10);

    if ((layer > VO_LAYER_VSD0) || (layer == VO_LAYER_VP)) {
        printf("invalid parameter!\n");
        return -1;
    }

    stop_videolayer(layer);

    printf("video layer %u closed!\n", layer);

    return 0;
}

static int do_startgx(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    unsigned int layer, strd, x, y, w, h;
    unsigned long addr;
    hi_vo_rect gx_rect;
    int max_x, max_y, layer_max_w, layer_max_h;
    if (argc < 8) {
        printf("insufficient parameter!\n");
        printf ("usage:\n%s\n", cmdtp->usage);
        return -1;
    }

    layer = (unsigned int)simple_strtoul(argv[1], NULL, CMD_VO_ARGS_BASE10);
    addr  = (unsigned long)simple_strtoul(argv[2], NULL, CMD_VO_ARGS_BASE16);
    strd  = (unsigned int)simple_strtoul(argv[3], NULL, CMD_VO_ARGS_BASE10);
    x     = (unsigned int)simple_strtoul(argv[4], NULL, CMD_VO_ARGS_BASE10);
    y     = (unsigned int)simple_strtoul(argv[5], NULL, CMD_VO_ARGS_BASE10);
    w     = (unsigned int)simple_strtoul(argv[6], NULL, CMD_VO_ARGS_BASE10);
    h     = (unsigned int)simple_strtoul(argv[7], NULL, CMD_VO_ARGS_BASE10);

    if (layer == VO_GRAPHC_G0) {
        max_x =GFX0_PIC_MAX_WIDTH;
        max_y = GFX0_PIC_MAX_HEIGHT;
        layer_max_w = GFX0_PIC_MAX_WIDTH;
        layer_max_h = GFX0_PIC_MAX_HEIGHT;
    } else if (layer == VO_GRAPHC_G1) {
        max_x =GFX1_PIC_MAX_WIDTH;
        max_y = GFX1_PIC_MAX_HEIGHT;
        layer_max_w = GFX1_PIC_MAX_WIDTH;
        layer_max_h = GFX1_PIC_MAX_HEIGHT;
    } else {
        printf("invalid parameter!\n");
        return -1;
    }

    if((strd > (layer_max_w * 2)) ||
        (x > max_x) || (x & 0x1) ||
        (y > max_y) || (y & 0x1) ||
        (w > layer_max_w) || (w & 0x1) || (w < PIC_MIN_LENTH) ||
        (h > layer_max_h) || (h & 0x1) || (h < PIC_MIN_LENTH)) {
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

static int do_stopgx(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    unsigned int layer;

    if (argc < 2) {
        printf("insufficient parameter!\n");
        printf ("usage:\n%s\n", cmdtp->usage);
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

U_BOOT_CMD(
    startvo,    CFG_MAXARGS,    1,  do_startvo,
    "startvo   - open vo device with a certain output interface.\n"
    "\t- startvo [dev intftype sync]",
    "\nargs: [dev, intftype, sync]\n"
    "\t-<dev> : 0: DHD0,1: DHD1\n"
    "\t-<intftype>: 8(BT.656),16(BT.1120),32(HDMI),16384(mipi_tx)\n"
    "\t-<sync>: typical value:\n"
    "\t\t0(PAL),          1(NTSC),         4(1080P30),      6(720P60)\n"
    "\t\t10(1080P60),     21(1920x1200),   26(2560x1440_30),31(3840x2160_30)\n"
    "\t\t33(3840x2160_60),45(1080x1920_60),47(user)\n");

U_BOOT_CMD(
    stopvo,    CFG_MAXARGS,    1,  do_stopvo,
    "stopvo   - close interface of vo device.\n"
    "\t- stopvo [dev]",
    "\nargs: [dev]\n"
    "\t-<dev> : 0~1(HD0~HD1)\n");

U_BOOT_CMD(
    startvl,    CFG_MAXARGS,    1,  do_startvl,
    "startvl   - open video layer.\n"
    "\t- startvl [layer addr stride x y w h]\n",
    "\nargs: [layer, addr, stride, x, y, w, h]\n"
    "\t-<layer>   : 0(V0), 1(V1)\n"
    "\t-<addr>    : picture address\n"
    "\t-<stride>  : picture stride\n"
    "\t-<x,y,w,h> : display area\n");

U_BOOT_CMD(
    stopvl,    CFG_MAXARGS,    1,  do_stopvl,
    "stopvl   - close video layer.\n"
    "\t- stopvl [layer]",
    "\nargs: [layer]\n"
    "\t-<layer> : 0(V0), 1(V1)\n");

U_BOOT_CMD(
    setvobg,    CFG_MAXARGS,    1,  do_vobg,
    "setvobg   - set vo backgroud color.\n"
    "\t- setvobg [dev color]",
    "\nargs: [dev, color]\n"
    "\t-<dev> : 0~1(HD0~1)\n"
    "\t-<color>: rgb color space\n");

U_BOOT_CMD(
    startgx,    CFG_MAXARGS,    1,  do_startgx,
    "startgx   - open graphics layer.\n"
    "\t- startgx [layer addr stride x y w h]\n",
    "\nargs: [layer, addr, stride, x, y, w, h]\n"
    "\t-<layer>   : 0(G0), 1(G1)\n"
    "\t-<addr>    : picture address\n"
    "\t-<stride>  : picture stride\n"
    "\t-<x,y,w,h> : display area\n");

U_BOOT_CMD(
    stopgx,    CFG_MAXARGS,    1,  do_stopgx,
    "stopgx   - close graphics layer.\n"
    "\t- stopgx [layer]",
    "\nargs: [layer]\n"
    "\t-<layer> : 0(G0), 1(G1)\n");
