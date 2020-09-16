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
/**
 * start to trace
 * @param {number} phase the phase of tracing
 */
export function startTracing(phase) {
  if (typeof profiler !== 'undefined') {
    profiler.startTracing(phase);
  }
}

/**
 * stop to trace
 */
export function stopTracing() {
  if (typeof profiler !== 'undefined') {
    profiler.stopTracing();
  }
}

/**
 * keep sync with js_profiler.h
 */

export const PHASE_FWK_EVAL = 5;
export const PHASE_APP_INIT = 6;
export const PHASE_INIT_STATE = 7;
export const PHASE_INIT_DATA_GET_DATA = 8;
export const PHASE_INIT_DATA_PROXY = 9;
export const PHASE_INIT_DATA_OBSERVE = 10;
