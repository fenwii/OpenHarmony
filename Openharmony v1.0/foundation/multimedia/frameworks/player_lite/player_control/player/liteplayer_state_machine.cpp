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

#include "liteplayer_state_machine.h"
#include "liteplayer.h"
#include "liteplayer_comm.h"
#include "hi_liteplayer_err.h"

namespace OHOS {
namespace Media {

namespace {
    /*****************************************************************************
    status table of operation, false is not support
    *******************************************************************/
    const bool LITEPLAY_STATE[LITEPLAYER_MSG_BUTT][PLAY_STATUS_BUTT] = {
        /* idle,    init,     prepare   play,     tplay,    pause,    err */
        { false, false, true,  false, false, false, false }, /* setMedia */
        { true,  true,  true,  true,  true,  true,  true },  /* regCallbk */
        { true,  true,  false, false, false, false, false }, /* setsrc_fd */
        { true,  true,  false, false, false, false, false }, /* setsrc_uri */
        { true,  true,  false, false, false, false, false }, /* setsrc_stream */
        { false, true,  true,  false, false, false, false }, /* prepare */
        { false, false, true,  true,  true,  true,  false }, /* play */
        { false, false, false, true,  false, true,  false }, /* seek */
        { false, false, false, true,  false, true,  false }, /* pause */
        { false, false, false, true,  true,  false, false }, /* tplay */
        { true,  true,  true,  true,  true,  true,  true },  /* stop */
        { false, false, true,  true,  true,  true,  false }, /* getInfo */
        { true,  false, false, true,  true,  true,  false }, /* handledata */
        { true,  true,  true,  true,  true,  true,  true },  /* Error */
        { false,  false,  true,  true,  true,  true,  true },  /* setVolume */
    };

    struct LiteplayerStatusMap {
        PlayerStatus state;
        const std::string stateName;
    };

