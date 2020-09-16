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

#ifndef UART_DEV_SAMPLE_H
#define UART_DEV_SAMPLE_H

#include "sys/ioctl.h"
#include "uart_core.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define UART_IOC_MAGIC   'u'

/* baudrate config */
#define UART_CFG_BAUDRATE _IO(UART_IOC_MAGIC, 1)

void UartSampleAddDev(struct UartHost *host);
void UartSampleRemoveDev(struct UartHost *host);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* UART_DEV_SAMPLE_H */
