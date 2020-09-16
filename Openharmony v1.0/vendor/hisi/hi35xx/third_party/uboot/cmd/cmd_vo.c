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
#include "hi_common_vo.h"
#include "vo.h"
#if CONFIG_HI_HDMI_SUPPORT
#include "hi_hdmi.h"
#endif

#define CFG_MAXARGS_SETVOBG 3
#define CFG_MAXARGS_STARTVO 4
#define CFG_MAXARGS_STOPVO 2
#define CFG_MAXARGS_STARTVL 8
#define CFG_MAXARGS_STOPVL 2
#define CFG_MAXARGS_STARTGX 9
#define CFG_MAXARGS_STOPGX 2
#define CMD_VO_ARGS_BASE10 10
#define CMD_VO_ARGS_BASE16 16
#define CMD_VO_ARGS_BASE_ALL 0
#define INSUFFICIENT_PARAM_STR "insufficient parameter or operation not permitted!\n"

#define VO_DEV_MAX_NUM 3

static unsigned int g_a_interface_type[VO_DEV_MAX_NUM] = { [0 ... (VO_DEV_MAX_NUM - 1)] = 0};

static unsigned int vo_get_interface_type(unsigned int dev)
{
    if (dev >= VO_DEV_MAX_NUM) {
        return 0;
    }
    return g_a_interface_type[dev];
}

static void vo_set_interface_type(unsigned int dev, unsigned int type)
{
    if (dev >= VO_DEV_MAX_NUM) {
        return;
    }
    g_a_interface_type[dev] = type;
}

static int vobg_parse(char *const argv[], unsigned int *dev, unsigned int *rgb)
{
    int ret;
    unsigned long dev_tmp, rgb_tmp;
    ret = strict_strtoul(argv[1], CMD_VO_ARGS_BASE10, &dev_tmp); /* 1st arg */
    if (ret != 0) {
        printf("parse dev failed.\n");
        return -1;
    }
    ret = strict_strtoul(argv[2], CMD_VO_ARGS_BASE_ALL, &rgb_tmp); /* 2nd arg */
    if (ret != 0) {
        printf("parse color failed.\n");
        return -1;
    }
    *dev = (unsigned int)dev_tmp;
    *rgb = (unsigned int)rgb_tmp;
    return 0;
}

static int do_vobg(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    int ret;
    unsigned int dev, rgb;

    if (argc < 3) { /* max 3 args */
        printf("insufficient parameter!\n");
        printf("usage:\n%s\n", cmdtp->usage);
        return -1;
    }
    ret = vobg_parse(argv, &dev, &rgb);
    if (ret != 0) {
        printf("insufficient parameter!\n");
        return -1;
    }
    ret = set_vobg(dev, rgb);
    if (ret != 0) {
        printf(INSUFFICIENT_PARAM_STR);
        return -1;
    }

    printf("dev %u set background color 0x%x!\n", dev, rgb);

    return 0;
}

static int startvo_parse(char *const argv[], unsigned int *dev, unsigned int *intftype, unsigned int *sync)
{
    int ret;
    unsigned long dev_tmp, intftype_tmp, sync_tmp;
    ret = strict_strtoul(argv[1], CMD_VO_ARGS_BASE10, &dev_tmp);  /* 1st arg */
    if (ret != 0) {
        printf("parse dev failed.\n");
        return -1;
    }
    ret = strict_strtoul(argv[2], CMD_VO_ARGS_BASE10, &intftype_tmp);  /* 2nd arg */
    if (ret != 0) {
        printf("parse intftype failed.\n");
        return -1;
    }
    ret = strict_strtoul(argv[3], CMD_VO_ARGS_BASE10, &sync_tmp);  /* 3rd arg */
    if (ret != 0) {
        printf("parse sync failed.\n");
        return -1;
    }
    *dev = (unsigned int)dev_tmp;
    *intftype = (unsigned int)intftype_tmp;
    *sync = (unsigned int)sync_tmp;
    return 0;
}

