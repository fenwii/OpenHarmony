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

const float BETA_FC = 0.99;
const int BLOB_NUM_EXCLUDE_BIAS_FC = 7;
namespace caffe {
template <typename Dtype>
OptFcLayer<Dtype>::OptFcLayer(
      const LayerParameter& param) : InnerProductLayer<Dtype>(param),
      BaseOptLayer<Dtype>() {

  this->Opt_weight_algo_ = this->layer_param_.opt_param().weight_type();
  this->Opt_input_algo_ = this->layer_param_.opt_param().input_type();
  this->opt_input_or_weight_ = 1;
    this->beta = BETA_FC;
  LOG(INFO) << "Enter OptConvolution, weight precision:" << this->Opt_weight_algo_;
  LOG(INFO) << "Enter OptConvolution, input precision:" << this->Opt_input_algo_;
}

template <typename Dtype>
void OptFcLayer<Dtype>::LayerSetUp(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top) {
  const int num_output = this->layer_param_.inner_product_param().num_output();
  this->bias_term_ = this->layer_param_.inner_product_param().bias_term();
  this->transpose_ = this->layer_param_.inner_product_param().transpose();
  this->N_ = num_output;
  const int axis = bottom[0]->CanonicalAxisIndex(
      this->layer_param_.inner_product_param().axis());
  // Dimensions starting from "axis" are "flattened" into a single
  // length K_ vector. For example, if bottom[0]'s shape is (N, C, H, W),
  // and axis == 1, N inner products with dimension CHW are performed.
  this->K_ = bottom[0]->count(axis);
  // Check if we need to set up the weights
    int i_bias = 0;
  if (this->blobs_.size() > 0) {
    LOG(INFO) << "Skipping parameter initialization";
  } else {
    if (this->bias_term_) {
        i_bias += 1;
        this->blobs_.resize(i_bias+BLOB_NUM_EXCLUDE_BIAS_FC);
    } else {
        this->blobs_.resize(BLOB_NUM_EXCLUDE_BIAS_FC);
    }
    // Initialize the weights
    vector<int> weight_shape(2);
    if (this->transpose_) {
      weight_shape[0] = this->K_;
      weight_shape[1] = this->N_;
    } else {
      weight_shape[0] = this->N_;
      weight_shape[1] = this->K_;
    }
    this->blobs_[0].reset(new Blob<Dtype>(weight_shape));
    // fill the weights
    shared_ptr<Filler<Dtype> > weight_filler(GetFiller<Dtype>(
        this->layer_param_.inner_product_param().weight_filler()));
    weight_filler->Fill(this->blobs_[0].get());
    // If necessary, intiialize and fill the bias term
    if (this->bias_term_) {
      vector<int> bias_shape(1, this->N_);
      this->blobs_[1].reset(new Blob<Dtype>(bias_shape));
      shared_ptr<Filler<Dtype> > bias_filler(GetFiller<Dtype>(
          this->layer_param_.inner_product_param().bias_filler()));
      bias_filler->Fill(this->blobs_[1].get());
    }

    if (this->bias_term_) {
        // fill the para1
        // this->precision_ = this->layer_param_.opt_param().weight_type();
        vector<int> para_shape(1, 1);
        this->blobs_[2].reset(new Blob<Dtype>(weight_shape)); 
        shared_ptr<Filler<Dtype> > weight_q(GetFiller<Dtype>(
            this->layer_param_.opt_param().weight_q()));
        weight_q->Fill(this->blobs_[2].get()); 
        
        // fill the para2
          this->blobs_[3].reset(new Blob<Dtype>(para_shape)); 
          shared_ptr<Filler<Dtype> > w_scale(GetFiller<Dtype>(
              this->layer_param_.opt_param().w_scale()));
          w_scale->Fill(this->blobs_[3].get());
          this->blobs_[4].reset(new Blob<Dtype>(para_shape)); 
          shared_ptr<Filler<Dtype> > w_offset(GetFiller<Dtype>(
              this->layer_param_.opt_param().w_offset()));
          w_offset->Fill(this->blobs_[4].get());
          this->blobs_[5].reset(new Blob<Dtype>(para_shape)); 
          shared_ptr<Filler<Dtype> > i_max(GetFiller<Dtype>(
              this->layer_param_.opt_param().i_max()));
          i_max->Fill(this->blobs_[5].get());
          this->blobs_[6].reset(new Blob<Dtype>(para_shape)); 
          shared_ptr<Filler<Dtype> > i_min(GetFiller<Dtype>(
              this->layer_param_.opt_param().i_min()));
          i_min->Fill(this->blobs_[6].get());

            this->blobs_[BLOB_NUM_EXCLUDE_BIAS_FC].reset(new Blob<Dtype>(para_shape)); 
            shared_ptr<Filler<Dtype> > moving_factor(GetFiller<Dtype>(
                this->layer_param_.opt_param().moving_factor()));
            moving_factor->Fill(this->blobs_[BLOB_NUM_EXCLUDE_BIAS_FC].get());    
    }else{
        // fill the para1
        // this->precision_ = this->layer_param_.opt_param().weight_type();
        vector<int> para_shape(1, 1);
        this->blobs_[1].reset(new Blob<Dtype>(weight_shape)); 
        shared_ptr<Filler<Dtype> > weight_q(GetFiller<Dtype>(
            this->layer_param_.opt_param().weight_q()));
        weight_q->Fill(this->blobs_[1].get()); 

        // fill the para2
        this->blobs_[2].reset(new Blob<Dtype>(para_shape)); 
        shared_ptr<Filler<Dtype> > w_scale(GetFiller<Dtype>(
            this->layer_param_.opt_param().w_scale()));
        w_scale->Fill(this->blobs_[2].get());

        this->blobs_[3].reset(new Blob<Dtype>(para_shape)); 
        shared_ptr<Filler<Dtype> > w_offset(GetFiller<Dtype>(
            this->layer_param_.opt_param().w_offset()));
        w_offset->Fill(this->blobs_[3].get());

        this->blobs_[4].reset(new Blob<Dtype>(para_shape)); 
        shared_ptr<Filler<Dtype> > i_max(GetFiller<Dtype>(
            this->layer_param_.opt_param().i_max()));
        i_max->Fill(this->blobs_[4].get());     

        this->blobs_[5].reset(new Blob<Dtype>(para_shape)); 
        shared_ptr<Filler<Dtype> > i_min(GetFiller<Dtype>(
            this->layer_param_.opt_param().i_min()));
        i_min->Fill(this->blobs_[5].get());

        this->blobs_[BLOB_NUM_EXCLUDE_BIAS_FC].reset(new Blob<Dtype>(para_shape)); 
        shared_ptr<Filler<Dtype> > moving_factor(GetFiller<Dtype>(
            this->layer_param_.opt_param().moving_factor()));
        moving_factor->Fill(this->blobs_[BLOB_NUM_EXCLUDE_BIAS_FC].get());    
    }
  }  // parameter initialization
  this->param_propagate_down_.resize(this->blobs_.size(), true);
  // Initialize the weights
  vector<int> weight_shape(2);
  if (this->transpose_) {
    weight_shape[0] = this->K_;
    weight_shape[1] = this->N_;
  } else {
    weight_shape[0] = this->N_;
    weight_shape[1] = this->K_;
  }  
  LOG(INFO) << "init quant weight FC" ;
  this->opt_weight_.reset(new Blob<Dtype>(this->blobs_[0]->shape()));
    this->inf_bottom_.reset(new Blob<Dtype>(bottom[0]->shape()));

  LOG(INFO) << "this->blobs_[0]->shape():"<<this->blobs_[0]->shape_string();
  LOG(INFO) << "opt_weight_   :          "<<this->opt_weight_->shape_string();
  LOG(INFO) << "bottom[0]->shape():      "<<bottom[0]->shape_string();
    LOG(INFO) << "inf_bottom_->shape():    "<<this->inf_bottom_->shape_string();
}

template <typename Dtype>
void OptFcLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
    const vector<Blob<Dtype>*>& top) {  
  const Dtype* bottom_data = bottom[0]->cpu_data();
  Dtype* top_data = top[0]->mutable_cpu_data();

  vector<shared_ptr<Blob<Dtype> > > weights;
  weights.push_back(this->blobs_[0]);
  weights.push_back(this->opt_weight_);
  vector<Blob<Dtype>* > datas;
  datas.push_back(top[0]);
  datas.push_back(bottom[0]);
    int is_train = 0;
    if(this->phase_ == TRAIN) {
        is_train = 1;
        this->opt_input_or_weight_ = OPT_WEIGHT;
        this->Opt_cpu(weights, datas, is_train, OPT_FC);      
    }  
    if (this->Opt_weight_algo_ == OPT_INT8) {
        this->opt_input_or_weight_ = OPT_INPUT;
        this->Opt_cpu(weights, datas, is_train, OPT_FC);
    }

  const Dtype* weight = this->opt_weight_->cpu_data();

  caffe_cpu_gemm<Dtype>(CblasNoTrans, this->transpose_ ? CblasNoTrans : CblasTrans,
      this->M_, this->N_, this->K_, (Dtype)1.,
      bottom_data, weight, (Dtype)0., top_data);
  if (this->bias_term_) {
    caffe_cpu_gemm<Dtype>(CblasNoTrans, CblasNoTrans, this->M_, this->N_, 1, (Dtype)1.,
        this->bias_multiplier_.cpu_data(),
        this->blobs_[1]->cpu_data(), (Dtype)1., top_data);
  }
}

