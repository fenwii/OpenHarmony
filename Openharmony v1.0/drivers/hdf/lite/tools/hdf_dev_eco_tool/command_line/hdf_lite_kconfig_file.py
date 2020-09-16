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


class HdfLiteKconfigFile(object):
    def __init__(self, root):
        self.file_path = hdf_utils.get_hdf_lite_kconfig_path(root)
        self.orig_exist = False
        if os.path.exists(self.file_path):
            self.lines = hdf_utils.read_file_lines(self.file_path)
            self.orig_exist = True
        else:
            self.lines = []
        self.vendor_pattern = r'source\s+".*/vendor/.*/Kconfig"'
        self.target_pattern_format = r'source\s+".*/vendor/%s/.*/Kconfig"'
        self.target_index = -1

    def _save(self):
        if self.orig_exist:
            hdf_utils.write_file(self.file_path, ''.join(self.lines))

    def _find_all_vendors(self, target_vendor):
        vendors = []
        for index, line in enumerate(self.lines):
            if self.target_index == -1:
                if re.search(self.target_pattern_format % target_vendor, line):
                    self.target_index = index
                    continue
            if re.search(self.vendor_pattern, line):
                vendors.append(index)
        return vendors

    def _comment_other_vendors(self, other_vendors):
        for index in other_vendors:
            if not hdf_utils.is_commented_line(self.lines[index], '#'):
                self.lines[index] = '# %s' % self.lines[index]

    def set_vendor(self, current_vendor):
        other_vendors = self._find_all_vendors(current_vendor)
        self._comment_other_vendors(other_vendors)
        drivers_path = HdfToolSettings().get_drivers_path()
        new_line = 'source "../../vendor/%s/%s/Kconfig"\n' % \
                   (current_vendor, drivers_path)
        if self.target_index != -1:
            self.lines[self.target_index] = new_line
        else:
            pos = len(self.lines) - 1
            while pos > 0 and len(self.lines[pos].strip()) == 0:
                pos -= 1
            pos += 1
            self.lines.insert(pos, new_line)
        self._save()
