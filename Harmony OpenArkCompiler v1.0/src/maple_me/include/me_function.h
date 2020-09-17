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
#ifndef MAPLE_ME_INCLUDE_ME_FUNCTION_H
#define MAPLE_ME_INCLUDE_ME_FUNCTION_H
#include "mir_parser.h"
#include "mir_function.h"
#include "opcode_info.h"
#include "me_option.h"
#include "mempool.h"
#include "mempool_allocator.h"
#include "ver_symbol.h"
#include "bb.h"
#include "ssa_tab.h"
#include "func_emit.h"
#include "me_ir.h"
#include "me_ssa.h"

namespace maple {
class MirCFG;
class MeIRMap;
#if DEBUG
extern MIRModule *g_mirmodule;
extern MeFunction *g_func;
extern MeIRMap *g_irmap;
extern SSATab *g_ssatab;
#endif

template <typename Iterator>
class FilterIterator {
  using FilterFunc = std::function<bool(Iterator)>;
  static bool FilterNone(Iterator) {
    return true;
  }

 public:
  using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
  using value_type = typename std::iterator_traits<Iterator>::value_type;
  using difference_type = typename std::iterator_traits<Iterator>::difference_type;
  using pointer = typename std::iterator_traits<Iterator>::pointer;
  using reference = typename std::iterator_traits<Iterator>::reference;
  using const_pointer = typename std::add_const<pointer>::type;
  using const_reference = typename std::add_const<reference>::type;

  explicit FilterIterator(Iterator it) : iterator(it) {}

  FilterIterator(Iterator it, FilterFunc func) : iterator(it), func(func) {
    while (!func(iterator)) {
      ++iterator;
    }
  }

  Iterator base() const {
    return iterator;
  }

  ~FilterIterator() = default;

  reference operator*() const {
    return *iterator;
  }

  pointer operator->() const {
    return iterator.operator->();
  }

  FilterIterator &operator++() {
    ++iterator;
    return func(iterator) ? *this : ++(*this);
  }

  FilterIterator &operator--() {
    --iterator;
    return func(iterator) ? *this : --(*this);
  }

  FilterIterator operator++(int) {
    FilterIterator it = *this;
    ++(*this);
    return it;
  }

  FilterIterator operator--(int) {
    FilterIterator it = *this;
    --(*this);
    return it;
  }

  bool operator==(const FilterIterator &it) const {
    return this->iterator == it.iterator;
  }

  bool operator!=(const FilterIterator &it) const {
    return !(*this == it);
  }

  bool operator==(const Iterator &it) const {
    return this->iterator == it;
  }

  bool operator!=(const Iterator &it) const {
    return !(*this == it);
  }

 private:
  Iterator iterator;
  FilterFunc func = FilterIterator::FilterNone;
};

template <typename Iterator>
inline auto build_filter_iterator(Iterator it) -> FilterIterator<Iterator> {
  return FilterIterator<Iterator>(it);
}

template <typename Iterator, typename _Func>
inline auto build_filter_iterator(Iterator it, _Func func) -> FilterIterator<Iterator> {
  return FilterIterator<Iterator>(it, std::function<bool(Iterator)>(func));
}

template <typename Iterator>
inline auto build_filter_iterator(Iterator it, std::function<bool(Iterator)> func) -> FilterIterator<Iterator> {
  return FilterIterator<Iterator>(it, func);
}

template <typename Iterator>
bool FilterNullPtr(Iterator it, Iterator endIt) {
  return it == endIt || *it != nullptr;
}

enum MeFuncHint {
    kReserved      = 0x00,       // reserved
    kPlacementRCed = 0x01,       // method processed by placementrc
    kAnalyzeRCed   = 0x02,       // method processed by analyzerc
    kRcLowered     = 0x04,       // method lowered by rclowering
};

// to suppress warning
// lint -sem(maple::MeFunction::PartialInit,initializer)
class MeFunction : public FuncEmit {
  using BBPtrHolder = MapleVector<BB*>;

