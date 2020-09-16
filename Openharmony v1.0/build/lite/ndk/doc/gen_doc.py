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
import shutil
import re
import tempfile
import argparse
import distutils.spawn
sys.path.append(os.path.join(os.path.dirname(__file__), os.pardir, os.pardir))
from utils import check_output, makedirs  # noqa: E402


def gen_doc(args):
    html_output_dir = args.output
    contents = None
    with tempfile.NamedTemporaryFile(
            suffix=os.path.basename(args.doxygen_file)) as doxygen_file:
        shutil.copyfile(args.doxygen_file, doxygen_file.name)
        with open(doxygen_file.name, 'r') as file:
            contents = file.read()
        if contents is None:
            raise Exception('Failed to read %s' % args.doxygen_file)

        keys = {
            '%VERSION%':
                args.version,
            '%EXCLUDE_DIR%':
                args.exclude_dir,
            '%OUTPUT_DIR%':
                os.path.relpath(html_output_dir, args.working_dir)
        }
        for (key, value) in list(keys.items()):
            value = value.replace('\\', '\\\\')
            contents = re.sub(key, value, contents)

        with open(doxygen_file.name, 'w') as file:
            file.write(contents)

        old_cwd = os.getcwd()
        try:
            # if no ndk headers exist, return.
            if os.path.exists(args.working_dir) is not True:
                print("no ndk headers exist, return")
                return
            os.chdir(args.working_dir)

            doxygen_path = distutils.spawn.find_executable('doxygen')
            if doxygen_path is None:
                print(
                    "Warning: Failed to find doxygen, please install doxygen "
                    "with \"sudo apt-get install doxygen\" on Ubuntu"
                )
                return
            html_output_dir = os.path.relpath(html_output_dir,
                                              args.working_dir)
            if not os.path.exists(html_output_dir):
                makedirs(html_output_dir)
            cmd = [doxygen_path, doxygen_file.name]
            check_output(cmd)

        finally:
            os.chdir(old_cwd)


def main():
    parser = argparse.ArgumentParser(description='Generate ndk docs')
    parser.add_argument('--version', help='OHOS version', required=True)
    parser.add_argument('--exclude_dir', help='doxygen exclude dirs',
                        required=True)
    parser.add_argument('--doxygen-file', help='doxygen config file')
    parser.add_argument('--output', help='output index.html')
    parser.add_argument(
        '--working-dir',
        help='the directory where doxygen command will be executed')
    args = parser.parse_args()

    return gen_doc(args)


if __name__ == "__main__":
    sys.exit(main())
