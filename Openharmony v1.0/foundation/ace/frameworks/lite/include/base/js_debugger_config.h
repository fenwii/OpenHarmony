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

#ifndef OHOS_ACELITE_JS_DEBUGGER_CONFIG_H
#define OHOS_ACELITE_JS_DEBUGGER_CONFIG_H
#include <cstdio>
#include <cstdint>
#include "js_config.h"
#include "memory_heap.h"

/**
 * For now DEBUGGER is only supported in Simulator
 */
namespace OHOS {
namespace ACELite {
enum DebugProtocol { TCP, SERIAL };
enum DebugChannel { WEBSOCKET, RAWPACKET };
const uint16_t DEFAULT_PORT = 5001; // default port
struct DebuggerConfig : public MemoryHeap {
    DebugProtocol protocol;   // use tcp as default
    DebugChannel channel;     // use websocket as default
    uint32_t heapSize;        // the JS heap size want to setup, count in bytes
    uint16_t port;            // used for tcp, default is 5001
    bool startDebuggerServer; // default is false
    bool logToFile;           // default print to stdout
    bool snapshotMode;        // if run in snapshot mode
    char *logFilePath;        // the log file path
    DebuggerConfig()
        : protocol(TCP),
          channel(WEBSOCKET),
          heapSize(0),
          port(DEFAULT_PORT),
          startDebuggerServer(false),
          logToFile(false),
          snapshotMode(false),
          logFilePath(nullptr)
    {
    }
};

/**
 * @class Debugger
 *
 * @brief: Enable to start jerry ensign debugger for current JS application.
 *
 * This is only available for windows simulator
 */
class Debugger final : public MemoryHeap {
public:
    /**
     * @brief Get the debugger instance
     *
     * @return an instance of debugger
     */
    static Debugger &GetInstance()
    {
        static Debugger instance;
        return instance;
    }
    Debugger()
#if ENABLED(ENGINE_DEBUGGER)
        : consoleLogFileHandler_(nullptr),
#ifdef JS_ENGINE_EXTERNAL_CONTEXT
          engineContext_(nullptr),
#endif // JS_ENGINE_EXTERNAL_CONTEXT
          debuggerStarted_(false)
#endif // ENABLED(ENGINE_DEBUGGER)
          {}
    ~Debugger() = default;

    /**
     * @brief Configure related debugger
     */
    void ConfigDebugger();

    /**
     * @brief Get state of the debugger
     *
     * @return true to enable, false to disenable
     */
    bool IsDebuggerEnabled();

    /**
     * @brief Make the debugger start
     */
    void StartDebugger();

    /**
     * @brief Tear down the debugger
     */
    void TearDownDebugger();

    /**
     * @brief Configure debugger based on the config file
     *
     * @param [out] config: The configuration of the debugger
     */
    void ConfigEngineDebugger(DebuggerConfig &config);

    /**
     * @brief Print out the log into stdout
     *
     * @param [in] str: Information about log
     */
    void Output(const char *str);

    /**
     * @brief Flush the output buffer of stream
     */
    void FlushOutput();

    /**
     * @brief Setup jerry external context if needed
     */
    void SetupJSContext();

    /**
     * @brief Release jerry external context
     */
    void ReleaseJSContext();
private:
#if ENABLED(ENGINE_DEBUGGER)
    FILE *consoleLogFileHandler_;
#ifdef JS_ENGINE_EXTERNAL_CONTEXT
    void *engineContext_;
#endif // JS_ENGINE_EXTERNAL_CONTEXT
    bool debuggerStarted_;
#endif // ENABLED(ENGINE_DEBUGGER)
    DebuggerConfig debuggerConfig_;
};
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_JS_DEBUGGER_CONFIG_H
