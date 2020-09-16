/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
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

#include "app_demo_upg_verify.h"
#include <hi_early_debug.h>
#include <hi_stdlib.h>

hi_u32 app_demo_upg_check_chip_product(const hi_upg_user_info *info, hi_void *param)
{
    hi_char file_chip[HI_APP_CHIP_PRODUCT_LEN] = { 0 };
    app_upg_user_info *user_info = HI_NULL;

    hi_unref_param(param);
    if (info == HI_NULL) {
        printf("[app upg demo verify]null.");
        return HI_ERR_FAILURE;
    }
    user_info = (app_upg_user_info *)info;
    if (sprintf_s(file_chip, HI_APP_CHIP_PRODUCT_LEN, "%s", CONFIG_CHIP_PRODUCT_NAME) < 0) {
        printf("[app upg demo verify]sprintf_s error \r\n");
        return HI_ERR_FAILURE;
    }
    printf("[app upg demo verify]kernel chip product:%s \r\n", file_chip);

    if (memcmp(user_info->chip_product, file_chip, HI_APP_CHIP_PRODUCT_LEN) == EOK) {
        return HI_ERR_SUCCESS;
    }

    return HI_ERR_FAILURE;
}

hi_u32 app_demo_upg_init(hi_void)
{
    return hi_upg_register_file_verify_fn(app_demo_upg_check_chip_product, HI_NULL);
}