template <typename Dtype>
void OptFcLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
    const vector<bool>& propagate_down,
    const vector<Blob<Dtype>*>& bottom) {
  if (this->param_propagate_down_[0]) {
    const Dtype* top_diff = top[0]->cpu_diff();
    const Dtype* bottom_data = bottom[0]->cpu_data();
    // Gradient with respect to weight
    if (this->transpose_) {
      caffe_cpu_gemm<Dtype>(CblasTrans, CblasNoTrans,
          this->K_, this->N_, this->M_,
          (Dtype)1., bottom_data, top_diff,
          (Dtype)1., this->blobs_[0]->mutable_cpu_diff());
    } else {
      caffe_cpu_gemm<Dtype>(CblasTrans, CblasNoTrans,
          this->N_, this->K_, this->M_,
          (Dtype)1., top_diff, bottom_data,
          (Dtype)1., this->blobs_[0]->mutable_cpu_diff());
    }
  }
  if (this->bias_term_ && this->param_propagate_down_[1]) {
    const Dtype* top_diff = top[0]->cpu_diff();
    // Gradient with respect to bias
    caffe_cpu_gemv<Dtype>(CblasTrans, this->M_, this->N_, (Dtype)1., top_diff,
        this->bias_multiplier_.cpu_data(), (Dtype)1.,
        this->blobs_[1]->mutable_cpu_diff());
  }
  if (propagate_down[0]) {
    const Dtype* top_diff = top[0]->cpu_diff();
    // Gradient with respect to bottom data
    if (this->transpose_) {
      caffe_cpu_gemm<Dtype>(CblasNoTrans, CblasTrans,
          this->M_, this->K_, this->N_,
          (Dtype)1., top_diff, this->opt_weight_->cpu_data(),
          (Dtype)0., bottom[0]->mutable_cpu_diff());
    } else {
      caffe_cpu_gemm<Dtype>(CblasNoTrans, CblasNoTrans,
          this->M_, this->K_, this->N_,
          (Dtype)1., top_diff, this->opt_weight_->cpu_data(),
          (Dtype)0., bottom[0]->mutable_cpu_diff());
    }
  }
}

#ifdef CPU_ONLY
STUB_GPU(OptFcLayer);
#endif

INSTANTIATE_CLASS(OptFcLayer);
REGISTER_LAYER_CLASS(OptFc);

}  // namespace caffe
