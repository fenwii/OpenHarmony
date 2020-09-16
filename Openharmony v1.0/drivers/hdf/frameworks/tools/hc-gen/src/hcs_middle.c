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
#include "hcs_compiler.h"
#include "hcs_option.h"

static int32_t HcsNodeExpand(ParserObject *current);

static ParserObject *HcsLookupAstObject(const ParserObject *current, const char *path)
{
    /* Not absolute path, lookup in peers */
    if (!strchr(path, '.')) {
        return HcsAstLookupObjectInPeers(current, path);
    }

    /* Absolute path lookup form root and subtree */
    char *splitPath = strdup(path);
    if (splitPath == NULL) {
        HCS_ERROR("oom");
        return NULL;
    }
    char *nodeName = strtok(splitPath, ".");

    /* path must start with "root" */
    if (nodeName == NULL || strcmp(nodeName, "root") != 0) {
        HcsMemFree(splitPath);
        return NULL;
    }

    /* skip root in path */
    nodeName = strtok(NULL, ".");
    ParserObject *object = HcsGetParserRoot();
    while (nodeName != NULL) {
        object = HcsAstLookupObjectInChildren(object, nodeName);
        if (object == NULL)
            break;
        nodeName = strtok(NULL, ".");
    }
    HcsMemFree(splitPath);

    if (object != NULL) {
        return object;
    }

    return NULL;
}

static int32_t HcsExpandNodeRef(ParserObject *object)
{
    ParserObject *refNode = HcsLookupAstObject(object, object->configNode.refNodePath);
    if (refNode == NULL) {
        HCS_OBJECT_ERROR(object, "ref node '%s' not exist", object->configNode.refNodePath);
        return EINVALARG;
    }
    if (refNode->objectBase.status != PARSER_OBJ_IDLE) {
        HCS_OBJECT_ERROR(object, "circular reference '%s'", object->configNode.refNodePath);
        return EINVALARG;
    }

    /* expand target ref or copy */
    int32_t res = HcsNodeExpand(refNode);
    if (res) {
        return res;
    }
    ParserObject *child = (ParserObject *)object->objectBase.child;
    if (child == NULL) {
        return 0;
    }

    res = HcsAstCopySubTree(object, refNode, AST_COPY_SRC_OVER_DST);
    if (res) {
        return res;
    }
    HcsDeleteParserObjectTree(object);
    return NOERR;
}

static int32_t HcsExpandNodeCopy(ParserObject *object)
{
    object->configNode.nodeType = CONFIG_NODE_NOREF;
    ParserObject *copyNode = HcsLookupAstObject(object, object->configNode.refNodePath);
    if (copyNode == NULL) {
        HCS_OBJECT_ERROR(object, "node %s copy node '%s' not exist", object->objectBase.name,
            object->configNode.refNodePath);
        return EINVALARG;
    }

    /* check copy parent */
    ParserObjectBase *parent = object->objectBase.parent;
    while (parent != NULL) {
        if (parent == &copyNode->objectBase) {
            HCS_OBJECT_ERROR(object, "Never copy parent node which will make a loop reference");
            return EINVALARG;
        }
        parent = parent->parent;
    }

    if (HcsOptShouldGenTextConfig()) {
        ParserObjectBase *copyChild = copyNode->objectBase.child;
        while (copyChild != NULL) {
            if (copyChild->type == PARSEROP_CONFNODE) {
                HCS_OBJECT_ERROR(object, "Not allow copy node has child node when output text config, at %s:%d",
                    copyChild->src, copyChild->lineno);
                return EINVALARG;
            }
            copyChild = copyChild->next;
        }
    }

    return HcsAstCopySubTree(copyNode, object, AST_COPY_DST_OVER_SRC);
}

static bool HcsProcessDelete(ParserObject *current)
{
    switch (current->objectBase.type) {
        case PARSEROP_CONFNODE:
            if (current->configNode.nodeType == CONFIG_NODE_DELETE) {
                HcsDeleteParserObjectTree(current);
                return true;
            }
            break;
        case PARSEROP_CONFTERM:
            if (current->objectBase.child->type == PARSEROP_DELETE) {
                HcsDeleteParserObjectTree(current);
                return true;
            }
            break;
        default:
            break;
    }

    return false;
}

