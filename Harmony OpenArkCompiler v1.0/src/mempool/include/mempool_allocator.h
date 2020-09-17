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
#ifndef MEMPOOL_INCLUDE_MEMPOOL_ALLOCATOR_H
#define MEMPOOL_INCLUDE_MEMPOOL_ALLOCATOR_H
#include <stddef.h>
#include <limits>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <forward_list>
#include "mempool.h"

namespace maple {
template <typename T>
class MapleAllocatorAdapter;
class MapleAllocator {
 public:
  explicit MapleAllocator(MemPool *m) : memPool(m) {}

  virtual ~MapleAllocator() {}

  // Get adapter for use in STL containers. See arena_containers.h .
  MapleAllocatorAdapter<void> Adapter();
  void *Alloc(size_t bytes) {
    return (memPool ? memPool->Malloc(bytes) : nullptr);
  }

  MemPool *GetMemPool() {
    return memPool;
  }

  void SetMemPool(MemPool *m) {
    memPool = m;
  }

 private:
  MemPool *memPool;
  template <typename U>
  friend class MapleAllocatorAdapter;
};  // MapleAllocator

template <typename T>
class MapleAllocatorAdapter;
template <typename T>
using MapleQueue = std::deque<T, MapleAllocatorAdapter<T>>;
template <typename T>
using MapleVector = std::vector<T, MapleAllocatorAdapter<T>>;
template <typename T>
class MapleStack {
 public:
  using size_type = typename MapleVector<T>::size_type;
  using iterator = typename MapleVector<T>::iterator;

 public:
  MapleStack(MapleAllocatorAdapter<T> adapter) : vect(adapter) {}

  ~MapleStack() = default;

  MapleVector<T> &GetVector() {
    return vect;
  }

  bool empty() const {
    return vect.empty();
  }

  size_type size() const {
    return vect.size();
  }

  iterator begin() {
    return vect.begin();
  }

  iterator end() {
    return vect.end();
  }

  void push(T x) {
    vect.push_back(x);
  }

  void pop() {
    vect.pop_back();
  }

  T top() {
    return vect.back();
  }

  void clear() {
    vect.resize(0);
  }

 private:
  MapleVector<T> vect;
};

template <typename T>
using MapleList = std::list<T, MapleAllocatorAdapter<T>>;
template <typename T>
using MapleForwardList = std::forward_list<T, MapleAllocatorAdapter<T>>;
template <typename T, typename Comparator = std::less<T>>
using MapleSet = std::set<T, Comparator, MapleAllocatorAdapter<T>>;
template <typename T, typename Hash = std::hash<T>, typename Equal = std::equal_to<T>>
using MapleUnorderedSet = std::unordered_set<T, Hash, Equal, MapleAllocatorAdapter<T>>;
template <typename K, typename V, typename Comparator = std::less<K>>
using MapleMap = std::map<K, V, Comparator, MapleAllocatorAdapter<std::pair<const K, V>>>;
template <typename K, typename V, typename Comparator = std::less<K>>
using MapleMultiMap = std::multimap<K, V, Comparator, MapleAllocatorAdapter<std::pair<const K, V>>>;
template <typename K, typename V, typename Hash = std::hash<K>, typename Equal = std::equal_to<K>>
using MapleUnorderedMap = std::unordered_map<K, V, Hash, Equal, MapleAllocatorAdapter<std::pair<const K, V>>>;
template <typename K, typename V, typename Hash = std::hash<K>, typename Equal = std::equal_to<K>>
using MapleUnorderedMultiMap = std::unordered_multimap<K, V, Hash, Equal, MapleAllocatorAdapter<std::pair<const K, V>>>;
// Implementation details below.
template <>
class MapleAllocatorAdapter<void> {
 public:
  using value_type = void;
  using pointer = void*;
  using const_pointer = const void*;
  template <typename U>
  struct rebind {
    using other = MapleAllocatorAdapter<U>;
  };

  explicit MapleAllocatorAdapter(MapleAllocator *currMapleAllocator) : mapleAllocator(currMapleAllocator) {}

  template <typename U>
  MapleAllocatorAdapter(const MapleAllocatorAdapter<U> &other) : mapleAllocator(other.mapleAllocator) {}

  MapleAllocatorAdapter(const MapleAllocatorAdapter &other) = default;
  MapleAllocatorAdapter &operator=(const MapleAllocatorAdapter &other) = default;
  ~MapleAllocatorAdapter() = default;

 private:
  MapleAllocator *mapleAllocator;
  template <typename U>
  friend class MapleAllocatorAdapter;
};

template <typename T>
class MapleAllocatorAdapter {
 public:
  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using const_pointer = const T*;
  using const_reference = const T&;
  using size_type = size_t;
  using difference_type = std::ptrdiff_t;
  template <typename U>
  struct rebind {
    using other = MapleAllocatorAdapter<U>;
  };

  explicit MapleAllocatorAdapter(MapleAllocator *currMapleAllocator) : mapleAllocator(currMapleAllocator) {}

  template <typename U>
  MapleAllocatorAdapter(const MapleAllocatorAdapter<U> &other) : mapleAllocator(other.mapleAllocator) {}

  MapleAllocatorAdapter(const MapleAllocatorAdapter &other) = default;
  MapleAllocatorAdapter &operator=(const MapleAllocatorAdapter &other) = default;
  ~MapleAllocatorAdapter() = default;
  size_type max_size() const {
    return static_cast<size_type>(-1) / sizeof(T);
  }

  pointer address(reference x) const {
    return &x;
  }

  const_pointer address(const_reference x) const {
    return &x;
  }

  pointer allocate(size_type n, MapleAllocatorAdapter<void>::pointer hint = nullptr) {
    return reinterpret_cast<T*>(mapleAllocator->Alloc(n * sizeof(T)));
  }

  void deallocate(pointer p, size_type n) {}

  void construct(const pointer p, const_reference val) {
    new (static_cast<void*>(p)) value_type(val);
  }

  void destroy(const pointer p) {
    p->~value_type();
  }

 private:
  MapleAllocator *mapleAllocator;
  template <typename U>
  friend class MapleAllocatorAdapter;
  template <typename U>
  friend bool operator==(const MapleAllocatorAdapter<U> &lhs, const MapleAllocatorAdapter<U> &rhs);
};

template <typename T>
inline bool operator==(const MapleAllocatorAdapter<T> &lhs, const MapleAllocatorAdapter<T> &rhs) {
  return lhs.mapleAllocator == rhs.mapleAllocator;
}

template <typename T>
inline bool operator!=(const MapleAllocatorAdapter<T> &lhs, const MapleAllocatorAdapter<T> &rhs) {
  return !(lhs == rhs);
}

inline MapleAllocatorAdapter<void> MapleAllocator::Adapter() {
  return MapleAllocatorAdapter<void>(this);
}

}  // namespace maple
#endif  // MEMPOOL_INCLUDE_MEMPOOL_ALLOCATOR_H
