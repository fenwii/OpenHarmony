/* Copyright 2020 Huawei Device Co., Ltd.
 *
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

#include <string.h>
#include "hdf_log.h"
#include "osal_mem.h"
#include "uart_if.h"

#define HDF_LOG_TAG "hello_uart_dispatch"
#define UART_PORT 5

int main()
{
    const char *info = " HELLO UART! ";

    struct DevHandle *handle = UartOpen(UART_PORT);
    if (handle == NULL) {
        HDF_LOGE("Failed to open uart %d", UART_PORT);
        return HDF_FAILURE;
    }

    int ret = UartWrite(handle, (uint8_t *)info, strlen(info));
    if (ret != HDF_SUCCESS) {
        HDF_LOGE("Failed to send data to uart");
    }

    UartClose(handle);
    return ret;
}