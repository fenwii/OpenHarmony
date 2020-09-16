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
import hashlib

from hdf_tool_exception import HdfToolException
from hdf_tool_settings import HdfToolSettings


class WordsConverter(object):
    def __init__(self, words_str):
        self.words_str = words_str
        if len(self.words_str) == 0:
            raise HdfToolException('empty words')
        self.words_list = self.split()
        self.upper = '_'.join([w.upper() for w in self.words_list])
        self.lower = '_'.join([w.lower() for w in self.words_list])
        self.upper_camel = ''.join([w.capitalize() for w in self.words_list])
        if len(self.upper_camel) == 1:
            self.lower_camel = self.upper_camel[0].lower()
        else:
            self.lower_camel = '%s%s' % (self.upper_camel[0].lower(),
                                         self.upper_camel[1:])

    def _capital_pos_generator(self):
        count = len(self.words_str)
        for i in range(count):
            if self.words_str[i].isupper():
                yield i
        yield count

    def split(self):
        words_list = []
        capital_split_words = []
        start = 0
        for i in self._capital_pos_generator():
            end = i
            if end != start:
                capital_split_words.append(self.words_str[start:end])
                start = end
        for word in capital_split_words:
            words_list.extend([w for w in word.split('_') if w])
        return words_list

    def upper_case(self):
        return self.upper

    def lower_case(self):
        return self.lower

    def upper_camel_case(self):
        return self.upper_camel

    def lower_camel_case(self):
        return self.lower_camel


class SectionRange(object):
    def __init__(self, start_pos, end_pos):
        self.start_pos = start_pos
        self.end_pos = end_pos


class SectionContent(object):
    def __init__(self, begin_flag, content, end_flag):
        self.begin_flag = begin_flag
        self.content = content
        self.end_flag = end_flag

    def to_str(self):
        return '%s%s%s' % (self.begin_flag, self.content, self.end_flag)


def find_section(file_content, section_content):
    if not file_content or not section_content:
        return None
    start_pos = file_content.find(section_content.begin_flag)
    if start_pos == -1:
        return None
    end_pos = file_content.find(section_content.end_flag)
    if end_pos == -1:
        return None
    return SectionRange(start_pos, end_pos + len(section_content.end_flag) - 1)


def _write_one_section(file_obj, section_content):
    if not file_obj or not section_content:
        return
    file_obj.write(section_content.begin_flag)
    file_obj.write(section_content.content)
    file_obj.write(section_content.end_flag)


def add_before_and_save(file_content, file_path, pos_range, new_section):
    if not file_content or not file_path or not pos_range or not new_section:
        return
    with open(file_path, 'w', newline='\n') as file:
        file.write(file_content[:pos_range.start_pos])
        _write_one_section(file, new_section)
        file.write(file_content[pos_range.start_pos:])


def add_after_and_save(file_content, file_path, pos_range, new_section):
    if not file_content or not file_path or not pos_range or not new_section:
        return
    with open(file_path, 'w', newline='\n') as file:
        file.write(file_content[:pos_range.end_pos + 1])
        _write_one_section(file, new_section)
        if len(file_content) > pos_range.end_pos + 1:
            file.write(file_content[pos_range.end_pos + 1:])


def append_and_save(file_content, file_path, new_section):
    if not file_content or not file_path or not new_section:
        return
    with open(file_path, 'w', newline='\n') as file:
        file.write(file_content)
        _write_one_section(file, new_section)


def delete_and_save(file_content, file_path, delete_range):
    if not file_content or not file_path or not delete_range:
        return
    length = len(file_content)
    with open(file_path, 'w', newline='\n') as file:
        file.write(file_content[:delete_range.start_pos])
        if delete_range.end_pos + 1 < length:
            file.write(file_content[delete_range.end_pos + 1:])


