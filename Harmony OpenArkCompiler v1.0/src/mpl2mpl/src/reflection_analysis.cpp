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
#include "reflection_analysis.h"
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <fstream>
#include "vtable_analysis.h"
#include "vtable_impl.h"
#include "option.h"
#include "muid_replacement.h"
#include "mir_builder.h"
#include "name_mangler.h"
#include "itab_util.h"
#include "zlib.h"
#include "string_utils.h"

// Reflection metadata
// This file is used to generate the classmetadata and classhashmetadata.
//
// A. Classmetadata is consists of three parts:classinfo, fields, methods,
//    and we generates these data according to the structure which defined in
//    the reflection_analysis.h && metadata_layout.h and then add their address
//    to mirbuilder.
using namespace NameMangler;

namespace maple {
std::string ReflectionAnalysis::strTab = std::string(1, '\0');
std::unordered_map<std::string, uint32> ReflectionAnalysis::str2IdxMap;
std::string ReflectionAnalysis::strTabStartHot = std::string(1, '\0');
std::string ReflectionAnalysis::strTabBothHot = std::string(1, '\0');
std::string ReflectionAnalysis::strTabRunHot = std::string(1, '\0');
bool ReflectionAnalysis::strTabInited = false;
uint8 *DeflateBuffer(const uint8 *rawBuffer, uint32 rawBufferSize, uint32 *deflateSize) {
  z_stream stream;
  stream.zalloc = Z_NULL;
  stream.zfree = Z_NULL;
  stream.opaque = Z_NULL;
  int ret = deflateInit(&stream, Z_BEST_COMPRESSION);
  if (ret != Z_OK) {
    return nullptr;
  }
  uint32 deflateMaxSize = deflateBound(&stream, rawBufferSize);
  CHECK_FATAL(deflateMaxSize > 0, "Buffer size checkout");
  uint8 *deflateBuffer = nullptr;
  deflateBuffer = new uint8[deflateMaxSize];
  stream.avail_in = rawBufferSize;
  stream.next_in = const_cast<uint8*>(rawBuffer);
  stream.avail_out = deflateMaxSize;
  stream.next_out = &deflateBuffer[0];
  ret = deflate(&stream, Z_FINISH);
  if (ret == Z_STREAM_ERROR) {
    delete[] deflateBuffer;
    deflateBuffer = nullptr;
    return nullptr;
  }
  *deflateSize = deflateMaxSize - stream.avail_out;
  deflateEnd(&stream);
  return deflateBuffer;
}

int ReflectionAnalysis::GetDeflateStringIdx(const std::string &subStr) {
  uint32 deflateSize = 0;
  uint32 signatureIdx;
  char *deflateBuffer =
      reinterpret_cast<char*>(DeflateBuffer((const uint8*)(subStr.c_str()), subStr.size(), &deflateSize));
  // The flag length at least 6 byte, so we do not compress if compress gain less than 6 byte.
  if (subStr.size() < deflateSize + 6) {
    signatureIdx = FindOrInsertReflectString("0!" + subStr);
  } else {
    CHECK_FATAL(deflateBuffer != nullptr, "deflateBuffer check");
    std::string deflateString(deflateBuffer, deflateBuffer + deflateSize);
    signatureIdx = FindOrInsertReflectString(std::to_string(deflateSize) + "!" + std::to_string(subStr.size()) + "!" +
                                             deflateString);
  }
  if (deflateBuffer != nullptr) {
    delete[] deflateBuffer;
    deflateBuffer = nullptr;
  }
  return signatureIdx;
}

static uint32 FirstFindOrInsertRepeatString(const std::string &str, bool isHot, uint8 hotType) {
  uint32 index = 0;
  constexpr int kLengthShift = 2;
  auto it = ReflectionAnalysis::GetStr2IdxMap().find(str);
  if (it != ReflectionAnalysis::GetStr2IdxMap().end()) {
    index = it->second;
  } else {
    if (isHot) {
      if (hotType == kLayoutBootHot) {
        uint32 length = ReflectionAnalysis::GetStrTabStartHot().length();
        index = (length << kLengthShift) | (kLayoutBootHot + kCStringShift);  // Use the LSB to indicate hotness.
        ReflectionAnalysis::AddStrTabStartHot(str + '\0');
      } else if (hotType == kLayoutBothHot) {
        uint32 length = ReflectionAnalysis::GetStrTabBothHot().length();
        index = (length << kLengthShift) | (kLayoutBothHot + kCStringShift);  // Use the LSB to indicate hotness.
        ReflectionAnalysis::AddStrTabBothHot(str + '\0');
      } else {
        uint32 length = ReflectionAnalysis::GetStrTabRunHot().length();
        index = (length << kLengthShift) | (kLayoutRunHot + kCStringShift);  // Use the LSB to indicate hotness.
        ReflectionAnalysis::AddStrTabRunHot(str + '\0');
      }
    } else {
      uint32 length = ReflectionAnalysis::GetStrTab().length();
      index = length << kLengthShift;
      ReflectionAnalysis::AddStrTab(str + '\0');
    }
    ReflectionAnalysis::SetStr2IdxMap(str, index);
  }
  return index;
}

void ReflectionAnalysis::InitReflectString() {
  std::string initHot[] = { "V", "Z", "B", "C", "S", "I", "J", "F", "D", "Ljava/lang/String;", "Ljava/lang/Object;" };
  for (auto const &innerType : initHot) {
    (void)FirstFindOrInsertRepeatString(innerType, true, kLayoutBothHot);
  }
}

uint32 ReflectionAnalysis::FindOrInsertRepeatString(const std::string &str, bool isHot, uint8 hotType) {
  if (strTabInited == false) {
    // Add default hot strings.
    strTabInited = true;
  }
  return FirstFindOrInsertRepeatString(str, isHot, hotType);
}

BaseNode *ReflectionAnalysis::GenClassInfoAddr(BaseNode *obj, MIRBuilder *builder) {
  GenMetadataType(builder->GetMirModule());
  MIRClassType *objectType = static_cast<MIRClassType*>(WKTypes::Util::GetJavaLangObjectType());
  BaseNode *classinfoAddress = nullptr;
  if (objectType != nullptr && objectType->GetKind() != kTypeClassIncomplete) {
    classinfoAddress = builder->CreateExprIread(GlobalTables::GetTypeTable().GetRef(),
                                                GlobalTables::GetTypeTable().GetOrCreatePointerType(objectType),
                                                OBJ_KLASS_FIELDID, obj);
  } else {
    // If java.lang.Object type is not defined, fall back to use the classinfo struct to retrieve the first field.
    MIRStructType *classMetadataType = static_cast<MIRStructType*>(
        GlobalTables::GetTypeTable().GetTypeFromTyIdx(ReflectionAnalysis::classMetadataTyIdx));
    classinfoAddress = builder->CreateExprIread(GlobalTables::GetTypeTable().GetRef(),
                                                GlobalTables::GetTypeTable().GetOrCreatePointerType(classMetadataType),
                                                METADATA_KLASS_FIELDID, obj);
  }
  return classinfoAddress;
}

const char *ReflectionAnalysis::klassPtrName = kShadowClassName;
TyIdx ReflectionAnalysis::classMetadataTyIdx = TyIdx(0);
TyIdx ReflectionAnalysis::classMetadataRoTyIdx = TyIdx(0);
TyIdx ReflectionAnalysis::methodsInfoTyIdx = TyIdx(0);
TyIdx ReflectionAnalysis::methodsInfoCompactTyIdx = TyIdx(0);
TyIdx ReflectionAnalysis::fieldsInfoTyIdx = TyIdx(0);
TyIdx ReflectionAnalysis::fieldsInfoCompactTyIdx = TyIdx(0);
TyIdx ReflectionAnalysis::superclassMetadataTyIdx = TyIdx(0);
TyIdx ReflectionAnalysis::invalidIdx = TyIdx(-1);
static constexpr int kModPublic = 1;                 // 0x00000001
static constexpr int kModPrivate = 2;                // 0x00000002
static constexpr int kModProtected = 3;              // 0x00000004
static constexpr int kModStatic = 4;                 // 0x00000008
static constexpr int kModFinal = 5;                  // 0x00000010
static constexpr int kModSynchronized = 6;           // 0x00000020
static constexpr int kModVolatile = 7;               // 0x00000040
static constexpr int kModTransient = 8;              // 0x00000080
static constexpr int kModNative = 9;                 // 0x00000100
static constexpr int kModAbstract = 11;              // 0x00000400
static constexpr int kModStrict = 12;                // 0x00000800
static constexpr int kModSynthetic = 13;             // 0x00001000
static constexpr int kModConstructor = 17;           // 0x00010000
static constexpr int kModDefault = 22;               // 0x00400000
static constexpr int kModBridge = 7;                 // 0x00000040
static constexpr int kModVarargs = 8;                // 0x00000080
static constexpr int kModEnum = 15;                  // 0x00004000
static constexpr int kModDeclaredSynchronized = 18;  // 0x00020000
static constexpr int kModifierRCUnowned = 24;        // 0x00800000
static constexpr int kModifierRCWeak = 25;           // 0x01000000

uint32 GetMethodModifier(FuncAttrs fa) {
  return (static_cast<unsigned char>(fa.GetAttr(FUNCATTR_public)) << (kModPublic - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FUNCATTR_protected)) << (kModProtected - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FUNCATTR_private)) << (kModPrivate - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FUNCATTR_abstract)) << (kModAbstract - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FUNCATTR_static)) << (kModStatic - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FUNCATTR_final)) << (kModFinal - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FUNCATTR_declared_synchronized)) << (kModSynchronized - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FUNCATTR_declared_synchronized)) << (kModDeclaredSynchronized - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FUNCATTR_native)) << (kModNative - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FUNCATTR_strict)) << (kModStrict - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FUNCATTR_synthetic)) << (kModSynthetic - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FUNCATTR_bridge)) << (kModBridge - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FUNCATTR_constructor)) << (kModConstructor - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FUNCATTR_varargs)) << (kModVarargs - 1));
}

uint32 GetFieldModifier(FieldAttrs fa) {
  return (static_cast<unsigned char>(fa.GetAttr(FLDATTR_public)) << (kModPublic - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FLDATTR_protected)) << (kModProtected - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FLDATTR_private)) << (kModPrivate - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FLDATTR_static)) << (kModStatic - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FLDATTR_final)) << (kModFinal - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FLDATTR_transient)) << (kModTransient - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FLDATTR_volatile)) << (kModVolatile - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FLDATTR_synthetic)) << (kModSynthetic - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FLDATTR_enum)) << (kModEnum - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FLDATTR_rcunowned)) << (kModifierRCUnowned - 1)) |
         (static_cast<unsigned char>(fa.GetAttr(FLDATTR_rcweak)) << (kModifierRCWeak - 1));
}

uint32 GetClassAccessFlags(MIRClassType *classType) {
  int32 accessFlag = 0;
  for (MIRPragma *prag : classType->GetPragmVec()) {
    if (prag->GetKind() == kPragmaClass) {
      MapleVector<MIRPragmaElement*> elemVector = prag->GetElementVector();
      for (MIRPragmaElement *elem : elemVector) {
        std::string name = GlobalTables::GetStrTable().GetStringFromStrIdx(elem->GetNameStrIdx());
        if (name == kAccessFlags) {
          accessFlag = elem->GetI32Val();
          return static_cast<uint32>(accessFlag);
        }
      }
    }
  }
  size_t size = classType->GetInfo().size();
  for (size_t i = 0; i < size; i++) {
    if (GlobalTables::GetStrTable().GetStringFromStrIdx(classType->GetInfoElemt(i).first) == kINFOAccessFlags) {
      return classType->GetInfoElemt(i).second;
    }
  }
  return 0;
}

