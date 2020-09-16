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

#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include <sys/types.h>
#include <sys/uio.h>

int OpenTcpServer(const char *ip, uint16_t port);
int GetSockPort(int fd);
int TcpSendData(int fd, const char *buf, int len, int timeout);
int TcpRecvData(int fd, char *buf, int len, int timeout);
void CloseFd(int fd);
void ShutDown(int fd);

#endif // TCP_SOCKET_H
