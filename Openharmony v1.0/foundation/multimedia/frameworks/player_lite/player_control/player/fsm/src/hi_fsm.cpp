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

#include "hi_fsm.h"

#include <cstdio>
#include <cstdlib>
#include "securec.h"
#include <unistd.h>
#include <cstring>
#include <pthread.h>
#include "fsm_common.h"
#include "fsm_state.h"
#include "hi_state_machine.h"
#include "fsm_oberver.h"
#include "media_log.h"

using OHOS::HiStateMachine;
using OHOS::FsmState;
using OHOS::HiState;
using OHOS::FsmOberver;

struct FsmInstanceCtx {
    HiStateMachine *stateMachine;
    pthread_mutex_t instanceLock;
    std::list<FsmState *> fsmStateList;
    FsmOberver *fsmOberver;
};

struct FsmContext {
    pthread_mutex_t listLock;
    std::list<FsmInstanceCtx *> fsmInstanceList;
};

static FsmContext g_fsmContext = {
    PTHREAD_MUTEX_INITIALIZER,
};

static bool FsmCheckInstanceExist(FsmInstanceCtx &fsmInstance)
{
    FSM_LOCK(g_fsmContext.listLock);
    std::list<FsmInstanceCtx *>::iterator msgIter = g_fsmContext.fsmInstanceList.begin();

    for (; msgIter != g_fsmContext.fsmInstanceList.end(); msgIter++) {
        if (&fsmInstance == *msgIter) {
            FSM_UNLOCK(g_fsmContext.listLock);
            return true;
        }
    }
    FSM_UNLOCK(g_fsmContext.listLock);
    return false;
}

static void FsmAddInstance(FsmInstanceCtx &fsmInstance)
{
    FSM_LOCK(g_fsmContext.listLock);

    g_fsmContext.fsmInstanceList.push_back(&fsmInstance);

    FSM_UNLOCK(g_fsmContext.listLock);
}

static void FsmDelInstance(FsmInstanceCtx &fsmInstance)
{
    FSM_LOCK(g_fsmContext.listLock);

    std::list<FsmInstanceCtx *>::iterator msgIter = g_fsmContext.fsmInstanceList.begin();

    for (; msgIter != g_fsmContext.fsmInstanceList.end(); msgIter++) {
        if (&fsmInstance == *msgIter) {
            g_fsmContext.fsmInstanceList.erase(msgIter);
            break;
        }
    }
    FSM_UNLOCK(g_fsmContext.listLock);
}

static FsmState *FsmFindState(FsmInstanceCtx &fsmInstance, const HiFsmState &state)
{
    std::list<FsmState *>::iterator msgIter = fsmInstance.fsmStateList.begin();

    for (; msgIter != fsmInstance.fsmStateList.end(); msgIter++) {
        FsmState *fsmState = *msgIter;
        std::string stateName(state.stateName);
        if (stateName == fsmState->Name()) {
            return fsmState;
        }
    }

    return nullptr;
}

int32_t HI_FSM_Create(void **stateMachine, uint32_t maxQueueSize, uint32_t msgPayloadLen, const char *fsmName)
{
    FSM_RETURN_IF_NULL(fsmName);
    FSM_RETURN_IF_NULL(stateMachine);
    auto fsmInstance = new (std::nothrow) FsmInstanceCtx();
    if (fsmInstance == nullptr) {
        MEDIA_ERR_LOG("malloc FsmInstanceCtx failed");
        return HI_FAILURE;
    }
    fsmInstance->stateMachine = nullptr;

    fsmInstance->stateMachine = new (std::nothrow) HiStateMachine();
    if (fsmInstance->stateMachine == nullptr) {
        MEDIA_ERR_LOG("create HiStateMachine  error !");
        delete fsmInstance;
        fsmInstance = nullptr;
        return HI_FAILURE;
    }
    if (fsmInstance->stateMachine->Init(maxQueueSize, msgPayloadLen, fsmName) != HI_SUCCESS) {
        MEDIA_ERR_LOG("HiStateMachine init error !");
        delete fsmInstance->stateMachine;
        fsmInstance->stateMachine = nullptr;
        delete fsmInstance;
        fsmInstance = nullptr;
        return HI_FAILURE;
    }

    fsmInstance->fsmStateList.clear();

    fsmInstance->fsmOberver = nullptr;

    (void)pthread_mutex_init(&fsmInstance->instanceLock, nullptr);

    FsmAddInstance(*fsmInstance);

    *stateMachine = static_cast<void *>(fsmInstance);
    return HI_SUCCESS;
}

