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
        selectedTime: "00:00",
        targetHour: "00",
        targetMinute: "00",
        isSelectTimeChanged: false,
        dataWrapper: {
            mode: "",
            repeat: "Once",
            time: "00:00",
            alarmItemIndex: -1
        },
        isDebug: false,
        originData: []
    },
    onInit() {
        if (this.isDebug) {
            console.log("[timePicker init] mode: " + this.dataWrapper.mode);
            console.log("[timePicker init] time: " + this.dataWrapper.time);
            console.log("[timePicker init] repeat: " + this.dataWrapper.repeat);
            console.log("[timePicker init] alarmItemIndex: " + this.dataWrapper.alarmItemIndex);
        }
        this.isSelectTimeChanged = false;
        if (this.dataWrapper.mode === "addAlarm" || this.dataWrapper.mode === "editAlarm") {
            this.selectedTime = this.dataWrapper.time;
        }
        if (this.originData.toString() !== "undefined") {
            this.originData = this.originData;
        }
    },
    getSelectedTime(e) {
        this.targetHour = e.hour;
        this.targetMinute = e.minute;
        this.isSelectTimeChanged = true;
    },
    next() {
        if (this.isSelectTimeChanged) {
            this.targetHour = this.targetHour.toString().length === 1 ? "0" + this.targetHour : this.targetHour;
            this.targetMinute = this.targetMinute.toString().length === 1 ? "0" + this.targetMinute : this.targetMinute;
            this.dataWrapper.time = this.targetHour + ":" + this.targetMinute + " AM";
        }
        if (this.dataWrapper.mode === "addAlarm") {
            router.replace({
                uri: 'pages/weekSelector/week_select_page',
                params:{dataWrapper: this.dataWrapper, originData: this.originData}
            });
        }else if (this.dataWrapper.mode === "editAlarm") {
            router.replace({
                uri: 'pages/editAlarm/edit_alarm',
                params:{dataWrapper: this.dataWrapper, originData: this.originData}
            });
        }
    }
}