#include "system_config.h"

#define LOS_CB_START(module)     __##module##_start
#define LOS_CB_END(module)       __##module##_end
#define LOS_BLOCK_START(module)  __block_##module##_start
#define LOS_BLOCK_END(module)    __block_##module##_end
#define LOS_GET_SPACE_FOR_SYSTEM(module, X)  \
    . = ALIGN(8);\
    LOS_BLOCK_START(module) = .;\
    LOS_CB_START(module) = .;\
    KEEP(*(.##module)); \
    LOS_CB_END(module) = .;\
    . += (LOS_CB_END(module) - LOS_CB_START(module))*((X) - 1);\
    LOS_BLOCK_END(module) = .

LOS_GET_SPACE_FOR_SYSTEM(sysmemused,(LOSCFG_BASE_CORE_TSK_LIMIT_CONFIG + 1));
LOS_GET_SPACE_FOR_SYSTEM(errno,(LOSCFG_BASE_CORE_TSK_LIMIT_CONFIG + 1));

