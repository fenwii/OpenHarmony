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
var displayData = ["flex", "none"];
export default {
    data: {
        text1: "item-abcd设置display，点击按钮切换display",
        status: true,
        displayValue: displayData[0]
    },
    changeDisplay: function () {
        if (this.status == true) {
            this.displayValue = displayData[1];
            this.status = false;
        } else {
            this.displayValue = displayData[0];
            this.status = true;
        }
    },
    ...backPage("pages/component/list/list-item/indexCommonStyle/index")
}