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
import platform
import time
from ast import literal_eval
from dataclasses import dataclass
from xml.etree import ElementTree

from _core.logger import platform_logger
from _core.report.encrypt import check_pub_key_exist
from _core.report.encrypt import do_rsa_encrypt

LOG = platform_logger("ReporterHelper")


@dataclass
class ReportConstant:
    # report name constants
    summary_data_report = "summary_report.xml"
    summary_vision_report = "summary_report.html"
    details_vision_report = "details_report.html"
    failures_vision_report = "failures_report.html"
    summary_ini = "summary.ini"
    summary_report_hash = "summary_report.hash"
    title_name = "title_name"
    summary_title = "Summary Report"
    details_title = "Details Report"
    failures_title = "Failures Report"
    decc_mode = "decc"

    # exec_info constants
    platform = "platform"
    test_type = "test_type"
    device_name = "device_name"
    host_info = "host_info"
    test_time = "test_time"
    log_path = "log_path"
    log_path_title = "Log Path"
    execute_time = "execute_time"

    # summary constants
    product_params = "product_params"
    modules = "modules"
    modules_done = "modules_done"
    name = "name"
    time = "time"
    total = "total"
    tests = "tests"
    passed = "passed"
    errors = "errors"
    disabled = "disabled"
    failures = "failures"
    blocked = "blocked"
    ignored = "ignored"
    unavailable = "unavailable"
    message = "message"

    # case result constants
    module = "module"
    result = "result"
    status = "status"
    run = "run"
    true = "true"
    false = "false"
    skip = "skip"
    disable = "disable"
    class_name = "classname"
    level = "level"
    empty_name = "-"

    # time constants
    time_stamp = "timestamp"
    start_time = "start_time"
    end_time = "end_time"
    time_format = "%Y-%m-%d %H:%M:%S"

    # xml tag constants
    test_suites = "testsuites"
    test_suite = "testsuite"
    test_case = "testcase"

    # report title constants
    failed = "failed"
    error = "error"
    color_normal = "color-normal"
    color_failed = "color-failed"
    color_blocked = "color-blocked"
    color_ignored = "color-ignored"
    color_unavailable = "color-unavailable"


