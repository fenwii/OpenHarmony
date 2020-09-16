/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <securec.h>
#include "gtest/gtest.h"
#include "utils/SamgrTestBase.h"

const int RUN_TIMES = 10;
const int THREAD_NUM = 2;

using namespace testing::ext;

struct Node {
    int id;
    char *name;
    int value;
};

static const Node *GetNode(const Node *node1)
{
    return node1;
}

static MutexId g_mutex;

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

class CommonTest : public testing::Test {
protected:
    // SetUpTestCase: Testsuit setup, run before 1st testcase
    static void SetUpTestCase(void)
    {
        printf("[hcpptest]SetUpTestCase ! \n");
        SystemInitProxy();
    }
    // TearDownTestCase: Testsuit teardown, run after last testcase
    static void TearDownTestCase(void)
    {
    }
    // Testcase setup
    virtual void SetUp()
    {
        usleep(OPER_INTERVAL * MS2US);
    }
    // Testcase teardown
    virtual void TearDown()
    {
    }
};

/**
 * @tc.number    : DMSLite_SAMGR_Common_0010
 * @tc.name      : The vector operation after initialization is correct
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(CommonTest, testCommon0010, TestSize.Level2)
{
    Vector nodeVector = VECTOR_Make((VECTOR_Key)GetNode, (VECTOR_Compare)CompareNode);

    int16 vectorSize = VECTOR_Size(&nodeVector);
    ASSERT_EQ(vectorSize == 0, TRUE);

    int16 vectorNum = VECTOR_Num(&nodeVector);
    ASSERT_EQ(vectorNum == 0, TRUE);

    Node *vectorAt = (Node *)VECTOR_At(&nodeVector, (int16)0);
    ASSERT_EQ(vectorAt == nullptr, TRUE);

    Node node = {1, (char*)"node1", 1};
    Node *vectorSwap = (Node *)VECTOR_Swap(&nodeVector, (int16)0, &node);
    ASSERT_EQ(vectorSwap == nullptr, TRUE);

    int16 indexFind = VECTOR_Find(&nodeVector, &node);
    ASSERT_EQ(INVALID_INDEX, indexFind);

    int16 indexFindByKey = VECTOR_FindByKey(&nodeVector, &node);
    ASSERT_EQ(INVALID_INDEX, indexFindByKey);

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
HWTEST_F(CommonTest, testCommon0020, TestSize.Level2)
{
    Vector nodeVector = VECTOR_Make((VECTOR_Key)GetNode, (VECTOR_Compare)CompareNode);

    Node node = {1, (char*)"node1", 1};
    int16 resultAdd = VECTOR_Add(&nodeVector, &node);
    ASSERT_EQ(resultAdd, 0);
    
    int16 vectorSize = VECTOR_Size(&nodeVector);
    ASSERT_EQ(vectorSize, 1);

    int16 vectorNum = VECTOR_Num(&nodeVector);
    ASSERT_EQ(vectorNum, 1);

    Node *vectorAt = (Node *)VECTOR_At(&nodeVector, (int16)0);
    ASSERT_EQ(vectorAt != nullptr, TRUE);

    Node node2 = {2, (char*)"node2", 2};
    Node *resultNode = (Node *)VECTOR_Swap(&nodeVector, (int16)0, &node2);
    ASSERT_EQ(resultNode != nullptr, TRUE);

    int16 indexFind = VECTOR_Find(&nodeVector, &node2);
    ASSERT_EQ(indexFind, 0);

    int16 indexFindByKey = VECTOR_FindByKey(&nodeVector, &node2);
    ASSERT_EQ(indexFindByKey, 0);

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
HWTEST_F(CommonTest, testCommon0030, TestSize.Level2)
{
    Vector nodeVector = VECTOR_Make((VECTOR_Key)GetNode, (VECTOR_Compare)CompareNode);

    Node node[] = {
        {0, (char*)"node", 0},
        {1, (char*)"node", 1},
        {2, (char*)"node", 2},
        {3, (char*)"node", 3},
        {4, (char*)"node", 4},
        {5, (char*)"node", 5},
        {6, (char*)"node", 6},
        {7, (char*)"node", 7},
        {8, (char*)"node", 8},
        {9, (char*)"node", 9},
    };

    for (int i = 0; i < RUN_TIMES; i++) {
        int16 resultAdd = VECTOR_Add(&nodeVector, &(node[i]));
        ASSERT_EQ(i, resultAdd);
    }
    
    int16 vectorSize = VECTOR_Size(&nodeVector);
    ASSERT_EQ(vectorSize, RUN_TIMES);

    int16 vectorNum = VECTOR_Num(&nodeVector);
    ASSERT_EQ(vectorNum, RUN_TIMES);

    for (int i = 0; i < RUN_TIMES; i++) {
        Node *vectorAt = (Node *)VECTOR_At(&nodeVector, (int16)i);
        ASSERT_EQ(vectorAt != nullptr, TRUE);
        ASSERT_EQ(vectorAt->id, i);

        int16 indexFind = VECTOR_Find(&nodeVector, &node[i]);
        ASSERT_EQ(indexFind, i);

        int16 indexFindByKey = VECTOR_FindByKey(&nodeVector, &node[i]);
        ASSERT_EQ(indexFindByKey, i);
    }

    Node nodeX = {99, (char*)"node", 99};
    Node *resultNode = (Node *)VECTOR_Swap(&nodeVector, (int16)0, &nodeX);
    ASSERT_EQ(resultNode != nullptr, TRUE);
    ASSERT_EQ(resultNode->id, 0);

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
HWTEST_F(CommonTest, testCommon0040, TestSize.Level2)
{
    Vector nodeVector = VECTOR_Make((VECTOR_Key)GetNode, (VECTOR_Compare)CompareNode);
    Node node[] = {
        {0, (char*)"node", 0},
        {1, (char*)"node", 1},
        {2, (char*)"node", 2},
        {3, (char*)"node", 3},
        {4, (char*)"node", 4},
        {5, (char*)"node", 5},
        {6, (char*)"node", 6},
        {7, (char*)"node", 7},
        {8, (char*)"node", 8},
        {9, (char*)"node", 9},
    };
    for (int i = 0; i < RUN_TIMES; i++) {
        VECTOR_Add(&nodeVector, &(node[i]));
    }

    for (int i = 0; i < RUN_TIMES; i++) {
        Node *resultNode = (Node *)VECTOR_Swap(&nodeVector, (int16)i, nullptr);
        ASSERT_EQ(resultNode != nullptr, TRUE);
        ASSERT_EQ(i, resultNode->id);

        int16 vectorSize = VECTOR_Size(&nodeVector);
        ASSERT_EQ(RUN_TIMES, vectorSize);

        int16 vectorNum = VECTOR_Num(&nodeVector);
        ASSERT_EQ(RUN_TIMES - (i + 1), vectorNum);

        Node *vectorAt = (Node *)VECTOR_At(&nodeVector, (int16)i);
        ASSERT_EQ(TRUE, vectorAt == nullptr);

        int16 indexFind = VECTOR_Find(&nodeVector, &node[i]);
        ASSERT_EQ(INVALID_INDEX, indexFind);

        int16 indexFindByKey = VECTOR_FindByKey(&nodeVector, &node[i]);
        ASSERT_EQ(INVALID_INDEX, indexFindByKey);
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
HWTEST_F(CommonTest, testCommon0050, TestSize.Level2)
{
    Vector nodeVector = VECTOR_Make((VECTOR_Key)GetNode, (VECTOR_Compare)CompareNode);
    Node node[] = {
        {0, (char*)"node", 0},
        {1, (char*)"node", 1},
        {2, (char*)"node", 2},
        {3, (char*)"node", 3},
        {4, (char*)"node", 4},
        {5, (char*)"node", 5},
        {6, (char*)"node", 6},
        {7, (char*)"node", 7},
        {8, (char*)"node", 8},
        {9, (char*)"node", 9},
    };
    for (int i = 0; i < RUN_TIMES * RUN_TIMES; i++) {
        for (int j = 0; j < RUN_TIMES; j++) {
            VECTOR_Add(&nodeVector, &(node[j]));
        }
        for (int j = 0; j < RUN_TIMES; j++) {
            VECTOR_Swap(&nodeVector, (int16)j, nullptr);
        }
    }

    for (int i = 0; i < RUN_TIMES; i++) {
        VECTOR_Add(&nodeVector, &(node[i]));
    }
    printf("[hctest]test start \n");
    for (int i = 0; i < RUN_TIMES; i++) {
        int16 indexFind = VECTOR_Find(&nodeVector, &node[i]);
        ASSERT_EQ(indexFind >= 0, TRUE);

        int16 indexFindByKey = VECTOR_FindByKey(&nodeVector, &node[i]);
        ASSERT_EQ(indexFindByKey >= 0, TRUE);

        Node *resultNode = (Node *)VECTOR_Swap(&nodeVector, indexFind, nullptr);
        ASSERT_EQ(resultNode != nullptr, TRUE);
        ASSERT_EQ(i, resultNode->id);

        int16 vectorSize = VECTOR_Size(&nodeVector);
        ASSERT_EQ(vectorSize > (RUN_TIMES - (i + 1)), TRUE);

        int16 vectorNum = VECTOR_Num(&nodeVector);
        ASSERT_EQ(RUN_TIMES - (i + 1), vectorNum);

        Node *vectorAt = (Node *)VECTOR_At(&nodeVector, indexFind);
        ASSERT_EQ(TRUE, vectorAt == nullptr);
    }
    
    VECTOR_Clear(&nodeVector);
}

/**
 * @tc.number    : DMSLite_SAMGR_Common_0060
 * @tc.name      : If vector or element is nullptr adding element fails
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(CommonTest, testCommon0060, TestSize.Level2)
{
    Vector nodeVector = VECTOR_Make((VECTOR_Key)GetNode, (VECTOR_Compare)CompareNode);

    Node node = {1, (char*)"node1", 1};
    int16 resultAdd = VECTOR_Add(NULL, &node);
    ASSERT_EQ(INVALID_INDEX, resultAdd);
    
    resultAdd = VECTOR_Add(&nodeVector, nullptr);
    ASSERT_EQ(INVALID_INDEX, resultAdd);

    VECTOR_Clear(&nodeVector);
}

/**
 * @tc.number    : DMSLite_SAMGR_Common_0070
 * @tc.name      : If vector is nullptr deleting element fails
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(CommonTest, testCommon0070, TestSize.Level2)
{
    Vector nodeVector = VECTOR_Make((VECTOR_Key)GetNode, (VECTOR_Compare)CompareNode);
    Node node = {1, (char*)"node1", 1};
    VECTOR_Add(&nodeVector, &node);

    Node *vectorSwap = (Node *)VECTOR_Swap(NULL, (int16)0, nullptr);
    ASSERT_EQ(TRUE, vectorSwap == nullptr);

    VECTOR_Clear(&nodeVector);
}

/**
 * @tc.number    : DMSLite_SAMGR_Common_0080
 * @tc.name      : If vector is nullptr getting information from vector fails
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(CommonTest, testCommon0080, TestSize.Level2)
{
    Vector nodeVector = VECTOR_Make((VECTOR_Key)GetNode, (VECTOR_Compare)CompareNode);
    Node node = {1, (char*)"node1", 1};
    VECTOR_Add(&nodeVector, &node);

    int16 vectorSize = VECTOR_Size(NULL);
    ASSERT_EQ(INVALID_INDEX, vectorSize);

    int16 vectorNum = VECTOR_Num(NULL);
    ASSERT_EQ(INVALID_INDEX, vectorNum);

    Node *vectorAt = (Node *)VECTOR_At(NULL, (int16)0);
    ASSERT_EQ(TRUE, vectorAt == nullptr);

    VECTOR_Clear(&nodeVector);
}

/**
 * @tc.number    : DMSLite_SAMGR_Common_0090
 * @tc.name      : If vector is nullptr searching from vector fails
 * @tc.desc      : [C- SOFTWARE -0200]
 * @tc.size      : MEDIUM
 * @tc.type      : FUNC
 * @tc.level     : Level 2
*/
HWTEST_F(CommonTest, testCommon0090, TestSize.Level2)
{
    Vector nodeVector = VECTOR_Make((VECTOR_Key)GetNode, (VECTOR_Compare)CompareNode);
    Node node = {1, (char*)"node1", 1};
    VECTOR_Add(&nodeVector, &node);

    int16 indexFind = VECTOR_Find(NULL, &node);
    ASSERT_EQ(INVALID_INDEX, indexFind);

    int16 indexFindByKey = VECTOR_FindByKey(NULL, &node);
    ASSERT_EQ(INVALID_INDEX, indexFindByKey);

    VECTOR_Clear(&nodeVector);
}