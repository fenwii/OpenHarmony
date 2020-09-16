/**
 * @file hi_mdm_types.h
 *
 * Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
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

#ifndef __HI_MDM_TYPES_H__
#define __HI_MDM_TYPES_H__
#ifndef __HI_TYPES_H__
#error "Please include hi_types.h before using hi_mdm_types.h"
#endif
HI_START_HEADER

#include <hi_types_base.h>

#define HI_ALL_F_32          0xFFFFFFFF

typedef struct {
    hi_u32 major_minor_version;
    hi_u32 revision_version;
    hi_u32 build_version;
} hi_ue_soft_version;

#define HI_BUILD_VER_DATE_LEN             10
#define HI_BUILD_VER_TIME_LEN             8
#define HI_BUILD_VER_PRODUCT_NAME_LEN_MAX 28
#define HI_BUILD_VER_PRODUCT_LEN_MAX      (HI_BUILD_VER_PRODUCT_NAME_LEN_MAX + HI_BUILD_VER_DATE_LEN + \
                                            HI_BUILD_VER_TIME_LEN + 6)
typedef struct {
    hi_u16 version_v;
    hi_u16 version_r;
    hi_u16 version_c;
    hi_u16 version_b;
    hi_u16 version_spc;
    hi_u16 reserved[3];  /* 3 bytes reserved */
} hi_ue_product_ver;

typedef struct {
    hi_char* build_date; /* pszDate;        // For example: 2011-08-01 */
    hi_char* build_time; /* pszTime;        // For example: 14:30:26 */
} hi_product_info;

/*
* @ingroup  iot_diag
* @brief Registers the callback function for DIAG channel status changes.
CNcomment:DIAG通道状态变更回调函数。CNend
*
* @par 描述:
*      Registers the callback function for DIAG channel status changes. That is, when the DIAG channel is
*      connected or disconnected, the function registered by this API is called back.
CNcomment:注册DIAG通道变更回调函数（即：当DIAG通道连接或断开时，会回调本接口注册的函数）。CNend
*
* @attention None。
* @param  port_num   [IN] type #hi_u16，port number.
CNcomment:端口号。CNend
* @param  is_connected  [IN] type #hi_bool，connection status.
CNcomment:连接状态。CNend
*
* @retval #0      Success.
* @retval #Other  Failure. For details, see hi_errno.h.
* @par Dependency:
*           @li hi_diag.h: Describes DIAG APIs.
CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
 */
typedef hi_u32 (*hi_diag_connect_f)(hi_u16 port_num, hi_bool is_connected);

/**
* @ingroup  iot_dms
*
* Strcture of Channel interface object.
CNcomment:通道接口实例结构。CNend
*/
#define HI_DMS_FRM_INTER_INFO1_SIZE (sizeof(hi_u8) + sizeof(hi_u8)) /* mmt, vt */
#define HI_DMS_FRM_INTER_INFO2_SIZE 4                             /* 公用控制字段长度 */
#define HI_DMS_INTER_INFO_SIZE      (HI_DMS_FRM_INTER_INFO1_SIZE + HI_DMS_FRM_INTER_INFO2_SIZE)

typedef struct {
    hi_u16 data_size;                          /**< Length of data element(Unit: type).
                                                  CNcomment: 数据大小，即ucData所占空间大小（单位：byte）CNend */
    hi_u8 inside_info[HI_DMS_INTER_INFO_SIZE]; /**< For internal use. CNcomment:内部使用CNend */
    hi_u8 data[0];                             /**< Data. CNcomment:数据CNend */
} hi_dms_chl_tx_data;

#define HI_DMS_CHL_FRAME_HRD_SIZE (sizeof(hi_dms_chl_tx_data))

typedef struct {
    hi_u32 id;  /* Specify the message id. */
    hi_u32 src_mod_id;
    hi_u32 dest_mod_id;
    hi_u32 data_size;  /* the data size in bytes. */
    hi_pvoid data;     /* Pointer to the data buffer. */
} hi_diag_layer_msg;

