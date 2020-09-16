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

#include "liteplayer.h"

#include "hi_liteplayer_err.h"
#include "liteplayer_comm.h"
#include <sys/prctl.h>
#include <sys/time.h>
#include <unistd.h>
#include "decoder.h"

using OHOS::Media::PlayerSource;
using OHOS::Media::SinkManager;
using OHOS::Media::Decoder;

namespace OHOS {
namespace Media {
const uint32_t PLAYER_MPF_MBUF_SIZE = 624640;
/* DEFAULT_VID_BUFSIZE: 2 * 1024 * 1024 */
const uint32_t DEFAULT_VID_BUFSIZE = 2097152;
/* DEFAULT_AUD_BUFSIZE: 256 * 1024 */
const uint32_t DEFAULT_AUD_BUFSIZE = 262144;

const uint32_t GET_BUFFER_TIMEOUT_MS = 100u;
const uint32_t RENDER_FULL_SLEEP_TIME_US = 5000u;
const uint32_t RENDER_EOS_SLEEP_TIME_US = 3000000u;
const uint32_t DECODER_MAX_WIDTH = 1920;
const uint32_t DECODER_MAX_HEIGTH = 1080;
const uint32_t QUEUE_BUFFER_FULL_SLEEP_TIME_US = 5000u;

namespace {
    /* playing position notify interval in ms */
    const uint32_t DEFAULT_POS_NOFITY_INTERVAL = 300;
}

#define CHECK_NULL_RETURN(value, ret, printfString) \
do { \
    if ((value) == nullptr) { \
        MEDIA_ERR_LOG("LitePlayer::%s:%d %s", __func__, __LINE__, \
            printfString ? printfString : " "); \
        return (ret); \
    } \
} while (0)

#define CHECK_FAILED_RETURN(value, target, ret, printfString) \
do { \
    if (value != target) { \
        MEDIA_ERR_LOG("LitePlayer::%s:%d %s", __func__, __LINE__, \
            printfString ? printfString : " "); \
        return ret; \
    } \
} while (0)

#define CHECK_STATE_SAME(srcState, dstState)                                                                         \
    do {                                                                                                             \
        if ((dstState) == (srcState)) {                                                                              \
            MEDIA_INFO_LOG("current play state already be %d", (dstState)); \
            return HI_SUCCESS;                                                                                       \
        }                                                                                                            \
    } while (0)

const int32_t  SS2US = 1000000;
const int32_t US2MS = 1000;

static int64_t GetCurTimeUs()
{
    struct timeval ts = {};
    gettimeofday(&ts, nullptr);
    return (((int64_t)ts.tv_sec) * SS2US) + ((int64_t)ts.tv_usec);
}

static int64_t GetCurTimeMs()
{
    int64_t curTimeUs = GetCurTimeUs();
    return (int64_t)(curTimeUs / US2MS);
}

static void CondTimeWait(pthread_cond_t &cond, pthread_mutex_t &mutex, uint32_t delayUs)
{
    uint32_t tmpUs;
    struct timeval ts = {};
    struct timespec outtime = {};
    gettimeofday(&ts, nullptr);
    ts.tv_sec += (delayUs / SS2US);
    tmpUs = delayUs % SS2US;

    if (ts.tv_usec + tmpUs > SS2US) {
        outtime.tv_sec = ts.tv_sec + 1;
        outtime.tv_nsec = ((ts.tv_usec + tmpUs) - SS2US) * 1000;
    } else {
        outtime.tv_sec = ts.tv_sec;
        outtime.tv_nsec = (ts.tv_usec + tmpUs) * 1000;
    }
    pthread_cond_timedwait(&cond, &mutex, &outtime);
}

LitePlayer::LitePlayer() : m_stateMachine(nullptr), m_observer(nullptr), m_isInited(false),
    m_isNeedPause(false),
    m_isFirstFramePaused(false), m_pauseMode(false), m_isPlayEnd(false), m_isVidPlayEos(false),
    m_isAudPlayEos(false), m_cachedPacket(false), m_lastRendPos(0), m_lastNotifyTime(0),
    m_tplayMode(PLAYER_TPLAY_ONLY_I_FRAME), m_lastReadPktStrmIdx(-1), m_lastReadPktPts(0), m_lastSendPktPts(0),
    m_curSeekOffset(0), m_isVideoStarted(false), m_isAudioStarted(false), m_isVidContinueLost(false),
    m_strmReadEnd(false), m_isPlayErr(false), m_isTplayLastFrame(false), m_isTplayStartRead(false),
    m_lastSendVdecPts(AV_INVALID_PTS), m_lastSendAdecPts(AV_INVALID_PTS), paused(false), schThreadExit(false),
    loop_(false), hasRenderAudioEos_(false), hasRenderVideoEos_(false), renderSleepTime_(0), leftVolume_(-1.0f),
    rightVolume_(-1.0f), schProcess(-1), seekToTimeMs_(-1), m_sourceType_(SOURCE_TYPE_BUT), m_fd_(-1),
    m_playerSource_(nullptr), m_sinkManager_(nullptr), audioDecoder_(nullptr), videoDecoder_(nullptr)
{
    m_eventCallback.player = nullptr;
    m_eventCallback.callbackFun = nullptr;
    m_fmtFileInfo = {};
    m_fmtFileInfo.s32UsedAudioStreamIndex = HI_DEMUXER_NO_MEDIA_STREAM;
    m_fmtFileInfo.s32UsedVideoStreamIndex = HI_DEMUXER_NO_MEDIA_STREAM;
    m_playerParam = {};
    m_formatPacket = {};
    m_tplayAttr.direction = TPLAY_DIRECT_BUTT;
    m_tplayAttr.speed = 1.0;
    m_stream_ = {};
    streamAttr_ = {};
    vdecAttr_ = {};
    adecAttr_ = {};
    audioCachedOutBuffer_ = {};
    videoCachedOutBuffer_ = {};
    m_surface = nullptr;
}

LitePlayer::~LitePlayer()
{
    (void)Deinit();
    if (m_stateMachine !=  nullptr) {
        delete m_stateMachine;
        m_stateMachine = nullptr;
    }
    if (m_observer !=  nullptr) {
        delete m_observer;
        m_observer = nullptr;
    }
    (void)AvplayDestroy();
}

PlayerStatus LitePlayer::GetState(void)
{
    CHECK_NULL_RETURN(m_stateMachine, PLAY_STATUS_BUTT, "m_stateMachine nullptr");
    return m_stateMachine->GetCurState();
}

int32_t LitePlayer::InitAttr(const PlayerControlParam &createParam)
{
    if (memset_s(&m_fmtFileInfo, sizeof(m_fmtFileInfo), 0x00, sizeof(m_fmtFileInfo)) != EOK) {
        MEDIA_ERR_LOG("set m_fmtFileInfo fail");
        return HI_ERR_LITEPLAYER_MEM_SET;
    }
    m_fmtFileInfo.s32UsedAudioStreamIndex = HI_DEMUXER_NO_MEDIA_STREAM;
    m_fmtFileInfo.s32UsedVideoStreamIndex = HI_DEMUXER_NO_MEDIA_STREAM;
    if (memset_s(&m_playerParam, sizeof(m_playerParam), 0x00, sizeof(m_playerParam)) != EOK) {
        MEDIA_ERR_LOG("set m_playerParam fail");
        return HI_ERR_LITEPLAYER_MEM_SET;
    }
    if (memset_s(&m_formatPacket, sizeof(m_formatPacket), 0x00, sizeof(m_formatPacket)) != EOK) {
        MEDIA_ERR_LOG("set m_formatPacket fail");
        return HI_ERR_LITEPLAYER_MEM_SET;
    }
    if (memset_s(&m_tplayAttr, sizeof(m_tplayAttr), 0x00, sizeof(m_tplayAttr)) != EOK) {
        MEDIA_ERR_LOG("set m_tplayAttr fail");
        return HI_ERR_LITEPLAYER_MEM_SET;
    }
    if (memset_s(&streamAttr_, sizeof(streamAttr_), 0x00, sizeof(streamAttr_)) != EOK) {
        MEDIA_ERR_LOG("set m_streamAttr fail");
        return HI_FAILURE;
    }
    if (memset_s(&vdecAttr_, sizeof(vdecAttr_), 0x00, sizeof(vdecAttr_)) != EOK) {
        MEDIA_ERR_LOG("set m_vdecAttr fail");
        return HI_FAILURE;
    }
    if (memset_s(&adecAttr_, sizeof(adecAttr_), 0x00, sizeof(adecAttr_)) != EOK) {
        MEDIA_ERR_LOG("set m_adecAttr fail");
        return HI_FAILURE;
    }
    streamAttr_.playMode = RENDER_MODE_NORMAL;
    streamAttr_.videoBufSize = DEFAULT_VID_BUFSIZE;
    streamAttr_.audioBufSize = DEFAULT_AUD_BUFSIZE;

    m_lastReadPktPts = 0;
    m_lastSendPktPts = 0;
    m_pauseMode = createParam.bPauseMode;
    if (memcpy_s(&m_playerParam, sizeof(m_playerParam), &createParam, sizeof(PlayerControlParam)) != EOK) {
        MEDIA_ERR_LOG("copy m_playerParam fail");
    }
    m_playerParam.u32PlayPosNotifyIntervalMs = (createParam.u32PlayPosNotifyIntervalMs == 0) ?
        DEFAULT_POS_NOFITY_INTERVAL : createParam.u32PlayPosNotifyIntervalMs;
    return HI_SUCCESS;
}

int32_t LitePlayer::Init(const PlayerControlParam &createParam)
{
    MEDIA_INFO_LOG("Init int");
    if (m_isInited) {
        MEDIA_ERR_LOG("already be inited");
        return HI_SUCCESS;
    }
    if (pthread_mutex_init(&m_demuxMutex, nullptr) != 0) {
        MEDIA_ERR_LOG("m_demuxMutex init failed");
        return HI_FAILURE;
    }
    int32_t ret = InitAttr(createParam);
    if (ret != HI_SUCCESS) {
        goto DEL_MUTEX;
    }
    m_stateMachine = new(std::nothrow) PlayerControlStateMachine(*this);
    if (m_stateMachine == nullptr) {
        MEDIA_ERR_LOG("new PlayerControlStateMachine failed");
        goto DEL_MUTEX;
    }
    m_observer = new(std::nothrow) PlayerControlSMObserver(*this);
    if (m_observer == nullptr) {
        MEDIA_ERR_LOG("new PlayerControlSMObserver failed");
        goto DEL_STATE;
    }
    (void)m_stateMachine->RegisterObserver(*m_observer);
    ret = m_stateMachine->Init(MAX_MSG_QUEUE_SIZE, MAX_MSG_QUEUE_PAYLOAD_SIZE);
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("init PlayerControlStateMachine failed");
        goto DEL_OBSERVER;
    }
    ret = m_stateMachine->Start();
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("start PlayerControlStateMachine failed");
        goto DEINIT_STATE;
    }
    pthread_mutex_init(&schMutex_, nullptr);
    pthread_cond_init(&schCond_, nullptr);

