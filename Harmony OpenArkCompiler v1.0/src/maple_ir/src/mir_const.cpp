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
#include "mir_const.h"
#include <iostream>
#include <iomanip>
#include "mir_nodes.h"
#include "mir_function.h"
#include "global_tables.h"
#include "printing.h"
#if MIR_FEATURE_FULL

namespace maple {
void MIRConst::Dump() const {
  if (fieldID) {
    LogInfo::MapleLogger() << fieldID << "= ";
  }
}

void MIRIntConst::Dump() const {
  MIRConst::Dump();
  if (value <= 1024) {
    LogInfo::MapleLogger() << value;
  } else {
    LogInfo::MapleLogger() << std::hex << "0x" << value << std::dec;
  }
}

bool MIRIntConst::operator==(MIRConst &rhs) const {
  if (&rhs == this) {
    return true;
  }
  MIRIntConst *intConst = dynamic_cast<MIRIntConst*>(&rhs);
  return (intConst && (intConst->GetType() == GetType()) && (intConst->value == value));
}

void MIRAddrofConst::Dump() const {
  MIRConst::Dump();
  LogInfo::MapleLogger() << "addrof " << GetPrimTypeName(PTY_ptr);
  ASSERT(stIdx.IsGlobal(), "MIRAddrofConst can only point to a global symbol");
  MIRSymbol *sym = GlobalTables::GetGsymTable().GetSymbolFromStidx(stIdx.Idx());
  LogInfo::MapleLogger() << " $" << sym->GetName();
  if (fldID > 0) {
    LogInfo::MapleLogger() << fldID;
  }
}

bool MIRAddrofConst::operator==(MIRConst &rhs) const {
  if (&rhs == this) {
    return true;
  }
  MIRAddrofConst *rhsA = dynamic_cast<MIRAddrofConst*>(&rhs);
  if (rhsA == nullptr) {
    return false;
  }
  if (GetType() != rhs.GetType()) {
    return false;
  }
  return (stIdx == rhsA->stIdx && fldID == rhsA->fldID);
}

void MIRAddroffuncConst::Dump() const {
  MIRConst::Dump();
  LogInfo::MapleLogger() << "addroffunc " << GetPrimTypeName(PTY_ptr);
  MIRFunction *func = GlobalTables::GetFunctionTable().GetFunctionFromPuidx(puIdx);
  LogInfo::MapleLogger() << " &" << GlobalTables::GetGsymTable().GetSymbolFromStidx(func->GetStIdx().Idx())->GetName();
}

bool MIRAddroffuncConst::operator==(MIRConst &rhs) const {
  if (&rhs == this) {
    return true;
  }
  MIRAddroffuncConst *rhsAf = dynamic_cast<MIRAddroffuncConst*>(&rhs);
  if (rhsAf == nullptr) {
    return false;
  }
  return (GetType() == rhs.GetType() && puIdx == rhsAf->puIdx);
}

bool MIRLblConst::operator==(MIRConst &rhs) const {
  if (&rhs == this) {
    return true;
  }
  MIRLblConst *lblConst = dynamic_cast<MIRLblConst*>(&rhs);
  return (lblConst && (lblConst->value == value));
}

bool MIRFloatConst::operator==(MIRConst &rhs) const {
  if (&rhs == this) {
    return true;
  }
  MIRFloatConst *floatConst = dynamic_cast<MIRFloatConst*>(&rhs);
  if (floatConst == nullptr) {
    return false;
  }
  if (std::isnan(floatConst->value.floatValue)) {
    return std::isnan(value.floatValue);
  }
  if (std::isnan(value.floatValue)) {
    return std::isnan(floatConst->value.floatValue);
  }
  return (fabs(floatConst->value.floatValue - value.floatValue) <= 1e-6);
}

bool MIRDoubleConst::operator==(MIRConst &rhs) const {
  if (&rhs == this) {
    return true;
  }
  MIRDoubleConst *floatConst = dynamic_cast<MIRDoubleConst*>(&rhs);
  if (floatConst == nullptr) {
    return false;
  }
  if (std::isnan(floatConst->value.dValue)) {
    return std::isnan(value.dValue);
  }
  if (std::isnan(value.dValue)) {
    return std::isnan(floatConst->value.dValue);
  }
  return (fabs(floatConst->value.dValue - value.dValue) <= 1e-15);
}

bool MIRFloat128Const::operator==(MIRConst &rhs) const {
  if (&rhs == this) {
    return true;
  }
  MIRFloat128Const *floatConst = dynamic_cast<MIRFloat128Const*>(&rhs);
  if (floatConst == nullptr) {
    return false;
  }
  if ((value[0] == floatConst->value[0]) && (value[1] == floatConst->value[1])) {
    return true;
  }
  return false;
}

bool MIRAggConst::operator==(MIRConst &rhs) const {
  if (&rhs == this) {
    return true;
  }
  MIRAggConst *aggregateConst = dynamic_cast<MIRAggConst*>(&rhs);
  if (aggregateConst == nullptr) {
    return false;
  }
  if (aggregateConst->constVec.size() != constVec.size()) {
    return false;
  }
  for (size_t i = 0; i < constVec.size(); ++i) {
    if (!(*aggregateConst->constVec[i] == *constVec[i])) {
      return false;
    }
  }
  return true;
}

void MIRFloatConst::Dump() const {
  MIRConst::Dump();
  LogInfo::MapleLogger() << std::setprecision(std::numeric_limits<float>::max_digits10) << value.floatValue << "f";
}

void MIRDoubleConst::Dump() const {
  MIRConst::Dump();
  LogInfo::MapleLogger() << std::setprecision(std::numeric_limits<double>::max_digits10) << value.dValue;
}

void MIRFloat128Const::Dump() const {
  MIRConst::Dump();
  std::ios::fmtflags f(LogInfo::MapleLogger().flags());
  LogInfo::MapleLogger().setf(std::ios::uppercase);
  LogInfo::MapleLogger() << "0xL" << std::hex << std::setfill('0') << std::setw(16) << value[0] << std::setfill('0')
                         << std::setw(16) << value[1];
  LogInfo::MapleLogger().flags(f);
}

void MIRAggConst::Dump() const {
  MIRConst::Dump();
  LogInfo::MapleLogger() << "[";
  size_t size = constVec.size();
  for (size_t i = 0; i < size; i++) {
    constVec[i]->Dump();
    if (i != size - 1) {
      LogInfo::MapleLogger() << ", ";
    }
  }
  LogInfo::MapleLogger() << "]";
}

MIRStrConst::MIRStrConst(const std::string &str, MIRType *type)
    : MIRConst(type), value(GlobalTables::GetUStrTable().GetOrCreateStrIdxFromName(str)) {
  SetKind(kConstStrConst);
}

void MIRStrConst::Dump() const {
  MIRConst::Dump();
  LogInfo::MapleLogger() << "conststr " << GetPrimTypeName(GetType()->GetPrimType());
  const std::string kStr = GlobalTables::GetUStrTable().GetStringFromStrIdx(value);
  PrintString(kStr);
}

bool MIRStrConst::operator==(MIRConst &rhs) const {
  if (&rhs == this) {
    return true;
  }
  MIRStrConst *rhsCs = dynamic_cast<MIRStrConst*>(&rhs);
  if (rhsCs == nullptr) {
    return false;
  }
  return (GetType() == rhs.GetType() && value == rhsCs->value);
}

MIRStr16Const::MIRStr16Const(const std::u16string &str, MIRType *type)
    : MIRConst(type), value(GlobalTables::GetU16StrTable().GetOrCreateStrIdxFromName(str)) {
  SetKind(kConstStr16Const);
}

void MIRStr16Const::Dump() const {
  MIRConst::Dump();
  LogInfo::MapleLogger() << "conststr16 " << GetPrimTypeName(GetType()->GetPrimType());
  std::u16string str16 = GlobalTables::GetU16StrTable().GetStringFromStrIdx(value);
  // UTF-16 string are dumped as UTF-8 string in mpl to keep the printable chars in ascii form
  std::string str;
  NameMangler::UTF16ToUTF8(str, str16);
  PrintString(str);
}

bool MIRStr16Const::operator==(MIRConst &rhs) const {
  if (&rhs == this) {
    return true;
  }
  MIRStr16Const *rhsCs = dynamic_cast<MIRStr16Const*>(&rhs);
  if (rhsCs == nullptr) {
    return false;
  }
  return (GetType() == rhs.GetType() && value == rhsCs->value);
}

}  // namespace maple
#endif  // MIR_FEATURE_FULL
