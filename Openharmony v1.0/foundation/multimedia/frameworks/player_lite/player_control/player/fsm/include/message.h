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

#ifndef FSM_MESSAGE_H
#define FSM_MESSAGE_H

typedef void (*MsgCallback)(void *privDate);

typedef struct MsgInfo {
    int32_t what;
    uint32_t arg1;
    uint32_t arg2;
    void *msgData;
    uint32_t msgDataLen;

    // below is private info,do not change outside
    bool isNeedReply;
    MsgCallback msgCallback;
    void *privDate;
} MsgInfo;

#endif  // __FSM_MESSAGE_H__