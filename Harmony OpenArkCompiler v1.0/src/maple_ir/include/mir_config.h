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
/* configuration definition for code in maple_ir namespace */
#ifndef MAPLE_IR_INCLUDE_MIR_CONFIG_H
#define MAPLE_IR_INCLUDE_MIR_CONFIG_H
/**
 * MIR_FEATURE_FULL = 1 : for host/server size building, by default.
 * MIR_FEATURE_FULL = 0 : for resource-constrained devices. optimized for memory size
 */
#if !defined(MIR_FEATURE_FULL)
#define MIR_FEATURE_FULL 1  // default to full feature building, for debugging
#endif                      // MIR_FEATURE_FULL define
// assertion
#if !MIR_FEATURE_FULL
#define MIR_ASSERT(...) \
  do {                  \
  } while (0)
#define MIR_PRINTF(...) \
  do {                  \
  } while (0)
#define MIR_INFO(...) \
  do {                \
  } while (0)
#define MIR_ERROR(...) \
  do {                 \
  } while (0)
#define MIR_WARNING(...) \
  do {                   \
  } while (0)
#define MIR_CAST_TO(var, totype) ((totype)(var))
#define MIR_DYN_CAST(var, totype) ((totype)(var))
#include <stdlib.h>
#if DEBUG
#include <stdio.h>
#define MIR_FATAL(...)                                   \
  do {                                                   \
    printf("FATAL ERROR: (%s:%d) ", __FILE__, __LINE__); \
    printf(__VA_ARGS__);                                 \
    exit(1);                                             \
  } while (0)
#else
#define MIR_FATAL(...) \
  do {                 \
    exit(1);           \
  } while (0)
#endif  // DEBUG
#else   // MIR_FEATURE_FULL
#include <cassert>
#include <cstdio>
#include <cstdlib>

namespace maple {
#define MIR_ASSERT(...) assert(__VA_ARGS__)
#define MIR_FATAL(...)                                            \
  do {                                                            \
    fprintf(stderr, "FATAL ERROR: (%s:%d) ", __FILE__, __LINE__); \
    fprintf(stderr, __VA_ARGS__);                                 \
    exit(EXIT_FAILURE);                                           \
  } while (0)
#define MIR_ERROR(...)                                      \
  do {                                                      \
    fprintf(stderr, "ERROR: (%s:%d) ", __FILE__, __LINE__); \
    fprintf(stderr, __VA_ARGS__);                           \
  } while (0)
#define MIR_WARNING(...)                                      \
  do {                                                        \
    fprintf(stderr, "WARNING: (%s:%d) ", __FILE__, __LINE__); \
    fprintf(stderr, __VA_ARGS__);                             \
  } while (0)
#define MIR_PRINTF(...) printf(__VA_ARGS__)
#define MIR_INFO(...) printf(__VA_ARGS__)
#define MIR_CAST_TO(var, totype) static_cast<totype>(var)
#define MIR_DYN_CAST(var, totype) dynamic_cast<totype>(var)
#endif  // !MIR_FEATURE_FULL
/**
 * MIR specific configurations.
 */
// Note: fix size definition cannot handle arbitary long MIR lines, such
// as those array initialization lines.
constexpr int kMirMaxLineSize = 3072;  // a max of 3K characters per line initially

}  // namespace maple
#endif  // MAPLE_IR_INCLUDE_MIR_CONFIG_H
