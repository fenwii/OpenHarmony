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

#ifndef SAMGR_TEST_UTILS
#define SAMGR_TEST_UTILS

#include <cstdio>
#include <cstdlib>
#include "samgr_lite.h"

const int MS2US = 1000;
const int OPER_INTERVAL = 200;

const int PRESSURE_BASE = 1024 * 10;
const int PRESSURE_L0 = 1024;

void SystemInitProxy();

#endif