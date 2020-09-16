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

#ifndef LITEPLAYER_H
#define LITEPLAYER_H

#include <string>
#include "hi_liteplayer.h"
#include "liteplayer_state_machine.h"
#include "player_define.h"
#include "player_source.h"
#include "player_sink_manager.h"
#include "hi_demuxer.h"
#include "decoder.h"
#include "surface.h"

namespace OHOS {
namespace Media {
class PlayerSource;
class SinkManager;
class Decoder;

class LitePlayer : public PlayerControlHandle {
public:
    friend class PlayerControlState;
    friend class PlayerControlSMObserver;

    LitePlayer();
    ~LitePlayer() override;

    int32_t Init(const PlayerControlParam &createParam);  // liteplayer create

    int32_t Deinit(void);  // liteplayer destroy

    PlayerStatus GetState(void);

    int32_t RegCallback(PlayerCtrlCallbackParam &eventCallback);

    int32_t SetDataSource(const std::string filepath);
    int32_t SetDataSource(const int32_t fd);
    int32_t SetDataSource(BufferStream &stream);

    int32_t Prepare(void);

    int32_t Play(void);

    int32_t SetVolume(VolumeAttr &volumeAttr);

    int32_t Stop(void);

    int32_t Pause(void);

    int32_t Seek(int64_t timeInMs);

    int32_t GetFileInfo(FormatFileInfo &formatInfo);

    int32_t SetMedia(PlayerControlStreamAttr &mediaAttr);

    int32_t SetSurface(Surface *surface);

    int32_t TPlay(TplayAttr tplayAttr);

    int32_t OnAvplayEvent(const void* avplay, const EventCbType event);

    int32_t OnSwitchTPlay2Play(void);

    void OnAvplayVideoEndOfStream(void);

    int32_t OnAvplayStatusChange(const void *avplay, PlayerStatus status);

    void StateChangeCallback(PlayerStatus state) override;

protected:
    int32_t DoRegCallback(PlayerCtrlCallbackParam &observer) override;

    int32_t DoSetDataSource(const std::string filepath) override;
    int32_t DoSetDataSource(const int fd) override;
    int32_t DoSetDataSource(BufferStream &stream)  override;
    int32_t DoPrepare(void) override;

    int32_t DoPlay(void) override;

    int32_t DoSetVolume(VolumeAttr &volumeAttr) override;

    int32_t ReadPacketAndPushToDecoder(void) override;

    int32_t DoStop(void) override;

    int32_t DoSeek(int64_t timeInMs) override;

    int32_t DoPause(void) override;

    int32_t DoGetFileInfo(FormatFileInfo &fileInfo) override;

    int32_t DoSetMedia(PlayerControlStreamAttr &mediaAttr) override;

    int32_t DoTPlay(TplayAttr& trickPlayAttr) override;

    void ClearCachePacket(void);

    void NotifyError(PlayerControlError playerError) override;

    void EventCallback(PlayerControlEvent event, const void* data);

private:
    int32_t InitAttr(const PlayerControlParam &createParam);

    bool IsPlayEos(void);

    int32_t CheckMediaType(FormatFileInfo &fmtFileInfo);

    int32_t SyncPrepare(void);

    int32_t AyncSeek(int64_t seekTime);

    int32_t TPlayAfterFrameRead(FormatFrame& packet);

    int32_t TPlayBeforeFrameRead(void);

    int32_t TPlayResetBuffer(void);

    int32_t TPlayGetSeekOffset(float speed, TplayDirect direction);

    int32_t IsRepeatTplayReq(TplayAttr &tplayAttr, bool &isRepeat);

    PlayerTplayMode TPlayGetPlayMode(void);

    int32_t TPlayCheckContinueLost(void);

    bool TPlayIsFileReadEnd(void);

    int32_t ReadPacket(void);

    int32_t ReadTplayData(void);

    int32_t SeekInTplayMode(int64_t seekTimeInMs, FormatSeekMode seekFlag);

    void UpdateProgressNotify(void);

    void DealPlayEnd(void);

    int32_t DemuxStop(void);

    int32_t DemuxRead(FormatFrame &fmtFrame);

    int32_t DemuxFree(FormatFrame &fmtFrame);

    int32_t DemuxSeek(int32_t streamIndex, int64_t mSec, FormatSeekMode flag);

    int32_t DemuxGetinfo(FormatFileInfo &fmtInfo);

    int32_t DemuxSetattr(FormatMediaAttr &fmtInfo);

