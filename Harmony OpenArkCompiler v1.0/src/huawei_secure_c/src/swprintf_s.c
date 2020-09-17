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

#include "securec.h"

/*
 * <FUNCTION DESCRIPTION>
 *   The  swprintf_s  function  is  the  wide-character  equivalent  of the sprintf_s function
 *
 * <INPUT PARAMETERS>
 *    strDest                   Storage location for the output.
 *    destMax                  Maximum number of characters to store.
 *    format                    Format-control string.
 *    ...                        Optional arguments
 *
 * <OUTPUT PARAMETERS>
 *    strDest                    is updated
 *
 * <RETURN VALUE>
 *    return  the number of wide characters stored in strDest, not  counting the terminating null wide character.
 *    return -1  if an error occurred.
 *
 * If there is a runtime-constraint violation, strDest[0] will be set to the '\0' when strDest and destMax valid
 */
int swprintf_s(wchar_t *strDest, size_t destMax, const wchar_t *format, ...)
{
    int ret;                    /* If initialization causes  e838 */
    va_list argList;

    va_start(argList, format);
    ret = vswprintf_s(strDest, destMax, format, argList);
    va_end(argList);
    (void)argList;              /* to clear e438 last value assigned not used , the compiler will optimize this code */

    return ret;
}