    m_isInited = true;
    return HI_SUCCESS;
DEINIT_STATE:
        (void)m_stateMachine->Deinit();
DEL_OBSERVER:
        delete m_observer;
        m_observer = nullptr;
DEL_STATE:
        delete m_stateMachine;
        m_stateMachine = nullptr;
DEL_MUTEX:
    (void)pthread_mutex_destroy(&m_demuxMutex);
    return HI_FAILURE;
}

int32_t LitePlayer::Deinit()
{
    if (m_isInited == false) {
        return HI_SUCCESS;
    }
    if (m_stateMachine != nullptr) {
        MsgInfo msgInfo;
        if (memset_s(&msgInfo, sizeof(msgInfo), 0x00, sizeof(msgInfo)) != EOK) {
            MEDIA_ERR_LOG("set msgInfo fail");
        }
        msgInfo.what = LITEPLAYER_MSG_HANDLEDATA;
        int32_t ret = m_stateMachine->RemoveEvent(msgInfo);
        if (ret != HI_SUCCESS) {
            MEDIA_ERR_LOG("m_stateMachine->RemoveEvent fail");
        }
        ret = m_stateMachine->Stop();
        if (ret != HI_SUCCESS) {
            MEDIA_ERR_LOG("m_stateMachine->Stop fail");
        }
        ret = m_stateMachine->Deinit();
        if (ret != HI_SUCCESS) {
            MEDIA_ERR_LOG("m_stateMachine->Deinit fail");
        }
        delete m_observer;
        m_observer = nullptr;
        delete m_stateMachine;
        m_stateMachine = nullptr;
    }
    (void)pthread_mutex_destroy(&m_demuxMutex);
    pthread_mutex_destroy(&schMutex_);
    pthread_cond_destroy(&schCond_);
    m_isInited = false;
    return HI_SUCCESS;
}

int32_t LitePlayer::RegCallback(PlayerCtrlCallbackParam &eventObserver)
{
    CHECK_NULL_RETURN(m_stateMachine, HI_ERR_LITEPLAYER_NULL_PTR, "m_stateMachine nullptr");
    MsgInfo msg;
    msg.what = LITEPLAYER_MSG_REGCALLBACK;
    msg.msgData = reinterpret_cast<void *>(&eventObserver);
    msg.msgDataLen = 0;
    return m_stateMachine->Send(msg);
}

int32_t LitePlayer::SetDataSource(const std::string filePath)
{
    CHECK_NULL_RETURN(m_stateMachine, HI_ERR_LITEPLAYER_NULL_PTR, "m_stateMachine nullptr");
    std::string mediafile = filePath;
    MsgInfo msg;
    msg.what = LITEPLAYER_MSG_SET_DATASOURCE_URI;
    msg.msgData = reinterpret_cast<void *>(&mediafile);
    msg.msgDataLen = 0;
    return m_stateMachine->Send(msg);
}

int32_t LitePlayer::SetDataSource(const int fd)
{
    CHECK_NULL_RETURN(m_stateMachine, HI_ERR_LITEPLAYER_NULL_PTR, "m_stateMachine nullptr");
    int mediaFd = fd;
    MsgInfo msg;
    msg.what = LITEPLAYER_MSG_SET_DATASOURCE_FD;
    msg.msgData = reinterpret_cast<void *>(&mediaFd);
    msg.msgDataLen = 0;
    return m_stateMachine->Send(msg);
}

int32_t LitePlayer::SetDataSource(BufferStream &stream)
{
    CHECK_NULL_RETURN(m_stateMachine, HI_ERR_LITEPLAYER_NULL_PTR, "m_stateMachine nullptr");
    MsgInfo msg;
    msg.what = LITEPLAYER_MSG_SET_DATASOURCE_STREAM;
    msg.msgData = reinterpret_cast<void *>(&stream);
    msg.msgDataLen = 0;
    return m_stateMachine->Send(msg);
}

int32_t LitePlayer::Prepare()
{
    CHECK_NULL_RETURN(m_stateMachine, HI_ERR_LITEPLAYER_NULL_PTR, "m_stateMachine nullptr");
    return m_stateMachine->Send(LITEPLAYER_MSG_PREPARE);
}

int32_t LitePlayer::Play()
{
    CHECK_NULL_RETURN(m_stateMachine, HI_ERR_LITEPLAYER_NULL_PTR, "m_stateMachine nullptr");
    int32_t ret = m_stateMachine->Send(LITEPLAYER_MSG_PLAY);
    if (ret != HI_SUCCESS) {
        MEDIA_INFO_LOG( "play failed");
    }
    return ret;
}

int32_t LitePlayer::SetVolume(VolumeAttr &volumeAttr)
{
    CHECK_NULL_RETURN(m_stateMachine, HI_ERR_LITEPLAYER_NULL_PTR, "m_stateMachine nullptr");
    VolumeAttr attr = volumeAttr;
    MsgInfo msg;
    msg.what = LITEPLAYER_MSG_SET_VOLUME;
    msg.msgData = reinterpret_cast<void *>(&attr);
    msg.msgDataLen = 0;
    return m_stateMachine->Send(msg);
}

int32_t LitePlayer::Stop()
{
    CHECK_NULL_RETURN(m_stateMachine, HI_ERR_LITEPLAYER_NULL_PTR, "m_stateMachine nullptr");
    return m_stateMachine->Send(LITEPLAYER_MSG_STOP);
}

int32_t LitePlayer::Pause()
{
    CHECK_NULL_RETURN(m_stateMachine, HI_ERR_LITEPLAYER_NULL_PTR, "m_stateMachine nullptr");
    return m_stateMachine->Send(LITEPLAYER_MSG_PAUSE);
}

int32_t LitePlayer::Seek(int64_t timeInMs)
{
    CHECK_NULL_RETURN(m_stateMachine, HI_ERR_LITEPLAYER_NULL_PTR, "m_stateMachine nullptr");
    if (m_fmtFileInfo.enVideoType == CODEC_JPEG) {
        MEDIA_ERR_LOG(
                      "seek action not support for play picture");
        return HI_ERR_LITEPLAYER_NOT_SUPPORT;
    }
    if ((m_fmtFileInfo.s64Duration > 0) && (m_fmtFileInfo.s64Duration < timeInMs)) {
        return HI_ERR_LITEPLAYER_ILLEGAL_PARAM;
    }
    if (!m_stateMachine->EventValidAtCurState(LITEPLAYER_MSG_SEEK)) {
        MEDIA_ERR_LOG(
                      "invalid event seek at current state");
        return HI_ERR_LITEPLAYER_ILLEGAL_STATE_ACTION;
    }
    seekToTimeMs_ = timeInMs;
    MEDIA_INFO_LOG( "seek %lld ms ok", timeInMs);
    return HI_SUCCESS;
}

int32_t LitePlayer::GetFileInfo(FormatFileInfo &formatInfo)
{
    CHECK_NULL_RETURN(m_stateMachine, HI_ERR_LITEPLAYER_NULL_PTR, "m_stateMachine nullptr");
    MsgInfo msg;
    msg.what = LITEPLAYER_MSG_GETFILEINFO;
    msg.msgData = &formatInfo;
    msg.msgDataLen = sizeof(FormatFileInfo);
    return m_stateMachine->Send(msg);
}

int32_t LitePlayer::SetMedia(PlayerControlStreamAttr &mediaAttr)
{
    CHECK_NULL_RETURN(m_stateMachine, HI_ERR_LITEPLAYER_NULL_PTR, "m_stateMachine nullptr");
    MsgInfo msg;
    msg.what = LITEPLAYER_MSG_SETATTR;
    msg.msgData = &mediaAttr;
    msg.msgDataLen = sizeof(PlayerControlStreamAttr);
    return m_stateMachine->Send(msg);
}

int32_t LitePlayer::SetSurface(Surface *surface)
{
    m_surface = surface;
    return 0;
}

int32_t LitePlayer::TPlay(TplayAttr tplayAttr)
{
    CHECK_NULL_RETURN(m_stateMachine, HI_ERR_LITEPLAYER_NULL_PTR, "m_stateMachine nullptr");
    MsgInfo msg;
    msg.what = LITEPLAYER_MSG_TPLAY;
    msg.msgData = &tplayAttr;
    msg.msgDataLen = sizeof(TplayAttr);
    return m_stateMachine->Send(msg);
}

void LitePlayer::ClearCachePacket()
{
    if (m_cachedPacket) {
        if (m_formatPacket.data != nullptr) {
            if (DemuxFree(m_formatPacket) < 0) {
                MEDIA_ERR_LOG("DemuxFree failed");
            }
        }
        /* end packet is null do not need to demux free */
        m_cachedPacket = false;
    }
}

int32_t LitePlayer::OnAvplayStatusChange(const void *priv, PlayerStatus status)
{
    (void)priv;
    MEDIA_INFO_LOG( "avplay onstatusChange :%d", status);
    return HI_SUCCESS;
}

void LitePlayer::OnAvplayVideoEndOfStream()
{
    if (m_stateMachine == nullptr) {
        MEDIA_INFO_LOG( "stateMachine nullptr");
        return;
    }
    if ((m_fmtFileInfo.s32UsedAudioStreamIndex == HI_DEMUXER_NO_MEDIA_STREAM ||
        m_stateMachine->GetCurState() == PLAY_STATUS_TPLAY) &&
        m_lastSendVdecPts > AV_INVALID_PTS) {
        EventCallback(HI_LITEPLAYER_EVENT_PROGRESS, &m_lastSendVdecPts);
    }
    m_isVidPlayEos = true;
    m_isPlayEnd = IsPlayEos() ? true : m_isPlayEnd;
}

int32_t LitePlayer::OnAvplayEvent(const void *priv, const EventCbType event)
{
    PlayerControlError playerError;
    MEDIA_DEBUG_LOG( "handleEvent %d", event);

    switch (event) {
        case EVNET_VIDEO_PLAY_EOS:
            OnAvplayVideoEndOfStream();
            break;
        case EVNET_VIDEO_PLAY_SOS:
            MEDIA_INFO_LOG( "video sos recv");
            break;
        case EVNET_AUDIO_PLAY_EOS:
            CHECK_NULL_RETURN(m_stateMachine, HI_ERR_LITEPLAYER_NULL_PTR, "m_stateMachine nullptr");
            if (m_stateMachine->GetCurState() != PLAY_STATUS_TPLAY) {
                m_isAudPlayEos = true;
                m_isPlayEnd = IsPlayEos() ? true : m_isPlayEnd;
                if (m_lastSendAdecPts > AV_INVALID_PTS) {
                    EventCallback(HI_LITEPLAYER_EVENT_PROGRESS, &m_lastSendAdecPts);
                }
            }
            break;
        case EVNET_VIDEO_RUNNING_ERR:
        case EVNET_AUDIO_RUNNING_ERR:
            playerError = HI_LITEPLAYER_ERROR_VID_PLAY_FAIL;
            m_isPlayErr = true;
            EventCallback(HI_LITEPLAYER_EVENT_ERROR, &playerError);
            break;
        case EVNET_FRAME_CONTINUE_LOST:
            m_isVidContinueLost = true;
            MEDIA_INFO_LOG( "receive avplayer frame continue lost");
            break;
        case EVNET_ON_JPEG_FRAME_RENDED:
            MEDIA_INFO_LOG( " video rended");
            break;
        case EVNET_FIRST_VIDEO_REND:
            if (m_pauseMode) {
                MEDIA_INFO_LOG( "first video rended");
                m_isNeedPause = true;
            }
            break;

        default:
            break;
    }
    return HI_SUCCESS;
}

