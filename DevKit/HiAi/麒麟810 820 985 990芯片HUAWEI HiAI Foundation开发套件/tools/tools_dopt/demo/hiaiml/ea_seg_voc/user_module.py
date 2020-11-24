#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Script description:user_module Script.
# Copyright © Huawei Technologies Co., Ltd. 2010-2018. All rights reserved.
from abc import ABCMeta
from abc import abstractmethod
import os
import tensorflow as tf
import numpy as np
import multiprocessing

from deeplab.input_preprocess import preprocess_image_and_label
from deeplab.core import utils
from deeplab.utils import train_utils
from sklearn.metrics import confusion_matrix

scale_dimension = utils.scale_dimension
slim = tf.contrib.slim
tfexample_decoder = slim.tfexample_decoder

try:
    import horovod.tensorflow as hvd
except ImportError:
    hvd = None



_NUM_IMAGES = {'train': 1464, 'train_aug': 10582, 'trainval': 2913, 'val': 1449}
_NUM_CLASS = 21
_IGNORE_LABEL = 255
_NUM_TRAIN_FILES = 4
_SHUFFLE_BUFFER = 1000
OUTPUT_TYPE = "semantic"
outputs_to_num_classes = {OUTPUT_TYPE: 21}
DECODER_SCOPE = 'decoder'
LOGITS_SCOPE_NAME = 'logits'
MERGED_LOGITS_SCOPE = 'merged_logits'
WEIGHT_DECAY = 0.0001
LOGITS_KERNEL_SIZE = 1

params = {
    'crop_size': [513, 513],
    'min_scale_factor': 0.5,
    'max_scale_factor': 2.,
    'scale_factor_step_size': 0.25,
}

flags = tf.app.flags
FLAGS = flags.FLAGS


class BasePreNet(tf.keras.Model):
    __metaclass__ = ABCMeta

    @abstractmethod
    def __init__(self):
        super(BasePreNet, self).__init__()
        """
        Constructor of PreNet
        """
        pass

    @abstractmethod
    def call(self, inputs, training=True):
        """
        Build model's input macro-architecture.

        :param inputs:
        :param training:
        :return: A tensor - input of the TBS block.
        """
        pass


class BasePostNet(tf.keras.Model):
    __metaclass__ = ABCMeta

    @abstractmethod
    def __init__(self):
        super(BasePostNet, self).__init__()
        """
        Constructor of PostNet
        """
        pass

    @abstractmethod
    def call(self, inputs, feature_layer=None, training=True):
        """
       Build model's output macro-architecture.

       :param inputs:
       :param feature_layer:
       :param training:
       :return: A tensor - model's output.
       """
        pass


class UserModuleInterface:
    __metaclass__ = ABCMeta

    @abstractmethod
    def __init__(self, epoch, batch_size):
        self.epoch = epoch
        self.batch_size = batch_size

    @abstractmethod
    def build_dataset_search(self, dataset_dir, is_training, is_shuffle):
        """
        Build dataset for nas search

        :param dataset_dir:
        :param is_training:
        :param is_shuffle:
        :return:  dataset iterator and data num
        """
        pass

    @abstractmethod
    def loss_op(self, labels, logits):
        """
        Loss Function

        :param labels: GT labels.
        :param logits: logits of network's forward pass.
        :return: A Tensor - loss function's loss
        """
        pass

    @abstractmethod
    def lr_scheduler(self, lr_init, global_step):
        """
        Define learning rate update scheduler.

        :param lr_init: a Python number. The initial learning rate.
        :param global_step: a Python number. Global step to use for
        the decay computation.
        :return: A scalar Tensor of the same type as learning_rate.
        The decayed learning rate.
        """
        pass

    @abstractmethod
    def metrics_op(self, inputs, outputs):
        """
        define accuracy function

        :param inputs: GT labels.
        :param outputs: outputs of network's forward pass.
        :return:
        """
        pass


class ModelOptions(object):
    outputs_to_num_classes = {'semantic': 21}
    crop_size = [513, 513]
    atrous_rates = [6, 12, 18]
    output_stride = 16
    merge_method = 'max'
    add_image_level_feature = True
    image_pooling_crop_size = None
    aspp_with_batch_norm = True
    aspp_with_separable_conv = True
    multi_grid = None
    decoder_output_stride = 4
    decoder_use_separable_conv = True
    logits_kernel_size = 1
    model_variant = 'resnet_v1_50'
    depth_multiplier = 1.0
    dense_prediction_cell_config = None


def get_filenames(is_training, data_dir):
    if is_training:
        return [os.path.join(data_dir, 'train-%05d-of-00004.tfrecord' % i)
                for i in range(4)]
    else:
        return [os.path.join(data_dir, 'val-%05d-of-00004.tfrecord' % i)
                for i in range(4)]


