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
#include "mir_module.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <cctype>
#include "mir_const.h"
#include "mir_preg.h"
#include "mir_function.h"
#include "mir_builder.h"
#include "intrinsics.h"
#include "bin_mplt.h"

namespace maple {
#if MIR_FEATURE_FULL  // to avoid compilation error when MIR_FEATURE_FULL=0
MIRModule::MIRModule(const char *fn)
    : memPool(mempoolctrler.NewMemPool("maple_ir mempool")),
      memPoolAllocator(memPool),
      functionList(memPoolAllocator.Adapter()),
      compilationList(memPoolAllocator.Adapter()),
      importedMplt(memPoolAllocator.Adapter()),
      typeDefOrder(memPoolAllocator.Adapter()),
      externStructTypeSet(std::less<TyIdx>(), memPoolAllocator.Adapter()),
      symbolSet(std::less<StIdx>(), memPoolAllocator.Adapter()),
      symbolDefOrder(memPoolAllocator.Adapter()),
      someSymbolNeedForwDecl(false),
      out(LogInfo::MapleLogger()),
      entryFuncName(""),
      fileName(fn),
      throwableTyIdx(0),
      fileInfo(memPoolAllocator.Adapter()),
      fileInfoIsString(memPoolAllocator.Adapter()),
      fileData(memPoolAllocator.Adapter()),
      srcFileInfo(memPoolAllocator.Adapter()),
      importFiles(memPoolAllocator.Adapter()),
      importPaths(memPoolAllocator.Adapter()),
      classList(memPoolAllocator.Adapter()),
      entryFunc(nullptr),
      floatNum(0),
      optimizedFuncs(memPoolAllocator.Adapter()),
      rcNotNeedingLock(memPoolAllocator.Adapter()),
      puIdxFieldInitializedMap(std::less<PUIdx>(), memPoolAllocator.Adapter()) {
  flavor = kFlavorUnknown;
  srcLang = kSrcLangUnknown;
  id = 0xffff;
  globalMemSize = 0;
  globalBlkMap = nullptr;
  globalWordsTypeTagged = nullptr;
  globalWordsRefCounted = nullptr;
  numFuncs = 0;
  withProfileInfo = false;
  GlobalTables::GetGsymTable().SetModule(this);
  typeNameTab = memPool->New<MIRTypeNameTable>(&memPoolAllocator);
  mirBuilder = memPool->New<MIRBuilder>(this);
  IntrinDesc::InitMIRModule(this);
  binMplt = nullptr;
  curFunction = nullptr;
}

MIRModule::~MIRModule() {
  mempoolctrler.DeleteMemPool(memPool);
  if (binMplt) {
    delete binMplt;
  }
}

MIRFunction *MIRModule::CurFunction(void) const {
  return curFunction;
}

MemPool *MIRModule::CurFuncCodeMemPool(void) const {
  return CurFunction()->GetCodeMempool();
}

MapleAllocator *MIRModule::CurFuncCodeMemPoolAllocator(void) const {
  return curFunction->GetCodeMempoolAllocator();
}

void MIRModule::AddExternStructType(TyIdx tyIdx) {
  externStructTypeSet.insert(tyIdx);
}

void MIRModule::AddExternStructType(const MIRType *t) {
  ASSERT(t != nullptr, "MIRType is null");
  externStructTypeSet.insert(t->GetTypeIndex());
}

void MIRModule::AddSymbol(StIdx stIdx) {
  auto it = symbolSet.find(stIdx);
  if (it == symbolSet.end()) {
    symbolDefOrder.push_back(stIdx);
  }
  symbolSet.insert(stIdx);
}

void MIRModule::AddSymbol(const MIRSymbol *s) {
  ASSERT(s != nullptr, "s is null");
  AddSymbol(s->GetStIdx());
}

void MIRModule::DumpGlobals(bool emitStructureType) {
  if (flavor != kFlavorUnknown) {
    LogInfo::MapleLogger() << "flavor " << flavor << std::endl;
  }
  if (srcLang != kSrcLangUnknown) {
    LogInfo::MapleLogger() << "srclang " << srcLang << std::endl;
  }
  LogInfo::MapleLogger() << "id " << id << std::endl;
  if (globalMemSize != 0) {
    LogInfo::MapleLogger() << "globalmemsize " << globalMemSize << std::endl;
  }
  if (globalBlkMap != nullptr) {
    LogInfo::MapleLogger() << "globalmemmap = [ ";
    uint32 *p = reinterpret_cast<uint32*>(globalBlkMap);
    LogInfo::MapleLogger() << std::hex;
    while (p < reinterpret_cast<uint32*>(globalBlkMap + globalMemSize)) {
      LogInfo::MapleLogger() << std::hex << "0x" << *p << " ";
      p++;
    }
    LogInfo::MapleLogger() << std::dec << "]\n";
  }
  if (globalWordsTypeTagged != nullptr) {
    LogInfo::MapleLogger() << "globalwordstypetagged = [ ";
    uint32 *p = reinterpret_cast<uint32*>(globalWordsTypeTagged);
    LogInfo::MapleLogger() << std::hex;
    while (p < reinterpret_cast<uint32*>(globalWordsTypeTagged + BlockSize2BitVectorSize(globalMemSize))) {
      LogInfo::MapleLogger() << std::hex << "0x" << *p << " ";
      p++;
    }
    LogInfo::MapleLogger() << std::dec << "]\n";
  }
  if (globalWordsRefCounted != nullptr) {
    LogInfo::MapleLogger() << "globalwordsrefcounted = [ ";
    uint32 *p = reinterpret_cast<uint32*>(globalWordsRefCounted);
    LogInfo::MapleLogger() << std::hex;
    while (p < reinterpret_cast<uint32*>(globalWordsRefCounted + BlockSize2BitVectorSize(globalMemSize))) {
      LogInfo::MapleLogger() << std::hex << "0x" << *p << " ";
      p++;
    }
    LogInfo::MapleLogger() << std::dec << "]\n";
  }
  LogInfo::MapleLogger() << "numfuncs " << numFuncs << std::endl;
  if (!importFiles.empty()) {
    // Output current module's mplt on top, imported ones at below
    for (auto it = importFiles.rbegin(); it != importFiles.rend(); it++) {
      LogInfo::MapleLogger() << "import \"" << GlobalTables::GetStrTable().GetStringFromStrIdx(*it) << "\""
                             << std::endl;
    }
  }
  if (!importPaths.empty()) {
    size_t size = importPaths.size();
    for (size_t i = 0; i < size; i++) {
      LogInfo::MapleLogger() << "importpath \"" << GlobalTables::GetStrTable().GetStringFromStrIdx(importPaths[i])
                             << "\"" << std::endl;
    }
  }
  if (entryFuncName.length()) {
    LogInfo::MapleLogger() << "entryfunc &" << entryFuncName << std::endl;
  }
  if (!fileInfo.empty()) {
    LogInfo::MapleLogger() << "fileinfo {\n";
    size_t size = fileInfo.size();
    for (size_t i = 0; i < size; i++) {
      LogInfo::MapleLogger() << "  @" << GlobalTables::GetStrTable().GetStringFromStrIdx(fileInfo[i].first) << " ";
      if (!fileInfoIsString[i]) {
        LogInfo::MapleLogger() << "0x" << std::hex << fileInfo[i].second;
      } else {
        LogInfo::MapleLogger() << "\"" << GlobalTables::GetStrTable().GetStringFromStrIdx(GStrIdx(fileInfo[i].second))
                               << "\"";
      }
      if (i < size - 1) {
        LogInfo::MapleLogger() << ",\n";
      } else {
        LogInfo::MapleLogger() << "}\n";
      }
    }
    LogInfo::MapleLogger() << std::dec;
  }
  if (!srcFileInfo.empty()) {
    LogInfo::MapleLogger() << "srcfileinfo {\n";
    size_t size = srcFileInfo.size();
    size_t i = 0;
    for (auto it : srcFileInfo) {
      LogInfo::MapleLogger() << "  " << it.second;
      LogInfo::MapleLogger() << " \"" << GlobalTables::GetStrTable().GetStringFromStrIdx(it.first) << "\"";
      if (i++ < size - 1) {
        LogInfo::MapleLogger() << ",\n";
      } else {
        LogInfo::MapleLogger() << "}\n";
      }
    }
  }
  if (!fileData.empty()) {
    LogInfo::MapleLogger() << "filedata {\n";
    size_t size = fileData.size();
    for (size_t i = 0; i < size; i++) {
      LogInfo::MapleLogger() << "  @" << GlobalTables::GetStrTable().GetStringFromStrIdx(fileData[i].first) << " ";
      size_t dataSize = fileData[i].second.size();
      for (size_t j = 0; j < dataSize; j++) {
        uint8 data = fileData[i].second[j];
        LogInfo::MapleLogger() << "0x" << std::hex << static_cast<uint32>(data);
        if (j < dataSize - 1) {
          LogInfo::MapleLogger() << ' ';
        }
      }
      if (i < size - 1) {
        LogInfo::MapleLogger() << ",\n";
      } else {
        LogInfo::MapleLogger() << "}\n";
      }
    }
    LogInfo::MapleLogger() << std::dec;
  }
  if (flavor < kMmpl) {
    for (auto it = typeDefOrder.begin(); it != typeDefOrder.end(); it++) {
      TyIdx tyIdx = typeNameTab->GetTyIdxFromGStrIdx(*it);
      const std::string &name = GlobalTables::GetStrTable().GetStringFromStrIdx(*it);
      MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx);
      ASSERT(type != nullptr, "type should not be nullptr here");
      MIRStructType *structType = dynamic_cast<MIRStructType*>(type);
      if (structType != nullptr && !emitStructureType) {
        // still emit what in extern_structtype_set_
        if (externStructTypeSet.find(structType->GetTypeIndex()) == externStructTypeSet.end()) {
          continue;
        }
      }
      if (structType != nullptr && structType->IsImported()) {
        continue;
      }
      LogInfo::MapleLogger() << "type $" << name << " ";
      if (type->GetKind() == kTypeByName) {
        LogInfo::MapleLogger() << "void";
      } else if (type->GetNameStrIdx() == *it) {
        type->Dump(1, true);
      } else {
        type->Dump(1);
      }
      LogInfo::MapleLogger() << std::endl;
    }
    if (someSymbolNeedForwDecl) {
      // an extra pass thru the global symbol table to print forward decl
      for (auto sit = symbolSet.begin(); sit != symbolSet.end(); sit++) {
        MIRSymbol *s = GlobalTables::GetGsymTable().GetSymbolFromStidx((*sit).Idx());
        if (s->IsNeedForwDecl()) {
          s->Dump(false, 0, true);
        }
      }
    }
    // dump javaclass and javainterface first
    for (auto sit = symbolDefOrder.begin(); sit != symbolDefOrder.end(); sit++) {
      MIRSymbol *s = GlobalTables::GetGsymTable().GetSymbolFromStidx((*sit).Idx());
      if (!s->IsJavaClassInterface()) {
        continue;
      }
      // Verify: all wpofake variables should have been deleted from globaltable
      if (!s->IsDeleted()) {
        s->Dump(false, 0);
      }
    }
    for (auto sit = symbolDefOrder.begin(); sit != symbolDefOrder.end(); sit++) {
      MIRSymbol *s = GlobalTables::GetGsymTable().GetSymbolFromStidx((*sit).Idx());
      CHECK_FATAL(s != nullptr, "nullptr check");
      if (s->IsJavaClassInterface()) {
        continue;
      }
      if (!s->IsDeleted() && !s->GetIsImported()) {
        s->Dump(false, 0);
      }
    }
  }
}