int32_t LitePlayer::PauseResume(void)
{
    CHECK_NULL_RETURN(m_sinkManager_, HI_ERR_LITEPLAYER_NULL_PTR, "sinkManager_ nullptr");
    int32_t ret = m_sinkManager_->Resume();
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("m_render resume  failed Ret: %d", ret);
        return ret;
    }
    pthread_mutex_lock(&schMutex_);
    paused = false;
    pthread_cond_signal(&schCond_);
    pthread_mutex_unlock(&schMutex_);
    return HI_SUCCESS;
}

int32_t LitePlayer::TPlayResume(void)
{
    CHECK_NULL_RETURN(m_sinkManager_, HI_ERR_LITEPLAYER_NULL_PTR, "sinkManager_ nullptr");
    int32_t ret = m_sinkManager_->Pause();
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("m_render pause  failed Ret: %d", ret);
        return ret;
    }
    ret = m_sinkManager_->Resume();
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("m_render resume  failed Ret: %d", ret);
        return ret;
    }
    return HI_SUCCESS;
}

int32_t LitePlayer::OnSwitchTPlay2Play()
{
    int32_t ret = HI_SUCCESS;

    if (m_tplayMode != PLAYER_TPLAY_FULL_PLAY) {
        ret = TPlayResetBuffer();
        if (ret != HI_SUCCESS) {
            MEDIA_ERR_LOG("TPlayResetBuffer failed , ret:%d", ret);
            return ret;
        }
        ret = DemuxSeek(m_fmtFileInfo.s32UsedVideoStreamIndex, m_lastReadPktPts, FORMAT_SEEK_MODE_FORWARD_KEY);
        if (ret != HI_SUCCESS) {
            MEDIA_ERR_LOG("DemuxSeek failed , ret:%d", ret);
            return ret;
        }
        m_strmReadEnd = false;
    }
    ret = TPlayResume();
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("HiAvplayResume failed , ret:%d", ret);
        return ret;
    }
    return ret;
}

int32_t LitePlayer::CheckMediaInfo(void)
{
    if (m_fmtFileInfo.s32UsedAudioStreamIndex >= HI_DEMUXER_RESOLUTION_CNT
        || m_fmtFileInfo.s32UsedVideoStreamIndex >= HI_DEMUXER_RESOLUTION_CNT) {
        MEDIA_ERR_LOG("input file error video track: %d audio %d",
                      m_fmtFileInfo.s32UsedVideoStreamIndex, m_fmtFileInfo.s32UsedAudioStreamIndex);
        return HI_ERR_LITEPLAYER_DEMUX_ERROR;
    }
    if (CheckMediaType(m_fmtFileInfo) != HI_SUCCESS) {
        return HI_ERR_LITEPLAYER_NOT_SUPPORT;
    }
    return HI_SUCCESS;
}

int32_t LitePlayer::SetVDecAttr(void)
{
    StreamResolution resolution = { 0 };
    if (DemuxGetResolution(m_fmtFileInfo.s32UsedVideoStreamIndex, resolution) != HI_SUCCESS) {
        MEDIA_ERR_LOG("DemuxGetResolution failed");
        return HI_FAILURE;
    }
    vdecAttr_.maxWidth = resolution.u32Width;
    vdecAttr_.maxHeight = resolution.u32Height;
    vdecAttr_.type = resolution.enVideoType;
    vdecAttr_.frameBufCnt = m_playerParam.u32VdecFrameBufCnt;
    return HI_SUCCESS;
}

int32_t LitePlayer::SetADecAttr(void)
{
    adecAttr_.bitWidth = AUDIO_BITWIDTH;
    adecAttr_.channel = m_fmtFileInfo.u32AudioChannelCnt;
    adecAttr_.sampleRate = m_fmtFileInfo.u32SampleRate;
    adecAttr_.type = m_fmtFileInfo.enAudioType;
    return HI_SUCCESS;
}

uint32_t LitePlayer::AvplayDefaultVideoBufSize(uint32_t width, uint32_t height)
{
    uint32_t bufSize;
    if (width >= PLAYER_8K_WIDTH && height >= PLAYER_8K_HEIGHT) {
        bufSize = PLAYER_VID_BUF_SIZE_LEVEL1;
    } else if (width >= PLAYER_4K_WIDTH && height >= PLAYER_4K_HEIGHT) {
        bufSize = PLAYER_VID_BUF_SIZE_LEVEL2;
    } else if (width >= PLAYER_1080P_WIDTH && height >= PLAYER_1080P_HEIGHT) {
        bufSize = PLAYER_VID_BUF_SIZE_LEVEL3;
    } else {
        bufSize = PLAYER_VID_BUF_SIZE_LEVEL4;
    }
    return bufSize;
}

int32_t LitePlayer::SetStreamAttr()
{
    if (m_pauseMode) {
        streamAttr_.playMode = RENDER_MODE_PAUSE_AFTER_PLAY;
    }
    if (m_fmtFileInfo.enVideoType == CODEC_JPEG) {
        if (streamAttr_.videoBufSize < PLAYER_MPF_ESBUF_MIN && m_playerParam.u32VideoEsBufSize != 0) {
            MEDIA_ERR_LOG("videoEsBufSize:%u for jpeg less than min %d",
                m_playerParam.u32VideoEsBufSize, PLAYER_MPF_ESBUF_MIN);
            return HI_ERR_LITEPLAYER_ILLEGAL_PARAM;
        }
    }

    if (m_fmtFileInfo.s32UsedVideoStreamIndex != HI_DEMUXER_NO_MEDIA_STREAM) {
        StreamResolution resolution = { 0 };
        if (DemuxGetResolution(m_fmtFileInfo.s32UsedVideoStreamIndex, resolution) != HI_SUCCESS) {
            MEDIA_ERR_LOG("DemuxGetResolution failed");
            return HI_ERR_LITEPLAYER_ILLEGAL_PARAM;
        }
        streamAttr_.videoBufSize = (m_playerParam.u32VideoEsBufSize) ? (m_playerParam.u32VideoEsBufSize) :
            AvplayDefaultVideoBufSize(resolution.u32Width, resolution.u32Height);
    }
    if (m_fmtFileInfo.s32UsedAudioStreamIndex != HI_DEMUXER_NO_MEDIA_STREAM) {
        streamAttr_.audioBufSize = (m_playerParam.u32AudioEsBufSize) ? (m_playerParam.u32AudioEsBufSize) :
            streamAttr_.audioBufSize;
    }

    if (m_sinkManager_ != nullptr) {
        m_sinkManager_->SetRenderMode(streamAttr_.playMode);
    }
    return HI_SUCCESS;
}

int32_t LitePlayer::SetDecoderAndStreamAttr(void)
{
    int ret;

    if (m_fmtFileInfo.s32UsedAudioStreamIndex != HI_DEMUXER_NO_MEDIA_STREAM) {
        ret = SetADecAttr();
        if (ret != HI_SUCCESS) {
            return ret;
        }
    }
    if (m_fmtFileInfo.s32UsedVideoStreamIndex != HI_DEMUXER_NO_MEDIA_STREAM) {
        ret = SetVDecAttr();
        if (ret != HI_SUCCESS) {
            return ret;
        }
    }
    ret = SetStreamAttr();
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("SetStreamAttr failed ret:%x", ret);
    }
    return ret;
}

static AvCodecMime TransformCodecFormatToAvCodecMime(CodecFormat format)
{
    AvCodecMime mime = MEDIA_MIMETYPE_INVALID;
    switch (format) {
        case CODEC_H264:
            mime = MEDIA_MIMETYPE_VIDEO_AVC;
            break;
        case CODEC_H265:
            mime = MEDIA_MIMETYPE_VIDEO_HEVC;
            break;
        case CODEC_JPEG:
            mime = MEDIA_MIMETYPE_IMAGE_JPEG;
            break;
        case CODEC_AAC:
            mime = MEDIA_MIMETYPE_AUDIO_AAC;
            break;
        default:
            MEDIA_ERR_LOG("not support codec:%d", format);
            break;
    }
    return mime;
}

int32_t LitePlayer::DecoderStart(void)
{
    if (m_fmtFileInfo.s32UsedAudioStreamIndex == -1 && m_fmtFileInfo.s32UsedVideoStreamIndex == -1) {
        MEDIA_ERR_LOG("not decoder need start");
        return -1;
    }
    printf("LitePlayer::DecoderStart streamid:%d-%d",
        m_fmtFileInfo.s32UsedAudioStreamIndex, m_fmtFileInfo.s32UsedVideoStreamIndex);
    if (m_fmtFileInfo.s32UsedAudioStreamIndex != -1) {
        if (m_fmtFileInfo.enAudioType != CODEC_AAC) {
            MEDIA_ERR_LOG("DecoderStart not support codec:%d",
                m_fmtFileInfo.enAudioType);
            return -1;
        }
        audioDecoder_ = std::make_shared<Decoder>();
        CHECK_NULL_RETURN(audioDecoder_, -1, "new decoder failed");
        AvAttribute attr;
        attr.type = AUDIO_DECODER;
        attr.adecAttr.mime = MEDIA_MIMETYPE_AUDIO_AAC;
        attr.adecAttr.priv = nullptr;
        attr.adecAttr.bufSize = 1024;
        const std::string audioName = "codec.aac.soft.decoder";
        int32_t ret = audioDecoder_->CreateHandle(audioName, attr);
        CHECK_FAILED_RETURN(ret, 0, -1, "create audio decoder failed");
        ret = audioDecoder_->StartDec();
        CHECK_FAILED_RETURN(ret, 0, -1, "start audio decoder failed");
        printf("audio decoder started");
    }
    if (m_fmtFileInfo.s32UsedVideoStreamIndex != -1) {
        AvAttribute attr;
        AvCodecMime mime = TransformCodecFormatToAvCodecMime(m_fmtFileInfo.enVideoType);
        if (mime == MEDIA_MIMETYPE_INVALID) {
            MEDIA_ERR_LOG("DecoderStart not support codec:%d",
                m_fmtFileInfo.enVideoType);
            return -1;
        }
        videoDecoder_ = std::make_shared<Decoder>();
        CHECK_NULL_RETURN(videoDecoder_, -1, "new decoder failed");
        attr.type = VIDEO_DECODER;
        attr.vdecAttr.mime = mime;
        attr.vdecAttr.priv = nullptr;
        attr.vdecAttr.bufSize = 0;
        attr.vdecAttr.maxWidth = DECODER_MAX_WIDTH;
        attr.vdecAttr.maxHeight = DECODER_MAX_HEIGTH;
        const std::string videoName = "codec.avc.soft.decoder";
        int32_t ret = videoDecoder_->CreateHandle(videoName, attr);
        CHECK_FAILED_RETURN(ret, 0, -1, "create video decoder failed");
        ret = videoDecoder_->StartDec();
        CHECK_FAILED_RETURN(ret, 0, -1, "start video decoder failed");
        printf("video decoder started");
    }
    return 0;
}

