#!/bin/bash
# Script function comment:bash script for optpatch
# Copyright © Huawei Technologies Co., Ltd. 2010-2018. All rights reserved.
set -e
echo Patch caffe.proto
patch -p0 < caffe.proto.patch
##############################
echo Patch Makefile.config
if [ ! -f "Makefile.config" ];then
  cp Makefile.config.example Makefile.config
fi
echo USE_NCCL := 1 >> Makefile.config
echo USE_CUDNN := 1 >> Makefile.config
echo LIBRARY_DIRS += ./libs/ >> Makefile.config
##############################
echo Patch Makefile
sed -i '/ifeq ($(USE_NCCL), 1)/aLIBRARIES += opt\nNVCCFLAGS += -Wno-deprecated-gpu-targets' Makefile
##############################
echo Test GCC Version
GCC=gcc
VER=$($GCC -dumpversion | sed -e 's/\.\([0-9][0-9]\)/\1/g' -e 's/\.\([0-9]\)/0\1/g' -e 's/^[0-9]\{3,4\}$$/&00/')
echo GCC Version: $VER
if [ "$VER" -ge 50000 ];then
  echo Copy algorithm so file with new ABI
  MAJOR=5
else
  echo Copy algorithm so file with old ABI
  MAJOR=4
fi
ln -s ../libs/caffe_libs/so${MAJOR} libs
