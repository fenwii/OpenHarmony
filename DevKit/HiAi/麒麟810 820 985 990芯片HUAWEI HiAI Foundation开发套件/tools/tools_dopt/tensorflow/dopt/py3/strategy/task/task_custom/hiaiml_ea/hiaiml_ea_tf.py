#!/usr/bin/env python
# coding: utf-8
# Copyright © Huawei Technologies Co., Ltd. 2010-2018. All rights reserved.
import sys
sys.path.insert(0, 'PYTHONPATH')
import argparse
from user_module import PreNet
from user_module import PostNet
from user_module import UserModule
from hiaiml_ea import main


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='HiAIMLEASearch')
    parser.add_argument('--cfg_path', metavar='DIR', help='path to config file')
    args = parser.parse_args()
    main(args, PreNet, PostNet, UserModule)
