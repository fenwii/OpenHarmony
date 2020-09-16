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
import threading
import time
from concurrent.futures import ThreadPoolExecutor
from concurrent.futures import wait

from _core.executor.request import Request
from _core.logger import platform_logger
from _core.plugin import Config
from _core.utils import get_instance_name

LOG = platform_logger("Concurrent")


class Concurrent:
    @classmethod
    def executor_callback(cls, worker):
        worker_exception = worker.exception()
        if worker_exception:
            LOG.error("Worker return exception: {}".format(worker_exception))

    @classmethod
    def concurrent_execute(cls, func, params_list, max_size=8):
        """
        Provider the ability to execute target function concurrently
        :param func: target function name
        :param params_list: the list of params in these target functions
        :param max_size:  the max size of thread  you wanted  in thread pool
        :return:
        """
        with ThreadPoolExecutor(max_size) as executor:
            future_params = dict()
            for params in params_list:
                future = executor.submit(func, *params)
                future_params.update({future: params})
                future.add_done_callback(cls.executor_callback)
            wait(future_params)  # wait all function complete
            result_list = []
            for future in future_params:
                result_list.append((future.result(), future_params[future]))
            return result_list


class DriversThread(threading.Thread):
    def __init__(self, test_driver, task, environment, message_queue):
        threading.Thread.__init__(self)
        self.test_driver = test_driver
        self.listeners = None
        self.task = task
        self.environment = environment
        self.message_queue = message_queue
        self.thread_id = None
        self.error_message = ""

    def set_listeners(self, listeners):
        self.listeners = listeners
        for listener in listeners:
            listener.device_sn = self.environment.devices[0].device_sn

    def set_thread_id(self, thread_id):
        self.thread_id = thread_id

    def run(self):
        from xdevice import Scheduler
        LOG.debug("thread id: %s start" % self.thread_id)
        execute_message = ExecuteMessage('', self.environment,
                                         self.test_driver, self.thread_id)
        driver, test = None, None
        try:
            if self.test_driver and Scheduler.is_execute:
                # construct params
                driver, test = self.test_driver
                driver_request = self._get_driver_request(test,
                                                          execute_message)
                if driver_request is None:
                    return

                # setup device
                self._do_task_setup(driver_request)

                # driver execute
                driver.__check_config__(driver_request.config)
                driver.__execute__(driver_request)

        except Exception as exception:
            LOG.exception(
                "device: %s, exception: %s" % (
                    self.environment.__get_serial__(), exception.args))
            self.error_message = "{}: {}".format(
                get_instance_name(exception), str(exception.args))

        finally:
            if driver and test:
                execute_result = driver.__result__()
                if getattr(self.task.config, "history_report_path", ""):
                    execute_result = self._inherit_execute_result(
                        execute_result, test)
                execute_message.set_result(execute_result)

            if self.error_message:
                execute_message.set_state(ExecuteMessage.DEVICE_ERROR)
            else:
                execute_message.set_state(ExecuteMessage.DEVICE_FINISH)
            LOG.debug("put thread %s result", self.thread_id)
            self.message_queue.put(execute_message)

            LOG.debug("thread %s free environment",
                      execute_message.get_thread_id())
            Scheduler.__free_environment__(
                execute_message.get_environment())
            LOG.info("")

    def _do_task_setup(self, driver_request):
        from xdevice import Scheduler
        for device in self.environment.devices:
            if getattr(device, "need_kit_setup", True):
                for kit in self.task.config.kits:
                    if not Scheduler.is_execute:
                        break
                    kit.__setup__(device, request=driver_request)
                setattr(device, "need_kit_setup", False)

        if getattr(driver_request, "product_params", "") and not getattr(
                self.task, "product_params", ""):
            product_params = getattr(driver_request, "product_params")
            if not isinstance(product_params, dict):
                LOG.warning("product params should be dict, %s",
                            product_params)
                return
            setattr(self.task, "product_params", product_params)

    def _get_driver_request(self, root_desc, execute_message):
        config = Config()
        config.update(self.task.config.__dict__)
        config.environment = self.environment
        if getattr(config, "history_report_path", ""):
            # modify config.testargs
            history_report_path = getattr(config, "history_report_path", "")
            unpassed_test_params = self._get_unpassed_test_params(
                history_report_path, root_desc)
            if not unpassed_test_params:
                LOG.info("%s all test cases are passed, no need retry",
                         root_desc.source.test_name)
                driver_request = Request(self.thread_id, root_desc,
                                         self.listeners, config)
                execute_message.set_request(driver_request)
                return None
            test_args = getattr(config, "testargs", {})
            test_params = []
            for unpassed_test_param in unpassed_test_params:
                if unpassed_test_param not in test_params:
                    test_params.append(unpassed_test_param)
            test_args["test"] = test_params
            if "class" in test_args.keys():
                test_args.pop("class")
            setattr(config, "testargs", test_args)

        for listener in self.listeners:
            LOG.debug("thread id %s, listener %s" % (
                self.thread_id, listener))
        driver_request = Request(self.thread_id, root_desc, self.listeners,
                                 config)
        execute_message.set_request(driver_request)
        return driver_request

    def _get_unpassed_test_params(self, history_report_path, root_desc):
        from xdevice import Scheduler
        if Scheduler.mode == "decc":
            return self._get_decc_unpassed_params(root_desc)

        unpassed_test_params = []
        # get target_report_file
        history_report_file = ""
        report_file_suffix = "%s.xml" % root_desc.source.test_name
        for root_dir, _, files in os.walk(history_report_path):
            for report_file in files:
                if report_file.endswith(report_file_suffix):
                    history_report_file = os.path.abspath(
                        os.path.join(root_dir, report_file))
                    break
        if not history_report_file:
            return unpassed_test_params

        # append unpassed_test_param
        self._append_unpassed_test_param(history_report_file,
                                         unpassed_test_params)
        LOG.debug("get unpassed test params %s", unpassed_test_params)
        return unpassed_test_params

    @classmethod
    def _get_decc_unpassed_params(cls, root_desc):
        from xdevice import SuiteReporter
        from _core.report.reporter_helper import DataHelper
        from _core.report.reporter_helper import ReportConstant

        if not SuiteReporter.get_report_result():
            LOG.warning("decc retry command no previous result")
            return []
        summary_result = SuiteReporter.get_report_result()[0][1]
        summary_element = DataHelper.parse_data_report(summary_result)
        for child in summary_element:
            if child.get(ReportConstant.module) == root_desc.source.test_name:
                return []
        return [root_desc.source.test_name]

    @classmethod
    def _append_unpassed_test_param(cls, history_report_file,
                                    unpassed_test_params):
        from _core.report.reporter_helper import DataHelper
        from _core.report.reporter_helper import Suite
        testsuites_element = DataHelper.parse_data_report(history_report_file)
        for testsuite_element in testsuites_element:
            suite_name = testsuite_element.get("name", "")
            suite = Suite()
            suite.set_cases(testsuite_element)
            for case in suite.cases:
                if case.is_passed():
                    continue
                unpassed_test_param = "{}#{}#{}".format(
                    suite_name, case.classname, case.name)
                unpassed_test_params.append(unpassed_test_param)

    def _inherit_execute_result(self, execute_result, root_desc):
        from xdevice import Scheduler
        if Scheduler.mode == "decc":
            return

        # get history execute result
        execute_result_name = "%s.xml" % root_desc.source.test_name
        history_execute_result = self._get_history_execute_result(
            execute_result_name)
        if not history_execute_result:
            LOG.warning("%s no history execute result exists",
                        execute_result_name)
            return execute_result

        if not os.path.exists(execute_result):
            result_dir = os.path.join(self.task.config.report_path, "result")
            os.makedirs(result_dir, exist_ok=True)
            target_execute_result = os.path.join(result_dir,
                                                 execute_result_name)
            shutil.copyfile(history_execute_result, target_execute_result)
            LOG.info("copy %s to %s" % (history_execute_result,
                                        target_execute_result))
            return target_execute_result

        # inherit history execute result
        from _core.report.reporter_helper import DataHelper
        LOG.info("inherit history execute result: %s", history_execute_result)
        history_testsuites_element = DataHelper.parse_data_report(
            history_execute_result)
        testsuites_element = DataHelper.parse_data_report(execute_result)
        self._inherit_element(history_testsuites_element, testsuites_element)

        # generate inherit execute result
        DataHelper.generate_report(testsuites_element, execute_result)
        return execute_result

    def _inherit_element(self, history_testsuites_element, testsuites_element):
        from _core.report.reporter_helper import ReportConstant
        for history_testsuite_element in history_testsuites_element:
            history_testsuite_name = history_testsuite_element.get("name", "")
            target_testsuite_element = None
            for testsuite_element in testsuites_element:
                if history_testsuite_name == testsuite_element.get("name", ""):
                    target_testsuite_element = testsuite_element
                    break

            if target_testsuite_element is None:
                testsuites_element.append(history_testsuite_element)
                inherited_test = int(testsuites_element.get(
                    ReportConstant.tests, 0)) + int(
                    history_testsuite_element.get(ReportConstant.tests, 0))
                testsuites_element.set(ReportConstant.tests,
                                       str(inherited_test))
                continue

            pass_num = 0
            for history_testcase_element in history_testsuite_element:
                if self._check_testcase_pass(history_testcase_element):
                    target_testsuite_element.append(history_testcase_element)
                    pass_num += 1

            inherited_test = int(target_testsuite_element.get(
                ReportConstant.tests, 0)) + pass_num
            target_testsuite_element.set(ReportConstant.tests,
                                         str(inherited_test))
            inherited_test = int(testsuites_element.get(
                ReportConstant.tests, 0)) + pass_num
            testsuites_element.set(ReportConstant.tests, str(inherited_test))

    def _get_history_execute_result(self, execute_result_name):
        history_execute_result = ""
        for root_dir, _, files in os.walk(
                self.task.config.history_report_path):
            for result_file in files:
                if result_file.endswith(execute_result_name):
                    history_execute_result = os.path.abspath(
                        os.path.join(root_dir, result_file))
        return history_execute_result

    @classmethod
    def _check_testcase_pass(cls, history_testcase_element):
        from _core.report.reporter_helper import ReportConstant
        from _core.report.reporter_helper import Case
        case = Case()
        case.result = history_testcase_element.get(ReportConstant.result, "")
        case.status = history_testcase_element.get(ReportConstant.status, "")
        case.message = history_testcase_element.get(ReportConstant.message, "")
        if len(history_testcase_element) > 0:
            if not case.result:
                case.result = ReportConstant.false
            case.message = history_testcase_element[0].get(
                ReportConstant.message)

        return case.is_passed()