bool ReflectionAnalysis::IsStaticClass(MIRClassType *classType) {
  return GetClassAccessFlags(classType) & 0x00000008;  // #  Modifier_Static 0x00000008;
}

bool ReflectionAnalysis::IsPrivateClass(MIRClassType *classType) {
  return GetClassAccessFlags(classType) & 0x00000002;  // #  Modifier_Private 0x00000002;
}

static inline GStrIdx GetOrCreateGStrIdxFromName(const std::string &name) {
  return GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(NameMangler::GetInternalNameLiteral(name.c_str()));
}

static bool IsFinalize(const std::string &funcName, const std::string &signature) {
  return funcName == "finalize" && signature == "()V";
}

static bool NeedFourBytes(PragmaValueType type) {
  return type == kValueInt || type == kValueByte || type == kValueShort;
}

static std::string GetSignatureFromFullName(const std::string &fullname) {
  size_t pos = fullname.find("|");
  if (pos != std::string::npos) {
    return fullname.substr(pos + 1);
  } else {
    FATAL(kLncFatal, "can not find \"|\" in fullname");
  }
}

int ReflectionAnalysis::SolveAnnotation(MIRClassType *classType, MIRFunction *func) {
  std::string annoArray1;
  std::map<int, int> idxNumMap;
  GeneAnnotation(idxNumMap, annoArray1, classType, kPragmaFunc, func->GetName(), invalidIdx);
  // Parameter annotation.
  std::string annoArray2;
  std::map<int, int> paramNumArray;
  int paramIndex = 0;
  std::map<int, int> paramIdxNumMap;
  GeneAnnotation(paramIdxNumMap, annoArray2, classType, kPragmaParam, func->GetName(), invalidIdx, &paramNumArray,
                 &paramIndex);
  std::string subStr = "";
  if (idxNumMap.empty() && paramIdxNumMap.empty()) {
    subStr += "0";
  } else {
    subStr += std::to_string(idxNumMap.size());
    subStr += "!";
    std::for_each(idxNumMap.begin(), idxNumMap.end(), [&subStr](const std::pair<const int, int> p) {
      subStr += std::to_string(p.second);
      subStr += "!";
    });
    subStr += annoArray1;
    // Parameter.
    subStr += '|';
    subStr += std::to_string(paramIdxNumMap.size());
    subStr += "!";
    std::for_each(paramIdxNumMap.begin(), paramIdxNumMap.end(), [&subStr](const std::pair<const int, int> p) {
      subStr += std::to_string(p.second);
      subStr += "!";
    });
    for (int z = 0; z < paramIndex; z++) {
      subStr += std::to_string(paramNumArray[z]);
      subStr += "!";
    }
    subStr += annoArray2;
  }
  return GetDeflateStringIdx(subStr);
}

uint32 ReflectionAnalysis::GetTypeNameIdxFromType(MIRType *type, const Klass *klass, const std::string &fieldname) {
  uint32 typeNameIdx = 0;
  switch (type->GetKind()) {
    case kTypeScalar: {
      std::string name(GetPrimTypeJavaName(type->GetPrimType()));
      typeNameIdx = FindOrInsertReflectString(name);
      break;
    }
    case kTypePointer: {
      MIRType *ptype = static_cast<MIRPtrType*>(type)->GetPointedType();
      if (ptype->GetKind() == kTypeArray || ptype->GetKind() == kTypeJArray) {
        CHECK_FATAL(dynamic_cast<MIRJarrayType*>(ptype) != nullptr, "null ptr check");
        std::string javaName = dynamic_cast<MIRJarrayType*>(ptype)->GetJavaName();
        std::string klassJavaDescriptor;
        NameMangler::DecodeMapleNameToJavaDescriptor(javaName, klassJavaDescriptor);
        typeNameIdx = FindOrInsertReflectString(klassJavaDescriptor);
      } else if (ptype->GetKind() == kTypeByName || ptype->GetKind() == kTypeClass ||
                 ptype->GetKind() == kTypeInterface || ptype->GetKind() == kTypeClassIncomplete ||
                 ptype->GetKind() == kTypeInterfaceIncomplete || ptype->GetKind() == kTypeConstString) {
        std::string javaName = ptype->GetName();
        std::string klassJavaDescriptor;
        NameMangler::DecodeMapleNameToJavaDescriptor(javaName, klassJavaDescriptor);
        typeNameIdx = FindOrInsertReflectString(klassJavaDescriptor);
      } else {
        CHECK_FATAL(false, "In class %s: field %s 's type is UNKNOWN", klass->GetKlassName().c_str(),
                    fieldname.c_str());
      }
      break;
    }
    default: {
      CHECK_FATAL(false, "In class %s: field %s 's type is UNKNOWN", klass->GetKlassName().c_str(), fieldname.c_str());
    }
  }
  return typeNameIdx;
}

void ReflectionAnalysis::CheckPrivateInnerAndNoSubClass(Klass *clazz, const std::string &annoArr) {
  // LMain_24A_3B  `EC!`VL!24!LMain_3B!`IC!`AF!4!2!name!23!A!
  size_t pos = annoArr.find(kInnerClassPrefix, 0);
  if (pos == std::string::npos) {
    return;
  }
  if (!IsPrivateClass(clazz->GetMIRClassType())) {
    return;  // Check private.
  }
  if (clazz->HasSubKlass()) {
    clazz->SetPrivateInnerAndNoSubClass(false);
  } else {
    clazz->SetPrivateInnerAndNoSubClass(true);
  }
}

uint16 GetCharHashIndex(const std::string &name) {
  unsigned int hashCode = DJBHash(name.c_str());
  return static_cast<uint16>(hashCode % kMethodFieldHashSize);
}

uint16 GenMethodHashIndex(const std::string &name, const std::string &signature) {
  std::string fullName = name + signature;
  size_t p = fullName.find(')');
  CHECK_FATAL(p != std::string::npos, "can not find )");
  std::string subName = fullName.substr(0, p + 1);
  uint16 h = GetCharHashIndex(subName);
  return h;
}

void ReflectionAnalysis::ConvertMethodSig(std::string &signature) {
  size_t signatureSize = signature.size();
  for (size_t i = 1; i < signatureSize; i++) {
    if (signature[i] == 'L') {
      while (signature[++i] != ';')  // eg. Ljava/io/InputStream; so we do not check the boundary.
        ;
    } else if (signature[i] == 'A') {
      signature[i] = '[';
    }
  }
}

void ReflectionAnalysis::GenAllMethodHash(std::vector<std::pair<MethodPair*, int>> &methodInfoVec,
                                          std::unordered_map<uint32, std::string> &baseNameMap,
                                          std::unordered_map<uint32, std::string> &fullNameMap) {
  std::vector<MIRFunction*> methodVector;
  std::vector<uint16> hashVector;
  for (auto &methodInfo : methodInfoVec) {
    MIRSymbol *funcSym = GlobalTables::GetGsymTable().GetSymbolFromStidx(methodInfo.first->first.Idx());
    MIRFunction *func = funcSym->GetFunction();
    std::string baseName = func->GetBaseFuncName();
    baseName = NameMangler::DecodeName(baseName);
    baseNameMap[func->GetBaseFuncNameStrIdx().GetIdx()] = baseName;
    std::string fullName = func->GetBaseFuncNameWithType();
    fullName = NameMangler::DecodeName(fullName);
    fullNameMap[func->GetBaseFuncNameWithTypeStrIdx().GetIdx()] = fullName;
    CHECK_FATAL(fullName.find("|") != std::string::npos, "can not find |");
    std::string signature = fullName.substr(fullName.find("|") + 1);
    ConvertMethodSig(signature);
    uint16 h = GenMethodHashIndex(baseName, signature);
    if (IsFinalize(baseName, signature)) {
      h = kHashConflictFlag;
    }
    func->SetHashCode(h);
    hashVector.push_back(h);
  }
  for (auto &methodInfo : methodInfoVec) {
    MIRSymbol *funcSym = GlobalTables::GetGsymTable().GetSymbolFromStidx(methodInfo.first->first.Idx());
    MIRFunction *func = funcSym->GetFunction();
    uint16 h = func->GetHashCode();
    int c = std::count(hashVector.begin(), hashVector.end(), h);
    if (c > 1) {
      func->SetHashCode(kHashConflictFlag);  // conflict flag
    }
  }
}

void ReflectionAnalysis::GenAllFieldHash(std::vector<std::pair<FieldPair, uint16>> &fieldV) {
  std::vector<MIRFunction*> methodVector;
  std::vector<uint16> hashVector;
  for (auto &field : fieldV) {
    uint16 h = field.second;
    hashVector.push_back(h);
  }
  for (auto &field : fieldV) {
    uint16 h = field.second;
    int c = std::count(hashVector.begin(), hashVector.end(), h);
    if (c > 1) {
      field.second = kHashConflictFlag;  // Conflict flag.
    }
  }
}

uint16 GetFieldHash(std::vector<std::pair<FieldPair, uint16>> &fieldV, FieldPair fieldSources) {
  for (auto &field : fieldV) {
    FieldPair f = field.first;
    if (f == fieldSources) {
      return field.second;
    }
  }
  return 0;
}

static void DelimeterConvert(std::string &str) {
  size_t loc = str.find("`");
  while (loc != std::string::npos) {
    str.replace(loc, 1, "``");
    loc = str.find("`", loc + 2);
  }
  loc = str.find("!");
  while (loc != std::string::npos) {
    str.replace(loc, 1, "`!");
    loc = str.find("!", loc + 2);
  }
  loc = str.find("|");
  while (loc != std::string::npos) {
    str.replace(loc, 1, "`|");
    loc = str.find("|", loc + 2);
  }
}

bool ReflectionAnalysis::RootClassDefined() {
  if (isLibcore < 0) {
    // Check whether this module defines root classes including Class/Object/Fields/Methods.
    Klass *objectKlass = klassh->GetKlassFromLiteral(kJavaLangObjectStr);
    isLibcore = 0;
    if (objectKlass != nullptr && objectKlass->GetMIRStructType()->IsLocal()) {
      isLibcore = 1;
    }
  }
  return (isLibcore == 1);
}

MIRSymbol *ReflectionAnalysis::GetOrCreateSymbol(const std::string &name, TyIdx tyIdx, bool needInit = false) {
  const GStrIdx strIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(name);
  MIRSymbol *st = GetSymbol(strIdx, tyIdx);
  if (st != nullptr && !needInit) {
    // Previous symbol is a forward declaration, create a new symbol for definiton.
    return st;
  }
  st = CreateSymbol(strIdx, tyIdx);
  // Set classinfo symbol as extern if not defined locally.
  if (StringUtils::StartsWith(name, CLASSINFO_PREFIX_STR)) {
    std::string className = name.substr(strlen(CLASSINFO_PREFIX_STR));
    Klass *klass = klassh->GetKlassFromName(className);
    if (klass && !klass->GetMIRStructType()->IsLocal()) {
      st->SetStorageClass(kScExtern);
    }
  }
  return st;
}

MIRSymbol *ReflectionAnalysis::GetSymbol(const std::string &name, TyIdx tyIdx) {
  const GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(name);
  MIRSymbol *st = GetSymbol(stridx, tyIdx);
  return st;
}

