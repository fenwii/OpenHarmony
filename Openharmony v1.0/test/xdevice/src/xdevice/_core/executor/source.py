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
from collections import namedtuple

from _core.constants import DeviceTestType
from _core.constants import HostDrivenTestType
from _core.exception import ParamError
from _core.logger import platform_logger
from _core.utils import get_filename_extension
from _core.utils import is_config_str
from _core.utils import unique_id

__all__ = ["TestSetSource", "TestSource", "find_test_descriptors",
           "find_testdict_descriptors"]

TestSetSource = namedtuple('TestSetSource', 'set')
TestSource = namedtuple('TestSource', 'source_file source_string config_file '
                                      'test_name test_type')

TEST_TYPE_DICT = {"DEX": DeviceTestType.dex_test,
                  "HAP": DeviceTestType.hap_test,
                  "APK": DeviceTestType.hap_test,
                  "PYT": HostDrivenTestType.device_test,
                  "JST": DeviceTestType.jsunit_test,
                  "CXX": DeviceTestType.cpp_test,
                  "BIN": DeviceTestType.lite_cpp_test}
EXT_TYPE_DICT = {".dex": DeviceTestType.dex_test,
                 ".hap": DeviceTestType.hap_test,
                 ".apk": DeviceTestType.hap_test,
                 ".py": HostDrivenTestType.device_test,
                 ".js": DeviceTestType.jsunit_test,
                 ".bin": DeviceTestType.lite_cpp_test,
                 "default": DeviceTestType.cpp_test}
MODULE_CONFIG_SUFFIX = ".json"
LOG = platform_logger("TestSource")


def find_test_descriptors(config):
    if config.testfile == "" and config.testlist == "" and config.task == "":
        return None

    # get test sources
    testcases_dirs = _get_testcases_dirs(config)
    test_sources = _get_test_sources(config, testcases_dirs)
    LOG.debug("test sources: %s", test_sources)

    # normalize test sources
    test_sources = _normalize_test_sources(testcases_dirs, test_sources)

    # make test descriptors
    test_descriptors = _make_test_descriptors_from_testsources(test_sources,
                                                               config)
    return test_descriptors


def _get_testcases_dirs(config):
    from xdevice import Variables
    # add config.testcases_path and its subfolders
    testcases_dirs = []
    if getattr(config, "testcases_path", ""):
        testcases_dirs = [config.testcases_path]
        _append_subfolders(config.testcases_path, testcases_dirs)

    # add inner testcases dir and its subfolders
    inner_testcases_dir = os.path.abspath(os.path.join(
        Variables.top_dir, "testcases"))
    if getattr(config, "testcases_path", "") and os.path.normcase(
            config.testcases_path) != os.path.normcase(inner_testcases_dir):
        testcases_dirs.append(inner_testcases_dir)
        _append_subfolders(inner_testcases_dir, testcases_dirs)

    # add execution dir and top dir
    testcases_dirs.append(Variables.exec_dir)
    if os.path.normcase(Variables.exec_dir) != os.path.normcase(
            Variables.top_dir):
        testcases_dirs.append(Variables.top_dir)

    LOG.debug("testcases directories: %s", testcases_dirs)
    return testcases_dirs


def _append_subfolders(testcases_path, testcases_dirs):
    for root, dirs, _ in os.walk(testcases_path):
        for sub_dir in dirs:
            testcases_dirs.append(os.path.abspath(os.path.join(root, sub_dir)))


def find_testdict_descriptors(config):
    from xdevice import Variables
    if getattr(config, "testdict", "") == "":
        return None
    testdict = config.testdict
    test_descriptors = []
    for test_type_key, files in testdict.items():
        for file_name in files:
            if not os.path.isabs(file_name):
                file_name = os.path.join(Variables.exec_dir, file_name)
            if os.path.isfile(
                    file_name) and test_type_key in TEST_TYPE_DICT.keys():
                desc = _make_test_descriptor(os.path.abspath(file_name),
                                             test_type_key)
                if desc is not None:
                    test_descriptors.append(desc)
    if not test_descriptors:
        raise ParamError("test source is none")
    return test_descriptors


def _get_test_sources(config, testcases_dirs):
    test_sources = []

    # get test sources from testcases_dirs
    if not config.testfile and not config.testlist and config.task:
        for testcases_dir in testcases_dirs:
            _append_module_test_source(testcases_dir, test_sources)
        return test_sources

    # get test sources from config.testlist
    if getattr(config, "testlist", ""):
        for test_source in config.testlist.split(";"):
            if test_source.strip():
                test_sources.append(test_source.strip())
        return test_sources

    # get test sources from config.testfile
    test_file = _get_test_file(config, testcases_dirs)
    with open(test_file, "r") as file_content:
        for line in file_content:
            if line.strip():
                test_sources.append(line.strip())
    return test_sources


