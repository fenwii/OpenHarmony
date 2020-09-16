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
        time: ["07:20 AM", "07:30 AM", "12:00 AM", "06:00 PM"],
        repeat: ["Mon Tue Wed Thu Fri", "Mon Tue Wed Thu Fri Sat Sun", "Mon Tue Wed Thu Fri", "Once"],
        mode: ["addAlarm", "editAlarm", "deleteAlarm", "timeArrive"],
        switchStatus: [false, false, false, false],

        dataWrapper: {
            mode: "",
            time: "00:00",
            repeat: "Once",
            alarmItemIndex: -1
        },

        originData: [],
        isDebug: true
    },
    packOriginData() {
        this.originData = [this.time, this.repeat, this.switchStatus];
    },
    unPackOriginData() {
        this.time = this.originData[0];
        this.repeat = this.originData[1];
        this.switchStatus = this.originData[2];
    },
    onInit() {
        console.log("[mainPage init]");
        if (this.originData.length === 0) { // app first start
            this.packOriginData();
        } else {
            if (this.isDebug) {
                console.log("[mainPage init] mode: " + this.dataWrapper.mode);
                console.log("[mainPage init] mode: " + this.dataWrapper.time);
                console.log("[mainPage init] mode: " + this.dataWrapper.repeat);
                console.log("[mainPage init] mode: " + this.dataWrapper.alarmItemIndex);
            }

            this.unPackOriginData(); // apply origin data to current enviroment

            if (this.dataWrapper.mode === this.mode[0]) { // add alarm
                this.time.push(this.transforTimeToTwelvehour(this.dataWrapper.time));
                this.repeat.push(this.dataWrapper.repeat);
                this.switchStatus.push(false);

            } else if (this.dataWrapper.mode === this.mode[1]) { // edit alarm
                if (typeof(this.deleteAlarm) != "undefined") {
                    this.time.splice(this.dataWrapper.alarmItemIndex, 1);
                    this.repeat.splice(this.dataWrapper.alarmItemIndex, 1);
                    this.switchStatus.splice(this.dataWrapper.alarmItemIndex, 1);
                } else {
                    this.time[this.dataWrapper.alarmItemIndex] = this.transforTimeToTwelvehour(this.dataWrapper.time);
                    this.repeat[this.dataWrapper.alarmItemIndex] = this.dataWrapper.repeat;
                    this.switchStatus[this.dataWrapper.alarmItemIndex] = true;
                }

            } else if (this.dataWrapper.mode === this.mode[3]) { // time arrive
                var switchValue = this.switchValue;
                this.switchStatus[this.dataWrapper.switchIndex] = switchValue;
            }

            this.packOriginData(); // wrap current enviroment data as origin data
        }
    },
    transforTimeToTwelvehour(time) {
        var timeArray = time.split(" ")[0].split(":");
        var hour = timeArray[0];
        var minute = timeArray[1];
        if (minute.length === 1) {
            minute = "0" + minute;
        }
        if (Number(hour) >= 12) {
            hour = Number(hour) - 12;
            return hour + ":" + minute + " PM";
        } else {
            return hour + ":" + minute + " AM";
        }
    },
    addAlarm() {
        var date = new Date();
        var strHour = date.getHours();
        var strMin = date.getMinutes();
        this.dataWrapper.mode = this.mode[0];
        this.dataWrapper.time = strHour + ":" + strMin;
        router.replace({
            uri: 'pages/timeSelector/time_picker_page',
            params:{dataWrapper: this.dataWrapper, originData: this.originData}
        });
    },
    switchToEditAlarm(index) {
        this.dataWrapper.mode = this.mode[1];
        this.dataWrapper.time = this.time[index];
        this.dataWrapper.repeat = this.repeat[index];
        this.dataWrapper.alarmItemIndex = index;
        router.replace({
            uri: 'pages/editAlarm/edit_alarm',
            params:{dataWrapper: this.dataWrapper, originData: this.originData}
        });
    },
    switchChange(index, e) {
        if (e.checked) {
            this.dataWrapper.time = this.time[index];
            this.dataWrapper.mode = this.mode[3];
            this.dataWrapper.alarmItemIndex = index;
            var dataWrapper = this.dataWrapper;
            var oriData = this.originData;
            setTimeout(function () {
                router.replace({
                    uri: 'pages/timeArrive/time_arrive',
                    params:{dataWrapper: dataWrapper, originData: oriData}
                });
            }, 2000);
        }
    }
}