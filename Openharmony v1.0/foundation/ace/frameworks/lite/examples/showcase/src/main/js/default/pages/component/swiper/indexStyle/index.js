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
import {backPage, routePage} from "../../../../common/js/general";
export default {
    ...backPage("pages/component/swiper/index/index"),
    changePage1: routePage("pages/component/swiper/swiper2/swiper2").changePage,
    changePage2: routePage("pages/component/swiper/swiper3/swiper3").changePage,
    changePage3: routePage("pages/component/swiper/swiper4/swiper4").changePage,
    changePage4: routePage("pages/component/swiper/swiper8/swiper8").changePage,
    changePage5: routePage("pages/component/swiper/swiper9/swiper9").changePage,
    changePage6: routePage("pages/component/swiper/swiper10/swiper10").changePage
}