 public:
  MeFunction(MIRModule *mod, MIRFunction *func, MemPool *memPool, MemPool *versMemPool,
             const std::string &fileName)
      : memPool(memPool),
        alloc(memPool),
        versMemPool(versMemPool),
        versAlloc(versMemPool),
        mirModule(*mod),
        mirFunc(func),
        nextBBId(0),
        labelBBIdMap(alloc.Adapter()),
        bbVec(alloc.Adapter()),
        theCFG(nullptr),
        meSSATab(nullptr),
        irmap(nullptr),
        bbTryNodeMap(alloc.Adapter()),
        endTryBB2TryBB(alloc.Adapter()),
        fileName(fileName),
        regNum(0),
        hints(0),
        hasEH(false),
        secondPass(false) {}

  virtual ~MeFunction() {}

  using value_type = BBPtrHolder::value_type;
  using size_type = BBPtrHolder::size_type;
  using difference_type = BBPtrHolder::difference_type;
  using pointer = BBPtrHolder::pointer;
  using const_pointer = BBPtrHolder::const_pointer;
  using reference = BBPtrHolder::reference;
  using const_reference = BBPtrHolder::const_reference;
  using iterator = BBPtrHolder::iterator;
  using const_iterator = BBPtrHolder::const_iterator;
  using reverse_iterator = BBPtrHolder::reverse_iterator;
  using const_reverse_iterator = BBPtrHolder::const_reverse_iterator;

  iterator begin() {
    return bbVec.begin();
  }

  const_iterator begin() const {
    return bbVec.begin();
  }

  const_iterator cbegin() const {
    return bbVec.cbegin();
  }

  iterator end() {
    return bbVec.end();
  }

  const_iterator end() const {
    return bbVec.end();
  }

  const_iterator cend() const {
    return bbVec.cend();
  }

  reverse_iterator rbegin() {
    return bbVec.rbegin();
  }

  const_reverse_iterator rbegin() const {
    return bbVec.rbegin();
  }

  const_reverse_iterator crbegin() const {
    return bbVec.crbegin();
  }

  reverse_iterator rend() {
    return bbVec.rend();
  }

  const_reverse_iterator rend() const {
    return bbVec.rend();
  }

  const_reverse_iterator crend() const {
    return bbVec.crend();
  }

  reference front() {
    return bbVec.front();
  }

  reference back() {
    return bbVec.back();
  }

  const_reference front() const {
    return bbVec.front();
  }

  const_reference back() const {
    return bbVec.back();
  }

  bool empty() const {
    return bbVec.empty();
  }

  size_t size() const {
    return bbVec.size();
  }

  FilterIterator<const_iterator> valid_begin() const {
    return build_filter_iterator(begin(), std::bind(FilterNullPtr<const_iterator>, std::placeholders::_1, end()));
  }

  FilterIterator<const_iterator> valid_end() const {
    return build_filter_iterator(end());
  }

  FilterIterator<const_reverse_iterator> valid_rbegin() const {
    return build_filter_iterator(rbegin(),
                                 std::bind(FilterNullPtr<const_reverse_iterator>, std::placeholders::_1, rend()));
  }

  FilterIterator<const_reverse_iterator> valid_rend() const {
    return build_filter_iterator(rend());
  }

  const_iterator common_entry() const {
    return begin();
  }

  const_iterator context_begin() const {
    return (++(++begin()));
  }

  const_iterator context_end() const {
    return end();
  }

  const_iterator common_exit() const {
    return (++begin());
  }

  uint32 NumBBs(void) const {
    return nextBBId;
  }

  void Dump(bool DumpSimpIr = false);
  virtual void Prepare(unsigned long rangeNum);
  void Verify();
  const std::string &GetName() const {
    return mirModule.CurFunction()->GetName();
  }

  VersionSt *GetVerSt(size_t veridx) {
    return meSSATab->GetVerSt(veridx);
  }

