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
var router = require("@system.router");
module.exports = {
  data: {
    listData: [
      "a",
      "b",
      "c",
      "d",
      "e",
      "f",
      "g",
      "h"
    ]
  },
  backMain: function () {
        router.replace({ uri: "pages/index/index" });
  },
  backSuperior: function () {
        router.replace({ uri: "pages/component/list/list/indexOperation/index" });
  },
  listClick() {
    router.replace({ uri: "pages/component/list/list/list13/list13" });
    console.log("list onclick is triggered");
  },
  scrollEnd(endState, endComponentIndex) {
    console.log("list onscrollend is triggered, end component index=" + endComponentIndex);
    console.log("list onscrollend is triggered, state=" + endState);
  },
  clickscrollTo() {
    this.$refs.listObj.scrollTo({index:2});
  },
  onInit() {
    console.log("on init called...");
  },
  onShow() {
    this.$refs.listObj.scrollTo({index:3});
    console.log("on Ready called...");
  },
};
