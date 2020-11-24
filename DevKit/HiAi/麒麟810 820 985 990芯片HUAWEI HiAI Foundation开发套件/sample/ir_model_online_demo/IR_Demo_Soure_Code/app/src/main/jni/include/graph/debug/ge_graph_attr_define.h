/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: ge_graph_attr_define, graph attribute define
 */
#ifndef GE_GRAPH_ATTR_DEFINE_H_
#define GE_GRAPH_ATTR_DEFINE_H_

namespace hiai {

    const char* const ATTR_NAME_ALGO = "algo";
    const char* const ATTR_NAME_FORMAT = "format";
    const char* const ATTR_NAME_AIPP = "aipp";
    const char* const AIPP_MODE = "aipp_mode";
    const char* const AIPP_INPUT_NAME = "aipp_input_name";
    const char* const ATTR_NAME_WEIGHTS = "value";

    const char* const ATTR_MODEL_TARGET_TYPE = "target_type";
    const char* const ATTR_MODEL_STREAM_NUM = "stream_num";
    const char* const ATTR_MODEL_EVENT_NUM = "event_num";
    const char* const ATTR_MODEL_MEMORY_SIZE = "memory_size";
    const char* const ATTR_MODEL_WEIGHT_SIZE = "weight_size";
    const char* const ATTR_NAME_WEIGHTS_DATA = "weights_data";

    const char* const TARGET_TYPE_MINI  = "MINI";
    const char* const TARGET_TYPE_LITE  = "LITE";

    const char* const AIPP_MODEL_DATA_DIM_W = "aipp_model_data_dim_w";
    const char* const AIPP_MODEL_DATA_DIM_H = "aipp_model_data_dim_h";
    const char* const SUBGRAPH_NAME = "subgraph_name";
    const char* const SUBGRAPH = "subgraph";
    const char* const ATTR_ORIGINAL_OP_NAME_LIST = "original_op_name_list";
    const char* const GRAPHOP_TASK_SIZE = "graphop_task_size";
    const char* const GRAPHOP_WEIGHT_SIZE = "graphop_weight_size";
    const char* const GRAPHOP_TASK_OFFSET = "graphop_task_offset";
    const char* const GRAPHOP_WEIGHT_OFFSET = "graphop_weight_offset";

    const char* const ATTR_NAME_ORG_FORMAT = "original_format";
    const char* const ATTR_RUN_FORMAT = "run_format";
    const char* const ATTR_NAME_RELUFLAG = "relu_flag";
    const char* const ATTR_NAME_X_QUANT_TYPE = "x_QuantType";
    const char* const ATTR_NAME_W_QUANT_TYPE = "w_QuantType";

    // ResizeBilinear
    const char* const RESIZE_BILINEAR_ATTR_HEIGHT        = "height";
    const char* const RESIZE_BILINEAR_ATTR_WIDTH         = "width";
    const char* const RESIZE_BILINEAR_ATTR_ZOOM_FACTOR   = "zoom_factor";
    const char* const RESIZE_BILINEAR_ATTR_SHRINK_FACTOR = "shrink_factor";
    const char* const RESIZE_BILINEAR_ATTR_PAD_BEGIN     = "pad_begin";
    const char* const RESIZE_BILINEAR_ATTR_PAD_END       = "pad_end";

    // argmax
    const char* const ARGMAX_ATTR_NAME_AXISTYPE = "axis_type";

}
#endif
