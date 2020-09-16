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

#ifndef _APP_DEMO_UPG_VERIFY_H_
#define _APP_DEMO_UPG_VERIFY_H_

#include <hi_upg_api.h>

#define HI_APP_CHIP_PRODUCT_LEN 8 /* 8: chip product length */

typedef struct {
    hi_char chip_product[HI_APP_CHIP_PRODUCT_LEN];
    hi_u8 reserved[24]; /* 24 bytes reserved */
}app_upg_user_info;

hi_u32 app_demo_upg_init(hi_void);

#endif /* _APP_DEMO_UPG_VERIFY_H_ */