def _append_module_test_source(testcases_path, test_sources):
    if not os.path.isdir(testcases_path):
        return
    for item in os.listdir(testcases_path):
        item_path = os.path.join(testcases_path, item)
        if os.path.isfile(item_path) and item_path.endswith(
                MODULE_CONFIG_SUFFIX):
            test_sources.append(item_path)


def _get_test_file(config, testcases_dirs):
    if os.path.isabs(config.testfile):
        if os.path.exists(config.testfile):
            return config.testfile
        else:
            raise ParamError("test file '%s' not exists" % config.testfile)

    for testcases_dir in testcases_dirs:
        test_file = os.path.join(testcases_dir, config.testfile)
        if os.path.exists(test_file):
            return test_file

    raise ParamError("test file '%s' not exists" % config.testfile)


def _normalize_test_sources(testcases_dirs, test_sources):
    norm_test_sources = []
    for test_source in test_sources:
        append_result = False
        for testcases_dir in testcases_dirs:
            append_result = _append_norm_test_source(
                norm_test_sources, test_source, testcases_dir)
            if append_result:
                break

        if not append_result:
            norm_test_sources.append(test_source)
    if not norm_test_sources:
        raise ParamError("test source not found")
    return norm_test_sources


def _append_norm_test_source(norm_test_sources, test_source, testcases_dir):
    # get norm_test_source
    norm_test_source = test_source
    if not os.path.isabs(test_source):
        norm_test_source = os.path.abspath(
            os.path.join(testcases_dir, test_source))
    # append to norm_test_sources
    if os.path.isfile(norm_test_source):
        norm_test_sources.append(norm_test_source)
        return True
    elif os.path.isfile(norm_test_source + MODULE_CONFIG_SUFFIX):
        norm_test_sources.append(norm_test_source + MODULE_CONFIG_SUFFIX)
        return True
    return False


def _make_test_descriptor(file_path, test_type_key):
    from _core.executor.request import Descriptor
    if test_type_key is None:
        return None

    # get params
    filename, _ = get_filename_extension(file_path)
    uid = unique_id("TestSource", filename)
    test_type = TEST_TYPE_DICT[test_type_key]
    config_file = _get_config_file(
        os.path.join(os.path.dirname(file_path), filename))

    # make test descriptor
    desc = Descriptor(uuid=uid, name=filename,
                      source=TestSource(file_path, "", config_file, filename,
                                        test_type))
    return desc


def _get_test_driver(test_source):
    try:
        from _core.testkit.json_parser import JsonParser
        json_config = JsonParser(test_source)
        return json_config.get_driver_type()
    except ParamError as error:
        LOG.error(error)
        return ""


def _make_test_descriptors_from_testsources(test_sources, config):
    test_descriptors = []

    for test_source in test_sources:
        filename, ext = test_source.split()[0], "str"
        if os.path.isfile(test_source):
            filename, ext = get_filename_extension(test_source)

        test_driver = config.testdriver
        if is_config_str(test_source):
            test_driver = _get_test_driver(test_source)

        # get params
        config_file = _get_config_file(
            os.path.join(os.path.dirname(test_source), filename))
        test_type = _get_test_type(config_file, test_driver, ext)
        if not test_type:
            LOG.error("no driver to execute '%s'" % test_source)
            continue

        desc = _create_descriptor(config_file, filename, test_source,
                                  test_type)
        test_descriptors.append(desc)

    return test_descriptors


def _create_descriptor(config_file, filename, test_source, test_type):
    from _core.executor.request import Descriptor

    uid = unique_id("TestSource", filename)
    # create Descriptor
    if os.path.isfile(test_source):
        desc = Descriptor(uuid=uid, name=filename,
                          source=TestSource(test_source, "", config_file,
                                            filename, test_type))
    elif is_config_str(test_source):
        desc = Descriptor(uuid=uid, name=filename,
                          source=TestSource("", test_source, config_file,
                                            filename, test_type))
    else:
        raise ParamError("test source '%s' or '%s' not exists" % (
            test_source, "%s%s" % (test_source, ".json")))
    return desc


def _get_config_file(filename):
    config_file = None
    if os.path.exists(filename + MODULE_CONFIG_SUFFIX):
        config_file = filename + MODULE_CONFIG_SUFFIX
    return config_file


def _get_test_type(config_file, test_driver, ext):
    if test_driver:
        return test_driver

    if config_file:
        if not os.path.exists(config_file):
            LOG.error("config file '%s' not exists" % config_file)
            return ""
        return _get_test_driver(config_file)

    # .py .js .hap, .dex, .bin
    if ext in [".py", ".js", ".dex", ".hap", ".bin"] \
            and ext in EXT_TYPE_DICT.keys():
        test_type = EXT_TYPE_DICT[ext]
    # .apk
    elif ext in [".apk"] and ext in EXT_TYPE_DICT.keys():
        test_type = DeviceTestType.hap_test
    # cxx
    else:
        test_type = DeviceTestType.cpp_test
    return test_type
