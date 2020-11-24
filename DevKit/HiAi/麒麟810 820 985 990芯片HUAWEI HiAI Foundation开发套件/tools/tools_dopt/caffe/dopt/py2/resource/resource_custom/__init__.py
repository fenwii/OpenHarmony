#!/usr/bin/env python
# encoding: utf-8
# Copyright © Huawei Technologies Co., Ltd. 2010-2018. All rights reserved.

""" davinci opt tool chain init"""
from os.path import dirname, join, isdir, abspath, basename, realpath
from glob import glob

class ResourceImport:
    @staticmethod
    def file_import():
        pwd = dirname(__file__)
        name = __name__
        import_num = 0
        for x in glob(join(pwd, '*.py')):
            if not x.endswith('__.py'):
                name_module = name[:-8] + basename(x)[:-3]
                __import__(name_module, globals(), locals())
                import_num = import_num + 1

        if import_num == 0:
            for x in glob(join(pwd, '*.so')):
                if not x.endswith('__.so'):
                    name_module = name[:-8] + basename(x)[:-3]
                    __import__(name_module, globals(), locals())
