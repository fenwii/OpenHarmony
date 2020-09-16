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

import sys
import argparse
import importlib
import logging
import os


def usage():
    msg = "\n  python build.py ipcamera_hi3516dv300\n  "\
          "python build.py ipcamera_hi3518ev300\n  "\
          "python build.py wifiiot"
    return msg


def main():
    if not __package__:
        path = os.path.join(os.path.abspath(os.path.dirname(__file__)),
                            'build')
        sys.path.insert(0, path)

    parser = argparse.ArgumentParser(usage=usage())
    parser_list = []
    parser_list.append({
        'name': 'compile',
        'help': 'Build source code'
    })

    for each in parser_list:
        module = importlib.import_module('.{}'.format(each.get('name')),
                                         'lite')
        module.add_options(parser)
        parser.set_defaults(command=module.exec_command)

    args = parser.parse_args()

    try:
        status = args.command(args)
    except KeyboardInterrupt:
        logging.warning('interrupted')
        status = -1
    except Exception as e:
        print(e)
        parser.print_help()
        status = -1

    return status


if __name__ == "__main__":
    sys.exit(main())
