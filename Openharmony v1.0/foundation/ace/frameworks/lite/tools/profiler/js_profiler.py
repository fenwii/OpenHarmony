# -*- coding: utf-8 -*-
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


import sys
import argparse

from js_profiler_config import key_word
from js_profiler_config import label_name
from js_profiler_config import profiler_name

sys.path.append('./js_profiler_config.py')


def add_label(index):
    return label_name[index]


def add_parent_label(index):
    parent_info = profiler_name[label_name[index]]
    return 'UNKNOWN' if parent_info == 'P_UNKNOWN' else parent_info


def add_component_info(component_id):
    return key_word[component_id]


def add_description_info(description_id):
    return '' if description_id == 0 else key_word[description_id]


def parser(opt):
    source_file = opt.source
    try:
        with open(source_file, 'r') as source:
            for line in source.readlines():
                strlist = line.split(' ')
                if len(strlist) == 5:
                    msg = 'COST ' + add_component_info(int(strlist[0]))
                    msg = msg + ' ' + add_label(int(strlist[1]))
                    msg = msg + ' ' + strlist[2] + 'ms'
                    msg = msg + ' [' + \
                          add_description_info(int(strlist[3])) + ']'
                    msg = msg + ' ' + add_parent_label(int(strlist[4]))
                    print(msg)
                    output(msg, opt.destination)
    except Exception:
        print('open source file error')


def output(msg, dest):
    try:
        with open(dest, 'a+') as destination:
            destination.write(msg + '\n')
    except Exception:
        print('open destination file error')


def get_parameters():
    parser_config = argparse.ArgumentParser()
    parser_config.add_argument('--source', type=str, default='',
                               help='input file')
    parser_config.add_argument('--destination', type=str, default='.',
                               help='output file')
    config = parser_config.parse_args()
    return config


if __name__ == '__main__':
    parser(get_parameters())
