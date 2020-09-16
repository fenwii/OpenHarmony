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
import router from '@system.router'

export default {
    data:{
        location:"HangZhou",
        udpateStatus:"15:13",
        dataSource:"tianqi.com",
        updated:'Updated',
        dataSourceName:'Data Source',
        selectedIndex:0,
        airData:['100', '90', '120', '50', '150', '40', '25']
    },
    onInit(){
        this.location = this.$t(this.location);
        this.updated = this.$t("updated");
        this.dataSourceName = this.$t("dataSourceName");
        this.sampledOn = this.$t("sampledOn");
        this.monitoringStation = this.$t("monitoringStation");
        this.selectedIndex = this.selectedCityIndex;
    },
    openHistroy(){
        router.replace({
            uri:'pages/history/history'
        });
    },
    backMain(){
        router.replace({
            uri:'pages/index/index',
            params:{selectedCityIndex:this.selectedIndex}
        });
    }
}