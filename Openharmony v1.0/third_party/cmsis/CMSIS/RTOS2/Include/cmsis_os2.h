/*
 * Copyright (c) 2013-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ----------------------------------------------------------------------
 *
 * $Date:        18. June 2018
 * $Revision:    V2.1.3
 *
 * Project:      CMSIS-RTOS2 API
 * Title:        cmsis_os2.h header file
 *
 * Version 2.1.3
 *    Additional functions allowed to be called from Interrupt Service Routines:
 *    - osThreadGetId
 * Version 2.1.2
 *    Additional functions allowed to be called from Interrupt Service Routines:
 *    - osKernelGetInfo, osKernelGetState
 * Version 2.1.1
 *    Additional functions allowed to be called from Interrupt Service Routines:
 *    - osKernelGetTickCount, osKernelGetTickFreq
 *    Changed Kernel Tick type to uint32_t:
 *    - updated: osKernelGetTickCount, osDelayUntil
 * Version 2.1.0
 *    Support for critical and uncritical sections (nesting safe):
 *    - updated: osKernelLock, osKernelUnlock
 *    - added: osKernelRestoreLock
 *    Updated Thread and Event Flags:
 *    - changed flags parameter and return type from int32_t to uint32_t
 * Version 2.0.0
 *    Initial Release
 *---------------------------------------------------------------------------*/

/**
 * @addtogroup CMSIS
 * @{
 *
 * @brief Provides standard, universal real-time operating system (RTOS) APIs.
 *
 * CMSIS Module may contain portions from ARM Cortex Microcontroller Software Interface Standard (CMSIS) licensed under Apache License v2.0.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef CMSIS_OS2_H_
#define CMSIS_OS2_H_

#ifndef __NO_RETURN
#if   defined(__CC_ARM)
#define __NO_RETURN __declspec(noreturn)
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#define __NO_RETURN __attribute__((__noreturn__))
#elif defined(__GNUC__)
#define __NO_RETURN __attribute__((__noreturn__))
#elif defined(__ICCARM__)
#define __NO_RETURN __noreturn
#else
#define __NO_RETURN
#endif
#endif

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


//  ==== Enumerations, structures, defines ====

/**
* @brief Describes the system version.
*
* @since 1.0
* @version 1.0
*/
typedef struct {
  /** API version */
  uint32_t                       api;
  /** Kernel version */
  uint32_t                    kernel;
} osVersion_t;

/**
* @brief Enumerates kernel states.
*
*/
typedef enum {
  /** The kernel is inactive. */
  osKernelInactive        =  0,
  /** The kernel is ready. */
  osKernelReady           =  1,
  /** The kernel is running. */
  osKernelRunning         =  2,
  /** The kernel is locked. */
  osKernelLocked          =  3,
  /** The kernel is suspended. */
  osKernelSuspended       =  4,
  /** The kernel is abnormal. */
  osKernelError           = -1,
  /** Reserved */
  osKernelReserved        = 0x7FFFFFFFU
} osKernelState_t;

/**
* @brief Enumerates thread states.
*
*/
typedef enum {
  /** The thread is inactive. */
  osThreadInactive        =  0,
  /** The thread is ready. */
  osThreadReady           =  1,
  /** The thread is running. */
  osThreadRunning         =  2,
  /** The thread is blocked. */
  osThreadBlocked         =  3,
  /** The thread is terminated. */
  osThreadTerminated      =  4,
  /** The thread is abnormal. */
  osThreadError           = -1,
  /** Reserved */
  osThreadReserved        = 0x7FFFFFFF
} osThreadState_t;

