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
        listData: [
            "text组件b",
            "text组件c",
            "text组件d"
        ]
    },
    ...backPage("pages/component/list/list/indexOperation/index"),
    pushItem: function () {
        console.log("push an item.");
        this.listData.push("text组件z");
    },
    popItem: function () {
        console.log("pop an item.");
        this.listData.pop();
    },
    shiftItem: function () {
        console.log("shift an item.");
        this.listData.shift();
    },
    unshiftItem: function () {
        console.log("unshift an item.");
        this.listData.unshift("text组件a");
    },
    spliceItem: function () {
        console.log("splice items.");
        this.listData.splice(0, 1, "text组件x", "text组件y");
    }
}