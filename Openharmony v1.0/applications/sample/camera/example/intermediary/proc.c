/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <unistd.h>
#include <securec.h>
#include "samgr_lite.h"
const char FUN_ARG_S[] = "0123456I";
#define DEFAULT 0
#define MAX_LEN 0x100
void __attribute__((weak)) OHOS_SystemInit(void)
{
    SAMGR_Bootstrap();
};
void HiLogPrintf(unsigned char module, unsigned char level, const char *nums, const char *fmt, ...);

int main()
{
    HiLogPrintf(DEFAULT, DEFAULT, NULL, "Start Server System Start");
    OHOS_SystemInit();
    HiLogPrintf(DEFAULT, DEFAULT, NULL, "Start Server System End");
    pause();
}
void __attribute__((weak)) HiLogPrintf(unsigned char module, unsigned char level,
                                       const char *nums, const char *fmt, ...)
{
    static char buf[MAX_LEN] = {0};
    va_list args;
    va_start(args, fmt);
    int ret = vsprintf_s(buf, sizeof(buf), fmt, args);
    va_end(args);
    if (ret < 0) {
        printf("Server fmt failed(%d)", ret);
    }
    printf("Server M:%d l:%d %s\n", module, level, buf);
}
