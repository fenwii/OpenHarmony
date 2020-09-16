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

#ifndef __HI_DEFINES_H__
#define __HI_DEFINES_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#ifndef HICHIP
#define HICHIP                          0x3521d200
#endif

#define HI3521D_V200                    0x3521D200
#define HI3531D_V200                    0x3531D200

#define HI35xx_Vxxx                     0x35000000

#if HICHIP == HI3521D_V200
#define HI_CHIP_NAME                       "Hi3521DV200"
#endif

/* For VO */
#define HI_VO_MAX_PHYS_DEV_NUM             3  /* max physical dev num */
#define HI_VO_MAX_VIRT_DEV_NUM             0  /* max virtual dev num */
#define HI_VO_MAX_CAS_DEV_NUM              0  /* max cascade dev num */
#define HI_VO_MAX_DEV_NUM                  (HI_VO_MAX_PHYS_DEV_NUM + HI_VO_MAX_VIRT_DEV_NUM + HI_VO_MAX_CAS_DEV_NUM) /* max dev num */

#define HI_VO_VIRT_DEV_0                   3  /* virtual device 0 */
#define HI_VO_VIRT_DEV_1                   4  /* virtual device 1 */
#define HI_VO_VIRT_DEV_2                   5  /* virtual device 2 */
#define HI_VO_VIRT_DEV_3                   6  /* virtual device 3 */
#define HI_VO_CAS_DEV_1                    35  /* cascade device 1 */
#define HI_VO_CAS_DEV_2                    36  /* cascade device 2 */

#define HI_VO_MAX_PHYS_VIDEO_LAYER_NUM     4  /* max physical video layer num */
#define HI_VO_MAX_GFX_LAYER_NUM             4  /* max graphic layer num */
#define HI_VO_MAX_PHYS_LAYER_NUM           (HI_VO_MAX_PHYS_VIDEO_LAYER_NUM + HI_VO_MAX_GFX_LAYER_NUM) /* max physical layer num */
#define HI_VO_MAX_LAYER_NUM                (HI_VO_MAX_PHYS_LAYER_NUM + HI_VO_MAX_VIRT_DEV_NUM + HI_VO_MAX_CAS_DEV_NUM) /* max layer num */
#define HI_VO_MAX_LAYER_IN_DEV             2 /* max video layer num of each dev */

#define HI_VO_LAYER_V0                     0  /* video layer 0 */
#define HI_VO_LAYER_V1                     1  /* video layer 1 */
#define HI_VO_LAYER_V2                     2  /* video layer 2 */
#define HI_VO_LAYER_V3                     3  /* video layer 3 */
#define HI_VO_LAYER_G0                     4  /* graphics layer 0 */
#define HI_VO_LAYER_G1                     5  /* graphics layer 1 */
#define HI_VO_LAYER_G2                     6  /* graphics layer 2 */
#define HI_VO_LAYER_G3                     7  /* graphics layer 3 */
#define hi_vo_get_virt_layer(vo_virt_dev) ((vo_virt_dev) + 5)  /* get virtual layer of virtual dev */
#define hi_vo_get_cas_layer(vo_cas_dev)   ((vo_cas_dev) + 5)   /* get cascade layer of cascade dev */

#define HI_VO_MAX_PRIORITY                 4 /* max layer priority */
#define HI_VO_MIN_TOLERATE                 1 /* min play toleration 1ms */
#define HI_VO_MAX_TOLERATE                 100000 /* max play toleration 100s */

#define HI_VO_MAX_CHN_NUM                  64 /* max chn num */
#define HI_VO_MIN_CHN_WIDTH                32 /* channel minimal width */
#define HI_VO_MIN_CHN_HEIGHT               32 /* channel minimal height */
#define HI_VO_MAX_ZOOM_RATIO               1000 /* max zoom ratio, 1000 means 100% scale */

#define HI_VO_MAX_WBC_NUM                  1 /* max wbc num */

#define HI_VO_MAX_CAS_PATTERN             128     /* cascade pattern max number */
#define HI_VO_MAX_CAS_POS_32RGN           32      /* cascade position max number */
#define HI_VO_MAX_CAS_POS_64RGN           64      /* cascade position max number */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_DEFINES_H__ */
