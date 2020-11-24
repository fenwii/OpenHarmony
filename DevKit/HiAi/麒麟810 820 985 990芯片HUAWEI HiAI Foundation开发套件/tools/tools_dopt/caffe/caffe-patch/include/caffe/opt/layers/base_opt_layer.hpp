/*
*
* Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
*
*/

#ifndef BASE_OPT_LAYER_HPP_
#define BASE_OPT_LAYER_HPP_

#include "caffe/blob.hpp"
#include "caffe/util/im2col.hpp"
#include "caffe/layers/base_data_layer.hpp"
#include "caffe/proto/caffe.pb.h"

namespace caffe {

template <typename Dtype>
class BaseOptLayer{
 public:
  explicit BaseOptLayer();
  ~ BaseOptLayer() {};
 protected:
  void Opt_cpu(vector<shared_ptr<Blob<Dtype> > > weights, vector<Blob<Dtype>* > datas, int is_train, int layer_type);
  void Opt_gpu(vector<shared_ptr<Blob<Dtype> > > weights, vector<Blob<Dtype>* > datas, int is_train, int layer_type);
  void Opt_BP_gpu(vector<shared_ptr<Blob<Dtype> > > weights, vector<Blob<Dtype>* > datas);

  shared_ptr<Blob<Dtype> > opt_weight_;
  // bottom for inference, can be either quantized or float
  shared_ptr<Blob<Dtype> > inf_bottom_;

  shared_ptr<Blob<Dtype> > para1;
  shared_ptr<Blob<Dtype> > para2;

  int Opt_input_algo_;
  int Opt_weight_algo_;
  int opt_input_or_weight_;

  Dtype scale_;
  Dtype offset_;
  float beta;

};

}  // namespace caffe

#endif  // BASE_OPT_LAYER_HPP_
