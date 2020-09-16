/**
 * @file hks_device_provision.h
 *
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved. \n
 * Description: device pki provision, verify; efuse write, verify function \n
 * Author: Huawei \n
 * Create: 2020-03-26
 */

 /**
 * @defgroup iot_hks
 * @ingroup hks
 */

#ifndef HKS_DEVICE_PROVISION_H
#define HKS_DEVICE_PROVISION_H

#include "hks_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @ingroup  iot_hks
* @brief Production write efuse and certificate import verification function.
  CNcomment:产线写入efuse和证书导入验证功能。CNend
*
* @par 描述:
*           Production write efuse and certificate import verification function.
  CNcomment:产线写入efuse和证书导入验证功能。CNend
*
* @attention None
* @param  cmd       [IN] type #uint32_t，Command word id. CNcomment: 命令字id。CNend
* @param  input     [IN] type #const struct hks_blob *，keybox data for pki provision function;
  common name information for certificate.
  CNcomment:证书导入keybox数据或者为证书common name信息。CNend
* @param  output    [OUT] type #struct hks_blob *，reserved parameters, not used. CNcomment:保留参数，暂不使用。CNend
* @retval #0       Success.
* @retval #Other   Failure.
* @par 依赖:
*            @li hks_types.h：describes hks_types SDK interfaces.CNcomment:描述hks_types SDK的接口。CNend
* @see hks_pki_provision
*/
HKS_DLL_API_PUBLIC int32_t hks_pki_provision(uint32_t cmd, const struct hks_blob *input, struct hks_blob *output);

#ifdef __cplusplus
}
#endif

#endif /* HKS_DEVICE_PROVISION_H */
