/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef COAP_SOCKET_H
#define COAP_SOCKET_H
#if defined(__LITEOS_M__) || defined(__LITEOS_RISCV__)
#include "lwip/sockets.h"
#else
#include <arpa/inet.h>
#endif
#include <unistd.h>
#define COAP_DEFAULT_PORT      5684

typedef struct {
    int cliendFd;
    struct sockaddr_in dstAddr;
} SocketInfo;

int GetCoapServerSocket(void);
int GetCoapClientSocket(void);
int CoapInitSocket(void);
int CoapCreatUdpClient(const struct sockaddr_in *sockAddr);
int CoapCreateUdpServer(const struct sockaddr_in *sockAddr);
int CoapSocketRecv(int socketFd, uint8_t *buffer, size_t length);
int CoapSocketSend(const SocketInfo *socket, const uint8_t *buffer, size_t length);
#define COAP_MAX_PDU_SIZE 1024
#endif
