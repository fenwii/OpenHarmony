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
import re
import time
from queue import Queue

from _core.interface import IParser
from _core.plugin import Plugin
from _core.constants import ParserType
from _core.executor.listener import StateRecorder
from _core.executor.listener import TestDescription
from _core.interface import LifeCycle
from _core.report.suite_reporter import ResultCode
from _core.logger import platform_logger
from _core.report.encrypt import check_pub_key_exist

__all__ = ["CppTestListParserLite", "CTestParser", "OpenSourceParser",
           "CppTestParserLite", "ShellHandler"]

_INFORMATIONAL_START = "[----------]"
_TEST_START_RUN_TAG = "[==========] Running"
_TEST_RUN_TAG = "[==========]"
_CPP_TEST_DRYRUN_TAG = "Running main() "
_TEST_START_TAG = "[ RUN      ]"
_TEST_OK_TAG = "[       OK ]"
_TEST_SKIPPED_TAG = "[  SKIPPED ]"
_TEST_FAILED_TAG = "[  FAILED  ]"
_ALT_OK_TAG = "[    OK    ]"
_TIMEOUT_TAG = "[ TIMEOUT  ]"

_CTEST_START_TEST_RUN_TAG = "Framework inited."
_CTEST_END_TEST_RUN_TAG = "Framework finished."
_CTEST_SUITE_TEST_RUN_TAG = "Start to run test suite:"
_CTEST_SUITE_TIME_RUN_TAG = "Run test suite "
_CTEST_SETUP_TAG = "setup"
_CTEST_RUN_TAG = "-----------------------"

_TEST_PASSED_LOWER = "test pass"

_COMPILE_PASSED = "compile PASSED"
_COMPILE_PARA = r"(.* compile .*)"

_PRODUCT_PARA = r"(.*The .* is .*)"
_PRODUCT_PARA_START = r"To Obtain Product Params Start"
_PRODUCT_PARA_END = r"To Obtain Product Params End"

LOG = platform_logger("ParserLite")