void MIRModule::Dump(bool emitStructureType) {
  DumpGlobals(emitStructureType);
  DumpFunctionList();
}

void MIRModule::DumpGlobalArraySymbol() {
  MapleSet<StIdx>::iterator sit = symbolSet.begin();
  for (; sit != symbolSet.end(); sit++) {
    MIRSymbol *s = GlobalTables::GetGsymTable().GetSymbolFromStidx((*sit).Idx());
    MIRType *sType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(s->GetTyIdx());
    if (sType == nullptr || sType->GetKind() != kTypeArray) {
      continue;
    }
    s->Dump(false, 0);
  }
}

void MIRModule::Emit(const std::string &outfileName) {
  std::ofstream file;
  // Change cout's buffer to file.
  std::streambuf *backup = LogInfo::MapleLogger().rdbuf();
  LogInfo::MapleLogger().rdbuf(file.rdbuf());
  file.open(outfileName.c_str(), std::ios::trunc);
  DumpGlobals();
  for (MIRFunction *mirFunc : functionList) {
    mirFunc->Dump();
  }
  // Restore cout's buffer.
  LogInfo::MapleLogger().rdbuf(backup);
  file.close();
}

void MIRModule::DumpFunctionList(bool skipBody) {
  for (auto it = functionList.begin(); it != functionList.end(); it++) {
    (*it)->Dump(skipBody);
  }
}

