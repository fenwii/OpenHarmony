#!/usr/bin/env python3
# coding=utf-8

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

__all__ = ["get_source_code_root_path"]


def is_source_code_root_path(path):
    check_name_list = ["build.sh", "base", "build"]
    for item in check_name_list:
        check_path = os.path.join(path, item)
        if not os.path.exists(check_path):
            return False
    return True


def get_source_code_root_path(path):
    source_code_root_path = path
    while True:
        if source_code_root_path == "":
            break
        if (source_code_root_path == "/" or
                source_code_root_path.endswith(":\\")):
            source_code_root_path = ""
            break
        if is_source_code_root_path(source_code_root_path):
            break
        source_code_root_path = os.path.dirname(source_code_root_path)
    return source_code_root_path