int32_t HI_FSM_Destroy(void *stateMachine)
{
    FSM_RETURN_IF_NULL(stateMachine);
    FsmInstanceCtx *fsmInstance = static_cast<FsmInstanceCtx *>(stateMachine);
    FSM_RETURN_IF_HANDLE_NOT_EXIST(FsmCheckInstanceExist, *fsmInstance);
    int32_t ret = HI_SUCCESS;

    if (fsmInstance->stateMachine != nullptr) {
        ret = fsmInstance->stateMachine->Stop();
        if (ret != HI_SUCCESS) {
            MEDIA_ERR_LOG("stateMachine stop failed");
        }
        delete fsmInstance->stateMachine;
        fsmInstance->stateMachine = nullptr;
    }

    if (fsmInstance->fsmOberver != nullptr) {
        delete fsmInstance->fsmOberver;
        fsmInstance->fsmOberver = nullptr;
    }

    std::list<FsmState *>::iterator msgIter = fsmInstance->fsmStateList.begin();
    while (msgIter != fsmInstance->fsmStateList.end()) {
        FsmState *fsmState = *msgIter;
        delete fsmState;
        fsmState = nullptr;
        msgIter = fsmInstance->fsmStateList.erase(msgIter);
    }

    (void)pthread_mutex_destroy(&fsmInstance->instanceLock);

    FsmDelInstance(*fsmInstance);

    delete fsmInstance;

    return HI_SUCCESS;
}

int32_t HI_FSM_AddState(void *stateMachine, const HiFsmState *state)
{
    FSM_RETURN_IF_NULL(stateMachine);
    FSM_RETURN_IF_NULL(state);
    FSM_RETURN_IF_NULL(state->handlerCallback);
    FSM_RETURN_IF_NULL(state->enterCallback);
    FSM_RETURN_IF_NULL(state->exitCallback);
    FSM_RETURN_IF_NULL(state->priv);
    FsmInstanceCtx *fsmInstance = static_cast<FsmInstanceCtx *>(stateMachine);
    FSM_RETURN_IF_HANDLE_NOT_EXIST(FsmCheckInstanceExist, *fsmInstance);
    FSM_RETURN_IF_NULL(fsmInstance->stateMachine);
    std::string stateName(state->stateName);

    FSM_LOCK(fsmInstance->instanceLock);
    FsmState *fsmState = FsmFindState(*fsmInstance, *state);
    if (fsmState != nullptr) {
        MEDIA_ERR_LOG("state: %s already exist", state->stateName);
        FSM_UNLOCK(fsmInstance->instanceLock);
        return HI_FAILURE;
    }

    fsmState = new (std::nothrow) FsmState(state->handlerCallback, state->enterCallback, state->exitCallback,
        state->priv, stateName);
    if (fsmState == nullptr) {
        MEDIA_ERR_LOG("state new failed");
        FSM_UNLOCK(fsmInstance->instanceLock);
        return HI_FAILURE;
    }

    fsmInstance->fsmStateList.push_back(fsmState);
    int32_t ret = fsmInstance->stateMachine->AddState(*fsmState);
    FSM_UNLOCK(fsmInstance->instanceLock);
    return ret;
}

