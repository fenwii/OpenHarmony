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
import uuid
from dataclasses import dataclass

from _core.plugin import Plugin
from _core.constants import ListenerType
from _core.interface import LifeCycle
from _core.interface import IListener
from _core.logger import platform_logger
from _core.report.result_reporter import ResultReporter
from _core.report.suite_reporter import SuiteReporter
from _core.report.suite_reporter import ResultCode
from _core.report.encrypt import check_pub_key_exist

__all__ = ["LogListener", "ReportListener", "UploadListener",
           "CollectingTestListener", "CollectingLiteGTestListener",
           "CaseResult", "SuiteResult", "SuitesResult", "StateRecorder",
           "TestDescription"]

LOG = platform_logger("Listener")


@dataclass
class CaseResult:
    index = ""
    code = ResultCode.FAILED.value
    test_name = None
    test_class = None
    stacktrace = ""
    run_time = 0
    is_completed = False
    num_tests = 0
    current = 0

    def is_running(self):
        return self.test_name is not None and not self.is_completed


@dataclass
class SuiteResult:
    index = ""
    code = ResultCode.UNKNOWN.value
    suite_name = None
    test_num = 0
    stacktrace = ""
    run_time = 0
    is_completed = False
    is_started = False
    suite_num = 0


@dataclass
class SuitesResult:
    index = ""
    code = ResultCode.UNKNOWN.value
    suites_name = None
    test_num = 0
    stacktrace = ""
    run_time = 0
    is_completed = False
    product_params = {}


@dataclass
class StateRecorder:
    current_suite = None
    current_suites = None
    current_test = None
    trace_logs = []
    running_test_index = 0

    def is_started(self):
        return self.current_suite is not None

    def suites_is_started(self):
        return self.current_suites is not None

    def suite_is_running(self):
        suite = self.current_suite
        return suite is not None and suite.suite_name is not None and \
            not suite.is_completed

    def suites_is_running(self):
        suites = self.current_suites
        return suites is not None and suites.suites_name is not None and \
            not suites.is_completed

    def test_is_running(self):
        test = self.current_test
        return test is not None and test.is_running()

    def suite(self, reset=False):
        if reset or not self.current_suite:
            self.current_suite = SuiteResult()
            self.current_suite.index = uuid.uuid4().hex
        return self.current_suite

    def get_suites(self, reset=False):
        if reset or not self.current_suites:
            self.current_suites = SuitesResult()
            self.current_suites.index = uuid.uuid4().hex
        return self.current_suites

    def test(self, reset=False):
        if reset or not self.current_test:
            self.current_test = CaseResult()
            self.current_test.index = uuid.uuid4().hex
        return self.current_test


class TestDescription(object):
    def __init__(self, class_name, test_name):
        self.class_name = class_name
        self.test_name = test_name

    def __eq__(self, other):
        return self.class_name == other.class_name and \
               self.test_name == other.test_name

    @classmethod
    def remove_test(cls, tests, execute_tests):
        for execute_test in execute_tests:
            if execute_test in tests:
                tests.remove(execute_test)
        return tests


