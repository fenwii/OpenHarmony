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

#ifndef OHOS_ACELITE_KEY_PARSER_H
#define OHOS_ACELITE_KEY_PARSER_H
#include <cstdint>
#include "ace_mem_base.h"
#include "memory_heap.h"
#include "non_copyable.h"
namespace OHOS {
namespace ACELite {
class KeyParser final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(KeyParser);
    /**
     * @fn uint16_t ParseKeyId(const char* s)
     *
     * @brief Search the key id in the keyword info with key string,
     * do not use by default
     *
     * @param[in] The key string to be parsed
     *
     * @return The key id enum value
     */
    static uint16_t ParseKeyId(const char * const s);

    /**
     * @fn uint16_t ParseKeyId(const char* s, const size_t len)
     *
     * @brief Search the key id in the keyword info with key string,
     * add the length string has better performance
     *
     * @param[in] The key string to be parsed
     *
     * @param[in] The key string length
     *
     * @return The key id enum value
     */
    static uint16_t ParseKeyId(const char *keystr, const size_t len);

    /**
     * @fn bool IsKeyValid(uint16_t id)
     *
     * @brief Check if the input id is supported.
     *
     * @param[in] The id
     *
     * @return true if the given id is valid, false for otherwise
     */
    static bool IsKeyValid(uint16_t id);

    /**
     * @fn const char* GetKeyById(uint16_t id);
     *
     * @brief Get the key string by id index, for debugging print,
     * do not support by default
     *
     * @param[in] The key id for index
     *
     * @return The key string
     */
    static const char *GetKeyById(uint16_t id);

    /**
     * @fn uint8_t GetKeyLengthById(uint16_t id);
     *
     * @brief Get the key string length,
     *
     * @param[in] The key id for index
     *
     * @return The key string length, less than UINT8_MAX
     */
    static uint8_t GetKeyLengthById(uint16_t id);

private:
    KeyParser() {}
    ~KeyParser() {}
};
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_KEY_PARSER_H
