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

/* *
 * @defgroup los_rbtree Rbtree
 * @ingroup kernel
 */

#include "los_rbtree.h"
#include "los_memory.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

STATIC VOID OsRbLeftRotateNode(LosRbTree *pstTree, LosRbNode *pstX);
STATIC VOID OsRbRightRotateNode(LosRbTree *pstTree, LosRbNode *pstY);
STATIC VOID OsRbInsertNodeFixup(LosRbTree *pstTree, VOID *pstData);
STATIC VOID OsRbDeleteNodeFixup(LosRbTree *pstTree, LosRbNode *pstNode);
STATIC VOID OsRbDeleteNode(LosRbTree *pstTree, VOID *pstData);
STATIC VOID OsRbInitTree(LosRbTree *pstTree);
STATIC VOID OsRbClearTree(LosRbTree *pstTree);

STATIC VOID OsRbLeftRotateNode(LosRbTree *pstTree, LosRbNode *pstX)
{
    LosRbNode *pstY = NULL;
    LosRbNode *pstNilT = NULL;
    LosRbNode *pstParent = NULL;

    if (NULL == pstTree || NULL == pstX) {
        return;
    }
    pstNilT = &(pstTree->stNilT);
    /* If pstX or pstY node's either child is NilT node:
     * Left / right rotation might change the NilT's parent.
     * NilT's parent shouldn't be changed.
     * If NilT's parent node changes,
     * then Delete_FixUp function might access NilT's parent's right/left child,
     * which might lead to error.
     * Solution: So we record the NilT's parent and at the end of the rotaion,
     * replace the NilT's parent with the recorded node.
     */
    pstParent = pstNilT->pstParent;
    pstY = pstX->pstRight;
    pstX->pstRight = pstY->pstLeft;
    pstY->pstLeft->pstParent = pstX;
    pstY->pstParent = pstX->pstParent;
    if (pstNilT == pstX->pstParent) {
        pstTree->pstRoot = pstY;
    } else {
        if (pstX == pstX->pstParent->pstLeft) {
            pstX->pstParent->pstLeft = pstY;
        } else {
            pstX->pstParent->pstRight = pstY;
        }
    }
    pstX->pstParent = pstY;
    pstY->pstLeft = pstX;
    pstNilT->pstParent = pstParent;
    return;
}

STATIC VOID OsRbRightRotateNode(LosRbTree *pstTree, LosRbNode *pstY)
{
    LosRbNode *pstX = NULL;
    LosRbNode *pstNilT = NULL;
    LosRbNode *pstParent = NULL;
    if (NULL == pstTree || NULL == pstY) {
        return;
    }

    pstNilT = &(pstTree->stNilT);

    /* If pstX or pstY node's either child is NilT node:
     * Left / right rotation might change the NilT's parent.
     * NilT's parent shouldn't be changed.
     * If NilT's parent node changes,
     * then Delete_FixUp function might access NilT's parent's right/left child,
     * which might lead to error.
     * Solution: So we record the NilT's parent and at the end of the rotaion,
     * replace the NilT's parent with the recorded node.
     */
    pstParent = pstNilT->pstParent;
    pstX = pstY->pstLeft;
    pstY->pstLeft = pstX->pstRight;
    pstX->pstRight->pstParent = pstY;
    pstX->pstParent = pstY->pstParent;
    if (pstNilT == pstY->pstParent) {
        pstTree->pstRoot = pstX;
    } else {
        if (pstY == pstY->pstParent->pstRight) {
            pstY->pstParent->pstRight = pstX;
        } else {
            pstY->pstParent->pstLeft = pstX;
        }
    }
    pstY->pstParent = pstX;
    pstX->pstRight = pstY;
    pstNilT->pstParent = pstParent;
    return;
}

