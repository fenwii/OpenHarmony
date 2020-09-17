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
#ifndef MPL2MPL_INCLUDE_CLASS_HIERARCHY_H
#define MPL2MPL_INCLUDE_CLASS_HIERARCHY_H
#include "mir_function.h"
#include "module_phase.h"

namespace maple {
class KlassHierarchy;
// should be consistent with runtime
static constexpr uint32 kClassPrim = 0x0001;
static constexpr uint32 kClassArray = 0x0002;
static constexpr uint32 kClassHasFinalizer = 0x0004;
static constexpr uint32 kClassSoftreference = 0x0008;
static constexpr uint32 kClassWeakreference = 0x0010;
static constexpr uint32 kClassPhantomreference = 0x0020;
static constexpr uint32 kClassFinalizereference = 0x0040;
static constexpr uint32 kClassCleaner = 0x0080;
static constexpr uint32 kClassFinalizerreferenceSentinel = 0x0100;
static constexpr uint32 kClassIsExceptionKlass = 0x0200;
static constexpr uint32 kClassIsanonymousclass = 0x0400;
static constexpr uint32 kClassIscoldclass = 0x0800;
static constexpr uint32 kClassNeedDecouple = 0x1000;
static constexpr uint32 kClassLazyBindingClass = 0x2000;
static constexpr char kJavaLangNoMethodStr[] = "Ljava_2Flang_2FNoSuchMethodException_3B";

#define CLASS_REFERENCE \
  (kClassSoftreference | kClassWeakreference | kClassCleaner | kClassFinalizereference | kClassPhantomreference)
// Klass is the basic node for building class hierarchy
class Klass {
 public:
  struct KlassComparator {
    bool operator()(const Klass *lhs, const Klass *rhs) const {
      return lhs->GetKlassName() < rhs->GetKlassName();
    }
  };

 private:
  // structType can be class or interface
  MIRStructType *structType;
  MapleAllocator *alloc;
  // A collection of super classes.
  // superklass is nullptr if it is not defined in the module.
  MapleList<Klass*> superKlasses;
  // A collection of sub classes
  MapleSet<Klass*, KlassComparator> subKlasses;
  // a collection of classes which implement the current interface
  MapleSet<Klass*, KlassComparator> implKlasses;
  // a collection of interfaces which is implemented by the current klass
  MapleSet<Klass*, KlassComparator> implInterfaces;
  // A collection of class member methods
  MapleList<MIRFunction*> methods;
  // A mapping to track every method to its baseFuncNameWithType
  MapleMap<GStrIdx, MIRFunction*> strIdx2Method;
  MIRFunction *clinitMethod;
  MIRSymbol *classInitBridge;
  // A mapping to track possible implementations for each virtual function
  MapleMap<GStrIdx, MapleVector<MIRFunction*>*> strIdx2CandidateMap;
  // flags of this class.
  // Now contains whether this class is exception, reference or has finalizer.
  uint32 flags;
  bool isPrivateInnerAndNoSubClassFlag;
  bool hasNativeMethods;
  bool needDecoupling;
  void DumpKlassImplInterfaces() const;
  void DumpKlassImplKlasses() const;
  void DumpKlassSuperKlasses() const;
  void DumpKlassSubKlasses() const;
  void DumpKlassMethods() const;
  bool IsVirtualMethod(const MIRFunction *func) const;

 public:
  Klass(MIRStructType *type, MapleAllocator *alc);
  ~Klass() {}

  // Return true if Klass represents an interface
  bool IsInterface() const {
    return (structType->GetKind() == kTypeInterface);
  }

  // Return true if Klass represents a normal java class
  bool IsClass() const {
    return (structType->GetKind() == kTypeClass);
  }

  // Return true if found in the member methods
  bool IsKlassMethod(const MIRFunction *func) const;
  // Return MIRFunction if has method
  const MIRFunction *HasMethod(const char *funcname);
  const MapleList<MIRFunction*> &GetMethods() const {
    return methods;
  }

  const MIRFunction *GetMethod(GStrIdx idx) const {
    MapleMap<GStrIdx, MIRFunction*>::const_iterator it = strIdx2Method.find(idx);
    return it != strIdx2Method.end() ? it->second : nullptr;
  }
  GStrIdx GetKlassNameStrIdx() const {
    return structType->GetNameStrIdx();
  }

  const std::string &GetKlassName() const {
    return structType->GetName();
  }