@Plugin(type=Plugin.PARSER, id=ParserType.cpp_test_lite)
class CppTestParserLite(IParser):
    def __init__(self):
        self.state_machine = StateRecorder()
        self.suite_name = ""
        self.listeners = []
        self.product_params = {}
        self.is_params = False

    def get_suite_name(self):
        return self.suite_name

    def get_listeners(self):
        return self.listeners

    def __process__(self, lines):
        if not self.state_machine.suites_is_started():
            self.state_machine.trace_logs.extend(lines)
        for line in lines:
            if not check_pub_key_exist():
                LOG.debug(line)
            self.parse(line)

    def __done__(self):
        suite_result = self.state_machine.suite()
        suite_result.is_completed = True
        for listener in self.get_listeners():
            suite = copy.copy(suite_result)
            listener.__ended__(LifeCycle.TestSuite, suite, is_clear=True)
        self.state_machine.running_test_index = 0

        suites_result = self.state_machine.get_suites()
        if not suites_result.suites_name:
            return
        for listener in self.get_listeners():
            suites = copy.copy(suites_result)
            listener.__ended__(LifeCycle.TestSuites, test_result=suites,
                               suites_name=suites.suites_name,
                               product_params=suites.product_params)
        self.state_machine.current_suites = None

    @staticmethod
    def _is_test_run(line):
        return True if line.startswith(_TEST_RUN_TAG) else False

    @staticmethod
    def _is_test_start_run(line):
        return True if line.startswith(_TEST_START_RUN_TAG) else False

    @staticmethod
    def _is_informational_start(line):
        return True if line.startswith(_INFORMATIONAL_START) else False

    @staticmethod
    def _is_test_start(line):
        return True if line.startswith(_TEST_START_TAG) else False

    def _process_informational_line(self, line):
        pattern = r"(.*) (\(\d+ ms total\))"
        message = line[len(_INFORMATIONAL_START):].strip()
        if re.match(pattern, line.strip()):
            self.handle_suite_ended_tag(message)
        elif re.match(r'(\d+) test[s]? from (.*)', message):
            self.handle_suite_started_tag(message)

    def _process_test_run_line(self, line):
        if not self.state_machine.suites_is_running():
            return
        message = line[len(_TEST_RUN_TAG):].strip()
        self.handle_suites_ended_tag(message)

    def parse(self, line):
        if _PRODUCT_PARA_START in line:
            self.is_params = True
        elif _PRODUCT_PARA_END in line:
            self.is_params = False
        if re.match(_PRODUCT_PARA, line) and self.is_params:
            handle_product_params(line, self.product_params)

        if self.state_machine.suites_is_started() or self._is_test_run(line):
            if self._is_test_start_run(line):
                message = line[len(_TEST_RUN_TAG):].strip()
                self.handle_suites_started_tag(message)
            elif self._is_informational_start(line):
                self._process_informational_line(line)
            elif self._is_test_run(line):
                self._process_test_run_line(line)
            elif self._is_test_start(line):
                message = line[len(_TEST_START_TAG):].strip()
                self.handle_test_started_tag(message)
            else:
                self.process_test(line)

    def process_test(self, line):
        if _TEST_SKIPPED_TAG in line:
            message = line[line.index(_TEST_SKIPPED_TAG) + len(
                _TEST_SKIPPED_TAG):].strip()
            if not self.state_machine.test_is_running():
                LOG.error(
                    "Found {} without {} before, wrong GTest log format".
                        format(line, _TEST_START_TAG))
                return
            self.handle_test_ended_tag(message, ResultCode.SKIPPED)
        elif _TEST_OK_TAG in line:
            message = line[line.index(_TEST_OK_TAG) + len(
                _TEST_OK_TAG):].strip()
            if not self.state_machine.test_is_running():
                LOG.error(
                    "Found {} without {} before, wrong GTest log format".
                        format(line, _TEST_START_TAG))
                return
            self.handle_test_ended_tag(message, ResultCode.PASSED)
        elif _ALT_OK_TAG in line:
            message = line[line.index(_ALT_OK_TAG) + len(
                _ALT_OK_TAG):].strip()
            self.fake_run_marker(message)
            self.handle_test_ended_tag(message, ResultCode.PASSED)
        elif _TEST_FAILED_TAG in line:
            message = line[line.index(_TEST_FAILED_TAG) + len(
                _TEST_FAILED_TAG):].strip()
            if not self.state_machine.suite_is_running():
                return
            if not self.state_machine.test_is_running():
                self.fake_run_marker(message)
            self.handle_test_ended_tag(message, ResultCode.FAILED)
        elif _TIMEOUT_TAG in line:
            message = line[line.index(_TIMEOUT_TAG) + len(
                _TIMEOUT_TAG):].strip()
            self.fake_run_marker(message)
            self.handle_test_ended_tag(message, ResultCode.FAILED)
        elif self.state_machine.test_is_running():
            self.append_test_output(line)

    def handle_test_started_tag(self, message):
        test_class, test_name, _ = self.parse_test_description(message)
        test_result = self.state_machine.test(reset=True)
        test_result.test_class = test_class
        test_result.test_name = test_name
        for listener in self.get_listeners():
            test_result = copy.copy(test_result)
            listener.__started__(LifeCycle.TestCase, test_result)

    @classmethod
    def parse_test_description(cls, message):
        run_time = 0
        matcher = re.match(r'(.*) \((\d+) ms\)', message)
        if matcher:
            test_class, test_name = matcher.group(1).rsplit(".", 1)
            run_time = int(matcher.group(2))
        else:
            test_class, test_name = message.rsplit(".", 1)
        return test_class, test_name, run_time

    def handle_test_ended_tag(self, message, test_status):
        test_class, test_name, run_time = self.parse_test_description(
            message)
        test_result = self.state_machine.test()
        test_result.run_time = int(run_time)
        test_result.code = test_status.value
        if not test_result.is_running():
            LOG.error(
                "Test has no start tag when trying to end test: %s", message)
            return
        found_unexpected_test = False
        if test_result.test_class != test_class:
            LOG.error(
                "Expected class: {} but got:{} ".format(test_result.test_class,
                                                        test_class))
            found_unexpected_test = True
        if test_result.test_name != test_name:
            LOG.error(
                "Expected test: {} but got: {}".format(test_result.test_name,
                                                       test_name))
            found_unexpected_test = True
        test_result.current = self.state_machine.running_test_index + 1
        self.state_machine.test().is_completed = True
        if found_unexpected_test:
            test_result.code = ResultCode.FAILED.value

        for listener in self.get_listeners():
            result = copy.copy(test_result)
            listener.__ended__(LifeCycle.TestCase, result)
        self.state_machine.running_test_index += 1

    def fake_run_marker(self, message):
        fake_marker = re.compile(" +").split(message)
        self.handle_test_started_tag(fake_marker)

    def handle_suites_started_tag(self, message):
        self.state_machine.get_suites(reset=True)
        matcher = re.match(r'Running (\d+) test[s]? from .*', message)
        expected_test_num = int(matcher.group(1)) if matcher else -1
        if expected_test_num >= 0:
            test_suites = self.state_machine.get_suites()
            test_suites.suites_name = self.get_suite_name()
            test_suites.test_num = expected_test_num
            test_suites.product_params = self.product_params
            for listener in self.get_listeners():
                suite_report = copy.copy(test_suites)
                listener.__started__(LifeCycle.TestSuites, suite_report)

    def handle_suite_started_tag(self, message):
        self.state_machine.suite(reset=True)
        matcher = re.match(r'(\d+) test[s]? from (.*)', message)
        expected_test_num = int(matcher.group(1)) if matcher else -1
        if expected_test_num >= 0:
            test_suite = self.state_machine.suite()
            test_suite.suite_name = matcher.group(2)
            test_suite.test_num = expected_test_num
            for listener in self.get_listeners():
                suite_report = copy.copy(test_suite)
                listener.__started__(LifeCycle.TestSuite, suite_report)

    def handle_suite_ended_tag(self, message):
        suite_result = self.state_machine.suite()
        matcher = re.match(r'.*\((\d+) ms total\)', message)
        if matcher:
            suite_result.run_time = int(matcher.group(1))
        suite_result.is_completed = True
        for listener in self.get_listeners():
            suite = copy.copy(suite_result)
            listener.__ended__(LifeCycle.TestSuite, suite, is_clear=True)
        self.state_machine.running_test_index = 0

    def handle_suites_ended_tag(self, message):
        suites = self.state_machine.get_suites()
        matcher = re.match(r'.*\((\d+) ms total\)', message)
        if matcher:
            suites.run_time = int(matcher.group(1))
        suites.is_completed = True
        for listener in self.get_listeners():
            copy_suites = copy.copy(suites)
            listener.__ended__(LifeCycle.TestSuites, test_result=copy_suites,
                               suites_name=suites.suites_name,
                               product_params=suites.product_params)

    def append_test_output(self, message):
        if self.state_machine.test().stacktrace:
            self.state_machine.test().stacktrace = "{}\r\n".format(
                self.state_machine.test().stacktrace)
        self.state_machine.test().stacktrace = "{}{}".format(
            self.state_machine.test().stacktrace, message)

    @staticmethod
    def handle_test_run_failed(error_msg):
        if not error_msg:
            error_msg = "Unknown error"
        if not check_pub_key_exist():
            LOG.debug("error_msg:%s" % error_msg)

    def mark_test_as_failed(self, test):
        if not self.state_machine.current_suite and not test.class_name:
            return
        suites_result = self.state_machine.get_suites(reset=True)
        suites_result.suites_name = self.get_suite_name()

        suite_name = self.state_machine.current_suite.suite_name if \
            self.state_machine.current_suite else None
        suite_result = self.state_machine.suite(reset=True)
        test_result = self.state_machine.test(reset=True)
        suite_result.suite_name = suite_name or test.class_name
        suite_result.suite_num = 1
        test_result.test_class = test.class_name
        test_result.test_name = test.test_name
        test_result.stacktrace = "error_msg: Unknown error"
        test_result.num_tests = 1
        test_result.run_time = 0
        test_result.code = ResultCode.FAILED.value
        for listener in self.get_listeners():
            suite_report = copy.copy(suites_result)
            listener.__started__(LifeCycle.TestSuites, suite_report)
        for listener in self.get_listeners():
            suite_report = copy.copy(suite_result)
            listener.__started__(LifeCycle.TestSuite, suite_report)
        for listener in self.get_listeners():
            test_result = copy.copy(test_result)
            listener.__started__(LifeCycle.TestCase, test_result)
        for listener in self.get_listeners():
            test_result = copy.copy(test_result)
            listener.__ended__(LifeCycle.TestCase, test_result)
        for listener in self.get_listeners():
            suite_report = copy.copy(suite_result)
            listener.__ended__(LifeCycle.TestSuite, suite_report,
                               is_clear=True)
        self.__done__()


