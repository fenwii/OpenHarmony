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


def _init_global_config():
    import sys
    import os

    # insert src path for loading xdevice modules
    sys.framework_src_dir = os.path.abspath(
        os.path.dirname(os.path.dirname(__file__)))
    sys.path.insert(0, sys.framework_src_dir)
    sys.framework_root_dir = os.path.abspath(
        os.path.dirname(os.path.dirname(os.path.dirname(__file__))))

    sys.xdevice_dir = os.path.abspath(os.path.join(
        sys.framework_root_dir,
        "..",
        "xdevice",
        "src"))
    sys.path.insert(0, sys.xdevice_dir)

    sys.framework_res_dir = os.path.abspath(os.path.join(
        os.path.dirname(os.path.dirname(__file__)), "core", "resource"))

    sys.exec_dir = sys.framework_root_dir

    from core.common import get_source_code_root_path
    sys.source_code_root_path = get_source_code_root_path(
        sys.framework_root_dir)

_init_global_config()
del _init_global_config
