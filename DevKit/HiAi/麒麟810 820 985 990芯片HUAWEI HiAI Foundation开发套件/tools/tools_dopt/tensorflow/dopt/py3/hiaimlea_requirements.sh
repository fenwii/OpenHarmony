#!/bin/bash
# encoding: utf-8
# Copyright © Huawei Technologies Co., Ltd. 2010-2018. All rights reserved.
set -e
clear

for line in $(cat $(dirname $0)/strategy/task/task_custom/hiaiml_ea/requirements.txt)
do 
    pip3 install $line
done
