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
#ifndef OHOS_ACELITE_JS_PROFILER_H
#define OHOS_ACELITE_JS_PROFILER_H
#include "acelite_config.h"
#include "js_config.h"
#include "memory_heap.h"
#include "non_copyable.h"
#include <cstdint>
#include <stddef.h>

/*
 * Wrapper macro, use directly in code after including this header file.
 */
#if ENABLED(JS_PROFILER)
// start tracing for one given phase, and return a traceId which will be used when calling STOP_TRACING
#define START_TRACING(traceTag) JSProfiler::GetInstance()->PushTrace(traceTag, 0, 0)
// start tracing for one given phase, and provids the component name together
#define START_TRACING_WITH_COMPONENT_NAME(traceTag, componentNameId) \
    JSProfiler::GetInstance()->PushTrace(traceTag, componentNameId, 0)
#define START_TRACING_WITH_EXTRA_INFO(traceTag, componentNameId, extraInfoId) \
    JSProfiler::GetInstance()->PushTrace(traceTag, componentNameId, extraInfoId)
// stop tracing
#define STOP_TRACING() JSProfiler::GetInstance()->PopTrace()
#define OUTPUT_TRACE() JSProfiler::GetInstance()->Output()
#else // ENABLED(JS_PROFILER)
#define START_TRACING(traceTag)
#define START_TRACING_WITH_COMPONENT_NAME(traceTag, componentNameId)
#define START_TRACING_WITH_EXTRA_INFO(traceTag, componentNameId, extraInfoId)
#define STOP_TRACING()
#define OUTPUT_TRACE()
#endif // ENABLED(JS_PROFILER)

// invoked into compiling only if performance measurement enabled
#if ENABLED(JS_PROFILER)
namespace OHOS {
namespace ACELite {
/**
 * Define all trace point tags for performance measurement.
 *
 * NOTE: KEEP SYNC WITH g_PerformanceTagName in cpp file
 */
enum PerformanceTag {
    P_UNKNOWN = 0X00,
    LAUNCH,
    ENGINE_INIT,
    FWK_INIT,
    JS_BEGIN,
    JS_FWK_EVAL,           // 5
    JS_APP_INIT,           // 6
    JS_INIT_STATE,         // 7
    JS_INIT_DATA_GET_DATA, // 8
    JS_INIT_DATA_PROXY,    // 9
    JS_INIT_DATA_OBSERVE,  // 10
    JS_END,
    FWK_CODE_LOAD,
    FWK_CODE_EVAL,
    APP_CODE_LOAD,
    APP_CODE_EVAL,
    PAGE_CODE_LOAD,
    PAGE_CODE_EVAL,
    STYLESHEET_INIT,
    APP_ON_CREATE,
    APP_ON_DESTROY,
    ROUTER_REPLACE,
    PAGE_TRANSFER_DATA,
    PAGE_ON_INIT,
    PAGE_ON_READY,
    PAGE_ON_SHOW,
    PAGE_ON_DESTROY,
    RENDER,
    ADD_TO_ROOT_VIEW,
    RENDER_CREATE_COMPONENT,
    RENDER_COMBINE_STYLE,
    RENDER_BIND_JS_OBJECT,
    RENDER_PARSE_ATTR,
    RENDER_PARSE_EVENT,
    RENDER_APPLY_STYLE,
    RENDER_PROCESS_CHILDREN,
    SET_ATTR_PARSE_EXPRESSION,
    SET_ATTR_STRING_OF,
    SET_ATTR_PARSE_KEY_ID,
    SET_ATTR_SET_TO_NATIVE,
    APPLY_STYLE_ITEM,
    WATCHER_CALLBACK_FUNC,
    FOR_WATCHER_CALLBACK_FUNC,
    WATCHER_CONSTRUCT
};

/**
 * The max count of tracing we can support at the same time.
 * NOTE: please define this value as a multiple of 2, and dont make it's bigger than 256
 */
constexpr uint8_t maxCountAllAtOnce = 16;

// need more data slots for static profiling mode, as we record them all before output the result
constexpr uint16_t maxTracingDataCount = 512;

/**
 * Performance data holder.
 */
struct PerformanceData {
    uint64_t start; // count in clock ticks (usually 1ms)
    uint64_t end;
    uint8_t label;       // what's the phase this time cost data is representing
    uint8_t description; // other description, NOTE: we don't do string copy, so const char* must be given
    uint8_t component;
};

#ifdef FEATURE_ACELITE_MC_JS_PROFILER
static constexpr uint8_t MSG_LENGTH = 20;

struct ProfilerMsg {
    char msg[MSG_LENGTH] = {'\0'};
};
#endif

/**
 * @brief The JSProfiler class is an runtime performance recorder and outputter, used for recording
 *        runtime timecost mainly. Implemented for development and will be disabled for release version.
 */
class JSProfiler final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(JSProfiler);
    /**
     * @brief Default constructor.
     */
    JSProfiler();

