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

__all__ = [
    "DeviceOsType", "ProductForm", "TestType", "TestExecType",
    "DeviceTestType", "HostTestType", "HostDrivenTestType",
    "SchedulerType", "ListenerType", "ToolCommandType",
    "LogType", "ProtocolType", "ProxyType"
]


class DeviceOsType(object):
    """
    DeviceOsType enumeration
    """
    DEFAULT_OS = "OHOS"
    OTHER_OS = "Others"

    @property
    def default_os_type(self):
        return DeviceOsType.DEFAULT_OS

    @property
    def other_os_type(self):
        return DeviceOsType.OTHER_OS


class ProductForm(object):
    """
    ProductForm enumeration
    """
    PHONE = "phone"
    CAR = "car"
    TELEVISION = "tv"
    WATCH = "watch"

    @property
    def default_phone(self):
        return ProductForm.PHONE

    @property
    def default_watch(self):
        return ProductForm.WATCH


class TestType(object):
    """
    TestType enumeration
    """
    UNIT_TEST = "unittest"
    MST = "moduletest"
    SYSTEM_TEST = "systemtest"
    PERF = "performance"
    SEC = "security"
    RELI = "reliability"
    DST = "distributedtest"
    ALL = "ALL"

    @property
    def default_test_type(self):
        return TestType.ALL

    @property
    def ut_test_type(self):
        return TestType.UNIT_TEST


TEST_TYPE_DICT = {
    "UT": TestType.UNIT_TEST,
    "MST": TestType.MST,
    "ST": TestType.SYSTEM_TEST,
    "PERF": TestType.PERF,
    "SEC": TestType.SEC,
    "RELI": TestType.RELI,
    "DST": TestType.DST,
    "ALL": TestType.ALL,
}


class TestExecType(object):
    """
    TestExecType enumeration according to test execution method
    """
    # A test running on the device
    DEVICE_TEST = "device"
    # A test running on the host (pc)
    HOST_TEST = "host"
    # A test running on the host that interacts with one or more devices.
    HOST_DRIVEN_TEST = "hostdriven"

    @property
    def default_exec_type(self):
        return TestExecType.DEVICE_TEST

    @property
    def host_exec_type(self):
        return TestExecType.HOST_TEST


class DeviceTestType(object):
    """
    DeviceTestType enumeration
    """
    LITE_JUNIT_TEST = "LiteJUnitTest"
    LITE_ICUNIT_TEST = "LiteICUnitTest"
    LITE_CTEST = "LiteCTest"
    LITE_UNIT_TEST = "LiteUnitTest"

    @property
    def default_cpp_type(self):
        return DeviceTestType.LITE_UNIT_TEST

    @property
    def default_c_type(self):
        return DeviceTestType.LITE_CTEST


class HostTestType(object):
    """
    HostTestType enumeration
    """
    HOST_CPP_TEST = "HostCppTest"
    HOST_JAVA_TEST = "HostJavaTest"

    @property
    def default_test_type(self):
        return HostTestType.HOST_CPP_TEST

    @property
    def host_java_test(self):
        return HostTestType.HOST_JAVA_TEST


class HostDrivenTestType(object):
    """
    HostDrivenType enumeration
    """
    CPP_TEST = "CppTest"
    JAVA_TEST = "JavaTest"
    PYTHON_TEST = "PythonTest"

    @property
    def default_driver_type(self):
        return HostDrivenTestType.PYTHON_TEST

    @property
    def java_host_test_driver(self):
        return HostDrivenTestType.JAVA_TEST

    @property
    def cpp_host_test_driver(self):
        return HostDrivenTestType.CPP_TEST


class SchedulerType(object):
    """
    SchedulerType enumeration
    """
    # default scheduler
    SCHEDULER = "Scheduler"
    COMBINATION = "Combination"
    SPLIT = "Split"

    @property
    def default_type(self):
        return SchedulerType.SCHEDULER

    @property
    def combination_type(self):
        return SchedulerType.COMBINATION


class LogType:
    TOOL = "Tool"
    DEVICE = "Device"

    @property
    def tool_log(self):
        return LogType.TOOL

    @property
    def device_log(self):
        return LogType.DEVICE


class ListenerType:
    LOG = "Log"
    REPORT = "Report"

    @property
    def log_listener(self):
        return ListenerType.LOG

    @property
    def report_listener(self):
        return ListenerType.REPORT


class ToolCommandType(object):
    TOOLCMD_KEY_HELP = "help"
    TOOLCMD_KEY_SHOW = "show"
    TOOLCMD_KEY_RUN = "run"
    TOOLCMD_KEY_QUIT = "quit"
    TOOLCMD_KEY_LIST = "list"

    @property
    def run_command(self):
        return ToolCommandType.TOOLCMD_KEY_RUN

    @property
    def help_command(self):
        return ToolCommandType.TOOLCMD_KEY_HELP


class ProtocolType(object):
    USB_PROTOCOL = "usb"
    SERIAL_PROTOCOL = "serial"
    WLAN_PROTOCOL = "wlan"

    @property
    def default_protocol(self):
        return ProtocolType.SERIAL_PROTOCOL

    @property
    def common_protocol(self):
        return ProtocolType.USB_PROTOCOL


class ProxyType(object):
    USB_PROXY = ""
    SERIAL_PROXY = "serial_proxy"
    WLAN_PROXY = "wlan_proxy"

    @property
    def default_proxy(self):
        return ProxyType.SERIAL_PROXY

    @property
    def common_proxy(self):
        return ProxyType.USB_PROXY