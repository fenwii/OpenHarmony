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

import datetime
import os
import queue
import time
import uuid
from xml.etree import ElementTree

from _core.utils import unique_id
from _core.utils import get_filename_extension
from _core.utils import convert_serial
from _core.utils import get_instance_name
from _core.utils import is_config_str
from _core.utils import check_result_report
from _core.environment.manager_env import EnvironmentManager
from _core.environment.manager_env import DeviceSelectionOption
from _core.exception import ParamError
from _core.exception import DeviceError
from _core.interface import LifeCycle
from _core.executor.request import Request
from _core.executor.request import Task
from _core.executor.request import Descriptor
from _core.plugin import get_plugin
from _core.plugin import Plugin
from _core.plugin import Config
from _core.report.reporter_helper import ExecInfo
from _core.report.reporter_helper import ReportConstant
from _core.report.reporter_helper import Case
from _core.report.reporter_helper import DataHelper
from _core.constants import TestExecType
from _core.constants import DeviceLabelType
from _core.constants import SchedulerType
from _core.constants import HostDrivenTestType
from _core.constants import ListenerType
from _core.executor.concurrent import Concurrent
from _core.executor.concurrent import DriversThread
from _core.executor.concurrent import QueueMonitorThread
from _core.executor.source import TestSetSource
from _core.executor.source import find_test_descriptors
from _core.executor.source import find_testdict_descriptors
from _core.logger import platform_logger
from _core.logger import add_task_file_handler
from _core.logger import remove_task_file_handler

__all__ = ["Scheduler"]
LOG = platform_logger("Scheduler")