void MIRModule::OutputFunctionListAsciiMpl(const char *phaseName) {
  std::string fileStem;
  std::string::size_type lastDot = fileName.find_last_of('.');
  if (lastDot == std::string::npos) {
    fileStem = fileName.append(phaseName);
  } else {
    fileStem = fileName.substr(0, lastDot).append(phaseName);
  }
  std::string outfileName;
  if (flavor >= kMmpl) {
    outfileName = fileStem.append(".mmpl");
  } else {
    outfileName = fileStem.append(".mpl");
  }
  std::ofstream mplFile;
  mplFile.open(outfileName, std::ios::app);
  std::streambuf *backup = LogInfo::MapleLogger().rdbuf();
  LogInfo::MapleLogger().rdbuf(mplFile.rdbuf());  // change cout's buffer to that of file
  DumpGlobalArraySymbol();
  DumpFunctionList();
  LogInfo::MapleLogger().rdbuf(backup);  // restore cout's buffer
  mplFile.close();
  return;
}

void MIRModule::DumpToFile(const std::string &fileNameStr, bool emitStructureType) {
  std::ofstream file;
  file.open(fileNameStr.c_str(), std::ios::trunc);
  if (!file.is_open()) {
    std::cerr << "Cannot open " << fileNameStr << std::endl;
  }
  // Change cout's buffer to file.
  std::streambuf *backup = LogInfo::MapleLogger().rdbuf();
  LogInfo::MapleLogger().rdbuf(file.rdbuf());
  Dump(emitStructureType);
  // Restore cout's buffer.
  LogInfo::MapleLogger().rdbuf(backup);
}

