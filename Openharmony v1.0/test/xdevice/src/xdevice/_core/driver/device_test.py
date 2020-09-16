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

import copy
import os
import sys

from _core.constants import HostDrivenTestType
from _core.constants import DeviceLabelType
from _core.driver.drivers_lite import init_remote_server
from _core.exception import DeviceError
from _core.exception import ParamError
from _core.exception import ReportException
from _core.exception import ExecuteTerminate
from _core.interface import IDriver
from _core.logger import platform_logger
from _core.plugin import Plugin
from _core.testkit.json_parser import JsonParser
from _core.utils import get_config_value
from _core.utils import get_kit_instances
from _core.utils import check_result_report
from _core.report.suite_reporter import SuiteReporter

LOG = platform_logger("DeviceTest")


def start_task(test_file, configs, device, logger):
    from xdevice import Variables
    # insert& devicetest path for loading devicetest module
    devicetest_module = os.path.join(Variables.modules_dir, "_devicetest")
    if os.path.exists(devicetest_module):
        sys.path.insert(1, devicetest_module)

    if configs["testcases_path"]:
        sys.path.insert(1, configs["testcases_path"])

    from _devicetest.devicetest.main import DeviceTest
    device_test = DeviceTest(test_list=test_file, configs=configs,
                             devices=[device], log=logger)
    device_test.run()


def set_up_env(request, source):
    if not source.endswith(".json"):
        source = "%s.json" % source
    json_config = JsonParser(source)
    test_args = get_config_value('xml-output', json_config.get_driver())

    kits = get_kit_instances(json_config, request.config.resource_path,
                             request.config.testcases_path)
    kits_copy = copy.deepcopy(kits)
    from xdevice import Scheduler
    for kit in kits:
        if not Scheduler.is_execute:
            raise ExecuteTerminate()
        kit.__setup__(request.config.device, request=request)
    return test_args, kits, kits_copy


def get_file_list(module_path):
    file_list = []

    if not file_list:
        for test_file in os.listdir(module_path):
            if test_file.endswith(".py") or test_file.endswith(".pyd"):
                file_list.append(os.path.join(
                    module_path, test_file))
        return file_list
    else:
        filter_file_list = []
        for test_file in file_list:
            if (test_file.endswith(".pyd") or test_file.endswith(".py")) and \
                    os.path.exists(os.path.join(module_path, test_file)):
                filter_file_list.append(os.path.join(
                    module_path, test_file))

        return filter_file_list


@Plugin(type=Plugin.DRIVER, id=HostDrivenTestType.device_test)
class DeviceTestDriver(IDriver):
    """
    DeviceTest is a Test that runs a host-driven test on given devices.
    """
    # test driver config
    config = None
    result = ""
    error_message = ""
    py_file = ""

    def __init__(self):
        self.linux_host = ""
        self.linux_directory = ""

    def __check_environment__(self, device_options):
        pass

    def __check_config__(self, config=None):
        del config
        self.py_file = ""

    def __init_nfs_server__(self, request=None):
        return init_remote_server(self, request)

    def __execute__(self, request):
        kits, source = self._parse_request(request)
        configs = dict()
        configs["testargs"] = self.config.testargs or ""
        configs["testcases_path"] = self.config.testcases_path or ""
        configs["request"] = request

        try:
            if self.config.device and self.config.device.label == \
                    DeviceLabelType.ipcamera:
                self.__init_nfs_server__(request=request)
                _, kits, kits_copy = set_up_env(request, source)
                configs["linux_host"] = self.linux_host
                configs["linux_directory"] = self.linux_directory
                configs["kits"] = kits_copy
                self.run_module(request, configs, source)
            elif self.config.device and self.config.device.label == \
                    DeviceLabelType.watch:
                self.run_module(request, configs, source)
            elif self.config.device and self.config.device.label == \
                    DeviceLabelType.phone:
                self.run_module(request, configs, source)
        except (ReportException, ModuleNotFoundError, ExecuteTerminate,
                SyntaxError, ValueError, AttributeError, TypeError,
                KeyboardInterrupt, ParamError) as exception:
            LOG.exception(exception)
            self.error_message = exception

        finally:
            self._handle_finally(kits, request)

    def _handle_finally(self, kits, request):
        from xdevice import Scheduler
        for kit in kits:
            kit.__teardown__(request.config.device)
        if self.config.device.label == \
                DeviceLabelType.ipcamera or self.config.device.label == \
                DeviceLabelType.watch:
            self.config.device.close()
        report_name = request.root.source.test_name if \
            not request.root.source.test_name.startswith("{") \
            else "report"
        if Scheduler.mode != "decc":
            self.result = check_result_report(
                request.config.report_path, self.result, self.error_message,
                report_name)
        else:
            tmp_list = copy.copy(SuiteReporter.get_report_result())
            if os.path.dirname(self.result) not in \
                    [report_path for report_path, _ in tmp_list]:
                if not self.error_message:
                    self.error_message = "An unknown exception occurred " \
                                         "during the execution case"
                self.result = check_result_report(
                    request.config.report_path, self.result,
                    self.error_message, report_name)

    def _parse_request(self, request):
        from xdevice import Variables
        kits = []
        self.config = request.config
        self.config.device = request.config.environment.devices[0]
        if not self.config.device:
            raise DeviceError("no device..........................")
        current_dir = request.config.resource_path if \
            request.config.resource_path else Variables.exec_dir
        if request.root.source.source_file.strip():
            source = os.path.join(current_dir,
                                  request.root.source.source_file.strip())
            LOG.debug("Testfile FilePath: %s" % source)
        else:
            source = request.root.source.source_string.strip()
        self.config.tmp_folder = os.path.join(self.config.report_path,
                                              "temp")
        self.config.tmp_id = str(request.uuid)
        return kits, source

    def run_module(self, request, configs, source):
        json_config = JsonParser(source)
        if request.root.source.source_file.strip():
            folder_name = "task_%s_%s" % (self.config.tmp_id,
                                          request.root.source.test_name)

            tmp_sub_folder = os.path.join(self.config.tmp_folder, folder_name)
            os.makedirs(tmp_sub_folder, exist_ok=True)

            configs["report_path"] = tmp_sub_folder

            self.result = "%s.xml" % os.path.join(tmp_sub_folder, "report")

            module_path = os.path.dirname(source)
            file_list = get_config_value('py_file', json_config.get_driver(),
                                         is_list=True)
            if not file_list:
                file_list = get_file_list(module_path)
        else:
            folder_name = "task_%s_report" % self.config.tmp_id
            tmp_sub_folder = os.path.join(self.config.tmp_folder,
                                          folder_name)
            self.result = "%s.xml" % os.path.join(tmp_sub_folder, "report")

            json_config = JsonParser(source)
            file_list = get_config_value('py_file', json_config.get_driver(),
                                         is_list=True)
        configs["test_name"] = request.root.source.test_name
        configs["execute"] = get_config_value('execute',
                                              json_config.get_driver(), False)

        os.makedirs(tmp_sub_folder, exist_ok=True)
        self._run_devicetest(configs, file_list)

    def _run_devicetest(self, configs, test_file):
        start_task(test_file, configs, self.config.device, LOG)

    def __result__(self):
        return self.result if os.path.exists(self.result) else ""