/**
* @brief Enumerates thread priorities.
*
*/
typedef enum {
  /** Undefined */
  osPriorityNone          =  0,
  /** Reserved for idle threads */
  osPriorityIdle          =  1,
  /** Low (unsupported) */
  osPriorityLow           =  8,
  /** Low + 1 */
  osPriorityLow1          =  8+1,
  /** Low + 2 */
  osPriorityLow2          =  8+2,
  /** Low + 3 */
  osPriorityLow3          =  8+3,
  /** Low + 4 */
  osPriorityLow4          =  8+4,
  /** Low + 5 */
  osPriorityLow5          =  8+5,
  /** Low + 6 */
  osPriorityLow6          =  8+6,
  /** Low + 7 */
  osPriorityLow7          =  8+7,
  /** Below normal */
  osPriorityBelowNormal   = 16,
  /** Below normal + 1 */
  osPriorityBelowNormal1  = 16+1,
  /** Below normal + 2 */
  osPriorityBelowNormal2  = 16+2,
  /** Below normal + 3 */
  osPriorityBelowNormal3  = 16+3,
  /** Below normal + 4 */
  osPriorityBelowNormal4  = 16+4,
  /** Below normal + 5 */
  osPriorityBelowNormal5  = 16+5,
  /** Below normal + 6 */
  osPriorityBelowNormal6  = 16+6,
  /** Below normal + 7 */
  osPriorityBelowNormal7  = 16+7,
  /** Normal */
  osPriorityNormal        = 24,
  /** Normal + 1 */
  osPriorityNormal1       = 24+1,
  /** Normal + 2 */
  osPriorityNormal2       = 24+2,
  /** Normal + 3 */
  osPriorityNormal3       = 24+3,
  /** Normal + 4 */
  osPriorityNormal4       = 24+4,
  /** Normal + 5 */
  osPriorityNormal5       = 24+5,
  /** Normal + 6 */
  osPriorityNormal6       = 24+6,
  /** Normal + 7 */
  osPriorityNormal7       = 24+7,
  /** Above normal */
  osPriorityAboveNormal   = 32,
  /** Above normal + 1 */
  osPriorityAboveNormal1  = 32+1,
  /** Above normal + 2 */
  osPriorityAboveNormal2  = 32+2,
  /** Above normal + 3 */
  osPriorityAboveNormal3  = 32+3,
  /** Above normal + 4 */
  osPriorityAboveNormal4  = 32+4,
  /** Above normal + 5 */
  osPriorityAboveNormal5  = 32+5,
  /** Above normal + 6 */
  osPriorityAboveNormal6  = 32+6,
  /** Above normal + 7 (unsupported) */
  osPriorityAboveNormal7  = 32+7,
  /** High (unsupported) */
  osPriorityHigh          = 40,
  /** High + 1 (unsupported) */
  osPriorityHigh1         = 40+1,
  /** High + 2 (unsupported)  */
  osPriorityHigh2         = 40+2,
  /** High + 3 (unsupported)  */
  osPriorityHigh3         = 40+3,
  /** High + 4 (unsupported)  */
  osPriorityHigh4         = 40+4,
  /** High + 5 (unsupported)  */
  osPriorityHigh5         = 40+5,
  /** High + 6 (unsupported)  */
  osPriorityHigh6         = 40+6,
  /** High + 7 (unsupported)  */
  osPriorityHigh7         = 40+7,
  /** Real-time (unsupported)  */
  osPriorityRealtime      = 48,
  /** Real-time + 1 (unsupported) */
  osPriorityRealtime1     = 48+1,
  /** Real-time + 2 (unsupported) */
  osPriorityRealtime2     = 48+2,
  /** Real-time + 3 (unsupported) */
  osPriorityRealtime3     = 48+3,
  /** Real-time + 4 (unsupported) */
  osPriorityRealtime4     = 48+4,
  /** Real-time + 5 (unsupported) */
  osPriorityRealtime5     = 48+5,
  /** Real-time + 6 (unsupported) */
  osPriorityRealtime6     = 48+6,
  /** Real-time + 7 (unsupported) */
  osPriorityRealtime7     = 48+7,
  /** Reserved for ISR deferred threads (unsupported) */
  osPriorityISR           = 56,
  /** Invalid */
  osPriorityError         = -1,
  /** Reserved. It enables the compiler to identify enumeration variables as 32-bit numbers and prevents the enumeration variables from being optimized. */
  osPriorityReserved      = 0x7FFFFFFF
} osPriority_t;

/**
* @brief Callback for thread scheduling
*
*/
typedef void (*osThreadFunc_t) (void *argument);

/**
* @brief Callback for timer triggering
*
*/
typedef void (*osTimerFunc_t) (void *argument);

/**
* @brief Enumerates timer types.
*
*/
typedef enum {
  /** One-shot timer */
  osTimerOnce               = 0,
  /** Repeating timer */
  osTimerPeriodic           = 1
} osTimerType_t;

