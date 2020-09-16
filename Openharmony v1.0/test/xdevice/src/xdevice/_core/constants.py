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

__all__ = ["DeviceOsType", "ProductForm", "TestType", "TestExecType",
           "DeviceTestType", "HostTestType", "HostDrivenTestType",
           "SchedulerType", "ListenerType", "ToolCommandType",
           "TEST_DRIVER_SET", "LogType", "ParserType", "CKit", "ComType",
           "DeviceLabelType", "DeviceLiteKernel", "GTestConst", "ManagerType"]


@dataclass
class DeviceOsType(object):
    """
    DeviceOsType enumeration
    """
    default = "default"
    lite = "lite"


@dataclass
class ProductForm(object):
    """
    ProductForm enumeration
    """
    phone = "phone"
    car = "car"
    television = "tv"
    watch = "watch"


@dataclass
class TestType(object):
    """
    TestType enumeration
    """
    unittest = "unittest"
    mst = "moduletest"
    systemtest = "systemtest"
    perf = "performance"
    sec = "security"
    reli = "reliability"
    dst = "distributedtest"
    all = "ALL"


@dataclass
class ComType(object):
    """
    ComType enumeration
    """
    cmd_com = "cmd"
    deploy_com = "deploy"


@dataclass
class DeviceLabelType(object):
    """
    DeviceLabelType enumeration
    """
    wifiiot = "wifiiot"
    ipcamera = "ipcamera"
    watch = "watch"
    phone = "phone"


@dataclass
class DeviceLiteKernel(object):
    """
    Lite device os enumeration
    """
    linux_kernel = "linux"
    lite_kernel = "lite"


TEST_TYPE_DICT = {
    "UT": TestType.unittest,
    "MST": TestType.mst,
    "ST": TestType.systemtest,
    "PERF": TestType.perf,
    "SEC": TestType.sec,
    "RELI": TestType.reli,
    "DST": TestType.dst,
    "ALL": TestType.all,
}


@dataclass
class TestExecType(object):
    """
    TestExecType enumeration according to test execution method
    """
    # A test running on the device
    device_test = "device"
    # A test running on the host (pc)
    host_test = "host"
    # A test running on the host that interacts with one or more devices.
    host_driven_test = "hostdriven"


@dataclass
class DeviceTestType(object):
    """
    DeviceTestType enumeration
    """
    cpp_test = "CppTest"
    dex_test = "DexTest"
    hap_test = "HapTest"
    junit_test = "JUnitTest"
    jsunit_test = "JSUnitTest"
    ctest_lite = "CTestLite"
    cpp_test_lite = "CppTestLite"
    lite_cpp_test = "LiteUnitTest"
    open_source_test = "OpenSourceTest"


@dataclass
class HostTestType(object):
    """
    HostTestType enumeration
    """
    host_gtest = "HostGTest"
    host_junit_test = "HostJUnitTest"


@dataclass
class HostDrivenTestType(object):
    """
    HostDrivenType enumeration
    """
    device_test = "DeviceTest"


TEST_DRIVER_SET = {
    DeviceTestType.cpp_test,
    DeviceTestType.dex_test,
    DeviceTestType.hap_test,
    DeviceTestType.junit_test,
    DeviceTestType.jsunit_test,
    DeviceTestType.cpp_test_lite,
    DeviceTestType.ctest_lite,
    DeviceTestType.lite_cpp_test,
    HostDrivenTestType.device_test
}


@dataclass
class SchedulerType(object):
    """
    SchedulerType enumeration
    """
    # default scheduler
    scheduler = "Scheduler"


@dataclass
class LogType:
    tool = "Tool"
    device = "Device"


@dataclass
class ListenerType:
    log = "Log"
    report = "Report"
    upload = "Upload"
    collect = "Collect"
    collect_lite = "CollectLite"


@dataclass
class ParserType:
    ctest_lite = "CTestLite"
    cpp_test_lite = "CppTestLite"
    cpp_test_list_lite = "CppTestListLite"
    open_source_test = "OpenSourceTest"


@dataclass
class ManagerType:
    device = "device"
    lite_device = "device_lite"


@dataclass
class ToolCommandType(object):
    toolcmd_key_help = "help"
    toolcmd_key_show = "show"
    toolcmd_key_run = "run"
    toolcmd_key_quit = "quit"
    toolcmd_key_list = "list"


@dataclass
class CKit:
    push = "PushKit"
    install = "ApkInstallKit"
    command = "CommandKit"
    config = "ConfigKit"
    wifi = "WIFIKit"
    propertycheck = 'PropertyCheckKit'
    sts = 'STSKit'
    shell = "ShellKit"
    deploy = 'DeployKit'
    mount = 'MountKit'
    liteuikit = 'LiteUiKit'
    rootfs = "RootFsKit"
    query = "QueryKit"


@dataclass
class GTestConst(object):
    exec_para_filter = "--gtest_filter"
    exec_para_level = "--gtest_testsize"
