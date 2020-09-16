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

#include "animator/interpolation.h"

namespace OHOS {
/* B(t) = P0*(1-t)^3 + 3*P1*t*(1-t)^2 + 3*P2*t^2*(1-t) + P3*t^3 */
int16_t Interpolation::GetBezierInterpolation(int16_t t, int16_t u0, int16_t u1, int16_t u2, int16_t u3)
{
    int64_t invT = INTERPOLATION_RANGE - t;
    int64_t invT2 = invT * invT;
    int64_t invT3 = invT2 * invT;
    int64_t t2 = t * t;
    int64_t t3 = t2 * t;

    int64_t ret = invT3 * u0;
    ret += BESSEL_COEFFICIENT * invT2 * t * u1;
    ret += BESSEL_COEFFICIENT * invT * t2 * u2;
    ret += t3 * u3;
    ret = ret >> CUBIC_BEZIER_CALCULATE_OFFSET;
    return static_cast<int16_t>(ret);
}
}