/**
* @brief Indicates that the RTOS waits forever unless an event flag is received.
*
*/
#define osWaitForever         0xFFFFFFFFU

/**
* @brief Indicates that the RTOS does not wait.
*
*/
#define osNoWait              0x0U

/**
* @brief Indicates that the RTOS waits until any event flag is triggered.
*
*/
#define osFlagsWaitAny        0x00000000U

/**
* @brief Indicates that the system waits until all event flags are triggered.
*
*/
#define osFlagsWaitAll        0x00000001U

/**
* @brief Indicates that defined flags are not cleared.
*
*/
#define osFlagsNoClear        0x00000002U

/**
* @brief Indicates a flag error.
*
*/
#define osFlagsError          0x80000000U

/**
* @brief Indicates an unknown error.
*
*/
#define osFlagsErrorUnknown   0xFFFFFFFFU

/**
* @brief Indicates a timeout.
*
*/
#define osFlagsErrorTimeout   0xFFFFFFFEU

/**
* @brief Indicates a resource error.
*
*/
#define osFlagsErrorResource  0xFFFFFFFDU

/**
* @brief Indicates an incorrect parameter.
*
*/
#define osFlagsErrorParameter 0xFFFFFFFCU
#define osFlagsErrorISR       0xFFFFFFFAU

// Thread attributes (attr_bits in \ref osThreadAttr_t).
#define osThreadDetached      0x00000000U
#define osThreadJoinable      0x00000001U

// Mutex attributes (attr_bits in \ref osMutexAttr_t).
#define osMutexRecursive      0x00000001U
#define osMutexPrioInherit    0x00000002U
#define osMutexRobust         0x00000008U

/**
* @brief Enumerates return values of CMSIS-RTOS.
*
*/
typedef enum {
  /** Operation completed successfully */
  osOK                      =  0,
  /** Unspecified error */
  osError                   = -1,
  /** Timeout */
  osErrorTimeout            = -2,
  /** Resource error */
  osErrorResource           = -3,
  /** Incorrect parameter */
  osErrorParameter          = -4,
  /** Insufficient memory */
  osErrorNoMemory           = -5,
  /** Service interruption */
  osErrorISR                = -6,
  /** Reserved. It is used to prevent the compiler from optimizing enumerations. */
  osStatusReserved          = 0x7FFFFFFF
} osStatus_t;

/**
* @brief Identifies a thread.
*
*/
typedef void *osThreadId_t;

/**
* @brief Identifies a timer.
*
*/
typedef void *osTimerId_t;

/**
* @brief Identifies an event flag.
*
*/
typedef void *osEventFlagsId_t;

/**
* @brief Identifies a mutex.
*
*/
typedef void *osMutexId_t;

/**
* @brief Identifies a semaphore object.
*
*/
typedef void *osSemaphoreId_t;


typedef void *osMemoryPoolId_t;

/**
* @brief Identifies a message queue.
*
*/
typedef void *osMessageQueueId_t;


#ifndef TZ_MODULEID_T
#define TZ_MODULEID_T

/**
* @brief Identifies a TrustZone module call process.
*
*/
typedef uint32_t TZ_ModuleId_t;
#endif

/**
* @brief Describes thread attributes.
*
* @since 1.0
* @version 1.0
*/
typedef struct {
  /** Thread name */
  const char                   *name;
  /** Thread attribute bits */
  uint32_t                 attr_bits;
  /** Memory for the thread control block */
  void                      *cb_mem;
  /** Size of the memory for the thread control block */
  uint32_t                   cb_size;
  /** Memory for the thread stack */
  void                   *stack_mem;
  /** Size of the thread stack */
  uint32_t                stack_size;
  /** Thread priority */
  osPriority_t              priority;
  /** TrustZone module of the thread */
  TZ_ModuleId_t            tz_module;
  /** Reserved */
  uint32_t                  reserved;
} osThreadAttr_t;

/**
* @brief Describes timer attributes.
*
* @since 1.0
* @version 1.0
*/
typedef struct {
  /** Timer name */
  const char                   *name;
  /** Reserved attribute bits */
  uint32_t                 attr_bits;
  /** Memory for the timer control block */
  void                      *cb_mem;
  /** Size of the memory for the timer control block */
  uint32_t                   cb_size;
} osTimerAttr_t;

