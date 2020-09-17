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
#ifndef MPL2MPL_INCLUDE_REFLECTION_ANALYSIS_H
#define MPL2MPL_INCLUDE_REFLECTION_ANALYSIS_H
#include "class_hierarchy.h"

namespace maple {

// +1 is needed here because our field id starts with 0 pointing to the struct itself
#define OBJ_KLASS_FIELDID (static_cast<uint32>(ClassProperty::kShadow) + 1)
#define METADATA_KLASS_FIELDID (static_cast<uint32>(ClassProperty::kShadow) + 1)
static constexpr bool raDebug = false;
static constexpr int64 kTBDValue = 0xABCD;
static constexpr int kMaxOptimiseThreshold = 6;
static constexpr uint32 kMethodFieldHashSize = 1022;
static constexpr uint16 kHashConflictFlag = 1023;

static constexpr char kModStr[] = "mod";
static constexpr char kAddrStr[] = "addr";
static constexpr char kFlagStr[] = "flag";
static constexpr char kItabStr[] = "itab";
static constexpr char kVtabStr[] = "vtab";
static constexpr char kGctibStr[] = "gctib";
static constexpr char kIndexStr[] = "index";
static constexpr char kOffsetStr[] = "offset";
static constexpr char kShadowStr[] = "shadow";
static constexpr char kClassSuffix[] = "_3B";
static constexpr char kArgsizeStr[] = "argsize";
static constexpr char kIfieldsStr[] = "ifields";
static constexpr char kMethodsStr[] = "methods";
static constexpr char kMonitorStr[] = "monitor";
static constexpr char kObjsizeStr[] = "objsize";
static constexpr char kPaddingStr[] = "padding";
static constexpr char kTypeNameStr[] = "typeName";
static constexpr char kClassnameStr[] = "classname";
static constexpr char kFieldnameStr[] = "fieldname";
static constexpr char kAccessFlags[] = "accessFlags";
static constexpr char kAnnotationStr[] = "annotation";
static constexpr char kClinitAddrStr[] = "clinitAddr";
static constexpr char kMethodnameStr[] = "methodname";
static constexpr char kInitFuntionStr[] = "_3Cinit_3E";
static constexpr char kClassinforoStr[] = "classinforo";
static constexpr char kClassloaderStr[] = "classloader";
static constexpr char kINFOFileName[] = "INFO_filename";
static constexpr char kLebPadding0Str[] = "lebPadding0";
static constexpr char kNumoffieldsStr[] = "numoffields";
static constexpr char kClinitbridgeStr[] = "clinitbridge";
static constexpr char kNumofmethodsStr[] = "numofmethods";
static constexpr char kSignaturenameStr[] = "signaturename";
static constexpr char kDeclaringclassStr[] = "declaringclass";
static constexpr char kFieldInfoTypeName[] = "__field_info__";
static constexpr char kINFOAccessFlags[] = "INFO_access_flags";
static constexpr char kSuperclassinfoStr[] = "superclassinfo";
static constexpr char kAnnotationvalueStr[] = "annotationvalue";
static constexpr char kMethodInfoTypeName[] = "__method_info__";
static constexpr char kClinitSuffixStr[] = "_3Cclinit_3E_7C_28_29V";
static constexpr char kJavaLangEnumStr[] = "Ljava_2Flang_2FEnum_3B";
static constexpr char kNumofsuperclassesStr[] = "numofsuperclasses";
static constexpr char kClassMetadataRoTypeName[] = "__class_meta_ro__";
static constexpr char kMethodInVtabIndexStr[] = "method_in_vtab_index";
static constexpr char kClassStateInitializedStr[] = "classStateInitialized";
static constexpr char kSuperclassMetadataTypeName[] = "__superclass_meta__";
static constexpr char kFieldInfoCompactTypeName[] = "__field_info_compact__";
static constexpr char kClassInitProtectRegionStr[] = "classInitProtectRegion";
static constexpr char kMethodInfoCompactTypeName[] = "__method_info_compact__";
static constexpr char kReflectionFieldPrefixStr[] = "Ljava_2Flang_2Freflect_2FField_3B";
static constexpr char kReflectionProxyPrefixStr[] = "Ljava_2Flang_2Freflect_2FProxy_3B";
static constexpr char kReflectionMethodPrefixStr[] = "Ljava_2Flang_2Freflect_2FMethod_3B";
static constexpr char kSuperclassOrComponentclassStr[] = "superclass_or_componentclass";
static constexpr char kReflectionReferencePrefixStr[] = "Ljava_2Flang_2Fref_2FReference_3B";
static constexpr char kReflectionProxy241PrefixStr[] = "Ljava_2Flang_2Freflect_2FProxy_241_3B";
static constexpr char kReflectionMethon241PrefixStr[] = "Ljava_2Flang_2Freflect_2FMethod_241_3B";
static constexpr char kReflectionExecutablePrefixStr[] = "Ljava_2Flang_2Freflect_2FExecutable_3B";
static constexpr char kReflectionConstructorPrefixStr[] = "Ljava_2Flang_2Freflect_2FConstructor_3B";
static constexpr char kJavaLangAnnotationRetentionStr[] = "Ljava_2Flang_2Fannotation_2FRetention_3B";
static constexpr char kReflectionAccessibleobjectPrefixStr[] = "Ljava_2Flang_2Freflect_2FAccessibleObject_3B";

static constexpr int kAnonymousClassIndex = 5;
static constexpr char kAnonymousClassSuffix[] = "30";
static constexpr char kAnonymousClassPrefix[] = "`IC";
static constexpr char kInnerClassPrefix[] = "`EC";

// maple field index definition
enum struct ClassRO : uint32 {
  kClassname,
  kIfields,
  kMethods,
  kSuperclass,
  kNumoffields,
  kNumofMethods,
#ifndef USE_32BIT_REF
  kFlag,
  kNumofsup,
  kPadding,
#endif  //! USE_32BIT_REF
  kMod,
  kAnnotation,
  kClinitAddr
};

enum struct ClassProperty : uint32 {
  kShadow,
  kMonitor,
  kClassloader,
  kObjsize,
#ifdef USE_32BIT_REF
  FLAG,
  NUMOFSUP,
#endif  // USE_32BIT_REF
  kItab,
  kVtab,
  kGctib,
  kInfoRo,
  kClint
};

enum struct MethodProperty : uint32 {
  kVtabIndex,
  kDeclarclass,
  kAddr,
  kMod,
  kMethodname,
  kSigname,
  kAnnotation,
  kFlag,
  kArgsize,
#ifndef USE_32BIT_REF
  padding
#endif
};

enum struct MethodInfoCompact : uint32 {
  kVtabIndex,
  kAddr
};

enum struct FieldProperty : uint32 {
  kOffset,
  kMod,
  kFlag,
  kIndex,
  kTypeName,
  kName,
  kAnnotation,
  kDeclarclass
};

enum struct FieldPropertyCompact : uint32 {
  kOffset,
  kMod,
  kTypeName,
  kIndex,
  kName,
  kAnnotation
};

// If needed, we can make field type in two bits.
static constexpr uint64 kFieldPrim = 0x00000001;
static constexpr uint64 kFieldArray = 0x00000002;
static constexpr uint64 kFieldInterface = 0x00000004;
static constexpr uint64 kFieldStatic = 0x00000008;
static constexpr uint64 kMethodNotVirtual = 0x00000001;
static constexpr uint64 kMethodFinalize = 0x00000002;
static constexpr uint64 kMethodMetaCompact = 0x00000004;
static constexpr uint64 kMethodAbstract = 0x00000010;
#define CaseCondition(ARRAYNAME, ELEM)                                                                     \
  case kValueInt:                                                                                          \
    ARRAYNAME += std::to_string(ELEM->GetI32Val());                                                        \
    oss.str();                                                                                             \
    break;                                                                                                 \
  case kValueLong:                                                                                         \
    ARRAYNAME += std::to_string(ELEM->GetI64Val());                                                        \
    break;                                                                                                 \
  case kValueDouble:                                                                                       \
    oss << tmp << std::setiosflags(std::ios::scientific) << std::setprecision(16) << ELEM->GetDoubleVal(); \
    ARRAYNAME += oss.str();                                                                                \
    break;                                                                                                 \
  case kValueFloat:                                                                                        \
    oss << tmp << std::setiosflags(std::ios::scientific) << std::setprecision(7) << ELEM->GetFloatVal();   \
    ARRAYNAME += oss.str();                                                                                \
    break;                                                                                                 \
  case kValueString: {                                                                                     \
    stridx.SetIdx(ELEM->GetU64Val());                                                                      \
    std::string s = GlobalTables::GetStrTable().GetStringFromStrIdx(stridx);                               \
    DelimeterConvert(s);                                                                                   \
    ReflectionAnalysis::CompressHighFrequencyStr(s);                                                       \
    ARRAYNAME += s;                                                                                        \
    break;                                                                                                 \
  }                                                                                                        \
  case kValueEnum:                                                                                         \
    stridx.SetIdx(ELEM->GetU64Val());                                                                      \
    ARRAYNAME += GlobalTables::GetStrTable().GetStringFromStrIdx(stridx);                                  \
    break;                                                                                                 \
  case kValueBoolean:                                                                                      \
    ARRAYNAME += std::to_string(ELEM->GetU64Val());                                                        \
    break;                                                                                                 \
  case kValueByte:                                                                                         \
    ARRAYNAME += std::to_string(ELEM->GetI32Val());                                                        \
    break;                                                                                                 \
  case kValueShort:                                                                                        \
    ARRAYNAME += std::to_string(ELEM->GetI32Val());                                                        \
    break;                                                                                                 \
  case kValueChar:                                                                                         \
    ARRAYNAME += std::to_string(ELEM->GetU64Val());                                                        \
    break;
class ReflectionAnalysis : public AnalysisResult {
 public:
  static void GenStrTab(MIRModule *mirmodule);
  static uint32 FindOrInsertRepeatString(const std::string &str, bool isHot = false, uint8 hotType = kLayoutUnused);
  static BaseNode *GenClassInfoAddr(BaseNode *obj, MIRBuilder *builder);
  ReflectionAnalysis(MIRModule *mod, MemPool *memPool, KlassHierarchy *kh, MIRBuilder &builder)
      : AnalysisResult(memPool),
        mirModule(mod),
        allocator(memPool),
        klassh(kh),
        mirBuilder(builder),
        classTab(allocator.Adapter()) {
    isLibcore = -1;
  }