/**
* @ingroup  iot_diag
* @brief Callback function for handling diagnosis commands.
CNcommond:HSO命令处理回调函数。CNend
*
* @par 描述:
*           Callback function for handling diagnosis commands, that is, the function body for executing commands.
CNcomment:HSO命令处理回调函数，即命令的执行函数体。CNend
*
* @attention
*           @li If the returned value is not HI_ERR_CONSUMED, the DIAG framework automatically forwards
*               the returned value to the host. CNcomment:如果返回值不为HI_ERR_CONSUMED，
则表示有DIAG框架自动直接将返回值回复给HSO。CNend
*           @li If the return value is HI_ERR_CONSUMED, it indicates that the user sends a response (local connection)
*               to the host through the hi_diag_send_ack_packet API. The DIAG framework does not automatically
*               respond to the host. CNcomment:如果返回值为HI_ERR_CONSUMED，
则表示用户通过hi_diag_send_ack_packet接口给HSO应答（本地连接），DIAG框架不自动给HSO应答。CNend
*           @li The return value of the API cannot be HI_ERR_NOT_FOUND.
CNcomment:该注册接口的返回值不能为HI_ERR_NOT_FOUND。CNend
* @param  cmd_id          [IN] type #hi_u16，Command ID CNcomment:命令ID。CNend
* @param  cmd_param       [IN] type #hi_pvoid，Pointer to the use input command.
CNcomment:用户输入命令指针。CNend
* @param  cmd_param_size  [IN] type #hi_u16，Length of the command input by the user (unit:byte).
CNcomment:用户输入命令长度（单位：byte）。CNend
* @param  option          [IN] type #hi_u8，#HI_DIAG_CMD_INSTANCE_LOCAL and #HI_DIAG_CMD_INSTANCE_IREMOTE are supported.
CNcomment:支持使用#HI_DIAG_CMD_INSTANCE_LOCAL、#HI_DIAG_CMD_INSTANCE_IREMOTE。CNend.
*
* @retval #0              Success
* @retval #Other            Failure. For details, see hi_errno.h
* @par Dependency:
*           @li hi_diag.h: Describes DIAG APIs.
CNcomment: 文件用于描述DIAG相关接口。CNend
* @see  None.
*/
typedef hi_u32 (*hi_diag_cmd_f)(hi_u16 cmd_id, hi_pvoid cmd_param, hi_u16 cmd_param_size, hi_u8 option);
/**
* @ingroup  iot_diag
* Command registration structure. The same callback function can be used within the command ID range.
CNcommand:命令注册结构体，支持标注命令ID范围内使用同一个回调函数。CNend.
*
* If a single command is used, the maximum and minimum IDs are the same.
CNcommand:如果单命令，则最大和最小填写相同ID号。CNend
*/
typedef struct {
    hi_u16 min_id;           /**< Minimum DIAG ID, [0, 65535]. CNcomment:最小的DIAG ID，取值范围[0, 65535]。 CNend */
    hi_u16 max_id;           /**< Maximum DIAG ID, [0, 65535]. CNcomment:最大的DIAG ID，取值范围[0, 65535]。 CNend */
    hi_diag_cmd_f input_cmd; /**< This Handler is used to process the HSO command.
                                CNcomment:处理HSO命令的入口函数。CNend */
} hi_diag_cmd_reg_obj;

/**
 * @ingroup  iot_diag
 * Local instance  -->HSO  Interaction command between the host software and the local station.
 CNcomment:本地实例  -->HSO  表示上位机软件和本地站点间的交互命令 CNend
 */
#define HI_DIAG_CMD_INSTANCE_DEFAULT ((hi_u8)0)

/**
 * @ingroup  iot_diag
 * Local instance  -->HSO  Interaction command between the host software and the local station.
 CNcomment: 本地实例  -->HSO  表示上位机软件和本地站点间的交互命令 CNend
 */
#define HI_DIAG_CMD_INSTANCE_LOCAL   HI_DIAG_CMD_INSTANCE_DEFAULT /* Local CMD.CNcomment:本地命令 CNend */
#define HI_DIAG_CMD_INSTANCE_IREMOTE 1 /* Remote CMD.CNcomment:远程命令 CNend */

