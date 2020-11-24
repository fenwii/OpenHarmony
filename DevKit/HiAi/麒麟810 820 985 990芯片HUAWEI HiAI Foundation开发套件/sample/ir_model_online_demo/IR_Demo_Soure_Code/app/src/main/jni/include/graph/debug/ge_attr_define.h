/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2020. All rights reserved.
 * Description: ge_attr_define, common attribute define
 */
#ifndef GE_ATTR_DEFINE_H_
#define GE_ATTR_DEFINE_H_
#include "ge_graph_attr_define.h"
namespace hiai
{
    /**
    * 公共属性
    */
    const char* const ATTR_NAME_NAME = "name";

    const char* const ATTR_NAME_TYPE = "type";

    const char* const ATTR_NAME_ALPHA = "alpha";

    const char* const ATTR_NAME_BETA = "beta";

    const char* const ATTR_NAME_PADMODE = "pad_mode";

    const char* const ATTR_NAME_MODE = "mode";

    const char* const ATTR_NAME_FILTER = "filter";

    const char* const ATTR_NAME_HAS_BIAS_VALUE = "has_bias_value";

    const char* const ATTR_NAME_PAD = "pads";

    const char* const ATTR_NAME_PADS = "pad";

    const char* const ATTR_NAME_PAD_MODE = "pad mode";

    const char* const ATTR_NAME_SCALE = "scale";

    const char* const ATTR_NAME_RELUMODE = "relu_mode";

    const char* const ATTR_NAME_RELU_FLAG = "relu_flag";

    const char* const ATTR_NAME_WINO_FLAG = "wino_flag";

    const char* const ATTR_NAME_ORG_WEIGHT_FORMAT = "original_weight_format";

    const char* const ATTR_NAME_NCHW_TO_NC1HWC0 = "nchw_to_nc1hwc0";

    const char* const ATTR_NAME_NC1HWC0_TO_NCHW = "nc1hwc0_to_nchw";

    const char* const ATTR_NAME_FILTER_FORMAT = "filter_format";

    const char* const ATTR_NAME_AXIS = "axis";

    const char* const ATTR_NAME_OUTPUT_NUM = "num_split";

    const char* const ATTR_IMG_H = "img_h";
    const char* const ATTR_IMG_W = "img_w";
    const char* const ATTR_NET_H = "net_h";
    const char* const ATTR_NET_W = "net_w";

    const char* const ATTR_NAME_MULTIPLES = "multiples";

    const char* const ATTR_NAME_T = "T";

    const char* const ATTR_AIPP_COMPATIBLE = "aipp_compatible_flag";
    const char* const ATTR_AIPP_CONV_FLAG = "Aipp_Conv_Flag";
    const char* const ATTR_AIPP_NEW_VERSION = "aipp_version_v2";

    const char* const ATTR_NAME_IS_OUTPUT_DATATYPE_SET = "is_output_datatype_set";

    const char* const ATTR_NAME_INPUT_FORMAT = "input_format";
    const char* const ATTR_NAME_OUTPUT_FORMAT = "output_format";

    const char* const ATTR_NAME_FRAMEWORK_FWK_TYPE = "framework_type";

    const char* const ATTR_NAME_MULTISHAPE_BATCHLIST = "multi_shape_batchlist";
    const char* const ATTR_NAME_MULTISHAPE_BATCHLIST_SIZE = "multi_shape_batchlist_size";

    const char* const ATTR_NAME_INFERRED_FORMAT = "inferred_format";
    const char* const ATTR_NAME_PRED_PERMUTE_DELETED = "pred_permute_deleted";
    const char* const ATTR_NAME_BROACAST_REAL_DIM_CNT = "broacast_real_dim_cnt";
    const char* const ATTR_NAME_DIM_ALIGN = "dim_align";
    const char* const BLOCK_FUSION_WORKSPACE_SIZE = "blockFusion_workspaceSize";
    const char* const BLOCK_FUSION_OP_NODE = "BlockFusionOpNode";
    const char* const FUSION_OP_NAME = "FusionOpName";
    const char* const OP_LIST_ORDER = "op_list_order";
    const char* const FUSION_OP_TYPE = "FusionOpType";

