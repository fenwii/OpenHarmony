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
import subprocess
from binascii import hexlify
from concurrent.futures import wait
from concurrent.futures import ThreadPoolExecutor
from _core.logger import platform_logger

COUNT = 0
UTIL_LOG = platform_logger("utils")


def get_filename_extension(file):
    _, fullname = os.path.split(file)
    filename, ext = os.path.splitext(fullname)
    return filename, ext


def unique_id(type_name, value):
    global COUNT
    COUNT += 1
    return "{}_{}_{:0>4d}".format(type_name, value, COUNT)


def concurrent_exec_all_complete(func, params_list, max_size=8):
    """
    Provider the ability to execute target function concurrently
    :param func: target function name
    :param params_list: the list of params in these target functions
    :param max_size:  the max size of thread  you wanted  in thread pool
    :return:
    """
    with ThreadPoolExecutor(max_size) as executor:
        future_params = dict()
        for params in params_list:
            future = executor.submit(func, *params)
            future_params.update({future: params})
        wait(future_params)  # wait all function complete
        result_list = []
        for future in future_params:
            result_list.append((future.result(), future_params[future]))
        return result_list


def get_decode(input_str):
    if not isinstance(input_str, str) and not isinstance(input_str, bytes):
        return_str = str(input_str)
    else:
        try:
            return_str = input_str.decode("utf-8", errors="ignore")
        except (UnicodeDecodeError, AttributeError):
            try:
                return_str = str(input_str)
            except (TypeError, ValueError):
                return_str = hexlify(input_str)
    return return_str


def is_proc_running(pid, name=None):
    if name is None or name == "":
        return True

    if platform.system() == "Windows":
        command = "tasklist | findstr \"%s\""
    else:
        command = "ps -ef | grep %s"

    proc = subprocess.Popen(command % str(pid), stdout=subprocess.PIPE,
                            shell=False)
    out, _ = proc.communicate()
    out = get_decode(out).strip()
    return False if out == "" else out.find(name) != -1


def get_running_proc_num(name):
    if name is None or name == "":
        return 0

    if platform.system() == "Windows":
        command = "tasklist | findstr {}".format(name)
    else:
        command = "ps -ef | grep {}".format(name)
    proc = subprocess.Popen(command, stdout=subprocess.PIPE, shell=False)
    out, _ = proc.communicate()
    out = get_decode(out).strip()
    return 0 if out == "" else len(out.splitlines())


def create_dir(path):
    full_path = os.path.abspath(os.path.expanduser(path))
    if not os.path.exists(full_path):
        os.makedirs(full_path, exist_ok=True)


def get_file_list(find_path, postfix=""):
    file_names = os.listdir(find_path)
    file_list = []
    if len(file_names) > 0:
        for file_name in file_names:
            if postfix != "":
                if file_name.find(postfix) != -1 \
                        and file_name[-len(postfix):] == postfix:
                    file_list.append(file_name)
            else:
                file_list.append(file_name)
    return file_list


def get_file_list_by_postfix(path, postfix=""):
    file_list = []
    for dirs in os.walk(path):
        files = get_file_list(find_path=dirs[0], postfix=postfix)
        for file_name in files:
            if "" != file_name and -1 == file_name.find(__file__):
                file_name = os.path.join(dirs[0], file_name)
                if os.path.isfile(file_name):
                    file_list.append(file_name)
    return file_list
