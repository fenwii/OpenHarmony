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

#include "drv_hdmi_infoframe.h"
#include "boot_hdmi_intf.h"
#include "hdmi_product_define.h"
#include "drv_hdmi_common.h"
#include "hdmi_hal.h"

#define  INFOFRAME_BUFFER_LEN 32

hdmi_video_timing drv_hdmi_video_timing_lookup(hdmi_video_code vic, hdmi_picture_aspect aspect)
{
    hi_u32 cnt, vic_size;
    hdmi_video_timing video_timing = HDMI_VIDEO_TIMING_UNKNOWN;

    vic_size = sizeof(g_cea_video_codes_des) / sizeof(g_cea_video_codes_des[0]);
    for (cnt = 0; cnt < vic_size; cnt++) {
        if (g_cea_video_codes_des[cnt].video_code == vic &&
            g_cea_video_codes_des[cnt].aspect_ratio == aspect) {
            video_timing = g_cea_video_codes_des[cnt].timing;
            break;
        }
    }

    return video_timing;
}

hdmi_video_timing drv_hdmi_vsif_video_timing_lookup(hdmi_vsif_vic vic, hdmi_picture_aspect aspect)
{
    hi_u32 cnt, vic_size;
    hdmi_video_timing video_timing = 0;

    vic_size = sizeof(g_h14b_hdmi_video_codes_4k) / sizeof(g_h14b_hdmi_video_codes_4k[0]);
    for (cnt = 0; cnt < vic_size; cnt++) {
        if (g_h14b_hdmi_video_codes_4k[cnt].hdmi_vic == vic) {
            video_timing = g_h14b_hdmi_video_codes_4k[cnt].timing;
            break;
        }
    }

    return video_timing;
}

static hi_void hdmi_infoframe_checksum(hi_void *buffer, hi_u32 size)
{
    hi_u8 *ptr = HI_NULL;
    hi_u8 csum = 0;
    hi_u32 i;

    if (buffer == HI_NULL) {
        return;
    }
    if (size < 3) {
        return;
    }
    ptr = buffer;

    /* compute checksum */
    for (i = 0; i < size; i++) {
        csum += ptr[i];
    }
    if ((0 < csum) && (csum <= 255)) {
        ptr[3] = 256 - csum;
    } else {
        ptr[3] = 0;
    }
}

