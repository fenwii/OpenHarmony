#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright © Huawei Technologies Co., Ltd. 2010-2018. All rights reserved.
"""ConvNet model for Mnist datasets."""

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
from abc import ABCMeta
from abc import abstractmethod



class UserModelInterface():
    """ abstract base class """
    __metaclass__ = ABCMeta
    """Interface for user defined model."""
    def __init__(self, dataset_dir, train_batch_size, #pylint: disable=R0913
        test_batch_size, train_batch_num, test_batch_num):
        """Constructor function."""
        self.dataset_dir = dataset_dir
        self.train_batch_size = train_batch_size
        self.test_batch_size = test_batch_size
        self.train_batch_num = train_batch_num
        self.test_batch_num = test_batch_num

    @abstractmethod
    def forward_fn(self, inputs, is_train):
        """Forward pass function.

        Args:
        * inputs: inputs to the network's forward pass
        * is_train: Boolean, True for training, False for evaluation

        Returns:
        * outputs: outputs from the network's forward pass
        """
        pass #pylint: disable=W0107

    @abstractmethod
    def loss_op(self, inputs, outputs):
        """loss function for training.

        Args:
        * inputs: inputs to the network's forward pass
        * outputs: outputs of the network's forward pass

        Returns:
        * loss: TF op of loss function
        """
        pass #pylint: disable=W0107

    @abstractmethod
    def metrics_op(self, inputs, outputs):
        """metrics function for evaluation.

        Args:
        * inputs: inputs to the network's forward pass
        * outputs: outputs of the network's forward pass

        Returns:
        * metrics: TF op of metrics function
        """
        pass #pylint: disable=W0107

    @abstractmethod
    def get_batch_num(self, is_train):
        """Get the iteration number for training or evaluation.

        Args:
        * is_train: Boolean, True for training, False for evaluation

        Returns:
        * iter_num: iteration number
        """
        pass #pylint: disable=W0107

    @abstractmethod
    def config_lr_policy(self, global_step):
        """config the learning rate policy during training

        Args:
        * global_step: int

        Returns:
        * learning rate
        """
        pass #pylint: disable=W0107




class UserModel(UserModelInterface):
    """Class for user defined model. Don't change the class name."""

    def __init__(self, dataset_dir, train_batch_size, test_batch_size, #pylint: disable=R0913
        train_batch_num, test_batch_num):
        """Constructor function."""
        super(UserModel, self).__init__(
            dataset_dir, train_batch_size, test_batch_size, train_batch_num, test_batch_num)
        self.data = None

    def get_next_batch(self, is_train):
        """ get next input image batch """
        if self.data is None:
            self.data = input_data.read_data_sets(self.dataset_dir, one_hot=True)
        if is_train is True:
            return self.data.train.next_batch(self.train_batch_size)
        else:
            return self.data.test.next_batch(self.test_batch_size)

    def get_input_placeholder(self): #pylint: disable=R0201
        """ get input placeholder """
        images = tf.placeholder(tf.float32, [None, 784])
        labels = tf.placeholder(tf.float32, [None, 10])
        return [images, labels]

    def forward_fn(self, inputs, is_train):
        """Forward pass function.

        Args:
        * inputs: inputs to the network's forward pass
        * is_train: Boolean, True for training, False for testing

        Returns:
        * outputs: outputs from the network's forward pass
        """
        # split images and labels from inputs
        images, _ = inputs
        images = tf.reshape(images, [-1, 28, 28, 1])
        # conv1
        outputs = tf.layers.conv2d(images, 32, [5, 5], padding='same',
            activation=tf.nn.relu, name='conv1')
        outputs = tf.layers.max_pooling2d(outputs, [2, 2], 2, padding='same', name='pool1')

        # conv2
        outputs = tf.layers.conv2d(outputs, 64, [5, 5], padding='same',
            activation=tf.nn.relu, name='conv2')
        outputs = tf.layers.max_pooling2d(outputs, [2, 2], 2, padding='same', name='pool2')

        # fc1
        outputs = tf.layers.flatten(outputs, name='flatten')
        outputs = tf.layers.dense(outputs, 1024, activation=tf.nn.relu, name='fc1')

        # dropout
        outputs = tf.layers.dropout(outputs, training=is_train, name='dropout')

        # fc2
        outputs = tf.layers.dense(outputs, 10, name='fc2')

        return outputs

    def loss_op(self, inputs, outputs):
        """loss function for training.

        Args:
        * inputs: inputs to the network's forward pass
        * outputs: outputs of the network's forward pass

        Returns:
        * loss: TF op of loss function
        """

        # split images and labels from inputs
        _, labels = inputs
        loss = tf.losses.softmax_cross_entropy(labels, outputs)
        return loss

    def metrics_op(self, inputs, outputs):
        """metrics function for testing.

        Args:
        * inputs: inputs to the network's forward pass
        * outputs: outputs of the network's forward pass

        Returns:
        * metrics: TF op of metrics function
        """
        # split images and labels from inputs
        _, labels = inputs
        index = tf.argmax(labels, axis=1)
        metrics = tf.reduce_mean(tf.cast(tf.nn.in_top_k(outputs, index, 1), tf.float32))
        return metrics

    def get_batch_num(self, is_train):
        """Get the iteration number for training or testing.

        Args:
        * is_train: Boolean, True for training, False for testing

        Returns:
        * iter_num: iteration number
        """
        if is_train is True:
            return self.train_batch_num
        else:
            return self.test_batch_num

    def config_lr_policy(self, global_step):
        """config the learning rate policy during training

        Args:
        * global_step: int

        Returns:
        * learning rate
        """
        train_num = 60000
        train_batch_size = 600
        epochs = [3., 6., 8., 9.]
        decay_rates = [1., 0.1, 0.01, 0.001, 0.0001]
        lr_init = 0.1
        num_per_epoch = float(train_num / train_batch_size)
        boundaries = [int(num_per_epoch * id_epoch) for id_epoch in epochs]
        learning_rates = [lr_init * decay_rate for decay_rate in decay_rates]

        learning_rate = tf.train.piecewise_constant(global_step, boundaries, learning_rates)

        return learning_rate

