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

#include "mipi_tx.h"
#include <common.h>
#include "type.h"
#include "mipi_tx_hal.h"
#include "hi3516cv500_vo.h"

#define MIPI_TX_DEV_NAME  "hi_mipi_tx"
#define MIPI_TX_PROC_NAME "mipi_tx"

#define HIMEDIA_DYNAMIC_MINOR 255

typedef struct {
    combo_dev_cfg_t dev_cfg;
} mipi_tx_dev_ctx_t;

mipi_tx_dev_ctx_t g_mipi_tx_dev_ctx;

/* the numbers below is the initialization of the dev config, not magic number */
/* 720x576_50 sync config */
static combo_dev_cfg_t g_mipi_tx_720x576_50_config = {
    .devno = 0,
    .lane_id = { 0, 1, 2, 3 },
    .output_mode = OUTPUT_MODE_DSI_VIDEO,
    .output_format = OUT_FORMAT_RGB_24_BIT,
    .video_mode = BURST_MODE,
    .sync_info = {
        .vid_pkt_size = 720,
        .vid_hsa_pixels = 64,
        .vid_hbp_pixels = 68,
        .vid_hline_pixels = 864,
        .vid_vsa_lines = 5,
        .vid_vbp_lines = 39,
        .vid_vfp_lines = 5,
        .vid_active_lines = 576,
        .edpi_cmd_size = 0,
    },
    .phy_data_rate = 459,
    .pixel_clk = 27000,
};

/* 1280x720_60 sync config */
static combo_dev_cfg_t g_mipi_tx_1280x720_60_config = {
    .devno = 0,
    .lane_id = { 0, 1, 2, 3 },
    .output_mode = OUTPUT_MODE_DSI_VIDEO,
    .output_format = OUT_FORMAT_RGB_24_BIT,
    .video_mode = BURST_MODE,
    .sync_info = {
        .vid_pkt_size = 1280,
        .vid_hsa_pixels = 40,
        .vid_hbp_pixels = 220,
        .vid_hline_pixels = 1650,
        .vid_vsa_lines = 5,
        .vid_vbp_lines = 20,
        .vid_vfp_lines = 5,
        .vid_active_lines = 720,
        .edpi_cmd_size = 0,
    },
    .phy_data_rate = 459,
    .pixel_clk = 74250,
};

/* 1920x1080_60 sync config */
static combo_dev_cfg_t g_mipi_tx_1920x1080_60_config = {
    .devno = 0,
    .lane_id = { 0, 1, 2, 3 },
    .output_mode = OUTPUT_MODE_DSI_VIDEO,
    .output_format = OUT_FORMAT_RGB_24_BIT,
    .video_mode = BURST_MODE,
    .sync_info = {
        .vid_pkt_size = 1920,
        .vid_hsa_pixels = 44,
        .vid_hbp_pixels = 148,
        .vid_hline_pixels = 2200,
        .vid_vsa_lines = 5,
        .vid_vbp_lines = 36,
        .vid_vfp_lines = 4,
        .vid_active_lines = 1080,
        .edpi_cmd_size = 0,
    },
    .phy_data_rate = 945,
    .pixel_clk = 148500,
};

/* 1024x768_60 sync config */
static combo_dev_cfg_t g_mipi_tx_1024x768_60_config = {
    .devno = 0,
    .lane_id = { 0, 1, 2, 3 },
    .output_mode = OUTPUT_MODE_DSI_VIDEO,
    .output_format = OUT_FORMAT_RGB_24_BIT,
    .video_mode = BURST_MODE,
    .sync_info = {
        .vid_pkt_size = 1024,
        .vid_hsa_pixels = 136,
        .vid_hbp_pixels = 160,
        .vid_hline_pixels = 1344,
        .vid_vsa_lines = 6,
        .vid_vbp_lines = 29,
        .vid_vfp_lines = 3,
        .vid_active_lines = 768,
        .edpi_cmd_size = 0,
    },
    .phy_data_rate = 495,  /* 486 */
    .pixel_clk = 65000,
};

