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
        amOrPm: "",
        dataWrapper: {
            mode: "",
            time: "00:00",
            repeat: "Once",
            alarmItemIndex: -1
        },
        originData: []
    },
    onInit() {
        this.dataWrapper = this.dataWrapper;
        if (this.originData.toString() !== "undefined") {
            this.originData = this.originData;
        }

        var alarmTime = this.dataWrapper.time;
        var alarmTimeArray = alarmTime.split(" ");
        this.dataWrapper.time = alarmTimeArray[0];
        this.amOrPm = alarmTimeArray[1];
    },
    postpone() {
        router.replace({
            uri: 'pages/index/index',
            params:{dataWrapper: this.dataWrapper, switchValue: true, originData: this.originData}
        });
    },
    cancel() {
        router.replace({
            uri: 'pages/index/index',
            params:{dataWrapper: this.dataWrapper, switchValue: false, originData: this.originData}
        });
    }
}