static bool IsSameType(TyIdx tyIdx1, TyIdx tyIdx2) {
  if (tyIdx1 == tyIdx2) {
    return true;
  }
  MIRType *type1 = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx1);
  MIRType *type2 = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx2);
  return type1->EqualTo(*type2);
}

MIRSymbol *ReflectionAnalysis::GetSymbol(GStrIdx strIdx, TyIdx tyIdx) {
  MIRSymbol *st = GlobalTables::GetGsymTable().GetSymbolFromStrIdx(strIdx);
  if (st && st->GetSKind() == kStVar && IsSameType(st->GetTyIdx(), tyIdx)) {
    return st;
  }
  return nullptr;
}

MIRSymbol *ReflectionAnalysis::CreateSymbol(GStrIdx strIdx, TyIdx tyIdx) {
  MIRSymbol *st = GlobalTables::GetGsymTable().CreateSymbol(kScopeGlobal);
  st->SetStorageClass(kScGlobal);
  st->SetSKind(kStVar);
  st->SetNameStrIdx(strIdx);
  GlobalTables::GetGsymTable().AddToStringSymbolMap(st);
  st->SetAttr(ATTR_public);
  st->SetTyIdx(tyIdx);
  return st;
}

void ReflectionAnalysis::CompressHighFrequencyStr(std::string &s) {
  if (highFrequencyStrMap.find(s) != highFrequencyStrMap.end()) {
    s = ReflectionAnalysis::highFrequencyStrMap[s];
  }
}

bool ReflectionAnalysis::VtableFunc(const MIRFunction *func) const {
  return (func->GetAttr(FUNCATTR_virtual) && !func->GetAttr(FUNCATTR_private) && !func->GetAttr(FUNCATTR_static));
}

bool RtRetentionPolicyCheck(const MIRSymbol *clInfo) {
  GStrIdx stridx;
  MIRClassType *annoType =
      static_cast<MIRClassType*>(GlobalTables::GetTypeTable().GetTypeFromTyIdx(clInfo->GetTyIdx()));
  for (MIRPragma *p : annoType->GetPragmVec()) {
    if (GlobalTables::GetStrTable().GetStringFromStrIdx(
            GlobalTables::GetTypeTable().GetTypeFromTyIdx(p->GetTyIdx())->GetNameStrIdx()) ==
        (kJavaLangAnnotationRetentionStr)) {
      stridx.SetIdx(p->GetElementVector()[0]->GetU64Val());
      std::string retentionType = GlobalTables::GetStrTable().GetStringFromStrIdx(stridx);
      if (retentionType != "RUNTIME") {
        return false;
      } else {
        return true;
      }
    }
  }
  return false;
}

int16 ReflectionAnalysis::GetMethodInVtabIndex(const Klass *klass, const MIRFunction *func) {
  int methodInVtabIndex = 0;
  bool findMethod = false;
  MIRClassType *classType = klass->GetMIRClassType();
  MIRSymbol *vtableSymbol = GlobalTables::GetGsymTable().GetSymbolFromStrIdx(
      GlobalTables::GetStrTable().GetStrIdxFromName(VTAB_PREFIX_STR + klass->GetKlassName()));
  if (klass->IsClass() && vtableSymbol != nullptr) {
    MIRAggConst *vtableConst = dynamic_cast<MIRAggConst*>(vtableSymbol->GetKonst());
    for (MIRConstPtr &node : vtableConst->GetConstVec()) {
      if (node->GetKind() == kConstAddrofFunc) {
        MIRAddroffuncConst *addr = static_cast<MIRAddroffuncConst*>(node);
        MIRFunction *vtableFunc = GlobalTables::GetFunctionTable().GetFunctionFromPuidx(addr->GetValue());
        // NOTE: In VtableAnalysis::AddMethodToTable, a abstract method will not
        // be added to the vtable if there is already an abstract method of the
        // same name and descriptor (but from a superclass or implemented
        // interface) in the vtable.  Therefore, we cannot compare methods by
        // their GetNameStrIdx() (which includes package+class+method+descriptor),
        // because otherwise we may not find the exact method.
        if (func->GetBaseFuncNameWithTypeStrIdx() == vtableFunc->GetBaseFuncNameWithTypeStrIdx()) {
          findMethod = true;
          break;
        }
      }
      methodInVtabIndex++;
    }
  } else if (klass->IsInterface()) {
    methodInVtabIndex = 0;
    for (MethodPair &methodPair : classType->GetMethods()) {
      MIRSymbol *currSym = GlobalTables::GetGsymTable().GetSymbolFromStidx(methodPair.first.Idx());
      MIRFunction *currFunc = currSym->GetFunction();
      if (func->GetNameStrIdx() == currFunc->GetNameStrIdx()) {
        findMethod = true;
        break;
      }
      methodInVtabIndex++;
    }
  }
  if (!findMethod) {
    constexpr int notFoundMethod = -10;
    methodInVtabIndex = notFoundMethod;
  }
  // Check VtabIndex, int16.
  CHECK_FATAL((methodInVtabIndex > std::numeric_limits<int16>::min()) &&
              (methodInVtabIndex < std::numeric_limits<int16>::max()),
              "Error:the methodInVtabIndex is too large");
  return static_cast<int16>(methodInVtabIndex);
}

void ReflectionAnalysis::GetSignatureTypeNames(const char *signature, std::vector<std::string> &typeNames) {
  int sigLen = strlen(signature);
  int i = 0;
  const char *methodSignature = signature;
  i++;
  while (i < sigLen && methodSignature[i] != ')') {
    std::string descriptor;
    if (methodSignature[i] != 'L' && methodSignature[i] != '[') {
      descriptor += methodSignature[i];
    } else {
      if (methodSignature[i] == '[') {
        while (methodSignature[i] == '[') {
          descriptor += methodSignature[i++];
        }
      }
      if (methodSignature[i] != 'L') {
        descriptor += methodSignature[i];
      } else {
        while (methodSignature[i] != ';') {
          descriptor += methodSignature[i++];
        }
        descriptor += ';';
      }
    }
    typeNames.push_back(descriptor);
    i++;
  }
  // Return type.
  i++;
  typeNames.push_back(methodSignature + i);
}

struct HashCodeComparator {
  std::unordered_map<uint32, std::string> &basenameMp;
  std::unordered_map<uint32, std::string> &fullnameMp;
  HashCodeComparator(std::unordered_map<uint32, std::string> &arg1, std::unordered_map<uint32, std::string> &arg2)
      : basenameMp(arg1), fullnameMp(arg2) {}

  bool operator()(std::pair<MethodPair*, int> a, std::pair<MethodPair*, int> b) {
    MIRSymbol *funcSymA = GlobalTables::GetGsymTable().GetSymbolFromStidx(a.first->first.Idx());
    MIRFunction *funcA = funcSymA->GetFunction();
    auto itB = basenameMp.find(funcA->GetBaseFuncNameStrIdx().GetIdx());
    ASSERT(itB != basenameMp.end(), "check funcAname!");
    std::string funcAName = itB->second;
    auto itF = fullnameMp.find(funcA->GetBaseFuncNameWithTypeStrIdx().GetIdx());
    ASSERT(itF != fullnameMp.end(), "check funcAname!");
    std::string fullNameA = itF->second;
    CHECK_FATAL(fullNameA.find("|") != fullNameA.npos, "not found |");
    std::string signatureA = fullNameA.substr(fullNameA.find("|") + 1);
    MIRSymbol *funcSymB = GlobalTables::GetGsymTable().GetSymbolFromStidx(b.first->first.Idx());
    MIRFunction *funcB = funcSymB->GetFunction();
    itB = basenameMp.find(funcB->GetBaseFuncNameStrIdx().GetIdx());
    ASSERT(itB != basenameMp.end(), "check funcBname!");
    std::string funcBName = itB->second;
    itF = fullnameMp.find(funcB->GetBaseFuncNameWithTypeStrIdx().GetIdx());
    ASSERT(itF != fullnameMp.end(), "check funcBname!");
    std::string fullNameB = itF->second;
    CHECK_FATAL(fullNameB.find("|") != std::string::npos, "not found |");
    std::string signatureB = fullNameB.substr(fullNameB.find("|") + 1);
    // Make bridge the end.
    if ((funcA->GetHashCode() == kHashConflictFlag) && (funcB->GetHashCode() == kHashConflictFlag)) {
      // Only deal with return type is different.
      if ((funcA->GetAttr(FUNCATTR_bridge)) && !(funcB->GetAttr(FUNCATTR_bridge))) {
        return true;
      }
      if (!(funcA->GetAttr(FUNCATTR_bridge)) && (funcB->GetAttr(FUNCATTR_bridge))) {
        return false;
      }
    }
    // As finalize()V is frequency, check it first, we put it at the end method_s.
    if (IsFinalize(funcAName, signatureA) && !IsFinalize(funcBName, signatureB)) {
      return false;
    }
    if (!IsFinalize(funcAName, signatureA) && IsFinalize(funcBName, signatureB)) {
      return true;
    }
    return funcA->GetHashCode() < funcB->GetHashCode();
  }
};

