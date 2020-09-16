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

#include "upg_user_verify.h"

HI_PRV upg_user_verify_inf g_user_file_verify_inf = {HI_NULL, HI_NULL};

upg_user_verify_inf *upg_get_user_verify_inf(hi_void)
{
    return &g_user_file_verify_inf;
}

hi_u32 upg_user_define_verify(const hi_upg_user_info *info)
{
    hi_u32 ret = HI_ERR_SUCCESS;
    upg_user_verify_inf *user_inf_ctx = upg_get_user_verify_inf();

    if (user_inf_ctx->upg_file_check_fn) {
        ret = user_inf_ctx->upg_file_check_fn(info, user_inf_ctx->user_param);
    } else {
        upg_print("[upg user verify]not define \r\n");
    }

    if (ret != HI_ERR_SUCCESS) {
        upg_print("[upg user verify]check ret:0x%x \r\n", ret);
        return HI_ERR_UPG_USER_VERIFY;
    }

    return HI_ERR_SUCCESS;
}

hi_u32 hi_upg_register_file_verify_fn(
    hi_u32 (*upg_file_check_fn)(const hi_upg_user_info *info, hi_void *param),
    hi_void *param)
{
    upg_user_verify_inf *user_info_ctx = upg_get_user_verify_inf();

    if (!hi_is_valid_code_addr((uintptr_t)upg_file_check_fn)) {
        return HI_ERR_UPG_PARAMETER;
    }
    user_info_ctx->upg_file_check_fn = upg_file_check_fn;
    user_info_ctx->user_param        = param;
    return HI_ERR_SUCCESS;
}