int32_t HI_FSM_RegMsgCallback(void *stateMachine,
    HI_FSM_EventCallback eventCallback, void *priv)
{
    FSM_RETURN_IF_NULL(stateMachine);
    FSM_RETURN_IF_NULL(eventCallback);
    FsmInstanceCtx *fsmInstance = static_cast<FsmInstanceCtx *>(stateMachine);
    FSM_RETURN_IF_HANDLE_NOT_EXIST(FsmCheckInstanceExist, *fsmInstance);
    FSM_RETURN_IF_NULL(fsmInstance->stateMachine);
    FSM_LOCK(fsmInstance->instanceLock);

    FsmOberver *observer = new (std::nothrow) FsmOberver(eventCallback, priv);
    if (observer == nullptr) {
        MEDIA_ERR_LOG("FsmOberver new failed");
        FSM_UNLOCK(fsmInstance->instanceLock);
        return HI_FAILURE;
    }
    int32_t ret = fsmInstance->stateMachine->RegisterObserver(*observer);
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("stateMachine registerObserver failed");
        delete observer;
        FSM_UNLOCK(fsmInstance->instanceLock);
        return HI_FAILURE;
    }

    if (fsmInstance->fsmOberver != nullptr) {
        delete fsmInstance->fsmOberver;
    }

    fsmInstance->fsmOberver = observer;

    FSM_UNLOCK(fsmInstance->instanceLock);

    return HI_SUCCESS;
}

int32_t HI_FSM_AddTransition(void *stateMachine, const HiFsmStateTrans *stateTrans)
{
    FSM_RETURN_IF_NULL(stateMachine);
    FSM_RETURN_IF_NULL(stateTrans);
    FSM_RETURN_IF_NULL(stateTrans->srcState);
    FSM_RETURN_IF_NULL(stateTrans->destState);
    FsmInstanceCtx *fsmInstance = static_cast<FsmInstanceCtx *>(stateMachine);
    FSM_RETURN_IF_HANDLE_NOT_EXIST(FsmCheckInstanceExist, *fsmInstance);
    FSM_LOCK(fsmInstance->instanceLock);

    FsmState *fsmSrcState = FsmFindState(*fsmInstance, *(stateTrans->srcState));
    if (fsmSrcState == nullptr) {
        MEDIA_ERR_LOG("could not find state: %s",
                      stateTrans->srcState->stateName);
        FSM_UNLOCK(fsmInstance->instanceLock);
        return HI_FAILURE;
    }

    FsmState *fsmDstState = FsmFindState(*fsmInstance, *(stateTrans->destState));
    if (fsmDstState == nullptr) {
        MEDIA_ERR_LOG("could not find state: %s ",
                      stateTrans->destState->stateName);
        FSM_UNLOCK(fsmInstance->instanceLock);
        return HI_FAILURE;
    }

    fsmSrcState->AddTransition(stateTrans->msgType, *fsmDstState);
    FSM_UNLOCK(fsmInstance->instanceLock);

    return HI_SUCCESS;
}

int32_t HI_FSM_SetInitState(void *stateMachine, const HiFsmState *state)
{
    FSM_RETURN_IF_NULL(stateMachine);
    FSM_RETURN_IF_NULL(state);

    FsmInstanceCtx *fsmInstance = static_cast<FsmInstanceCtx *>(stateMachine);
    FSM_RETURN_IF_HANDLE_NOT_EXIST(FsmCheckInstanceExist, *fsmInstance);
    FSM_RETURN_IF_NULL(fsmInstance->stateMachine);
    FSM_LOCK(fsmInstance->instanceLock);
    FsmState *fsmState = FsmFindState(*fsmInstance, *state);
    if (fsmState == nullptr) {
        MEDIA_ERR_LOG("could not find state: %s ", state->stateName);
        FSM_UNLOCK(fsmInstance->instanceLock);
        return HI_FAILURE;
    }
    int32_t ret = fsmInstance->stateMachine->SetInitialState(*fsmState);
    FSM_UNLOCK(fsmInstance->instanceLock);

    return ret;
}

