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
#include "components/ui_image_view.h"

using namespace OHOS;
using namespace testing::ext;

class ImageViewTest : public testing::Test {
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
* @tc.number     SUB_UIKIT_NDKAPI_IMAGE_IMAGE_POSITION_0100
* @tc.name       test image option api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageViewTest, testImagePosition, TestSize.Level0) {
    UIImageView* imageView = new UIImageView();
    imageView->SetPosition(10, 10);
    imageView->SetHeight(100);
    imageView->SetWidth(200);

    EXPECT_EQ(imageView->GetX(), 10);
    EXPECT_EQ(imageView->GetY(), 10);

    imageView->SetPosition(30, 50, 70, 90);
    EXPECT_EQ(imageView->GetX(), 30);
    EXPECT_EQ(imageView->GetY(), 50);
    delete(imageView);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGE_IMAGE_SIZE_0100
* @tc.name       test image option api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageViewTest, testImageSize, TestSize.Level0) {
    UIImageView* imageView = new UIImageView();
    imageView->SetHeight(100);
    imageView->SetWidth(200);
    EXPECT_EQ(imageView->GetHeight(), 100);
    EXPECT_EQ(imageView->GetWidth(), 200);

    imageView->SetPosition(30, 50, 70, 90);
    EXPECT_EQ(imageView->GetWidth(), 70);
    EXPECT_EQ(imageView->GetHeight(), 90);
    delete(imageView);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGE_IMAGE_RESIZE_0100
* @tc.name       test image option api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageViewTest, testImageReSize, TestSize.Level0) {
    UIImageView* imageView = new UIImageView();
    imageView->SetHeight(100);
    imageView->SetWidth(200);
    imageView->Resize(100, 300);
    EXPECT_EQ(imageView->GetWidth(), 100);
    EXPECT_EQ(imageView->GetHeight(), 300);
    delete(imageView);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGE_IMAGE_PATH_0100
* @tc.name       test image path api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageViewTest, testImagePath, TestSize.Level0) {
    UIImageView* imageView = new UIImageView();
    char* srcPath = nullptr;
    imageView->SetSrc(srcPath);
    EXPECT_EQ(imageView->GetPath(), nullptr);

    ImageInfo* srcPath2 = nullptr;
    imageView->SetSrc(srcPath2);
    EXPECT_EQ(imageView->GetPath(), nullptr);

    imageView->SetSrc("..\\config\\images\\A021_001.bin");
    EXPECT_NE(imageView->GetPath(), nullptr);

    imageView->SetSrc("..\\config\\images\\A021_001.bin");
    EXPECT_NE(imageView->GetPath(), nullptr);
    delete(imageView);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGE_IMAGE_AUTOENABLE_0100
* @tc.name       test image auto enable api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageViewTest, testImageAutoEnable, TestSize.Level0) {
    UIImageView* imageView = new UIImageView();
    imageView->SetAutoEnable(true);
    EXPECT_EQ(imageView->GetAutoEnable(), true);
    delete(imageView);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGE_IMAGE_PARENT_0100
* @tc.name       test image parent api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageViewTest, testImageParent, TestSize.Level0) {
    UIImageView* imageView = new UIImageView();

    imageView->SetParent(nullptr);
    EXPECT_EQ(imageView->GetParent(), nullptr);

    UIView uiView;
    imageView->SetParent(&uiView);
    EXPECT_NE(imageView->GetParent(), nullptr);
    delete(imageView);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGE_IMAGE_NEXTSIBLING_0100
* @tc.name       test image next sibling api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageViewTest, testImageNextSibling, TestSize.Level0) {
    UIImageView* imageView = new UIImageView();
    imageView->SetNextSibling(nullptr);
    EXPECT_EQ(imageView->GetNextSibling(), nullptr);

    UIView uiView;
    imageView->SetNextSibling(&uiView);
    EXPECT_NE(imageView->GetNextSibling(), nullptr);
    delete(imageView);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGE_IMAGE_VISIBLE_0100
* @tc.name       test image visible api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageViewTest, testImageVisible, TestSize.Level0) {
    UIImageView* imageView = new UIImageView();
    imageView->SetVisible(true);
    EXPECT_EQ(imageView->IsVisible(), true);

    imageView->SetVisible(false);
    EXPECT_EQ(imageView->IsVisible(), false);
    delete(imageView);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGE_IMAGE_TOUCHABLE_0100
* @tc.name       test image touchable api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageViewTest, testImageTouchable, TestSize.Level0) {
    UIImageView* imageView = new UIImageView();
    imageView->SetTouchable(true);
    EXPECT_EQ(imageView->IsTouchable(), true);

    imageView->SetTouchable(false);
    EXPECT_EQ(imageView->IsTouchable(), false);
    delete(imageView);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGE_IMAGE_DRAGGABLE_0100
* @tc.name       test image draggable api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageViewTest, testImageDraggable, TestSize.Level0) {
    UIImageView* imageView = new UIImageView();
    imageView->SetDraggable(true);
    EXPECT_EQ(imageView->IsDraggable(), true);

    imageView->SetDraggable(false);
    EXPECT_EQ(imageView->IsDraggable(), false);
    delete(imageView);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGE_IMAGE_DRAGPARENTINSTREAD_0100
* @tc.name       test image drag parent instead api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageViewTest, testImageDragParentInstead, TestSize.Level0) {
    UIImageView* imageView = new UIImageView();
    imageView->SetDragParentInstead(true);
    EXPECT_EQ(imageView->IsDragParentInstead(), true);

    imageView->SetDragParentInstead(false);
    EXPECT_EQ(imageView->IsDragParentInstead(), false);
    delete(imageView);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGE_IMAGE_LISTENER_0100
* @tc.name       test image listener api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageViewTest, testImageListener, TestSize.Level0) {
    UIImageView* imageView = new UIImageView();
    imageView->SetOnDragListener(nullptr);
    EXPECT_EQ(imageView->GetOnDragListener(), nullptr);

    imageView->SetOnClickListener(nullptr);
    EXPECT_EQ(imageView->GetOnClickListener(), nullptr);

    imageView->SetOnLongPressListener(nullptr);
    EXPECT_EQ(imageView->GetOnLongPressListener(), nullptr);
    delete(imageView);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGE_IMAGE_VIEW_0100
* @tc.name       test image view api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageViewTest, testImageViewTest1, TestSize.Level0) {
    UIImageView* imageView = new UIImageView();
    imageView->SetViewId(nullptr);
    EXPECT_EQ(imageView->GetViewId(), nullptr);

    imageView->SetViewIndex(101);
    EXPECT_EQ(imageView->GetViewIndex(), 101);
    delete(imageView);
}

/**
* @tc.number     SUB_UIKIT_NDKAPI_IMAGE_IMAGE_STYLE_0100
* @tc.name       test image style api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ImageViewTest, testImageViewTest2, TestSize.Level0) {
    UIImageView* imageView = new UIImageView();
    imageView->SetStyle(STYLE_BACKGROUND_OPA, 0);
    imageView->SetStyle(STYLE_BACKGROUND_COLOR, 800);
    imageView->SetStyle(STYLE_BORDER_RADIUS, 100);
    imageView->SetStyle(STYLE_IMAGE_OPA, 190);

    EXPECT_EQ(imageView->GetStyle(STYLE_BACKGROUND_OPA), 0);
    EXPECT_EQ(imageView->GetStyle(STYLE_BACKGROUND_COLOR), 800);
    EXPECT_EQ(imageView->GetStyle(STYLE_BORDER_RADIUS), 100);
    EXPECT_EQ(imageView->GetStyle(STYLE_IMAGE_OPA), 190);
    delete(imageView);
}