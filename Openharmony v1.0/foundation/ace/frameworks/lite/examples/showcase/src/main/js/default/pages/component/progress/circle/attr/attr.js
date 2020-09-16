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
import {goPage,routePage} from "../../../../../common/js/general";
import {changeStatus, changeStatusIf, changeDisplay} from "../../../../../common/js/progress"
export default {
    data: {
        showStatus: true,
        ifStatus: true,
        percentAttribute: 20,
        loopArray: ["1", "2", "3"],
        p01: "p01",
        display: "flex"
    },
    ...goPage("pages/component/progress/circle/index/index"),
    changePercent() {
        this.percentAttribute = this.percentAttribute + 10;
    },
    changeStatus() {
        if (this.showStatus == true) {
            this.showStatus = false;
        } else {
            this.showStatus = true;
        }
    },
    changeStatusIf: changeStatusIf,
    changeDisplay: changeDisplay
}