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

import sys
import os

from core.constants import ToolCommandType
from core.utils import get_file_list
from core.utils import get_file_list_by_postfix
from core.build.filter_targets import FilterTargets
from core.config.config_manager import UserConfigManager
from core.config.config_manager import FrameworkConfigManager

CMD_KEY_PRODUCTLIST = "productlist"
CMD_KEY_TYPELIST = "typelist"
CMD_KEY_SUBSYSTEMLIST = "subsystemlist"
CMD_KEY_MODULELIST = "modulelist"


TOOL_VERSION_INFO = """DeveloperTest V1.0.0 \
(default, Dec 27 2018, 20:10:10) Type "help" for more information.
"""

HLEP_COMMAND_INFOMATION = """use help [follow command] for more information:
    """ + \
    "show: " + """Display a list of supported show command.
    """ + \
    "run:  " + """Display a list of supported run command.
    """ + \
    "quit: " + """Exit the test framework application.
"""

SUPPORT_COMMAND_SHOW = """use show [follow command] for more information:
    """ + \
    "productlist" + """
    """ + \
    "typelist" + """
    """ + \
    "subsystemlist" + """
    """ + \
    "modulelist" + """
"""


RUNCASES_INFOMATION = "run\n" + """
    Usage: run [OPTION]...
    This command is used to execute the selected testcases.
    It includes a series of processes such as use case compilation, \
    execution, and result collection.
    """ + """\n""" + "Arguments" + """
    -t [testtype]         Specify the type of test that needs to be performed,
                           this parameter is mandatory, Query by typelist.
                           Example:
                           %s
      -ss [subsystemname]  Specify the name of the subsystem to be executed, \
        Query by subsystemlist.
        -tm [testmodule]     Specify the name of the module to be executed, \
        Query by modulelist.
          -ts [testsuit]     Specify the name of the testsuit to be executed.
            -tc [testcase]   Specify the case name to execute.
    -tl [testlevel]        Specifies the execution level of the case.
                           Note: -l and -c cannot exist at the same time.
    """ + """\n""" + "Examples" + """
    run -t UT
    run -t UT -ss aafwk
    run -t UT -ss aafwk -tm intent_test
    run -t UT -ss aafwk -tm intent_test -ts intent_base_test
    run -t UT -ss aafwk -tm intent_test -ts intent_base_test -tl 2
    run -t UT -ss aafwk -tm intent_test -ts intent_base_test -tc \
        IntentBaseTest.*
    run -t UT -ss aafwk -tm intent_test -ts intent_base_test -tc \
        IntentBaseTest.AaFwk_Intent_Entity_001
    run -t MST
    ...
    run -t ALL
    ...
"""

PLANLIST_INFOMATION = "productlist\n" + """
    This command is used to display a list of currently \
        supported product forms.
"""

TYPELIST_INFOMATION = "typelist\n" + """
    This command is used to display a list of currently supported test types.
"""

SUBSYSTEMLIST_INFOMATION = "subsystemlist\n" + """
    This command is used to display a list of currently supported subsystem.
"""

MODULELIST_INFOMATION = "modulelist\n" + """
    This command is used to display a list of currently supported modules.
"""

HELP_INFOMATION = "help\n" + """
    This command is used to display help information for a specified target.
"""

QUIT_INFOMATION = "quit\n" + """
    This command is used to exit the test framework application.
"""


#############################################################################
#############################################################################

def select_user_input(data_list):
    data_item_count = len(data_list)
    select_item_value = ""
    select_item_index = -1

    if len(data_list) != 0:
        count = 0
        while True:
            input_data = input("")
            if "" != input_data and input_data.isdigit():
                input_num = int(input_data)
                if input_num > 0 and (input_num <= data_item_count):
                    select_item_index = input_num - 1
                    select_item_value = data_list[input_num - 1]
                    break
                else:
                    print("The data you entered is out of range, \
                        please re-enter:")
                    count += 1
            else:
                if "" == input_data:
                    select_item_index = 0
                    select_item_value = data_list[0]
                    break
                else:
                    print("You entered a non-numeric character, \
                        please re-enter:")
                    count += 1

            if count >= 3:
                print("You entered the error three times in a row, \
                    exit the frame.")
                quit()
                sys.exit(0)
        return select_item_value, select_item_index