def _parse_example_proto(example_serialized):
    feature_map = {
        'image/encoded': tf.FixedLenFeature(
            (), tf.string, default_value=''),
        'image/filename': tf.FixedLenFeature(
            (), tf.string, default_value=''),
        'image/format': tf.FixedLenFeature(
            (), tf.string, default_value='jpeg'),
        'image/height': tf.FixedLenFeature(
            (), tf.int64, default_value=0),
        'image/width': tf.FixedLenFeature(
            (), tf.int64, default_value=0),
        'image/segmentation/class/encoded': tf.FixedLenFeature(
            (), tf.string, default_value=''),
        'image/segmentation/class/format': tf.FixedLenFeature(
            (), tf.string, default_value='png'),
    }
    items_to_handlers = {
        'image': tfexample_decoder.Image(
            image_key='image/encoded',
            format_key='image/format',
            channels=3),
        'image_name': tfexample_decoder.Tensor('image/filename'),
        'height': tfexample_decoder.Tensor('image/height'),
        'width': tfexample_decoder.Tensor('image/width'),
        'labels_class': tfexample_decoder.Image(
            image_key='image/segmentation/class/encoded',
            format_key='image/segmentation/class/format',
            channels=1),
    }

    features = tf.parse_single_example(example_serialized, feature_map)
    outputs = {}
    items = list(items_to_handlers.keys())
    for item in items:
        handler = items_to_handlers[item]
        keys_to_tensors = {key: features[key] for key in handler.keys}
        outputs[item] = handler.tensors_to_item(keys_to_tensors)

    return outputs


def parse_record(raw_record, is_training):
    example = _parse_example_proto(raw_record)
    image = example['image']
    label = example['labels_class']
    image_name = example['image_name']
    height = example['height']
    width = example['width']

    if label is not None:
        if label.shape.ndims == 2:
            label = tf.expand_dims(label, 2)
        elif label.shape.ndims == 3 and label.shape.dims[2] == 1:
            pass
        else:
            raise ValueError('Input label shape must be [height, width], or '
                             '[height, width, 1].')

        label.set_shape([None, None, 1])
    if is_training:
        original_image, image, label = preprocess_image_and_label(
            image,
            label,
            crop_height=params['crop_size'][0],
            crop_width=params['crop_size'][1],
            min_scale_factor=params['min_scale_factor'],
            max_scale_factor=params['max_scale_factor'],
            scale_factor_step_size=params['scale_factor_step_size'],
            is_training=True,
            model_variant='resnet_v1_50')
    else:
        original_image, image, label = preprocess_image_and_label(
            image,
            label,
            crop_height=params['crop_size'][0],
            crop_width=params['crop_size'][1],
            is_training=False,
            model_variant='resnet_v1_50')
    sample = {'image': image, 'label': label, 'height': height, 'width': width,
              'image_name': image_name}
    return sample


def compute_iou(y_pred, y_true):
    y_pred = y_pred.flatten()
    y_true = y_true.flatten()
    current = confusion_matrix(y_true, y_pred)
    intersection = np.diag(current)
    ground_truth_set = current.sum(axis=1)
    predicted_set = current.sum(axis=0)
    union = ground_truth_set + predicted_set - intersection
    IoU = intersection / union.astype(np.float32)
    return np.mean(IoU)


