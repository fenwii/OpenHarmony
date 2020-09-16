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

__all__ = ["get_source_code_rootpath"]


def is_source_code_rootpath(path):
    check_name_list = ["build.sh", "base", "build"]
    for item in check_name_list:
        check_path = os.path.join(path, item)
        if not os.path.exists(check_path):
            return False
    return True


def get_source_code_rootpath(path):
    source_code_rootpath = path
    while True:
        if source_code_rootpath == "":
            break
        if source_code_rootpath == "/" or source_code_rootpath.endswith(":\\"):
            source_code_rootpath = ""
            break
        if is_source_code_rootpath(source_code_rootpath):
            break
        source_code_rootpath = os.path.dirname(source_code_rootpath)
    return source_code_rootpath
