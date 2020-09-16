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

import sys
import os
import shutil
from utils import read_json_file
from xml.etree.ElementTree import parse
from utils import remove_path


def is_opensource(bundle):
    """Get opensource infomation from bundle.json."""
    bundle_data = read_json_file(bundle)
    bundle_publish = bundle_data.get('publishAs')
    if not bundle_publish:
        raise Exception('Could not find "publishAs" in {}'.format(bundle))

    if bundle_publish == 'source':
        return True

    return False


def filter_out_code(code_path):
    if not os.path.exists(code_path):
        raise Exception('Could not find code path: {}'.format(code_path))
    shutil.rmtree(code_path)


def get_source_list(tag):
    if tag is None:
        return None

    source_list = []
    for source in tag.iterfind('project'):
        path = source.attrib['path']
        source_list.append(path)

    return source_list


def get_filter_list(xml):
    """Parse the config xml and get selected code path."""
    filter_xml = parse(xml)
    opensource_tag = filter_xml.find('opensource')
    non_opensource_tag = filter_xml.find('non_opensource')

    opensource_list = get_source_list(opensource_tag)
    non_opensource_list = get_source_list(non_opensource_tag)

    return opensource_list, non_opensource_list


def check_ignore(no_commit_msg):
    if no_commit_msg:
        ignore = shutil.ignore_patterns('.git', '.repo')
    else:
        ignore = None

    return ignore


def filter_by_bundle(config, path, no_commit_msg):
    """Filter out code by bundle.json in every code repository."""
    cwd_path = os.getcwd()
    ignore = check_ignore(no_commit_msg)
    shutil.copytree(cwd_path, path, symlinks=False, ignore=ignore)

    for relpath, dirs, files in os.walk(path):
        if config in files:
            full_path = os.path.join(path, relpath, config)
            bundle_path = os.path.normpath(os.path.abspath(full_path))
            if not is_opensource(bundle_path):
                code_path = os.path.join(path, relpath)
                filter_out_code(code_path)


def filter_by_path(config, path, no_commit_msg):
    """Filter out code by the config."""
    if not os.path.exists(config):
        raise Exception("Could not find config: {}".format(config))
    opensouce_list, non_opensource_list = get_filter_list(config)

    # remove target path if exsits
    remove_path(path)
    cwd_path = os.getcwd()
    ignore = check_ignore(no_commit_msg)

    # copy opensource code directly
    if opensouce_list:
        for each in opensouce_list:
            source_path = os.path.join(cwd_path, each)
            dst_path = os.path.join(path, each)
            if os.path.isfile(source_path):
                shutil.copy(source_path, dst_path)
            else:
                try:
                    shutil.copytree(source_path, dst_path, symlinks=False,
                                    ignore=ignore)
                except Exception as e:
                    print(e.args[0])

        if non_opensource_list:
            for source_code in non_opensource_list:
                source_path = os.path.join(path, source_code)
                if os.path.exists(source_path):
                    shutil.rmtree(source_path)
    # copy whole source code to target path and remove selected code in config
    elif non_opensource_list:
        shutil.copytree(cwd_path, path, symlinks=False, ignore=ignore)
        for source_code in non_opensource_list:
            source_path = os.path.join(path, source_code)
            if os.path.exists(source_path):
                shutil.rmtree(source_path)


def code_filter(**kwargs):
    """
    description: Filter out code by config or bundle.json
    param:
        callback_dict: building class, contains the path of config
        or bundle.json
        no_commit_msg: true if remove git message, like .git and .repo
        target_path: target code path after filtering out
    return: NA
    """
    callback_dict = kwargs['callback_dict']
    no_commit_msg = kwargs['no_commit_msg']
    target_path = kwargs['target_path']

    if callback_dict.config is None:
        target_config = 'bundle.json'
        filter_by_bundle(target_config, target_path, no_commit_msg)
    else:
        target_config = callback_dict.config
        filter_by_path(target_config, target_path, no_commit_msg)


if __name__ == "__main__":
    sys.exit(0)