    const LiteplayerStatusMap LITEPLAY_STATEMAP[PLAY_STATUS_BUTT] = {
        { PLAY_STATUS_IDLE,     "idle" },
        { PLAY_STATUS_INIT,     "init" },
        { PLAY_STATUS_PREPARED, "prepare" },
        { PLAY_STATUS_PLAY,     "play" },
        { PLAY_STATUS_TPLAY,    "tplay" },
        { PLAY_STATUS_PAUSE,    "pause" },
        { PLAY_STATUS_ERR,      "error" },
    };
}

#define CHECK_NULL_RETURN(value, ret, printfString) \
do { \
    if (value == nullptr) { \
        MEDIA_ERR_LOG( "playerStateMachine %s \n", printfString ? printfString : " "); \
        return ret; \
    } \
} while (0)

PlayerStatus StateConvert2Enum(const std::string stateName)
{
    bool isFound = false;
    uint32_t i = 0;

    for (; i < PLAY_STATUS_BUTT; i++) {
        if (stateName == LITEPLAY_STATEMAP[i].stateName) {
            isFound = true;
            break;
        }
    }
    if (isFound == false) {
        MEDIA_ERR_LOG("could not find respond state :%s", stateName.c_str());
        return PLAY_STATUS_BUTT;
    }
    return LITEPLAY_STATEMAP[i].state;
}

static std::string StateEnum2Name(PlayerStatus state)
{
    return LITEPLAY_STATEMAP[state].stateName;
}

PlayerControlState::~PlayerControlState()
{
}

int PlayerControlState::Enter()
{
    PlayerStatus playerStatus = StateConvert2Enum(Name());
    CHECK_NULL_RETURN(m_liteplayerHandle, HI_ERR_LITEPLAYER_NULL_PTR, "handle null");
    m_liteplayerHandle->StateChangeCallback(playerStatus);
    MEDIA_INFO_LOG( "enter state: %s", Name().c_str());
    return HI_SUCCESS;
}

int PlayerControlState::Exit()
{
    MEDIA_INFO_LOG( "exit state: %s", Name().c_str());
    return HI_SUCCESS;
}

HiState *PlayerControlState::FindTransition(int event)
{
    HiState *dstState = HiState::FindTransition(event);
    return dstState;
}

int PlayerControlState::HandleMessage(const MsgInfo& msgInfo)
{
    int32_t ret = HI_SUCCESS;

    CHECK_NULL_RETURN(m_curState, HI_ERR_LITEPLAYER_NULL_PTR, "curState null");
    if (!m_curState->EventValidAtCurState((LiteplayerMsgType)msgInfo.what)) {
        MEDIA_ERR_LOG( "invalid event :%d at current state: %s ", msgInfo.what,
                      Name().c_str());
        return HI_ERR_LITEPLAYER_ILLEGAL_STATE_ACTION;
    }
    CHECK_NULL_RETURN(m_liteplayerHandle, HI_ERR_LITEPLAYER_NULL_PTR, "handle null");
    switch (msgInfo.what) {
        case LITEPLAYER_MSG_REGCALLBACK:
            CHECK_NULL_RETURN(msgInfo.msgData, HI_ERR_LITEPLAYER_NULL_PTR, "msgData null");
            ret = m_liteplayerHandle->DoRegCallback(*reinterpret_cast<PlayerCtrlCallbackParam *>(msgInfo.msgData));
            break;
        case LITEPLAYER_MSG_SET_DATASOURCE_URI:
            CHECK_NULL_RETURN(msgInfo.msgData, HI_ERR_LITEPLAYER_NULL_PTR, "msgData null");
            ret = m_liteplayerHandle->DoSetDataSource(*reinterpret_cast<const std::string *>(msgInfo.msgData));
            break;
        case LITEPLAYER_MSG_SET_DATASOURCE_FD:
            CHECK_NULL_RETURN(msgInfo.msgData, HI_ERR_LITEPLAYER_NULL_PTR, "msgData null");
            ret = m_liteplayerHandle->DoSetDataSource(*reinterpret_cast<const int *>(msgInfo.msgData));
            break;
        case LITEPLAYER_MSG_SET_DATASOURCE_STREAM:
            CHECK_NULL_RETURN(msgInfo.msgData, HI_ERR_LITEPLAYER_NULL_PTR, "msgData null");
            ret = m_liteplayerHandle->DoSetDataSource(*reinterpret_cast<BufferStream *>(msgInfo.msgData));
            break;
        case LITEPLAYER_MSG_SETATTR:
            CHECK_NULL_RETURN(msgInfo.msgData, HI_ERR_LITEPLAYER_NULL_PTR, "msgData null");
            ret = m_liteplayerHandle->DoSetMedia(*reinterpret_cast<PlayerControlStreamAttr *>(msgInfo.msgData));
            break;
        case LITEPLAYER_MSG_PAUSE:
            ret = m_liteplayerHandle->DoPause();
            break;
        case LITEPLAYER_MSG_TPLAY:
            CHECK_NULL_RETURN(msgInfo.msgData, HI_ERR_LITEPLAYER_NULL_PTR, "msgData null");
            ret = m_liteplayerHandle->DoTPlay(*reinterpret_cast<TplayAttr *>(msgInfo.msgData));
            break;
        case LITEPLAYER_MSG_PREPARE:
            ret = m_liteplayerHandle->DoPrepare();
            break;
        case LITEPLAYER_MSG_PLAY:
            ret = m_liteplayerHandle->DoPlay();
            break;
        case LITEPLAYER_MSG_SET_VOLUME:
            CHECK_NULL_RETURN(msgInfo.msgData, HI_ERR_LITEPLAYER_NULL_PTR, "msgData null");
            ret = m_liteplayerHandle->DoSetVolume(*reinterpret_cast<VolumeAttr *>(msgInfo.msgData));
            break;
        case LITEPLAYER_MSG_HANDLEDATA:
            ret = HI_SUCCESS;
            break;
        case LITEPLAYER_MSG_STOP:
            ret = m_liteplayerHandle->DoStop();
            break;
        case LITEPLAYER_MSG_SEEK:
            CHECK_NULL_RETURN(msgInfo.msgData, HI_ERR_LITEPLAYER_NULL_PTR, "msgData null");
            ret = m_liteplayerHandle->DoSeek(*reinterpret_cast<int64_t *>(msgInfo.msgData));
            break;
        case LITEPLAYER_MSG_GETFILEINFO:
            CHECK_NULL_RETURN(msgInfo.msgData, HI_ERR_LITEPLAYER_NULL_PTR, "msgData null");
            ret = m_liteplayerHandle->DoGetFileInfo(*reinterpret_cast<FormatFileInfo *>(msgInfo.msgData));
            break;
        default:
            ret = HI_ERR_LITEPLAYER_ILLEGAL_PARAM;
            break;
    }

    return ret;
}

void PlayerControlSMObserver::OnEventHandled(const HiStateMachine &curState, int event, int result)
{
    (void)curState;
    if ((result == HI_ERR_LITEPLAYER_ILLEGAL_STATE_ACTION) && (event == LITEPLAYER_MSG_SEEK) &&
        (m_liteplayerHandle != nullptr)) {
        m_liteplayerHandle->NotifyError(HI_LITEPLAYER_ERROR_ILLEGAL_STATEACTION);
    }
}

PlayerControlSMObserver::~PlayerControlSMObserver()
{
}

PlayerControlStateMachine::PlayerControlStateMachine(PlayerControlHandle& liteplayerHandle)
    : HiStateMachine(), m_liteplayerHandle(&liteplayerHandle), m_stateIdle(nullptr), m_stateInit(nullptr),
      m_statePrepare(nullptr), m_statePlay(nullptr), m_stateTPlay(nullptr),
      m_statePause(nullptr), m_stateError(nullptr)
{
}

PlayerControlStateMachine::~PlayerControlStateMachine()
{
    (void)Deinit();
}

int32_t PlayerControlStateMachine::CreateStates()
{
    CHECK_NULL_RETURN(m_liteplayerHandle, HI_ERR_LITEPLAYER_NULL_PTR, "handle null");
    m_stateIdle = new(std::nothrow) PlayerControlState(*m_liteplayerHandle, *this,
        StateEnum2Name(PLAY_STATUS_IDLE));
    if (m_stateIdle == nullptr) {
        MEDIA_ERR_LOG( "new m_stateIdle failed");
        return HI_ERR_LITEPLAYER_MEM_MALLOC;
    }
    m_stateInit = new(std::nothrow) PlayerControlState(*m_liteplayerHandle, *this,
        StateEnum2Name(PLAY_STATUS_INIT));
    if (m_stateInit == nullptr) {
        MEDIA_ERR_LOG( "new m_stateInit failed");
        goto DESTROY;
    }
    m_statePrepare = new(std::nothrow) PlayerControlState(*m_liteplayerHandle, *this,
        StateEnum2Name(PLAY_STATUS_PREPARED));
    if (m_statePrepare == nullptr) {
        MEDIA_ERR_LOG( "new m_statePrepare failed");
        goto DESTROY;
    }
    m_statePlay = new(std::nothrow) PlayerControlState(*m_liteplayerHandle, *this,
        StateEnum2Name(PLAY_STATUS_PLAY));
    if (m_statePlay == nullptr) {
        MEDIA_ERR_LOG( "new m_statePlay failed");
        goto DESTROY;
    }
    m_stateTPlay = new(std::nothrow) PlayerControlState(*m_liteplayerHandle, *this,
        StateEnum2Name(PLAY_STATUS_TPLAY));
    if (m_stateTPlay == nullptr) {
        MEDIA_ERR_LOG( "new m_stateTPlay failed");
        goto DESTROY;
    }
    m_statePause = new(std::nothrow) PlayerControlState(*m_liteplayerHandle, *this,
        StateEnum2Name(PLAY_STATUS_PAUSE));
    if (m_statePause == nullptr) {
        MEDIA_ERR_LOG( "new m_statePause failed");
        goto DESTROY;
    }
    m_stateError = new(std::nothrow) PlayerControlState(*m_liteplayerHandle, *this,
        StateEnum2Name(PLAY_STATUS_ERR));
    if (m_stateError == nullptr) {
        MEDIA_ERR_LOG( "new m_stateError failed");
        goto DESTROY;
    }
    return HI_SUCCESS;
DESTROY:
    DestroyStates();
    return HI_ERR_LITEPLAYER_MEM_MALLOC;
}

void PlayerControlStateMachine::DestroyStates()
{
    if (m_stateIdle != nullptr) {
        delete m_stateIdle;
        m_stateIdle = nullptr;
    }
    if (m_stateInit != nullptr) {
        delete m_stateInit;
        m_stateInit = nullptr;
    }
    if (m_statePrepare != nullptr) {
        delete m_statePrepare;
        m_statePrepare = nullptr;
    }
    if (m_statePlay != nullptr) {
        delete m_statePlay;
        m_statePlay = nullptr;
    }
    if (m_stateTPlay != nullptr) {
        delete m_stateTPlay;
        m_stateTPlay = nullptr;
    }
    if (m_statePause != nullptr) {
        delete m_statePause;
        m_statePause = nullptr;
    }
    if (m_stateError != nullptr) {
        delete m_stateError;
        m_stateError = nullptr;
    }
}

int32_t PlayerControlStateMachine::Init(uint32_t maxQueueSize, uint32_t maxMsgPayloadSize)
{
    const std::string LITEPLAYER_SM_NAME = "liteplayer_sm";
    int32_t ret = HiStateMachine::Init(maxQueueSize, maxMsgPayloadSize, LITEPLAYER_SM_NAME);
    if (ret != HI_SUCCESS) {
        printf("HiStateMachine::Init failed");
        return ret;
    }
    ret = CreateStates();
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG( "createStates failed");
        return ret;
    }
    m_stateIdle->AddTransition(LITEPLAYER_MSG_SET_DATASOURCE_FD, *m_stateInit);
    m_stateIdle->AddTransition(LITEPLAYER_MSG_SET_DATASOURCE_URI, *m_stateInit);
    m_stateIdle->AddTransition(LITEPLAYER_MSG_SET_DATASOURCE_STREAM, *m_stateInit);
    m_stateIdle->AddTransition(LITEPLAYER_MSG_ERROR, *m_stateError);
    m_stateInit->AddTransition(LITEPLAYER_MSG_PREPARE, *m_statePrepare);
    m_stateInit->AddTransition(LITEPLAYER_MSG_ERROR, *m_stateError);
    m_stateInit->AddTransition(LITEPLAYER_MSG_STOP, *m_stateIdle);
    m_statePrepare->AddTransition(LITEPLAYER_MSG_PLAY, *m_statePlay);
    m_statePrepare->AddTransition(LITEPLAYER_MSG_STOP, *m_stateIdle);
    m_statePrepare->AddTransition(LITEPLAYER_MSG_ERROR, *m_stateError);
    m_statePlay->AddTransition(LITEPLAYER_MSG_STOP, *m_stateIdle);
    m_statePlay->AddTransition(LITEPLAYER_MSG_TPLAY, *m_stateTPlay);
    m_statePlay->AddTransition(LITEPLAYER_MSG_PAUSE, *m_statePause);
    m_statePlay->AddTransition(LITEPLAYER_MSG_ERROR, *m_stateError);
    m_stateTPlay->AddTransition(LITEPLAYER_MSG_STOP, *m_stateIdle);
    m_stateTPlay->AddTransition(LITEPLAYER_MSG_PLAY, *m_statePlay);
    m_stateTPlay->AddTransition(LITEPLAYER_MSG_ERROR, *m_stateError);
    m_statePause->AddTransition(LITEPLAYER_MSG_STOP, *m_stateIdle);
    m_statePause->AddTransition(LITEPLAYER_MSG_PLAY, *m_statePlay);
    m_statePause->AddTransition(LITEPLAYER_MSG_ERROR, *m_stateError);
    m_stateError->AddTransition(LITEPLAYER_MSG_STOP, *m_stateIdle);
    (void)AddState(*m_stateIdle);
    (void)AddState(*m_stateInit);
    (void)AddState(*m_statePrepare);
    (void)AddState(*m_statePlay);
    (void)AddState(*m_stateTPlay);
    (void)AddState(*m_statePause);
    (void)AddState(*m_stateError);
    (void)SetInitialState(*m_stateIdle);
    return HI_SUCCESS;
}

int32_t PlayerControlStateMachine::Deinit()
{
    DestroyStates();
    int32_t ret = HiStateMachine::Deinit();
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG( "HiStateMachine::Deinit failed");
        return ret;
    }
    return HI_SUCCESS;
}

PlayerStatus PlayerControlStateMachine::GetCurState()
{
    const HiState* curState = CurrentState();
    return StateConvert2Enum(curState->Name());
}

bool PlayerControlStateMachine::EventValidAtCurState(LiteplayerMsgType type)
{
    if (type < LITEPLAYER_MSG_SETATTR || type >= LITEPLAYER_MSG_BUTT) {
        MEDIA_ERR_LOG( "EventValidAtCurState MSG type not support %d", type);
        return false;
    }
    return LITEPLAY_STATE[type][GetCurState()];
}
}
}
