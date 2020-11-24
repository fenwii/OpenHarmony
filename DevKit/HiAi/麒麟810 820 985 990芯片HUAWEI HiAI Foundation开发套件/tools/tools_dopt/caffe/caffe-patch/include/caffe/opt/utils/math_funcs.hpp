#ifndef MATH_FUNCS_HPP_
#define MATH_FUNCS_HPP_


enum Opt_algo
{
    OPT_INT16 = 0,
    OPT_INT8,
    OPT_INT4,
    OPT_INT2,
    OPT_INT1 
};

enum Opt_type
{
    OPT_WEIGHT = 1,
    OPT_INPUT
};

enum EMA_TYPE
{
    LOCAL = 0,
    GLOBAL = 1 
};

enum LAYER_TYPE
{
    OPT_FC = 0,
    OPT_CONV = 1  
};

template<typename Dtype>
struct Weight_blob
{
    const Dtype asum_data;
    const Dtype* data;
    const int count;
    const int out_ch;
};

template<typename Dtype>
struct Forward_blob
{
    Dtype* mutable_data;
    const Dtype* data;
    const int count;
};

template<typename Dtype>
struct Opt_forward_params
{
    Forward_blob<Dtype> opt_blob;
    Weight_blob<Dtype> weight_blob;
    Forward_blob<Dtype> bottom_blob;
    Forward_blob<Dtype> top_blob;

    Forward_blob<Dtype> weight_scale_blob;
    Forward_blob<Dtype> weight_offset_blob;

    Forward_blob<Dtype> min_blob;
    Forward_blob<Dtype> max_blob;
    Forward_blob<Dtype> moving_factor_blob;

    Forward_blob<Dtype> inf_bottom_blob;

    int opt_input_or_weight;
    int Opt_input_algo;
    int Opt_weight_algo;
    int is_global;
    int layer_type;
    float beta;    
};

template<typename Dtype>
struct BP_blob
{
    Dtype* mutable_diff;
    const Dtype* diff;
    const Dtype* data;
    const int count;
};

template<typename Dtype>
struct Opt_BP_params
{
    BP_blob<Dtype> weight_blob;
    BP_blob<Dtype> top_blob;
    BP_blob<Dtype> bottom_blob;

    BP_blob<Dtype> min_blob;
    BP_blob<Dtype> max_blob;

    int opt_input_or_weight;
    int Opt_input_algo;
    int Opt_weight_algo;
};



template<typename Dtype>
void opt_cpu(Opt_forward_params<Dtype> &opt_params);

template<typename Dtype>
void opt_gpu(Opt_forward_params<Dtype> &opt_params);

template<typename Dtype>
void opt_BP_gpu(Opt_BP_params<Dtype> &opt_params);

template<typename Dtype>
void opt_BP_cpu(Opt_BP_params<Dtype> &opt_params);

#endif  // MATH_FUNCS_HPP_
