/*
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
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

#include "hi_stdlib.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "app_http_client.h"
#define HTTPC_DEMO_RECV_BUFSIZE 64
#define SOCK_TARGET_PORT  80

static const char *g_request = "GET / HTTP/1.1\r\n\
Content-Type: application/x-www-form-urlencoded;charset=UTF-8\r\n\
Host: baidu.com\r\n\
Connection: close\r\n\
\r\n";

/*****************************************************************************
* Func description: demo for http get action
*****************************************************************************/
unsigned int http_clienti_get(int argc, const char *argv[])
{
    if ((argc != 1) || (argv == NULL)) {
        return 1;
    }
    struct sockaddr_in addr = {0};
    int s, r;
    char recv_buf[HTTPC_DEMO_RECV_BUFSIZE];
    addr.sin_family = AF_INET;
    addr.sin_port = PP_HTONS(SOCK_TARGET_PORT);
    addr.sin_addr.s_addr = inet_addr(argv[0]);
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        return 1;
    }
    printf("... allocated socket");
    if (connect(s, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
        printf("... socket connect failed errno=%d", errno);
        lwip_close(s);
        return 1;
    }
    printf("... connected");
    if (lwip_write(s, g_request, strlen(g_request)) < 0) {
        lwip_close(s);
        return 1;
    }
    printf("... socket send success");
    struct timeval receiving_timeout;
    /* 5S Timeout */
    receiving_timeout.tv_sec = 5;
    receiving_timeout.tv_usec = 0;
    if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &receiving_timeout, sizeof(receiving_timeout)) < 0) {
        printf("... failed to set socket receiving timeout");
        lwip_close(s);
        return 1;
    }
    printf("... set socket receiving timeout success");
    /* Read HTTP response */
    do {
        (void)memset_s(recv_buf, sizeof(recv_buf), 0, sizeof(recv_buf));
        r = lwip_read(s, recv_buf, sizeof(recv_buf) - 1);
        for (int i = 0; i < r; i++) {
            putchar(recv_buf[i]);
        }
    } while (r > 0);
    printf("... done reading from socket. Last read return=%d errno=%d\r\n", r, errno);
    lwip_close(s);
    return 0;
}

