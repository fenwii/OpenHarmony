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
import sys
from dataclasses import dataclass

__all__ = ["Variables"]

SRC_DIR = os.path.abspath(os.path.dirname(os.path.dirname(__file__)))
MODULES_DIR = os.path.abspath(os.path.dirname(__file__))
TOP_DIR = os.path.abspath(
    os.path.dirname(os.path.dirname(os.path.dirname(__file__))))
sys.path.insert(0, SRC_DIR)
sys.path.insert(1, MODULES_DIR)
sys.path.insert(2, TOP_DIR)


@dataclass
class ReportVariables:
    report_dir = ""
    log_dir = ""
    log_format = ""
    log_level = ""
    log_handler = ""
    pub_key_file = None


@dataclass
class Variables:
    modules_dir = ""
    top_dir = ""
    res_dir = ""
    exec_dir = ""
    report_vars = ReportVariables()
    task_name = ""
    source_code_rootpath = ""


def _init_global_config():
    import logging

    from _core.common import get_source_code_rootpath

    Variables.modules_dir = MODULES_DIR
    Variables.top_dir = TOP_DIR
    Variables.res_dir = os.path.abspath(os.path.join(
        MODULES_DIR, "_core", "resource"))

    # set report variables
    Variables.report_vars.log_dir = "log"
    Variables.report_vars.report_dir = "reports"
    Variables.report_vars.log_format = "%(asctime)s %(name)-15s " \
                                       "%(levelname)-8s %(message)s"
    Variables.report_vars.log_level = logging.INFO
    Variables.report_vars.log_handler = "console, file"

    # set execution directory
    if not Variables.exec_dir:
        current_exec_dir = os.path.abspath(os.getcwd())
        try:
            common_path = os.path.commonpath([Variables.top_dir,
                                              current_exec_dir])
            if os.path.normcase(common_path) == os.path.normcase(
                    Variables.top_dir):
                Variables.exec_dir = common_path
            else:
                Variables.exec_dir = current_exec_dir
        except (ValueError, AttributeError):
            Variables.exec_dir = current_exec_dir
    Variables.source_code_rootpath = get_source_code_rootpath(
        Variables.top_dir)
    _init_logger()


def _init_logger():
    import time
    from _core.constants import LogType
    from _core.logger import Log
    from _core.plugin import Plugin
    from _core.plugin import get_plugin

    tool_logger_plugin = get_plugin(Plugin.LOG, LogType.tool)
    if tool_logger_plugin:
        return

    @Plugin(type=Plugin.LOG, id=LogType.tool, enabled=True)
    class ToolLog(Log):
        @classmethod
        def get_plugin_type(cls):
            return Plugin.LOG

        @classmethod
        def get_plugin_id(cls):
            return LogType.tool

    tool_log_file = None
    if Variables.exec_dir and os.path.normcase(
            Variables.exec_dir) == os.path.normcase(Variables.top_dir):
        host_log_path = os.path.join(Variables.exec_dir,
                                     Variables.report_vars.report_dir,
                                     Variables.report_vars.log_dir)
        os.makedirs(host_log_path, exist_ok=True)
        time_str = time.strftime('%Y-%m-%d-%H-%M-%S', time.localtime())
        tool_file_name = "platform_log_{}.log".format(time_str)
        tool_log_file = os.path.join(host_log_path, tool_file_name)

    tool_logger_plugin = get_plugin(Plugin.LOG, LogType.tool)[0] or ToolLog()
    tool_logger_plugin.__initial__(Variables.report_vars.log_handler,
                                   tool_log_file,
                                   Variables.report_vars.log_level,
                                   Variables.report_vars.log_format)


def _iter_module_plugins(packages):
    import importlib
    import pkgutil
    for package in packages:
        pkg_path = getattr(package, "__path__", "")
        pkg_name = getattr(package, "__name__", "")
        if not pkg_name or not pkg_path:
            continue

        _iter_modules = pkgutil.iter_modules(pkg_path, "%s%s" % (
            pkg_name, "."))
        for _, name, _ in _iter_modules:
            importlib.import_module(name)


def _load_internal_plugins():
    import _core.driver
    import _core.testkit
    import _core.environment
    import _core.executor
    _iter_module_plugins([_core.driver, _core.testkit, _core.environment,
                          _core.executor])


_init_global_config()
_load_internal_plugins()

del _init_global_config
del _init_logger
del _load_internal_plugins
del _iter_module_plugins
