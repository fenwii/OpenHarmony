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
from command_line.hdf_command_error_code import CommandErrorCode
import hdf_utils


class HdfManagerConfigFile(object):
    def __init__(self, file_path):
        self.file_path = file_path
        self.file_dir = os.path.dirname(self.file_path)
        self.host_pattern = r'%s\s*::\s*host\s*{'
        self.hdf_manager_pattern = r'device_info\s*{'
        self.contents = ''
        self._read_contents()

    def _read_contents(self):
        if os.path.exists(self.file_path):
            self.contents = hdf_utils.read_file(self.file_path)
        else:
            self.contents = ''

    def check_and_create(self):
        if self.contents:
            return
        template_str = \
            hdf_utils.get_template('hdf_driver_manager_config.template')
        self.contents = Template(template_str).safe_substitute({})
        if not os.path.exists(self.file_dir):
            os.makedirs(self.file_dir)
        hdf_utils.write_file(self.file_path, self.contents)

    def _find_range(self, pattern):
        match_obj = re.search(pattern, self.contents)
        if not match_obj:
            return None
        start = match_obj.start()
        if start == -1:
            return None
        braces = []
        start += len(match_obj.group(0)) - 1
        end = start
        for i in range(start, len(self.contents)):
            if '{' == self.contents[i]:
                braces.append('{')
            elif '}' == self.contents[i]:
                count = len(braces)
                if count == 0:
                    return None
                if count == 1:
                    end = i
                    break
                braces.pop()
        if end != start:
            while end > start + 1:
                end -= 1
                if self.contents[end] not in [' ', '\t']:
                    break
            return hdf_utils.SectionRange(start, end)
        return None

    @staticmethod
    def _begin_end(module, driver):
        dev_id = hdf_utils.get_id(module, driver)
        device_begin = '\n/* <begin %s */\n' % dev_id
        device_end = '\n/* %s end> */\n' % dev_id
        return device_begin, device_end

    def _create_device(self, module, driver):
        drv_converter = hdf_utils.WordsConverter(driver)
        data_model = {
            'driver_lower_case': drv_converter.lower_case(),
            'driver_lower_camel_case': drv_converter.lower_camel_case()
        }
        template_str = \
            hdf_utils.get_template('hdf_driver_manager_config_device.template')
        contents = Template(template_str).safe_substitute(data_model)
        begin, end = self._begin_end(module, driver)
        return hdf_utils.SectionContent(begin, contents, end)

    def _get_host_range(self):
        pattern = self.host_pattern % 'common'
        host_range = self._find_range(pattern)
        if not host_range:
            self.add_host('common')
            self._read_contents()
            host_range = self._find_range(pattern)
        return host_range

    def add_device(self, module, driver):
        device_config = self._create_device(module, driver)
        old_device_range = hdf_utils.find_section(self.contents, device_config)
        if old_device_range:
            hdf_utils.replace_and_save(self.contents, self.file_path,
                                       old_device_range, device_config)
            return
        host_range = self._get_host_range()
        last_brace_range = hdf_utils.SectionRange(host_range.end_pos,
                                                  host_range.end_pos)
        hdf_utils.add_after_and_save(self.contents, self.file_path,
                                     last_brace_range, device_config)

    def delete_device(self, module, driver):
        begin, end = self._begin_end(module, driver)
        empty_device = hdf_utils.SectionContent(begin, '', end)
        old_range = hdf_utils.find_section(self.contents, empty_device)
        if old_range:
            hdf_utils.delete_and_save(self.contents, self.file_path, old_range)

    def _create_host(self, module):
        template_str = \
            hdf_utils.get_template('hdf_driver_manager_config_host.template')
        mod_converter = hdf_utils.WordsConverter(module)
        data_model = {
            'module_lower_case': mod_converter.lower_case()
        }
        host_content = Template(template_str).safe_substitute(data_model)
        begin, end = self._begin_end(module, module)
        return hdf_utils.SectionContent(begin, host_content, end)

    def add_host(self, module):
        manager_range = self._find_range(self.hdf_manager_pattern)
        if not manager_range:
            raise HdfToolException('file: %s format wrong, no hdf_manager node'
                                   ' found' % self.file_path,
                                   CommandErrorCode.FILE_FORMAT_WRONG)
        host_section = self._create_host(module)
        last_brace = hdf_utils.SectionRange(manager_range.end_pos,
                                            manager_range.end_pos)
        hdf_utils.add_after_and_save(self.contents, self.file_path,
                                     last_brace, host_section)

    def delete_host(self, module):
        begin, end = self._begin_end(module, module)
        empty_section = hdf_utils.SectionContent(begin, "", end)
        host_range = hdf_utils.find_section(self.contents, empty_section)
        if not host_range:
            return
        hdf_utils.delete_and_save(self.contents, self.file_path, host_range)
