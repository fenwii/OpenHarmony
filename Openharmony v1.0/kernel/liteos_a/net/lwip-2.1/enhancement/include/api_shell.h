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

#ifndef LWIP_API_SHELL_H
#define LWIP_API_SHELL_H

#include "arch/cc.h"
#include "lwip/opt.h"

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif

u32_t lwip_ifconfig(int argc, const char **argv);
u32_t lwip_arp(int argc, const char **argv);
u32_t osShellNetIfUp(int argc, const char **argv);
u32_t osShellNetIfDown(int argc, const char **argv);
u32_t osShellPing(int argc, const char **argv);
u32_t osShellTftp(int argc, const char **argv);
#if LWIP_SNTP
u32_t osShellNtpdate(int argc, const char **argv);
#endif
#if LWIP_DNS
u32_t osShellDns(int argc, const char **argv);
#endif /* LWIP_DNS */
u32_t osShellNetstat(int argc, const char **argv);
void netstat_internal(void *ctx);

#if defined (__cplusplus) && __cplusplus
}
#endif


#endif

