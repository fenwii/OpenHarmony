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

from hdf_tool_exception import HdfToolException
from .hdf_command_error_code import CommandErrorCode
import hdf_utils


class HdfModuleMkFile(object):
    def __init__(self, root, vendor, module):
        self.module = module
        self.file_path = hdf_utils.get_module_mk_path(root, vendor, module)
        if os.path.exists(self.file_path):
            self.contents = hdf_utils.read_file(self.file_path)
        else:
            self.contents = ''

    def _begin_end(self, driver):
        driver_id = hdf_utils.get_id(self.module, driver)
        begin = '\n# <begin %s\n' % driver_id
        end = '\n# %s end>\n' % driver_id
        return begin, end

    def _create_driver_item(self, driver):
        drv_converter = hdf_utils.WordsConverter(driver)
        data_model = {
            'driver_upper_case': drv_converter.upper_case(),
            'driver_lower_case': drv_converter.lower_case()
        }
        template_str = hdf_utils.get_template('hdf_module_mk_driver.template')
        content = Template(template_str).safe_substitute(data_model)
        begin_flag, end_flag = self._begin_end(driver)
        return hdf_utils.SectionContent(begin_flag, content, end_flag)

    def add_driver(self, driver):
        drv_section = self._create_driver_item(driver)
        old_range = hdf_utils.find_section(self.contents, drv_section)
        if old_range:
            hdf_utils.replace_and_save(self.contents, self.file_path,
                                       old_range, drv_section)
            return
        tail_pattern = r'include\s+\$\(HDF_DRIVER\)'
        replacement = '%sinclude $(HDF_DRIVER)' % drv_section.to_str()
        new_content, count = re.subn(tail_pattern, replacement, self.contents)
        if count != 1:
            raise HdfToolException('Makefile: %s has more than one include'
                                   ' $(HDF_DRIVER)' % self.file_path,
                                   CommandErrorCode.FILE_FORMAT_WRONG)
        hdf_utils.write_file(self.file_path, new_content)

    def delete_driver(self, driver):
        begin_flag, end_flag = self._begin_end(driver)
        empty_content = hdf_utils.SectionContent(begin_flag, '', end_flag)
        drv_range = hdf_utils.find_section(self.contents, empty_content)
        if drv_range:
            hdf_utils.delete_and_save(self.contents, self.file_path, drv_range)
