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
import router from "@system.router";
export const backPage = function(superiorUri) {
  return {
    backMain() {
      router.replace({ uri: "pages/index/index" });
    },
    backSuperior() {
      router.replace({ uri: superiorUri });
    }
  };
};
export const goPage = function(superiorUri) {
  return {
    goHome() {
      router.replace({ uri: "pages/index/index" });
    },
    goPrevious() {
      router.replace({ uri: superiorUri });
    }
  };
};
export const routePage = function(page) {
  return {
    changePage() {
      router.replace({ uri: page });
    }
  };
};
export const eventCommon = function() {
  return {
    text1: "点击事件未触发",
    text2: "长按事件未触发",
    text3: "swipe事件未触发",
    clickFunc: function() {
      this.text1 = "点击事件已触发";
    },
    longpressFunc: function() {
      this.text2 = "长按事件已触发";
    },
    swipeFunc: function(e) {
      this.text3 = "swipe方向：" + e.direction;
    }
  };
};