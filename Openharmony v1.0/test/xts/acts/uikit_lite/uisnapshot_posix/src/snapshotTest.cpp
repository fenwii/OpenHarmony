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
#include "components/ui_snapshot.h"

using namespace OHOS;
using namespace testing::ext;

class SnapshotTest : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_SNAPSHOT_SNAPSHOT_ADD_0100
* @tc.name       test snapshot add api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(SnapshotTest, testSnapshotAdd, TestSize.Level0) {
    UISnapShot* group = new UISnapShot();
    UIView* view = new UIView();
    group->Add(view);
    EXPECT_EQ(view, group->GetChildrenHead());
    EXPECT_EQ(view->GetParent(), group);
    delete(view);
    delete(group);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_SNAPSHOT_SNAPSHOT_FREEZE_0100
* @tc.name       test snapshot freeze api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(SnapshotTest, testSnapshotFreeze, TestSize.Level0) {
    UISnapShot* group = new UISnapShot();
    UIView* view = new UIView();
    group->Add(view);
    group->Freeze(true);
    EXPECT_EQ(false, group->IsViewGroup());
    group->UnFreeze();
    EXPECT_EQ(true, group->IsViewGroup());
    delete(view);
    delete(group);
}