/**
* @brief Describes event attributes.
*
* @since 1.0
* @version 1.0
*/
typedef struct {
  /** Event name */
  const char                   *name;
  /** Reserved attribute bits */
  uint32_t                 attr_bits;
  /** Memory for the event control block */
  void                      *cb_mem;
  /** Size of the memory for the event control block */
  uint32_t                   cb_size;
} osEventFlagsAttr_t;

/**
* @brief Describes mutex attributes.
*
* @since 1.0
* @version 1.0
*/
typedef struct {
  /** Mutex name */
  const char                   *name;
  /** Reserved attribute bits */
  uint32_t                 attr_bits;
  /** Memory for the mutex control block */
  void                      *cb_mem;
  /** Size of the memory for the mutex control block */
  uint32_t                   cb_size;
} osMutexAttr_t;

/**
* @brief Describes semaphore attributes.
*
* @since 1.0
* @version 1.0
*/
typedef struct {
  /** Semaphore name */
  const char                   *name;
  /** Reserved attribute bits */
  uint32_t                 attr_bits;
  /** Memory for the semaphore control block */
  void                      *cb_mem;
  /** Size of the memory for the semaphore control block */
  uint32_t                   cb_size;
} osSemaphoreAttr_t;
 

typedef struct {
  const char                   *name;
  uint32_t                 attr_bits;
  void                      *cb_mem; 
  uint32_t                   cb_size;
  void                      *mp_mem; 
  uint32_t                   mp_size;
} osMemoryPoolAttr_t;
 
/**
* @brief Describes message queue attributes.
*
* @since 1.0
* @version 1.0
*/
typedef struct {
  /** Message queue name */
  const char                   *name;
  /** Reserved attribute bits */
  uint32_t                 attr_bits;
  /** Memory for the message queue control block */
  void                      *cb_mem;
  /** Size of the memory for the message queue control block */
  uint32_t                   cb_size;
  /** Memory for storing data in the message queue */
  void                      *mq_mem;
  /** Size of the memory for storing data in the message queue */
  uint32_t                   mq_size;
} osMessageQueueAttr_t;
 
 
//  ==== Kernel Management Functions ====
 
/**
* @brief Initializes the RTOS kernel.
*
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osKernelInitialize (void);
 
/**
* @brief Obtains the system version and name.
*
* @param version Indicates the pointer to the buffer for storing the version.
* @param id_buf Indicates the pointer to the buffer for storing the kernel ID.
* @param id_size Indicates the size of the buffer for storing the kernel ID.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osKernelGetInfo (osVersion_t *version, char *id_buf, uint32_t id_size);
 
/**
* @brief Obtains the kernel state.
*
* @return Returns the kernel state.
* @since 1.0
* @version 1.0
*/
osKernelState_t osKernelGetState (void);
 
/**
* @brief Starts the kernel.
*
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osKernelStart (void);
 
/**
* @brief Locks the kernel.
*
* @return Returns 1 if the kernel is locked successfully; returns 0 if the lock starts; returns a negative value in the case of an error.
* @since 1.0
* @version 1.0
*/
int32_t osKernelLock (void);
 
/**
* @brief Unlocks the kernel.
*
* @return Returns 1 if the kernel is unlocked successfully; returns 0 if the kernel is not locked; returns a negative value in the case of an error.
* @since 1.0
* @version 1.0
*/
int32_t osKernelUnlock (void);
 
/**
* @brief Restores the previous lock state of the kernel.
*
* @param lock Indicates the lock state to restore to. The value 1 indicates the locked state, and 0 indicates the unlocked state.
* @return Returns 1 if the kernel is locked; returns 0 if the kernel is not locked; returns a negative value in the case of an error.
* @since 1.0
* @version 1.0
*/
int32_t osKernelRestoreLock (int32_t lock);
 
uint32_t osKernelSuspend (void);
 
void osKernelResume (uint32_t sleep_ticks);

/// Get the RTOS kernel tick count.
/// \return RTOS kernel current tick count.
uint32_t osKernelGetTickCount (void);
 


/**
* @brief Obtains the number of kernel ticks per second.
*
* @return Returns the number of kernel ticks.
* @since 1.0
* @version 1.0
*/
uint32_t osKernelGetTickFreq (void);
 
