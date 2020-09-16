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


#include "fstream"
#include "iostream"
#include "thread"
#include "unistd.h"
#include <climits>
#include <sys/prctl.h>
#include <fcntl.h>
#include "securec.h"
#include "gtest/gtest.h"
#include "surface.h"
#include "source.h"
#include "player.h"
#include "format.h"

const int FRAME_RATE_DEFAULT = 30;
const int FILE_PATH_LEN = 2048;

#define DOFUNC_STR_NORET(func, str) \
    do { \
        HI_S32 s32Ret = 0; \
        s32Ret = func; \
        if (s32Ret != HI_SUCCESS) \
        { \
            printf("[liteplayer_sample][%s:%d] ret:%d, %s \n", __FILE__, __LINE__, s32Ret, str); \
            return NULL; \
        } \
    } while (0)

#define DOFUNC_STR_RET(func, str) \
    do { \
        HI_S32 s32Ret = 0; \
        s32Ret = func; \
        if (s32Ret != HI_SUCCESS) \
        { \
            printf("[liteplayer_sample][%s:%d] ret:%d, %s \n", __FILE__, __LINE__, s32Ret, str); \
            return HI_FAILURE; \
        } \
    } while (0)

#define IS_OK(ret) \
do { \
    if (ret != 0) { \
        printf("[%s: %d] ret:%d\n", __func__, __LINE__, ret); \
    } \
} while (0)

using namespace std;
using namespace OHOS::Media;
using namespace testing::ext;