static hi_s32 hdmi_avi_infoframe_pack(struct hdmi_avi_infoframe *frame, hi_void *buffer,
    hi_u32 size, hdmi_3d_mode _3d_mode)
{
    hi_u32 length = 0;
    hi_u8 *ptr = HI_NULL;
    hi_bool _3d_enable = HI_FALSE;
    enum hdmi_video_code video_code = 0;

    hdmi_if_null_return(frame, HI_FAILURE);
    hdmi_if_null_return(buffer, HI_FAILURE);

    ptr = buffer;
    length = HDMI_INFOFRAME_HEADER_SIZE + frame->length;

    if (size < length) {
        return -1;
    }

    _3d_enable = (_3d_mode != HDMI_3D_BUTT) ? HI_FALSE : HI_TRUE;
    video_code = drv_hdmi_vic_search(frame->video_timing, frame->picture_aspect, _3d_enable);

    memset(buffer, 0, length);
    ptr[0] = frame->type;

    /* Y2 = 1 or vic >= 128, version shall use 3 */
    if (((hi_u32)frame->colorspace & 0x4) || (video_code >= 128)) {
        frame->version = 3; /* frame version 3 */
    } else if (frame->colorimetry == HDMI_COLORIMETRY_EXTENDED &&
               frame->extended_colorimetry == HDMI_EXTENDED_COLORIMETRY_ADDITIONAL) {
        /* (C1,C0)=(1,1) and (EC2,EC1,EC0)=(1,1,1), version shall use 4 */
        frame->version = 4;
    }

    ptr[1] = frame->version;
    ptr[2] = frame->length;
    ptr[3] = 0; /* checksum */

    /* start infoframe payload */
    ptr += HDMI_INFOFRAME_HEADER_SIZE;

    /* colorspace in bit[6,5], need shift left 5 bit */
    ptr[0] = (((hi_u8)frame->colorspace & 0x3) << 5) | ((hi_u8)frame->scan_mode & 0x3);

    if (frame->active_info_valid) {
        ptr[0] |= SET_BIT(4); /* set bit 4 */
    }
    if (frame->horizontal_bar_valid) {
        ptr[0] |= SET_BIT(3); /* set bit 3 */
    }
    if (frame->vertical_bar_valid) {
        ptr[0] |= SET_BIT(2); /* set bit 2 */
    }
    /*
     * colorimetry in bit[7,6], need shift left 6 bit
     * picture_aspect in bit[5,4], need shift left 4 bit
     */
    ptr[1] = (((hi_u8)frame->colorimetry & 0x3) << 6) |
             (((hi_u8)frame->picture_aspect & 0x3) << 4) |
             ((hi_u8)frame->active_aspect & 0xf);
    /*
     * extended_colorimetry in bit[6,4], need shift left 4 bit
     * quantization_range in bit[3,2], shift left 2 bit
     */
    ptr[2] = (((hi_u8)frame->extended_colorimetry & 0x7) << 4) |
             (((hi_u8)frame->quantization_range & 0x3) << 2) |
             ((hi_u8)frame->nups & 0x3);
    if (frame->itc) {
        ptr[2] |= SET_BIT(7); /* set bit 7 */
    }
    ptr[3] = (hi_u8)video_code & 0xff; /* frame->video_code */
    /*
     * ycc_quantization_range in bit[7,6], need shift left 6 bit
     * content_type in bit[5,4], need shift left 4 bit
     */
    ptr[4] = (((hi_u8)frame->ycc_quantization_range & 0x3) << 6) |
             (((hi_u8)frame->content_type & 0x3) << 4) |
             ((frame->pixel_repeat - 1) & 0xf);
    ptr[5]  = frame->top_bar & 0xff;
    ptr[6]  = (frame->top_bar >> 8) & 0xff; /* get high 8bit, shift right 8 */
    ptr[7]  = frame->bottom_bar & 0xff;
    ptr[8]  = (frame->bottom_bar >> 8) & 0xff; /* get high 8bit, shift right 8 */
    ptr[9]  = frame->left_bar & 0xff;
    ptr[10] = (frame->left_bar >> 8) & 0xff; /* get high 8bit, shift right 8 */
    ptr[11] = frame->right_bar & 0xff;
    ptr[12] = (frame->right_bar >> 8) & 0xff; /* get high 8bit, shift right 8 */
    hdmi_infoframe_checksum(buffer, length);

    return length;
}

static hi_s32 hdmi_vendor_specific_infoframe_pack(struct hdmi_vendor_specific_infoframe *frame,
    hi_void *buffer, hi_u32 size)
{
    hi_u8  *ptr = HI_NULL;
    hi_u32 length;

    hdmi_if_null_return(frame, HI_FAILURE);
    hdmi_if_null_return(buffer, HI_FAILURE);

    ptr = buffer;
    length = HDMI_INFOFRAME_HEADER_SIZE + frame->length;
    if (size < length) {
        return -1;
    }
    memset(buffer, 0, length);

    ptr[0] = frame->type;
    ptr[1] = frame->version;
    ptr[2] = frame->length;
    ptr[3] = 0; /* checksum */

    if (frame->vsif_content.h14_vsif_content.ieee == HDMI14_IEEE_OUI) { /* for HDMI 1.4 */
        hdmi_14_vsif_content *vsif_content = &frame->vsif_content.h14_vsif_content;
        /* IEEE OUI */
        ptr[4] = HDMI14_IEEE_OUI & 0xff;
        ptr[5] = (HDMI14_IEEE_OUI >> 8) & 0xff; /* get [15,8]bit, shift right 8 */
        ptr[6] = (HDMI14_IEEE_OUI >> 16) & 0xff; /* get [23,16]bit, shift right 16 */
        /* format in [7,5], shift left 5 bit */
        ptr[7] = ((hi_u8)vsif_content->format & 0x7) << 5;
        if (vsif_content->format == HDMI_VIDEO_FORMAT_4K) {
            ptr[8] = vsif_content->vic;
        } else if (vsif_content->format == HDMI_VIDEO_FORMAT_3D) {
            ptr[8] = ((hi_u8)vsif_content->_3d_structure & 0xf) << 4; /* _3d_structure in [7,4], shift left 4 bit */
        }
    }
    hdmi_infoframe_checksum(buffer, length);

    return length;
}

