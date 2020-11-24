#!/bin/bash
# Script function comment:bash script for run_develop
# Copyright © Huawei Technologies Co., Ltd. 2010-2018. All rights reserved.
set -e
clear
rm -r opt_field/ || echo "remove opt_field..."

# replace the root path in template files
ROOT=$(cd ../../..; pwd)
find -L . -name "*.tmp" | xargs -i -n1 -r sh -c 'FN_TMP={}; FN=${FN_TMP%.*}; cp ${FN_TMP} ${FN}; sed -i -e "s#@ROOT@#'"${ROOT}"'#g" ${FN}'

python3 ${ROOT}/tensorflow/dopt/py3/dopt_so.py -c  scen.yaml
