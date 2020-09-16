/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

#ifndef __SNTP_H__
#define __SNTP_H__

#include "lwip/sntp_opts.h"
#include "arch/sys_arch.h"
#include "lwip/err.h"
#include "lwip/ip_addr.h"

#if defined (__cplusplus) && __cplusplus
extern "C" {
#endif
/*
 * SNTP operating modes: default is to poll using unicast.
 * The mode has to be set before calling sntp_init().
 */
#define SNTP_OPMODE_POLL            0
#define SNTP_OPMODE_LISTENONLY      1
void sntp_setoperatingmode(u8_t operating_mode);
u8_t sntp_getoperatingmode(void);

void sntp_init(void *arg);

u8_t sntp_enabled(void);

void sntp_setserver(u8_t idx, const ip_addr_t *addr);
const ip_addr_t *sntp_getserver(u8_t idx);

#if SNTP_SERVER_DNS
void sntp_setservername(u8_t idx, char *server);
char *sntp_getservername(u8_t idx);
#endif /* SNTP_SERVER_DNS */

#if SNTP_GET_SERVERS_FROM_DHCP
void sntp_servermode_dhcp(int set_servers_from_dhcp);
#else /* SNTP_GET_SERVERS_FROM_DHCP */
#define sntp_servermode_dhcp(x)
#endif /* SNTP_GET_SERVERS_FROM_DHCP */

/**
* @cond liteos
* @defgroup SNTP_Interfaces
* This section contains the SNTP related interfaces.
*/
/*
Func Name:  lwip_sntp_start
*/
/**
* @defgroup lwip_sntp_start
* @ingroup SNTP_Interfaces
*
* @brief
* This API is used to start the SNTP module.
*
* @param[in]    server_num   Total servers in param sntp_server [N/A]
* @param[in]    sntp_server  Domain name or IP_add of SNTP server in string format [N/A]
* @param[out]   time         the time of server if lwip_sntp_start return successfully. [N/A]
*
* @par Return values
* ERR_OK: On success\n
* ERR_MEM: On failure, due to memory error\n
* ERR_ARG: On failure, due to incorrect arg\n
* ERR_TIMEOUT: On failure, due to sntp server is not response\n
* ERR_INPROGRESS: On failure, SNTP client is already running.\n

*
* @par Note
* 1. If input parameter sntp_server passed as NULL or server_num passed as 0 to this API,
* in that case this API will fail with return value ERR_ARG. \n
* 2. This API will block for a few seconds waiting for sntp server reply.\n
* 3. If this API return successfully, and param time is not NULL,
* then 'time' will be the time obtain from sntp server.\n
* 4. This API doesn't support concurrent operation. Calling it before other operation
* done will fail with ERR_INPROGRESS.
*
* @endcond
*
*/
int lwip_sntp_start(int server_num, char **sntp_server, struct timeval *time);

#if defined (__cplusplus) && __cplusplus
}
#endif

#endif /* __SNTP_H__ */
