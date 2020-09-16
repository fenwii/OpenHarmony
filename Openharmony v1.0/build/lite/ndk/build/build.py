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
import argparse
import platform
import subprocess
import time


def exec_command(cmd, log_path='out/build.log', **kwargs):
    process = subprocess.Popen(cmd)
    process.wait()
    ret_code = process.returncode

    if ret_code != 0:
        raise Exception("{} failed, return code is {}".format(cmd, ret_code))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('action', help='action, build or clean path.',
                        nargs='*')
    parser.add_argument('-v', '--build_type', help='Release or debug version.',
                        nargs='*')
    args = parser.parse_args()

    product_path = './out/'
    log_path = os.path.join(product_path, 'compile.log')

    args.action = ['build'] if not args.action else args.action

    if args.action[0] == 'build':
        gn_cmd = ''
        ninja_cmd = ''
        print("\n=== start build ===\n")
        if platform.system().find('Windows') == 0:
            gn_cmd = ['gn.exe', 'gen', product_path, '--root=.',
                      '--dotfile=build/.gn']

            ninja_cmd = ['ninja.exe',
                         '-C', product_path]
        else:
            gn_cmd = ['gn', 'gen', product_path, '--root=.',
                      '--dotfile=build/.gn']
            if args.build_type == 'debug':
                gn_cmd += ['--args=ohos_build_type=\"debug\"']

            ninja_cmd = ['ninja', '-C', product_path]
        print("=== gn working ===\n")
        exec_command(gn_cmd, log_path)
        time.sleep(2)
        print("\n=== ninja working ===")
        exec_command(ninja_cmd, log_path)
        print("build success!")
    elif args.action[0] == 'clean':
        clean_cmd = ''
        if not os.path.exists(product_path):
            print('Nothing to clean! No build found.')
            return 0
        print("\n=== start clean ===\n")
        if platform.system().find('Windows') == 0:
            clean_cmd = ['ninja.exe', '-C', product_path, '-t', 'clean']
        else:
            clean_cmd = ['ninja', '-C', product_path, '-t', 'clean']
        print("=== clean working ===\n")
        exec_command(clean_cmd, log_path)
        print("clean success!")


if __name__ == '__main__':
    sys.exit(main())