class DataHelper:
    LINE_BREAK = "\n"
    LINE_BREAK_INDENT = "\n  "
    INDENT = "  "
    DATA_REPORT_SUFFIX = ".xml"

    def __init__(self):
        pass

    @staticmethod
    def parse_data_report(data_report):
        if os.path.exists(data_report):
            with open(data_report, 'r', encoding='UTF-8') as file_content:
                data_str = file_content.read()
        else:
            data_str = data_report

        data_str = data_str.replace(chr(2), "").replace(chr(15), "") \
            .replace(chr(16), "").replace(chr(1), "")
        try:
            return ElementTree.fromstring(data_str)
        except SyntaxError as error:
            LOG.error("%s %s", data_report, error.args)
            return ElementTree.Element("empty")

    @staticmethod
    def set_element_attributes(element, element_attributes):
        for key, value in element_attributes.items():
            element.set(key, str(value))

    @classmethod
    def initial_element(cls, tag, tail, text):
        element = ElementTree.Element(tag)
        element.tail = tail
        element.text = text
        return element

    def initial_suites_element(self):
        return self.initial_element(ReportConstant.test_suites,
                                    self.LINE_BREAK, self.LINE_BREAK_INDENT)

    def initial_suite_element(self):
        return self.initial_element(ReportConstant.test_suite,
                                    self.LINE_BREAK_INDENT,
                                    self.LINE_BREAK_INDENT + self.INDENT)

    def initial_case_element(self):
        return self.initial_element(ReportConstant.test_case,
                                    self.LINE_BREAK_INDENT + self.INDENT, "")

    @classmethod
    def get_summary_result(cls, report_path, file_name, key=None,
                           reverse=False):
        data_reports = cls._get_data_reports(report_path)
        if not data_reports:
            return
        if key:
            data_reports.sort(key=key, reverse=reverse)
        summary_result = None
        need_update_attributes = [ReportConstant.tests, ReportConstant.errors,
                                  ReportConstant.failures,
                                  ReportConstant.disabled,
                                  ReportConstant.unavailable]
        for data_report in data_reports:
            data_report_element = cls.parse_data_report(data_report)
            if not summary_result:
                summary_result = data_report_element
                continue
            summary_testsuite = summary_result[0]
            data_testsuite = data_report_element[0]
            cls._update_attributes(summary_testsuite, data_testsuite,
                                   need_update_attributes)
            for element in data_testsuite:
                summary_testsuite.append(element)

        need_update_attributes.append(ReportConstant.time)
        for attribute in need_update_attributes:
            summary_result.set(attribute, summary_result[0].get(attribute))

        cls.generate_report(summary_result, file_name)

    @classmethod
    def _get_data_reports(cls, report_path):
        if not os.path.isdir(report_path):
            return []
        data_reports = []
        for root, _, files in os.walk(report_path):
            for file_name in files:
                if not file_name.endswith(cls.DATA_REPORT_SUFFIX):
                    continue
                data_reports.append(os.path.join(root, file_name))
        return data_reports

    @classmethod
    def _update_attributes(cls, summary_element, data_element,
                           need_update_attributes):
        for attribute in need_update_attributes:
            updated_value = int(summary_element.get(attribute, 0)) + \
                            int(data_element.get(attribute, 0))
            summary_element.set(attribute, str(updated_value))
        # update time
        updated_time = round(float(summary_element.get(
            ReportConstant.time, 0)) + float(
            summary_element.get(ReportConstant.time, 0)), 3)
        summary_element.set(ReportConstant.time, str(updated_time))

    @staticmethod
    def generate_report(element, file_name):
        if check_pub_key_exist():
            plain_text = DataHelper.to_string(element)
            cipher_text = do_rsa_encrypt(plain_text)
            with open(file_name, "wb") as file_handler:
                file_handler.write(cipher_text)
        else:
            tree = ElementTree.ElementTree(element)
            tree.write(file_name, encoding="UTF-8", xml_declaration=True,
                       short_empty_elements=True)
        LOG.info("generate data report: %s", file_name)

    @staticmethod
    def to_string(element):
        return str(
            ElementTree.tostring(element, encoding='UTF-8', method='xml'),
            encoding="UTF-8")


@dataclass
class ExecInfo:
    keys = [ReportConstant.platform, ReportConstant.test_type,
            ReportConstant.device_name, ReportConstant.host_info,
            ReportConstant.test_time, ReportConstant.execute_time]
    test_type = ""
    device_name = ""
    host_info = ""
    test_time = ""
    log_path = ""
    platform = ""
    execute_time = ""
    product_params = dict()


class Result:

    def __init__(self):
        self.total = 0
        self.passed = 0
        self.failed = 0
        self.blocked = 0
        self.ignored = 0
        self.unavailable = 0

    def get_total(self):
        return self.total

    def get_passed(self):
        return self.passed


class Summary:
    keys = [ReportConstant.modules, ReportConstant.total,
            ReportConstant.passed, ReportConstant.failed,
            ReportConstant.blocked, ReportConstant.unavailable,
            ReportConstant.ignored, ReportConstant.modules_done]

    def __init__(self):
        self.result = Result()
        self.modules = None
        self.modules_done = 0

    def get_result(self):
        return self.result

    def get_modules(self):
        return self.modules


class Suite:
    keys = [ReportConstant.module, ReportConstant.name, ReportConstant.total,
            ReportConstant.passed, ReportConstant.failed,
            ReportConstant.blocked, ReportConstant.ignored,
            ReportConstant.time]
    module = ReportConstant.empty_name
    name = ""
    time = ""

    def __init__(self):
        self.message = ""
        self.result = Result()
        self.cases = []  # need initial to create new object

    def get_cases(self):
        return self.cases

    def set_cases(self, element):
        if len(element) == 0:
            LOG.warning("%s has no testcase",
                        element.get(ReportConstant.name, ""))
            return

        # get case context and add to self.cases
        for child in element:
            case = Case()
            case.module = self.module
            for key, value in child.items():
                setattr(case, key, value)
            if len(child) > 0:
                if not getattr(case, ReportConstant.result, ""):
                    setattr(case, ReportConstant.result, ReportConstant.false)
                message = child[0].get(ReportConstant.message, "")
                if child[0].text and message != child[0].text:
                    message = "%s\n%s" % (message, child[0].text)
                setattr(case, ReportConstant.message, message)
            self.cases.append(case)
        self.cases.sort(key=lambda x: (
            x.is_failed(), x.is_blocked(), x.is_unavailable(), x.is_passed()),
                        reverse=True)


