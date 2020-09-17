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
#ifndef MAPLE_IR_INCLUDE_PRIM_TYPES_H
#define MAPLE_IR_INCLUDE_PRIM_TYPES_H
#include "types_def.h"
#include "cfg_primitive_types.h"

namespace maple {

class PrimitiveType {
 public:
  PrimitiveType(PrimType type) {
    property = &GetPrimitiveTypeProperty(type);
  }
  ~PrimitiveType() = default;

  PrimType GetType() const {
    return property->type;
  }

  bool IsInteger() const {
    return property->isInteger;
  }
  bool IsUnsigned() const {
    return property->isUnsigned;
  }
  bool IsAddress() const {
    return property->isAddress;
  }
  bool IsFloat() const {
    return property->isFloat;
  }
  bool IsPointer() const {
    return property->isPointer;
  }
  bool IsDynamic() const {
    return property->isDynamic;
  }
  bool IsSimple() const {
    return property->isSimple;
  }
  bool IsDynamicAny() const {
    return property->isDynamicAny;
  }
  bool IsDynamicNone() const {
    return property->isDynamicNone;
  }

 private:
  const PrimitiveTypeProperty *property;
};

}  // namespace maple
#endif  // MAPLE_IR_INCLUDE_PRIM_TYPES_H
