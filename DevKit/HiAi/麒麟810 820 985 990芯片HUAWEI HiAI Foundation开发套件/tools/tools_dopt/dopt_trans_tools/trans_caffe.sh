#!/bin/bash
# Script function comment:bash script for trans_caffe.
# Copyright © Huawei Technologies Co., Ltd. 2010-2018. All rights reserved.
set -e
DIR="$1"
if [[ -z "${DIR}" || "${DIR}" == -h || "${DIR}" == --help ]]; then 
    echo "Usage:      $0 TargetDir [CaffeDir]"
    echo "TargetDir - path of optimization task"
    echo "CaffeDir  - Optional, path of Caffe"
    exit 0
fi
if [ ! -d "${DIR}" ]; then
    echo ${DIR} not found!
    exit 1
fi
ABSDIR=$(cd "${DIR}"; pwd)

CAFFE_DIR="$2"
if [ -z "${CAFFE_DIR}" ]; then 
    CAFFE_DIR=../caffe/caffe-mod
fi
if [ ! -e "${CAFFE_DIR}/libs/libopt.so" ]; then
    echo Caffe not found at "${DIR}"!
    exit 1
fi

export  LD_LIBRARY_PATH="${LD_LIBRARY_PATH}":"${CAFFE_DIR}"/libs/

PY_VER=$(python -c "import sys; print(sys.version_info[0])")
dopt_trans_path=$(dirname $(readlink -f "$0"))
python2 "$dopt_trans_path"/py2/dopt_trans_model_so.py  -d  "${ABSDIR}" -c "${CAFFE_DIR}"