#if CONFIG_HI_HDMI_SUPPORT
static void do_start_hdmi(unsigned int intftype, unsigned int sync)
{
    if (intftype & HI_VO_INTF_HDMI) {
        if (intftype == (HI_VO_INTF_HDMI | HI_VO_INTF_MIPI)) {
            /* start hdmi */
            hdmi_display(sync, HI_HDMI_VIDEO_MODE_RGB444, HI_HDMI_VIDEO_MODE_YCBCR444);
        } else {
            /* start hdmi */
            hdmi_display(sync, HI_HDMI_VIDEO_MODE_YCBCR444, HI_HDMI_VIDEO_MODE_YCBCR444);
        }
    }
}
#endif

static int do_startvo(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    int ret;
    unsigned int dev, intftype, sync;

    if (argc < 4) { /* max 4 args */
        printf("insufficient parameter!\n");
        printf("usage:\n%s\n", cmdtp->usage);
        return -1;
    }
    ret = startvo_parse(argv, &dev, &intftype, &sync);
    if (ret != 0) {
        printf("insufficient parameter!\n");
        return -1;
    }

    ret = start_vo(dev, intftype, sync);
    if (ret != 0) {
        printf(INSUFFICIENT_PARAM_STR);
        return -1;
    }

#if CONFIG_HI_HDMI_SUPPORT
    do_start_hdmi(intftype, sync);
#endif

    vo_set_interface_type(dev, intftype);

    printf("dev %u opened!\n", dev);

    return 0;
}

static void do_stop_hdmi(unsigned int dev)
{
    if (vo_get_interface_type(dev) & HI_VO_INTF_HDMI) {
        /* stop hdmi */
#if CONFIG_HI_HDMI_SUPPORT
        hdmi_stop();
#endif
    }
}

static void do_stop_intf(unsigned int dev)
{
    do_stop_hdmi(dev);
    vo_set_interface_type(dev, 0);
}

static int stopvo_parse(char *const argv[], unsigned int *dev)
{
    int ret;
    unsigned long dev_tmp;
    ret = strict_strtoul(argv[1], CMD_VO_ARGS_BASE10, &dev_tmp);
    if (ret != 0) {
        printf("parse dev failed.\n");
        return -1;
    }
    *dev = (unsigned int)dev_tmp;
    return 0;
}

static int do_stopvo(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    int ret;
    unsigned int dev;
    if (argc < 2) { /* max 2 args */
        printf("insufficient parameter!\n");
        printf("usage:\n%s\n", cmdtp->usage);
        return -1;
    }
    ret = stopvo_parse(argv, &dev);
    if (ret != 0) {
        printf("insufficient parameter!\n");
        return -1;
    }

    /* step1: stop vo */
    ret = stop_vo(dev);
    if (ret != 0) {
        printf(INSUFFICIENT_PARAM_STR);
        return -1;
    }
    /* step2: stop intf */
    do_stop_intf(dev);

    printf("dev %u closed!\n", dev);

    return 0;
}

static int start_layer_parse(char *const argv[], unsigned int *layer,
    unsigned long *addr, unsigned int *strd, hi_rect *layer_rect)
{
    int ret;
    unsigned long layer_tmp, addr_tmp, strd_tmp, x_tmp, y_tmp, width_tmp, height_tmp;
    ret = strict_strtoul(argv[1], CMD_VO_ARGS_BASE10, &layer_tmp);  /* 1st arg */
    if (ret != 0) {
        printf("parse layer failed.\n");
        return -1;
    }
    ret = strict_strtoul(argv[2], CMD_VO_ARGS_BASE16, &addr_tmp);  /* 2nd arg */
    if (ret != 0) {
        printf("parse addr failed.\n");
        return -1;
    }
    ret = strict_strtoul(argv[3], CMD_VO_ARGS_BASE10, &strd_tmp);  /* 3rd arg */
    if (ret != 0) {
        printf("parse strd failed.\n");
        return -1;
    }
    ret = strict_strtoul(argv[4], CMD_VO_ARGS_BASE10, &x_tmp);  /* 4th arg */
    if (ret != 0) {
        printf("parse x failed.\n");
        return -1;
    }
    ret = strict_strtoul(argv[5], CMD_VO_ARGS_BASE10, &y_tmp);  /* 5th arg */
    if (ret != 0) {
        printf("parse y failed.\n");
        return -1;
    }
    ret = strict_strtoul(argv[6], CMD_VO_ARGS_BASE10, &width_tmp);  /* 6th arg */
    if (ret != 0) {
        printf("parse width failed.\n");
        return -1;
    }
    ret = strict_strtoul(argv[7], CMD_VO_ARGS_BASE10, &height_tmp);  /* 7th arg */
    if (ret != 0) {
        printf("parse height failed.\n");
        return -1;
    }
    *layer = (unsigned int)layer_tmp;
    *addr = addr_tmp;
    *strd = (unsigned int)strd_tmp;
    layer_rect->x = (unsigned int)x_tmp;
    layer_rect->y = (unsigned int)y_tmp;
    layer_rect->width = (unsigned int)width_tmp;
    layer_rect->height = (unsigned int)height_tmp;
    return 0;
}

