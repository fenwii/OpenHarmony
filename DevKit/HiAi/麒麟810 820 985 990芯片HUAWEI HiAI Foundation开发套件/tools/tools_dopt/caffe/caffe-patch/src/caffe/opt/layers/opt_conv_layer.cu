/*
*
* Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
*
*/

#include <vector>

#include "caffe/layers/conv_layer.hpp"
#include "caffe/util/im2col.hpp"
#include "caffe/opt/layers/opt_conv_layer.hpp"
#include "caffe/opt/utils/math_funcs.hpp"

namespace caffe {

#ifdef USE_CUDNN
__global__ void sync_opt_conv_groups() {}
#endif

template <typename Dtype>
void OptConvolutionLayer<Dtype>::Forward_gpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top) {
  int index = 0;
  if (this->bias_term_) {
    index += 1;
  }
  
  vector<shared_ptr<Blob<Dtype> > > weights;
  if (this->blobs_.size() != index+7)
  {
    printf("invalid blobs_ size!\n");
    return;
  }
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
    this->Opt_gpu(weights, datas, is_train, OPT_CONV);
  }

  
  this->opt_input_or_weight_ = OPT_INPUT;
  this->Opt_gpu(weights, datas, is_train, OPT_CONV);  
  
  
  const Dtype* weight = this->blobs_[index+1]->gpu_data();  //quantized weight
#ifdef USE_CUDNN
  for (int i = 0; i < bottom.size(); ++i) {
    const Dtype* bottom_data = this->inf_bottom_->gpu_data();
    Dtype* top_data = top[i]->mutable_gpu_data();   
    // Forward through cuDNN in parallel over groups.
    for (int g = 0; g < this->group_; g++) {
      // Filters.
      CUDNN_CHECK(cudnnConvolutionForward(handle_[g],
            cudnn::dataType<Dtype>::one,
            bottom_descs_[i], bottom_data + bottom_offset_ * g,
            filter_desc_, weight + this->weight_offset_ * g,
            conv_descs_[i],
            fwd_algo_[i], workspace[g], workspace_fwd_sizes_[i],
            cudnn::dataType<Dtype>::zero,
            top_descs_[i], top_data + top_offset_ * g));

      // Bias.
      if (this->bias_term_) {
        const Dtype* bias_data = this->blobs_[1]->gpu_data();
        CUDNN_CHECK(cudnnAddTensor(handle_[g],
              cudnn::dataType<Dtype>::one,
              bias_desc_, bias_data + bias_offset_ * g,
              cudnn::dataType<Dtype>::one,
              top_descs_[i], top_data + top_offset_ * g));
      }
    }

    // Synchronize the work across groups, each of which went into its own
    // stream, by launching an empty kernel into the default (null) stream.
    // NOLINT_NEXT_LINE(whitespace/operators)
    sync_opt_conv_groups<<<1, 1>>>();
  }
#else
  for (int i = 0; i < bottom.size(); ++i) {
    const Dtype* bottom_data = this->inf_bottom_->gpu_data();
    Dtype* top_data = top[i]->mutable_gpu_data();
    for (int n = 0; n < this->num_; ++n) {
      this->forward_gpu_gemm(bottom_data + n * this->bottom_dim_, weight,
          top_data + n * this->top_dim_);
      if (this->bias_term_) {
        const Dtype* bias = this->blobs_[1]->gpu_data();
        this->forward_gpu_bias(top_data + n * this->top_dim_, bias);
      }
    }
  }
#endif
}