/* 1280x1024_60 sync config */
static combo_dev_cfg_t g_mipi_tx_1280x1024_60_config = {
    .devno = 0,
    .lane_id = { 0, 1, 2, 3 },
    .output_mode = OUTPUT_MODE_DSI_VIDEO,
    .output_format = OUT_FORMAT_RGB_24_BIT,
    .video_mode = BURST_MODE,
    .sync_info = {
        .vid_pkt_size = 1280,
        .vid_hsa_pixels = 112,
        .vid_hbp_pixels = 248,
        .vid_hline_pixels = 1688,
        .vid_vsa_lines = 3,
        .vid_vbp_lines = 38,
        .vid_vfp_lines = 1,
        .vid_active_lines = 1024,
        .edpi_cmd_size = 0,
    },
    .phy_data_rate = 495,  /* 486 */
    .pixel_clk = 108000,
};

/* 720x1280_60 sync config */
static combo_dev_cfg_t g_mipi_tx_720x1280_60_config = {
    .devno = 0,
    .lane_id = { 0, 1, 2, 3 },
    .output_mode = OUTPUT_MODE_DSI_VIDEO,
    .output_format = OUT_FORMAT_RGB_24_BIT,
    .video_mode = BURST_MODE,
    .sync_info = {
        .vid_pkt_size = 720,       /* hact */
        .vid_hsa_pixels = 24,      /* hsa */
        .vid_hbp_pixels = 99,      /* hbp */
        .vid_hline_pixels = 943,   /* hact + hsa + hbp + hfp */
        .vid_vsa_lines = 4,        /* vsa */
        .vid_vbp_lines = 20,       /* vbp */
        .vid_vfp_lines = 8,        /* vfp */
        .vid_active_lines = 1280,  /* vact */
        .edpi_cmd_size = 0,
    },
    .phy_data_rate = 459,
    .pixel_clk = 74250,
};

/* 1080x1920_60 sync config */
static combo_dev_cfg_t g_mipi_tx_1080x1920_60_config = {
    .devno = 0,
    .lane_id = { 0, 1, 2, 3 },
    .output_mode = OUTPUT_MODE_DSI_VIDEO,
    .output_format = OUT_FORMAT_RGB_24_BIT,
    .video_mode = BURST_MODE,
    .sync_info = {
        .vid_pkt_size = 1080,
        .vid_hsa_pixels = 8,
        .vid_hbp_pixels = 20,
        .vid_hline_pixels = 1238,
        .vid_vsa_lines = 10,
        .vid_vbp_lines = 26,
        .vid_vfp_lines = 16,
        .vid_active_lines = 1920,
        .edpi_cmd_size = 0,
    },
    .phy_data_rate = 945,
    .pixel_clk = 148500,
};


static int mipi_tx_check_comb_dev_cfg(const combo_dev_cfg_t *dev_cfg)
{
    return 0;
}

static int mipi_tx_set_combo_dev_cfg(const combo_dev_cfg_t *dev_cfg)
{
    int ret;

    ret = mipi_tx_check_comb_dev_cfg(dev_cfg);
    if (ret < 0) {
        hi_err("mipi_tx check combo_dev config failed!\n");
        return -1;
    }

    /* set controler config */
    mipi_tx_drv_set_controller_cfg(dev_cfg);

    /* set phy config */
    mipi_tx_drv_set_phy_cfg(dev_cfg);

    memcpy(&g_mipi_tx_dev_ctx.dev_cfg, dev_cfg, sizeof(combo_dev_cfg_t));

    return ret;
}

static int mipi_tx_set_cmd(const cmd_info_t *cmd_info)
{
    return mipi_tx_drv_set_cmd_info(cmd_info);
}

static int mipi_tx_get_cmd(get_cmd_info_t *get_cmd_info)
{
    return mipi_tx_drv_get_cmd_info(get_cmd_info);
}

static void mipi_tx_enable(void)
{
    output_mode_t output_mode;

    output_mode = g_mipi_tx_dev_ctx.dev_cfg.output_mode;

    mipi_tx_drv_enable_input(output_mode);
}

static void mipi_tx_disable(void)
{
    mipi_tx_drv_disable_input();
}

