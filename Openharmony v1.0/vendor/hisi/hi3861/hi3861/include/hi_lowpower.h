/**
 * @file hi_lowpower.h
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

/**
 * @defgroup iot_lp Power consumption management
 * @ingroup  system
 */

#ifndef __HI_LOWPOWER_H__
#define __HI_LOWPOWER_H__

#include <hi_types.h>
#include <hi_gpio.h>

/**
 * @ingroup iot_lp
 * UDP wakes up source enumeration.
 */
typedef enum {
    HI_UDS_GPIO3 = 1 << 0,  /**< ultra sleep wakeup source GPIO3.CNcomment:超深睡唤醒源GPIO3 CNend */
    HI_UDS_GPIO5 = 1 << 1,  /**< ultra sleep wakeup source GPIO5.CNcomment:超深睡唤醒源GPIO5 CNend */
    HI_UDS_GPIO7 = 1 << 2,  /**< ultra sleep wakeup source GPIO7.CNcomment:超深睡唤醒源GPIO7 CNend */
    HI_UDS_GPIO14 = 1 << 3, /**< ultra sleep wakeup source GPIO14.CNcomment:超深睡唤醒源GPIO14 CNend */
} hi_udsleep_src;

/**
 * @ingroup iot_lp
 * Sleep level enumeration.
 */
typedef enum {
    HI_NO_SLEEP,    /**< no sleep type.CNcomment:不睡模式 CNend */
    HI_LIGHT_SLEEP, /**< light sleep type.CNcomment:浅睡模式 CNend */
    HI_DEEP_SLEEP,  /**< deep sleep type.CNcomment:深睡模式 CNend */
} hi_lpc_type;

/**
 * @ingroup hct_lp
 *
 * 睡眠模块ID 枚举，每个id占用1个bit，继续扩展时要注意最大为(1 << 31)。
 */
typedef enum {
    HI_LPC_ID_DIAG  = 1 << 0, /**< diag uart Id.CNcomment:diag模块 Id */
    HI_LPC_ID_SHELL = 1 << 1, /**< shell Id.CNcomment:shell模块 Id CNend */
    HI_LPC_ID_RSV   = 1 << 15, /**< 之前均为内部预留id.CNcomment:内部预留 Id CNend */
    HI_LPC_ID_DEMO  = 1 << 16, /**< demo Id.CNcomment:低功耗管理id样例，之后为客户预留Id CNend */
}hi_lpc_id;

/**
 * @ingroup iot_lp
 * Low power management structure.
 */
