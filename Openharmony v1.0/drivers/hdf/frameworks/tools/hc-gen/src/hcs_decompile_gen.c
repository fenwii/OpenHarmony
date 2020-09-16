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

#include <string.h>
#include <securec.h>
#include "hcs_file.h"
#include "hcs_ast.h"
#include "hcs_mem.h"
#include "hcs_log.h"

#define WRITE_BUFFER_LEN 256
#define HCS_TAB_SIZE 4

#define HCS_DECOMPILE_FILE_HEADER           \
    "/*\n"                                  \
    " * HDF decompile hcs file\n"           \
    " */\n\n"

static char *HcsAssembleNodeRefName(char *buff, uint32_t buffSize, const char *name)
{
    int32_t res = strcat_s(buff, buffSize, name);
    if (res) {
        HCS_ERROR("%s:%d: string cat fail", __func__, __LINE__);
        return NULL;
    }
    char *str = strdup(buff);
    if (str == NULL) {
        HCS_ERROR("%s %d %s OOM", __FILE__, __LINE__, __func__);
        return NULL;
    }
    return str;
}

static char *HcsGetNodeRefPath(uint64_t hash)
{
    char pathBuffer[WRITE_BUFFER_LEN] = {'\0'};
    char *path = pathBuffer;
    ParserObjectBase *it = (ParserObjectBase *)HcsGetParserRoot();
    if (it == NULL) {
        return NULL;
    }

    while (it->child) {
        int32_t res = strcat_s(path, WRITE_BUFFER_LEN, it->name);
        if (res) {
            HCS_ERROR("%s:%d: strcat fail", __func__, __LINE__);
            return NULL;
        }
        res = strcat_s(path, WRITE_BUFFER_LEN, ".");
        if (res) {
            HCS_ERROR("%s:%d: strcat fail", __func__, __LINE__);
            return NULL;
        }
        ParserObjectBase *child = it->child;
        bool deepIn = false;
        while (child != NULL) {
            if (child->type != PARSEROP_CONFNODE) {
                child = child->next;
                continue;
            }
            if (child->hash == hash) {
                return HcsAssembleNodeRefName(pathBuffer, WRITE_BUFFER_LEN, child->name);
            }

            if (hash > child->hash && hash < (child->hash + child->size)) {
                it = child;
                deepIn = true;
                break;
            }
            child = child->next;
        }
        if (!deepIn) {
            HCS_ERROR("ref unknown node, hash = %"PRIu64, hash);
            return NULL;
        }
    }

    return NULL;
}

static int32_t HcsDecompilePrintBaseType(char *buffer, uint32_t bufferSize, const ParserObject *object);

static int32_t HcsDecompilePrintArrayType(char *buffer, uint32_t bufferSize, const ParserObject *object)
{
    int32_t res = sprintf_s(buffer, bufferSize, "[");
    PRINTF_CHECK_AND_RETURN(res);
    ParserObject *arrayElement = (ParserObject *)object->objectBase.child;
    while (arrayElement->objectBase.next) {
        res = HcsDecompilePrintBaseType(buffer + strlen(buffer), bufferSize - strlen(buffer), arrayElement);
        if (res) {
            return EOUTPUT;
        }
        res = sprintf_s(buffer + strlen(buffer), bufferSize - strlen(buffer), ", ");
        PRINTF_CHECK_AND_RETURN(res);
        arrayElement = (ParserObject *)arrayElement->objectBase.next;
    }
    res = HcsDecompilePrintBaseType(buffer + strlen(buffer), bufferSize - strlen(buffer), arrayElement);
    if (res) {
        return EOUTPUT;
    }
    res = sprintf_s(buffer + strlen(buffer), bufferSize - strlen(buffer), "]");
    PRINTF_CHECK_AND_RETURN(res);

    return NOERR;
}

static int32_t HcsDecompilePrintBaseType(char *buffer, uint32_t bufferSize, const ParserObject *object)
{
    int32_t res;
    switch (object->objectBase.type) {
        case PARSEROP_UINT8:
        case PARSEROP_UINT16:
        case PARSEROP_UINT32:
        case PARSEROP_UINT64:
            res = sprintf_s(buffer, bufferSize, "0x%"PRIx64, object->objectBase.integerValue);
            PRINTF_CHECK_AND_RETURN(res);
            break;
        case PARSEROP_STRING:
            res = sprintf_s(buffer, bufferSize, "\"%s\"", object->objectBase.stringValue);
            PRINTF_CHECK_AND_RETURN(res);
            break;
        case PARSEROP_NODEREF: {
            char *refPath = HcsGetNodeRefPath(object->objectBase.value);
            if (refPath == NULL) {
                return EOUTPUT;
            }
            res = sprintf_s(buffer, bufferSize, "&%s", refPath);
            HcsMemFree(refPath);
            PRINTF_CHECK_AND_RETURN(res);
        }
            break;
        case PARSEROP_ARRAY:
            return HcsDecompilePrintArrayType(buffer, bufferSize, object);
        default:
            HCS_ERROR("unknown OpCode %u", object->objectBase.type);
            return EFAIL;
    }

    return NOERR;
}

