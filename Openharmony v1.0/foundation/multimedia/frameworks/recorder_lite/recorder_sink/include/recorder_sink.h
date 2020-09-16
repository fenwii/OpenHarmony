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

#ifndef RECORDER_SINK_H
#define RECORDER_SINK_H

#include <cstddef>
#include <cstdint>
#include <time.h>
#include <memory>

#include "media_errors.h"
#include "media_info.h"
#include "format.h"
#include "format_type.h"
#include "recorder.h"

namespace OHOS {
namespace Media {
using namespace std;


class RecorderSink {
public:

    RecorderSink();
    virtual ~RecorderSink();

    int32_t AddTrackSource(const TrackSource &trackSource, int32_t &trackId);
    int32_t WriteData(int32_t trackId, FormatFrame &frameData) const;
    int32_t SetOutputFormat(OutputFormat format);
    int32_t SetOutputPath(const string &path);
    int32_t SetOutputFile(int32_t fd);
    int32_t SetNextOutputFile(int32_t fd);
    int32_t SetMaxDuration(int64_t duration);
    int32_t SetMaxFileSize(int64_t size);
    int32_t SetOrientationHint(int degrees);
    int32_t SetLocation(int latitude, int longitude);
    int32_t SetRecorderCallback(const std::shared_ptr<RecorderCallback> &callback);
    int32_t Prepare();
    int32_t Start();
    int32_t Stop(bool block);
    int32_t Reset();
    int32_t Release();
    int32_t SetFileSplitDuration(ManualSplitType type, int64_t timestamp, uint32_t duration);
    int32_t SetParameter(int32_t trackId, const Format &format);

    int32_t SendCallbackInfo(int32_t type, int32_t extra);
    int32_t SendCallbackError(int32_t errorType, int32_t errorCode);

private:
    int32_t CheckPrepared();
    int32_t CheckStarted() const;
    void *formatMuxerHandle_;
    bool prepared_;
    bool started_;
    OutputFormat outputFormat_;
    FormatOutputConfig outputConfig_;
    int32_t outputFd_;
    std::string path_;
    int64_t maxFileSize_;
    int64_t maxDuration_;
    std::shared_ptr<RecorderCallback> recCallBack_;
    std::shared_ptr<FormatCallback> sinkCallback_;
};
}  // namespace Media
}  // namespace OHOS

#endif  // RECORDER_SINK_H
