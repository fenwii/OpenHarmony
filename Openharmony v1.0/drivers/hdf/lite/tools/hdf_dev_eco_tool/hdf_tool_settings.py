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
import json

from hdf_tool_exception import HdfToolException
from command_line.hdf_command_error_code import CommandErrorCode


def singleton(clazz):
    _instances = {}

    def create_instance():
        if clazz not in _instances:
            _instances[clazz] = clazz()
        return _instances[clazz]
    return create_instance


def get_hdf_tool_settings_path():
    cur_dir = os.path.realpath(os.path.dirname(__file__))
    return os.path.join(cur_dir, 'resources', 'settings.json')


@singleton
class HdfToolSettings(object):
    def __init__(self):
        self.file_path = get_hdf_tool_settings_path()
        self.settings = {}
        if not os.path.exists(self.file_path):
            return
        with open(self.file_path) as file:
            try:
                self.settings = json.load(file)
            except ValueError as exc:
                raise HdfToolException('file: %s format wrong, %s' %
                                       (self.file_path, str(exc)),
                                       CommandErrorCode.FILE_FORMAT_WRONG)
        self.supported_boards_key = 'supported_boards'
        self.drivers_path_key = 'drivers_path_relative_to_vendor'
        self.dot_configs_key = 'dot_configs'
        self.board_path_key = 'board_parent_path'
        self.dot_config_path_key = 'dot_config_path'

    def get_supported_boards(self):
        key = self.supported_boards_key
        if key in self.settings:
            return ','.join(self.settings[key].keys())
        return ''

    def get_board_parent_path(self, board_name):
        key = self.supported_boards_key
        board_entry = {}
        if key in self.settings:
            if board_name in self.settings[key]:
                board_entry = self.settings[key][board_name]
        key = self.board_path_key
        return board_entry.get(key, '')

    def get_drivers_path(self):
        key = self.drivers_path_key
        return self.settings.get(key, 'hdf')

    def get_dot_configs(self, board_name):
        key = self.supported_boards_key
        boards = self.settings.get(key, None)
        if not boards:
            return []
        board = boards.get(board_name, None)
        if not board:
            return []
        dot_config_path = board.get(self.dot_config_path_key, '')
        if not dot_config_path:
            return []
        configs = board.get(self.dot_configs_key, [])
        return [os.path.join(dot_config_path, config) for config in configs]