static int32_t HcsNodeRefAssembling(ParserObject *current)
{
    ParserObject *refNode =
        HcsLookupAstObject((ParserObject *)current->objectBase.parent, current->objectBase.stringValue);
    if (refNode == NULL) {
        HCS_OBJECT_ERROR(current, "reference invalid node %s", current->objectBase.stringValue);
        return EINVALARG;
    }
    if (refNode->objectBase.type != PARSEROP_CONFNODE) {
        HCS_OBJECT_ERROR(current, "reference node %s is not node", current->objectBase.stringValue);
        return EINVALARG;
    }
    if (refNode->configNode.nodeType == CONFIG_NODE_REF) {
        HCS_OBJECT_ERROR(current, "reference node %s referenced another", current->objectBase.stringValue);
        return EINVALARG;
    }
    HcsMemFree(current->objectBase.stringValue);
    current->objectBase.value = (uint64_t)refNode;
    return NOERR;
}

static int32_t HcsInheritNodeCompareWithBase(const ParserObject *obj, const ParserObject *base)
{
    ParserObjectBase *objChild = obj->objectBase.child;

    while (objChild != NULL) {
        ParserObject *objInBase = NULL;
        if (objChild->type == PARSEROP_CONFNODE &&
            ((ParserObject *)objChild)->configNode.nodeType == CONFIG_NODE_INHERIT) {
            ParserObject *templateNode =
                HcsLookupAstObject((ParserObject *)objChild, ((ParserObject *)objChild)->configNode.refNodePath);
            if (templateNode == NULL) {
                HCS_OBJECT_ERROR(objChild, "node '%s' inherit invalid template", objChild->name);
                return EFAIL;
            }
            ParserObject *peerTemplate = HcsLookupAstObject((ParserObject *)objChild, templateNode->objectBase.name);
            if (templateNode != peerTemplate) {
                HCS_OBJECT_ERROR(objChild, "term '%s' not in base node", objChild->name);
                return EFAIL;
            }
            objChild = objChild->next;
            continue;
        } else {
            objInBase = HcsAstLookupObjectInChildren(base, objChild->name);
        }

        if (objInBase == NULL) {
            HCS_OBJECT_ERROR(objChild, "term '%s' not in base node", objChild->name);
            return EFAIL;
        }
        if (objChild->type == PARSEROP_CONFNODE) {
            return HcsInheritNodeCompareWithBase((ParserObject *)objChild, objInBase);
        }

        objChild = objChild->next;
    }
    return NOERR;
}

static int32_t HcsAddInstanceToTemplate(ParserObject *instanceNode, ParserObject *template)
{
    TemplateNodeInstance *instance = HcsMemZalloc(sizeof(TemplateNodeInstance));
    if (instance == NULL) {
        return EOOM;
    }

    instance->nodeObject = (struct ConfigNode *)instanceNode;

    TemplateNodeInstance *listEnd = template->configNode.subClasses;
    if (listEnd == NULL) {
        template->configNode.subClasses = instance;
    } else {
        while (listEnd->next != NULL) {
            listEnd = listEnd->next;
        }

        listEnd->next = instance;
    }
    instanceNode->configNode.inheritIndex = template->configNode.inheritCount++;
    return NOERR;
}

static int32_t HcsNodeInheritExpand(ParserObject *obj)
{
    ParserObject *base = HcsLookupAstObject(obj, obj->configNode.refNodePath);
    if (base == NULL || base->objectBase.type != PARSEROP_CONFNODE ||
        base->configNode.nodeType != CONFIG_NODE_TEMPLATE) {
        HCS_OBJECT_ERROR(obj, "inherit invalid node : %s", obj->configNode.refNodePath);
        return EFAIL;
    }

    obj->configNode.inheritNode = (struct ConfigNode *)base;
    int32_t ret = HcsAstCopySubTree(base, obj, AST_COPY_DST_OVER_SRC);
    if (ret) {
        return ret;
    }

    ret = HcsInheritNodeCompareWithBase(obj, base);
    if (ret) {
        return ret;
    }

    return HcsAddInstanceToTemplate(obj, base);
}

