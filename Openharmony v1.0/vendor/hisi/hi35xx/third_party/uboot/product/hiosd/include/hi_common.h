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

#ifndef __HI_COMMON_H__
#define __HI_COMMON_H__

#include "hi_type.h"
#include "hi_defines.h"
#ifndef __KERNEL__
#include "securec.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* end of #ifdef __cplusplus */

#ifndef VER_X
#define VER_X                  1
#endif

#ifndef VER_Y
#define VER_Y                  0
#endif

#ifndef VER_Z
#define VER_Z                  0
#endif

#ifndef VER_P
#define VER_P                  0
#endif

#ifndef VER_B
#define VER_B                  0
#endif

#ifdef HI_DEBUG
#define VER_D                  " Debug"
#else
#define VER_D                  " Release"
#endif

#define HI_COMPAT_POINTER(ptr, type) \
    do { \
        hi_ulong ulAddr = (hi_ulong)ptr; \
        hi_u32 u32Addr = (hi_u32)ulAddr; \
        ptr = (type)(hi_ulong)u32Addr; \
    } while (0)

#define __MK_VERSION(x, y, z, p, b) #x "." #y "." #z "." #p " B0" #b
#define MK_VERSION(x, y, z, p, b) __MK_VERSION(x, y, z, p, b)
#define HI_MPP_VERSION            HI_CHIP_NAME HI_MPP_VER_PRIX MK_VERSION(VER_X, VER_Y, VER_Z, VER_P, VER_B) VER_D


#define HI_MAX_VERSION_NAME_LEN    64
#define HI_INVALID_CHN         (-1)
#define HI_INVALID_WAY         (-1)
#define HI_INVALID_LAYER       (-1)
#define HI_INVALID_DEV         (-1)
#define HI_INVALID_HANDLE      (-1)
#define HI_INVALID_VALUE       (-1)
#define HI_INVALID_TYPE        (-1)

#define HI_MPP_MOD_VI             "vi"
#define HI_MPP_MOD_VO             "vo"
#define HI_MPP_MOD_AVS            "avs"
#define HI_MPP_MOD_HDMI           "hdmi"
#define HI_MPP_MOD_VGS            "vgs"
#define HI_MPP_MOD_GDC            "gdc"
#define HI_MPP_MOD_DIS            "dis"
#define HI_MPP_MOD_GYRODIS        "gyrodis"
#define HI_MPP_MOD_CHNL           "chnl"
#define HI_MPP_MOD_VENC           "venc"
#define HI_MPP_MOD_VPSS           "vpss"
#define HI_MPP_MOD_RGN            "rgn"
#define HI_MPP_MOD_IVE            "ive"
#define HI_MPP_MOD_FD             "fd"
#define HI_MPP_MOD_MD             "md"
#define HI_MPP_MOD_IVP            "ivp"
#define HI_MPP_MOD_SVP            "svp"
#define HI_MPP_MOD_SVP_NNIE       "nnie"
#define HI_MPP_MOD_SVP_DSP        "dsp"
#define HI_MPP_MOD_SVP_ALG        "svp_alg"
#define HI_MPP_MOD_DPU_RECT       "rect"
#define HI_MPP_MOD_DPU_MATCH      "match"
#define HI_MPP_MOD_SVP_MAU        "mau"
#define HI_MPP_MOD_H264E          "h264e"
#define HI_MPP_MOD_H265E          "h265e"
#define HI_MPP_MOD_JPEGE          "jpege"
#define HI_MPP_MOD_MPEG4E         "mpeg4e"
#define HI_MPP_MOD_VEDU           "vedu"
#define HI_MPP_MOD_PRORES         "prores"
#define HI_MPP_MOD_VDEC           "vdec"
#define HI_MPP_MOD_H264D          "h264d"
#define HI_MPP_MOD_JPEGD          "jpegd"
#define HI_MPP_MOD_AI             "ai"
#define HI_MPP_MOD_AO             "ao"
#define HI_MPP_MOD_AENC           "aenc"
#define HI_MPP_MOD_ADEC           "adec"
#define HI_MPP_MOD_AIO            "aio"
#define HI_MPP_MOD_ACODEC         "acodec"
#define HI_MPP_MOD_VB             "vb"
#define HI_MPP_MOD_SYS            "sys"
#define HI_MPP_MOD_CMPI           "cmpi"
#define HI_MPP_MOD_PCIV           "pciv"
#define HI_MPP_MOD_PCIVFMW        "pcivfmw"
#define HI_MPP_MOD_PROC           "proc"
#define HI_MPP_MOD_LOG            "logmpp"
#define HI_MPP_MOD_FB             "fb"
#define HI_MPP_MOD_RC             "rc"
#define HI_MPP_MOD_TDE            "tde"
#define HI_MPP_MOD_ISP            "isp"
#define HI_MPP_MOD_USR            "usr"
#define HI_MPP_MOD_MCF            "mcf"
#define HI_MPP_MOD_PM             "pm"
#define HI_MPP_MOD_MFUSION        "motionfusion"
#define HI_MPP_MOD_VDA            "vda"

