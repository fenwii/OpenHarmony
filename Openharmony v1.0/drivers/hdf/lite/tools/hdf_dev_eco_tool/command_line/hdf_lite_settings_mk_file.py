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
import re

from .hdf_command_error_code import CommandErrorCode
from hdf_tool_exception import HdfToolException
import hdf_utils


class HdfLiteSettingsMkFile(object):
    def __init__(self, root_dir):
        self.root_dir = root_dir
        self.file_path = hdf_utils.get_hdf_lite_settings_mk_path(root_dir)
        if os.path.exists(self.file_path):
            self.lines = hdf_utils.read_file_lines(self.file_path)
        else:
            dir_path = os.path.dirname(self.file_path)
            if not os.path.exists(dir_path):
                os.makedirs(dir_path)
            self.lines = []
        self.line_pattern = r'(%s\s*:=\s*)(.*)'
        self.hdf_vendor_var_name = 'HDF_COMPILE_VENDOR'
        self.board_vendor_path_var_name = 'HDF_SET_BOARD_VENDOR_PATH'

    def _save(self):
        if self.lines:
            hdf_utils.write_file(self.file_path, ''.join(self.lines))

    def _append(self, new_line):
        self.lines.append(new_line)
        self._save()

    def _find_var_line(self, var_name):
        for index, line in enumerate(self.lines):
            if var_name in line:
                return index, line
        return 0, ''

    def _is_vendor_valid(self, vendor_name):
        vendor_hdf_path = \
            hdf_utils.get_vendor_hdf_dir(self.root_dir, vendor_name)
        if os.path.exists(vendor_hdf_path):
            return True
        return False

    def _set_var_value(self, var_name, var_value):
        idx, var_line = self._find_var_line(var_name)
        if var_line:
            self.lines[idx] = re.sub(self.line_pattern % var_name,
                                     r'\g<1>%s' % var_value, var_line)
            self._save()
        else:
            new_line = '\n%s := %s' % (var_name, var_value)
            self._append(new_line)

    def _get_var_value(self, var_name):
        idx, var_line = self._find_var_line(var_name)
        var_value = ''
        if var_line:
            match_obj = re.search(self.line_pattern % var_name, var_line)
            if match_obj:
                var_value = match_obj.group(2)
        return var_value.strip()

    def set_vendor(self, vendor_name):
        if not self._is_vendor_valid(vendor_name):
            raise HdfToolException('vendor: "%s" not exist' % vendor_name,
                                   CommandErrorCode.TARGET_NOT_EXIST)
        self._set_var_value(self.hdf_vendor_var_name, vendor_name)

    def get_vendor(self):
        vendor_name = self._get_var_value(self.hdf_vendor_var_name)
        if self._is_vendor_valid(vendor_name):
            return vendor_name
        return ''

    def set_board_vendor_path(self, board_vendor_path):
        self._set_var_value(self.board_vendor_path_var_name, board_vendor_path)
