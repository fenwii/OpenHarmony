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

#ifndef HI_FINITE_STATEMACHINE_H
#define HI_FINITE_STATEMACHINE_H

#include <stdint.h>
#include "message.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

const uint8_t MAX_STATE_NAME_LEN = 64;

typedef int32_t (*HI_FSM_StateHandleEvent)(void *priv, const MsgInfo *msg);

typedef int32_t (*HI_FSM_StateEnter)(const void *priv, const char *stateName);

typedef int32_t (*HI_FSM_StateExit)(const void *priv, const char *stateName);

typedef int32_t (*HI_FSM_EventCallback)(const void *stateMachine, const void *priv, int32_t event, int32_t retVal);

typedef struct HiFsmState {
    char stateName[MAX_STATE_NAME_LEN];
    HI_FSM_StateHandleEvent handlerCallback;
    HI_FSM_StateEnter enterCallback;
    HI_FSM_StateExit exitCallback;
    void *priv;
} HiFsmState;

typedef struct HiFsmStateTrans {
    int32_t msgType;
    HiFsmState *srcState;
    HiFsmState *destState;
} HiFsmStateTrans;

int32_t HI_FSM_Create(void **stateMachine, uint32_t maxQueueSize, uint32_t msgPayloadLen,
                      const char *fsmName);

int32_t HI_FSM_Destroy(void *stateMachine);

int32_t HI_FSM_AddState(void *stateMachine, const HiFsmState *state);

int32_t HI_FSM_AddTransition(void *stateMachine, const HiFsmStateTrans *stateTrans);

int32_t HI_FSM_RegMsgCallback(void *stateMachine, HI_FSM_EventCallback eventCallback, void *priv);

int32_t HI_FSM_SetInitState(void *stateMachine, const HiFsmState *state);

int32_t HI_FSM_Start(void *stateMachine);

int32_t HI_FSM_Stop(void *stateMachine);

int32_t HI_FSM_GetCurrentState(void *stateMachine, char stateName[MAX_STATE_NAME_LEN]);

int32_t HI_FSM_SendAsync(void *stateMachine, const MsgInfo *msg, uint64_t delayUs);

int32_t HI_FSM_SendSync(void *stateMachine, const MsgInfo *msg, const MsgInfo *replyMsg);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  // __HI_FINITE_STATEMACHINE_H__