  BB *NewBasicBlock();
  BB *InsertNewBasicBlock(BB *position);
  void DeleteBasicBlock(const BB *bb);
  BB *NextBB(const BB *bb);
  BB *PrevBB(const BB *bb);
  /* create label for bb */
  void CreateBBLabel(BB *bb);
  /* clone stmtnodes from orig to newbb */
  void CloneBasicBlock(BB *newbb, BB *orig);
  BB *SplitBB(BB *bb, StmtNode *splitPoint);
  const bool HasException() const {
    return hasEH;
  }

  void SetSecondPass() {
    secondPass = true;
  }

  bool IsSecondPass() const {
    return secondPass;
  }

  MapleAllocator &GetAlloc() {
    return alloc;
  }

  MapleUnorderedMap<LabelIdx, BB*> &GetLabelBBIdMap() {
    return labelBBIdMap;
  }

  MapleVector<BB*> &GetAllBBs() {
    return bbVec;
  }

  BB *GetBBFromID(BBId bbID) {
    ASSERT(bbID.idx < bbVec.size(), "array index out of range");
    return bbVec.at(bbID.idx);
  }

  SSATab *GetMeSSATab() {
    return meSSATab;
  }

  void SetMeSSATab(SSATab *currMessaTab) {
    meSSATab = currMessaTab;
  }

  MIRFunction *GetMirFunc() {
    return mirFunc;
  }

  BB *GetCommonEntryBB() {
    return *common_entry();
  }

  BB *GetCommonExitBB() {
    return *common_exit();
  }

  BB *GetFirstBB() {
    return *(++(++valid_begin()));
  }

  BB *GetLastBB() {
    return *valid_rbegin();
  }

  MIRModule &GetMIRModule() {
    return mirModule;
  }

  MeIRMap *GetIRMap() {
    return irmap;
  }

  void SetIRMap(MeIRMap *currIRMap) {
    irmap = currIRMap;
  }

  MapleUnorderedMap<BB*, StmtNode*> &GetBBTryNodeMap() {
    return bbTryNodeMap;
  }

  MapleUnorderedMap<BB*, BB*> &GetEndTryBB2TryBB() {
    return endTryBB2TryBB;
  }

  BB *GetEndTryBB(BB *endTry) {
    return endTryBB2TryBB[endTry];
  }

  MirCFG *GetTheCfg() {
    return theCFG;
  }

  void SetTheCfg(MirCFG *currTheCfg) {
    theCFG = currTheCfg;
  }

  bool GetSecondPass() {
    return secondPass;
  }

  MemPool *GetVersMp() {
    return versMemPool;
  }

  void SetNextBBId(uint32 currNextBBId) {
    nextBBId = currNextBBId;
  }

  uint32 GetRegNum() const {
    return regNum;
  }

  void SetRegNum(uint32 num) {
    regNum = num;
  }

  uint32 GetHints() const {
    return hints;
  }

  void SetHints(uint32 num) {
    hints = num;
  }

  void PartialInit(bool isSecondPass);

 private:
  void CreateBasicBlocks();
  void SetTryBlockInfo(const StmtNode *nextStmt, StmtNode *tryStmt, BB *lastTryBB, BB *curBB, BB *newBB);
  void RemoveEhEdgesInSyncRegion();

  MemPool *memPool;
  MapleAllocator alloc;
  MemPool *versMemPool;
  MapleAllocator versAlloc;
  MIRModule &mirModule;
  MIRFunction *mirFunc;
  uint32 nextBBId;
  /* mempool */
  MapleUnorderedMap<LabelIdx, BB*> labelBBIdMap;
  BBPtrHolder bbVec;
  MirCFG *theCFG;
  SSATab *meSSATab;
  MeIRMap *irmap;
  MapleUnorderedMap<BB*, StmtNode*> bbTryNodeMap;  // maps isTry bb to its try stmt
  MapleUnorderedMap<BB*, BB*> endTryBB2TryBB;      // maps endtry bb to its try bb
  /* input */
  std::string fileName;
  uint32 regNum;    // count virtual registers
  uint32 hints;
  bool hasEH;       /* current has try statement */
  bool secondPass;  // second pass for the same function
};

}  // namespace maple
#endif  // MAPLE_ME_INCLUDE_ME_FUNCTION_H
