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

#include <unistd.h>
#include <sys/time.h>
#include "player_sync.h"
#include "player_sink_type.h"
#include "media_log.h"

namespace OHOS {
namespace Media {
const int32_t SYNC_STOP_NEGATIVE_MS = 6000;
const int32_t SYNC_STOP_PLUS_MS = 3000;
const int32_t SYNC_START_NEGATIVE_MS = 100;
const int32_t SYNC_START_PLUS_MS = 50;
const int32_t MAX_VID_LOST_FRAMENUM = 10;

const int32_t SS2US = 1000000;
const int32_t US2MS = 1000;

static int64_t GetCurTimeUs()
{
    struct timeval ts = {0, 0};
    gettimeofday(&ts, NULL);
    return (((int64_t)ts.tv_sec) * SS2US) + ((int64_t)ts.tv_usec);
}

SyncRet PlayerSync::CheckAVDiff(int64_t latenessMs, uint32_t &continueLost)
{
    SyncRet syncRet = SYNC_RET_PLAY;

    if (continueLost >= MAX_VID_LOST_FRAMENUM) {
        continueLost = 0;
        return syncRet;
    }
    // sync lateness out range exception; pts jump err, just skip this frame
    if (latenessMs > (int64_t)m_syncAttr.syncStopRegion.vidNegativeTime
        || latenessMs < (-(int64_t)m_syncAttr.syncStopRegion.vidPlusTime)) {
        syncRet = SYNC_RET_DROP;
        continueLost++;
        return syncRet;
    }
    if (latenessMs > (int64_t)m_syncAttr.syncStartRegion.vidNegativeTime) {
        syncRet = SYNC_RET_DROP;
        continueLost++;
    } else if (latenessMs < (-(int64_t)m_syncAttr.syncStartRegion.vidPlusTime)) {
        syncRet = SYNC_RET_REPEAT;
    } else {
        syncRet = SYNC_RET_PLAY;
        continueLost = 0;
    }
    return syncRet;
}

int32_t PlayerSync::TPlayProcess(int64_t timestampUs, SyncRet &result)
{
    int64_t nowTsUs;
    int64_t latenessUs = 0;
    int64_t realTimeElapseUs = GetCurTimeUs() - m_frstVidFrameTime;
    int64_t trickTimeElapseUs = (int64_t)(realTimeElapseUs * m_speed_);

    if (m_tplayDirect_ == TPLAY_DIRECT_FORWARD) {
        nowTsUs = m_firstVidFrameTs + trickTimeElapseUs;
        latenessUs = (nowTsUs - timestampUs);
    } else {  // backward
        nowTsUs = m_firstVidFrameTs - trickTimeElapseUs;
        if (nowTsUs < 0) {
            nowTsUs = 0;
        }
        latenessUs = (timestampUs - nowTsUs);
    }
    int64_t latenessMs = (m_speed_ != 0) ? (latenessUs / ((int)(m_speed_ * MS_SCALE))) : 0;
    result = CheckAVDiff(latenessMs, m_continousVidLost);
    return HI_SUCCESS;
}

int32_t PlayerSync::Reset(SyncChn syncChn)
{
    m_diffAvPlayTime = 0;

    if (syncChn == SYNC_CHN_VID) {
        pthread_mutex_lock(&m_vidSyncLock);
        m_isFristVidFrame = true;
        m_vidTimeSourceDelta = 0;
        m_lastVideoTsUs = AV_INVALID_PTS;
        m_continousVidLost = 0;
        m_firstVidFrameTs = AV_INVALID_PTS;
        m_frstVidFrameTime = 0;
        pthread_mutex_unlock(&m_vidSyncLock);
    } else if (syncChn == SYNC_CHN_AUD) {
        pthread_mutex_lock(&m_audSyncLock);
        m_isFristAudFrame = true;
        m_audTimeSourceDelta = 0;
        m_lastAudioTsUs = AV_INVALID_PTS;
        m_lastAudioRealTsUs = AV_INVALID_PTS;
        m_firstAudFrameTs = AV_INVALID_PTS;
        pthread_mutex_unlock(&m_audSyncLock);
    } else {
        MEDIA_ERR_LOG("invalid sync chn: %d", syncChn);
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

int32_t PlayerSync::GetStatus(PlaySyncStatus &info)
{
    info.firstAudPts = (m_firstVidFrameTs == AV_INVALID_PTS) ? AV_INVALID_PTS : (m_firstVidFrameTs / MS_SCALE);
    info.lastAudPts = (m_lastAudioTsUs == AV_INVALID_PTS) ? AV_INVALID_PTS : (m_lastAudioTsUs / MS_SCALE);
    info.firstVidPts = (m_firstVidFrameTs == AV_INVALID_PTS) ? AV_INVALID_PTS : (m_firstVidFrameTs / MS_SCALE);
    info.lastVidPts = (m_lastVideoTsUs == AV_INVALID_PTS) ? AV_INVALID_PTS : (m_lastVideoTsUs / MS_SCALE);
    info.diffTime = m_diffAvPlayTime;
    info.localTime = AV_INVALID_PTS;
    return HI_SUCCESS;
}

int32_t PlayerSync::GetAttr(PlayerSyncAttr &syncAttr)
{
    syncAttr = m_syncAttr;
    return HI_SUCCESS;
}

int32_t PlayerSync::SetAttr(PlayerSyncAttr &syncAttr)
{
    m_syncAttr = syncAttr;
    return HI_SUCCESS;
}

PlayerSync::PlayerSync()
{
    m_isVidEnable = false;
    m_isAudEnable = false;
    m_isFristVidFrame = false;
    m_vidTimeSourceDelta = 0;
    m_lastVideoTsUs = 0;
    m_firstVidFrameTs = 0;
    m_frstVidFrameTime = 0;
    m_continousVidLost = 0;
    m_isFristAudFrame = false;
    m_audTimeSourceDelta = 0;
    m_lastAudioTsUs = 0;
    m_lastAudioRealTsUs = 0;
    m_firstAudFrameTs = 0;
    m_isInTrickPlayMode = false;
    m_speed_ = 1.0;
    m_tplayDirect_ = TPLAY_DIRECT_BUTT;
    m_syncAttr.isQuickOutput = true;
    m_syncAttr.refType = PLAYER_SYNC_REF_AUD;
    m_syncAttr.syncStartRegion.vidNegativeTime = SYNC_START_NEGATIVE_MS;
    m_syncAttr.syncStartRegion.vidPlusTime = SYNC_START_PLUS_MS;
    m_syncAttr.syncStopRegion.vidNegativeTime = SYNC_STOP_NEGATIVE_MS;
    m_syncAttr.syncStopRegion.vidPlusTime = SYNC_STOP_PLUS_MS;
    m_diffAvPlayTime = 0;
    m_isInited = false;
}

PlayerSync::~PlayerSync()
{
    (void)Deinit();
}

int32_t PlayerSync::Deinit(void)
{
    int32_t ret = HI_SUCCESS;
    if (m_isInited == true) {
        ret = pthread_mutex_destroy(&m_vidSyncLock);
        if (ret != 0) {
            MEDIA_ERR_LOG("pthread_mutex_destroy m_vidSyncLock failed");
        }
        ret = pthread_mutex_destroy(&m_audSyncLock);
        if (ret != 0) {
            MEDIA_ERR_LOG("pthread_mutex_destroy m_audSyncLock failed");
        }
        m_isInited = false;
    }
    return ret;
}

int32_t PlayerSync::Init(void)
{
    if (m_isInited) {
        return HI_SUCCESS;
    }
    int32_t ret = pthread_mutex_init(&m_vidSyncLock, nullptr);
    if (ret != 0) {
        MEDIA_ERR_LOG("pthread_mutex_init m_vidSyncLock failed");
        return ret;
    }
    ret = pthread_mutex_init(&m_audSyncLock, nullptr);
    if (ret != 0) {
        MEDIA_ERR_LOG("pthread_mutex_init m_vidSyncLock failed");
        (void)pthread_mutex_destroy(&m_vidSyncLock);
        return ret;
    }
    (void)Reset(SYNC_CHN_VID);
    (void)Reset(SYNC_CHN_AUD);
    m_isInited = true;
    return HI_SUCCESS;
}

int32_t PlayerSync::Start(SyncChn syncChn)
{
    if (m_isInited == false) {
        MEDIA_ERR_LOG("sync start before inited");
        return HI_FAILURE;
    }
    if (syncChn == SYNC_CHN_VID) {
        m_isVidEnable = true;
    } else if (syncChn == SYNC_CHN_AUD) {
        m_isAudEnable = true;
    } else {
        MEDIA_ERR_LOG("invalid sync chn: %d", syncChn);
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

int32_t PlayerSync::SetSpeed(float speed, TplayDirect  tplayDirect)
{
    if (m_isInited == false) {
        MEDIA_ERR_LOG("sync TPlay before inited");
        return HI_FAILURE;
    }
    pthread_mutex_lock(&m_vidSyncLock);
    m_isInTrickPlayMode = true;
    m_speed_ = speed;
    m_tplayDirect_ = tplayDirect;
    pthread_mutex_unlock(&m_vidSyncLock);
    return HI_SUCCESS;
}

/* only used to resume from tplay to normal */
int32_t PlayerSync::Resume()
{
    if (m_isInited == false) {
        MEDIA_ERR_LOG("sync Resume before inited");
        return HI_FAILURE;
    }
    pthread_mutex_lock(&m_vidSyncLock);
    m_isInTrickPlayMode = false;
    pthread_mutex_unlock(&m_vidSyncLock);
    return HI_SUCCESS;
}

int32_t PlayerSync::Stop(SyncChn syncChn)
{
    if (m_isInited == false) {
        MEDIA_ERR_LOG("sync Stop before inited");
        return HI_FAILURE;
    }
    if (syncChn == SYNC_CHN_VID) {
        m_isVidEnable = false;
        Reset(syncChn);
    } else if (syncChn == SYNC_CHN_AUD) {
        m_isAudEnable = false;
        Reset(syncChn);
    } else {
        MEDIA_ERR_LOG("invalid sync chn: %d", syncChn);
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

void PlayerSync::UpdateCurTimeWithAudio(int64_t& nowUs)
{
    if (m_syncAttr.refType == PLAYER_SYNC_REF_AUD) {
        // ref with audio pts
        if (m_lastAudioTsUs != AV_INVALID_PTS) {
            /* compensate for audio frame pts gap maybe too long, eg: 64ms */
            nowUs = m_lastAudioTsUs + (GetCurTimeUs() - m_lastAudioRealTsUs);
        }
    }
}

SyncRet PlayerSync::OnVideoFirstFrame(int64_t ptsUs)
{
    // caculate pts and clock delta of first frame
    int64_t firstTimeUs = GetCurTimeUs();
    m_vidTimeSourceDelta = firstTimeUs - ptsUs;
    m_lastVideoTsUs = ptsUs;
    m_frstVidFrameTime = firstTimeUs;
    m_firstVidFrameTs = ptsUs;
    m_isFristVidFrame = false;
    return SYNC_RET_PLAY;
}

int32_t PlayerSync::ProcVidFrame(int64_t ptsMs, SyncRet &result)
{
    int32_t ret = HI_SUCCESS;
    int64_t ptsUs;
    int64_t nowUs;

    if (m_isInited == false) {
        MEDIA_ERR_LOG("sync ProcVidFrame before inited");
        return HI_FAILURE;
    }
    pthread_mutex_lock(&m_vidSyncLock);
    if (m_isVidEnable == false) {
        MEDIA_ERR_LOG("sync module have not enabled");
        result = SYNC_RET_DROP;
        ret = HI_FAILURE;
        goto UNLOCK;
    }
    if (m_syncAttr.refType == PLAYER_SYNC_REF_NONE) {
        result = SYNC_RET_PLAY;
        goto UNLOCK;
    }
    ptsUs = ptsMs * US2MS;
    // first video frame quickoutput
    if (m_isFristVidFrame == true) {
        result = OnVideoFirstFrame(ptsUs);
        goto UNLOCK;
    }
    if (m_isInTrickPlayMode) {
        (void)TPlayProcess(ptsUs, result);
        m_lastVideoTsUs = ptsUs;
        goto UNLOCK;
    }
    nowUs = GetCurTimeUs() - m_vidTimeSourceDelta;
    UpdateCurTimeWithAudio(nowUs);
    m_diffAvPlayTime = (nowUs - ptsUs) / MS_SCALE;
    if (m_syncAttr.refType == PLAYER_SYNC_REF_VID) {
        if (m_diffAvPlayTime < (-(int64_t)(m_syncAttr.syncStartRegion.vidPlusTime))) {
            result = SYNC_RET_REPEAT;
        } else { /* do not care the fps and decode speed, just play */
            result = SYNC_RET_PLAY;
        }
    } else {
        result = CheckAVDiff(m_diffAvPlayTime, m_continousVidLost);
    }
    m_lastVideoTsUs = ptsUs;
    /* fall through */
UNLOCK:
    pthread_mutex_unlock(&m_vidSyncLock);
    return ret;
}

int32_t PlayerSync::ProcAudFrame(int64_t ptsMs, SyncRet &result)
{
    if (m_isInited == false) {
        MEDIA_ERR_LOG("sync ProcAudFrame before inited");
        return HI_FAILURE;
    }
    pthread_mutex_lock(&m_audSyncLock);
    if (m_isAudEnable == false) {
        MEDIA_ERR_LOG("sync module have not enabled");
        result = SYNC_RET_DROP;
        pthread_mutex_unlock(&m_audSyncLock);
        return HI_FAILURE;
    }
    if (m_isInTrickPlayMode == true) {
        result = SYNC_RET_DROP;
        pthread_mutex_unlock(&m_audSyncLock);
        return HI_SUCCESS;
    }
    int64_t timeUs = ptsMs * US2MS;
    int64_t nowUs;
    if (m_isFristAudFrame == true) {
        // caculate pts and clock delta of first frame
        int64_t firstTimeUs = GetCurTimeUs();
        m_audTimeSourceDelta = firstTimeUs - timeUs;
        m_isFristAudFrame = false;
        m_firstAudFrameTs = timeUs;
    }
    if (m_syncAttr.refType == PLAYER_SYNC_REF_AUD) {
        // calc current shouldbe timestamp ref in sys clock
        nowUs = GetCurTimeUs() - m_audTimeSourceDelta;
        int64_t latenessMs = (nowUs - timeUs) / MS_SCALE;
        /* if have mechanism to fast or shorter audio sound play, handle here, now we just ignore */
        if (latenessMs > (int64_t)m_syncAttr.syncStopRegion.vidNegativeTime ||
            latenessMs < (-(int64_t)m_syncAttr.syncStopRegion.vidPlusTime)) {
        }
        m_lastAudioTsUs = timeUs;
        m_lastAudioRealTsUs = GetCurTimeUs();
    } else if (m_syncAttr.refType == PLAYER_SYNC_REF_VID) {
        MEDIA_ERR_LOG("current do not support ref video, if have audio");
        result = SYNC_RET_DROP;
        pthread_mutex_unlock(&m_audSyncLock);
        return HI_FAILURE;
    }
    result = SYNC_RET_PLAY;
    pthread_mutex_unlock(&m_audSyncLock);
    return HI_SUCCESS;
}
};
};