int32_t LitePlayer::AvplayDestroy()
{
    if (audioDecoder_ != nullptr) {
        audioDecoder_->StopDec();
        audioDecoder_->DestroyHandle();
    }
    if (videoDecoder_ != nullptr) {
        videoDecoder_->StopDec();
        videoDecoder_->DestroyHandle();
    }
    return 0;
}

int32_t LitePlayer::AvplayStop()
{
    OutputInfo outInfo;

    if (static_cast<intptr_t>(schProcess) != -1) {
        pthread_mutex_lock(&schMutex_);
        schThreadExit = true;
        pthread_cond_signal(&schCond_);
        pthread_mutex_unlock(&schMutex_);
        pthread_join(schProcess, nullptr);
    }
    if (m_sinkManager_ != nullptr) {
        m_sinkManager_->Stop();
    }
    if (audioDecoder_ != nullptr && m_sinkManager_ != nullptr) {
        while (m_sinkManager_->DequeReleaseFrame(true, outInfo) == 0) {
            audioDecoder_->QueueOutputBuffer(outInfo, GET_BUFFER_TIMEOUT_MS);
        }
        audioDecoder_->StopDec();
    }
    if (videoDecoder_ != nullptr && m_sinkManager_ != nullptr) {
        while (m_sinkManager_->DequeReleaseFrame(true, outInfo) == 0) {
            videoDecoder_->QueueOutputBuffer(outInfo, GET_BUFFER_TIMEOUT_MS);
        }
        videoDecoder_->StopDec();
    }
    m_isVideoStarted = false;
    m_isAudioStarted = false;

    return HI_SUCCESS;
}


int32_t LitePlayer::AddAudioSink(void)
{
    if (m_isAudioStarted == true) {
        MEDIA_ERR_LOG("audio already started");
        return HI_SUCCESS;
    }

    SinkAttr attr;
    attr.sinkType = SINK_TYPE_AUDIO;
    attr.trackId = m_fmtFileInfo.s32UsedAudioStreamIndex;
    attr.audAttr.format = m_fmtFileInfo.enAudioType;
    attr.audAttr.sampleFmt = 2;
    attr.audAttr.sampleRate = adecAttr_.sampleRate;
    attr.audAttr.channel = m_fmtFileInfo.u32AudioChannelCnt;
    attr.audAttr.volume = 6;

    if (m_sinkManager_->AddNewSink(attr) != 0) {
        MEDIA_ERR_LOG("AddNewSink  failed");
        return -1;
    }
    m_isAudioStarted = true;
    return HI_SUCCESS;
}

int32_t LitePlayer::AddVideoSink()
{
    if (m_isVideoStarted == true) {
        return HI_SUCCESS;
    }

    SinkAttr attr;
    attr.sinkType = SINK_TYPE_VIDEO;
    attr.trackId = m_fmtFileInfo.s32UsedVideoStreamIndex;
    attr.vidAttr.width = m_fmtFileInfo.u32Width;
    attr.vidAttr.height = m_fmtFileInfo.u32Height;
    attr.vidAttr.frameRate = m_fmtFileInfo.fFrameRate;
    attr.vidAttr.format = m_fmtFileInfo.enVideoType;
    attr.vidAttr.surface = m_surface;
    if (m_sinkManager_->AddNewSink(attr) != 0) {
        MEDIA_ERR_LOG("AddNewSink  failed");
        return -1;
    }
    m_isVideoStarted = true;
    return HI_SUCCESS;
}


int32_t LitePlayer::SinkStart(void)
{
    int32_t ret = HI_SUCCESS;
    m_sinkManager_ = std::make_shared<SinkManager>();
    if (m_sinkManager_ == nullptr) {
        MEDIA_ERR_LOG("sinkManager new failed");
        return -1;
    }

    if (m_fmtFileInfo.s32UsedVideoStreamIndex != HI_DEMUXER_NO_MEDIA_STREAM && !m_isVideoStarted) {
        ret = AddVideoSink();
        if (ret != HI_SUCCESS) {
            MEDIA_ERR_LOG("HiAvplayStart video error, ret:0x%x", ret);
            goto FAILED;
        }
        m_isVideoStarted = true;
    }
    if (m_fmtFileInfo.s32UsedAudioStreamIndex != HI_DEMUXER_NO_MEDIA_STREAM && !m_isAudioStarted) {
        ret = AddAudioSink();
        if (ret != HI_SUCCESS) {
            MEDIA_ERR_LOG("HiAvplayStart audio error, ret:0x%x", ret);
            goto FAILED;
        }
        m_isAudioStarted = true;
    }

    PlayEventCallback callback;
    GetPlayElementEventCallBack(callback);
    ret = m_sinkManager_->RegisterCallBack(callback);
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("m_sinkManager_ register callbak failed ret:%x", ret);
    }

    if (m_sinkManager_->Start() != 0) {
        MEDIA_ERR_LOG("sink Start  failed\n");
        return -1;
    }
    if (leftVolume_ >= 0.0f || rightVolume_ >= 0.0f) {
        m_sinkManager_->SetVolume(leftVolume_, rightVolume_);
    }
    return HI_SUCCESS;

FAILED:
    return ret;
}

int32_t LitePlayer::AvplaySendStreamEos()
{
    return HI_SUCCESS;
}

int32_t LitePlayer::DemuxStop()
{
    CHECK_NULL_RETURN(m_playerSource_, HI_ERR_LITEPLAYER_NULL_PTR, "playerSource_ nullptr");
    return m_playerSource_->Stop();;
}

int32_t LitePlayer::DemuxRead(FormatFrame &fmtFrame)
{
    CHECK_NULL_RETURN(m_playerSource_, HI_ERR_LITEPLAYER_NULL_PTR, "playerSource_ nullptr");
    int ret = m_playerSource_->ReadFrame(fmtFrame);
    // Check consistency of fmtFrame
    if ((ret == HI_SUCCESS) && (fmtFrame.data != nullptr) && (fmtFrame.len == 0)) {
        MEDIA_ERR_LOG("DemuxRead ERROR : u32Size is invalid");
        ret = HI_FAILURE;
    }
    return ret;
}

int32_t LitePlayer::DemuxFree(FormatFrame &fmtFrame)
{
    CHECK_NULL_RETURN(m_playerSource_, HI_ERR_LITEPLAYER_NULL_PTR, "playerSource_ nullptr");
    int ret = m_playerSource_->FreeFame(fmtFrame);
    fmtFrame.data = nullptr;
    fmtFrame.len = 0;
    fmtFrame.trackId = -1;
    return ret;
}

int32_t LitePlayer::DemuxSeek(int32_t streamIndex, int64_t m_sec, FormatSeekMode flag)
{
    CHECK_NULL_RETURN(m_playerSource_, HI_ERR_LITEPLAYER_NULL_PTR, "playerSource_ nullptr");
    return m_playerSource_->Seek(streamIndex, m_sec, flag);
}

int32_t LitePlayer::DemuxGetinfo(FormatFileInfo &fmtInfo)
{
    CHECK_NULL_RETURN(m_playerSource_, HI_ERR_LITEPLAYER_NULL_PTR, "playerSource_ nullptr");
    return m_playerSource_->GetFileInfo(fmtInfo);
}

int32_t LitePlayer::DemuxSetattr(FormatMediaAttr &fmtInfo)
{
    int32_t retVid = m_playerSource_->SelectTrack(FORMAT_INVALID_PROGRAM_ID, fmtInfo.s32VidStreamId);
    if (retVid != HI_SUCCESS) {
        MEDIA_ERR_LOG("SelectTrack VidStreamId failed:%d", retVid);
    }
    int32_t retAud = m_playerSource_->SelectTrack(FORMAT_INVALID_PROGRAM_ID, fmtInfo.s32AudStreamId);
    if (retAud != HI_SUCCESS) {
        MEDIA_ERR_LOG("SelectTrack AudStreamId failed:%d", retAud);
    }
    if (retVid == HI_SUCCESS && retAud == HI_SUCCESS) {
        return HI_SUCCESS;
    } else {
        return HI_FAILURE;
    }
}

int32_t LitePlayer::DemuxGetResolution(int32_t streamIdx, StreamResolution &resolution)
{
    if (streamIdx == HI_DEMUXER_NO_MEDIA_STREAM) {
        MEDIA_ERR_LOG("stream id [%d] in invalid", streamIdx);
        return HI_FAILURE;
    }

    for (uint32_t i = 0; i < HI_DEMUXER_RESOLUTION_CNT; i++) {
        if (m_fmtFileInfo.stSteamResolution[i].s32VideoStreamIndex == streamIdx) {
            resolution.enVideoType = m_fmtFileInfo.stSteamResolution[i].enVideoType;
            resolution.s32VideoStreamIndex = m_fmtFileInfo.stSteamResolution[i].s32VideoStreamIndex;
            resolution.u32Width = m_fmtFileInfo.stSteamResolution[i].u32Width;
            resolution.u32Height = m_fmtFileInfo.stSteamResolution[i].u32Height;
            return HI_SUCCESS;
        }
    }

    MEDIA_ERR_LOG("not found stream[%d] in file", streamIdx);
    return HI_FAILURE;
}

// message begin
int32_t LitePlayer::DoRegCallback(PlayerCtrlCallbackParam &eventCallback)
{
    if (m_eventCallback.callbackFun != nullptr) {
        MEDIA_WARNING_LOG(
            "you have reg callback,now the before callback fun pointer will be overwrite");
    }
    m_eventCallback = eventCallback;
    return HI_SUCCESS;
}

int32_t LitePlayer::DoSetDataSource(const std::string filepath)
{
    m_filePath_ = filepath;
    m_sourceType_ = SOURCE_TYPE_URI;
    return HI_SUCCESS;
}

int32_t LitePlayer::DoSetDataSource(const int32_t fd)
{
    m_fd_ = fd;
    m_sourceType_ = SOURCE_TYPE_FD;
    return HI_SUCCESS;
}

int32_t LitePlayer::DoSetDataSource(BufferStream &stream)
{
    m_stream_ = stream;
    m_sourceType_ = SOURCE_TYPE_STREAM;
    return HI_SUCCESS;
}

int32_t LitePlayer::DoPrepare(void)
{
    CHECK_NULL_RETURN(m_stateMachine, HI_FAILURE, "m_stateMachine nullptr");
    PlayerStatus playerState = m_stateMachine->GetCurState();
    CHECK_STATE_SAME(playerState, PLAY_STATUS_PREPARED);

    if (m_eventCallback.callbackFun == nullptr) {
        MEDIA_ERR_LOG("call back functin  is not  set");
        return HI_ERR_LITEPLAYER_CALLBACK_ERROR;
    }
    m_isPlayEnd = false;
    m_isTplayStartRead = false;
    int32_t ret = SyncPrepare();
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("DO_AVPLAYER_PREPARE exec failed,s32ret:0x%x", ret);
        return HI_ERR_LITEPLAYER_OTHER;
    }
    if (m_playerParam.u32PlayPosNotifyIntervalMs >= m_fmtFileInfo.s64Duration) {
        MEDIA_WARNING_LOG(
            "play postion notify interval %d ms oversize file duration, user will never receive notify",
            m_playerParam.u32PlayPosNotifyIntervalMs);
    }
    return HI_SUCCESS;
}

