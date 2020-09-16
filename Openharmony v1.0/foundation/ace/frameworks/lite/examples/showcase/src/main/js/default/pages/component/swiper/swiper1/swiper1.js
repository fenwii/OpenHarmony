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
        index: 0,
        text2: "longpress未触发",
        text3: "click未触发",
        text4: "swipe未触发",
    },
    ...backPage("pages/component/swiper/indexEvent/index"),
    textChange2: function () {
        this.text2 = "longpress已触发";
    },
    textChange3: function () {
        this.text3 = "click已触发";
    },
    textChange4: function (e) {
        this.text4 = "swipe方向：" + e.direction;
    },
    showPage: function (e) {
        this.index = e.index + 1;
    }
}