/**
* @brief Obtains the kernel system timer.
*
* @return Returns the kernel system timer.
* @since 1.0
* @version 1.0
*/
uint32_t osKernelGetSysTimerCount (void);
 
/**
* @brief Obtains the frequency of the system timer.
*
* @return Returns the system timer frequency.
* @since 1.0
* @version 1.0
*/
uint32_t osKernelGetSysTimerFreq (void);
 
 
//  ==== Thread Management Functions ====
 
/**
* @brief Creates an active thread.
*
* @param func Indicates the entry of the thread callback function.
* @param argument Indicates the pointer to the argument passed to the thread.
* @param attr Indicates the thread attributes.
* @return Returns the thread ID; returns NULL in the case of an error.
* @since 1.0
* @version 1.0
*/
osThreadId_t osThreadNew (osThreadFunc_t func, void *argument, const osThreadAttr_t *attr);
 
/**
* @brief Obtains the name of a thread.
*
* @param thread_id Indicates the thread ID, which is obtained using osThreadNew or osThreadGetId.
* @return Returns the thread name; returns NULL in the case of an error.
* @since 1.0
* @version 1.0
*/
const char *osThreadGetName (osThreadId_t thread_id);
 
/**
* @brief Obtains the ID of the currently running thread.
*
* @return Returns the thread ID; returns NULL in the case of an error.
* @since 1.0
* @version 1.0
*/
osThreadId_t osThreadGetId (void);
 

/**
* @brief Obtains the state of a thread.
*
* @param thread_id Indicates the thread ID, which is obtained using osThreadNew or osThreadGetId.
* @return Returns the thread state.
* @since 1.0
* @version 1.0
*/
osThreadState_t osThreadGetState (osThreadId_t thread_id);
 
/**
* @brief Obtains the stack size of a thread.
*
* @param thread_id Indicates the thread ID, which is obtained using osThreadNew or osThreadGetId.
* @return Returns the stack size, in bytes; returns 0 in the case of an error.
* @since 1.0
* @version 1.0
*/
uint32_t osThreadGetStackSize (osThreadId_t thread_id);
 
/**
* @brief Obtains the size of the available stack space for a thread based on the stack watermark.
*
* @param thread_id Indicates the thread ID, which is obtained using osThreadNew or osThreadGetId.
* @return Returns the available stack size, in bytes; returns 0 in the case of an error.
* @since 1.0
* @version 1.0
*/
uint32_t osThreadGetStackSpace (osThreadId_t thread_id);
 
/**
* @brief Changes the priority of a thread.
*
* @param thread_id Indicates the thread ID, which is obtained using osThreadNew or osThreadGetId.
* @param priority Indicates the new priority.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osThreadSetPriority (osThreadId_t thread_id, osPriority_t priority);

/**
* @brief Gets the prority of an active thread.
*
* @param thread_id Indicates the thread ID, which is obtained using osThreadNew or osThreadGetId.
* @return Returns the prority of the thread.
* @since 1.0
* @version 1.0
*/
osPriority_t osThreadGetPriority (osThreadId_t thread_id);
 
/**
* @brief Sets the currently running thread to the ready state.
*
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osThreadYield (void);
 
/**
* @brief Suspends a thread.
*
* @param thread_id Indicates the thread ID, which is obtained using osThreadNew or osThreadGetId.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osThreadSuspend (osThreadId_t thread_id);
 
/**
* @brief Resumes a thread from the suspended state.
*
* @param thread_id Indicates the thread ID, which is obtained using osThreadNew or osThreadGetId.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osThreadResume (osThreadId_t thread_id);
 
osStatus_t osThreadDetach (osThreadId_t thread_id);
 
osStatus_t osThreadJoin (osThreadId_t thread_id);
 
void osThreadExit (void);
 
/**
* @brief Terminates a thread.
*
* @param thread_id Indicates the thread ID, which is obtained using osThreadNew or osThreadGetId.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osThreadTerminate (osThreadId_t thread_id);
 
/**
* @brief Obtains the number of active threads.
*
* @return Returns the number; returns 0 in the case of an error.
* @since 1.0
* @version 1.0
*/
uint32_t osThreadGetCount (void);
 
uint32_t osThreadEnumerate (osThreadId_t *thread_array, uint32_t array_items);
 
 
//  ==== Thread Flags Functions ====
 