typedef struct {
    hi_char version[HI_MAX_VERSION_NAME_LEN];
} hi_mpp_version;

typedef hi_s32 hi_ai_chn;
typedef hi_s32 hi_ao_chn;
typedef hi_s32 hi_aenc_chn;
typedef hi_s32 hi_adec_chn;
typedef hi_s32 hi_audio_dev;
typedef hi_s32 hi_vi_dev;
typedef hi_s32 hi_vi_pipe;
typedef hi_s32 hi_vi_way;
typedef hi_s32 hi_vi_chn;
typedef hi_s32 hi_vo_dev;
typedef hi_s32 hi_vo_layer;
typedef hi_s32 hi_vo_chn;
typedef hi_s32 hi_vo_wbc;
typedef hi_s32 hi_gfx_layer;
typedef hi_s32 hi_venc_chn;
typedef hi_s32 hi_vdec_chn;
typedef hi_s32 hi_ive_handle;
typedef hi_s32 hi_fd_chn;
typedef hi_s32 hi_md_chn;
typedef hi_s32 hi_sensor_id;
typedef hi_s32 hi_mipi_dev;
typedef hi_s32 hi_slave_dev;
typedef hi_s32 hi_svp_nnie_handle;
typedef hi_s32 hi_svp_dsp_handle;
typedef hi_s32 hi_svp_alg_chn;
typedef hi_s32 hi_svp_mau_handle;
typedef hi_s32 hi_vpss_grp;
typedef hi_s32 hi_vpss_grp_pipe;
typedef hi_s32 hi_vpss_chn;
typedef hi_s32 hi_avs_grp;
typedef hi_s32 hi_avs_pipe;
typedef hi_s32 hi_avs_chn;
typedef hi_s32 hi_mcf_grp;
typedef hi_s32 hi_mcf_pipe;
typedef hi_s32 hi_mcf_chn;
typedef hi_s32 hi_vda_chn;
typedef hi_s32 hi_pciv_chn;

typedef enum {
    HI_ID_CMPI    = 0,
    HI_ID_VB      = 1,
    HI_ID_SYS     = 2,
    HI_ID_RGN      = 3,
    HI_ID_CHNL    = 4,
    HI_ID_VDEC    = 5,
    HI_ID_AVS     = 6,
    HI_ID_VPSS    = 7,
    HI_ID_VENC    = 8,
    HI_ID_SVP     = 9,
    HI_ID_H264E   = 10,
    HI_ID_JPEGE   = 11,
    HI_ID_H265E   = 13,
    HI_ID_JPEGD   = 14,
    HI_ID_VO      = 15,
    HI_ID_VI      = 16,
    HI_ID_DIS     = 17,
    HI_ID_VALG    = 18,
    HI_ID_RC      = 19,
    HI_ID_AIO     = 20,
    HI_ID_AI      = 21,
    HI_ID_AO      = 22,
    HI_ID_AENC    = 23,
    HI_ID_ADEC    = 24,
    HI_ID_VPU    = 25,
    HI_ID_PCIV    = 26,
    HI_ID_PCIVFMW = 27,
    HI_ID_ISP      = 28,
    HI_ID_IVE      = 29,
    HI_ID_USER    = 30,
    HI_ID_PROC    = 33,
    HI_ID_LOG     = 34,
    HI_ID_VFMW    = 35,
    HI_ID_GDC     = 37,
    HI_ID_PHOTO   = 38,
    HI_ID_FB      = 39,
    HI_ID_HDMI    = 40,
    HI_ID_VOIE    = 41,
    HI_ID_TDE     = 42,
    HI_ID_HDR      = 43,
    HI_ID_PRORES  = 44,
    HI_ID_VGS     = 45,
    HI_ID_FD      = 47,
    HI_ID_OD      = 48,
    HI_ID_LPR      = 50,
    HI_ID_SVP_NNIE     = 51,
    HI_ID_SVP_DSP      = 52,
    HI_ID_DPU_RECT     = 53,
    HI_ID_DPU_MATCH    = 54,

    HI_ID_MOTIONSENSOR = 55,
    HI_ID_MOTIONFUSION = 56,

    HI_ID_GYRODIS      = 57,
    HI_ID_PM           = 58,
    HI_ID_SVP_ALG      = 59,
	HI_ID_IVP          = 60,
	HI_ID_MCF          = 61,
    HI_ID_SVP_MAU      = 62,
    HI_ID_VDA     = 63,

    HI_ID_BUTT,
} hi_mod_id;