hi_s32 drv_hdmi_infoframe_send(hdmi_infoframe_str *infoframe, hdmi_infoframe_id infoframe_id,
                               hdmi_infoframe *info_frame)
{
    hi_u8 buffer[INFOFRAME_BUFFER_LEN] = {0};
    hdmi_device *hdmi_dev = HI_NULL;

    hdmi_if_null_return(infoframe, HI_FAILURE);
    hdmi_if_null_return(info_frame, HI_FAILURE);

    hdmi_dev = HDMI_CONTAINER_OF(infoframe, __typeof__(*hdmi_dev), infoframe);
    hdmi_if_null_return(hdmi_dev, HI_FAILURE);

    /* pack infoframe */
    switch (infoframe_id) {
        case HDMI_INFOFRAME_TYPE_VENDOR: {
            info_frame->vendor_infoframe.type    = HDMI_INFOFRAME_TYPE_VENDOR;
            info_frame->vendor_infoframe.version = 1;
            info_frame->vendor_infoframe.length  = 0x07;
            hdmi_vendor_specific_infoframe_pack(&info_frame->vendor_infoframe, buffer, INFOFRAME_BUFFER_LEN);
            break;
        }
        case HDMI_INFOFRAME_TYPE_AVI: {
            info_frame->avi_infoframe.type      = HDMI_INFOFRAME_TYPE_AVI;
            info_frame->avi_infoframe.version   = 2; /* avi infoframe versio 2 */
            info_frame->avi_infoframe.length    = 13; /* avi infoframe length 13 */
            hdmi_avi_infoframe_pack(&info_frame->avi_infoframe, buffer,
                INFOFRAME_BUFFER_LEN, hdmi_dev->attr.vo_attr.stereo_mode);
            break;
        }
        case HDMI_INFOFRAME_TYPE_AUDIO: {
            break;
        }
        default:
            return HI_FAILURE;
    }

    drv_hdmi_infoframe_enable_set(infoframe, infoframe_id, HI_FALSE);
    hal_call_void(hal_hdmi_infoframe_set, hdmi_dev->hal, infoframe_id, buffer);
    drv_hdmi_infoframe_enable_set(infoframe, infoframe_id, HI_TRUE);

    return HI_SUCCESS;
}

hi_s32 drv_hdmi_infoframe_enable_set(hdmi_infoframe_str *infoframe, hdmi_infoframe_id infoframe_id, hi_bool enable)
{
    hdmi_device *hdmi_dev = HI_NULL;

    hdmi_if_null_return(infoframe, HI_FAILURE);
    hdmi_dev = HDMI_CONTAINER_OF(infoframe, __typeof__(*hdmi_dev), infoframe);
    hal_call_void(hal_hdmi_infoframe_enable_set, hdmi_dev->hal, infoframe_id, enable);

    return HI_SUCCESS;
}

hi_s32 drv_hdmi_avi_infoframe_send(hdmi_infoframe_str *infoframe, hi_bool enable)
{
    hdmi_infoframe info_frame = {0};
    hdmi_device *hdmi_dev = HI_NULL;
    hdmi_vo_attr *vo_attr = HI_NULL;
    hdmi_app_attr *app_attr = HI_NULL;
    hdmi_avi_infoframe *avi_infoframe = HI_NULL;

    hdmi_if_null_return(infoframe, HI_FAILURE);

    if (enable == HI_FALSE) {
        drv_hdmi_infoframe_enable_set(infoframe, HDMI_INFOFRAME_TYPE_AVI, HI_FALSE);
        return HI_SUCCESS;
    }

    hdmi_dev = HDMI_CONTAINER_OF(infoframe, __typeof__(*hdmi_dev), infoframe);
    hdmi_if_null_return(hdmi_dev, HI_FAILURE);

    vo_attr  = &hdmi_dev->attr.vo_attr;
    app_attr = &hdmi_dev->attr.app_attr;
    avi_infoframe = &infoframe->avi_infoframe;
    memset(avi_infoframe, 0, sizeof(hdmi_avi_infoframe));
    avi_infoframe->disp_fmt               = vo_attr->disp_fmt;
    avi_infoframe->video_timing           = vo_attr->video_timing;
    avi_infoframe->picture_aspect         = vo_attr->picture_aspect;
    avi_infoframe->active_aspect          = vo_attr->active_aspect;
    avi_infoframe->nups                   = vo_attr->picture_scaling;
    avi_infoframe->pixel_repeat           = vo_attr->pixel_repeat;
    avi_infoframe->active_info_valid      = HI_TRUE;
    avi_infoframe->horizontal_bar_valid   = HI_FALSE;
    avi_infoframe->vertical_bar_valid     = HI_FALSE;
    avi_infoframe->scan_mode              = HDMI_SCAN_MODE_NONE;
    avi_infoframe->itc                    = HI_FALSE;
    avi_infoframe->content_type           = HDMI_CONTENT_TYPE_NONE;
    avi_infoframe->top_bar                = 0;
    avi_infoframe->bottom_bar             = 0;
    avi_infoframe->left_bar               = 0;
    avi_infoframe->right_bar              = 0;
    avi_infoframe->extended_colorimetry   = vo_attr->extended_colorimetry;
    avi_infoframe->quantization_range     = vo_attr->rgb_quantization;
    avi_infoframe->ycc_quantization_range = vo_attr->ycc_quantization;
    avi_infoframe->colorspace             = app_attr->out_colorspace;
    avi_infoframe->colorimetry            = app_attr->bxv_ycc_mode ? HDMI_COLORIMETRY_EXTENDED : vo_attr->colorimetry;
    memcpy(&info_frame.avi_infoframe, avi_infoframe, sizeof(hdmi_avi_infoframe));
    drv_hdmi_infoframe_send(infoframe, HDMI_INFOFRAME_TYPE_AVI, &info_frame);

    return HI_SUCCESS;

}