STATIC VOID OsRbInsertNodeFixup(LosRbTree *pstTree, VOID *pstData)
{
    LosRbNode *pstParent = NULL;
    LosRbNode *pstGParent = NULL;
    LosRbNode *pstY = NULL;
    LosRbNode *pstX = NULL;

    /* begin: for earse pc-lint warning */
    if ((NULL == pstTree) || (NULL == pstData)) {
        return;
    }
    /* end */
    pstX = (LosRbNode *)pstData;
    /* NilT is forbidden. */
    (pstTree->ulNodes)++;
    while (LOS_RB_RED == pstX->pstParent->lColor) {
        pstParent = pstX->pstParent;
        pstGParent = pstParent->pstParent;

        if (pstParent == pstGParent->pstLeft) {
            pstY = pstGParent->pstRight;
            if (LOS_RB_RED == pstY->lColor) {
                pstY->lColor = LOS_RB_BLACK;
                pstParent->lColor = LOS_RB_BLACK;
                pstGParent->lColor = LOS_RB_RED;
                pstX = pstGParent;
                continue;
            }

            if (pstParent->pstRight == pstX) {
                pstX = pstParent;
                OsRbLeftRotateNode(pstTree, pstX);
            }

            pstX->pstParent->lColor = LOS_RB_BLACK;
            pstGParent->lColor = LOS_RB_RED;
            OsRbRightRotateNode(pstTree, pstGParent);
        } else {
            pstY = pstGParent->pstLeft;
            if (LOS_RB_RED == pstY->lColor) {
                pstY->lColor = LOS_RB_BLACK;
                pstParent->lColor = LOS_RB_BLACK;
                pstGParent->lColor = LOS_RB_RED;
                pstX = pstGParent;
                continue;
            }

            if (pstParent->pstLeft == pstX) {
                pstX = pstParent;
                OsRbRightRotateNode(pstTree, pstX);
            }

            pstX->pstParent->lColor = LOS_RB_BLACK;
            pstGParent->lColor = LOS_RB_RED;
            OsRbLeftRotateNode(pstTree, pstGParent);
        }
    }

    /* if we arrive here, pstTree is not NULL, sp we can close pc-lint warning */
    /*lint -e613 */
    /*lint -e831 */
    pstTree->pstRoot->lColor = LOS_RB_BLACK;

    /*lint -e613 */
    /*lint -e831 */

    return;
}

STATIC VOID OsRbDeleteNodeFixup(LosRbTree *pstTree, LosRbNode *pstNode)
{
    LosRbNode *pstW = NULL;

    if (NULL == pstTree || NULL == pstNode) {
        return;
    }
    while ((pstNode != pstTree->pstRoot) && (LOS_RB_BLACK == pstNode->lColor)) {
        if (pstNode->pstParent->pstLeft == pstNode) {
            pstW = pstNode->pstParent->pstRight;
            if (LOS_RB_RED == pstW->lColor) {
                pstW->lColor = LOS_RB_BLACK;
                pstNode->pstParent->lColor = LOS_RB_RED;
                OsRbLeftRotateNode(pstTree, pstNode->pstParent);
                pstW = pstNode->pstParent->pstRight;
            }

            if ((LOS_RB_BLACK == pstW->pstLeft->lColor) && (LOS_RB_BLACK == pstW->pstRight->lColor)) {
                pstW->lColor = LOS_RB_RED;
                pstNode = pstNode->pstParent;
            } else {
                if (LOS_RB_BLACK == pstW->pstRight->lColor) {
                    pstW->pstLeft->lColor = LOS_RB_BLACK;
                    pstW->lColor = LOS_RB_RED;
                    OsRbRightRotateNode(pstTree, pstW);
                    pstW = pstNode->pstParent->pstRight;
                }
                pstW->lColor = pstNode->pstParent->lColor;
                pstNode->pstParent->lColor = LOS_RB_BLACK;
                pstW->pstRight->lColor = LOS_RB_BLACK;
                OsRbLeftRotateNode(pstTree, pstNode->pstParent);
                pstNode = pstTree->pstRoot;
            }
        } else {
            pstW = pstNode->pstParent->pstLeft;
            if (LOS_RB_RED == pstW->lColor) {
                pstW->lColor = LOS_RB_BLACK;
                pstNode->pstParent->lColor = LOS_RB_RED;
                OsRbRightRotateNode(pstTree, pstNode->pstParent);
                pstW = pstNode->pstParent->pstLeft;
            }
            if ((LOS_RB_BLACK == pstW->pstLeft->lColor) && (LOS_RB_BLACK == pstW->pstRight->lColor)) {
                pstW->lColor = LOS_RB_RED;
                pstNode = pstNode->pstParent;
            } else {
                if (LOS_RB_BLACK == pstW->pstLeft->lColor) {
                    pstW->pstRight->lColor = LOS_RB_BLACK;
                    pstW->lColor = LOS_RB_RED;
                    OsRbLeftRotateNode(pstTree, pstW);
                    pstW = pstNode->pstParent->pstLeft;
                }
                pstW->lColor = pstNode->pstParent->lColor;
                pstNode->pstParent->lColor = LOS_RB_BLACK;
                pstW->pstLeft->lColor = LOS_RB_BLACK;
                OsRbRightRotateNode(pstTree, pstNode->pstParent);
                pstNode = pstTree->pstRoot;
            }
        }
    }
    pstNode->lColor = LOS_RB_BLACK;
    if (0 == pstTree->ulNodes) {
        OsRbClearTree(pstTree);
    }

    return;
}

