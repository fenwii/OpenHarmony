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


class ConfigItem(object):
    def __init__(self, index, line):
        self.index = index
        self.line = line


class HdfDotConfigFile(object):
    def __init__(self, dot_config_path):
        self.file_path = dot_config_path
        if os.path.exists(dot_config_path):
            self.lines = hdf_utils.read_file_lines(dot_config_path)
            self.dot_config_exist = True
        else:
            self.lines = []
            self.dot_config_exist = False
        self.cache = {}
        self.hdf_item = 'LOSCFG_DRIVERS_HDF'
        self.prefix = 'LOSCFG_'

    def save(self):
        if not self.dot_config_exist:
            return
        with open(self.file_path, 'r+', newline='\n') as file:
            file.truncate()
            file.write(''.join(self.lines))

    def _update_cache(self, item, index, line):
        self.cache[item] = ConfigItem(index, line)

    def _find(self, item):
        if item in self.cache:
            index = self.cache[item].index
            line = self.cache[item].line
            return index, line
        for index, line in enumerate(self.lines):
            item_pattern = r'%s\s*(=|is)' % item
            if re.search(item_pattern, line):
                line_ = line.strip()
                self._update_cache(item, index, line_)
                return index, line_
        return 0, ''

    @staticmethod
    def _is_line_enabled(line):
        if line.strip().startswith('#'):
            return False
        return True

    def _enable(self, item):
        if not item:
            return
        new_line = '%s=y\n' % item
        index, line = self._find(item)
        if line:
            if self._is_line_enabled(line):
                return
            self.lines[index] = new_line
            self._update_cache(item, index, new_line)
            return
        else:
            count = len(self.lines)
            self.lines.append(new_line)
            self._update_cache(item, count, new_line)

    def _disable(self, item):
        if not item:
            return
        new_line = '# %s is not set\n' % item
        index, line = self._find(item)
        if not line:
            return
        if not self._is_line_enabled(line):
            return
        self.lines[index] = new_line
        self._update_cache(item, index, new_line)

    def _is_enabled(self, item):
        if not item:
            return False
        index, line = self._find(item)
        if not line:
            return False
        return self._is_line_enabled(line)

    def _add_prefix(self, item):
        if not item.startswith(self.prefix):
            item = '%s%s' % (self.prefix, item)
        return item

    def is_enabled(self, item, depends_on_item):
        if item:
            item = self._add_prefix(item)
        if depends_on_item:
            depends_on_item = self._add_prefix(depends_on_item)
        if depends_on_item:
            if not self._is_enabled(depends_on_item):
                return False
        return self._is_enabled(item)

    def enable(self, item, depends_on_item):
        if item:
            item = self._add_prefix(item)
        if depends_on_item:
            depends_on_item = self._add_prefix(depends_on_item)
        self._enable(self.hdf_item)
        self._enable(depends_on_item)
        self._enable(item)

    def disable(self, item):
        if item:
            item = self._add_prefix(item)
        self._disable(item)