static int start_gx_type_parse(char *const argv[], unsigned int *type)
{
    int ret;
    unsigned long type_tmp;
    ret = strict_strtoul(argv[8], CMD_VO_ARGS_BASE10, &type_tmp);  /* 8th arg */
    if (ret != 0) {
        printf("parse type failed.\n");
        return -1;
    }
    *type = (unsigned int)type_tmp;
    return 0;
}

static int do_startgx(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    int ret;
    unsigned int layer, strd, type;
    unsigned long addr;
    hi_rect gx_rect;
    if (argc < 9) { /* max 9 args */
        printf("insufficient parameter!\n");
        printf("usage:\n%s\n", cmdtp->usage);
        return -1;
    }
    ret = start_layer_parse(argv, &layer, &addr, &strd, &gx_rect);
    if (ret != 0) {
        printf("insufficient parameter!\n");
        return -1;
    }

    ret = start_gx_type_parse(argv, &type);
    if (ret != 0) {
        printf("insufficient parameter!\n");
        return -1;
    }

    ret = start_gx(layer, addr, strd, gx_rect, type);
    if (ret != 0) {
        printf(INSUFFICIENT_PARAM_STR);
        return -1;
    }

    printf("graphic layer %u opened!\n", layer);

    return 0;
}

static int stopgx_parse(char *const argv[], unsigned int *layer)
{
    int ret;
    unsigned long layer_tmp;
    ret = strict_strtoul(argv[1], CMD_VO_ARGS_BASE10, &layer_tmp);  /* 1st arg */
    if (ret != 0) {
        printf("parse layer failed.\n");
        return -1;
    }
    *layer = (unsigned int)layer_tmp;
    return 0;
}

static int do_stopgx(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    int ret;
    unsigned int layer;

    if (argc < 2) { /* max 2 args */
        printf("insufficient parameter!\n");
        printf("usage:\n%s\n", cmdtp->usage);
        return -1;
    }

    ret = stopgx_parse(argv, &layer);
    if (ret != 0) {
        printf("insufficient parameter!\n");
        return -1;
    }

    ret = stop_gx(layer);
    if (ret != 0) {
        printf(INSUFFICIENT_PARAM_STR);
        return -1;
    }

    printf("graphic layer %u closed!\n", layer);

    return 0;
}

static int do_startvl(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    int ret;
    unsigned int layer, strd;
    unsigned long addr;
    hi_rect layer_rect;

    if (argc < 8) { /* max 8 args */
        printf("insufficient parameter!\n");
        printf("usage:\n%s\n", cmdtp->usage);
        return -1;
    }

    ret = start_layer_parse(argv, &layer, &addr, &strd, &layer_rect);
    if (ret != 0) {
        printf("insufficient parameter!\n");
        return -1;
    }

    ret = start_videolayer(layer, addr, strd, layer_rect);
    if (ret != 0) {
        printf(INSUFFICIENT_PARAM_STR);
        return -1;
    }

    printf("video layer %u opened!\n", layer);

    return 0;
}

