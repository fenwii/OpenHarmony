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
        text1: "点击按钮改变状态",
        ifStatus: true
    },
    ...backPage("pages/component/canvas/indexAttr/index"),
    fillRectFunc: function () {
        var canvasRef = this.$refs.canvas1;
        var ctx = canvasRef.getContext("2d");
        ctx.fillRect(20,20,100,150);
    },
    changeIf: function () {
        if (this.ifStatus == true) {
            this.ifStatus = false;
        } else {
            this.ifStatus = true;
        }
    }
}