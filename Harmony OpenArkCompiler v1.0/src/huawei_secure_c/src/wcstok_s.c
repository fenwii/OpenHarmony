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
 * FindBegin Wide character postion  function
 */
static wchar_t *SecFindBeginW(wchar_t *strToken, const wchar_t *strDelimit)
{
    /* Find beginning of token (skip over leading delimiters). Note that
     * there is no token if this loop sets string to point to the terminal null.
     */
    wchar_t *token = strToken;
    while (*token != L'\0') {
        const wchar_t *ctl = strDelimit;
        while (*ctl != L'\0' && *ctl != *token) {
            ++ctl;
        }
        if (*ctl == L'\0') {
            break;
        }
        ++token;
    }
    return token;
}

/*
 * FindBegin rest Wide character postion  function
 */
static wchar_t *SecFindRestW(wchar_t *strToken, const wchar_t *strDelimit)
{
    /* Find the end of the token. If it is not the end of the string,
     * put a null there.
     */
    wchar_t *token = strToken;
    while (*token != L'\0') {
        const wchar_t *ctl = strDelimit;
        while (*ctl != L'\0' && *ctl != *token) {
            ++ctl;
        }
        if (*ctl != L'\0') {
            *token++ = L'\0';
            break;
        }
        ++token;
    }
    return token;
}

/*
 * Update Token wide character  function
 */
static wchar_t *SecUpdateTokenW(wchar_t *strToken, const wchar_t *strDelimit, wchar_t **context)
{
    /* point to updated position */
    wchar_t *token = SecFindRestW(strToken, strDelimit);
    /* Update the context */
    *context = token;
    /* Determine if a token has been found. */
    if (token == strToken) {
        return NULL;
    }
    return strToken;
}

/*
 * <NAME>
 *    wcstok_s
 *
 *
 * <FUNCTION DESCRIPTION>
 *   The  wcstok_s  function  is  the  wide-character  equivalent  of the strtok_s function
 *
 * <INPUT PARAMETERS>
 *    strToken               String containing token or tokens.
 *    strDelimit             Set of delimiter characters.
 *    context                Used to store position information between calls to
 *                               wcstok_s.
 *
 * <OUTPUT PARAMETERS>
 *    context               is updated
 * <RETURN VALUE>
 *   The  wcstok_s  function  is  the  wide-character  equivalent  of the strtok_s function
 */
wchar_t *wcstok_s(wchar_t *strToken, const wchar_t *strDelimit, wchar_t **context)
{
    wchar_t *orgToken = strToken;
    /* validation section */
    if (context == NULL || strDelimit == NULL) {
        return NULL;
    }
    if (orgToken == NULL && (*context) == NULL) {
        return NULL;
    }
    /* If string==NULL, continue with previous string */
    if (orgToken == NULL) {
        orgToken = *context;
    }
    orgToken = SecFindBeginW(orgToken, strDelimit);
    return SecUpdateTokenW(orgToken, strDelimit, context);
}

