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

#include "vou_coef_org.h"

/* RGB->YUV601 */
const vo_csc_coef g_csc_rgb_to_yuv601_pc = {
    /* csc coef */
    299, 587, 114, -172, -339, 511, 511, -428, -83,
    /* csc(IDC) */
    0, 0, 0,
    /* csc(ODC) */
    0, 128, 128,
};

/* RGB->YUV709 */
const vo_csc_coef g_csc_rgb_to_yuv709_pc = {
    /* csc coef */
    213, 715, 72, -117, -394, 511, 511, -464, -47,
    /* csc(IDC) */
    0, 0, 0,
    /* csc(ODC) */
    0, 128, 128,
};

/* YUV601->RGB */
const vo_csc_coef g_csc_yuv601_to_rgb_pc = {
    /* csc */
    1164, 0, 1596, 1164, -391, -813, 1164, 2018, 0,
    /* csc(IDC) */
    -16, -128, -128,
    /* csc(ODC) */
    0, 0, 0,
};

/* YUV709->RGB */
const vo_csc_coef g_csc_yuv709_to_rgb_pc = {
    /* csc */
    1164, 0, 1793, 1164, -213, -534, 1164, 2115, 0,
    /* csc(IDC) */
    -16, -128, -128,
    /* csc(ODC) */
    0, 0, 0,
};

/* YUV601->YUV709 */
const vo_csc_coef g_csc_yuv_to_yuv_601_709 = {
    /* csc coef */
    1000, -116, 208, 0, 1017, 114, 0, 75, 1025,
    /* csc(IDC) */
    -16, -128, -128,
    /* csc(ODC) */
    16, 128, 128,
};

/* YUV709->YUV601 */
const vo_csc_coef g_csc_yuv_to_yuv_709_601 = {
    /* csc coef */
    1000, 99, 192, 0, 990, -111, 0, -72, 983,
    /* csc(IDC) */
    -16, -128, -128,
    /* csc(ODC) */
    16, 128, 128,
};

/* YUV601->YUV709 */
const vo_csc_coef g_csc_init = {
    /* csc coef */
    1000, 0, 0, 0, 1000, 0, 0, 0, 1000,
    /* csc(IDC) */
    -16, -128, -128,
    /* csc(ODC) */
    16, 128, 128,
};

const int g_sin_table[61] = { /* 61 sin table length */
    -500, -485, -469, -454, -438, -422, -407, -391, -374, -358,
    -342, -325, -309, -292, -276, -259, -242, -225, -208, -191,
    -174, -156, -139, -122, -104, -87, -70, -52, -35, -17,
    0, 17, 35, 52, 70, 87, 104, 122, 139, 156,
    174, 191, 208, 225, 242, 259, 276, 292, 309, 325,
    342, 358, 374, 391, 407, 422, 438, 454, 469, 485,
    500
};

const int g_cos_table[61] = { /* 61 cos table length */
    866, 875, 883, 891, 899, 906, 914, 921, 927, 934,
    940, 946, 951, 956, 961, 966, 970, 974, 978, 982,
    985, 988, 990, 993, 995, 996, 998, 999, 999, 1000,
    1000, 1000, 999, 999, 998, 996, 995, 993, 990, 988,
    985, 982, 978, 974, 970, 966, 961, 956, 951, 946,
    940, 934, 927, 921, 914, 906, 899, 891, 883, 875,
    866
};