  ~ReflectionAnalysis() {}

  static TyIdx GetClassMetaDataTyIdx() {
    return classMetadataTyIdx;
  }

  static std::unordered_map<std::string, uint32> &GetStr2IdxMap() {
    return str2IdxMap;
  }

  static void SetStr2IdxMap(const std::string &str, uint32 index) {
    str2IdxMap[str] = index;
  }

  static const std::string &GetStrTab() {
    return strTab;
  }

  static const std::string &GetStrTabStartHot() {
    return strTabStartHot;
  }

  static const std::string &GetStrTabBothHot() {
    return strTabBothHot;
  }

  static const std::string &GetStrTabRunHot() {
    return strTabRunHot;
  }

  static void AddStrTab(const std::string &str) {
    strTab += str;
  }

  static void AddStrTabStartHot(const std::string &str) {
    strTabStartHot += str;
  }

  static void AddStrTabBothHot(const std::string &str) {
    strTabBothHot += str;
  }

  static void AddStrTabRunHot(const std::string &str) {
    strTabRunHot += str;
  }

  MIRSymbol *GetOrCreateSymbol(const std::string &name, TyIdx tyIdx, bool needInit);
  MIRSymbol *GetSymbol(const std::string &name, TyIdx tyIdx);
  MIRSymbol *CreateSymbol(GStrIdx strIdx, TyIdx tyIdx);
  MIRSymbol *GetSymbol(GStrIdx strIdx, TyIdx tyIdx);
  void GenClassMetaData(Klass *klass);
  std::string GetAnnoValueWithoutArray(const MIRPragmaElement *annoElem);
  void CompressHighFrequencyStr(std::string &s);
  std::string GetArrayValue(MapleVector<MIRPragmaElement*> subElemVector, bool isSN = false);
  std::string GetAnnotationValue(MapleVector<MIRPragmaElement*> subElemVector, GStrIdx typeStrIdx);
  MIRSymbol *GenSuperClassMetaData(const Klass *klass, std::list<Klass*> superClassList);
  MIRSymbol *GenFieldsMetaData(const Klass *klass);
  MIRSymbol *GenMethodsMetaData(const Klass *klass);
  static void GenMetadataType(MIRModule *mirModule);
  static MIRType *GetRefFieldType(MIRBuilder *mirBuilder);
  static TyIdx GenMetaStructType(MIRModule *mirModule, MIRStructType &metaType, const std::string &str);
  int64 GetHashIndex(const std::string &strname);
  static void GenHotClassNameString(const Klass *klass);
  uint32 FindOrInsertReflectString(const std::string &str);
  static void InitReflectString();
  int64 BKDRHash(const std::string &strname, uint32 seed);
  void GenClassHashMetaData();
  void MarkWeakMethods();
  void Run();
  bool VtableFunc(const MIRFunction *func) const;
  void GenPrimitiveClass();
  bool RootClassDefined();  // wether current module defines root classes
  void GenAllMethodHash(std::vector<std::pair<MethodPair*, int>> &methodInfoVec,
                        std::unordered_map<uint32, std::string> &baseNameMap,
                        std::unordered_map<uint32, std::string> &fullNameMap);
  void GenAllFieldHash(std::vector<std::pair<FieldPair, uint16>> &fieldV);
  void GeneAnnotation(std::map<int, int> &idxNumMap, std::string &annoArr, MIRClassType *classType,
                      PragmaKind paragKind, const std::string &paragName, TyIdx fieldTypeIdx,
                      std::map<int, int> *paramNumArray = nullptr, int *paramIndex = nullptr);
  void SetAnnoFieldConst(const MIRStructType *metadataRoType, MIRAggConst *newConst, uint32 fieldID,
                         std::map<int, int> &idxNumMap, const std::string &annoArr);
  bool IsAnonymousClass(const std::string &annotationString);
  bool IsPrivateClass(MIRClassType *classType);
  bool IsStaticClass(MIRClassType *classType);
  void CheckPrivateInnerAndNoSubClass(Klass *clazz, const std::string &annoArr);
  void ConvertMapleClassName(const std::string &mplClassName, std::string &javaDsp);
  static void ConvertMethodSig(std::string &signature);
  int GetDeflateStringIdx(const std::string &subStr);
  uint32 GetAnnoCstrIndex(std::map<int, int> &idxNumMap, const std::string &annoArr);
  int16 GetMethodInVtabIndex(const Klass *clazz, const MIRFunction *func);
  void GetSignatureTypeNames(const char *signature, std::vector<std::string> &typeNames);
  MIRSymbol *GetClinitFuncSymbol(const Klass *klass);
  int SolveAnnotation(MIRClassType *classType, MIRFunction *func);
  uint32 GetTypeNameIdxFromType(MIRType *type, const Klass *klass, const std::string &fieldName);

