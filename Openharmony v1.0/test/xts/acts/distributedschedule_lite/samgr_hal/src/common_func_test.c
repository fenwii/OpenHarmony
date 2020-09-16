/**
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Description : testcases for distributedschedule_lite subsystem
 * Create      : 2020/04/19
 */

#include <los_base.h>
#include "hctest.h"
#include "common.h"

#define OPER_INTERVAL 200    // 200 ms
#define RUN_TIMES 10

typedef struct Node {
    const int id;
    const char *name;
} Node;

static const Node *GetNode(const Node *node1)
{
    return node1;
}

static int CompareNode(const Node *node1, const Node *node2)
{
    if (node1->id < node2->id) {
        return -1;
    } else if (node1->id == node2->id) {
        return 0;
    } else {
        return 1;
    }
}

LITE_TEST_SUIT(test, samgr, CommonTestSuite);

static BOOL CommonTestSuiteSetUp(void)
{
    LOS_Msleep(OPER_INTERVAL);
    return TRUE;
}

static BOOL CommonTestSuiteTearDown(void)
{
    return TRUE;
}

/**
 * @tc.number    : DMSLite_SAMGR_Common_0010
 * @tc.name      : The vector operation after initialization is correct
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(CommonTestSuite, testCommon0010, LEVEL2)
{
    Vector nodeVector = VECTOR_Make((VECTOR_Key)GetNode, (VECTOR_Compare)CompareNode);
    TEST_ASSERT_EQUAL_INT(&nodeVector != NULL, TRUE);

    int16 vectorSize = VECTOR_Size(&nodeVector);
    TEST_ASSERT_EQUAL_INT(vectorSize == 0, TRUE);

    int16 vectorNum = VECTOR_Num(&nodeVector);
    TEST_ASSERT_EQUAL_INT(vectorNum == 0, TRUE);

    Node *vectorAt = (Node *)VECTOR_At(&nodeVector, (int16)0);
    TEST_ASSERT_EQUAL_INT(vectorAt == NULL, TRUE);

    Node node = {1, "node1"};
    Node *vectorSwap = (Node *)VECTOR_Swap(&nodeVector, (int16)0, &node);
    TEST_ASSERT_EQUAL_INT(vectorSwap == NULL, TRUE);

    int16 indexFind = VECTOR_Find(&nodeVector, &node);
    TEST_ASSERT_EQUAL_INT(INVALID_INDEX, indexFind);

    int16 indexFindByKey = VECTOR_FindByKey(&nodeVector, &node);
    TEST_ASSERT_EQUAL_INT(INVALID_INDEX, indexFindByKey);

    VECTOR_Clear(&nodeVector);
}

/**
 * @tc.number    : DMSLite_SAMGR_Common_0020
 * @tc.name      : The vector operation is correct when only 1 element
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(CommonTestSuite, testCommon0020, LEVEL2)
{
    Vector nodeVector = VECTOR_Make((VECTOR_Key)GetNode, (VECTOR_Compare)CompareNode);

    Node node = {1, "node1"};
    int16 resultAdd = VECTOR_Add(&nodeVector, &node);
    TEST_ASSERT_EQUAL_INT(resultAdd == 0, TRUE);
    
    int16 vectorSize = VECTOR_Size(&nodeVector);
    TEST_ASSERT_EQUAL_INT(vectorSize == 1, TRUE);

    int16 vectorNum = VECTOR_Num(&nodeVector);
    TEST_ASSERT_EQUAL_INT(vectorNum == 1, TRUE);

    Node *vectorAt = (Node *)VECTOR_At(&nodeVector, (int16)0);
    TEST_ASSERT_EQUAL_INT(vectorAt != NULL, TRUE);

    Node node2 = {2, "node2"};
    VECTOR_Swap(&nodeVector, (int16)0, &node2);
    
    int16 indexFind = VECTOR_Find(&nodeVector, &node2);
    TEST_ASSERT_EQUAL_INT(indexFind == 0, TRUE);

    int16 indexFindByKey = VECTOR_FindByKey(&nodeVector, &node2);
    TEST_ASSERT_EQUAL_INT(indexFindByKey == 0, TRUE);

    VECTOR_Clear(&nodeVector);
}

/**
 * @tc.number    : DMSLite_SAMGR_Common_0030
 * @tc.name      : The vector operation is correct when multi elements
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(CommonTestSuite, testCommon0030, LEVEL2)
{
    Vector nodeVector = VECTOR_Make((VECTOR_Key)GetNode, (VECTOR_Compare)CompareNode);

    Node node[] = {
        {0, "node"},
        {1, "node"},
        {2, "node"},
        {3, "node"},
        {4, "node"},
        {5, "node"},
        {6, "node"},
        {7, "node"},
        {8, "node"},
        {9, "node"},
    };

    for (int i = 0; i < RUN_TIMES; i++) {
        int16 resultAdd = VECTOR_Add(&nodeVector, &(node[i]));
        TEST_ASSERT_EQUAL_INT(i, resultAdd);
    }
    
    int16 vectorSize = VECTOR_Size(&nodeVector);
    TEST_ASSERT_EQUAL_INT(vectorSize == RUN_TIMES, TRUE);

    int16 vectorNum = VECTOR_Num(&nodeVector);
    TEST_ASSERT_EQUAL_INT(vectorNum == RUN_TIMES, TRUE);

    for (int i = 0; i < RUN_TIMES; i++) {
        Node *vectorAt = (Node *)VECTOR_At(&nodeVector, (int16)i);
        TEST_ASSERT_EQUAL_INT(vectorAt != NULL, TRUE);
        TEST_ASSERT_EQUAL_INT(vectorAt->id == i, TRUE);

        int16 indexFind = VECTOR_Find(&nodeVector, &node[i]);
        TEST_ASSERT_EQUAL_INT(indexFind == i, TRUE);

        int16 indexFindByKey = VECTOR_FindByKey(&nodeVector, &node[i]);
        TEST_ASSERT_EQUAL_INT(indexFindByKey == i, TRUE);
    }

    Node nodeX = {99, "node"};
    Node *resultNode = (Node *)VECTOR_Swap(&nodeVector, (int16)0, &nodeX);
    TEST_ASSERT_EQUAL_INT(TRUE, resultNode != NULL);
    TEST_ASSERT_EQUAL_INT(resultNode->id == 0, TRUE);

    VECTOR_Clear(&nodeVector);
}

/**
 * @tc.number    : DMSLite_SAMGR_Common_0040
 * @tc.name      : The vector operation is correct after delete some elements
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(CommonTestSuite, testCommon0040, LEVEL2)
{
    Vector nodeVector = VECTOR_Make((VECTOR_Key)GetNode, (VECTOR_Compare)CompareNode);
    Node node[] = {
        {0, "node"},
        {1, "node"},
        {2, "node"},
        {3, "node"},
        {4, "node"},
        {5, "node"},
        {6, "node"},
        {7, "node"},
        {8, "node"},
        {9, "node"},
    };
    for (int i = 0; i < RUN_TIMES; i++) {
        VECTOR_Add(&nodeVector, &(node[i]));
    }

    for (int i = 0; i < RUN_TIMES; i++) {
        Node *resultNode = (Node *)VECTOR_Swap(&nodeVector, (int16)i, NULL);
        TEST_ASSERT_EQUAL_INT(TRUE, resultNode != NULL);
        TEST_ASSERT_EQUAL_INT(i, resultNode->id);

        int16 vectorSize = VECTOR_Size(&nodeVector);
        TEST_ASSERT_EQUAL_INT(RUN_TIMES, vectorSize);

        int16 vectorNum = VECTOR_Num(&nodeVector);
        TEST_ASSERT_EQUAL_INT(RUN_TIMES - (i + 1), vectorNum);

        Node *vectorAt = (Node *)VECTOR_At(&nodeVector, (int16)i);
        TEST_ASSERT_EQUAL_INT(TRUE, vectorAt == NULL);

        int16 indexFind = VECTOR_Find(&nodeVector, &node[i]);
        TEST_ASSERT_EQUAL_INT(INVALID_INDEX, indexFind);

        int16 indexFindByKey = VECTOR_FindByKey(&nodeVector, &node[i]);
        TEST_ASSERT_EQUAL_INT(INVALID_INDEX, indexFindByKey);
    }
    
    VECTOR_Clear(&nodeVector);
}

/**
 * @tc.number    : DMSLite_SAMGR_Common_0050
 * @tc.name      : The vector operation is correct after add and delete some elements
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(CommonTestSuite, testCommon0050, LEVEL2)
{
    Vector nodeVector = VECTOR_Make((VECTOR_Key)GetNode, (VECTOR_Compare)CompareNode);
    Node node[] = {
        {0, "node"},
        {1, "node"},
        {2, "node"},
        {3, "node"},
        {4, "node"},
        {5, "node"},
        {6, "node"},
        {7, "node"},
        {8, "node"},
        {9, "node"},
    };
    for (int i = 0; i < (RUN_TIMES * RUN_TIMES); i++) {
        for (int j = 0; j < RUN_TIMES; j++) {
            VECTOR_Add(&nodeVector, &(node[j]));
        }
        for (int j = 0; j < RUN_TIMES; j++) {
            VECTOR_Swap(&nodeVector, (int16)j, NULL);
        }
    }

    for (int i = 0; i < RUN_TIMES; i++) {
        VECTOR_Add(&nodeVector, &(node[i]));
    }
    printf("[hctest]test start \n");
    for (int i = 0; i < RUN_TIMES; i++) {
        int16 indexFind = VECTOR_Find(&nodeVector, &node[i]);
        TEST_ASSERT_EQUAL_INT(indexFind >= 0, TRUE);

        int16 indexFindByKey = VECTOR_FindByKey(&nodeVector, &node[i]);
        TEST_ASSERT_EQUAL_INT(indexFindByKey >= 0, TRUE);

        Node *resultNode = (Node *)VECTOR_Swap(&nodeVector, indexFind, NULL);
        TEST_ASSERT_EQUAL_INT(TRUE, resultNode != NULL);
        TEST_ASSERT_EQUAL_INT(i, resultNode->id);

        int16 vectorSize = VECTOR_Size(&nodeVector);
        TEST_ASSERT_EQUAL_INT(vectorSize > (RUN_TIMES - (i + 1)), TRUE);

        int16 vectorNum = VECTOR_Num(&nodeVector);
        TEST_ASSERT_EQUAL_INT(RUN_TIMES - (i + 1), vectorNum);

        Node *vectorAt = (Node *)VECTOR_At(&nodeVector, indexFind);
        TEST_ASSERT_EQUAL_INT(TRUE, vectorAt == NULL);
    }
    
    VECTOR_Clear(&nodeVector);
}

/**
 * @tc.number    : DMSLite_SAMGR_Common_0060
 * @tc.name      : If vector or element is NULL adding element fails
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(CommonTestSuite, testCommon0060, LEVEL2)
{
    Vector nodeVector = VECTOR_Make((VECTOR_Key)GetNode, (VECTOR_Compare)CompareNode);

    Node node = {1, "node1"};
    int16 resultAdd = VECTOR_Add(NULL, &node);
    TEST_ASSERT_EQUAL_INT(INVALID_INDEX, resultAdd);
    
    resultAdd = VECTOR_Add(&nodeVector, NULL);
    TEST_ASSERT_EQUAL_INT(INVALID_INDEX, resultAdd);

    VECTOR_Clear(&nodeVector);
}

/**
 * @tc.number    : DMSLite_SAMGR_Common_0070
 * @tc.name      : If vector is NULL deleting element fails
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(CommonTestSuite, testCommon0070, LEVEL2)
{
    Vector nodeVector = VECTOR_Make((VECTOR_Key)GetNode, (VECTOR_Compare)CompareNode);
    Node node = {1, "node1"};
    VECTOR_Add(&nodeVector, &node);

    Node *vectorSwap = (Node *)VECTOR_Swap(NULL, (int16)0, NULL);
    TEST_ASSERT_EQUAL_INT(TRUE, vectorSwap == NULL);

    VECTOR_Clear(&nodeVector);
}

/**
 * @tc.number    : DMSLite_SAMGR_Common_0080
 * @tc.name      : If vector is NULL getting information from vector fails
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(CommonTestSuite, testCommon0080, LEVEL2)
{
    Vector nodeVector = VECTOR_Make((VECTOR_Key)GetNode, (VECTOR_Compare)CompareNode);
    Node node = {1, "node1"};
    VECTOR_Add(&nodeVector, &node);

    int16 vectorSize = VECTOR_Size(NULL);
    TEST_ASSERT_EQUAL_INT(INVALID_INDEX, vectorSize);

    int16 vectorNum = VECTOR_Num(NULL);
    TEST_ASSERT_EQUAL_INT(INVALID_INDEX, vectorNum);

    Node *vectorAt = (Node *)VECTOR_At(NULL, (int16)0);
    TEST_ASSERT_EQUAL_INT(TRUE, vectorAt == NULL);

    VECTOR_Clear(&nodeVector);
}

/**
 * @tc.number    : DMSLite_SAMGR_Common_0090
 * @tc.name      : If vector is NULL searching from vector fails
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
 */
LITE_TEST_CASE(CommonTestSuite, testCommon0090, LEVEL2)
{
    Vector nodeVector = VECTOR_Make((VECTOR_Key)GetNode, (VECTOR_Compare)CompareNode);
    Node node = {1, "node1"};
    VECTOR_Add(&nodeVector, &node);

    int16 indexFind = VECTOR_Find(NULL, &node);
    TEST_ASSERT_EQUAL_INT(INVALID_INDEX, indexFind);

    int16 indexFindByKey = VECTOR_FindByKey(NULL, &node);
    TEST_ASSERT_EQUAL_INT(INVALID_INDEX, indexFindByKey);

    VECTOR_Clear(&nodeVector);
}

RUN_TEST_SUITE(CommonTestSuite);