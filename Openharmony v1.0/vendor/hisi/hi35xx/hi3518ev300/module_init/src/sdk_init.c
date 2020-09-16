/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include "asm/io.h"
#include "hi_module_param.h"

#include "stdlib.h"
#include "fcntl.h"
#include "string.h"
#include "board.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define SENSOR_NAME_LEN             64
#define CHIP_NAME_LEN               64
#define BOARD_NAME_LEN              64

static unsigned long long g_mmz_start = 0x42000000;
static unsigned int       g_mmz_size  = 32;   /* M Byte */
static char   g_chip_name[CHIP_NAME_LEN]     = "hi3518ev300";  /* hi3518ev300 */
static char   g_sensor_name[SENSOR_NAME_LEN] = "f23";       /* f23 */
static char   g_board_name[BOARD_NAME_LEN]   = "demo";         /* demo sck */

static void CHIP_init(void)
{
    return;
}

static int SYSCONFIG_init(void)
{
    extern int  hi_sysconfig_init(void);
    extern int  g_quick_start_flag;
    extern int  g_online_flag;
    extern int  g_cmos_yuv_flag;
    extern char g_sensor_list[SENSOR_NAME_LEN];
    extern char g_chip_list[CHIP_NAME_LEN];
    extern char g_board_list[BOARD_NAME_LEN];

    g_quick_start_flag = 0;
    g_online_flag      = 0;
    g_cmos_yuv_flag    = 0;
    strncpy(g_chip_list,   g_chip_name,   CHIP_NAME_LEN);
    strncpy(g_sensor_list, g_sensor_name, SENSOR_NAME_LEN);
    strncpy(g_board_list,  g_board_name,  BOARD_NAME_LEN);

    return hi_sysconfig_init();
}


static int MMZ_init(void)
{
    extern int media_mem_init(void *pArgs);
    MMZ_SETUP_MODULE_PARAMS_S stMMZ_Param = {0};

    snprintf(stMMZ_Param.mmz, MMZ_SETUP_CMDLINE_LENGTH, "anonymous,0,0x%llx,%dM", g_mmz_start, g_mmz_size);

    stMMZ_Param.anony = 1;

    dprintf("g_mmz_start=0x%llx, g_mmz_size=0x%x\n", g_mmz_start, g_mmz_size);
    dprintf("mmz param= %s\n", stMMZ_Param.mmz);

    return media_mem_init(&stMMZ_Param);
}

static int BASE_init(void)
{
    extern void base_get_module_param(void *pArgs);
    extern int base_mod_init(void *pArgs);

    BASE_MODULE_PARAMS_S stBaseModuleParam;
    base_get_module_param(&stBaseModuleParam);

    return base_mod_init(&stBaseModuleParam);
}

static int SYS_init(void)
{
    extern int sys_mod_init(void);

    return sys_mod_init();
}

static int RGN_init(void)
{
    extern int rgn_mod_init(void);

    return rgn_mod_init();
}

static int ISP_init(void)
{
    extern int isp_mod_init(void);

    return isp_mod_init();
}

static int VI_init(void)
{
    extern int vi_mod_init(void);

    return vi_mod_init();
}

static int VGS_init(void)
{
    extern void vgs_get_module_param(void *pArgs);
    extern int vgs_mod_init(void *pArgs);

    VGS_MODULE_PARAMS_S  stVgsModuleParam;

    vgs_get_module_param((void*)&stVgsModuleParam);
    stVgsModuleParam.u32MaxVgsJob  = 64;  /* 64 -- max job num */
    stVgsModuleParam.u32MaxVgsTask = 100; /* 100 -- max task num */
    stVgsModuleParam.u32MaxVgsNode = 100; /* 100 -- max node num */

    return vgs_mod_init(&stVgsModuleParam);
}

