cmake_minimum_required(VERSION 3.16.5)

set(GlobalSrc "${PROJECT_SOURCE_DIR}/base/global/frameworks/resmgr_lite/src")
set(GlobalInc "${PROJECT_SOURCE_DIR}/base/global/frameworks/resmgr_lite/include")
set(GlobalKitInc "${PROJECT_SOURCE_DIR}/base/global/interfaces/innerkits/resmgr_lite")

include_directories(${PROJECT_SOURCE_DIR}/third_party/bounds_checking_function/include)

add_library(global_resmgr STATIC
    ${GlobalSrc}/global.c
    ${GlobalSrc}/global_utils.c
)

target_include_directories(global_resmgr PUBLIC ${GlobalInc} ${GlobalKitInc})