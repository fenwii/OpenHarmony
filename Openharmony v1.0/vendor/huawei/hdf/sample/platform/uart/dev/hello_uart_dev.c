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

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "hdf_log.h"

#define HDF_LOG_TAG "hello_uart"
#define INFO_SIZE 16

int main(void)
{
    int ret;
    int fd;
    const char info[INFO_SIZE] = {" HELLO UART! "};

    fd = open("/dev/uartdev-5", O_RDWR);
    if (fd < 0) {
        HDF_LOGE("hello_uart uartdev-5 open failed %d", fd);
        return -1;
    }
    ret = write(fd, info, INFO_SIZE);
    if (ret != 0) {
        HDF_LOGE("hello_uart write uartdev-5 ret is %d", ret);
    }
    ret = close(fd);
    if (ret != 0) {
        HDF_LOGE("hello_uart uartdev-5 close failed %d", fd);
        return -1;
    }
    return ret;
}