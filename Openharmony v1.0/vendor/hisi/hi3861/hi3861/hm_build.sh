#!/bin/bash
set -e

# prebuild #
cd ../../../../vendor/hisi/hi3861/hi3861
CROOT=$(pwd)

OUTPUT_SRC_DIR=$CROOT/output/bin
OUTPUT_DST_DIR=$CROOT/../../../../out

OHOS_LIBS_DIR=$CROOT/ohos/libs

rm $OHOS_LIBS_DIR -rf

mkdir -p $OHOS_LIBS_DIR
find $OUTPUT_DST_DIR/wifiiot/libs/ -name '*.a' -exec cp "{}" $OHOS_LIBS_DIR  \;
find $CROOT/3rd_sdk/ -name '*.a' -exec cp "{}" $OHOS_LIBS_DIR  \;


# build #
./build.sh wifiiot_app

# after build #
if [ ! -d $OUTPUT_DST_DIR ]; then
   mkdir $OUTPUT_DST_DIR
fi
cp $OUTPUT_SRC_DIR/* $OUTPUT_DST_DIR/wifiiot/ -rf

