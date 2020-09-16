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

#ifndef PLAYER_SOURCE_H
#define PLAYER_SOURCE_H

#include "player_demux.h"
#include <memory>
#include <vector>

using namespace std;

namespace OHOS {
namespace Media {
class PlayerDemuxer;
class PlayerSource {
friend PlayerDemuxer;
public:
    PlayerSource();
    ~PlayerSource();
    int32_t Init();
    int32_t SetSource(int32_t fd);
    int32_t SetSource(const char *url);
    int32_t SetSource(BufferStream &stream);
    int32_t SetCallBack(PlayEventCallback &callBack);
    int32_t Prepare(void);
    int32_t GetFileInfo(FormatFileInfo &fileInfo);
    int32_t SelectTrack(int32_t programId, int32_t trackId);
    int32_t UnselectTrack(int32_t programId, int32_t trackId);
    int32_t GetSelectedTrack(int32_t &programId, int32_t trackId[], int32_t &nums);
    int32_t Start();
    int32_t ReadFrame(FormatFrame &frame);
    int32_t FreeFame(FormatFrame &frame);
    int32_t Seek(int32_t streamIndex, int64_t timeStampUs, FormatSeekMode mode);
    int32_t Stop();
    int32_t SetParam(int32_t trackId, const ParameterItem *metaData, int32_t metaDataCnt);
    int32_t GetParam(int32_t trackId, ParameterItem &metaData);
private:
    bool m_inited_;
    bool m_prepared_;
    bool m_started_;
    SourceType m_sourceType_;
    int32_t m_fd_;
    std::string m_filePath_;
    BufferStream m_stream_;
    std::shared_ptr<PlayerDemuxer> m_demuxer_;
};
}  // namespace Media
}  // namespace OHOS

#endif  // PLAYER_SOURCE_H
