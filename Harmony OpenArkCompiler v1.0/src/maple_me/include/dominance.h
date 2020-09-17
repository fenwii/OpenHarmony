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
#ifndef MAPLE_ME_INCLUDE_DOMINANCE_H
#define MAPLE_ME_INCLUDE_DOMINANCE_H
#include "phase.h"
#include "bb.h"

namespace maple {
class Dominance : public AnalysisResult {
 public:
  Dominance(MemPool *memPool, MemPool *tmpPool, MapleVector<BB*> *bbVec, BB *commonEntryBB, BB *commonExitBB)
      : AnalysisResult(memPool),
        domAllocator(memPool),
        tmpAllocator(tmpPool),
        bbVec(*bbVec),
        commonEntryBB(commonEntryBB),
        commonExitBB(commonExitBB),
        postOrderIDVec(bbVec->size(), -1, tmpAllocator.Adapter()),
        reversePostOrder(tmpAllocator.Adapter()),
        doms(bbVec->size(), nullptr, domAllocator.Adapter()),
        pdomPostOrderIDVec(bbVec->size(), -1, tmpAllocator.Adapter()),
        pdomReversePostOrder(tmpAllocator.Adapter()),
        pdoms(bbVec->size(), nullptr, domAllocator.Adapter()),
        domFrontier(bbVec->size(), MapleSet<BBId>(std::less<BBId>(), domAllocator.Adapter()), domAllocator.Adapter()),
        domChildren(bbVec->size(), MapleSet<BBId>(std::less<BBId>(), domAllocator.Adapter()), domAllocator.Adapter()),
        dtPreOrder(bbVec->size(), BBId(0), domAllocator.Adapter()),
        dtDfn(bbVec->size(), -1, domAllocator.Adapter()),
        pdomFrontier(bbVec->size(), MapleSet<BBId>(std::less<BBId>(), domAllocator.Adapter()), domAllocator.Adapter()),
        pdomChildren(bbVec->size(), MapleSet<BBId>(std::less<BBId>(), domAllocator.Adapter()), domAllocator.Adapter()),
        pdtPreOrder(bbVec->size(), BBId(0), domAllocator.Adapter()),
        pdtDfn(bbVec->size(), -1, domAllocator.Adapter()) {}

  ~Dominance() = default;

  void GenPostOrderID();
  void ComputeDominance();
  void ComputeDomFrontiers();
  void ComputeDomChildren();
  void ComputeDtPreorder(const BB *bb, size_t &num);
  void ComputeDtDfn();
  bool Dominate(const BB *b1, BB *b2);  // true if b1 dominates b2
  void DumpDoms();
  void PdomGenPostOrderID();
  void ComputePostDominance();
  void ComputePdomFrontiers();
  void ComputePdomChildren();
  void ComputePdtPreorder(const BB *bb, size_t &num);
  void ComputePdtDfn();
  bool PostDominate(const BB *b1, BB *b2);  // true if b1 postdominates b2
  void DumpPdoms();

  MapleVector<BB*> &GetBBVec() {
    return bbVec;
  }

  const MapleVector<BB*> &GetBBVec() const {
    return bbVec;
  }

  bool IsBBVecEmpty() const {
    return bbVec.empty();
  }

  size_t GetBBVecSize() const {
    return bbVec.size();
  }

  BB *GetBBAt(uint i) {
    return bbVec[i];
  }

  BB *GetCommonEntryBB() {
    return commonEntryBB;
  }

  void SetCommonEntryBB(BB *bb) {
    commonEntryBB = bb;
  }

  BB *GetCommonExitBB() {
    return commonExitBB;
  }

  void SetCommonExitBB(BB *exitBB) {
    commonExitBB = exitBB;
  }

  MapleVector<int32> &GetPostOrderIDVec() {
    return postOrderIDVec;
  }

  MapleVector<BB*> &GetReversePostOrder() {
    return reversePostOrder;
  }

  const MapleVector<BB*> &Getdoms() const {
    return doms;
  }

  MapleVector<BBId> &GetDtPreOrder() {
    return dtPreOrder;
  }

  BBId &GetDtPreOrderItem(size_t idx) {
    return dtPreOrder[idx];
  }

