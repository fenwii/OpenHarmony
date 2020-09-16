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
    data: {
      textColor1:'#00ff00',
      textColor2:'#00ff00',
      bgColor1:'#669966',
      bgColor2:'#669966',
      swiperPage:0,
      percent1:0,
      percent2:0,
      src1:'common/cloud_green.png',
      src2:'common/cloud_green.png',
      airData: [{
        location: 'HangZhou',
        airQuality: 'Good',
        detailData: 10
      }, {
        location: 'ShangHai',
        airQuality: 'Unhealth',
        detailData:90
      }]
    },
    onInit () {
      this.airData[0].location = this.$t(this.airData[0].location);
      this.airData[1].location = this.$t(this.airData[1].location);
      this.airData[0].airQuality = this.$t(this.airData[0].airQuality);
      this.airData[1].airQuality = this.$t(this.airData[1].airQuality);
      if(this.airData[0].detailData > 100){
        this.src1 = "common/cloud_red.png";
        this.textColor1 = '#ff0000';
        this.bgColor1 = '#9d7462';
      } else if(50 < this.airData[0].detailData &&  this.airData[0].detailData <= 100){
        this.src1 = "common/cloud_yellow.png";
        this.textColor1 = '#ecf19a';
        this.bgColor1 = '#9d9d62';
      }
      if(this.airData[1].detailData > 100){
        this.src2 = "common/cloud_red.png";
        this.textColor2 = '#ff0000';
        this.bgColor2 = '#9d7462';
      } else if(50 < this.airData[1].detailData &&  this.airData[1].detailData <= 100){
        this.src2 = "common/cloud_yellow.png";
        this.textColor2 = '#ecf19a';
        this.bgColor2 =  '#9d9d62';
      }
      if(this.selectedCityIndex){
        this.swiperPage = this.selectedCityIndex;
      }
    },
    onShow () {
      var self = this;
      var time = 1000/(self.airData[self.swiperPage].detailData);
      if(time == 0){
        time = 100;
      }
      var interval = setInterval(function () {
        if ((self.swiperPage==0?self.percent1:self.percent2) >= self.airData[self.swiperPage].detailData) {
          clearInterval(interval);
          return;
        }
        (self.swiperPage==0?self.percent1++:self.percent2++);
      }, time)
    },
    openDetail () {
      router.replace({
        uri:'pages/detail/detail',
        params:{selectedCityIndex:this.swiperPage}
      });
    },
    swiperChange (e) {
      this.swiperPage = e.index;
      var self = this;
      var time = 1000/(self.airData[self.swiperPage].detailData);
      if(time == 0){
        time = 100;
      }
      var interval = setInterval(function () {
        if ((self.swiperPage==0?self.percent1:self.percent2) >= self.airData[self.swiperPage].detailData) {
          clearInterval(interval);
          return;
        }
        (self.swiperPage==0?self.percent1++:self.percent2++);
      }, time)
    }
}
