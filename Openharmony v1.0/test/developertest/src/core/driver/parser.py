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

from dataclasses import dataclass
from enum import Enum

__all__ = ["CaseResult", "SuiteResult", "ResultCode"]


class ResultCode(Enum):
    UNKNOWN = -1010
    SUCCESS = 0
    FAILED = 1
    SKIPPED = 2


@dataclass
class CaseResult:
    case_id = ""
    code = ResultCode.UNKNOWN.value
    test_name = None
    test_class = None
    stacktrace = ""
    run_time = 0
    is_completed = False

    def is_running(self):
        return self.test_name is not None and not self.is_completed


@dataclass
class SuiteResult:
    suite_id = ""
    code = ResultCode.UNKNOWN.value
    suite_name = None
    test_num = 0
    stacktrace = ""
    run_time = 0
    is_completed = False


