#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Script description:notrain_pb2 Script.
# Copyright Huawei Technologies Co., Ltd. 2010-2018. All rights reserved.
""" tensorflow notrain proto """
import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
    name='notrain.proto',
    package='',
    serialized_pb=_b('\n\rnotrain.proto\"\xaa\x01\n\x13PreProcessParameter\x12\x1e\n\ninput_type\x18\x01 \x02(\x0e\x32\n.InputType\x12\'\n\x0cimage_format\x18\x02 \x01(\x0e\x32\x0c.ImageFormat:\x03\x42GR\x12\x17\n\x0finput_file_path\x18\x03 \x02(\t\x12\x12\n\nmean_value\x18\x04 \x03(\x02\x12\x1d\n\x12standard_deviation\x18\x05 \x01(\x02:\x01\x31\"\x93\x01\n\x10NotrainParameter\x12\x1e\n\x08strategy\x18\x01 \x01(\t:\x0cQuant_INT8-8\x12\x17\n\x06\x64\x65vice\x18\x02 \x02(\x0e\x32\x07.Device\x12\x32\n\x14preprocess_parameter\x18\x03 \x03(\x0b\x32\x14.PreProcessParameter\x12\x12\n\nexclude_op\x18\x04 \x03(\t*\"\n\x06\x44\x65vice\x12\x0b\n\x07USE_CPU\x10\x00\x12\x0b\n\x07USE_GPU\x10\x01*\"\n\tInputType\x12\t\n\x05IMAGE\x10\x00\x12\n\n\x06\x42INARY\x10\x01*\x1f\n\x0bImageFormat\x12\x07\n\x03\x42GR\x10\x00\x12\x07\n\x03RGB\x10\x01')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

_DEVICE = _descriptor.EnumDescriptor(
    name='Device',
    full_name='Device',
    filename=None,
    file=DESCRIPTOR,
    values=[
      _descriptor.EnumValueDescriptor(
        name='USE_CPU', index=0, number=0,
        options=None,
        type=None),
      _descriptor.EnumValueDescriptor(
        name='USE_GPU', index=1, number=1,
        options=None,
        type=None),
    ],
    containing_type=None,
    options=None,
    serialized_start=340,
    serialized_end=374,
)
_sym_db.RegisterEnumDescriptor(_DEVICE)

Device = enum_type_wrapper.EnumTypeWrapper(_DEVICE)
_INPUTTYPE = _descriptor.EnumDescriptor(
    name='InputType',
    full_name='InputType',
    filename=None,
    file=DESCRIPTOR,
    values=[
      _descriptor.EnumValueDescriptor(
        name='IMAGE', index=0, number=0,
        options=None,
        type=None),
      _descriptor.EnumValueDescriptor(
        name='BINARY', index=1, number=1,
        options=None,
        type=None),
    ],
    containing_type=None,
    options=None,
    serialized_start=376,
    serialized_end=410,
)
_sym_db.RegisterEnumDescriptor(_INPUTTYPE)

InputType = enum_type_wrapper.EnumTypeWrapper(_INPUTTYPE)
_IMAGEFORMAT = _descriptor.EnumDescriptor(
    name='ImageFormat',
    full_name='ImageFormat',
    filename=None,
    file=DESCRIPTOR,
    values=[
      _descriptor.EnumValueDescriptor(
        name='BGR', index=0, number=0,
        options=None,
        type=None),
      _descriptor.EnumValueDescriptor(
        name='RGB', index=1, number=1,
        options=None,
        type=None),
    ],
    containing_type=None,
    options=None,
    serialized_start=412,
    serialized_end=443,
)
_sym_db.RegisterEnumDescriptor(_IMAGEFORMAT)

ImageFormat = enum_type_wrapper.EnumTypeWrapper(_IMAGEFORMAT)
USE_CPU = 0
USE_GPU = 1
IMAGE = 0
BINARY = 1
BGR = 0
RGB = 1



_PREPROCESSPARAMETER = _descriptor.Descriptor(
  name='PreProcessParameter',
  full_name='PreProcessParameter',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='input_type', full_name='PreProcessParameter.input_type', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='image_format', full_name='PreProcessParameter.image_format', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=True, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='input_file_path', full_name='PreProcessParameter.input_file_path', index=2,
      number=3, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='mean_value', full_name='PreProcessParameter.mean_value', index=3,
      number=4, type=2, cpp_type=6, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='standard_deviation', full_name='PreProcessParameter.standard_deviation', index=4,
      number=5, type=2, cpp_type=6, label=1,
      has_default_value=True, default_value=1,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=18,
  serialized_end=188,
)


_NOTRAINPARAMETER = _descriptor.Descriptor(
  name='NotrainParameter',
  full_name='NotrainParameter',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='strategy', full_name='NotrainParameter.strategy', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=True, default_value=_b("Quant_INT8-8").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='device', full_name='NotrainParameter.device', index=1,
      number=2, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='preprocess_parameter', full_name='NotrainParameter.preprocess_parameter', index=2,
      number=3, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='exclude_op', full_name='NotrainParameter.exclude_op', index=3,
      number=4, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=191,
  serialized_end=338,
)

_PREPROCESSPARAMETER.fields_by_name['input_type'].enum_type = _INPUTTYPE
_PREPROCESSPARAMETER.fields_by_name['image_format'].enum_type = _IMAGEFORMAT
_NOTRAINPARAMETER.fields_by_name['device'].enum_type = _DEVICE
_NOTRAINPARAMETER.fields_by_name['preprocess_parameter'].message_type = _PREPROCESSPARAMETER
DESCRIPTOR.message_types_by_name['PreProcessParameter'] = _PREPROCESSPARAMETER
DESCRIPTOR.message_types_by_name['NotrainParameter'] = _NOTRAINPARAMETER
DESCRIPTOR.enum_types_by_name['Device'] = _DEVICE
DESCRIPTOR.enum_types_by_name['InputType'] = _INPUTTYPE
DESCRIPTOR.enum_types_by_name['ImageFormat'] = _IMAGEFORMAT

PreProcessParameter = _reflection.GeneratedProtocolMessageType('PreProcessParameter', (_message.Message,), dict(
  DESCRIPTOR = _PREPROCESSPARAMETER,
  __module__ = 'notrain_pb2'
  # @@protoc_insertion_point(class_scope:PreProcessParameter)
  ))
_sym_db.RegisterMessage(PreProcessParameter)

NotrainParameter = _reflection.GeneratedProtocolMessageType('NotrainParameter', (_message.Message,), dict(
  DESCRIPTOR = _NOTRAINPARAMETER,
  __module__ = 'notrain_pb2'
  # @@protoc_insertion_point(class_scope:NotrainParameter)
  ))
_sym_db.RegisterMessage(NotrainParameter)


# @@protoc_insertion_point(module_scope)

