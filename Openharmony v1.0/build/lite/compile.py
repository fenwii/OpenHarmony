#!/usr/bin/env python
# -*- coding: utf-8 -*-

#
# Copyright (c) 2020 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

from utils import CallbackDict
from compile_process import config_create
from compile_process import run_build
from config import Config


def add_options(parser):
    parser.add_argument('product', help='Name of the product', nargs='*')
    parser.add_argument('-b', '--build_type', help='release or debug version.',
                        nargs=1, default=['release'])
    parser.add_argument('-t', '--test', help='Compile test suit', nargs='*')
    parser.add_argument('-n', '--ndk', help='Compile ndk', action='store_true')


def exec_command(args):
    callback_dict = CallbackDict()

    # parse product
    if args.product:
        config = Config(args)
        callback_dict.register(config.product, config_create)
        callback_dict.register(config.product, run_build)

        callback_dict.excute(config.product,
                             config=config,
                             args=args)
    else:
        raise Exception("Error: product not found.")
