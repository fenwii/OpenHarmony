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

from command_line.hdf_command_line_server import HdfCommandLineServer
from hdf_tool_exception import HdfToolException


class HdfToolDaemonServer(object):
    def __init__(self, server_type):
        self.server_type = server_type
        self.servers = {
            'command_line': HdfCommandLineServer
        }
        self.read_obj = sys.stdin.buffer
        self.write_obj = sys.stdout.buffer

    def run(self):
        if self.server_type in self.servers:
            self.servers[self.server_type](self.read_obj, self.write_obj).run()
        else:
            raise HdfToolException('unknown type: %s' % self.server_type)
