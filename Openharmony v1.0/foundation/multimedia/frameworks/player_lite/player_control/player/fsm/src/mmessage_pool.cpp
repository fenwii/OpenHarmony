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

#include "mmessage_pool.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>

#include "securec.h"
#include "fsm_common.h"
#include "media_log.h"

using namespace OHOS;

const char DEFAULT_MSG_ID = -1;

MMessagePool::MMessagePool(std::string name) : m_name(name)
{
    m_msgFreeList.clear();
    m_msgBusyList.clear();
}

MMessagePool::~MMessagePool()
{
    Deinit();
}

int32_t MMessagePool::Init(uint32_t msgNum, uint32_t msgPayloadLen)
{
    if (m_isInit == true) {
        MEDIA_ERR_LOG("MMessagePool has inited");
        return HI_SUCCESS;
    }
    if (msgNum == 0 || msgPayloadLen == 0) {
        MEDIA_ERR_LOG("msgpool init msgNum or msgPayloadLen 0 err");
        return HI_FAILURE;
    }
    if ((msgNum >= (INT_MAX / msgPayloadLen)) || (msgNum >= (INT_MAX / sizeof(MsgInfo))) ||
        (msgNum >= (INT_MAX / sizeof(MsgPrivateInfo)))) {
        MEDIA_ERR_LOG("interger malloc overflow");
        return HI_FAILURE;
    }
    if (pthread_mutex_init(&m_listLock, nullptr) != HI_SUCCESS) {
        MEDIA_ERR_LOG("pthread_mutex_init err");
        return HI_FAILURE;
    }

    if (MallocMemPool(msgNum, msgPayloadLen) != HI_SUCCESS) {
        MEDIA_ERR_LOG("MallocMemPool err");
        (void)pthread_mutex_destroy(&m_listLock);
        return HI_FAILURE;
    }

    for (uint32_t i = 0; i < msgNum; i++) {
        m_msgMemList[i].msgData = (msgPayloadLen > 0) ?
            static_cast<void *>(&m_msgPayloadList[i * msgPayloadLen]) : nullptr;
        m_msgMemList[i].privDate = static_cast<void *>(&m_msgPrivList[i]);
        m_msgMemList[i].what = DEFAULT_MSG_ID;
        m_msgFreeList.push_back(&m_msgMemList[i]);
    }

    m_maxMsgNum = msgNum;
    m_maxMsgPayloadLen = msgPayloadLen;
    m_isInit = true;
    return HI_SUCCESS;
}

int32_t MMessagePool::Deinit()
{
    if (m_isInit != true) {
        MEDIA_INFO_LOG( "MMessagePool not inited");
        return HI_SUCCESS;
    }
    if (!m_msgBusyList.empty()) {
        MEDIA_ERR_LOG(
                      "pool: %s: %d msgs not released", m_name.c_str(), (uint32_t)m_msgBusyList.size());
    }

    if (m_msgFreeList.size() != m_maxMsgNum) {
        MEDIA_ERR_LOG("free msg size not same with inited");
    }

    std::list<MsgInfo *>::iterator msgIter = m_msgFreeList.begin();
    while (msgIter != m_msgFreeList.end()) {
        msgIter = m_msgFreeList.erase(msgIter);
    }
    m_msgFreeList.clear();
    m_msgBusyList.clear();
    FreeMemPool();
    (void)pthread_mutex_destroy(&m_listLock);
    m_isInit = false;
    return HI_SUCCESS;
}

MsgInfo *MMessagePool::GetEmptyMsg()
{
    MsgInfo *msg = nullptr;

    FSM_LOCK(m_listLock);

    std::list<MsgInfo *>::iterator msgIter = m_msgFreeList.begin();
    if (msgIter != m_msgFreeList.end()) {
        msg = *msgIter;
        m_msgFreeList.erase(msgIter);
    }

    if (msg == nullptr || msg->privDate == nullptr) {
        MEDIA_ERR_LOG("getMsg failed, msg pool is empty");
        FSM_UNLOCK(m_listLock);
        return nullptr;
    }
    if (msg->privDate == nullptr) {
        MEDIA_ERR_LOG("msg->privDate is NULL");
        FSM_UNLOCK(m_listLock);
        return nullptr;
    }
    if (memset_s(msg->privDate, sizeof(MsgPrivateInfo), 0x00, sizeof(MsgPrivateInfo)) != EOK) {
        MEDIA_ERR_LOG("memset failed");
        FSM_UNLOCK(m_listLock);
        return nullptr;
    }
    msg->what = DEFAULT_MSG_ID;
    msg->msgDataLen = m_maxMsgPayloadLen;

    m_msgBusyList.push_back(msg);

    FSM_UNLOCK(m_listLock);

    return msg;
}