void LitePlayer::ReleaseADecoderOutputFrame(void)
{
    if (audioDecoder_ == nullptr || m_sinkManager_ == nullptr) {
        return;
    }
    while (true) {
        OutputInfo outInfo = {};
        if (m_sinkManager_->DequeReleaseFrame(true, outInfo) != 0) {
            break;
        }
        audioDecoder_->QueueOutputBuffer(outInfo, GET_BUFFER_TIMEOUT_MS);
        if (m_strmReadEnd == true && hasRenderAudioEos_ == false && outInfo.timeStamp == m_lastSendAdecPts) {
            m_sinkManager_->RenderEos(true);
            hasRenderAudioEos_ = true;
            printf("[%lld] have render audio eos", GetCurTimeMs());
            if (IsPlayEos() == true) {
                m_isPlayEnd = true;
            }
        }
    }
}

void LitePlayer::RenderAudioFrame(void)
{
    if (audioDecoder_ == nullptr || m_sinkManager_ == nullptr) {
        return;
    }
    OutputInfo outInfo = {};
    CodecBufferInfo outBuf;
    outInfo.bufferCnt = 1;
    outInfo.buffers = &outBuf;
    int ret = audioDecoder_->DequeueOutputBuffer(outInfo, GET_BUFFER_TIMEOUT_MS);
    if (ret != 0) {
        outInfo.bufferCnt = 0;
        outInfo.type = AUDIO_DECODER;
        outInfo.vendorPrivate = nullptr;
    }
    ret = m_sinkManager_->RenderFrame(outInfo);
    if (ret == SINK_RENDER_FULL || ret == SINK_RENDER_DELAY) {
        renderSleepTime_ = RENDER_FULL_SLEEP_TIME_US;
    } else {
        renderSleepTime_ = 0;
    }
    ReleaseADecoderOutputFrame();
}

void LitePlayer::ReleaseVDecoderOutputFrame(void)
{
    if (videoDecoder_ == nullptr || m_sinkManager_ == nullptr) {
        return;
    }
    while (true) {
        OutputInfo outInfo = {};
        if (m_sinkManager_->DequeReleaseFrame(false, outInfo) != 0) {
            break;
        }
        videoDecoder_->QueueOutputBuffer(outInfo, GET_BUFFER_TIMEOUT_MS);
        if (m_strmReadEnd == true && hasRenderVideoEos_ == false && outInfo.timeStamp == m_lastSendVdecPts) {
            m_sinkManager_->RenderEos(false);
            hasRenderVideoEos_ = true;
            MEDIA_INFO_LOG("[%lld] have render video eos", GetCurTimeMs());
            if (IsPlayEos() == true) {
                m_isPlayEnd = true;
            }
        }
    }
}

void LitePlayer::RenderVideoFrame(void)
{
    if (videoDecoder_ == nullptr || m_sinkManager_ == nullptr) {
        return;
    }
    OutputInfo outInfo = {};
    CodecBufferInfo outBuf;
    outInfo.bufferCnt = 1;
    outInfo.buffers = &outBuf;
    int ret = videoDecoder_->DequeueOutputBuffer(outInfo, GET_BUFFER_TIMEOUT_MS);
    if (ret != 0) {
        outInfo.bufferCnt = 0;
        outInfo.type = VIDEO_DECODER;
        outInfo.vendorPrivate = nullptr;
    }
    ret = m_sinkManager_->RenderFrame(outInfo);
    if (ret == SINK_RENDER_FULL || ret == SINK_RENDER_DELAY) {
        renderSleepTime_ = RENDER_FULL_SLEEP_TIME_US;
    } else {
        renderSleepTime_ = 0;
    }
    ReleaseVDecoderOutputFrame();
}

void LitePlayer::ReortRenderPosition(void)
{
    int64_t position = -1;
    if (m_sinkManager_ == nullptr) {
        return;
    }
    m_sinkManager_->GetRenderPosition(position);
    if (position != -1 && currentPosition_ != position) {
        currentPosition_ = position;
        EventCallback(HI_LITEPLAYER_EVENT_PROGRESS, &currentPosition_);
    }
}

void* LitePlayer::DataSchProcess(void *priv)
{
    LitePlayer *play = (LitePlayer*)priv;
    CHECK_NULL_RETURN(play, nullptr, "play nullptr");

    prctl(PR_SET_NAME, "PlaySch", 0, 0, 0);
    MEDIA_INFO_LOG( "start work");
    while (true) {
        pthread_mutex_lock(&play->schMutex_);
        if (play->schThreadExit == true) {
            pthread_mutex_unlock(&play->schMutex_);
            break;
        }
        if (play->paused == true) {
            pthread_cond_wait(&play->schCond_, &play->schMutex_);
        }
        pthread_mutex_unlock(&play->schMutex_);
        play->DoSeekIfNeed();
        play->renderSleepTime_ = 0;
        play->ReadPacketAndPushToDecoder();

        /* get and render frame */
        play->RenderAudioFrame();
        play->RenderVideoFrame();
        play->ReortRenderPosition();
        if (play->m_isPlayEnd == true) {
            play->DealPlayEnd();
            play->m_isPlayEnd = false;
        }
        if (play->IsPlayEos() == true) {
            play->renderSleepTime_ = RENDER_EOS_SLEEP_TIME_US;
        }
        if (play->renderSleepTime_ > 0) {
            pthread_mutex_lock(&play->schMutex_);
            CondTimeWait(play->schCond_, play->schMutex_, play->renderSleepTime_);
            pthread_mutex_unlock(&play->schMutex_);
        }
    }
    pthread_mutex_lock(&play->schMutex_);
    play->schThreadExit = true;
    pthread_mutex_unlock(&play->schMutex_);
    MEDIA_INFO_LOG("end work");
    return nullptr;
}

int32_t LitePlayer::DoPlay()
{
    CHECK_NULL_RETURN(m_stateMachine, HI_ERR_LITEPLAYER_NULL_PTR, "m_stateMachine nullptr");
    int32_t ret = HI_SUCCESS;
    PlayerStatus playerState = m_stateMachine->GetCurState();
    CHECK_STATE_SAME(playerState, PLAY_STATUS_PLAY);
    if (playerState == PLAY_STATUS_TPLAY) {
        ret = OnSwitchTPlay2Play();
        if (ret != HI_SUCCESS) {
            MEDIA_ERR_LOG("OnSwitchTPlay2Play");
            return ret;
        }
    } else if (playerState == PLAY_STATUS_PREPARED) {
        ret = CheckMediaInfo();
        if (ret != HI_SUCCESS) {
            MEDIA_ERR_LOG("CheckMediaInfo failed ret:%x", ret);
            return ret;
        }
        ret = SetDecoderAndStreamAttr();
        if (ret != HI_SUCCESS) {
            MEDIA_ERR_LOG("SinkManagerCreate failed,s32ret:%d", ret);
            return ret;
        }
        ret = DecoderStart();
        if (ret != HI_SUCCESS) {
            MEDIA_ERR_LOG("HiAvplayStart failed,s32ret:%d", ret);
            return ret;
        }

        ret = SinkStart();
        if (ret != HI_SUCCESS) {
            MEDIA_ERR_LOG("HiAvplayStart failed,s32ret:%d", ret);
            return ret;
        }
        if (m_playerSource_ != nullptr) {
            ret = m_playerSource_->Start();
            if (ret != HI_SUCCESS) {
                MEDIA_ERR_LOG("HiAvplayStart failed,s32ret:%d", ret);
                return ret;
            }
        }
        pthread_mutex_lock(&schMutex_);
        paused = true;
        pthread_mutex_unlock(&schMutex_);
        int32_t ret = pthread_create(&schProcess, nullptr, DataSchProcess, this);
        if (ret != 0) {
            MEDIA_ERR_LOG("pthread_create failed %d", ret);
            pthread_mutex_lock(&schMutex_);
            schThreadExit = 0;
            pthread_mutex_unlock(&schMutex_);
            return -1;
        }
        pthread_mutex_lock(&schMutex_);
        paused = false;
        pthread_cond_signal(&schCond_);
        pthread_mutex_unlock(&schMutex_);
    } else if (playerState == PLAY_STATUS_PAUSE) {
        ret = PauseResume();
        if (ret != HI_SUCCESS) {
            MEDIA_ERR_LOG("HiAvplayStart failed,s32ret:%d", ret);
            return ret;
        }
    } else {
        return HI_ERR_LITEPLAYER_ILLEGAL_STATE_ACTION;
    }
    m_strmReadEnd = false;
    m_isVidPlayEos = false;
    m_isAudPlayEos = false;
    return ret;
}

int32_t LitePlayer::DoSetVolume(VolumeAttr &volumeAttr)
{
    CHECK_NULL_RETURN(m_sinkManager_, HI_ERR_LITEPLAYER_NULL_PTR, "sinkManager_ nullptr");
    leftVolume_ = volumeAttr.leftVolume;
    rightVolume_ = volumeAttr.rightVolume;
    if (m_sinkManager_ == nullptr) {
        return HI_SUCCESS;
    }
    return m_sinkManager_->SetVolume(volumeAttr.leftVolume, volumeAttr.rightVolume);
}

int32_t LitePlayer::ReadPacket()
{
    int32_t ret = HI_SUCCESS;
    if (m_cachedPacket) {
        return ret;
    }

    // use mbuffer size as mpf slice len
    if (m_fmtFileInfo.enVideoType == CODEC_JPEG) {
#ifndef __HI3518EV300__
        m_formatPacket.len = PLAYER_MPF_MBUF_SIZE;
#else
        m_formatPacket.len = 0;
#endif
    }
    ret = DemuxRead(m_formatPacket);
    if (ret != HI_RET_FILE_EOF && m_formatPacket.data == nullptr && m_formatPacket.len == 0) {
        return HI_RET_NODATA;
    }
    if (ret == HI_RET_FILE_EOF) {
        CHECK_FAILED_RETURN(memset_s(&m_formatPacket, sizeof(m_formatPacket), 0, sizeof(m_formatPacket)), EOK, -1,
            "memset_s failed");
        ret = HI_SUCCESS;
    } else if (ret == HI_RET_NODATA) {
        CHECK_FAILED_RETURN(memset_s(&m_formatPacket, sizeof(m_formatPacket), 0, sizeof(m_formatPacket)), EOK, -1,
            "memset_s failed");
        m_strmReadEnd = false;
        return ret;
    } else if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("DemuxRead failed , ret:%d", ret);
        NotifyError(HI_LITEPLAYER_ERROR_DEMUX_FAIL);
        return HI_FAILURE;
    }
    m_strmReadEnd = false;
    m_cachedPacket = true;

    return ret;
}

