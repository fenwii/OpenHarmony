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

import logging
import sys
from logging.handlers import RotatingFileHandler

from _core.constants import LogType
from _core.plugin import Plugin
from _core.plugin import get_plugin

__all__ = ["Log", "platform_logger", "device_logger", "shutdown",
           "add_task_file_handler", "remove_task_file_handler"]

_HANDLERS = []
_LOGGERS = []
MAX_LOG_LENGTH = 10 * 1024 * 1024


class Log:
    task_file_handler = None

    def __init__(self):
        self.level = logging.INFO
        self.handlers = []
        self.loggers = {}
        self.task_file_handler = None

    def __initial__(self, log_handler_flag, log_file=None, level=None,
                    log_format=None):
        if _LOGGERS:
            return

        self.handlers = []
        if log_file and "console" in log_handler_flag:
            file_handler = RotatingFileHandler(
                log_file, mode="a", maxBytes=MAX_LOG_LENGTH, backupCount=5,
                encoding="UTF-8")
            file_handler.setFormatter(logging.Formatter(log_format))
            self.handlers.append(file_handler)
        if "console" in log_handler_flag:
            stream_handler = logging.StreamHandler(sys.stdout)
            stream_handler.setFormatter(logging.Formatter(log_format))
            self.handlers.append(stream_handler)

        if level:
            self.level = level
        self.loggers = {}
        self.task_file_handler = None
        _HANDLERS.extend(self.handlers)

    def __logger__(self, name=None):
        if not name:
            return _init_global_logger(name)
        elif name in self.loggers:
            return self.loggers.get(name)
        else:
            log = self.loggers.setdefault(name, FrameworkLog(name))
            _LOGGERS.append(log)
            log.platform_log.setLevel(self.level)
            for handler in self.handlers:
                log.platform_log.addHandler(handler)
            if self.task_file_handler:
                log.add_task_log(self.task_file_handler)
            return log

    def add_task_file_handler(self, log_file):
        from xdevice import Variables
        file_handler = RotatingFileHandler(
                log_file, mode="a", maxBytes=MAX_LOG_LENGTH, backupCount=5,
                encoding="UTF-8")
        file_handler.setFormatter(logging.Formatter(
            Variables.report_vars.log_format))
        self.task_file_handler = file_handler
        for _, log in self.loggers.items():
            log.add_task_log(self.task_file_handler)

    def remove_task_file_handler(self):
        if self.task_file_handler is None:
            return
        for _, log in self.loggers.items():
            log.remove_task_log(self.task_file_handler)
        self.task_file_handler.close()
        self.task_file_handler = None


class FrameworkLog:

    def __init__(self, name):
        self.name = name
        self.platform_log = logging.Logger(name)
        self.task_log = None

    def add_task_log(self, handler):
        if self.task_log:
            return
        self.task_log = logging.Logger(self.name)
        self.task_log.setLevel(logging.DEBUG)
        self.task_log.addHandler(handler)

    def remove_task_log(self, handler):
        if not self.task_log:
            return
        self.task_log.removeHandler(handler)
        self.task_log = None

    def info(self, msg, *args, **kwargs):
        self.platform_log.info(msg, *args, **kwargs)
        if self.task_log:
            self.task_log.info(msg, *args, **kwargs)

    def debug(self, msg, *args, **kwargs):
        self.platform_log.debug(msg, *args, **kwargs)
        if self.task_log:
            self.task_log.debug(msg, *args, **kwargs)

    def error(self, msg, *args, **kwargs):
        self.platform_log.error(msg, *args, **kwargs)
        if self.task_log:
            self.task_log.error(msg, *args, **kwargs)

    def warning(self, msg, *args, **kwargs):
        self.platform_log.warning(msg, *args, **kwargs)
        if self.task_log:
            self.task_log.warning(msg, *args, **kwargs)

    def exception(self, msg, exc_info=True, **kwargs):
        self.platform_log.exception(msg, exc_info=exc_info, **kwargs)
        if self.task_log:
            self.task_log.exception(msg, exc_info=exc_info, **kwargs)


def platform_logger(name=None):
    plugins = get_plugin(Plugin.LOG, LogType.tool)
    for log_plugin in plugins:
        if log_plugin.get_plugin_config().enabled:
            return log_plugin.__logger__(name)
    return _init_global_logger(name)


def device_logger(name=None):
    plugins = get_plugin(Plugin.LOG, LogType.device)
    for log_plugin in plugins:
        if log_plugin.get_plugin_config().enabled:
            return log_plugin.__logger__(name)
    return _init_global_logger(name)


def shutdown():
    # logging will be shutdown automatically, when the program exits.
    # This function is used by testing.
    for log in _LOGGERS:
        for handler in log.handlers:
            log.removeHandler(handler)
    for handler in _HANDLERS:
        handler.close()
    _HANDLERS.clear()
    _LOGGERS.clear()


def add_task_file_handler(log_file=None):
    if log_file is None:
        return
    plugins = get_plugin(Plugin.LOG, LogType.tool)
    for log_plugin in plugins:
        if log_plugin.get_plugin_config().enabled:
            log_plugin.add_task_file_handler(log_file)


def remove_task_file_handler():
    plugins = get_plugin(Plugin.LOG, LogType.tool)
    for log_plugin in plugins:
        if log_plugin.get_plugin_config().enabled:
            log_plugin.remove_task_file_handler()


def _init_global_logger(name=None):
    handler = logging.StreamHandler(sys.stdout)
    log_format = "%(asctime)s %(name)-15s %(levelname)-8s %(message)s"
    handler.setFormatter(logging.Formatter(log_format))
    log = logging.Logger(name)
    log.setLevel(logging.INFO)
    log.addHandler(handler)
    return log
