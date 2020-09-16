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
import { Observer, Subject } from '../observer';
import {
  PHASE_APP_INIT,
  PHASE_FWK_EVAL,
  PHASE_INIT_DATA_GET_DATA,
  PHASE_INIT_DATA_OBSERVE,
  PHASE_INIT_DATA_PROXY,
  PHASE_INIT_STATE,
  startTracing,
  stopTracing
} from '../profiler';

startTracing(PHASE_APP_INIT);

/**
 * ViewModel constructor
 * @param {Object} options the options of ViewModel
 * @return {ViewModel} ViewModel instance
 */
export function ViewModel(options) {
  startTracing(PHASE_FWK_EVAL);
  if (!(this instanceof ViewModel)) {
    return new ViewModel(options);
  }

  const vm = (this._vm = this);

  if (Object.prototype.toString.call(options) === '[object Object]') {
    Object.keys(options).forEach(key => {
      const value = options[key];
      if (key === 'render') {
        vm.$render = value;
      } else if (key === 'data') {
        initState(vm, value);
      } else if (key === 'styleSheet') {
        initStyleSheet(value);
      } else if (typeof value === 'function') {
        vm[key] = value.bind(vm);
      } else {
        // do nothing
      }
    });
  }

  stopTracing();
}

ViewModel.prototype.$watch = function(getter, callback, meta) {
  return new Observer(this, getter, callback, meta);
};

/**
 * initialize the state of ViewModel instance
 * @param {ViewModel} vm ViewModel instance
 * @param {Object} data the data to be observe
 */
function initState(vm, data) {
  startTracing(PHASE_INIT_STATE);

  startTracing(PHASE_INIT_DATA_GET_DATA);
  if (typeof data === 'function') {
    data = data.call(vm, vm);
  }
  stopTracing(); // PHASE_INIT_DATA_GET_DATA

  startTracing(PHASE_INIT_DATA_PROXY);
  Object.keys(data).forEach(key => proxy(vm, data, key));
  stopTracing(); // PHASE_INIT_DATA_PROXY

  startTracing(PHASE_INIT_DATA_OBSERVE);
  Subject.of(data);
  stopTracing(); // PHASE_INIT_DATA_OBSERVE

  stopTracing(); // PHASE_INIT_STATE
}

/**
 * proxy data
 * @param {ViewModel} target ViewModel instance
 * @param {Object} source the data to be proxy
 * @param {String} key the key to be proxy
 */
function proxy(target, source, key) {
  Object.defineProperty(target, key, {
    enumerable: false,
    configurable: true,
    get() {
      return source[key];
    },
    set(value) {
      source[key] = value;
    }
  });
}

stopTracing();
