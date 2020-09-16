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

from command_line.hdf_tool_commands import HdfToolCommands
from hdf_tool_daemon_server import HdfToolDaemonServer
from hdf_tool_exception import HdfToolException
from command_line.hdf_command_error_code import CommandErrorCode


def check_python_version():
    if sys.version_info < (3, 0):
        print('Please run with python version >= 3.0')
        sys.exit(-1)


def main():
    check_python_version()
    commands = HdfToolCommands()
    help_info = 'Tools backend for hdf driver development.'
    arg_parser = argparse.ArgumentParser(description=help_info)
    arg_parser.add_argument('--run_as_daemon', action='store_true')
    arg_parser.add_argument('--server_type', help='command_line or ls_hcs,'
                                                  'default command_line',
                            default='command_line')
    arg_parser.add_argument('command', help=commands.help())
    arg_parser.add_argument('remainder_args', nargs=argparse.REMAINDER)
    args = arg_parser.parse_args()
    if args.run_as_daemon:
        HdfToolDaemonServer(args.server_type).run()
        return
    try:
        ret = commands.run(args.command, args.remainder_args)
        if ret:
            print(ret)
    except HdfToolException as exc:
        print('error: {}, {}'.format(exc.error_code, exc.exc_msg))
    except Exception as exc:
        print('error: {}, {}'.format(CommandErrorCode.UNKNOWN_ERROR, str(exc)))


if __name__ == "__main__":
    main()