MIRSymbol *ReflectionAnalysis::GenMethodsMetaData(const Klass *klass) {
  MIRClassType *classType = klass->GetMIRClassType();
  if (!classType || classType->GetMethods().empty()) {
    return nullptr;
  }
  size_t arraySize = classType->GetMethods().size();
  MIRStructType *methodsInfoType =
      static_cast<MIRStructType*>(GlobalTables::GetTypeTable().GetTypeFromTyIdx(methodsInfoTyIdx));
  MIRArrayType *arraytype = GlobalTables::GetTypeTable().GetOrCreateArrayType(methodsInfoType, arraySize);
  MIRAggConst *aggconst = mirModule->GetMemPool()->New<MIRAggConst>(mirModule, arraytype);
  std::vector<std::pair<MethodPair*, int>> methodinfoVec;
  for (MethodPair &methodPair : classType->GetMethods()) {
    methodinfoVec.push_back(std::make_pair(&methodPair, -1));
  }

  std::unordered_map<uint32, std::string> basenameMp, fullnameMp;
  GenAllMethodHash(methodinfoVec, basenameMp, fullnameMp);
  // Sort constVec by hashcode.
  HashCodeComparator comparator(basenameMp, fullnameMp);
  std::sort(methodinfoVec.begin(), methodinfoVec.end(), comparator);
  const GStrIdx finalizeMethod = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName("finalize_7C_28_29V");
  // DeclaringClass self.
  for (auto &methodinfo : methodinfoVec) {
    MIRSymbol *funcSym = GlobalTables::GetGsymTable().GetSymbolFromStidx(methodinfo.first->first.Idx());
    reflectionMuidStr += funcSym->GetName();
    MIRFunction *func = funcSym->GetFunction();
    MIRAggConst *newconst = mirModule->GetMemPool()->New<MIRAggConst>(mirModule, methodsInfoType);
    uint32 fieldID = 1;
    uint32 flag = 0;
    if (!VtableFunc(func)) {
      flag |= kMethodNotVirtual;
    }
    if (func->GetBaseFuncNameWithTypeStrIdx() == finalizeMethod) {
      flag |= kMethodFinalize;
    }
    if (func->GetAttr(FUNCATTR_abstract)) {
      flag |= kMethodAbstract;
    }
    uint16 hash = func->GetHashCode();
    flag |= (hash << 6);  // hash 10 bit
    // @method_in_vtable_index
    uint32 methodInVtabIndex = static_cast<uint32>(static_cast<int32>(GetMethodInVtabIndex(klass, func)));
    methodInVtabIndex &= 0xFFFF;
    mirBuilder.AddIntFieldConst(methodsInfoType, newconst, fieldID++, methodInVtabIndex);

    // @declaringclass
    MIRSymbol *dklassSt = GetOrCreateSymbol(CLASSINFO_PREFIX_STR + func->GetBaseClassName(), classMetadataTyIdx);
    mirBuilder.AddAddrofFieldConst(methodsInfoType, newconst, fieldID++, dklassSt);
    // @addr : Function address
    mirBuilder.AddAddroffuncFieldConst(methodsInfoType, newconst, fieldID++, funcSym);

    // @modifier
    uint32 mod = GetMethodModifier(func->GetFuncAttrs());
    // Add default attribute.
    if (klass->IsInterface() && !func->GetAttr(FUNCATTR_abstract) && !func->GetAttr(FUNCATTR_static)) {
      mod |= (1 << (kModDefault));
    }
    mirBuilder.AddIntFieldConst(methodsInfoType, newconst, fieldID++, mod);
    // @methodname
    std::string baseName = basenameMp[func->GetBaseFuncNameStrIdx().GetIdx()];
    uint32 methodnameIdx = FindOrInsertReflectString(baseName);
    mirBuilder.AddIntFieldConst(methodsInfoType, newconst, fieldID++, methodnameIdx);
    // @methodsignature
    std::string fullname = fullnameMp[func->GetBaseFuncNameWithTypeStrIdx().GetIdx()];
    std::string signature = GetSignatureFromFullName(fullname);
    ConvertMethodSig(signature);
    std::vector<std::string> typeNames;
    GetSignatureTypeNames(signature.c_str(), typeNames);
    uint32 signatureIdx = 0;
    signatureIdx = FindOrInsertReflectString(signature);
    mirBuilder.AddIntFieldConst(methodsInfoType, newconst, fieldID++, signatureIdx);
    // @annotation
    int annotationIdx = SolveAnnotation(classType, func);
    mirBuilder.AddIntFieldConst(methodsInfoType, newconst, fieldID++, annotationIdx);
    mirBuilder.AddIntFieldConst(methodsInfoType, newconst, fieldID++, flag);
    // @argsize: Number of arguments.
    size_t argsSize = func->GetParamSize();
    mirBuilder.AddIntFieldConst(methodsInfoType, newconst, fieldID++, argsSize);
#ifndef USE_32BIT_REF
    // @padding
    mirBuilder.AddIntFieldConst(methodsInfoType, newconst, fieldID++, 0);
#endif
    aggconst->GetConstVec().push_back(newconst);
  }
  MIRSymbol *methodsArraySt =
      GetOrCreateSymbol(NameMangler::kMethodsInfoPrefixStr + klass->GetKlassName(), arraytype->GetTypeIndex(), true);
  methodsArraySt->SetStorageClass(kScFstatic);
  methodsArraySt->SetKonst(aggconst);
  return methodsArraySt;
}

MIRSymbol *ReflectionAnalysis::GenSuperClassMetaData(const Klass *klass, std::list<Klass*> superClassList) {
  size_t size = superClassList.size();
  MIRStructType *superclassMetadataType =
      static_cast<MIRStructType*>(GlobalTables::GetTypeTable().GetTypeFromTyIdx(superclassMetadataTyIdx));
  MIRArrayType *arrayType = GlobalTables::GetTypeTable().GetOrCreateArrayType(superclassMetadataType, size);
  MIRAggConst *aggconst = mirModule->GetMemPool()->New<MIRAggConst>(mirModule, arrayType);
  for (auto it = superClassList.begin(); it != superClassList.end(); ++it) {
    MIRSymbol *dklassSt = GetOrCreateSymbol(CLASSINFO_PREFIX_STR + (*it)->GetKlassName(), classMetadataTyIdx);
    MIRAggConst *newconst = mirModule->GetMemPool()->New<MIRAggConst>(mirModule, superclassMetadataType);
    mirBuilder.AddAddrofFieldConst(superclassMetadataType, newconst, 1, dklassSt);
    aggconst->GetConstVec().push_back(newconst);
  }
  MIRSymbol *superclassArraySt =
      GetOrCreateSymbol(SUPERCLASSINFO_PREFIX_STR + klass->GetKlassName(), arrayType->GetTypeIndex(), true);
  // Direct access to superclassinfo is only possible within a .so.
  superclassArraySt->SetStorageClass(kScFstatic);
  superclassArraySt->SetKonst(aggconst);
  return superclassArraySt;
}

static void ConvertFieldName(std::string &fieldname, bool staticfield) {
  // Convert field name to java define name.
  if (staticfield) {
    // Remove class name prefix.
    size_t pos1 = fieldname.find(kClassNameSplitterStr);
    CHECK_FATAL(pos1 != fieldname.npos, "fieldname not found");
    int fieldLength = strlen(kClassNameSplitterStr);
    fieldname = fieldname.substr(pos1 + fieldLength);
  }
  fieldname = NameMangler::DecodeName(fieldname);
}

MIRSymbol *ReflectionAnalysis::GenFieldsMetaData(const Klass *klass) {
  MIRClassType *classType = klass->GetMIRClassType();
  FieldVector fields = classType->GetFields();
  FieldVector staticFields = classType->GetStaticFields();
  ASSERT(fields.size() < fields.max_size() - staticFields.size(), "size too large");
  size_t size = fields.size() + staticFields.size();
  if (size == 0) {
    return nullptr;
  }
  MIRStructType *fieldsInfoType =
      static_cast<MIRStructType*>(GlobalTables::GetTypeTable().GetTypeFromTyIdx(fieldsInfoTyIdx));
  MIRArrayType *arraytype = GlobalTables::GetTypeTable().GetOrCreateArrayType(fieldsInfoType, size);
  MIRAggConst *aggconst = mirModule->GetMemPool()->New<MIRAggConst>(mirModule, arraytype);
  std::vector<std::pair<FieldPair, uint16>> fieldHashvec(size);
  size_t i = 0;
  for (; i < fields.size(); i++) {
    std::string fieldname = GlobalTables::GetStrTable().GetStringFromStrIdx(fields[i].first);
    ConvertFieldName(fieldname, false);
    uint32 hashcode = GetCharHashIndex(fieldname.c_str());
    fieldHashvec[i] = std::make_pair(fields[i], hashcode);
  }
  for (size_t j = 0; j < staticFields.size(); j++) {
    std::string fieldname = GlobalTables::GetStrTable().GetStringFromStrIdx(staticFields[j].first);
    ConvertFieldName(fieldname, true);
    uint32 hashcode = GetCharHashIndex(fieldname.c_str());
    fieldHashvec[i++] = std::make_pair(staticFields[j], hashcode);
  }
  GenAllFieldHash(fieldHashvec);
  // Sort field_hashvec by hashcode.
  std::sort(fieldHashvec.begin(), fieldHashvec.end(),
            [](std::pair<FieldPair, uint16> a, std::pair<FieldPair, uint16> b) {
              maple::uint16 fieldHashA = a.second;
              maple::uint16 fieldHashB = b.second;
              return fieldHashA < fieldHashB;
            });
  std::vector<std::pair<FieldPair, int>> fieldinfoVec(size);
  size_t j = 0;
  size_t k = 0;
  for (auto it = fieldHashvec.begin(); it != fieldHashvec.end(); ++it) {
    FieldPair f = (*it).first;
    if (f.second.second.GetAttr(FLDATTR_static)) {
      fieldinfoVec[j] = std::make_pair(f, -1);
    } else {
      fieldinfoVec[j] = std::make_pair(f, k++);
    }
    j++;
  }
  ASSERT(i == size, "In class %s: %d fields seen, BUT %d fields declared", klass->GetKlassName().c_str(), i, size);
  int idx = 0;
  for (auto &fieldinfo : fieldinfoVec) {
    std::vector<uint8> fieldsCompactLeb128Vec;
    FieldPair fieldP = fieldinfo.first;
    MIRAggConst *newconst = mirModule->GetMemPool()->New<MIRAggConst>(mirModule, fieldsInfoType);
    uint32 fieldID = 1;
    // We'll amend for the fieldname in generated metadata, so we need an original version of fieldname.
    std::string originFieldname = GlobalTables::GetStrTable().GetStringFromStrIdx(fieldP.first);
    std::string fieldname = originFieldname;
    TyIdx fieldTyidx = fieldP.second.first;
    MIRType *ty = GlobalTables::GetTypeTable().GetTypeFromTyIdx(fieldTyidx);
    // Collect the the information about the fieldname and fieldtyidx.
    reflectionMuidStr += originFieldname;
    reflectionMuidStr += ty->GetName();
    bool staticfield = (fieldinfo.second == -1);
    // ==== FieldMetadata ====
    // @offset:
    if (staticfield) {
      // Offset of the static field, we fill the global var address.
      const GStrIdx strIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(
          GlobalTables::GetStrTable().GetStringFromStrIdx(fieldP.first));
      MIRSymbol *gvarSt = GetSymbol(strIdx, fieldTyidx);
      if (gvarSt == nullptr) {
        // If this static field is not used, the symbol will not be generated,
        // so we just generate a weak one here.
        gvarSt = CreateSymbol(strIdx, fieldTyidx);
        gvarSt->SetAttr(ATTR_weak);
        gvarSt->SetAttr(ATTR_static);
      }
      mirBuilder.AddAddrofFieldConst(fieldsInfoType, newconst, fieldID++, gvarSt);
    } else {
      // Offset of the instance field, we fill the index of fields here and let CG to fill in.
      FieldID fldID = mirBuilder.GetStructFieldIDFromNameAndTypeParentFirstFoundInChild(
          klass->GetMIRClassType(), originFieldname.c_str(), fieldP.second.first);
      mirBuilder.AddIntFieldConst(fieldsInfoType, newconst, fieldID++, fldID);
    }
    // @modifier
    FieldAttrs fa = fieldP.second.second;
    mirBuilder.AddIntFieldConst(fieldsInfoType, newconst, fieldID++, GetFieldModifier(fa));
    ConvertFieldName(fieldname, staticfield);
    uint32 fieldname32Idx = FindOrInsertReflectString(fieldname);
    uint32 typeNameIdx = GetTypeNameIdxFromType(ty, klass, fieldname);
    // @flag
    uint16 hash = GetFieldHash(fieldHashvec, fieldP);
    uint16 flag = (hash << 6);  // Hash 10 bit.
    mirBuilder.AddIntFieldConst(fieldsInfoType, newconst, fieldID++, flag);
    // @index
    mirBuilder.AddIntFieldConst(fieldsInfoType, newconst, fieldID++, idx);
    // @type :  Klass for type.
    // It's stored as type name, it's stored as a MIRIntConst.
    mirBuilder.AddIntFieldConst(fieldsInfoType, newconst, fieldID++, typeNameIdx);
    // @fieldname : Offset of the name in *local* strTab.
    // In CG, we need to fill the offset as (__reflection_strtab___$file + offset of name).
    mirBuilder.AddIntFieldConst(fieldsInfoType, newconst, fieldID++, fieldname32Idx);
    //  @annotation
    std::string annoArr;
    std::map<int, int> idxNumMap;
    GeneAnnotation(idxNumMap, annoArr, classType, kPragmaVar, fieldname, ty->GetTypeIndex());
    uint32 annotationIdx = GetAnnoCstrIndex(idxNumMap, annoArr);
    mirBuilder.AddIntFieldConst(fieldsInfoType, newconst, fieldID++, annotationIdx);
    //  @declaring class
    MIRSymbol *dklassSt = GetOrCreateSymbol(CLASSINFO_PREFIX_STR + klass->GetKlassName(), classMetadataTyIdx);
    mirBuilder.AddAddrofFieldConst(fieldsInfoType, newconst, fieldID++, dklassSt);
    aggconst->GetConstVec().push_back(newconst);
    idx++;
  }
  MIRSymbol *fieldsArraySt =
      GetOrCreateSymbol(NameMangler::kFieldsInfoPrefixStr + klass->GetKlassName(), arraytype->GetTypeIndex(), true);
  fieldsArraySt->SetStorageClass(kScFstatic);
  fieldsArraySt->SetKonst(aggconst);
  return fieldsArraySt;
}

