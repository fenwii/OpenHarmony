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
import shutil
import glob

from _core.config.config_manager import UserConfigManager
from _core.constants import DeviceTestType
from _core.constants import GTestConst
from _core.constants import DeviceLabelType
from _core.constants import ComType
from _core.constants import ParserType
from _core.driver.parser_lite import ShellHandler
from _core.environment.dmlib_lite import generate_report
from _core.exception import ExecuteTerminate
from _core.exception import ShellCommandUnresponsiveException
from _core.exception import DeviceError
from _core.exception import LiteDeviceExecuteCommandError
from _core.exception import LiteDeviceReadOutputError
from _core.executor.listener import CollectingLiteGTestListener
from _core.executor.listener import TestDescription
from _core.interface import IDriver
from _core.plugin import Plugin
from _core.plugin import get_plugin
from _core.logger import platform_logger
from _core.report.reporter_helper import DataHelper
from _core.testkit.json_parser import JsonParser
from _core.testkit.kit_lite import DeployKit
from _core.utils import get_config_value
from _core.utils import get_kit_instances
from _core.utils import check_result_report
from _core.utils import get_device_log_file
from _core.utils import get_filename_extension
from _core.utils import get_file_absolute_path
from _core.utils import get_test_component_version

__all__ = ["CppTestDriver", "CTestDriver", "init_remote_server"]
LOG = platform_logger("DriversLite")
FAILED_RUN_TEST_ATTEMPTS = 2


def get_nfs_server(request):
    config_manager = UserConfigManager(env=request.config.test_environment)
    remote_info = config_manager.get_user_config("testcases/server",
                                                 filter_name="NfsServer")
    if not remote_info:
        err_msg = "The name of remote nfs server does not match"
        LOG.error(err_msg)
        raise TypeError(err_msg)
    return remote_info


def init_remote_server(lite_instance, request=None):
    config_manager = UserConfigManager(env=request.config.test_environment)
    linux_dict = config_manager.get_user_config("testcases/server")

    # linux ip and replace the ip in commands list on top, which is only
    # the default ip
    if linux_dict:
        setattr(lite_instance, "linux_host", linux_dict.get("ip"))
        setattr(lite_instance, "linux_port", linux_dict.get("port"))
        setattr(lite_instance, "linux_directory", linux_dict.get("dir"))

    else:
        error_message = "nfs server does not exist, please " \
                        "check user_config.xml"
        LOG.error(error_message)
        raise DeviceError(error_message)


def get_execute_command(bin_file, xml_output, device_directory=None):
    if bin_file.startswith("/"):
        bin_file = ".%s" % bin_file
    else:
        bin_file = "./%s" % bin_file

    if xml_output:
        report_path = "/%s/%s/" % ("reports", bin_file.split(".")[0])
        command = "".join((bin_file, " ", "--gtest_output=xml:",
                           device_directory, report_path))
        return command, report_path, True
    else:
        return bin_file, "", False


def get_testcases(testcases_list):
    cases_list = []
    for test in testcases_list:
        test_item = test.split("#")
        if len(test_item) == 1:
            cases_list.append(test)
        elif len(test_item) == 3:
            cases_list.append(test_item[-1])
    return cases_list


def sort_by_length(file_name):
    return len(file_name)