typedef struct {
    hi_u32  wakeup_times;                   /**< wakeup times.CNcomment:唤醒次数统计 CNend */
    hi_u32  sleep_threshold_refuse_times;  /**< sleep threshold refuse times.CNcomment:
                                                可睡时间小于设定门限次数统计 CNend */
    hi_u32  sleep_check_refuse_times;       /**< sleep check refuse times.CNcomment:
                                                入睡投票睡眠失败次数统计 CNend */
    hi_u32  sleep_times;                   /**< sleep times.CNcomment:入睡次数统计 CNend */
    hi_u32  sleep_threshold;               /**< sleep threshold, unit is ms, only when
                                                the system' Remaining idle time is bigger than the threshold,
                                                system can enter deep sleep state.CNcomment:深睡眠门限，单位
                                                为ms，当系统剩余空闲时间大于该门限时，方可进入深睡 CNend */
    hi_u32  dsleep_fail_times; /**< the times of power off fail during deepsleep.CNcomment:深睡下电失败次数统计 CNend */
    hi_u8   type;                  /**< hi_lpc_type type, enable low power management.
                                         CNcomment:hi_lp_type类型，低功耗类型 CNend */
    hi_u8   evt_sts;                 /**< wakeup event state, bit0:gpio wkup, bit1:rtc wkup, bit2:sdio wkup, bit4:
                                        sta0 wkup, bit5:sta1 wkup, bit6:ap0 wkup.CNcomment:唤醒事件状态，bit0:gpio 唤醒，
                                        bit1:rtc 唤醒，bit2:sdio 唤醒，bit4:sta0 唤醒, bit5:sta1 唤醒，
                                        bit6:ap0 唤醒。 CNend */
    hi_u8   int_sts;                 /**< wakeup interrupt state, bit0:gpio wkup, bit1:rtc wkup, bit2:sdio wkup, bit4:
                                        sta0 wkup, bit5:sta1 wkup, bit6:ap0 wkup.CNcomment:唤醒中断状态，bit0:gpio 唤醒，
                                        bit1:rtc 唤醒，bit2:sdio 唤醒，bit4:sta0 唤醒, bit5:sta1 唤醒,
                                        bit6:ap0 唤醒 CNend */
    hi_u8   last_time_vote_state;    /**< last time vote state, 0:no sleep, 1: light sleep, 2: deep sleep.
                                        CNcomment:最近一次睡眠状态，0:没有入睡，1:浅睡，2:深睡。 CNend */
    hi_u32  timer_ticks; /**< the time ticks is about to expire, unit is 10 ms, if the value is 0xffffffff, there is
                                no timer that is about to expire.
                            CNcomment:定时器即将到期的时间，单位为10ms；如果是0xffffffff，表示没有即将到期的
                            定时器 CNend */
    hi_u32  timer_handle; /**< the callback function address of the timer that is about to expire. if the value is
                                0xffffffff, it means that there is no timer that is about to expire.
                            CNcomment:即将到期定时器回调函数的地址，如果是0xffffffff,表示没有即将到期的定时器 CNend */
    hi_u32  timer_handle_arg; /**< the parameter of the timer callback function, if the value is 0xffffffff, it means
                                there is no timer to expire.CNcomment:定时器回调函数的参数，如果是0xffffffff,
                                表示没有即将到期的定时器 CNend */
    hi_u32  task_ticks;  /**< the task ticks is about to expire, unit is 10 ms.CNcomment:任务即将到期的时间，
                            单位为10ms。CNend */
    hi_u32  task_id; /**< the task id that is about to expire.CNcomment:即将到期任务的ID。CNend */
    hi_u32  sleep_ticks; /**< last sleep time ticks, unit is 10 ms.CNcomment:最近一次睡眠的tick时间，
                            单位为10ms。CNend */
    hi_u32  veto_info;   /**< veto_info.CNcomment:投票否决睡眠信息，详见hi_lpc_id。CNend */
    hi_u16  dsleep_wk_gpio; /**< wakeup gpio for deep sleep.CNcomment:唤醒的GPIO,该值(1<<x)为1表示GPIOx使能。CNend */
    hi_u16  reserve;   /**< reserve.CNcomment:预留。CNend */
    hi_u32  refuse_vote_handle; /**< Address of voting funcfion refusing to vote for sleep.CNcomment:
                                    拒绝投睡眠票的投票函数地址。CNend */
} hi_lpc_info;

/**
 * @ingroup  iot_lp
 * @brief  Low power initialization.
 *
 * @par Description:
 *           Initializes power saving management. CNcomment:低功耗初始化CNend
 *
 * @attention This is an initialization API and does not support multi-task calling or repeated calling.
 must call after hi_sal_init.
 CNcomment:初始化操作是非多任务安全的，并且不支持重复调用。
 必须在hi_sal_init之后调用。CNend
 * @param  None
 *
 * @retval #0                Success.
 * @retval #Other            Failure. For details, see hi_errno.h.
 * @par Dependency:
 *            @li hi_lowpower.h: Describes power saving management APIs.
 * @see  None
 */
hi_u32 hi_lpc_init(hi_void);

/**
 * @ingroup  iot_lp
 * @brief  Set current lowpower type.
 *
 * @par Description:
 *           Set current lowpower sleep mode. CNcomment:设置低功耗模式CNend
 *
 * @param  type  [IN] type #hi_lpc_type type.
 CNcomment:低功耗模式CNend
 *
 * @retval #HI_ERR_SUCCESS   Success.
 * @retval #Other    Failure. For details, see hi_errno.h.
 * @par Dependency:
 *            @li hi_lowpower.h: Describes power saving management APIs.
 * @see  None
 */
hi_u32 hi_lpc_set_type(hi_lpc_type type);

/**
 * @ingroup  iot_lp
 * @brief  Get current lowpower type.
 *
 * @par Description:
 *           Get current lowpower type.CNcomment:获取当前低功耗模式。CNend
 *
 * @param  None
 *
 * @retval #hi_lpc_type current lowpower type.
 * @par Dependency:
 *            @li hi_lowpower.h: Describes power saving management APIs.
 * @see  None
 */
