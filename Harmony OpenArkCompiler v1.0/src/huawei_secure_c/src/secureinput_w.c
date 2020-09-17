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

/* if some platforms don't have wchar.h, dont't include it */
#if !(defined(SECUREC_VXWORKS_PLATFORM))
/* This header file is placed below secinput.h, which will cause tool alarm,
 * but  If there is no macro above, it will cause vs2010 compiling alarm
 */
#if defined(_MSC_VER) && (_MSC_VER >= 1400)
#ifndef __STDC_WANT_SECURE_LIB__
/* The order of adjustment is to eliminate alarm of Duplicate Block */
#define __STDC_WANT_SECURE_LIB__ 0
#endif
#ifndef _CRTIMP_ALTERNATIVE
#define _CRTIMP_ALTERNATIVE     /* comment microsoft *_s function */
#endif
#endif
#include <wchar.h>
#endif
#define SECUREC_ENABLE_WCHAR_FUNC       0
#define SECUREC_FORMAT_OUTPUT_INPUT     1
#ifndef SECUREC_FOR_WCHAR
#define SECUREC_FOR_WCHAR
#endif

#include "secinput.h"

#ifndef WEOF
#define WEOF ((wchar_t)(-1))
#endif

#include "input.inl"

