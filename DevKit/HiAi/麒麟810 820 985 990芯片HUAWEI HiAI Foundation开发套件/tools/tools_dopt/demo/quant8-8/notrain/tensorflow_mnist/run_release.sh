#!/bin/bash
# Scipt function desciption:tensorflow_imagenet_resnet50 run_release Scipt.
# Copyright © Huawei Technologies Co., Ltd. 2010-2018. All rights reserved.
set -e
clear

mkdir  curmodel || echo "Creating output directory..."

# replace the root path in template files
ROOT=$(cd ../../../..; pwd)
find -L . -name "*.tmp" | xargs -i -n1 -r sh -c 'FN_TMP={}; FN=${FN_TMP%.*}; cp ${FN_TMP} ${FN}; sed -i -e "s#@ROOT@#'"${ROOT}"'#g" ${FN}'

PY_VER=$(python -c "import sys; print(sys.version_info[0])")
python3 ${ROOT}/tensorflow/dopt/py3/dopt_so.py  --framework 3 -m   0   --model ./basemodel/mnist.pb --cal_conf ./config.prototxt --output  ./curmodel/finalmodel.pb --input_format  NHWC   --input_shape   "Placeholder:1,28,28,1"   --out_nodes  "Softmax" --compress_conf  ./curmodel/mnist_param --device_idx   0