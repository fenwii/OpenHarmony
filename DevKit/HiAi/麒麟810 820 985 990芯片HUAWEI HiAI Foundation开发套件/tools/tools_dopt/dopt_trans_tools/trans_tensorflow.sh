#!/bin/bash
# Script function comment:bash script for trans_tensorflow.
# Copyright © Huawei Technologies Co., Ltd. 2010-2018. All rights reserved.
set -e
DIR="$1"
if [[ -z "${DIR}" || "${DIR}" == -h || "${DIR}" == --help ]]; then 
    echo "Usage:      $0 TargetDir [OutputOp]"
    echo "TargetDir - path of optimization task"
    echo "OutputOp  - Optional, comma-separated names of output Op"
    exit 0
fi
if [ ! -d "${DIR}" ]; then
    echo "${DIR}" not found!
    exit 1
fi

OUTPUTS="$2"
if [ -z "${OUTPUTS}" ]; then 
    echo Warning: Outputs not defined! Skip generate pb file
    ARGS=""
else
    ARGS="-o ${OUTPUTS}"
fi

ABSDIR=$(cd "${DIR}"; pwd)
PY_VER=$(python -c "import sys; print(sys.version_info[0])")
dopt_trans_path=$(dirname $(readlink -f "$0"))
python3 "$dopt_trans_path"/py3/dopt_trans_model_so.py  -d  "${ABSDIR}" "${ARGS}"
