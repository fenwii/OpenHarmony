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
from utils import makedirs
from utils import read_json_file
from config import Compile


def run_build(**kwargs):
    print("\n=== start build ===\n")
    config = kwargs['config']
    compile = Compile()
    compile.compile(config)
    print("ohos {} build success!".format(config.product))


def parse_product_json(config):
    product = config.product
    product_json = os.path.join(config.get_build_path(), 'product',
                                '{}.json'.format(product))
    json_content = read_json_file(product_json)
    Compile.get_tool_path(config, json_content)
    return load_subsystem_feature(json_content, config)


def check_build(config):
    # Delete and create output directory
    out_path = config.get_out_path()
    if os.path.exists(out_path):
        shutil.rmtree(out_path)
    makedirs(out_path)
    return parse_product_json(config)


def load_subsystem_feature(json_content, config):
    for subsystem in json_content['subsystem']:
        for component in subsystem['component']:
            for feature in component['features']:
                config.args_list.append(feature)
    return True


def config_create(**kwargs):
    config = kwargs['config']
    check_build(config)
    return True
