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
#include "hcs_mem.h"
#include "hcs_log.h"
#include "hcs_option.h"
#include "hcs_ast.h"

#define ANONYMOUS_OBJECT_NAME "|_"
static ParserObject *g_parserRoot = NULL;

bool HcsIsAnonymousObject(const ParserObject *obj)
{
    return strcmp(obj->objectBase.name, ANONYMOUS_OBJECT_NAME) == 0;
}

ParserObject *HcsAllocParserObject(void)
{
    ParserObject *new = (ParserObject *)HcsMemZalloc(sizeof(ParserObject));
    if (new == NULL) {
        HCS_ERROR("%s %d %s OOM", __FILE__, __LINE__, __func__);
        return NULL;
    }
    new->objectBase.src = HcsGetCurrentSourceName();
    new->objectBase.lineno = HcsGetCurrentSourceLine();
    return new;
}

void HcsAstFreeObject(ParserObject *object)
{
    if (object == NULL) {
        return;
    }
    if (object->objectBase.type == PARSEROP_CONFNODE) {
        TemplateNodeInstance *subClass = object->configNode.subClasses;
        while (subClass != NULL) {
            TemplateNodeInstance *temp = subClass;
            subClass = subClass->next;
            HcsMemFree(temp);
        }
        HcsMemFree((char *)object->configNode.refNodePath);
    }

    HcsAstRemoveChildLink(object->objectBase.parent, (ParserObjectBase *)object);
    if (object->objectBase.type == PARSEROP_STRING) {
        HcsMemFree(object->objectBase.stringValue);
    }

    HcsMemFree((char*)object->objectBase.name);
    HcsMemFree(object);
}

static int32_t HcsAstWalkFreeObjectCallback(ParserObject *object, int32_t walkDepth)
{
    (void)walkDepth;
    HcsAstFreeObject(object);
    return NOERR;
}

static void HcsAstFreeObjectAndSubtree(ParserObject *object)
{
    if (HcsWalkAst(object, AST_WALK_BACKEND, NULL, HcsAstWalkFreeObjectCallback)) {
        HCS_WARNING("%s may failed", __func__);
    }
}

void HcsDeleteParserObjectTree(ParserObject *object)
{
    if (object == NULL) {
        return;
    }
    /* delete current and subtree */
    HcsAstFreeObjectAndSubtree(object);
}

ParserObject *HcsGetParserRoot(void)
{
    if (g_parserRoot != NULL) {
        return g_parserRoot;
    }
    HCS_DEBUG("instance root node");
    char *rootNodeName = strdup("root");
    if (rootNodeName == NULL) {
        HCS_ERROR("%s %d %s OOM", __FILE__, __LINE__, __func__);
        return NULL;
    }
    g_parserRoot = HcsNewConfigNode(rootNodeName, CONFIG_NODE_NOREF, NULL);
    if (g_parserRoot == NULL) {
        HcsMemFree(rootNodeName);
    }
    return g_parserRoot;
}

void HcsSetParserRoot(ParserObject *newRoot)
{
    g_parserRoot = newRoot;
}

ParserObject *HcsNewConfigNode(const char *nodeName, uint32_t nodeType, const char *refName)
{
    HCS_DEBUG("create node: %s", nodeName ? nodeName : "nil");
    ParserObject *object = HcsAllocParserObject();
    if (object == NULL) {
        return NULL;
    }
    object->configNode.name = nodeName;
    object->objectBase.type = PARSEROP_CONFNODE;
    if (nodeType) {
        object->configNode.nodeType = nodeType;
        object->configNode.refNodePath = refName;
    }

    return object;
}

uint32_t HcsFitIntegerValueType(uint64_t value)
{
    if (value <= UINT8_MAX) {
        return PARSEROP_UINT8;
    } else if (value <= UINT16_MAX) {
        return PARSEROP_UINT16;
    } else if (value <= UINT32_MAX) {
        return PARSEROP_UINT32;
    } else {
        return PARSEROP_UINT64;
    }
}

ParserObject *HcsNewConfigTerm(const char *name, ParserObject *value)
{
    if (name == NULL || value == NULL) {
        return NULL;
    }
    ParserObject *object = HcsAllocParserObject();
    if (object == NULL) {
        return NULL;
    }
    object->objectBase.name = name;
    object->objectBase.type = PARSEROP_CONFTERM;
    object->objectBase.child = (ParserObjectBase *)value;
    ParserObjectBase *child = &value->objectBase;
    while (child != NULL) {
        child->parent = (ParserObjectBase *)object;
        child = child->next;
    }

    return object;
}

