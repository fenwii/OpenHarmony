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

#ifndef __HI_MOD_PARAM__
#define __HI_MOD_PARAM__

typedef enum {
    HI_FALSE = 0,
    HI_TRUE  = 1,
} HI_BOOL;

#define VGS_IP_NUM                     1
#define VPSS_IP_NUM                    1
#define GDC_IP_NUM                     1
#define VEDU_IP_NUM                    1

typedef struct hiBASE_MODULE_PARAMS_S {
    HI_BOOL bVbForceExit;
} BASE_MODULE_PARAMS_S;


typedef struct hiHIFB_MODULE_PARAMS_S {
    char video[64];
    HI_BOOL bUpdateRotateRect;
} HIFB_MODULE_PARAMS_S;

typedef struct hiVGS_MODULE_PARAMS_S {
    unsigned int u32MaxVgsJob;
    unsigned int u32MaxVgsTask;
    unsigned int u32MaxVgsNode;
    unsigned int au32VgsEn[VGS_IP_NUM];
    HI_BOOL bVgsHdrSupport;
    HI_BOOL bVgsExitInSys;
} VGS_MODULE_PARAMS_S;

typedef struct hiVPSS_MODULE_PARAMS_S {
    unsigned int u32VpssEn[VPSS_IP_NUM];
} VPSS_MODULE_PARAMS_S;

typedef struct hiGDC_MODULE_PARAMS_S {
    unsigned int u32MaxGdcJob;
    unsigned int u32MaxGdcTask;
    unsigned int u32MaxGdcNode;
    unsigned int au32GdcEn[GDC_IP_NUM];
} GDC_MODULE_PARAMS_S;

typedef struct hiVDEC_MODULE_PARAMS_S {
    unsigned int u32VdecMaxChnNum;
    HI_BOOL bVdecHfr;
} VDEC_MODULE_PARAMS_S;

typedef struct hiIVE_MODULE_PARAMS_S {
    HI_BOOL bSavePowerEn;
    unsigned short  u16IveNodeNum;
    unsigned short  u16Rsv;
} IVE_MODULE_PARAMS_S;

typedef struct hiSVP_NNIE_MODULE_PARAMS_S {
    HI_BOOL bSavePowerEn;
    unsigned short u16NnieTskBufNum;
} SVP_NNIE_MODULE_PARAMS_S;

typedef struct hiSVP_DSP_MODULE_PARAMS_S {
    unsigned short u16NodeNum;
    unsigned short u16DspInitMode;
} SVP_DSP_MODULE_PARAMS_S;

typedef struct hiACODEC_MODULE_PARAMS_S {
    unsigned int  u32InitDelayTimeMs;
} ACODEC_MODULE_PARAMS_S;

typedef struct hiISP_MODULE_PARAMS_S {
    unsigned int u32PwmNum;
    unsigned int u32ProcParam;
    unsigned int u32UpdatePos;
    unsigned int u32IntTimeOut;
    unsigned int bIntBottomHalf;
    unsigned int u32StatIntvl;
} ISP_MODULE_PARAMS_S;

typedef struct hiH265E_MODULE_PARAMS_S {
    unsigned int u32FeatureEnable;
} H265E_MODULE_PARAMS_S;

typedef struct hiVENC_MODULE_PARAMS_S {
    unsigned int u32VencMaxChnNum;
} VENC_MODULE_PARAMS_S;

typedef struct hiVEDU_MODULE_PARAMS_S {
    unsigned int  vedu_en[VEDU_IP_NUM];
} VEDU_MODULE_PARAMS_S;
typedef struct hiVFMW_MODULE_PARAMS_S {
    int s32VfmwMaxChnNum;
} VFMW_MODULE_PARAMS_S;

typedef struct hiSIL9024_MODULE_PARAMS_S {
    int norm;
    int i2c_num;
} SIL9024_MODULE_PARAMS_S;

typedef struct hiADV7179_MODULE_PARAMS_S {
    int Norm_mode;
    int i2c_num;
} ADV7179_MODULE_PARAMS_S;

typedef struct hiPM_MODULE_PARAMS_S {
    HI_BOOL  bAvspOn; /* HI_TRUE: on,HI_FALSE: off */
    HI_BOOL  bSvpAcceleratorOn; /* HI_TRUE: on,HI_FALSE: off */
    // HI_U32 u32RegulatorType; /* 0:DC-DC, 1:PMU */
} PM_MODULE_PARAMS_S;

#define MMZ_SETUP_CMDLINE_LENGTH      256
typedef struct hiMMZ_SETUP_MODULE_PARAMS_S {
    char mmz[MMZ_SETUP_CMDLINE_LENGTH];
    char map_mmz[MMZ_SETUP_CMDLINE_LENGTH];
    int anony;
} MMZ_SETUP_MODULE_PARAMS_S;

#endif