@Plugin(type=Plugin.PARSER, id=ParserType.cpp_test_list_lite)
class CppTestListParserLite(IParser):
    def __init__(self):
        self.last_test_class_name = None
        self.state_machine = StateRecorder()
        self.listeners = []
        self.tests = []
        self.suites_name = ""
        self.class_result = None
        self.method_result = None

    def __process__(self, lines):
        for line in lines:
            if not check_pub_key_exist():
                LOG.debug(line)
            self.parse(line)

    def get_suite_name(self):
        return self.suites_name

    def get_listeners(self):
        return self.listeners

    def __done__(self):
        if self.state_machine.is_started():
            self.handle_suite_ended_tag()
        suites_result = self.state_machine.get_suites()
        if not suites_result.suites_name:
            return
        for listener in self.get_listeners():
            suites = copy.copy(suites_result)
            listener.__ended__(LifeCycle.TestSuites, test_result=suites,
                               suites_name=suites.suites_name)
        self.state_machine.current_suites = None

    def _is_class(self, line):
        self.class_result = re.compile('^([a-zA-Z]+.*)\\.$').match(line)
        return self.class_result

    def _is_method(self, line):
        self.method_result = re.compile(
            '\\s+([a-zA-Z_]+[\\S]*)(.*)?(\\s+.*)?$').match(line)
        return self.method_result

    def _process_class_line(self, line):
        del line
        if not self.state_machine.suites_is_started():
            self.handle_suites_started_tag()
        self.last_test_class_name = self.class_result.group(1)
        if self.state_machine.is_started():
            self.handle_suite_ended_tag()
        self.handle_suite_started_tag(self.class_result.group(1))

    def _process_method_line(self, line):
        if not self.last_test_class_name:
            LOG.error(
                "parsed new test case name %s but no test class"
                " name has been set" % line)
        else:
            test = TestDescription(self.last_test_class_name,
                                   self.method_result.group(1))
            self.tests.append(test)
            self.handle_test_tag(self.last_test_class_name,
                                 self.method_result.group(1))

    @staticmethod
    def _is_cpp_test_dryrun(line):
        return True if line.find(_CPP_TEST_DRYRUN_TAG) != -1 else False

    def parse(self, line):
        if self.state_machine.suites_is_started() or self._is_cpp_test_dryrun(
                line):
            if self._is_cpp_test_dryrun(line):
                self.handle_suites_started_tag()
            elif self._is_class(line):
                self._process_class_line(line)
            elif self._is_method(line):
                self._process_method_line(line)
            else:
                if not check_pub_key_exist():
                    LOG.debug("line ignored: %s" % line)

    def handle_test_tag(self, test_class, test_name):
        test_result = self.state_machine.test(reset=True)
        test_result.test_class = test_class
        test_result.test_name = test_name
        for listener in self.get_listeners():
            test_result = copy.copy(test_result)
            listener.__started__(LifeCycle.TestCase, test_result)
        self.state_machine.test().is_completed = True
        test_result.code = ResultCode.SKIPPED.value
        for listener in self.get_listeners():
            result = copy.copy(test_result)
            listener.__ended__(LifeCycle.TestCase, result)
        self.state_machine.running_test_index += 1
        test_suites = self.state_machine.get_suites()
        test_suite = self.state_machine.suite()
        test_suites.test_num += 1
        test_suite.test_num += 1

    def handle_suites_started_tag(self):
        self.state_machine.get_suites(reset=True)
        test_suites = self.state_machine.get_suites()
        test_suites.suites_name = self.get_suite_name()
        test_suites.test_num = 0
        for listener in self.get_listeners():
            suite_report = copy.copy(test_suites)
            listener.__started__(LifeCycle.TestSuites, suite_report)

    def handle_suite_started_tag(self, class_name):
        self.state_machine.suite(reset=True)
        test_suite = self.state_machine.suite()
        test_suite.suite_name = class_name
        test_suite.test_num = 0
        for listener in self.get_listeners():
            test_suite_copy = copy.copy(test_suite)
            listener.__started__(LifeCycle.TestSuite, test_suite_copy)

    def handle_suite_ended_tag(self):
        suite_result = self.state_machine.suite()
        suite_result.is_completed = True
        for listener in self.get_listeners():
            suite = copy.copy(suite_result)
            listener.__ended__(LifeCycle.TestSuite, suite)

    def handle_suites_ended_tag(self):
        suites = self.state_machine.get_suites()
        suites.is_completed = True
        for listener in self.get_listeners():
            copy_suites = copy.copy(suites)
            listener.__ended__(LifeCycle.TestSuites, test_result=copy_suites,
                               suites_name=suites.suites_name)

    def mark_test_as_failed(self, test):
        if not self.state_machine.current_suite and not test.class_name:
            return
        suite_name = self.state_machine.current_suite.suite_name if \
            self.state_machine.current_suite else None
        suite_result = self.state_machine.suite(reset=True)
        test_result = self.state_machine.test(reset=True)
        suite_result.suite_name = suite_name or test.class_name
        suite_result.suite_num = 1
        test_result.test_class = test.class_name
        test_result.test_name = test.test_name
        test_result.stacktrace = "error_msg: Unknown error"
        test_result.num_tests = 1
        test_result.run_time = 0
        test_result.code = ResultCode.FAILED.value
        for listener in self.get_listeners():
            suite_report = copy.copy(suite_result)
            listener.__started__(LifeCycle.TestSuite, suite_report)
        for listener in self.get_listeners():
            test_result = copy.copy(test_result)
            listener.__started__(LifeCycle.TestCase, test_result)
        for listener in self.get_listeners():
            test_result = copy.copy(test_result)
            listener.__ended__(LifeCycle.TestCase, test_result)
        self.__done__()