STATIC VOID OsRbDeleteNode(LosRbTree *pstTree, VOID *pstData)
{
    LosRbNode *pstChild = NULL;
    LosRbNode *pstDel = NULL;
    ULONG_T lColor;
    LosRbWalk *pstWalk = NULL;
    LosRbNode *pstNilT = NULL;
    LosRbNode *pstZ = NULL;
    LOS_DL_LIST *pstNode = NULL;

    /* begin: for earse pc-lint warning */
    if ((NULL == pstTree) || (NULL == pstData)) {
        return;
    }
    /* End */

    pstZ = (LosRbNode *)pstData;
    pstNilT = &(pstTree->stNilT);

    /* NilT is forbidden. */
    if (!RB_IS_NOT_NILT(pstZ)) {
        return;
    }

    /* check whether the Node is in a tree */
    if ((pstZ->pstParent == pstNilT) && (pstZ->pstLeft == pstNilT) && (pstZ->pstRight == pstNilT) &&
        (pstTree->pstRoot != pstZ)) {
        return;
    }

    if (pstTree == NULL) {
        return;
    }
    (pstTree->ulNodes)--;

    if (!LOS_ListEmpty(&pstTree->stWalkHead)) {
        LOS_DL_LIST_FOR_EACH(pstNode, &pstTree->stWalkHead)
        {
            pstWalk = LOS_DL_LIST_ENTRY(pstNode, LosRbWalk, stLink);
            if (pstWalk->pstCurrNode == pstZ) {
                pstWalk->pstCurrNode = LOS_RbSuccessorNode(pstTree, pstZ);
            }
        }
    }

    if ((pstNilT == pstZ->pstLeft) || (pstNilT == pstZ->pstRight)) {
        pstChild = ((pstNilT != pstZ->pstLeft) ? pstZ->pstLeft : pstZ->pstRight);
        if (NULL == pstChild) { /* Edit by r60958 for coverrity */
            return;
        }

        pstChild->pstParent = pstZ->pstParent;

        if (pstNilT == pstZ->pstParent) {
            /* if we arrive here, pastTree is no NULL, so we can close pclint warning */
            /*lint -e613 */
            /*lint -e831 */
            pstTree->pstRoot = pstChild;
            /*lint +e831 */
            /*lint +e613 */
        } else {
            if (pstZ->pstParent->pstLeft == pstZ) {
                pstZ->pstParent->pstLeft = pstChild;
            } else {
                pstZ->pstParent->pstRight = pstChild;
            }
        }

        if (LOS_RB_BLACK == pstZ->lColor) {
            OsRbDeleteNodeFixup(pstTree, pstChild);
        }

        /* re-initalize the pstZ */
        pstZ->lColor = LOS_RB_RED;
        pstZ->pstLeft = pstZ->pstRight = pstZ->pstParent = pstNilT;

        return;
    }

    /* Here is some different with book "Introduction to Algorithms,
     * Second Edition", book's arithmetic won't delete pstZ, and it deletes
     * pstZ's successor node instead. But we delete pstZ because
     * our data structure has no internal node. So code is some complex.
     */
    pstDel = pstZ;

    /* Get pstZ's successor node */
    pstZ = pstZ->pstRight;
    while (pstNilT != pstZ->pstLeft) {
        pstZ = pstZ->pstLeft;
    }

    /* Because left is nilT, so child must be right. */
    pstChild = pstZ->pstRight;
    if (NULL == pstChild) { /* Edit by r60958 for coverrity */
        return;
    }

    lColor = pstZ->lColor;

    /* Remove successor node out of tree. */
    pstChild->pstParent = pstZ->pstParent;

    if (pstNilT == pstZ->pstParent) {
        /* In fact, we never go here. */
        /* if we arrive here, pastTree is no NULL, so we can close pclint warning */
        /*lint -e613 */
        /*lint -e831 */
        pstTree->pstRoot = pstChild;
        /*lint +e831 */
        /*lint +e613 */
    } else {
        if (pstZ->pstParent->pstLeft == pstZ) {
            pstZ->pstParent->pstLeft = pstChild;
        } else {
            pstZ->pstParent->pstRight = pstChild;
        }
    }

    /* Insert successor node into tree and remove pstZ out of tree. */
    pstZ->pstParent = pstDel->pstParent;
    pstZ->lColor = pstDel->lColor;
    pstZ->pstRight = pstDel->pstRight;
    pstZ->pstLeft = pstDel->pstLeft;

    if (pstNilT == pstDel->pstParent) {
        /* if we arrive here, pastTree is no NULL, so we can close pclint warning */
        /*lint -e613 */
        /*lint -e831 */
        pstTree->pstRoot = pstZ;
        /*lint +e831 */
        /*lint +e613 */
    } else {
        if (pstDel->pstParent->pstLeft == pstDel) {
            pstDel->pstParent->pstLeft = pstZ;
        } else {
            pstDel->pstParent->pstRight = pstZ;
        }
    }

    pstDel->pstLeft->pstParent = pstZ;
    pstDel->pstRight->pstParent = pstZ;

    if (LOS_RB_BLACK == lColor) {
        OsRbDeleteNodeFixup(pstTree, pstChild);
    }

    /* re-initalize the pstDel */
    pstDel->lColor = LOS_RB_RED;
    pstDel->pstLeft = pstDel->pstRight = pstDel->pstParent = pstNilT;
    return;
}


