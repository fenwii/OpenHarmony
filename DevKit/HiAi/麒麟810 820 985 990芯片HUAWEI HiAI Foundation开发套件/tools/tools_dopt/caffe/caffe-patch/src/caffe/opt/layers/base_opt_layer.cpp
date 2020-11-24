/*
*
* Copyright (C) 2019. Huawei Technologies Co., Ltd. All rights reserved.
*
*/

#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

#include "caffe/opt/layers/base_opt_layer.hpp"
#include "caffe/opt/utils/math_funcs.hpp"
#include "caffe/opt/layers/opt_conv_layer.hpp"

namespace caffe {
template <typename Dtype>
BaseOptLayer<Dtype>::BaseOptLayer() {

}

template <typename Dtype>
void BaseOptLayer<Dtype>::Opt_cpu(vector<shared_ptr<Blob<Dtype> > > weights, vector<Blob<Dtype>* > datas, 
                                  int is_train, int layer_type)
{
    /**/
}

template BaseOptLayer<double>::BaseOptLayer();
template BaseOptLayer<float>::BaseOptLayer();

template void BaseOptLayer<double>::Opt_cpu(vector<shared_ptr<Blob<double> > > weights, vector<Blob<double>* > datas,
                                            int is_train, int layer_type);
template void BaseOptLayer<float>::Opt_cpu(vector<shared_ptr<Blob<float> > > weights, vector<Blob<float>* > datas, 
                                           int is_train, int layer_type);

} // end namespace caffe