uint32_t osThreadFlagsSet (osThreadId_t thread_id, uint32_t flags);
 
uint32_t osThreadFlagsClear (uint32_t flags);
 
uint32_t osThreadFlagsGet (void);
 
uint32_t osThreadFlagsWait (uint32_t flags, uint32_t options, uint32_t timeout);
 
 
//  ==== Generic Wait Functions ====
 
/**
* @brief Waits for a period of time.
*
* @param ticks Indicates the number of ticks to wait for.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osDelay (uint32_t ticks);
 
/**
* @brief Waits until a specified time arrives.
*
* @param ticks Indicates the number of ticks converted from the absolute time.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osDelayUntil (uint32_t ticks);
 
 
//  ==== Timer Management Functions ====
 
/**
* @brief Creates and initializes a timer.
*
* @param func Indicates the entry of the timer callback function.
* @param type Indicates the timer type.
* @param argument Indicates the pointer to the argument used in timer callback.
* @param attr Indicates the pointer to the timer attributes. This parameter is not used.
* @return Returns the timer ID; returns NULL in the case of an error.
* @since 1.0
* @version 1.0
*/
osTimerId_t osTimerNew (osTimerFunc_t func, osTimerType_t type, void *argument, const osTimerAttr_t *attr);
 
/**
* @brief Obtains the timer name.
*
* @param timer_id Indicates the timer ID, which is obtained using osTimerNew.
* @return Returns the timer name; returns NULL in the case of an error.
* @since 1.0
* @version 1.0
*/
const char *osTimerGetName (osTimerId_t timer_id);
 
/**
* @brief Starts or restarts a timer.
*
* @param timer_id Indicates the timer ID, which is obtained using osTimerNew.
* @param ticks Indicates the number of ticks since the timer starts running.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osTimerStart (osTimerId_t timer_id, uint32_t ticks);
 
/**
* @brief Stops a timer.
*
* @param timer_id Indicates the timer ID, which is obtained using osTimerNew.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osTimerStop (osTimerId_t timer_id);
 
/**
* @brief Checks whether a timer is running.
*
* @param timer_id Indicates the timer ID, which is obtained using osTimerNew.
* @return Returns 1 if the timer is running; returns 0 otherwise.
* @since 1.0
* @version 1.0
*/
uint32_t osTimerIsRunning (osTimerId_t timer_id);
 
/**
* @brief Deletes a timer.
*
* @param timer_id Indicates the timer ID, which is obtained using osTimerNew.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osTimerDelete (osTimerId_t timer_id);
 
 
//  ==== Event Flags Management Functions ====
 
/**
* @brief Creates and initializes an event flags object.
*
* @param attr Indicates the pointer to the event flags attributes. This parameter is not used.
* @return Returns the event flags ID; returns NULL in the case of an error.
* @since 1.0
* @version 1.0
*/
osEventFlagsId_t osEventFlagsNew (const osEventFlagsAttr_t *attr);
 
/**
* @brief Obtains the name of an event flags object.
*
* @param ef_id Indicates the event flags ID, which is obtained using osEventFlagsNew.
* @return Returns the event flags name; returns NULL in the case of an error.
* @since 1.0
* @version 1.0
*/
const char *osEventFlagsGetName (osEventFlagsId_t ef_id);
 
/**
* @brief Sets event flags.
*
* @param ef_id Indicates the event flags ID, which is obtained using osEventFlagsNew.
* @param flags Indicates the event flags to set.
* @return Returns the event flags; returns osFlagsErrorParameter in the case of an error.
* @since 1.0
* @version 1.0
*/
uint32_t osEventFlagsSet (osEventFlagsId_t ef_id, uint32_t flags);
 
/**
* @brief Clears event flags.
*
* @param ef_id Indicates the event flags ID, which is obtained using osEventFlagsNew.
* @param flags Indicates the event flags to clear.
* @return Returns the event flags; returns osFlagsErrorParameter in the case of an error.
* @since 1.0
* @version 1.0
*/
uint32_t osEventFlagsClear (osEventFlagsId_t ef_id, uint32_t flags);
 
/**
* @brief Obtains event flags.
*
* @param ef_id Indicates the event flags ID, which is obtained using osEventFlagsNew.
* @return Returns the event flags triggered.
* @since 1.0
* @version 1.0
*/
uint32_t osEventFlagsGet (osEventFlagsId_t ef_id);
 
