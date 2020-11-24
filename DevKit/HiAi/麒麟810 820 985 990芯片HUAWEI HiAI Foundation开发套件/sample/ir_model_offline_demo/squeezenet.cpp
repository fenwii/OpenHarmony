#include "graph/operator_hiai_reg.h"
#include "graph/graph.h"
#include "graph/model.h"
#include "graph/op/all_ops.h"
#include "hiai_ir_build.h"
#include "graph/buffer.h"
#include <cstdlib>
#include <fstream>
#include <memory>
#include <unistd.h>

#include <algorithm>

using namespace std;
using namespace ge;


bool readFile(std::string value_path,uint32_t in_channels, uint32_t out_channels, uint32_t h, uint32_t w, vector<float>& output)
{
     uint32_t length = w*h*in_channels*out_channels;
     if(length == 0) {
         cout<<"read length is 0"<<endl;
         return false;
     }

     std::ifstream ifs(value_path, std::ios::binary | std::ios::in);
     if(!ifs.is_open()) {
         cout<<value_path<<" open failed !!!"<<endl;
         return false;
     }
     ifs.seekg(0, std::ios::end);
     uint32_t nFileLen = ifs.tellg();
     if(nFileLen != length*sizeof(float)) {
         cout<<"weight file "<<value_path<<" length is not equal with the shape length."<<endl;
         cout<<"weight file length is "<<nFileLen<<" ,but shape length is "<<length*sizeof(float)<<endl;
         return false;
     }

     float* tempArray = new (std::nothrow) float[length];
     if(tempArray == nullptr){
         cout<<"tempArray is nullptr."<<endl;
         return false;
     }

     ifs.seekg(0, std::ios::beg);
     ifs.read((char*)tempArray, sizeof(float) * length);
     if(!ifs) {
         cout << "error: only " << ifs.gcount() << " could be read"<<endl;
         delete[] tempArray;
         tempArray = nullptr;
         return false;
     }

     for(uint32_t i = 0; i < length; i++) {
         output.push_back(tempArray[i]);
     }
     delete[] tempArray;
     tempArray = nullptr;
     return true;
}

bool readWeight(string layername,int in_channels, int out_channels, int h, int w, vector<float>& weights)
{
    string tmpname = layername;
    replace(tmpname.begin(),tmpname.end(),'/','@');
    std::string value_path = "./squeezenet_weight/"+tmpname + "_weight.dat";
    return readFile(value_path,in_channels,out_channels,h,w,weights);
}

bool readBias(string layername,int in_channels, int out_channels, int h, int w, vector<float>& bias)
{
    string tmpname = layername;
    replace(tmpname.begin(),tmpname.end(),'/','@');
    std::string value_path = "./squeezenet_weight/"+tmpname + "_bias.dat";
    return readFile(value_path,in_channels,out_channels,h,w,bias);
}

bool getConvRealWeight(string layername,ge::AttrValue::LIST_TENSOR &weight, int in_channels, int out_channels, int h, int w){

    TensorDesc fdesc(Shape({in_channels, out_channels, h, w}), FORMAT_NCHW,  DT_FLOAT);
    TensorPtr filter = std::shared_ptr<ge::Tensor>(new(std::nothrow) ge::Tensor());
    if (filter == nullptr) {
        return false;
    }
    filter->SetTensorDesc(fdesc);
    vector<float> dataValuec;
    if(readWeight(layername,in_channels,out_channels,h,w,dataValuec)) {
        filter->SetData((uint8_t *)dataValuec.data(), w*h*in_channels*out_channels * sizeof(float));
        weight.push_back(filter);
        return true;
    }
    return false;
}

bool getConvRealBias(string layername,ge::AttrValue::LIST_TENSOR &weight, int in_channels, int out_channels, int h, int w){

    TensorDesc fdesc(Shape({in_channels, out_channels, h, w}), FORMAT_NCHW,  DT_FLOAT);
    TensorPtr filter = std::shared_ptr<ge::Tensor>(new(std::nothrow) ge::Tensor());
    if (filter == nullptr) {
        return false;
    }
    filter->SetTensorDesc(fdesc);
    vector<float> dataValuec;
    if(readBias(layername,in_channels,out_channels,h,w,dataValuec)) {
        filter->SetData((uint8_t *)dataValuec.data(), w*h*in_channels*out_channels * sizeof(float));
        weight.push_back(filter);
        return true;
    }
    return false;
}

void getConvdata(hiai::op::Data &data ,string op_name, int in_channels, int out_channels, int h, int w, ge::Format format , ge::DataType datatype){

    TensorDesc desc(Shape({in_channels, out_channels, h, w}), format,  datatype);
    string data_name = op_name;
    data = hiai::op::Data(data_name);
    data.update_input_desc_x(desc);
}

