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
#include "intrinsics.h"
#include "mir_module.h"
#include "mir_type.h"
#include "mir_builder.h"

namespace maple {
MIRType *IntrinDesc::jsValueType = nullptr;
MIRModule *IntrinDesc::mirModule = nullptr;
IntrinDesc IntrinDesc::intrinTable[INTRN_LAST + 1] = {
#define DEF_MIR_INTRINSIC(X, NAME, INTRN_CLASS, RETURN_TYPE, ...) \
  { (NAME), (INTRN_CLASS), { (RETURN_TYPE), ##__VA_ARGS__ } },
#include "intrinsics.def"
#undef DEF_MIR_INTRINSIC
};
MIRType *IntrinDesc::GetOrCreateJSValueType() {
  if (jsValueType != nullptr) {
    return jsValueType;
  }
  MIRBuilder *jsBuilder = mirModule->GetMIRBuilder();
  FieldVector payloadFields;
  GStrIdx i32 = jsBuilder->GetOrCreateStringIndex("i32");
  GStrIdx u32 = jsBuilder->GetOrCreateStringIndex("u32");
  GStrIdx boo = jsBuilder->GetOrCreateStringIndex("boo");
  GStrIdx ptr = jsBuilder->GetOrCreateStringIndex("ptr");
  payloadFields.push_back(
      FieldPair(i32, TyIdxFieldAttrPair(GlobalTables::GetTypeTable().GetInt32()->GetTypeIndex(), FieldAttrs())));
  payloadFields.push_back(
      FieldPair(u32, TyIdxFieldAttrPair(GlobalTables::GetTypeTable().GetUInt32()->GetTypeIndex(), FieldAttrs())));
  payloadFields.push_back(
      FieldPair(boo, TyIdxFieldAttrPair(GlobalTables::GetTypeTable().GetUInt32()->GetTypeIndex(), FieldAttrs())));
  payloadFields.push_back(
      FieldPair(ptr, TyIdxFieldAttrPair(GlobalTables::GetTypeTable().GetVoidPtr()->GetTypeIndex(), FieldAttrs())));
  FieldVector parentFields;
  MIRType *payloadType =
      GlobalTables::GetTypeTable().GetOrCreateUnionType("payload_type", payloadFields, parentFields, mirModule);
  FieldVector sFields;
  GStrIdx payload = jsBuilder->GetOrCreateStringIndex("payload");
  GStrIdx tag = jsBuilder->GetOrCreateStringIndex("tag");
  sFields.push_back(FieldPair(payload, TyIdxFieldAttrPair(payloadType->GetTypeIndex(), FieldAttrs())));
  sFields.push_back(
      FieldPair(tag, TyIdxFieldAttrPair(GlobalTables::GetTypeTable().GetUInt32()->GetTypeIndex(), FieldAttrs())));
  MIRType *sType = GlobalTables::GetTypeTable().GetOrCreateStructType("s_type", sFields, parentFields, mirModule);
  CHECK_FATAL(sType != nullptr, "can't get struct type, check it!");
  FieldVector jsValLayoutFields;
  GStrIdx asBits = jsBuilder->GetOrCreateStringIndex("asBits");
  GStrIdx s = jsBuilder->GetOrCreateStringIndex("s");
  GStrIdx asDouble = jsBuilder->GetOrCreateStringIndex("asDouble");
  GStrIdx asPtr = jsBuilder->GetOrCreateStringIndex("asPtr");
  jsValLayoutFields.push_back(
      FieldPair(asBits, TyIdxFieldAttrPair(GlobalTables::GetTypeTable().GetUInt64()->GetTypeIndex(), FieldAttrs())));
  jsValLayoutFields.push_back(FieldPair(s, TyIdxFieldAttrPair(sType->GetTypeIndex(), FieldAttrs())));
  jsValLayoutFields.push_back(
      FieldPair(asDouble, TyIdxFieldAttrPair(GlobalTables::GetTypeTable().GetDouble()->GetTypeIndex(), FieldAttrs())));
  jsValLayoutFields.push_back(
      FieldPair(asPtr, TyIdxFieldAttrPair(GlobalTables::GetTypeTable().GetVoidPtr()->GetTypeIndex(), FieldAttrs())));
  MIRType *jsValLayoutType = GlobalTables::GetTypeTable().GetOrCreateUnionType("jsval_layout_type", jsValLayoutFields,
                                                                               parentFields, mirModule);
  return jsValLayoutType;
}

void IntrinDesc::InitMIRModule(MIRModule *mod) {
  mirModule = mod;
}

MIRType *IntrinDesc::GetTypeFromArgTy(IntrinArgType argtype) const {
  switch (argtype) {
    case kArgTyVoid:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_void);
    case kArgTyI8:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_i8);
    case kArgTyI16:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_i16);
    case kArgTyI32:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_i32);
    case kArgTyI64:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_i64);
    case kArgTyU8:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_u8);
    case kArgTyU16:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_u16);
    case kArgTyU32:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_u32);
    case kArgTyU64:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_u64);
    case kArgTyU1:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_u1);
    case kArgTyPtr:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_ptr);
    case kArgTyRef:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_ref);
    case kArgTyA32:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_a32);
    case kArgTyA64:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_a64);
    case kArgTyF32:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_f32);
    case kArgTyF64:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_f64);
    case kArgTyF128:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_f128);
    case kArgTyC64:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_c64);
    case kArgTyC128:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_c128);
    case kArgTyAgg:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_agg);
#ifdef DYNAMICLANG
    case kArgTySimplestr:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_simplestr);
    case kArgTySimpleobj:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_simpleobj);
    case kArgTyDynany:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_dynany);
    case kArgTyDyni32:
      return GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_dyni32);
#endif
    default:
      return nullptr;
  }
}

MIRType *IntrinDesc::GetArgType(uint32 index) const {
  // 0 is the arg of return type
  CHECK_FATAL(index < kMaxArgsNum, "index out of range");
  return GetTypeFromArgTy(argTypes[index + 1]);
}

MIRType *IntrinDesc::GetReturnType() const {
  return GetTypeFromArgTy(argTypes[0]);
}

}  // namespace maple
