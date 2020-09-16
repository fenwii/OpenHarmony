/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "shcmd.h"
#include "sherr.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/*
 * Filter out double quote or single-quoted strings at both ends
 */
char *OsCmdParseStrdup(const char *str)
{
    char *tempStr = NULL;
    char *newStr = NULL;

    newStr = (char *)malloc(strlen(str) + 1);
    if (newStr == NULL) {
        return NULL;
    }

    tempStr = newStr;
    for (; *str != '\0'; str++) {
        if ((*str == '\"') || (*str == '\'')) {
            continue;
        }
        *newStr = *str;
        newStr++;
    }
    *newStr = '\0';
    return tempStr;
}

unsigned int OsCmdParseParaGet(char **value, const char *paraTokenStr)
{
    if ((paraTokenStr == NULL) || (value == NULL)) {
        return (unsigned int)SH_ERROR;
    }
    *value = OsCmdParseStrdup(paraTokenStr);
    if (*value == NULL) {
        return SH_NOK;
    }
    return SH_OK;
}

unsigned int OsCmdParseOneToken(CmdParsed *cmdParsed, unsigned int index, const char *token)
{
    unsigned int ret = SH_OK;
    unsigned int tempLen;

    if (cmdParsed == NULL) {
        return (unsigned int)SH_ERROR;
    }

    if (index == 0) {
        if (cmdParsed->cmdType != CMD_TYPE_STD) {
            return ret;
        }
    }

    if ((token != NULL) && (cmdParsed->paramCnt < CMD_MAX_PARAS)) {
        tempLen = cmdParsed->paramCnt;
        ret = OsCmdParseParaGet(&(cmdParsed->paramArray[tempLen]), token);
        if (ret != SH_OK) {
            return ret;
        }
        cmdParsed->paramCnt++;
    }
    return ret;
}

unsigned int OsCmdTokenSplit(char *cmdStr, char split, CmdParsed *cmdParsed)
{
    enum {
        STAT_INIT,
        STAT_TOKEN_IN,
        STAT_TOKEN_OUT
    } state = STAT_INIT;
    unsigned int count = 0;
    char *p = NULL;
    char *token = cmdStr;
    unsigned int ret = SH_OK;
    bool quotes = FALSE;

    if (cmdStr == NULL) {
        return (unsigned int)SH_ERROR;
    }

    for (p = cmdStr; (*p != '\0') && (ret == SH_OK); p++) {
        if (*p == '\"') {
            SWITCH_QUOTES_STATUS(quotes);
        }
        switch (state) {
            case STAT_INIT:
            case STAT_TOKEN_IN:
                if ((*p == split) && QUOTES_STATUS_CLOSE(quotes)) {
                    *p = '\0';
                    ret = OsCmdParseOneToken(cmdParsed, count++, token);
                    state = STAT_TOKEN_OUT;
                }
                break;
            case STAT_TOKEN_OUT:
                if (*p != split) {
                    token = p;
                    state = STAT_TOKEN_IN;
                }
                break;
            default:
                break;
        }
    }

    if (((ret == SH_OK) && (state == STAT_TOKEN_IN)) || (state == STAT_INIT)) {
        ret = OsCmdParseOneToken(cmdParsed, count, token);
    }

    return ret;
}

unsigned int OsCmdParse(char *cmdStr, CmdParsed *cmdParsed)
{
    if ((cmdStr == NULL) || (cmdParsed == NULL) || (strlen(cmdStr) == 0)) {
        return (unsigned int)SH_ERROR;
    }
    return OsCmdTokenSplit(cmdStr, ' ', cmdParsed);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