    /* to be deleted*/
    const char* const ATTR_TO_BE_DELETED = "to_be_deleted";
    const char* const PERMUTE_RESHAPE_FUSION = "permute_reshape_fusion";
    const char* const PERMUTE_RESHAPE_FUSION_CONV_PROPOSAL = "fusion_conv_proposal";
    const char* const PERMUTE_RESHAPE_FUSION_CONV_DECODEBBOX = "fusion_conv_decodebbox";
    const char* const PERMUTE_RESHAPE_FUSION_BOX_TYPE_NUM = "box_type_num";
    const char* const SSD_MBOX_LOC_FUSION = "permute_flatten_fusion";
    const char* const SSD_MBOX_CONF_FUSION = "permute_flatten_reshape_flatten_fusion";
    const char* const SSD_MBOX_FUSION_BOX_TYPE_NUM = "ssd_mbox_fusion_box_type_num";
    const char* const SSD_RESHAPE_SLICE_CONCAT_FUSION = "reshape_slice_concat_fusion";

    const char* const SSD_PRIORBOX_CONCAT = "ssd_mbox_conf_priorbox_concat_flag";

    const char* const SCALE_RELU_FUSION = "scale_relu_fusion";

    /**
     * convolution
    */
    const char* const ATTR_NAME_COEF = "coef";

    const char* const ATTR_NAME_STRIDE = "strides";

    const char* const ATTR_NAME_DILATION = "dilations";

    const char* const CONV_ATTR_NAME_ALGO = "algo";

    const char* const CONV_ATTR_NAME_RELU_FLAG = "relu_flag";

    const char* const CONV_ATTR_NAME_ADJ = "adj";

    const char* const CONV_ATTR_NAME_TARGET_SHAPE = "target_shape";

    const char* const CONV_ATTR_NAME_BEFORE_PAD = "before_pad";

    const char* const CONV_ATTR_NAME_HAS_BIAS = "has_bias";

    const char* const ATTR_NO_NEED_SYNCWORKSPACE_FLAG = "no_need_syncworkspace_flag";

    /*Pooling*/
    const char* const POOLING_ATTR_NAN_OPT = "nan_opt";

    /*Eltwise*/
    const char* const ELTWISE_ATTR_RELU_FLAG = "relu_flag";
    const char* const ELTWISE_ATTR_BETA = "beta";

    /*FullConnection*/
    const char* const FULL_CONNECTION_ATTR_RELU_FLAG = "relu_flag";

    /*SoftmaxOpParams*/
    const char* const SOFTMAX_ATTR_MODE = "mode";

    const char* const COMPARE_OP_TYPE = "compare_type";
    const char* const ARGMAXMIN_OP_TYPE = "argmaxmin_type";
    /* Const */
    const char* const CONST_ATTR_NAME_OUTPUT_FORMAT = "output_format";
    const char* const CONST_ATTR_NAME_OUTPUT_TYPE = "output_type";

    /* roipooling */
    const char* const ROIPOOLING_ATTR_NAME_POOLED_H = "pooled_h";
    const char* const ROIPOOLING_ATTR_NAME_POOLED_W = "pooled_w";
    const char* const ROIPOOLING_ATTR_NAME_SPATIAL_SCALE = "spatial_scale";
    const char* const ROIPOOLING_ATTR_NAME_RIO_POOLING_MODE = "rio_pooling_mode";
    const char* const ROIPOOLING_ATTR_NAME_SAMPLING_RATIO = "sampling_ratio";
    const char* const ROIPOOLING_ATTR_NAME_SPATIAL_SCALE_W = "spatial_scale_w";
    const char* const ROIPOOLING_ATTR_NAME_SPATIAL_SCALE_H = "spatial_scale_h";

    /* DetectionOutput */
    const char* const DETECTIONOUTPUT_ATTR_NUM_CLASSES = "num_classes";
    const char* const DETECTIONOUTPUT_ATTR_NMS_THRESHOLD = "nms_threshold";
    const char* const DETECTIONOUTPUT_ATTR_TOP_K = "top_k";
    const char* const DETECTIONOUTPUT_ATTR_CONFIDENCE_THRESHOLD = "confidence_threshold";
    const char* const DETECTIONOUTPUT_ATTR_IMG_H = "img_h";
    const char* const DETECTIONOUTPUT_ATTR_IMG_W = "img_w";