    int32_t DemuxGetResolution(int32_t streamIdx, StreamResolution &resolution);

    // avplay
    int32_t AvplayCheckMediaInfo(void);

    int32_t AvplaySetVDecAttr(void);

    int32_t AvplaySetMPFDecAttr(void);

    int32_t AvplaySetADecAttr(void);

    uint32_t AvplayDefaultVideoBufSize(uint32_t width, uint32_t height);

    int32_t AvplaySetStreamAttr(void);

    int32_t AvplaySetRenderAttr(void);

    int32_t AvplayCreate(void);

    int32_t AvplayDestroy(void);

    int32_t AvplayStop(void);

    int32_t AvplayStart(void);

    int32_t AvplaySendStreamEos();

    void GetPlayElementEventCallBack(PlayEventCallback &callback);
    int32_t PauseResume(void);
    int32_t TPlayResume(void);
    int32_t DecoderAndSinkReset(void);
    int32_t GetStreamInfo(PlayerStreamInfo &streamInfo);
    int32_t SinkStart(void);
    int32_t DecoderStart(void);
    int32_t SetDecoderAndStreamAttr(void);
    int32_t CheckMediaInfo(void);
    int32_t AddAudioSink(void);
    int32_t AddVideoSink();
    int32_t SetVDecAttr(void);
    int32_t SetADecAttr(void);
    int32_t SetStreamAttr();
    void ReleaseADecoderOutputFrame(void);
    void ReleaseVDecoderOutputFrame(void);
    void RenderAudioFrame(void);
    void RenderVideoFrame(void);
    static void* DataSchProcess(void *priv);
    void ReortRenderPosition(void);
    void PushPacketToADecoder(void);
    void PushPacketToVDecoder(void);
    int32_t DoSeekIfNeed(void);
    void FlushDecoder(void);

private:
    PlayerControlStateMachine *m_stateMachine;
    PlayerControlSMObserver *m_observer;
    bool m_isInited;
    pthread_mutex_t m_demuxMutex;
    FormatFileInfo m_fmtFileInfo;
    PlayerCtrlCallbackParam m_eventCallback; /* the regeisted call back function */
    bool m_isNeedPause; /* need to pause after first frame render */
    bool m_isFirstFramePaused; /* first frame pause already take effect */
    bool m_pauseMode;
    bool m_isPlayEnd;
    bool m_isVidPlayEos;
    bool m_isAudPlayEos;
    PlayerControlParam m_playerParam;
    FormatFrame m_formatPacket;
    bool m_cachedPacket;
    int64_t m_lastRendPos;
    uint64_t m_lastNotifyTime;
    /* TPlay */
    PlayerTplayMode m_tplayMode;
    TplayAttr m_tplayAttr;
    uint32_t m_lastReadPktStrmIdx;
    int64_t m_lastReadPktPts;
    int64_t m_lastSendPktPts;
    int32_t m_curSeekOffset;
    bool m_isVideoStarted;
    bool m_isAudioStarted;
    bool m_isVidContinueLost;
    bool m_strmReadEnd;
    bool m_isPlayErr;
    bool m_isTplayLastFrame;
    bool m_isTplayStartRead;
    int64_t m_lastSendVdecPts;
    int64_t m_lastSendAdecPts;
    int64_t currentPosition_ = 0;
    HiAvplayStreamAttr streamAttr_;
    HiAvplayVdecAttr vdecAttr_;
    HiAvplayAdecAttr adecAttr_;
    bool paused;
    bool schThreadExit;
    bool loop_;
    bool hasRenderAudioEos_;
    bool hasRenderVideoEos_;
    uint32_t renderSleepTime_;
    float leftVolume_;
    float rightVolume_;
    pthread_mutex_t schMutex_;
    pthread_cond_t schCond_;
    pthread_t schProcess;
    int64_t seekToTimeMs_;
    SourceType m_sourceType_;
    int32_t m_fd_;
    std::string m_filePath_;
    BufferStream m_stream_;
    std::shared_ptr<PlayerSource> m_playerSource_;
    std::shared_ptr<SinkManager> m_sinkManager_;
    OutputInfo audioCachedOutBuffer_;
    OutputInfo videoCachedOutBuffer_;
    std::shared_ptr<Decoder> audioDecoder_;
    std::shared_ptr<Decoder> videoDecoder_;
    Surface *m_surface;

private:
    LitePlayer(const LitePlayer &);
    LitePlayer &operator=(const LitePlayer &);
};
}
}
#endif  // LITEPLAYER_H__
