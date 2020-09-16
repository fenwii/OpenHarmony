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

#ifndef MMESSAGE_POOL_H
#define MMESSAGE_POOL_H
#include <list>
#include <string>
#include <pthread.h>
#include "message.h"

namespace OHOS {
struct MsgPrivateInfo {
    bool isReplied;
    MsgInfo *replyMsg;
    bool isCondErr;
};

class MMessagePool {
public:
    explicit MMessagePool(std::string name);
    ~MMessagePool();
    int32_t Init(uint32_t msgNum, uint32_t msgPayloadLen);
    MsgInfo *GetMsg(const MsgInfo &msg);
    int32_t PutMsg(MsgInfo &msg);
    MsgInfo *GetEmptyMsg();
    void Dump(void);

private:
    int32_t Deinit(void);
    int32_t MallocMemPool(uint32_t msgNum, uint32_t msgPayloadLen);
    void FreeMemPool(void);

private:
    std::list<MsgInfo *> m_msgFreeList;
    std::list<MsgInfo *> m_msgBusyList;
    uint32_t m_maxMsgNum = 0;
    uint32_t m_maxMsgPayloadLen = 0;
    std::string m_name;
    MsgInfo *m_msgMemList = nullptr;
    MsgPrivateInfo *m_msgPrivList = nullptr;
    uint8_t *m_msgPayloadList = nullptr;
    pthread_mutex_t m_listLock = PTHREAD_MUTEX_INITIALIZER;
    bool m_isInit = false;
};
}
#endif
