/*
*
* Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
*
*/

#include "caffe/opt/layers/base_opt_layer.hpp"
#include "caffe/opt/utils/math_funcs.hpp"

namespace caffe {
template <typename Dtype>
void BaseOptLayer<Dtype>::Opt_gpu(vector<shared_ptr<Blob<Dtype> > > weights, vector<Blob<Dtype>* > datas, int is_train, int layer_type)
{
  if (weights.size() == 0) {
    printf("weight size is zero!\n");
    return;
  }
  if (datas.size() == 0) {
    printf("data size is zero!\n");
    return;
  }
  shared_ptr<Blob<Dtype> > origin_weight = weights[0];
  shared_ptr<Blob<Dtype> > opt_weight = weights[1];
  shared_ptr<Blob<Dtype> > scale_weight = weights[2];
  shared_ptr<Blob<Dtype> > offset_weight = weights[3];
  shared_ptr<Blob<Dtype> > max_input= weights[4];
  shared_ptr<Blob<Dtype> > min_input = weights[5];
  shared_ptr<Blob<Dtype> > moving_factor = weights[6];
  Blob<Dtype>* top_data = datas[0];
  Blob<Dtype>* bottom_data = datas[1];
  shared_ptr<Blob<Dtype> > inf_bottom = weights[7];
  
  Forward_blob<Dtype> opt_blob = {opt_weight->mutable_gpu_data(), opt_weight->gpu_data(), opt_weight->count()};
  Weight_blob<Dtype> weight_blob = {origin_weight->asum_data(), origin_weight->gpu_data(), origin_weight->count(), origin_weight->shape()[0]};
  Forward_blob<Dtype> top_blob = {top_data->mutable_gpu_data(), top_data->gpu_data(), top_data->count()};
  Forward_blob<Dtype> bottom_blob = {bottom_data->mutable_gpu_data(), bottom_data->gpu_data(), bottom_data->count()};
  Forward_blob<Dtype> min_blob = {min_input->mutable_gpu_data(), min_input->gpu_data(), min_input->count()};
  Forward_blob<Dtype> max_blob = {max_input->mutable_gpu_data(), max_input->gpu_data(), max_input->count()};

  Forward_blob<Dtype> moving_factor_blob= {moving_factor->mutable_gpu_data(), moving_factor->gpu_data(), moving_factor->count()};

  Forward_blob<Dtype> scale_blob = {scale_weight->mutable_gpu_data(), scale_weight->gpu_data(), scale_weight->count()};

  Forward_blob<Dtype> offset_blob = {offset_weight->mutable_gpu_data(), offset_weight->gpu_data(), offset_weight->count()};

  Forward_blob<Dtype> inf_bottom_blob = {inf_bottom->mutable_gpu_data(), inf_bottom->gpu_data(), inf_bottom->count()};

  int is_ema_global = GLOBAL;
  if (is_train == 1) {
    is_ema_global = LOCAL;    
  }
  Opt_forward_params<Dtype> opt_params = \
    {opt_blob, weight_blob, bottom_blob, top_blob, scale_blob, offset_blob, min_blob, max_blob, moving_factor_blob, inf_bottom_blob, opt_input_or_weight_, Opt_input_algo_, Opt_weight_algo_, is_ema_global, layer_type, this->beta};  
  
  opt_gpu(opt_params);
}

template void BaseOptLayer<double>::Opt_gpu(vector<shared_ptr<Blob<double> > > weights, vector<Blob<double>* > datas, int is_train, int layer_type);
template void BaseOptLayer<float>::Opt_gpu(vector<shared_ptr<Blob<float> > > weights, vector<Blob<float>* > datas, int is_train, int layer_type);

template <typename Dtype>
void BaseOptLayer<Dtype>::Opt_BP_gpu(vector<shared_ptr<Blob<Dtype> > > weights, vector<Blob<Dtype>* > datas)
{
  if (weights.size() == 0) {
    printf("weight size is zero!\n");
    return;
  }
  shared_ptr<Blob<Dtype> > origin_weight = weights[0];
  shared_ptr<Blob<Dtype> > max_input= weights[1];
  shared_ptr<Blob<Dtype> > min_input = weights[2];
  if (datas.size() == 0) {
    printf("data size is zero!\n");
    return;
  }
  Blob<Dtype>* top_data = datas[0];
  Blob<Dtype>* bottom_data = datas[1];

  BP_blob<Dtype> weight_blob = {origin_weight->mutable_gpu_diff(), origin_weight->gpu_diff(),origin_weight->gpu_data(), origin_weight->count()};

  BP_blob<Dtype> top_blob = {top_data->mutable_gpu_diff(), top_data->gpu_diff(),top_data->gpu_data(), top_data->count()};

  BP_blob<Dtype> bottom_blob = {bottom_data->mutable_gpu_diff(), bottom_data->gpu_diff(),bottom_data->gpu_data(), bottom_data->count()};

  BP_blob<Dtype> max_blob= {max_input->mutable_gpu_diff(), max_input->gpu_diff(),max_input->gpu_data(), max_input->count()};

  BP_blob<Dtype> min_blob = {min_input->mutable_gpu_diff(), min_input->gpu_diff(),min_input->gpu_data(), min_input->count()};

  Opt_BP_params<Dtype> opt_BP_params = {weight_blob, top_blob, bottom_blob, min_blob, max_blob, opt_input_or_weight_, Opt_input_algo_, Opt_weight_algo_ };

  opt_BP_gpu(opt_BP_params);
}

template void BaseOptLayer<double>::Opt_BP_gpu(vector<shared_ptr<Blob<double> > > weights, vector<Blob<double>* > datas);
template void BaseOptLayer<float>::Opt_BP_gpu(vector<shared_ptr<Blob<float> > > weights, vector<Blob<float>* > datas);

} // end namespace caffe