 private:
  MIRModule *mirModule;
  MapleAllocator allocator;
  KlassHierarchy *klassh;
  MIRBuilder &mirBuilder;
  MapleVector<MIRSymbol*> classTab;
  int isLibcore;
  std::map<std::string, std::string> highFrequencyStrMap;
  std::string reflectionMuidStr;
  static const char *klassPtrName;
  static TyIdx classMetadataTyIdx;
  static TyIdx classMetadataRoTyIdx;
  static TyIdx methodsInfoTyIdx;
  static TyIdx methodsInfoCompactTyIdx;
  static TyIdx fieldsInfoTyIdx;
  static TyIdx fieldsInfoCompactTyIdx;
  static TyIdx superclassMetadataTyIdx;
  static std::string strTab;
  static std::unordered_map<std::string, uint32> str2IdxMap;
  static std::string strTabStartHot;
  static std::string strTabBothHot;
  static std::string strTabRunHot;
  static bool strTabInited;
  static TyIdx invalidIdx;
};

class DoReflectionAnalysis : public ModulePhase {
 public:
  explicit DoReflectionAnalysis(ModulePhaseID id) : ModulePhase(id) {}

  ~DoReflectionAnalysis() {}

  AnalysisResult *Run(MIRModule *module, ModuleResultMgr *m) override;
  std::string PhaseName() const override {
    return "reflectionanalysis";
  }
};

}  // namespace maple
#endif  // MPL2MPL_INCLUDE_REFLECTION_ANALYSIS_H
