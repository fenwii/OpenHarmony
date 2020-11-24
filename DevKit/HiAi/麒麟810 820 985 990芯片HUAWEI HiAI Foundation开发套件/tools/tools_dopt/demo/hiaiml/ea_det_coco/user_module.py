#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Script description:user_module Script.
# Copyright © Huawei Technologies Co., Ltd. 2010-2018. All rights reserved.
from abc import ABCMeta
from abc import abstractmethod
import tensorflow as tf
from tensorflow.keras.regularizers import l2
from pycocotools.coco import COCO
from pycocotools.cocoeval import COCOeval
import json
from math import ceil
import os
import numpy as np
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
        
val_batch_size = 1
predictor_layers = 6
predictor_sizes = [(38, 38), (19, 19), (10, 10), (5, 5), (3, 3), (1, 1)]



class UserModule(UserModuleInterface):
    def __init__(self, epoch, batch_size):
        super(UserModule, self).__init__(epoch, batch_size)
        self.epoch = epoch
        self.batch_size = batch_size

    def loss_op(self, labels, logits):
        ssd_loss = SSDLoss(neg_pos_ratio=3, alpha=1.0)
        loss = ssd_loss.compute_loss(labels, logits)
        return loss

    def lr_scheduler(self, lr_init, global_step):
        learn_rate = tf.constant(lr_init, name="learning_rate")
        return learn_rate

    def metrics_op(self, inputs, outputs):
        valid_dir = inputs[0]
        model = inputs[1]
        block_choice = inputs[2]
        data_generator = outputs[0]
        proxy_val_image_ids = outputs[1]
        data_size = outputs[2]

        MS_COCO_dataset_annotations_filename = os.path.join(valid_dir, "annotations/instances_val2017.json")
        if hvd is not None:
            results_file = 'detections_val2017_ssd300_results_{}.json'.format(hvd.rank())
        else:
            results_file = 'detections_val2017_ssd300_results.json'
        res_mAP = cocoEval.stats[0]
        return res_mAP

    def build_dataset_search(self, dataset_dir, is_training=True, is_shuffle=True):
        if is_training:
            train_images_dir = os.path.join(dataset_dir, "train2017")
            train_labels_filename = os.path.join(dataset_dir, "annotations/instances_train2017.json")
            return train_generator, train_dataset_size
        else:
            MS_COCO_dataset_images_dir = os.path.join(dataset_dir, "val2017")
            MS_COCO_dataset_annotations_filename = os.path.join(dataset_dir, "annotations/instances_val2017.json")
            return [val_generator, val_dataset], val_dataset_size


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
        self.act = tf.nn.relu
        self.l2_regularization = 0.0005
  
        self.aspect_ratios_global = None
        self.aspect_ratios_per_layer = aspect_ratios
        self.n_classes = n_classes + 1  # Account for the background class.
        self.n_predictor_layers = predictor_layers  # The number of predictor conv layers in the network is 6 for the original SSD300.
        l2_reg = self.l2_regularization  # Make the internal name shorter.

        # Compute the number of boxes to be predicted per cell for each predictor layer.
        # We need this so that we know how many channels the predictor layers need to have.
        if self.aspect_ratios_per_layer:
            n_boxes = []
            for ar in self.aspect_ratios_per_layer:
                if (1 in ar) & two_boxes_for_ar1:
                    n_boxes.append(len(ar) + 1)  # +1 for the second box for aspect ratio 1
                else:
                    n_boxes.append(len(ar))
        else:  # If only a global aspect ratio list was passed, then the number of boxes is the same for each predictor layer
            if (1 in self.aspect_ratios_global) & two_boxes_for_ar1:
                n_boxes = len(self.aspect_ratios_global) + 1
            else:
                n_boxes = len(self.aspect_ratios_global)
            n_boxes = [n_boxes] * self.n_predictor_layers

        self.fc6 = tf.keras.layers.Conv2D(filters=1024, kernel_size=[3, 3], dilation_rate=(6, 6), padding='same',
                                          kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                          activation=self.act, name='fc6')

        self.fc7 = tf.keras.layers.Conv2D(filters=1024, kernel_size=[1, 1], padding='same',
                                          kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                          activation=self.act, name='fc7')

        self.conv6_1 = tf.keras.layers.Conv2D(filters=256, kernel_size=[1, 1], padding='same',
                                              kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                              activation=self.act, name='conv6_1')
        self.conv6_1_pad = tf.keras.layers.ZeroPadding2D(padding=((1, 1), (1, 1)), name='conv6_padding')
        self.conv6_2 = tf.keras.layers.Conv2D(filters=512, kernel_size=[3, 3], strides=(2, 2), padding='valid',
                                              kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                              activation=self.act, name='conv6_2')

        self.conv7_1 = tf.keras.layers.Conv2D(filters=128, kernel_size=[1, 1], padding='same',
                                              kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                              activation=self.act, name='conv7_1')
        self.conv7_1_pad = tf.keras.layers.ZeroPadding2D(padding=((1, 1), (1, 1)), name='conv7_padding')
        self.conv7_2 = tf.keras.layers.Conv2D(filters=256, kernel_size=[3, 3], strides=(2, 2), padding='valid',
                                              kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                              activation=self.act, name='conv7_2')

        self.conv8_1 = tf.keras.layers.Conv2D(filters=128, kernel_size=[1, 1], padding='same',
                                              kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                              activation=self.act, name='conv8_1')
        self.conv8_2 = tf.keras.layers.Conv2D(filters=256, kernel_size=[3, 3], strides=(1, 1), padding='valid',
                                              kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                              activation=self.act, name='conv8_2')

        self.conv9_1 = tf.keras.layers.Conv2D(filters=128, kernel_size=[1, 1], padding='same',
                                              kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                              activation=self.act, name='conv9_1')
        self.conv9_2 = tf.keras.layers.Conv2D(filters=256, kernel_size=[3, 3], strides=(1, 1), padding='valid',
                                              kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                              activation=self.act, name='conv9_2')

        # Build the convolutional predictor layers on top of the base network
        # We precidt `n_classes` confidence values for each box, hence the confidence predictors have depth `n_boxes * n_classes`
        # Output shape of the confidence layers: `(batch, height, width, n_boxes * n_classes)`

        self.conv4_3_norm_mbox_conf = tf.keras.layers.Conv2D(filters=n_boxes[0] * self.n_classes, kernel_size=[3, 3],
                                                             padding='same',
                                                             kernel_initializer='he_normal',
                                                             kernel_regularizer=l2(l2_reg),
                                                             activation=None, name='conv4_3_norm_mbox_conf')

        self.fc7_mbox_conf = tf.keras.layers.Conv2D(filters=n_boxes[1] * self.n_classes, kernel_size=[3, 3],
                                                    padding='same',
                                                    kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                                    activation=None, name='fc7_mbox_conf')

        self.conv6_2_mbox_conf = tf.keras.layers.Conv2D(filters=n_boxes[2] * self.n_classes, kernel_size=[3, 3],
                                                        padding='same',
                                                        kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                                        activation=None, name='conv6_2_mbox_conf')

        self.conv7_2_mbox_conf = tf.keras.layers.Conv2D(filters=n_boxes[3] * self.n_classes, kernel_size=[3, 3],
                                                        padding='same',
                                                        kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                                        activation=None, name='conv7_2_mbox_conf')

        self.conv8_2_mbox_conf = tf.keras.layers.Conv2D(filters=n_boxes[4] * self.n_classes, kernel_size=[3, 3],
                                                        padding='same',
                                                        kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                                        activation=None, name='conv8_2_mbox_conf')

        self.conv9_2_mbox_conf = tf.keras.layers.Conv2D(filters=n_boxes[5] * self.n_classes, kernel_size=[3, 3],
                                                        padding='same',
                                                        kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                                        activation=None, name='conv9_2_mbox_conf')

        # We predict 4 box coordinates for each box, hence the localization predictors have depth `n_boxes * 4`
        # Output shape of the localization layers: `(batch, height, width, n_boxes * 4)`
        self.conv4_3_norm_mbox_loc = tf.keras.layers.Conv2D(filters=n_boxes[0] * 4, kernel_size=[3, 3], padding='same',
                                                            kernel_initializer='he_normal',
                                                            kernel_regularizer=l2(l2_reg),
                                                            activation=None, name='conv4_3_norm_mbox_loc')

        self.fc7_mbox_loc = tf.keras.layers.Conv2D(filters=n_boxes[1] * 4, kernel_size=[3, 3], padding='same',
                                                   kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                                   activation=None, name='fc7_mbox_loc')

        self.conv6_2_mbox_loc = tf.keras.layers.Conv2D(filters=n_boxes[2] * 4, kernel_size=[3, 3], padding='same',
                                                       kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                                       activation=None, name='conv6_2_mbox_loc')

        self.conv7_2_mbox_loc = tf.keras.layers.Conv2D(filters=n_boxes[3] * 4, kernel_size=[3, 3], padding='same',
                                                       kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                                       activation=None, name='conv7_2_mbox_loc')

        self.conv8_2_mbox_loc = tf.keras.layers.Conv2D(filters=n_boxes[4] * 4, kernel_size=[3, 3], padding='same',
                                                       kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                                       activation=None, name='conv8_2_mbox_loc')

        self.conv9_2_mbox_loc = tf.keras.layers.Conv2D(filters=n_boxes[5] * 4, kernel_size=[3, 3], padding='same',
                                                       kernel_initializer='he_normal', kernel_regularizer=l2(l2_reg),
                                                       activation=None, name='conv9_2_mbox_loc')

    def call(self, inputs, feature_layer, training=True):

        ############################################################################
        # Compute the anchor box parameters.
        ############################################################################
        tbs_feature_choose1, tbs_feature_choose2 = feature_layer
        # Set the aspect ratios for each predictor layer. These are only needed for the anchor box layers.
        if self.aspect_ratios_per_layer:
            aspect_ratios = self.aspect_ratios_per_layer
        else:
            aspect_ratios = [self.aspect_ratios_global] * self.n_predictor_layers


        fc6 = self.fc6(inputs)
        fc7 = self.fc7(fc6)
        conv6_1 = self.conv6_1(fc7)
        conv6_1_pad = self.conv6_1_pad(conv6_1)
        conv6_2 = self.conv6_2(conv6_1_pad)

        conv7_1 = self.conv7_1(conv6_2)
        conv7_1_pad = self.conv7_1_pad(conv7_1)
        conv7_2 = self.conv7_2(conv7_1_pad)

        conv8_1 = self.conv8_1(conv7_2)
        conv8_2 = self.conv8_2(conv8_1)

        # Feed tbs_feature_choose1 into the L2 normalization layer
        resnet_stage1_norm = L2Normalization(gamma_init=20, name='conv4_3_norm')(tbs_feature_choose1)

        ### Build the convolutional predictor layers on top of the base network
        # We precidt `n_classes` confidence values for each box, hence the confidence predictors have depth `n_boxes * n_classes`
        # Output shape of the confidence layers: `(batch, height, width, n_boxes * n_classes)`
        conv4_3_norm_mbox_conf = self.conv4_3_norm_mbox_conf(resnet_stage1_norm)
        fc7_mbox_conf = self.fc7_mbox_conf(tbs_feature_choose2)
        conv6_2_mbox_conf = self.conv6_2_mbox_conf(fc7)
        conv7_2_mbox_conf = self.conv7_2_mbox_conf(conv6_2)
        conv8_2_mbox_conf = self.conv8_2_mbox_conf(conv7_2)
        conv9_2_mbox_conf = self.conv9_2_mbox_conf(conv8_2)

        # We predict 4 box coordinates for each box, hence the localization predictors have depth `n_boxes * 4`
        # Output shape of the localization layers: `(batch, height, width, n_boxes * 4)`
        conv4_3_norm_mbox_loc = self.conv4_3_norm_mbox_loc(resnet_stage1_norm)
        fc7_mbox_loc = self.fc7_mbox_loc(tbs_feature_choose2)
        conv6_2_mbox_loc = self.conv6_2_mbox_loc(fc7)
        conv7_2_mbox_loc = self.conv7_2_mbox_loc(conv6_2)
        conv8_2_mbox_loc = self.conv8_2_mbox_loc(conv7_2)
        conv9_2_mbox_loc = self.conv9_2_mbox_loc(conv8_2)
        

        ### Reshape
        # Reshape the class predictions, yielding 3D tensors of shape `(batch, height * width * n_boxes, n_classes)`
        # We want the classes isolated in the last axis to perform softmax on them
        conv4_3_norm_mbox_conf_reshape = tf.keras.layers.Reshape((-1, self.n_classes),
                                                                 name='conv4_3_norm_mbox_conf_reshape')(
            conv4_3_norm_mbox_conf)
        fc7_mbox_conf_reshape = tf.keras.layers.Reshape((-1, self.n_classes), name='fc7_mbox_conf_reshape')(
            fc7_mbox_conf)
        conv6_2_mbox_conf_reshape = tf.keras.layers.Reshape((-1, self.n_classes), name='conv6_2_mbox_conf_reshape')(
            conv6_2_mbox_conf)
        conv7_2_mbox_conf_reshape = tf.keras.layers.Reshape((-1, self.n_classes), name='conv7_2_mbox_conf_reshape')(
            conv7_2_mbox_conf)
        conv8_2_mbox_conf_reshape = tf.keras.layers.Reshape((-1, self.n_classes), name='conv8_2_mbox_conf_reshape')(
            conv8_2_mbox_conf)
        conv9_2_mbox_conf_reshape = tf.keras.layers.Reshape((-1, self.n_classes), name='conv9_2_mbox_conf_reshape')(
            conv9_2_mbox_conf)

        # Reshape the box predictions, yielding 3D tensors of shape `(batch, height * width * n_boxes, 4)`
        # We want the four box coordinates isolated in the last axis to compute the smooth L1 loss
        conv4_3_norm_mbox_loc_reshape = tf.keras.layers.Reshape((-1, 4), name='conv4_3_norm_mbox_loc_reshape')(
            conv4_3_norm_mbox_loc)
        fc7_mbox_loc_reshape = tf.keras.layers.Reshape((-1, 4), name='fc7_mbox_loc_reshape')(fc7_mbox_loc)
        conv6_2_mbox_loc_reshape = tf.keras.layers.Reshape((-1, 4), name='conv6_2_mbox_loc_reshape')(conv6_2_mbox_loc)
        conv7_2_mbox_loc_reshape = tf.keras.layers.Reshape((-1, 4), name='conv7_2_mbox_loc_reshape')(conv7_2_mbox_loc)
        conv8_2_mbox_loc_reshape = tf.keras.layers.Reshape((-1, 4), name='conv8_2_mbox_loc_reshape')(conv8_2_mbox_loc)
        conv9_2_mbox_loc_reshape = tf.keras.layers.Reshape((-1, 4), name='conv9_2_mbox_loc_reshape')(conv9_2_mbox_loc)

        # Reshape the anchor box tensors, yielding 3D tensors of shape `(batch, height * width * n_boxes, 8)`
        conv4_3_norm_mbox_priorbox_reshape = tf.keras.layers.Reshape((-1, 8),
                                                                     name='conv4_3_norm_mbox_priorbox_reshape')(
            conv4_3_norm_mbox_priorbox)
        fc7_mbox_priorbox_reshape = tf.keras.layers.Reshape((-1, 8), name='fc7_mbox_priorbox_reshape')(
            fc7_mbox_priorbox)
        conv6_2_mbox_priorbox_reshape = tf.keras.layers.Reshape((-1, 8), name='conv6_2_mbox_priorbox_reshape')(
            conv6_2_mbox_priorbox)
        conv7_2_mbox_priorbox_reshape = tf.keras.layers.Reshape((-1, 8), name='conv7_2_mbox_priorbox_reshape')(
            conv7_2_mbox_priorbox)
        conv8_2_mbox_priorbox_reshape = tf.keras.layers.Reshape((-1, 8), name='conv8_2_mbox_priorbox_reshape')(
            conv8_2_mbox_priorbox)
        conv9_2_mbox_priorbox_reshape = tf.keras.layers.Reshape((-1, 8), name='conv9_2_mbox_priorbox_reshape')(
            conv9_2_mbox_priorbox)

        ### Concatenate the predictions from the different layers

        # Axis 0 (batch) and axis 2 (n_classes or 4, respectively) are identical for all layer predictions,
        # so we want to concatenate along axis 1, the number of boxes per layer
        # Output shape of `mbox_conf`: (batch, n_boxes_total, n_classes)
        mbox_conf = tf.keras.layers.concatenate([conv4_3_norm_mbox_conf_reshape,
                                                 fc7_mbox_conf_reshape,
                                                 conv6_2_mbox_conf_reshape,
                                                 conv7_2_mbox_conf_reshape,
                                                 conv8_2_mbox_conf_reshape,
                                                 conv9_2_mbox_conf_reshape],
                                                axis=1, name='mbox_conf')

        # Output shape of `mbox_loc`: (batch, n_boxes_total, 4)
        mbox_loc = tf.keras.layers.concatenate([conv4_3_norm_mbox_loc_reshape,
                                                fc7_mbox_loc_reshape,
                                                conv6_2_mbox_loc_reshape,
                                                conv7_2_mbox_loc_reshape,
                                                conv8_2_mbox_loc_reshape,
                                                conv9_2_mbox_loc_reshape],
                                               axis=1, name='mbox_loc')

        # Output shape of `mbox_priorbox`: (batch, n_boxes_total, 8)
        mbox_priorbox = tf.keras.layers.concatenate([conv4_3_norm_mbox_priorbox_reshape,
                                                     fc7_mbox_priorbox_reshape,
                                                     conv6_2_mbox_priorbox_reshape,
                                                     conv7_2_mbox_priorbox_reshape,
                                                     conv8_2_mbox_priorbox_reshape,
                                                     conv9_2_mbox_priorbox_reshape],
                                                    axis=1, name='mbox_priorbox')

        # The box coordinate predictions will go into the loss function just the way they are,
        # but for the class predictions, we'll apply a softmax activation layer first
        mbox_conf_softmax = tf.keras.activations.softmax(mbox_conf)

        # Concatenate the class and box predictions and the anchors to one large predictions vector
        # Output shape of `predictions`: (batch, n_boxes_total, n_classes + 4 + 8)
        predictions = tf.keras.layers.concatenate([mbox_conf_softmax, mbox_loc, mbox_priorbox], axis=2,
                                                  name='predictions')

        return predictions