    /* Ssd DetectionOutput */
    const char* const DETECTIONOUTPUT_ATTR_ETA = "eta";
    const char* const DETECTIONOUTPUT_ATTR_SHARED_LOCATION = "shared_location";
    const char* const DETECTIONOUTPUT_ATTR_BACKGROUND_LABEL_ID = "background_label_id";
    const char* const DETECTIONOUTPUT_ATTR_CODE_TYPE = "code_type";
    const char* const DETECTIONOUTPUT_ATTR_VARIANCE_ENCODED_IN_TARGET = "variance_encoded_in_target";
    const char* const DETECTIONOUTPUT_ATTR_KEEP_TOP_K = "keep_top_k";
    const char* const DETECTIONOUTPUT_ATTR_USE_POLYGON = "use_polygon";
    /* yolo DetectionOutput */
    const char* const DETECTIONOUTPUT_ATTR_ClASSES = "classes";
    const char* const DETECTIONOUTPUT_ATTR_BIASES = "biases";
    const char* const DETECTIONOUTPUT_ATTR_RELATIVE = "relative";
    const char* const DETECTIONOUTPUT_ATTR_OBJECTNESS_THRESHOLD = "objectness_threshold";
    const char* const DETECTIONOUTPUT_ATTR_CLASS_THRESHOLD = "class_threshold";
    const char* const DETECTIONOUTPUT_ATTR_POST_TOP_K = "post_top_k";
    const char* const DETECTIONOUTPUT_ATTR_IOU_THRESHOLD_DECAY = "iou_threshold_decay";
    const char* const DETECTIONOUTPUT_ATTR_COOR_SCALE_FACTOR = "coor_scale_factor";
    const char* const DETECTIONOUTPUT_ATTR_YOLO_VERSION = "yolo_version";

    /* Spatialtransfrom */
    const char* const SPTIALTF_ATTR_NAME_OUTPUT_H = "output_h";
    const char* const SPTIALTF_ATTR_NAME_OUTPUT_W = "output_w";
    const char* const SPTIALTF_ATTR_NAME_AFFINE_TRANSFORM = "affine_transform";

    /* Proposal */
    const char* const PROPOSAL_ATTR_NAME_FEAT_STRIDE = "feat_stride";
    const char* const PROPOSAL_ATTR_NAME_BASE_SIZE = "base_size";
    const char* const PROPOSAL_ATTR_NAME_MIN_SIZE = "min_size";
    const char* const PROPOSAL_ATTR_NAME_RATIO = "ratio";
    const char* const PROPOSAL_ATTR_NAME_SCALE = "scale";
    const char* const PROPOSAL_ATTR_NAME_PRE_NMS_TOPN = "pre_nms_topn";
    const char* const PROPOSAL_ATTR_NAME_POST_NMS_TOPN = "post_nms_topn";
    const char* const PROPOSAL_ATTR_NAME_NMS_THRESH = "iou_thresh";
    const char* const PROPOSAL_ATTR_NAME_TOP_SIZE = "top_size";
    const char* const PROPOSAL_ATTR_IMG_H = "img_h";
    const char* const PROPOSAL_ATTR_IMG_W = "img_w";

    /* SsdPRIORBOX */
    const char* const SSD_PRIOR_BOX_ATTR_FLIP = "flip";
    const char* const SSD_PRIOR_BOX_ATTR_CLIP = "clip";
    const char* const SSD_PRIOR_BOX_ATTR_IMG_H = "img_h";
    const char* const SSD_PRIOR_BOX_ATTR_IMG_W = "img_w";
    const char* const SSD_PRIOR_BOX_ATTR_STEP_H = "step_h";
    const char* const SSD_PRIOR_BOX_ATTR_STEP_W = "step_w";
    const char* const SSD_PRIOR_BOX_ATTR_OFFSET = "offset";
    const char* const SSD_PRIOR_BOX_ATTR_MIN_SIZE = "min_size";
    const char* const SSD_PRIOR_BOX_ATTR_MAX_SIZE = "max_size";
    const char* const SSD_PRIOR_BOX_ATTR_MIN_SIZE_NUM = "min_size_num";
    const char* const SSD_PRIOR_BOX_ATTR_MAX_SIZE_NUM = "max_size_num";
    const char* const SSD_PRIOR_BOX_ATTR_ASPECT_RATIO = "aspect_ratio";
    const char* const SSD_PRIOR_BOX_ATTR_ASPECT_RATIO_NUM = "aspect_ratio_num";
    const char* const SSD_PRIOR_BOX_ATTR_VARIANCE = "variance";
    const char* const SSD_PRIOR_BOX_ATTR_VARIANCE_NUM = "variance_num";

    /* PRelu */
    const char* const PRELU_ATTR_CHANNEL_SHARED = "channel_shared";
    const char* const PRELU_ATTR_WEIGHT_DATATYPE = "weight_data_type";
    const char* const PRELU_ATTR_ANN_DATA = "ann_data";

    /* power */
    const char* const POWER_ATTR_NAME_POWER = "power";
    const char* const POWER_ATTR_NAME_SCALE = "scale";
    const char* const POWER_ATTR_NAME_SHIFT = "shift";