namespace OHOS {
using OHOS::Media::Player;
using OHOS::Media::PlayerSeekMode;
using OHOS::Media::Source;
using OHOS::Media::Format;
using OHOS::Media::StreamSource;
using OHOS::Media::StreamCallback;

class StreamSourceSample;
class StreamSource;
class StreamCallback;
class Format;
typedef struct TagTestSample {
    std::shared_ptr<Player> adaptr;
    pthread_t process;
    pthread_mutex_t mutex;
    int32_t isThreadRunning;
    int32_t sourceType;
    char filePath[FILE_PATH_LEN];
    std::shared_ptr<StreamSourceSample> streamSample;
} TestSample;

typedef struct TagIdleBuffer {
    size_t idx;
    size_t offset;
    size_t size;
} IdleBuffer;

class StreamSourceSample :public StreamSource {
public:
    StreamSourceSample(void);
    ~StreamSourceSample(void);
    void OnBufferAvailable(size_t index, size_t offset, size_t size);
    void SetStreamCallback(const std::shared_ptr<StreamCallback> &callback);
    uint8_t *GetBufferAddress(size_t idx);
    void QueueBuffer(size_t index, size_t offset, size_t size, int64_t timestampUs, uint32_t flags);
    int GetAvailableBuffer(IdleBuffer* buffer);
    std::weak_ptr<StreamCallback> m_callBack;
private:

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
static void* StreamProcess(void* arg)
{
#define READ_LEN  (1024)
    IdleBuffer buffer;
    int ret;
    uint8_t *data = nullptr;
    size_t readLen;
    size_t len;
    TestSample *sample = (TestSample *)arg;
    FILE* pFile = fopen(sample->filePath, "rb");
    if (pFile == nullptr) {
        return nullptr;
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

void SetSchParam(void)
{
    int ret;
    struct sched_param param;
    pthread_attr_t attr;
    ret = pthread_attr_getschedparam(&attr, &param);
    param.sched_priority = 9;
    ret = pthread_setschedparam(pthread_self(), SCHED_RR, &param);
}
} // namespace OHOS

using namespace OHOS;
const int HI_SUCCESS = 0;
const int HI_FAILURE = -1;

static TagTestSample g_tagTestSample;
static const char *VEDIO_FILE_NAME = "0506_480p.mp4";
static const char *AUDIO_FILE_NAME = "AACLC_1channel_001.aac";
class Demo : public testing::Test {
protected:
    static void SetUpTestCase(void) {
    }
    static void TearDownTestCase(void) {
    }
    virtual void SetUp()
    {
        SetSchParam();
        g_tagTestSample.adaptr = std::make_shared<Player>();
    }
    virtual void TearDown()
    {
        int32_t ret = g_tagTestSample.adaptr->Reset();
        ret = g_tagTestSample.adaptr->Release();
        if (g_tagTestSample.sourceType == 2) {
            pthread_mutex_lock(&g_tagTestSample.mutex);
            g_tagTestSample.isThreadRunning = 0;
            pthread_mutex_unlock(&g_tagTestSample.mutex);
            pthread_join(g_tagTestSample.process, nullptr);
            pthread_mutex_destroy(&g_tagTestSample.mutex);
        }
    }
};

static int32_t CreateAndSetSource(int32_t sourceType, const char *argv)
{
    if (sourceType != 1 && sourceType != 2) {
        printf("unsupport!\n", errno);
        return -1;
    }
    g_tagTestSample.sourceType = sourceType;
    if (realpath(argv, g_tagTestSample.filePath) == nullptr) {
        printf("realpath input file failed, errno: %d!\n", errno);
        return -1;
    }
    if (sourceType == 1) {
        std::string uri(g_tagTestSample.filePath);
        std::map<std::string, std::string> header;
        Source source(uri, header);
        int32_t ret = g_tagTestSample.adaptr->SetSource(source);
        EXPECT_EQ(HI_SUCCESS, ret);
    } else {
        struct stat stFileState = {0};
        if (lstat(g_tagTestSample.filePath, &stFileState) != 0) {
            printf("lstat %s failed, please check the file exist, errno:%d\n", g_tagTestSample.filePath, errno);
            return -1;
        }
        g_tagTestSample.streamSample = std::make_shared<StreamSourceSample>();
        Format formats;
        formats.SetFormat(CODEC_MIME, MIME_AUDIO_AAC);
        Source source(g_tagTestSample.streamSample, formats);

        int32_t ret1 = g_tagTestSample.adaptr->SetSource(source); // forward
        EXPECT_EQ(HI_SUCCESS, ret1);
        pthread_mutex_init(&g_tagTestSample.mutex, nullptr);
        g_tagTestSample.isThreadRunning = 1;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setstacksize(&attr, 0x10000);
        int32_t ret = pthread_create(&g_tagTestSample.process, &attr, StreamProcess, &g_tagTestSample);
        if (ret != 0) {
            printf("pthread_create failed %d\n", ret);
            g_tagTestSample.isThreadRunning = 0;
            return -1;
        }
    }
    return 0;
}

HWTEST_F(Demo, Test_SetSource01, TestSize.Level0){
    int32_t ret = CreateAndSetSource(1, VEDIO_FILE_NAME);
    EXPECT_EQ(HI_SUCCESS, ret);
}

HWTEST_F(Demo, Test_Prepare01, TestSize.Level0){
    int32_t ret = CreateAndSetSource(1, VEDIO_FILE_NAME);
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Prepare();
    EXPECT_EQ(HI_SUCCESS, ret);
}

HWTEST_F(Demo, Test_Prepare02, TestSize.Level0){
    int32_t ret = g_tagTestSample.adaptr->Prepare();
    EXPECT_EQ(HI_FAILURE, ret);
}

HWTEST_F(Demo, Test_Play01, TestSize.Level0){
    int32_t ret = CreateAndSetSource(1, VEDIO_FILE_NAME);
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Prepare();
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Play();
    sleep(10);
    EXPECT_EQ(HI_SUCCESS, ret);
}

HWTEST_F(Demo, Test_Play02, TestSize.Level0){
    int32_t ret = g_tagTestSample.adaptr->Play();
    EXPECT_EQ(HI_FAILURE, ret);
}

HWTEST_F(Demo, Test_Play03, TestSize.Level0){
    int32_t ret = CreateAndSetSource(2, AUDIO_FILE_NAME);
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Prepare();
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Play();
    sleep(10);
    EXPECT_EQ(HI_SUCCESS, ret);
}

HWTEST_F(Demo, Test_IsPlaying01, TestSize.Level0){
    int32_t ret = CreateAndSetSource(1, VEDIO_FILE_NAME);
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Prepare();
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Play();
    EXPECT_EQ(HI_SUCCESS, ret);
    sleep(10);
    bool flag = g_tagTestSample.adaptr->IsPlaying();  // IsLoop()
    EXPECT_EQ(true, flag);
}

HWTEST_F(Demo, Test_Stop01, TestSize.Level0){
    int32_t ret = CreateAndSetSource(1, VEDIO_FILE_NAME);
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Prepare();
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Play();
    EXPECT_EQ(HI_SUCCESS, ret);
    sleep(10);
    ret = g_tagTestSample.adaptr->Stop();
    EXPECT_EQ(HI_SUCCESS, ret);
}

HWTEST_F(Demo, Test_Pause01, TestSize.Level0){
    int32_t ret = CreateAndSetSource(1, VEDIO_FILE_NAME);
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Prepare();
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Play();
    EXPECT_EQ(HI_SUCCESS, ret);
    sleep(10);
    ret = g_tagTestSample.adaptr->Pause();
    EXPECT_EQ(HI_SUCCESS, ret);
}


HWTEST_F(Demo, Test_SetVolume01, TestSize.Level0){
    int32_t ret = CreateAndSetSource(1, VEDIO_FILE_NAME);
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Prepare();
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Play();
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->SetVolume(50, 50);
    EXPECT_EQ(HI_SUCCESS, ret);
}

HWTEST_F(Demo, Test_IsLooping01, TestSize.Level0){
    int32_t ret = CreateAndSetSource(1, VEDIO_FILE_NAME);
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Prepare();
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Play();
    EXPECT_EQ(HI_SUCCESS, ret);
    bool flag = g_tagTestSample.adaptr->IsLooping();
    EXPECT_EQ(false, flag);
}

HWTEST_F(Demo, Test_GetPlayerState01, TestSize.Level0){
    int32_t ret = CreateAndSetSource(1, VEDIO_FILE_NAME);
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Prepare();
    EXPECT_EQ(HI_SUCCESS, ret);
    int32_t state;
    ret = g_tagTestSample.adaptr->GetPlayerState(state);
    EXPECT_EQ(HI_SUCCESS, ret);
}

HWTEST_F(Demo, Test_GetCurrentPosition01, TestSize.Level0){
    int32_t ret = CreateAndSetSource(1, VEDIO_FILE_NAME);
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Prepare();
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Play();
    EXPECT_EQ(HI_SUCCESS, ret);
    sleep(10);
    int64_t currentPosition;
    ret = g_tagTestSample.adaptr->GetCurrentPosition(currentPosition);
    EXPECT_EQ(HI_SUCCESS, ret);
}

HWTEST_F(Demo, Test_GetDuration01, TestSize.Level0){
    int32_t ret = CreateAndSetSource(1, VEDIO_FILE_NAME);
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Prepare();
    EXPECT_EQ(HI_SUCCESS, ret);
    int64_t duration;
    ret = g_tagTestSample.adaptr->GetDuration(duration);
    EXPECT_EQ(HI_SUCCESS, ret);
}

HWTEST_F(Demo, Test_GetVideoWidth01, TestSize.Level0){
    int32_t ret = CreateAndSetSource(1, VEDIO_FILE_NAME);
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Prepare();
    EXPECT_EQ(HI_SUCCESS, ret);
    int32_t videoWidth;
    ret = g_tagTestSample.adaptr->GetVideoWidth(videoWidth);
    EXPECT_EQ(HI_SUCCESS, ret);
}

HWTEST_F(Demo, Test_GetVideoHeight01, TestSize.Level0){
    int32_t ret = CreateAndSetSource(1, VEDIO_FILE_NAME);
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Prepare();
    EXPECT_EQ(HI_SUCCESS, ret);
    int32_t videoHeight;
    ret = g_tagTestSample.adaptr->GetVideoHeight(videoHeight);
    EXPECT_EQ(HI_SUCCESS, ret);
}

HWTEST_F(Demo, Test_SetPlaybackSpeed01, TestSize.Level0){
    int32_t ret = CreateAndSetSource(1, VEDIO_FILE_NAME);
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Prepare();
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Play();
}

HWTEST_F(Demo, Test_GetPlaybackSpeed01, TestSize.Level0){
    int32_t ret = CreateAndSetSource(1, VEDIO_FILE_NAME);
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Prepare();
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Play();
    EXPECT_EQ(HI_SUCCESS, ret);
}

HWTEST_F(Demo, Test_SetLoop01, TestSize.Level0){
    int32_t ret = CreateAndSetSource(1, VEDIO_FILE_NAME);
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Prepare();
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Play();
    EXPECT_EQ(HI_SUCCESS, ret);
    sleep(10);
    bool loop = true;
    ret = g_tagTestSample.adaptr->SetLoop(loop);
    EXPECT_EQ(HI_SUCCESS, ret);
}

HWTEST_F(Demo, Test_Reset01, TestSize.Level0){
    int32_t ret = CreateAndSetSource(1, VEDIO_FILE_NAME);
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Prepare();
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Play();
    EXPECT_EQ(HI_SUCCESS, ret);
    sleep(10);
    ret = g_tagTestSample.adaptr->Reset();
    EXPECT_EQ(HI_SUCCESS, ret);
}

HWTEST_F(Demo, Test_Release01, TestSize.Level0){
    int32_t ret = CreateAndSetSource(1, VEDIO_FILE_NAME);
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Prepare();
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Play();
    EXPECT_EQ(HI_SUCCESS, ret);
    sleep(10);
    ret = g_tagTestSample.adaptr->Reset();
    EXPECT_EQ(HI_SUCCESS, ret);
    ret = g_tagTestSample.adaptr->Release();
    EXPECT_EQ(HI_SUCCESS, ret);
}