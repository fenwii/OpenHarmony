#!/bin/bash
set -e
ROOT_DIR=$(dirname "$0")

strip_and_copy_to()
{
    if [ "$3" == "clang" ];
    then
        $COMPILER_DIR/bin/llvm-strip $ROOT_DIR/build/$2
    else
        strip $ROOT_DIR/build/$2
    fi

    cp $ROOT_DIR/build/$2 $1
}

copy_to()
{
    if [ -f $ROOT_DIR/build/$2 ];then
        mkdir -p $1/obj/third_party/wpa_supplicant/wpa_supplicant-2.9
        cp $ROOT_DIR/build/$2 $1/obj/third_party/wpa_supplicant/wpa_supplicant-2.9/
    fi
}

build_for_ndk()
{
    cp $ROOT_DIR/build/libwpa_client.so $1/ndk/sysroot/usr/lib
    cp $ROOT_DIR/build/libwpa.so $1/ndk/sysroot/usr/lib
    cp $ROOT_DIR/src/common/wpa_ctrl.h $1/ndk/sysroot/usr/include
}

# LIB_TYPE: 0 is static library, 1 is sharedlibrary
# COMPILER_TYPE gcc or clang
do_build()
{
    if [ -d "$ROOT_DIR/build/objs" ]; then
    rm -rf $ROOT_DIR/build/objs
    fi
    mkdir -p $ROOT_DIR/build/objs

    make -C $ROOT_DIR/wpa_supplicant/ clean
    make DEPDIR=$1 COMPILER_TYPE=$3 LIB_TYPE=$2 DEBUG=$4 COMPILER_DIR=$5 -C $ROOT_DIR/wpa_supplicant/ -j

    make -C $ROOT_DIR/hostapd/ clean
    make DEPDIR=$1 COMPILER_TYPE=$3 LIB_TYPE=$2 DEBUG=$4 COMPILER_DIR=$5 -C $ROOT_DIR/hostapd/ -j

    make -C $ROOT_DIR/build/ clean
    make DEPDIR=$1 COMPILER_TYPE=$3 LIB_TYPE=$2 DEBUG=$4 COMPILER_DIR=$5 -C $ROOT_DIR/build/

    if [ "$2" = 1 ]; then
        strip_and_copy_to $1 libwpa.so $3
    else
        copy_to $1 libwpa.a
    fi

    if [ "$2" = 1 ]; then
        make DEPDIR=DEPDIR=$1 COMPILER_TYPE=$3 LIB_TYPE=$2 DEBUG=$4 COMPILER_DIR=$5 -C $ROOT_DIR/wpa_supplicant/ libwpa_client.so -j
        strip_and_copy_to $1 libwpa_client.so $3
    else
        make DEPDIR=DEPDIR=$1 COMPILER_TYPE=$3 LIB_TYPE=$2 DEBUG=$4 COMPILER_DIR=$5 -C $ROOT_DIR/wpa_supplicant/ libwpa_client.a -j
        copy_to $1 libwpa_client.a
    fi
}

main()
{
    OUT_DIR=$1
    COMPILER_TYPE=$2
    NDK_FLAG=$3
    DEBUG=$4
    COMPILER_DIR=$5

    if [ "$4" == "debug" ]; then
        DEBUG=1
    else
        DEBUG=0
    fi

    do_build $OUT_DIR 0 $COMPILER_TYPE $DEBUG $COMPILER_DIR
    do_build $OUT_DIR 1 $COMPILER_TYPE $DEBUG $COMPILER_DIR

    if [ "$NDK_FLAG" = true ]; then
        build_for_ndk $OUT_DIR
    fi
}

main $1 $2 $3 $4 $5