class Case:
    module = ReportConstant.empty_name
    name = ReportConstant.empty_name
    classname = ReportConstant.empty_name
    status = ""
    result = ""
    message = ""
    time = ""

    def is_passed(self):
        if self.result == ReportConstant.true and \
                (self.status == ReportConstant.run or self.status == ""):
            return True
        if self.result == "" and self.status == ReportConstant.run and \
                self.message == "":
            return True
        return False

    def is_failed(self):
        return self.result == ReportConstant.false and \
               (self.status == ReportConstant.run or self.status == "")

    def is_blocked(self):
        return self.status in [ReportConstant.blocked, ReportConstant.disable,
                               ReportConstant.error]

    def is_unavailable(self):
        return self.status in [ReportConstant.unavailable]

    def is_ignored(self):
        return self.status in [ReportConstant.skip]

    def get_result(self):
        if self.is_failed():
            return ReportConstant.failed
        if self.is_blocked():
            return ReportConstant.blocked
        if self.is_unavailable():
            return ReportConstant.unavailable
        if self.is_ignored():
            return ReportConstant.ignored
        return ReportConstant.passed


@dataclass
class ColorType:
    keys = [ReportConstant.failed, ReportConstant.blocked,
            ReportConstant.ignored, ReportConstant.unavailable]
    failed = ReportConstant.color_normal
    blocked = ReportConstant.color_normal
    ignored = ReportConstant.color_normal
    unavailable = ReportConstant.color_normal


