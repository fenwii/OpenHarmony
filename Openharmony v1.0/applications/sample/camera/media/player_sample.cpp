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

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/prctl.h>
#include "source.h"
#include "player.h"
#include "format.h"
#include <string>
#include <sys/prctl.h>
#include "securec.h"

using OHOS::Surface;

using OHOS::Media::Player;
using OHOS::Media::PlayerSeekMode;
using OHOS::Media::Source;
using OHOS::Media::Format;
using OHOS::Media::StreamSource;
using OHOS::Media::StreamCallback;
using namespace OHOS::Media;

#define DOFUNC_STR_NORET(func , str)  \
    do { \
        HI_S32 s32Ret = 0; \
        s32Ret = func; \
        if(s32Ret != 0) \
        { \
            printf("[liteplayer_sample][%s:%d] ret:%d,  %s \n", __FILE__, __LINE__, s32Ret,str); \
            return NULL;\
        } \
    } while (0)

#define DOFUNC_STR_RET(func , str)  \
    do { \
        HI_S32 s32Ret = 0; \
        s32Ret = func; \
        if(s32Ret != 0) \
        { \
            printf("[liteplayer_sample][%s:%d] ret:%d,  %s \n", __FILE__, __LINE__, s32Ret,str); \
            return -1;\
        } \
    } while (0)

#define IS_OK(ret) \
do { \
    if (ret != 0) { \
        printf("[%s: %d] ret:%d\n", __func__, __LINE__, ret); \
    } \
} while (0)

