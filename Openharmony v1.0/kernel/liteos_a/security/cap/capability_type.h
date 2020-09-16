/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CAPABILITY_TYPE_H
#define CAPABILITY_TYPE_H

// posix capabilities
#define CAP_CHOWN                       0
#define CAP_DAC_EXECUTE                 1
#define CAP_DAC_WRITE                   2
#define CAP_DAC_READ_SEARCH             3
#define CAP_FOWNER                      4
#define CAP_KILL                        5
#define CAP_SETGID                      6
#define CAP_SETUID                      7

// socket capabilities
#define CAP_NET_BIND_SERVICE            8
#define CAP_NET_BROADCAST               9
#define CAP_NET_ADMIN                   10
#define CAP_NET_RAW                     11

// fs capabilities
#define CAP_FS_MOUNT                    12
#define CAP_FS_FORMAT                   13

// process capabilities
#define CAP_SCHED_SETPRIORITY           14

// time capabilities
#define CAP_SET_TIMEOFDAY               15
#define CAP_CLOCK_SETTIME               16

// process capabilities
#define CAP_CAPSET                      17

// reboot capability
#define CAP_REBOOT                      18
// self deined privileged syscalls
#define CAP_SHELL_EXEC                  19
#endif