@Plugin(type=Plugin.PARSER, id=ParserType.ctest_lite)
class CTestParser(IParser):
    last_line = ""
    pattern = r"(\d{4}-\d{1,2}-\d{1,2}\s\d{1,2}:\d{1,2}:\d{1,2}\.\d{3}) "

    def __init__(self):
        self.state_machine = StateRecorder()
        self.suites_name = ""
        self.listeners = []
        self.product_params = {}
        self.is_params = False

    def get_suite_name(self):
        return self.suites_name

    def get_listeners(self):
        return self.listeners

    def __process__(self, lines):
        if not self.state_machine.suites_is_started():
            self.state_machine.trace_logs.extend(lines)
        for line in lines:
            self.parse(line)

    def __done__(self):
        suites = self.state_machine.get_suites()
        suites.is_completed = True

        for listener in self.get_listeners():
            listener.__ended__(LifeCycle.TestSuites, test_result=suites,
                               suites_name=suites.suites_name,
                               product_params=suites.product_params)
        self.state_machine.current_suites = None

    @staticmethod
    def _is_ctest_start_test_run(line):
        return True if line.endswith(_CTEST_START_TEST_RUN_TAG) else False

    @staticmethod
    def _is_ctest_end_test_run(line):
        return True if line.endswith(_CTEST_END_TEST_RUN_TAG) else False

    @staticmethod
    def _is_ctest_run(line):
        return True if line.endswith(_CTEST_RUN_TAG) else False

    def _is_ctest_suite_test_run(self, line):
        return re.match("{}{}".format(self.pattern, _CTEST_SUITE_TEST_RUN_TAG),
                        line)

    def is_ctest_suite_time_run(self, line):
        return re.match("{}{}".format(self.pattern, _CTEST_SUITE_TIME_RUN_TAG),
                        line)

    def _process_ctest_suite_test_run_line(self, line):
        _, message_index = re.match(
            "{}{}".format(self.pattern, _CTEST_SUITE_TEST_RUN_TAG),
            line).span()
        self.handle_suite_started_tag(line[message_index:].strip())

    @staticmethod
    def _is_execute_result_line(line):
        return re.match(
            r"(.*" + "\\.c:" + "\\d+:.*:(PASS|FAIL|OK|IGNORE"")\\.*)",
            line.strip())

    def parse(self, line):
        if _PRODUCT_PARA_START in line:
            self.is_params = True
        elif _PRODUCT_PARA_END in line:
            self.is_params = False
        if self.is_params and re.match(_PRODUCT_PARA, line):
            handle_product_params(line, self.product_params)

        if self.state_machine.suites_is_started() or \
                self._is_ctest_start_test_run(line):
            try:
                if self._is_ctest_start_test_run(line):
                    self.handle_suites_started_tag()
                elif self._is_ctest_end_test_run(line):
                    self.process_suites_ended_tag()
                elif self._is_ctest_run(line):
                    self.handle_suite_ended_tag()
                elif self._is_ctest_suite_test_run(line) and \
                        not self.state_machine.suite_is_running():
                    self._process_ctest_suite_test_run_line(line)
                elif self.is_ctest_suite_time_run(line) and \
                        not self.state_machine.suite_is_running():
                    self.handle_suite_started_tag(line)
                elif line.find(":") != -1 and line.count(":") >= 3:
                    if self._is_execute_result_line(line):
                        self.handle_one_test_tag(line.strip())
            except AttributeError:
                LOG.error("parsing log: %s failed" % (line.strip()))
            self.last_line = line

    def parse_test_description(self, message):

        test_class = message.split(".c:")[0].split(" ")[-1].split("/")[-1]
        message_index = message.index(".c:")
        end_time = re.match(self.pattern, message).group().strip()
        start_time = re.match(self.pattern,
                              self.last_line.strip()).group().strip()
        start_timestamp = int(time.mktime(
            time.strptime(start_time, "%Y-%m-%d %H:%M:%S.%f"))) * 1000 + int(
            start_time.split(".")[-1])
        end_timestamp = int(time.mktime(
            time.strptime(end_time, "%Y-%m-%d %H:%M:%S.%f"))) * 1000 + int(
            end_time.split(".")[-1])
        run_time = end_timestamp - start_timestamp
        message_list = message[message_index + 3:].split(":")
        test_name, status = message_list[1].strip(), message_list[2].strip()
        status_dict = {"PASS": ResultCode.PASSED, "FAIL": ResultCode.FAILED,
                       "IGNORE": ResultCode.SKIPPED}
        status = status_dict.get(status)
        return test_class, test_name, status, run_time

    def handle_one_test_tag(self, message):
        test_class, test_name, status, run_time = \
            self.parse_test_description(message)
        test_result = self.state_machine.test(reset=True)
        test_result.test_class = test_class
        test_result.test_name = test_name
        test_result.run_time = run_time
        self.state_machine.running_test_index += 1
        test_result.current = self.state_machine.running_test_index
        test_result.code = status.value
        self.state_machine.suite().run_time += run_time
        for listener in self.get_listeners():
            test_result = copy.copy(test_result)
            listener.__started__(LifeCycle.TestCase, test_result)

        test_suite = self.state_machine.suite()
        test_suites = self.state_machine.get_suites()

        found_unexpected_test = False

        if found_unexpected_test or ResultCode.FAILED == status:
            if "FAIL:" in message and not message.endswith("FAIL:"):
                test_result.stacktrace = message[
                                         message.rindex("FAIL:") + len(
                                             "FAIL:"):]
            for listener in self.get_listeners():
                result = copy.copy(test_result)
                listener.__failed__(LifeCycle.TestCase, result)
        elif ResultCode.SKIPPED == status:
            for listener in self.get_listeners():
                result = copy.copy(test_result)
                listener.__skipped__(LifeCycle.TestCase, result)

        self.state_machine.test().is_completed = True
        test_suite.test_num += 1
        test_suites.test_num += 1

        for listener in self.get_listeners():
            result = copy.copy(test_result)
            listener.__ended__(LifeCycle.TestCase, result)

    def handle_suites_started_tag(self):
        self.state_machine.get_suites(reset=True)
        test_suites = self.state_machine.get_suites()
        test_suites.suites_name = self.suites_name
        test_suites.product_params = self.product_params
        test_suites.test_num = 0
        for listener in self.get_listeners():
            suite_report = copy.copy(test_suites)
            listener.__started__(LifeCycle.TestSuites, suite_report)

    def handle_suite_started_tag(self, message):
        if re.match("{}{}".format(self.pattern, _CTEST_SUITE_TIME_RUN_TAG),
                    message.strip()):
            message = self.state_machine.suite().suite_name
        self.state_machine.suite(reset=True)
        test_suite = self.state_machine.suite()
        test_suite.suite_name = message
        test_suite.test_num = 0
        for listener in self.get_listeners():
            suite_report = copy.copy(test_suite)
            listener.__started__(LifeCycle.TestSuite, suite_report)

    def handle_suite_ended_tag(self):
        suite_result = self.state_machine.suite()
        suites = self.state_machine.get_suites()
        suite_result.run_time = suite_result.run_time
        suites.run_time += suite_result.run_time
        suite_result.is_completed = True

        for listener in self.get_listeners():
            suite = copy.copy(suite_result)
            listener.__ended__(LifeCycle.TestSuite, suite, is_clear=True)
        self.state_machine.running_test_index = 0

    def process_suites_ended_tag(self):
        suites = self.state_machine.get_suites()
        suites.is_completed = True

        for listener in self.get_listeners():
            listener.__ended__(LifeCycle.TestSuites, test_result=suites,
                               suites_name=suites.suites_name,
                               product_params=suites.product_params)

    def append_test_output(self, message):
        if self.state_machine.test().stacktrace:
            self.state_machine.test().stacktrace = "{}\r\n".format(
                self.state_machine.test().stacktrace)
        self.state_machine.test().stacktrace = "{}{}".format(
            self.state_machine.test().stacktrace, message)


