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
        dataWrapper: {
            mode: "",
            time: "00:00",
            repeat: "Once",
            alarmItemIndex: -1
        },
        originData: [],
        isDebug: false
    },
    onInit() {
        if (this.isDebug) {
            console.log("[editAlarm init] mode: " + this.dataWrapper.mode);
            console.log("[editAlarm init] mode: " + this.dataWrapper.time);
            console.log("[editAlarm init] mode: " + this.dataWrapper.repeat);
            console.log("[editAlarm init] mode: " + this.dataWrapper.alarmItemIndex);
        }
        this.dataWrapper = this.dataWrapper;
        this.transforTimeToTwentyFourHour(this.dataWrapper.time);
        if (this.originData.toString() !== "undefined") {
            this.originData = this.originData;
        }
    },
    transforTimeToTwentyFourHour(time) {
        var timeArray = time.split(" ");
        var timeDigital = timeArray[0];
        var timeAMPM = timeArray[1];
        if (timeAMPM === "PM") {
            var hourTimeArray = timeDigital.split(":");
            var hour = hourTimeArray[0];
            var minute = hourTimeArray[1];
            hour = Number(hour) + 12;
            this.dataWrapper.time = hour + ":" + minute;
        } else {
            this.dataWrapper.time = timeDigital;
        }
    },
    switchToTimePicker() {
        router.replace({
            uri: 'pages/timeSelector/time_picker_page',
            params:{dataWrapper: this.dataWrapper, originData: this.originData}
        });
    },
    switchToWeekSelector() {
        router.replace({
            uri: 'pages/weekSelector/week_select_page',
            params:{dataWrapper: this.dataWrapper, originData: this.originData}
        });
    },
    submit() {
        router.replace({
            uri: 'pages/index/index',
            params:{dataWrapper: this.dataWrapper, originData: this.originData}
        });
    },
    remove() {
        router.replace({
            uri: 'pages/index/index',
            params:{dataWrapper: this.dataWrapper, deleteAlarm: true, originData: this.originData}
        });
    }
}