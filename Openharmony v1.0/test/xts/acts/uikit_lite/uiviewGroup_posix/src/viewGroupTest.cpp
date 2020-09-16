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

#include "gtest/gtest.h"
#include <climits>
#include "components/root_view.h"
#include "components/ui_view_group.h"

using namespace OHOS;
using namespace testing::ext;

class ViewGroupTest : public testing::Test {
protected:
    // SetUpTestCase: Testsuit setup, run before 1st testcase
    static void SetUpTestCase(void) {}
    // TearDownTestCase: Testsuit teardown, run after last testcase
    static void TearDownTestCase(void) {}
    // Testcase setup
    virtual void SetUp() {}
    // Testcase teardown
    virtual void TearDown() {}
};

/**
* @tc.number     SUB_UIKIT_NDKAPI_VIEWGROUP_VIEWGROUP_ADD_0100
* @tc.name       test view group add api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ViewGroupTest, testViewGroupAdd, TestSize.Level0) {
    UIViewGroup* group = new UIViewGroup();
    UIView* view = new UIView();
    group->Add(view);
    EXPECT_EQ(view, group->GetChildrenHead());
    EXPECT_EQ(view->GetParent(), group);
    delete(view);
    delete(group);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_VIEWGROUP_VIEWGROUP_INSERT_0100
* @tc.name       test view group insert api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ViewGroupTest, testViewGroupInsert, TestSize.Level0) {
    UIViewGroup* group = new UIViewGroup();
    UIView* preView = new UIView();
    UIView* view = new UIView();
    group->Add(preView);
    group->Insert(preView, view);
    EXPECT_EQ(view, preView->GetNextSibling());
    delete(preView);
    delete(view);
    delete(group);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_VIEWGROUP_VIEWGROUP_REMOVE_0100
* @tc.name       test view group remove api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ViewGroupTest, testViewGroupRemove, TestSize.Level0) {
    UIViewGroup* group = new UIViewGroup();
    UIView* view = new UIView();
    group->Add(view);
    group->Remove(view);
    EXPECT_EQ(nullptr, group->GetChildrenHead());
    EXPECT_EQ(nullptr, view->GetParent());
    delete(view);
    delete(group);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_VIEWGROUP_VIEWGROUP_REMOVEALL_0100
* @tc.name       test view group remove all api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ViewGroupTest, testViewGroupRemoveAll, TestSize.Level0) {
    UIViewGroup* group = new UIViewGroup();
    UIView* view = new UIView();
    UIView* view2 = new UIView();
    group->Add(view);
    group->RemoveAll();
    EXPECT_EQ(nullptr, group->GetChildrenHead());
    delete(view);
    delete(view2);
    delete(group); 
}