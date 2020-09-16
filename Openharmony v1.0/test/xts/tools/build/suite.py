#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Copyright (c) 2020 Huawei Device Co., Ltd.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
"""


import os
import sys
import argparse
import re
import subprocess
import xml.dom.minidom
from xml.parsers.expat import ExpatError
from string import Template
import utils
import json
import shutil
import platform


class SuiteModuleBuilder:
    """
    To Build Suite Module
    @arguments(build_target_name, target_file...)
    """

    def __init__(self, arguments):
        self.arguments = arguments
        self.args = None

    def build_module(self):
        """
        build_target_name='wifiaware_test',
        javalib_file=None,
        project_path='xxx/communication_lite/wifiaware',
        project_type='hctest',
        source_path='xxx/x.c,xxx/x.c
        subsystem_name='communication',
        suite_filename='libwifiaware_test.a',
        suite_out_paths='out/x/suites/acts/testcases/communication,'
        target_file='xxxx/libs/libmodule_wifiaware_test.a',
        test_xml='xxx/Test.json'
        :return:
        """

        parser = argparse.ArgumentParser()
        parser.add_argument('--build_target_name', help='', required=False)
        parser.add_argument('--target_file', help='', required=True)
        parser.add_argument('--javalib_file', help='', required=False)
        parser.add_argument('--project_path', help='', required=True)
        parser.add_argument('--test_xml', help='', required=False)
        parser.add_argument('--project_type', help='', required=True)
        parser.add_argument('--suite_out_paths', help='', required=True)
        parser.add_argument('--suite_filename', help='', required=True)
        parser.add_argument('--subsystem_name', help='', required=False)

        self.args = parser.parse_args(self.arguments)

        for one_file in self.args.target_file.rstrip(",").split(","):
            self._check_file_exist(one_file)

        for _suite_out_file in self.args.suite_out_paths.split(","):
            if not _suite_out_file:
                continue
            if self.args.project_type == "pythontest":
                _out_file = _suite_out_file
            else:
                _out_file = os.path.join(_suite_out_file,
                                         self.args.suite_filename)
            if self.args.project_type == "pythontest":
                utils.copy_file(output=_out_file,
                                source_dirs=self.args.target_file,
                                to_dir=True)
            elif self.args.project_type == "open_source_test":
                utils.copy_file(output=_out_file,
                                sources=self.args.target_file,
                                to_dir=True)
            elif self.args.project_type != "hctest":
                utils.copy_file(output=_out_file,
                                sources=self.args.target_file,
                                to_dir=False)
            if self.args.project_type == "apk":
                return
            _testsuite_name = self.args.suite_filename
            _matcher = re.match(r"(lib|libmodule_)?(\S+)\.\S+",
                                _testsuite_name)
            if _matcher:
                _testsuite_name = _matcher.group(2)
            _testcase_xml = os.path.join(_suite_out_file,
                                       _testsuite_name + ".xml")
            if self.args.project_type != "open_source_test":
                _config_file = os.path.join(_suite_out_file,
                                            _testsuite_name + ".json")
            else:
                _config_file = os.path.join(_out_file,
                                            _testsuite_name + ".json")
            utils.record_testmodule_info(self.args.build_target_name,
                                         _testsuite_name,
                                         self.args.subsystem_name,
                                         _suite_out_file)
            _test_xml = self.args.test_xml
            if _test_xml and os.path.exists(_test_xml):
                utils.copy_file(output=_config_file, sources=_test_xml,
                                to_dir=False)
            else:
                self._generate_xml_by_template(_test_xml, _testsuite_name,
                                               _config_file)

    @staticmethod
    def _record_testmodule_info(build_target_name, module_name,
                                subsystem_name, suite_out_dir):
        if not build_target_name or not subsystem_name:
            print(
                'build_target_name or subsystem_name of testmodule "%s" '
                'is invalid!' % module_name)
            return
        module_info_dir = os.path.dirname(suite_out_dir)
        module_info_list_file = os.path.join(module_info_dir,
                                             'module_info.json')
        module_info_data = {}
        if os.path.exists(module_info_list_file):
            try:
                with open(module_info_list_file, 'r') as module_file:
                    module_info_data = json.load(module_file)
            except ValueError:
                print("NO json object could be decoded but continue")
        module_info = {'subsystem': subsystem_name,
                       'build_target_name': build_target_name}
        module_info_data[module_name] = module_info
        with open(module_info_list_file, 'w') as out_file:
            json.dump(module_info_data, out_file)

    def _generate_xml_by_template(self, test_xml, module_name,
                                  config_file):
        index = test_xml.rfind(".json")
        tmpl_file = test_xml[:index] + ".tmpl"
        if not os.path.exists(tmpl_file):
            raise Exception(
                "Can't find the Test.json or Test.tmpl in the "
                "path %s " % os.path.dirname(
                    test_xml))
        tmpl_content = utils.read_file(tmpl_file)
        values = {"module": module_name, "subsystem": self.args.subsystem_name}
        xml_content = Template(tmpl_content).substitute(values)
        utils.write_file(config_file, xml_content, False)

    @staticmethod
    def _check_file_exist(file_path):
        if not os.path.exists(file_path):
            raise Exception("File [%s] does not exist!" % file_path)


class XDeviceBuilder:
    """
    To build XTS as a egg package
    @arguments(project_dir, output_dirs)
    """

    def __init__(self, arguments):
        parser = argparse.ArgumentParser()
        parser.add_argument('--project_dir', help='', required=True)
        parser.add_argument('--output_dirs', help='', required=True)
        self.args = parser.parse_args(arguments)

    def build_xdevice(self):
        """
        build xdevice package
        :return:
        """
        command = [utils.get_python_cmd(), "setup.py", "install", "--user"]
        factory_script = os.path.join(self.args.project_dir, "factory.sh")
        if os.path.exists(factory_script):
            os.chmod(factory_script, 0o775)
            command = factory_script
        try:
            subprocess.check_call(command, cwd=self.args.project_dir)
        except subprocess.CalledProcessError as exc:
            print('returncode: {} cmd: {} output: {}'.format(
                exc.returncode, exc.cmd, exc.output))

        dist_dir = os.path.join(self.args.project_dir, 'dist')
        run_scripts = ",".join(
            [os.path.join(self.args.project_dir, "run.bat"),
             os.path.join(self.args.project_dir, "run.sh")])
        config_dir = os.path.join(self.args.project_dir, "config")
        res_dir = os.path.join(self.args.project_dir, "resource")
        for tool_dir in self.args.output_dirs.split(","):
            if tool_dir:
                utils.copy_file(output=tool_dir, source_dirs=dist_dir,
                                to_dir=True)
                root_dir = os.path.dirname(tool_dir)
                utils.copy_file(output=root_dir, sources=run_scripts,
                                to_dir=True)
                to_dir = os.path.join(root_dir, "config")
                utils.copy_file(output=to_dir, source_dirs=config_dir,
                                to_dir=True)
                utils.copy_file(os.path.join(root_dir, "resource"),
                                source_dirs=res_dir)
        return 0


class SuiteArchiveBuilder:
    def __init__(self, arguments):
        self.module_info_dir = None
        self.arguments = arguments

    def archive_suite(self):
        parser = argparse.ArgumentParser()
        parser.add_argument('--suite_path', help='', required=True)
        parser.add_argument('--testcases_name', help='', required=True)
        parser.add_argument('--prebuilts_resource', help='', required=True)
        parser.add_argument('--build_enabled', help='', required=True)
        args = parser.parse_args(self.arguments)
        if not args.build_enabled.lower() == 'true':
            print('build hit not enabled, skip making archive')
            return 0

        suite_path = args.suite_path
        if not os.path.isdir(suite_path):
            raise Exception("[%s] does not exist" % suite_path)

        # generate module_info.json
        copyfiles = args.prebuilts_resource.split(",")
        for file in copyfiles:
            if os.path.exists(file):
                subprocess.call(["/bin/cp", "-rf", file, suite_path])

        archive_name = os.path.basename(suite_path)
        suite_root_path = os.path.dirname(suite_path)
        # remove the extra output of target "java_prebuilt"
        # such as ztest-tradefed-common.interface.jar
        subprocess.call(
            ["/usr/bin/find", suite_path, "-name", "*.interface.jar",
             "-exec", "rm", "{}", "+"])
        shutil.make_archive(suite_path, "zip", suite_root_path, archive_name)
        return 0


ACTION_MAP = {"build_module": "SuiteModuleBuilder",
              "build_xdevice": "XDeviceBuilder",
              "archive_suite": "SuiteArchiveBuilder",
              }


def _find_action(action, arguments):
    class_name = ACTION_MAP[action]
    if not class_name:
        raise ValueError('Unsupported operation: %s' % action)

    this_module = sys.modules[__name__]
    class_def = getattr(this_module, class_name, None)
    if not class_def:
        raise ValueError(
            'Unsupported operation(No Implementation Class): %s' % action)
    class_obj = class_def(arguments)
    func = getattr(class_obj, action, None)
    if not func:
        raise ValueError(
            'Unsupported operation(No Implementation Method): %s' % action)
    return func


def main(arguments):
    action = arguments[0]
    args = arguments[1:]
    func = _find_action(action, args)
    func()
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
