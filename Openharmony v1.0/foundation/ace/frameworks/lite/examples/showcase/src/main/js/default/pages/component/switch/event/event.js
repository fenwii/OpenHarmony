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
import {backPage, routePage} from "../../../../common/js/general";
export default {
    data: {
        clickValue: "点击文字改变",
        longpressValue: "长按文字改变",
        swipeValue: "滑动文字改变",
        checkedValue: false
    },
    ...backPage("pages/component/switch/index/index"),
    click: function () {
        this.clickValue = "点击已经触发";
    },
    longpress: function () {
        this.longpressValue = "长按已经触发";
    },
    swipeEvent: function (e) {
        this.swipeValue = "swipe方向：" + e.direction;
    },
    change: function () {
        if (this.checkedValue == false) {
            this.checkedValue = true;
        } else {
            this.checkedValue = false;
        }
    }
}