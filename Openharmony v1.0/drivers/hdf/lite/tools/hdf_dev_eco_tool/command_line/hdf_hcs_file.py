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

import hdf_utils


class HdfHcsFile(object):
    def __init__(self, file_path):
        self.file_path = file_path
        self.file_dir = os.path.dirname(self.file_path)
        if os.path.exists(self.file_path):
            self.lines = hdf_utils.read_file_lines(self.file_path)
        else:
            self.lines = []
        self.line_template = '#include "%s/%s_config.hcs"\n'
        self.line_pattern = r'^\s*#include\s+"%s/%s_config.hcs"'
        self.include_pattern = r'^\s*#include'

    def _save(self):
        if self.lines:
            hdf_utils.write_file(self.file_path, ''.join(self.lines))

    def _find_line(self, pattern):
        for index, line in enumerate(self.lines):
            if re.search(pattern, line):
                return index, line
        return 0, ''

    def _find_last_include(self):
        if not self.lines:
            return 0
        i = len(self.lines) - 1
        while i >= 0:
            line = self.lines[i]
            if re.search(self.include_pattern, line):
                return i + 1
            i -= 1
        return 0

    def _create_makefile(self):
        mk_path = os.path.join(self.file_dir, 'Makefile')
        template_str = hdf_utils.get_template('hdf_hcs_makefile.template')
        hdf_utils.write_file(mk_path, template_str)

    def check_and_create(self):
        if self.lines:
            return
        if not os.path.exists(self.file_dir):
            os.makedirs(self.file_dir)
        self._create_makefile()
        self.lines.append('#include "hdf_manager/manager_config.hcs"\n')
        self._save()

    def add_driver(self, module, driver):
        target_line = self.line_template % (module, driver)
        target_pattern = self.line_pattern % (module, driver)
        idx, line = self._find_line(target_pattern)
        if line:
            self.lines[idx] = target_line
        else:
            pos = self._find_last_include()
            self.lines.insert(pos, target_line)
        self._save()

    def delete_driver(self, module, driver):
        target_pattern = self.line_pattern % (module, driver)
        idx, line = self._find_line(target_pattern)
        if not line:
            return
        self.lines[idx] = ''
        self._save()