void ReflectionAnalysis::ConvertMapleClassName(const std::string &mplClassName, std::string &javaDsp) {
  // Convert classname end with _3B, 3 is strlen("_3B")
  unsigned int len = strlen(kClassSuffix);
  if (mplClassName.size() > len && mplClassName.rfind(kClassSuffix, mplClassName.size() - len) != std::string::npos &&
      false) {
    NameMangler::DecodeMapleNameToJavaDescriptor(mplClassName, javaDsp);
    if (highFrequencyStrMap.find(javaDsp) == highFrequencyStrMap.end()) {
      uint32 idx = ReflectionAnalysis::FindOrInsertReflectString(javaDsp);
      javaDsp = "`" + std::to_string(idx);
    }
  } else {
    javaDsp = mplClassName;
  }
}

std::string ReflectionAnalysis::GetAnnotationValue(MapleVector<MIRPragmaElement*> subelemVector, GStrIdx typestridx) {
  std::string annoArray, tmp;
  GStrIdx stridx;
  annoArray += '[';
  annoArray += std::to_string(subelemVector.size());
  annoArray += '!';
  std::string javaDscp;
  ConvertMapleClassName(GlobalTables::GetStrTable().GetStringFromStrIdx(typestridx), javaDscp);
  annoArray += javaDscp;
  for (MIRPragmaElement *arrayElem : subelemVector) {
    annoArray += '!';
    std::ostringstream oss3;
    annoArray += GlobalTables::GetStrTable().GetStringFromStrIdx(arrayElem->GetNameStrIdx());
    annoArray += '!';
    annoArray += std::to_string(arrayElem->GetType());
    annoArray += '!';
    if (NeedFourBytes(arrayElem->GetType())) {
      annoArray += std::to_string(arrayElem->GetI32Val());
    } else if (arrayElem->GetType() == kValueLong) {
      annoArray += std::to_string(arrayElem->GetI64Val());
    } else if (arrayElem->GetType() == kValueDouble) {
      oss3 << tmp << std::setiosflags(std::ios::scientific) << std::setprecision(16) << arrayElem->GetDoubleVal();
      annoArray += oss3.str();
    } else if (arrayElem->GetType() == kValueFloat) {
      oss3 << tmp << std::setiosflags(std::ios::scientific) << std::setprecision(7) << arrayElem->GetFloatVal();
      annoArray += oss3.str();
    } else if (arrayElem->GetType() == kValueString || arrayElem->GetType() == kValueEnum) {
      stridx.SetIdx(arrayElem->GetU64Val());
      std::string t = GlobalTables::GetStrTable().GetStringFromStrIdx(stridx);
      DelimeterConvert(t);
      ReflectionAnalysis::CompressHighFrequencyStr(t);
      annoArray += t;
    } else if (arrayElem->GetType() == kValueBoolean || arrayElem->GetType() == kValueChar) {
      annoArray += std::to_string(arrayElem->GetU64Val());
    } else if (arrayElem->GetType() == kValueType) {
      stridx.SetIdx(arrayElem->GetU64Val());
      std::string javaDsp;
      ConvertMapleClassName(GlobalTables::GetStrTable().GetStringFromStrIdx(stridx), javaDsp);
      annoArray += javaDsp;
    } else if (arrayElem->GetType() == kValueAnnotation) {
      annoArray += GetAnnotationValue(arrayElem->GetSubElemVec(), arrayElem->GetTypeStrIdx());
    } else if (arrayElem->GetType() == kValueArray) {
      annoArray += GetArrayValue(arrayElem->GetSubElemVec());
    } else {
      annoArray += std::to_string(arrayElem->GetU64Val());
      annoArray += '!';
      annoArray += GlobalTables::GetStrTable().GetStringFromStrIdx(arrayElem->GetNameStrIdx());
      stridx.SetIdx(arrayElem->GetU64Val());
      annoArray += GlobalTables::GetStrTable().GetStringFromStrIdx(stridx);
      annoArray += '!';
    }
  }
  annoArray += ']';
  return annoArray;
}

std::string ReflectionAnalysis::GetArrayValue(MapleVector<MIRPragmaElement*> subelemVector, bool isSN) {
  std::string annoArray;
  GStrIdx stridx;
  annoArray += '[';
  annoArray += std::to_string(subelemVector.size());
  annoArray += '!';
  if (!subelemVector.empty()) {
    annoArray += std::to_string(subelemVector[0]->GetType());
    annoArray += '!';
  }
  for (MIRPragmaElement *arrayElem : subelemVector) {
    std::ostringstream oss3;
    std::string javaDsp;
    ConvertMapleClassName(GlobalTables::GetStrTable().GetStringFromStrIdx(arrayElem->GetTypeStrIdx()), javaDsp);
    std::string typeStr = javaDsp;
    ReflectionAnalysis::CompressHighFrequencyStr(typeStr);
    annoArray += typeStr;
    annoArray += '!';
    std::string type;
    MapleVector<MIRPragmaElement*> subsubelemVector = arrayElem->GetSubElemVec();
    if (arrayElem->GetType() == kValueAnnotation) {
      std::ostringstream oss4;
      oss4 << type << subsubelemVector.size();
      annoArray += oss4.str();
      annoArray += '!';
      for (MIRPragmaElement *annoElem : subsubelemVector) {
        annoArray += GlobalTables::GetStrTable().GetStringFromStrIdx(annoElem->GetNameStrIdx());
        annoArray += '!';
        annoArray += std::to_string(annoElem->GetType());
        annoArray += '!';
        annoArray += GetAnnoValueWithoutArray(annoElem);
        annoArray += '!';
      }
    } else if (NeedFourBytes(arrayElem->GetType())) {
      oss3 << type << arrayElem->GetI32Val();
      annoArray += oss3.str();
    } else if (arrayElem->GetType() == kValueLong) {
      oss3 << type << arrayElem->GetI64Val();
      annoArray += oss3.str();
    } else if (arrayElem->GetType() == kValueDouble) {
      oss3 << type << std::setiosflags(std::ios::scientific) << std::setprecision(16) << arrayElem->GetDoubleVal();
      annoArray += oss3.str();
    } else if (arrayElem->GetType() == kValueFloat) {
      oss3 << type << std::setiosflags(std::ios::scientific) << std::setprecision(7) << arrayElem->GetFloatVal();
      annoArray += oss3.str();
    } else if (arrayElem->GetType() == kValueString || arrayElem->GetType() == kValueEnum) {
      stridx.SetIdx(arrayElem->GetU64Val());
      std::string t = GlobalTables::GetStrTable().GetStringFromStrIdx(stridx);
      DelimeterConvert(t);
      ReflectionAnalysis::CompressHighFrequencyStr(t);
      if (arrayElem->GetType() == kValueString && isSN && t.size() > kMaxOptimiseThreshold) {
        uint32 idx = ReflectionAnalysis::FindOrInsertReflectString(t);
        t = "`" + std::to_string(idx);
      }
      annoArray += t;
    } else if (arrayElem->GetType() == kValueBoolean || arrayElem->GetType() == kValueChar) {
      oss3 << type << arrayElem->GetU64Val();
      annoArray += oss3.str();
    } else if (arrayElem->GetType() == kValueType) {
      stridx.SetIdx(arrayElem->GetU64Val());
      std::string javaDspInner;
      ConvertMapleClassName(GlobalTables::GetStrTable().GetStringFromStrIdx(stridx), javaDspInner);
      annoArray += javaDspInner;
    } else {
      oss3 << type << arrayElem->GetU64Val();
      annoArray += oss3.str();
      annoArray += '!';
      annoArray += GlobalTables::GetStrTable().GetStringFromStrIdx(arrayElem->GetNameStrIdx());
      stridx.SetIdx(arrayElem->GetU64Val());
      annoArray += GlobalTables::GetStrTable().GetStringFromStrIdx(stridx);
      annoArray += '!';
    }
  }
  annoArray += ']';
  return annoArray;
}

std::string ReflectionAnalysis::GetAnnoValueWithoutArray(const MIRPragmaElement *annoElem) {
  std::ostringstream oss;
  std::string tmp, annoArray;
  GStrIdx stridx;
  if (NeedFourBytes(annoElem->GetType())) {
    annoArray += std::to_string(annoElem->GetI32Val());
  } else if (annoElem->GetType() == kValueFloat) {
    annoArray += std::to_string(annoElem->GetFloatVal());
  } else if (annoElem->GetType() == kValueDouble) {
    annoArray += std::to_string(annoElem->GetDoubleVal());
  } else if (annoElem->GetType() == kValueLong) {
    annoArray += std::to_string(annoElem->GetI64Val());
  } else if (annoElem->GetType() == kValueBoolean || annoElem->GetType() == kValueChar) {
    annoArray += std::to_string(annoElem->GetU64Val());
  } else if (annoElem->GetType() == kValueArray) {
    annoArray += GetArrayValue(annoElem->GetSubElemVec());
  } else {
    stridx.SetIdx(annoElem->GetU64Val());
    annoArray += GlobalTables::GetStrTable().GetStringFromStrIdx(stridx);
  }
  return annoArray;
}

int64 ReflectionAnalysis::BKDRHash(const std::string &strname, uint32 seed) {
  const char *name = strname.c_str();
  int64 hash = 0;
  while (*name) {
    hash = hash * seed + (*name++);
  }
  return hash;
}

int64 ReflectionAnalysis::GetHashIndex(const std::string &strname) {
  constexpr int hashSeed = 211;
  return BKDRHash(strname, hashSeed);
}

void ReflectionAnalysis::GenHotClassNameString(const Klass *klass) {
  MIRClassType *classType = klass->GetMIRClassType();
  if (!classType->IsLocal()) {
    // External class.
    return;
  }
  if (!klass->HasNativeMethod()) {
    return;  // It's a cold class, we don't care.
  }
  std::string klassName = klass->GetKlassName();
  std::string klassJavaDescriptor;
  NameMangler::DecodeMapleNameToJavaDescriptor(klassName, klassJavaDescriptor);
  (void)ReflectionAnalysis::FindOrInsertRepeatString(klassJavaDescriptor, true);  // Always used.
}

uint32 ReflectionAnalysis::FindOrInsertReflectString(const std::string &str) {
  uint8 hotType = 0;
  return ReflectionAnalysis::FindOrInsertRepeatString(str, false, hotType);
}

