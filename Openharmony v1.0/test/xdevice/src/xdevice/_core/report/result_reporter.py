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
import time
import zipfile
from ast import literal_eval

from _core.logger import platform_logger
from _core.report.encrypt import check_pub_key_exist
from _core.report.encrypt import do_rsa_encrypt
from _core.report.encrypt import get_file_summary
from _core.report.reporter_helper import DataHelper
from _core.report.reporter_helper import VisionHelper
from _core.report.reporter_helper import ReportConstant

LOG = platform_logger("ResultReporter")


class ResultReporter:

    def __init__(self, report_path, task_info):
        self.report_path = report_path
        self.task_info = task_info
        self.data_helper = DataHelper()
        self.vision_helper = VisionHelper()
        self.summary_data_path = os.path.join(
            self.report_path, ReportConstant.summary_data_report)
        self.exec_info = task_info

    def generate_reports(self):
        LOG.info("")
        LOG.info("**************************************************")
        LOG.info("************** Start generate reports ************")
        LOG.info("**************************************************")
        LOG.info("")

        # generate data report
        self._generate_data_report()

        # generate vision reports
        self._generate_vision_reports()

        # generate summary ini
        self._generate_summary()

        # copy reports to reports/latest folder
        self._copy_report()

        # compress report folder
        self._compress_report_folder()

        LOG.info("")
        LOG.info("**************************************************")
        LOG.info("************** Ended generate reports ************")
        LOG.info("**************************************************")
        LOG.info("")

    def _generate_data_report(self):
        # initial element
        test_suites_element = self.data_helper.initial_suites_element()

        # update test suites element
        update_flag = self._update_test_suites(test_suites_element)
        if not update_flag:
            return

        # generate report
        if not self._check_mode(ReportConstant.decc_mode):
            self.data_helper.generate_report(test_suites_element,
                                             self.summary_data_path)

        # set SuiteReporter.suite_report_result
        if not check_pub_key_exist() and not self._check_mode(
                ReportConstant.decc_mode):
            return
        from xdevice import SuiteReporter
        SuiteReporter.suite_report_result = [(
            self.summary_data_path, DataHelper.to_string(
                test_suites_element))]

        if self._check_mode(ReportConstant.decc_mode):
            try:
                from devicetest.agent.auth_server import Handler
                from xdevice import Scheduler
                Handler.upload_task_summary_results(
                    SuiteReporter.suite_report_result[0][1])
                tmp_element = self.data_helper.initial_suites_element()
                for child in test_suites_element:
                    result, _ = Scheduler.get_script_result(child)
                    if result == "Passed":
                        tmp_element.append(child)
                SuiteReporter.suite_report_result = [(
                    self.summary_data_path, DataHelper.to_string(tmp_element))]
            except ModuleNotFoundError as error:
                LOG.error("module not found %s", error.args)

    def _update_test_suites(self, test_suites_element):
        # initial attributes for test suites element
        test_suites_attributes, need_update_attributes = \
            self._init_attributes()

        # get test suite elements that are children of test suites element
        modules = dict()
        test_suite_elements = []
        for data_report, module_name in self.data_reports:
            if data_report.endswith(ReportConstant.summary_data_report):
                continue
            root = self.data_helper.parse_data_report(data_report)
            if module_name == ReportConstant.empty_name:
                module_name = self._get_module_name(data_report, root)
            total = int(root.get(ReportConstant.tests, 0))
            modules[module_name] = modules.get(module_name, 0) + total

            self._append_product_params(test_suites_attributes, root)
            for child in root:
                child.tail = self.data_helper.LINE_BREAK_INDENT
                if not child.get(ReportConstant.module) or child.get(
                        ReportConstant.module) == ReportConstant.empty_name:
                    child.set(ReportConstant.module, module_name)
                self._check_tests_and_unavailable(child)
                test_suite_elements.append(child)
                for update_attribute in need_update_attributes:
                    update_value = child.get(update_attribute, 0)
                    if not update_value:
                        update_value = 0
                    test_suites_attributes[update_attribute] += int(
                        update_value)

        if test_suite_elements:
            child = test_suite_elements[-1]
            child.tail = self.data_helper.LINE_BREAK
        else:
            LOG.error("execute result not exists")
            return False

        # set test suites element attributes and children
        modules_zero = [module_name for module_name, total in modules.items()
                        if total == 0]
        if modules_zero:
            LOG.info("the total tests of %s module is 0", ",".join(
                modules_zero))
        test_suites_attributes[ReportConstant.modules_done] = \
            len(modules) - len(modules_zero)
        test_suites_attributes[ReportConstant.modules] = len(modules)
        self.data_helper.set_element_attributes(test_suites_element,
                                                test_suites_attributes)
        test_suites_element.extend(test_suite_elements)
        return True

    @classmethod
    def _check_tests_and_unavailable(cls, child):
        total = child.get(ReportConstant.tests, "0")
        unavailable = child.get(ReportConstant.unavailable, "0")
        if total and total != "0" and unavailable and \
                unavailable != "0":
            child.set(ReportConstant.unavailable, "0")
            LOG.warning("%s total: %s, unavailable: %s", child.get(
                ReportConstant.name), total, unavailable)

    @classmethod
    def _append_product_params(cls, test_suites_attributes, root):
        product_params = root.get(ReportConstant.product_params, "")
        if not product_params:
            return
        try:
            product_params = literal_eval(str(product_params))
        except SyntaxError as error:
            LOG.error("%s %s", root.get(ReportConstant.name, ""), error.args)
            return

        if not test_suites_attributes[ReportConstant.product_params]:
            test_suites_attributes[ReportConstant.product_params] = \
                product_params
            return
        for key, value in product_params.items():
            exist_value = test_suites_attributes[
                ReportConstant.product_params].get(key, "")

            if not exist_value:
                test_suites_attributes[
                    ReportConstant.product_params][key] = value
                continue
            if value in exist_value:
                continue
            test_suites_attributes[ReportConstant.product_params][key] = \
                "%s,%s" % (exist_value, value)

    @classmethod
    def _get_module_name(cls, data_report, root):
        # get module name from data report
        from _core.utils import get_filename_extension
        module_name = get_filename_extension(data_report)[0]
        if "report" in module_name or "summary" in module_name or \
                "<" in data_report or ">" in data_report:
            module_name = root.get(ReportConstant.name,
                                   ReportConstant.empty_name)
            if "report" in module_name or "summary" in module_name:
                module_name = ReportConstant.empty_name
        return module_name

    def _init_attributes(self):
        test_suites_attributes = {
            ReportConstant.name:
                ReportConstant.summary_data_report.split(".")[0],
            ReportConstant.start_time: self.task_info.test_time,
            ReportConstant.end_time: time.strftime(ReportConstant.time_format,
                                                   time.localtime()),
            ReportConstant.errors: 0, ReportConstant.disabled: 0,
            ReportConstant.failures: 0, ReportConstant.tests: 0,
            ReportConstant.ignored: 0, ReportConstant.unavailable: 0,
            ReportConstant.product_params: self.task_info.product_params,
            ReportConstant.modules: 0, ReportConstant.modules_done: 0}
        need_update_attributes = [ReportConstant.tests, ReportConstant.ignored,
                                  ReportConstant.failures,
                                  ReportConstant.disabled,
                                  ReportConstant.errors,
                                  ReportConstant.unavailable]
        return test_suites_attributes, need_update_attributes

    def _generate_vision_reports(self):
        if not self.summary_data_report_exist:
            LOG.error("summary data report not exists")
            return

        if check_pub_key_exist():
            from xdevice import SuiteReporter
            if not SuiteReporter.get_report_result():
                LOG.error("summary data report not exists")
                return
            self.summary_data_path = SuiteReporter.get_report_result()[0][1]
            SuiteReporter.clear_report_result()

        # parse data
        summary_element_tree = self.data_helper.parse_data_report(
            self.summary_data_path)
        parsed_data = self.vision_helper.parse_element_data(
            summary_element_tree, self.report_path, self.task_info)
        self.exec_info, summary, _ = parsed_data
        if not check_pub_key_exist():
            LOG.info("Summary result: modules: %s, modules done: %s, total: "
                     "%s, passed: %s, failed: %s, blocked: %s, ignored: %s, "
                     "unavailable: %s", summary.modules, summary.modules_done,
                     summary.result.total, summary.result.passed,
                     summary.result.failed, summary.result.blocked,
                     summary.result.ignored, summary.result.unavailable)
        LOG.info("Log path: %s", self.exec_info.log_path)

        # generate summary vision report
        report_generate_flag = self._generate_vision_report(
            parsed_data, ReportConstant.summary_title,
            ReportConstant.summary_vision_report)

        # generate details vision report
        if report_generate_flag and summary.result.total > 0:
            self._generate_vision_report(
                parsed_data, ReportConstant.details_title,
                ReportConstant.details_vision_report)

        # generate failures vision report
        if summary.result.total != (
                summary.result.passed + summary.result.ignored) or \
                summary.result.unavailable > 0:
            self._generate_vision_report(
                parsed_data, ReportConstant.failures_title,
                ReportConstant.failures_vision_report)

    def _generate_vision_report(self, parsed_data, title, render_target):

        # render data
        report_context = self.vision_helper.render_data(
            title, parsed_data, render_target=render_target)

        # generate report
        if report_context:
            report_path = os.path.join(self.report_path, render_target)
            self.vision_helper.generate_report(report_path, report_context)
            return True
        else:
            LOG.error("Failed to generate %s", render_target)
            return False

    @property
    def summary_data_report_exist(self):
        if self._check_mode(ReportConstant.decc_mode):
            return False
        return os.path.exists(self.summary_data_path) or (
            "<" in self.summary_data_path and ">" in self.summary_data_path)

    @property
    def data_reports(self):
        if check_pub_key_exist() or self._check_mode(ReportConstant.decc_mode):
            from xdevice import SuiteReporter
            suite_reports = SuiteReporter.get_report_result()
            data_reports = [(suite_report[1], ReportConstant.empty_name) for
                            suite_report in suite_reports]
            SuiteReporter.clear_report_result()
            return data_reports

        if not os.path.isdir(self.report_path):
            return []
        data_reports = []
        result_path = os.path.join(self.report_path, "result")
        for root, _, files in os.walk(self.report_path):
            for file_name in files:
                if not file_name.endswith(self.data_helper.DATA_REPORT_SUFFIX):
                    continue
                module_name = self._find_module_name(result_path, root)
                data_reports.append((os.path.join(root, file_name),
                                     module_name))
        return data_reports

    @classmethod
    def _find_module_name(cls, result_path, root):
        # find module name from directory tree
        common_path = os.path.commonpath([result_path, root])
        if os.path.normcase(result_path) != os.path.normcase(common_path) or \
                os.path.normcase(result_path) == os.path.normcase(root):
            return ReportConstant.empty_name

        root_dir, module_name = os.path.split(root)
        if os.path.normcase(result_path) == os.path.normcase(root_dir):
            return ReportConstant.empty_name
        root_dir, subsystem_name = os.path.split(root_dir)
        while os.path.normcase(result_path) != os.path.normcase(root_dir):
            module_name = subsystem_name
            root_dir, subsystem_name = os.path.split(root_dir)
        return module_name

    def _generate_summary(self):
        if not self.summary_data_report_exist:
            return
        summary_ini_content = \
            "[default]\n" \
            "Platform=%s\n" \
            "Test Type=%s\n" \
            "Device Name=%s\n" \
            "Host Info=%s\n" \
            "Test Start/ End Time=%s\n" \
            "Execution Time=%s\n" % (
                self.exec_info.platform, self.exec_info.test_type,
                self.exec_info.device_name, self.exec_info.host_info,
                self.exec_info.test_time, self.exec_info.execute_time)
        if self.exec_info.product_params:
            for key, value in self.exec_info.product_params.items():
                summary_ini_content = "{}{}".format(
                    summary_ini_content, "%s=%s\n" % (key, value))
        summary_ini_content = "{}{}".format(
            summary_ini_content, "Log Path=%s\n" % self.exec_info.log_path)

        # write summary_ini_content
        summary_filepath = os.path.join(self.report_path,
                                        ReportConstant.summary_ini)
        with open(summary_filepath, 'wb') as file_handler:
            if check_pub_key_exist():
                cipher_text = do_rsa_encrypt(summary_ini_content)
                file_handler.write(cipher_text)
            else:
                file_handler.write(bytes(summary_ini_content, 'utf-8'))
            LOG.info("generate summary ini: %s", summary_filepath)

    def _copy_report(self):
        from xdevice import Scheduler
        if Scheduler.upload_address:
            return

        from xdevice import Variables
        dst_path = os.path.join(Variables.exec_dir,
                                Variables.report_vars.report_dir, "latest")
        try:
            shutil.rmtree(dst_path, ignore_errors=True)
            os.makedirs(dst_path, exist_ok=True)
            LOG.info("copy summary files to %s", dst_path)

            # copy reports to reports/latest folder
            for report_file in os.listdir(self.report_path):
                src_file = os.path.join(self.report_path, report_file)
                dst_file = os.path.join(dst_path, report_file)
                if os.path.isfile(src_file):
                    shutil.copyfile(src_file, dst_file)
        except OSError:
            return

    def _compress_report_folder(self):
        if not os.path.isdir(self.report_path):
            LOG.error("'%s' is not folder!" % self.report_path)
            return
        if self._check_mode(ReportConstant.decc_mode):
            return

        # get file path list
        file_path_list = []
        for dir_path, _, file_names in os.walk(self.report_path):
            f_path = dir_path.replace(self.report_path, '')
            f_path = f_path and f_path + os.sep or ''
            for filename in file_names:
                file_path_list.append(
                    (os.path.join(dir_path, filename), f_path + filename))

        # compress file
        zipped_file = "%s.zip" % os.path.join(
            self.report_path, os.path.basename(self.report_path))
        zip_object = zipfile.ZipFile(zipped_file, 'w', zipfile.ZIP_DEFLATED,
                                     allowZip64=True)
        try:
            LOG.info("executing compress process, please wait...")
            for src_path, target_path in file_path_list:
                zip_object.write(src_path, target_path)
            LOG.info("generate zip file: %s", zipped_file)
        except zipfile.BadZipFile as bad_error:
            LOG.error("zip report folder error: %s" % bad_error.args)
        finally:
            zip_object.close()

        # generate hex digest, then save it to summary_report.hash
        hash_file = os.path.abspath(os.path.join(
            self.report_path, ReportConstant.summary_report_hash))
        with open(hash_file, "w") as hash_file_handler:
            hash_file_handler.write(get_file_summary(zipped_file))
            LOG.info("generate hash file: %s", hash_file)
        return zipped_file

    @classmethod
    def _check_mode(cls, mode):
        from xdevice import Scheduler
        return Scheduler.mode == mode
