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

#include <unistd.h>
#include "SamgrTestBase.h"

extern "C" void __attribute__((weak)) HOS_SystemInit(void)
{
    SAMGR_Bootstrap();
};

static const int INIT_TIME = 1000;
static BOOL isInited = FALSE;
void SystemInitProxy()
{
    if (isInited == FALSE) {
        printf("[hcpptest]samgr start init.\n");
        HOS_SystemInit();

        usleep(OPER_INTERVAL * INIT_TIME);
        isInited = TRUE;
    } else {
        printf("[hcpptest]samgr already init. \n");
    }
}