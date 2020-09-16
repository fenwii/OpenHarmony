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
import {backPage, routePage} from "../../../../../common/js/general";
export default {
    data: {
        text1: "上面绿块为list",
        text2: "点击按钮切换display",
        text3: "支持flex/none",
        display: "flex"
    },
    ...backPage("pages/component/list/list/indexCommonStyle/index"),
    changeDisplay: function () {
        if (this.display === "flex") {
            this.display = "none";
        } else {
            this.display = "flex";
        }
    }
}