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
#include "mir_pragma.h"
#include <iomanip>
#include "mir_nodes.h"
#include "mir_function.h"
#include "printing.h"
#include "maple_string.h"

namespace maple {
static std::string GetKind(PragmaValueType kind) {
  switch (kind) {
    case kValueByte:
      return "i8";
    case kValueShort:
      return "i16";
    case kValueChar:
      return "u16";
    case kValueInt:
      return "i32";
    case kValueLong:
      return "i64";
    case kValueFloat:
      return "f32";
    case kValueDouble:
      return "f64";
    case kValueMethodType:
      return "retype";
    case kValueMethodHandle:
      return "ref";
    case kValueString:
      return "ptr";
    case kValueType:
      return "type";
    case kValueField:
      return "var";
    case kValueMethod:
      return "func";
    case kValueEnum:
      return "enum";
    case kValueArray:
      return "array";
    case kValueAnnotation:
      return "annotation";
    case kValueNull:
      return "const";
    case kValueBoolean:
      return "u1";
    default:
      return "unknown";
  }
}

// status: 0 : unexpected char, stop
//         1 : < start subvec
//         2 : normal type str end with ';'
//         3 : normal type str end with '<' -- need append ';'
//         4 : > end subvec
//         5 : ; ignore and continue
//
//  2: Lfoofoofoofoo;xx  3: Lfoofoofoofoo<
//     |             |      |            |
//     start         end    start        end
static void GetTypeStr(const std::string &str, uint32 &start, uint32 &end, uint32 &status) {
  uint32 i = start;
  status = 0;
  while (str[i] == '[') {
    i++;
  }
  start = i;
  end = i;
  switch (str[i]) {
    case 'Z':
    case 'B':
    case 'S':
    case 'C':
    case 'I':
    case 'J':
    case 'F':
    case 'D':
    case 'V':
      status = 2;
      end = i + 1;
      break;
    case 'L':
    case 'T':
      // Lfoo; or Lfoo<...>;
      while (i < str.length()) {
        if (str[i] == ';') {
          status = 2;
          end = i + 1;
          break;
        } else if (str[i] == '<') {
          status = 3;
          end = i;
          break;
        } else {
          i++;
        }
      }
      break;
    case '<':
      status = 1;
      end = i + 1;
      break;
    case '>':
      status = 4;
      end = i + 1;
      break;
    case ';':
      // continue cases
      status = 5;
      end = i + 1;
      break;
    default:
      // termination - reached unexpected char
      end = i;
      break;
  }
}

MIRPragmaElement *MIRPragma::GetPragmaElemFromSignature(const std::string &signature) {
  if (signature.empty()) {
    return nullptr;
  }
  std::stack<MIRPragmaElement*> elemStack;
  MIRPragmaElement *elem = mod->GetMemPool()->New<MIRPragmaElement>(mod);
  elem->SetType(kValueArray);
  elemStack.push(elem);
  uint32 status = 0;
  uint32 start = 0;
  uint32 end = 0;
  while (1) {
    if (signature.size() <= start) {
      break;
    }
    GetTypeStr(signature, start, end, status);
    // status: 0:stop/1:start_subvec/2:normal/3:normal+';'/4:end_subvec/5:ignore_and_continue
    switch (status) {
      case 0:
        return elem;
      case 1: {
        MIRPragmaElement *etmp = mod->GetMemPool()->New<MIRPragmaElement>(mod);
        etmp->SetType(kValueArray);
        elemStack.top()->PushSubElemVec(etmp);
        elemStack.push(etmp);
        break;
      }
      case 2: {
        MIRPragmaElement *etmp = mod->GetMemPool()->New<MIRPragmaElement>(mod);
        etmp->SetType(kValueType);
        std::string typeStr = signature.substr(start, end - start);
        etmp->SetU64Val((uint64)GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(typeStr).GetIdx());
        elemStack.top()->PushSubElemVec(etmp);
        break;
      }
      case 3: {
        MIRPragmaElement *etmp = mod->GetMemPool()->New<MIRPragmaElement>(mod);
        etmp->SetType(kValueType);
        std::string typeStr = signature.substr(start, end - start) + ";";
        etmp->SetU64Val((uint64)GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(typeStr).GetIdx());
        elemStack.top()->PushSubElemVec(etmp);
        break;
      }
      case 4:
        if (elemStack.empty()) {  // Invalid annotation signature format
          return nullptr;
        }
        elemStack.pop();
        break;
      case 5:
        break;
      default:
        ASSERT(false, "unexpected status");
        break;
    }
    start = end;
  }
  return elem;
}

void MIRPragmaElement::Dump(int indent) {
  GStrIdx gStrIdx;
  std::string str = GetKind(valueType);
  switch (valueType) {
    case kValueByte:
      LogInfo::MapleLogger() << str.c_str() << " " << val.i;
      break;
    case kValueShort:
      LogInfo::MapleLogger() << str.c_str() << " " << val.i;
      break;
    case kValueChar:
      LogInfo::MapleLogger() << str.c_str() << " " << val.u;
      break;
    case kValueInt:
      LogInfo::MapleLogger() << str.c_str() << " " << val.i;
      break;
    case kValueLong:
      LogInfo::MapleLogger() << str.c_str() << " " << val.j;
      break;
    case kValueFloat:
      LogInfo::MapleLogger() << std::setiosflags(std::ios::scientific) << str.c_str() << " " << std::setprecision(7)
                             << val.f << "f";
      break;
    case kValueDouble:
      LogInfo::MapleLogger() << std::setiosflags(std::ios::scientific) << str.c_str() << " " << std::setprecision(16)
                             << val.d;
      break;
    case kValueMethodType:
      LogInfo::MapleLogger() << str.c_str() << " $" << std::hex << "0x" << val.u << std::dec;
      break;
    case kValueMethodHandle:
      LogInfo::MapleLogger() << str.c_str() << " " << std::hex << "0x" << val.u << std::dec;
      break;
    case kValueString:
      gStrIdx.SetIdx(val.u);
      LogInfo::MapleLogger() << str.c_str() << " \"" << GlobalTables::GetStrTable().GetStringFromStrIdx(gStrIdx).c_str()
                             << "\"";
      break;
    case kValueType:
      gStrIdx.SetIdx(val.u);
      LogInfo::MapleLogger() << str.c_str() << " <$" << GlobalTables::GetStrTable().GetStringFromStrIdx(gStrIdx).c_str()
                             << ">";
      break;
    case kValueField:
      gStrIdx.SetIdx(val.u);
      LogInfo::MapleLogger() << str.c_str() << " @" << GlobalTables::GetStrTable().GetStringFromStrIdx(gStrIdx).c_str();
      break;
    case kValueMethod:
      gStrIdx.SetIdx(val.u);
      LogInfo::MapleLogger() << str.c_str() << " &" << GlobalTables::GetStrTable().GetStringFromStrIdx(gStrIdx).c_str();
      break;
    case kValueEnum:
      gStrIdx.SetIdx(val.u);
      LogInfo::MapleLogger() << str.c_str() << " " << GlobalTables::GetStrTable().GetStringFromStrIdx(gStrIdx).c_str();
      break;
    case kValueArray: {
      size_t num = subElemVec.size();
      LogInfo::MapleLogger() << "array [" << num;
      if (num != 0) {
        if (num > 1) {
          LogInfo::MapleLogger() << "," << std::endl;
        } else {
          LogInfo::MapleLogger() << ", ";
        }
        size_t i = 0;
        while (i < num) {
          if (num > 1) {
            PrintIndentation(indent + 2);
          }
          subElemVec[i]->Dump(indent + 2);
          if (i != num - 1) {
            LogInfo::MapleLogger() << "," << std::endl;
          }
          i++;
        }
      }
      LogInfo::MapleLogger() << "]";
      break;
    }
    case kValueAnnotation: {
      size_t num = subElemVec.size();
      LogInfo::MapleLogger() << "annotation <$";
      LogInfo::MapleLogger() << GlobalTables::GetStrTable().GetStringFromStrIdx(typeStrIdx).c_str() << "> [" << num;
      if (num) {
        if (num > 1) {
          LogInfo::MapleLogger() << "," << std::endl;
        } else {
          LogInfo::MapleLogger() << ", ";
        }
        size_t i = 0;
        while (i < num) {
          if (num > 1) {
            PrintIndentation(indent + 2);
          }
          LogInfo::MapleLogger() << "@"
                                 << GlobalTables::GetStrTable().GetStringFromStrIdx(subElemVec[i]->nameStrIdx).c_str()
                                 << " ";
          subElemVec[i]->Dump(indent + 2);
          if (i != num - 1) {
            LogInfo::MapleLogger() << "," << std::endl;
          }
          i++;
        }
      }
      LogInfo::MapleLogger() << "]";
      break;
    }
    case kValueNull:
      LogInfo::MapleLogger() << str.c_str() << " nullptr";
      break;
    case kValueBoolean:
      LogInfo::MapleLogger() << str.c_str() << " " << val.u;
      break;
  }
}

void MIRPragma::Dump(int indent) {
  LogInfo::MapleLogger() << std::endl;
  PrintIndentation(indent);
  LogInfo::MapleLogger() << "pragma " << static_cast<int>(visibility) << " ";
  switch (pragmaKind) {
    case kPragmaClass:
      LogInfo::MapleLogger() << "class $";
      break;
    case kPragmaFunc:
      LogInfo::MapleLogger() << "func &";
      break;
    case kPragmaField:
      LogInfo::MapleLogger() << "var @";
      break;
    case kPragmaVar:
      LogInfo::MapleLogger() << "var %";
      break;
    case kPragmaParam:
      LogInfo::MapleLogger() << "param " << paramNum << " &";
      break;
    case kPragmaFuncExecptioni:
      LogInfo::MapleLogger() << "func_ex &";
      break;
    case kPragmaFuncVar:
      LogInfo::MapleLogger() << "func_var &";
      break;
    default:
      ASSERT(false, "unexpected func kind");
      break;
  }
  LogInfo::MapleLogger() << GlobalTables::GetStrTable().GetStringFromStrIdx(strIdx) << " ";
  GStrIdx gStrIdx = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->GetNameStrIdx();
  if (tyIdxEx.GetIdx() != 0) {
    MIRType *typeEx = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdxEx);
    LogInfo::MapleLogger() << "\"" << typeEx->GetMplTypeName() << "\" ";
  }
  LogInfo::MapleLogger() << "<$" << GlobalTables::GetStrTable().GetStringFromStrIdx(gStrIdx) << "> {";
  for (size_t j = 0; j < elementVec.size(); j++) {
    LogInfo::MapleLogger() << std::endl;
    PrintIndentation(indent + 1);
    MIRPragmaElement *e = elementVec[j];
    gStrIdx = e->GetNameStrIdx();
    LogInfo::MapleLogger() << "@" << GlobalTables::GetStrTable().GetStringFromStrIdx(gStrIdx) << " ";
    e->Dump(indent);
    if (j != elementVec.size() - 1) {
      LogInfo::MapleLogger() << ",";
    }
  }
  LogInfo::MapleLogger() << "}";
  return;
}

}  // namespace maple