    /* split */
    const char* const SPLIT_ATTR_NAME_SLICE_POINT = "slice_point";
    const char* const SPLIT_ATTR_NAME_SIZE_SPLIT = "size_split";

    /* Tvm */
    const char* const TVM_ATTR_NAME_MAGIC = "tvm_magic";
    const char* const TVM_ATTR_NAME_BLOCKDIM = "tvm_blockdim";
    const char* const TVM_ATTR_NAME_METADATA = "tvm_metadata";

    /*slice*/
    const char* const SLICE_ATTR_NAME_BEGINS = "begins";
    const char* const SLICE_ATTR_NAME_SIZES = "sizes";

    /*generate_rpn_proposal*/
    const char* const GENERATE_RPN_PROPOSAL_ATTR_PRE_NMS_TOPK = "pre_nms_topk";
    const char* const GENERATE_RPN_PROPOSAL_ATTR_POST_NMS_TOPK = "post_nms_topk";
    const char* const GENERATE_RPN_PROPOSAL_ATTR_RPN_MINI_SIZE = "rpn_mini_size";
    const char* const GENERATE_RPN_PROPOSAL_ATTR_RPN_PROPOSAL_NMS_THRESH= "rpn_proposal_nms_thresh";

    /*decode_bbox*/
    const char* const DECODE_BBOX_ATTR_DECODECLIP = "decodeClip";

    /* fastrcnnn predications*/
    const char* const FASTRCNN_PREDICTIONS_ATTR_TOPK = "fsr_topk";
    const char* const FASTRCNN_PREDICTIONS_ATTR_SCORE_THRESHOLD = "fsr_score_thres";
    const char* const FASTRCNN_PREDICTIONS_ATTR_NMS_THRESHOLD = "fsr_nms_thres";
    const char* const FASTRCNN_PREDICTIONS_ATTR_NUM_CLASSES = "fsr_num_classes";

    /* REORG*/
    const char* const REORG_ATTR_STRIDE = "stride";
    const char* const REORG_ATTR_REVERSE = "reverse";

    /* MERGE*/
    const char* const MERGE_PRENODE_FLAG = "merge_prenode_flag";
    const char* const TO_BE_OUTPUT = "to_be_output";

    /*Concatv2*/
    const char* const CONCAT_V2_ATTR_TIDX = "Tidx";
    const char* const CONCAT_V2_ATTR_N = "N";
    /* SUM*/
    const char* const SUM_ATTR_TIDX = "Tidx";
    const char* const SUM_ATTR_AXIS = "axis";

    /*ResizeBilinear*/
    const char* const RESIZE_BILINEAR_ATTR_MODE          = "mode";
    const char* const RESIZE_BILINEAR_ATTR_ALPHA         = "alpha";
    const char* const RESIZE_BILINEAR_ATTR_BETA          = "beta";

    /*MatMul*/
    const char* const MATMUL_HAS_BIAS = "has_bias";

    /*Flatten*/
    const char* const FLATTEN_START_AXIS = "start_axis";
    const char* const FLATTEN_END_AXIS = "end_axis";

    /*frameoworkop*/
    const char* const ATTR_NAME_OUT_N = "out_n";
    const char* const ATTR_NAME_OUT_C = "out_c";
    const char* const ATTR_NAME_OUT_H = "out_h";
    const char* const ATTR_NAME_OUT_W = "out_w";
    const char* const ATTR_PAD_DEPTH_CONV = "pad_depth_conv";
    const char* const ATTR_PAD_CONV = "pad_conv";

    const char* const ATTR_NAME_BEFORE_PAD = "before_pad";
    const char* const ANN_MEAN_KEEPDIMS = "AnnMeanKeepDims";
    const char* const PAD_ATTR_PADDINGDS = "paddings";
    const char* const PAD_ATTR_CONSTANT_VALUE = "padvalue";

    /*Rnn*/
    const char* const RNN_TENSORFLOW = "rnn_tensorflow";
    const char* const RNN_MODE_STATIC = "rnn_static";
    const char* const MUTI_RNN = "multi_rnn";
    const char* const CELL_MODE = "mode";
    const char* const LSTM_CELL = "lstm_cell";
    const char* const GRU_CELL = "gru_cell";
    const char* const RNN_HT = "ht";
    const char* const RNN_XT_HT = "xt_ht";
    const char* const RNN_BATCH_SIZE = "batch_size";
    const char* const LSTM_CELL_CLIP = "lstm_cell_clip";
    const char* const LSTM_PROJ_CLIP = "lstm_proj_clip";
    const char* const LSTM_ACTIVATE  = "activation";