def start_wizard_mode():
    select_value = "Single device wizard"
    wizard_mode_list = \
        ["Non-guided mode", "Single device wizard", "Multi-device wizard"]
    if len(wizard_mode_list) != 0:
        print("Please select the wizard mode:")
        for wizard_mode in wizard_mode_list:
            print("start wizard mode: %s" % wizard_mode)
        print("default is [1] %s" % wizard_mode_list[0])
        select_value, select_index = select_user_input(wizard_mode_list)
    print(select_value)
    return select_index


def select_productform():
    select_value = "phone"
    productform_list = \
        FrameworkConfigManager().get_framework_config("productform")
    if len(productform_list) != 0:
        print("Please select the current tested product form:")
        index = 1
        for product_form in productform_list:
            print("select {:d} product form: {}".format(index, product_form))
            index += 1
        print("default is [1] {}".format(productform_list[0]))
        select_value, _ = select_user_input(productform_list)
    print(select_value)
    return select_value


def show_wizard_mode():
    wizard_data_dic = {}
    print("+++++++++++++++++++++++++++++++++++++++++++++")

    productform = select_productform()
    if productform == "":
        productform = "phone"
    wizard_data_dic["productform"] = productform

    print("+++++++++++++++++++++++++++++++++++++++++++++")
    print("The environment is ready, please use the run command to test.")
    return wizard_data_dic


#############################################################################
#############################################################################

def display_help_info(para_list):
    if len(para_list) == 0 or para_list[0] != ToolCommandType.TOOLCMD_KEY_HELP:
        print("This command is not support.")
        return

    if len(para_list) > 1:
        display_help_command_info(para_list[1])
    else:
        print(HLEP_COMMAND_INFOMATION)


def display_show_info(para_list):
    if len(para_list) == 0 or para_list[0] != ToolCommandType.TOOLCMD_KEY_SHOW:
        print("This command is not support.")
        return

    if len(para_list) > 1:
        display_show_command_info(para_list[1])
    else:
        print(SUPPORT_COMMAND_SHOW)


#############################################################################
#############################################################################

def get_output_path_by_param():
    module_path_list = []
    module_list_file_path = os.path.join(
        sys.source_code_root_path,
        "out",
        "release",
        "module_list_files")
    print(module_list_file_path)
    if os.path.exists(module_list_file_path):
        file_list = get_file_list_by_postfix(module_list_file_path, ".mlf")
        for file in file_list:
            module_path = \
                file[len(module_list_file_path) + 1: file.rfind(os.sep)]
            if module_path != "" and module_path not in module_path_list:
                module_path_list.append(module_path)
    else:
        print("%s does not exist." % module_list_file_path)
    module_path_list.sort()
    return module_path_list


def get_test_dir_by_param(test_case_dir):
    file_list = []
    test_case_tests_path = os.path.join(test_case_dir, "tests")
    if os.path.exists(test_case_tests_path):
        test_type_name_list = os.listdir(test_case_tests_path)
        for test_type in test_type_name_list:
            file_path = os.path.join(test_case_tests_path, test_type)
            for dirs in os.walk(file_path):
                files = get_file_list(find_path=dirs[0])
                for file_name in files:
                    if "" != file_name and -1 == file_name.find(__file__):
                        file_name = os.path.join(dirs[0], file_name)
                        if os.path.isfile(file_name):
                            file_name = file_name[len(file_path) + 1:
                                                  file_name.rfind(os.sep)]
                            file_list.append(file_name)
    return file_list


