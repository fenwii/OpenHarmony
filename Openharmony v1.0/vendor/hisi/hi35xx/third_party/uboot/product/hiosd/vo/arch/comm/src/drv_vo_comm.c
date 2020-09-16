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

#include "drv_vo_comm.h"
#include "drv_vo.h"
#include "hal_vo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#if VO_DESC("UBOOT")
#if VO_DESC("pub")

hal_disp_syncinfo g_sync_timing[HI_VO_OUT_BUTT] = {
    /*
     * |--INTFACE---||-----TOP-----||----HORIZON--------||----BOTTOM-----||-PULSE-||-INVERSE-|
     * syncm, iop, itf,   vact, vbb,  vfb,  hact,  hbb,  hfb, hmid,bvact,bvbb, bvfb, hpw, vpw,idv, ihs, ivs
     */
    { 0, 0, 0, 288, 22, 2, 720, 132, 12, 1, 288, 23, 2, 126, 3, 0, 0, 0 }, /* 576I(PAL)  */
    { 0, 0, 0, 240, 18, 4, 720, 119, 19, 1, 240, 19, 4, 124, 3, 0, 0, 0 }, /* 480I(NTSC) */
    { 0, 0, 0, 288, 22, 2, 960, 176, 16, 1, 288, 23, 2, 168, 3, 0, 0, 0 }, /* 960H(PAL) */
    { 0, 0, 0, 240, 18, 4, 960, 163, 21, 1, 240, 19, 4, 168, 3, 0, 0, 0 }, /* 960H(NTSC) */

    { 1, 1, 2, 480,  35, 10, 640,  144, 16,  1, 1, 1, 1, 96,  2, 0, 1, 1 }, /* 640*480@60_hz CVT */
    { 1, 1, 1, 480, 36, 9, 720, 122, 16, 1, 1, 1, 1, 62, 6, 0, 0, 0 }, /* 480P@60_hz */
    { 1, 1, 1, 576, 44, 5, 720, 132, 12, 1, 1, 1, 1, 64, 5, 0, 0, 0 }, /* 576P@50_hz */
    { 1, 1, 2, 600,  27, 1,  800,  216, 40,  1, 1, 1, 1, 128, 4, 0, 0, 0 }, /* 800*600@60_hz VGA@60_hz */
    { 1, 1, 2, 768,  35, 3,  1024, 296, 24,  1, 1, 1, 1, 136, 6, 0, 1, 1 }, /* 1024x768@60_hz */
    { 0, 1, 1, 720,  25, 5, 1280, 260, 440, 1, 1,   1,  1, 40, 5, 0, 0, 0 }, /* 720P@50_hz */
    { 0, 1, 1, 720,  25, 5, 1280, 260, 110, 1, 1,   1,  1, 40, 5, 0, 0, 0 }, /* 720P@60_hz */
    { 1, 1, 2, 800,  28, 3,  1280, 328, 72,  1, 1, 1, 1, 128, 6, 0, 1, 0 }, /* 1280*800@60_hz VGA@60_hz */
    { 1, 1, 2, 1024, 41, 1,  1280, 360, 48,  1, 1, 1, 1, 112, 3, 0, 0, 0 }, /* 1280x1024@60_hz */
    { 1, 1, 2, 768,  27, 3,  1366, 356, 70,  1, 1, 1, 1, 143, 3, 0, 0, 0 }, /* 1366x768@60_hz */
    { 1, 1, 2, 1050, 36, 3,  1400, 376, 88,  1, 1, 1, 1, 144, 4, 0, 0, 0 }, /* 1400x1050@60_hz */
    { 1, 1, 2, 900,  31, 3,  1440, 384, 80,  1, 1, 1, 1, 152, 6, 0, 1, 0 }, /* 1440x900@60_hz */
    { 1, 1, 2, 1200, 49, 1,  1600, 496, 64,  1, 1, 1, 1, 192, 3, 0, 0, 0 }, /* 1600*1200@60_hz */
    { 1, 1, 2, 1050, 36, 3,  1680, 456, 104, 1, 1, 1, 1, 176, 6, 0, 1, 0 }, /* 1680*1050@60_hz */

    { 0, 1, 1, 1080, 41, 4, 1920, 192, 638, 1, 1, 1, 1, 44, 5, 0, 0, 0 }, /* 1080P@24_hz */
    { 0, 1, 1, 1080, 41, 4, 1920, 192, 528, 1, 1, 1, 1, 44, 5, 0, 0, 0 }, /* 1080P@25_hz */
    { 0, 1, 1, 1080, 41, 4, 1920, 192, 88,  1, 1, 1, 1, 44, 5, 0, 0, 0 }, /* 1080P@30_hz */
    { 0, 0, 1, 540,  20, 2, 1920, 192, 528, 1128, 540, 21, 2, 44, 5, 0, 0, 0 }, /* 1080I@50_hz */
    { 0, 0, 1, 540,  20, 2, 1920, 192, 88,  908,  540, 21, 2, 44, 5, 0, 0, 0 }, /* 1080I@60_hz */
    { 0, 1, 1, 1080, 41, 4, 1920, 192, 528, 1,    1,   1,  1, 44, 5, 0, 0, 0 }, /* 1080P@50_hz */
    { 0, 1, 1, 1080, 41, 4, 1920, 192, 88,  1,    1,   1,  1, 44, 5, 0, 0, 0 }, /* 1080P@60_hz */

    { 1, 1, 2, 1200, 32, 3,  1920, 112, 48,  1, 1, 1, 1, 32,  6, 0, 0, 1 }, /* 1920*1200@60_hz CVT (reduced blanking) */
    { 0, 1, 1, 2160, 72, 8, 1920, 192, 88,   1, 1, 1, 1, 44, 5,  0, 0, 0 }, /* 1920*2160@30_hz */
    { 1, 1, 2, 1440, 39, 2, 2560, 112, 48,   1, 1, 1, 1, 32, 5,  0, 0, 0 }, /* 2560*1440@30_hz */
    { 1, 1, 2, 1440, 39, 2, 2560, 112, 48,   1, 1, 1, 1, 32, 5,  0, 0, 0 }, /* 2560*1440@60_hz */
    { 0, 1, 2, 1600, 43, 3, 2560, 112, 48,   1, 1, 1, 1, 32, 6,  0, 0, 1 }, /* 2560*1600@60_hz CVT (reduced blanking) */
    { 0, 1, 1, 2160, 82, 8, 3840, 384, 1276, 1, 1, 1, 1, 88, 10, 0, 0, 0 }, /* 3840*2160@24_hz */
    { 0, 1, 1, 2160, 82, 8, 3840, 384, 1056, 1, 1, 1, 1, 88, 10, 0, 0, 0 }, /* 3840*2160@25_hz */
    { 0, 1, 1, 2160, 82, 8, 3840, 384, 176,  1, 1, 1, 1, 88, 10, 0, 0, 0 }, /* 3840*2160@30_hz */
    { 0, 1, 1, 2160, 82, 8, 3840, 384, 1056, 1, 1, 1, 1, 88, 10, 0, 0, 0 }, /* 3840*2160@50_hz */
    { 0, 1, 1, 2160, 82, 8, 3840, 384, 176,  1, 1, 1, 1, 88, 10, 0, 0, 0 }, /* 3840*2160@60_hz */

    { 0,  1, 1, 2160, 82, 8,  4096, 384, 1020, 1, 1,   1,  1, 88, 10, 0, 0, 0 }, /* 4096x2160@24 */
    { 0,  1, 1, 2160, 82, 8,  4096, 216, 968,  1, 1,   1,  1, 88, 10, 0, 0, 0 }, /* 4096x2160@25 */
    { 0,  1, 1, 2160, 82, 8,  4096, 216, 88,   1, 1,   1,  1, 88, 10, 0, 0, 0 }, /* 4096x2160@30 */
    { 0,  1, 1, 2160, 82, 8,  4096, 216, 968,  1, 1,   1,  1, 88, 10, 0, 0, 0 }, /* 4096x2160@50 */
    { 0,  1, 1, 2160, 82, 8,  4096, 216, 88,   1, 1,   1,  1, 88, 10, 0, 0, 0 }, /* 4096x2160@60 */
    { 0,  1, 1, 4320, 64,  16, 7680, 768, 552, 1, 1, 1, 1, 176, 20, 0, 0, 0 }, /* 7680x4320@30 */

    { 0,  1, 1, 320,  10, 4,  240,  30,  10,   1, 1,   1,  1, 10, 2,  0, 0, 0 }, /* 240X320@50  6bit LCD */
    { 0,  1, 1, 240,  2,  2,  320,  5,   10,   1, 1,   1,  1, 10, 1,  0, 0, 0 }, /* 320X240@50  6bit LCD */
    { 0,  1, 1, 320,  4,  8,  240,  20,  10,   1, 1,   1,  1, 2,  2,  0, 0, 0 }, /* 240X320@60 16bit LCD */
    { 0,  1, 1, 240,  15, 9,  320,  65,  7,    1, 240, 14, 9, 1,  1,  0, 0, 0 }, /* 320X240@60  8bit LCD */
    { 0,  1, 1, 600,  23, 12, 800,  210, 46,   1, 1,   1,  1, 2,  1,  0, 0, 0 }, /* 800X600@60 24bit LCD */

    { 0,  1, 1, 1280, 24,  8,  720,  123, 99,  1, 1, 1, 1, 24,  4,  0, 0, 0 }, /* for MIPI DSI tx 720 x1280 at 60 hz */
    { 0,  1, 1, 1920, 36,  16, 1080, 28,  130, 1, 1, 1, 1, 8,   10, 0, 0, 0 }, /* for MIPI DSI tx 1080 x1920 at 60 hz */
    {} /* user */
};

