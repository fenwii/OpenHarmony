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
import sys
import signal
import platform

from core.constants import ToolCommandType
from xdevice import platform_logger
from xdevice import EnvironmentManager
from core.command.run import Run
from core.command.display import display_show_info
from core.command.display import show_wizard_mode
from core.config.config_manager import UserConfigManager

__all__ = ["Console"]

##############################################################################
##############################################################################


class Console(object):
    """
    Class representing an console for executing test.
    Main xDevice console providing user with the interface to interact
    """
    __instance = None
    wizard_dic = {}
    log = platform_logger("Console")

    def __new__(cls, *args, **kwargs):
        if cls.__instance is None:
            cls.__instance = super(Console, cls).__new__(cls, *args, **kwargs)
        return cls.__instance

    def __init__(self):
        pass

    def handler_ctrl_c(self, signalnum, frame):
        pass

    def handler_ctrl_z(self, signalnum, frame):
        pass

    def console(self, args):
        """
        Main xDevice console providing user with the interface to interact
        """
        if args is None or len(args) < 2:
            self.wizard_dic = show_wizard_mode()
            print(self.wizard_dic)
            EnvironmentManager()
            if self._build_version(self.wizard_dic["productform"]):
                self._console()
            else:
                self.log.error("Build version failed, exit test framework.")
        else:
            EnvironmentManager()
            self.command_parser(" ".join(args[1:]))

    def _console(self):
        if platform.system() != 'Windows':
            signal.signal(signal.SIGTSTP, self.handler_ctrl_z)  # ctrl+x linux
        signal.signal(signal.SIGINT, self.handler_ctrl_c)  # ctrl+c

        while True:
            try:
                usr_input = input(">>> ")
                if usr_input == "":
                    continue
                self.command_parser(usr_input)
            except SystemExit:
                self.log.info("Program exit normally!")
                return
            except (IOError, EOFError, KeyboardInterrupt) as error:
                self.log.exception("Input Error: %s" % error)

    @classmethod
    def argument_parser(cls, para_list):
        """
        argument parser
        """
        options = None
        unparsed = []
        valid_param = True
        parser = None

        try:
            parser = argparse.ArgumentParser(
                description="Specify test para.")
            parser.add_argument("action", type=str.lower,
                                help="Specify action")

            # Developer test general test parameters
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
                                default=["ut"],
                                help="Specify test type(ut,mst,st,perf,all)"
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

            # Developer test extended test parameters
            parser.add_argument("-os", "--target_os_name",
                                action="store",
                                type=str,
                                dest="target_os_name",
                                default="OHOS",
                                help="Specify target os name"
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
                                default=["testcase"],
                                help="Specify build values(version,testcase)"
                                )
            parser.add_argument("-cov", "--coverage",
                                action="store",
                                type=str,
                                dest="coverage",
                                default="",
                                help="Specify coverage"
                                )
            parser.add_argument("-tf", "--testfile",
                                action="store",
                                type=str,
                                dest="testfile",
                                default="",
                                help="Specify test suites list file"
                                )
            parser.add_argument("-res", "--resource",
                                action="store",
                                type=str,
                                dest="resource",
                                default="",
                                help="Specify test resource"
                                )

            # Developer test other test parameters
            parser.add_argument("-sn", "--device_sn",
                                action="store",
                                type=str,
                                dest="device_sn",
                                default="",
                                help="Specify device serial number"
                                )
            parser.add_argument("-c", "--config",
                                action="store",
                                type=str,
                                dest="config",
                                default="",
                                help="Specify test config file"
                                )
            parser.add_argument("-rp", "--reportpath",
                                action="store",
                                type=str,
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
            parser.add_argument("-td", "--testdriver",
                                action="store",
                                type=str,
                                dest="test_driver",
                                default="",
                                help="Specify test driver id"
                                )
            (options, unparsed) = parser.parse_known_args(para_list)
        except SystemExit:
            valid_param = False
            parser.print_help()
            cls.log.warning("Parameter parsing systemexit exception.")

        return options, unparsed, valid_param, parser

    def command_parser(self, args):
        try:
            self.log.info("Input command: " + args)
            para_list = args.split()
            (options, _, valid_param, parser) = \
                self.argument_parser(para_list)
            if options is None or not valid_param:
                self.log.warning("options is None.")
                return

            command = options.action
            if command == "":
                self.log.warning("action is empty.")
                return

            if command.startswith(ToolCommandType.TOOLCMD_KEY_HELP):
                self._process_command_help(parser, para_list)
            elif command.startswith(ToolCommandType.TOOLCMD_KEY_SHOW):
                self._process_command_show(para_list)
            elif command.startswith(ToolCommandType.TOOLCMD_KEY_RUN):
                if "productform" in self.wizard_dic:
                    options.productform = self.wizard_dic["productform"]
                self._process_command_run(command, options)
            elif command.startswith(ToolCommandType.TOOLCMD_KEY_QUIT):
                self._process_command_quit(command)
            elif command.startswith(ToolCommandType.TOOLCMD_KEY_LIST):
                self._process_command_device(command)
            else:
                self.log.error("command error: %s" % command)
        except (AttributeError, IOError, IndexError, ImportError, NameError,
                RuntimeError, SystemError, TypeError, ValueError,
                UnicodeError) as exception:
            self.log.exception(exception, exc_info=False)

    @classmethod
    def _process_command_help(cls, parser, para_list):
        if para_list[0] == ToolCommandType.TOOLCMD_KEY_HELP:
            parser.print_help()
        else:
            cls.log.error("Wrong help command.")
        return

    @classmethod
    def _process_command_show(cls, para_list):
        if para_list[0] == ToolCommandType.TOOLCMD_KEY_SHOW:
            display_show_info(para_list)
        else:
            cls.log.error("Wrong show command.")
        return

    @classmethod
    def _process_command_run(cls, command, options):
        if command == ToolCommandType.TOOLCMD_KEY_RUN:
            Run().process_command_run(command, options)
        else:
            cls.log.error("Wrong run command.")
        return

    @classmethod
    def _process_command_device(cls, command):
        if command == ToolCommandType.TOOLCMD_KEY_LIST:
            env_manager = EnvironmentManager()
            env_manager.list_devices()
        else:
            cls.log.error("Wrong list command.")
        return

    @classmethod
    def _process_command_quit(cls, command):
        if command == ToolCommandType.TOOLCMD_KEY_QUIT:
            env_manager = EnvironmentManager()
            env_manager.env_stop()
            sys.exit(0)
        else:
            cls.log.error("Wrong exit command.")
        return

    @classmethod
    def _build_version(cls, product_form):
        build_result = True
        project_root_path = sys.source_code_root_path
        if project_root_path != "":
            from _core.build.build_manager import BuildManager
            build_manager = BuildManager()
            is_build_version = UserConfigManager().get_user_config_flag(
                "build", "version")
            if is_build_version:
                build_result = build_manager.build_version(project_root_path,
                                                           product_form)
            else:
                build_result = build_manager.build_gn_file(project_root_path,
                                                           product_form)
        return build_result

##############################################################################
##############################################################################
