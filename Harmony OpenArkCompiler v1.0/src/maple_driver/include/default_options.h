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
#ifndef MAPLE_DRIVER_INCLUDE_DEFAULT_OPTIONS_H
#define MAPLE_DRIVER_INCLUDE_DEFAULT_OPTIONS_H

namespace maple {
// O0 jbc2mpl options
static MplOption kJbc2mplDefaultOptionsO0[] = {
#include "default/O0_options_jbc2mpl.def"
};
// O0 ME options
static MplOption kMeDefaultOptionsO0[] = {
#include "default/O0_options_me.def"
};
// O0 mpl2mpl options
static MplOption kMpl2MplDefaultOptionsO0[] = {
#include "default/O0_options_mpl2mpl.def"
};
// O0 mplcg options
static MplOption kMplcgDefaultOptionsO0[] = {
#include "default/O0_options_mplcg.def"
};

}  // namespace maple
#endif  // MAPLE_DRIVER_INCLUDE_DEFAULT_OPTIONS_H
