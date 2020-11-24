#!/bin/bash
# Scipt function desciption:caffe_imagenet_inception_v3 run_release Scipt.
# Copyright © Huawei Technologies Co., Ltd. 2010-2018. All rights reserved.
set -e
clear

mkdir  curmodel || echo "Creating output directory..."

# replace the root path in template files
ROOT=$(cd ../../../..; pwd)
find -L . -name "*.tmp" | xargs -i -n1 -r sh -c 'FN_TMP={}; FN=${FN_TMP%.*}; cp ${FN_TMP} ${FN}; sed -i -e "s#@ROOT@#'"${ROOT}"'#g" ${FN}'

PY_VER=$(python -c "import sys; print(sys.version_info[0])")
python2 ${ROOT}/caffe/dopt/py2/dopt_so.py  --framework 0 -m   0   --model   basemodel/mnist.prototxt   --weight   basemodel/mnist.caffemodel   --cal_conf   ./config.prototxt   --output  ./curmodel/finalmodel.caffemodel   --input_format   NCHW   --input_shape   data:1,1,28,28   --out_nodes   ip2   --compress_conf  ./curmodel/mnist_param     --device_idx   0   --caffe_dir   /opt/caffe