static int32_t HcsDecompileOutputWalk(ParserObject *current, int32_t walkDepth)
{
    if (current->objectBase.type != PARSEROP_CONFNODE && current->objectBase.type != PARSEROP_CONFTERM) {
        return NOERR;
    }

    int32_t res;
    char writeBuffer[WRITE_BUFFER_LEN] = {'\0'};
    int32_t tabSize = walkDepth * HCS_TAB_SIZE;
    if (walkDepth) {
        res = sprintf_s(writeBuffer, WRITE_BUFFER_LEN, "%*c", tabSize, ' ');
        PRINTF_CHECK_AND_RETURN(res);
    }

    switch (current->objectBase.type) {
        case PARSEROP_CONFNODE:
            res = sprintf_s(writeBuffer + strlen(writeBuffer), WRITE_BUFFER_LEN - strlen(writeBuffer),
                "%s {\n", current->configNode.name);
            PRINTF_CHECK_AND_RETURN(res);
            if (current->objectBase.child == NULL) {
                res = sprintf_s(writeBuffer + strlen(writeBuffer) - 1,
                    WRITE_BUFFER_LEN - strlen(writeBuffer) + 1, "}\n");
                PRINTF_CHECK_AND_RETURN(res);
            }
            break;
        case PARSEROP_CONFTERM:
            res = sprintf_s(writeBuffer + strlen(writeBuffer), WRITE_BUFFER_LEN - strlen(writeBuffer),
                "%s = ", current->configNode.name);
            PRINTF_CHECK_AND_RETURN(res);
            res = HcsDecompilePrintBaseType(writeBuffer + strlen(writeBuffer), WRITE_BUFFER_LEN - strlen(writeBuffer),
                (ParserObject *)current->configNode.child);
            if (res) {
                return res;
            }
            res = sprintf_s(writeBuffer + strlen(writeBuffer), WRITE_BUFFER_LEN - strlen(writeBuffer), ";\n");
            PRINTF_CHECK_AND_RETURN(res);
            break;
        default:
            break;
    }

    return HcsOutputWrite(writeBuffer, strlen(writeBuffer));
}

static int32_t HcsDecompileCloseBraceGen(ParserObject *current, int32_t walkDepth)
{
    if (current->objectBase.type != PARSEROP_CONFNODE) {
        return NOERR;
    }
    int32_t res;
    int32_t tabSize = walkDepth * HCS_TAB_SIZE;
    char writeBuffer[WRITE_BUFFER_LEN] = {'\0'};

    if (current != HcsGetParserRoot()) {
        res = sprintf_s(writeBuffer, WRITE_BUFFER_LEN, "%*c}\n", tabSize, ' ');
        PRINTF_CHECK_AND_RETURN(res);
    } else {
        res = sprintf_s(writeBuffer, WRITE_BUFFER_LEN, "}\n");
        PRINTF_CHECK_AND_RETURN(res);
    }

    return HcsOutputWrite(writeBuffer, strlen(writeBuffer));
}

int32_t HcsDecompileOutput()
{
    ParserObject *astRoot = HcsGetParserRoot();
    if (astRoot == NULL) {
        return EOUTPUT;
    }

    int32_t ret = EOUTPUT;
    struct HcsFile *outputFIle = HcsOpenOutputFile(HCS_DECOMPILE_OUTPUT_FILE_SUFFIX);
    if (outputFIle == NULL) {
        goto OUT;
    }

    const char *fileHeader = HCS_DECOMPILE_FILE_HEADER;
    if (HcsOutputWrite(fileHeader, strlen(fileHeader))) {
        goto OUT;
    }

    ret = HcsWalkAst(astRoot, AST_WALK_ROUND, HcsDecompileOutputWalk, HcsDecompileCloseBraceGen);

OUT:
    HcsCloseOutput(outputFIle);
    return ret;
}