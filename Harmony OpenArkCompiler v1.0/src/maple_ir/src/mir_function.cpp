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
#include "mir_function.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include "mir_nodes.h"
#include "class_hierarchy.h"
#include "printing.h"

namespace maple {
void FuncAttrs::DumpAttributes() const {
#define STRING(s) #s
#define FUNC_ATTR
#define ATTR(AT)              \
  if (GetAttr(FUNCATTR_##AT)) \
    LogInfo::MapleLogger() << " " << STRING(AT);
#include "all_attributes.def"
#undef ATTR
#undef FUNC_ATTR
}

void MIRFunction::Dump(bool withoutBody) {
  // skip the functions that are added during process methods in
  // class and interface decls.  these has nothing in formals
  // they do have paramtypelist_. this can not skip ones without args
  // but for them at least the func decls are valid
  if (GetParamSize() != formals.size()) {
    return;
  }
  if (GetAttr(FUNCATTR_optimized)) {
    return;
  }
  // save the module's curfunction and set it to the one currently Dump()ing
  MIRFunction *savedFunc = module->CurFunction();
  module->SetCurFunction(this);
  MIRSymbol *fnSt = GlobalTables::GetGsymTable().GetSymbolFromStidx(symbolTableIdx.Idx());
  ASSERT(fnSt != nullptr, "fnSt MIRSymbol is null");
  LogInfo::MapleLogger() << "func "
                         << "&" << fnSt->GetName();
  funcAttrs.DumpAttributes();
  if (module->GetFlavor() < kMmpl) {
    LogInfo::MapleLogger() << " (";
    // Dump arguments
    uint32 argSize = GetParamSize();
    for (uint32 i = 0; i < argSize; i++) {
      MIRSymbol *symbol = formals[i];
      if (symbol != nullptr) {
        if (symbol->GetSKind() != kStPreg) {
          LogInfo::MapleLogger() << "var %" << symbol->GetName() << " ";
        } else {
          LogInfo::MapleLogger() << "reg %" << symbol->GetPreg()->GetPregNo() << " ";
        }
      }
      MIRType *ty = GetNthParamType(i);
      ty->Dump(2);
      TypeAttrs tA = GetNthParamAttr(i);
      tA.DumpAttributes();
      if (i != (argSize - 1)) {
        LogInfo::MapleLogger() << ", ";
      }
    }
    if (IsVarargs()) {
      if (argSize == 0) {
        LogInfo::MapleLogger() << "...";
      } else {
        LogInfo::MapleLogger() << ", ...";
      }
    }
    LogInfo::MapleLogger() << ") ";
    GetReturnType()->Dump(1);
  }
  // codeMemPool is nullptr, means maple_ir has been released for memory's sake
  if (codeMemPool == nullptr) {
    LogInfo::MapleLogger() << std::endl;
    LogInfo::MapleLogger() << "# [WARNING] skipped dumping because codeMemPool is nullptr " << std::endl;
  } else if (GetBody() && !withoutBody && fnSt->GetStorageClass() != kScExtern) {
    ResetInfoPrinted();  // this ensures funcinfo will be printed
    GetBody()->Dump(module, 0, module->GetFlavor() < kMmpl ? GetSymTab() : nullptr,
                    module->GetFlavor() < kMmpl ? GetPregTab() : nullptr, false, true);  // Dump body
  } else {
    LogInfo::MapleLogger() << std::endl;
  }
  // restore the curfunction
  module->SetCurFunction(savedFunc);
}

void MIRFunction::DumpUpFormal(int32 indent) const {
  PrintIndentation(indent + 1);
  LogInfo::MapleLogger() << "upformalsize " << static_cast<uint32>(GetUpFormalSize()) << std::endl;
  if (GetLocalWordsTypeTagged() != nullptr) {
    PrintIndentation(indent + 1);
    LogInfo::MapleLogger() << "formalwordstypetagged = [ ";
    uint32 *p = const_cast<uint32*>(reinterpret_cast<const uint32*>(GetLocalWordsTypeTagged()));
    LogInfo::MapleLogger() << std::hex;
    while (p < const_cast<uint32*>(reinterpret_cast<const uint32*>(
                   GetLocalWordsTypeTagged() + BlockSize2BitVectorSize(GetUpFormalSize())))) {
      LogInfo::MapleLogger() << std::hex << "0x" << *p << " ";
      p++;
    }
    LogInfo::MapleLogger() << std::dec << "]\n";
  }
  if (GetFormalWordsRefCounted() != nullptr) {
    PrintIndentation(indent + 1);
    LogInfo::MapleLogger() << "formalwordsrefcounted = [ ";
    uint32 *p = const_cast<uint32*>(reinterpret_cast<const uint32*>(GetFormalWordsRefCounted()));
    LogInfo::MapleLogger() << std::hex;
    while (p < const_cast<uint32*>(reinterpret_cast<const uint32*>(
                   GetFormalWordsRefCounted() + BlockSize2BitVectorSize(GetUpFormalSize())))) {
      LogInfo::MapleLogger() << std::hex << "0x" << *p << " ";
      p++;
    }
    LogInfo::MapleLogger() << std::dec << "]\n";
  }
}

void MIRFunction::DumpFrame(int32 indent) const {
  PrintIndentation(indent + 1);
  LogInfo::MapleLogger() << "framesize " << GetFrameSize() << std::endl;
  if (GetLocalWordsTypeTagged() != nullptr) {
    PrintIndentation(indent + 1);
    LogInfo::MapleLogger() << "localwordstypetagged = [ ";
    uint32 *p = const_cast<uint32*>(reinterpret_cast<const uint32*>(GetLocalWordsTypeTagged()));
    LogInfo::MapleLogger() << std::hex;
    while (p < const_cast<uint32*>(reinterpret_cast<const uint32*>(
                   GetLocalWordsTypeTagged() + BlockSize2BitVectorSize(GetFrameSize())))) {
      LogInfo::MapleLogger() << std::hex << "0x" << *p << " ";
      p++;
    }
    LogInfo::MapleLogger() << std::dec << "]\n";
  }
  if (GetLocalWordsRefCounted() != nullptr) {
    PrintIndentation(indent + 1);
    LogInfo::MapleLogger() << "localwordsrefcounted = [ ";
    uint32 *p = const_cast<uint32*>(reinterpret_cast<const uint32*>(GetLocalWordsRefCounted()));
    LogInfo::MapleLogger() << std::hex;
    while (p < const_cast<uint32*>(reinterpret_cast<const uint32*>(
                   GetLocalWordsRefCounted() + BlockSize2BitVectorSize(GetFrameSize())))) {
      LogInfo::MapleLogger() << std::hex << "0x" << *p << " ";
      p++;
    }
    LogInfo::MapleLogger() << std::dec << "]\n";
  }
}

void MIRFunction::DumpFuncBody(int32 indent) {
  LogInfo::MapleLogger() << "  funcid " << GetPuidxOrigin() << std::endl;
  if (!IsInfoPrinted()) {
    SetInfoPrinted();
    if (GetUpFormalSize()) {
      DumpUpFormal(indent);
    }
    if (GetFrameSize()) {
      DumpFrame(indent);
    }
    if (GetModuleId()) {
      PrintIndentation(indent + 1);
      LogInfo::MapleLogger() << "moduleid " << static_cast<uint32>(GetModuleId()) << std::endl;
    }
    if (GetModuleId()) {
      PrintIndentation(indent + 1);
      LogInfo::MapleLogger() << "funcsize " << GetFuncSize() << std::endl;
    }
    if (!GetInfoVector().empty()) {
      MIRInfoVector funcInfo = GetInfoVector();
      MapleVector<bool> funcInfoIsString = InfoIsString();
      PrintIndentation(indent + 1);
      LogInfo::MapleLogger() << "funcinfo {\n";
      size_t size = funcInfo.size();
      for (size_t i = 0; i < size; i++) {
        PrintIndentation(indent + 2);
        LogInfo::MapleLogger() << "@" << GlobalTables::GetStrTable().GetStringFromStrIdx(funcInfo[i].first) << " ";
        if (!funcInfoIsString[i]) {
          LogInfo::MapleLogger() << funcInfo[i].second;
        } else {
          LogInfo::MapleLogger() << "\""
                                 << GlobalTables::GetStrTable().GetStringFromStrIdx(GStrIdx(funcInfo[i].second))
                                 << "\"";
        }
        if (i < size - 1) {
          LogInfo::MapleLogger() << ",\n";
        } else {
          LogInfo::MapleLogger() << "}\n";
        }
      }
      LogInfo::MapleLogger() << std::endl;
    }
  }
}

bool MIRFunction::IsEmpty() const {
  return (body == nullptr || body->IsEmpty());
}

bool MIRFunction::IsClinit() const {
  const std::string &funcName = this->GetName();
  size_t clinitSuffixPos = funcName.rfind("_7C_3Cclinit_3E_7C_28_29V");
  bool isClinit = (clinitSuffixPos != std::string::npos) &&
                  (clinitSuffixPos + sizeof("_7C_3Cclinit_3E_7C_28_29V") - 1 == funcName.size());
  // this does not work for smali files like art/test/511-clinit-interface/smali/BogusInterface.smali,
  // which is decorated without "constructor".
  return isClinit;
}

uint32 MIRFunction::GetInfo(GStrIdx strIdx) const {
  size_t size = info.size();
  for (size_t i = 0; i < size; i++) {
    if (info[i].first == strIdx) {
      return info[i].second;
    }
  }
  ASSERT(false, "info ptr check");
  return 0;
}

uint32 MIRFunction::GetInfo(const std::string &string) const {
  GStrIdx strIdx = GlobalTables::GetStrTable().GetStrIdxFromName(string);
  return GetInfo(strIdx);
}

void MIRFunction::OverrideBaseClassFuncNames(GStrIdx strIdx) {
  baseClassStrIdx.SetIdx(0);
  baseFuncStrIdx.SetIdx(0);
  SetBaseClassFuncNames(strIdx);
}

// there are two ways to represent the delimiter: '|' or "_7C"
// where 7C is the ascii value of char '|' in hex
void MIRFunction::SetBaseClassFuncNames(GStrIdx strIdx) {
  if (baseClassStrIdx != 0 || baseFuncStrIdx != 0) {
    return;
  }
  std::string name = GlobalTables::GetStrTable().GetStringFromStrIdx(strIdx);
  std::string delimiter = "|";
  uint32 width = 1;  // delimiter width
  size_t pos = name.find(delimiter);
  if (pos == std::string::npos) {
    delimiter = NameMangler::kNameSplitterStr;
    width = 3;
    pos = name.find(delimiter);
    // make sure it is not __7C, but ___7C ok
    while (pos != std::string::npos && (name[pos - 1] == '_' && name[pos - 2] != '_')) {
      pos = name.find(delimiter, pos + width);
    }
  }
  if (pos != std::string::npos && pos > 0) {
    std::string className = name.substr(0, pos);
    baseClassStrIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(className);
    std::string funcNameWithtype = name.substr(pos + width, name.length() - pos - width);
    baseFuncWithTypeStrIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(funcNameWithtype);
    size_t index = name.find(NameMangler::kRigthBracketStr);
    ASSERT(index != std::string::npos, "Invalid name, cannot find '_29' in name");
    size_t posEnd = index + (std::string(NameMangler::kRigthBracketStr)).length();
    funcNameWithtype = name.substr(pos + width, posEnd - pos - width);
    size_t pos1 = name.find(delimiter, pos + width);
    while (pos1 != std::string::npos && (name[pos1 - 1] == '_' && name[pos1 - 2] != '_')) {
      pos1 = name.find(delimiter, pos1 + width);
    }
    if (pos1) {
      std::string funcName = name.substr(pos + width, pos1 - pos - width);
      baseFuncStrIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(funcName);
      std::string signature = name.substr(pos1 + width, name.length() - pos1 - width);
      signatureStrIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(signature);
    }
    return;
  }
  baseFuncStrIdx = strIdx;
}

MIRSymbol *MIRFunction::GetLocalOrGlobalSymbol(const StIdx &idx, bool checkFirst) const {
  return idx.Islocal() ? GetSymbolTabItem(idx.Idx(), checkFirst)
                       : GlobalTables::GetGsymTable().GetSymbolFromStidx(idx.Idx(), checkFirst);
}

MIRType *MIRFunction::GetNodeType(BaseNode *node) {
  ASSERT(node != nullptr, "node cannot be nullptr");
  if (node->GetOpCode() == OP_dread) {
    MIRSymbol *sym = GetLocalOrGlobalSymbol(static_cast<DreadNode*>(node)->GetStIdx());
    return GlobalTables::GetTypeTable().GetTypeFromTyIdx(sym->GetTyIdx());
  } else if (node->GetOpCode() == OP_regread) {
    RegreadNode *nodeReg = static_cast<RegreadNode*>(node);
    MIRPreg *pReg = GetPregTab()->PregFromPregIdx(nodeReg->GetRegIdx());
    if (pReg->GetPrimType() == PTY_ref) {
      return pReg->GetMIRType();
    }
  }
  return nullptr;
}

void MIRFunction::NewBody() {
  SetBody(codeMemPool->New<BlockNode>());
  // If mir_function.has been seen as a declaration, its symtab has to be moved
  // from module mempool to function mempool.
  MIRSymbolTable *oldSymTable = GetSymTab();
  MIRPregTable *oldPregTable = GetPregTab();
  MIRTypeNameTable *oldTypenameTable = typeNameTab;
  MIRLabelTable *oldLabelTable = GetLabelTab();
  SetSymTab(dataMemPool->New<MIRSymbolTable>(&dataMPAllocator));
  SetPregTab(dataMemPool->New<MIRPregTable>(module, &dataMPAllocator));
  typeNameTab = dataMemPool->New<MIRTypeNameTable>(&dataMPAllocator);
  SetLabelTab(dataMemPool->New<MIRLabelTable>(&dataMPAllocator));
  if (oldSymTable != nullptr) {
    for (size_t i = 1; i < oldSymTable->GetSymbolTableSize(); i++) {
      (void)GetSymTab()->AddStOutside(oldSymTable->GetSymbolFromStIdx(i));
    }
  }
  if (oldPregTable != nullptr) {
    for (size_t i = 1; i < oldPregTable->Size(); i++) {
      GetPregTab()->AddPreg(oldPregTable->PregFromPregIdx(i));
    }
  }
  if (oldTypenameTable != nullptr) {
    ASSERT(oldTypenameTable->Size() == typeNameTab->Size(),
           "Does not expect to process typeNameTab in MIRFunction::NewBody");
  }
  if (oldLabelTable != nullptr) {
    ASSERT(oldLabelTable->Size() == GetLabelTab()->Size(),
           "Does not expect to process labelTab in MIRFunction::NewBody");
  }
}

void MIRFunction::SetUpGDBEnv() {
  if (codeMemPool != nullptr) {
    mempoolctrler.DeleteMemPool(codeMemPool);
  }
  codeMemPool = mempoolctrler.NewMemPool("tmp debug");
  codeMemPoolAllocator.SetMemPool(codeMemPool);
}

void MIRFunction::ResetGDBEnv() {
  mempoolctrler.DeleteMemPool(codeMemPool);
  codeMemPool = nullptr;
}

}  // namespace maple
