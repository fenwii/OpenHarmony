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

#include  <string.h>
#include "hcs_option.h"
#include "hcs_file.h"
#include "hcs_opcode.h"
#include "hcs_parser.h"
#include "hcs_log.h"
#include "hcs_compiler.h"
#include "hcs_decompiler.h"

static ParserObject *RebuildObject(uint8_t opCode);

static bool HcsVerifyHbcFile()
{
    struct HcsFile *input = HcsSourceQueueTop();
    HbcHeader header = { 0 };
    uint32_t size = HcsSourceFileRead(input, (uint8_t*)&header, sizeof(header));
    if (size != sizeof(header)) {
        HCS_ERROR("Illegal hcb file, invalid file size");
        return false;
    }

    if (header.magicNumber != HBC_MAGIC_NUM) {
        HCS_ERROR("file %s is not a hcb file", HcsGetCurrentSourceName());
        return false;
    }
    if (header.totalSize < 0) {
        HcsOptSetAlign(true);
        header.totalSize = -header.totalSize;
    }
    uint32_t fileSize = HcsSourceFileGetSize(input);
    if (fileSize != (sizeof(header) + header.totalSize)) {
        HCS_ERROR("size mismatch, may broken file");
        return false;
    }

    HCS_INFO("Build by hcs compile %u.%u", header.versionMajor, header.versionMinor);
    HCS_INFO("hcb file total size: %u\n", header.totalSize);
    return true;
}

#define HCS_STRING_READ_BUF_LEN 256

static char *ReadCString()
{
    char buff[HCS_STRING_READ_BUF_LEN] = {'\0'};
    int32_t index = 0;
    while (HcsSourceFileRead(NULL, (uint8_t*)&buff[index], sizeof(char))) {
        if (index == HCS_STRING_READ_BUF_LEN || buff[index] == '\0') {
            break;
        }
        index++;
    }

    if (index >= HCS_STRING_READ_BUF_LEN || buff[index] != '\0') {
        HCS_ERROR("read unterminated or too long c string at %u", HcsGetSourceFilePos(NULL));
        return NULL;
    }
    uint32_t stringFullSize = index + 1;
    uint32_t alignAppendSize = HcsAlign(stringFullSize) - stringFullSize;
    if (alignAppendSize) {
        uint8_t alignReadBuffer[ALIGN_SIZE];
        if (HcsSourceFileRead(NULL, alignReadBuffer, alignAppendSize) != alignAppendSize) {
            HCS_ERROR("read c string length mismatch %u", HcsGetSourceFilePos(NULL));
            return NULL;
        }
    }
    char *str = strdup(buff);
    if (str == NULL) {
        HCS_ERROR("%s %d %s OOM", __FILE__, __LINE__, __func__);
        return NULL;
    }
    return str;
}

static bool ReadUint64(uint64_t *value)
{
    if (HcsSourceFileRead(NULL, (uint8_t*)value, sizeof(*value)) != sizeof(*value)) {
        HCS_ERROR("fail to read uint64");
        return false;
    }
    return true;
}

static bool ReadUint32(uint32_t *value)
{
    if (HcsSourceFileRead(NULL, (uint8_t*)value, sizeof(*value)) != sizeof(*value)) {
        HCS_ERROR("fail to read uint32");
        return false;
    }

    return true;
}

static bool ReadUint16(uint16_t *value)
{
    if (HcsAlign(sizeof(uint16_t)) != sizeof(uint16_t)) {
        uint32_t readValue = 0;
        if (!ReadUint32(&readValue)) {
            return false;
        }
        *value = (uint16_t)readValue;
        return true;
    }
    if (HcsSourceFileRead(NULL, (uint8_t*)value, sizeof(*value)) != sizeof(*value)) {
        HCS_ERROR("fail to read uint16");
        return false;
    }

    return true;
}

static bool ReadUint8(uint8_t *value)
{
    if (HcsAlign(sizeof(uint8_t)) != sizeof(uint8_t)) {
        uint32_t readValue = 0;
        if (!ReadUint32(&readValue)) {
            return false;
        }
        *value = (uint8_t)readValue;
        return true;
    }

    if (HcsSourceFileRead(NULL, value, sizeof(*value)) != sizeof(*value)) {
        HCS_ERROR("fail to read uint8");
        return false;
    }

    return true;
}

static bool NextByteCode(uint32_t *byteCode)
{
    switch (HcsAlign(OPCODE_BYTE_WIDTH)) {
        case BYTE_SIZE: {
            uint8_t value = 0;
            bool ret = ReadUint8(&value);
            *byteCode = value;
            return ret;
        }
        case DWORD_SIZE:
            return ReadUint32(byteCode);
        default:
            break;
    }
    return false;
}

static ParserObject *RebuildNode()
{
    uint32_t nodeHash = HcsGetSourceFilePos(NULL) - HcsAlign(OPCODE_BYTE_WIDTH);
    char *nodeName = ReadCString();
    if (nodeName == NULL) {
        return NULL;
    }

    ParserObject *node = HcsNewConfigNode(nodeName, CONFIG_NODE_NOREF, NULL);
    if (node == NULL) {
        HcsMemFree(nodeName);
        return NULL;
    }
    uint32_t nodeSize = 0;
    if (!ReadUint32(&nodeSize)) {
        goto ERROR;
    }
    node->objectBase.hash = nodeHash;
    node->objectBase.size = nodeSize;
    uint32_t pos = HcsGetSourceFilePos(NULL); // node content start
    uint64_t nodeEnd = nodeSize + pos;
    while (pos < nodeEnd) {
        uint32_t childOpCode;
        if (!NextByteCode(&childOpCode)) {
            HCS_ERROR("broken node");
            goto ERROR;
        }
        ParserObject *child = RebuildObject(childOpCode);
        if (child == NULL) {
            goto ERROR;
        }
        HcsAstAddChild(node, child);
        pos = HcsGetSourceFilePos(NULL);
    }

    return node;
ERROR:
    HcsDeleteParserObjectTree(node);
    return NULL;
}

