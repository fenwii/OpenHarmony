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

#ifndef UART_IF_H
#define UART_IF_H

#include <stdint.h>

#define UART_DEV_SERVICE_NAME_PREFIX "HDF_PLATFORM_UART_%d"
#define MAX_DEV_NAME_SIZE 32

enum {
    UART_WRITE = 1
};

struct DevHandle {
    void *object;
};

struct DevHandle *UartOpen(uint32_t port);
int32_t UartWrite(struct DevHandle *handle, uint8_t *data, uint32_t size);
void UartClose(struct DevHandle *handle);

#endif // UART_IF_H