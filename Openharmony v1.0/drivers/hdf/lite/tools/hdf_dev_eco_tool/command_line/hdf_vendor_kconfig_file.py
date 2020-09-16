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

from hdf_tool_settings import HdfToolSettings
import hdf_utils


class HdfVendorKconfigFile(object):
    def __init__(self, root_dir, vendor_name):
        self.root = root_dir
        self.vendor = vendor_name
        self.kconfig_path = \
            hdf_utils.get_vendor_kconfig_path(root_dir, vendor_name)
        if os.path.exists(self.kconfig_path):
            self.lines = hdf_utils.read_file_lines(self.kconfig_path)
        else:
            self.lines = []
        drivers_path = HdfToolSettings().get_drivers_path()
        line_pattern = \
            r'^\s*source\s+"../../(vendor/%s/%s/([a-zA-Z0-9_\-]+)/.*)"' % \
            (vendor_name, drivers_path)
        self.line_re = re.compile(line_pattern)
        self.line_prefix = 'source "../../vendor/%s/%s' % \
                           (vendor_name, drivers_path)

    def _save(self):
        if self.lines:
            hdf_utils.write_file(self.kconfig_path, ''.join(self.lines))

    def get_module_and_config_path(self):
        tuples = []
        for line in self.lines:
            match_obj = self.line_re.search(line)
            if match_obj:
                k_path_raw = match_obj.group(1).replace('/', os.sep)
                k_path = os.path.join(self.root, k_path_raw)
                tuples.append((match_obj.group(2), k_path))
        return tuples

    def _find_line(self, line_part):
        for index, line in enumerate(self.lines):
            if line_part in line:
                return index, line
        return 0, ''

    def add_module(self, module_to_k_path_parts):
        module_k_part = '/'.join(module_to_k_path_parts)
        index, line = self._find_line(module_k_part)
        if line:
            return
        line = '\n%s/%s"\n' % (self.line_prefix, module_k_part)
        if self.lines:
            if self.lines[-1].endswith('\n'):
                line = '%s/%s"\n' % (self.line_prefix, module_k_part)
        self.lines.append(line)
        self._save()

    def delete_module(self, module):
        line_part = '%s/%s' % (self.line_prefix, module)
        index, line = self._find_line(line_part)
        if line:
            self.lines[index] = ''
        self._save()

    def rename_vendor(self, ):
        for i, line in enumerate(self.lines):
            pattern = r'vendor/([a-zA-Z0-9_\-]+)/'
            replacement = 'vendor/%s/' % self.vendor
            self.lines[i] = re.sub(pattern, replacement, line)
        self._save()