void MIRModule::DumpInlineCandidateToFile(const std::string &fileNameStr) {
  if (optimizedFuncs.empty()) {
    return;
  }
  std::ofstream file;
  // Change cout's buffer to file.
  std::streambuf *backup = LogInfo::MapleLogger().rdbuf();
  LogInfo::MapleLogger().rdbuf(file.rdbuf());
  file.open(fileNameStr.c_str(), std::ios::trunc);
  for (auto it = optimizedFuncs.begin(); it != optimizedFuncs.end(); it++) {
    (*it)->SetWithLocInfo(false);
    (*it)->Dump();
  }
  // Restore cout's buffer.
  LogInfo::MapleLogger().rdbuf(backup);
  file.close();
}

// This is not efficient. Only used in debug mode for now.
const std::string &MIRModule::GetFileNameFromFileNum(uint32 fileNum) {
  GStrIdx nameIdx = GStrIdx(0);
  for (auto &info : srcFileInfo) {
    if (info.second == fileNum) {
      nameIdx = info.first;
    }
  }
  return GlobalTables::GetStrTable().GetStringFromStrIdx(nameIdx);
}


void MIRModule::DumpClassToFile(const char *path) {
  ASSERT(path != nullptr, "null ptr check");
  std::string spath(path);
  spath.append("/");
  for (auto it : typeNameTab->GetGStrIdxToTyIdxMap()) {
    const std::string &name = GlobalTables::GetStrTable().GetStringFromStrIdx(it.first);
    MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(it.second);
    std::string outClassFile = name.c_str();
    /* replace class name / with - */
    std::replace(outClassFile.begin(), outClassFile.end(), '/', '-');
    outClassFile.insert(0, spath);
    outClassFile.append(".mpl");
    std::ofstream mplFile;
    mplFile.open(outClassFile.c_str(), std::ios::trunc);
    std::streambuf *backup = LogInfo::MapleLogger().rdbuf();
    LogInfo::MapleLogger().rdbuf(mplFile.rdbuf());
    /* dump class type */
    LogInfo::MapleLogger() << "type $" << name << " ";
    if (type->GetNameStrIdx() == it.first && type->GetKind() != kTypeByName) {
      type->Dump(1, true);
    } else {
      type->Dump(1);
    }
    LogInfo::MapleLogger() << std::endl;
    /* restore cout */
    LogInfo::MapleLogger().rdbuf(backup);
    mplFile.close();
  }
}

