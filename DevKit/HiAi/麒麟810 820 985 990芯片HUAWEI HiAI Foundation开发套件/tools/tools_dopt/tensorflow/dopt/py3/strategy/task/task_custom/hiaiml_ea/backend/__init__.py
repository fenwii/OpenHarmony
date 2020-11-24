#!/usr/bin/env python
# coding: utf-8
# Copyright Â© Huawei Technologies Co., Ltd. 2010-2018. All rights reserved.

from hiaiml_ea.backend import keras


class Backend:
    backend = keras

    def __init__(self):
        pass

    @classmethod
    def calc_output_feature_map(cls, input_feature_map, model_inst):
        return cls.backend.calc_output_feature_map(input_feature_map, model_inst)

    @classmethod
    def get_model_complexity_info(cls, model, input_res):
        return cls.backend.get_model_complexity_info(model, input_res)

    @classmethod
    def get_all_block_cls_names(cls):
        return cls.backend.get_all_block_cls_names()
