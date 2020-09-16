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

#include "mkp_vo_user.h"
#include "mkp_vo.h"

#if VO_DESC("dev user sync timing")
/* dhd0: 1080P60, dhd1: 1080P60, dsd0: pal */
static hi_vo_sync_info g_vo_user_sync_timing[HI_VO_MAX_PHYS_DEV_NUM] = {
    /*
     * |--INTFACE---||-----TOP-----||----HORIZON--------||----BOTTOM-----||-PULSE-||-INVERSE-|
     * syncm, iop, itf,   vact, vbb,  vfb,  hact,  hbb,  hfb, hmid,bvact,bvbb, bvfb, hpw, vpw,idv, ihs, ivs
     */
    { 0, 1, 1, 1080, 41, 4, 1920, 192, 88,  1,    1,   1,  1,  44, 5, 0, 0, 0 }, /* 1080P@60_hz */
    { 0, 1, 1, 1080, 41, 4, 1920, 192, 88,  1,    1,   1,  1,  44, 5, 0, 0, 0 }, /* 1080P@60_hz */
    { 0, 0, 0,  288, 22, 2,  720, 132, 12,  1,  288,  23,  2, 126, 3, 0, 0, 0 }, /* 576I(PAL)  */
};

hi_vo_sync_info *vo_get_dev_user_sync_timing(hi_vo_dev dev)
{
    if ((dev < 0) || (dev >= HI_VO_MAX_PHYS_DEV_NUM)) {
        return HI_NULL;
    }
    return &(g_vo_user_sync_timing[dev]);
}
#endif

#if VO_DESC("dev user sync info")
/* dhd0: 1080P60, dhd1: 1080P60, dsd0: pal */
static hi_vo_user_sync_info g_vo_user_sync_info[HI_VO_MAX_PHYS_DEV_NUM] = {
    {
        .user_sync_attr = {
            .clk_src = HI_VO_CLK_SRC_PLL,
            .vo_pll = { /* if hdmi, set it by pixel clk and div mode */
                .fb_div = 99, /* 99 fb div */
                .frac = 0,
                .ref_div = 2, /* 2 ref div */
                .post_div1 = 4, /* 4 post div1 */
                .post_div2 = 2, /* 2 post div2 */
            },
        },
        .pre_div = 1, /* if hdmi, set it by pixel clk */
        .dev_div = 1, /* if rgb, set it by serial mode */
        .clk_reverse_en = HI_TRUE,
    }, {
        .user_sync_attr = {
            .clk_src = HI_VO_CLK_SRC_PLL,
            .vo_pll = { /* if hdmi, set it by pixel clk and div mode */
                .fb_div = 99, /* 99 fb div */
                .frac = 0,
                .ref_div = 2, /* 2 ref div */
                .post_div1 = 4, /* 4 post div1 */
                .post_div2 = 2, /* 2 post div2 */
            },
        },
        .pre_div = 1, /* if hdmi, set it by pixel clk */
        .dev_div = 1, /* if rgb, set it by serial mode */
        .clk_reverse_en = HI_TRUE,
    }, {
        .user_sync_attr = {
            .clk_src = HI_VO_CLK_SRC_PLL,
            .vo_pll = { /* if hdmi, set it by pixel clk and div mode */
                .fb_div = 99, /* 99 fb div */
                .frac = 0,
                .ref_div = 2, /* 2 ref div */
                .post_div1 = 4, /* 4 post div1 */
                .post_div2 = 2, /* 2 post div2 */
            },
        },
        .pre_div = 1, /* if hdmi, set it by pixel clk */
        .dev_div = 4, /* if cvbs, set it by 4 div mode */
        .clk_reverse_en = HI_FALSE,
    }
};

hi_vo_user_sync_info *vo_get_dev_user_sync_info(hi_vo_dev dev)
{
    if ((dev < 0) || (dev >= HI_VO_MAX_PHYS_DEV_NUM)) {
        return HI_NULL;
    }
    return &g_vo_user_sync_info[dev];
}
#endif
