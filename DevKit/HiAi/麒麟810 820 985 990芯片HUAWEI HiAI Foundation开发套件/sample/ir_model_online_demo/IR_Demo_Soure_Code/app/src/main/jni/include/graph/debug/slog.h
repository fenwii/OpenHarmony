/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: slog
 */

#ifndef _D_SYSLOG_H
#define _D_SYSLOG_H 1

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _DPATH_LOG
#undef _DPATH_LOG
#endif

#define _DPATH_LOG "/dev/slog"
constexpr int MSG_LENGTH = 1024;
#define PATH_DLOG_DIR "/var/log/slog"

constexpr int DLOG_ERROR = 0 ; // error conditions
constexpr int DLOG_WARN = 1 ; // warning conditions
constexpr int DLOG_INFO = 2 ; // informational
constexpr int DLOG_DEBUG = 3 ; // debug-level messages

constexpr uint64_t DLOG_PRIMASK = 0x07 ; // mask to extract priority part (internal)

#define DLOG_PRI(p) ((p) & DLOG_PRIMASK)

struct DCODE {
    const char *c_name;
    int c_val;
};

// moudle id
enum {
    DLOG = 0,      // Dlog
    SLOG,          // Slog
    IDEDD,         // IDE daemon device
    IDEDH,         // IDE daemon host
    LOGAGTH,       // log agent host
    HCCL,          // HCCL
    FMK,           // Framework
    HIAIENGINE,    // Matrix
    DVPP,          // DVPP
    RUNTIME,       // Runtime
    CCE,           // CCE
#if (OS_TYPE == 0)
    HDC,           // HDC
#else
    HDCL,
#endif
    DRV,           // Driver
    MDCCONTROL,    // Mdc control
    MDCFUSION,     // Mdc fusion
    MDCLOCATION,   // Mdc location
    MDCPERCEPTION, // Mdc perception
    MDCMOP,
    MDCFSM,
    MDCCOMMON,
    MDCMONITOR,
    MDCBSWP,    // MDC basesoftware platform
    MDCDEFAULT, // MDC UNDEFINE
    MDCSC,      // MDC spatial cognition
    MDCBP,
    MLL,
    DEVMM,  // Dlog memory managent
    KERNEL, // Kernel
    INVLID_MOUDLE_ID
};

constexpr int MAX_MOD_NAME_LEN = 32;

#ifdef __MODULE_ID_NAME__
#define SET_MOUDLE_ID_MAP_NAME(x) { #x, x }

static DCODE MODULEID_NAME[] = { SET_MOUDLE_ID_MAP_NAME(DLOG),
                                SET_MOUDLE_ID_MAP_NAME(SLOG),
                                SET_MOUDLE_ID_MAP_NAME(IDEDD),
                                SET_MOUDLE_ID_MAP_NAME(IDEDH),
                                SET_MOUDLE_ID_MAP_NAME(LOGAGTH),
                                SET_MOUDLE_ID_MAP_NAME(HCCL),
                                SET_MOUDLE_ID_MAP_NAME(FMK),
                                SET_MOUDLE_ID_MAP_NAME(HIAIENGINE),
                                SET_MOUDLE_ID_MAP_NAME(DVPP),
                                SET_MOUDLE_ID_MAP_NAME(RUNTIME),
                                SET_MOUDLE_ID_MAP_NAME(CCE),
                                SET_MOUDLE_ID_MAP_NAME(HDC),
                                SET_MOUDLE_ID_MAP_NAME(DRV),
                                SET_MOUDLE_ID_MAP_NAME(MDCCONTROL),
                                SET_MOUDLE_ID_MAP_NAME(MDCFUSION),
                                SET_MOUDLE_ID_MAP_NAME(MDCLOCATION),
                                SET_MOUDLE_ID_MAP_NAME(MDCPERCEPTION),
                                SET_MOUDLE_ID_MAP_NAME(MDCMOP),
                                SET_MOUDLE_ID_MAP_NAME(MDCFSM),
                                SET_MOUDLE_ID_MAP_NAME(MDCCOMMON),
                                SET_MOUDLE_ID_MAP_NAME(MDCMONITOR),
                                SET_MOUDLE_ID_MAP_NAME(MDCBSWP),
                                SET_MOUDLE_ID_MAP_NAME(MDCDEFAULT),
                                SET_MOUDLE_ID_MAP_NAME(MDCSC),
                                SET_MOUDLE_ID_MAP_NAME(MDCBP),
                                SET_MOUDLE_ID_MAP_NAME(MLL),
                                SET_MOUDLE_ID_MAP_NAME(DEVMM),
                                SET_MOUDLE_ID_MAP_NAME(KERNEL),
                                { NULL, -1 } };
#endif

extern void dlog_error(int moduleId, const char *fmt, ...);

extern void dlog_warn(int moduleId, const char *fmt, ...);

extern void dlog_info(int moduleId, const char *fmt, ...);

extern void dlog_debug(int moduleId, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* sys/slog.h */