static int IVE_init(void)
{
    extern int ive_mod_init(void *pArgs);
    extern void ive_get_module_param(void *pArgs);

    IVE_MODULE_PARAMS_S stIveModuleParam;
    ive_get_module_param((void*)&stIveModuleParam);
    stIveModuleParam.bSavePowerEn = HI_TRUE;
    stIveModuleParam.u16IveNodeNum = 512; /* 512 -- node num */
    return ive_mod_init(&stIveModuleParam);
}

static int VPSS_init(void)
{
    extern void vpss_get_module_param(void *pArgs);
    extern int vpss_mod_init(void *pArgs);

    VPSS_MODULE_PARAMS_S  stVpssModuleParam;
    vpss_get_module_param((void*)&stVpssModuleParam);

    return vpss_mod_init(&stVpssModuleParam);
}

static int VO_init(void)
{
    extern int vou_module_init(void);

    return vou_module_init();
}

static int RC_init(void)
{
    extern int  rc_mod_init(void);
    return rc_mod_init();
}

static int VENC_init(void)
{
    extern void venc_get_module_param(void *pArgs);
    extern int  venc_mod_init(void *pArgs);

    VENC_MODULE_PARAMS_S  stVencModuleParam;
    venc_get_module_param((void*)&stVencModuleParam);
    return venc_mod_init(&stVencModuleParam);
}

static int CHNL_init(void)
{
    extern int chnl_mod_init(void);
    return chnl_mod_init();
}

static int VEDU_init(void)
{
    extern int vedu_mod_init(void);
    return vedu_mod_init();
}

static int H264e_init(void)
{
    extern int h264e_mod_init(void);
    return h264e_mod_init();
}

static int H265e_init(void)
{
    extern int h265e_mod_init(void *pArgs);
    return h265e_mod_init(NULL);
}

static int JPEGE_init(void)
{
    extern int jpege_mod_init(void);
    return jpege_mod_init();
}

static int hi_sensor_spi_init(void)
{
    extern int sensor_spi_dev_init(void *pArgs);
    return sensor_spi_dev_init(NULL);
}

static int hi_sensor_i2c_init(void)
{
    extern int hi_dev_init(void);
    return hi_dev_init();
}

static int PWM_init(void)
{
    return 0;
}

static int MIPI_RX_init(void)
{
    extern int mipi_rx_mod_init(void);
    return mipi_rx_mod_init();
}


static int AcodecMod_init(void)
{
    extern int acodec_mod_init(void *pArgs);
    return acodec_mod_init(NULL);
}

static int AiaoMod_init(void)
{
    extern int aiao_mod_init(void);
    return aiao_mod_init();
}

static int AiMod_init(void)
{
    extern int ai_mod_init(void);
    return ai_mod_init();
}

static int AoMod_init(void)
{
    extern int ao_mod_init(void *pArgs);
    return ao_mod_init(NULL);
}

static int AencMod_init(void)
{
    extern int  aenc_mod_init(void *pArgs);
    return aenc_mod_init(NULL);
}

static int AdecMod_init(void)
{
    extern int adec_mod_init(void *pArgs);
    return adec_mod_init(NULL);
}

static int  Cipher_init(void)
{
    extern int cipher_drv_mod_init(void);
    return cipher_drv_mod_init();
}

static int TDE_init(void)
{
    extern int tde_mod_init(void);
    return tde_mod_init();
}

static void insert_audio(void)
{
    int ret;

    ret = AiaoMod_init();
    if (ret != 0) {
        printf("aiao init error.\n");
    }

    ret = AiMod_init();
    if (ret != 0) {
        printf("ai init error.\n");
    }

    ret = AoMod_init();
    if (ret != 0) {
        printf("ao init error.\n");
    }

    ret = AencMod_init();
    if (ret != 0) {
        printf("aenc init error.\n");
    }

    ret = AdecMod_init();
    if (ret != 0) {
        printf("adec init error.\n");
    }

    ret = AcodecMod_init();
    if (ret != 0) {
        printf("acodec init error.\n");
    }

    printf("insert audio\n");
}
extern void osal_proc_init(void);
extern int hifb_init(void* pArgs);