/**
* @brief Waits for event flags to trigger.
*
* @param ef_id Indicates the event flags ID, which is obtained using osEventFlagsNew.
* @param flags Indicates the event flags to trigger.
* @param options Indicates the configuration of the event flags to trigger.
* @param timeout Indicates the timeout duration.
* @return Returns the triggered event flags; returns an error value in the case of an error.
* @since 1.0
* @version 1.0
*/
uint32_t osEventFlagsWait (osEventFlagsId_t ef_id, uint32_t flags, uint32_t options, uint32_t timeout);
 
/**
* @brief Deletes an event flags object.
*
* @param ef_id Indicates the event flags ID, which is obtained using osEventFlagsNew.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osEventFlagsDelete (osEventFlagsId_t ef_id);
 
 
//  ==== Mutex Management Functions ====
 
/**
* @brief Creates and initializes a mutex.
*
* @param attr Indicates the pointer to the mutex attributes. This parameter is not used.
* @return Returns the mutex ID; returns NULL in the case of an error.
* @since 1.0
* @version 1.0
*/
osMutexId_t osMutexNew (const osMutexAttr_t *attr);
 
const char *osMutexGetName (osMutexId_t mutex_id);
 
/**
* @brief Obtains a mutex.
*
* @param mutex_id Indicates the mutex ID, which is obtained using osMutexNew.
* @param timeout Indicates the timeout duration.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osMutexAcquire (osMutexId_t mutex_id, uint32_t timeout);
 
/**
* @brief Releases a mutex.
*
* @param mutex_id Indicates the mutex ID, which is obtained using osMutexNew.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osMutexRelease (osMutexId_t mutex_id);
 
/**
* @brief Obtains the thread ID of the currently acquired mutex.
*
* @param mutex_id Indicates the mutex ID, which is obtained using osMutexNew.
* @return Returns the thread ID.
* @since 1.0
* @version 1.0
*/
osThreadId_t osMutexGetOwner (osMutexId_t mutex_id);
 
/**
* @brief Deletes a mutex.
*
* @param mutex_id Indicates the mutex ID, which is obtained using osMutexNew.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osMutexDelete (osMutexId_t mutex_id);
 
 
//  ==== Semaphore Management Functions ====
 
/**
* @brief Creates and initializes a semaphore object.
*
* @param max_count Indicates the maximum number of available tokens that can be applied for.
* @param initial_count Indicates the initial number of available tokens.
* @param attr Indicates the pointer to the semaphore attributes. This parameter is not used.
* @return Returns the semaphore ID; returns NULL in the case of an error.
* @since 1.0
* @version 1.0
*/
osSemaphoreId_t osSemaphoreNew (uint32_t max_count, uint32_t initial_count, const osSemaphoreAttr_t *attr);
 
const char *osSemaphoreGetName (osSemaphoreId_t semaphore_id);
 
/**
* @brief Acquires a token of a semaphore object.
*
* @param semaphore_id Indicates the semaphore ID, which is obtained using osSemaphoreNew.
* @param timeout Indicates the timeout duration.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osSemaphoreAcquire (osSemaphoreId_t semaphore_id, uint32_t timeout);
 
/**
* @brief Releases a token of a semaphore object.
*
* @param semaphore_id Indicates the semaphore ID, which is obtained using osSemaphoreNew.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osSemaphoreRelease (osSemaphoreId_t semaphore_id);
 
/**
* @brief Obtains the number of available tokens of a semaphore object.
*
* @param semaphore_id Indicates the semaphore ID, which is obtained using osSemaphoreNew.
* @return Returns the number of available tokens.
* @since 1.0
* @version 1.0
*/
uint32_t osSemaphoreGetCount (osSemaphoreId_t semaphore_id);
 
