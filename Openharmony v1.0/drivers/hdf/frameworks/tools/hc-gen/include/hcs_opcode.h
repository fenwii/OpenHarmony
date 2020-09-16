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

#ifndef HCS_COMPILER_OPCODE_H
#define HCS_COMPILER_OPCODE_H

#include "hcs_parser.h"

#define HCS_NODE_OP         0x01
#define HCS_TERM_OP         0x02
#define HCS_NODEREF_OP      0x03
#define HCS_ARRAY_OP        0x04
#define HCS_BYTE_OP         0x10
#define HCS_WORD_OP         0x11
#define HCS_DWORD_OP        0x12
#define HCS_QWORD_OP        0x13
#define HCS_STRING_OP       0x14

typedef struct {
    uint8_t opCode;
    uint32_t size;
    const char *opStr;
} OpCodeMapEntry;

const OpCodeMapEntry *HcsGetOpCodeMap();

const OpCodeMapEntry *HcsParserObjectTypeToByteCode(uint32_t objectType);

void HcsCalculateOpcodeSize(ParserObject *object);

const char *HcsOpcodeToStr(uint16_t opCode);

#endif // HCS_COMPILER_OPCODE_H
