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
import ViewModel from '..';

describe('ViewModel', () => {
  test('01_proxy_data', () => {
    const options = { data: { count: 1 } };
    const vm = new ViewModel(options);
    expect(vm.count).toBe(options.data.count);
    vm.count = 2;
    expect(options.data.count).toBe(2);
  });
  test('02_data_type', () => {
    const as1 = new ViewModel({ data: { count: 1 } });
    const as2 = new ViewModel({
      data() {
        return { count: 2 };
      },
    });
    expect(as1.count).toBe(1);
    expect(as2.count).toBe(2);
  });
  test('03_handler', () => {
    const vm = new ViewModel({
      data() {
        return { count: 1 };
      },
      increase() {
        ++this.count;
      },
      decrease() {
        --this.count;
      },
    });
    expect(typeof vm.increase).toBe('function');
    expect(typeof vm.decrease).toBe('function');
    vm.increase();
    expect(vm.count).toBe(2);
    vm.decrease();
    expect(vm.count).toBe(1);
  });
  test('04_watch_basic_usage', (done) => {
    const vm = new ViewModel({
      data: function () {
        return { count: 1 };
      },
      increase() {
        ++this.count;
      },
      decrease() {
        --this.count;
      },
    });
    expect(vm.count).toBe(1);
    const watcher = vm.$watch(
      () => vm.count,
      (value) => {
        expect(value).toBe(2);
        watcher.unsubscribe();
        done();
      }
    );
    vm.increase();
  });
  test('05_watch_nested_object', (done) => {
    const vm = new ViewModel({
      data: function () {
        return { user: { name: 'Chen' } };
      },

      setName(name) {
        this.user.name = name;
      },
    });

    const watcher = vm.$watch(
      () => vm.user.name,
      (name) => {
        expect(name).toBe('Chen2');
        watcher.unsubscribe();
        done();
      }
    );

    vm.setName('Chen2');
  });
  test('06_watch_array', (done) => {
    const vm = new ViewModel({
      data: function () {
        return { cities: ['HangZhou'] };
      },
      add(city) {
        this.cities.push(city);
      },
    });

    const watcher = vm.$watch(
      () => vm.cities,
      (value) => {
        expect(value.length).toBe(2);
        expect(value[1]).toBe('ShenZhen');
        watcher.unsubscribe();
        done();
      }
    );

    vm.add('ShenZhen');
  });
  test('07_observed_array_push', (done) => {
    const vm = new ViewModel({
      data: {
        address: [],
      },
    });

    const watcher = vm.$watch(
      () => vm.address[0],
      (value) => {
        expect(value).toBe('BeiJing');
        watcher.unsubscribe();
        done();
      }
    );

    vm.address.push('BeiJing');
  });
  test('08_observed_array_pop', (done) => {
    const vm = new ViewModel({
      data: {
        address: ['HangZhou', 'BeiJing'],
      },
    });

    const watcher = vm.$watch(
      () => vm.address[1],
      (value) => {
        expect(value).toBeUndefined();
        watcher.unsubscribe();
        done();
      }
    );

    vm.address.pop();
  });
  test('09_observed_array_unshift', (done) => {
    const vm = new ViewModel({
      data: {
        address: [],
      },
    });

    const watcher = vm.$watch(
      () => vm.address[0],
      (value) => {
        expect(value).toBe('HangZhou');
        watcher.unsubscribe();
        done();
      }
    );

    vm.address.unshift('HangZhou');
  });
  test('10_observed_array_shift', (done) => {
    const vm = new ViewModel({
      data: {
        address: ['BeiJing', 'HangZhou'],
      },
    });

    const watcher = vm.$watch(
      () => vm.address[0],
      (value) => {
        expect(value).toBe('HangZhou');
        watcher.unsubscribe();
        done();
      }
    );

    vm.address.shift();
  });
  test('11_observed_array_splice', (done) => {
    const vm = new ViewModel({
      data: {
        address: ['BeiJing', 'HangZhou'],
      },
    });

    const watcher = vm.$watch(
      () => vm.address[0],
      (value) => {
        expect(value).toBe('ShenZhen');
        watcher.unsubscribe();
        done();
      }
    );

    vm.address.splice(0, 1, 'ShenZhen');
  });
  test('12_observed_array_splice', (done) => {
    const vm = new ViewModel({
      data: {
        address: ['BeiJing', 'HangZhou'],
      },
    });

    vm.$watch(
      () => vm.address[0],
      (value) => {
        expect(value).toBe('HangZhou');
        done();
      }
    );

    vm.address.reverse();
  });
  test('13_watch_multidimensional_array', (done) => {
    const vm = new ViewModel({
      data: function () {
        return {
          numbers: [
            [0, 0, 0, 2],
            [0, 0, 0, 0],
            [0, 0, 0, 0],
            [0, 0, 0, 0],
          ],
        };
      },
    });

    const watcher = vm.$watch(
      () => vm.numbers[0][0],
      (value) => {
        expect(value).toBe(4);
        watcher.unsubscribe();
        done();
      }
    );

    vm.numbers[0].splice(0, 1, 4);
  });
  test('14_watch_multidimensional_array', (done) => {
    const vm = new ViewModel({
      data: function () {
        return {
          numbers: [
            [0, 0, 0, 2],
            [0, 0, 0, 0],
            [0, 0, 0, 0],
            [0, 0, 0, 0],
          ],
        };
      },
    });

    const watcher = vm.$watch(
      () => vm.numbers[0][0],
      (value) => {
        expect(value).toBe(4);
        watcher.unsubscribe();
        done();
      }
    );

    vm.numbers.splice(0, 1, [4, 4, 4, 4]);
  });
  test('15_change_array_by_index', (done) => {
    const vm = new ViewModel({
      data: {
        users: ['Jack', 'Mike'],
      },
    });

    const watcher = vm.$watch(
      () => vm.users[0],
      (value) => {
        expect(value).toBe('Enzo');
        watcher.unsubscribe();
        done();
      }
    );

    vm.users[0] = 'Enzo';
  });
  test('15_watch_object_array', (done) => {
    const vm = new ViewModel({
      data: {
        users: [],
      },
    });

    const watcher = vm.$watch(
      () => vm.users[0],
      (user) => {
        expect(user.name).toEqual('Jack');
        watcher.unsubscribe();
      }
    );
    vm.users.push({ name: 'Jack' });

    const watcher2 = vm.$watch(
      () => vm.users[0] && vm.users[0].name,
      (name) => {
        expect(name).toEqual('Enzo');
        watcher2.unsubscribe();
        done();
      }
    );

    vm.users[0].name = 'Enzo';
  });
  test('99_lifecycle', () => {
    const onInit = jest.fn().mockReturnValue('onInit');
    const onReady = jest.fn().mockReturnValue('onReady');
    const onShow = jest.fn().mockReturnValue('onShow');
    const onDestroy = jest.fn().mockReturnValue('onDestroy');
    const onDataChange = jest.fn().mockReturnValue('onDataChange');

    const vm = new ViewModel({
      onInit,
      onReady,
      onShow,
      onDestroy,
      onDataChange,
    });

    expect(vm.onInit()).toBe('onInit');
    expect(vm.onDataChange()).toBe('onDataChange');
    expect(vm.onReady()).toBe('onReady');
    expect(vm.onShow()).toBe('onShow');
    expect(vm.onDestroy()).toBe('onDestroy');

    expect(onInit.mock.instances[0]).toBe(vm);
    expect(onDataChange.mock.instances[0]).toBe(vm);
    expect(onReady.mock.instances[0]).toBe(vm);
    expect(onShow.mock.instances[0]).toBe(vm);
    expect(onDestroy.mock.instances[0]).toBe(vm);
  });
});