@Plugin(type=Plugin.LISTENER, id=ListenerType.log)
class LogListener(IListener):
    """
    listener test status information to the console and log
    """
    test_num = 0
    device_sn = ""

    def __started__(self, lifecycle, test_result):
        if check_pub_key_exist():
            return
        if lifecycle == LifeCycle.TestSuite:
            LOG.debug("Start test suite [%s] with %s tests"
                      % (test_result.suite_name, test_result.test_num))
            self.test_num = test_result.test_num
        elif lifecycle == LifeCycle.TestCase:
            LOG.debug("testStarted(%s#%s)" % (test_result.test_class,
                                              test_result.test_name))

    def __ended__(self, lifecycle, test_result, **kwargs):
        if check_pub_key_exist():
            return

        from _core.utils import convert_serial
        del kwargs
        if lifecycle == LifeCycle.TestSuite:
            LOG.debug("End test suite [%s] and cost %sms."
                      % (test_result.suite_name, test_result.run_time))
        elif lifecycle == LifeCycle.TestCase:
            LOG.debug("testEnded(%s#%s)" % (test_result.test_class,
                                            test_result.test_name))
            ret = ResultCode(test_result.code).name
            if self.test_num:
                LOG.info("[%s/%s %s] %s#%s %s" %
                         (test_result.current, self.test_num,
                          convert_serial(self.device_sn),
                          test_result.test_class, test_result.test_name, ret))
            else:
                LOG.info("[%s/- %s] %s#%s %s" %
                         (test_result.current, convert_serial(self.device_sn),
                          test_result.test_class, test_result.test_name,
                          ret))

    @staticmethod
    def __skipped__(lifecycle, test_result, **kwargs):
        if check_pub_key_exist():
            return

        del kwargs
        if lifecycle == LifeCycle.TestSuite:
            LOG.debug("Test suite [{}] skipped".format(test_result.suite_name))
        elif lifecycle == LifeCycle.TestCase:
            ret = ResultCode(test_result.code).name
            LOG.debug("[{}] {}#{}".format(ret, test_result.test_class,
                                          test_result.test_name))

    @staticmethod
    def __failed__(lifecycle, test_result, **kwargs):
        pass


@Plugin(type=Plugin.LISTENER, id=ListenerType.report)
class ReportListener(IListener):
    """
    listener test status information to the console
    """

    def __init__(self):
        self.result = list()
        self.suites = dict()
        self.tests = dict()
        self.current_suite_id = 0
        self.current_test_id = 0
        self.report_path = ""

    def _get_suite_result(self, test_result, create=False):
        if test_result.index in self.suites:
            return self.suites.get(test_result.index)
        elif create:
            suite = SuiteResult()
            rid = uuid.uuid4().hex if test_result.index == "" else \
                test_result.index
            suite.index = rid
            return self.suites.setdefault(rid, suite)
        else:
            return self.suites.get(self.current_suite_id)

    def _get_test_result(self, test_result, create=False):
        if test_result.index in self.tests:
            return self.tests.get(test_result.index)
        elif create:
            test = CaseResult()
            rid = uuid.uuid4().hex if test_result.index == "" else \
                test_result.index
            test.index = rid
            return self.tests.setdefault(rid, test)
        else:
            return self.tests.get(self.current_test_id)

    def __started__(self, lifecycle, test_result):
        if lifecycle == LifeCycle.TestSuites:
            suites = self._get_suite_result(test_result=test_result,
                                            create=True)
            suites.suites_name = test_result.suites_name
            suites.test_num = test_result.test_num
            self.current_suite_id = suites.index
        elif lifecycle == LifeCycle.TestSuite:
            suite = self._get_suite_result(test_result=test_result,
                                           create=True)
            suite.suite_name = test_result.suite_name
            suite.test_num = test_result.test_num
            self.current_suite_id = suite.index
        elif lifecycle == LifeCycle.TestCase:
            test = self._get_test_result(test_result=test_result, create=True)
            test.test_name = test_result.test_name
            test.test_class = test_result.test_class
            self.current_test_id = test.index

    def __ended__(self, lifecycle, test_result=None, **kwargs):
        if lifecycle == LifeCycle.TestSuite:
            suite = self._get_suite_result(test_result=test_result,
                                           create=False)
            if not suite:
                return
            suite.run_time = test_result.run_time
            suite.code = test_result.code
            is_clear = kwargs.get("is_clear", False)
            suite.test_num = max(test_result.test_num, len(self.tests))
            # generate suite report
            if not kwargs.get("suite_report", False):
                if len(self.result) > 0 and self.result[-1][0].suite_name == \
                        self.suites[suite.index].suite_name:
                    self.result[-1][1].extend(list(self.tests.values()))
                    self.result[-1][0].test_num = max(suite.test_num,
                                                      len(self.result[-1][1]))
                else:
                    self.result.append((self.suites[suite.index],
                                        list(self.tests.values())))
            else:
                result_dir = os.path.join(self.report_path, "result")
                os.makedirs(result_dir, exist_ok=True)
                self.result.append((self.suites[suite.index],
                                    list(self.tests.values())))
                results = [(suite, list(self.tests.values()))]
                suite_report = SuiteReporter(results, suite.suite_name,
                                             result_dir)
                suite_report.generate_data_report()
            if is_clear:
                self.tests.clear()
        elif lifecycle == LifeCycle.TestSuites:
            if not kwargs.get("suite_report", False):
                result_dir = os.path.join(self.report_path, "result")
                os.makedirs(result_dir, exist_ok=True)
                suites_name = kwargs.get("suites_name", "")
                product_params = kwargs.get("product_params", "")
                suite_report = SuiteReporter(self.result, suites_name,
                                             result_dir,
                                             product_params=product_params)
                suite_report.generate_data_report()
        elif lifecycle == LifeCycle.TestCase:
            test = self._get_test_result(test_result=test_result, create=False)
            test.run_time = test_result.run_time
            test.stacktrace = test_result.stacktrace
            test.code = test_result.code
        elif lifecycle == LifeCycle.TestTask:
            result_report = ResultReporter(report_path=self.report_path,
                                           task_info=test_result)
            result_report.generate_reports()

    def __skipped__(self, lifecycle, test_result):
        if lifecycle == LifeCycle.TestSuite:
            suite = self._get_suite_result(test_result=test_result,
                                           create=False)
            suite.code = ResultCode.SKIPPED.value
        elif lifecycle == LifeCycle.TestCase:
            test = self._get_test_result(test_result=test_result, create=False)
            test.code = ResultCode.SKIPPED.value

    def __failed__(self, lifecycle, test_result):
        if lifecycle == LifeCycle.TestSuite:
            suite = self._get_suite_result(test_result=test_result,
                                           create=False)
            suite.stacktrace = test_result.stacktrace
            suite.code = ResultCode.FAILED.value
        elif lifecycle == LifeCycle.TestCase:
            test = self._get_test_result(test_result=test_result, create=False)
            test.stacktrace = test_result.stacktrace
            test.code = ResultCode.FAILED.value