bool buildSqueezenetGraph(Graph& graph)
{
    hiai::op::Data data;
    getConvdata(data,"data",1,3,227,227,(ge::Format)0,(ge::DataType)0);

    ge::AttrValue::LIST_TENSOR weightList0;
    if(!getConvRealBias("conv10",weightList0, 1,1000,1,1)){
        return false;
    }
    hiai::op::Const conv10_const_1= hiai::op::Const("conv10_const_1").set_attr_value(weightList0[0]);

    ge::AttrValue::LIST_TENSOR weightList1;
    if(!getConvRealWeight("conv10",weightList1, 1000,512,1,1)){
        return false;
    }
    hiai::op::Const conv10_const_0= hiai::op::Const("conv10_const_0").set_attr_value(weightList1[0]);

    ge::AttrValue::LIST_TENSOR weightList2;
    if(!getConvRealBias("fire9/expand3x3",weightList2, 1,256,1,1)){
        return false;
    }
    hiai::op::Const fire9_expand3x3_const_1= hiai::op::Const("fire9/expand3x3_const_1").set_attr_value(weightList2[0]);

    ge::AttrValue::LIST_TENSOR weightList3;
    if(!getConvRealWeight("fire9/expand3x3",weightList3, 256,64,3,3)){
        return false;
    }
    hiai::op::Const fire9_expand3x3_const_0= hiai::op::Const("fire9/expand3x3_const_0").set_attr_value(weightList3[0]);

    ge::AttrValue::LIST_TENSOR weightList4;
    if(!getConvRealBias("fire9/expand1x1",weightList4, 1,256,1,1)){
        return false;
    }
    hiai::op::Const fire9_expand1x1_const_1= hiai::op::Const("fire9/expand1x1_const_1").set_attr_value(weightList4[0]);

    ge::AttrValue::LIST_TENSOR weightList5;
    if(!getConvRealWeight("fire9/expand1x1",weightList5, 256,64,1,1)){
        return false;
    }
    hiai::op::Const fire9_expand1x1_const_0= hiai::op::Const("fire9/expand1x1_const_0").set_attr_value(weightList5[0]);

    ge::AttrValue::LIST_TENSOR weightList6;
    if(!getConvRealBias("fire9/squeeze1x1",weightList6, 1,64,1,1)){
        return false;
    }
    hiai::op::Const fire9_squeeze1x1_const_1= hiai::op::Const("fire9/squeeze1x1_const_1").set_attr_value(weightList6[0]);

    ge::AttrValue::LIST_TENSOR weightList7;
    if(!getConvRealWeight("fire9/squeeze1x1",weightList7, 64,512,1,1)){
        return false;
    }
    hiai::op::Const fire9_squeeze1x1_const_0= hiai::op::Const("fire9/squeeze1x1_const_0").set_attr_value(weightList7[0]);

    ge::AttrValue::LIST_TENSOR weightList8;
    if(!getConvRealBias("fire8/expand3x3",weightList8, 1,256,1,1)){
        return false;
    }
    hiai::op::Const fire8_expand3x3_const_1= hiai::op::Const("fire8/expand3x3_const_1").set_attr_value(weightList8[0]);

    ge::AttrValue::LIST_TENSOR weightList9;
    if(!getConvRealWeight("fire8/expand3x3",weightList9, 256,64,3,3)){
        return false;
    }
    hiai::op::Const fire8_expand3x3_const_0= hiai::op::Const("fire8/expand3x3_const_0").set_attr_value(weightList9[0]);

    ge::AttrValue::LIST_TENSOR weightList10;
    if(!getConvRealBias("fire8/expand1x1",weightList10, 1,256,1,1)){
        return false;
    }
    hiai::op::Const fire8_expand1x1_const_1= hiai::op::Const("fire8/expand1x1_const_1").set_attr_value(weightList10[0]);

    ge::AttrValue::LIST_TENSOR weightList11;
    if(!getConvRealWeight("fire8/expand1x1",weightList11, 256,64,1,1)){
        return false;
    }
    hiai::op::Const fire8_expand1x1_const_0= hiai::op::Const("fire8/expand1x1_const_0").set_attr_value(weightList11[0]);

    ge::AttrValue::LIST_TENSOR weightList12;
    if(!getConvRealBias("fire8/squeeze1x1",weightList12, 1,64,1,1)){
        return false;
    }
    hiai::op::Const fire8_squeeze1x1_const_1= hiai::op::Const("fire8/squeeze1x1_const_1").set_attr_value(weightList12[0]);

    ge::AttrValue::LIST_TENSOR weightList13;
    if(!getConvRealWeight("fire8/squeeze1x1",weightList13, 64,384,1,1)){
        return false;
    }
    hiai::op::Const fire8_squeeze1x1_const_0= hiai::op::Const("fire8/squeeze1x1_const_0").set_attr_value(weightList13[0]);

    ge::AttrValue::LIST_TENSOR weightList14;
    if(!getConvRealBias("fire7/expand3x3",weightList14, 1,192,1,1)){
        return false;
    }
    hiai::op::Const fire7_expand3x3_const_1= hiai::op::Const("fire7/expand3x3_const_1").set_attr_value(weightList14[0]);

    ge::AttrValue::LIST_TENSOR weightList15;
    if(!getConvRealWeight("fire7/expand3x3",weightList15, 192,48,3,3)){
        return false;
    }
    hiai::op::Const fire7_expand3x3_const_0= hiai::op::Const("fire7/expand3x3_const_0").set_attr_value(weightList15[0]);

    ge::AttrValue::LIST_TENSOR weightList16;
    if(!getConvRealBias("fire7/expand1x1",weightList16, 1,192,1,1)){
        return false;
    }
    hiai::op::Const fire7_expand1x1_const_1= hiai::op::Const("fire7/expand1x1_const_1").set_attr_value(weightList16[0]);

    ge::AttrValue::LIST_TENSOR weightList17;
    if(!getConvRealWeight("fire7/expand1x1",weightList17, 192,48,1,1)){
        return false;
    }
    hiai::op::Const fire7_expand1x1_const_0= hiai::op::Const("fire7/expand1x1_const_0").set_attr_value(weightList17[0]);

    ge::AttrValue::LIST_TENSOR weightList18;
    if(!getConvRealBias("fire7/squeeze1x1",weightList18, 1,48,1,1)){
        return false;
    }
    hiai::op::Const fire7_squeeze1x1_const_1= hiai::op::Const("fire7/squeeze1x1_const_1").set_attr_value(weightList18[0]);

    ge::AttrValue::LIST_TENSOR weightList19;
    if(!getConvRealWeight("fire7/squeeze1x1",weightList19, 48,384,1,1)){
        return false;
    }
    hiai::op::Const fire7_squeeze1x1_const_0= hiai::op::Const("fire7/squeeze1x1_const_0").set_attr_value(weightList19[0]);

    ge::AttrValue::LIST_TENSOR weightList20;
    if(!getConvRealBias("fire6/expand3x3",weightList20, 1,192,1,1)){
        return false;
    }
    hiai::op::Const fire6_expand3x3_const_1= hiai::op::Const("fire6/expand3x3_const_1").set_attr_value(weightList20[0]);

    ge::AttrValue::LIST_TENSOR weightList21;
    if(!getConvRealWeight("fire6/expand3x3",weightList21, 192,48,3,3)){
        return false;
    }
    hiai::op::Const fire6_expand3x3_const_0= hiai::op::Const("fire6/expand3x3_const_0").set_attr_value(weightList21[0]);

    ge::AttrValue::LIST_TENSOR weightList22;
    if(!getConvRealBias("fire6/expand1x1",weightList22, 1,192,1,1)){
        return false;
    }
    hiai::op::Const fire6_expand1x1_const_1= hiai::op::Const("fire6/expand1x1_const_1").set_attr_value(weightList22[0]);

    ge::AttrValue::LIST_TENSOR weightList23;
    if(!getConvRealWeight("fire6/expand1x1",weightList23, 192,48,1,1)){
        return false;
    }
    hiai::op::Const fire6_expand1x1_const_0= hiai::op::Const("fire6/expand1x1_const_0").set_attr_value(weightList23[0]);

    ge::AttrValue::LIST_TENSOR weightList24;
    if(!getConvRealBias("fire6/squeeze1x1",weightList24, 1,48,1,1)){
        return false;
    }
    hiai::op::Const fire6_squeeze1x1_const_1= hiai::op::Const("fire6/squeeze1x1_const_1").set_attr_value(weightList24[0]);

    ge::AttrValue::LIST_TENSOR weightList25;
    if(!getConvRealWeight("fire6/squeeze1x1",weightList25, 48,256,1,1)){
        return false;
    }
    hiai::op::Const fire6_squeeze1x1_const_0= hiai::op::Const("fire6/squeeze1x1_const_0").set_attr_value(weightList25[0]);

    ge::AttrValue::LIST_TENSOR weightList26;
    if(!getConvRealBias("fire5/expand3x3",weightList26, 1,128,1,1)){
        return false;
    }
    hiai::op::Const fire5_expand3x3_const_1= hiai::op::Const("fire5/expand3x3_const_1").set_attr_value(weightList26[0]);

    ge::AttrValue::LIST_TENSOR weightList27;
    if(!getConvRealWeight("fire5/expand3x3",weightList27, 128,32,3,3)){
        return false;
    }
    hiai::op::Const fire5_expand3x3_const_0= hiai::op::Const("fire5/expand3x3_const_0").set_attr_value(weightList27[0]);

    ge::AttrValue::LIST_TENSOR weightList28;
    if(!getConvRealBias("fire5/expand1x1",weightList28, 1,128,1,1)){
        return false;
    }
    hiai::op::Const fire5_expand1x1_const_1= hiai::op::Const("fire5/expand1x1_const_1").set_attr_value(weightList28[0]);

    ge::AttrValue::LIST_TENSOR weightList29;
    if(!getConvRealWeight("fire5/expand1x1",weightList29, 128,32,1,1)){
        return false;
    }
    hiai::op::Const fire5_expand1x1_const_0= hiai::op::Const("fire5/expand1x1_const_0").set_attr_value(weightList29[0]);

    ge::AttrValue::LIST_TENSOR weightList30;
    if(!getConvRealBias("fire5/squeeze1x1",weightList30, 1,32,1,1)){
        return false;
    }
    hiai::op::Const fire5_squeeze1x1_const_1= hiai::op::Const("fire5/squeeze1x1_const_1").set_attr_value(weightList30[0]);

    ge::AttrValue::LIST_TENSOR weightList31;
    if(!getConvRealWeight("fire5/squeeze1x1",weightList31, 32,256,1,1)){
        return false;
    }
    hiai::op::Const fire5_squeeze1x1_const_0= hiai::op::Const("fire5/squeeze1x1_const_0").set_attr_value(weightList31[0]);

    ge::AttrValue::LIST_TENSOR weightList32;
    if(!getConvRealBias("fire4/expand3x3",weightList32, 1,128,1,1)){
        return false;
    }
    hiai::op::Const fire4_expand3x3_const_1= hiai::op::Const("fire4/expand3x3_const_1").set_attr_value(weightList32[0]);

    ge::AttrValue::LIST_TENSOR weightList33;
    if(!getConvRealWeight("fire4/expand3x3",weightList33, 128,32,3,3)){
        return false;
    }
    hiai::op::Const fire4_expand3x3_const_0= hiai::op::Const("fire4/expand3x3_const_0").set_attr_value(weightList33[0]);

    ge::AttrValue::LIST_TENSOR weightList34;
    if(!getConvRealBias("fire4/expand1x1",weightList34, 1,128,1,1)){
        return false;
    }
    hiai::op::Const fire4_expand1x1_const_1= hiai::op::Const("fire4/expand1x1_const_1").set_attr_value(weightList34[0]);

    ge::AttrValue::LIST_TENSOR weightList35;
    if(!getConvRealWeight("fire4/expand1x1",weightList35, 128,32,1,1)){
        return false;
    }
    hiai::op::Const fire4_expand1x1_const_0= hiai::op::Const("fire4/expand1x1_const_0").set_attr_value(weightList35[0]);

    ge::AttrValue::LIST_TENSOR weightList36;
    if(!getConvRealBias("fire4/squeeze1x1",weightList36, 1,32,1,1)){
        return false;
    }
    hiai::op::Const fire4_squeeze1x1_const_1= hiai::op::Const("fire4/squeeze1x1_const_1").set_attr_value(weightList36[0]);

    ge::AttrValue::LIST_TENSOR weightList37;
    if(!getConvRealWeight("fire4/squeeze1x1",weightList37, 32,128,1,1)){
        return false;
    }
    hiai::op::Const fire4_squeeze1x1_const_0= hiai::op::Const("fire4/squeeze1x1_const_0").set_attr_value(weightList37[0]);

    ge::AttrValue::LIST_TENSOR weightList38;
    if(!getConvRealBias("fire3/expand3x3",weightList38, 1,64,1,1)){
        return false;
    }
    hiai::op::Const fire3_expand3x3_const_1= hiai::op::Const("fire3/expand3x3_const_1").set_attr_value(weightList38[0]);

    ge::AttrValue::LIST_TENSOR weightList39;
    if(!getConvRealWeight("fire3/expand3x3",weightList39, 64,16,3,3)){
        return false;
    }
    hiai::op::Const fire3_expand3x3_const_0= hiai::op::Const("fire3/expand3x3_const_0").set_attr_value(weightList39[0]);

    ge::AttrValue::LIST_TENSOR weightList40;
    if(!getConvRealBias("fire3/expand1x1",weightList40, 1,64,1,1)){
        return false;
    }
    hiai::op::Const fire3_expand1x1_const_1= hiai::op::Const("fire3/expand1x1_const_1").set_attr_value(weightList40[0]);

    ge::AttrValue::LIST_TENSOR weightList41;
    if(!getConvRealWeight("fire3/expand1x1",weightList41, 64,16,1,1)){
        return false;
    }
    hiai::op::Const fire3_expand1x1_const_0= hiai::op::Const("fire3/expand1x1_const_0").set_attr_value(weightList41[0]);

    ge::AttrValue::LIST_TENSOR weightList42;
    if(!getConvRealBias("fire3/squeeze1x1",weightList42, 1,16,1,1)){
        return false;
    }
    hiai::op::Const fire3_squeeze1x1_const_1= hiai::op::Const("fire3/squeeze1x1_const_1").set_attr_value(weightList42[0]);

    ge::AttrValue::LIST_TENSOR weightList43;
    if(!getConvRealWeight("fire3/squeeze1x1",weightList43, 16,128,1,1)){
        return false;
    }
    hiai::op::Const fire3_squeeze1x1_const_0= hiai::op::Const("fire3/squeeze1x1_const_0").set_attr_value(weightList43[0]);

    ge::AttrValue::LIST_TENSOR weightList44;
    if(!getConvRealBias("fire2/expand3x3",weightList44, 1,64,1,1)){
        return false;
    }
    hiai::op::Const fire2_expand3x3_const_1= hiai::op::Const("fire2/expand3x3_const_1").set_attr_value(weightList44[0]);

    ge::AttrValue::LIST_TENSOR weightList45;
    if(!getConvRealWeight("fire2/expand3x3",weightList45, 64,16,3,3)){
        return false;
    }
    hiai::op::Const fire2_expand3x3_const_0= hiai::op::Const("fire2/expand3x3_const_0").set_attr_value(weightList45[0]);

    ge::AttrValue::LIST_TENSOR weightList46;
    if(!getConvRealBias("fire2/expand1x1",weightList46, 1,64,1,1)){
        return false;
    }
    hiai::op::Const fire2_expand1x1_const_1= hiai::op::Const("fire2/expand1x1_const_1").set_attr_value(weightList46[0]);

    ge::AttrValue::LIST_TENSOR weightList47;
    if(!getConvRealWeight("fire2/expand1x1",weightList47, 64,16,1,1)){
        return false;
    }
    hiai::op::Const fire2_expand1x1_const_0= hiai::op::Const("fire2/expand1x1_const_0").set_attr_value(weightList47[0]);

    ge::AttrValue::LIST_TENSOR weightList48;
    if(!getConvRealBias("fire2/squeeze1x1",weightList48, 1,16,1,1)){
        return false;
    }
    hiai::op::Const fire2_squeeze1x1_const_1= hiai::op::Const("fire2/squeeze1x1_const_1").set_attr_value(weightList48[0]);

    ge::AttrValue::LIST_TENSOR weightList49;
    if(!getConvRealWeight("fire2/squeeze1x1",weightList49, 16,64,1,1)){
        return false;
    }
    hiai::op::Const fire2_squeeze1x1_const_0= hiai::op::Const("fire2/squeeze1x1_const_0").set_attr_value(weightList49[0]);

    ge::AttrValue::LIST_TENSOR weightList50;
    if(!getConvRealBias("conv1",weightList50, 1,64,1,1)){
        return false;
    }
    hiai::op::Const conv1_const_1= hiai::op::Const("conv1_const_1").set_attr_value(weightList50[0]);

    ge::AttrValue::LIST_TENSOR weightList51;
    if(!getConvRealWeight("conv1",weightList51, 64,3,3,3)){
        return false;
    }
    hiai::op::Const conv1_const_0= hiai::op::Const("conv1_const_0").set_attr_value(weightList51[0]);

    auto conv1 = hiai::op::Convolution("conv1").set_input_x(data).set_input_filter(conv1_const_0).set_input_bias(conv1_const_1).set_attr_strides(AttrValue::LIST_INT({ 2, 2})).set_attr_dilations(AttrValue::LIST_INT({ 1, 1})).set_attr_groups(1).set_attr_pads(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_pad_mode("SPECIFIC");
    auto relu_conv1 = hiai::op::Activation("relu_conv1").set_input_x(conv1).set_attr_coef(0.000000).set_attr_mode(1);
    auto pool1 = hiai::op::PoolingD("pool1").set_input_x(relu_conv1).set_attr_data_mode(0).set_attr_pad_mode(4).set_attr_ceil_mode(1).set_attr_mode(0).set_attr_pad(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_window(AttrValue::LIST_INT({ 3, 3})).set_attr_stride(AttrValue::LIST_INT({ 2, 2})).set_attr_global_pooling(0);
    auto fire2_squeeze1x1 = hiai::op::Convolution("fire2/squeeze1x1").set_input_x(pool1).set_input_filter(fire2_squeeze1x1_const_0).set_input_bias(fire2_squeeze1x1_const_1).set_attr_pad_mode("SPECIFIC").set_attr_groups(1).set_attr_pads(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_dilations(AttrValue::LIST_INT({ 1, 1})).set_attr_strides(AttrValue::LIST_INT({ 1, 1}));
    auto fire2_relu_squeeze1x1 = hiai::op::Activation("fire2/relu_squeeze1x1").set_input_x(fire2_squeeze1x1).set_attr_coef(0.000000).set_attr_mode(1);
    auto fire2_expand3x3 = hiai::op::Convolution("fire2/expand3x3").set_input_x(fire2_relu_squeeze1x1).set_input_filter(fire2_expand3x3_const_0).set_input_bias(fire2_expand3x3_const_1).set_attr_groups(1).set_attr_dilations(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC").set_attr_pads(AttrValue::LIST_INT({ 1, 1, 1, 1})).set_attr_strides(AttrValue::LIST_INT({ 1, 1}));
    auto fire2_relu_expand3x3 = hiai::op::Activation("fire2/relu_expand3x3").set_input_x(fire2_expand3x3).set_attr_coef(0.000000).set_attr_mode(1);
    auto fire2_expand1x1 = hiai::op::Convolution("fire2/expand1x1").set_input_x(fire2_relu_squeeze1x1).set_input_filter(fire2_expand1x1_const_0).set_input_bias(fire2_expand1x1_const_1).set_attr_pad_mode("SPECIFIC").set_attr_groups(1).set_attr_pads(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_dilations(AttrValue::LIST_INT({ 1, 1})).set_attr_strides(AttrValue::LIST_INT({ 1, 1}));
    auto fire2_relu_expand1x1 = hiai::op::Activation("fire2/relu_expand1x1").set_input_x(fire2_expand1x1).set_attr_mode(1).set_attr_coef(0.000000);
    auto fire2_concat = hiai::op::ConcatD("fire2/concat").create_dynamic_input_x(2).set_dynamic_input_x(1,fire2_relu_expand1x1).set_dynamic_input_x(2,fire2_relu_expand3x3).set_attr_concat_dim(1);
    auto fire3_squeeze1x1 = hiai::op::Convolution("fire3/squeeze1x1").set_input_x(fire2_concat).set_input_filter(fire3_squeeze1x1_const_0).set_input_bias(fire3_squeeze1x1_const_1).set_attr_pads(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_groups(1).set_attr_strides(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC").set_attr_dilations(AttrValue::LIST_INT({ 1, 1}));
    auto fire3_relu_squeeze1x1 = hiai::op::Activation("fire3/relu_squeeze1x1").set_input_x(fire3_squeeze1x1).set_attr_coef(0.000000).set_attr_mode(1);
    auto fire3_expand3x3 = hiai::op::Convolution("fire3/expand3x3").set_input_x(fire3_relu_squeeze1x1).set_input_filter(fire3_expand3x3_const_0).set_input_bias(fire3_expand3x3_const_1).set_attr_strides(AttrValue::LIST_INT({ 1, 1})).set_attr_dilations(AttrValue::LIST_INT({ 1, 1})).set_attr_groups(1).set_attr_pads(AttrValue::LIST_INT({ 1, 1, 1, 1})).set_attr_pad_mode("SPECIFIC");
    auto fire3_relu_expand3x3 = hiai::op::Activation("fire3/relu_expand3x3").set_input_x(fire3_expand3x3).set_attr_coef(0.000000).set_attr_mode(1);
    auto fire3_expand1x1 = hiai::op::Convolution("fire3/expand1x1").set_input_x(fire3_relu_squeeze1x1).set_input_filter(fire3_expand1x1_const_0).set_input_bias(fire3_expand1x1_const_1).set_attr_groups(1).set_attr_dilations(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC").set_attr_pads(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_strides(AttrValue::LIST_INT({ 1, 1}));
    auto fire3_relu_expand1x1 = hiai::op::Activation("fire3/relu_expand1x1").set_input_x(fire3_expand1x1).set_attr_mode(1).set_attr_coef(0.000000);
    auto fire3_concat = hiai::op::ConcatD("fire3/concat").create_dynamic_input_x(2).set_dynamic_input_x(1,fire3_relu_expand1x1).set_dynamic_input_x(2,fire3_relu_expand3x3).set_attr_concat_dim(1);
    auto pool3 = hiai::op::PoolingD("pool3").set_input_x(fire3_concat).set_attr_data_mode(0).set_attr_pad_mode(4).set_attr_ceil_mode(1).set_attr_mode(0).set_attr_window(AttrValue::LIST_INT({ 3, 3})).set_attr_pad(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_stride(AttrValue::LIST_INT({ 2, 2})).set_attr_global_pooling(0);
    auto fire4_squeeze1x1 = hiai::op::Convolution("fire4/squeeze1x1").set_input_x(pool3).set_input_filter(fire4_squeeze1x1_const_0).set_input_bias(fire4_squeeze1x1_const_1).set_attr_pads(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_groups(1).set_attr_strides(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC").set_attr_dilations(AttrValue::LIST_INT({ 1, 1}));
    auto fire4_relu_squeeze1x1 = hiai::op::Activation("fire4/relu_squeeze1x1").set_input_x(fire4_squeeze1x1).set_attr_coef(0.000000).set_attr_mode(1);
    auto fire4_expand3x3 = hiai::op::Convolution("fire4/expand3x3").set_input_x(fire4_relu_squeeze1x1).set_input_filter(fire4_expand3x3_const_0).set_input_bias(fire4_expand3x3_const_1).set_attr_strides(AttrValue::LIST_INT({ 1, 1})).set_attr_groups(1).set_attr_pads(AttrValue::LIST_INT({ 1, 1, 1, 1})).set_attr_dilations(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC");
    auto fire4_relu_expand3x3 = hiai::op::Activation("fire4/relu_expand3x3").set_input_x(fire4_expand3x3).set_attr_coef(0.000000).set_attr_mode(1);
    auto fire4_expand1x1 = hiai::op::Convolution("fire4/expand1x1").set_input_x(fire4_relu_squeeze1x1).set_input_filter(fire4_expand1x1_const_0).set_input_bias(fire4_expand1x1_const_1).set_attr_pads(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_groups(1).set_attr_strides(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC").set_attr_dilations(AttrValue::LIST_INT({ 1, 1}));
    auto fire4_relu_expand1x1 = hiai::op::Activation("fire4/relu_expand1x1").set_input_x(fire4_expand1x1).set_attr_mode(1).set_attr_coef(0.000000);
    auto fire4_concat = hiai::op::ConcatD("fire4/concat").create_dynamic_input_x(2).set_dynamic_input_x(1,fire4_relu_expand1x1).set_dynamic_input_x(2,fire4_relu_expand3x3).set_attr_concat_dim(1);
    auto fire5_squeeze1x1 = hiai::op::Convolution("fire5/squeeze1x1").set_input_x(fire4_concat).set_input_filter(fire5_squeeze1x1_const_0).set_input_bias(fire5_squeeze1x1_const_1).set_attr_pads(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_groups(1).set_attr_strides(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC").set_attr_dilations(AttrValue::LIST_INT({ 1, 1}));
    auto fire5_relu_squeeze1x1 = hiai::op::Activation("fire5/relu_squeeze1x1").set_input_x(fire5_squeeze1x1).set_attr_mode(1).set_attr_coef(0.000000);
    auto fire5_expand3x3 = hiai::op::Convolution("fire5/expand3x3").set_input_x(fire5_relu_squeeze1x1).set_input_filter(fire5_expand3x3_const_0).set_input_bias(fire5_expand3x3_const_1).set_attr_pads(AttrValue::LIST_INT({ 1, 1, 1, 1})).set_attr_groups(1).set_attr_strides(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC").set_attr_dilations(AttrValue::LIST_INT({ 1, 1}));
    auto fire5_relu_expand3x3 = hiai::op::Activation("fire5/relu_expand3x3").set_input_x(fire5_expand3x3).set_attr_mode(1).set_attr_coef(0.000000);
    auto fire5_expand1x1 = hiai::op::Convolution("fire5/expand1x1").set_input_x(fire5_relu_squeeze1x1).set_input_filter(fire5_expand1x1_const_0).set_input_bias(fire5_expand1x1_const_1).set_attr_pads(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_groups(1).set_attr_strides(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC").set_attr_dilations(AttrValue::LIST_INT({ 1, 1}));
    auto fire5_relu_expand1x1 = hiai::op::Activation("fire5/relu_expand1x1").set_input_x(fire5_expand1x1).set_attr_mode(1).set_attr_coef(0.000000);
    auto fire5_concat = hiai::op::ConcatD("fire5/concat").create_dynamic_input_x(2).set_dynamic_input_x(1,fire5_relu_expand1x1).set_dynamic_input_x(2,fire5_relu_expand3x3).set_attr_concat_dim(1);
    auto pool5 = hiai::op::PoolingD("pool5").set_input_x(fire5_concat).set_attr_mode(0).set_attr_data_mode(0).set_attr_pad_mode(4).set_attr_global_pooling(0).set_attr_stride(AttrValue::LIST_INT({ 2, 2})).set_attr_pad(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_window(AttrValue::LIST_INT({ 3, 3})).set_attr_ceil_mode(1);
    auto fire6_squeeze1x1 = hiai::op::Convolution("fire6/squeeze1x1").set_input_x(pool5).set_input_filter(fire6_squeeze1x1_const_0).set_input_bias(fire6_squeeze1x1_const_1).set_attr_groups(1).set_attr_dilations(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC").set_attr_pads(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_strides(AttrValue::LIST_INT({ 1, 1}));
    auto fire6_relu_squeeze1x1 = hiai::op::Activation("fire6/relu_squeeze1x1").set_input_x(fire6_squeeze1x1).set_attr_coef(0.000000).set_attr_mode(1);
    auto fire6_expand3x3 = hiai::op::Convolution("fire6/expand3x3").set_input_x(fire6_relu_squeeze1x1).set_input_filter(fire6_expand3x3_const_0).set_input_bias(fire6_expand3x3_const_1).set_attr_groups(1).set_attr_dilations(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC").set_attr_pads(AttrValue::LIST_INT({ 1, 1, 1, 1})).set_attr_strides(AttrValue::LIST_INT({ 1, 1}));
    auto fire6_relu_expand3x3 = hiai::op::Activation("fire6/relu_expand3x3").set_input_x(fire6_expand3x3).set_attr_mode(1).set_attr_coef(0.000000);
    auto fire6_expand1x1 = hiai::op::Convolution("fire6/expand1x1").set_input_x(fire6_relu_squeeze1x1).set_input_filter(fire6_expand1x1_const_0).set_input_bias(fire6_expand1x1_const_1).set_attr_groups(1).set_attr_dilations(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC").set_attr_pads(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_strides(AttrValue::LIST_INT({ 1, 1}));
    auto fire6_relu_expand1x1 = hiai::op::Activation("fire6/relu_expand1x1").set_input_x(fire6_expand1x1).set_attr_coef(0.000000).set_attr_mode(1);
    auto fire6_concat = hiai::op::ConcatD("fire6/concat").create_dynamic_input_x(2).set_dynamic_input_x(1,fire6_relu_expand1x1).set_dynamic_input_x(2,fire6_relu_expand3x3).set_attr_concat_dim(1);
    auto fire7_squeeze1x1 = hiai::op::Convolution("fire7/squeeze1x1").set_input_x(fire6_concat).set_input_filter(fire7_squeeze1x1_const_0).set_input_bias(fire7_squeeze1x1_const_1).set_attr_pads(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_groups(1).set_attr_strides(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC").set_attr_dilations(AttrValue::LIST_INT({ 1, 1}));
    auto fire7_relu_squeeze1x1 = hiai::op::Activation("fire7/relu_squeeze1x1").set_input_x(fire7_squeeze1x1).set_attr_coef(0.000000).set_attr_mode(1);
    auto fire7_expand3x3 = hiai::op::Convolution("fire7/expand3x3").set_input_x(fire7_relu_squeeze1x1).set_input_filter(fire7_expand3x3_const_0).set_input_bias(fire7_expand3x3_const_1).set_attr_pads(AttrValue::LIST_INT({ 1, 1, 1, 1})).set_attr_groups(1).set_attr_strides(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC").set_attr_dilations(AttrValue::LIST_INT({ 1, 1}));
    auto fire7_relu_expand3x3 = hiai::op::Activation("fire7/relu_expand3x3").set_input_x(fire7_expand3x3).set_attr_coef(0.000000).set_attr_mode(1);
    auto fire7_expand1x1 = hiai::op::Convolution("fire7/expand1x1").set_input_x(fire7_relu_squeeze1x1).set_input_filter(fire7_expand1x1_const_0).set_input_bias(fire7_expand1x1_const_1).set_attr_pad_mode("SPECIFIC").set_attr_groups(1).set_attr_pads(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_dilations(AttrValue::LIST_INT({ 1, 1})).set_attr_strides(AttrValue::LIST_INT({ 1, 1}));
    auto fire7_relu_expand1x1 = hiai::op::Activation("fire7/relu_expand1x1").set_input_x(fire7_expand1x1).set_attr_mode(1).set_attr_coef(0.000000);
    auto fire7_concat = hiai::op::ConcatD("fire7/concat").create_dynamic_input_x(2).set_dynamic_input_x(1,fire7_relu_expand1x1).set_dynamic_input_x(2,fire7_relu_expand3x3).set_attr_concat_dim(1);
    auto fire8_squeeze1x1 = hiai::op::Convolution("fire8/squeeze1x1").set_input_x(fire7_concat).set_input_filter(fire8_squeeze1x1_const_0).set_input_bias(fire8_squeeze1x1_const_1).set_attr_strides(AttrValue::LIST_INT({ 1, 1})).set_attr_groups(1).set_attr_pads(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_dilations(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC");
    auto fire8_relu_squeeze1x1 = hiai::op::Activation("fire8/relu_squeeze1x1").set_input_x(fire8_squeeze1x1).set_attr_coef(0.000000).set_attr_mode(1);
    auto fire8_expand3x3 = hiai::op::Convolution("fire8/expand3x3").set_input_x(fire8_relu_squeeze1x1).set_input_filter(fire8_expand3x3_const_0).set_input_bias(fire8_expand3x3_const_1).set_attr_groups(1).set_attr_dilations(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC").set_attr_pads(AttrValue::LIST_INT({ 1, 1, 1, 1})).set_attr_strides(AttrValue::LIST_INT({ 1, 1}));
    auto fire8_relu_expand3x3 = hiai::op::Activation("fire8/relu_expand3x3").set_input_x(fire8_expand3x3).set_attr_coef(0.000000).set_attr_mode(1);
    auto fire8_expand1x1 = hiai::op::Convolution("fire8/expand1x1").set_input_x(fire8_relu_squeeze1x1).set_input_filter(fire8_expand1x1_const_0).set_input_bias(fire8_expand1x1_const_1).set_attr_strides(AttrValue::LIST_INT({ 1, 1})).set_attr_groups(1).set_attr_pads(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_dilations(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC");
    auto fire8_relu_expand1x1 = hiai::op::Activation("fire8/relu_expand1x1").set_input_x(fire8_expand1x1).set_attr_mode(1).set_attr_coef(0.000000);
    auto fire8_concat = hiai::op::ConcatD("fire8/concat").create_dynamic_input_x(2).set_dynamic_input_x(1,fire8_relu_expand1x1).set_dynamic_input_x(2,fire8_relu_expand3x3).set_attr_concat_dim(1);
    auto fire9_squeeze1x1 = hiai::op::Convolution("fire9/squeeze1x1").set_input_x(fire8_concat).set_input_filter(fire9_squeeze1x1_const_0).set_input_bias(fire9_squeeze1x1_const_1).set_attr_strides(AttrValue::LIST_INT({ 1, 1})).set_attr_groups(1).set_attr_pads(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_dilations(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC");
    auto fire9_relu_squeeze1x1 = hiai::op::Activation("fire9/relu_squeeze1x1").set_input_x(fire9_squeeze1x1).set_attr_coef(0.000000).set_attr_mode(1);
    auto fire9_expand3x3 = hiai::op::Convolution("fire9/expand3x3").set_input_x(fire9_relu_squeeze1x1).set_input_filter(fire9_expand3x3_const_0).set_input_bias(fire9_expand3x3_const_1).set_attr_pads(AttrValue::LIST_INT({ 1, 1, 1, 1})).set_attr_groups(1).set_attr_strides(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC").set_attr_dilations(AttrValue::LIST_INT({ 1, 1}));
    auto fire9_relu_expand3x3 = hiai::op::Activation("fire9/relu_expand3x3").set_input_x(fire9_expand3x3).set_attr_coef(0.000000).set_attr_mode(1);
    auto fire9_expand1x1 = hiai::op::Convolution("fire9/expand1x1").set_input_x(fire9_relu_squeeze1x1).set_input_filter(fire9_expand1x1_const_0).set_input_bias(fire9_expand1x1_const_1).set_attr_pad_mode("SPECIFIC").set_attr_groups(1).set_attr_pads(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_dilations(AttrValue::LIST_INT({ 1, 1})).set_attr_strides(AttrValue::LIST_INT({ 1, 1}));
    auto fire9_relu_expand1x1 = hiai::op::Activation("fire9/relu_expand1x1").set_input_x(fire9_expand1x1).set_attr_coef(0.000000).set_attr_mode(1);
    auto fire9_concat = hiai::op::ConcatD("fire9/concat").create_dynamic_input_x(2).set_dynamic_input_x(1,fire9_relu_expand1x1).set_dynamic_input_x(2,fire9_relu_expand3x3).set_attr_concat_dim(1);
    auto conv10 = hiai::op::Convolution("conv10").set_input_x(fire9_concat).set_input_filter(conv10_const_0).set_input_bias(conv10_const_1).set_attr_groups(1).set_attr_dilations(AttrValue::LIST_INT({ 1, 1})).set_attr_pad_mode("SPECIFIC").set_attr_pads(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_strides(AttrValue::LIST_INT({ 1, 1}));
    auto relu_conv10 = hiai::op::Activation("relu_conv10").set_input_x(conv10).set_attr_mode(1).set_attr_coef(0.000000);
    auto pool10 = hiai::op::PoolingD("pool10").set_input_x(relu_conv10).set_attr_mode(1).set_attr_data_mode(0).set_attr_pad_mode(4).set_attr_global_pooling(1).set_attr_stride(AttrValue::LIST_INT({ 1, 1})).set_attr_pad(AttrValue::LIST_INT({ 0, 0, 0, 0})).set_attr_window(AttrValue::LIST_INT({ 0, 0})).set_attr_ceil_mode(1);
    auto prob = hiai::op::Softmax("prob").set_input_x(pool10).set_attr_axis(1);
    std::vector<Operator> inputs{data};
    std::vector<Operator> outputs{prob};
    graph.SetInputs(inputs).SetOutputs(outputs);

    return true;
}

bool WriteToOMFile(domi::ModelBufferData om_model_buff,std::string om_file_path)
{
    FILE *fp;
    fp = fopen(om_file_path.c_str(), "wb");
    if (fp == NULL) {
        cout<<om_file_path<<" open failed !!!"<<endl;
        return false;
    }

    uint32_t write_size = (uint32_t)fwrite(om_model_buff.data, 1, om_model_buff.length, fp);
    if (write_size != om_model_buff.length) {
        fclose(fp);
        cout<<"write om file failed !!!"<<endl;
        return false;
    }
    fclose(fp);
    return true;
}

int main(int argc,char** argv){

    Graph graph("bigGraph");
    if(!buildSqueezenetGraph(graph)) {
        cout<<"build graph failed!!!"<<endl;
        return 0;
    }
    ge::Model model("model", "model_v00001");
    model.SetGraph(graph);

    domi::HiaiIrBuild ir_build;
    domi::ModelBufferData om_model_buff;

    bool ret = ir_build.CreateModelBuff(model,om_model_buff);
    if(!ret){
        cout<<"create Model Buffer failed!!!"<<endl;
        return 0;
    }

    ret = ir_build.BuildIRModel(model,om_model_buff);
    if(ret){
        ret = WriteToOMFile(om_model_buff,"./squeezenet.ir.offline.om");
    }
    ir_build.ReleaseModelBuff(om_model_buff);

    return ret;
}

