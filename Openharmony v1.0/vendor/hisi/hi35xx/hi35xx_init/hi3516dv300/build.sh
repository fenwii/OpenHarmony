#!/bin/bash
# Copyright 2001-2020, Huawei Technologies Co. Ltd.
#
# ALL RIGHTS RESERVED
#
# Compile mpp/sample project, this is the entrance script
# error out on errors
set -e
OUT_DIR="$1"
OHOS_BUILD_COMPILER="$4"
function copySocLib() {
    ROOT_DIR=$(cd $(dirname "$0");pwd)
    SOURCE_LIB="$ROOT_DIR/../../hi3516dv300/soc/lib"

    cp -rf $SOURCE_LIB/./libmpi.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./lib_hiacs.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./lib_hiir_auto.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./lib_hiawb.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libive.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libdnvqe.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./lib_hidrc.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./lib_hildci.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libupvqe.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./lib_hidehaze.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./lib_hicalcflicker.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libVoiceEngine.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libisp.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libsns_imx335.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./lib_hiae.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libhdmi.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libaacdec.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libaacenc.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libaaccomm.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libaacsbrdec.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libaacsbrenc.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libsecurec.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libtde.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libhive_RES.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libhive_record.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libhive_HPF.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libhive_ANR.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libhive_common.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libhive_AEC.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libhive_AGC.so $OUT_DIR/
    cp -rf $SOURCE_LIB/./libhive_EQ.so $OUT_DIR/
}
function main(){
    ROOT_DIR=$(cd $(dirname "$0");pwd)
    copySocLib
    cd "$ROOT_DIR"
    make clean && make -j16 OUTDIR=$OUT_DIR
    cp OHOS_Image* $OUT_DIR/
}
main "$@"
