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
#include "dominance.h"
#include <iostream>

/* ================= for Dominance ================= */

namespace maple {
void Dominance::PostOrderWalk(BB *bb, int32 &pid, std::vector<bool> &visitedMap) {
  ASSERT(bb->GetBBId().idx < visitedMap.size(), "index out of range in Dominance::PostOrderWalk");
  if (visitedMap[bb->GetBBId().idx]) {
    return;
  }
  visitedMap[bb->GetBBId().idx] = true;
  for (BB *suc : bb->GetSucc()) {
    PostOrderWalk(suc, pid, visitedMap);
  }
  ASSERT(bb->GetBBId().idx < postOrderIDVec.size(), "index out of range in Dominance::PostOrderWalk");
  postOrderIDVec[bb->GetBBId().idx] = pid++;
  return;
}

void Dominance::GenPostOrderID() {
  ASSERT(!bbVec.empty(), "size to be allocated is 0");
  std::vector<bool> visitedMap(bbVec.size(), false);
  int32 postOrderID = 0;
  PostOrderWalk(commonEntryBB, postOrderID, visitedMap);
  // initialize reversePostOrder
  int32 maxPostOrderID = postOrderID - 1;
  reversePostOrder.resize(maxPostOrderID + 1);
  for (size_t i = 0; i < postOrderIDVec.size(); i++) {
    int32 postOrderNo = postOrderIDVec[i];
    if (postOrderNo == -1) {
      continue;
    }
    reversePostOrder[maxPostOrderID - postOrderNo] = bbVec[i];
  }
}

BB *Dominance::Intersect(BB *bb1, const BB *bb2) {
  while (bb1 != bb2) {
    while (postOrderIDVec[bb1->GetBBId().idx] < postOrderIDVec[bb2->GetBBId().idx]) {
      bb1 = doms[bb1->GetBBId().idx];
    }
    while (postOrderIDVec[bb2->GetBBId().idx] < postOrderIDVec[bb1->GetBBId().idx]) {
      bb2 = doms[bb2->GetBBId().idx];
    }
  }
  return bb1;
}

bool Dominance::CommonEntryBBIsPred(const BB *bb) {
  for (BB *suc : GetCommonEntryBB()->GetSucc()) {
    if (suc == bb) {
      return true;
    }
  }
  return false;
}

// Figure 3 in "A Simple, Fast Dominance Algorithm" by Keith Cooper et al.
void Dominance::ComputeDominance() {
  doms.at(commonEntryBB->GetBBId().idx) = commonEntryBB;
  bool changed = false;
  do {
    changed = false;
    for (size_t i = 1; i < reversePostOrder.size(); i++) {
      BB *bb = reversePostOrder[i];
      BB *pre = nullptr;
      if (CommonEntryBBIsPred(bb) || bb->GetPred().empty()) {
        pre = commonEntryBB;
      } else {
        pre = bb->GetPred(0);
      }
      size_t j = 1;
      while ((doms[pre->GetBBId().idx] == nullptr || pre == bb) && j < bb->GetPred().size()) {
        pre = bb->GetPred(j);
        j++;
      }
      BB *newIDom = pre;
      for (; j < bb->GetPred().size(); j++) {
        pre = bb->GetPred(j);
        if (doms[pre->GetBBId().idx] != nullptr && pre != bb) {
          newIDom = Intersect(pre, newIDom);
        }
      }
      if (doms[bb->GetBBId().idx] != newIDom) {
        doms[bb->GetBBId().idx] = newIDom;
        changed = true;
      }
    }
  } while (changed);
}

// Figure 5 in "A Simple, Fast Dominance Algorithm" by Keith Cooper et al.
void Dominance::ComputeDomFrontiers() {
  for (BB *bb : bbVec) {
    if (bb == nullptr || bb == commonExitBB) {
      continue;
    }
    if (bb->GetPred().size() < 2) {
      continue;
    }
    for (BB *pre : bb->GetPred()) {
      BB *runner = pre;
      while (runner != doms[bb->GetBBId().idx] && runner != commonEntryBB) {
        domFrontier[runner->GetBBId().idx].insert(bb->GetBBId());
        runner = doms[runner->GetBBId().idx];
      }
    }
  }
}

void Dominance::ComputeDomChildren() {
  for (BB *bb : bbVec) {
    if (bb == nullptr) {
      continue;
    }
    if (doms[bb->GetBBId().idx] == nullptr) {
      continue;
    }
    BB *parent = doms[bb->GetBBId().idx];
    if (parent == bb) {
      continue;
    }
    domChildren[parent->GetBBId().idx].insert(bb->GetBBId());
  }
}

void Dominance::ComputeDtPreorder(const BB *bb, size_t &num) {
  CHECK_FATAL(num < dtPreOrder.size(), "index out of range in Dominance::ComputeDtPreorder");
  dtPreOrder[num++] = bb->GetBBId();
  for (BBId k : domChildren[bb->GetBBId().idx]) {
    ComputeDtPreorder(bbVec[k.idx], num);
  }
}

void Dominance::ComputeDtDfn() {
  for (uint32 i = 0; i < dtPreOrder.size(); i++) {
    dtDfn[dtPreOrder[i].idx] = i;
  }
}

// true if b1 dominates b2
bool Dominance::Dominate(const BB *b1, BB *b2) {
  if (b1 == b2) {
    return true;
  }
  CHECK_FATAL(b2->GetBBId().idx < doms.size(), "index out of range in Dominance::Dominate ");
  if (doms[b2->GetBBId().idx] == nullptr) {
    return false;
  }
  BB *imdom = b2;
  do {
    if (imdom == nullptr) {
      return false;
    }
    imdom = doms[imdom->GetBBId().idx];
    if (imdom == b1) {
      return true;
    }
  } while (imdom != commonEntryBB);
  return false;
}

/* ================= for PostDominance ================= */
void Dominance::PdomPostOrderWalk(BB *bb, int32 &pid, std::vector<bool> &visitedMap) {
  ASSERT(bb->GetBBId().idx < visitedMap.size(), "index out of range in  Dominance::PdomPostOrderWalk");
  if (bbVec[bb->GetBBId().idx] == nullptr) {
    return;
  }
  if (visitedMap[bb->GetBBId().idx]) {
    return;
  }
  visitedMap[bb->GetBBId().idx] = true;
  for (BB *pre : bb->GetPred()) {
    PdomPostOrderWalk(pre, pid, visitedMap);
  }
  CHECK_FATAL(bb->GetBBId().idx < pdomPostOrderIDVec.size(), "index out of range in  Dominance::PdomPostOrderWalk");
  pdomPostOrderIDVec[bb->GetBBId().idx] = pid++;
  return;
}

void Dominance::PdomGenPostOrderID() {
  ASSERT(!bbVec.empty(), "call calloc failed in Dominance::PdomGenPostOrderID");
  std::vector<bool> visitedMap(bbVec.size(), false);
  int32 postOrderID = 0;
  PdomPostOrderWalk(commonExitBB, postOrderID, visitedMap);
  // initialize pdomReversePostOrder
  int32 maxPostOrderID = postOrderID - 1;
  pdomReversePostOrder.resize(maxPostOrderID + 1);
  for (size_t i = 0; i < pdomPostOrderIDVec.size(); i++) {
    int32 postOrderNo = pdomPostOrderIDVec[i];
    if (postOrderNo == -1) {
      continue;
    }
    pdomReversePostOrder[maxPostOrderID - postOrderNo] = bbVec[i];
  }
}

BB *Dominance::PdomIntersect(BB *bb1, const BB *bb2) {
  while (bb1 != bb2) {
    while (pdomPostOrderIDVec[bb1->GetBBId().idx] < pdomPostOrderIDVec[bb2->GetBBId().idx]) {
      bb1 = pdoms[bb1->GetBBId().idx];
    }
    while (pdomPostOrderIDVec[bb2->GetBBId().idx] < pdomPostOrderIDVec[bb1->GetBBId().idx]) {
      bb2 = pdoms[bb2->GetBBId().idx];
    }
  }
  return bb1;
}

// Figure 3 in "A Simple, Fast Dominance Algorithm" by Keith Cooper et al.
void Dominance::ComputePostDominance() {
  pdoms.at(commonExitBB->GetBBId().idx) = commonExitBB;
  bool changed = false;
  do {
    changed = false;
    for (size_t i = 1; i < pdomReversePostOrder.size(); i++) {
      BB *bb = pdomReversePostOrder[i];
      BB *suc = nullptr;
      if (bb->GetAttributes(kBBAttrIsExit) || bb->GetSucc().empty()) {
        suc = commonExitBB;
      } else {
        suc = bb->GetSucc(0);
      }
      size_t j = 1;
      while ((pdoms[suc->GetBBId().idx] == nullptr || suc == bb) && j < bb->GetSucc().size()) {
        suc = bb->GetSucc(j);
        j++;
      }
      if (pdoms[suc->GetBBId().idx] == nullptr) {
        suc = commonExitBB;
      }
      BB *newIDom = suc;
      for (; j < bb->GetSucc().size(); j++) {
        suc = bb->GetSucc(j);
        if (pdoms[suc->GetBBId().idx] != nullptr && suc != bb) {
          newIDom = PdomIntersect(suc, newIDom);
        }
      }
      if (pdoms[bb->GetBBId().idx] != newIDom) {
        pdoms[bb->GetBBId().idx] = newIDom;
        ASSERT(pdoms[newIDom->GetBBId().idx] != nullptr, "null ptr check");
        changed = true;
      }
    }
  } while (changed);
}

// Figure 5 in "A Simple, Fast Dominance Algorithm" by Keith Cooper et al.
void Dominance::ComputePdomFrontiers() {
  for (BB *bb : bbVec) {
    if (bb == nullptr || bb == commonEntryBB) {
      continue;
    }
    if (bb->GetSucc().size() < 2) {
      continue;
    }
    for (BB *suc : bb->GetSucc()) {
      BB *runner = suc;
      while (runner != pdoms[bb->GetBBId().idx] && runner != commonEntryBB) {
        pdomFrontier[runner->GetBBId().idx].insert(bb->GetBBId());
        ASSERT(pdoms[runner->GetBBId().idx] != nullptr, "ComputePdomFrontiers: pdoms[] is nullptr");
        runner = pdoms[runner->GetBBId().idx];
      }
    }
  }
}

void Dominance::ComputePdomChildren() {
  for (BB *bb : bbVec) {
    if (bb == nullptr) {
      continue;
    }
    if (pdoms[bb->GetBBId().idx] == nullptr) {
      continue;
    }
    BB *parent = pdoms[bb->GetBBId().idx];
    if (parent == bb) {
      continue;
    }
    pdomChildren[parent->GetBBId().idx].insert(bb->GetBBId());
  }
}

void Dominance::ComputePdtPreorder(const BB *bb, size_t &num) {
  ASSERT(num < pdtPreOrder.size(), "index out of range in Dominance::ComputePdtPreOrder");
  pdtPreOrder[num++] = bb->GetBBId();
  for (BBId k : pdomChildren[bb->GetBBId().idx]) {
    ComputePdtPreorder(bbVec[k.idx], num);
  }
}

void Dominance::ComputePdtDfn() {
  for (size_t i = 0; i < pdtPreOrder.size(); i++) {
    pdtDfn[pdtPreOrder[i].idx] = i;
  }
}

// true if b1 postdominates b2
bool Dominance::PostDominate(const BB *b1, BB *b2) {
  if (b1 == b2) {
    return true;
  }
  CHECK_FATAL(b2->GetBBId().idx < pdoms.size(), "index out of range in Dominance::PostDominate");
  if (pdoms[b2->GetBBId().idx] == nullptr) {
    return false;
  }
  BB *impdom = b2;
  do {
    if (impdom == nullptr) {
      return false;
    }
    impdom = pdoms[impdom->GetBBId().idx];
    if (impdom == b1) {
      return true;
    }
  } while (impdom != commonExitBB);
  return false;
}

void Dominance::DumpDoms() {
  for (size_t i = 0; i < reversePostOrder.size(); i++) {
    BB *bb = reversePostOrder[i];
    LogInfo::MapleLogger() << "postorder no " << postOrderIDVec[bb->GetBBId().idx];
    LogInfo::MapleLogger() << " is bb:" << bb->GetBBId().idx;
    LogInfo::MapleLogger() << " im_dom is bb:" << doms[bb->GetBBId().idx]->GetBBId().idx;
    LogInfo::MapleLogger() << " domfrontier: [";
    for (BBId id : domFrontier[bb->GetBBId().idx]) {
      LogInfo::MapleLogger() << id.idx << " ";
    }
    LogInfo::MapleLogger() << "] domchildren: [";
    for (BBId id : domChildren[bb->GetBBId().idx]) {
      LogInfo::MapleLogger() << id.idx << " ";
    }
    LogInfo::MapleLogger() << "]" << std::endl;
  }
  LogInfo::MapleLogger() << std::endl;
  LogInfo::MapleLogger() << "preorder traversal of dominator tree:";
  for (BBId id : dtPreOrder) {
    LogInfo::MapleLogger() << id.idx << " ";
  }
  LogInfo::MapleLogger() << std::endl << std::endl;
}

void Dominance::DumpPdoms() {
  for (size_t i = 0; i < pdomReversePostOrder.size(); i++) {
    BB *bb = pdomReversePostOrder[i];
    LogInfo::MapleLogger() << "pdom_postorder no " << pdomPostOrderIDVec[bb->GetBBId().idx];
    LogInfo::MapleLogger() << " is bb:" << bb->GetBBId().idx;
    LogInfo::MapleLogger() << " im_pdom is bb:" << pdoms[bb->GetBBId().idx]->GetBBId().idx;
    LogInfo::MapleLogger() << " pdomfrontier: [";
    for (BBId id : pdomFrontier[bb->GetBBId().idx]) {
      LogInfo::MapleLogger() << id.idx << " ";
    }
    LogInfo::MapleLogger() << "] pdomchildren: [";
    for (BBId id : pdomChildren[bb->GetBBId().idx]) {
      LogInfo::MapleLogger() << id.idx << " ";
    }
    LogInfo::MapleLogger() << "]" << std::endl;
  }
  LogInfo::MapleLogger() << std::endl;
  LogInfo::MapleLogger() << "preorder traversal of post-dominator tree:";
  for (BBId id : pdtPreOrder) {
    LogInfo::MapleLogger() << id.idx << " ";
  }
  LogInfo::MapleLogger() << std::endl << std::endl;
}

}  // namespace maple