STATIC VOID OsRbInitTree(LosRbTree *pstTree)
{
    if (NULL == pstTree) {
        return;
    }

    pstTree->ulNodes = 0;
    pstTree->pstRoot = &(pstTree->stNilT);
    pstTree->stNilT.lColor = LOS_RB_BLACK;
    pstTree->stNilT.pstLeft = NULL;   /* Always NULL */
    pstTree->stNilT.pstRight = NULL;  /* Always NULL */
    pstTree->stNilT.pstParent = NULL; /* Not NULL when tree isn't empty */
    LOS_ListInit(&pstTree->stWalkHead);

    pstTree->pfCmpKey = NULL;
    pstTree->pfFree = NULL;
    pstTree->pfGetKey = NULL;

    return;
}

STATIC VOID OsRbClearTree(LosRbTree *pstTree)
{
    LosRbWalk *pstWalk = NULL;
    LOS_DL_LIST *pstNode = NULL;

    if (NULL == pstTree) {
        return;
    }

    pstNode = LOS_DL_LIST_FIRST(&pstTree->stWalkHead);
    while (!LOS_DL_LIST_IS_END(&pstTree->stWalkHead, pstNode)) {
        pstWalk = LOS_DL_LIST_ENTRY(pstNode, LosRbWalk, stLink);
        pstWalk->pstCurrNode = NULL;
        pstWalk->pstTree = NULL;

        LOS_ListDelete(pstNode);
        pstNode = LOS_DL_LIST_FIRST(&pstTree->stWalkHead);
    }

    return;
}

LosRbWalk *LOS_RbCreateWalk(LosRbTree *pstTree)
{
    LosRbNode *pstNode = NULL;
    LosRbWalk *pstWalk = NULL;

    if (NULL == pstTree) {
        return NULL;
    }

    pstNode = LOS_RbFirstNode(pstTree);
    if (NULL == pstNode) {
        return NULL;
    }

    pstWalk = (LosRbWalk *)LOS_MemAlloc(m_aucSysMem0, sizeof(LosRbWalk));
    if (NULL == pstWalk) {
        return NULL;
    }

    LOS_ListAdd(&pstTree->stWalkHead, &pstWalk->stLink);
    pstWalk->pstCurrNode = pstNode;
    pstWalk->pstTree = pstTree;
    return pstWalk;
}

