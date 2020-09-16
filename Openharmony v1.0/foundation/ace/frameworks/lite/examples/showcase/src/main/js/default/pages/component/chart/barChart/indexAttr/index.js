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
    ...backPage("pages/component/chart/barChart/index/index"),
    changePage1: routePage("pages/component/chart/barChart/barChart6/barChart6").changePage,
    changePage2: routePage("pages/component/chart/barChart/barChart5/barChart5").changePage,
    changePage3: routePage("pages/component/chart/barChart/barChart7/barChart7").changePage,
    changePage4: routePage("pages/component/chart/barChart/barChart8/barChart8").changePage
}