typedef struct {
    hi_mod_id    mod_id;
    hi_s32      dev_id;
    hi_s32      chn_id;
} hi_mpp_chn;

/* We just coyp this value of payload type from RTP/RTSP definition */
typedef enum {
        HI_PT_PCMU          = 0,
        HI_PT_1016          = 1,
        HI_PT_G721          = 2,
        HI_PT_GSM           = 3,
        HI_PT_G723          = 4,
        HI_PT_DVI4_8K       = 5,
        HI_PT_DVI4_16K      = 6,
        HI_PT_LPC           = 7,
        HI_PT_PCMA          = 8,
        HI_PT_G722          = 9,
        HI_PT_S16BE_STEREO  = 10,
        HI_PT_S16BE_MONO    = 11,
        HI_PT_QCELP         = 12,
        HI_PT_CN            = 13,
        HI_PT_MPEGAUDIO     = 14,
        HI_PT_G728          = 15,
        HI_PT_DVI4_3        = 16,
        HI_PT_DVI4_4        = 17,
        HI_PT_G729          = 18,
        HI_PT_G711A         = 19,
        HI_PT_G711U         = 20,
        HI_PT_G726          = 21,
        HI_PT_G729A         = 22,
        HI_PT_LPCM          = 23,
        HI_PT_CelB          = 25,
        HI_PT_JPEG          = 26,
        HI_PT_CUSM          = 27,
        HI_PT_NV            = 28,
        HI_PT_PICW          = 29,
        HI_PT_CPV           = 30,
        HI_PT_H261          = 31,
        HI_PT_MPEGVIDEO     = 32,
        HI_PT_MPEG2TS       = 33,
        HI_PT_H263          = 34,
        HI_PT_SPEG          = 35,
        HI_PT_MPEG2VIDEO    = 36,
        HI_PT_AAC           = 37,
        HI_PT_WMA9STD       = 38,
        HI_PT_HEAAC         = 39,
        HI_PT_PCM_VOICE     = 40,
        HI_PT_PCM_AUDIO     = 41,
        HI_PT_MP3           = 43,
        HI_PT_ADPCMA        = 49,
        HI_PT_AEC           = 50,
        HI_PT_X_LD          = 95,
        HI_PT_H264          = 96,
        HI_PT_D_GSM_HR      = 200,
        HI_PT_D_GSM_EFR     = 201,
        HI_PT_D_L8          = 202,
        HI_PT_D_RED         = 203,
        HI_PT_D_VDVI        = 204,
        HI_PT_D_BT656       = 220,
        HI_PT_D_H263_1998   = 221,
        HI_PT_D_MP1S        = 222,
        HI_PT_D_MP2P        = 223,
        HI_PT_D_BMPEG       = 224,
        HI_PT_MP4VIDEO      = 230,
        HI_PT_MP4AUDIO      = 237,
        HI_PT_VC1           = 238,
        HI_PT_JVC_ASF       = 255,
        HI_PT_D_AVI         = 256,
        HI_PT_DIVX3         = 257,
        HI_PT_AVS           = 258,
        HI_PT_REAL8         = 259,
        HI_PT_REAL9         = 260,
        HI_PT_VP6           = 261,
        HI_PT_VP6F          = 262,
        HI_PT_VP6A          = 263,
        HI_PT_SORENSON      = 264,
        HI_PT_H265          = 265,
        HI_PT_VP8           = 266,
        HI_PT_MVC           = 267,
        HI_PT_PNG           = 268,
        /* add by hisilicon */
        HI_PT_AMR           = 1001,
        HI_PT_MJPEG         = 1002,
        HI_PT_AMRWB         = 1003,
        HI_PT_PRORES        = 1006,
        HI_PT_OPUS          = 1007,
        HI_PT_BUTT
    } hi_payload_type;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of #ifdef __cplusplus */

#endif /* __HI_COMMON_H__ */

