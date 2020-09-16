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
import { ObserverStack, canObserve } from './utils';

/**
 * Observer constructor
 * @param {ViewModel} context execute context of callback
 * @param {Function} getter getter function
 * @param {Function} callback callback function
 * @param {Object} meta meta data that Observer object don't care about
 */
export function Observer(context, getter, callback, meta) {
  this._ctx = context;
  this._getter = getter;
  this._fn = callback;
  this._meta = meta;
  this._lastValue = this._get();
}

Observer.prototype._get = function() {
  try {
    ObserverStack.push(this);
    return this._getter.call(this._ctx);
  } finally {
    ObserverStack.pop();
  }
};

Observer.prototype.update = function() {
  const lastValue = this._lastValue;
  const nextValue = this._get();
  const context = this._ctx;
  const meta = this._meta;

  if (nextValue !== lastValue || canObserve(nextValue)) {
    this._fn.call(context, nextValue, lastValue, meta);
    this._lastValue = nextValue;
  }
};

Observer.prototype.subscribe = function(subject, key) {
  const detach = subject.attach(key, this);
  if (typeof detach !== 'function') {
    return void 0;
  }
  if (!this._detaches) {
    this._detaches = [];
  }
  this._detaches.push(detach);
};

Observer.prototype.unsubscribe = function() {
  const detaches = this._detaches;
  if (!detaches) {
    return void 0;
  }
  while (detaches.length) {
    detaches.pop()();
  }
};
