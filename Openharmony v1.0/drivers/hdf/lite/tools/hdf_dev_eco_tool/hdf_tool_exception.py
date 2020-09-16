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

from command_line.hdf_command_error_code import CommandErrorCode


class HdfToolException(Exception):
    def __init__(self, msg, error_code=CommandErrorCode.UNKNOWN_ERROR):
        super(HdfToolException, self).__init__(msg)
        self.error_code = error_code
        self.exc_msg = msg
