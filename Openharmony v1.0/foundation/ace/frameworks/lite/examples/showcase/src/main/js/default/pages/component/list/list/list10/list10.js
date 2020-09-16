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
        text2: "margin已设置",
        text3: "宽高已设置"
    },
    ...backPage("pages/component/list/list/indexCommonStyle/index"),
    changeStatus: function () {
        if (this.status == true) {
            this.status = false;
        } else {
            this.status = true;
        }
    }
}