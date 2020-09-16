/*
 * ----------------------------------------------------------------------
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * ----------------------------------------------------------------------
 */

#ifndef _SYS_CAPABILITY_H
#define _SYS_CAPABILITY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/capability.h>

// posix capabilities
#define OHOS_CAP_CHOWN                       0
#define OHOS_CAP_DAC_EXECUTE                 1
#define OHOS_CAP_DAC_WRITE                   2
#define OHOS_CAP_DAC_READ_SEARCH             3
#define OHOS_CAP_FOWNER                      4
#define OHOS_CAP_KILL                        5
#define OHOS_CAP_SETGID                      6
#define OHOS_CAP_SETUID                      7

// socket capabilities
#define OHOS_CAP_NET_BIND_SERVICE            8
#define OHOS_CAP_NET_BROADCAST               9
#define OHOS_CAP_NET_ADMIN                   10
#define OHOS_CAP_NET_RAW                     11

// fs capabilities
#define OHOS_CAP_FS_MOUNT                    12
#define OHOS_CAP_FS_FORMAT                   13

// process capabilities
#define OHOS_CAP_SCHED_SETPRIORITY           14

// time capabilities
#define OHOS_CAP_SET_TIMEOFDAY               15
#define OHOS_CAP_CLOCK_SETTIME               16

// process capabilities
#define OHOS_CAP_CAPSET                      17

// reboot capability
#define OHOS_CAP_REBOOT                      18
// self deined privileged syscalls
#define OHOS_CAP_SHELL_EXEC                  19

int capget(cap_user_header_t hdr_ptr, cap_user_data_t data_ptr);
int capset(cap_user_header_t hdr_ptr, const cap_user_data_t data_ptr);
int ohos_capget(unsigned int *caps);
int ohos_capset(unsigned int caps);

#ifdef __cplusplus
}
#endif

#endif /* _SYS_CAPABILITY_H */