static long mipi_tx_ioctl(unsigned int cmd, unsigned long arg)
{
    int ret = 0;

    switch (cmd) {
        case HI_MIPI_TX_SET_DEV_CFG: {
            combo_dev_cfg_t *combo_dev_cfg = (combo_dev_cfg_t *)(uintptr_t)arg;
            mipi_tx_check_null_ptr_return(combo_dev_cfg);

            ret = mipi_tx_set_combo_dev_cfg(combo_dev_cfg);
            if (ret < 0) {
                hi_err("mipi_tx set combo_dev config failed!\n");
                ret = -1;
            }
            break;
        }

        case HI_MIPI_TX_SET_CMD: {
            cmd_info_t *cmd_info = (cmd_info_t *)(uintptr_t)arg;
            mipi_tx_check_null_ptr_return(cmd_info);

            ret = mipi_tx_set_cmd(cmd_info);
            if (ret < 0) {
                hi_err("mipi_tx set cmd failed!\n");
                ret = -1;
            }
            break;
        }

        case HI_MIPI_TX_GET_CMD: {
            get_cmd_info_t *get_cmd_info = (get_cmd_info_t *)(uintptr_t)arg;
            mipi_tx_check_null_ptr_return(get_cmd_info);
            ret = mipi_tx_get_cmd(get_cmd_info);
            if (ret < 0) {
                hi_err("mipi_tx get cmd failed!\n");
                ret = -1;
            }
            break;
        }

        case HI_MIPI_TX_ENABLE: {
            mipi_tx_enable();
            break;
        }

        case HI_MIPI_TX_DISABLE: {
            mipi_tx_disable();
            break;
        }

        default: {
            hi_err("invalid mipi_tx ioctl cmd\n");
            ret = -1;
            break;
        }
    }

    return ret;
}

static int mipi_tx_init(void)
{
    return mipi_tx_drv_init();
}

static void mipi_tx_exit(void)
{
    mipi_tx_drv_exit();
}

int mipi_tx_module_init(void)
{
    int ret;

    ret = mipi_tx_init();
    if (ret != 0) {
        printf("hi_mipi_init failed!\n");
        return -1;
    }

    printf("load mipi_tx driver successful!\n");
    return 0;
}

void mipi_tx_module_exit(void)
{
    mipi_tx_exit();

    printf("unload mipi_tx driver ok!\n");
}

int mipi_tx_display(unsigned int vosync)
{
    int ret;
    combo_dev_cfg_t *mipi_tx_config = HI_NULL;
    printf("this is mipi_tx begin.\n");
    /* mipi_tx drv init. */
    mipi_tx_module_init();

    switch (vosync) {
        case VO_OUTPUT_576P50:
            mipi_tx_config = &g_mipi_tx_720x576_50_config;
            break;
        case VO_OUTPUT_720P60:
            mipi_tx_config = &g_mipi_tx_1280x720_60_config;
            break;
        case VO_OUTPUT_1080P60:
            mipi_tx_config = &g_mipi_tx_1920x1080_60_config;
            break;
        case VO_OUTPUT_1024x768_60:
            mipi_tx_config = &g_mipi_tx_1024x768_60_config;
            break;
        case VO_OUTPUT_1280x1024_60:
            mipi_tx_config = &g_mipi_tx_1280x1024_60_config;
            break;
        case VO_OUTPUT_720x1280_60:
            mipi_tx_config = &g_mipi_tx_720x1280_60_config;
            break;
        case VO_OUTPUT_1080x1920_60:
            mipi_tx_config = &g_mipi_tx_1080x1920_60_config;
            break;
        default:
            mipi_tx_config = &g_mipi_tx_1920x1080_60_config;
            break;
    }

    /* step 1 : config mipi_tx controller. */
    ret = mipi_tx_ioctl(HI_MIPI_TX_SET_DEV_CFG, (unsigned long)(uintptr_t)mipi_tx_config);
    if (ret != 0) {
        printf("MIPI_TX SET_DEV_CONFIG failed\n");
        return -1;
    }

    /* step 2 : init display device (do it yourself ). */
    udelay(10000); /* delay 10000 us for the stable signal */

    /* step 3 : enable mipi_tx controller. */
    ret = mipi_tx_ioctl(HI_MIPI_TX_ENABLE, (unsigned long)0);
    if (ret != 0) {
        printf("MIPI_TX enable failed\n");
        return -1;
    }

    printf("this is mipi_tx end.\n");

    return 0;
}

int mipi_tx_stop(void)
{
    printf("this is mipi_tx stop begin.\n");

    /* mipi_tx drv exit. */
    mipi_tx_module_exit();
    printf("this is mipi_tx stop end.\n");
    return 0;
}

