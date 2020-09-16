/**
 * @file hi_reset.h
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

/** @defgroup iot_sys  Active Reset
 * @ingroup system
 */

#ifndef __HI_RESET_H__
#define __HI_RESET_H__
#include <hi_types.h>
#include <hi_mdm_types.h>
#include <hi_ft_nv.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HI_SYS_REBOOT_CAUSE_USR_BEGIN   0x8000
#define HI_SYS_REBOOT_CAUSE_USR_END     63 /* 8bit: 0 - 63 */

/**
* @ingroup  iot_sys
*
* Cause for active restart. CNcomment:主动重启原因CNend
*/
typedef enum {
    HI_SYS_REBOOT_CAUSE_UNKNOWN = 0,
    HI_SYS_REBOOT_CAUSE_CMD,        /**< system reset begin. */
    HI_SYS_REBOOT_CAUSE_UPG,        /**< upgrade reset begin. */
    HI_SYS_REBOOT_CAUSE_UPG_B,      /**< upgrade backup image reset. */
    HI_SYS_REBOOT_CAUSE_WIFI_MODE,  /**< wifi module reset begin. */
    HI_SYS_REBOOT_CAUSE_USR_NORMAL_REBOOT, /**< user reset begin. */
    HI_SYS_REBOOT_CAUSE_USR0,
    HI_SYS_REBOOT_CAUSE_USR1,
    HI_SYS_REBOOT_CAUSE_AT_BUSY,
    HI_SYS_REBOOT_CAUSE_MAX = HI_SYS_REBOOT_CAUSE_USR_END + 1,
} hi_sys_reboot_cause;

/**
* @ingroup  iot_sys
* @brief  System hard reboot. CNcomment:系统硬重启。CNend
*
* @par 描述:
*          System Hard reboot:reset whole chip. CNcomment:硬重启 ：整芯片复位。CNend
*
* @attention  None
*
* @param  cause         [IN] type #hi_sys_reboot_cause , reboot cause, see hi_sys_reboot_cause.
CNcomment:重启原因，取值参见hi_sys_reboot_cause。CNend
*
*
* @retval None.
*
* @par 依赖:
*            @li hi_reset.h: Describes the APIs for obtaining system information.
CNcomment:文件用于描述系统复位相关接口。CNend
* @see None
*/
hi_void hi_hard_reboot(hi_sys_reboot_cause cause);

/**
* @ingroup  iot_sys
* @brief  System soft reboot. CNcomment:系统软重启。CNend
*
* @par 描述:
*          System Soft reboot:part of peripheral won't reset(such as GPIO/PWM).
CNcomment:软重启：部分外设不复位，如GPIO/PWM。CNend
* @attention
*           @li only GPIO is the default peripheral that won't reset when soft reboot.
PWM should config in menuconfig. other peripheras need another setting.
CNcomment:仅GPIO在软重启时默认不复位，PWM需要在menuconfig中配置，
其余外设需要额外配置。CNend
*
* @param  cause         [IN] type #hi_sys_reboot_cause ,  reboot cause, see hi_sys_reboot_cause.
CNcomment:重启原因，取值参见hi_sys_reboot_cause。CNend
*
*
* @retval None.
*
* @par 依赖:
*            @li hi_reset.h: Describes the APIs for obtaining system information.
CNcomment:文件用于描述系统复位相关接口。CNend
* @see None
*/
hi_void hi_soft_reboot(hi_sys_reboot_cause cause);

/**
* @ingroup  iot_sys
* @brief  Enables or disables the function of recording the reset times.
CNcomment:使能(去使能)记录复位次数功能。CNend
*
* @par 描述:
*     @li Enables or disables the function of recording the reset times. When the function of recording the reset times
*         is enabled, in order to avoid the issue that fast flash life exhaustion caused by writing NV when the system
*         is frequently powered on and off, NV will be written 30 seconds after the system is started.
CNcomment:使能(去使能)记录复位次数功能。使能复位次数记录功能后，
为避免系统经常频繁上下电时写NV导致flash寿命快速耗尽问题，每次启动时会在上电后30秒时写NV,正常计数复位次数。CNend
*     @li When the number of reset times is updated, the flash memory needs to be written. Generally, when the system
*         frequently powers on and off and power-on NV write greatly hurts the flash service life, set enable to
*         HI_FALSE and check whether the service function is affected.
CNcomment:复位次数更新需要执行写Flash操作，通常在系统经常频繁上下电，
不能接受上电写NV导致flash寿命快速耗尽的场景时，将enable设置为HI_FALSE，
同时要考虑是否对业务功能造成影响。CNend
*     @li Set enable takes effect after the next reset, and set disable takes effect when write NV next time.
CNcomment:配置开启是在下次复位后生效，配置关闭是在下次写NV时生效。CNend
*
* @attention
*   @li This feature should be disable by default. CNcomment:该功能默认不使能。CNend
*   @li It should be called in the initialization function of the app layer.
CNcomment:应该在应用层初始化函数中调用。CNend
*   @li Disabling this function may result in some influences. You are advised to disable it in scenarios where the
*       system is frequently powered on and off.CNcomment:关闭该功能需要考虑对使用复位次数业务功能
的影响，建议在系统经常频繁上下电的场景关闭该功能，其他场景打开该功能。CNend
*
* @param enable [IN] type #hi_bool Enable/Disable. CNcomment:是否使能计数功能。CNend
*
* @retval #0               Success.
* @retval #Other           Failure. For details, see hi_errno.h.
*
* @par 依赖:
*            @li hi_reset.h: Describes the APIs for obtaining system information.
CNcomment:文件用于描述系统复位相关接口。CNend
* @see None
*/
hi_u32 hi_enable_reset_times_save(hi_bool enable);

/**
* @ingroup  iot_sys
* @brief  Obtains reset times recorded in NV. CNcomment:获取NV中记录的系统复位次数。CNend
*
* @par 描述:
*          Obtains reset times recorded in NV. CNcomment:获取NV中记录的系统复位次数。CNend
*
* @attention  None
*
* @param None
*
* @retval #HI_ERR_FAILURE  Read NV Failure.
* @retval #Other           Reboot times number. CNcomment:系统复位次数。CNend
*
* @par 依赖:
*            @li hi_reset.h: Describes the APIs for obtaining system information.
CNcomment:文件用于描述系统复位相关接口。CNend
* @see None
*/
hi_u32 hi_get_reset_times(hi_void);

#ifdef __cplusplus
}
#endif

#endif /* __HI_RESET_H__ */