  TyIdx GetTypeIdx() const {
    return structType->GetTypeIndex();
  }

  MIRStructType *GetMIRStructType() const {
    return structType;
  }

  MIRClassType *GetMIRClassType() const {
    return static_cast<MIRClassType*>(structType);
  }

  MIRInterfaceType *GetMIRInterfaceType() const {
    return static_cast<MIRInterfaceType*>(structType);
  }

  bool HasSuperKlass() const {
    return !superKlasses.empty();
  }

  bool HasSubKlass() const {
    return !subKlasses.empty();
  }

  bool HasImplementInterfaces() const {
    return !implInterfaces.empty();
  }

  bool ImplementsKlass() const;
  void SetFlag(uint32 flag) {
    flags |= flag;
  }

  uint32 GetFlag(uint32 flag) const {
    return flags & flag;
  }

  bool HasFlag(uint32 flag) const {
    return static_cast<bool>(GetFlag(flag) != 0);
  }

  bool IsExceptionKlass() const {
    return HasFlag(kClassIsExceptionKlass);
  }

  void SetExceptionKlass() {
    SetFlag(kClassIsExceptionKlass);
  }

  bool HasFinalizer() const {
    return HasFlag(kClassHasFinalizer);
  }

  void SetHasFinalizer() {
    SetFlag(kClassHasFinalizer);
  }

  bool HasNativeMethod() const {
    return hasNativeMethods;
  }

  void SetHasNativeMethod(bool flag) {
    hasNativeMethods = flag;
  }

  bool IsReference(uint32 flag) const {
    return HasFlag(flag);
  }

  bool IsReference() const {
    return HasFlag(CLASS_REFERENCE);
  }

  bool IsArray() const {
    return (structType->GetName().find(JARRAY_PREFIX_STR) == 0);
  }

  bool IsPrivateInnerAndNoSubClass() const {
    return isPrivateInnerAndNoSubClassFlag;
  }

  void SetPrivateInnerAndNoSubClass(bool flag) {
    isPrivateInnerAndNoSubClassFlag = flag;
  }

  bool GetNeedDecoupling() const {
    return needDecoupling;
  }

  void SetNeedDecoupling(bool flag) {
    needDecoupling = flag;
  }

  const MIRFunction * const GetClinit() const {
    return clinitMethod;
  }

  void SetClinit(MIRFunction *m) {
    clinitMethod = m;
  }

  MIRSymbol *GetClassInitBridge() const {
    return classInitBridge;
  }

  void SetClassInitBridge(MIRSymbol *s) {
    classInitBridge = s;
  }

  // Return the function defined in the current class, or the inherited
  // function if it is not defined in the current class.
  MIRFunction *GetClosestMethod(GStrIdx) const;
  // This for class only, which only has 0 or 1 super class
  Klass *GetSuperKlass() const;
  const MapleList<Klass*> &GetSuperKlasses() const {
    return superKlasses;
  }

  const MapleSet<Klass*, KlassComparator> &GetSubKlasses() const {
    return subKlasses;
  }

  const MapleSet<Klass*, KlassComparator> &GetImplKlasses() const {
    return implKlasses;
  }

  const MapleSet<Klass*, KlassComparator> &GetImplInterfaces() const {
    return implInterfaces;
  }

  // Return a vector of possible functions
  MapleVector<MIRFunction*> *GetCandidates(GStrIdx mnameNoklassStridx) const;
  // Return the unique method if there is only one target virtual function.
  // Return nullptr if there are multiple targets.
  MIRFunction *GetUniqueMethod(GStrIdx mnameNoklassStridx) const;
  void AddSuperKlass(Klass *superclass) {
    superKlasses.push_back(superclass);
  }

  void AddSubKlass(Klass *subclass) {
    subKlasses.insert(subclass);
  }

  void AddImplKlass(Klass *implclass) {
    implKlasses.insert(implclass);
  }

  void AddImplInterface(Klass *interfaceKlass) {
    implInterfaces.insert(interfaceKlass);
  }

  void AddMethod(MIRFunction *func) {
    methods.push_front(func);
    strIdx2Method.insert({ func->GetBaseFuncNameWithTypeStrIdx(), func });
  }