ParserObject *HcsNewParserObject(const char *name, uint32_t type, uint64_t value)
{
    if (type >= PARSEROP_COUNT) {
        HCS_ERROR("unknown object type");
        return NULL;
    }

    ParserObject *object = HcsAllocParserObject();
    if (object == NULL) {
        return NULL;
    }

    if (name == NULL) {
        name = strdup(ANONYMOUS_OBJECT_NAME);
        if (name == NULL) {
            HcsMemFree(object);
            return NULL;
        }
    }

    object->objectBase.name = name;
    object->objectBase.type = type;
    object->objectBase.value = value;

    switch (type) {
        case PARSEROP_UINT8:  /* fall-through */
        case PARSEROP_UINT16: /* fall-through */
        case PARSEROP_UINT32: /* fall-through */
        case PARSEROP_UINT64:
            object->objectBase.type = HcsFitIntegerValueType(value);
            break;
        default:
            break;
    }

    return object;
}

ParserObject *HcsAstAddChild(ParserObject *parent, ParserObject *child)
{
    if (child == NULL) {
        return parent;
    }

    if (parent->objectBase.child == NULL) {
        parent->objectBase.child = (ParserObjectBase *)child;
        ParserObjectBase *childNext = &child->objectBase;
        while (childNext != NULL) {
            childNext->parent = (ParserObjectBase *)parent;
            childNext = childNext->next;
        }
    } else {
        HcsAstAddPeer((ParserObject *)parent->configNode.child, child);
    }

    return parent;
}

void HcsAstRemoveChildLink(ParserObjectBase *parent, ParserObjectBase *child)
{
    if (parent == NULL || child == NULL || child->parent != parent) {
        return;
    }
    child->parent = NULL;
    if (parent->child == child) {
        parent->child = child->next;
        child->next = NULL;
        return;
    }

    ParserObjectBase *pre = parent->child;
    while (pre != NULL) {
        if (pre->next == child) {
            pre->next = pre->next->next;
        }

        pre = pre->next;
    }
    child->next = NULL;
}

ParserObject *HcsAstAddPeer(ParserObject *forward, ParserObject *peer)
{
    if (forward == NULL && peer == NULL) {
        return forward;
    }

    if (forward == NULL) {
        return peer;
    }

    if (peer == NULL) {
        return forward;
    }

    if (forward == peer) {
        HCS_ERROR("add self as peer");
        return NULL;
    }

    ParserObjectBase *lastNode = &forward->objectBase;
    while (lastNode->next) {
        lastNode = lastNode->next;
    }

    lastNode->next = (ParserObjectBase *)peer;
    peer->objectBase.parent = forward->objectBase.parent;

    ParserObjectBase *peerNext = peer->objectBase.next;
    while (peerNext != NULL) {
        peerNext->parent = forward->objectBase.parent;
        peerNext = peerNext->next;
    }

    return forward;
}

ParserObject *HcsAstLookupObjectInPeers(const ParserObject *current, const char *name)
{
    ParserObject *peer = (ParserObject *)current->objectBase.parent->child;
    while (peer != NULL) {
        if (peer->objectBase.type == PARSEROP_CONFNODE && !strcmp(peer->objectBase.name, name)) {
            return peer;
        }

        peer = (ParserObject *)peer->objectBase.next;
    }

    return NULL;
}

ParserObject *HcsAstLookupObjectInChildren(const ParserObject *current, const char *name)
{
    if (current == NULL) {
        return NULL;
    }
    ParserObject *peer = (ParserObject *)current->objectBase.child;
    while (peer != NULL) {
        if (!strcmp(peer->objectBase.name, name)) {
            return peer;
        }

        peer = (ParserObject *)peer->objectBase.next;
    }

    return NULL;
}

static ParserObject *HcsParserObjectClone(const ParserObject *object)
{
    if (object == NULL) {
        return NULL;
    }
    ParserObject *clone = HcsAllocParserObject();
    if (clone == NULL) {
        HCS_ERROR("%s %d %s OOM", __FILE__, __LINE__, __func__);
        return NULL;
    }

    (void)memcpy_s(clone, sizeof(*clone), object, sizeof(*object));
    clone->configNode.refNodePath = NULL;
    clone->objectBase.name = NULL;
    clone->objectBase.child = NULL;
    clone->objectBase.next = NULL;
    clone->objectBase.parent = NULL;
    if (object->objectBase.type == PARSEROP_STRING) {
        clone->objectBase.stringValue = strdup(object->objectBase.stringValue);
        if (clone->objectBase.stringValue == NULL) {
            HcsAstFreeObject(clone);
            return NULL;
        }
    }
    if (object->configNode.refNodePath != NULL) {
        clone->configNode.refNodePath = strdup(object->configNode.refNodePath);
        if (clone->configNode.refNodePath == NULL) {
            HcsAstFreeObject(clone);
            return NULL;
        }
    }
    clone->objectBase.name = strdup(object->objectBase.name);
    if (clone->objectBase.name == NULL) {
        HcsAstFreeObject(clone);
        return NULL;
    }

    return clone;
}

