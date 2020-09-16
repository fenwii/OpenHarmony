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
import {
  ObserverStack,
  SYMBOL_OBSERVABLE,
  canObserve,
  defineProp
} from './utils';


/**
 * Subject constructor
 * @param {any} target the target object to be observed
 */
export function Subject(target) {
  const subject = this;
  subject._hijacking = true;
  defineProp(target, SYMBOL_OBSERVABLE, subject);

  if (Array.isArray(target)) {
    hijackArray(target);
  }

  Object.keys(target).forEach(key => hijack(target, key, target[key]));
}

Subject.of = function(target) {
  if (!target || !canObserve(target)) {
    return target;
  }
  if (target[SYMBOL_OBSERVABLE]) {
    return target[SYMBOL_OBSERVABLE];
  }
  return new Subject(target);
};

Subject.is = function(target) {
  return target && target._hijacking;
};
Subject.prototype.attach = function(key, observer) {
  if (typeof key === 'undefined' || !observer) {
    return void 0;
  }
  if (!this._obsMap) {
    this._obsMap = {};
  }
  if (!this._obsMap[key]) {
    this._obsMap[key] = [];
  }
  const observers = this._obsMap[key];
  if (observers.indexOf(observer) < 0) {
    observers.push(observer);
    return function() {
      observers.splice(observers.indexOf(observer), 1);
    };
  }
};

Subject.prototype.notify = function(key) {
  if (
    typeof key === 'undefined' ||
    !this._obsMap ||
    !this._obsMap[key]
  ) {
    return void 0;
  }
  this._obsMap[key].forEach(observer => observer.update());
};

Subject.prototype.setParent = function(parent, key) {
  this._parent = parent;
  this._key = key;
};

Subject.prototype.notifyParent = function() {
  this._parent && this._parent.notify(this._key);
};

const ObservedMethods = {
  PUSH: 'push',
  POP: 'pop',
  UNSHIFT: 'unshift',
  SHIFT: 'shift',
  SPLICE: 'splice',
  REVERSE: 'reverse'
};

const OBSERVED_METHODS = Object.keys(ObservedMethods).map(
    key => ObservedMethods[key]
);

/**
 * observe the change of array
 * @param {Array} target a plain JavaScript array to be observed
 */
function hijackArray(target) {
  OBSERVED_METHODS.forEach(key => {
    const originalMethod = target[key];

    defineProp(target, key, function() {
      // eslint-disable-next-line
      const args = Array.prototype.slice.call(arguments);
      // eslint-disable-next-line
      originalMethod.apply(this, args);

      let inserted;
      if (ObservedMethods.PUSH === key || ObservedMethods.UNSHIFT === key) {
        inserted = args;
      } else if (ObservedMethods.SPLICE) {
        inserted = args.slice(2);
      }

      if (inserted && inserted.length) {
        inserted.forEach(Subject.of);
      }

      const subject = target[SYMBOL_OBSERVABLE];
      if (subject) {
        subject.notifyParent();
      }
    });
  });
}

/**
 * observe object
 * @param {any} target the object to be observed
 * @param {String} key the key to be observed
 * @param {any} cache the cached value
 */
function hijack(target, key, cache) {
  const subject = target[SYMBOL_OBSERVABLE];

  Object.defineProperty(target, key, {
    enumerable: true,
    get() {
      const observer = ObserverStack.top();
      if (observer) {
        observer.subscribe(subject, key);
      }

      const subSubject = Subject.of(cache);
      if (Subject.is(subSubject)) {
        subSubject.setParent(subject, key);
      }

      return cache;
    },
    set(value) {
      cache = value;
      subject.notify(key);
    }
  });
}
