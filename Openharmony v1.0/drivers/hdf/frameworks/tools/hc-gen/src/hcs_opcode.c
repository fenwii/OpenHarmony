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
#include "hcs_opcode.h"


OpCodeMapEntry g_byteCodeMap[PARSEROP_COUNT] = {
    [PARSEROP_UINT8]    = {HCS_BYTE_OP,     BYTE_SIZE, "Uint8"},
    [PARSEROP_UINT16]   = {HCS_WORD_OP,     WORD_SIZE, "Uint16"},
    [PARSEROP_UINT32]   = {HCS_DWORD_OP,    DWORD_SIZE, "Uint32"},
    [PARSEROP_UINT64]   = {HCS_QWORD_OP,    QWORD_SIZE, "Uint64"},
    [PARSEROP_STRING]   = {HCS_STRING_OP,   0, "String"},
    [PARSEROP_ARRAY]    = {HCS_ARRAY_OP,    WORD_SIZE, "Array"}, /* ElementCount - WORD */
    [PARSEROP_CONFNODE] = {HCS_NODE_OP,     DWORD_SIZE, "ConfigNode"}, /* SubSize - DWORD */
    [PARSEROP_CONFTERM] = {HCS_TERM_OP,     0, "ConfigTerm"},
    [PARSEROP_NODEREF]  = {HCS_NODEREF_OP,  DWORD_SIZE, "NodeRef"}, /* RefHashCode - DWORD */
};

const OpCodeMapEntry *HcsGetOpCodeMap()
{
    return g_byteCodeMap;
}

const OpCodeMapEntry *HcsParserObjectTypeToByteCode(uint32_t objectType)
{
    if (objectType >= PARSEROP_COUNT) {
        return NULL;
    }
    return &g_byteCodeMap[objectType];
}

const char *HcsOpcodeToStr(uint16_t objectType)
{
    if (objectType >= PARSEROP_COUNT) {
        return "illegal OpCode, out of range";
    }

    return g_byteCodeMap[objectType].opStr;
}

void HcsCalculateOpcodeSize(ParserObject *object)
{
    const OpCodeMapEntry *byteCodeMap = HcsGetOpCodeMap();
    uint32_t size = HcsAlign(OPCODE_BYTE_WIDTH) + HcsAlign(byteCodeMap[object->objectBase.type].size);
    switch (object->objectBase.opCode) {
        case HCS_NODE_OP: /* fall-through */
        case HCS_TERM_OP:
            /* name string */
            size += HcsAlign(strlen(object->objectBase.name) + 1); // add 1 for '\0'
            break;
        case HCS_STRING_OP:
            size += HcsAlign(strlen(object->objectBase.stringValue) + 1);
            break;
        default:
            break;
    }

    ParserObjectBase *child = object->objectBase.child;
    uint32_t subSize = 0;
    while (child != NULL) {
        subSize += child->size;
        child = child->next;
    }

    object->objectBase.size += subSize + size;
    object->objectBase.subSize = subSize;
}