static int HIFB_init(void)
{
    HIFB_MODULE_PARAMS_S stHIFB_Param;
    snprintf(stHIFB_Param.video, 64, "hifb:vram0_size:1620");  /* 64 -- str length */
    stHIFB_Param.bUpdateRotateRect = HI_FALSE;
    return hifb_init(&stHIFB_Param);
}

static int PM_init(void)
{
    return 0;
}


void SDK_init(void)
{
    int ret;

    CHIP_init();
    SYSCONFIG_init();
    osal_proc_init();

    ret = MMZ_init();
    if (ret != 0) {
        printf("MMZ init error.\n");
    }

    ret = BASE_init();
    if (ret != 0) {
        printf("base init error.\n");
    }

    ret = SYS_init();
    if (ret != 0) {
        printf("sys init error.\n");
    }

    ret = RGN_init();
    if (ret != 0) {
        printf("rgn init error.\n");
    }

    ret = VGS_init();
    if (ret != 0) {
        printf("vgs init error.\n");
    }

    ret = ISP_init();
    if (ret != 0) {
        printf("isp init error.\n");
    }

    ret = VI_init();
    if (ret != 0) {
        printf("vi init error.\n");
    }

    ret = VPSS_init();
    if (ret != 0) {
        printf("vpss init error.\n");
    }

    ret = VO_init();
    if (ret != 0) {
        printf("vo init error.\n");
    }

    ret = CHNL_init();
    if (ret != 0) {
        printf("chnl init error.\n");
    }

    ret = VEDU_init();
    if (ret != 0) {
        printf("vedu init error.\n");
    }

    ret = RC_init();
    if (ret != 0) {
        printf("rc init error.\n");
    }

    ret = VENC_init();
    if (ret != 0) {
        printf("venc init error.\n");
    }

    ret = H264e_init();
    if (ret != 0) {
        printf("H264e init error.\n");
    }

    ret = H265e_init();
    if (ret != 0) {
        printf("H265e init error.\n");
    }

    ret = JPEGE_init();
    if (ret != 0) {
        printf("jpege init error.\n");
    }

    ret = IVE_init();
    if (ret != 0) {
        printf("ive init error.\n");
    }
    insert_audio();

    ret = PWM_init();
    if (ret != 0) {
        printf("pwm init error.\n");
    }

#ifndef LOSCFG_DRIVERS_HDF_PLATFORM_SPI
#ifdef LOSCFG_DRIVERS_SPI
    dprintf("spi bus init ...\n");
    extern int spi_dev_init(void);
    spi_dev_init();
#endif
#endif

#ifndef LOSCFG_DRIVERS_HDF_PLATFORM_I2C
#ifdef LOSCFG_DRIVERS_I2C
    dprintf("i2c bus init ...\n");
    extern int i2c_dev_init(void);
    i2c_dev_init();
#endif
#endif

    ret = hi_sensor_spi_init();
    if (ret != 0) {
        printf("sensor spi init error.\n");
    }

    ret = Cipher_init();
    if (ret != 0) {
        printf("cipher init error.\n");
    }

    ret = MIPI_RX_init();
    if (ret != 0) {
        printf("mipi_rx init error.\n");
    }

    ret = hi_sensor_i2c_init();
    if (ret != 0) {
        printf("sensor i2c init error.\n");
    } else {
        printf("sensor i2c init OK.\n");
    }

    ret = TDE_init();
    if (ret != 0) {
        printf("TDE init error.\n");
    }

    ret =  HIFB_init();
    if (ret != 0) {
        printf("HIFB_init error.\n");
    }

    ret =  PM_init();
    if (ret != 0) {
        printf("PM_init error.\n");
    }

    printf("SDK init ok...\n");
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
