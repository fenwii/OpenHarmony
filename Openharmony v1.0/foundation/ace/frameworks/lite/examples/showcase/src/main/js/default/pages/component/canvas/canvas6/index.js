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
        text1: "边框和内边距"
    },
    ...backPage("pages/component/canvas/indexCommonStyle/index"),
    fillStyleFunc: function () {
        var canvasRef = this.$refs.canvas1;
        var ctx = canvasRef.getContext("2d");
        ctx.fillStyle = "#00ff00";
        ctx.strokeStyle = "#ff0000"; // 因为是填充图形，所以边框设置无效
        ctx.fillRect(0,0,100,150);
    }
}