static int stopvl_parse(char *const argv[], unsigned int *layer)
{
    int ret;
    unsigned long layer_tmp;
    ret = strict_strtoul(argv[1], CMD_VO_ARGS_BASE10, &layer_tmp);  /* 1st arg */
    if (ret != 0) {
        printf("parse layer failed.\n");
        return -1;
    }
    *layer = (unsigned int)layer_tmp;
    return 0;
}

static int do_stopvl(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    int ret;
    unsigned int layer;

    if (argc < 2) { /* max 2 args */
        printf("insufficient parameter!\n");
        printf("usage:\n%s\n", cmdtp->usage);
        return -1;
    }
    ret = stopvl_parse(argv, &layer);
    if (ret != 0) {
        printf("insufficient parameter!\n");
        return -1;
    }

    ret = stop_videolayer(layer);
    if (ret != 0) {
        printf(INSUFFICIENT_PARAM_STR);
        return -1;
    }

    printf("video layer %u closed!\n", layer);

    return 0;
}

#if ((defined(CHIP_HI3531DV200)) || (defined(CHIP_HI3535AV100)))
#define USAGE_DEV_STRING                                                           \
    "\t-<dev> : 0: DHD0,1: DHD1,2: DSD0\n"

#define USAGE_INTF_STRING                                                          \
    "\t-<intftype>: 1(CVBS),2(VGA),8(BT.1120),16(HDMI)\n"                           \

#define USAGE_GX_STRING                           \
    "\t-<layer>   : 4(G0), 5(G1), 7(G3)\n"

#define USAGE_VL_STRING                           \
    "\t-<layer>   : 0(V0), 1(V1), 3(V3)\n"

#elif (defined(CHIP_HI3521DV200))

#define USAGE_DEV_STRING                                                           \
    "\t-<dev> : 0: DHD0,1: DHD1,2: DSD0\n"

#define USAGE_INTF_STRING                                                          \
    "\t-<intftype>: 1(CVBS),2(VGA),4(BT.656),8(BT.1120),16(HDMI)\n"                  \

#define USAGE_GX_STRING                           \
    "\t-<layer>   : 4(G0), 5(G1), 7(G3)\n"

#define USAGE_VL_STRING                           \
    "\t-<layer>   : 0(V0), 1(V1), 3(V3)\n"

#elif (defined(CHIP_HI3520DV500))

#define USAGE_DEV_STRING                                                           \
    "\t-<dev> : 0: DHD0,2: DSD0\n"

#define USAGE_INTF_STRING                                                          \
    "\t-<intftype>: 1(CVBS),2(VGA),4(BT.656),8(BT.1120),16(HDMI)\n"                  \
    "\t\t128(RGB_16BIT),256(RGB_18BIT),512(RGB_24BIT)\n"

#define USAGE_GX_STRING                           \
    "\t-<layer>   : 4(G0), 7(G3)\n"

#define USAGE_VL_STRING                           \
    "\t-<layer>   : 0(V0), 3(V3)\n"

#else

#define USAGE_DEV_STRING                          \
    "\t-<dev> : 0: DHD0,1: DHD1,2: DSD0\n"

#define USAGE_INTF_STRING                                                          \
    "\t-<intftype>: 1(CVBS),2(VGA),8(BT.1120),16(HDMI)\n"                           \
    "\t\t32(RGB_6BIT),64(RGB_8BIT),128(RGB_16BIT),256(RGB_18BIT),512(RGB_24BIT)\n"

#define USAGE_GX_STRING                            \
    "\t-<layer>   : 4(G0), 5(G1), 7(G3)\n"

#define USAGE_VL_STRING                            \
    "\t-<layer>   : 0(V0), 1(V1), 3(V3)\n"

#endif

#define USAGE_GX_TYPE                              \
    "\t-<type>    : 0(argb1555), 1(bmp1555)\n"