void HcsAstFreeSubTree(ParserObject *object)
{
    ParserObjectBase *child = object->objectBase.child;
    while (child != NULL) {
        ParserObjectBase *tmp = child->next;
        HcsAstRemoveChildLink((ParserObjectBase *)object, child);
        HcsAstFreeObjectAndSubtree((ParserObject *)child);
        child = tmp;
    }
}

bool HcsIsEmptyArray(const ParserObject *src)
{
    return src->objectBase.child == NULL;
}

int32_t HcsAstCopyArray(const ParserObject *src, ParserObject *dst)
{
    if (src == NULL || dst == NULL) {
        return NOERR;
    }

    if (HcsIsEmptyArray(src)) {
        return NOERR;
    }

    if (!HcsIsEmptyArray(dst) &&
        !HcsIsSameTypeObject((ParserObject *)src->objectBase.child, (ParserObject *)dst->objectBase.child)) {
        HCS_OBJECT_ERROR(dst, "overwrite different type");
        return EINVALARG;
    }

    /* Children of array is anonymous object, can not use name to index them, delete first */
    HcsAstFreeSubTree(dst);
    dst->objectBase.child = NULL;

    ParserObject *arrayElement = (ParserObject *)src->objectBase.child;
    while (arrayElement != NULL) {
        ParserObject *copy = HcsParserObjectClone(arrayElement);
        if (copy == NULL) {
            HCS_ERROR("%s %d %s OOM", __FILE__, __LINE__, __func__);
            return EOOM;
        }
        HcsAstAddChild(dst, copy);
        arrayElement = (ParserObject *)arrayElement->objectBase.next;
    }

    return NOERR;
}

static int32_t HcsCopyObject(const ParserObject *src, ParserObject *dst)
{
    if (!HcsIsSameTypeObject(src, dst)) {
        HCS_OBJECT_ERROR(src, "overwrite different type");
        return EINVALARG;
    }

    if (HcsIsNumberObject(src)) {
        dst->objectBase.integerValue = src->objectBase.integerValue;
    } else if (HcsIsStringObject(src)) {
        HcsMemFree(dst->objectBase.stringValue);
        dst->objectBase.stringValue = strdup(src->objectBase.stringValue);
        if (dst->objectBase.stringValue == NULL) {
            HCS_ERROR("%s %d %s OOM", __FILE__, __LINE__, __func__);
            return EOOM;
        }
    } else if (src->objectBase.type == PARSEROP_ARRAY) {
        return HcsAstCopyArray(src, dst);
    }

    return NOERR;
}

/*
 * Copy src tree as dstTree's child
 */
static int32_t HcsAstCopyTree(ParserObject *src, ParserObject *dstTree, uint32_t overWriteFlag)
{
    if (src == NULL || dstTree == NULL) {
        return NOERR;
    }

    int32_t ret;
    ParserObject *dstExistObject = HcsAstLookupObjectInChildren(dstTree, src->objectBase.name);
    if (dstExistObject == NULL) {
        ParserObject *copy = HcsParserObjectClone(src);
        HcsAstAddChild(dstTree, copy);
        dstExistObject = copy;
        if (src->objectBase.type == PARSEROP_ARRAY) {
            return HcsAstCopyArray(src, dstExistObject);
        }
    } else if (overWriteFlag == AST_COPY_SRC_OVER_DST) {
        ret = HcsCopyObject(src, dstExistObject);
        if (ret || src->objectBase.type == PARSEROP_ARRAY) {
            return ret;
        }
    } else if (HcsOptShouldGenTextConfig() && HcsIsNumberObject(src) &&
        dstExistObject->objectBase.type > src->objectBase.type) {
        /* At template case, should do type upward transformation to template */
        src->objectBase.type = dstExistObject->objectBase.type;
    }

    ParserObjectBase *srcChild = src->objectBase.child;
    while (srcChild != NULL) {
        ret = HcsAstCopyTree((ParserObject *)srcChild, dstExistObject, overWriteFlag);
        if (ret) {
            return ret;
        }
        srcChild = srcChild->next;
    }

    return NOERR;
}