  void DelMethod(const MIRFunction *func);
  // Collect the virtual methods from parent class and interfaces
  void CountVirtMethTopDown(const KlassHierarchy *kh);
  // Count the virtual methods for subclasses and merge with itself
  void CountVirtMethBottomUp();
  void Dump() const;
};

// Some well known types like java.lang.Object. They may be commonly referenced.
// j - java
// jl - java lang
// jlr - java lang reflect
class WKTypes {
 public:
  static void Init();
  class Util {
   public:
    static bool MayRefString(const BaseNode *n, MIRType *type);
    static bool MayRefMeta(const BaseNode *n, MIRType *type);
    static bool MayNotRefCyclicly(const BaseNode *n, MIRType *type);
    static MIRType *GetJavaLangObjectType() {
      return javalangObject;
    }

   private:
    static bool NotCyclicType(MIRType *type, std::set<MIRType*> &workList);
  };

 private:
  static MIRType *javalangObject;
  static MIRType *jlString;
  static MIRType *javalangobjectSerializable;
  static MIRType *javalangComparable;
  static MIRType *javalangCharSequence;
  static MIRType *javalangClass;
  static MIRType *javalangrefGenericDeclaration;
  static MIRType *javalangrefAnnotatedElement;
  static MIRType *jlrType;
  static MIRType *javalangrefMethod;
  static MIRType *javalangrefExecutable;
  static MIRType *javalangrefAccessibleObject;
  static MIRType *javalangrefMember;
  static MIRType *javalangrefField;
  static MIRType *javalangrefConstructor;
};

/* data structure to represent class information defined in the module */
class KlassHierarchy : public AnalysisResult {
 public:
  static bool traceFlag;
  KlassHierarchy(MIRModule *mirmodule, MemPool *memPool);
  virtual ~KlassHierarchy() {}

  // Get a class. Return nullptr it does not exist.
  Klass *GetKlassFromStrIdx(GStrIdx stridx) const;
  Klass *GetKlassFromTyIdx(TyIdx tyidx) const;
  Klass *GetKlassFromFunc(const MIRFunction *func) const;
  Klass *GetKlassFromName(const std::string &name) const;
  Klass *GetKlassFromLiteral(const char *name) const;
  const MapleMap<GStrIdx, Klass*> &GetKlasses() const {
    return strIdx2KlassMap;
  }

  // Get lowest common ancestor for two classes
  Klass *GetLCA(Klass *k1, Klass *k2) const;
  TyIdx GetLCA(TyIdx ty1, TyIdx ty2) const;
  GStrIdx GetLCA(GStrIdx str1, GStrIdx str2) const;
  const std::string &GetLCA(const std::string &name1, const std::string &name2) const;
  bool IsSuperKlass(const Klass *super, const Klass *base) const;
  bool IsSuperKlassForInterface(const Klass *super, Klass *base) const;
  bool IsInterfaceImplemented(Klass *interface, const Klass *base) const;
  // return true if class, its super or interfaces have at least one clinit function
  bool NeedClinitCheckRecursively(Klass *kl);
  void TopologicalSortKlasses();
  void MarkClassFlags();
  void CountVirtualMethods();
  void BuildHierarchy();
  void Dump() const;
  const MapleVector<Klass*> &GetTopoSortedKlasses() const {
    return topoWorkList;
  }

  const MIRModule *GetModule() const {
    return mirModule;
  }

 private:
  MapleAllocator alloc;
  MIRModule *mirModule;
  // Map from class name to klass. Use name as the key because the type
  // information is incomplete, e.g.
  // method to class link, e.g.
  //    class A { void foo(); void bar(); }
  //    class B extends A { void foo(); }
  //    In this case, there is no link from B.bar to B in the maple file.
  MapleMap<GStrIdx, Klass*> strIdx2KlassMap;
  MapleVector<Klass*> topoWorkList;
  // New all klass
  void AddKlasses();
  // Add superklass/subclass edge and class methods for each class
  void AddKlassRelationAndMethods();
  void TagThrowableKlasses();
  // Connect all class<->interface edges based on Depth-First Search
  void UpdateImplementedInterfaces();
  // Get a vector of parent class and implementing interface
  void GetParentKlasses(const Klass *klass, std::vector<Klass*> &parentKlasses) const;
  // Get a vector of child class and implemented class
  void GetChildKlasses(const Klass *klass, std::vector<Klass*> &childKlasses) const;
  void ExceptionFlagProp(Klass *klass);
  Klass *AddClassFlag(const char *name, uint32 flag);
};

}  // namespace maple
#endif  // MPL2MPL_INCLUDE_CLASS_HIERARCHY_H