class QueueMonitorThread(threading.Thread):

    def __init__(self, message_queue, current_driver_threads, test_drivers):
        threading.Thread.__init__(self)
        self.message_queue = message_queue
        self.current_driver_threads = current_driver_threads
        self.test_drivers = test_drivers

    def run(self):
        from xdevice import Scheduler
        LOG.debug("queue monitor thread start")
        while self.test_drivers or self.current_driver_threads:
            if not self.current_driver_threads:
                time.sleep(3)
                continue
            execute_message = self.message_queue.get()

            self.current_driver_threads.pop(execute_message.get_thread_id())

            if execute_message.get_state() == ExecuteMessage.DEVICE_FINISH:
                LOG.debug("thread id: %s execute finished" %
                          execute_message.get_thread_id())
            elif execute_message.get_state() == ExecuteMessage.DEVICE_ERROR:
                LOG.debug("thread id: %s execute error" %
                          execute_message.get_thread_id())

            if Scheduler.upload_address:
                Scheduler.upload_module_result(execute_message)

        LOG.debug("queue monitor thread end")
        if not Scheduler.is_execute:
            LOG.info("terminate success")
            Scheduler.terminate_result.put("terminate success")


class ExecuteMessage:
    DEVICE_RUN = 'device_run'
    DEVICE_FINISH = 'device_finish'
    DEVICE_ERROR = 'device_error'

    def __init__(self, state, environment, drivers, thread_id):
        self.state = state
        self.environment = environment
        self.drivers = drivers
        self.thread_id = thread_id
        self.request = None
        self.result = None

    def set_state(self, state):
        self.state = state

    def get_state(self):
        return self.state

    def set_request(self, request):
        self.request = request

    def get_request(self):
        return self.request

    def set_result(self, result):
        self.result = result

    def get_result(self):
        return self.result

    def get_environment(self):
        return self.environment

    def get_thread_id(self):
        return self.thread_id

    def get_drivers(self):
        return self.drivers
