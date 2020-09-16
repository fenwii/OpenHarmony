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

#ifndef HCS_COMPILER_PARSER_H
#define HCS_COMPILER_PARSER_H

#include <stdio.h>
#include "hcs_types.h"

#define OBJECT_NAME_MAX_LEN 100

enum ParserObjectType {
    PARSEROP_UINT8 = 0x01,
    PARSEROP_UINT16,
    PARSEROP_UINT32,
    PARSEROP_UINT64,
    PARSEROP_STRING,
    PARSEROP_CONFNODE,
    PARSEROP_CONFTERM,
    PARSEROP_ARRAY,
    PARSEROP_NODEREF,
    PARSEROP_DELETE,
    PARSEROP_COUNT,
};

enum NodeRefType {
    CONFIG_NODE_NOREF = 0,
    CONFIG_NODE_COPY,
    CONFIG_NODE_REF,
    CONFIG_NODE_DELETE,
    CONFIG_NODE_TEMPLATE,
    CONFIG_NODE_INHERIT,
    CONFIG_NODE_TYPE_COUNT
};
enum ParserObjectStatus {
    PARSER_OBJ_IDLE = 0,
    PARSER_OBJ_PROCESSING,
};
struct ParserObjectBase;
typedef struct ParserObjectBase ParserObjectBase;

#define PARSER_OBJECT_COMMON   \
    uint32_t type;             \
    uint32_t status;           \
    const char *name;          \
    ParserObjectBase *parent;  \
    ParserObjectBase *next;    \
    ParserObjectBase *child;   \
    uint32_t lineno;           \
    const char *src;           \
    uint8_t opCode;            \
    uint32_t size;             \
    uint32_t subSize;          \
    uint32_t hash;             \
    union {                    \
        uint64_t value;        \
        uint64_t integerValue; \
        char *stringValue;     \
    };

struct ParserObjectBase {
    PARSER_OBJECT_COMMON;
};

typedef struct TemplateNodeInstance {
    struct ConfigNode *nodeObject;
    struct TemplateNodeInstance *next;
} TemplateNodeInstance;

typedef struct ConfigNode {
    PARSER_OBJECT_COMMON;
    const char *refNodePath;
    uint32_t nodeType;
    struct ConfigNode *inheritNode;
    uint32_t inheritIndex;
    uint32_t inheritCount;
    uint32_t templateSignNum;
    TemplateNodeInstance *subClasses;
} ConfigNode;

typedef struct {
    PARSER_OBJECT_COMMON;
    uint32_t flag; // for array or other assembly type
    uint32_t signNum;
} ConfigTerm;

typedef union {
    ParserObjectBase objectBase;
    ConfigNode configNode;
    ConfigTerm configTerm;
} ParserObject;

enum AstWalkDirection {
    AST_WALK_FORWARD = 0x01,
    AST_WALK_BACKEND,
    AST_WALK_ROUND,
};

enum AstCopyOverWriteFlag {
    AST_COPY_SRC_OVER_DST = 0,  // source term overwrite destination terms
    AST_COPY_DST_OVER_SRC,      // destination term overwrite source terms
};

/* lexer and parser auto-gen api start */
void HcsParserRestart(FILE *inputFile);

int32_t HcsCompilerparse(void);

/* lexer and parser auto-gen api end */
bool HcsIsAnonymousObject(const ParserObject *obj);

int32_t HcsProcessInclude(char *includePath, uint32_t lineNumber);

bool HcsIsSameTypeObject(const ParserObject *cs, const ParserObject *ct);

bool HcsIsNumberObject(const ParserObject *obj);

bool HcsIsStringObject(const ParserObject *obj);

const char *HcsParserNodeTypeToStr(uint32_t nodeType);

void HcsAstFreeObject(ParserObject *object);

int32_t HcsGetCurrentSourceLine(void);

void HcsSetCurrentSourceLine(int32_t lineNumber);

uint32_t HcsAlign(uint32_t size);

#endif // HCS_COMPILER_PARSER_H
