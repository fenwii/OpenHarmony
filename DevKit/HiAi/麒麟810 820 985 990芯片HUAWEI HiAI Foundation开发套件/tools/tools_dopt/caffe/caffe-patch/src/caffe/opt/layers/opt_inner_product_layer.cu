/*
*
* Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
*
*/

#include <vector>

#include "caffe/filler.hpp"
#include "caffe/layers/inner_product_layer.hpp"
#include "caffe/util/math_functions.hpp"

#include "caffe/opt/layers/opt_inner_product_layer.hpp"
#include "caffe/opt/utils/math_funcs.hpp"

namespace caffe {

template <typename Dtype>
void OptFcLayer<Dtype>::Forward_gpu(const vector<Blob<Dtype>*>& bottom,
    const vector<Blob<Dtype>*>& top) {  
  //const Dtype* bottom_data = bottom[0]->gpu_data();
  Dtype* top_data = top[0]->mutable_gpu_data();

  int index = 0;
  if (this->bias_term_) 
    index += 1;

  if (this->blobs_.size() != index+7)
  {
    printf("invalid blobs_ size!\n");
    return;
  }

  vector<shared_ptr<Blob<Dtype> > > weights;
  weights.push_back(this->blobs_[0]);
  weights.push_back(this->blobs_[index+1]);
  weights.push_back(this->blobs_[index+2]);
  weights.push_back(this->blobs_[index+3]);
  weights.push_back(this->blobs_[index+4]);
  weights.push_back(this->blobs_[index+5]);
  weights.push_back(this->blobs_[index+6]);

  weights.push_back(this->inf_bottom_);
  vector<Blob<Dtype>* > datas;
  datas.push_back(top[0]);
  datas.push_back(bottom[0]);
  int is_train = 0;
  if(this->phase_ == TRAIN)
  {
    is_train = 1;
    this->opt_input_or_weight_ = OPT_WEIGHT;
    this->Opt_gpu(weights, datas, is_train, OPT_FC);      
  }
  
  this->opt_input_or_weight_ = OPT_INPUT;
  this->Opt_gpu(weights, datas, is_train, OPT_FC);

  const Dtype* weight = this->blobs_[index+1]->gpu_data();  //quantized weight
  if (this->inf_bottom_ == NULL)
  {
      printf("inf_bottom_ is NULL!\n");
      return;
  }
  const Dtype* inf_bottom_data = this->inf_bottom_->gpu_data();
  if (this->M_ == 1) {
    caffe_gpu_gemv<Dtype>(CblasNoTrans, this->N_, this->K_, (Dtype)1.,
                         weight, inf_bottom_data, (Dtype)0., top_data);
    if (this->bias_term_)
      caffe_gpu_axpy<Dtype>(this->N_, this->bias_multiplier_.cpu_data()[0],
                            this->blobs_[1]->gpu_data(), top_data);
  } else {
    caffe_gpu_gemm<Dtype>(CblasNoTrans,
                          this->transpose_ ? CblasNoTrans : CblasTrans,
                          this->M_, this->N_, this->K_, (Dtype)1.,
                          inf_bottom_data, weight, (Dtype)0., top_data);
    if (this->bias_term_)
      caffe_gpu_gemm<Dtype>(CblasNoTrans, CblasNoTrans, this->M_, this->N_, 1, (Dtype)1.,
                            this->bias_multiplier_.gpu_data(),
                            this->blobs_[1]->gpu_data(), (Dtype)1., top_data);
  }
}

template <typename Dtype>
void OptFcLayer<Dtype>::Backward_gpu(const vector<Blob<Dtype>*>& top,
    const vector<bool>& propagate_down,
    const vector<Blob<Dtype>*>& bottom) {

  int index = 0;
  if (this->bias_term_) 
    index += 1;

  if (this->param_propagate_down_[0]) {
    const Dtype* top_diff = top[0]->gpu_diff();
    const Dtype* bottom_data = bottom[0]->gpu_data();
    // Gradient with respect to weight
    if (this->transpose_) {
      caffe_gpu_gemm<Dtype>(CblasTrans, CblasNoTrans,
          this->K_, this->N_, this->M_,
          (Dtype)1., bottom_data, top_diff,
          (Dtype)1., this->blobs_[0]->mutable_gpu_diff());
    } else {
      caffe_gpu_gemm<Dtype>(CblasTrans, CblasNoTrans,
          this->N_, this->K_, this->M_,
          (Dtype)1., top_diff, bottom_data,
          (Dtype)1., this->blobs_[0]->mutable_gpu_diff());
    }
  }
  if (this->bias_term_ && this->param_propagate_down_[1]) {
    const Dtype* top_diff = top[0]->gpu_diff();
    // Gradient with respect to bias
    caffe_gpu_gemv<Dtype>(CblasTrans, this->M_, this->N_, (Dtype)1., top_diff,
        this->bias_multiplier_.gpu_data(), (Dtype)1.,
        this->blobs_[1]->mutable_gpu_diff());
  }

  if (propagate_down[0]) {
    const Dtype* top_diff = top[0]->gpu_diff();
    // Gradient with respect to bottom data
    if (this->transpose_) {
      caffe_gpu_gemm<Dtype>(CblasNoTrans, CblasTrans,
          this->M_, this->K_, this->N_,
          (Dtype)1., top_diff, this->blobs_[index+1]->gpu_data(), //quantized weight
          (Dtype)0., bottom[0]->mutable_gpu_diff());
    } else {
      caffe_gpu_gemm<Dtype>(CblasNoTrans, CblasNoTrans,
          this->M_, this->K_, this->N_,
         (Dtype)1., top_diff, this->blobs_[index+1]->gpu_data(),  //quantized weight
         (Dtype)0., bottom[0]->mutable_gpu_diff()); 
    }
  }

  vector<shared_ptr<Blob<Dtype> > > weights;
  if (this->blobs_.size() != index+7)
  {
    printf("invalid blobs_ size!\n");
    return;
  }
  weights.push_back(this->blobs_[0]);
  weights.push_back(this->blobs_[index+4]);
  weights.push_back(this->blobs_[index+5]);
  vector<Blob<Dtype>* > datas;
  datas.push_back(top[0]);
  datas.push_back(bottom[0]);

  this->opt_input_or_weight_ = OPT_INPUT;
  this->Opt_BP_gpu(weights, datas);
}

INSTANTIATE_LAYER_GPU_FUNCS(OptFcLayer);

}  // namespace caffe