#define SAMPLE_RETURN_VAL_IF_NULL(condition)                                           \
    do {                                                                               \
        if ((condition) == nullptr) {                                                  \
            printf("" #condition " is NULL error %s %d\n", __FUNCTION__, __LINE__);    \
            return -1;                                                         \
        }                                                                              \
    } while (0)

class StreamSourceSample;
typedef struct TagTestSample
{
    std::shared_ptr<Player> adapter;
    pthread_t process;
    pthread_mutex_t mutex;
    int32_t isThreadRunning;
    int32_t sourceType;
    char filePath[PATH_MAX];
    std::shared_ptr<StreamSourceSample> streamSample;
} TestSample;

typedef struct TagIdleBuffer{
    size_t idx;
    size_t offset;
    size_t size;
} IdleBuffer;

class StreamSourceSample :public StreamSource
{
public:
    StreamSourceSample(void);
    virtual ~StreamSourceSample(void);
    void OnBufferAvailable(size_t index, size_t offset, size_t size);
    void SetStreamCallback(const std::shared_ptr<StreamCallback> &callback);
    uint8_t *GetBufferAddress(size_t idx);
    void QueueBuffer(size_t index, size_t offset, size_t size, int64_t timestampUs, uint32_t flags);
    int GetAvailableBuffer(IdleBuffer* buffer);

private:
    std::weak_ptr<StreamCallback> m_callBack;
    std::vector<IdleBuffer> aviableBuffer;
    pthread_mutex_t m_mutex;
};

StreamSourceSample::StreamSourceSample(void)
{
    aviableBuffer.clear();
    pthread_mutex_init(&m_mutex, nullptr);
}

StreamSourceSample::~StreamSourceSample(void)
{
    aviableBuffer.clear();
    pthread_mutex_destroy(&m_mutex);
}

void StreamSourceSample::SetStreamCallback(const std::shared_ptr<StreamCallback> &callback)
{
    m_callBack = callback;
}

uint8_t *StreamSourceSample::GetBufferAddress(size_t idx)
{
    std::shared_ptr<StreamCallback> callback = m_callBack.lock();
    if (callback == nullptr) {
        return nullptr;
    }
    return callback->GetBuffer(idx);
}

void StreamSourceSample::QueueBuffer(size_t index, size_t offset, size_t size, int64_t timestampUs, uint32_t flags)
{
    std::shared_ptr<StreamCallback> callback = m_callBack.lock();
    if (callback == nullptr) {
        return;
    }
    callback->QueueBuffer(index, offset, size, timestampUs, flags);
}

void StreamSourceSample::OnBufferAvailable(size_t index, size_t offset, size_t size)
{
    IdleBuffer buffer;
    pthread_mutex_lock(&m_mutex);
    buffer.idx = index;
    buffer.offset = offset;
    buffer.size = size;
    aviableBuffer.push_back(buffer);
    pthread_mutex_unlock(&m_mutex);
}

int StreamSourceSample::GetAvailableBuffer(IdleBuffer* buffer)
{
    SAMPLE_RETURN_VAL_IF_NULL(buffer);
    pthread_mutex_lock(&m_mutex);
    if (aviableBuffer.empty()) {
        pthread_mutex_unlock(&m_mutex);
        return -1;
    }
    *buffer = aviableBuffer[0];
    aviableBuffer.erase(aviableBuffer.begin());
    pthread_mutex_unlock(&m_mutex);
    return 0;
}

static void* streamProcess(void* arg)
{
#define READ_LEN  (1024)
    IdleBuffer buffer;
    int ret;
    uint8_t *data = nullptr;
    size_t readLen;
    size_t len;
    TestSample *sample = (TestSample *)arg;
    FILE* pFile = fopen(sample->filePath, "rb");
    if (pFile == NULL) {
        return NULL;
    }
    prctl(PR_SET_NAME, "StreamProc", 0, 0, 0);
    printf("[%s,%d] file:%s\n", __func__, __LINE__, sample->filePath);
    while(sample->isThreadRunning) {
        ret = sample->streamSample->GetAvailableBuffer(&buffer);
        if (ret != 0) {
            usleep(20000);
            continue;
        }
        data = sample->streamSample->GetBufferAddress(buffer.idx);
        if (data == nullptr) {
            printf("[%s, %d] get buffer null", __func__, __LINE__);
            break;
        }
        len = (buffer.size < READ_LEN) ? buffer.size : READ_LEN;
        readLen = fread(data + buffer.offset, 1, len, pFile);
        if (readLen <= len && readLen > 0) {
            sample->streamSample->QueueBuffer(buffer.idx, buffer.offset, readLen, 0, 8);
        } else {
            sample->streamSample->QueueBuffer(buffer.idx, buffer.offset, readLen, 0, 4);
            break;
        }
    }
    fclose(pFile);
    printf("[%s,%d]\n", __func__, __LINE__);
    return NULL;
}

static void SampleCmd(TestSample &sample)
{
    char cmd[64];   /* 64: Array length */
    int ret;
    int64_t timeMs = 0;
    int64_t duration;
    int64_t currentPosition;
    int32_t videoWidth;
    int32_t videoHeight;
    float lvolume;
    float rvolume;
    int loop = 0;

    printf("Input CMD: quit, show, pause(pu), play(pl), seek [ms], volume [lvol] [rvol], loop\n");
    while (fgets(cmd, 20, stdin)) {  /* 10: use array length */
        cmd[20] = '\0';  /* 10: end of string */
        if (strncmp(cmd, "quit", 4) == 0) {
            break;
        } else if (strncmp(cmd, "pause", 4) == 0 || strncmp(cmd, "pu", 2) == 0) {
            ret = sample.adapter->Pause();
        } else if (strncmp(cmd, "play", 4) == 0 || strncmp(cmd, "pl", 2) == 0) {
            ret = sample.adapter->Play();
        } else if (strncmp(cmd, "seek", 4) == 0) {
            if (sscanf_s(cmd, "seek %d", &timeMs) != 1) {
                printf("ERR: not input seek time, example: seek 1000!\n");
                continue;
            }
            if (sample.sourceType < 2) {
               sample.adapter->Rewind(timeMs, PlayerSeekMode::PLAYER_SEEK_PREVIOUS_SYNC);
            }
        } else if (strncmp(cmd, "volume", 6) == 0) {
            if (sscanf_s(cmd, "volume %f %f", &lvolume, &rvolume) != 2) {
                printf("ERR: not input volume, example: volume 50 50!\n");
                continue;
            }
            printf("try set volume %f %f\n", lvolume, rvolume);
            ret = sample.adapter->SetVolume(lvolume, rvolume);
        } else if (strncmp(cmd, "show", 4) == 0) {
            printf("now show player info\n");

            printf("player IsPlaying:%d IsSingleLooping:%d\n",
                   sample.adapter->IsPlaying(), sample.adapter->IsSingleLooping());

            ret = sample.adapter->GetDuration(duration);
            IS_OK(ret);
            ret = sample.adapter->GetCurrentTime(currentPosition);
            IS_OK(ret);
            printf("player duration:%lld GetCurrentTime:%ld\n", duration, currentPosition);

            ret = sample.adapter->GetVideoWidth(videoWidth);
            IS_OK(ret);
            ret = sample.adapter->GetVideoHeight(videoHeight);
            IS_OK(ret);
            printf("player videoWidth:%d videoHeight:%d\n", videoWidth, videoHeight);
        } else if (strncmp(cmd, "loop", 4) == 0) {
            if (sscanf_s(cmd, "loop %d", &loop) != 1) {
                printf("ERR: not input loop flag, example: loop 1!\n");
                continue;
            }
            printf("try set loop %d\n", loop);
            ret = sample.adapter->EnableSingleLooping(loop == 1);
            IS_OK(ret);
            printf("Set loop %d\n", loop);
        } else {
            printf("Input CMD: quit, show, pause(pu), play(pl), seek [ms], volume [lvol] [rvol], loop\n");
        }
    }
}

void SetSchParam(void)
{
    struct sched_param param;
    pthread_attr_t attr;

    (void)pthread_attr_getschedparam(&attr, &param);
    param.sched_priority = 9;
    (void)pthread_setschedparam(pthread_self(), SCHED_RR, &param);
}

int main(int argc, char** argv)
{
    prctl(PR_SET_NAME, "mainProc", 0, 0, 0);
    int sourceType = 1;
    SAMPLE_RETURN_VAL_IF_NULL(argv);
    if (argc < 2) {  /* 2: Minimum number of inputs */
        printf("usage: %s filename  (or vpss channel index)\n", argv[0]);
        return -1;
    }
    if (argc >= 3) {  /* 4:  sourceType */
        sourceType = atoi(argv[2]);  /*  */
        if ((sourceType != 1) && (sourceType != 2)) {
            printf("unsuport sourceType:%d\n", sourceType);
            return -1;
        }
    }
    TestSample sample;
    sample.sourceType = sourceType;
    if (realpath(argv[1], sample.filePath) == nullptr) {
        printf("realpath input file failed, errno: %d!\n", errno);
        return -1;
    }
    sample.adapter = std::make_shared<Player>();
    int64_t duration;
    int32_t width;
    int32_t heighth;
    Format formats;
    printf("[%s,%d]\n", __func__, __LINE__);
    SetSchParam();
    printf("[%s,%d]\n", __func__, __LINE__);

    printf("[%s,%d] sourceType:%d, path:%s\n", __func__, __LINE__, sourceType, sample.filePath);
    if (sourceType == 1) {
        std::string uri(sample.filePath);
        std::map<std::string, std::string> header;
        Source source(uri, header);
        sample.adapter->SetSource(source);
    } else {
        struct stat stFileState = {0};
        if (lstat(sample.filePath, &stFileState) != 0) {
            printf("lstat %s failed, please check the file exist, errno:%d\n", sample.filePath, errno);
            return -1;
        }
        sample.streamSample = std::make_shared<StreamSourceSample>();
        formats.PutStringValue(CODEC_MIME, MIME_AUDIO_AAC);
        Source source(sample.streamSample, formats);
        sample.adapter->SetSource(source);
        pthread_mutex_init(&sample.mutex, nullptr);
        sample.isThreadRunning = 1;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setstacksize(&attr, 0x10000);
        int32_t ret = pthread_create(&sample.process, &attr, streamProcess, &sample);
        if (ret != 0) {
            printf("pthread_create failed %d\n", ret);
            sample.isThreadRunning = 0;
            return -1;
        }
    }

    sample.adapter->Prepare();

    sample.adapter->GetDuration(duration);
    printf("[%s,%d] GetDuration:%lld\n", __func__, __LINE__, duration);
    sample.adapter->GetVideoWidth(width);
    printf("[%s,%d] width:%d\n", __func__, __LINE__, width);
    sample.adapter->GetVideoHeight(heighth);
    printf("[%s,%d] heighth:%d\n", __func__, __LINE__, heighth);

    Surface *surface = Surface::CreateSurface();
    if (surface == nullptr) {
        printf("[%s,%d] CreateSurface failed\n",  __func__, __LINE__);
        return -1;
    }
    surface->SetUserData("region_position_x", "0");
    surface->SetUserData("region_position_y", "0");
    surface->SetUserData("region_width", "480");
    surface->SetUserData("region_height", "480");
    sample.adapter->SetVideoSurface(surface);

    sample.adapter->Play();

    /* ¶¨ÖÆ»¯´¦Àí */
    SampleCmd(sample);

    sample.adapter->Stop();
    sample.adapter->Reset();

    sample.adapter->Release();
    if (sample.sourceType == 2) {
        pthread_mutex_lock(&sample.mutex);
        sample.isThreadRunning = 0;
        pthread_mutex_unlock(&sample.mutex);
        pthread_join(sample.process, nullptr);
        pthread_mutex_destroy(&sample.mutex);
    }
    printf("[%s, %d] main end\n", __func__, __LINE__);
    return 0;
}