/**
* @brief Deletes a semaphore object.
*
* @param semaphore_id Indicates the semaphore ID, which is obtained using osSemaphoreNew.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osSemaphoreDelete (osSemaphoreId_t semaphore_id);
 
 
//  ==== Memory Pool Management Functions ====
 
osMemoryPoolId_t osMemoryPoolNew (uint32_t block_count, uint32_t block_size, const osMemoryPoolAttr_t *attr);
 
const char *osMemoryPoolGetName (osMemoryPoolId_t mp_id);
 
void *osMemoryPoolAlloc (osMemoryPoolId_t mp_id, uint32_t timeout);
 
osStatus_t osMemoryPoolFree (osMemoryPoolId_t mp_id, void *block);
 
uint32_t osMemoryPoolGetCapacity (osMemoryPoolId_t mp_id);
 
uint32_t osMemoryPoolGetBlockSize (osMemoryPoolId_t mp_id);
 
uint32_t osMemoryPoolGetCount (osMemoryPoolId_t mp_id);
 
uint32_t osMemoryPoolGetSpace (osMemoryPoolId_t mp_id);
 
osStatus_t osMemoryPoolDelete (osMemoryPoolId_t mp_id);
 
 
//  ==== Message Queue Management Functions ====
 
/**
* @brief Creates and initializes a message queue.
*
* @param msg_count Indicates the number of messages in the message queue.
* @param msg_size Indicates the size of messages in the message queue.
* @param attr Indicates the pointer to the message queue attributes. This parameter is not used.
* @return Returns the message queue ID; returns NULL in the case of an error.
* @since 1.0
* @version 1.0
*/
osMessageQueueId_t osMessageQueueNew (uint32_t msg_count, uint32_t msg_size, const osMessageQueueAttr_t *attr);
 
const char *osMessageQueueGetName (osMessageQueueId_t mq_id);
 
/**
* @brief Places a message in a message queue.
*
* @param mq_id Indicates the message queue ID, which is obtained using osMessageQueueNew.
* @param msg_ptr Indicates the pointer to the buffer for storing the message to be placed in the message queue.
* @param msg_prio Indicates the priority of the message to be placed in the message queue.
* @param timeout Indicates the timeout duration.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osMessageQueuePut (osMessageQueueId_t mq_id, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout);
 
/**
* @brief Obtains a message in a message queue.
*
* @param mq_id Indicates the message queue ID, which is obtained using osMessageQueueNew.
* @param msg_ptr Indicates the pointer to the buffer for storing the message to be retrieved from the message queue.
* @param msg_prio Indicates the pointer to the buffer for storing the priority of the message to be retrieved from the message queue. This parameter can be set to NULL.
* @param timeout Indicates the timeout duration.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osMessageQueueGet (osMessageQueueId_t mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout);
 
/**
* @brief Obtains the maximum number of messages that can be placed in a message queue.
*
* @param mq_id Indicates the message queue ID, which is obtained using osMessageQueueNew.
* @return Returns the maximum number.
* @since 1.0
* @version 1.0
*/
uint32_t osMessageQueueGetCapacity (osMessageQueueId_t mq_id);
 
/**
* @brief Obtains the maximum size of messages that can be placed in a message queue.
*
* @param mq_id Indicates the message queue ID, which is obtained using osMessageQueueNew.
* @return Returns the maximum message size.
* @since 1.0
* @version 1.0
*/
uint32_t osMessageQueueGetMsgSize (osMessageQueueId_t mq_id);
 
/**
* @brief Obtains the number of queued messages in a message queue.
*
* @param mq_id Indicates the message queue ID, which is obtained using osMessageQueueNew.
* @return Returns the number of queued messages.
* @since 1.0
* @version 1.0
*/
uint32_t osMessageQueueGetCount (osMessageQueueId_t mq_id);
 
/**
* @brief Obtains the number of available slots for messages in a message queue.
*
* @param mq_id Indicates the message queue ID, which is obtained using osMessageQueueNew.
* @return Returns the number of available slots for messages.
* @since 1.0
* @version 1.0
*/
uint32_t osMessageQueueGetSpace (osMessageQueueId_t mq_id);
 
osStatus_t osMessageQueueReset (osMessageQueueId_t mq_id);
 
/**
* @brief Deletes a message queue.
*
* @param mq_id Indicates the message queue ID, which is obtained using osMessageQueueNew.
* @return Returns the CMSIS-RTOS running result.
* @since 1.0
* @version 1.0
*/
osStatus_t osMessageQueueDelete (osMessageQueueId_t mq_id);
 
 
#ifdef  __cplusplus
}
#endif
 
#endif  // CMSIS_OS2_H_
