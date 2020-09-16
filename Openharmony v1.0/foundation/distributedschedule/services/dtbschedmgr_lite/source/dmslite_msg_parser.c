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

#include "dmslite_msg_parser.h"

#include <stdlib.h>
#include <unistd.h>

#include "distributed_service_interface.h"
#include "dmslite_check_remote_permission.h"
#include "dmslite_famgr.h"
#include "dmslite_inner_common.h"
#include "dmslite_log.h"
#include "dmslite_tlv_common.h"

static int8_t ReadTlvNode(const TLV_NODE_S *head, TlvDmsMsgInfo *dmsMsg)
{
    TLV_ERR_CODE errCode = DMS_TLV_SUCCESS;
    TLV_NODE_S *tlvNode = (TLV_NODE_S*) head;
    while (tlvNode != NULL) {
        switch (tlvNode->type) {
            case DMS_TLV_TYPE_COMMAND_ID: {
                dmsMsg->commandId = *((uint8_t*) tlvNode->value);
                break;
            }

            case DMS_TLV_TYPE_CALLEE_BUNDLE_NAME: {
                dmsMsg->calleeBundleName = (char*) tlvNode->value;
                if (dmsMsg->calleeBundleName[tlvNode->length - 1] != '\0') {
                    errCode = DMS_TLV_ERR_BAD_SOURCE;
                }
                break;
            }

            case DMS_TLV_TYPE_CALLEE_ABILITY_NAME: {
                dmsMsg->calleeAbilityName = (char*) tlvNode->value;
                if (dmsMsg->calleeAbilityName[tlvNode->length - 1] != '\0') {
                    errCode = DMS_TLV_ERR_BAD_SOURCE;
                }
                break;
            }

            case DMS_TLV_TYPE_CALLER_SIGNATURE: {
                dmsMsg->callerSignature = (char*) tlvNode->value;
                if (dmsMsg->callerSignature[tlvNode->length - 1] != '\0') {
                    errCode = DMS_TLV_ERR_BAD_SOURCE;
                }
                break;
            }

            default: {
                HILOGW("[Unkonwn tlv type = %d]", tlvNode->type);
                errCode = DMS_TLV_ERR_UNKNOWN_TYPE;
                break;
            }
        }
        tlvNode = tlvNode->next;
    }

    return errCode;
}

static void TlvFreeNodeListMem(TLV_NODE_S *node)
{
    TLV_NODE_S *next = NULL;
    while (node != NULL) {
        next = node->next;
        free(node);
        node = next;
    }
}

static int8_t DecodeDmsTlv(const uint8_t *payload, uint16_t length, TlvDmsMsgInfo *dmsMsg)
{
    if (length > MAX_DMS_MSG_LENGTH || dmsMsg == NULL) {
        HILOGE("[Bad parameters][length = %d]", length);
        return DMS_TLV_ERR_PARAM;
    }

    TLV_NODE_S *head = NULL;
    TLV_ERR_CODE errCode = TlvBytesToNode(payload, length, &head);
    if (errCode == DMS_TLV_SUCCESS) {
        errCode = ReadTlvNode(head, dmsMsg);
    }
    HILOGI("[errCode = %d]", errCode);

    TlvFreeNodeListMem(head);

    return errCode;
}

static bool CanCall()
{
    uid_t callerUid = getuid();
    /* only foundation and xts (shell-enabled mode only) is reasonable to call DmsLiteProcessCommuMsg directly */
    if (callerUid != FOUNDATION_UID && callerUid != SHELL_UID) {
        HILOGD("[Caller uid is not allowed, uid = %d]", callerUid);
        return false;
    }
    return true;
}

int8_t DmsLiteProcessCommuMsg(const CommuInterInfo *interInfo, const IDmsFeatureCallback *dmsFeatureCallback)
{
    if (!CanCall()) {
        return DMS_EC_FAILURE;
    }

    if (interInfo == NULL || interInfo->payload == NULL || dmsFeatureCallback == NULL) {
        return DMS_EC_FAILURE;
    }

    TlvDmsMsgInfo dmsRequest = { 0 };
    int8_t errCode = DecodeDmsTlv(interInfo->payload, interInfo->payloadLength, &dmsRequest);
    /* mainly for xts testsuit convenient, in non-test mode the onTlvParseDone should be set NULL */
    if (dmsFeatureCallback->onTlvParseDone != NULL) {
        dmsFeatureCallback->onTlvParseDone(errCode, &dmsRequest);
    }
    if (errCode != DMS_TLV_SUCCESS) {
        return DMS_EC_PARSE_TLV_FAILURE;
    }

    switch (dmsRequest.commandId) {
        case DMS_MSG_CMD_START_FA: {
            errCode = CheckRemotePermission(&dmsRequest);
            if (errCode != DMS_EC_SUCCESS) {
                HILOGE("[CheckPermission failed]");
                return errCode;
            }
            errCode = StartAbilityFromRemote(dmsRequest.calleeBundleName, dmsRequest.calleeAbilityName,
                dmsFeatureCallback->onStartAbilityDone);
            break;
        }

        default: {
            HILOGW("[Unkonwn command id = %d]", dmsRequest.commandId);
            errCode = DMS_EC_UNKNOWN_COMMAND_ID;
            break;
        }
    }

    return errCode;
}