hi_lpc_type hi_lpc_get_type(hi_void);

/**
 * @ingroup  iot_lp
 * @brief  Register check callback fucntion.
 *
 * @par Description:
 *           Register check callback function.CNComment:注册检查是否允许睡眠接口CNend
 *
 * @param  check_allowed [IN] type #hi_u32_void_callback
 *         If the return value is 0 means to disable sleep,others means enable.
 *         CNcomment:返回值为0禁止睡眠，其他值为允许.CNend
 *
 * @retval #hi_pvoid Hanlder.CNcomment:句柄CNend
 * @par Dependency:
 *            @li hi_lowpower.h: Describes power saving management APIs.
 * @see  hi_lowpower_unregister_vote
 */
hi_pvoid hi_lpc_register_check_handler(hi_u32_void_callback check_allowed);

/**
 * @ingroup  iot_lp
 * @brief  Cancel registation of check callback fucntion.
 *
 * @par Description:
 *            Cancel registation of check callback fucntion.CNcomment:取消检查接口注册CNend
 *
 * @param  handle [IN] type #hi_pvoid Low power handler.CNcomment:低功耗句柄CNend
 *
 * @retval #0   Success.
 * @retval #Other    Failure. For details, see hi_errno.h.
 * @par Dependency:
 *            @li hi_lowpower.h: Describes power saving management APIs.
 * @see  hi_lowpower_register_vote
 */
hi_u32 hi_lpc_unregister_check_handler(hi_pvoid handle);

/**
 * @ingroup  iot_lp
 * @brief  Add low power sleep veto.
 *
 * @par Description:
 *           Add low power sleep veto. CNcomment:禁止进入睡眠模式CNend
 *
 * @param  id  [IN] type #hi_lpc_id module id.
 CNcomment:模块idCNend
 *
 * @retval #HI_ERR_SUCCESS   Success.
 * @retval #Other    Failure. For details, see hi_errno.h.
 * @par Dependency:
 *            @li hi_lowpower.h: Describes power saving management APIs.
 * @see  None
 */
hi_u32 hi_lpc_add_veto(hi_lpc_id id);

/**
 * @ingroup  iot_lp
 * @brief  Remove low power sleep veto.
 *
 * @par Description:
 *           Set low power sleep mode. CNcomment:解除对应id的禁止进入睡眠模式状态CNend
 *
 * @param  id  [IN] type #hi_lpc_id module id.
 CNcomment:模块idCNend
 *
 * @retval #HI_ERR_SUCCESS   Success.
 * @retval #Other    Failure. For details, see hi_errno.h.
 * @par Dependency:
 *            @li hi_lowpower.h: Describes power saving management APIs.
 * @see  None
 */
hi_u32 hi_lpc_remove_veto(hi_lpc_id id);

/**
 * @ingroup  iot_lp
 * @brief  Statistics related to power saving.
 *
 * @par Description:
 *           Statistics related to power saving.CNcomment:低功耗相关维测统计CNend
 *
 * @param  None
 *
 * @retval hi_lp_stat Pointer to the status sturcture. CNcomment:统计量指针CNend
 * @par Dependency:
 *            @li hi_lowpower.h: Describes power saving management APIs.
 * @see  None
 */
hi_lpc_info* hi_lpc_get_info(hi_void);

/**
 * @ingroup  iot_lp
 * @brief  enable ultra deep sleep wakeup source.
 *
 * @par Description:
 *            enable ultra deep sleep wakeup source to low power module.CNcomment:使能低功耗超深睡唤醒源CNend
 *
 * @param  src  [IN] type #hi_udsleep_src Type of ultra deep sleep wakeup source enumeration.
 CNcomment:超深睡唤醒源CNend
 *
 * @retval #0   Success.
 * @retval #Other    Failure. For details, see hi_errno.h.
 *
 * @par Dependency:
 *            @li hi_lowpower.h: Describes power saving management APIs.
 * @see  None
 */
hi_u32 hi_lpc_enable_udsleep(hi_udsleep_src src);