void LitePlayer::PushPacketToADecoder(void)
{
    InputInfo inputData = {};
    CodecBufferInfo inBufInfo = {};
    if (audioDecoder_ == nullptr) {
        return;
    }
    int32_t ret = audioDecoder_->DequeInputBuffer(inputData, GET_BUFFER_TIMEOUT_MS);
    if (ret != 0) {
        return;
    }
    inBufInfo.addr = m_formatPacket.data;
    inBufInfo.length = m_formatPacket.len;
    inputData.bufferCnt = 1;
    inputData.buffers = &inBufInfo;
    inputData.pts = m_formatPacket.timestampUs;
    inputData.flag = 0;
    ret = audioDecoder_->QueueInputBuffer(inputData, GET_BUFFER_TIMEOUT_MS);
    if (ret == CODEC_ERR_STREAM_BUF_FULL) {
        renderSleepTime_ = QUEUE_BUFFER_FULL_SLEEP_TIME_US;
        return;
    }
    if (m_formatPacket.data != nullptr || m_formatPacket.len != 0) {
        m_lastSendAdecPts = m_formatPacket.timestampUs;
    }
    ClearCachePacket();
}

void LitePlayer::PushPacketToVDecoder(void)
{
    InputInfo inputData = {};
    CodecBufferInfo inBufInfo = {};
    if (videoDecoder_ == nullptr) {
        return;
    }
    int32_t ret = videoDecoder_->DequeInputBuffer(inputData, GET_BUFFER_TIMEOUT_MS);
    if (ret != 0) {
        return;
    }
    inBufInfo.addr = m_formatPacket.data;
    inBufInfo.length = m_formatPacket.len;
    inputData.bufferCnt = 1;
    inputData.buffers = &inBufInfo;
    inputData.pts = m_formatPacket.timestampUs;
    inputData.flag = 0;
    ret = videoDecoder_->QueueInputBuffer(inputData, GET_BUFFER_TIMEOUT_MS);
    if (ret == CODEC_ERR_STREAM_BUF_FULL) {
        renderSleepTime_ = QUEUE_BUFFER_FULL_SLEEP_TIME_US;
        return;
    }
    if (m_formatPacket.data != nullptr || m_formatPacket.len != 0) {
        m_lastSendVdecPts = m_formatPacket.timestampUs;
    }
    ClearCachePacket();
}

int32_t LitePlayer::ReadPacketAndPushToDecoder()
{
    int32_t ret = HI_SUCCESS;
    PlayerStatus playerState;
    CHECK_NULL_RETURN(m_stateMachine, -1, "stateMachine null");
    playerState = m_stateMachine->GetCurState();
    if ((playerState != PLAY_STATUS_PLAY) && (playerState != PLAY_STATUS_TPLAY)) {
        return HI_SUCCESS;
    }
    if (m_isNeedPause == true) {
        m_isNeedPause = false;
        m_isFirstFramePaused = true;
        return HI_SUCCESS;
    }
    if (m_strmReadEnd == true) {
        return HI_SUCCESS;
    }
    if (m_strmReadEnd == true) {
        goto RE_SEND;
    }
    if (playerState == PLAY_STATUS_PLAY) {
        ret = ReadPacket();
    } else {
        ret = ReadTplayData();
    }
    if (ret == HI_RET_NODATA) {
        renderSleepTime_ = QUEUE_BUFFER_FULL_SLEEP_TIME_US;
        goto RE_SEND;
    } else if (ret != HI_SUCCESS) {
        goto RE_SEND;
    }
    if (m_formatPacket.data == nullptr && m_formatPacket.len == 0) {
        PushPacketToADecoder();
        PushPacketToVDecoder();
        m_strmReadEnd = true;
        ClearCachePacket();
        return HI_SUCCESS;
    }
    if (m_formatPacket.frameType == FRAME_TYPE_AUDIO && audioDecoder_ != nullptr) {
        PushPacketToADecoder();

    } else if (m_formatPacket.frameType == FRAME_TYPE_VIDEO  && videoDecoder_ != nullptr) {
        PushPacketToVDecoder();
    }
    return HI_SUCCESS;
    /* fall through */
RE_SEND:
    ClearCachePacket();
    return ret;
}

int32_t LitePlayer::ReadTplayData()
{
    int32_t ret = HI_SUCCESS;
    if (m_cachedPacket) {
        return ret;
    }

    ret = TPlayBeforeFrameRead();
    if (ret == HI_RET_FILE_EOF) {
        if (memset_s(&m_formatPacket, sizeof(m_formatPacket), 0, sizeof(m_formatPacket)) != EOK) {
            MEDIA_ERR_LOG("SET  m_formatPacket failed");
            return HI_FAILURE;
        }
        m_cachedPacket = true;  // send eos
        return HI_SUCCESS;
    } else if (ret != HI_SUCCESS) {
        NotifyError(HI_LITEPLAYER_ERROR_DEMUX_FAIL);
        return HI_FAILURE;
    }
    ret = DemuxRead(m_formatPacket);
    if (ret == HI_RET_FILE_EOF) {
        if (memset_s(&m_formatPacket, sizeof(m_formatPacket), 0, sizeof(m_formatPacket)) != EOK) {
            MEDIA_ERR_LOG("SET  m_formatPacket failed ");
            return HI_FAILURE;
        }
    } else if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("DemuxRead failed , ret:%d", ret);
        NotifyError(HI_LITEPLAYER_ERROR_DEMUX_FAIL);
        return HI_FAILURE;
    }
    m_cachedPacket = true;
    m_lastReadPktStrmIdx = m_formatPacket.trackId;
    ret = TPlayAfterFrameRead(m_formatPacket);
    if (ret == HI_RET_SKIP_PACKET) {
        ClearCachePacket();
        return ret;
    }
    m_isTplayStartRead = true;
    m_strmReadEnd = false;
    return ret;
}

int32_t LitePlayer::DoStop()
{
    CHECK_NULL_RETURN(m_stateMachine, HI_ERR_LITEPLAYER_NULL_PTR, "m_stateMachine nullptr");
    int32_t ret = HI_SUCCESS;
    PlayerStatus playerState = m_stateMachine->GetCurState();
    CHECK_STATE_SAME(playerState, PLAY_STATUS_IDLE);

    MsgInfo msgInfo;
    if (memset_s(&msgInfo, sizeof(MsgInfo), 0x00, sizeof(msgInfo)) != EOK) {
        MEDIA_ERR_LOG("memset_s msgInfo failed");
        return HI_ERR_LITEPLAYER_MEM_SET;
    }
    msgInfo.what = LITEPLAYER_MSG_SEEK;
    (void)m_stateMachine->RemoveEvent(msgInfo);
    ret = AvplayStop();
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("AvplayStop failed ret:%x", ret);
    }
    ClearCachePacket();
    ret = DemuxStop();
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("DemuxStop failed");
    }
    m_isPlayEnd = false;
    m_strmReadEnd = false;
    m_isPlayErr = false;
    m_isFirstFramePaused = false;
    m_lastRendPos = 0;
    m_lastReadPktPts = 0;
    m_lastSendPktPts = 0;
    m_isAudPlayEos = false;
    m_isVidPlayEos = false;
    hasRenderVideoEos_ = false;
    hasRenderAudioEos_ = false;
    m_lastNotifyTime = 0;
    seekToTimeMs_ = -1;
    if (memset_s(&(m_fmtFileInfo), sizeof(m_fmtFileInfo), 0, sizeof(m_fmtFileInfo)) != EOK) {
        MEDIA_ERR_LOG("SET m_fmtFileInfo failed ");
        return HI_ERR_LITEPLAYER_MEM_SET;
    }
    return ret;
}

int32_t LitePlayer::DoPause()
{
    CHECK_NULL_RETURN(m_stateMachine, HI_ERR_LITEPLAYER_NULL_PTR, "m_stateMachine nullptr");
    PlayerStatus playerState = m_stateMachine->GetCurState();
    CHECK_STATE_SAME(playerState, PLAY_STATUS_PAUSE);

    if (playerState == PLAY_STATUS_PLAY || (playerState == PLAY_STATUS_TPLAY)) {
        pthread_mutex_lock(&schMutex_);
        paused = true;
        pthread_mutex_unlock(&schMutex_);
        if (m_sinkManager_ == nullptr) {
            return -1;
        }
        if (m_sinkManager_->Pause() != 0) {
            MEDIA_ERR_LOG("sink pause   failed ");
            return HI_ERR_LITEPLAYER_AVPLAYER;
        }
    } else {
        return HI_ERR_LITEPLAYER_ILLEGAL_STATE_ACTION;
    }
    return HI_SUCCESS;
}

int32_t LitePlayer::DoSeekIfNeed(void)
{
    if (seekToTimeMs_ == -1) {
        return HI_SUCCESS;
    }
    int32_t ret = AyncSeek(seekToTimeMs_);
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG(" AyncSeek  failed , ret:%d", ret);
        NotifyError(HI_LITEPLAYER_ERROR_VID_PLAY_FAIL);
        return ret;
    }
    m_strmReadEnd = false;
    m_isAudPlayEos = false;
    m_isVidPlayEos = false;
    hasRenderVideoEos_ = false;
    hasRenderAudioEos_ = false;
    m_isPlayEnd = false;
    seekToTimeMs_ = -1;
    MEDIA_INFO_LOG("[%s:%d] seek end", __func__, __LINE__);
    return HI_SUCCESS;
}

int32_t LitePlayer::DoSeek(int64_t timeInMs)
{
    seekToTimeMs_ = timeInMs;
    return DoSeekIfNeed();
}

int32_t LitePlayer::DoGetFileInfo(FormatFileInfo &fileInfo)
{
    return memcpy_s(&fileInfo, sizeof(FormatFileInfo), &m_fmtFileInfo, sizeof(m_fmtFileInfo));
}

int32_t LitePlayer::DoSetMedia(PlayerControlStreamAttr &mediaAttr)
{
    FormatMediaAttr formatMediaAttr;

    formatMediaAttr.s32AudStreamId = mediaAttr.s32AudStreamId;
    formatMediaAttr.s32VidStreamId = mediaAttr.s32VidStreamId;
    int32_t ret = DemuxSetattr(formatMediaAttr);
    if (ret != 0) {
        MEDIA_ERR_LOG(" exec fmt_setattr failed ");
        return HI_ERR_LITEPLAYER_DEMUX_ERROR;
    }
    m_fmtFileInfo.s32UsedVideoStreamIndex = mediaAttr.s32VidStreamId;
    m_fmtFileInfo.s32UsedAudioStreamIndex = mediaAttr.s32AudStreamId;
    return HI_SUCCESS;
}

