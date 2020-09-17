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
#define SECUREC_INLINE_DO_MEMCPY 1

#include "securecutil.h"

static errno_t SecDoWcsncpy(wchar_t *strDest, size_t destMax, const wchar_t *strSrc, size_t count)
{
    size_t srcStrLen;
    if (count < destMax) {
        SECUREC_CALC_WSTR_LEN(strSrc, count, &srcStrLen);
    } else {
        SECUREC_CALC_WSTR_LEN(strSrc, destMax, &srcStrLen);
    }
    if (srcStrLen == destMax) {
        strDest[0] = '\0';
        SECUREC_ERROR_INVALID_RANGE("wcsncpy_s");
        return ERANGE_AND_RESET;
    }
    if (strDest == strSrc) {
        return EOK;
    }
    if (SECUREC_STRING_NO_OVERLAP(strDest, strSrc, srcStrLen)) {
        /* performance optimization srcStrLen not include '\0' */
        SecDoMemcpy(strDest, strSrc, srcStrLen * sizeof(wchar_t));
        *(strDest + srcStrLen) = L'\0';
        return EOK;
    } else {
        strDest[0] = L'\0';
        SECUREC_ERROR_BUFFER_OVERLAP("wcsncpy_s");
        return EOVERLAP_AND_RESET;
    }
}

/*
 * <FUNCTION DESCRIPTION>
 *    The wcsncpy_s function copies not more than n successive wide characters
 *     (not including the terminating null wide character)
 *     from the array pointed to by strSrc to the array pointed to by strDest
 *
 * <INPUT PARAMETERS>
 *    strDest             Destination string.
 *    destMax             The size of the destination string, in characters.
 *    strSrc              Source string.
 *    count                Number of characters to be copied.
 *
 * <OUTPUT PARAMETERS>
 *    strDest              is updated
 *
 * <RETURN VALUE>
 *    EOK                  Success
 *    EINVAL               strDest is  NULL and destMax != 0 and destMax <= SECUREC_WCHAR_STRING_MAX_LEN
 *    EINVAL_AND_RESET     strDest != NULL and strSrc is NULLL and destMax != 0
 *                         and destMax <= SECUREC_WCHAR_STRING_MAX_LEN
 *    ERANGE               destMax > SECUREC_WCHAR_STRING_MAX_LEN or destMax is 0
 *    ERANGE_AND_RESET     count > SECUREC_WCHAR_STRING_MAX_LEN or
 *                         (destMax <= length of strSrc and destMax <= count and strDest != strSrc
 *                          and strDest != NULL and strSrc != NULL and destMax != 0 and
 *                          destMax <= SECUREC_WCHAR_STRING_MAX_LEN and not overlap)
 *    EOVERLAP_AND_RESET     dest buffer and source buffer are overlapped and  all  parameters are valid
 *
 *
 *    If there is a runtime-constraint violation, strDest[0] will be set to the '\0' when strDest and destMax valid
 */
errno_t wcsncpy_s(wchar_t *strDest, size_t destMax, const wchar_t *strSrc, size_t count)
{
    if (destMax == 0 || destMax > SECUREC_WCHAR_STRING_MAX_LEN) {
        SECUREC_ERROR_INVALID_RANGE("wcsncpy_s");
        return ERANGE;
    }
    if (strDest == NULL || strSrc == NULL) {
        SECUREC_ERROR_INVALID_PARAMTER("wcsncpy_s");
        if (strDest != NULL) {
            strDest[0] = '\0';
            return EINVAL_AND_RESET;
        }
        return EINVAL;
    }
    if (count > SECUREC_WCHAR_STRING_MAX_LEN) {
#ifdef SECUREC_COMPATIBLE_WIN_FORMAT
        if (count == (size_t)(-1)) {
            return SecDoWcsncpy(strDest, destMax, strSrc, destMax - 1);
        }
#endif
        strDest[0] = '\0';      /* clear dest string */
        SECUREC_ERROR_INVALID_RANGE("wcsncpy_s");
        return ERANGE_AND_RESET;
    }

    if (count == 0) {
        strDest[0] = '\0';
        return EOK;
    }

    return SecDoWcsncpy(strDest, destMax, strSrc, count);
}

