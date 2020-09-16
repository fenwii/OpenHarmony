/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "init_read_cfg.h"
#include "init_signal_handler.h"
#include "parameter.h"

static void PrintSysInfo()
{
    char* sysInfo = GetVersionId();
    if (sysInfo != NULL) {
        printf("[Init] %s\n", sysInfo);
        free(sysInfo);
        sysInfo = NULL;
        return;
    }
    printf("[Init] main, GetVersionId failed!\n");
}

int main(int argc, char * const argv[])
{
    // 1. print system info
    PrintSysInfo();

    // 2. signal register
    SignalInitModule();

    // 3. read configuration file and do jobs
    InitReadCfg();

    // 4. keep process alive
    printf("[Init] main, entering wait.\n");
    while (1) {
        // pause only returns when a signal was caught and the signal-catching function returned.
        // pause only returns -1, no need to process the return value.
        (void)pause();
    }
    return 0;
}
