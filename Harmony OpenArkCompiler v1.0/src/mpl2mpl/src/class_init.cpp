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
#include "class_init.h"
#include <iostream>
#include <fstream>

// This phase does two things.
// 1. Insert clinit(class initialization) check, a intrinsic call INTRN_MPL_CLINIT_CHECK
//   for place where needed.
//   Insert clinit check for static native methods which are not private.
// 2. Lower JAVA_CLINIT_CHECK to MPL_CLINIT_CHECK.

namespace maple {
ClassInit::ClassInit(MIRModule *mod, KlassHierarchy *kh, bool dump) : FuncOptimizeImpl(mod, kh, dump) {
}


bool ClassInit::CanRemoveClinitCheck(const std::string &clinitClassname) {
  return false;
}

#undef CLINIT_CHECK
void ClassInit::GenClassInitCheckProfile(MIRFunction *func, MIRSymbol *classinfo, StmtNode *clinit) const {
#ifdef CLINIT_CHECK
  GenPreClassInitCheck(func, classinfo, clinit);
  GenPostClassInitCheck(func, classinfo, clinit);
#endif  // CLINIT_CHECK
}

void ClassInit::GenPreClassInitCheck(MIRFunction *func, const MIRSymbol *classinfo, StmtNode *clinit) {
  MIRFunction *preClinit = builder->GetOrCreateFunction(kMCCPreClinitCheck, (TyIdx)(PTY_void));
  BaseNode *classInfoNode = builder->CreateExprAddrof(0, classinfo);
  MapleVector<BaseNode*> args(builder->GetCurrentFuncCodeMpAllocator()->Adapter());
  args.push_back(classInfoNode);
  CallNode *callPreclinit = builder->CreateStmtCall(preClinit->GetPuidx(), args);
  func->GetBody()->InsertBefore(clinit, callPreclinit);
}

void ClassInit::GenPostClassInitCheck(MIRFunction *func, const MIRSymbol *classinfo, StmtNode *clinit) {
  MIRFunction *postClinit = builder->GetOrCreateFunction(kMCCPostClinitCheck, (TyIdx)(PTY_void));
  BaseNode *classInfoNode = builder->CreateExprAddrof(0, classinfo);
  MapleVector<BaseNode*> args(builder->GetCurrentFuncCodeMpAllocator()->Adapter());
  args.push_back(classInfoNode);
  CallNode *callPostclinit = builder->CreateStmtCall(postClinit->GetPuidx(), args);
  func->GetBody()->InsertAfter(clinit, callPostclinit);
}

void ClassInit::ProcessFunc(MIRFunction *func) {
  // No field will be involved in critical native funcs.
  if (func->IsEmpty() || func->GetAttr(FUNCATTR_critical_native)) {
    return;
  }
  currFunc = func;
  builder->SetCurrentFunction(func);
  // Insert clinit check for static methods.
  MIRType *selfClassType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(func->GetClassTyIdx());
  std::string selfClassName;
  if (selfClassType != nullptr) {
    selfClassName = GlobalTables::GetStrTable().GetStringFromStrIdx(selfClassType->GetNameStrIdx());
  } else {
    const std::string &funcName = func->GetName();
    size_t pos = funcName.find(NameMangler::kNameSplitterStr);
    while (pos != std::string::npos && (pos >= 2 && funcName[pos - 1] == '_' && funcName[pos - 2] != '_')) {
      pos = funcName.find(NameMangler::kNameSplitterStr, pos + 3);
    }
    selfClassName = funcName.substr(0, pos);
  }
  // Insert clinit check for static native methods which are not private.
  // We have to do this here because native methods are generated as empty by maplefe,
  // If we simply insert clinit-check (which does not have return value), there will
  // be no return statement for native methods which do hava a return value.
  // clinit check for static java (non-native) methods which are not private is
  // already inserted by maplefe.
  if (func->IsStatic() && !func->IsPrivate() && !func->IsClinit() && func->IsNative()) {
    MIRType *classType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(func->GetClassTyIdx());
    CHECK_FATAL(classType != nullptr, "class type is nullptr");
    const std::string &className = GlobalTables::GetStrTable().GetStringFromStrIdx(classType->GetNameStrIdx());
    if (!CanRemoveClinitCheck(className)) {
      Klass *klass = klassHierarchy->GetKlassFromName(className);
      CHECK_FATAL(klass != nullptr, "klass is nullptr in ClassInit::ProcessFunc");
      if (klass->GetClinit() && func != klass->GetClinit()) {
        MIRSymbol *classInfo = GetClassInfo(className);
        BaseNode *classInfoNode = builder->CreateExprAddrof(0, classInfo);
        if (trace) {
          LogInfo::MapleLogger() << "\t- low-cost clinit - insert check in static method " << func->GetName()
                                 << "clasname " << className << std::endl;
        }
        MapleVector<BaseNode*> args(builder->GetCurrentFuncCodeMpAllocator()->Adapter());
        args.push_back(classInfoNode);
        StmtNode *intrinsicCall = builder->CreateStmtIntrinsicCall(INTRN_MPL_CLINIT_CHECK, args);
        func->GetBody()->InsertFirst(intrinsicCall);
        GenClassInitCheckProfile(func, classInfo, intrinsicCall);
      }
    }
  }
  // Lower JAVA_CLINIT_CHECK to MPL_CLINIT_CHECK.
  StmtNode *stmt = func->GetBody()->GetFirst();
  while (stmt != nullptr) {
    if (stmt->GetOpCode() == OP_intrinsiccallwithtype) {
      IntrinsiccallNode *intrinsicCall = static_cast<IntrinsiccallNode*>(stmt);
      if (intrinsicCall->GetIntrinsic() == INTRN_JAVA_CLINIT_CHECK) {
        // intrinsiccallwithtype <$LTest_3B> JAVA_CLINIT_CHECK ()        -->
        // intrinsiccall MPL_CLINIT_CHECK (addrof ptr $__cinf_LTest_3B)
        CHECK_FATAL(intrinsicCall->GetNopndSize() == 0, "wrong arg vectors");
        CHECK_FATAL(intrinsicCall->GetTyIdx().GetIdx() < GlobalTables::GetTypeTable().GetTypeTable().size(),
                    "index out of range");
        MIRType *classType = GlobalTables::GetTypeTable().GetTypeTable()[intrinsicCall->GetTyIdx().GetIdx()];
        CHECK_FATAL(classType && classType->GetNameStrIdx() != 0, "symbol name is null for type index %d",
                    intrinsicCall->GetTyIdx().GetIdx());
        const std::string &className = GlobalTables::GetStrTable().GetStringFromStrIdx(classType->GetNameStrIdx());
        Klass *klass = klassHierarchy->GetKlassFromName(className);
        bool doClinitCheck = false;
        if (!klass) {
          WARN(kLncWarn, "ClassInit::ProcessFunc: Skip INCOMPLETE type %s", className.c_str());
          doClinitCheck = true;
        } else {
          doClinitCheck = !CanRemoveClinitCheck(className) && klassHierarchy->NeedClinitCheckRecursively(klass);
        }
        if (doClinitCheck) {
          MIRSymbol *classInfo = GetClassInfo(className);
          AddrofNode *classInfoNode = builder->CreateExprAddrof(0, classInfo);
          MapleVector<BaseNode*> args(builder->GetCurrentFuncCodeMpAllocator()->Adapter());
          args.push_back(classInfoNode);
          StmtNode *mplIntrinsicCall = builder->CreateStmtIntrinsicCall(INTRN_MPL_CLINIT_CHECK, args);
          func->GetBody()->ReplaceStmt1WithStmt2(stmt, mplIntrinsicCall);
          if (trace) {
            LogInfo::MapleLogger() << "\t- low-cost clinit - lower JAVA_CLINIT_CHECK " << className << " in "
                                   << func->GetName() << "()" << std::endl;
          }
          GenClassInitCheckProfile(func, classInfo, mplIntrinsicCall);
        } else {
          func->GetBody()->RemoveStmt(stmt);
        }
      }
    }
    stmt = stmt->GetNext();
  }
}

MIRSymbol *ClassInit::GetClassInfo(const std::string &classname) {
  const std::string &classInfoName = CLASSINFO_PREFIX_STR + classname;
  MIRType *classInfoType =
      GlobalTables::GetTypeTable().GetOrCreateClassType(NameMangler::kClassMetadataTypeName, GetModule());
  MIRSymbol *classInfo = builder->GetOrCreateGlobalDecl(classInfoName.c_str(), classInfoType);
  Klass *klass = klassHierarchy->GetKlassFromName(classname);
  if (klass == nullptr || !klass->GetMIRStructType()->IsLocal()) {
    classInfo->SetStorageClass(kScExtern);
  }
  return classInfo;
}

}  // namespace maple
