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
export const ObserverStack = {
  stack: [],
  push(observer) {
    this.stack.push(observer);
  },
  pop() {
    return this.stack.pop();
  },
  top() {
    return this.stack[this.stack.length - 1];
  }
};

export const SYMBOL_OBSERVABLE = '__ob__';

export const canObserve = target => typeof target === 'object';

export const defineProp = (target, key, value) => {
  Object.defineProperty(target, key, { enumerable: false, value });
};
