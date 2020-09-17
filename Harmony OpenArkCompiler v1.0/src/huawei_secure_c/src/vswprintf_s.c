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

#include "secureprintoutput.h"


/*
 * <FUNCTION DESCRIPTION>
 *    The  vswprintf_s  function  is  the  wide-character  equivalent  of the vsprintf_s function
 *
 * <INPUT PARAMETERS>
 *    strDest                  Storage location for the output.
 *    destMax                Size of strDest
 *    format                  Format specification.
 *    argList                   pointer to list of arguments
 *
 * <OUTPUT PARAMETERS>
 *    strDest                 is updated
 *
 * <RETURN VALUE>
 *    return  the number of wide characters stored in strDest, not  counting the terminating null wide character.
 *    return -1  if an error occurred.
 *
 * If there is a runtime-constraint violation, strDest[0] will be set to the '\0' when strDest and destMax valid
 */
int vswprintf_s(wchar_t *strDest, size_t destMax, const wchar_t *format, va_list argList)
{
    int retVal;               /* If initialization causes  e838 */

    if (format == NULL || strDest == NULL || destMax == 0 || destMax > (SECUREC_WCHAR_STRING_MAX_LEN)) {
        if (strDest != NULL && destMax > 0) {
            strDest[0] = '\0';
        }
        SECUREC_ERROR_INVALID_PARAMTER("vswprintf_s");
        return -1;
    }

    retVal = SecVswprintfImpl(strDest, destMax, format, argList);

    if (retVal < 0) {
        strDest[0] = '\0';
        if (retVal == SECUREC_PRINTF_TRUNCATE) {
            /* Buffer too small */
            SECUREC_ERROR_INVALID_RANGE("vswprintf_s");
        }
        SECUREC_ERROR_INVALID_PARAMTER("vswprintf_s");
        return -1;
    }

    return retVal;
}


