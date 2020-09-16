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

from .hdf_add_handler import HdfAddHandler
from .hdf_delete_handler import HdfDeleteHandler
from .hdf_get_handler import HdfGetHandler
from .hdf_set_handler import HdfSetHandler
from .hdf_ping_handler import HdfPingHandler
from .hdf_command_error_code import CommandErrorCode
from hdf_tool_exception import HdfToolException


class HdfToolCommands(object):
    def __init__(self):
        self.commands = {
            'add': HdfAddHandler,
            'delete': HdfDeleteHandler,
            'get': HdfGetHandler,
            'set': HdfSetHandler,
            'ping': HdfPingHandler
        }

    def run(self, cmd, args):
        if cmd in self.commands:
            return self.commands[cmd](args).run()
        else:
            raise HdfToolException('unknown cmd: "%s"' % cmd,
                                   CommandErrorCode.INTERFACE_ERROR)

    def help(self):
        helps = ['command list:']
        for cmd in self.commands.keys():
            helps.append(cmd)
        return ' '.join(helps)