int32_t LitePlayer::GetStreamInfo(PlayerStreamInfo &streamInfo)
{
    CHECK_NULL_RETURN(m_stateMachine, HI_ERR_LITEPLAYER_NULL_PTR, "m_stateMachine nullptr");
    streamInfo.avStatus.syncStatus.lastAudPts = AV_INVALID_PTS;
    streamInfo.avStatus.syncStatus.lastVidPts = AV_INVALID_PTS;
    if (m_sinkManager_->GetStatus(streamInfo) != HI_SUCCESS) {
        return HI_FAILURE;
    }
    PlayerStatus status = m_stateMachine->GetCurState();
    if (status == PLAY_STATUS_PLAY) {
        streamInfo.avStatus.vidStatus = (m_isVideoStarted) ? (DecoderStatus)status : DECODER_STATUS_IDLE;
        streamInfo.avStatus.audStatus = (m_isAudioStarted) ? (DecoderStatus)status : DECODER_STATUS_IDLE;
    } else {
        streamInfo.avStatus.audStatus = (DecoderStatus)status;
    }

    streamInfo.audioInfo.channel = adecAttr_.channel;
    streamInfo.audioInfo.bitwith = adecAttr_.bitWidth;
    streamInfo.audioInfo.sampleRate = adecAttr_.sampleRate;
    streamInfo.audioInfo.esBufSize = streamAttr_.audioBufSize;
    streamInfo.audioInfo.freeEsBufSize = streamAttr_.audioBufSize >> 1;
    streamInfo.videoInfo.esBufSize = streamAttr_.videoBufSize;
    streamInfo.videoInfo.freeEsBufSize = streamAttr_.videoBufSize >> 1;
    return HI_SUCCESS;
}


int32_t LitePlayer::IsRepeatTplayReq(TplayAttr &tplayAttr, bool &isRepeat)
{
    CHECK_NULL_RETURN(m_stateMachine, HI_ERR_LITEPLAYER_NULL_PTR, "m_stateMachine nullptr");
    isRepeat = false;
    if (m_stateMachine->GetCurState() == PLAY_STATUS_TPLAY &&
        m_tplayAttr.direction == tplayAttr.direction &&
        m_tplayAttr.speed == tplayAttr.speed) {
        MEDIA_ERR_LOG("TPlay input Attr same with current");
        isRepeat = true;
        return HI_SUCCESS;
    }
    PlayerStreamInfo streamInfo;
    int64_t lastVidRendPts;
    int32_t ret = GetStreamInfo(streamInfo);
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("HiAvplayGetStreamInfo failed , ret:%x", ret);
        return ret;
    }
    lastVidRendPts = streamInfo.avStatus.syncStatus.lastVidPts;
    if (m_tplayAttr.direction == TPLAY_DIRECT_BACKWARD  &&
        tplayAttr.direction == TPLAY_DIRECT_BACKWARD &&
        lastVidRendPts == 0) {
        MEDIA_DEBUG_LOG( "TPlay already played to start");
        isRepeat = true;
        return HI_SUCCESS;
    }
    return HI_SUCCESS;
}

int32_t LitePlayer::DoTPlay(TplayAttr &trickPlayAttr)
{
    m_isTplayLastFrame = false;
    m_isTplayStartRead = false;
    if (m_fmtFileInfo.enVideoType == CODEC_JPEG) {
        MEDIA_ERR_LOG("jpeg file do not support tplay");
        return HI_ERR_LITEPLAYER_NOT_SUPPORT;
    }
    if (m_fmtFileInfo.s32UsedVideoStreamIndex == HI_DEMUXER_NO_MEDIA_STREAM) {
        MEDIA_ERR_LOG("only audio file do not support tplay");
        return HI_ERR_LITEPLAYER_NOT_SUPPORT;
    }
    bool isRepeat = false;
    int32_t ret = IsRepeatTplayReq(trickPlayAttr, isRepeat);
    if (ret != HI_SUCCESS) {
        return ret;
    }
    if (isRepeat) {
        return HI_SUCCESS;
    }
    if (memcpy_s(&m_tplayAttr, sizeof(m_tplayAttr), &trickPlayAttr, sizeof(trickPlayAttr)) != EOK) {
        MEDIA_ERR_LOG("copy m_tplayAttr fail ");
        return HI_FAILURE;
    }
    ret = TPlayResetBuffer();
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("TPlayResetBuffer failed , ret:%d", ret);
        return ret;
    }
    m_isVidContinueLost = false;
    ret = m_sinkManager_->SetSpeed(m_tplayAttr.speed, m_tplayAttr.direction);
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("HiAvplayTPlay failed,s32ret:%d ", ret);
        return ret;
    }
    m_curSeekOffset = TPlayGetSeekOffset(m_tplayAttr.speed, m_tplayAttr.direction);
    m_tplayMode = TPlayGetPlayMode();
    if (m_strmReadEnd == true) {
        m_lastReadPktStrmIdx = (uint32_t)m_fmtFileInfo.s32UsedVideoStreamIndex;
    }
    m_strmReadEnd = false;
    m_isVidPlayEos = false;
    m_isAudPlayEos = false;
    m_lastSendAdecPts = AV_INVALID_PTS;
    return HI_SUCCESS;
}

// util bigein
void LitePlayer::EventCallback(PlayerControlEvent event, const void *data)
{
    if (m_eventCallback.callbackFun == nullptr) {
        return;
    }
    m_eventCallback.callbackFun(m_eventCallback.player, event, data);
}

void LitePlayer::NotifyError(PlayerControlError playerError)
{
    EventCallback(HI_LITEPLAYER_EVENT_ERROR, reinterpret_cast<void *>(&playerError));
}

void LitePlayer::StateChangeCallback(PlayerStatus state)
{
    EventCallback(HI_LITEPLAYER_EVENT_STATE_CHANGED, reinterpret_cast<void *>(&state));
}

void LitePlayer::UpdateProgressNotify()
{
    if (m_stateMachine == nullptr) {
        MEDIA_INFO_LOG( "[%s:%d]stateMachine nullptr", __func__, __LINE__);
        return;
    }
    int64_t lastRendPts;
    PlayerStreamInfo streamInfo;
    uint64_t curTime = LiteplayerGetCurRelativeTime();

    if (!m_isPlayEnd) {
        // First progress is not sended to reduce cpu
        m_lastNotifyTime = (!m_lastNotifyTime) ? curTime : m_lastNotifyTime;
        if (m_lastNotifyTime &&
            (curTime - m_lastNotifyTime) < m_playerParam.u32PlayPosNotifyIntervalMs) {
            return;
        }
    }
    int32_t ret = GetStreamInfo(streamInfo);
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("HiAvplayGetStreamInfo failed , ret:%x", ret);
        return;
    }
    if (m_fmtFileInfo.s32UsedAudioStreamIndex != HI_DEMUXER_NO_MEDIA_STREAM &&
        m_stateMachine->GetCurState() != PLAY_STATUS_TPLAY) {
        lastRendPts = streamInfo.avStatus.syncStatus.lastAudPts;
        if (lastRendPts < m_fmtFileInfo.s64StartTime) {
            return;
        }
        lastRendPts -= m_fmtFileInfo.s64StartTime;
        if (!m_isAudPlayEos) {
            EventCallback(HI_LITEPLAYER_EVENT_PROGRESS, &lastRendPts);
        }
        m_lastNotifyTime = curTime;
        m_lastRendPos = lastRendPts;
    } else if (!m_isVidPlayEos) {
        lastRendPts = streamInfo.avStatus.syncStatus.lastVidPts;
        if (lastRendPts < m_fmtFileInfo.s64StartTime) {
            return;
        }
        lastRendPts -= m_fmtFileInfo.s64StartTime;
        EventCallback(HI_LITEPLAYER_EVENT_PROGRESS, &lastRendPts);
        m_lastNotifyTime = curTime;
        m_lastRendPos = lastRendPts;
    }
}

void LitePlayer::DealPlayEnd()
{
    if (m_stateMachine == nullptr) {
        MEDIA_INFO_LOG( "[%s:%d]stateMachine nullptr", __func__, __LINE__);
        return;
    }
    PlayerStatus playState = m_stateMachine->GetCurState();
    if (TPLAY_DIRECT_BACKWARD == m_tplayAttr.direction && playState == PLAY_STATUS_TPLAY) {
        EventCallback(HI_LITEPLAYER_EVENT_SOF, nullptr);
    } else {
        EventCallback(HI_LITEPLAYER_EVENT_PROGRESS, &m_fmtFileInfo.s64Duration);
        EventCallback(HI_LITEPLAYER_EVENT_EOF, nullptr);
    }
}

PlayerTplayMode LitePlayer::TPlayGetPlayMode()
{
    PlayerTplayMode tplayMode = PLAYER_TPLAY_ONLY_I_FRAME;
    StreamResolution resolution = { 0 };
    if (DemuxGetResolution(m_fmtFileInfo.s32UsedVideoStreamIndex, resolution) != HI_SUCCESS) {
        MEDIA_ERR_LOG("DemuxGetResolution failed");
        return PLAYER_TPLAY_ONLY_I_FRAME;
    }

    if (m_tplayAttr.direction == TPLAY_DIRECT_FORWARD
        && m_tplayAttr.speed == PLAY_SPEED_2X_FAST) {
        if ((resolution.u32Width * resolution.u32Height) <= FULL_TPLAY_RESULITON_LIMIT
            && m_fmtFileInfo.fFrameRate <= FULL_TPLAY_FRAMERATE_LIMIT
            && m_fmtFileInfo.u32Bitrate <= FULL_TPLAY_BITRATE_LIMIT) {
            tplayMode = PLAYER_TPLAY_FULL_PLAY;
        }
    }
    return tplayMode;
}

int32_t LitePlayer::TPlayGetSeekOffset(float playSpeed, TplayDirect direction)
{
    int32_t seekOffset = 0;
    switch ((int)playSpeed) {
        case PLAY_SPEED_2X_FAST:
            seekOffset = (int32_t)TPLAY_SEEK_OFFSET_2X;
            break;
        case PLAY_SPEED_4X_FAST:
            seekOffset = (int32_t)TPLAY_SEEK_OFFSET_4X;
            break;
        case PLAY_SPEED_8X_FAST:
            seekOffset = (int32_t)TPLAY_SEEK_OFFSET_8X;
            break;
        case PLAY_SPEED_16X_FAST:
            seekOffset = (int32_t)TPLAY_SEEK_OFFSET_16X;
            break;
        case PLAY_SPEED_32X_FAST:
            seekOffset = (int32_t)TPLAY_SEEK_OFFSET_32X;
            break;
        case PLAY_SPEED_64X_FAST:
            seekOffset = (int32_t)TPLAY_SEEK_OFFSET_64X;
            break;
        case PLAY_SPEED_128X_FAST:
            seekOffset = (int32_t)TPLAY_SEEK_OFFSET_128X;
            break;
        default:
            MEDIA_ERR_LOG("unsupported play speed: %f", playSpeed);
            break;
    }
    seekOffset = (direction == TPLAY_DIRECT_BACKWARD) ? (-seekOffset) : seekOffset;
    return seekOffset;
}

int32_t LitePlayer::TPlayResetBuffer()
{
    int32_t ret;
    int64_t lastVidRendPts;
    PlayerStreamInfo streamInfo;

    if (memset_s(&streamInfo, sizeof(streamInfo), 0x00, sizeof(streamInfo)) != EOK) {
        return HI_FAILURE;
    }
    ret = GetStreamInfo(streamInfo);
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("HiAvplayGetStreamInfo failed , ret:%x", ret);
        return ret;
    }
    lastVidRendPts = streamInfo.avStatus.syncStatus.lastVidPts;
    m_lastReadPktPts = (lastVidRendPts < 0) ? (m_lastRendPos) : (lastVidRendPts);
    m_isTplayLastFrame = false;
    ClearCachePacket();
    ret = DecoderAndSinkReset();
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("HiAvplayReset failed , ret:%d", ret);
        return ret;
    }
    return HI_SUCCESS;
}