@Plugin(type=Plugin.PARSER, id=ParserType.open_source_test)
class OpenSourceParser(IParser):
    def __init__(self):
        self.state_machine = StateRecorder()
        self.suite_name = ""
        self.test_name = ""
        self.test_num = 1
        self.listeners = []
        self.output = ""
        self.lines = []

    def get_suite_name(self):
        return self.suite_name

    def get_listeners(self):
        return self.listeners

    def __process__(self, lines):
        self.lines.extend(lines)

    def __done__(self):
        if not self.state_machine.suites_is_started():
            self.state_machine.trace_logs.extend(self.lines)
        self.handle_suite_started_tag(self.test_num)

        test_result = self.state_machine.test(reset=True)
        test_result.run_time = 0
        test_result.test_class = self.suite_name
        test_result.test_name = self.test_name
        test_result.test_num = 1
        test_result.current = 1
        for listener in self.get_listeners():
            result = copy.copy(test_result)
            listener.__started__(LifeCycle.TestCase, result)
        for line in self.lines:
            self.output = "{}{}".format(self.output, line)
            if _TEST_PASSED_LOWER in line.lower():
                test_result.code = ResultCode.PASSED.value
                for listener in self.get_listeners():
                    result = copy.copy(test_result)
                    listener.__ended__(LifeCycle.TestCase, result)
                break
        else:
            test_result.code = ResultCode.FAILED.value
            for listener in self.get_listeners():
                result = copy.copy(test_result)
                listener.__ended__(LifeCycle.TestCase, result)

        self.state_machine.test().is_completed = True
        self.handle_suite_ended_tag()

    def handle_suite_started_tag(self, test_num):
        test_suite = self.state_machine.suite()
        if test_num >= 0:
            test_suite.suite_name = self.suite_name
            test_suite.test_num = test_num
            for listener in self.get_listeners():
                suite_report = copy.copy(test_suite)
                listener.__started__(LifeCycle.TestSuite, suite_report)

    def handle_suite_ended_tag(self):
        suite_result = self.state_machine.suite()
        for listener in self.get_listeners():
            suite = copy.copy(suite_result)
            listener.__ended__(LifeCycle.TestSuite, suite,
                               suite_report=True)


