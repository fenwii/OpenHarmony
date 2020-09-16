/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ability_stack_manager.h"

#include "util/abilityms_helper.h"

namespace OHOS {
PageAbilityRecord *AbilityStackManager::GeneratePageAbility(const AbilityInfo &target,
    const Want &want, const PageAbilityRecord *topAbility, AbilityMgrContext &amsContext) const
{
    CHECK_NULLPTR_RETURN_PTR(target.name, "AbilityStackManager", "target ability name is nullptr");
    auto stack = const_cast<AbilityMissionStack *>(amsContext.GetTargetMissionStack(target.bundleName));
    CHECK_NULLPTR_RETURN_PTR(stack, "AbilityStackManager", "missionStack is nullptr");

    PageAbilityRecord *targetAbility = nullptr;
    AbilityMissionRecord *targetMission = stack->GetTargetMissionRecord(target.bundleName);
    /* launcher -> default or default -> launcher */
    if (topAbility == nullptr || AbilityMsHelper::IsAceAbility(target.name) ||
        (!topAbility->IsLauncherAbility() && AbilityMsHelper::IsLauncherAbility(target.bundleName)) ||
        (topAbility->IsLauncherAbility() && !AbilityMsHelper::IsLauncherAbility(target.bundleName))) {
        // Get the mission record of the current bundleName
        PRINTD("AbilityStackManager", "launcher jumps to default or default jumps to launcher");
        if (targetMission == nullptr) {
            targetMission = new AbilityMissionRecord(stack, target.bundleName);
            targetAbility = new PageAbilityRecord(target, want);
            targetMission->PushPageAbility(*targetAbility);
            stack->PushTopMissionRecord(*targetMission);
        } else {
            targetMission->SetPrevMissionRecord(nullptr);
            targetAbility = const_cast<PageAbilityRecord *>(targetMission->GetTopPageAbility());
            stack->MoveMissionRecordToTop(*targetMission);
        }
    } else {
        PRINTD("AbilityStackManager", "default application jumps to another default");
        auto topMissionRecord = stack->GetTopMissionRecord();
        if (targetMission == nullptr) {
            targetMission = new AbilityMissionRecord(stack, target.bundleName);
            stack->PushTopMissionRecord(*targetMission);
        } else {
            stack->MoveMissionRecordToTop(*targetMission);
        }
        if (topMissionRecord != nullptr && targetMission != topMissionRecord) {
            targetMission->SetPrevMissionRecord(topMissionRecord);
        }
        targetAbility = new PageAbilityRecord(target, want);
        targetMission->PushPageAbility(*targetAbility);
    }

    amsContext.SetTopMissionStacks(stack);
    return targetAbility;
}

const PageAbilityRecord *AbilityStackManager::GetTopPageAbility(const AbilityMgrContext &amsContext) const
{
    const AbilityMissionStack *topMissionStack = amsContext.GetTopMissionStacks();
    CHECK_NULLPTR_RETURN_PTR(topMissionStack, "AbilityStackManager", "topMissionStack is nullptr");
    return topMissionStack->GetTopPageAbility();
}

void AbilityStackManager::RemovePageAbility(const PageAbilityRecord &target, AbilityMgrContext &amsContext)
{
    AbilityMissionRecord *missionRecord = const_cast<AbilityMissionRecord *>(target.GetMissionRecord());
    CHECK_NULLPTR_RETURN(missionRecord, "AbilityStackManager", "missionRecord is nullptr");
    missionRecord->RemovePageAbility(target);
    // Current mission reocrd is empty
    if (missionRecord->IsEmpty()) {
        AbilityMissionStack *stack = const_cast<AbilityMissionStack *>(missionRecord->GetMissionStack());
        if (stack != nullptr) {
            stack->RemoveMissionRecord(*missionRecord);
        }
        auto prevMissionRecord = const_cast<AbilityMissionRecord *>(missionRecord->GetPrevMissionRecord());
        if (stack != nullptr && prevMissionRecord != nullptr) {
            stack->MoveMissionRecordToTop(*prevMissionRecord);
        } else {
            amsContext.SetTopMissionStacks(amsContext.GetLauncherMissionStacks());
        }
        delete missionRecord;
    }
}

void AbilityStackManager::ClearAbilityStack(const char *bundleName, AbilityMgrContext &amsContext) const
{
    CHECK_NULLPTR_RETURN(bundleName, "AbilityStackManager", "invalid argument");
    AbilityConnectMission *connectMission = const_cast<AbilityConnectMission *>(amsContext.GetServiceConnects());
    if (connectMission != nullptr) {
        connectMission->RemoveServiceRecord(bundleName);
    }
    // get target mission record
    auto missionStack = const_cast<AbilityMissionStack *>(amsContext.GetTargetMissionStack(bundleName));
    CHECK_NULLPTR_RETURN(missionStack, "AbilityStackManager", "missionStack is nullptr");
    AbilityMissionRecord *missionRecord = missionStack->GetTargetMissionRecord(bundleName);
    if (missionRecord != nullptr) {
        // if default application jumps to another default, return prev application
        auto prevMissionRecord = const_cast<AbilityMissionRecord *>(missionRecord->GetPrevMissionRecord());
        if (prevMissionRecord != nullptr) {
            missionStack->MoveMissionRecordToTop(*prevMissionRecord);
        } else {
            // return launcher application
            const AbilityMissionStack *topMissionStack = amsContext.GetTopMissionStacks();
            if (topMissionStack != nullptr && topMissionStack->IsTopMissionRecord(bundleName)) {
                amsContext.SetTopMissionStacks(amsContext.GetLauncherMissionStacks());
            }
        }
    }

    missionStack->RemoveMissionRecord(connectMission, bundleName);
}

PageAbilityRecord *AbilityStackManager::FindPageAbility(const AbilityMgrContext &amsContext, uint64_t token) const
{
    PageAbilityRecord *record = nullptr;
    const AbilityMissionStack *stack = amsContext.GetDefaultMissionStacks();
    if (stack != nullptr) {
        record = stack->FindPageAbility(token);
        if (record != nullptr) {
            return record;
        }
    }
    stack = amsContext.GetLauncherMissionStacks();
    if (stack != nullptr) {
        record = stack->FindPageAbility(token);
    }

    // find service ability
    if (record == nullptr) {
        auto serviceConnects = amsContext.GetServiceConnects();
        if (serviceConnects != nullptr) {
            record = serviceConnects->FindServiceRecord(token);
        }
    }
    return record;
}

const PageAbilityRecord *AbilityStackManager::FindPageAbility(const AbilityMgrContext &amsContext,
    const Want &want) const
{
    CHECK_NULLPTR_RETURN_PTR(want.element, "AbilityStackManager", "element is nullptr");
    auto missionStack = amsContext.GetTargetMissionStack(want.element->bundleName);
    CHECK_NULLPTR_RETURN_PTR(missionStack, "AbilityStackManager", "target mission stack is nullptr");
    PageAbilityRecord *record = missionStack->FindPageAbility(want);
    if (record != nullptr) {
        return record;
    }
    const AbilityConnectMission *connectMission = amsContext.GetServiceConnects();
    CHECK_NULLPTR_RETURN_PTR(connectMission, "AbilityStackManager", "service connect is nullptr");
    return connectMission->FindServiceRecord(want.element->bundleName, want.element->abilityName);
}

const PageAbilityRecord *AbilityStackManager::GetPrevPageAbility(const AbilityMgrContext &amsContext,
    const PageAbilityRecord &current) const
{
    AbilityMissionRecord *currentMission = const_cast<AbilityMissionRecord *>(current.GetMissionRecord());
    if (currentMission != nullptr) {
        PageAbilityRecord *prevAbility = currentMission->GetPrevPageAbility(current);
        if (prevAbility != nullptr) {
            return prevAbility;
        } else {
            auto prevMission = currentMission->GetPrevMissionRecord();
            if (prevMission != nullptr) {
                return prevMission->GetTopPageAbility();
            }
        }
    }
    auto launcherStack = amsContext.GetLauncherMissionStacks();
    CHECK_NULLPTR_RETURN_PTR(launcherStack, "AbilityStackManager", "launcherStack is nullptr");
    return launcherStack->GetTopPageAbility();
}

bool AbilityStackManager::ExistAppInStack(const AbilityInfo &target, AbilityMgrContext &amsContext) const
{
    auto stack = amsContext.GetTargetMissionStack(target.bundleName);
    if (stack == nullptr) {
        return false;
    }
    AbilityMissionRecord *targetMission = stack->GetTargetMissionRecord(target.bundleName);
    return targetMission != nullptr;
}

#ifdef OHOS_DEBUG
AbilityMsStatus AbilityStackManager::DumpAllAbilityRecord(const AbilityMgrContext &amsContext) const
{
    AbilityMsStatus result = AbilityMsStatus::DumpStatus("");
    const AbilityMissionStack *stack = amsContext.GetTopMissionStacks();
    if (stack != nullptr) {
        result.DumpAppend(stack->DumpMissionStack());
        if (stack->GetStackType() == LAUNCHER) {
            stack = amsContext.GetDefaultMissionStacks();
            if (stack != nullptr) {
                result.DumpAppend(stack->DumpMissionStack());
            }
        } else if (stack->GetStackType() == DEFAULT) {
            stack = amsContext.GetLauncherMissionStacks();
            if (stack != nullptr) {
                result.DumpAppend(stack->DumpMissionStack());
            }
        }
    }
    const AbilityConnectMission *mission = amsContext.GetServiceConnects();
    if (mission != nullptr) {
        result.DumpAppend(mission->DumpConnectMission());
    }
    return result;
}
#endif

PageAbilityRecord *AbilityStackManager::FindServiceAbility(const AbilityMgrContext &amsContext, uint64_t token) const
{
    auto serviceConnects = amsContext.GetServiceConnects();
    CHECK_NULLPTR_RETURN_PTR(serviceConnects, "AbilityStackManager", "serviceConnects is nullptr");
    return serviceConnects->FindServiceRecord(token);
}

PageAbilityRecord *AbilityStackManager::FindServiceAbility(const AbilityMgrContext &amsContext,
    const char *bundleName, const char *abilityName) const
{
    auto serviceConnects = amsContext.GetServiceConnects();
    CHECK_NULLPTR_RETURN_PTR(serviceConnects, "AbilityStackManager", "serviceConnects is nullptr");
    return serviceConnects->FindServiceRecord(bundleName, abilityName);
}
}