hi_s32 drv_hdmi_vendor_infoframe_send(hdmi_infoframe_str *infoframe, hi_bool enable)
{
    hi_u32 vic;
    hdmi_infoframe info_frame = {0};
    hdmi_vo_attr *vo_attr = HI_NULL;
    hdmi_device *hdmi_dev = HI_NULL;
    hdmi_14_vsif_content *h14_vsif_content = HI_NULL;
    hdmi_vendor_infoframe *vendor_infoframe = HI_NULL;
    hi_bool vendor_infoframe_enable = HI_FALSE;

    hdmi_if_null_return(infoframe, HI_FAILURE);
    if (enable == HI_FALSE) {
        drv_hdmi_infoframe_enable_set(infoframe, HDMI_INFOFRAME_TYPE_VENDOR, HI_FALSE);
        return HI_SUCCESS;
    }
    hdmi_dev = HDMI_CONTAINER_OF(infoframe, __typeof__(*hdmi_dev), infoframe);
    hdmi_if_null_return(hdmi_dev, HI_FAILURE);

    vo_attr  = &hdmi_dev->attr.vo_attr;
    vendor_infoframe = &infoframe->vendor_infoframe;
    memset(vendor_infoframe, 0, sizeof(hdmi_vendor_infoframe));

    h14_vsif_content = &vendor_infoframe->vsif_content.h14_vsif_content;
    vic = drv_hdmi_vic_search(vo_attr->video_timing, vo_attr->picture_aspect, HI_FALSE); /* find the real Vic */
    if (((vic >= HDMI_3840X2160P24_16_9 && vic <= HDMI_3840X2160P30_16_9) ||
        vic == HDMI_4096X2160P24_256_135) && vo_attr->stereo_mode == HDMI_3D_BUTT) {
        hi_u32 cnt;
        h14_vsif_content->ieee   = HDMI14_IEEE_OUI;
        h14_vsif_content->format = HDMI_VIDEO_FORMAT_4K;
        h14_vsif_content->vic    = 0;
        for (cnt = 0; cnt < 4; cnt++) {
            if (g_h14b_hdmi_video_codes_4k[cnt].timing == vo_attr->video_timing) {
                h14_vsif_content->vic = g_h14b_hdmi_video_codes_4k[cnt].hdmi_vic;   /* HDMI_VIC */
                break;
            }
        }
        vendor_infoframe_enable = HI_TRUE;
    } else if (vo_attr->stereo_mode < HDMI_3D_BUTT)   /* common 3D */  {
        h14_vsif_content->ieee = HDMI14_IEEE_OUI;
        h14_vsif_content->format = HDMI_VIDEO_FORMAT_3D;
        h14_vsif_content->_3d_structure = vo_attr->stereo_mode;
        vendor_infoframe_enable = HI_TRUE;
    } else {
        h14_vsif_content->ieee = HDMI14_IEEE_OUI;
        h14_vsif_content->format = HDMI_VIDEO_FORMAT_NONE;
        h14_vsif_content->_3d_structure = vo_attr->stereo_mode;
        vendor_infoframe_enable = HI_TRUE;
    }
    if (vendor_infoframe_enable == HI_TRUE) {
        memcpy(&info_frame.vendor_infoframe, vendor_infoframe, sizeof(hdmi_vendor_infoframe));
        drv_hdmi_infoframe_send(infoframe, HDMI_INFOFRAME_TYPE_VENDOR, &info_frame);
    }

    return HI_SUCCESS;
}

