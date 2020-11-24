#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Script description:user_module Script.
# Copyright © Huawei Technologies Co., Ltd. 2010-2018. All rights reserved.
import os
import multiprocessing
from abc import ABCMeta
from abc import abstractmethod

import tensorflow as tf
import imagenet_preprocessing


try:
    import horovod.tensorflow as hvd
except ImportError:
    hvd = None


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
        :param global_step: a Python number. Global step to use for the decay computation.
        :return: A scalar Tensor of the same type as learning_rate. The decayed learning rate.
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


_DEFAULT_IMAGE_SIZE = 224
_NUM_CHANNELS = 3
_NUM_CLASSES = 1001

_NUM_IMAGES = {'train': 1281167, 'validation': 50000}

_NUM_TRAIN_FILES = 1024
_SHUFFLE_BUFFER = 10000


def get_filenames(is_training, data_dir):
    if is_training:
        return [os.path.join(data_dir, 'train-%05d-of-01024' % i) for i in range(_NUM_TRAIN_FILES)]
    else:
        return [os.path.join(data_dir, 'validation-%05d-of-00128' % i) for i in range(128)]


def _parse_example_proto(example_serialized):
    feature_map = {'image/encoded':
                        tf.FixedLenFeature([], dtype=tf.string, default_value=''),
                   'image/class/label':
                        tf.FixedLenFeature([], dtype=tf.int64, default_value=-1),
                   'image/class/text':
                        tf.FixedLenFeature([], dtype=tf.string, default_value='')}
    sparse_float32 = tf.VarLenFeature(dtype=tf.float32)
    feature_map.update(
        {k: sparse_float32 for k in ['image/object/bbox/xmin',
                                     'image/object/bbox/ymin',
                                     'image/object/bbox/xmax',
                                     'image/object/bbox/ymax']})

    features = tf.parse_single_example(example_serialized, feature_map)
    label = tf.cast(features['image/class/label'], dtype=tf.int32)

    xmin = tf.expand_dims(features['image/object/bbox/xmin'].values, 0)
    ymin = tf.expand_dims(features['image/object/bbox/ymin'].values, 0)
    xmax = tf.expand_dims(features['image/object/bbox/xmax'].values, 0)
    ymax = tf.expand_dims(features['image/object/bbox/ymax'].values, 0)

    bbox = tf.concat([ymin, xmin, ymax, xmax], 0)

    bbox = tf.expand_dims(bbox, 0)
    bbox = tf.transpose(bbox, [0, 2, 1])

    return features['image/encoded'], label, bbox


def parse_record(raw_record, is_training):
    image_buffer, label, bbox = _parse_example_proto(raw_record)

    image = imagenet_preprocessing.preprocess_image(
        image_buffer=image_buffer,
        bbox=bbox,
        output_height=_DEFAULT_IMAGE_SIZE,
        output_width=_DEFAULT_IMAGE_SIZE,
        num_channels=_NUM_CHANNELS,
        is_training=is_training)
    image = tf.cast(image, tf.float32)
    label = tf.one_hot(tf.reshape(label, []), _NUM_CLASSES)
    return image, label


