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

#include "vo.h"
#include "mkp_vo_dev.h"
#include "mkp_vo_video.h"
#include "mkp_vo_comm.h"
#include "mkp_vo_gfx.h"
#include "mkp_vo_init.h"
#include "mkp_vo_user.h"
#include "hi_math.h"
#include <common.h>
#include <command.h>
#include <version.h>
#include <asm/io.h>
#include <asm/arch/platform.h>
#include <config.h>
#include <cpu_func.h>

#include "drv_vo.h"
#include "drv_vo_gfx.h"

hi_void vo_dcache_range(hi_phys_addr_t start_addr, hi_u64 size)
{
    if (dcache_status()) {
        flush_dcache_range(start_addr, start_addr + size);
    }
}

int set_vobg(unsigned int dev, unsigned int rgb)
{
    vo_check_dev_id_return(dev);
    vo_dev_set_bg_color(dev, rgb);
    return HI_SUCCESS;
}

static hi_void vo_construct_pub_attr(unsigned int dev,
    unsigned int type, unsigned int sync, hi_vo_pub_attr *pub_attr)
{
    hi_vo_sync_info *sync_info = HI_NULL;

    pub_attr->bg_color = vo_dev_get_bg_color(dev);
    pub_attr->intf_sync = sync;
    pub_attr->intf_type = type;
    if (vo_is_user_intf_sync(sync) == HI_TRUE) {
        sync_info = vo_get_dev_user_sync_timing(dev);
        if (sync_info != NULL) {
            memcpy(&(pub_attr->sync_info), sync_info, sizeof(hi_vo_sync_info));
        }
    }
}

static hi_s32 vo_set_user_sync_clk(unsigned int dev, unsigned int sync)
{
    hi_s32 ret;
    hi_vo_user_sync_info *user_sync = HI_NULL;

    if (vo_is_user_intf_sync(sync) == HI_TRUE) {
        /* set the user sync info: clk source, clk value */
        user_sync = vo_get_dev_user_sync_info(dev);
        if (user_sync == HI_NULL) {
            return HI_FAILURE;
        }
        ret = vo_set_user_sync_info(dev, user_sync);
        if (ret != HI_SUCCESS) {
            return ret;
        }
    }
    return HI_SUCCESS;
}

int start_vo(unsigned int dev, unsigned int type, unsigned int sync)
{
    hi_s32 ret;
    hi_vo_pub_attr pub_attr = {0};

    vo_init();

    vo_construct_pub_attr(dev, type, sync, &pub_attr);

    ret = vo_set_pub_attr(dev, &pub_attr);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    ret = vo_set_user_sync_clk(dev, sync);
    if (ret != HI_SUCCESS) {
        return ret;
    }

    ret = vo_enable(dev);
    return ret;
}

int stop_vo(unsigned int dev)
{
    vo_check_dev_id_return(dev);
    return vo_disable(dev);
}

static hi_s32 vo_construct_gfx_attr(unsigned long addr, unsigned int strd,
    hi_rect gfx_rect, unsigned int type, hi_vo_gfx_attr *gfx_attr)
{
    hi_vo_gfx_attr gfx_attr_tmp = {0};

    gfx_attr_tmp.stride = strd;
    gfx_attr_tmp.address = addr;
    gfx_attr_tmp.type = type;
    memcpy(&gfx_attr_tmp.display_rect, &gfx_rect, sizeof(hi_rect));

    return vo_drv_gfx_convert_gfx_attr(&gfx_attr_tmp, gfx_attr);
}

int start_gx(unsigned int layer, unsigned long addr, unsigned int strd, hi_rect gx_rect, unsigned int type)
{
    hi_s32 ret;
    hi_vo_gfx_attr gfx_attr = {0};

    ret = vo_construct_gfx_attr(addr, strd, gx_rect, type, &gfx_attr);
    if (ret != HI_SUCCESS) {
        vo_err_trace("convert gfx attr failed.\n");
        return ret;
    }

    ret = vo_set_gfx_attr(layer, &gfx_attr);
    if (ret != HI_SUCCESS) {
        printf("invalid parameter!\n");
        return ret;
    }
    ret = vo_enable_gfx_layer(layer, &gfx_attr);

    return ret;
}

int stop_gx(unsigned int layer)
{
    hi_s32 ret;
    ret = vo_disable_gfx_layer(layer);
    if (ret != HI_SUCCESS) {
        printf("invalid parameter!\n");
        return ret;
    }

    return HI_SUCCESS;
}

static hi_void vo_contruct_video_layer_attr(unsigned long addr, unsigned int strd,
    hi_rect layer_rect, hi_vo_video_layer_attr *video_attr)
{
    video_attr->stride = strd;
    video_attr->address = addr;
    memcpy(&video_attr->display_rect, &layer_rect, sizeof(hi_rect));
}

int start_videolayer(unsigned int layer, unsigned long addr, unsigned int strd, hi_rect layer_rect)
{
    hi_s32 ret;
    hi_vo_video_layer_attr video_attr = {0};

    vo_contruct_video_layer_attr(addr, strd, layer_rect, &video_attr);
    ret = vo_set_video_layer_attr(layer, &video_attr);
    if (ret != HI_SUCCESS) {
        printf("invalid parameter!\n");
        return ret;
    }

    vo_dcache_range(addr, strd * layer_rect.height * 3 / 2); /* 3 / 2 times */

    ret = vo_enable_video_layer(layer, &video_attr);

    return ret;
}

int stop_videolayer(unsigned int layer)
{
    hi_s32 ret;
    ret = vo_disable_video_layer(layer);
    if (ret != HI_SUCCESS) {
        printf("invalid parameter!\n");
        return ret;
    }

    return 0;
}
