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
#include "hcs_compiler.h"
#include "hcs_gener.h"
#include "hcs_ast.h"
#include "hcs_option.h"

const char *g_nodeTypeStringMap[CONFIG_NODE_TYPE_COUNT] = {
    [CONFIG_NODE_NOREF] = "NodeReference",
    [CONFIG_NODE_COPY] = "NodeCopy",
    [CONFIG_NODE_REF] = "NodeReference",
    [CONFIG_NODE_DELETE] = "NodeDelete",
    [CONFIG_NODE_INHERIT] = "NodeInherit",
    [CONFIG_NODE_TEMPLATE] = "NodeTemplate",
};

uint32_t HcsAlign(uint32_t size)
{
    if (HcsOptShouldAlign()) {
        return  (size + ALIGN_SIZE - 1) & (~(ALIGN_SIZE - 1));
    } else {
        return size;
    }
}

const char *HcsParserNodeTypeToStr(uint32_t nodeType)
{
    if (nodeType >= CONFIG_NODE_TYPE_COUNT) {
        return "";
    }

    return g_nodeTypeStringMap[nodeType];
}

bool HcsIsNumberObject(const ParserObject *obj)
{
    return obj->objectBase.type >= PARSEROP_UINT8 && obj->objectBase.type <= PARSEROP_UINT64;
}

bool HcsIsStringObject(const ParserObject *obj)
{
    return obj->objectBase.type == PARSEROP_STRING;
}

bool HcsIsSameTypeObject(const ParserObject *cs, const ParserObject *ct)
{
    if (HcsIsNumberObject(cs)) {
        return HcsIsNumberObject(ct);
    } else if (cs->objectBase.type == PARSEROP_CONFTERM || cs->objectBase.type == PARSEROP_ARRAY) {
        return ct->objectBase.type == cs->objectBase.type && cs->objectBase.child->type == ct->objectBase.child->type;
    } else {
        return ct->objectBase.type == cs->objectBase.type;
    }
}

void HcsSetCompilerIn(FILE *in);

static void InitParser(const struct HcsFile *sourceFile)
{
    HcsSetCompilerIn(sourceFile->file);
    HcsParserRestart(sourceFile->file);
    HcsSetCurrentSourceLine(1);
}

void ParserCleanUp()
{
    ParserObject *astRoot = HcsGetParserRoot();
    HcsDeleteParserObjectTree(astRoot);
    HcsSourceNameSetClean();
}

int32_t HcsProcessInclude(char *includePath, uint32_t lineNumber)
{
    if (includePath[0] == '/' || !strstr(includePath, HCS_SOURCE_FILE_SUFFIX)) {
        HCS_ERROR("File:%s Line:%u\n\tinclude file %s is invalid", HcsGetCurrentSourceName(), lineNumber, includePath);
        return EFAIL;
    }

    struct HcsFile *currentSource = HcsSourceQueueTop();
    /* assembly include path to current source file */
    uint32_t pathSize = strlen(currentSource->fullPath) + strlen(includePath) + 1;
    char *path = HcsMemZalloc(pathSize);
    if (path == NULL) {
        HCS_ERROR("oom");
        return EOOM;
    }

    if (HcsFileCopyDir(path, pathSize, currentSource->fullPath) != true) {
        HcsMemFree(path);
        return EFAIL;
    }

    int32_t res = strcat_s(path, pathSize, includePath);
    if (res != EOK) {
        HcsMemFree(path);
        HCS_ERROR("%s:string cat fail", __func__);
        return EFAIL;
    }
    HcsMemFree(includePath);

    struct HcsFile *source = NULL;
    uint32_t ret = HcsOpenSourceFile(path, &source, NULL);
    if (ret == EREOPENF) {
        HcsMemFree(path);
        return NOERR;
    }

    if (ret) {
        HCS_ERROR("File:%s Line:%u\n\tinclude file %s is invalid", HcsGetCurrentSourceName(), lineNumber, path);
        HcsMemFree(path);
        return EINVALF;
    }

    HcsSourceQueuePush(source);
    HcsMemFree(path);
    return NOERR;
}

int32_t HcsDoCompile()
{
    struct HcsFile *source = NULL;
    char *forestName = strdup("ForestRoot");
    if (forestName == NULL) {
        return EOOM;
    }
    ParserObject *astForest = HcsNewParserObject(forestName, PARSEROP_CONFNODE, 0);
    if (astForest == NULL) {
        HcsMemFree(forestName);
        return EFAIL;
    }

    uint32_t ret = HcsOpenSourceFile(HcsGetInputFileName(), &source, NULL);
    if (ret) {
        HCS_ERROR("Invalid source file: %s", HcsGetInputFileName());
        HcsAstFreeObject(astForest);
        return ret;
    }
    HcsSourceQueuePush(source);

    /* parse specified source file and included files */
    while (HcsSourceQueueSize()) {
        source = HcsSourceQueueTop();
        HCS_DEBUG("parsing file : %s%s", source->fullPath, source->name);
        InitParser(source);

        /* do parse */
        ret = HcsCompilerparse();
        ParserObject *currentRoot = HcsGetParserRoot();
        /* pop current file, parse next file which maybe imported by include */
        HcsSourceQueuePop();
        HcsCloseFile(source);
        if (ret) {
            goto OUT;
        }

        HcsAstAddChild(astForest, currentRoot);
        HcsSetParserRoot(NULL);
    }
    HcsSetParserRoot(astForest);

    if (HcsVerbosePrint()) {
        HcsDumpAst("Origin");
    }

    /* middle process */
    ret = HcsDoOptimize();
    if (ret) {
        goto OUT;
    }

    /* output */
    if (HcsOptShouldGenTextConfig()) {
        ret = HcsTextCodeOutput();
    } else if (HcsOptShouldGenByteCodeConfig()) {
        ret = HcsBytecodeOutput();
    }
OUT:
    ParserCleanUp();
    if (HcsGetParserRoot() != astForest) {
        HcsDeleteParserObjectTree(astForest);
    }
    return ret;
}