MIRSymbol *ReflectionAnalysis::GetClinitFuncSymbol(const Klass *klass) {
  MIRClassType *classType = klass->GetMIRClassType();
  if (!classType || classType->GetMethods().empty()) {
    return nullptr;
  }
  MIRSymbol *clinitFuncSymbol = nullptr;
  for (MethodPair &methodPair : classType->GetMethods()) {
    MIRSymbol *funcSymA = GlobalTables::GetGsymTable().GetSymbolFromStidx(methodPair.first.Idx());
    MIRFunction *funcA = funcSymA->GetFunction();
    std::string funcName = funcA->GetBaseFuncNameWithType();
    if (funcName == kClinitSuffixStr) {
      clinitFuncSymbol = funcSymA;
      break;
    }
  }
  return clinitFuncSymbol;
}

void ReflectionAnalysis::GenClassMetaData(Klass *klass) {
  MIRClassType *classType = klass->GetMIRClassType();
  if (!classType->IsLocal()) {
    // External class.
    return;
  }


  std::string klassName = klass->GetKlassName();
  reflectionMuidStr += klassName;
  std::string klassJavaDescriptor;
  NameMangler::DecodeMapleNameToJavaDescriptor(klassName, klassJavaDescriptor);
  int64 hashIndex = GetHashIndex(klassJavaDescriptor);
  if (raDebug) {
    LogInfo::MapleLogger(kLlErr) << "========= Gen Class: " << klassJavaDescriptor
                                 << " (" << hashIndex << ") ========" << std::endl;
  }
  MIRStructType *classMetadataROType =
      static_cast<MIRStructType*>(GlobalTables::GetTypeTable().GetTypeFromTyIdx(classMetadataRoTyIdx));
  MIRAggConst *newconst = mirModule->GetMemPool()->New<MIRAggConst>(mirModule, classMetadataROType);
  uint32 fieldID = 1;
  // @classname
  uint32 nameIdx = FindOrInsertReflectString(klassJavaDescriptor);
  mirBuilder.AddIntFieldConst(classMetadataROType, newconst, fieldID++, nameIdx);
  // @iFields: All instance fields.
  int numOfFields = 0;
  bool hasAdded = false;
  if (klass->GetKlassName() == NameMangler::GetInternalNameLiteral(kJavaLangObjectStr)) {
    const GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(
        kFieldsInfoPrefixStr + NameMangler::GetInternalNameLiteral(kJavaLangObjectStr));
    MIRSymbol *fieldsSt = GlobalTables::GetGsymTable().GetSymbolFromStrIdx(stridx);
    if (fieldsSt != nullptr) {
      mirBuilder.AddAddrofFieldConst(classMetadataROType, newconst, fieldID++, fieldsSt);
      hasAdded = true;
    }
  }
  if (!hasAdded) {
    MIRSymbol *fieldsSt = GenFieldsMetaData(klass);
    if (fieldsSt != nullptr) {
      numOfFields = static_cast<MIRAggConst*>(fieldsSt->GetKonst())->GetConstVec().size();
      // All meta data will be weak if dummy constructors.
      mirBuilder.AddAddrofFieldConst(classMetadataROType, newconst, fieldID++, fieldsSt);
    } else {
      mirBuilder.AddIntFieldConst(classMetadataROType, newconst, fieldID++, 0);
    }
  }
  // @methods: All methods.
  int numOfMethods = 0;
  MIRSymbol *methodsSt;
  methodsSt = GenMethodsMetaData(klass);
  if (methodsSt != nullptr) {
    numOfMethods = static_cast<MIRAggConst*>(methodsSt->GetKonst())->GetConstVec().size();
    mirBuilder.AddAddrofFieldConst(classMetadataROType, newconst, fieldID++, methodsSt);
  } else {
    mirBuilder.AddIntFieldConst(classMetadataROType, newconst, fieldID++, 0);
  }
  // @superclass: Super class and a list of implemented interfaces.
  std::list<Klass*> superClassList;
  bool missingSuper = false;
  for (Klass *superClass : klass->GetSuperKlasses()) {
    superClassList.push_back(superClass);
  }
  for (TyIdx const kTyIdx : classType->GetInerfaceImplemented()) {
    Klass *interface = klassh->GetKlassFromTyIdx(kTyIdx);
    if (interface == nullptr) {
      missingSuper = true;
      MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(kTyIdx);
      LogInfo::MapleLogger() << "Error: Interface " << static_cast<MIRStructType*>(type)->GetName() << " is not found"
                             << std::endl;
    }
    std::list<Klass*>::iterator it = std::find(superClassList.begin(), superClassList.end(), interface);
    if (it == superClassList.end()) {
      superClassList.push_back(interface);
    }
  }
  if (missingSuper) {
    LogInfo::MapleLogger(kLlErr) << "Error: Missing interface for " << klass->GetKlassName() << std::endl;
    CHECK_FATAL(0, "Missing interface");
  }
  size_t superClassSize = superClassList.size();
  if (superClassSize >= 1) {
    MIRSymbol *superClassSymbolType = GenSuperClassMetaData(klass, superClassList);
    mirBuilder.AddAddrofFieldConst(classMetadataROType, newconst, fieldID++, superClassSymbolType);
  } else {
    mirBuilder.AddIntFieldConst(classMetadataROType, newconst, fieldID++, 0);
  }
  // @numoffields: Num of fields (own).
  CHECK_FATAL(numOfFields <= 0xffff, "Error:the num of fields is too large");
  mirBuilder.AddIntFieldConst(classMetadataROType, newconst, fieldID++, numOfFields);
  // @numofmethods: Num of methods in vtable.
  CHECK_FATAL(numOfMethods <= 0xffff, "Error:the num of methods is too large");
  mirBuilder.AddIntFieldConst(classMetadataROType, newconst, fieldID++, numOfMethods);
  // Do annotation.
  std::string annoArray;
  std::map<int, int> idxNumMap;
  GeneAnnotation(idxNumMap, annoArray, classType, kPragmaClass, klass->GetKlassName(), invalidIdx);
  bool isAnonymous = IsAnonymousClass(annoArray);
  CheckPrivateInnerAndNoSubClass(klass, annoArray);

#ifndef USE_32BIT_REF
  // @flag
  // Array class and primitive class is not generated by compiler.
  uint32 flag = klass->GetFlag(kClassHasFinalizer | CLASS_REFERENCE | kClassFinalizerreferenceSentinel);
  flag = isAnonymous ? (flag | kClassIsanonymousclass) : flag;
  mirBuilder.AddIntFieldConst(classMetadataROType, newconst, fieldID++, flag);
  // @numofsuperclasses
  CHECK_FATAL(superClassSize <= 0xffff, "Error:the size of superClass is too big");
  mirBuilder.AddIntFieldConst(classMetadataROType, newconst, fieldID++, superClassSize);
  // @padding
  mirBuilder.AddIntFieldConst(classMetadataROType, newconst, fieldID++, 0);
#endif  // USE_32BIT_REF
  // @modifier: For class fill ClassAccessFlags.
  uint32 modifier = GetClassAccessFlags(classType);
  mirBuilder.AddIntFieldConst(classMetadataROType, newconst, fieldID++, modifier);
  // @annotation: Set annotation field.
  SetAnnoFieldConst(classMetadataROType, newconst, fieldID++, idxNumMap, annoArray);
  // @ClinitFuncAddr
  MIRSymbol *clinitFuncSym = GetClinitFuncSymbol(klass);
  if (clinitFuncSym != nullptr) {
    mirBuilder.AddAddroffuncFieldConst(classMetadataROType, newconst, fieldID++, clinitFuncSym);
  } else {
    mirBuilder.AddIntFieldConst(classMetadataROType, newconst, fieldID++, 0);
  }
  MIRSymbol *classMetadataROSymbolType =
      GetOrCreateSymbol(CLASSINFO_RO_PREFIX_STR + klass->GetKlassName(), classMetadataRoTyIdx, true);
  classMetadataROSymbolType->SetStorageClass(kScFstatic);
  classMetadataROSymbolType->SetKonst(newconst);
  // Class Metadata definition start here.
  MIRStructType *classMetadataType =
      static_cast<MIRStructType*>(GlobalTables::GetTypeTable().GetTypeFromTyIdx(classMetadataTyIdx));
  newconst = mirModule->GetMemPool()->New<MIRAggConst>(mirModule, classMetadataType);
  fieldID = 1;
  // @shadow: multiplex used for def index.
  mirBuilder.AddIntFieldConst(classMetadataType, newconst, fieldID++, 0);
  // @monitor: multiplex used for class hash.
  mirBuilder.AddIntFieldConst(classMetadataType, newconst, fieldID++, hashIndex);
  // @class loader: Use maximum value unsigned(-1) as non-initialized flag.
  mirBuilder.AddIntFieldConst(classMetadataType, newconst, fieldID++, static_cast<uint16>(-1));
  // @objsize: Fill this in the CG.
  mirBuilder.AddIntFieldConst(classMetadataType, newconst, fieldID++, 0);
#ifdef USE_32BIT_REF
  // @flag
  // Array class and primitive class is not generated by compiler.
  uint32 flag = klass->GetFlag(kClassHasFinalizer | CLASS_REFERENCE | kClassFinalizerreferenceSentinel);
  flag = isAnonymous ? (flag | kClassIsanonymousclass) : flag;
  mirBuilder.AddIntFieldConst(classMetadataType, newconst, fieldID++, flag);
  // @numofsuperclasses
  CHECK_FATAL(superClassSize <= 0xffff, "Error:the size of superClass is too big");
  mirBuilder.AddIntFieldConst(classMetadataType, newconst, fieldID++, superClassSize);
#endif  // USE_32BIT_REF
  // @itab
  GStrIdx strIdx = GlobalTables::GetStrTable().GetStrIdxFromName(ITAB_PREFIX_STR + klass->GetKlassName());
  if (strIdx != 0) {
    MIRSymbol *itableSymbolType = GlobalTables::GetGsymTable().GetSymbolFromStrIdx(strIdx);
    mirBuilder.AddAddrofFieldConst(classMetadataType, newconst, fieldID++, itableSymbolType);
  } else {
    mirBuilder.AddIntFieldConst(classMetadataType, newconst, fieldID++, 0);
  }
  // @vtab
  strIdx = GlobalTables::GetStrTable().GetStrIdxFromName(VTAB_PREFIX_STR + klass->GetKlassName());
  if (strIdx != 0) {
    MIRSymbol *vtableSymbolType = GlobalTables::GetGsymTable().GetSymbolFromStrIdx(strIdx);
    mirBuilder.AddAddrofFieldConst(classMetadataType, newconst, fieldID++, vtableSymbolType);
  } else {
    mirBuilder.AddIntFieldConst(classMetadataType, newconst, fieldID++, 0);
  }
  // @gctib
  MIRSymbol *gctibSt = GetOrCreateSymbol(GCTIB_PREFIX_STR + klass->GetKlassName(),
                                         GlobalTables::GetTypeTable().GetVoidPtr()->GetTypeIndex(), false);
  if (klass->GetKlassName() != NameMangler::GetInternalNameLiteral(kJavaLangObjectStr)) {
    // Direct access to gctib is only possible within a .so, for most classes.
    gctibSt->SetStorageClass(kScFstatic);
  }
  mirBuilder.AddAddrofFieldConst(classMetadataType, newconst, fieldID++, gctibSt);
  // @classinfo ro.
  mirBuilder.AddAddrofFieldConst(classMetadataType, newconst, fieldID++, classMetadataROSymbolType);
  // Set default value to class initialization state.
  // If this class and its parents do not have clinit, we do not clinit-check for this class.
  if (klassh->NeedClinitCheckRecursively(klass)) {
    MIRType *ptrType = GlobalTables::GetTypeTable().GetPtr();
    MIRSymbol *classInitProtectRegion = mirBuilder.GetOrCreateSymbol(
        ptrType->GetTypeIndex(), kClassInitProtectRegionStr, kStVar, kScExtern, nullptr, kScopeGlobal, true);
    classInitProtectRegion->SetAttr(ATTR_extern);
    mirBuilder.AddAddrofFieldConst(classMetadataType, newconst, fieldID++, classInitProtectRegion);
  } else {
    MIRType *clinitState = GlobalTables::GetTypeTable().GetUInt64();
    // The class initialization state is modified to classStateInitialized.
    MIRSymbol *classInfo = mirBuilder.GetOrCreateGlobalDecl(kClassStateInitializedStr, clinitState);
    mirBuilder.AddAddrofFieldConst(classMetadataType, newconst, fieldID++, classInfo);
  }
  // Finally generate class metadata here.
  MIRSymbol *classSt = GetOrCreateSymbol(CLASSINFO_PREFIX_STR + klass->GetKlassName(), classMetadataTyIdx, true);
  classSt->SetKonst(newconst);
  classTab.push_back(classSt);
}