@Plugin(type=Plugin.SCHEDULER, id=SchedulerType.scheduler)
class Scheduler(object):
    """
    The Scheduler is the main entry point for client code that wishes to
    discover and execute tests.
    """
    # factory params
    is_execute = True
    terminate_result = queue.Queue()
    upload_address = ""
    task_type = ""
    task_name = ""
    mode = ""

    # command_queue to store test commands
    command_queue = []
    max_command_num = 50
    # the number of tests in current task
    test_number = 0

    def __discover__(self, args):
        """discover task to execute"""
        config = Config()
        config.update(args)
        task = Task(drivers=[])
        task.init(config)

        root_descriptor = self._find_test_root_descriptor(task.config)
        task.set_root_descriptor(root_descriptor)
        return task

    def __execute__(self, task):
        try:
            self._start_task_logcat(task.config.log_path)
            Scheduler.is_execute = True
            if Scheduler.command_queue:
                LOG.debug("Run command: %s" % Scheduler.command_queue[-1])
                run_command = Scheduler.command_queue.pop()
                task_id = str(uuid.uuid1()).split("-")[0]
                Scheduler.command_queue.append((task_id, run_command,
                                                task.config.report_path))
                if len(Scheduler.command_queue) > self.max_command_num:
                    Scheduler.command_queue.pop(0)

            self.test_number = len(task.test_drivers)

            if task.config.exectype == TestExecType.device_test:
                self._device_test_execute(task)
            elif task.config.exectype == TestExecType.host_test:
                self._host_test_execute(task)
            else:
                LOG.info("exec type %s is bypassed" % task.config.exectype)

            if Scheduler.upload_address:
                Scheduler.upload_task_result(task)
                Scheduler.upload_report_end()
        finally:
            self._stop_task_logcat()

    def _device_test_execute(self, task):
        used_devices = {}
        try:
            self._dynamic_concurrent_execute(task, used_devices)
        finally:
            # generate reports
            self._generate_task_report(task, used_devices)

    def _host_test_execute(self, task):
        """execute host test"""
        test_drivers = task.test_drivers
        if not test_drivers:
            raise ParamError("test driver not found")

        params_list = []
        for test_driver in task.test_drivers:
            listeners = self._create_listeners(task)
            params_list.append((listeners, task, [test_driver]))
        try:
            Concurrent.concurrent_execute(self._execute_test_drivers,
                                          params_list, 2)
        finally:
            # generate reports
            self._generate_task_report(task)

    def _generate_task_report(self, task, used_devices=None):
        task_info = ExecInfo()
        test_type = getattr(task, "testtype", [])
        task_name = getattr(task.config, "task", "")
        if task_name:
            task_info.test_type = str(task_name).upper()
        else:
            task_info.test_type = ",".join(
                test_type) if test_type else "Test"
        if used_devices:
            serials = []
            platforms = []
            for serial, device in used_devices.items():
                serials.append(convert_serial(serial))
                platform = str(device.label).capitalize()
                if platform not in platforms:
                    platforms.append(platform)
            task_info.device_name = ",".join(serials)
            task_info.platform = ",".join(platforms)
        else:
            task_info.device_name = "None"
            task_info.platform = "None"
        task_info.test_time = task.config.start_time
        task_info.product_params = getattr(task, "product_params", "")

        listeners = self._create_listeners(task)
        for listener in listeners:
            listener.__ended__(LifeCycle.TestTask, task_info)

    @classmethod
    def _create_listeners(cls, task):
        listeners = []
        # append log listeners
        log_listeners = get_plugin(Plugin.LISTENER, ListenerType.log)
        for log_listener in log_listeners:
            log_listener_instance = log_listener.__class__()
            listeners.append(log_listener_instance)
        # append report listeners
        report_listeners = get_plugin(Plugin.LISTENER, ListenerType.report)
        for report_listener in report_listeners:
            report_listener_instance = report_listener.__class__()
            setattr(report_listener_instance, "report_path",
                    task.config.report_path)
            listeners.append(report_listener_instance)
        # append upload listeners
        upload_listeners = get_plugin(Plugin.LISTENER, ListenerType.upload)
        for upload_listener in upload_listeners:
            upload_listener_instance = upload_listener.__class__()
            listeners.append(upload_listener_instance)
        return listeners

    @staticmethod
    def _find_device_options(environment_config, options, test_source):
        devices_option = []
        for device_dict in environment_config:
            label = device_dict.get("label", "")
            if not label:
                continue
            device_option = DeviceSelectionOption(options, label, test_source)
            device_option.source_file = test_source.config_file or \
                                        test_source.source_string
            devices_option.append(device_option)
        return devices_option

    def __allocate_environment__(self, options, test_driver):
        device_options = self.get_device_options(options,
                                                 test_driver[1].source)
        environment = None
        env_manager = EnvironmentManager()
        while True:
            if not Scheduler.is_execute:
                break
            environment = env_manager.apply_environment(device_options)
            if len(environment.devices) == len(device_options):
                return environment
            else:
                env_manager.release_environment(environment)
                LOG.debug("'%s' is waiting available device",
                          test_driver[1].source.test_name)
                if env_manager.check_device_exist(device_options):
                    continue
                else:
                    raise DeviceError("The '%s' required device does not exist"
                                      % test_driver[1].source.source_file)

        return environment

    @classmethod
    def get_device_options(cls, options, test_source):
        device_options = []
        config_file = test_source.config_file

        from _core.testkit.json_parser import JsonParser
        if test_source.source_string and is_config_str(
                test_source.source_string):
            json_config = JsonParser(test_source.source_string)
            device_options = cls._find_device_options(
                json_config.get_environment(), options, test_source)
        elif config_file and os.path.exists(config_file):
            json_config = JsonParser(test_source.config_file)
            device_options = cls._find_device_options(
                json_config.get_environment(), options, test_source)

        if not device_options:
            if str(test_source.source_file).endswith(".bin"):
                device_option = DeviceSelectionOption(
                    options, DeviceLabelType.ipcamera, test_source)
            else:
                device_option = DeviceSelectionOption(
                    options, None, test_source)
            device_option.source_file = test_source.source_file or \
                                        test_source.source_string
            device_options.append(device_option)
        return device_options

    @staticmethod
    def __free_environment__(environment):
        env_manager = EnvironmentManager()
        env_manager.release_environment(environment)

    def _dynamic_concurrent_execute(self, task, used_devices):
        from xdevice import SuiteReporter

        # initial params
        current_driver_threads = {}
        test_drivers = task.test_drivers
        message_queue = queue.Queue()

        # execute test drivers
        queue_monitor_thread = self._start_queue_monitor(
            message_queue, test_drivers, current_driver_threads)
        while test_drivers:
            # clear remaining test drivers when scheduler is terminated
            if not Scheduler.is_execute:
                LOG.info("clear test drivers")
                self._clear_not_executed(test_drivers, task)
                break

            # get test driver and device
            test_driver = test_drivers[0]

            if getattr(task.config, "history_report_path", "") and \
                    Scheduler.mode == "decc":
                if test_driver[1].source.test_name not in \
                        SuiteReporter.get_failed_case_list():
                    test_drivers.pop(0)
                    self.test_number = self.test_number - 1
                    LOG.info("%s has been passed, test number changes to %s",
                             test_driver[1].source.test_name, self.test_number)
                    continue
                else:
                    SuiteReporter.get_failed_case_list().remove(
                        test_driver[1].source.test_name)

            # get environment
            try:
                environment = self.__allocate_environment__(
                    task.config.__dict__, test_driver)
            except DeviceError as exception:
                self._handle_device_error(exception, task, test_drivers)
                continue

            if not Scheduler.is_execute:
                if environment:
                    Scheduler.__free_environment__(environment)
                continue

            # display executing progress
            self._display_executing_process(environment, test_driver,
                                            test_drivers)

            # add to used devices and set need_kit_setup attribute
            self._append_used_devices(environment, used_devices)

            # start driver thread
            self._start_driver_thread(current_driver_threads, (
                environment, message_queue, task, test_driver))
            test_drivers.pop(0)

        # wait for all drivers threads finished and do kit teardown
        while True:
            if not queue_monitor_thread.is_alive():
                break
            time.sleep(3)
        self._do_taskkit_teardown(task, used_devices)

    def _handle_device_error(self, exception, task, test_drivers):
        error_message = "%s: %s" % \
                        (get_instance_name(exception), exception)
        LOG.exception(error_message, exc_info=False)
        # under "decc" mode ,response device error
        if Scheduler.mode == "decc":
            self._report_not_executed(
                task, test_drivers[1], error_message)
        test_drivers.pop(0)
        self.test_number = self.test_number - 1
        LOG.info("test number changes to %s", self.test_number)

    @classmethod
    def _clear_not_executed(cls, task, test_drivers):
        if Scheduler.mode != "decc":
            # clear all
            test_drivers.clear()
            return
        # The result is reported only in DECC mode, and also clear all.
        error_message = "task execution terminated!"
        cls._report_not_executed(task, test_drivers, error_message)
        test_drivers.clear()

    @classmethod
    def _report_not_executed(cls, task, test_drivers, error_message):
        # traversing list to get remained elements
        for test_driver in test_drivers:
            report_path = task.config.report_path
            report_file = os.path.join(
                report_path, "result",
                "%s.xml" % test_driver[1].source.test_name)
            report_name = test_driver[1].source.test_name if \
                not test_driver[1].source.test_name.startswith("{") \
                else "report"
            # here, normally create empty report and then upload result
            check_result_report(report_path, report_file, error_message,
                                report_name)

    def _start_driver_thread(self, current_driver_threads, thread_params):
        environment, message_queue, task, test_driver = thread_params
        thread_id = self._get_thread_id(current_driver_threads)
        driver_thread = DriversThread(test_driver, task, environment,
                                      message_queue)
        driver_thread.setDaemon(True)
        driver_thread.set_thread_id(thread_id)
        driver_thread.set_listeners(self._create_listeners(task))
        driver_thread.start()
        current_driver_threads.setdefault(thread_id, driver_thread)

    @classmethod
    def _do_taskkit_teardown(cls, task, used_devices):
        for device in used_devices.values():
            if getattr(device, "need_kit_setup", True):
                continue
            for kit in task.config.kits:
                kit.__teardown__(device)
            setattr(device, "need_kit_setup", True)

    def _display_executing_process(self, environment, test_driver,
                                   test_drivers):
        source_content = test_driver[1].source.source_file or \
                         test_driver[1].source.source_string
        LOG.info("[%d / %d] Executing: %s, Device: %s, Driver: %s" %
                 (self.test_number - len(test_drivers) + 1,
                  self.test_number, source_content,
                  environment.__get_serial__(),
                  test_driver[1].source.test_type))

    @classmethod
    def _get_thread_id(cls, current_driver_threads):
        thread_id = datetime.datetime.now().strftime(
            '%Y-%m-%d-%H-%M-%S-%f')
        while thread_id in current_driver_threads.keys():
            thread_id = datetime.datetime.now().strftime(
                '%Y-%m-%d-%H-%M-%S-%f')
        return thread_id

    @classmethod
    def _append_used_devices(cls, environment, used_devices):
        for device in environment.devices:
            device_serial = device.__get_serial__() if device else "None"
            if device_serial and device_serial not in used_devices.keys():
                used_devices[device_serial] = device
                setattr(device, "need_kit_setup", True)

    @staticmethod
    def _start_queue_monitor(message_queue, test_drivers,
                             current_driver_threads):
        queue_monitor_thread = QueueMonitorThread(message_queue,
                                                  current_driver_threads,
                                                  test_drivers)
        queue_monitor_thread.setDaemon(True)
        queue_monitor_thread.start()
        return queue_monitor_thread

    @classmethod
    def _execute_test_drivers(cls, listeners, task, allocated_test_drivers):
        LOG.debug('========= test_drivers count = %s =========' % len(
            allocated_test_drivers))
        for listener in listeners:
            LOG.debug("listener %s" % listener)
        for driver, test in allocated_test_drivers:
            config = Config()
            config.update(task.config.__dict__)
            driver_request = Request(test, listeners, config)
            driver.__execute__(driver_request)

    def exec_command(self, command, options):
        """
        Directly executes a command without adding it to the command queue.
        """
        if command != "run":
            LOG.error("exec_command can only deal with run command")
            raise SystemError("exec_command can only deal with run command")

        try:
            if getattr(options, "test_environment", ""):
                self._reset_environment(options.test_environment)

            exec_type = options.exectype
            if exec_type in [TestExecType.device_test, TestExecType.host_test,
                             TestExecType.host_driven_test]:
                self._exec_task(options)
            else:
                LOG.error("unsupported execution type '%s'" % exec_type)
        finally:
            if getattr(options, "test_environment", ""):
                self._restore_environment()

        return

    def _exec_task(self, options):
        """
        Directly allocates a device and execute a device test.
        """
        task = self.__discover__(options.__dict__)
        self.__execute__(task)

    @classmethod
    def _reset_environment(cls, environment):
        env_manager = EnvironmentManager()
        env_manager.env_stop()
        EnvironmentManager(environment)

    @classmethod
    def _restore_environment(cls):
        env_manager = EnvironmentManager()
        env_manager.env_stop()
        EnvironmentManager()

    @classmethod
    def _start_task_logcat(cls, log_path):
        tool_file_name = "task_log.log"
        tool_log_file = os.path.join(log_path, tool_file_name)
        add_task_file_handler(tool_log_file)

    @classmethod
    def _stop_task_logcat(cls):
        remove_task_file_handler()

    @staticmethod
    def _find_test_root_descriptor(config):
        # read test list from testfile, testlist or task
        if getattr(config, "testfile", "") or getattr(config, "testlist", "") \
                or getattr(config, "task", ""):
            test_set = config.testfile or config.testlist or config.task
            fname, _ = get_filename_extension(test_set)
            uid = unique_id("Scheduler", fname)
            root = Descriptor(uuid=uid, name=fname,
                              source=TestSetSource(test_set), container=True)
            root.children = find_test_descriptors(config)
            return root
        # read test list from testdict
        elif getattr(config, "testdict", "") != "":
            uid = unique_id("Scheduler", "testdict")
            root = Descriptor(uuid=uid, name="testdict",
                              source=TestSetSource(config.testdict),
                              container=True)
            root.children = find_testdict_descriptors(config)
            return root
        else:
            raise ParamError("no test file, list, dict or task found")

    @classmethod
    def terminate_cmd_exec(cls):
        Scheduler.is_execute = False
        LOG.info("start to terminate execution")
        return Scheduler.terminate_result.get()

    @classmethod
    def upload_case_result(cls, upload_param):
        if not Scheduler.upload_address:
            return
        case_id, result, error, start_time, end_time, report_path = \
            upload_param
        if error and len(error) > 150:
            error = "%s..." % error[:150]
        LOG.info(
            "get upload params: %s, %s, %s, %s, %s, %s" % (
                case_id, result, error, start_time, end_time, report_path))
        from agent.factory import upload_result
        upload_result(case_id, result, error, start_time, end_time,
                      report_path)

    @classmethod
    def upload_module_result(cls, exec_message):
        if not Scheduler.is_execute:
            return
        result_file = exec_message.get_result()
        request = exec_message.get_request()

        test_name = request.root.source.test_name
        if not result_file or not os.path.exists(result_file):
            LOG.error("%s result not exists", test_name)
            return

        test_type = request.root.source.test_type
        LOG.info("need upload result: %s, test type: %s, upload address: %s" %
                 (result_file, test_type, Scheduler.upload_address))
        upload_params, _, _ = \
            cls._get_upload_params(result_file, test_type)
        if not upload_params:
            LOG.error("%s no test case result to upload" % result_file)
            return
        for upload_param in upload_params:
            cls.upload_case_result(upload_param)

    @classmethod
    def _get_upload_params(cls, result_file, test_type):
        upload_params = []

        report_path = result_file
        testsuite_element = DataHelper.parse_data_report(report_path)
        start_time, end_time = cls._get_time(testsuite_element)

        if test_type == HostDrivenTestType.device_test:
            for model_element in testsuite_element:
                case_id = model_element.get(ReportConstant.name, "")
                result, error = cls.get_script_result(model_element)
                upload_params.append((case_id, result, error, start_time,
                                      end_time, report_path))
        else:
            for model_element in testsuite_element:
                model_name = model_element.get(ReportConstant.name, "none")
                for case_element in model_element:
                    case_id = cls._get_case_id(case_element, model_name)
                    case_result, error = cls._get_case_result(case_element)
                    upload_params.append(
                        (case_id, case_result, error, start_time,
                         end_time, report_path))
        return upload_params, start_time, end_time

    @classmethod
    def get_script_result(cls, model_element):
        disabled = int(model_element.get(ReportConstant.disabled)) if \
            model_element.get(ReportConstant.disabled, "") else 0
        failures = int(model_element.get(ReportConstant.failures)) if \
            model_element.get(ReportConstant.failures, "") else 0
        errors = int(model_element.get(ReportConstant.errors)) if \
            model_element.get(ReportConstant.errors, "") else 0
        unavailable = int(model_element.get(ReportConstant.unavailable)) if \
            model_element.get(ReportConstant.unavailable, "") else 0
        if failures > 0 or errors > 0:
            result = "Failed"
        elif disabled > 0 or unavailable > 0:
            result = "Unavailable"
        else:
            result = "Passed"

        if result == "Passed":
            return result, ""
        if Scheduler.mode == "decc":
            result = "Failed"

        error_msg = model_element.get(ReportConstant.message, "")
        if not error_msg and len(model_element) > 0:
            error_msg = model_element[0].get(ReportConstant.message, "")
            if not error_msg and len(model_element[0]) > 0:
                error_msg = model_element[0][0].get(ReportConstant.message, "")
        return result, error_msg

    @classmethod
    def _get_case_id(cls, case_element, model_name):
        package_name = case_element.get(ReportConstant.class_name, "none")
        method_name = case_element.get(ReportConstant.name, "none")
        case_id = "{}#{}#{}#{}".format(Scheduler.task_name, model_name,
                                       package_name, method_name)
        return case_id

    @classmethod
    def _get_case_result(cls, case_element):
        # get result
        case = Case()
        case.status = case_element.get(ReportConstant.status, "")
        case.result = case_element.get(ReportConstant.result, "")
        if case_element.get(ReportConstant.message, ""):
            case.message = case_element.get(ReportConstant.message)
        if len(case_element) > 0:
            if not case.result:
                case.result = ReportConstant.false
            case.message = case_element[0].get(ReportConstant.message)
        if case.is_passed():
            result = "Passed"
        elif case.is_failed():
            result = "Failed"
        elif case.is_blocked():
            result = "Blocked"
        else:
            result = "Unavailable"
        return result, case.message

    @classmethod
    def _get_time(cls, testsuite_element):
        start_time = testsuite_element.get(ReportConstant.start_time, "")
        end_time = testsuite_element.get(ReportConstant.end_time, "")
        if start_time and end_time:
            start_time = int(time.mktime(time.strptime(
                start_time, ReportConstant.time_format)) * 1000)
            end_time = int(time.mktime(time.strptime(
                end_time, ReportConstant.time_format)) * 1000)
        else:
            timestamp = str(testsuite_element.get(
                ReportConstant.time_stamp, "")).replace("T", " ")
            cost_time = testsuite_element.get(ReportConstant.time, "")
            if timestamp and cost_time:
                end_time = int(time.mktime(time.strptime(
                    timestamp, ReportConstant.time_format)) * 1000)
                start_time = int(end_time - float(cost_time) * 1000)
            else:
                current_time = int(time.time() * 1000)
                start_time, end_time = current_time, current_time
        return start_time, end_time

    @classmethod
    def upload_task_result(cls, task):
        if not Scheduler.task_name:
            LOG.info("no need upload summary report")
            return

        summary_data_report = os.path.join(task.config.report_path,
                                           ReportConstant.summary_data_report)
        summary_vision_report = os.path.join(
            task.config.report_path, ReportConstant.summary_vision_report)
        if not os.path.exists(summary_data_report):
            Scheduler.upload_unavailable_result("summary report not exists")
            return

        task_element = ElementTree.parse(summary_data_report).getroot()
        start_time, end_time = cls._get_time(task_element)
        task_result = cls._get_task_result(task_element)
        error_msg = ""
        for child in task_element:
            if child.get(ReportConstant.message, ""):
                error_msg = "{}{}".format(
                    error_msg, "%s;" % child.get(ReportConstant.message))
        if error_msg:
            error_msg = error_msg[:-1]
        cls.upload_case_result((Scheduler.task_name, task_result,
                                error_msg, start_time, end_time,
                                summary_vision_report))

    @classmethod
    def _get_task_result(cls, task_element):
        failures = int(task_element.get(ReportConstant.failures, 0))
        errors = int(task_element.get(ReportConstant.errors, 0))
        disabled = int(task_element.get(ReportConstant.disabled, 0))
        unavailable = int(task_element.get(ReportConstant.unavailable, 0))
        if disabled > 0:
            task_result = "Blocked"
        elif errors > 0 or failures > 0:
            task_result = "Failed"
        elif unavailable > 0:
            task_result = "Unavailable"
        else:
            task_result = "Passed"
        return task_result

    @classmethod
    def upload_unavailable_result(cls, error_msg):
        start_time = int(time.time() * 1000)
        LOG.info(
            "get exception upload params: %s, %s, %s, %s, %s, %s" % (
                Scheduler.task_name, "Unavailable",
                error_msg, start_time, start_time, ""))
        Scheduler.upload_case_result((Scheduler.task_name, "Unavailable",
                                      error_msg, start_time, start_time, ""))

    @classmethod
    def upload_report_end(cls):
        from agent.factory import report_end
        LOG.info("upload report end")
        report_end()