@Plugin(type=Plugin.DRIVER, id=DeviceTestType.cpp_test_lite)
class CppTestDriver(IDriver):
    """
    CppTest is a test that runs a native test package on given lite device.
    """
    config = None
    result = ""
    error_message = ""
    has_param = False

    def __init__(self):
        self.rerun = True
        self.file_name = ""
        self.need_download = False

    def __check_environment__(self, device_options):
        if len(device_options) != 1 or \
                device_options[0].label != DeviceLabelType.ipcamera:
            self.error_message = "check environment failed"
            return False
        return True

    def __check_config__(self, config=None):
        pass

    def __init_nfs_server__(self, request=None):
        return init_remote_server(self, request)

    def is_download(self, testcases_dir):
        from _core.utils import get_local_ip
        if (str(get_local_ip()) == self.linux_host) and (
                self.linux_directory == ("/data%s" % testcases_dir)):
            return False
        return True

    def __execute__(self, request):
        kits = []
        try:
            self.config = request.config
            self.init_cpp_config()
            self.config.device = request.config.environment.devices[0]
            self.__init_nfs_server__(request=request)
            config_file = request.root.source.config_file
            json_config = JsonParser(config_file)
            self._get_driver_config(json_config)

            bin_file = get_config_value('execute', json_config.get_driver(),
                                        False)
            kits = get_kit_instances(json_config,
                                     request.config.resource_path,
                                     request.config.testcases_path)
            from xdevice import Scheduler
            for kit in kits:
                if not Scheduler.is_execute:
                    raise ExecuteTerminate()
                kit.__setup__(request.config.device, request=request)

            execute_dir = "/".join(bin_file.split("/")[0:-1])
            execute_bin = bin_file.split("/")[-1]

            self.config.device.execute_command_with_timeout(
                command="cd {}".format(execute_dir), timeout=1)

            command, report_path, self.has_param = get_execute_command(
                execute_bin, self.config.xml_output, execute_dir)
            self.config.device_xml_path = (self.linux_directory +
                                           report_path).replace("//", "/")
            self.set_file_name(request, command)
            self.need_download = self.is_download(
                request.config.testcases_path)
            if self.need_download and self.has_param:
                self.delete_device_xml(request, self.config.device_xml_path)
            if os.path.exists(self.result):
                os.remove(self.result)
            if request.config.testargs.get("dry_run"):
                self.config.dry_run = request.config.testargs.get(
                    "dry_run")[0].lower()
                self.dry_run(command, request.listeners)
            else:
                self.run_cpp_test(command, request)
                self.generate_device_xml(request, execute_bin)
                device_log_file = get_device_log_file(
                    request.config.report_path,
                    request.config.device.__get_serial__())
                with open(device_log_file, "a", encoding="UTF-8") as file_name:
                    file_name.write(self.config.command_result)

        except (LiteDeviceExecuteCommandError, Exception) as exception:
            LOG.exception(exception)
            self.error_message = exception
        finally:
            LOG.info("-------------finally-----------------")
            self._after_command(kits, request)

    def _get_driver_config(self, json_config):
        xml_output = get_config_value('xml-output',
                                      json_config.get_driver(), False)

        if isinstance(xml_output, bool):
            self.config.xml_output = xml_output
        elif str(xml_output).lower() == "true":
            self.config.xml_output = True
        else:
            self.config.xml_output = False

        rerun = get_config_value('rerun', json_config.get_driver(), False)
        if isinstance(rerun, bool):
            self.rerun = rerun
        elif str(rerun).lower() == "false":
            self.rerun = False
        else:
            self.rerun = True

    def _after_command(self, kits, request):
        self.config.device.execute_command_with_timeout(
            command="cd /", timeout=1)
        for kit in kits:
            kit.__teardown__(request.config.device)
        close_error = self.config.device.close()
        self.error_message = close_error if close_error else \
            "case results are abnormal"
        self.delete_device_xml(request, self.linux_directory)

        report_name = "report" if request.root.source. \
            test_name.startswith("{") else get_filename_extension(
            request.root.source.test_name)[0]
        if not self.config.dry_run:
            self.result = check_result_report(
                request.config.report_path, self.result, self.error_message,
                report_name)

    def generate_device_xml(self, request, execute_bin):
        if self.has_param:
            if self.need_download:
                self.download_nfs_xml(request, self.config.device_xml_path)
                xml_count = 0
                for file_name in os.listdir(os.path.dirname(self.result)):
                    if file_name.startswith(execute_bin):
                        xml_count += 1
                if xml_count > 1:
                    self.merge_xml(execute_bin)
                elif xml_count == 1:
                    self.copy_result(execute_bin)

    def dry_run(self, command, listener=None):
        parsers = get_plugin(Plugin.PARSER, ParserType.cpp_test_list_lite)
        parser_instances = []
        for parser in parsers:
            parser_instance = parser.__class__()
            parser_instance.suites_name = os.path.basename(self.result)
            if listener:
                parser_instance.listeners = listener
            parser_instances.append(parser_instance)
        handler = ShellHandler(parser_instances)

        collect_test_command = "%s --gtest_list_tests" % command.split(" ")[0]
        result, _, _ = self.config.device.execute_command_with_timeout(
            command=collect_test_command,
            case_type=DeviceTestType.cpp_test_lite,
            timeout=5, receiver=handler)
        self.config.command_result = "{}{}".format(
            self.config.command_result, result)
        from xdevice import SuiteReporter
        if parser_instances[0].tests and len(parser_instances[0].tests) > 0:
            SuiteReporter.set_suite_list([item.test_name for item in
                                          parser_instances[0].tests])
        else:
            SuiteReporter.set_suite_list([])

        return parser_instances[0].tests

    def run_cpp_test(self, command, request):
        if request.config.testargs.get("test"):
            testcases_list = get_testcases(
                request.config.testargs.get("test"))
            for test in testcases_list:
                if not self.has_param:
                    command = "{} {}=*{}".format(
                        command, GTestConst.exec_para_filter, test)

                    self.run(command,
                             request.listeners,
                             timeout=15)
                else:
                    self.run(command,
                             None,
                             timeout=15)
        else:
            self._do_test_run(command, request)

    def init_cpp_config(self):
        setattr(self.config, "command_result", "")
        setattr(self.config, "xml_path", "")
        setattr(self.config, "device_xml_path", "")
        setattr(self.config, "dry_run", False)

    def merge_xml(self, execute_bin):
        DataHelper.get_summary_result(os.path.join(
            self.config.report_path, "result"), self.result,
            key=sort_by_length)
        for xml_file in os.listdir(os.path.split(self.result)[0]):
            if not xml_file.startswith(execute_bin):
                continue
            if xml_file != os.path.split(self.result)[1]:
                os.remove(os.path.join(os.path.split(
                    self.result)[0], xml_file))

    def copy_result(self, execute_bin):
        path, _ = os.path.split(self.result)
        for xml_file in os.listdir(path):
            if not xml_file.startswith(execute_bin):
                continue
            device_file = open(os.path.join(path, xml_file), 'r')
            if os.path.exists(self.result):
                os.remove(self.result)
            result_file = open(self.result, "w")
            for line in device_file:
                result_file.write(line)
            device_file.close()
            result_file.close()
            os.remove(os.path.join(path, xml_file))

    def set_file_name(self, request, command):
        if not self.has_param or not self.is_download(
                request.config.testcases_path):
            self.file_name = command.split(" ")[0].split("/")[-1].split(".")[0]
        else:
            self.file_name = command.split(" ")[0].split("/")[-1].split(".")[0]
            self.config.xml_path = "{}/reports/{}.xml".format(
                self.linux_directory, self.file_name).replace("//", "/")
        self.result = "%s.xml" % os.path.join(request.config.report_path,
                                              "result", self.file_name)

    def run(self, command=None, listener=None, timeout=900):
        if listener:
            parsers = get_plugin(Plugin.PARSER, ParserType.cpp_test_lite)
            parser_instances = []
            for parser in parsers:
                parser_instance = parser.__class__()
                parser_instance.suite_name = self.file_name
                parser_instance.listeners = listener
                parser_instances.append(parser_instance)
            handler = ShellHandler(parser_instances)
        else:
            handler = None
        result, _, error = self.config.device.execute_command_with_timeout(
            command=command, case_type=DeviceTestType.cpp_test_lite,
            timeout=timeout, receiver=handler)
        self.config.command_result += result
        return error, result, handler

    def _do_test_run(self, command, request):
        listeners = request.listeners
        test_to_run = self._collect_test_to_run(command)
        if self.has_param and self.need_download:
            listeners = None
        if not test_to_run:
            error, _, _ = self.run(command, listeners, timeout=900)
            if error:
                raise LiteDeviceExecuteCommandError(
                    "execute %s failed" % command)
        else:
            self._run_with_rerun(command, request, test_to_run)

    def _run_with_rerun(self, command, request, expected_tests):
        test_tracker = CollectingLiteGTestListener()

        if self.has_param and self.need_download:
            listener = []
        else:
            listener = request.listeners
        listener_copy = listener.copy()
        listener_copy.append(test_tracker)
        self.run(command, listener_copy, timeout=900)
        test_run = test_tracker.get_current_run_results()
        if len(test_run) != len(expected_tests):
            expected_tests = TestDescription.remove_test(expected_tests,
                                                         test_run)
            self._rerun_tests(command, expected_tests, listener)

    def _rerun_tests(self, command, expected_tests, listener):
        if not expected_tests:
            LOG.debug("No tests to re-run, all tests executed at least once.")
        for test in expected_tests:
            self._re_run(command, test, listener)

    def _re_run(self, command, test, listener):
        handler = None
        for _ in range(FAILED_RUN_TEST_ATTEMPTS):
            try:
                listener_copy = listener.copy()
                test_tracker = CollectingLiteGTestListener()
                listener_copy.append(test_tracker)
                _, _, handler = self.run("{} {}=*{}".format(
                       command, GTestConst.exec_para_filter, test.test_name),
                    listener_copy, timeout=15)
                if len(test_tracker.get_current_run_results()):
                    return
            except ShellCommandUnresponsiveException:
                LOG.debug("Exception: ShellCommandUnresponsiveException")
        handler.parsers[0].mark_test_as_failed(test)

    def _collect_test_to_run(self, command):
        if self.rerun:
            collect_test_command = command.split(" ")[0]
            tests = self.dry_run(collect_test_command)
            return tests
        return None

    def download_nfs_xml(self, request, report_path):
        remote_nfs = get_nfs_server(request)
        if not remote_nfs:
            err_msg = "The name of remote device {} does not match". \
                format(self.remote)
            LOG.error(err_msg)
            raise TypeError(err_msg)
        LOG.info("Trying to pull remote server: {}:{} report files to local "
                 "in dir {}".format
                 (remote_nfs.get("ip"), remote_nfs.get("port"),
                  os.path.dirname(self.result)))
        result_dir = os.path.join(request.config.report_path, "result")
        os.makedirs(result_dir, exist_ok=True)
        try:
            if remote_nfs["remote"] == "true":
                import paramiko
                client = paramiko.Transport((remote_nfs.get("ip"),
                                             int(remote_nfs.get("port"))))
                client.connect(username=remote_nfs.get("username"),
                               password=remote_nfs.get("password"))
                sftp = paramiko.SFTPClient.from_transport(client)
                files = sftp.listdir(report_path)

                for report_xml in files:
                    if report_xml.endswith(".xml"):
                        filepath = report_path + report_xml
                        try:
                            sftp.get(remotepath=filepath,
                                     localpath=os.path.join(os.path.split(
                                         self.result)[0], report_xml))
                        except IOError as error:
                            LOG.error(error)
                client.close()
            else:
                if os.path.isdir(report_path):
                    for report_xml in os.listdir(report_path):
                        if report_xml.endswith(".xml"):
                            filepath = report_path + report_xml
                            shutil.copy(filepath,
                                        os.path.join(os.path.split(
                                            self.result)[0], report_xml))
        except (FileNotFoundError, IOError) as error:
            LOG.error("download xml failed %s" % error)

    def delete_device_xml(self, request, report_path):
        remote_nfs = get_nfs_server(request)
        if not remote_nfs:
            err_msg = "The name of remote device {} does not match". \
                format(self.remote)
            LOG.error(err_msg)
            raise TypeError(err_msg)
        LOG.info("delete xml directory {} from remote server: {}"
                 "".format
                 (report_path, remote_nfs.get("ip")))
        if remote_nfs["remote"] == "true":
            import paramiko
            client = paramiko.Transport((remote_nfs.get("ip"),
                                         int(remote_nfs.get("port"))))
            client.connect(username=remote_nfs.get("username"),
                           password=remote_nfs.get("password"))
            sftp = paramiko.SFTPClient.from_transport(client)
            try:
                sftp.stat(report_path)
                files = sftp.listdir(report_path)
                for report_xml in files:
                    if report_xml.endswith(".xml"):
                        filepath = "{}{}".format(report_path, report_xml)
                        try:
                            sftp.remove(filepath)
                        except IOError:
                            pass
            except FileNotFoundError:
                pass
            client.close()
        else:
            for report_xml in glob.glob(os.path.join(report_path, '*.xml')):
                os.remove(report_xml)

    def __result__(self):
        return self.result if os.path.exists(self.result) else ""


