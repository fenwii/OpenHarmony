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
from string import Template

from .hdf_command_error_code import CommandErrorCode
from hdf_tool_exception import HdfToolException
from hdf_tool_settings import HdfToolSettings
import hdf_utils


class HdfVendorMkFile(object):
    def __init__(self, root, vendor):
        self.vendor = vendor
        self.file_path = hdf_utils.get_vendor_mk_path(root, vendor)
        if not os.path.exists(self.file_path):
            raise HdfToolException('file: %s not exist' % self.file_path,
                                   CommandErrorCode.TARGET_NOT_EXIST)
        self.contents = hdf_utils.read_file(self.file_path)

    def _begin_end(self, module):
        module_id = hdf_utils.get_id(self.vendor, module)
        begin = '\n# <begin %s\n' % module_id
        end = '\n# %s end>\n' % module_id
        return begin, end

    def _create_module(self, module, need_content=True):
        begin, end = self._begin_end(module)
        if not need_content:
            return hdf_utils.SectionContent(begin, '', end)
        vendor_converter = hdf_utils.WordsConverter(self.vendor)
        module_converter = hdf_utils.WordsConverter(module)
        data_model = {
            'module_upper_case': module_converter.upper_case(),
            'module_lower_case': module_converter.lower_case(),
            'vendor_lower_case': vendor_converter.lower_case(),
            'drivers_path': HdfToolSettings().get_drivers_path()
        }
        template_str = hdf_utils.get_template('hdf_vendor_mk_module.template')
        module_item = Template(template_str).safe_substitute(data_model)
        return hdf_utils.SectionContent(begin, module_item, end)

    def add_module(self, module):
        module_ = self._create_module(module)
        old_range = hdf_utils.find_section(self.contents, module_)
        if old_range:
            hdf_utils.replace_and_save(self.contents, self.file_path,
                                       old_range, module_)
            return
        hdf_utils.append_and_save(self.contents, self.file_path, module_)

    def delete_module(self, module):
        module_content = self._create_module(module, False)
        old_range = hdf_utils.find_section(self.contents, module_content)
        if not old_range:
            return
        hdf_utils.delete_and_save(self.contents, self.file_path, old_range)

    def rename_vendor(self):
        pattern = r'vendor/([a-zA-Z0-9_\-]+)/'
        replacement = 'vendor/%s/' % self.vendor
        new_content = re.sub(pattern, replacement, self.contents)
        hdf_utils.write_file(self.file_path, new_content)
