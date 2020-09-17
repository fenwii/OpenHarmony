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
#ifndef MAPLE_UTIL_INCLUDE_STRING_UTILS_H
#define MAPLE_UTIL_INCLUDE_STRING_UTILS_H
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <regex>

namespace maple {
class StringUtils {
 public:
  template <class Container>
  static void Split(const std::string &src, Container &container, char delim) {
    if (Trim(src).empty()) {
      return;
    }

    std::stringstream strStream(src);
    std::string item;
    while (std::getline(strStream, item, delim)) {
      container.emplace_back(item);
    }
  }

  static void Split(const std::string &src, std::unordered_set<std::string> &container, char delim);

  const static std::string Trim(const std::string &s);
  const static std::string Replace(const std::string &src, const std::string &target, const std::string &replacement);
  const static std::string Append(const std::string &src, const std::string &target, const std::string &spliter);
  const static std::string GetStrAfterLast(const std::string &src, const std::string &target,
                                           const bool isReturnEmpty = false);
  const static std::string GetStrBeforeLast(const std::string &src, const std::string &target,
                                            const bool isReturnEmpty = false);
  static bool HasCommandInjectionChar(const std::string &s) {
    return std::regex_search(s, kCommandInjectionRegex);
  }

  const static bool EndsWith(const std::string &str, const std::string &end) {
    if (end.size() > str.size()) {
      return false;
    }

    return std::equal(end.rbegin(), end.rend(), str.rbegin());
  }

  const static bool StartsWith(const std::string &str, const std::string &start) {
    if (start.size() > str.size()) {
      return false;
    }

    return std::equal(start.cbegin(), start.cend(), str.cbegin());
  }

 private:
  static std::regex kCommandInjectionRegex;
};

}  // namespace maple
#endif  // MAPLE_UTIL_INCLUDE_STRING_UTILS_H
