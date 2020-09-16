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
import sys
from subprocess import Popen
import argparse
import shlex


def cmd_exec(command):
    cmd = shlex.split(command)
    proc = Popen(cmd)
    proc.wait()
    ret_code = proc.returncode
    if ret_code != 0:
        raise Exception("{} failed, return code is {}".format(cmd, ret_code))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--path', help='Build path.')
    parser.add_argument('--prebuilts', help='Build prebuilts.')
    parser.add_argument('--command', help='Build command.')
    parser.add_argument('--enable', help='enable python.', nargs='*')
    args = parser.parse_args()

    if args.enable:
        if args.enable[0] == 'false':
            return

    if args.path:
        curr_dir = os.getcwd()
        os.chdir(args.path)
        if args.prebuilts:
            cmd_exec(args.prebuilts)
        if args.command:
            if '&&' in args.command:
                command = args.command.split('&&')
                for data in command:
                    cmd_exec(data)
            else:
                cmd_exec(args.command)

        os.chdir(curr_dir)


if __name__ == '__main__':
    sys.exit(main())
