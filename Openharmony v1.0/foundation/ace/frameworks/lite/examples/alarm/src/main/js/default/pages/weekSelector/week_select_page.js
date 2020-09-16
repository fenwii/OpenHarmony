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
import router from "@system.router"

module.exports = {
    data: {
        weekImgSrc1: "common/weekUnSelected_Mon.png",
        weekImgSrc2: "common/weekUnSelected_Tue.png",
        weekImgSrc3: "common/weekUnSelected_Wed.png",
        weekImgSrc4: "common/weekUnSelected_Thu.png",
        weekImgSrc5: "common/weekUnSelected_Fri.png",
        weekImgSrc6: "common/weekUnSelected_Sat.png",
        weekImgSrc7: "common/weekUnSelected_Sun.png",
        dataWrapper: {
            mode: "",
            time: "00:00",
            repeat: "",
            alarmItemIndex: -1
        },
        originData: [],
        isDebug: false
    },
    onInit() {
        if (this.isDebug) {
            console.log("[weekSelector init] mode: " + this.dataWrapper.mode);
            console.log("[weekSelector init] time: " + this.dataWrapper.time);
            console.log("[weekSelector init] repeat: " + this.dataWrapper.repeat);
            console.log("[weekSelector init] alarmItemIndex: " + this.dataWrapper.alarmItemIndex);
        }

        if (this.dataWrapper.repeat.indexOf("Mon") !== -1) {
            this.weekImgSrc1 = "common/weekSelected_Mon.png";
        }
        if (this.dataWrapper.repeat.indexOf("Tue") !== -1) {
            this.weekImgSrc2 = "common/weekSelected_Tue.png";
        }
        if (this.dataWrapper.repeat.indexOf("Wed") !== -1) {
            this.weekImgSrc3 = "common/weekSelected_Wed.png";
        }
        if (this.dataWrapper.repeat.indexOf("Thu") !== -1) {
            this.weekImgSrc4 = "common/weekSelected_Thu.png";
        }
        if (this.dataWrapper.repeat.indexOf("Fri") !== -1) {
            this.weekImgSrc5 = "common/weekSelected_Fri.png";
        }
        if (this.dataWrapper.repeat.indexOf("Sat") !== -1) {
            this.weekImgSrc6 = "common/weekSelected_Sat.png";
        }
        if (this.dataWrapper.repeat.indexOf("Sun") !== -1) {
            this.weekImgSrc7 = "common/weekSelected_Sun.png";
        }

        this.dataWrapper.repeat = "";

        if (this.originData.toString() !== "undefined") {
            this.originData = this.originData;
        }
    },
    changeWeekImgSrc1() {
        this.weekImgSrc1 = this.weekImgSrc1.indexOf("UnSelected") === -1 ? "common/weekUnSelected_Mon.png" : "common/weekSelected_Mon.png";
    },
    changeWeekImgSrc2() {
        this.weekImgSrc2 = this.weekImgSrc2.indexOf("UnSelected") === -1 ? "common/weekUnSelected_Tue.png" : "common/weekSelected_Tue.png";
    },
    changeWeekImgSrc3() {
        this.weekImgSrc3 = this.weekImgSrc3.indexOf("UnSelected") === -1 ? "common/weekUnSelected_Wed.png" : "common/weekSelected_Wed.png";
    },
    changeWeekImgSrc4() {
        this.weekImgSrc4 = this.weekImgSrc4.indexOf("UnSelected") === -1 ? "common/weekUnSelected_Thu.png" : "common/weekSelected_Thu.png";
    },
    changeWeekImgSrc5() {
        this.weekImgSrc5 = this.weekImgSrc5.indexOf("UnSelected") === -1 ? "common/weekUnSelected_Fri.png" : "common/weekSelected_Fri.png";
    },
    changeWeekImgSrc6() {
        this.weekImgSrc6 = this.weekImgSrc6.indexOf("UnSelected") === -1 ? "common/weekUnSelected_Sat.png" : "common/weekSelected_Sat.png";
    },
    changeWeekImgSrc7() {
        this.weekImgSrc7 = this.weekImgSrc7.indexOf("UnSelected") === -1 ? "common/weekUnSelected_Sun.png" : "common/weekSelected_Sun.png";
    },
    submit() {
        if (this.weekImgSrc1.indexOf("UnSelected") === -1) {
            this.dataWrapper.repeat = "Mon";
        }
        if (this.weekImgSrc2.indexOf("UnSelected") === -1) {
            this.dataWrapper.repeat = this.dataWrapper.repeat + " Tue";
        }
        if (this.weekImgSrc3.indexOf("UnSelected") === -1) {
            this.dataWrapper.repeat = this.dataWrapper.repeat + " Wed";
        }
        if (this.weekImgSrc4.indexOf("UnSelected") === -1) {
            this.dataWrapper.repeat = this.dataWrapper.repeat + " Thu";
        }
        if (this.weekImgSrc5.indexOf("UnSelected") === -1) {
            this.dataWrapper.repeat = this.dataWrapper.repeat + " Fri";
        }
        if (this.weekImgSrc6.indexOf("UnSelected") === -1) {
            this.dataWrapper.repeat = this.dataWrapper.repeat + " Sat";
        }
        if (this.weekImgSrc7.indexOf("UnSelected") === -1) {
            this.dataWrapper.repeat = this.dataWrapper.repeat + " Sun";
        }
        if (this.dataWrapper.repeat === "") {
            this.dataWrapper.repeat = "Once";
        }

        if (this.dataWrapper.mode === "addAlarm") {
            router.replace({
                uri: 'pages/index/index',
                params:{dataWrapper: this.dataWrapper, originData: this.originData}
            });
        } else if (this.dataWrapper.mode === "editAlarm") {
            router.replace({
                uri: 'pages/editAlarm/edit_alarm',
                params: {dataWrapper: this.dataWrapper, originData: this.originData}
            });
        }
    }
}