def replace_and_save(file_content, file_path, old_range, new_section):
    if not file_content or not file_path or not old_range or not new_section:
        return
    with open(file_path, 'w', newline='\n') as file:
        file.write(file_content[:old_range.start_pos])
        _write_one_section(file, new_section)
        file.write(file_content[old_range.end_pos + 1:])


def get_id(part1, part2):
    full_name = '%s-%s' % (part1, part2)
    return hashlib.sha256(full_name.encode('utf8')).hexdigest()[:32]


def create_dirs(dir_path):
    if dir_path and not os.path.exists(dir_path):
        try:
            os.makedirs(dir_path)
        except Exception:
            raise HdfToolException('create dirs fail: %s' % dir_path)


def read_file(file_path):
    with open(file_path) as file:
        content = file.read()
    return content


def read_file_lines(file_path):
    with open(file_path) as file:
        lines = file.readlines()
    return lines


def write_file(file_path, content):
    with open(file_path, 'w', newline='\n') as file:
        file.write(content)


def get_framework_lite_dir(root):
    return os.path.join(root, 'drivers', 'hdf', 'lite')


def get_vendor_root_dir(root):
    return os.path.join(root, 'vendor')


def get_vendor_dir(root, vendor):
    return os.path.join(get_vendor_root_dir(root), vendor)


def get_vendor_hdf_dir(root, vendor):
    relative_path = HdfToolSettings().get_drivers_path()
    return os.path.join(get_vendor_dir(root, vendor), relative_path)


def get_vendor_mk_path(root, vendor):
    return os.path.join(get_vendor_hdf_dir(root, vendor), 'hdf_vendor.mk')


def get_module_dir(root, vendor, module):
    return os.path.join(get_vendor_hdf_dir(root, vendor), module)


def get_drv_root_dir(root, vendor, module):
    return os.path.join(get_module_dir(root, vendor, module), 'driver')


def get_drv_dir(root, vendor, module, driver):
    return os.path.join(get_drv_root_dir(root, vendor, module), driver)


def get_drv_src_dir(root, vendor, module, driver):
    return os.path.join(get_drv_dir(root, vendor, module, driver), 'src')


def get_drv_include_dir(root, vendor, module, driver):
    return os.path.join(get_drv_dir(root, vendor, module, driver), 'include')


def get_vendor_kconfig_path(root, vendor):
    hdf_dir = get_vendor_hdf_dir(root, vendor)
    return os.path.join(hdf_dir, 'Kconfig')


def get_module_kconfig_path(root, vendor, module):
    return os.path.join(get_drv_root_dir(root, vendor, module), 'Kconfig')


def get_module_mk_path(root, vendor, module):
    return os.path.join(get_drv_root_dir(root, vendor, module), 'Makefile')


def get_liteos_a_dot_config_path(root):
    return os.path.join(root, 'kernel', 'liteos_a', '.config')


def get_resources_dir():
    cur_dir = os.path.realpath(os.path.dirname(__file__))
    return os.path.join(cur_dir, 'resources')


def get_templates_dir():
    return os.path.join(get_resources_dir(), 'templates')


def get_templates_lite_dir():
    return os.path.join(get_templates_dir(), 'lite')


def get_template(template_name, type_='lite'):
    templates_dir = os.path.join(get_templates_dir(), type_)
    template = os.path.join(templates_dir, template_name)
    with open(template) as file:
        template_str = file.read()
    return template_str


def get_hdf_lite_settings_mk_path(root_dir):
    return os.path.join(get_framework_lite_dir(root_dir),
                        'hdf_lite_settings.mk')


def get_hdf_lite_mk_path(root_dir):
    return os.path.join(get_framework_lite_dir(root_dir),
                        'hdf_lite.mk')


def get_hdf_lite_kconfig_path(root_dir):
    return os.path.join(get_framework_lite_dir(root_dir),
                        'Kconfig')


def is_commented_line(line, comment_start):
    if line.strip().startswith(comment_start):
        return True
    else:
        return False
