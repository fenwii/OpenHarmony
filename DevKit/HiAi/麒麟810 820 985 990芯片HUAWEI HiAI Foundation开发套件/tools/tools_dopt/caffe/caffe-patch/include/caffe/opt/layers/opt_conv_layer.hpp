/*
*
* Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
*
*/

#ifndef OPT_CONV_LAYER_HPP_
#define OPT_CONV_LAYER_HPP_
#include "caffe/blob.hpp"
#include "caffe/opt/layers/base_opt_conv_layer.hpp"
#include "caffe/opt/layers/base_opt_layer.hpp"

namespace caffe {

template <typename Dtype>
class OptConvolutionLayer : public BaseOptConvolutionLayer<Dtype>,
      public BaseOptLayer<Dtype> {
 public:
  explicit OptConvolutionLayer(const LayerParameter& param);
  virtual inline const char* type() const { return "OptConvolution"; }
  virtual ~OptConvolutionLayer();

 protected:
  void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Forward_gpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
  virtual void Backward_gpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
  virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);

  virtual inline bool reverse_dimensions() { return false; }
  virtual void compute_output_shape();

#ifdef USE_CUDNN
  bool handles_setup_;
  cudnnHandle_t* handle_;
  cudaStream_t*  stream_;

  // algorithms for forward and backwards convolutions
  cudnnConvolutionFwdAlgo_t *fwd_algo_;
  cudnnConvolutionBwdFilterAlgo_t *bwd_filter_algo_;
  cudnnConvolutionBwdDataAlgo_t *bwd_data_algo_;

  vector<cudnnTensorDescriptor_t> bottom_descs_, top_descs_;
  cudnnTensorDescriptor_t    bias_desc_;
  cudnnFilterDescriptor_t      filter_desc_;
  vector<cudnnConvolutionDescriptor_t> conv_descs_;
  int bottom_offset_, top_offset_, bias_offset_;

  size_t *workspace_fwd_sizes_;
  size_t *workspace_bwd_data_sizes_;
  size_t *workspace_bwd_filter_sizes_;
  size_t workspaceSizeInBytes;  // size of underlying storage
  void *workspaceData;  // underlying storage
  void **workspace;  // aliases into workspaceData
#endif
};

}
#endif //BASE_OPT_LAYER_HPP_