int32_t HI_FSM_Start(void *stateMachine)
{
    FSM_RETURN_IF_NULL(stateMachine);
    FsmInstanceCtx *fsmInstance = static_cast<FsmInstanceCtx *>(stateMachine);
    FSM_RETURN_IF_HANDLE_NOT_EXIST(FsmCheckInstanceExist, *fsmInstance);
    FSM_RETURN_IF_NULL(fsmInstance->stateMachine);

    FSM_LOCK(fsmInstance->instanceLock);
    int32_t ret = fsmInstance->stateMachine->Start();
    FSM_UNLOCK(fsmInstance->instanceLock);

    return ret;
}

int32_t HI_FSM_Stop(void *stateMachine)
{
    FSM_RETURN_IF_NULL(stateMachine);
    FsmInstanceCtx *fsmInstance = static_cast<FsmInstanceCtx *>(stateMachine);
    FSM_RETURN_IF_HANDLE_NOT_EXIST(FsmCheckInstanceExist, *fsmInstance);
    FSM_RETURN_IF_NULL(fsmInstance->stateMachine);
    FSM_LOCK(fsmInstance->instanceLock);
    int32_t ret = fsmInstance->stateMachine->Stop();
    FSM_UNLOCK(fsmInstance->instanceLock);

    return ret;
}

int32_t HI_FSM_GetCurrentState(void *stateMachine, char stateName[MAX_STATE_NAME_LEN])
{
    FSM_RETURN_IF_NULL(stateMachine);
    FSM_RETURN_IF_NULL(stateName);
    FsmInstanceCtx *fsmInstance = static_cast<FsmInstanceCtx *>(stateMachine);
    FSM_RETURN_IF_HANDLE_NOT_EXIST(FsmCheckInstanceExist, *fsmInstance);
    FSM_RETURN_IF_NULL(fsmInstance->stateMachine);
    FSM_LOCK(fsmInstance->instanceLock);
    const HiState *state = fsmInstance->stateMachine->CurrentState();
    if (state == nullptr) {
        MEDIA_ERR_LOG("current state is NULL");
        FSM_UNLOCK(fsmInstance->instanceLock);
        return HI_FAILURE;
    }

    if (strncpy_s(stateName, MAX_STATE_NAME_LEN, state->Name().c_str(), MAX_STATE_NAME_LEN - 1) != EOK) {
        MEDIA_ERR_LOG("strncpy failed");
        FSM_UNLOCK(fsmInstance->instanceLock);
        return HI_FAILURE;
    }

    FSM_UNLOCK(fsmInstance->instanceLock);

    return HI_SUCCESS;
}

int32_t HI_FSM_SendAsync(void *stateMachine, const MsgInfo *msg, uint64_t delayUs)
{
    FSM_RETURN_IF_NULL(stateMachine);
    FSM_RETURN_IF_NULL(msg);
    FsmInstanceCtx *fsmInstance = static_cast<FsmInstanceCtx *>(stateMachine);
    FSM_RETURN_IF_HANDLE_NOT_EXIST(FsmCheckInstanceExist, *fsmInstance);
    FSM_RETURN_IF_NULL(fsmInstance->stateMachine);
    return fsmInstance->stateMachine->Post(*msg, delayUs);
}

int32_t HI_FSM_SendSync(void *stateMachine, const MsgInfo *msg, const MsgInfo *replyMsg)
{
    FSM_RETURN_IF_NULL(stateMachine);
    FSM_RETURN_IF_NULL(msg);
    FSM_RETURN_IF_NULL(replyMsg);
    FsmInstanceCtx *fsmInstance = static_cast<FsmInstanceCtx *>(stateMachine);
    FSM_RETURN_IF_HANDLE_NOT_EXIST(FsmCheckInstanceExist, *fsmInstance);
    (void)(replyMsg);
    FSM_RETURN_IF_NULL(fsmInstance->stateMachine);
    return fsmInstance->stateMachine->Send(*msg);
}