@Plugin(type=Plugin.DRIVER, id=DeviceTestType.ctest_lite)
class CTestDriver(IDriver):
    """
    CTest is a test that runs a native test package on given lite device.
    """
    config = None
    result = ""
    error_message = ""
    version_cmd = "AT+CSV"

    def __init__(self):
        self.file_name = ""

    def __check_environment__(self, device_options):
        if len(device_options) != 1 or \
                device_options[0].label != DeviceLabelType.wifiiot:
            self.error_message = "check environment failed"
            return False
        return True

    def __check_config__(self, config=None):
        del config
        self.config = None

    def __execute__(self, request):
        from xdevice import Variables
        try:
            self.config = request.config
            self.config.device = request.config.environment.devices[0]
            current_dir = request.config.resource_path if \
                request.config.resource_path else Variables.exec_dir
            if request.root.source.source_file.strip():
                source = os.path.join(current_dir,
                                      request.root.source.source_file.strip())
                self.file_name = os.path.basename(
                    request.root.source.source_file.strip()).split(".")[0]
            else:
                source = request.root.source.source_string.strip()

            self._run_ctest(source=source, request=request)

        except (LiteDeviceExecuteCommandError, Exception) as exception:
            LOG.error(exception)
            self.error_message = exception
        finally:
            report_name = "report" if request.root.source. \
                test_name.startswith("{") else get_filename_extension(
                request.root.source.test_name)[0]
            self.result = check_result_report(
                request.config.report_path, self.result, self.error_message,
                report_name)

    def _run_ctest(self, source=None, request=None):
        parser_instances = []
        parsers = get_plugin(Plugin.PARSER, ParserType.ctest_lite)
        result = "Execute command error"
        try:
            if not source:
                LOG.error("Error: source don't exist %s." % source)
                return
            if not self.config.device.local_device:
                LOG.error(
                    "CTest must have a local device, please check "
                    "your config.")
                return

            reset_cmd = self._reset_device(request, source)
            self.result = "%s.xml" % os.path.join(
                request.config.report_path, "result", self.file_name)
            self.config.device.local_device.com_dict.get(
                ComType.deploy_com).connect()
            result, _, error = self.config.device.local_device. \
                execute_command_with_timeout(
                    command=reset_cmd, case_type=DeviceTestType.ctest_lite,
                    key=ComType.deploy_com,
                    timeout=90)
            device_log_file = get_device_log_file(request.config.report_path,
                                                  request.config.device.
                                                  __get_serial__())
            with open(device_log_file, "a", encoding="UTF-8") as file_name:
                file_name.write("{}{}".format(
                    "\n".join(result.split("\n")[0:-1]), "\n"))
            if error:
                raise LiteDeviceReadOutputError(error)
        except (LiteDeviceExecuteCommandError, Exception) as exception:
            LOG.error(exception)
            self.error_message = exception
        finally:
            close_error = self.config.device.local_device.com_dict.get(
                ComType.deploy_com).close()
            if close_error:
                self.error_message = close_error

        version = get_test_component_version(self.config)

        for parser in parsers:
            parser_instance = parser.__class__()
            parser_instance.suites_name = self.file_name
            parser_instance.product_params.setdefault("Version", version)
            parser_instance.listeners = request.listeners
            parser_instances.append(parser_instance)
        handler = ShellHandler(parser_instances)
        generate_report(handler, result)

    def _reset_device(self, request, source):
        json_config = JsonParser(source)
        reset_cmd = []
        kit_instances = get_kit_instances(json_config,
                                          request.config.resource_path,
                                          request.config.testcases_path)
        from xdevice import Scheduler
        for (kit_instance, kit_info) in zip(kit_instances,
                                            json_config.get_kits()):
            if not isinstance(kit_instance, DeployKit):
                continue
            if not self.file_name:
                self.file_name = get_config_value(
                    'burn_file', kit_info)[0].split("\\")[-1].split(".")[0]
            reset_cmd = kit_instance.burn_command
            if not Scheduler.is_execute:
                raise ExecuteTerminate()
            setup_result = kit_instance.__setup__(
                self.config.device.local_device)
            if not setup_result:
                raise DeviceError("set_up wifiiot failed")
        reset_cmd = [int(item, 16) for item in reset_cmd]
        return reset_cmd

    def __result__(self):
        return self.result if os.path.exists(self.result) else ""