template <typename Dtype>
void OptConvolutionLayer<Dtype>::Backward_gpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom) {

  int index = 0;
  if (this->bias_term_) 
    index += 1;

#ifdef USE_CUDNN
  const Dtype* weight = NULL;
  Dtype* weight_diff = NULL;
  if (this->param_propagate_down_[0]) {
    // weight = this->blobs_[0]->gpu_data(); //full weight
    weight = this->blobs_[index+1]->gpu_data(); //quantized weight
    weight_diff = this->blobs_[0]->mutable_gpu_diff();
  }
  Dtype* bias_diff = NULL;
  if (this->bias_term_ && this->param_propagate_down_[1]) {
    bias_diff = this->blobs_[1]->mutable_gpu_diff();
  }
  for (int i = 0; i < top.size(); ++i) {
    const Dtype* top_diff = top[i]->gpu_diff();
    // Backward through cuDNN in parallel over groups and gradients.
    for (int g = 0; g < this->group_; g++) {
      // Gradient w.r.t. bias.
      if (this->bias_term_ && this->param_propagate_down_[1]) {
        CUDNN_CHECK(cudnnConvolutionBackwardBias(handle_[0*this->group_ + g],
              cudnn::dataType<Dtype>::one,
              top_descs_[i],  top_diff + top_offset_ * g,
              cudnn::dataType<Dtype>::one,
              bias_desc_, bias_diff + bias_offset_ * g));
      }

      // Gradient w.r.t. weights.
      if (this->param_propagate_down_[0]) {
        const Dtype* bottom_data = bottom[i]->gpu_data();
        CUDNN_CHECK(cudnnConvolutionBackwardFilter(
              handle_[1*this->group_ + g],
              cudnn::dataType<Dtype>::one,
              bottom_descs_[i], bottom_data + bottom_offset_ * g,
              top_descs_[i],    top_diff + top_offset_ * g,
              conv_descs_[i],
              bwd_filter_algo_[i], workspace[1*this->group_ + g],
              workspace_bwd_filter_sizes_[i],
              cudnn::dataType<Dtype>::one,
              filter_desc_, weight_diff + this->weight_offset_ * g));
      }

      // Gradient w.r.t. bottom data.
      if (propagate_down[i]) {
        if (weight == NULL) {
          // weight = this->blobs_[0]->gpu_data();  //full weight
          weight = this->blobs_[index+1]->gpu_data(); //quantized weight
        }
        Dtype* bottom_diff = bottom[i]->mutable_gpu_diff();
        CUDNN_CHECK(cudnnConvolutionBackwardData(
              handle_[2*this->group_ + g],
              cudnn::dataType<Dtype>::one,
              filter_desc_, weight + this->weight_offset_ * g,
              top_descs_[i], top_diff + top_offset_ * g,
              conv_descs_[i],
              bwd_data_algo_[i], workspace[2*this->group_ + g],
              workspace_bwd_data_sizes_[i],
              cudnn::dataType<Dtype>::zero,
              bottom_descs_[i], bottom_diff + bottom_offset_ * g));
      }
    }

    // Synchronize the work across groups, each of which went into its own
    // stream, by launching an empty kernel into the default (null) stream.
    // NOLINT_NEXT_LINE(whitespace/operators)
    sync_opt_conv_groups<<<1, 1>>>();
  }
#else
  const Dtype* weight = this->blobs_[index+1]->gpu_data(); //quantized weight

  Dtype* weight_diff = this->blobs_[0]->mutable_gpu_diff();

  for (int i = 0; i < top.size(); ++i) {
    const Dtype* top_diff = top[i]->gpu_diff();
    // Bias gradient, if necessary.
    if (this->bias_term_ && this->param_propagate_down_[1]) {
      Dtype* bias_diff = this->blobs_[1]->mutable_gpu_diff();
      for (int n = 0; n < this->num_; ++n) {
        this->backward_gpu_bias(bias_diff, top_diff + n * this->top_dim_);
      }
    }
    if (this->param_propagate_down_[0] || propagate_down[i]) {
      const Dtype* bottom_data = bottom[i]->gpu_data();
      Dtype* bottom_diff = bottom[i]->mutable_gpu_diff();
      for (int n = 0; n < this->num_; ++n) {
        // gradient w.r.t. weight. Note that we will accumulate diffs.
        if (this->param_propagate_down_[0]) {
          this->weight_gpu_gemm(bottom_data + n * this->bottom_dim_,
              top_diff + n * this->top_dim_, weight_diff);
        }
        // gradient w.r.t. bottom data, if necessary.
        if (propagate_down[i]) {
          this->backward_gpu_gemm(top_diff + n * this->top_dim_, weight,
              bottom_diff + n * this->bottom_dim_);
        }
      }
    }
  }
#endif
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

INSTANTIATE_LAYER_GPU_FUNCS(OptConvolutionLayer);

}  // namespace caffe