MsgInfo *MMessagePool::GetMsg(const MsgInfo &msg)
{
    MsgInfo *msgInfo = nullptr;

    if (msg.msgDataLen > m_maxMsgPayloadLen) {
        MEDIA_ERR_LOG("getMsg input msg len: %d large than maxlen: %d",
                      msg.msgDataLen, m_maxMsgPayloadLen);
        return nullptr;
    }

    FSM_LOCK(m_listLock);

    std::list<MsgInfo *>::iterator msgIter = m_msgFreeList.begin();
    if (msgIter != m_msgFreeList.end()) {
        msgInfo = *msgIter;

        if (msgInfo->privDate == nullptr ||
            memset_s(msgInfo->privDate, sizeof(MsgPrivateInfo), 0x00, sizeof(MsgPrivateInfo)) != EOK) {
            MEDIA_ERR_LOG("memset_s failed");
            FSM_UNLOCK(m_listLock);
            return nullptr;
        }

        msgInfo->what = msg.what;
        msgInfo->arg1 = msg.arg1;
        msgInfo->arg2 = msg.arg2;

        if (msg.msgDataLen > 0 && msg.msgData != nullptr && msgInfo->msgData != nullptr) {
            if (memcpy_s(msgInfo->msgData, m_maxMsgPayloadLen, msg.msgData, msg.msgDataLen) != EOK) {
                MEDIA_ERR_LOG("memset_s failed");
                FSM_UNLOCK(m_listLock);
                return nullptr;
            }
            msgInfo->msgDataLen = msg.msgDataLen;
        }

        m_msgFreeList.erase(msgIter);
    }

    if (msgInfo == nullptr) {
        MEDIA_ERR_LOG("pool: %s is empty, left size: %zd busy size: %zd",
            m_name.c_str(), m_msgFreeList.size(), m_msgBusyList.size());
        FSM_UNLOCK(m_listLock);
        return nullptr;
    }

    m_msgBusyList.push_back(msgInfo);

    FSM_UNLOCK(m_listLock);

    return msgInfo;
}

int32_t MMessagePool::PutMsg(MsgInfo &msg)
{
    bool isFound = false;

    FSM_LOCK(m_listLock);

    std::list<MsgInfo *>::iterator msgIter = m_msgBusyList.begin();
    for (; msgIter != m_msgBusyList.end(); msgIter++) {
        MsgInfo *msgInfo = *msgIter;
        if (msgInfo == &msg) {
            isFound = true;
            break;
        }
    }

    if (!isFound) {
        MEDIA_ERR_LOG("pool: %s putMsg invalid msg", m_name.c_str());
        FSM_UNLOCK(m_listLock);
        return HI_FAILURE;
    }

    m_msgBusyList.erase(msgIter);

    msg.what = DEFAULT_MSG_ID;

    m_msgFreeList.push_back(&msg);

    FSM_UNLOCK(m_listLock);
    return HI_SUCCESS;
}

void MMessagePool::Dump()
{
    FSM_LOCK(m_listLock);
    MEDIA_INFO_LOG( "pool: %s, free msg: %zd, busy msg: %zd",
        m_name.c_str(), m_msgFreeList.size(), m_msgBusyList.size());
    std::list<MsgInfo *>::iterator msgIter = m_msgBusyList.begin();
    for (; msgIter != m_msgBusyList.end(); msgIter++) {
        MEDIA_INFO_LOG( "msg id: %d", (*msgIter)->what);
    }
    FSM_UNLOCK(m_listLock);
}

int32_t MMessagePool::MallocMemPool(uint32_t msgNum, uint32_t msgPayloadLen)
{
    m_msgPayloadList = static_cast<uint8_t *>(malloc(msgPayloadLen * msgNum));
    if (m_msgPayloadList == nullptr) {
        MEDIA_ERR_LOG("alloc msg payload list size failed");
        return HI_FAILURE;
    }

    m_msgMemList = static_cast<MsgInfo *>(malloc(sizeof(MsgInfo) * msgNum));
    if (m_msgMemList == nullptr) {
        MEDIA_ERR_LOG("alloc msg list num: %u failed", msgNum);
        free(m_msgPayloadList);
        m_msgPayloadList = nullptr;
        return HI_FAILURE;
    }

    m_msgPrivList = static_cast<MsgPrivateInfo *>(malloc(sizeof(MsgPrivateInfo) * msgNum));
    if (m_msgPrivList == nullptr) {
        MEDIA_ERR_LOG("alloc msg private list num: %u failed", msgNum);
        free(m_msgMemList);
        m_msgMemList = nullptr;
        free(m_msgPayloadList);
        m_msgPayloadList = nullptr;
        return HI_FAILURE;
    }

    if (memset_s(m_msgPrivList, sizeof(MsgPrivateInfo) * msgNum, 0x00, (sizeof(MsgPrivateInfo) * msgNum)) != EOK ||
        memset_s(m_msgPayloadList, msgPayloadLen * msgNum, 0x00, (msgPayloadLen * msgNum)) != EOK ||
            memset_s(m_msgMemList, sizeof(MsgInfo) * msgNum, 0x00, (sizeof(MsgInfo) * msgNum)) != EOK) {
        MEDIA_ERR_LOG("memset_s failed");
        free(m_msgPrivList);
        m_msgPrivList = nullptr;
        free(m_msgMemList);
        m_msgMemList = nullptr;
        free(m_msgPayloadList);
        m_msgPayloadList = nullptr;
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

void MMessagePool::FreeMemPool()
{
    if (m_msgPrivList != nullptr) {
        free(m_msgPrivList);
        m_msgPrivList = nullptr;
    }

    if (m_msgPayloadList != nullptr) {
        free(m_msgPayloadList);
        m_msgPayloadList = nullptr;
    }

    if (m_msgMemList != nullptr) {
        free(m_msgMemList);
        m_msgMemList = nullptr;
    }
}
