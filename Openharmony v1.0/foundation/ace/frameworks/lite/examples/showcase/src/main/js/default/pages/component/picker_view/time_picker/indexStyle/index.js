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
    ...backPage("pages/component/picker_view/time_picker/index/index"),
    changePage1: routePage("pages/component/picker_view/time_picker/time_picker2/time_picker2").changePage,
    changePage2: routePage("pages/component/picker_view/time_picker/time_picker3/time_picker3").changePage,
    changePage3: routePage("pages/component/picker_view/time_picker/time_picker4/time_picker4").changePage,
    change2Style: routePage("pages/component/picker_view/time_picker/time_picker9/time_picker9").changePage,
    change2Display: routePage("pages/component/picker_view/time_picker/time_picker10/time_picker10").changePage
}