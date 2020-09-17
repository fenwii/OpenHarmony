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
/* [Standardize-exceptions] Use unsafe function: Performance-sensitive
 * [reason] Always used in the performance critical path,
 *          and sufficient input validation is performed before calling
 */
#define SECUREC_INLINE_STR_LEN 1
#define SECUREC_INLINE_DO_MEMCPY 1

#include "securecutil.h"

#if defined(SECUREC_COMPATIBLE_WIN_FORMAT)
#define SECUREC_STRNCPY_PARAM_OK(strDest, destMax, strSrc, count) \
    (((destMax) > 0 && (destMax) <= SECUREC_STRING_MAX_LEN && (strDest) != NULL && (strSrc) != NULL && \
    ((count) <= SECUREC_STRING_MAX_LEN || (count) == ((size_t)(-1))) && (count) > 0))
#else
#define SECUREC_STRNCPY_PARAM_OK(strDest, destMax, strSrc, count) \
    (((destMax) > 0 && (destMax) <= SECUREC_STRING_MAX_LEN && (strDest) != NULL && (strSrc) != NULL && \
    (count) <= SECUREC_STRING_MAX_LEN && (count) > 0))
#endif

/*
 * Check Src Count Range
 */
static errno_t CheckSrcCountRange(char *strDest, size_t destMax, const char *strSrc, size_t count)
{
    size_t tmpDestMax = destMax;
    size_t tmpCount = count;
    const char *endPos = strSrc;

    /* use destMax and  count as boundary checker and destMax must be greater than zero */
    while (*(endPos) != '\0' && tmpDestMax > 0 && tmpCount > 0) {
        ++endPos;
        --tmpCount;
        --tmpDestMax;
    }
    if (tmpDestMax == 0) {
        strDest[0] = '\0';
        SECUREC_ERROR_INVALID_RANGE("strncpy_s");
        return ERANGE_AND_RESET;
    }
    return EOK;
}

/*
 * Handling errors, when dest euqal src return EOK
 */
errno_t strncpy_error(char *strDest, size_t destMax, const char *strSrc, size_t count)
{
    if (destMax == 0 || destMax > SECUREC_STRING_MAX_LEN) {
        SECUREC_ERROR_INVALID_RANGE("strncpy_s");
        return ERANGE;
    } else if (strDest == NULL || strSrc == NULL) {
        SECUREC_ERROR_INVALID_PARAMTER("strncpy_s");
        if (strDest != NULL) {
            strDest[0] = '\0';
            return EINVAL_AND_RESET;
        }
        return EINVAL;
    } else if (count > SECUREC_STRING_MAX_LEN) {
        strDest[0] = '\0';      /* clear dest string */
        SECUREC_ERROR_INVALID_RANGE("strncpy_s");
        return ERANGE_AND_RESET;
    } else if (count == 0) {
        strDest[0] = '\0';
        return EOK;
    }

    return CheckSrcCountRange(strDest, destMax, strSrc, count);
}

/*
 * <FUNCTION DESCRIPTION>
 *   The strncpy_s function copies not more than n successive characters (not including the terminating null character)
 *                     from the array pointed to by strSrc to the array pointed to by strDest.
 *
 * <INPUT PARAMETERS>
 *    strDest                          Destination string.
 *    destMax                          The size of the destination string, in characters.
 *    strSrc                            Source string.
 *    count                              Number of characters to be copied.
 *
 * <OUTPUT PARAMETERS>
 *    strDest                           is updated
 *
 * <RETURN VALUE>
 *    EOK                               Success
 *    EINVAL                          strDest is  NULL and destMax != 0 and destMax <= SECUREC_STRING_MAX_LEN
 *    EINVAL_AND_RESET       strDest !=  NULL and strSrc is NULL and destMax != 0 and destMax <= SECUREC_STRING_MAX_LEN
 *    ERANGE                         destMax is 0 and destMax > SECUREC_STRING_MAX_LEN
 *    ERANGE_AND_RESET      strDest have not enough space  and all other parameters are valid  and not overlap
 *    EOVERLAP_AND_RESET   dest buffer and source buffer are overlapped and all  parameters are valid
 *
 *    If there is a runtime-constraint violation, strDest[0] will be set to the '\0' when strDest and destMax valid
 */
errno_t strncpy_s(char *strDest, size_t destMax, const char *strSrc, size_t count)
{
    if (SECUREC_STRNCPY_PARAM_OK(strDest, destMax, strSrc, count)) {
        size_t minCpLen;        /* use it to store the maxi length limit */
        if (count < destMax) {
            minCpLen = SecStrMinLen(strSrc, count); /* no ending terminator */
        } else {
            size_t tmpCount = destMax;
#ifdef  SECUREC_COMPATIBLE_WIN_FORMAT
            if (count == ((size_t)(-1))) {
                tmpCount = destMax - 1;
            }
#endif
            minCpLen = SecStrMinLen(strSrc, tmpCount);
            if (minCpLen == destMax) {
                strDest[0] = '\0';
                SECUREC_ERROR_INVALID_RANGE("strncpy_s");
                return ERANGE_AND_RESET;
            }
        }
        if (SECUREC_STRING_NO_OVERLAP(strDest, strSrc, minCpLen) || strDest == strSrc) {
            /* Not overlap */
            SecDoMemcpy(strDest, strSrc, minCpLen);    /* copy string without terminator */
            strDest[minCpLen] = '\0';
            return EOK;
        } else {
            strDest[0] = '\0';
            SECUREC_ERROR_BUFFER_OVERLAP("strncpy_s");
            return EOVERLAP_AND_RESET;
        }
    }
    return strncpy_error(strDest, destMax, strSrc, count);
}

#if SECUREC_IN_KERNEL
EXPORT_SYMBOL(strncpy_s);
#endif