int32_t LitePlayer::TPlayCheckContinueLost()
{
    int32_t ret = HI_SUCCESS;
    if (m_isVidContinueLost) {
        if (m_curSeekOffset < INT32_MAX / OFFSET_INCREASE_FOR_FRAME_LOST) {
            m_curSeekOffset *= OFFSET_INCREASE_FOR_FRAME_LOST;
        }
        MEDIA_ERR_LOG("vid dec frame slow, increase seekoffset to  %d",
                      m_curSeekOffset);
        ret = TPlayResetBuffer();
        if (ret != HI_SUCCESS) {
            MEDIA_ERR_LOG("TPlayResetBuffer failed , ret:%d", ret);
            return HI_FAILURE;
        }
        m_isVidContinueLost = false;
    }
    return HI_SUCCESS;
}

bool LitePlayer::TPlayIsFileReadEnd()
{
    if (m_lastReadPktPts == 0 && TPLAY_DIRECT_BACKWARD == m_tplayAttr.direction) {
        MEDIA_DEBUG_LOG( "backward last seek pts %lld ", m_lastReadPktPts);
        return true;
    } else if (m_isTplayLastFrame == true && (m_tplayAttr.direction == TPLAY_DIRECT_FORWARD)) {
        MEDIA_DEBUG_LOG(
            "forward last seek pts %lld m_fmtFileInfo.s64Duration:%lld ",
            m_lastReadPktPts, m_fmtFileInfo.s64Duration);
        return true;
    }
    return false;
}

int32_t LitePlayer::SeekInTplayMode(int64_t seekTimeInMs, FormatSeekMode seekFlag)
{
    int32_t ret = DemuxSeek(m_fmtFileInfo.s32UsedVideoStreamIndex, seekTimeInMs, seekFlag);
    if (ret != HI_SUCCESS) {
        // if forward tplay not find the last i frame, then seek again for backword
        if (m_tplayAttr.direction == TPLAY_DIRECT_FORWARD) {
            seekFlag = FORMAT_SEEK_MODE_FORWARD_KEY;
            m_isTplayLastFrame = true;
            ret = DemuxSeek(m_fmtFileInfo.s32UsedVideoStreamIndex, seekTimeInMs, seekFlag);
        }
        if (ret != HI_SUCCESS) {
            MEDIA_DEBUG_LOG(
                "seek failed maybe seek to file end, ret:%d", ret);
            /* read end */
            return HI_RET_FILE_EOF;
        }
    }
    return ret;
}
int32_t LitePlayer::TPlayBeforeFrameRead()
{
    int32_t ret = HI_SUCCESS;
    if (m_tplayMode != PLAYER_TPLAY_ONLY_I_FRAME) {
        return ret;
    }

    ret = TPlayCheckContinueLost();
    if (ret != HI_SUCCESS) {
        return ret;
    }
    /* last packet should be skip if streamidx is not playing video stream */
    if (m_lastReadPktStrmIdx == (uint32_t)m_fmtFileInfo.s32UsedVideoStreamIndex) {
        int64_t seekTimeInMs = m_lastReadPktPts + m_curSeekOffset;
        if (TPlayIsFileReadEnd()) {
            return HI_RET_FILE_EOF;
        }
        FormatSeekMode seekFlag = (m_tplayAttr.direction == TPLAY_DIRECT_BACKWARD) ? FORMAT_SEEK_MODE_BACKWARD_KEY :
            FORMAT_SEEK_MODE_FORWARD_KEY;
        if (seekTimeInMs < 0 && m_tplayAttr.direction == TPLAY_DIRECT_BACKWARD) {
            seekTimeInMs = 0;
            m_isTplayLastFrame = true;
        } else if (seekTimeInMs > m_fmtFileInfo.s64Duration && m_tplayAttr.direction == TPLAY_DIRECT_FORWARD) {
            seekTimeInMs = m_fmtFileInfo.s64Duration;
            seekFlag = FORMAT_SEEK_MODE_BACKWARD_KEY;
            m_isTplayLastFrame = true;
        } else if (m_lastReadPktPts == 0 && m_isTplayStartRead == false) {
            seekTimeInMs = 0;
            seekFlag = FORMAT_SEEK_MODE_BACKWARD_KEY;
            m_isTplayLastFrame = false;
        }
        ret = SeekInTplayMode(seekTimeInMs, seekFlag);
        if (ret != HI_SUCCESS) {
            return ret;
        }
    }
    return HI_SUCCESS;
}

int32_t LitePlayer::TPlayAfterFrameRead(FormatFrame &packet)
{
    int32_t ret = HI_SUCCESS;
    bool isSkipPkt = false;

    if ((int)packet.trackId == m_fmtFileInfo.s32UsedVideoStreamIndex) {
        if ((packet.timestampUs == m_lastSendPktPts) && (m_isTplayStartRead == true)) {
            m_lastReadPktPts += m_curSeekOffset;
            isSkipPkt = true;
        } else {
            m_lastReadPktPts = packet.timestampUs;
        }
    } else {
        m_lastReadPktPts = packet.timestampUs;
        isSkipPkt = true;
    }
    if (isSkipPkt) {
        ret = HI_RET_SKIP_PACKET;
    }
    return ret;
}

void LitePlayer::FlushDecoder(void)
{
    ReleaseADecoderOutputFrame();
    ReleaseVDecoderOutputFrame();
    if (audioDecoder_ != nullptr) {
        audioDecoder_->FlushDec();
    }
    if (videoDecoder_ != nullptr) {
        videoDecoder_->FlushDec();
    }
}

int32_t LitePlayer::DecoderAndSinkReset(void)
{
    int32_t ret;
    bool isNeedResume = false;

    ret = m_sinkManager_->Pause();
    if ((ret == HI_SUCCESS) && (paused == false)) {
        isNeedResume = true;
    }
    ret = m_sinkManager_->Reset();
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG("m_render reset failed");
        (void)m_sinkManager_->Resume();
        return HI_ERR_AVPLAY_INVALID_OP;
    }
    FlushDecoder();
    if (isNeedResume) {
        ret = m_sinkManager_->Resume();
        if (ret != HI_SUCCESS) {
            MEDIA_ERR_LOG("Render resume failed ret: %x", ret);
            return HI_FAILURE;
        }
    }
    return HI_SUCCESS;
}

int32_t LitePlayer::AyncSeek(int64_t seekTime)
{
    int64_t seekTimeInMs = seekTime;

    int32_t ret = DecoderAndSinkReset();
    if (ret != HI_SUCCESS) {
        MEDIA_ERR_LOG(
                      " exec HI_LITEPLAYER_IPCMSG_AVPLAYER_Reset failed , ret:%d", ret);
        return HI_FAILURE;
    }
    ClearCachePacket();
    if (m_fmtFileInfo.s32UsedVideoStreamIndex != HI_DEMUXER_NO_MEDIA_STREAM) {
        ret = DemuxSeek(m_fmtFileInfo.s32UsedVideoStreamIndex, seekTimeInMs, FORMAT_SEEK_MODE_BACKWARD_KEY);
        if (ret != HI_SUCCESS) {
            MEDIA_INFO_LOG( "exec fmt_seek video stream failed, ret:%d", ret);
            seekTimeInMs = m_lastRendPos;
        }
    } else if (m_fmtFileInfo.s32UsedAudioStreamIndex != HI_DEMUXER_NO_MEDIA_STREAM) {
        ret = DemuxSeek(m_fmtFileInfo.s32UsedAudioStreamIndex, seekTimeInMs, FORMAT_SEEK_MODE_BACKWARD_KEY);
        if (ret != HI_SUCCESS) {
            MEDIA_INFO_LOG( "exec fmt_seek audio stream failed, ret:%d", ret);
            seekTimeInMs = m_lastRendPos;
        }
    }
    EventCallback(HI_LITEPLAYER_EVENT_SEEK_END, reinterpret_cast<void *>(&seekTimeInMs));
    return HI_SUCCESS;
}

void LitePlayer::GetPlayElementEventCallBack(PlayEventCallback &callback)
{
    callback.onEventCallback = LiteplayerOnAvEvent;
    callback.onStatusChange = LiteplayerOnAvStatusChange;
    callback.priv = reinterpret_cast<void *>(this);
}
int32_t LitePlayer::SyncPrepare()
{
    int ret;

    m_playerSource_ = std::make_shared<PlayerSource>();
    if (m_playerSource_ == nullptr) {
        MEDIA_ERR_LOG("%s:%d, new PlayerSource failed", __func__, __LINE__);
        return -1;
    }
    m_playerSource_->Init();

    if (m_sourceType_ == SOURCE_TYPE_FD) {
        m_playerSource_->SetSource(m_fd_);
    } else if (m_sourceType_ == SOURCE_TYPE_STREAM) {
        m_playerSource_->SetSource(m_stream_);
    } else {
        m_playerSource_->SetSource(m_filePath_.c_str());
    }

    PlayEventCallback callback;
    GetPlayElementEventCallBack(callback);
    ret = m_playerSource_->SetCallBack(callback);
    if (ret != 0) {
        MEDIA_ERR_LOG("%s:%d, SetCallBack failed", __func__, __LINE__);
    }
    ret = m_playerSource_->Prepare();
    if (ret != 0) {
        MEDIA_ERR_LOG("%s:%d, Prepare failed,%d", __func__, __LINE__, ret);
        return ret;
    }
    ret = m_playerSource_->GetFileInfo(m_fmtFileInfo);
    if (ret != 0) {
        MEDIA_ERR_LOG("[%s:%d], GetFileInfo failed,%d", __func__, __LINE__, ret);
        return ret;
    }

    MEDIA_INFO_LOG( " used audiostream index %d",
                  m_fmtFileInfo.s32UsedAudioStreamIndex);
    MEDIA_INFO_LOG( " used videostream index %d",
                  m_fmtFileInfo.s32UsedVideoStreamIndex);
    return HI_SUCCESS;
}

bool LitePlayer::IsPlayEos()
{
    CHECK_NULL_RETURN(m_stateMachine, false, "m_stateMachine nullptr");
    PlayerStatus playerState = m_stateMachine->GetCurState();
    if (playerState == PLAY_STATUS_TPLAY && hasRenderVideoEos_) {
        return true;
    }
    if ((!m_isAudioStarted || hasRenderAudioEos_) && (!m_isVideoStarted || hasRenderVideoEos_)) {
        return true;
    }
    return false;
}

int32_t LitePlayer::CheckMediaType(FormatFileInfo &fmtFileInfo)
{
    if (fmtFileInfo.s32UsedVideoStreamIndex == HI_DEMUXER_NO_MEDIA_STREAM) {
        return HI_SUCCESS;
    }
    if ((fmtFileInfo.enVideoType == CODEC_H264)
        || (fmtFileInfo.enVideoType == CODEC_H265)
        || (fmtFileInfo.enVideoType == CODEC_JPEG)) {
        return HI_SUCCESS;
    }
    MEDIA_ERR_LOG("video type: %d not supported ", fmtFileInfo.enVideoType);
    return HI_ERR_LITEPLAYER_NOT_SUPPORT;
}
}
}