    /*Upsample*/
    const char* const UPSAMPLE_ATTR_NAME_SCALE = "scale";

    /* filler */
    const char* const FILLER_TYPE = "filler_type";
    const char* const FILLER_VALUE = "filler_value";

    /* android q channel shuffle */
    const char* const CHANNEL_SHUFFLE_NUM_GROUP = "group";

    /* android q detection postprocessing */
    const char* const DETECTION_POSTPROCESSING_SCALE_X = "scale_x";
    const char* const DETECTION_POSTPROCESSING_SCALE_Y = "scale_y";
    const char* const DETECTION_POSTPROCESSING_SCALE_H = "scale_h";
    const char* const DETECTION_POSTPROCESSING_SCALE_W = "scale_w";
    const char* const DETECTION_POSTPROCESSING_NMS     = "use_regular_nms";
    const char* const DETECTION_POSTPROCESSING_MAX_BOX = "max_num_detections";
    const char* const DETECTION_POSTPROCESSING_MAX_CLASS = "max_classes_per_detection";
    const char* const DETECTION_POSTPROCESSING_MAX_DETECTION = "max_detections_per_class";
    const char* const DETECTION_POSTPROCESSING_SCORE_THRESHOLD = "score_threshold";
    const char* const DETECTION_POSTPROCESSING_IOU_THRESHOLD = "iou_threshold";
    const char* const DETECTION_POSTPROCESSING_BG_IN_LABEL = "is_bg_in_label";

    const char* const BIDIRECTIONAL_SEQ_ACTIVATION = "bidirectional_lstm_activation";
    const char* const BIDIRECTIONAL_SEQ_CELL_CLIP = "bidirectional_lstm_cell_clip";
    const char* const BIDIRECTIONAL_SEQ_PROJ_CLIP = "bidirectional_lstm_proj_clip";
    const char* const BIDIRECTIONAL_SEQ_DATA_LAYOUT = "bidirectional_lstm_data_layout";
    const char* const BIDIRECTIONAL_SEQ_USE_PEEPHOLES = "bidirectional_lstm_use_peepholes";
    const char* const BIDIRECTIONAL_SEQ_USE_PROJECTION = "bidirectional_lstm_use_projction";
    const char* const BIDIRECTIONAL_SEQ_USE_PROJECTION_BIAS = "bidirectional_lstm_use_projction_bias";
    const char* const BIDIRECTIONAL_SEQ_CIFG = "bidirectional_lstm_cifg";

    /* androidnn box with nms limit */
    const char* const BOX_WITH_NMS_LIMIT_SCORE_THRESHOLD = "score_threshold";
    const char* const BOX_WITH_NMS_LIMIT_MAX_NUM_SELECT = "max_num_boxes";
    const char* const BOX_WITH_NMS_LIMIT_NMS_KERNEL = "nms_kernel_method";
    const char* const BOX_WITH_NMS_LIMIT_IOU_THRESHOLD = "iou_threshold";
    const char* const BOX_WITH_NMS_LIMIT_NMS_SCORE_THRESHOLD = "nms_score_threshold";

    /*Calibaration*/
    const char* const STRIDE_H_INDEX = "STRIDE_H_INDEX";
    const char* const STRIDE_W_INDEX = "STRIDE_W_INDEX";
    const char* const PAD_BOTTOM_INDEX = "PAD_BOTTOM_INDEX";
    const char* const PAD_RIGHT_INDEX = "PAD_RIGHT_INDEX";
    const char* const PAD_LEFT_INDEX = "PAD_LEFT_INDEX";

    const char* const QUANTIZE_SCALE_MODE = "quantize_scale_mode";
    const char* const QUANTIZE_SCALE_VALUE = "quantize_scale_value";
    const char* const QUANTIZE_SCALE_OFFSET = "quantize_scale_offset";

    const char* const DEQUANTIZE_SCALE_VALUE = "dequantize_scale_value";
    const char* const DEQUANTIZE_SCALE_OFFSET = "dequantize_scale_offset";

    const char* const ATTR_NAME_GROUP = "group";
    const char* const ATTR_NAME_EPSILON = "epsilon";

    /*Biasadd*/
    const char* const BIASADD_ATTR_DATA_FORMAT = "data_format";

    /**
    * 公共属性
    */
    const char* const ATTR_NAME_OP_KERNEL_TYPE = "op_kernel_type";
    const char* const SAME_INPUT_CONVS ="same_input_conv_flag";
}
#endif