VOID *LOS_RbWalkNext(LosRbWalk *pstWalk)
{
    LosRbNode *pstNode = NULL;

    /*
     * Here, in the previous code, we didn't check pstCurrNode
     * pstTree, but in some circumstance, we will delete a tree
     * (by calling function RB_ClearTree), meanwhile, we will
     * evaluate pstCurrNode and pstTree to NULL, but at present,
     * if we are walking groups and ports, then we will call this
     * function(LOS_RbWalkNext), but the tree has been deleted already
     */
    if ((NULL == pstWalk) || (NULL == pstWalk->pstCurrNode) || (NULL == pstWalk->pstTree)) {
        return NULL;
    }

    pstNode = pstWalk->pstCurrNode;
    pstWalk->pstCurrNode = LOS_RbSuccessorNode(pstWalk->pstTree, pstNode);
    return pstNode;
}

VOID LOS_RbDeleteWalk(LosRbWalk *pstWalk)
{
    if (NULL == pstWalk) {
        return;
    }

    if (LOS_DL_LIST_IS_ON_QUEUE(&pstWalk->stLink)) {
        LOS_ListDelete(&pstWalk->stLink);
    }
    pstWalk->pstCurrNode = NULL;
    pstWalk->pstTree = NULL;
    LOS_MemFree(m_aucSysMem0, pstWalk);

    return;
}

VOID LOS_RbInsertOneNodeProcess(LosRbTree *pstTree, LosRbNode *pstParent, LosRbNode *pstNew)
{
    LosRbNode *pstNilT = &pstTree->stNilT;
    VOID *pNodeKey = NULL;
    VOID *pKey = NULL;
    ULONG_T ulCmpResult;

    pstNew->lColor = LOS_RB_RED;
    pstNew->pstLeft = pstNew->pstRight = pstNilT;
    if ((pstNew->pstParent = pstParent) == pstNilT) {
        pstTree->pstRoot = pstNew;
    } else {
        pNodeKey = pstTree->pfGetKey(pstNew);
        pKey = pstTree->pfGetKey(pstParent);
        ulCmpResult = pstTree->pfCmpKey(pNodeKey, pKey);
        if (RB_SMALLER == ulCmpResult) {
            pstParent->pstLeft = pstNew;
        } else {
            pstParent->pstRight = pstNew;
        }
    }

    OsRbInsertNodeFixup(pstTree, pstNew);

    return;
}

VOID LOS_RbInitTree(LosRbTree *pstTree, pfRBCmpKeyFn pfCmpKey, pfRBFreeFn pfFree, pfRBGetKeyFn pfGetKey)
{
    if (NULL == pstTree) {
        return;
    }

    OsRbInitTree(pstTree);

    pstTree->pfCmpKey = pfCmpKey;
    pstTree->pfFree = pfFree;
    pstTree->pfGetKey = pfGetKey;

    return;
}

VOID LOS_RbDestroyTree(LosRbTree *pstTree)
{
    LosRbNode *pstNode = NULL;

    if (NULL == pstTree) {
        return;
    }
    if (NULL == pstTree->pfFree) {
        return;
    }

    RB_WALK(pstTree, pstNode, pstWalk)
    {
        OsRbDeleteNode(pstTree, pstNode);
        (VOID)pstTree->pfFree(pstNode);
    }
    RB_WALK_END(pstTree, pstNode, pstWalk);

    OsRbClearTree(pstTree);

    return;
}

VOID *LOS_RbFirstNode(LosRbTree *pstTree)
{
    LosRbNode *pstNode = NULL;
    LosRbNode *pstNilT = NULL;

    if (NULL == pstTree) {
        return NULL;
    }

    pstNode = pstTree->pstRoot;
    if (pstNode == NULL) {
        return NULL;
    }
    pstNilT = &(pstTree->stNilT);

    if (pstNilT == pstNode) {
        return NULL;
    }

    while (pstNilT != pstNode->pstLeft) {
        pstNode = pstNode->pstLeft;
    }

    return pstNode;
}