int32_t HcsAstCopySubTree(ParserObject *src, ParserObject *dst, uint32_t overWriteFlag)
{
    if (src == NULL || dst == NULL) {
        return NOERR;
    }

    if (!HcsIsSameTypeObject(src, dst)) {
        HCS_OBJECT_ERROR(src, "overwrite different type");
        return EINVALARG;
    }

    ParserObjectBase *srcChild = src->objectBase.child;
    while (srcChild != NULL) {
        int32_t ret = HcsAstCopyTree((ParserObject *)srcChild, dst, overWriteFlag);
        if (ret) {
            return ret;
        }
        srcChild = srcChild->next;
    }

    return NOERR;
}

static int32_t inline AstWalkCallBackDefault(ParserObject *current, int32_t walkDepth)
{
    (void)current;
    (void)walkDepth;
    return NOERR;
}

static int32_t HcsForwardWalkAst(ParserObject *start, AstWalkCallBack callback)
{
    ParserObjectBase *startObj = (ParserObjectBase *)start;
    ParserObjectBase *forwardWalkObj = startObj;
    int32_t walkDepth = 0;
    bool preVisited = false;

    while (forwardWalkObj != NULL) {
        if (!preVisited) {
            int32_t ret = callback((ParserObject *)forwardWalkObj, walkDepth);
            if (ret && ret != EASTWALKBREAK) {
                return EINVALARG;
            } else if (!ret && forwardWalkObj->child) {
                /* when callback return EASTWALKBREAK, not walk current's child */
                walkDepth++;
                forwardWalkObj = forwardWalkObj->child;
                continue;
            }
        }
        if (forwardWalkObj == startObj) {
            break;
        }

        if (forwardWalkObj->next) {
            forwardWalkObj = forwardWalkObj->next;
            preVisited = false;
        } else {
            forwardWalkObj = forwardWalkObj->parent;
            preVisited = true;
            walkDepth--;
        }
    }

    return NOERR;
}

static int32_t HcsBackwardWalkAst(ParserObject *start, AstWalkCallBack callback)
{
    ParserObjectBase *startObj = (ParserObjectBase *)start;
    ParserObjectBase *backWalkObj = startObj;
    ParserObjectBase *next = NULL;
    ParserObjectBase *parent = NULL;
    int32_t walkDepth = 0;
    bool preVisited = false;

    while (backWalkObj != NULL) {
        if (backWalkObj->child == NULL || preVisited) {
            next = backWalkObj->next;
            parent = backWalkObj->parent;
            /* can safe delete current in callback */
            if (callback((ParserObject *)backWalkObj, walkDepth)) {
                return EINVALARG;
            }
        } else {
            if (backWalkObj->child) {
                walkDepth++;
                backWalkObj = backWalkObj->child;
                continue;
            }
        }
        if (backWalkObj == startObj) {
            break;
        }

        if (next != NULL) {
            backWalkObj = next;
            preVisited = false;
        } else {
            backWalkObj = parent;
            preVisited = true;
            walkDepth--;
        }
    }

    return NOERR;
}

static int32_t HcsRoundWalkAst(ParserObject *start, AstWalkCallBack forwardCallback, AstWalkCallBack backwardCallback)
{
    ParserObjectBase *startObj = (ParserObjectBase *)start;
    ParserObjectBase *roundWalkObj = startObj;
    int32_t walkDepth = 0;
    bool preVisited = false;

    while (roundWalkObj != NULL) {
        if (preVisited) {
            if (backwardCallback((ParserObject *)roundWalkObj, walkDepth)) {
                return EFAIL;
            }
        } else {
            int32_t ret = forwardCallback((ParserObject *)roundWalkObj, walkDepth);
            /* when callback return EASTWALKBREAK, not walk current's child */
            if (ret && ret != EASTWALKBREAK) {
                return EFAIL;
            } else if (!ret && roundWalkObj->child) {
                walkDepth++;
                roundWalkObj = roundWalkObj->child;
                continue;
            }
        }
        if (roundWalkObj == startObj) {
            break;
        }

        if (roundWalkObj->next) {
            roundWalkObj = roundWalkObj->next;
            preVisited = false;
        } else {
            roundWalkObj = roundWalkObj->parent;
            preVisited = true;
            walkDepth--;
        }
    }

    return NOERR;
}