    /**
     * @brief Default destructor.
     */
    ~JSProfiler();

    /**
     * @brief Use static global variable for easy access in different source code file.
     *
     * @return global JSProfiler object
     */
    static JSProfiler *GetInstance();

    /**
     * Called to free all performance data records and the global JSProfiler object.
     */
    void Release();

#ifdef FEATURE_ACELITE_MC_JS_PROFILER
    /**
     * @brief Flush output to file.
     */
    static void FlushProfilerMsg(void *data);
#endif

    /**
     * @brief Clean all performance record in data_.
     */
    void ResetData();

    /**
     * @brief Record the current timestamp for the given tag.
     *
     * @param [in] tag The given phase's trace name, must be given.
     * @param [in] name The component name of the current tracing phase, default is null.
     * @param [in] description The extra description string id (must can be parsed by KeyParser)
     * for this trace, default is null.
     *
     */
    void PushTrace(PerformanceTag tag, uint8_t name, uint8_t description);

    /**
     * @brief Calculate the time interval and log out.
     *
     */
    void PopTrace();

    /**
     * @brief Calculate all time cost and output to trace.
     *
     * NOTE: Delay the elapsed time calculating to this method to save band width.
     */
    void Output();

    /**
     * @brief Get current timestamp for recording.
     *
     * @return the current timestamp, count in clock tick, will be converted into ms during output performance data
     */
    uint64_t GetCurrentClockTick() const;

    /**
     * @brief Calculate the elapsed milliseconds from two input clock timestamp.
     *
     * @param [in] start The start timestamp, must count in clock tick.
     * @param [in] end The end timestamp, must count in clock tick.
     *
     * @return the elapsed time from start to end, count in ms
     */
    uint64_t CalculateElapsedTime(uint64_t start, uint64_t end) const;

    /**
     * @brief Check if the profiler is enabled or not.
     *
     * @return true for enabled, false for not
     */
    bool IsEnabled();

    /**
     * @brief malloc data buffer for saving performance data.
     */
    void PrepareDataBuffer();

private:
    /**
     * The trace id stack, MAX_COUNT_ALL_AT_ONCE at the same time
     */
    uint16_t traceIdStack_[maxTracingDataCount] = {0};

    /**
     * The tracing data
     */
    PerformanceData *data_ = nullptr;

    uint16_t dataCount_ = 0;
    uint16_t traceIdSlot_ = 0;
    bool enabled_ = false;
#ifdef FEATURE_ACELITE_MC_JS_PROFILER
    static constexpr uint8_t PROFILER_MSG_LENGTH = 128;
    static constexpr uint8_t TEXT_LENGTH = 30;
    ProfilerMsg *msg_ = nullptr;
#endif
};
} // namespace ACELite
} // namespace OHOS

#endif // ENABLED(JS_PROFILER)
#endif // OHOS_ACELITE_JS_PROFILER_H
