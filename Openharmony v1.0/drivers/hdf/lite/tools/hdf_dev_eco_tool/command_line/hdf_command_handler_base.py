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

from .hdf_command_error_code import CommandErrorCode
from .hdf_tool_argument_parser import HdfToolArgumentParser
from hdf_tool_exception import HdfToolException
import hdf_utils


class HdfCommandHandlerBase(object):
    def __init__(self):
        self.cmd = 'base'
        self.action_type = 'base_action_type'
        self.handlers = {}
        self.args = {}
        self.parser = HdfToolArgumentParser()

    def run(self):
        self.action_type = self._get_action_type()
        if self.action_type in self.handlers:
            return self.handlers[self.action_type]()
        else:
            raise HdfToolException('unknown action_type: "%s" for "%s" cmd' %
                                   (self.action_type, self.cmd),
                                   CommandErrorCode.INTERFACE_ERROR)

    def _get_action_type(self):
        try:
            return getattr(self.args, 'action_type')
        except AttributeError:
            return ''

    def check_arg_raise_if_not_exist(self, arg):
        try:
            value = getattr(self.args, arg)
            if not value:
                raise AttributeError()
        except AttributeError:
            raise HdfToolException('argument "--%s" is required for "%s" cmd' %
                                   (arg, self.cmd),
                                   CommandErrorCode.INTERFACE_ERROR)

    def _get_arg(self, arg):
        try:
            value = getattr(self.args, arg)
            return value
        except AttributeError:
            return ''

    def get_args(self):
        args = ['vendor_name', 'module_name', 'driver_name', 'board_name']
        ret = [self._get_arg('root_dir')]
        for arg in args:
            value = self._get_arg(arg)
            if value:
                value = hdf_utils.WordsConverter(value).lower_case()
            ret.append(value)
        return tuple(ret)

    @staticmethod
    def check_path_raise_if_not_exist(full_path):
        if not os.path.exists(full_path):
            raise HdfToolException('%s not exist' % full_path,
                                   CommandErrorCode.TARGET_NOT_EXIST)
