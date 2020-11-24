/*
*
* Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
*
*/

#ifndef BASE_INNER_PRODUCT_LAYER_HPP_
#define BASE_INNER_PRODUCT_LAYER_HPP_
#include "caffe/layers/inner_product_layer.hpp"
#include "caffe/blob.hpp"
#include "caffe/opt/layers/base_opt_layer.hpp"

namespace caffe {

template <typename Dtype>
class OptFcLayer : public InnerProductLayer<Dtype>,
      public BaseOptLayer<Dtype>{
 public:
  explicit OptFcLayer(const LayerParameter& param);
  ~ OptFcLayer() {}
  void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual inline const char* type() const { return "OptFc"; }
  virtual inline int ExactNumBottomBlobs() const { return 1; }
  virtual inline int ExactNumTopBlobs() const { return 1; }

 protected:
  virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Forward_gpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
  virtual void Backward_gpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
};

}
#endif //BASE_INNER_PRODUCT_LAYER_HPP_
