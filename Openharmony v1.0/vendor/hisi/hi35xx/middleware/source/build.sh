#!/bin/bash
# Copyright 2020-2020, Huawei Technologies Co. Ltd.
#
# ALL RIGHTS RESERVED
#
# Compile middleware project, this is the entrance script

# error out on errors
set -e
OUT_DIR="$1"
BOARD_NAME="$2"
HOS_KERNEL_TYPE="$3"
HOS_BUILD_COMPILER="$4"
COMPILER_DIR=$5

function main(){
    ROOT_DIR=$(cd $(dirname "$0");pwd)
    CHIP_TYPE="$2"
    unset OS_TYPE
    BUILD_COMPILER="llvm"
    if [ "$HOS_KERNEL_TYPE" = "liteos_a" ];then
        OS_TYPE="ohos"
    elif [ "$HOS_KERNEL_TYPE" = "linux" ];then
        OS_TYPE="linux"
    fi
    if [ "$HOS_BUILD_COMPILER" = "gcc" ];then
        BUILD_COMPILER="gcc"
    fi
    sed -i "/^CFG_COMPILE_DIR=/cCFG_COMPILE_DIR=$COMPILER_DIR" $(pwd)/third_party/ffmpeg/cfg.mak
    cd $ROOT_DIR/third_party/ffmpeg; make clean; make -j; cd -;
    cp -rf $ROOT_DIR/third_party/ffmpeg/ffmpeg-y/install/lib/libavcodec.so $OUT_DIR/
    cp -rf $ROOT_DIR/third_party/ffmpeg/ffmpeg-y/install/lib/libavformat.so $OUT_DIR/
    cp -rf $ROOT_DIR/third_party/ffmpeg/ffmpeg-y/install/lib/libavutil.so $OUT_DIR/

    cp -rf $ROOT_DIR/component/fileformat/mp4/lib/$BUILD_COMPILER/$OS_TYPE/libmp4.so $OUT_DIR/
    cp -rf $ROOT_DIR/component/fileformat/common/lib/$BUILD_COMPILER/$OS_TYPE/libfileformat.so $OUT_DIR/
    cp -rf $ROOT_DIR/component/recorder_pro/lib/$BUILD_COMPILER/$OS_TYPE/librecorder_pro.so $OUT_DIR/
    cp -rf $ROOT_DIR/component/dtcf/lib/$BUILD_COMPILER/$OS_TYPE/libdtcf.so $OUT_DIR/
    cp -rf $ROOT_DIR/component/fstool/lib/$BUILD_COMPILER/$OS_TYPE/libfstool.so $OUT_DIR/
    cp -rf $ROOT_DIR/common/hitimer/lib/$BUILD_COMPILER/$OS_TYPE/libhitimer.so $OUT_DIR/
    cp -rf $ROOT_DIR/common/mbuffer/lib/$BUILD_COMPILER/$OS_TYPE/libmbuf.so $OUT_DIR/
    cp -rf $ROOT_DIR/common/log/lib/$BUILD_COMPILER/$OS_TYPE/libmwlog.so $OUT_DIR/
}

main "$@"