def get_subsystem_module_list():
    module_path_list = []
    testcase_dir = UserConfigManager().get_user_config("testcases").get("dir")
    if testcase_dir == "":
        module_path_list = get_output_path_by_param()
    else:
        module_path_list = \
            get_test_dir_by_param(testcase_dir)
    return module_path_list


def get_test_dir_by_subsystem(test_case_dir):
    subsystem_name_list = []
    testcase_tests_path = os.path.join(test_case_dir, "tests")
    if os.path.exists(testcase_tests_path):
        testtype_name_list = os.listdir(testcase_tests_path)
        for testtype in testtype_name_list:
            file_path = os.path.join(testcase_tests_path, testtype)
            subsystemname_list = os.listdir(file_path)
            for subsystem_name in subsystemname_list:
                if subsystem_name != "" \
                        and subsystem_name not in subsystem_name_list:
                    subsystem_name_list.append(subsystem_name)
    return subsystem_name_list


#############################################################################
#############################################################################


def show_product_list():
    print("List of currently supported productform:")
    productform_list = FrameworkConfigManager().get_framework_config(
        "productform")
    if 0 != len(productform_list):
        for product_form in productform_list:
            print("show product: {}".format(product_form))
    else:
        print("No category specified.")


def show_testtype_list():
    print("List of currently supported test types:")
    testtype_list = FrameworkConfigManager().get_framework_config(
        "test_category")
    if 0 != len(testtype_list):
        for test_type in testtype_list:
            print("show test type:{}".format(test_type))
    else:
        print("No category specified.")


def show_subsystem_list(product_form):
    print("List of currently supported subsystem names:")

    test_case_dir = \
        UserConfigManager().get_user_config("test_cases").get("dir")
    if test_case_dir == "":
        subsystem_name_list = FilterTargets(
            sys.source_code_root_path).get_part_name_list_by_product(
            product_form)
    else:
        subsystem_name_list = get_test_dir_by_subsystem(test_case_dir)

    subsystem_name_list.sort()
    for subsystem_name in subsystem_name_list:
        print("show subsystem_name: {}".format(subsystem_name))


def show_module_list():
    print("List of currently supported module names:")
    subsystem_name_list = []
    subsystem_module_list = get_subsystem_module_list()

    for item in subsystem_module_list:
        if item != "":
            subsystem_name = item.split(os.sep)[0]
            if subsystem_name not in subsystem_name_list:
                subsystem_name_list.append(subsystem_name)

    for subsystem_name in subsystem_name_list:
        print("%s:" % subsystem_name)
        index = 0
        module_value_list = []
        for item in subsystem_module_list:
            find_key = subsystem_name + os.sep
            pos_subsystem = item.find(find_key)
            if pos_subsystem >= 0:
                subsystem_module_dir = \
                    item[pos_subsystem + len(find_key):len(item)]
                module_value = subsystem_module_dir.split(os.sep)[0]
                if module_value not in module_value_list:
                    module_value_list.append(module_value)
                    index += 1
                    print("    %d. %s" % (index, module_value))


def display_help_command_info(command):
    if command == CMD_KEY_PRODUCTLIST:
        print(PLANLIST_INFOMATION)
    elif command == CMD_KEY_TYPELIST:
        print(TYPELIST_INFOMATION)
    elif command == CMD_KEY_SUBSYSTEMLIST:
        print(SUBSYSTEMLIST_INFOMATION)
    elif command == CMD_KEY_MODULELIST:
        print(MODULELIST_INFOMATION)
    else:
        print("'%s' command no help information." % command)


def display_show_command_info(command, product_form="phone"):
    if command == CMD_KEY_PRODUCTLIST:
        show_product_list()
    elif command == CMD_KEY_TYPELIST:
        show_testtype_list()
    elif command == CMD_KEY_SUBSYSTEMLIST:
        show_subsystem_list(product_form)
    elif command == CMD_KEY_MODULELIST:
        show_module_list()
    else:
        print("This command is not support.")

#############################################################################
#############################################################################
