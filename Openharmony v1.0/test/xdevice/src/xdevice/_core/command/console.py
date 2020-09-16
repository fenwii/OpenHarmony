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

import argparse
import os
import platform
import signal
import sys
import threading

from _core.config.config_manager import UserConfigManager
from _core.constants import SchedulerType
from _core.constants import ToolCommandType
from _core.environment.manager_env import EnvironmentManager
from _core.exception import ParamError
from _core.exception import ExecuteTerminate
from _core.executor.request import Task
from _core.executor.scheduler import Scheduler
from _core.logger import platform_logger
from _core.plugin import Plugin
from _core.plugin import get_plugin
from _core.utils import SplicingAction
from _core.utils import get_instance_name

__all__ = ["Console"]

LOG = platform_logger("Console")
try:
    if platform.system() != 'Windows':
        import readline
except ModuleNotFoundError:
    LOG.warning("readline module is not exist.")


class Console(object):
    """
    Class representing an console for executing test.
    Main xDevice console providing user with the interface to interact
    """
    __instance = None

    def __new__(cls, *args, **kwargs):
        """
        Singleton instance
        """
        if cls.__instance is None:
            cls.__instance = super(Console, cls).__new__(cls, *args, **kwargs)
        return cls.__instance

    def __init__(self):
        pass

    @classmethod
    def handler_terminate_signal(cls, signalnum, frame):
        # ctrl+c
        del signalnum, frame
        if not Scheduler.is_execute:
            return
        LOG.info("get terminate input")
        terminate_thread = threading.Thread(
            target=Scheduler.terminate_cmd_exec)
        terminate_thread.setDaemon(True)
        terminate_thread.start()

    def console(self, args):
        """
        Main xDevice console providing user with the interface to interact
        """
        if sys.version < '3.7':
            LOG.error("Please use python 3.7 or higher version to "
                      "start project")
            sys.exit(0)

        if args is None or len(args) < 2:
            # init environment manager
            EnvironmentManager()
            # Enter xDevice console
            self._console()
        else:
            # init environment manager
            EnvironmentManager()
            # Enter xDevice command parser
            self.command_parser(" ".join(args[1:]))

    def _console(self):
        # Enter xDevice console
        signal.signal(signal.SIGINT, self.handler_terminate_signal)

        while True:
            try:
                usr_input = input(">>> ")
                if usr_input == "":
                    continue

                self.command_parser(usr_input)

            except SystemExit:
                LOG.info("Program exit normally!")
                return
            except ExecuteTerminate:
                LOG.info("execution terminated")
            except (IOError, EOFError, KeyboardInterrupt) as error:
                LOG.exception("Input Error: {}".format(error),
                              exc_info=False)

    def argument_parser(self, para_list):
        """
        argument parser
        """
        options = None
        unparsed = []
        valid_param = True
        parser = None

        try:
            parser = argparse.ArgumentParser(
                description="Specify tests to run.")
            group = parser.add_mutually_exclusive_group()
            parser.add_argument("action",
                                type=str.lower,
                                help="Specify action")
            parser.add_argument("task",
                                type=str,
                                default=None,
                                help="Specify task name")
            parser.add_argument("-sn", "--device_sn",
                                action="store",
                                type=str,
                                dest="device_sn",
                                default="",
                                help="Specify device serial number"
                                )
            group.add_argument("-tf", "--testfile",
                               action=SplicingAction,
                               type=str,
                               nargs='+',
                               dest="testfile",
                               default="",
                               help="Specify test list file"
                               )
            parser.add_argument("-c", "--config",
                                action="store",
                                type=str,
                                dest="config",
                                default="",
                                help="Specify test config file"
                                )
            parser.add_argument("-rp", "--reportpath",
                                action=SplicingAction,
                                type=str,
                                nargs='+',
                                dest="reportpath",
                                default="",
                                help="Specify test report path"
                                )
            parser.add_argument("-e", "--exectype",
                                action="store",
                                type=str,
                                dest="exectype",
                                default="device",
                                help="Specify test execute type"
                                )
            parser.add_argument("-p", "--productform",
                                action="store",
                                type=str,
                                dest="productform",
                                default="phone",
                                help="Specified product form"
                                )
            parser.add_argument("-t", "--testtype",
                                nargs='*',
                                dest="testtype",
                                default=["UT"],
                                help="Specify test type" +
                                     "(UT,MST,ST,PERF,SEC,RELI,DST,ALL)"
                                )
            parser.add_argument("-ss", "--subsystem",
                                action="store",
                                type=str,
                                dest="subsystem",
                                default="",
                                help="Specify test subsystem"
                                )
            parser.add_argument("-tm", "--testmodule",
                                action="store",
                                type=str,
                                dest="testmodule",
                                default="",
                                help="Specified test module"
                                )
            parser.add_argument("-ts", "--testsuit",
                                action="store",
                                type=str,
                                dest="testsuit",
                                default="",
                                help="Specify test suit"
                                )
            parser.add_argument("-tc", "--testcase",
                                action="store",
                                type=str,
                                dest="testcase",
                                default="",
                                help="Specify test case"
                                )
            parser.add_argument("-tl", "--testlevel",
                                action="store",
                                type=str,
                                dest="testlevel",
                                default="",
                                help="Specify test level"
                                )
            parser.add_argument("-td", "--testdriver",
                                action="store",
                                type=str,
                                dest="testdriver",
                                default="",
                                help="Specify test driver id"
                                )
            parser.add_argument("-bv", "--build_variant",
                                action="store",
                                type=str,
                                dest="build_variant",
                                default="release",
                                help="Specify build variant(release,debug)"
                                )
            parser.add_argument("-b", "--build",
                                nargs='*',
                                dest="build",
                                default=[],
                                help="Specify build values"
                                     "(version,testcase,example)"
                                )
            parser.add_argument("-cov", "--coverage",
                                action="store",
                                type=str,
                                dest="coverage",
                                default="",
                                help="Specify coverage"
                                )
            parser.add_argument("-respath", "--resourcepath",
                                action=SplicingAction,
                                type=str,
                                nargs='+',
                                dest="resource_path",
                                default="",
                                help="Specify test resource path"
                                )
            parser.add_argument("-tcpath", "--testcasespath",
                                action=SplicingAction,
                                type=str,
                                nargs='+',
                                dest="testcases_path",
                                default="",
                                help="Specify testcases path"
                                )
            parser.add_argument("-ta", "--testargs",
                                action=SplicingAction,
                                type=str,
                                nargs='+',
                                dest="testargs",
                                default={},
                                help="Specify test arguments"
                                )
            group.add_argument("-l", "--testlist",
                               action=SplicingAction,
                               type=str,
                               nargs='+',
                               dest="testlist",
                               default="",
                               help="Specify test list"
                               )
            parser.add_argument("-env", "--environment",
                                action=SplicingAction,
                                type=str,
                                nargs='+',
                                dest="test_environment",
                                default="",
                                help="Specify test environment"
                                )
            parser.add_argument("--retry",
                                action="store",
                                type=str,
                                dest="retry",
                                default="",
                                help="Specify retry command"
                                )
            parser.add_argument("--pass_through",
                                action="store_true",
                                dest="pass_through",
                                help="Pass through test arguments"
                                )
            self._params_pre_processing(para_list)
            (options, unparsed) = parser.parse_known_args(para_list)
            if unparsed:
                LOG.warning("unparsed input: %s", " ".join(unparsed))
            self._params_post_processing(options)

        except SystemExit:
            valid_param = False
            parser.print_help()
            LOG.warning("Parameter parsing systemexit exception.")
        return options, unparsed, valid_param, parser

    @classmethod
    def _params_pre_processing(cls, para_list):
        if len(para_list) <= 1 or (
                len(para_list) > 1 and "-" in str(para_list[1])):
            para_list.insert(1, Task.EMPTY_TASK)
        for index, param in enumerate(para_list):
            if param == "--retry":
                if index + 1 == len(para_list):
                    para_list.append("retry_previous_command")
                elif "-" in str(para_list[index + 1]):
                    para_list.insert(index + 1, "retry_previous_command")
            elif param == "-->":
                para_list[index] = "!%s" % param

    def _params_post_processing(self, options):
        # params post-processing
        if options.task == Task.EMPTY_TASK:
            setattr(options, "task", "")
        if options.testargs and not options.pass_through:
            test_args = self._parse_combination_param(options.testargs)
            setattr(options, "testargs", test_args)
        if not options.resource_path:
            resource_path = UserConfigManager(env=options.test_environment).\
                get_resource_path()
            setattr(options, "resource_path", resource_path)
        if not options.testcases_path:
            testcases_path = UserConfigManager(env=options.test_environment). \
                get_testcases_dir()
            setattr(options, "testcases_path", testcases_path)

    def command_parser(self, args):
        try:
            Scheduler.command_queue.append(args)
            LOG.info("Input command: {}".format(args))
            para_list = args.split()
            (options, _, valid_param, parser) = self.argument_parser(
                para_list)
            if options is None or not valid_param:
                LOG.warning("options is None.")
                return None
            if options.action == ToolCommandType.toolcmd_key_run and \
                    options.retry:
                options = self._get_retry_options(options)
            else:
                from xdevice import SuiteReporter
                SuiteReporter.clear_failed_case_list()
                SuiteReporter.clear_report_result()

            command = options.action
            if command == "":
                LOG.info("command is empty.")
                return

            self._process_command(command, options, para_list, parser)
        except (ParamError, ValueError, TypeError, SyntaxError,
                AttributeError) as exception:
            LOG.exception("%s: %s" % (get_instance_name(exception), exception),
                          exc_info=False)
            if Scheduler.upload_address:
                Scheduler.upload_unavailable_result(str(exception.args))
                Scheduler.upload_report_end()
        finally:
            if isinstance(Scheduler.command_queue[-1], str):
                Scheduler.command_queue.pop()

    def _process_command(self, command, options, para_list, parser):
        if command.startswith(ToolCommandType.toolcmd_key_help):
            self._process_command_help(parser, para_list)
        elif command.startswith(ToolCommandType.toolcmd_key_show):
            self._process_command_show(para_list)
        elif command.startswith(ToolCommandType.toolcmd_key_run):
            self._process_command_run(command, options)
        elif command.startswith(ToolCommandType.toolcmd_key_quit):
            self._process_command_quit(command)
        elif command.startswith(ToolCommandType.toolcmd_key_list):
            self._process_command_list(command, para_list)
        else:
            LOG.error("unsupported command action: %s" % command)

    def _get_retry_options(self, options):
        input_report_path = options.reportpath

        # get history_command, history_report_path
        if options.retry == "retry_previous_command":
            if len(Scheduler.command_queue) < 2:
                raise ParamError("no previous command executed")
            _, history_command, history_report_path = \
                Scheduler.command_queue[-2]
        else:
            history_command, history_report_path = "", ""
            for command_tuple in Scheduler.command_queue[:-1]:
                if command_tuple[0] != options.retry:
                    continue
                history_command, history_report_path = \
                    command_tuple[1], command_tuple[2]
                break
            if not history_command:
                raise ParamError("wrong task id input: %s" % options.retry)

        LOG.info("History command: %s", history_command)
        # parse history_command, set history_report_path
        if not os.path.exists(history_report_path) and \
                Scheduler.mode != "decc":
            raise ParamError(
                "history report path %s not exists" % history_report_path)
        (options, _, _, _) = self.argument_parser(
            history_command.split())
        setattr(options, "history_report_path", history_report_path)

        # modify history_command -rp param
        if options.reportpath:
            if input_report_path:
                history_command = history_command.replace(
                    options.reportpath, input_report_path)
                setattr(options, "reportpath", input_report_path)
            else:
                history_command = history_command.replace(
                    options.reportpath, "").replace("-rp", "").replace(
                    "--reportpath", "")
                setattr(options, "reportpath", "")
        else:
            if input_report_path:
                history_command = "{}{}".format(history_command,
                                                " -rp %s" % input_report_path)
                setattr(options, "reportpath", input_report_path)
        history_command = history_command.strip()

        # add history command to Scheduler.command_queue
        LOG.info("Retry command: %s", history_command)
        Scheduler.command_queue[-1] = history_command
        return options

    @classmethod
    def _process_command_help(cls, parser, para_list):
        if para_list[0] == ToolCommandType.toolcmd_key_help:
            parser.print_help()
        else:
            LOG.error("Wrong help command. Use 'help' to print help")
        return

    @classmethod
    def _process_command_show(cls, para_list):
        if para_list[0] == ToolCommandType.toolcmd_key_show:
            pass
        else:
            LOG.error("Wrong show command.")
        return

    @classmethod
    def _process_command_run(cls, command, options):

        scheduler = get_plugin(plugin_type=Plugin.SCHEDULER,
                               plugin_id=SchedulerType.scheduler)[0]
        if scheduler is None:
            LOG.error("Can not find the scheduler plugin.")
        else:
            scheduler.exec_command(command, options)

        return

    def _process_command_list(self, command, para_list):
        if command != ToolCommandType.toolcmd_key_list:
            LOG.error("Wrong list command.")
            return
        if len(para_list) > 1:
            if para_list[1] == "history":
                self._list_history()
            elif para_list[1] == "devices" or para_list[1] == Task.EMPTY_TASK:
                env_manager = EnvironmentManager()
                env_manager.list_devices()
            else:
                self._list_task_id(para_list[1])
            return
        # list devices
        env_manager = EnvironmentManager()
        env_manager.list_devices()
        return

    @classmethod
    def _process_command_quit(cls, command):
        if command == ToolCommandType.toolcmd_key_quit:
            env_manager = EnvironmentManager()
            env_manager.env_stop()
            sys.exit(0)
        else:
            LOG.error("Wrong exit command. Use 'quit' to quit program")
        return

    @staticmethod
    def _parse_combination_param(combination_value):
        # sample: size:xxx1;exclude-annotation:xxx
        parse_result = {}
        key_value_pairs = str(combination_value).split(";")
        for key_value_pair in key_value_pairs:
            key, value = key_value_pair.split(":", 1)
            if not value:
                raise ParamError("'%s' no value" % key)
            value_list = str(value).split(",")
            exist_list = parse_result.get(key, [])
            exist_list.extend(value_list)
            parse_result[key] = exist_list
        return parse_result

    @classmethod
    def _list_history(cls):
        print("Command history:")
        print("{0:<16}{1:<50}{2:<50}".format(
            "TaskId", "Command", "ReportPath"))
        for command_info in Scheduler.command_queue[:-1]:
            command, report_path = command_info[1], command_info[2]
            if len(command) > 49:
                command = "%s..." % command[:46]
            if len(report_path) > 49:
                report_path = "%s..." % report_path[:46]
            print("{0:<16}{1:<50}{2:<50}".format(
                command_info[0], command, report_path))

    @classmethod
    def _list_task_id(cls, task_id):
        print("List task:")
        task_id, command, report_path = task_id, "", ""
        for command_info in Scheduler.command_queue[:-1]:
            if command_info[0] != task_id:
                continue
            task_id, command, report_path = command_info
            break
        print("{0:<16}{1:<100}".format("TaskId:", task_id))
        print("{0:<16}{1:<100}".format("Command:", command))
        print("{0:<16}{1:<100}".format("ReportPath:", report_path))
