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


class ParamError(Exception):
    def __init__(self, error_msg):
        super().__init__()
        self.error_msg = error_msg

    def __str__(self):
        return "ParamError: %s" % self.error_msg


class LiteDeviceConnectError(Exception):
    def __init__(self, error_msg):
        super().__init__()
        self.error_msg = error_msg

    def __str__(self):
        return "LiteDeviceConnectError: %s" % self.error_msg


class DeviceNotExistError(Exception):
    def __init__(self, error_msg):
        super().__init__()
        self.error_msg = error_msg

    def __str__(self):
        return "DeviceNotExistError: %s" % self.error_msg


class DeviceCommandRejectedException(Exception):
    """
    Exception thrown when device refuses a command.
    """
    def __init__(self, value):
        super().__init__()
        self.value = value

    def __str__(self):
        return "DeviceCommandRejectedException: %s" % self.value


class ShellCommandUnresponsiveException(Exception):
    """
    Exception thrown when a shell command executed on a device takes
    too long to send its output.
    """
    def __str__(self):
        return "ShellCommandUnresponsiveException"