void ReflectionAnalysis::SetAnnoFieldConst(const MIRStructType *metadataRoType, MIRAggConst *newconst, uint32 fieldid,
                                           std::map<int, int> &idxNumMap, const std::string &annoArr) {
  size_t annoNum = idxNumMap.size();
  if (annoNum == 0) {
    std::string subStr = "0!0";
    uint32 signatureIdx = FindOrInsertReflectString(subStr);
    mirBuilder.AddIntFieldConst(metadataRoType, newconst, fieldid, signatureIdx);
  } else {
    std::string subStr = std::to_string(annoNum);
    subStr += "!";
    std::for_each(idxNumMap.begin(), idxNumMap.end(), [&subStr](const std::pair<const int, int> p) {
      subStr += std::to_string(p.second);
      subStr += "!";
    });
    subStr += annoArr;
    uint32 signatureIdx = GetDeflateStringIdx(subStr);
    mirBuilder.AddIntFieldConst(metadataRoType, newconst, fieldid, signatureIdx);
  }
}


void ReflectionAnalysis::GeneAnnotation(std::map<int, int> &idxNumMap, std::string &annoArr, MIRClassType *classType,
                                        PragmaKind paragKind, const std::string &paragName, TyIdx fieldTypeIdx,
                                        std::map<int, int> *paramnumArray, int *paramIndex) {
  int annoNum = 0;
  std::string cmpString = "";
  for (MIRPragma *prag : classType->GetPragmVec()) {
    if (paragKind == kPragmaVar) {
      cmpString = NameMangler::DecodeName(GlobalTables::GetStrTable().GetStringFromStrIdx(prag->GetStrIdx()));
    } else {
      cmpString = GlobalTables::GetStrTable().GetStringFromStrIdx(prag->GetStrIdx());
    }
    bool validTypeFlag = false;
    if (prag->GetTyIdxEx() == fieldTypeIdx || fieldTypeIdx == invalidIdx) {
      validTypeFlag = true;
    }
    if (prag->GetKind() == paragKind && paragName == cmpString && validTypeFlag) {
      MapleVector<MIRPragmaElement*> elemVector = prag->GetElementVector();
      MIRSymbol *clInfo = GlobalTables::GetGsymTable().GetSymbolFromStrIdx(
          GlobalTables::GetTypeTable().GetTypeFromTyIdx(prag->GetTyIdx())->GetNameStrIdx());
      if (clInfo != nullptr) {
        if (!RtRetentionPolicyCheck(clInfo)) {
          continue;
        }
      }
      annoNum++;
      idxNumMap[annoNum - 1] = 0;
      GStrIdx gindex = GlobalTables::GetTypeTable().GetTypeFromTyIdx(prag->GetTyIdx())->GetNameStrIdx();
      std::string pregTypeString = GlobalTables::GetStrTable().GetStringFromStrIdx(gindex);
      std::string klassJavaDescriptor;
      ConvertMapleClassName(pregTypeString, klassJavaDescriptor);
      ReflectionAnalysis::CompressHighFrequencyStr(klassJavaDescriptor);
      annoArr += klassJavaDescriptor;
      annoArr += "!";
      if (paramnumArray) {
        CHECK_FATAL(paramIndex, "null ptr check");
        (*paramnumArray)[(*paramIndex)++] = prag->GetParamNum();
      }
      for (MIRPragmaElement *elem : elemVector) {
        idxNumMap[annoNum - 1]++;
        std::string convertTmp =
            NameMangler::DecodeName(GlobalTables::GetStrTable().GetStringFromStrIdx(elem->GetNameStrIdx()));
        ReflectionAnalysis::CompressHighFrequencyStr(convertTmp);
        annoArr += convertTmp;
        GStrIdx stridx;
        annoArr += "!";
        std::ostringstream oss;
        std::string tmp;
        annoArr += std::to_string(elem->GetType());
        annoArr += "!";
        MapleVector<MIRPragmaElement*> subelemVector = elem->GetSubElemVec();
        switch (elem->GetType()) {
          CaseCondition(annoArr, elem) case kValueAnnotation : annoArr +=
                                                               GetAnnotationValue(subelemVector, elem->GetTypeStrIdx());
          break;
          case kValueArray:
            break;
          default:
            stridx.SetIdx(elem->GetU64Val());
            std::string javaDescriptor;
            ConvertMapleClassName(GlobalTables::GetStrTable().GetStringFromStrIdx(stridx), javaDescriptor);
            annoArr += javaDescriptor;
        }
        annoArr += "!";
      }
    }
  }
}

uint32 ReflectionAnalysis::GetAnnoCstrIndex(std::map<int, int> &idxNumMap, const std::string &annoArr) {
  size_t annoNum = idxNumMap.size();
  uint32 signatureIdx = 0;
  if (annoNum == 0) {
    std::string subStr = "0!0";
    signatureIdx = FindOrInsertReflectString(subStr);
  } else {
    std::string subStr = std::to_string(annoNum);
    subStr += "!";
    std::for_each(idxNumMap.begin(), idxNumMap.end(), [&subStr](const std::pair<const int, int> p) {
      subStr += std::to_string(p.second);
      subStr += "!";
    });
    subStr += annoArr;
    signatureIdx = GetDeflateStringIdx(subStr);
  }
  return signatureIdx;
}

bool ReflectionAnalysis::IsAnonymousClass(const std::string &annotationString) {
  // eg: `IC!`AF!4!0!name!30!!
  size_t pos = annotationString.find(kAnonymousClassPrefix, 0);
  if (pos != std::string::npos) {
    int i = kAnonymousClassIndex;
    while (i--) {
      pos = annotationString.find("!", pos + 1);
      CHECK_FATAL(pos != std::string::npos, "Error:annotationString in func: isAnonymousClass()");
    }
    int annotationLength = strlen(kAnonymousClassSuffix);
    if (annotationString.substr(pos + 1, annotationLength) == kAnonymousClassSuffix) {
      return true;
    }
  }
  return false;
}

TyIdx ReflectionAnalysis::GenMetaStructType(MIRModule *mirModule, MIRStructType &metatype, const std::string &str) {
  const GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(str);
  TyIdx tyidx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&metatype);
  // Global?
  mirModule->GetTypeNameTab()->SetGStrIdxToTyIdx(stridx, tyidx);
  mirModule->GetTypeDefOrder().push_back(stridx);
  const size_t globalTypeTableSize = GlobalTables::GetTypeTable().GetTypeTable().size();
  CHECK_FATAL(globalTypeTableSize > tyidx.GetIdx(), "null ptr check");
  if (GlobalTables::GetTypeTable().GetTypeTable()[tyidx.GetIdx()]->GetNameStrIdx() == 0) {
    GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyidx)->GetNameStrIdx() = stridx;
  }
  return tyidx;
}

MIRType *ReflectionAnalysis::GetRefFieldType(MIRBuilder *mirbuilder) {
#ifdef USE_32BIT_REF
  return GlobalTables::GetTypeTable().GetUInt32();
#else
  return GlobalTables::GetTypeTable().GetVoidPtr();
#endif  // USE_32BIT_REF
}

void ReflectionAnalysis::GenMetadataType(MIRModule *mirModule) {
  if (classMetadataTyIdx != 0)
  // Types have been generated.
  {
    return;
  }
  MIRBuilder &mirBuilder = *(mirModule->GetMIRBuilder());
  // ClassMetaType
  MIRType *typeU8 = GlobalTables::GetTypeTable().GetUInt8();
  MIRType *typeU16 = GlobalTables::GetTypeTable().GetUInt16();
  MIRType *typeI32 = GlobalTables::GetTypeTable().GetInt32();
  MIRType *typeU32 = GlobalTables::GetTypeTable().GetUInt32();
  MIRType *typeI64 = GlobalTables::GetTypeTable().GetInt64();
  MIRType *typeU64 = GlobalTables::GetTypeTable().GetUInt64();
  MIRType *typeVoidPtr = GlobalTables::GetTypeTable().GetVoidPtr();
  MIRStructType classMetadataType(kTypeStruct);
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataType, kShadowStr, GetRefFieldType(&mirBuilder));
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataType, kMonitorStr, typeI32);
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataType, kClassloaderStr, typeU16);
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataType, kObjsizeStr, typeU16);
#ifdef USE_32BIT_REF
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataType, kFlagStr, typeU16);
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataType, kNumofsuperclassesStr, typeU16);
#endif  // USE_32BIT_REF
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataType, kItabStr, typeVoidPtr);
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataType, kVtabStr, typeVoidPtr);
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataType, kGctibStr, typeVoidPtr);
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataType, kClassinforoStr, typeVoidPtr);
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataType, kClinitbridgeStr, typeVoidPtr);
  classMetadataTyIdx = GenMetaStructType(mirModule, classMetadataType, kClassMetadataTypeName);
  MIRStructType classMetadataROType(kTypeStruct);
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataROType, kClassnameStr, typeVoidPtr);
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataROType, kIfieldsStr, typeVoidPtr);
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataROType, kMethodsStr, typeVoidPtr);
  // For array, this is component class; For primitive type, this is nullptr;
  // For general class, this is superclass (only one superclass), this is a pointer to a superclass&interface array.
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataROType, kSuperclassOrComponentclassStr, typeVoidPtr);
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataROType, kNumoffieldsStr, typeU16);
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataROType, kNumofmethodsStr, typeU16);
#ifndef USE_32BIT_REF
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataROType, kFlagStr, typeU16);
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataROType, kNumofsuperclassesStr, typeU16);
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataROType, kPaddingStr, typeU32);
#endif  // USE_32BIT_REF
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataROType, kModStr, typeI32);
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataROType, kAnnotationStr, typeI32);
  GlobalTables::GetTypeTable().AddFieldToStructType(&classMetadataROType, kClinitAddrStr, typeI32);
  classMetadataRoTyIdx = GenMetaStructType(mirModule, classMetadataROType, kClassMetadataRoTypeName);
  // MethodInfoType.
  MIRStructType methodInfoType(kTypeStruct);
#ifdef USE_32BIT_REF
  GlobalTables::GetTypeTable().AddFieldToStructType(&methodInfoType, kMethodInVtabIndexStr, typeI32);
  GlobalTables::GetTypeTable().AddFieldToStructType(&methodInfoType, kDeclaringclassStr, typeI32);
  GlobalTables::GetTypeTable().AddFieldToStructType(&methodInfoType, kAddrStr, typeI32);
