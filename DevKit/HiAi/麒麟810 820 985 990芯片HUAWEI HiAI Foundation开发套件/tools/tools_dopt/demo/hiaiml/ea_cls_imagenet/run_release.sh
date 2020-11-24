#!/bin/bash
# Script description:run_develop Script.
# Copyright © Huawei Technologies Co., Ltd. 2010-2018. All rights reserved.
set -e
clear
mkdir -p log_classification

LOG_FILE="log_classification/log_$(date '+%Y_%m_%d_%H_%M_%S').txt"

ROOT=$(cd ../../../; pwd)
python3 ${ROOT}/tensorflow/dopt/py3/dopt_so.py -c scen.yaml 2>&1 | tee ./${LOG_FILE}
