/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @defgroup los_trace Trace
 * @ingroup kernel
 */

#ifndef _LOS_TRACE_H
#define _LOS_TRACE_H

#include "los_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/**
 * @ingroup los_trace
 * Task error code: Insufficient memory for trace struct.
 *
 * Value: 0x02001400
 *
 * Solution: Decrease the maximum number of tasks.
 */
#define  LOS_ERRNO_TRACE_NO_MEMORY              LOS_ERRNO_OS_ERROR(LOS_MOD_TRACE, 0x00)

/**
 * @ingroup los_trace
 * Task error code: User type is invalid when register new trace.
 *
 * Value: 0x02001401
 *
 * Solution: Use valid type to regeister the new trace.
 */
#define  LOS_ERRNO_TRACE_TYPE_INVALID           LOS_ERRNO_OS_ERROR(LOS_MOD_TRACE, 0x01)


/**
 * @ingroup los_trace
 * Task error code: The callback function is null when register new trace.
 *
 * Value: 0x02001402
 *
 * Solution: Use valid callback function to regeister the new trace.
 */
#define  LOS_ERRNO_TRACE_FUNCTION_NULL          LOS_ERRNO_OS_ERROR(LOS_MOD_TRACE, 0x02)

/**
 * @ingroup los_trace
 * Task error code: The filled size is 0 when register new trace.
 *
 * Value: 0x02001403
 *
 * Solution: Use valid filled size to regeister the new trace.
 */
#define  LOS_ERRNO_TRACE_MAX_SIZE_INVALID       LOS_ERRNO_OS_ERROR(LOS_MOD_TRACE, 0x03)

/**
 * @ingroup los_trace
 * It's the total size of trace buffer. It's in the unit of char
 */
#define LOS_TRACE_BUFFER_SIZE 1024

/**
 * @ingroup los_trace
 * It's the legth of tag, filled by los_trace system
 */
#define LOS_TRACE_TAG_LENGTH  sizeof(UINT32)

/**
 * @ingroup los_trace
 * Stands for the trace type can be registered.
 */
typedef enum enTraceType {
    LOS_TRACE_SWITCH = 0,         /**< trace for task switch, 0 is reserved for taskswitch   */
    LOS_TRACE_INTERRUPT = 1,      /**< trace for Interrrupt, 1 is reserved for interrupt      */
    LOS_TRACE_TYPE_NUM =  10,     /**< num for the register type, user can use 2~ LOS_TRACE_TYPE_NUM-1 */
} TRACE_TYPE_E;


/**
 * @ingroup los_trace
 * struct to store the task switch infomation
 */
typedef struct tagTraceTaskSwitch {
    UINT8  ucSrcTaskId;           /**< source taskid    */
    UINT8  ucDestTaskId;          /**< destination taskid    */
    UINT32 uwSwitchTick;          /**< Time at which the task switch happens    */
} TRACE_TASKSWITCH_S;

/**
 * @ingroup los_trace
 * struct to store the interrupt infomation
 */
typedef struct tagTraceInterrupt {
    UINT8  ucIRQEntryExit;        /**< 1 stands for that the trace is happend before interrupt function */
                                  /**< 0 stands for that the trace is after before interrupt function */
    UINT16 usIRQNo;               /**< IRQ number which trigger the interrupt     */
    UINT32 uwTick;                /**< Time at which the the trace is called    */
} TRACE_INTERRUPT_S;

/**
 * @ingroup los_trace
 * union struct to store the interrupt and task switch infomation
 */
typedef struct tagTrace {
    union {
        TRACE_TASKSWITCH_S  stTraceTask;       /**< It used for trace the task    */
        TRACE_INTERRUPT_S   stTraceInterrupt;  /**< It used for trace the interrrupt    */
    };
} TRACE_S;

/**
 * @ingroup los_trace
 * Main struct to store the interrupt and task swithc infomation
 */
typedef struct tagTraceBuffer {
    UINT16            usTracePos;
    UINT16            usTraceWrapPos;
    UINT8             ucBuffer[LOS_TRACE_BUFFER_SIZE];
} TRACE_BUFFER_S;


/**
 * @ingroup los_trace
 * Struct to store the trace infomaion for each trace type
 */
typedef struct tagTraceInfo {
    TRACE_TYPE_E  eType;                             /**< trace type, selected from TRACE_TYPE_E */
    UINT16 (*pfnHook)(UINT8 *outBuffer, VOID *pInfo); /**< callback function for the specific trace type.
                                                       * This function is used to store the infomation
                                                       * which want to be traced */
} TRACE_INFO_S;

/**
 * @ingroup los_trace
 * @brief  Intialize the trace when the system startup.
 *
 * @par Description:
 * This API is used to intilize the trace for system level.
 * @attention
 * <ul>
 * <li>This API can be called only after the memory is initialized. Otherwise, the CPU usage fails to be obtained.</li>
 * </ul>
 *
 * @param None.
 *
 * @retval #LOS_ERRNO_TRACE_NO_MEMORY         0x02001400: The memory is not enough for initilize.
 * @retval #LOS_OK                            0x00000000: The intialization is successful.
 * @par Dependency:
 * <ul><li>los_trace.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_TraceInit
 */
extern UINT32 LOS_TraceInit(VOID);


/**
 * @ingroup los_trace
 * @brief main trace function is called by user to logger the information.
 *
 * @par Description:
 * This API is used to trace the infomation.
 * @attention
 * <ul>
 * <li>This API can be called only after trace type is intialized. Otherwise, the trace will be failed.</li>
 * </ul>
 *
 * @param  traceType     [IN] TRACE_TYPE_E. Type of trace information.
 * @param  traceInfo     [IN] VOID*. It's a input buffer to store trace infomation
 *
 * @retval NONE.
 *
 * @par Dependency:
 * <ul><li>los_trace.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_Trace
 */
extern VOID LOS_Trace(TRACE_TYPE_E traceType, VOID *traceInfo);



/**
 * @ingroup los_trace
 * @brief register the hook for specific trace type.
 *
 * @par Description:
 * This API is used to register the hook for specific trace type.
 * @attention
 * <ul>
 * <li>This API can be called only after trace type is called. therwise, the trace will be failed.</li>
 * </ul>
 *
 * @param  traceType     [IN] TRACE_TYPE_E. Type of trace information.
 * @param  hook          [IN] UINT16 (*)(UINT8*, VOID*). It's an callback function to store the useful trace
 *                            information
 * @param  size          [IN] UINT16. The maximum size the trace will use for the specific trace type.
 *
 * @retval #LOS_ERRNO_TRACE_NO_MEMORY          0x02001400: The memory is not enough for initilize.
 * @retval #LOS_ERRNO_TRACE_TYPE_INVALID       0x02001401: The trace type is invalid. Valid type is from
 *                                                         LOS_TRACE_TYPE_NUM-1
 * @retval #LOS_ERRNO_TRACE_FUNCTION_NULL      0x02001402: The input callback function is NULL
 * @retval #LOS_ERRNO_TRACE_MAX_SIZE_INVALID   0x02001403: The information maxmum size is 0 to store.
 * @retval #LOS_OK                             0x00000000: The registeration is successful.
 *
 * @par Dependency:
 * <ul><li>los_trace.h: the header file that contains the API declaration.</li></ul>
 * @see LOS_TraceUserReg
 */
extern UINT32 LOS_TraceUserReg(TRACE_TYPE_E traceType, UINT16 (*hook)(UINT8 *, VOID *), UINT16 size);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_TRACE_H */
