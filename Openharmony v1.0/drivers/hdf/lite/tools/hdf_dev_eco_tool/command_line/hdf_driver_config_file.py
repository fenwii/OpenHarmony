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
from string import Template

from .hdf_manager_config_file import HdfManagerConfigFile
from .hdf_hcs_file import HdfHcsFile
from hdf_tool_settings import HdfToolSettings
from hdf_tool_exception import HdfToolException
from command_line.hdf_command_error_code import CommandErrorCode
import hdf_utils


class HdfDriverConfigFile(object):
    def __init__(self, root, board, module, driver, only_path=False):
        self.root = root
        self.board = board
        self.module = module
        self.driver = driver
        bpp = HdfToolSettings().get_board_parent_path(self.board)
        board_path = os.path.join(self.root, bpp, self.board)
        if not os.path.exists(board_path):
            raise HdfToolException('board: %s not exist' % board_path,
                                   CommandErrorCode.TARGET_NOT_EXIST)
        self.config_dir = os.path.join(board_path, 'config')
        self.drv_dir = os.path.join(self.config_dir, self.module)
        self.drv_config_path = os.path.join(self.drv_dir,
                                            '%s_config.hcs' % self.driver)
        if only_path:
            return
        manager_hcs_path = os.path.join(self.config_dir, 'device_info',
                                        'device_info.hcs')
        self.manager_hcs = HdfManagerConfigFile(manager_hcs_path)
        hdf_hcs_path = os.path.join(self.config_dir, 'hdf.hcs')
        self.hdf_hcs = HdfHcsFile(hdf_hcs_path)

    def _check_and_create_common_config(self):
        self.manager_hcs.check_and_create()
        self.hdf_hcs.check_and_create()
        if not os.path.exists(self.drv_dir):
            os.makedirs(self.drv_dir)

    def create_driver(self):
        self._check_and_create_common_config()
        template_str = hdf_utils.get_template('hdf_driver_config.template')
        config_content = Template(template_str).safe_substitute({})
        hdf_utils.write_file(self.drv_config_path, config_content)
        self.manager_hcs.add_device(self.module, self.driver)
        self.hdf_hcs.add_driver(self.module, self.driver)

    def delete_driver(self):
        if not os.path.exists(self.drv_config_path):
            return
        os.remove(self.drv_config_path)
        self.manager_hcs.delete_device(self.module, self.driver)
        self.hdf_hcs.delete_driver(self.module, self.driver)

    def get_drv_config_path(self):
        if os.path.exists(self.drv_config_path):
            return os.path.realpath(self.drv_config_path)
        else:
            return ''
