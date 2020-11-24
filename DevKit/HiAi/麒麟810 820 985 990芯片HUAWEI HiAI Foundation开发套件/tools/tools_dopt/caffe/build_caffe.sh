#!/bin/bash
# Script function comment:bash script for build_caffe
# Copyright © Huawei Technologies Co., Ltd. 2010-2018. All rights reserved.
set -e
rm -rf caffe-mod
cp -rL caffe-1.0 caffe-mod
cp -r caffe-patch/* caffe-mod/
cd caffe-mod
./optpatch.sh
make clean
make -j
make pycaffe
