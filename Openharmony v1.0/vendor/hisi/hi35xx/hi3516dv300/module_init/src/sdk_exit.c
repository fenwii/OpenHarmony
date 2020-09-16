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

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

static void BASE_exit(void)
{
    extern void base_mod_exit(void);
    base_mod_exit();
}

static void MMZ_exit(void)
{
    extern void media_mem_exit(void);
    media_mem_exit();
}
static void SYS_exit(void)
{
    extern void sys_mod_exit(void);
    sys_mod_exit();
}

static void ISP_exit(void)
{
    extern void isp_mod_exit(void);
    isp_mod_exit();
}

static void VI_exit(void)
{
    extern void vi_mod_exit(void);
    vi_mod_exit();
}

static void RGN_exit(void)
{
    extern void rgn_mod_exit(void);
    rgn_mod_exit();
}

static void GDC_exit(void)
{
    extern void gdc_mod_exit(void);
    gdc_mod_exit();
}

static void DIS_exit(void)
{
    extern void dis_mod_exit(void);
    dis_mod_exit();
}

static void VGS_exit(void)
{
    extern void vgs_mod_exit(void);
    vgs_mod_exit();
}

static void VPSS_exit(void)
{
    extern void vpss_mod_exit(void);
    vpss_mod_exit();
}

static void VO_exit(void)
{
    extern void vou_module_exit(void);
    vou_module_exit();
}

static void TDE_exit(void)
{
    extern void tde_mod_exit(void);
    tde_mod_exit();
}

static void HIFB_exit(void)
{
    extern void hifb_cleanup(void);

    hifb_cleanup();
}

static void HDMI_exit(void)
{
    extern hi_void HDMI_DRV_ModExit(void);
    HDMI_DRV_ModExit();
}

static void MIPIRX_exit(void)
{
    extern void mipi_rx_mod_exit(void);
    mipi_rx_mod_exit();
}

static void MIPITX_exit(void)
{
    extern void mipi_tx_module_exit(void);
    mipi_tx_module_exit();
}

static void RC_exit(void)
{
    extern void rc_mod_exit(void);
    rc_mod_exit();
}

static void VENC_exit(void)
{
    extern void venc_mod_exit(void);
    venc_mod_exit();
}

static void CHNL_exit(void)
{
    extern void chnl_mod_exit(void);
    chnl_mod_exit();
}

static void VEDU_exit(void)
{
    extern void vedu_mod_exit(void);
    vedu_mod_exit();
}

static void H264e_exit(void)
{
    extern void h264e_mod_exit(void);
    h264e_mod_exit();
}

static void H265e_exit(void)
{
    extern  void h265e_mod_exit(void);
    h265e_mod_exit();
}

static void JPEGE_exit(void)
{
    extern void jpege_mod_exit(void);
    jpege_mod_exit();
}

static void PWM_exit(void)
{
    extern void pwm_exit(void);
    pwm_exit();
}

static void PIRIS_exit(void)
{
    extern void piris_exit(void);

    piris_exit();
}

static void hi_sensor_spi_exit(void)
{
    extern void sensor_spi_dev_exit(void);
    sensor_spi_dev_exit();
}

static void hi_sensor_i2c_exit(void)
{
    extern void hi_dev_exit(void);
    hi_dev_exit();
}

static void JPEGD_exit(void)
{
    extern void jpegd_mod_exit(void);
    jpegd_mod_exit();
}

static void VFMW_exit(void)
{
    extern void vfmw_mod_exit(void);
    vfmw_mod_exit();
}

static void VDEC_exit(void)
{
    extern void vdec_mod_exit(void);
    vdec_mod_exit();
}

static void IVE_exit(void)
{
    extern void ive_mod_exit(void);
    ive_mod_exit();
}

static void NNIE_exit(void)
{
    extern void nnie_mod_exit(void);
    nnie_mod_exit();
}

static void Cipher_exit(void)
{
    extern void cipher_drv_mod_exit(void);
    cipher_drv_mod_exit();
}

static void HI_USER_exit(void)
{
    extern void hi_user_exit(void);
    hi_user_exit();
}

static void AiaoMod_exit(void)
{
    extern void aiao_mod_exit(void);
    aiao_mod_exit();
}

static void AiMod_exit(void)
{
    extern void ai_mod_exit(void);
    ai_mod_exit();
}

static void AoMod_exit(void)
{
    extern void ao_mod_exit(void);
    ao_mod_exit();
}

static void AencMod_exit(void)
{
    extern void aenc_mod_exit(void);
    aenc_mod_exit();
}

static void AdecMod_exit(void)
{
    extern void adec_mod_exit(void);
    adec_mod_exit();
}

static void AcodecMod_exit(void)
{
    extern void acodec_mod_exit(void);
    acodec_mod_exit();
}

static void remove_audio(void)
{
    AcodecMod_exit();
    AdecMod_exit();
    AencMod_exit();
    AoMod_exit();
    AiMod_exit();
    AiaoMod_exit();
}

extern void osal_proc_exit(void);

void SDK_exit(void)
{
    HI_USER_exit();
    Cipher_exit();
    MIPITX_exit();
    MIPIRX_exit();
    HDMI_exit();
    hi_sensor_spi_exit();
    hi_sensor_i2c_exit();
    PIRIS_exit();
    PWM_exit();

    remove_audio();

    HIFB_exit();
    TDE_exit();
    NNIE_exit();
    IVE_exit();
    VDEC_exit();
    VFMW_exit();
    JPEGD_exit();
    JPEGE_exit();
    H265e_exit();
    H264e_exit();
    VENC_exit();
    RC_exit();
    VEDU_exit();
    CHNL_exit();

    VO_exit();
    VPSS_exit();
    ISP_exit();
    VI_exit();
    DIS_exit();
    VGS_exit();
    GDC_exit();
    RGN_exit();

    SYS_exit();
    BASE_exit();
    MMZ_exit();
    osal_proc_exit();

    printf("SDK exit ok...\n");
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