/**
 * @ingroup  iot_lp
 * @brief  get ultra deep sleep wakeup source.
 *
 * @par Description:
 *            get the  wakeup source of ultra deep sleep.CNcomment:获取低功耗超深睡唤醒的触发源CNend
 *
 * @param  src  [OUT] type #hi_u16 * Type of ultra deep sleep wakeup source enumeration.
 CNcomment:超深睡唤醒源CNend
 *
 * @retval #0   Success.
 * @retval #Other    Failure. For details, see hi_errno.h.
 *
 * @par Dependency:
 *            @li hi_lowpower.h: Describes power saving management APIs.
 * @see  None
 */
hi_u32 hi_lpc_get_udsleep_wakeup_src(hi_u16 *src);

/**
 * @ingroup  iot_lp
 * @brief  Register hardware callback func of light_sleep or deep_sleep.
 *
 * @par Description:
 *         Register hardware callback func of light_sleep or deep_sleep.CNcomment:设置睡眠阶段硬件相关回调函数CNend
 *
 * @attention The save function is called after voting success and befor sleep, and the restore function is called
 * when waking up.
 CNcomment:prepare函数在芯片实际休眠前执行，resume函数在睡醒时执行。CNend
 * @param  prepare     [IN] type #hi_u32_void_callback Callback func of sleep.CNcomment:睡眠准备阶段回调函数CNend
 * @param  resume  [IN] type #hi_u32_void_callback Callback func of wake up.CNcomment:唤醒阶段回调函数CNend
 *
 * @retval #0   Success.
 * @retval #Other    Failure. For details, see hi_errno.h.
 *
 * @par Dependency:
 *            @li hi_lowpower.h: Describes power saving management APIs.
 * @see  None
 */
hi_u32 hi_lpc_register_hw_handler(hi_u32_void_callback prepare, hi_u32_void_callback resume);

/**
 * @ingroup  iot_lp
 * @brief  Register software callback func of light_sleep or deep_sleep.
 *
 * @par Description:
 *         Register software callback func of light_sleep or deep_sleep.CNcomment:设置睡眠阶段软件相关回调函数CNend
 *
 * @attention The save function is called before voting for sleep, and the restore function is called when waking up or
 * vote fail.
 CNcomment:prepare函数在系统判断是否可休眠前执行，resume函数在睡醒时或投票失败后执行。CNend
 * @param  prepare     [IN] type #hi_u32_void_callback Callback func of sleep.CNcomment:睡眠准备阶段回调函数CNend
 * @param  resume  [IN] type #hi_u32_void_callback Callback func of wake up.CNcomment:唤醒阶段回调函数CNend
 *
 * @retval #0   Success.
 * @retval #Other    Failure. For details, see hi_errno.h.
 *
 * @par Dependency:
 *            @li hi_lowpower.h: Describes power saving management APIs.
 * @see  None
 */
hi_u32 hi_lpc_register_sw_handler(hi_u32_void_callback prepare, hi_u32_void_callback resume);

/**
 * @ingroup  iot_lp
 * @brief  Register callback func of peripheral init entry.
 *
 * @par Description:
 *            Register callback func of peripheral init entry.CNcomment:设置深睡唤醒时入口函数，一般用作外设初始化CNend
 *
 * @param  handler  [IN] type #hi_void_callback_f Callback func of wake up.CNcomment:唤醒回调函数CNend
 *
 * @retval #0   Success.
 * @retval #Other    Failure. For details, see hi_errno.h.
 *
 * @par Dependency:
 *            @li hi_lowpower.h: Describes power saving management APIs.
 * @see  None
 */
hi_u32 hi_lpc_register_wakeup_entry(hi_void_callback_f handler);

/**
 * @ingroup  iot_lp
 * @brief  Config deep sleep gpio wakeup IO.
 *
 * @par Description:
 *            Config deep sleep wakeup IO.CNcomment:深睡眠唤醒IO设置CNend
 *
 * @param  id  [IN] type #hi_gpio_idx Wake up source IO.CNcomment:唤醒IOCNend
 * @param  enable  [IN] type #hi_bool whether enable the source IO.CNcomment:唤醒IOCNend
 *
 * @retval #0   Success.
 * @retval #Other    Failure. For details, see hi_errno.h.
 *
 * @par Dependency:
 *            @li hi_lowpower.h: Describes power saving management APIs.
 * @see  None
 */
hi_u32 hi_lpc_config_dsleep_wakeup_io(hi_gpio_idx id, hi_bool enable);


#endif /* __HI_LOWPOWER_H__ */
