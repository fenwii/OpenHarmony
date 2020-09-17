/*
 * Copyright (c) [2019] Huawei Technologies Co.,Ltd.All rights reserved.
 *
 * OpenArkCompiler is licensed under the Mulan PSL v1.
 * You can use this software according to the terms and conditions of the Mulan PSL v1.
 * You may obtain a copy of Mulan PSL v1 at:
 *
 *     http://license.coscl.org.cn/MulanPSL
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR
 * FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v1 for more details.
 */
#ifndef MAPLE_UTIL_INCLUDE_MUID_H
#define MAPLE_UTIL_INCLUDE_MUID_H

// This is shared between maple compiler and runtime.

#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>

#ifdef USE_32BIT_REF
#define USE_64BIT_MUID
#endif // USE_32BIT_REF

constexpr unsigned int kSystemNamespace = 0xc0;
constexpr unsigned int kApkNamespace = 0x80;
constexpr unsigned int kBitMask = 0x3f;

#ifdef USE_64BIT_MUID
#undef MUID_LENGTH
#define MUID_LENGTH 8
#else
#undef MUID_LENGTH
#define MUID_LENGTH 16
#endif // USE_64BIT_MUID

// muid-related files are shared between maple compiler and runtime, thus not in
// namespace maplert

struct MuidContext {
  unsigned int a, b, c, d;
  unsigned int count[2];
  unsigned int block[16];
  unsigned char buffer[64];
};

struct MUID {
  union {
#ifdef USE_64BIT_MUID
    uint64_t raw;
    uint32_t words[2];
    uint8_t bytes[MUID_LENGTH];
#else
    uint64_t words[2];
    uint8_t bytes[MUID_LENGTH];
#endif // USE_64BIT_MUID
  } data;

  MUID() {
    data.words[0] = 0;
    data.words[1] = 0;
  }
  inline bool IsSystemNameSpace() const {
    return (data.bytes[MUID_LENGTH - 1] & ~kBitMask) == kSystemNamespace;
  }
  inline bool IsApkNameSpace() const {
    return (data.bytes[MUID_LENGTH - 1] & ~kBitMask) == kApkNamespace;
  }
  inline void SetSystemNameSpace() {
    data.bytes[MUID_LENGTH - 1] &= kBitMask;
    data.bytes[MUID_LENGTH - 1] |= kSystemNamespace;
  }
  inline void SetApkNameSpace() {
    data.bytes[MUID_LENGTH - 1] &= kBitMask;
    data.bytes[MUID_LENGTH - 1] |= kApkNamespace;
  }
  bool operator<(const MUID &muid) const {
    return (data.words[1] < muid.data.words[1] ||
            (data.words[1] == muid.data.words[1] && data.words[0] < muid.data.words[0]));
  }
  bool operator>(const MUID &muid) const {
    return (data.words[1] > muid.data.words[1] ||
            (data.words[1] == muid.data.words[1] && data.words[0] > muid.data.words[0]));
  }
  bool operator==(const MUID &muid) const {
    return data.words[1] == muid.data.words[1] && data.words[0] == muid.data.words[0];
  }
  bool operator!=(const MUID &muid) const {
    return data.words[1] != muid.data.words[1] || data.words[0] != muid.data.words[0];
  }
  std::string ToStr() const {
    std::stringstream sbuf;
#ifdef USE_64BIT_MUID
    sbuf << std::setfill('0') << std::setw(8) << std::hex << data.words[1]
         << std::setfill('0') << std::setw(8) << std::hex << data.words[0];
#else
    sbuf << std::setfill('0') << std::setw(16) << std::hex << data.words[1]
         << std::setfill('0') << std::setw(16) << std::hex << data.words[0];
#endif // USE_64BIT_MUID
    return sbuf.str();
  }

  // Return 64-bit size hash for AArch64.
  std::size_t hash() const {
#ifdef USE_64BIT_MUID
    return data.raw;
#else
    return data.words[0]; // Just return one word.
#endif // USE_64BIT_MUID
  }
};

void MuidInit(MuidContext *status);
void MuidDecode(MuidContext *status, const void *data, uint64_t size);
void MuidEncode(unsigned char *result, MuidContext *status, bool use64bit = false);

MUID GetMUID(const std::string &symbolName, bool forSystem = true);
#endif