class UserModule(UserModuleInterface):
    def __init__(self, epoch, batch_size):
        super(UserModule, self).__init__(epoch, batch_size)
        self.epoch = epoch
        self.batch_size = batch_size

    def loss_op(self, labels, logits):
        loss = train_utils.add_softmax_cross_entropy_loss_for_each_scale(
            logits[OUTPUT_TYPE],
            labels,
            21,
            _IGNORE_LABEL,
            loss_weight=1.0,
            upsample_logits=True,
            scope=OUTPUT_TYPE)
        return loss

    def lr_scheduler(self, lr_init, global_step):
        learn_rate = tf.constant(lr_init, name="learning_rate")
        return learn_rate

    def metrics_op(self, inputs, outputs):
        predictions = outputs[OUTPUT_TYPE]
        predictions = tf.reshape(predictions, shape=[-1])
        labels = tf.reshape(inputs, shape=[-1])
        labels = tf.where(
            tf.equal(labels, _IGNORE_LABEL), tf.zeros_like(labels), labels)
        miou = compute_iou(predictions.numpy(), labels.numpy())
        return miou

    def build_dataset_search(self, dataset_dir, is_training, is_shuffle):
        filenames = get_filenames(is_training, dataset_dir)
        data = tf.data.Dataset.from_tensor_slices(filenames)
        if is_training:
            data_num = _NUM_IMAGES['train']
        else:
            data_num = _NUM_IMAGES['val']
        if is_training and is_shuffle:
            data = data.shuffle(buffer_size=_NUM_TRAIN_FILES)

        dataset = data.apply(tf.data.experimental.parallel_interleave(
            tf.data.TFRecordDataset, cycle_length=10))
        dataset = dataset.prefetch(buffer_size=self.batch_size)
        if is_training and is_shuffle:
            dataset = dataset.shuffle(buffer_size=_SHUFFLE_BUFFER)
        dataset = dataset.repeat()
        num = multiprocessing.cpu_count()
        batchsize = self.batch_size if is_training else 1
        dataset = dataset.apply(
            tf.data.experimental.map_and_batch(
                lambda value: parse_record(value, is_training),
                batch_size=batchsize,
                num_parallel_batches=(num // 2),
                drop_remainder=True))

        dataset = dataset.prefetch(buffer_size=tf.contrib.data.AUTOTUNE)
        iterator = dataset.make_one_shot_iterator()

        return iterator, data_num


class PreNet(BasePreNet):
    def __init__(self):
        super(PreNet, self).__init__()
        self.conv0 = tf.keras.layers.Conv2D(64, [7, 7], strides=[2, 2],
                                            padding='same', name='in_conv1_ds0')
        self.bn = tf.keras.layers.BatchNormalization(axis=3, momentum=0.9, name='pre/bn')
        self.act = tf.keras.layers.ReLU()
        self.max_pool = tf.keras.layers.MaxPooling2D([3, 3], strides=2, padding='SAME')

    def call(self, inputs, training=True):
        m = self.conv0(inputs)
        m = self.bn(m, training=training)
        m = self.act(m)
        m = self.max_pool(m)
        return m


class PostNet(BasePostNet):
    def __init__(self):
        super(PostNet, self).__init__()
        self.refine_decoder = RefineByDecoder()
        self.branch_logits = GetBranchLogits()
        self.output_name = OUTPUT_TYPE
        self.outputs_to_scales_to_logits = {self.output_name: {}}

    def call(self, inputs, feature_layer=None, training=True):
        outputs_to_logits = {}
        outputs_to_logits[self.output_name] = self.branch_logits(inputs)

        image_pyramid = [1.0]
        logits_output_stride = (
                ModelOptions.decoder_output_stride or ModelOptions.output_stride)
        logits_height = scale_dimension(
            ModelOptions.crop_size[0],
            max(1.0, max(image_pyramid)) / logits_output_stride)
        logits_width = scale_dimension(
            ModelOptions.crop_size[1],
            max(1.0, max(image_pyramid)) / logits_output_stride)

        for output in sorted(outputs_to_logits):
            outputs_to_logits[output] = tf.image.resize_bilinear(
                outputs_to_logits[output], [logits_height, logits_width],
                align_corners=True)
        for output in sorted(ModelOptions.outputs_to_num_classes):
            self.outputs_to_scales_to_logits[output][MERGED_LOGITS_SCOPE] = outputs_to_logits[output]
        return self.outputs_to_scales_to_logits


class GetBranchLogits(tf.keras.Model):
    def __init__(self, atrous_rates=[6, 12, 18]):
        super(GetBranchLogits, self).__init__()

        self.semantic_conv_0 = tf.keras.layers.Conv2D(21, ModelOptions.logits_kernel_size,
                                                      strides=1,
                                                      padding="same",
                                                      dilation_rate=atrous_rates[0],
                                                      kernel_initializer=tf.truncated_normal_initializer(stddev=0.01),
                                                      kernel_regularizer=tf.keras.regularizers.l2(WEIGHT_DECAY),
                                                      activation=None, use_bias=True,
                                                      name='semantic_conv_0')

        self.semantic_conv_1 = tf.keras.layers.Conv2D(21, ModelOptions.logits_kernel_size,
                                                      strides=1,
                                                      padding="same",
                                                      dilation_rate=atrous_rates[1],
                                                      kernel_initializer=tf.truncated_normal_initializer(stddev=0.01),
                                                      kernel_regularizer=tf.keras.regularizers.l2(WEIGHT_DECAY),
                                                      activation=None, use_bias=True,
                                                      name='semantic_conv_1')

        self.semantic_conv_2 = tf.keras.layers.Conv2D(21, 1,
                                                      strides=1,
                                                      padding="same",
                                                      dilation_rate=atrous_rates[2],
                                                      kernel_initializer=tf.truncated_normal_initializer(stddev=0.01),
                                                      kernel_regularizer=tf.keras.regularizers.l2(WEIGHT_DECAY),
                                                      activation=None, use_bias=True,
                                                      name='semantic_conv_2')

    def call(self, features):
        branch_logits = []
        features = self.semantic_conv_0(features)
        branch_logits.append(features)
        features = self.semantic_conv_1(features)
        branch_logits.append(features)
        features = self.semantic_conv_2(features)
        branch_logits.append(features)
        return tf.add_n(branch_logits)


class RefineByDecoder(tf.keras.Model):
    def __init__(self):
        super(RefineByDecoder, self).__init__()

        self.feature_pro_conv0 = tf.keras.layers.Conv2D(48, 1,
                                                        strides=1,
                                                        padding="same",
                                                        kernel_regularizer=tf.keras.regularizers.l2(WEIGHT_DECAY),
                                                        activation=None, use_bias=False,
                                                        name='feature_projection0')
        self.feature_pro_bn0 = tf.keras.layers.BatchNormalization(momentum=0.9, epsilon=0.001,
                                                                  name='feature_projection_bn0')
        self.feature_pro_act0 = tf.keras.layers.ReLU()

        self.deco_Sconv0 = tf.keras.layers.DepthwiseConv2D(3, padding="same", use_bias=False,
                                                           depthwise_initializer=tf.truncated_normal_initializer(
                                                               stddev=0.33),
                                                           name="decoder_Sconv0_depthwise")
        self.deco_Sbn0 = tf.keras.layers.BatchNormalization(momentum=0.9, epsilon=0.001, name='decoder_Sbn0_depthwise')
        self.deco_Sact0 = tf.keras.layers.ReLU()

        self.deco_conv0 = tf.keras.layers.Conv2D(256, 1,
                                                 strides=1,
                                                 padding="same",
                                                 kernel_initializer=tf.truncated_normal_initializer(stddev=0.33),
                                                 kernel_regularizer=tf.keras.regularizers.l2(WEIGHT_DECAY),
                                                 activation=None, use_bias=False,
                                                 name='decoder_conv0_pointwise')
        self.deco_bn0 = tf.keras.layers.BatchNormalization(momentum=0.9, epsilon=0.001, name='decoder_bn0_pointwise')
        self.deco_act0 = tf.keras.layers.ReLU()

        self.deco_Sconv1 = tf.keras.layers.DepthwiseConv2D(3, padding="same", use_bias=False,
                                                           depthwise_initializer=tf.truncated_normal_initializer(
                                                               stddev=0.33),
                                                           name="decoder_Sconv1_depthwise")
        self.deco_Sbn1 = tf.keras.layers.BatchNormalization(momentum=0.9, epsilon=0.001, name='decoder_Sbn1_depthwise')
        self.deco_Sact1 = tf.keras.layers.ReLU()

        self.deco_conv1 = tf.keras.layers.Conv2D(256, 1,
                                                 strides=1,
                                                 padding="same",
                                                 kernel_initializer=tf.truncated_normal_initializer(stddev=0.33),
                                                 kernel_regularizer=tf.keras.regularizers.l2(WEIGHT_DECAY),
                                                 activation=None, use_bias=False,
                                                 name='decoder_conv1_pointwise')
        self.deco_bn1 = tf.keras.layers.BatchNormalization(momentum=0.9, epsilon=0.001, name='decoder_bn1_pointwise')
        self.deco_act1 = tf.keras.layers.ReLU()

    def call(self, features, end_points, decoder_height, decoder_width, decoder_use_separable_conv, is_training=False,
             fine_tune_batch_norm=False):
        self.decoder_height = decoder_height
        self.decoder_width = decoder_width
        self.decoder_use_separable_conv = decoder_use_separable_conv

        feature_list = [features]

        _x = self.feature_pro_conv0(end_points)
        _x = self.feature_pro_bn0(_x, training=is_training and fine_tune_batch_norm)
        _x = self.feature_pro_act0(_x)
        feature_list.append(_x)
        for j, feature in enumerate(feature_list):
            feature_list[j] = tf.image.resize_bilinear(
                feature, [self.decoder_height, self.decoder_width], align_corners=True)
            feature_list[j].set_shape([feature_shape[0], self.decoder_height, self.decoder_width, feature_shape[3]])
        _x = self.deco_Sconv0(tf.concat(feature_list, 3))
        _x = self.deco_Sbn0(_x)
        _x = self.deco_Sact0(_x)
        _x = self.deco_conv0(_x)
        _x = self.deco_bn0(_x)
        _x = self.deco_act0(_x)

        _x = self.deco_Sconv1(_x)
        _x = self.deco_Sbn1(_x)
        _x = self.deco_Sact1(_x)
        _x = self.deco_conv1(_x)
        _x = self.deco_bn1(_x)
        _x = self.deco_act1(_x)
        return _x
