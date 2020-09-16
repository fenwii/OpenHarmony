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

#ifndef UNITY_CONFIG_H
#define UNITY_CONFIG_H

#include <stdio.h>

#define UNITY_EXCLUDE_LIMITS_H

#define UNITY_EXCLUDE_STDINT_H

#define UNITY_OUTPUT_CHAR(a)                 printf("%c",a)


#define UNITY_EXCLUDE_SETJMP_H
#define UNITY_EXCLUDE_MATH_H

#endif /* UNITY_CONFIG_H */