VOID *LOS_RbSuccessorNode(LosRbTree *pstTree, VOID *pstData)
{
    LosRbNode *pstY = NULL;
    LosRbNode *pstNilT = NULL;
    LosRbNode *pstNode = NULL;

    /* begin: for earse pc_lint warning */
    if (NULL == pstTree) {
        return NULL;
    }
    /* end */

    pstNode = (LosRbNode *)pstData;

    if (NULL == pstNode) {
        return NULL;
    }

    /* NilT is forbidden. */
    if (!RB_IS_NOT_NILT(pstNode)) {
        return NULL;
    }

    /* if we arrive here, pastTree is no NULL, so we can close pclint warning */
    /*lint -e613 */
    /*lint -e831 */
    pstNilT = &(pstTree->stNilT);
    /*lint +e831 */
    /*lint +e613 */

    if (pstNilT != pstNode->pstRight) {
        pstNode = pstNode->pstRight;
        while (pstNilT != pstNode->pstLeft) {
            pstNode = pstNode->pstLeft;
        }

        return pstNode;
    }

    pstY = pstNode->pstParent;

    while ((pstNilT != pstY) && (pstNode == pstY->pstRight)) {
        pstNode = pstY;
        pstY = pstY->pstParent;
    }

    return ((pstNilT == pstY) ? NULL : pstY);
}

LosRbNode *LOS_RbGetNextNode(LosRbTree *pstTree, VOID *pKey)
{
    LosRbNode *pNode = NULL;

    if (TRUE == LOS_RbGetNode(pstTree, pKey, &pNode)) {
        return LOS_RbSuccessorNode(pstTree, pNode);
    } else if ((NULL == pNode) || (&pstTree->stNilT == pNode)) {
        return NULL;
    } else if (RB_BIGGER == pstTree->pfCmpKey(pKey, pstTree->pfGetKey(pNode))) {
        while (NULL != pNode) {
            pNode = LOS_RbSuccessorNode(pstTree, pNode);
            if (NULL == pNode) {
                return NULL;
            }

            if (RB_SMALLER == pstTree->pfCmpKey(pKey, pstTree->pfGetKey(pNode))) {
                break;
            }
        }
        return pNode;
    } else {
        return pNode;
    }
}

ULONG_T LOS_RbGetNode(LosRbTree *pstTree, VOID *pKey, LosRbNode **ppstNode)
{
    LosRbNode *pstNilT = NULL;
    LosRbNode *pstX = NULL;
    LosRbNode *pstY = NULL;
    VOID *pNodeKey = NULL;
    ULONG_T ulCmpResult;

    if ((NULL == pstTree) || (NULL == pKey) || (NULL == ppstNode)) {
        if (NULL != ppstNode) {
            *ppstNode = NULL;
        }
        return FALSE;
    }
    if ((NULL == pstTree->pfGetKey) || (NULL == pstTree->pfCmpKey)) {
        *ppstNode = NULL;
        return FALSE;
    }

    pstNilT = &pstTree->stNilT;
    pstY = pstTree->pstRoot;
    pstX = pstY;

    while (pstX != pstNilT) {
        pNodeKey = pstTree->pfGetKey(pstX);

        ulCmpResult = pstTree->pfCmpKey(pKey, pNodeKey);
        if (RB_EQUAL == ulCmpResult) {
            *ppstNode = pstX;
            return TRUE;
        }
        if (RB_SMALLER == ulCmpResult) {
            pstY = pstX;
            pstX = pstX->pstLeft;
        } else {
            pstY = pstX;
            pstX = pstX->pstRight;
        }
    }

    *ppstNode = pstY;
    return FALSE;
}

VOID LOS_RbDelNode(LosRbTree *pstTree, LosRbNode *pstNode)
{
    OsRbDeleteNode(pstTree, pstNode);
}

ULONG_T LOS_RbAddNode(LosRbTree *pstTree, LosRbNode *pstNew)
{
    ULONG_T ulSearchNode;
    VOID *pNodeKey = NULL;
    LosRbNode *pstX = NULL;

    if ((NULL == pstTree) || (NULL == pstNew)) {
        return FALSE;
    }
    if ((NULL == pstTree->pfGetKey) || (NULL == pstTree->pfCmpKey)) {
        return FALSE;
    }

    pNodeKey = pstTree->pfGetKey(pstNew);
    ulSearchNode = LOS_RbGetNode(pstTree, pNodeKey, &pstX);
    if (TRUE == ulSearchNode) {
        return FALSE;
    }

    if (NULL == pstX) {
        return FALSE;
    }

    LOS_RbInsertOneNodeProcess(pstTree, pstX, pstNew);

    return TRUE;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