#define USAGE_START_VO                                                             \
    "\nargs: [dev, intftype, sync]\n"                                              \
    USAGE_DEV_STRING                                                               \
    USAGE_INTF_STRING                                                              \
    "\t-<sync>:\n"                                                                 \
    "\t\t0(PAL),          1(NTSC),         2(960H_PAL),     3(960H_NTSC)\n"        \
    "\t\t4(640x480_60),   5(480P60),       6(576P50),       7(800x600_60)\n"       \
    "\t\t8(1024x768_60),  9(720P50),       10(720P60),      11(1280x800_60)\n"     \
    "\t\t12(1280x1024_60),13(1366x768_60), 14(1400x1050_60),15(1440x900_60)\n"     \
    "\t\t16(1600x1200_60),17(1680x1050_60),18(1080P24),     19(1080P25)\n"         \
    "\t\t20(1080P30),     21(1080I50),     22(1080I60),     23(1080P50)\n"         \
    "\t\t24(1080P60),     25(1920x1200_60),26(1920x2160_30),27(2560x1440_30)\n"    \
    "\t\t28(2560x1440_60),29(2560x1600_60),30(3840x2160_24),31(3840x2160_25)\n"    \
    "\t\t32(3840x2160_30),33(3840x2160_50),34(3840x2160_60),35(4096x2160_24)\n"    \
    "\t\t36(4096x2160_25),37(4096x2160_30),38(4096x2160_50),39(4096x2160_60)\n"    \
    "\t\t40(7680x4320_30),41(240x320_50),  42(320x240_50),  43(240x320_60)\n"      \
    "\t\t44(320x240_60),  45(800x600_50),  46(720x1280_60), 47(1080x1920_60)\n"    \
    "\t\t48(user)\n"

#define USAGE_STOP_VO                             \
    "\nargs: [dev]\n"                             \
    USAGE_DEV_STRING

#define USAGE_START_GX                            \
    "\nargs: [layer, addr, stride, x, y, w, h, type]\n" \
    USAGE_GX_STRING                               \
    "\t-<addr>    : picture address\n"            \
    "\t-<stride>  : picture stride\n"             \
    "\t-<x,y,w,h> : display area\n"               \
    USAGE_GX_TYPE

#define USAGE_STOP_GX                             \
    "\nargs: [layer]\n"                           \
    USAGE_GX_STRING

#define USAGE_START_VL                            \
    "\nargs: [layer, addr, stride, x, y, w, h]\n" \
    USAGE_VL_STRING                               \
    "\t-<addr>    : picture address\n"            \
    "\t-<stride>  : picture stride\n"             \
    "\t-<x,y,w,h> : display area\n"

#define USAGE_STOP_VL                             \
   "\nargs: [layer]\n"                            \
    USAGE_VL_STRING

#define USAGE_SET_VO_BG                           \
   "\nargs: [dev, color]\n"                       \
    USAGE_DEV_STRING                              \
   "\t-<color>: rgb color space\n"

U_BOOT_CMD(startvo, CFG_MAXARGS_STARTVO, 1, do_startvo,
           "startvo   - open vo device with a certain output interface.\n"
           "\t- startvo [dev intftype sync]", USAGE_START_VO);

U_BOOT_CMD(stopvo, CFG_MAXARGS_STOPVO, 1, do_stopvo,
           "stopvo   - close interface of vo device.\n"
           "\t- stopvo [dev]", USAGE_STOP_VO);

U_BOOT_CMD(startgx, CFG_MAXARGS_STARTGX, 1, do_startgx,
           "startgx   - open graphics layer.\n"
           "\t- startgx [layer addr stride x y w h type]", USAGE_START_GX);

U_BOOT_CMD(stopgx, CFG_MAXARGS_STOPGX, 1, do_stopgx,
           "stopgx   - close graphics layer.\n"
           "\t- stopgx [layer]", USAGE_STOP_GX);

U_BOOT_CMD(startvl, CFG_MAXARGS_STARTVL, 1, do_startvl,
           "startvl   - open video layer.\n"
           "\t- startvl [layer addr stride x y w h]", USAGE_START_VL);

U_BOOT_CMD(stopvl, CFG_MAXARGS_STOPVL, 1, do_stopvl,
           "stopvl   - close video layer.\n"
           "\t- stopvl [layer]", USAGE_STOP_VL);

U_BOOT_CMD(setvobg, CFG_MAXARGS_SETVOBG, 1, do_vobg,
           "setvobg   - set vo backgroud color.\n"
           "\t- setvobg [dev color]", USAGE_SET_VO_BG);
