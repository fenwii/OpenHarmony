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

#ifndef __DFX_SAL_H__
#define __DFX_SAL_H__
#include <hi_ft_nv.h>
#include <dfx_sys.h>

#define ID_DIAG_CMD_REMOTE              0x7000
#define ID_DIAG_CMD_DO_FRAME_ERR        0x7007 /* DIAG error report */

#define HI_DIAG_VER_FULL_PRODUCT_NAME_MAX_SIZE    60 /* Version Description */
#define HI_DIAG_VER_SDK_PRODUCT_NAME_MAX_SIZE     24 /* SDK Version */
#define HI_DIAG_VER_BOOT_NAME_MAX_SIZE            8
#define HI_DIAG_VER_FULL_HW_INFO_MAX_SIZE         40 /* Hardware information */
#define HI_DIAG_VER_FULL_DEV_VER_NAME_MAX_SIZE    40 /* Device information */

typedef struct {
    hi_char ver[HI_DIAG_VER_FULL_PRODUCT_NAME_MAX_SIZE];
    hi_char sdk_ver[HI_DIAG_VER_SDK_PRODUCT_NAME_MAX_SIZE];
    hi_char dev[HI_DIAG_VER_FULL_DEV_VER_NAME_MAX_SIZE];
    hi_char hw[HI_DIAG_VER_FULL_HW_INFO_MAX_SIZE];
    hi_char boot_ver[HI_DIAG_VER_BOOT_NAME_MAX_SIZE];
} diag_cmd_soft_new_ver;

#define HI_SYS_ERR_SIGNATURE     hi_make_identifier('s', 'y', 's', 'E')

typedef struct {
    hi_u32 id;
} hi_dbg_stat_q;

#endif /* __DFX_SAL_H__ */

