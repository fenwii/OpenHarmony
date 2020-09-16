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
from filter_process import code_filter


def add_options(parser):
    parser.add_argument('-c', '--config', help='Config for code filtering',
                        nargs='*')
    parser.add_argument('--no_commit_msg', help='Remove commit msg',
                        action='store_true')
    parser.add_argument('-p', '--path', help='Code targer path after '
                        'filtering out', nargs='*')


def exec_command(args):
    callback_dict = CallbackDict()
    target = 'filter'

    if args.config:
        callback_dict.config = args.config[0]
    no_commit_msg = args.no_commit_msg
    if args.path:
        target_path = args.path[0]
    else:
        target_path = 'ohos_opensource'

    callback_dict.register(target, code_filter)

    callback_dict.excute(target,
                         callback_dict=callback_dict,
                         no_commit_msg=no_commit_msg,
                         target_path=target_path)
