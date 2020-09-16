/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
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

#ifndef IPC_MQUEUE_TEST
#define IPC_MQUEUE_TEST

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <gtest/gtest.h>

const int MQ_NAME_LEN = 64;  // mqueue name len
const int MQ_TX_LEN   = 64;  // mqueue send buffer len
const int MQ_RX_LEN   = 64;  // mqueue receive buffer len
const int MQ_MSG_SIZE = 64;	 // mqueue message size
const int MQ_MSG_PRIO = 0;   // mqueue message priority
const int MQ_MAX_MSG  = 16;	 // mqueue message number

const char MQ_MSG[] = "MessageToSend";  // mqueue message to send
const int MQ_MSG_LEN = sizeof(MQ_MSG);  // mqueue message len to send

class IpcMqTest : public::testing::Test {
};

#endif