class UserModule(UserModuleInterface):
    def __init__(self, epoch, batch_size):
        super(UserModule, self).__init__(epoch, batch_size)
        self.epoch = epoch
        self.batch_size = batch_size

    def loss_op(self, labels, logits):
        loss = tf.losses.softmax_cross_entropy(labels, logits)
        return loss

    def lr_scheduler(self, lr_init, global_step):
        learn_rate = tf.constant(lr_init, name="learning_rate")
        return learn_rate

    def metrics_op(self, inputs, outputs):
        index = tf.argmax(inputs, axis=1)
        metrics = tf.reduce_mean(tf.cast(tf.nn.in_top_k(outputs, index, 1), tf.float32))
        return metrics

    def build_dataset_search(self, dataset_dir, is_training, is_shuffle):
        filenames = get_filenames(is_training, dataset_dir)
        data = tf.data.Dataset.from_tensor_slices(filenames)

        if is_training:
            data_num = _NUM_IMAGES['train']
        else:
            data_num = _NUM_IMAGES['validation']
        if is_training and is_shuffle:
            data = data.shuffle(buffer_size=_NUM_TRAIN_FILES)
        if hvd is not None and hvd.size() > 1 and is_training:
            size = hvd.size()
            data = data.shard(size, hvd.rank())
        else:
            size = 1

        n_data_num = data_num // size

        dataset = data.apply(tf.data.experimental.parallel_interleave(
            tf.data.TFRecordDataset, cycle_length=10))
        dataset = dataset.prefetch(buffer_size=self.batch_size)
        if is_training and is_shuffle:
            dataset = dataset.shuffle(buffer_size=_SHUFFLE_BUFFER)
        dataset = dataset.repeat()
        num = multiprocessing.cpu_count()

        dataset = dataset.apply(
            tf.data.experimental.map_and_batch(
                lambda value: parse_record(value, is_training),
                batch_size=self.batch_size,
                num_parallel_batches=(num // 2),
                drop_remainder=True))

        dataset = dataset.prefetch(buffer_size=tf.contrib.data.AUTOTUNE)
        iterator = dataset.make_one_shot_iterator()

        return iterator, n_data_num


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


class ResNet(tf.keras.Model):
    """Define the ResNet"""

    def __init__(self, c_in, c_out, stride, scope="ResNet", data_format='channels_last'):
        super(ResNet, self).__init__()
        self.c_in = c_in
        self.filters = c_out
        self.stride = stride
        self.scope = scope
        self.conv0 = tf.keras.layers.Conv2D(c_out, [1, 1], strides=stride,
                                            padding='same',
                                            data_format=data_format,
                                            use_bias=False, name='conv0')
        self.conv1 = tf.keras.layers.Conv2D(c_out, [3, 3], strides=stride,
                                            padding='same',
                                            data_format=data_format,
                                            use_bias=False, name='conv1')
        self.conv2 = tf.keras.layers.Conv2D(c_out, [3, 3], strides=1,
                                            padding='same',
                                            data_format=data_format,
                                            use_bias=False, name='conv2')
        self.bn0 = tf.keras.layers.BatchNormalization(axis=3, momentum=0.9,
                                                      name='conv0/bn')
        self.bn1 = tf.keras.layers.BatchNormalization(axis=3, momentum=0.9,
                                                      name='conv1/bn')
        self.bn2 = tf.keras.layers.BatchNormalization(axis=3, momentum=0.9,
                                                      name='conv2/bn')
        self.act = tf.keras.layers.ReLU()

    def call(self, inputs, training=True):
        with tf.variable_scope(self.scope, [inputs]):
            if self.c_in != self.filters or self.stride != 1:
                shortcut = self.conv0(inputs)
                shortcut = self.bn0(shortcut, training=training)
            else:
                shortcut = inputs
            residual = self.conv1(inputs)
            residual = self.bn1(residual, training=training)
            residual = self.act(residual)

            residual = self.conv2(residual)
            residual = self.bn2(residual, training=training)
            output = self.act(shortcut + residual)
        return output


class PostNet(BasePostNet):
    def __init__(self):
        super(PostNet, self).__init__()
        self.resnet1 = ResNet(c_in=256, c_out=512, stride=2, scope="ResNet5_1")
        self.resnet2 = ResNet(c_in=512, c_out=512, stride=1, scope="ResNet5_2")
        self.avg_pool = tf.keras.layers.AveragePooling2D([7, 7], padding='SAME')
        self.fc = tf.keras.layers.Dense(_NUM_CLASSES, activation=None)
        self.act = tf.nn.relu

    def call(self, inputs, feature_layer=None, training=True):
        m = self.resnet1(inputs, training=training)
        m = self.resnet2(m, training=training)
        m = self.avg_pool(m)
        m = self.fc(m)
        m = tf.reshape(m, [-1, _NUM_CLASSES])
        return m