@Plugin(type=Plugin.LISTENER, id=ListenerType.upload)
class UploadListener(IListener):
    def __started__(self, lifecycle, test_result):
        pass

    @staticmethod
    def __ended__(lifecycle, test_result, **kwargs):
        del test_result, kwargs
        if lifecycle == LifeCycle.TestCase:
            pass

    @staticmethod
    def __skipped__(lifecycle, test_result, **kwargs):
        pass

    @staticmethod
    def __failed__(lifecycle, test_result, **kwargs):
        pass


@Plugin(type=Plugin.LISTENER, id=ListenerType.collect)
class CollectingTestListener(IListener):
    """
    listener test status information to the console
    """

    def __init__(self):
        self.tests = []

    def __started__(self, lifecycle, test_result):
        if lifecycle == LifeCycle.TestCase:
            if not test_result.test_class or not test_result.test_name:
                return
            test = TestDescription(test_result.test_class,
                                   test_result.test_name)
            if test not in self.tests:
                self.tests.append(test)

    def __ended__(self, lifecycle, test_result=None, **kwargs):
        pass

    def __skipped__(self, lifecycle, test_result):
        pass

    def __failed__(self, lifecycle, test_result):
        pass

    def get_current_run_results(self):
        return self.tests


@Plugin(type=Plugin.LISTENER, id=ListenerType.collect_lite)
class CollectingLiteGTestListener(IListener):
    """
    listener test status information to the console
    """

    def __init__(self):
        self.tests = []

    def __started__(self, lifecycle, test_result):
        if lifecycle == LifeCycle.TestCase:
            if not test_result.test_class or not test_result.test_name:
                return
            test = TestDescription(test_result.test_class,
                                   test_result.test_name)
            if test not in self.tests:
                self.tests.append(test)

    def __ended__(self, lifecycle, test_result=None, **kwargs):
        pass

    def __skipped__(self, lifecycle, test_result):
        pass

    def __failed__(self, lifecycle, test_result):
        if lifecycle == LifeCycle.TestCase:
            if not test_result.test_class or not test_result.test_name:
                return
            test = TestDescription(test_result.test_class,
                                   test_result.test_name)
            if test not in self.tests:
                self.tests.append(test)

    def get_current_run_results(self):
        return self.tests
