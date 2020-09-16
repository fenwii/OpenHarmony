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

import os
import shutil
from utils import file_write
from utils import CallbackDict, makedirs
from utils import read_json_file


def args_gn_create(config):
    # Delete and create output directory
    out_path = config.get_out_path()
    if os.path.exists(out_path):
        shutil.rmtree(out_path)
    makedirs(out_path)


def args_gn_write(config):
    product_args_path = os.path.join(config.get_out_path(), 'args.gn')
    ndk = config.ndk
    build_type = config.build_type

    file_write(product_args_path, 'at', 'product = "{}"\n'.format(
               config.product))
    # Add import to the file header
    if ndk is not None:
        ndk_gn_args = ('ohos_build_ndk = true\n'
                       'ohos_build_ndk_target_host = "{}"'
                       '\n'.format(ndk))
        file_write(product_args_path, 'at', ndk_gn_args)
    if config.test_args:
        file_write(product_args_path, 'at',
                   'ohos_xts_test_args = "{}"\n'.format(config.test_args[1]))
    file_write(product_args_path, 'at',
               'ohos_build_type = "{}"\n'.format(build_type))
    for feature in CallbackDict.args_list:
        file_write(product_args_path, 'at', '{}\n'.format(feature))


def load_subsystem_feature(config):
    product = config.product
    product_json = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                'product', '{}.json'.format(product))
    json_content = read_json_file(product_json)
    for subsystem in json_content['subsystem']:
        for component in subsystem['component']:
            for feature in component['features']:
                CallbackDict.args_list.append(feature)


def config_create(**kwargs):
    config = kwargs['config']
    args_gn_create(config)
    load_subsystem_feature(config)
    args_gn_write(config)
    return True
