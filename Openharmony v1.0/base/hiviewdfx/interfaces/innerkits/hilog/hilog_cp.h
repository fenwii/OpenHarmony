/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HIVIEWDFX_HILOG_CPP_H
#define HIVIEWDFX_HILOG_CPP_H

#include "hiview_log.h"

#ifdef __cplusplus

namespace OHOS {
namespace HiviewDFX {
typedef struct HiLogLabel {
    LogType type;
    unsigned int domain;
    const char *tag;
} HiLogLabel;

class HiLog final {
public:
    static int Debug(const HiLogLabel &label, const char *fmt, ...) __attribute__((__format__(printf, 2, 3)));
    static int Info(const HiLogLabel &label, const char *fmt, ...) __attribute__((__format__(printf, 2, 3)));
    static int Warn(const HiLogLabel &label, const char *fmt, ...) __attribute__((__format__(printf, 2, 3)));
    static int Error(const HiLogLabel &label, const char *fmt, ...) __attribute__((__format__(printf, 2, 3)));
    static int Fatal(const HiLogLabel &label, const char *fmt, ...) __attribute__((__format__(printf, 2, 3)));
};
} // namespace HiviewDFX
} // namespace OHOS
#endif // __cplusplus

#endif // HIVIEWDFX_HILOG_CPP_H