static ParserObject *RebuildTerm()
{
    char *termName = ReadCString();
    if (termName == NULL) {
        return NULL;
    }
    uint32_t childOpCode;
    if (!NextByteCode(&childOpCode)) {
        HCS_ERROR("broken term");
        HcsMemFree(termName);
        return NULL;
    }

    ParserObject *value = RebuildObject(childOpCode);
    if (value == NULL) {
        HcsMemFree(termName);
        return NULL;
    }
    ParserObject *term = HcsNewConfigTerm(termName, value);
    if (term == NULL) {
        HcsMemFree(termName);
        HcsAstFreeObject(value);
    }
    return term;
}

static ParserObject *RebuildArray()
{
    uint16_t arraySize = 0;
    if (!ReadUint16(&arraySize)) {
        return NULL;
    }
    ParserObject *array = HcsNewParserObject(NULL, PARSEROP_ARRAY, 0);
    if (array == NULL) {
        return NULL;
    }
    for (int32_t i = 0; i < arraySize; ++i) {
        uint32_t elementOpCode;
        if (!NextByteCode(&elementOpCode)) {
            HCS_ERROR("broken term");
            goto ERROR;
        }
        ParserObject *element = RebuildObject(elementOpCode);
        if (element == NULL) {
            goto ERROR;
        }
        HcsAstAddChild(array, element);
    }
    return array;
ERROR:
    HcsDeleteParserObjectTree(array);
    return NULL;
}

static ParserObject *RebuildNumberObject(uint8_t type)
{
    uint8_t u8Value = 0;
    uint16_t u16Value = 0;
    uint32_t u32Value = 0;
    uint64_t u64Value = 0;
    switch (type) {
        case HCS_BYTE_OP:
            if (!ReadUint8(&u8Value)) {
                return NULL;
            }
            return HcsNewParserObject(NULL, PARSEROP_UINT8, u8Value);
        case HCS_WORD_OP:
            if (!ReadUint16(&u16Value)) {
                return NULL;
            }
            return HcsNewParserObject(NULL, PARSEROP_UINT16, u16Value);
        case HCS_DWORD_OP:
            if (!ReadUint32(&u32Value)) {
                return NULL;
            }
            return HcsNewParserObject(NULL, PARSEROP_UINT32, u32Value);
        case HCS_QWORD_OP:
            if (!ReadUint64(&u64Value)) {
                return NULL;
            }
            return HcsNewParserObject(NULL, PARSEROP_UINT64, u64Value);
        default:
            break;
    }

    return NULL;
}

static ParserObject *RebuildStringObject()
{
    char *objectName = ReadCString();
    if (objectName == NULL) {
        return NULL;
    }
    ParserObject *object = HcsNewParserObject(NULL, PARSEROP_STRING, (uint64_t)objectName);
    if (object == NULL) {
        HcsMemFree(objectName);
    }
    return object;
}

static ParserObject *RebuildNodeRefObject()
{
    uint32_t refNodeHash = 0;
    if (!ReadUint32(&refNodeHash)) {
        return NULL;
    }

    return HcsNewParserObject(NULL, PARSEROP_NODEREF, refNodeHash);
}

static ParserObject *RebuildObject(uint8_t opCode)
{
    switch (opCode) {
        case HCS_NODE_OP:
            return RebuildNode();
        case HCS_TERM_OP:
            return RebuildTerm();
        case HCS_NODEREF_OP:
            return RebuildNodeRefObject();
        case HCS_BYTE_OP: /* fall-through */
        case HCS_WORD_OP: /* fall-through */
        case HCS_DWORD_OP: /* fall-through */
        case HCS_QWORD_OP:
            return RebuildNumberObject(opCode);
        case HCS_ARRAY_OP:
            return RebuildArray();
        case HCS_STRING_OP:
            return RebuildStringObject();
        default:
            break;
    }
    HCS_ERROR("unknown OpCode %u", opCode);
    return NULL;
}

static bool RebuildAst()
{
    uint32_t currByteCode = 0;
    bool ret = NextByteCode(&currByteCode);
    if (!ret || currByteCode != HCS_NODE_OP) {
        HCS_ERROR("miss root node");
        return false;
    }

    ParserObject *rootObject = RebuildObject(currByteCode);
    if (rootObject == NULL) {
        return false;
    }

    HcsSetParserRoot(rootObject);
    return true;
}

int32_t HcsDoDecompile()
{
    struct HcsFile *source = NULL;
    uint32_t ret = HcsOpenSourceFile(HcsGetInputFileName(), &source, "rb");
    if (ret) {
        return ret;
    }
    HcsSourceQueuePush(source);

    do {
        if (!HcsVerifyHbcFile()) {
            ret = EDECOMP;
            break;
        }

        if (!RebuildAst()) {
            HCS_ERROR("failed to rebuild ast from hcb file");
            ret = EDECOMP;
            break;
        }
        if (HcsVerbosePrint()) {
            HcsDumpAst("Rebuild");
        }
    } while (0);

    HcsSourceQueuePop();
    HcsCloseFile(source);
    if (ret == NOERR) {
        ret = HcsDecompileOutput();
    }
    HcsDeleteParserObjectTree(HcsGetParserRoot());
    HcsSetParserRoot(NULL);
    HcsSourceNameSetClean();
    return ret;
}