  size_t GetDtPreOrderSize() const {
    return dtPreOrder.size();
  }

  uint32 GetDtDfnItem(size_t idx) const {
    return dtDfn[idx];
  }

  size_t GetDtDfnSize() const {
    return dtDfn.size();
  }

  MapleSet<BBId> &GetPdomFrontierItem(size_t idx) {
    return pdomFrontier[idx];
  }

  size_t GetPdomFrontierSize() const {
    return pdomFrontier.size();
  }

  MapleSet<BBId> &GetPdomChildrenItem(size_t idx) {
    return pdomChildren[idx];
  }

  MapleVector<BBId> &GetPdtPreOrder() {
    return pdtPreOrder;
  }

  BBId GetPdtPreOrderItem(size_t idx) const {
    return pdtPreOrder[idx];
  }

  uint32 GetPdtDfnItem(size_t idx) const {
    return pdtDfn[idx];
  }

  BB *GetDom(size_t idx) {
    return doms[idx];
  }

  uint32 GetDomsSize() const {
    return doms.size();
  }

  int32 GetPdomPostOrderIDVec(size_t idx) const {
    return pdomPostOrderIDVec[idx];
  }

  BB *GetPdomReversePostOrder(size_t idx) {
    return pdomReversePostOrder[idx];
  }

  MapleVector<BB*> &GetPdomReversePostOrder() {
    return pdomReversePostOrder;
  }

  size_t GetPdomReversePostOrderSize() const {
    return pdomReversePostOrder.size();
  }

  MapleSet<BBId> &GetDomFrontier(size_t idx) {
    return domFrontier[idx];
  }

  size_t GetDomFrontierSize() const {
    return domFrontier.size();
  }

  MapleVector<MapleSet<BBId>> &GetDomChildren() {
    return domChildren;
  }

  MapleSet<BBId> &GetDomChildren(size_t idx) {
    return domChildren[idx];
  }

  size_t GetDomChildrenSize() const {
    return domChildren.size();
  }

  BB *GetPdom(size_t idx) {
    return pdoms[idx];
  }

 protected:
  MapleAllocator domAllocator;  // stores the analysis results
 private:
  MapleAllocator tmpAllocator;  // can be freed after dominator computation
  MapleVector<BB*> &bbVec;
  BB *commonEntryBB;
  BB *commonExitBB;
  MapleVector<int32> postOrderIDVec;  // index is bb id
  MapleVector<BB*> reversePostOrder;  // an ordering of the BB in reverse postorder
  MapleVector<BB*> doms;              // index is bb id; immediate dominator for each BB
  // following is for post-dominance
  MapleVector<int32> pdomPostOrderIDVec;     // index is bb id
  MapleVector<BB*> pdomReversePostOrder;     // an ordering of the BB in reverse postorder
  MapleVector<BB*> pdoms;                    // index is bb id; immediate dominator for each BB
  MapleVector<MapleSet<BBId>> domFrontier;   // index is bb id
  MapleVector<MapleSet<BBId>> domChildren;   // index is bb id; for dom tree
  MapleVector<BBId> dtPreOrder;              // ordering of the BBs in a preorder traversal of the dominator tree
  MapleVector<uint32> dtDfn;                 // gives position of each BB in dt_preorder
  MapleVector<MapleSet<BBId>> pdomFrontier;  // index is bb id
  MapleVector<MapleSet<BBId>> pdomChildren;  // index is bb id; for pdom tree
  MapleVector<BBId> pdtPreOrder;             // ordering of the BBs in a preorder traversal of the post-dominator tree
  MapleVector<uint32> pdtDfn;                // gives position of each BB in pdt_preorder

 protected:
  void PostOrderWalk(BB *bb, int32 &pid, std::vector<bool> &visitedMap);
  BB *Intersect(BB *bb1, const BB *bb2);
  bool CommonEntryBBIsPred(const BB *bb);
  void PdomPostOrderWalk(BB *bb, int32 &pid, std::vector<bool> &visitedMap);
  BB *PdomIntersect(BB *bb1, const BB *bb2);
};

}  // namespace maple
#endif  // MAPLE_ME_INCLUDE_DOMINANCE_H
