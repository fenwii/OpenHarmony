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
import collections
import subprocess
import shutil
import sys
import json


def encode(data, encoding='utf-8'):
    if sys.version_info.major == 2:
        return data.encode(encoding)
    return data


def decode(data, encoding='utf-8'):
    if sys.version_info.major == 2:
        return data.decode(encoding)
    return data


def remove_path(path):
    if os.path.exists(path):
        shutil.rmtree(path)


# Read json file data
def read_json_file(input_file):
    if not os.path.exists(input_file):
        print('file [{}] no exist.'.format(input_file))
        return None
    data = None
    with open(input_file, 'rb') as input_f:
        data = json.load(input_f)
    return data


def exec_command(cmd, log_path='out/build.log', **kwargs):
    with open(log_path, 'at') as f:
        process = subprocess.Popen(cmd,
                                   stdout=subprocess.PIPE,
                                   stderr=subprocess.PIPE,
                                   universal_newlines=True,
                                   **kwargs)
        for line in iter(process.stdout.readline, ''):
            sys.stdout.write(line)
            f.write(line)

    process.wait()
    ret_code = process.returncode

    if ret_code != 0:
        with open(log_path, 'at') as f:
            for line in iter(process.stderr.readline, ''):
                sys.stdout.write(line)
                f.write(line)
        print('you can check build log in {}'.format(log_path))
        raise Exception("{} failed, return code is {}".format(cmd, ret_code))


def check_output(cmd, **kwargs):
    try:
        ret = subprocess.check_output(cmd,
                                      stderr=subprocess.STDOUT,
                                      universal_newlines=True,
                                      **kwargs)
    except subprocess.CalledProcessError as e:
        ret = e.output
        raise Exception("{} failed, failed log is {}".format(cmd, ret))

    return ret


def makedirs(path, exist_ok=True):
    try:
        os.makedirs(path)
    except OSError:
        if not os.path.isdir(path):
            raise Exception("{} makedirs failed".format(path))
        if not exist_ok:
            raise Exception("{} exists, makedirs failed".format(path))


class CallbackDict(object):
    handlers = None

    def __init__(self):
        self.handlers = collections.defaultdict(list)

    def register(self, event, callback):
        self.handlers[event].append(callback)

    def excute(self, event, **kwargs):
        if event not in self.handlers:
            raise Exception('{} not found in callback dict'.format(event))
        for handler in self.handlers.get(event, []):
            handler(**kwargs)