hal_disp_syncinfo *vo_drv_comm_get_sync_timing(hi_vo_intf_sync sync)
{
    return &g_sync_timing[sync];
}

hi_s32 vou_drv_check_cvbs_sync(hi_vo_dev dev, hi_vo_intf_type intf_type, hi_vo_intf_sync intf_sync)
{
    if (intf_type & HI_VO_INTF_CVBS) {
        if ((intf_sync != HI_VO_OUT_PAL) && (intf_sync != HI_VO_OUT_NTSC)) {
            vo_err_trace("for CVBS interface, vo%d's intfsync %d illegal!\n", dev, intf_sync);
            return HI_ERR_VO_NOT_SUPPORT;
        }
    }

    return HI_SUCCESS;
}

hal_disp_pixel_format vou_drv_convert_data_format(vou_layer_pixerl_format data_fmt)
{
    hal_disp_pixel_format pixel_format = HAL_DISP_PIXELFORMAT_BUTT;

    if (data_fmt == VOU_LAYER_PIXERL_FORMAT_SP_YCBCR_420) {
        pixel_format = HAL_INPUTFMT_YCBCR_SEMIPLANAR_420;
    } else if (data_fmt == VOU_LAYER_PIXERL_FORMAT_SP_YCBCR_422) {
        pixel_format = HAL_INPUTFMT_YCBCR_SEMIPLANAR_422;
    } else if (data_fmt == VOU_LAYER_PIXERL_FORMAT_SP_YCBCR_400) {
        pixel_format = HAL_INPUTFMT_YCBCR_SEMIPLANAR_400;
    }

    return pixel_format;
}

hi_void vo_drv_board_init(hi_void)
{
    hal_vou_init();
    vo_drv_default_setting();
}

hi_void vo_drv_csc_trans_to_register(csc_coef *coef)
{
    const hi_s32 dc_precision = 4; /* 4 */

    coef->csc_in_dc0 = dc_precision * coef->csc_in_dc0;
    coef->csc_in_dc1 = dc_precision * coef->csc_in_dc1;
    coef->csc_in_dc2 = dc_precision * coef->csc_in_dc2;

    coef->csc_out_dc0 = dc_precision * coef->csc_out_dc0;
    coef->csc_out_dc1 = dc_precision * coef->csc_out_dc1;
    coef->csc_out_dc2 = dc_precision * coef->csc_out_dc2;
}

#endif

#endif /* #if VO_DESC("UBOOT") */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */
