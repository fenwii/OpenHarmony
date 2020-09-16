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

#ifndef DATA_BUS_ERROR_H
#define DATA_BUS_ERROR_H

enum DataBusError {
    DBE_SUCCESS = 0,
    DBE_FIRST = 300,

    DBE_BAD_PARAM = DBE_FIRST + 0,
    DBE_LISTENER_OPENED = DBE_FIRST + 1,
    DBE_LISTENER_CLOSED = DBE_FIRST + 2,
    DBE_NAME_EXISTED = DBE_FIRST + 3,
    DBE_NO_PIPE_NAME = DBE_FIRST + 4,
    DBE_OPEN_SOCKET = DBE_FIRST + 5,
    DBE_BIND_SOCKET = DBE_FIRST + 6,
    DBE_CONNECT_SOCKET = DBE_FIRST + 7,
    DBE_INIT_CTRL = DBE_FIRST + 8,
    DBE_LISTEN_FD = DBE_FIRST + 9,
    DBE_CREATE_THREAD = DBE_FIRST + 10,
    DBE_JOIN_THREAD = DBE_FIRST + 11,
    DBE_SEND_MSG = DBE_FIRST + 12,
    DBE_RECV_MSG = DBE_FIRST + 13,
    DBE_BAD_MSG = DBE_FIRST + 14,
    DBE_ALREADY_STARTED = DBE_FIRST + 15,
    DBE_SESSION_NOT_EXIST = DBE_FIRST + 20,
    DBE_SESSION_OPEN = DBE_FIRST + 21,
    DBE_BUS_LISTENER = DBE_FIRST + 22,
    DBE_BUS_SERVICE = DBE_FIRST + 23,
    DBE_BUS_CREATE = DBE_FIRST + 24,
    DBE_RELEASE_FAILED = DBE_FIRST + 25,
    DBE_EPOLL_CREATE = DBE_FIRST + 26,
    DBE_ADD_SESSION = DBE_FIRST + 27,
    DBE_NO_MEMORY = DBE_FIRST + 28,
    DBE_BAD_IP = DBE_FIRST + 29,
    DBE_INIT_LISTEN = DBE_FIRST + 30,
    DBE_SEND_PACKET_FAIL = DBE_FIRST + 31,
    DBE_NOTIFY_FAIL = DBE_FIRST + 32,
    DBE_ACCEPT_SESSION_FAIL = DBE_FIRST + 33,
    DBE_RESP_ERROR = DBE_FIRST + 34,
    DBE_BAD_REPLY_SEQ = DBE_FIRST + 35,
    DBE_VERSION_REJECTED = DBE_FIRST + 36,
    DBE_TRANSACT_FAIL = DBE_FIRST + 37,
    DBE_DUP_FD_FAIL = DBE_FIRST + 38,

    DBE_LISTEN_FAIL = DBE_FIRST + 41,
    DBE_GET_SOCKET_PORT = DBE_FIRST + 42,
    DBE_START_LISTENER = DBE_FIRST + 43,
    DBE_BIND_TO_DEVICE = DBE_FIRST + 44,

    DBE_AES_CALC_ERROR = DBE_FIRST + 100,
    DBE_INNER_ERROR = DBE_FIRST + 150,
};

#endif // DATA_BUS_ERROR_H