static int32_t HcsNodeExpand(ParserObject *current)
{
    if (HcsProcessDelete(current)) {
        return NOERR;
    }

    switch (current->objectBase.type) {
        case PARSEROP_CONFNODE: {
            current->objectBase.status = PARSER_OBJ_PROCESSING;
            int32_t ret = NOERR;
            if (current->configNode.nodeType == CONFIG_NODE_REF) {
                return HcsExpandNodeRef(current);
            } else if (current->configNode.nodeType == CONFIG_NODE_COPY) {
                ret = HcsExpandNodeCopy(current);
            }
            current->objectBase.status = PARSER_OBJ_IDLE;
            return ret;
        }
        case PARSEROP_NODEREF:
            return HcsNodeRefAssembling(current);
        default:
            break;
    }

    return NOERR;
}

static int32_t HcsRedefineCheck(const ParserObject *object)
{
    if (object->objectBase.child == NULL) {
        return NOERR;
    }

    ParserObject *child = (ParserObject *)object->objectBase.child;
    while (child != NULL) {
        if (HcsIsAnonymousObject(object)) {
            child = (ParserObject *)child->objectBase.next;
            continue;
        }
        ParserObject *next = (ParserObject *)child->objectBase.next;
        while (next != NULL) {
            if (!HcsIsAnonymousObject(next) && !strcmp(child->objectBase.name, next->objectBase.name) &&
                (child->objectBase.src == next->objectBase.src)) {
                HCS_OBJECT_ERROR(next, "'%s' redefined, first define at Line: %u", next->objectBase.name,
                    child->objectBase.lineno);
                return EINVALARG;
            }
            next = (ParserObject *)next->objectBase.next;
        }
        child = (ParserObject *)child->objectBase.next;
    }

    return NOERR;
}

static int32_t HcsMiddleRedefineCheckCallback(ParserObject *current, int32_t walkDepth)
{
    (void)walkDepth;
    return HcsRedefineCheck(current);
}

static int32_t HcsMiddleInheritExpandCallback(ParserObject *current, int32_t walkDepth)
{
    (void)walkDepth;
    if (current->objectBase.type == PARSEROP_CONFNODE && current->configNode.nodeType == CONFIG_NODE_INHERIT) {
        return HcsNodeInheritExpand(current);
    }

    return NOERR;
}

static int32_t HcsMiddleProcessCallback(ParserObject *current, int32_t walkDepth)
{
    (void)walkDepth;
    return HcsNodeExpand(current);
}

static bool HcsApplyDelete(ParserObject *dst, ParserObject *src)
{
    if ((dst->objectBase.type == PARSEROP_CONFNODE && dst->configNode.nodeType == CONFIG_NODE_DELETE) ||
        (dst->objectBase.type == PARSEROP_CONFTERM && dst->objectBase.child->type == PARSEROP_DELETE)) {
        HCS_OBJECT_WARNING(dst, "target object of delete not in base");
    }

    if ((src->objectBase.type == PARSEROP_CONFNODE && src->configNode.nodeType == CONFIG_NODE_DELETE) ||
        (src->objectBase.type == PARSEROP_CONFTERM && src->objectBase.child->type == PARSEROP_DELETE)) {
        HcsDeleteParserObjectTree(dst);
        HcsDeleteParserObjectTree(src);
        return true;
    }

    return false;
}