#else
  GlobalTables::GetTypeTable().AddFieldToStructType(&methodInfoType, kMethodInVtabIndexStr, typeI64);
  GlobalTables::GetTypeTable().AddFieldToStructType(&methodInfoType, kDeclaringclassStr, typeI64);
  GlobalTables::GetTypeTable().AddFieldToStructType(&methodInfoType, kAddrStr, typeI64);
#endif
  GlobalTables::GetTypeTable().AddFieldToStructType(&methodInfoType, kModStr, typeI32);
  GlobalTables::GetTypeTable().AddFieldToStructType(&methodInfoType, kMethodnameStr, typeI32);
  GlobalTables::GetTypeTable().AddFieldToStructType(&methodInfoType, kSignaturenameStr, typeI32);
  GlobalTables::GetTypeTable().AddFieldToStructType(&methodInfoType, kAnnotationvalueStr, typeI32);
  GlobalTables::GetTypeTable().AddFieldToStructType(&methodInfoType, kFlagStr, typeU16);
  GlobalTables::GetTypeTable().AddFieldToStructType(&methodInfoType, kArgsizeStr, typeU16);
#ifndef USE_32BIT_REF
  GlobalTables::GetTypeTable().AddFieldToStructType(&methodInfoType, kPaddingStr, typeU32);
#endif  // USE_32BIT_REF
  methodsInfoTyIdx = GenMetaStructType(mirModule, methodInfoType, kMethodInfoTypeName);
  // MethodInfoCompactType.
  MIRStructType methodInfoCompactType(kTypeStruct);
  GlobalTables::GetTypeTable().AddFieldToStructType(&methodInfoCompactType, kMethodInVtabIndexStr, typeI32);
  GlobalTables::GetTypeTable().AddFieldToStructType(&methodInfoCompactType, kAddrStr, typeI32);
  GlobalTables::GetTypeTable().AddFieldToStructType(&methodInfoCompactType, kLebPadding0Str, typeU8);
  methodsInfoCompactTyIdx = GenMetaStructType(mirModule, methodInfoCompactType, kMethodInfoCompactTypeName);
  // FieldInfoType.
  MIRStructType fieldInfoType(kTypeStruct);
#ifndef USE_32BIT_REF
  GlobalTables::GetTypeTable().AddFieldToStructType(&fieldInfoType, kOffsetStr, typeU64);
#else
  GlobalTables::GetTypeTable().AddFieldToStructType(&fieldInfoType, kOffsetStr, typeI32);
#endif  // USE_32BIT_REF
  GlobalTables::GetTypeTable().AddFieldToStructType(&fieldInfoType, kModStr, typeU32);
  GlobalTables::GetTypeTable().AddFieldToStructType(&fieldInfoType, kFlagStr, typeU16);
  GlobalTables::GetTypeTable().AddFieldToStructType(&fieldInfoType, kIndexStr, typeU16);
#ifndef USE_32BIT_REF
  GlobalTables::GetTypeTable().AddFieldToStructType(&fieldInfoType, kTypeNameStr, typeI64);
#else
  GlobalTables::GetTypeTable().AddFieldToStructType(&fieldInfoType, kTypeNameStr, typeI32);
#endif  // USE_32BIT_REF
  GlobalTables::GetTypeTable().AddFieldToStructType(&fieldInfoType, kFieldnameStr, typeU32);
  GlobalTables::GetTypeTable().AddFieldToStructType(&fieldInfoType, kAnnotationStr, typeU32);
  GlobalTables::GetTypeTable().AddFieldToStructType(&fieldInfoType, kDeclaringclassStr, GetRefFieldType(&mirBuilder));
  fieldsInfoTyIdx = GenMetaStructType(mirModule, fieldInfoType, kFieldInfoTypeName);
  // FieldInfoType Compact.
  MIRStructType fieldInfoCompactType(kTypeStruct);
  GlobalTables::GetTypeTable().AddFieldToStructType(&fieldInfoCompactType, kOffsetStr, typeU32);
  GlobalTables::GetTypeTable().AddFieldToStructType(&fieldInfoCompactType, kLebPadding0Str, typeU8);
  fieldsInfoCompactTyIdx = GenMetaStructType(mirModule, fieldInfoCompactType, kFieldInfoCompactTypeName);
  // SuperClassMetaType.
  MIRStructType superclassMetadataType(kTypeStruct);
  GlobalTables::GetTypeTable().AddFieldToStructType(&superclassMetadataType, kSuperclassinfoStr, typeVoidPtr);
  superclassMetadataTyIdx = GenMetaStructType(mirModule, superclassMetadataType, kSuperclassMetadataTypeName);
}

void ReflectionAnalysis::GenClassHashMetaData() {
  MIRType *type = GlobalTables::GetTypeTable().GetVoidPtr();
  CHECK_FATAL(type != nullptr, "type is null in ReflectionAnalysis::GenClassHashMetaData");
  if (raDebug) {
    LogInfo::MapleLogger(kLlErr) << "========= HASH TABLE ========" << std::endl;
  }
  if (classTab.empty()) {
    return;
  }
  std::string bucketName = NameMangler::kMuidClassMetadataBucketPrefixStr + mirModule->GetFileNameAsPostfix();
  size_t bucketArraySize = classTab.size();
  MIRArrayType *bucketArraytype = GlobalTables::GetTypeTable().GetOrCreateArrayType(type, bucketArraySize);
  MIRSymbol *bucketSt = GetOrCreateSymbol(bucketName, bucketArraytype->GetTypeIndex(), true);
  MIRAggConst *bucketAggconst = mirModule->GetMemPool()->New<MIRAggConst>(mirModule, bucketArraytype);
  if (bucketAggconst == nullptr) {
    return;
  }
  for (MIRSymbol *classSt : classTab) {
    AddrofNode *classExpr = mirBuilder.CreateExprAddrof(0, classSt);
    MIRType *ptrType = GlobalTables::GetTypeTable().GetTypeTable()[PTY_ptr];
    MIRConst *classConst =
        mirModule->GetMemPool()->New<MIRAddrofConst>(classExpr->GetStIdx(), classExpr->GetFieldID(), ptrType);
    bucketAggconst->GetConstVec().push_back(classConst);
  }
  bucketSt->SetKonst(bucketAggconst);
}

static void ReflectionAnalysisGenStrTab(MIRModule *mirModule, const std::string &strTab,
                                        const std::string &strtabName) {
  MIRBuilder &mirBuilder = *(mirModule->GetMIRBuilder());
  size_t strtabSize = strTab.length();
  if (strtabSize == 1) {
    return;
  }
  MIRArrayType *strtabType =
      GlobalTables::GetTypeTable().GetOrCreateArrayType(GlobalTables::GetTypeTable().GetUInt8(), strtabSize);
  MIRSymbol *strtabSt = mirBuilder.CreateGlobalDecl(strtabName.c_str(), strtabType);
  MIRAggConst *strtabAggconst = mirModule->GetMemPool()->New<MIRAggConst>(mirModule, strtabType);
  if (strtabAggconst == nullptr) {
    return;
  }
  strtabSt->SetStorageClass(kScFstatic);
  for (const char &c : strTab) {
    MIRConst *newconst = mirModule->GetMemPool()->New<MIRIntConst>(c, GlobalTables::GetTypeTable().GetUInt8());
    strtabAggconst->GetConstVec().push_back(newconst);
  }
  strtabSt->SetKonst(strtabAggconst);
}

void ReflectionAnalysis::GenStrTab(MIRModule *mirModule) {
  // Hot string tab.
  std::string hotStrtabName = NameMangler::kReflectionStartHotStrtabPrefixStr + mirModule->GetFileNameAsPostfix();
  ReflectionAnalysisGenStrTab(mirModule, strTabStartHot, hotStrtabName);
  hotStrtabName = NameMangler::kReflectionBothHotStrTabPrefixStr + mirModule->GetFileNameAsPostfix();
  ReflectionAnalysisGenStrTab(mirModule, strTabBothHot, hotStrtabName);
  hotStrtabName = NameMangler::kReflectionRunHotStrtabPrefixStr + mirModule->GetFileNameAsPostfix();
  ReflectionAnalysisGenStrTab(mirModule, strTabRunHot, hotStrtabName);
  // Cold string tab.
  std::string strtabName = NameMangler::kReflectionStrtabPrefixStr + mirModule->GetFileNameAsPostfix();
  ReflectionAnalysisGenStrTab(mirModule, strTab, strtabName);
}

void ReflectionAnalysis::MarkWeakMethods() {
  GStrIdx classNames[] = { GetOrCreateGStrIdxFromName(kJavaLangClassStr),
                           GetOrCreateGStrIdxFromName(kJavaLangObjectStr),
                           GetOrCreateGStrIdxFromName(kReflectionReferencePrefixStr) };
  for (GStrIdx nameIdx : classNames) {
    Klass *klass = klassh->GetKlassFromStrIdx(nameIdx);
    if (klass == nullptr) {
      continue;
    }
    MIRClassType *classType = klass->GetMIRClassType();
    for (MethodPair const &methodPair : classType->GetMethods()) {
      MIRSymbol *funcSym = GlobalTables::GetGsymTable().GetSymbolFromStidx(methodPair.first.Idx());
      MIRFunction *mirfunc = funcSym->GetFunction();
      if (RootClassDefined()) {
        mirfunc->SetAttr(FUNCATTR_weak);  // It's marked weak since RT-first.
      } else {
        mirfunc->SetAttr(FUNCATTR_extern);
      }
    }
  }
}

void ReflectionAnalysis::Run() {
  MarkWeakMethods();
  GenMetadataType(mirModule);
  const MapleVector<Klass*> &klasses = klassh->GetTopoSortedKlasses();
  if (raDebug) {
    LogInfo::MapleLogger(kLlErr) << "========= Gen Class: Total " << klasses.size() << " ========" << std::endl;
  }
  // Cluster classname together in reflection string table to improve the locality.
  for (Klass *klass : klasses) {
    GenHotClassNameString(klass);
  }
  for (Klass *klass : klasses) {
    GenClassMetaData(klass);
    // Collect the full information about the classmetadata.
    reflectionMuidStr = GetMUID(reflectionMuidStr).ToStr();
  }
  reflectionMuidStr += MUIDReplacement::GetMplMd5().ToStr();
  MUIDReplacement::SetMplMd5(GetMUID(reflectionMuidStr));
  reflectionMuidStr.clear();
  reflectionMuidStr.shrink_to_fit();
  GenClassHashMetaData();
}

AnalysisResult *DoReflectionAnalysis::Run(MIRModule *module, ModuleResultMgr *mrm) {
  MemPool *memPool = mempoolctrler.NewMemPool("ReflectionAnalysis mempool");
  KlassHierarchy *kh = static_cast<KlassHierarchy*>(mrm->GetAnalysisResult(MoPhase_CHA, module));
  maple::MIRBuilder mirBuilder(module);
  ReflectionAnalysis *rv = memPool->New<ReflectionAnalysis>(module, memPool, kh, mirBuilder);
  if (rv == nullptr) {
    CHECK_FATAL(false, "failed to allocate memory");
  }
  rv->Run();
  // This is a transform phase, delete mempool.
  mempoolctrler.DeleteMemPool(memPool);
  return nullptr;
}

}  // namespace maple