MIRFunction *MIRModule::FindEntryFunction() {
  for (size_t i = 0; i < functionList.size(); i++) {
    MIRFunction *currFunc = functionList[i];
    if (currFunc->GetName() == entryFuncName) {
      entryFunc = currFunc;
      return currFunc;
    }
  }
  return nullptr;
}

// given the phase name (including '.' at beginning), output the program in the
// module in ascii form to the file with either .mpl or .mmpl suffix, and file
// stem from this->fileName appended with phasename
void MIRModule::OutputAsciiMpl(const char *phaseName, bool emitStructureType) {
  std::string fileStem;
  std::string::size_type lastDot = fileName.find_last_of(".");
  if (lastDot == std::string::npos) {
    fileStem = fileName.append(phaseName);
  } else {
    fileStem = fileName.substr(0, lastDot).append(phaseName);
  }
  std::string outfileName;
  if (flavor >= kMmpl) {
    outfileName = fileStem.append(".mmpl");
  } else {
    outfileName = fileStem.append(".mpl");
  }
  std::ofstream mplFile;
  mplFile.open(outfileName, std::ios::trunc);
  std::streambuf *backup = LogInfo::MapleLogger().rdbuf();
  LogInfo::MapleLogger().rdbuf(mplFile.rdbuf());  // change cout's buffer to that of file
  Dump(emitStructureType);
  LogInfo::MapleLogger().rdbuf(backup);  // restore cout's buffer
  mplFile.close();
  return;
}

uint32 MIRModule::GetFileinfo(GStrIdx strIdx) const {
  size_t size = fileInfo.size();
  for (size_t i = 0; i < size; i++) {
    if (fileInfo[i].first == strIdx) {
      return fileInfo[i].second;
    }
  }
  ASSERT(false, "should not be here");
  return 0;
}

std::string MIRModule::GetFileNameAsPostfix() const {
  std::string fileNameStr = NameMangler::kFileNameSplitterStr;
  if (!fileInfo.empty()) {
    // option 1: file name in INFO
    uint32 fileNameIdx = GetFileinfo(GlobalTables::GetStrTable().GetOrCreateStrIdxFromName("INFO_filename"));
    fileNameStr += GlobalTables::GetStrTable().GetStringFromStrIdx(GStrIdx(fileNameIdx));
  } else {
    // option 2: src file name removing ext name.
    ASSERT(fileNameStr.find_last_of(".") != fileNameStr.npos, "not found .");
    fileNameStr += fileNameStr.substr(0, fileNameStr.find_last_of("."));
  }
  for (uint32 i = 0; i < fileNameStr.length(); ++i) {
    char c = fileNameStr[i];
    if (!isalpha(c) && !isdigit(c) && c != '_' && c != '$') {
      fileNameStr[i] = '_';
    }
  }
  return fileNameStr;
}

void MIRModule::AddClass(TyIdx t) {
  classList.insert(t.GetIdx());
  return;
}

void MIRModule::RemoveClass(TyIdx t) {
  classList.erase(t.GetIdx());
  return;
}

#endif  // MIR_FEATURE_FULL
void MIRModule::SetFuncInfoPrinted() const {
  CurFunction()->SetInfoPrinted();
}

}  // namespace maple
