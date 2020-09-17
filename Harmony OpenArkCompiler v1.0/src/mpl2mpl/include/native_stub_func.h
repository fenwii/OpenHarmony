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
#ifndef MPL2MPL_INCLUDE_NATIVE_STUB_FUNC_H
#define MPL2MPL_INCLUDE_NATIVE_STUB_FUNC_H
#include "module_phase.h"
#include "phase_impl.h"

namespace maple {

static constexpr int kSlownativeFuncnum = 9;
static constexpr int kJniTypeNormal = 0;
static constexpr int kJniTypeMapleCriticalNative = 1;
static constexpr int kJnitTypeCriticalNative = 2;
static constexpr int kInvalidCode = 0xFF;

static constexpr char kPreNativeFunc[] = "MCC_PreNativeCall";
static constexpr char kPostNativeFunc[] = "MCC_PostNativeCall";
static constexpr char kDecodeRefFunc[] = "MCC_DecodeReference";
static constexpr char kFindNativeFunc[] = "MCC_FindNativeMethodPtr";
static constexpr char kFindNativeFuncNoeh[] = "MCC_FindNativeMethodPtrWithoutException";
static constexpr char kDummyNativeFunc[] = "MCC_DummyNativeMethodPtr";
static constexpr char kCheckThrowPendingExceptionFunc[] = "MCC_CheckThrowPendingException";
static constexpr char kCallFastNativeFunc[] = "MCC_CallFastNative";
static constexpr char kCallFastNativeExtFunc[] = "MCC_CallFastNativeExt";
static constexpr char kCallSlowNativeExtFunc[] = "MCC_CallSlowNativeExt";
static constexpr char kSetReliableUnwindContextFunc[] = "MCC_SetReliableUnwindContext";

class NativeFuncProperty {
 public:
  NativeFuncProperty() {
    jniType = kJniTypeNormal;
  }

 private:
  std::string javaFunc;
  std::string nativeFile;
  std::string nativeFunc;
  int jniType;

  friend class GenericNativeStubFunc;
};

class GenericNativeStubFunc : public FuncOptimizeImpl {
 public:
  GenericNativeStubFunc(MIRModule *mod, KlassHierarchy *kh, bool dump);
  ~GenericNativeStubFunc() {}

  void ProcessFunc(MIRFunction *func) override;
  void Finish() override;
  FuncOptimizeImpl *Clone() override {
    return new (std::nothrow) GenericNativeStubFunc(*this);
  }

 private:
  // a static binding function list
  std::unordered_set<std::string> staticBindingMethodsSet;
  TyIdx jstrPointerTypeIdx = TyIdx(0);
  MIRAggConst *regTableConst = nullptr;
  MIRSymbol *regFuncSymbol = nullptr;
  MIRAggConst *regFuncTabConst = nullptr;
  bool IsStaticBindingListMode() const;
  inline bool ReturnsJstr(TyIdx retType) {
    return (retType == jstrPointerTypeIdx);
  }

  void InitStaticBindingMethodList();
  bool IsStaticBindingMethod(const std::string &methodName);
  MIRFunction *MRTPreNativeFunc = nullptr;
  MIRFunction *MRTPostNativeFunc = nullptr;
  MIRFunction *MRTDecodeRefFunc = nullptr;
  MIRFunction *MRTCheckThrowPendingExceptionFunc = nullptr;
  MIRFunction *MRTCallFastNativeFunc = nullptr;
  MIRFunction *MRTCallFastNativeExtFunc = nullptr;
  MIRFunction *MRTCallSlowNativeFunc[kSlownativeFuncnum] = { nullptr };  // for native func which args <=8, use x0-x7
  MIRFunction *MRTCallSlowNativeExtFunc = nullptr;
  MIRFunction *MCCSetReliableUnwindContextFunc = nullptr;
  const std::string kCallSlowNativeFuncs[kSlownativeFuncnum] = {
    "MCC_CallSlowNative0", "MCC_CallSlowNative1", "MCC_CallSlowNative2", "MCC_CallSlowNative3", "MCC_CallSlowNative4",
    "MCC_CallSlowNative5", "MCC_CallSlowNative6", "MCC_CallSlowNative7", "MCC_CallSlowNative8"
  };
  MIRFunction *GetOrCreateDefaultNativeFunc(MIRFunction *stubFunc);
  void GenericRegisteredNativeFuncCall(MIRFunction *func, const MIRFunction *nativeFunc, MapleVector<BaseNode*> &args,
                                       const MIRSymbol *ret, bool needNativeCall, CallNode *prevNativeFuncCall,
                                       CallNode *postNativeFuncCall);
  StmtNode *CreateNativeWrapperCallNode(MIRFunction *func, BaseNode *funcPtr, MapleVector<BaseNode*> &args,
                                        const MIRSymbol *ret);
  void GenericNativeWrapperFuncCall(MIRFunction *func, const MIRFunction *nativeFunc, MapleVector<BaseNode*> &args,
                                    const MIRSymbol *ret);
  void GenericHelperFuncDecl();
  void GenericRegTabEntry(const MIRFunction *func);
  void GenericRegTableEntryType();
  void GenericRegTable();
  void GenericRegFuncTabEntryType();
  void GenericRegFuncTabEntry();
  void GenericRegFuncTab();
};

class DoGenericNativeStubFunc : public ModulePhase {
 public:
  explicit DoGenericNativeStubFunc(ModulePhaseID id) : ModulePhase(id) {}

  ~DoGenericNativeStubFunc() {}

  std::string PhaseName() const override {
    return "GenNativeStubFunc";
  }

  AnalysisResult *Run(MIRModule *mod, ModuleResultMgr *mrm) override {
    OPT_TEMPLATE(GenericNativeStubFunc);
    return nullptr;
  }
};

}  // namespace maple
#endif  // MPL2MPL_INCLUDE_NATIVE_STUB_FUNC_H