@Plugin(type=Plugin.DRIVER, id=DeviceTestType.open_source_test)
class OpenSourceTestDriver(IDriver):
    """
    OpenSourceTest is a test that runs a native test package on given
    device lite device.
    """
    config = None
    result = ""
    error_message = ""
    has_param = False

    def __init__(self):
        self.rerun = True
        self.file_name = ""
        self.handler = None

    def __check_environment__(self, device_options):
        if len(device_options) != 1 or \
                device_options[0].label != DeviceLabelType.ipcamera:
            self.error_message = "check environment failed"
            return False
        return True

    def __check_config__(self, config=None):
        pass

    def __init_nfs_server__(self, request=None):
        return init_remote_server(self, request)

    def __execute__(self, request):
        kits = []
        try:
            self.config = request.config
            setattr(self.config, "command_result", "")
            self.config.device = request.config.environment.devices[0]
            self.__init_nfs_server__(request=request)
            config_file = request.root.source.config_file
            json_config = JsonParser(config_file)
            pre_cmd = get_config_value('pre_cmd', json_config.get_driver(),
                                       False)
            execute_dir = get_config_value('execute', json_config.get_driver(),
                                           False)
            kits = get_kit_instances(json_config,
                                     request.config.resource_path,
                                     request.config.testcases_path)
            from xdevice import Scheduler
            for kit in kits:
                if not Scheduler.is_execute:
                    raise ExecuteTerminate()
                copy_list = kit.__setup__(request.config.device,
                                          request=request)

            self.file_name = request.root.source.test_name
            self.set_file_name(request, request.root.source.test_name)
            self.config.device.execute_command_with_timeout(
                command=pre_cmd, timeout=0.5)
            self.config.device.execute_command_with_timeout(
                command="cd {}".format(execute_dir), timeout=1)
            for test_bin in copy_list:
                if not test_bin.endswith(".run-test"):
                    continue
                command, _, _ = get_execute_command(test_bin, False)
                self._do_test_run(command, request)
            device_log_file = get_device_log_file(
                request.config.report_path,
                request.config.device.__get_serial__())
            with open(device_log_file, "a", encoding="UTF-8") as file_name:
                file_name.write(self.config.command_result)

        except (LiteDeviceExecuteCommandError, Exception) as exception:
            LOG.error(exception)
            self.error_message = exception
        finally:
            LOG.info("-------------finally-----------------")
            # umount the dirs already mount
            for kit in kits:
                kit.__teardown__(request.config.device)
            close_error = self.config.device.close()
            self.error_message = close_error if close_error else\
                "case results are abnormal"
            report_name = "report" if request.root.source. \
                test_name.startswith("{") else get_filename_extension(
                    request.root.source.test_name)[0]
            self.result = check_result_report(
                request.config.report_path, self.result, self.error_message,
                report_name)

    def set_file_name(self, request, bin_file):
        self.result = "%s.xml" % os.path.join(
            request.config.report_path, "result", bin_file)

    def run(self, command=None, listener=None, timeout=20):
        parsers = get_plugin(Plugin.PARSER,
                             ParserType.open_source_test)
        parser_instances = []
        for parser in parsers:
            parser_instance = parser.__class__()
            parser_instance.suite_name = self.file_name
            parser_instance.test_name = command.replace("./", "")
            parser_instance.listeners = listener
            parser_instances.append(parser_instance)
        self.handler = ShellHandler(parser_instances)
        result, _, error = self.config.device.execute_command_with_timeout(
            command=command, case_type=DeviceTestType.open_source_test,
            timeout=timeout, receiver=self.handler)
        self.config.command_result = "{}{}".format(
            self.config.command_result, result)
        return error, result, self.handler

    def _do_test_run(self, command, request):
        listeners = request.listeners
        for listener in listeners:
            listener.device_sn = self.config.device.device_sn
        error, _, _ = self.run(command, listeners, timeout=20)
        if error:
            LOG.error(
                "execute %s failed" % command)

    def __result__(self):
        return self.result if os.path.exists(self.result) else ""
