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

#ifndef HCS_COMPILER_AST_H
#define HCS_COMPILER_AST_H

#include "hcs_parser.h"

typedef int32_t (*AstWalkCallBack)(ParserObject *current, int32_t walkDepth);

ParserObject *HcsGetParserRoot(void);

void HcsSetParserRoot(ParserObject *newRoot);

ParserObject *HcsNewConfigNode(const char *nodeName, uint32_t nodeType, const char *refName);

ParserObject *HcsNewConfigTerm(const char *name, ParserObject *value);

ParserObject *HcsNewParserObject(const char *name, uint32_t type, uint64_t value);

ParserObject *HcsAstAddChild(ParserObject *parent, ParserObject *child);

void HcsAstRemoveChildLink(ParserObjectBase *parent, ParserObjectBase *child);

ParserObject *HcsAstAddPeer(ParserObject *forward, ParserObject *peer);

int32_t HcsWalkAst(ParserObject *start, uint32_t walkDirection, AstWalkCallBack forwardCallback,
    AstWalkCallBack backwardCallback);

void HcsDumpAst(const char *label);

ParserObject *HcsAstLookupObjectInPeers(const ParserObject *current, const char *name);

ParserObject *HcsAstLookupObjectInChildren(const ParserObject *current, const char *name);

int32_t HcsAstCopySubTree(ParserObject *src, ParserObject *dst, uint32_t overWriteFlag);

int32_t HcsAstCopyArray(const ParserObject *src, ParserObject *dst);

void HcsDeleteParserObjectTree(ParserObject *object);

uint16_t HcsCountArraySize(const ParserObject *arrayObj);

uint16_t HcsGetTermType(ParserObject *object);

const char *HcsGetModuleName(void);

#endif // HCS_COMPILER_AST_H
