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
    ...backPage("pages/component/canvas/indexAPI/index"),
    fillStyleFunc: function () {
        var canvasRef = this.$refs.canvas1;
        var ctx = canvasRef.getContext("2d");

        var getFillStyle1 = ctx.fillStyle; // getter默认fillStyle
        console.info("getFillStyle1=" + getFillStyle1);

        var getFillStyle2 = ctx.fillStyle; // 再次getter默认fillStyle
        console.info("getFillStyle2=" + getFillStyle2);

        ctx.fillStyle = "#00ff00"; // setter
        //ctx.fillStyle = "rgba(0,255,0,1)"; //支持
        //ctx.fillStyle = "red";  //不支持
        ctx.strokeStyle = "#ff0000"; // 因为是填充图形，所以边框设置无效

        var getFillStyle3 = ctx.fillStyle; // setter后getter fillStyle
        console.info("getFillStyle3=" + getFillStyle3);
        ctx.fillRect(20,20,100,150);
    },
    strokeStyleFunc: function () {
        var canvasRef = this.$refs.canvas2;
        var ctx = canvasRef.getContext("2d");
        
        var getStrokeStyle1 = ctx.strokeStyle; // getter默认strokeStyle
        console.info("getStrokeStyle1=" + getStrokeStyle1);
        var getStrokeStyle2 = ctx.strokeStyle; // 再次getter默认strokeStyle
        console.info("getStrokeStyle2=" + getStrokeStyle2);

        ctx.fillStyle = "#00ff00";  // 因为是画矩形框，所以填充设置无效
        ctx.strokeStyle = "#0000ff"; // setter

        var getStrokeStyle3 = ctx.strokeStyle; // setter之后getter strokeStyle
        console.info("getStrokeStyle3=" + getStrokeStyle3);
        ctx.strokeRect(20,20,100,150);
    },
    lineWidthFunc: function () {
        var canvasRef = this.$refs.canvas3;
        var ctx = canvasRef.getContext("2d");

        var getLineWidth1 = ctx.lineWidth; // getter默认lineWidth
        console.info("getLineWidth1=" + getLineWidth1);

        var getLineWidth2 = ctx.lineWidth; // 再次getter默认lineWidth
        console.info("getLineWidth2=" + getLineWidth2);

        ctx.strokeStyle = "#ff0000";
        ctx.lineWidth = "10"; // setter

        var getLineWidth3 = ctx.lineWidth; // setter后getter lineWidth
        console.info("getLineWidth3=" + getLineWidth3);

        ctx.strokeRect(20,20,100,150);
    },
    fontFunc: function () {
        var canvasRef = this.$refs.canvas4;
        var ctx = canvasRef.getContext("2d");

        var getFont1 = ctx.font; // getter默认font
        console.info("getFont1=" + getFont1);

        var getFont2 = ctx.font; // 再次getter默认font
        console.info("getFont2=" + getFont2);

        ctx.font = "  30px HYQiHei-65S two    three f "; // setter
        //ctx.font = "  "; // setter

        var getFont3 = ctx.font; // setter后getter font
        console.info("getFont3=" + getFont3);

        ctx.fillText("Hello ACE", 10, 50);
    },
    textAlignFunc: function () {
        var canvasRef = this.$refs.canvas5;
        var ctx = canvasRef.getContext("2d");

        var getTextAlign1 = ctx.textAlign; // getter默认text align
        console.info("getTextAlign1=" + getTextAlign1);

        var getTextAlign2 = ctx.textAlign; // 再次getter默认text align
        console.info("getTextAlign2=" + getTextAlign2);

        ctx.font = "30px HYQiHei-65S";
        ctx.textAlign = "left"; // setter
        ctx.fillText("left", 110, 10);
        ctx.textAlign = "right"; // setter
        ctx.fillText("right", 110, 50);
        ctx.textAlign = "center"; // setter
        ctx.fillText("center", 110, 100);

        var getTextAlign3 = ctx.textAlign; // setter后 getter text align
        console.info("getTextAlign3=" + getTextAlign3);
    },
    jumpFunc: routePage("pages/component/canvas/indexAPIAttr/index").changePage
}