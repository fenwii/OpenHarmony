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
import sys
import shutil
sys.path.append(os.path.join(os.path.dirname(__file__), os.pardir))
from utils import makedirs # noqa: E402


def make_archive(source, destination):
    base = os.path.basename(destination)
    fields = base.split('.')
    name = fields[0] + '.' + fields[1] + '.' + fields[2]
    file_format = fields[3]
    archive_from = os.path.dirname(source)
    archive_to = os.path.basename(source.strip(os.sep))
    print('Zipping: ', source, destination, archive_from, archive_to)
    shutil.make_archive(name, file_format, archive_from, archive_to)
    shutil.move('%s.%s' % (name, file_format), destination)


def main():
    parser = argparse.ArgumentParser(
        description='NDK archive tool.')
    parser.add_argument(
        '--src_dir',
        help='NDK source path.',
        required=True)
    parser.add_argument(
        '--name',
        help='NDK name.',
        required=True)
    parser.add_argument(
        '--dest_dir',
        help='NDK zip dest path.',
        required=True)
    args = parser.parse_args()

    src = args.src_dir
    assert os.path.exists(src), \
        'NDK build diretory not exist, please confirm NDK build result.'

    dest = args.dest_dir
    if not os.path.exists(dest):
        makedirs(dest)
    else:
        shutil.rmtree(dest)

    name = args.name
    print(dest, name)
    make_archive(src, dest + '-' + name + '.zip')
    return 0


if __name__ == '__main__':
    sys.exit(main())
