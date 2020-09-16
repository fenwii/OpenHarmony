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

#include "mkp_vo_init.h"
#include "mkp_vo_dev.h"
#include "mkp_vo_gfx.h"
#include "mkp_vo_video.h"
#include "vo.h"
#include "hi_common_vo.h"
#include "hi_common_video.h"

#include "mkp_vo.h"
#include "sys_ext.h"

#include "hi_board.h"
#include "drv_vo.h"

#if VO_DESC("clk init")
static hi_void vo_init_set_sys_clk(hi_void)
{
    vo_lpw_bus_reset(HI_FALSE);
}

static hi_void vo_init_crg_clk(hi_void)
{
    vo_drv_set_all_crg_clk(HI_TRUE);
}

static hi_void vo_init_board(hi_void)
{
    vo_drv_board_init();
}
#endif

#if VO_DESC("init context")

static hi_void vo_init_context(hi_void)
{
    vo_init_dev_info();

    vo_init_layer_resource();
}
#endif

#if VO_DESC("vo init flag")

static hi_bool g_is_initialized = HI_FALSE;
hi_bool vo_get_vo_init_flag(hi_void)
{
    return g_is_initialized;
}

static hi_void vo_set_vo_init_flag(hi_bool flag)
{
    g_is_initialized = flag;
}
#endif

#if VO_DESC("init operation")

hi_s32 vo_init(hi_void)
{
    hi_vo_dev dev;
    hi_vo_layer layer;
    if (vo_get_vo_init_flag() == HI_FALSE) {
        /* unreset */
        vo_init_set_sys_clk();

        /* clk enable */
        vo_init_crg_clk();

        /* step1: init drv context */
        vo_init_context();

        /* step2: init mkp context */
        for (dev = 0; dev < HI_VO_MAX_PHYS_DEV_NUM; dev++) {
            vo_init_dev_ctx(dev);
        }
        for (layer = 0; layer < HI_VO_MAX_PHYS_VIDEO_LAYER_NUM; layer++) {
            vo_init_layer_ctx(layer);
        }

        /* step3: init mkp gfx context */
        vo_init_gfx();

        /* hardware init */
        vo_init_board();

        vo_set_vo_init_flag(HI_TRUE);
    }

    return HI_SUCCESS;
}
#endif
