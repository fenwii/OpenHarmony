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


def main():
    if not __package__:
        path = os.path.join(os.path.dirname(__file__), os.pardir)
        sys.path.insert(0, path)

    parser = argparse.ArgumentParser(usage="lite [COMMAND]",
                                     description='lite build system')
    subparsers = parser.add_subparsers()
    parser_list = []
    parser_list.append({
        'name': 'compile',
        'help': 'Build source code'
    })

    parser_list.append({
        'name': 'filter',
        'help': 'Filter out non-open source code'
    })

    for each in parser_list:
        module_parser = subparsers.add_parser(name=each.get('name'),
                                              help=each.get('help'))
        module = importlib.import_module('.{}'.format(each.get('name')),
                                         'lite')
        module.add_options(module_parser)
        module_parser.set_defaults(command=module.exec_command)

    args = parser.parse_args()

    try:
        status = args.command(args)
    except KeyboardInterrupt:
        logging.warning('interrupted')
        status = -1
    except Exception as e:
        logging.error(e)
        status = -1

    return status


if __name__ == "__main__":
    sys.exit(main())
