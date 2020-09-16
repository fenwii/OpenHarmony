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

#include "player_impl.h"
#include <cinttypes>
#include <climits>
#include <string>
#include <sys/prctl.h>
#include "unistd.h"
#include "securec.h"
#include "format_type.h"
#include "hi_liteplayer_err.h"
#include "hi_liteplayer.h"
#include "player_define.h"
#include "media_log.h"
extern "C"
{
#include "codec_interface.h"
#include "hal_display.h"
}

using namespace std;
using OHOS::Media::AdapterStreamCallback;

namespace OHOS {
namespace Media {
const int DEFAULT_SEND_LEVEL = 3;
const int INVALID_MEDIA_POSITION = -1;
const int DEFAULT_REWIND_TIME = 0;
const float DEFAULT_MEDIA_VOLUME = 100.0f;
const int INIT_VIDEO_SIZE = 0;
const int DEFAULT_THREAD_ID = -1;
const int32_t IDLE_QUEQUE_SLEEP_TIME_US = 10000;

#define CHECK_FAILED_PRINT(func, target, printfString) \
do { \
    int ret = (func); \
    if (ret != (target)) { \
        MEDIA_ERR_LOG("%s, ret:%d", printfString ? printfString : " ", ret); \
    } \
} while (0)

#define CHK_NULL_RETURN(ptr) \
do { \
    if (ptr == nullptr) { \
        MEDIA_ERR_LOG("ptr null"); \
        return -1; \
    } \
} while (0)

Player::PlayerImpl::PlayerImpl()
    : m_player(nullptr), m_speed(1.0), m_videoScaleType(-1), m_liteplayerState(PLAY_STATUS_IDLE),
      m_isLoop(false),
      m_isPrepareSync(false),
      m_isAudioTearDown(false),
      m_currentPosition(INVALID_MEDIA_POSITION),
      m_rewindPosition(INVALID_MEDIA_POSITION),
      m_videoWidth(INIT_VIDEO_SIZE),
      m_videoHeight(INIT_VIDEO_SIZE),
      m_threadId(DEFAULT_THREAD_ID),
      m_leftVolume(DEFAULT_MEDIA_VOLUME),
      m_rightVolume(DEFAULT_MEDIA_VOLUME),
      m_surface(nullptr),
      m_sendLevel(DEFAULT_SEND_LEVEL),
      m_currentState(PLAYER_IDLE),
      m_rewindMode(PLAYER_SEEK_PREVIOUS_SYNC),
      m_currentRewindMode(PLAYER_SEEK_PREVIOUS_SYNC),
      m_streamType(0),
      m_callBack(nullptr),
      m_inited (false),
      m_released(true),
      m_isStreamSource(false),
      eos(false),
      bufferSource(nullptr),
      streamCallback(nullptr)
{
    m_formatFileInfo = {};
    buffer = {};
    buffer.idx = -1;
    m_mediaAttr = {};
}

int32_t Player::PlayerImpl::Init(void)
{
    int ret;
    if (m_inited == true) {
        return 0;
    }
    ret = HalPlayerSysInit();
    if (ret != 0) {
        MEDIA_WARNING_LOG("SystemInit has been inited before Ret: %x", ret);
    }
    ret = CodecInit();
    if (ret != 0) {
        return ret;
    }
    if (memset_s(&buffer, sizeof(QueBuffer), 0, sizeof(QueBuffer)) != EOK) {
        return -1;
    }
    buffer.idx = -1;
    m_inited = true;
    MEDIA_INFO_LOG("[PlayerImpl::%s, %d] success", __func__, __LINE__);
    return 0;
}

int32_t Player::PlayerImpl::DeInit(void)
{
    if (m_inited != true) {
        return 0;
    }
    if (m_released == false) {
        Release();
    }
    m_inited = false;
    return 0;
}

Player::PlayerImpl::~PlayerImpl()
{
    DeInit();
    m_player = NULL;
    MEDIA_INFO_LOG("~PlayerImpl process");
}

int32_t Player::PlayerImpl::SetSource(const Source &source)
{
    std::lock_guard<std::mutex> valueLock(lock_);
    MEDIA_INFO_LOG("process in");
    GetPlayer();
    CHK_NULL_RETURN(m_player);
    SourceType sType = source.GetSourceType();
    int32_t ret = -1;
    if (sType == SourceType::SOURCE_TYPE_FD) {
        MEDIA_ERR_LOG("not support fdSource now");
    } else if (sType == SourceType::SOURCE_TYPE_URI) {
        ret = SetUriSource(source);
    } else if (sType == SourceType::SOURCE_TYPE_STREAM) {
        ret = SetStreamSource(source);
    } else {
        MEDIA_ERR_LOG("SetSource failed, unkonwn source type");
    }
    return ret;
}

static void ShowFileInfo(const FormatFileInfo *fileInfo)
{
    for (int i = 0; i < HI_DEMUXER_RESOLUTION_CNT; i++) {
        const StreamResolution *resolution = &fileInfo->stSteamResolution[i];
        MEDIA_INFO_LOG("video[%d],w=%u,h=%u,index=%d ", i, resolution->u32Width,
            resolution->u32Height, resolution->s32VideoStreamIndex);
    }
    MEDIA_INFO_LOG("audio channel_cnt=%u,sampleRate=%u,AudioStreamIndex=%d videoIndex:%d",
        fileInfo->u32AudioChannelCnt, fileInfo->u32SampleRate, fileInfo->s32UsedAudioStreamIndex,
        fileInfo->s32UsedVideoStreamIndex);
}

void Player::PlayerImpl::UpdateState(PlayerImpl *curPlayer, PlayerStatus state)
{
    if (curPlayer == NULL) {
        return;
    }
    switch (state) {
        case PLAY_STATUS_IDLE:
            curPlayer->m_currentState |= PLAYER_IDLE;
            break;
        case PLAY_STATUS_INIT:
            curPlayer->m_currentState |= PLAYER_INITIALIZED;
            break;
        case PLAY_STATUS_PREPARED:
            curPlayer->m_currentState |= PLAYER_PREPARED;
            break;
        case PLAY_STATUS_PLAY:
            curPlayer->m_currentState |= PLAYER_STARTED;
            break;
        case PLAY_STATUS_TPLAY:
            curPlayer->m_currentState |= PLAYER_STARTED;
            break;
        case PLAY_STATUS_PAUSE:
            curPlayer->m_currentState |= PLAYER_PAUSED;
            break;
        default:
            break;
    }
    curPlayer->m_liteplayerState = state;
    MEDIA_INFO_LOG("@@player UpdateState, state:%d", state);
}

void Player::PlayerImpl::HiLitePlayerEventCb(void* pPlayer, PlayerControlEvent enEvent, const void* pData)
{
    PlayerControlError subErr = HI_LITEPLAYER_ERROR_BUTT;
    PlayerImpl *curPlayer = (PlayerImpl *)pPlayer;

    if (curPlayer == nullptr) {
        MEDIA_ERR_LOG("the handle is error");
        return;
    }
    switch (enEvent) {
        case HI_LITEPLAYER_EVENT_STATE_CHANGED:
            if (pData == nullptr) {
                return;
            }
            curPlayer->UpdateState(curPlayer, *reinterpret_cast<const PlayerStatus *>(pData));
            break;
        case HI_LITEPLAYER_EVENT_EOF:
            MEDIA_INFO_LOG("nend of file");
            curPlayer->NotifyPlaybackComplete(curPlayer);
            break;
        case HI_LITEPLAYER_EVENT_SOF:
            MEDIA_INFO_LOG("start of file");
            break;
        case HI_LITEPLAYER_EVENT_ERROR:
            if (pData == nullptr) {
                return;
            }
            subErr = *reinterpret_cast<const PlayerControlError *>(pData);
            MEDIA_ERR_LOG("error: %d", subErr);
            if (curPlayer->m_callBack != nullptr) {
                curPlayer->m_callBack->OnError(0, subErr);
            }
            break;
        case HI_LITEPLAYER_EVENT_PROGRESS:
            if (pData == nullptr) {
                return;
            }
            curPlayer->m_currentPosition = *reinterpret_cast<const int64_t *>(pData);
            break;

        case HI_LITEPLAYER_EVENT_SEEK_END:
            if (pData == nullptr) {
                return;
            }
            MEDIA_INFO_LOG("seek action end, time is %lld",  *reinterpret_cast<const int64_t *>(pData));
            curPlayer->NotifySeekComplete(curPlayer);
            break;
        default:
            break;
    }
}

int32_t Player::PlayerImpl::Prepare()
{
    std::lock_guard<std::mutex> valueLock(lock_);
    int ret;
    MEDIA_INFO_LOG("process in");
    CHK_NULL_RETURN(m_player);
    if ((m_currentState != PLAYER_INITIALIZED) && (m_currentState != PLAYER_STOPPED)) {
        MEDIA_ERR_LOG("Can not Prepare, currentState_ is %d", m_currentState);
        return -1;
    }
    PlayerCtrlCallbackParam param;
    param.player = this;
    param.callbackFun = HiLitePlayerEventCb;
    ret = m_player->RegCallback(param);
    if (ret != 0) {
        MEDIA_ERR_LOG("RegCallback exec failed ");
        return -1;
    }

    m_currentState = PLAYER_PREPARING;
    m_player->Prepare();
    m_currentState = PLAYER_PREPARED;

    ret = m_player->GetFileInfo(m_formatFileInfo);
    if (ret != 0) {
        MEDIA_ERR_LOG("GetFileInfo failed");
        return ret;
    }
    ShowFileInfo(&m_formatFileInfo);
    /* report video solution */
    for (int i = 0; i < HI_DEMUXER_RESOLUTION_CNT; i++) {
        if (m_formatFileInfo.stSteamResolution[i].s32VideoStreamIndex == m_formatFileInfo.s32UsedVideoStreamIndex) {
            if (m_callBack != nullptr) {
                m_callBack->OnVideoSizeChanged(m_formatFileInfo.stSteamResolution[i].u32Width,
                    m_formatFileInfo.stSteamResolution[i].u32Height);
            }
        }
    }
    MEDIA_INFO_LOG("process out");
    return 0;
}

int32_t Player::PlayerImpl::Play()
{
    std::lock_guard<std::mutex> valueLock(lock_);
    int ret;
    MEDIA_INFO_LOG("process in");
    if (m_player == NULL) {
        MEDIA_ERR_LOG("Play failed, player_ is null");
        m_threadId = 0;
        return -1;
    }

    if (m_currentState != PLAYER_PREPARED && m_currentState != PLAYER_PLAYBACK_COMPLETE &&
        m_currentState != PLAYER_PAUSED) {
        MEDIA_ERR_LOG("Can not Play, currentState is %d", m_currentState);
        return -1;
    }

    if (m_currentState == PLAYER_STARTED) {
        MEDIA_ERR_LOG("Can not Play, currentState_ is MEDIA_PLAYER_STARTED");
        return 0;
    }
    if (m_currentState == PLAYER_PAUSED) {
        goto play;
    }
    if (m_currentState == PLAYER_PLAYBACK_COMPLETE) {
        MEDIA_ERR_LOG("Can not Play, currentState_ is PLAYER_PLAYBACK_COMPLETE");
        return 0;
    }
    m_mediaAttr.s32VidStreamId = m_formatFileInfo.s32UsedVideoStreamIndex;
    m_mediaAttr.s32AudStreamId = m_formatFileInfo.s32UsedAudioStreamIndex;
    ret = m_player->SetMedia(m_mediaAttr);
    if (ret != 0) {
        MEDIA_ERR_LOG("HI_LITEPLAYER_SetMedia  exec failed");
        return  ret;
    }

    for (int i = 0; i < HI_DEMUXER_RESOLUTION_CNT; i++) {
        StreamResolution *resolution = &m_formatFileInfo.stSteamResolution[i];
        if (resolution->s32VideoStreamIndex == m_mediaAttr.s32VidStreamId) {
            MEDIA_INFO_LOG("used video w=%u,h=%u,index=%d",
                resolution->u32Width, resolution->u32Height, m_mediaAttr.s32VidStreamId);
            break;
        }
    }

play:
    ret = m_player->Play();
    if (ret != 0) {
        MEDIA_ERR_LOG("Play exec failed %x", ret);
        return -1;
    }
    m_currentState = PLAYER_STARTED;
    MEDIA_INFO_LOG("process out");
    return 0;
}

bool Player::PlayerImpl::IsPlaying()
{
    std::lock_guard<std::mutex> valueLock(lock_);
    MEDIA_INFO_LOG("process in\n");
    bool isPlaying = false;
    if (m_player != nullptr) {
        isPlaying = (m_currentState != PLAYER_STARTED) ? false : true;
    }
    return isPlaying;
}

int32_t Player::PlayerImpl::Pause()
{
    std::lock_guard<std::mutex> valueLock(lock_);
    MEDIA_INFO_LOG("process in");
    CHK_NULL_RETURN(m_player);
    if (m_currentState == PLAYER_PAUSED || m_currentState == PLAYER_PLAYBACK_COMPLETE) {
        MEDIA_ERR_LOG("currentState_ is %d", m_currentState);
        return 0;
    }

    if (m_currentState != PLAYER_STARTED) {
        MEDIA_ERR_LOG("Can not Pause, currentState_ is %d", m_currentState);
        return -1;
    }

    m_player->Pause();
    m_currentState = PLAYER_PAUSED;
    return 0;
}

int32_t Player::PlayerImpl::Stop()
{
    std::lock_guard<std::mutex> valueLock(lock_);
    MEDIA_INFO_LOG("process in");
    CHK_NULL_RETURN(m_player);
    if (m_currentState  == PLAYER_STOPPED) {
        return 0;
    }

    if (m_currentState != PLAYER_STARTED && m_currentState != PLAYER_PREPARED &&
        m_currentState != PLAYER_PAUSED && m_currentState != PLAYER_PLAYBACK_COMPLETE) {
        MEDIA_ERR_LOG("Can not Stop, currentState_ is %d", m_currentState);
        return -1;
    }

    int32_t ret = m_player->Stop();
    if (ret != 0) {
        m_currentState = PLAYER_STATE_ERROR;
        MEDIA_ERR_LOG("Stop failed, ret is %d", ret);
        return ret;
    }

    m_currentState = PLAYER_STOPPED;
    MEDIA_INFO_LOG("process out");
    return 0;
}

int32_t Player::PlayerImpl::RewindInner(int64_t mSeconds, PlayerSeekMode mode)
{
    MEDIA_INFO_LOG("process in");
    CHK_NULL_RETURN(m_player);
    if (mSeconds < DEFAULT_REWIND_TIME) {
        MEDIA_WARNING_LOG("Attempt to rewind to invalid position %lld", mSeconds);
        mSeconds = DEFAULT_REWIND_TIME;
    }
    int32_t ret;
    int64_t durationMs = -1;
    GetDurationInner(durationMs);
    if ((durationMs > DEFAULT_REWIND_TIME) && (mSeconds > durationMs)) {
        MEDIA_WARNING_LOG("Attempt to rewind to past end of file, request is %lld, durationMs is %lld", mSeconds,
            durationMs);
        return -1;
    }
    m_currentRewindMode = mode;
    if (m_rewindPosition >= DEFAULT_REWIND_TIME) {
        return 0;
    }

    m_rewindPosition = mSeconds;
    m_rewindMode = mode;
    ret = m_player->Seek(mSeconds);
    if (ret != 0) {
        MEDIA_ERR_LOG("RewindInner failed, ret is %d", ret);
    }
    MEDIA_INFO_LOG("process out");
    return ret;
}

bool Player::PlayerImpl::IsValidRewindMode(PlayerSeekMode mode)
{
    switch (mode) {
        case PLAYER_SEEK_PREVIOUS_SYNC:
        case PLAYER_SEEK_NEXT_SYNC:
        case PLAYER_SEEK_CLOSEST_SYNC:
        case PLAYER_SEEK_CLOSEST:
        case PLAYER_SEEK_FRAME_INDEX:
            break;
        default:
            MEDIA_ERR_LOG("Unknown rewind mode %d", mode);
            return false;
    }
    return true;
}

int32_t Player::PlayerImpl::Rewind(int64_t mSeconds, int32_t mode)
{
    std::lock_guard<std::mutex> valueLock(lock_);
    MEDIA_INFO_LOG("process in");
    if (m_currentState != PLAYER_STARTED && m_currentState != PLAYER_PREPARED &&
        m_currentState != PLAYER_PAUSED) {
        MEDIA_ERR_LOG("Can not Rewind, currentState_ is %d", m_currentState);
        return -1;
    }

    if (IsValidRewindMode((PlayerSeekMode)mode) != true) {
        MEDIA_ERR_LOG("Rewind failed, msec is %lld, mode is %d", mSeconds, mode);
        return -1;
    }

    if (m_isStreamSource == true) {
        MEDIA_ERR_LOG("Failed, streamsource not support Rewind");
        return 0;
    }
    int32_t ret = RewindInner(mSeconds, (PlayerSeekMode)mode);
    if (ret != 0) {
        MEDIA_ERR_LOG("ReWind failed, ret is %d", ret);
    } else {
        m_currentPosition = mSeconds;
    }
    MEDIA_INFO_LOG("process out");
    return ret;
}

int32_t Player::PlayerImpl::SetVolume(float leftVolume, float rightVolume)
{
    std::lock_guard<std::mutex> valueLock(lock_);
    MEDIA_INFO_LOG("process in");
    VolumeAttr attr;

    CHK_NULL_RETURN(m_player);
    if ((m_currentState != PLAYER_STARTED) && (m_currentState != PLAYER_PAUSED) &&
        (m_currentState != PLAYER_PREPARED)) {
        MEDIA_ERR_LOG("SetVolume failed, m_currentState is %d", m_currentState);
        return -1;
    }
    attr.leftVolume = leftVolume;
    attr.rightVolume = rightVolume;
    int ret = m_player->SetVolume(attr);
    if (ret != 0) {
        MEDIA_ERR_LOG("SetVolume failed %x", ret);
    }
    MEDIA_INFO_LOG("process out\n");
    return ret;
}

int32_t Player::PlayerImpl::SetSurface(Surface *surface)
{
    if (m_currentState != PLAYER_PREPARED) {
        MEDIA_ERR_LOG("SetSurface failed, m_currentState is %d", m_currentState);
        return -1;
    }
    m_surface = surface;
    m_player->SetSurface(surface);
    return 0;
}

bool Player::PlayerImpl::IsLooping()
{
    std::lock_guard<std::mutex> valueLock(lock_);
    bool isLoop = (m_player == nullptr) ? false : m_isLoop;
    return isLoop;
}

int32_t Player::PlayerImpl::GetPlayerState(int32_t &state)
{
    std::lock_guard<std::mutex> valueLock(lock_);
    state = m_currentState;
    return 0;
}

int32_t Player::PlayerImpl::GetCurrentPosition(int64_t &position)
{
    std::lock_guard<std::mutex> valueLock(lock_);
    MEDIA_INFO_LOG("process in");
    CHK_NULL_RETURN(m_player);
    position = (m_currentPosition >= 0) ? m_currentPosition : -1;
    return 0;
}

void Player::PlayerImpl::GetDurationInner(int64_t &durationMs)
{
    FormatFileInfo formatInfo;
    int32_t ret = m_player->GetFileInfo(formatInfo);
    if (ret != 0) {
        MEDIA_ERR_LOG("GetDuration failed, ret is %d", ret);
    }
    durationMs = (ret == 0) ? formatInfo.s64Duration : -1;
}

int32_t Player::PlayerImpl::GetDuration(int64_t &durationMs)
{
    std::lock_guard<std::mutex> valueLock(lock_);
    MEDIA_INFO_LOG("process in");
    CHK_NULL_RETURN(m_player);
    if (m_currentState != PLAYER_PREPARED && m_currentState != PLAYER_STARTED && m_currentState != PLAYER_PAUSED &&
        m_currentState != PLAYER_STOPPED && m_currentState != PLAYER_PLAYBACK_COMPLETE) {
        MEDIA_ERR_LOG("Can not GetDuration, currentState_ is %d", m_currentState);
        return -1;
    }
    GetDurationInner(durationMs);
    return 0;
}

int32_t Player::PlayerImpl::GetVideoWidth(int32_t &videoWidth)
{
    std::lock_guard<std::mutex> valueLock(lock_);
    MEDIA_INFO_LOG("process in");
    CHK_NULL_RETURN(m_player);
    FormatFileInfo formatInfo;
    int32_t ret;
    videoWidth = 0;
    ret = m_player->GetFileInfo(formatInfo);
    if (ret != 0) {
        MEDIA_ERR_LOG("GetFileInfo failed, ret is %d", ret);
        return ret;
    }
    if (m_formatFileInfo.s32UsedVideoStreamIndex == -1) {
        return -1;
    }
    for (int i = 0; i < HI_DEMUXER_RESOLUTION_CNT; i++) {
        if (m_formatFileInfo.stSteamResolution[i].s32VideoStreamIndex == m_formatFileInfo.s32UsedVideoStreamIndex) {
            videoWidth = m_formatFileInfo.stSteamResolution[i].u32Width;
            break;
        }
    }
    return 0;
}

int32_t Player::PlayerImpl::GetVideoHeight(int32_t &videoHeight)
{
    std::lock_guard<std::mutex> valueLock(lock_);
    MEDIA_INFO_LOG("process in");
    CHK_NULL_RETURN(m_player);
    FormatFileInfo formatInfo;
    int32_t ret;
    videoHeight = 0;
    ret = m_player->GetFileInfo(formatInfo);
    if (ret != 0) {
        MEDIA_ERR_LOG("HI_LITEPLAYER_GetFileInfo failed, ret is %d", ret);
        return ret;
    }
    if (m_formatFileInfo.s32UsedVideoStreamIndex == -1) {
        return -1;
    }
    for (int i = 0; i < HI_DEMUXER_RESOLUTION_CNT; i++) {
        if (m_formatFileInfo.stSteamResolution[i].s32VideoStreamIndex == m_formatFileInfo.s32UsedVideoStreamIndex) {
            videoHeight = m_formatFileInfo.stSteamResolution[i].u32Height;
            break;
        }
    }
    return ret;
}

int32_t Player::PlayerImpl::SetAudioStreamType(int32_t type)
{
    std::lock_guard<std::mutex> valueLock(lock_);
    MEDIA_INFO_LOG("process in");
    if (m_currentState == PLAYER_PREPARED || m_currentState == PLAYER_STARTED ||
        m_currentState == PLAYER_PAUSED || m_currentState == PLAYER_PLAYBACK_COMPLETE) {
        MEDIA_ERR_LOG("SetAudioStreamType called in state %d,type:%d",
            m_currentState, type);
        return -1;
    }
    m_streamType = type;
    return 0;
}

void Player::PlayerImpl::GetAudioStreamType(int32_t &type)
{
    std::lock_guard<std::mutex> valueLock(lock_);
    type = static_cast<int32_t>(m_streamType);
}

int32_t Player::PlayerImpl::Reset(void)
{
    std::lock_guard<std::mutex> valueLock(lock_);
    MEDIA_INFO_LOG("process in");
    CHK_NULL_RETURN(m_player);
    m_isLoop = false;
    if (m_currentState == PLAYER_IDLE) {
        return -1;
    }

    m_isPrepareSync = false;
    CHECK_FAILED_PRINT(m_player->Stop(), 0, "stop failed");
    if (m_player->GetState() != PLAY_STATUS_IDLE) {
        CHECK_FAILED_PRINT(m_player->Stop(), HI_SUCCESS, "stop failed");
    }
    if (m_player->GetState() != PLAY_STATUS_IDLE) {
        MEDIA_ERR_LOG("Destroy failed, player not idle state");
    }
    (void)m_player->Deinit();
    m_currentState = PLAYER_IDLE;
    m_threadId = 0;
    m_currentPosition = INVALID_MEDIA_POSITION;
    m_currentRewindMode = PLAYER_SEEK_PREVIOUS_SYNC;
    m_rewindPosition = INVALID_MEDIA_POSITION;
    m_rewindMode = PLAYER_SEEK_PREVIOUS_SYNC;
    return 0;
}

int32_t Player::PlayerImpl::Release()
{
    std::lock_guard<std::mutex> valueLock(lock_);
    MEDIA_INFO_LOG("process in");
    CHK_NULL_RETURN(m_player);
    m_released = true;
    return 0;
}

int Player::PlayerImpl::CreatePlayerParamCheck(PlayerControlParam &createParam)
{
    if (createParam.u32PlayPosNotifyIntervalMs < MIN_NOTIFY_INTERVAL_MS
        && createParam.u32PlayPosNotifyIntervalMs > 0) {
        MEDIA_ERR_LOG("notify interval small than min value %d",
            MIN_NOTIFY_INTERVAL_MS);
        return HI_ERR_LITEPLAYER_ILLEGAL_PARAM;
    }
    if ((createParam.u32VideoEsBufSize < AV_ESBUF_SIZE_MIN && createParam.u32VideoEsBufSize > 0)
        || createParam.u32VideoEsBufSize > VIDEO_ESBUF_SIZE_LIMIT) {
        MEDIA_ERR_LOG("video esbuffer illegal %u",
            createParam.u32VideoEsBufSize);
        return HI_ERR_LITEPLAYER_ILLEGAL_PARAM;
    }
    if ((createParam.u32AudioEsBufSize < AV_ESBUF_SIZE_MIN && createParam.u32AudioEsBufSize > 0)
        || createParam.u32AudioEsBufSize > AUDIO_ESBUF_SIZE_LIMIT) {
        MEDIA_ERR_LOG("audio esbuffer illegal %u",
            createParam.u32VideoEsBufSize);
        return HI_ERR_LITEPLAYER_ILLEGAL_PARAM;
    }
    if ((createParam.u32VdecFrameBufCnt < VDEC_VBBUF_CONUT_MIN) &&
        (createParam.u32VdecFrameBufCnt != 0)) {
        MEDIA_ERR_LOG("VDEC vb buffer count %u small than %d",
            createParam.u32VdecFrameBufCnt, VDEC_VBBUF_CONUT_MIN);
        return HI_ERR_LITEPLAYER_ILLEGAL_PARAM;
    }
    return 0;
}

int Player::PlayerImpl::GetPlayer()
{
    MEDIA_INFO_LOG("process in");
    PlayerControlParam playerParam;
    if (m_player != nullptr) {
        return 0;
    }
    if (memset_s(&playerParam, sizeof(PlayerControlParam), 0x00, sizeof(playerParam)) != EOK) {
        return -1;
    }

    playerParam.u32PlayPosNotifyIntervalMs = 300;
    if (CreatePlayerParamCheck(playerParam) != 0) {
        MEDIA_ERR_LOG("CreatePlayerParamCheck failed");
        return -1;
    }
    m_player = std::make_shared<LitePlayer>();
    if (m_player == nullptr || m_player.get() == nullptr) {
        MEDIA_ERR_LOG("LitePlayer new failed");
        return HI_ERR_LITEPLAYER_MEM_MALLOC;
    }
    if (m_player->Init(playerParam) != HI_SUCCESS) {
        MEDIA_ERR_LOG("Liteplayer init failed");
        return HI_ERR_LITEPLAYER_MEM_MALLOC;
    }
    m_currentState = PLAYER_INITIALIZED;
    MEDIA_INFO_LOG("GetPlayer success");
    return 0;
}

void Player::PlayerImpl::SetPlayerCallback(const std::shared_ptr<PlayerCallback> &cb)
{
    std::lock_guard<std::mutex> valueLock(lock_);
    MEDIA_INFO_LOG("process in");
    m_callBack = cb;
}

void Player::PlayerImpl::NotifyPrepared()
{
    m_currentState = PLAYER_PREPARED;
    if (m_isPrepareSync) {
        m_isPrepareSync = false;
    }
}

void Player::PlayerImpl::NotifyPlaybackComplete(PlayerImpl *curPlayer)
{
    if (curPlayer == NULL) {
        return;
    }
    if (!m_isLoop) {
        curPlayer->m_currentState = PLAYER_PLAYBACK_COMPLETE;
        MEDIA_INFO_LOG("OnPlayBackComplete, iscallbackNull:%d", (curPlayer->m_callBack != nullptr));
        if (curPlayer->m_callBack != nullptr) {
            curPlayer->m_callBack->OnPlaybackComplete();
        }
        return;
    }
    curPlayer->Rewind(0, PLAYER_SEEK_PREVIOUS_SYNC);
}

void Player::PlayerImpl::NotifyMediaError(int32_t prepareStatus, bool &isSend)
{
    m_currentState = PLAYER_STATE_ERROR;
    MEDIA_INFO_LOG("NotifyMediaError status: %d", prepareStatus);
    if (m_isPrepareSync) {
        m_isPrepareSync = false;
        isSend = false;
    }
}

void Player::PlayerImpl::NotifySeekComplete(PlayerImpl *curPlayer)
{
    if (curPlayer == NULL) {
        return;
    }
    if (curPlayer->m_rewindMode != curPlayer->m_currentRewindMode) {
        curPlayer->m_rewindPosition = -1;
        curPlayer->m_rewindMode = PLAYER_SEEK_PREVIOUS_SYNC;
        curPlayer->RewindInner(curPlayer->m_currentPosition, curPlayer->m_currentRewindMode);
    } else {
        curPlayer->m_rewindPosition = -1;
        curPlayer->m_currentRewindMode = curPlayer->m_rewindMode = PLAYER_SEEK_PREVIOUS_SYNC;
    }
    if (curPlayer->m_callBack != nullptr) {
        curPlayer->m_callBack->OnRewindToComplete();
    }
}

int32_t Player::PlayerImpl::SetLoop(bool loop)
{
    std::lock_guard<std::mutex> valueLock(lock_);
    CHK_NULL_RETURN(m_player);
    m_isLoop = loop;
    return 0;
}

int32_t Player::PlayerImpl::SetUriSource(const Source &source)
{
    MEDIA_INFO_LOG("process in");
    const std::string uri = source.GetSourceUri();
    if (uri.empty()) {
        MEDIA_ERR_LOG("SetUriSource failed, uri source do not set uri parameter");
        return -1;
    }
    char filePath[PATH_MAX];
    if (realpath(uri.c_str(), filePath) == nullptr) {
        MEDIA_ERR_LOG("Realpath input file failed");
        return -1;
    }
    if (access(filePath, R_OK) == -1) {
        MEDIA_ERR_LOG("No permission to read the file");
        return -1;
    }
    int32_t ret = m_player->SetDataSource(uri.c_str());
    if (ret != 0) {
        MEDIA_ERR_LOG("SetSource failed, ret is %d, uri is %s", ret, uri.c_str());
        return ret;
    }
    return 0;
}

AdapterStreamCallback::AdapterStreamCallback(std::shared_ptr<StreamSource> &stream,
    std::shared_ptr<BufferSource> &buffer)
    : m_streamProcess(0),
      m_isThreadRunning(false)
{
    streamSource = stream;
    bufferSource = buffer;
    pthread_mutex_init(&mutex_, nullptr);
}

AdapterStreamCallback::~AdapterStreamCallback(void)
{
    DeInit();
    MEDIA_INFO_LOG("process out");
}

void* AdapterStreamCallback::IdleBufferProcess(void* arg)
{
    int ret;
    QueBuffer buffer;
    BufferInfo info;
    if (memset_s(&info, sizeof(info), 0x00, sizeof(info)) != EOK) {
        return nullptr;
    }
    AdapterStreamCallback *process = (AdapterStreamCallback*)arg;
    if (process == nullptr) {
        return nullptr;
    }

    prctl(PR_SET_NAME, "IdlbufProc", 0, 0, 0);
    MEDIA_INFO_LOG("process start");
    while (true) {
        pthread_mutex_lock(&process->mutex_);
        if (process->m_isThreadRunning == false) {
            pthread_mutex_unlock(&process->mutex_);
            break;
        }
        pthread_mutex_unlock(&process->mutex_);
        if (process->bufferSource == nullptr) {
            MEDIA_ERR_LOG("bufferSource null break");
            break;
        }
        if (process->bufferSource->GetIdleQueSize() == 0) {
            usleep(IDLE_QUEQUE_SLEEP_TIME_US);
            continue;
        }
        ret = process->bufferSource->DequeIdleBuffer(&buffer, 0);
        if (ret == 0) {
            process->bufferSource->GetBufferInfo(buffer.idx, &info);
            std::shared_ptr<StreamSource> stream = process->streamSource.lock();
            if (stream == nullptr) {
                MEDIA_ERR_LOG("stream not exist break");
                break;
            }
            stream->OnBufferAvailable(buffer.idx, 0, info.bufLen);
        }
    };
    pthread_mutex_lock(&process->mutex_);
    process->m_isThreadRunning = false;
    pthread_mutex_unlock(&process->mutex_);
    MEDIA_INFO_LOG("work end");
    return nullptr;
}

int AdapterStreamCallback::Init(void)
{
    MEDIA_INFO_LOG("process in");
    pthread_mutex_lock(&mutex_);
    m_isThreadRunning = true;
    pthread_mutex_unlock(&mutex_);
    int32_t ret = pthread_create(&m_streamProcess, nullptr, IdleBufferProcess, this);
    if (ret != 0) {
        MEDIA_ERR_LOG("pthread_create failed %d", ret);
        pthread_mutex_lock(&mutex_);
        m_isThreadRunning = false;
        pthread_mutex_unlock(&mutex_);
        return -1;
    }
    return 0;
}

void AdapterStreamCallback::DeInit(void)
{
    MEDIA_INFO_LOG("process in");
    pthread_mutex_lock(&mutex_);
    m_isThreadRunning = false;
    pthread_mutex_unlock(&mutex_);
    if (m_streamProcess != 0) {
        pthread_join(m_streamProcess, nullptr);
    }
    pthread_mutex_destroy(&mutex_);
}

uint8_t* AdapterStreamCallback::GetBuffer(size_t index)
{
    BufferInfo info;
    if (bufferSource == nullptr) {
        MEDIA_ERR_LOG("bufferSource null");
        return nullptr;
    }
    if (bufferSource->GetBufferInfo(index, &info) != 0) {
        MEDIA_ERR_LOG("GetBufferInfo failed");
        return nullptr;
    }
    return (uint8_t*)info.virAddr;
}

void AdapterStreamCallback::QueueBuffer(size_t index, size_t offset, size_t size, int64_t timestampUs, uint32_t flags)
{
    QueBuffer buffer;
    if (bufferSource == nullptr) {
        MEDIA_ERR_LOG("bufferSource null");
        return;
    }

    buffer.idx = index;
    buffer.flag = flags;
    buffer.offset = offset;
    buffer.size = size;
    buffer.timestamp = timestampUs;
    if (bufferSource->QueFilledBuffer(&buffer) != 0) {
        MEDIA_ERR_LOG("QueFilledBuffer failed");
    }
}

void AdapterStreamCallback::SetParameters(const Format &params)
{
    MEDIA_ERR_LOG("process, not support");
}

int32_t Player::PlayerImpl::GetReadableSize(const void *handle)
{
    const PlayerImpl *playImpl = (const PlayerImpl*)handle;
    if (playImpl == nullptr) {
        MEDIA_ERR_LOG("handle null");
        return -1;
    }
    if (playImpl->bufferSource == nullptr) {
        MEDIA_ERR_LOG("bufferSource null");
        return -1;
    }
    return playImpl->bufferSource->GetFilledQueDataSize();
}

int32_t Player::PlayerImpl::ReadData(void *handle, uint8_t *data, int32_t size, int32_t timeOutMs, DataFlags *flags)
{
    PlayerImpl *playImpl = (PlayerImpl*)handle;

    if (playImpl == nullptr || playImpl->bufferSource == nullptr) {
        MEDIA_ERR_LOG("bufferSource null");
        return -1;
    }
    if (data == nullptr || size < 0  || flags == nullptr) {
        MEDIA_ERR_LOG("data null or buffer size < 0");
        return -1;
    }
    BufferInfo info;
    int readLen;
    if (playImpl->buffer.idx != -1) {
        goto READ_BUFFER_DATA;
    }

    if (playImpl->bufferSource->GetFilledQueSize() <= 0) {
        return 0;
    }
    if (playImpl->bufferSource->DequeFilledBuffer(&playImpl->buffer, 0) != 0) {
        playImpl->buffer.idx = -1;
        return 0;
    }
READ_BUFFER_DATA:
    if (playImpl->bufferSource->GetBufferInfo(playImpl->buffer.idx, &info) != 0) {
        return 0;
    }
    /* read all buffer data */
    if (playImpl->buffer.size <= size) {
        if (memcpy_s(data, size, (unsigned char*)(info.virAddr) + playImpl->buffer.offset,
            playImpl->buffer.size) != EOK) {
            return -1;
        }
        *flags = (playImpl->buffer.flag == BUFFER_FLAG_EOS) ? DATA_FLAG_EOS : DATA_FLAG_PARTIAL_FRAME;
        readLen = playImpl->buffer.size;
        playImpl->buffer.offset = 0;
        playImpl->buffer.size = info.size;
        playImpl->bufferSource->QueIdleBuffer(&playImpl->buffer);
        playImpl->buffer.idx = -1;
    } else {
        if (memcpy_s(data, size, (unsigned char*)(info.virAddr) + playImpl->buffer.offset, size) != EOK) {
            return -1;
        }
        playImpl->buffer.offset += size;
        playImpl->buffer.size -= size;
        *flags = DATA_FLAG_PARTIAL_FRAME;
        readLen = size;
    }
    return readLen;
}

int32_t Player::PlayerImpl::SetStreamSource(const Source &source)
{
    MEDIA_INFO_LOG("process in");
    std::string mimeType;
    Format format;
    m_isStreamSource = true;
    format.CopyFrom(source.GetSourceStreamFormat());
    if (format.GetStringValue(CODEC_MIME, mimeType) != true || mimeType.length() == 0) {
        MEDIA_ERR_LOG("get mime type failed");
        return -1;
    }
    if (strcmp(mimeType.c_str(), MIME_AUDIO_AAC) != 0) {
        MEDIA_ERR_LOG("mime_type[%s] error, current only support:%s", mimeType.c_str(), MIME_AUDIO_AAC);
        return -1;
    }
    bufferSource = std::make_shared<BufferSource>();
    if (bufferSource == NULL) {
        MEDIA_ERR_LOG("new BufferSource failed");
        return -1;
    }
    bufferSource->Init();
    std::shared_ptr<StreamSource> stream = source.GetSourceStream();
    streamCallback = std::make_shared<AdapterStreamCallback>(stream, bufferSource);
    if (streamCallback == nullptr || streamCallback.get() == nullptr) {
        MEDIA_ERR_LOG("new AdapterStreamCallback failed");
        return -1;
    }
    streamCallback->Init();
    stream->SetStreamCallback(streamCallback);

    BufferStream sourceTmp;
    sourceTmp.handle = this;
    sourceTmp.ReadData = ReadData;
    sourceTmp.GetReadableSize = GetReadableSize;
    int ret = m_player->SetDataSource(sourceTmp);
    if (ret != 0) {
        MEDIA_ERR_LOG("HI_LITEPLAYER_SetDataSource  exec failed");
        return -1;
    }
    return 0;
}
}  // namespace Media
}  // namespace OHOS