uint16_t HcsGetTermType(ParserObject *object)
{
    if (object->objectBase.type != PARSEROP_CONFTERM || object->objectBase.child == NULL) {
        return 0;
    }
    return object->objectBase.child->type;
}

int32_t HcsWalkAst(ParserObject *start, uint32_t walkDirection, AstWalkCallBack forwardCallback,
    AstWalkCallBack backwardCallback)
{
    forwardCallback = forwardCallback ? forwardCallback : AstWalkCallBackDefault;
    backwardCallback = backwardCallback ? backwardCallback : AstWalkCallBackDefault;
    ParserObject *startObj = start ? start : g_parserRoot;

    int32_t ret;
    switch (walkDirection) {
        case AST_WALK_FORWARD:
            ret = HcsForwardWalkAst(startObj, forwardCallback);
            break;
        case AST_WALK_BACKEND:
            ret = HcsBackwardWalkAst(startObj, backwardCallback);
            break;
        case AST_WALK_ROUND:
            ret = HcsRoundWalkAst(startObj, forwardCallback, backwardCallback);
            break;
        default:
            HCS_ERROR("unknown ast walk type(%u)", walkDirection);
            return EINVALARG;
    }

    return ret;
}

static const char *g_parserOpTypeStr[PARSEROP_COUNT] = {
    [PARSEROP_UINT8] = "UINT8",
    [PARSEROP_UINT16] = "UINT16",
    [PARSEROP_UINT32] = "UINT32",
    [PARSEROP_UINT64] = "UINT64",
    [PARSEROP_STRING] = "STRING",
    [PARSEROP_CONFNODE] = "CONFNODE",
    [PARSEROP_CONFTERM] = "CONFTERM",
    [PARSEROP_ARRAY] = "ARRAY",
    [PARSEROP_NODEREF] = "NODEREF",
};

static const char *ParserOpTypeToStr(uint32_t type)
{
    if (type >= PARSEROP_COUNT) {
        return "unknown_type";
    }

    return g_parserOpTypeStr[type];
}

#define AST_PRINT_TAB_SIZE 2

static int32_t AstDumpWalkCallback(ParserObject *current, int32_t walkDepth)
{
    int32_t printTab = walkDepth * AST_PRINT_TAB_SIZE;

    HCS_PRINT("%-15s%*c%-10s", ParserOpTypeToStr(current->objectBase.type), printTab, ' ', current->configNode.name);
    switch (current->objectBase.type) {
        case PARSEROP_UINT8:
        case PARSEROP_UINT16:
        case PARSEROP_UINT32:
        case PARSEROP_UINT64:
            HCS_PRINT(" %"PRIx64, current->configTerm.integerValue);
            break;
        case PARSEROP_STRING:
            HCS_PRINT(" %s", current->configTerm.stringValue);
            break;
        case PARSEROP_CONFNODE: {
            if (current->configNode.nodeType != CONFIG_NODE_NOREF) {
                HCS_PRINT("%-10s %-10s", HcsParserNodeTypeToStr(current->configNode.nodeType),
                    current->configNode.refNodePath ? current->configNode.refNodePath : "");
            }
        } break;
        case PARSEROP_NODEREF:
            HCS_PRINT("%-10s %"PRIx64, "NodeReference", current->objectBase.value);
            break;
        default:
            break;
    }

    HCS_PRINT("\n");

    return NOERR;
}

uint16_t HcsCountArraySize(const ParserObject *arrayObj)
{
    if (arrayObj == NULL) {
        return 0;
    }

    ParserObjectBase *child = arrayObj->objectBase.child;
    uint16_t size = 0;
    while (child != NULL) {
        size++;
        child = child->next;
    }

    return size;
}

const char *HcsGetModuleName(void)
{
    ParserObject *root = HcsGetParserRoot();
    if (root == NULL) {
        return NULL;
    }

    ParserObject *moduleAttr = HcsAstLookupObjectInChildren(root, "module");
    if (moduleAttr == NULL) {
        HCS_OBJECT_ERROR(root, "miss 'module' attribute under root node");
        return NULL;
    }

    return moduleAttr->configTerm.child->stringValue;
}

void HcsDumpAst(const char *label)
{
    HCS_PRINT("\nDump %s AST tree:\n", label);
    if (HcsWalkAst(g_parserRoot, AST_WALK_FORWARD, AstDumpWalkCallback, NULL)) {
        HCS_WARNING("%s failed", __func__);
    }
}