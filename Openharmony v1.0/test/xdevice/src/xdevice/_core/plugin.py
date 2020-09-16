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

from inspect import signature

from _core.interface import IDriver
from _core.interface import IParser
from _core.interface import IListener
from _core.interface import IScheduler
from _core.interface import IDevice
from _core.interface import ITestKit

__all__ = ["Config", "Plugin", "get_plugin", "set_plugin_params",
           "get_all_plugins", "clear_plugin_cache"]

# plugins dict
_PLUGINS = dict()
# plugin config name
_DEFAULT_CONFIG_NAME = "_plugin_config_"


class Config:
    """
    The common configuration
    """

    def __init__(self, params=None):
        if params is None:
            params = {}
        self.update(params)

    def __getitem__(self, item):
        return self.__dict__[item]

    def __setitem__(self, key, value):
        self.__dict__[key] = value

    def update(self, params):
        self.__dict__.update(params)


class Plugin(object):
    """
    Plugin decorator with parameters. You can decorate one class as following:
    @Plugin("type_name"), the default plugin id is the same as TypeName.
    @Plugin(type="type_name", id="plugin_id")
    """
    SCHEDULER = "scheduler"
    DRIVER = "driver"
    DEVICE = "device"
    LOG = "log"
    PARSER = "parser"
    LISTENER = "listener"
    TEST_KIT = "testkit"
    MANAGER = "manager"

    _builtin_plugin = dict({
        SCHEDULER: [IScheduler],
        DRIVER: [IDriver],
        DEVICE: [IDevice],
        PARSER: [IParser],
        LISTENER: [IListener],
        TEST_KIT: [ITestKit]
    })

    def __init__(self, *args, **kwargs):
        _param_dict = dict(kwargs)
        if len(args) == 1 and type(args[0]) == str:
            self.plugin_type = str(args[0])
            self.plugin_id = str(args[0])
        elif "id" in _param_dict.keys() and "type" in _param_dict.keys():
            self.plugin_type = _param_dict["type"]
            self.plugin_id = _param_dict["id"]
            del _param_dict["type"]
            del _param_dict["id"]
        else:
            raise ValueError(
                '@Plugin must be specify type and id attributes. such as '
                '@Plugin("plugin_type") or '
                '@Plugin(type="plugin_type", id="plugin_id")')
        self.params = _param_dict

    def __call__(self, cls):
        if hasattr(cls, _DEFAULT_CONFIG_NAME):
            raise TypeError(
                "'{}' attribute is not allowed for plugin {} .".format(
                    _DEFAULT_CONFIG_NAME, cls.__name__))
        setattr(cls, _DEFAULT_CONFIG_NAME, Config(self.params))

        init_func = getattr(cls, "__init__", None)
        if init_func and type(
                init_func).__name__ != "wrapper_descriptor" and len(
                signature(init_func).parameters) != 1:
            raise TypeError(
                "__init__ method must be no arguments for plugin {} .".format(
                    cls.__name__))

        if hasattr(cls, "get_plugin_config"):
            raise TypeError(
                "'{}' method is not allowed for plugin {} .".format(
                    "get_plugin_config", cls.__name__))

        def get_plugin_config(obj):
            del obj
            return getattr(cls, _DEFAULT_CONFIG_NAME)

        setattr(cls, "get_plugin_config", get_plugin_config)

        instance = cls()
        interfaces = self._builtin_plugin.get(self.plugin_type, [])
        for interface in interfaces:
            if not isinstance(instance, interface):
                raise TypeError(
                    "{} plugin must implement {} interface.".format(
                        cls.__name__, interface))

        _PLUGINS.setdefault((self.plugin_type, self.plugin_id), []).insert(
            0, instance)

        return cls

    def get_params(self):
        return self.params

    def get_builtin_plugin(self):
        return self._builtin_plugin


def get_plugin(plugin_type, plugin_id=None):
    """
    get plugin instance
    :param plugin_type: plugin type
    :param plugin_id: plugin id
    :return:  the instance list of plugin
    """
    if plugin_id is None:
        plugin_id = plugin_type
    return _PLUGINS.get((plugin_type, plugin_id), [])


def set_plugin_params(plugin_type, plugin_id=None, **kwargs):
    """
    set plugin parameters
    :param plugin_type: plugin type
    :param plugin_id: plugin id
    :param kwargs: the parameters for plugin
    :return:
    """
    if plugin_id is None:
        plugin_id = plugin_type
    plugins = get_plugin(plugin_type, plugin_id)
    if len(plugins) == 0:
        raise ValueError("Can not find the plugin %s" % plugin_id)
    for plugin in plugins:
        params = getattr(plugin, _DEFAULT_CONFIG_NAME)
        params.update(kwargs)


def get_all_plugins():
    """
    get all plugins
    """
    return dict(_PLUGINS)


def clear_plugin_cache():
    """
    clear all cached plugins
    """
    _PLUGINS.clear()