static int32_t HcsMergeTree(ParserObject *dst, ParserObject *src)
{
    if (strcmp(src->objectBase.name, dst->objectBase.name) != 0) {
        HCS_OBJECT_ERROR(src, "merge different node to %s:%d", dst->objectBase.src, dst->objectBase.lineno);
        return EINVALARG;
    }

    if (src->objectBase.type != dst->objectBase.type) {
        HCS_OBJECT_ERROR(src, "conflict type with %s:%d", dst->objectBase.src, dst->objectBase.lineno);
        return EINVALARG;
    }

    if (HcsApplyDelete(dst, src)) {
        return NOERR;
    }

    /* overwrite source info */
    dst->objectBase.src = src->objectBase.src;
    dst->objectBase.lineno = src->objectBase.lineno;

    /* overwrite value of base type  */
    if (HcsIsStringObject(src)) {
        HcsMemFree((void *)dst->objectBase.value);
        dst->objectBase.value = src->objectBase.value;
        src->objectBase.value = (uint64_t)NULL;
    } else if (HcsIsNumberObject(src)) {
        dst->objectBase.value = src->objectBase.value;
    }

    /* process sub-tree objects */
    ParserObject *childSrc = (ParserObject *)src->objectBase.child;
    int32_t ret = NOERR;
    while (childSrc != NULL) {
        ParserObject *childSrcNext = (ParserObject *)childSrc->objectBase.next;
        ParserObject *childDst = HcsAstLookupObjectInChildren(dst, childSrc->objectBase.name);
        if (childDst != NULL && childSrc->objectBase.type != childDst->objectBase.type) {
            HCS_OBJECT_ERROR(childSrc, "overwrite with different type at %s:%d", childDst->objectBase.src,
                childDst->objectBase.lineno);
            return EINVALARG;
        }
        if (childDst == NULL) {
            HcsAstRemoveChildLink(childSrc->objectBase.parent, (ParserObjectBase *)childSrc);
            HcsAstAddChild(dst, childSrc);
        } else if (childDst->objectBase.type == PARSEROP_ARRAY) {
            ret = HcsAstCopyArray(childSrc, childDst);
            break;
        } else {
            ret = HcsMergeTree(childDst, childSrc);
            if (ret) {
                break;
            }
        }
        childSrc = childSrcNext;
    }

    return ret;
}

static void HcsOrderForest(ParserObject *root)
{
    if (root->objectBase.child == NULL) {
        return;
    }

    ParserObjectBase *childStart = root->objectBase.child;
    ParserObjectBase *pre = childStart;
    ParserObjectBase *next = childStart->next;
    while (next != NULL) {
        ParserObjectBase *tmp = next->next;
        next->next = pre;
        pre = next;
        next = tmp;
    }

    childStart->next = NULL;
    root->objectBase.child = pre;
}

static int32_t HcsMiddleMerge(ParserObject **mergedRoot)
{
    ParserObject *root = HcsGetParserRoot();
    HcsOrderForest(root);

    ParserObject *peer = (ParserObject *)root->objectBase.child;
    while (peer->objectBase.next != NULL) {
        ParserObject *next = (ParserObject *)peer->objectBase.next;
        int32_t res = HcsMergeTree(peer, next);
        if (res) {
            return res;
        }
        HcsDeleteParserObjectTree(next);
    }
    HcsAstRemoveChildLink(peer->objectBase.parent, &peer->objectBase);
    HcsSetParserRoot(peer);
    *mergedRoot = peer;
    return NOERR;
}

int32_t HcsDoOptimize()
{
    ParserObject *root = HcsGetParserRoot();
    if (root == NULL) {
        HCS_ERROR("parser return empty ast");
        return EINVALARG;
    }

    /* redefine check */
    int32_t ret = HcsWalkAst(root, AST_WALK_BACKEND, NULL, HcsMiddleRedefineCheckCallback);
    if (ret) {
        return ret;
    }

    /* merge multi file objects */
    ret = HcsMiddleMerge(&root);
    if (ret) {
        return ret;
    }

    const char *moduleName = HcsGetModuleName();
    if (moduleName == NULL) {
        return EINVALARG;
    }
    HCS_INFO("compile module : %s", moduleName);
    /* expend node ref and node copy */
    ret = HcsWalkAst(root, AST_WALK_BACKEND, NULL, HcsMiddleProcessCallback);
    if (ret) {
        return ret;
    }

    ret = HcsWalkAst(root, AST_WALK_FORWARD, HcsMiddleInheritExpandCallback, NULL);
    if (ret) {
        return ret;
    }

    if (HcsVerbosePrint()) {
        HcsDumpAst("Optimized");
    }
    return ret;
}