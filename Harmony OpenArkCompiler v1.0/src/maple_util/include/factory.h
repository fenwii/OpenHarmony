/*
 * Copyright (c) [2019] Huawei Technologies Co.,Ltd.All rights reserved.
 *
 * OpenArkCompiler is licensed under the Mulan PSL v1.
 * You can use this software according to the terms and conditions of the Mulan PSL v1.
 * You may obtain a copy of Mulan PSL v1 at:
 *
 *     http://license.coscl.org.cn/MulanPSL
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR
 * FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v1 for more details.
 */
#ifndef MAPLE_UTIL_INCLUDE_FACTORY_H
#define MAPLE_UTIL_INCLUDE_FACTORY_H
#include <map>
#include <memory>
#include <functional>

namespace maple {

template <typename TKey, typename TObject, typename... TArgs>
class ObjectFactory {
  using PtrObject = std::unique_ptr<TObject>;
  using CreatFunc = std::function<PtrObject(TArgs...)>;
  using CreatorHolder = std::map<TKey, CreatFunc>;

 public:
  using Key = TKey;
  using Value = TObject;

  void Register(const TKey &key, CreatFunc func) {
    auto it = objectCreator.find(key);
    if (it == objectCreator.end()) {
      objectCreator[key] = func;
    }
  }

  std::unique_ptr<TObject> Create(const TKey &key, TArgs... Args) const {
    auto it = objectCreator.find(key);
    return it == objectCreator.end() ? PtrObject() : (it->second)(Args...);
  }

  template <typename TObjectImpl>
  static PtrObject DefaultCreator(TArgs... Args) {
    return PtrObject(new TObjectImpl(Args...));
  }

  static ObjectFactory &ins() {
    static ObjectFactory factory;
    return factory;
  }

 private:
  ObjectFactory() = default;
  ~ObjectFactory() = default;
  ObjectFactory(const ObjectFactory&) = delete;
  ObjectFactory(const ObjectFactory&&) = delete;
  ObjectFactory &operator=(const ObjectFactory&) = delete;
  ObjectFactory &operator=(const ObjectFactory&&) = delete;

 private:
  CreatorHolder objectCreator;
};

template <typename TFactory, typename TFactory::key TKey, typename TObjectImpl>
inline bool RegisterFactoryObject() {
  TFactory::ins().Register(TKey, TFactory::template DefaultCreator<TObjectImpl>);
  return true;
}

template <typename TFactory, typename... TArgs>
inline auto CreateProductObject(const typename TFactory::key &Key, TArgs... Args)
    -> std::unique_ptr<typename TFactory::value> {
  return TFactory::ins().Create(Key, Args...);
}

template <typename TKey, typename TRet, typename... TArgs>
class FunctionFactory {
  using FuncObject = std::function<TRet(TArgs...)>;
  using FuncHolder = std::map<TKey, FuncObject>;

 public:
  using Key = TKey;
  using Value = FuncObject;

  void Register(const TKey &key, FuncObject func) {
    auto it = funcCreator.find(key);
    if (it == funcCreator.end()) {
      funcCreator[key] = func;
    }
  }

  FuncObject Create(const TKey &key) const {
    auto it = funcCreator.find(key);
    if (it == funcCreator.end()) {
      return nullptr;
    }
    return it->second;
  }

  static FunctionFactory &ins() {
    static FunctionFactory factory;
    return factory;
  }

 private:
  FunctionFactory() = default;
  ~FunctionFactory() = default;
  FunctionFactory(const FunctionFactory&) = delete;
  FunctionFactory(const FunctionFactory&&) = delete;
  FunctionFactory &operator=(const FunctionFactory&) = delete;
  FunctionFactory &operator=(const FunctionFactory&&) = delete;

 private:
  FuncHolder funcCreator;
};

template <typename TFactory>
inline void RegisterFactoryFunction(const typename TFactory::Key &key, typename TFactory::Value func) {
  TFactory::ins().Register(key, func);
}

template <typename TFactory>
inline auto CreateProductFunction(const typename TFactory::Key &key) -> typename TFactory::Value {
  return TFactory::ins().Create(key);
}

}  // namespace maple

#endif  // MAPLE_UTIL_INCLUDE_FACTORY_H
