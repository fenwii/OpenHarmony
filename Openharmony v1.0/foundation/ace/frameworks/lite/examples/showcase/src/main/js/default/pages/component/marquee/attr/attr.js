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
import {goPage,routePage} from "../../../../common/js/general";
import {changeStatus, changeIfStatus} from "../../../../common/js/marquee"
export default {
  data: {
    status: true,
    ifstatus: true,
    marqueefor: [
      "1.marquee测试for标签，abcdefg",
      "2.marquee测试for标签，abcdefg"
    ]
  },
  ...goPage("pages/component/marquee/index/index"),
  changeStatus: changeStatus,
  changeIfStatus: changeIfStatus
};