class ShellHandler:
    def __init__(self, parsers):
        self.parsers = []
        self.unfinished_line = ""
        self.output_queue = Queue()
        for parser in parsers:
            if isinstance(parser, IParser):
                self.parsers.append(parser)
            else:
                raise TypeError(
                    "Parser {} must implement IOutputParser interface.".format(
                        parser, ))

    def _process_output(self, output, end_mark="\n"):
        content = output
        if self.unfinished_line:
            content = "".join((self.unfinished_line, content))
            self.unfinished_line = ""
        lines = content.split(end_mark)
        if content.endswith(end_mark):
            # get rid of the tail element of this list contains empty str
            return lines[:-1]
        else:
            self.unfinished_line = lines[-1]
            # not return the tail element of this list contains unfinished str,
            # so we set position -1
            return lines[:-1]

    def __read__(self, output):
        lines = self._process_output(output)
        for line in lines:
            for parser in self.parsers:
                try:
                    parser.__process__([line])
                except (ValueError, TypeError, SyntaxError, AttributeError) \
                        as error:
                    LOG.debug("Parse %s line error: %s" % (line, error))

    def __error__(self, message):
        if message:
            for parser in self.parsers:
                parser.__process__([message])

    def __done__(self, result_code="", message=""):
        msg_fmt = ""
        if message:
            msg_fmt = ", message is {}".format(message)
            for parser in self.parsers:
                parser.__process__([message])
        if not check_pub_key_exist():
            LOG.debug("result code is: {}{}".format(result_code, msg_fmt))
        for parser in self.parsers:
            parser.__done__()


def handle_product_params(message, product_params):
    message = message[message.index("The"):]
    items = message[len("The "):].split(" is ")
    product_params.setdefault(items[0].strip(),
                              items[1].strip().strip("[").strip("]"))
