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

import argparse
import os
import shutil
import sys
from utils import makedirs


def copytree(src, dst, symlinks=False, ignore=None):
    for item in os.listdir(src):
        if '.git' in item or '.repo' in item:
            continue
        src_path = os.path.join(src, item)
        dst_path = os.path.join(dst, item)
        if os.path.isdir(src_path):
            try:
                shutil.copytree(src_path, dst_path, symlinks)
            except Exception as e:
                print('Warning :{}\nIgnore invalid symlink!'.format(
                    str(e.args[0])))
        else:
            shutil.copy2(src_path, dst_path)


def main():
    parser = argparse.ArgumentParser(
        description='A common diretory and file copy.')
    parser.add_argument(
        '--src_type',
        help='src tyepe to copy.')
    parser.add_argument(
        '--src',
        help='List the sources to copy.',
        required=True)
    parser.add_argument(
        '--dest_dir',
        help='Path that the sources should be copied to.',
        required=True)

    args = parser.parse_args()

    out_dir = args.dest_dir
    if not os.path.exists(out_dir):
        makedirs(out_dir)

    if args.src_type == "file" or os.path.isfile(args.src):
        shutil.copy(args.src, out_dir)
        return 0

    source_dir = args.src
    assert os.path.exists(source_dir)

    copytree(source_dir, out_dir)

    return 0


if __name__ == '__main__':
    sys.exit(main())