#if defined(HAVE_PCLINT_CHECK)
#define hi_check_default_id(id) (id)
#else
#define hi_check_default_id(id) (((id) == 0) ? __LINE__ : (id))
#endif
#define hi_diag_log_msg_mk_id_e(id) hi_makeu32(((((hi_u16)(hi_check_default_id(id))) << 2) + 0), \
    HI_DIAG_LOG_MSG_FILE_ID)
#define hi_diag_log_msg_mk_id_w(id) hi_makeu32(((((hi_u16)(hi_check_default_id(id))) << 2) + 1), \
    HI_DIAG_LOG_MSG_FILE_ID)
#define hi_diag_log_msg_mk_id_i(id) hi_makeu32(((((hi_u16)(hi_check_default_id(id))) << 2) + 2), \
    HI_DIAG_LOG_MSG_FILE_ID)

#define HI_ND_SYS_BOOT_CAUSE_NORMAL        0x0
#define HI_ND_SYS_BOOT_CAUSE_EXP           0x1
#define HI_ND_SYS_BOOT_CAUSE_WD            0x2
#define HI_ND_SYS_BOOT_CAUSE_UPG_VERIFY    0x3
#define HI_ND_SYS_BOOT_CAUSE_UPG_FAIL      0x4
#define HI_ND_SYS_BOOT_CAUSE_UPG_BACK_FAIL 0x5

#define CHANLLENGE_SALT_SIZE 16
/******************************DIAG***********************************************/
#define HI_DIAG_LOG_OPT_LOCAL_REQ           1 /**< Local command request from the host to DIAG.
                                                 CNcomment:本地命令请求 上位机->DIAG CNend */
#define HI_DIAG_LOG_OPT_LOCAL_IND           2 /**< local response from DIAG to the host.
                                                 CNcomment: 本地应答 DIAG ->上位机 CNend */
#define HI_DIAG_LOG_OPT_LOCAL_ACK           3 /**< Local ACK from DIAG to the host.
                                                 CNcomment: 本地ACK DIAG ->上位机 CNend */

/**
 * @ingroup  iot_diag
 * Describes the command type transferred to the app layer.
 CNcomment: 描述传递给应用层的命令类型。CNend
 */
typedef struct {
    /**< Option configuration, which is used to set the command as a local command or a remote
       * command. The value is a HI_DIAG_LOG_OPT_XXX macro such as #HI_DIAG_LOG_OPT_LOCAL_REQ.
       CNcomment: 选项配置，用于设置此命令为本地命令或远程命令等信息，
       取值为HI_DIAG_LOG_OPT_XXX 宏 CNend */
    hi_u32 opt;
} hi_diag_log_ctrl;

/**
* @ingroup  iot_diag
* @brief  Callback function for notifying DIAG operations.
CNcomment:DIAG操作通知回调函数。CNend
*
* @par 描述:
*          Carbon copies data to the app layer by using a callback function in
*          the case of data interaction between the host and the board.
CNcomment: 该函数用于当HSO与单板有数据交互发生时，将数据通过回调函数抄送给应用层。CNend
*
* @attention 无。
* @param  cmd_id       [IN] type #hi_u32，Command ID. CNcomend:命令ID。CNend
* @param  buffer       [IN] type #hi_pvoid，Data pointer transferred to the app layer.
CNcomment:传递给应用层的数据指针。CNend
* @param  buffer_size  [IN] type #hi_u16，Length of the data transferred to the app layer (unit: byte)
CNcomment:传递给应用层的数据长度（单位：byte）。CNend
* @param  log_ctrl     [IN] type #hi_diag_log_ctrl*，Command type sent to the app layer
CNcomment:传递给应用层的命令类型。CNend
*
* @retval #0             Success
* @retval #Other         Failure. For details, see hi_errno.h.
* @par Dependency:
*           @li hi_diag.h：Describes DIAG APIs. CNcomment:文件用于描述DIAG相关接口。CNend
* @see  None
 */
typedef hi_void (*hi_diag_cmd_notify_f)(hi_u16 cmd_id, hi_pvoid buffer, hi_u16 buffer_size,
                                        hi_diag_log_ctrl *log_ctrl);
HI_END_HEADER
#endif  /* __HI_MDM_TYPES_H__ */