class VisionHelper:
    PLACE_HOLDER = "&nbsp;"
    MAX_LENGTH = 50

    def __init__(self):
        from xdevice import Variables
        self.summary_element = None
        self.template_name = os.path.join(Variables.res_dir, "template",
                                          "report.html")

    def parse_element_data(self, summary_element, report_path, task_info):
        self.summary_element = summary_element
        exec_info = self._set_exec_info(report_path, task_info)
        suites = self._set_suites_info()
        summary = self._set_summary_info()
        return exec_info, summary, suites

    def _set_exec_info(self, report_path, task_info):
        exec_info = ExecInfo()
        exec_info.platform = getattr(task_info, ReportConstant.platform,
                                     "None")
        exec_info.test_type = getattr(task_info, ReportConstant.test_type,
                                      "Test")
        exec_info.device_name = getattr(task_info, ReportConstant.device_name,
                                        "None")
        exec_info.host_info = platform.platform()
        start_time = self.summary_element.get(ReportConstant.start_time, "")
        end_time = self.summary_element.get(ReportConstant.end_time, "")
        exec_info.test_time = "%s/ %s" % (start_time, end_time)
        start_time = time.mktime(time.strptime(
            start_time, ReportConstant.time_format))
        end_time = time.mktime(time.strptime(
            end_time, ReportConstant.time_format))
        exec_info.execute_time = self._get_execute_time(round(
            end_time - start_time, 3))
        exec_info.log_path = os.path.abspath(os.path.join(report_path, "log"))

        try:
            product_params = self.summary_element.get(
                ReportConstant.product_params, "")
            if product_params:
                exec_info.product_params = literal_eval(str(product_params))
        except SyntaxError as error:
            LOG.error("summary report error: %s", error.args)
        return exec_info

    @classmethod
    def _get_execute_time(cls, second_time):
        hour, day = 0, 0
        second, minute = second_time % 60, second_time // 60
        if minute > 0:
            minute, hour = minute % 60, minute // 60
        if hour > 0:
            hour, day = hour % 24, hour // 24
        execute_time = "{}sec".format(str(int(second)))
        if minute > 0:
            execute_time = "{}min {}".format(str(int(minute)), execute_time)
        if hour > 0:
            execute_time = "{}hour {}".format(str(int(hour)), execute_time)
        if day > 0:
            execute_time = "{}day {}".format(str(int(day)), execute_time)
        return execute_time

    def _set_summary_info(self):
        summary = Summary()
        summary.modules = self.summary_element.get(
            ReportConstant.modules, 0)
        summary.modules_done = self.summary_element.get(
            ReportConstant.modules_done, 0)
        summary.result.total = int(self.summary_element.get(
            ReportConstant.tests, 0))
        summary.result.failed = int(
            self.summary_element.get(ReportConstant.failures, 0))
        summary.result.blocked = int(
            self.summary_element.get(ReportConstant.errors, 0)) + \
            int(self.summary_element.get(ReportConstant.disabled, 0))
        summary.result.ignored = int(
            self.summary_element.get(ReportConstant.ignored, 0))
        summary.result.unavailable = int(
            self.summary_element.get(ReportConstant.unavailable, 0))
        summary.result.passed = summary.result.total - summary.result.failed \
            - summary.result.blocked - summary.result.ignored
        return summary

    def _set_suites_info(self):
        suites = []
        for child in self.summary_element:
            suite = Suite()
            suite.module = child.get(ReportConstant.module,
                                     ReportConstant.empty_name)
            suite.name = child.get(ReportConstant.name, "")
            suite.message = child.get(ReportConstant.message, "")
            suite.result.total = int(child.get(ReportConstant.tests)) if \
                child.get(ReportConstant.tests) else 0
            suite.result.failed = int(child.get(ReportConstant.failures)) if \
                child.get(ReportConstant.failures) else 0
            suite.result.unavailable = int(child.get(
                ReportConstant.unavailable)) if child.get(
                ReportConstant.unavailable) else 0
            errors = int(child.get(ReportConstant.errors)) if child.get(
                ReportConstant.errors) else 0
            disabled = int(child.get(ReportConstant.disabled)) if child.get(
                ReportConstant.disabled) else 0
            suite.result.ignored = int(child.get(ReportConstant.ignored)) if \
                child.get(ReportConstant.ignored) else 0
            suite.result.blocked = errors + disabled
            suite.result.passed = suite.result.total - suite.result.failed - \
                suite.result.blocked - suite.result.ignored
            suite.time = child.get(ReportConstant.time, "")
            suite.set_cases(child)
            suites.append(suite)
        suites.sort(key=lambda x: (x.result.failed, x.result.blocked,
                                   x.result.unavailable), reverse=True)
        return suites

    def render_data(self, title_name, parsed_data,
                    render_target=ReportConstant.summary_vision_report):
        exec_info, summary, suites = parsed_data
        if not os.path.exists(self.template_name):
            LOG.error("template file not exists")
            return ""

        file_context = open(self.template_name).read()
        file_context = self._render_key("", ReportConstant.title_name,
                                        title_name, file_context)
        file_context = self._render_exec_info(file_context, exec_info)
        file_context = self._render_summary(file_context, summary)
        if render_target == ReportConstant.summary_vision_report:
            file_context = self._render_suites(file_context, suites)
        elif render_target == ReportConstant.details_vision_report:
            file_context = self._render_cases(file_context, suites)
        elif render_target == ReportConstant.failures_vision_report:
            file_context = self._render_failure_cases(file_context, suites)
        else:
            LOG.error("unsupported vision report type: %s", render_target)
        return file_context

    @classmethod
    def _render_key(cls, prefix, key, new_str, update_context):
        old_str = "<!--{%s%s}-->" % (prefix, key)
        return update_context.replace(old_str, new_str)

    def _render_exec_info(self, file_context, exec_info):
        prefix = "exec_info."
        for key in ExecInfo.keys:
            value = self._get_hidden_style_value(getattr(
                exec_info, key, "None"))
            file_context = self._render_key(prefix, key, value, file_context)
        file_context = self._render_product_params(exec_info, file_context,
                                                   prefix)
        return file_context

    def _render_product_params(self, exec_info, file_context, prefix):
        """construct product params context and render it to file context
        product params sample:
            <tr>
                <td class="normal first">key:</td>
                <td class="normal second">value</td>
                <td class="normal third">key:</td>
                <td class="normal fourth">value</td>
            </tr>
        """
        row_start = True
        try:
            keys = list(exec_info.product_params.keys())
        except AttributeError:
            LOG.error("product params error %s", exec_info.product_params)
            keys = []
        if ReportConstant.log_path_title not in keys:
            keys.append(ReportConstant.log_path_title)
        exec_info.product_params[ReportConstant.log_path_title] = \
            exec_info.log_path

        render_value = ""
        for key in keys:
            value = exec_info.product_params[key]
            if row_start:
                render_value = "%s<tr>\n" % render_value
            render_value = "{}{}".format(
                render_value, self._get_exec_info_td(key, value, row_start))
            if not row_start:
                render_value = "%s</tr>\n" % render_value
            row_start = not row_start
        if not row_start:
            render_value = "%s</tr>\n" % render_value
        file_context = self._render_key(prefix, ReportConstant.product_params,
                                        render_value, file_context)
        exec_info.product_params.pop(ReportConstant.log_path_title)
        return file_context

    def _get_exec_info_td(self, key, value, row_start):
        if not value:
            value = self.PLACE_HOLDER
        if key == ReportConstant.log_path_title and row_start:
            exec_info_td = \
                "  <td class='normal first'>%s:</td>\n" \
                "  <td class='normal second' colspan='3'>%s</td>\n" % \
                (key, value)
            return exec_info_td
        value = self._get_hidden_style_value(value)
        if row_start:
            exec_info_td = "  <td class='normal first'>%s:</td>\n" \
                           "  <td class='normal second'>%s</td>\n" % \
                           (key, value)
        else:
            exec_info_td = "  <td class='normal third'>%s:</td>\n" \
                           "  <td class='normal fourth'>%s</td>\n" % \
                           (key, value)
        return exec_info_td

    def _get_hidden_style_value(self, value):
        if len(value) <= self.MAX_LENGTH:
            return value
        return "<div class='hidden' title='%s'>%s</div>" % (value, value)

    def _render_summary(self, file_context, summary):
        file_context = self._render_data_object(file_context, summary,
                                                "summary.")

        # render color type
        color_type = ColorType()
        if summary.result.failed != 0:
            color_type.failed = ReportConstant.color_failed
        if summary.result.blocked != 0:
            color_type.blocked = ReportConstant.color_blocked
        if summary.result.ignored != 0:
            color_type.ignored = ReportConstant.color_ignored
        if summary.result.unavailable != 0:
            color_type.unavailable = ReportConstant.color_unavailable
        return self._render_data_object(file_context, color_type,
                                        "color_type.")

    def _render_data_object(self, file_context, data_object, prefix,
                            default=None):
        """construct data object context and render it to file context"""
        if default is None:
            default = self.PLACE_HOLDER
        update_context = file_context
        for key in getattr(data_object, "keys", []):
            if hasattr(Result(), key) and hasattr(
                    data_object, ReportConstant.result):
                result = getattr(data_object, ReportConstant.result, Result())
                new_str = str(getattr(result, key, default))
            else:
                new_str = str(getattr(data_object, key, default))
            update_context = self._render_key(prefix, key, new_str,
                                              update_context)
        return update_context

    def _render_suites(self, file_context, suites):
        """construct suites context and render it to file context
        suite record sample:
            <table class="suites">
            <tr>
                <th class="title" colspan="9">Test detail</th>
            </tr>
            <tr>
                <th class="normal module">Module</th>
                <th class="normal test-suite">Testsuite</th>
                <th class="normal total">Total Tests</th>
                <th class="normal passed">Passed</th>
                <th class="normal failed">Failed</th>
                <th class="normal blocked">Blocked</th>
                <th class="normal ignored">Ignored</th>
                <th class="normal time">Time</th>
                <th class="normal operate">Operate</th>
            </tr>
            <tr [class="background-color"]>
                <td class="normal module">base</td>
                <td class="normal test-suite">{suite.name}</td>
                <td class="normal total">{suite.result.total}</td>
                <td class="normal passed">{suite.result.passed}</td>
                <td class="normal failed">{suite.result.failed}</td>
                <td class="normal blocked">{suite.result.blocked}</td>
                <td class="normal ignored">{suite.result.ignored}</td>
                <td class="normal time">{suite.time}</td>
                <td class="normal operate">
                  <a href="details_report.html#{suite.name}" or
                          "failures_report.html#{suite.name}">
                  <div class="operate"></div></a>
                </td>
            </tr>
            ...
            </table>
        """
        replace_str = "<!--{suites.context}-->"

        suites_context = "<table class='suites'>\n"
        suites_context = "%s%s" % (suites_context, self._get_suites_title())
        for index, suite in enumerate(suites):
            # construct suite context
            suite_name = getattr(suite, "name", self.PLACE_HOLDER)
            suite_context = "<tr>\n  " if index % 2 == 0 else \
                "<tr class='background-color'>\n  "
            for key in Suite.keys:
                if hasattr(Result(), key):
                    result = getattr(suite, ReportConstant.result, Result())
                    text = getattr(result, key, self.PLACE_HOLDER)
                else:
                    text = getattr(suite, key, self.PLACE_HOLDER)
                suite_context = "{}{}".format(
                    suite_context, self._add_suite_td_context(key, text))
            if suite.result.total == 0:
                href = "%s#%s" % (
                    ReportConstant.failures_vision_report, suite_name)
            else:
                href = "%s#%s" % (
                    ReportConstant.details_vision_report, suite_name)
            suite_context = "{}{}".format(
                suite_context,
                "<td class='normal operate'><a href='%s'><div class='operate'>"
                "</div></a></td>\n</tr>\n" % href)
            # add suite context to suites context
            suites_context = "{}{}".format(suites_context, suite_context)

        suites_context = "%s</table>\n" % suites_context
        return file_context.replace(replace_str, suites_context)

    @classmethod
    def _get_suites_title(cls):
        suites_title = "<tr>\n" \
                       "  <th class='title' colspan='9'>Test detail</th>\n" \
                       "</tr>\n" \
                       "<tr>\n" \
                       "  <th class='normal module'>Module</th>\n" \
                       "  <th class='normal test-suite'>Testsuite</th>\n" \
                       "  <th class='normal total'>Total Tests</th>\n" \
                       "  <th class='normal passed'>Passed</th>\n" \
                       "  <th class='normal failed'>Failed</th>\n" \
                       "  <th class='normal blocked'>Blocked</th>\n" \
                       "  <th class='normal ignored'>Ignored</th>\n" \
                       "  <th class='normal time'>Time</th>\n" \
                       "  <th class='normal operate'>Operate</th>\n" \
                       "</tr>\n"
        return suites_title

    @staticmethod
    def _add_suite_td_context(style, text):
        if style == ReportConstant.name:
            style = "test-suite"
        td_style_class = "normal %s" % style
        return "<td class='%s'>%s</td>\n  " % (td_style_class, str(text))

    def _render_cases(self, file_context, suites):
        """construct cases context and render it to file context
        case table sample:
            <table class="test-suite">
            <tr>
                <th class="title" colspan="4" id="{suite.name}">
                    <span class="title">{suite.name}&nbsp;&nbsp;</span>
                    <a href="summary_report.html#summary">
                    <span class="return"></span></a>
                </th>
            </tr>
            <tr>
                <th class="normal module">Module</th>
                <th class="normal test-suite">Testsuite</th>
                <th class="normal test">Test</th>
                <th class="normal time">Time</th>
                <th class="normal status"><div class="circle-normal
                    circle-white"></div></th>
                <th class="normal result">Result</th>
            </tr>
            <tr [class="background-color"]>
                <td class="normal module">{case.module}</td>
                <td class="normal test-suite">{case.classname}</td>
                <td class="normal test">{case.name}</td>
                <td class="normal time">{case.time}</td>
                <td class="normal status"><div class="circle-normal
                    circle-{case.result/status}"></div></td>
                <td class="normal result">
                    [<a href="failures_report.html#{suite.name}.{case.name}">]
                    {case.result/status}[</a>]</td>
            </tr>
            ...
            </table>
            ...
        """
        replace_str = "<!--{cases.context}-->"
        cases_context = ""
        for suite in suites:
            # construct case context
            suite_name = getattr(suite, "name", self.PLACE_HOLDER)
            case_context = "<table class='test-suite'>\n"
            case_context = "{}{}".format(case_context,
                                         self._get_case_title(suite_name))
            for index, case in enumerate(suite.cases):
                case_context = "{}{}".format(
                    case_context,
                    self._get_case_td_context(index, case, suite_name))
            case_context = "%s</table>\n" % case_context

            # add case context to cases context
            cases_context = "{}{}".format(cases_context, case_context)
        return file_context.replace(replace_str, cases_context)

    @classmethod
    def _get_case_td_context(cls, index, case, suite_name):
        result = case.get_result()
        rendered_result = result
        if result != ReportConstant.passed and \
                result != ReportConstant.ignored:
            rendered_result = "<a href='%s#%s.%s'>%s</a>" % \
                              (ReportConstant.failures_vision_report,
                               suite_name, case.name, result)
        case_td_context = "<tr>\n" if index % 2 == 0 else \
            "<tr class='background-color'>\n"
        case_td_context = "{}{}".format(
            case_td_context,
            "  <td class='normal module'>%s</td>\n"
            "  <td class='normal test-suite'>%s</td>\n"
            "  <td class='normal test'>%s</td>\n"
            "  <td class='normal time'>%s</td>\n"
            "  <td class='normal status'>"
            "<div class='circle-normal circle-%s'></div></td>\n"
            "  <td class='normal result'>%s</td>\n"
            "</tr>\n" % (case.module, case.classname, case.name, case.time,
                         result, rendered_result))
        return case_td_context

    @classmethod
    def _get_case_title(cls, suite_name):
        case_title = \
            "<tr>\n" \
            "  <th class='title' colspan='4' id='%s'>\n" \
            "    <span class='title'>%s&nbsp;&nbsp;</span>\n" \
            "    <a href='%s#summary'>\n" \
            "    <span class='return'></span></a>\n" \
            "  </th>\n"  \
            "</tr>\n"  \
            "<tr>\n" \
            "  <th class='normal module'>Module</th>\n" \
            "  <th class='normal test-suite'>Testsuite</th>\n" \
            "  <th class='normal test'>Test</th>\n" \
            "  <th class='normal time'>Time</th>\n" \
            "  <th class='normal status'><div class='circle-normal " \
            "circle-white'></div></th>\n" \
            "  <th class='normal result'>Result</th>\n" \
            "</tr>\n" % (suite_name, suite_name,
                         ReportConstant.summary_vision_report)
        return case_title

    def _render_failure_cases(self, file_context, suites):
        """construct failure cases context and render it to file context
        failure case table sample:
            <table class="failure-test">
            <tr>
                <th class="title" colspan="4" id="{suite.name}">
                    <span class="title">{suite.name}&nbsp;&nbsp;</span>
                    <a href="details_report.html#{suite.name}" or
                            "summary_report.html#summary">
                    <span class="return"></span></a>
                </th>
            </tr>
            <tr>
                <th class="normal test">Test</th>
                <th class="normal status"><div class="circle-normal
                circle-white"></div></th>
                <th class="normal result">Result</th>
                <th class="normal details">Details</th>
            </tr>
            <tr [class="background-color"]>
                <td class="normal test" id="{suite.name}">
                    {suite.module}#{suite.name}</td>
                or
                <td class="normal test" id="{suite.name}.{case.name}">
                    {case.module}#{case.classname}#{case.name}</td>
                <td class="normal status"><div class="circle-normal
                    circle-{case.result/status}"></div></td>
                <td class="normal result">{case.result/status}</td>
                <td class="normal details">{case.message}</td>
            </tr>
            ...
            </table>
            ...
        """
        replace_str = "<!--{failures.context}-->"
        failure_cases_context = ""
        for suite in suites:
            if suite.result.total == (
                    suite.result.passed + suite.result.ignored) and \
                    suite.result.unavailable == 0:
                continue

            # construct failure cases context for failure suite
            suite_name = getattr(suite, "name", self.PLACE_HOLDER)
            case_context = "<table class='failure-test'>\n"
            case_context = \
                "{}{}".format(case_context, self._get_failure_case_title(
                        suite_name, suite.result.total))
            if suite.result.total == 0:
                case_context = "{}{}".format(
                    case_context, self._get_failure_case_td_context(
                       0, suite, suite_name, ReportConstant.unavailable))
            else:
                skipped_num = 0
                for index, case in enumerate(suite.cases):
                    result = case.get_result()
                    if result == ReportConstant.passed or \
                            result == ReportConstant.ignored:
                        skipped_num += 1
                        continue
                    case_context = "{}{}".format(
                        case_context, self._get_failure_case_td_context(
                          index - skipped_num, case, suite_name, result))

            case_context = "%s</table>\n" % case_context

            # add case context to cases context
            failure_cases_context = \
                "{}{}".format(failure_cases_context, case_context)
        return file_context.replace(replace_str, failure_cases_context)

    @classmethod
    def _get_failure_case_td_context(cls, index, case, suite_name, result):
        failure_case_td_context = "<tr>\n" if index % 2 == 0 else \
            "<tr class='background-color'>\n"
        if result == ReportConstant.unavailable:
            test_context = "%s#%s" % (case.module, case.name)
            href_id = suite_name
        else:
            test_context = \
                "%s#%s#%s" % (case.module, case.classname, case.name)
            href_id = "%s.%s" % (suite_name, case.name)
        details_context = case.message
        if details_context:
            details_context = str(details_context).replace("<", "&lt;"). \
                replace(">", "&gt;").replace("\\r\\n", "<br/>"). \
                replace("\\n", "<br/>").replace("\n", "<br/>")
        failure_case_td_context = "{}{}".format(
            failure_case_td_context,
            "  <td class='normal test' id='%s'>%s</td>\n"
            "  <td class='normal status'>"
            "<div class='circle-normal circle-%s'></div></td>\n"
            "  <td class='normal result'>%s</td>\n"
            "  <td class='normal details'>%s</td>\n"
            "</tr>\n" %
            (href_id, test_context, result, result, details_context))
        return failure_case_td_context

    @classmethod
    def _get_failure_case_title(cls, suite_name, total):
        if total == 0:
            href = "%s#summary" % ReportConstant.summary_vision_report
        else:
            href = "%s#%s" % (ReportConstant.details_vision_report, suite_name)
        failure_case_title = \
            "<tr>\n" \
            "  <th class='title' colspan='4' id='%s'>\n" \
            "    <span class='title'>%s&nbsp;&nbsp;</span>\n" \
            "    <a href='%s'>\n" \
            "    <span class='return'></span></a>\n" \
            "  </th>\n"  \
            "</tr>\n" \
            "<tr>\n" \
            "  <th class='normal test'>Test</th>\n"  \
            "  <th class='normal status'><div class='circle-normal " \
            "circle-white'></div></th>\n" \
            "  <th class='normal result'>Result</th>\n" \
            "  <th class='normal details'>Details</th>\n" \
            "</tr>\n" % (suite_name, suite_name, href)
        return failure_case_title

    @staticmethod
    def generate_report(summary_vision_path, report_context):
        vision_file = open(summary_vision_path, "wb")
        if check_pub_key_exist():
            cipher_text = do_rsa_encrypt(report_context)
            vision_file.write(cipher_text)
        else:
            vision_file.write(bytes(report_context, "utf-8"))
        vision_file.close()
        LOG.info("generate vision report: %s", summary_vision_path)
