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

from abc import ABC
from abc import abstractmethod
from enum import Enum

__all__ = ["LifeCycle", "IDevice", "IDriver", "IListener", "IShellReceiver",
           "IParser", "ITestKit", "IScheduler", "IDeviceManager"]


class LifeCycle(Enum):
    TestTask = "TestTask"
    TestSuite = "TestSuite"
    TestCase = "TestCase"
    TestSuites = "TestSuites"


def _check_methods(class_info, *methods):
    mro = class_info.__mro__
    for method in methods:
        for cls in mro:
            if method in cls.__dict__:
                if cls.__dict__[method] is None:
                    return NotImplemented
                break
        else:
            return NotImplemented
    return True


class IDeviceManager(ABC):
    """
    Class managing the set of different types of devices for testing
    """
    __slots__ = ()

    @abstractmethod
    def apply_device(self, device_option, timeout=10):
        pass

    @abstractmethod
    def release_device(self, device):
        pass

    @classmethod
    def __subclasshook__(cls, class_info):
        if cls is IDevice:
            return _check_methods(class_info, "__serial__")
        return NotImplemented


class IDevice(ABC):
    """
    IDevice provides an reliable and slightly higher level API to access
    devices
    """
    __slots__ = ()

    @abstractmethod
    def __set_serial__(self, device_sn=""):
        pass

    @abstractmethod
    def __get_serial__(self):
        pass

    @classmethod
    def __subclasshook__(cls, class_info):
        if cls is IDevice:
            return _check_methods(class_info, "__serial__")
        return NotImplemented


class IDriver(ABC):
    """
    A test driver runs the tests and reports results to a listener.
    """
    __slots__ = ()

    @classmethod
    def __check_failed__(cls, msg):
        raise ValueError(msg)

    @abstractmethod
    def __check_environment__(self, device_options):
        """
        check environment correct or not.
        you should return False when check failed.
        :param device_options:
        """

    @abstractmethod
    def __check_config__(self, config):
        """
        check config correct or not.
        you should raise exception when check failed.
        :param config:
        """
        self.__check_failed__("Not implementation for __check_config__")

    @abstractmethod
    def __execute__(self, request):
        """
        Execute tests according to the request.
        """

    @abstractmethod
    def __result__(self):
        """
        Return tests execution result
        """

    @classmethod
    def __subclasshook__(cls, class_info):
        if cls is IDriver:
            return _check_methods(class_info, "__check_config__",
                                  "__execute__")
        return NotImplemented


class IScheduler(ABC):
    """
    A scheduler to run jobs parallel.
    """
    __slots__ = ()

    @abstractmethod
    def __discover__(self, args):
        """
        Discover tests according to request, and return root TestDescriptor.
        """

    @abstractmethod
    def __execute__(self, request):
        """
        Execute tests according to the request.
        """

    @classmethod
    @abstractmethod
    def __allocate_environment__(cls, options, test_driver):
        """
        allocate_environment according to the request.
        """

    @classmethod
    @abstractmethod
    def __free_environment__(cls, environment):
        """
        free environment to the request.
        """

    @classmethod
    def __subclasshook__(cls, class_info):
        if cls is IScheduler:
            return _check_methods(class_info, "__discover__", "__execute__")
        return NotImplemented


class IListener(ABC):
    """
    Listener to be notified of test execution events by TestDriver, as
    following sequence:
    __started__(TestTask)
    __started__(TestSuite)
    __started__(TestCase)
    [__skipped__(TestCase)]
    [__failed__(TestCase)]
    __ended__(TestCase)
    ...
    [__failed__(TestSuite)]
    __ended__(TestSuite)
    ...
    [__failed__(TestTask)]
    __ended__(TestTask)
    """
    __slots__ = ()

    @abstractmethod
    def __started__(self, lifecycle, result):
        """
        Called when the execution of the TestCase or TestTask has started,
        before any test has been executed.
        """

    @abstractmethod
    def __ended__(self, lifecycle, result, **kwargs):
        """
        Called when the execution of the TestCase or TestTask has finished,
        after all tests have been executed.
        """

    @abstractmethod
    def __skipped__(self, lifecycle, result):
        """
        Called when the execution of the TestCase or TestTask has been skipped.
        """

    @abstractmethod
    def __failed__(self, lifecycle, result):
        """
        Called when the execution of the TestCase or TestTask has been skipped.
        """

    @classmethod
    def __subclasshook__(cls, class_info):
        if cls is IListener:
            return _check_methods(class_info, "__started__", "__ended__",
                                  "__skipped__", "__failed__")
        return NotImplemented


class IShellReceiver(ABC):
    """
    read the output from shell out.
    """
    __slots__ = ()

    @abstractmethod
    def __read__(self, output):
        pass

    @abstractmethod
    def __error__(self, message):
        pass

    @abstractmethod
    def __done__(self, result_code, message):
        pass

    @classmethod
    def __subclasshook__(cls, class_info):
        if cls is IShellReceiver:
            return _check_methods(class_info, "__read__", "__error__",
                                  "__done__")
        return NotImplemented


class IParser(ABC):
    """
    A parser to parse the output of testcases.
    """
    __slots__ = ()

    @abstractmethod
    def __process__(self, lines):
        pass

    @abstractmethod
    def __done__(self):
        pass

    @classmethod
    def __subclasshook__(cls, class_info):
        if cls is IParser:
            return _check_methods(class_info, "__process__", "__done__")
        return NotImplemented


class ITestKit(ABC):
    """
    A test kit running on the host.
    """
    __slots__ = ()

    @classmethod
    def __check_failed__(cls, msg):
        raise ValueError(msg)

    @abstractmethod
    def __check_config__(self, config):
        """
        check config correct or not.
        you should raise exception when check failed.
        :param config:
        """
        self.__check_failed__("Not implementation for __check_config__")

    @abstractmethod
    def __setup__(self, device, **kwargs):
        pass

    @abstractmethod
    def __teardown__(self, device):
        pass

    @classmethod
    def __subclasshook__(cls, class_info):
        if cls is ITestKit:
            return _check_methods(class_info, "__check_config__", "__setup__",
                                  "__teardown__")
        return NotImplemented
