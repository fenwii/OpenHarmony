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
export const dataCommon = {
  datasets: {
    barsets: [
      {
        fillColor: "#9c9c9c",
        data: [2478, 2600, 3000, 3200, 3500, 3888, 4023, 4501, 4999, 5267]
      },
      {
        fillColor: "#3f9c3f",
        data: [2000, 2, 800, 700, 433]
      },
      {
        fillColor: "#9c3f3f",
        data: [100, 200, 300, 400, 500, 600, 550, 450, 350]
      }
    ],
    linesets: [
      {
        strokeColor: "#eeaaff",
        data: [2478, 2600, 3000, 3200, 3500, 3888, 4023, 4501, 4999, 5267]
      },
      {
        strokeColor: "#ccddee",
        data: [2000, 2, 800, 700, 433]
      },
      {
        strokeColor: "#ddaacc",
        data: [100, 200, 300, 400, 500, 600, 550, 450, 350]
      }
    ]
  },
  options: {
    xAxis: {
      min: 0,
      max: 10,
      axisTick: 5,
      display: false
    },
    yAxis: {
      min: 0,
      max: 5000,
      axisTick: 5,
      display: false
    }
  },
  optionsNoDisplay: {
    xAxis: {
      min: 0,
      max: 10,
      axisTick: 5
    },
    yAxis: {
      min: 0,
      max: 5000,
      axisTick: 5
    }
  }
};
export const changeStatus = function() {
  if (this.status == true) {
    this.status = false;
  } else {
    this.status = true;
  }
};
export const changeDisplay = function() {
  if (this.display === "flex") {
    this.display = "none";
  } else {
    this.display = "flex";
  }
};