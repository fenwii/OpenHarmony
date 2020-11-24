/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2018-2019. All rights reserved.
 * Description: detection_defs
 */
#ifndef _HIAI_GRAPH_OP_GE_OP_DETECTION_DEFS_H
#define _HIAI_GRAPH_OP_GE_OP_DETECTION_DEFS_H
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "../operator_hiai_reg.h"

namespace hiai {
/*
 * Permutes the dimensions of the input according to a given pattern.
 * <Input>
 *    x : Input tensor.
 * <Output>
 *    y : Has the same shape as the input, but with the dimensions re-ordered according to the specified pattern.
 * <Attr>
 *    order : Tuple of dimension indices indicating the permutation pattern, list of dimension indices.
 * <Added in HiAI version>
 *    100.300.010.011
 */
const char* const PERMUTE_ATTR_ORDER = "order";

REG_OP(Permute)
.INPUT(x, TensorType({ DT_FLOAT }))
.OUTPUT(y, TensorType({ DT_FLOAT }))
.ATTR(order, AttrValue::LIST_INT ({ 0 }))
.OP_END()

/*
 * A layer in Faster R-CNN net, the role of FSRDetectionOutput is to generate the  number and coordinate of label boxes
 * according to position offset of prior box and adjusting parameters(nms threshold and confidence threshold).
 * <Input>
 *    rois : The coordinate of prior boxes.
 *    bbox_delta : The position offset.
 *    score : The probability score of all prior boxes.
 *    im_info : The image information. Const Op. (img_height, img_width)
 *    actual_rois_num: Reserved.
 * <Output>
 *    actual_bbox_num : The number of output box.
 *    box : The coordinate of output box.
 * <Attr>
 *    num_classes: The number of classes, and must be larger than 1.
 *    score_threshold: Confidence threshold parameter, and must be between 0 and 1.
 *    iou_threshold: Non maximum suppression threshold and must be between 0 and 1.
 *    batch_rois: The parameter of batch_size, and must be between 1 and 65535.
 *                N (number of rois) / batch_size should be a multiple of 16.
 * <Added in HiAI version>
 *    100.320.010.010
 */
const char* const FRS_DETECTIONOUTPUT_ATTR_NUM_CLASSES = "num_classes";
const char* const FRS_DETECTIONOUTPUT_ATTR_BATCH_ROIS = "batch_rois";
const char* const FRS_DETECTIONOUTPUT_ATTR_IOU_THRESHOLD = "iou_threshold";
const char* const FRS_DETECTIONOUTPUT_ATTR_SCORE_THRESHOLD = "score_threshold";

REG_OP(FSRDetectionOutput)
.INPUT(rois, TensorType({ DT_FLOAT }))
.INPUT(bbox_delta, TensorType({ DT_FLOAT }))
.INPUT(score, TensorType({ DT_FLOAT }))
.INPUT(im_info, TensorType({ DT_INT32 }))
.OPTIONAL_INPUT(actual_rois_num, TensorType({ DT_FLOAT }))
.OUTPUT(actual_bbox_num, TensorType({ DT_INT32 }))
.OUTPUT(box, TensorType({ DT_FLOAT }))
.REQUIRED_ATTR(num_classes, AttrValue::INT)
.REQUIRED_ATTR(score_threshold, AttrValue::FLOAT)
.REQUIRED_ATTR(iou_threshold, AttrValue::FLOAT)
.ATTR(batch_rois, AttrValue::INT { 1 })
.OP_END()

/*
 * Apply postprocessing steps to bounding box detections
 * <Input>
 *    score: the score of each anchor with each class.
 *    bbox_delta: the bounding box deltas.
 *    anchors: the shape of each predefined anchor.
 * <Output>
 *    detect_scores: the score of each output detections.
 *    rois: the coordinates of each output bounding box,with format [detect_scores, score, rois, bbox_delta].
 *    detect_class: the class label for each output detection.
 *    actual_rois_num: the number of valid output detections for each batch.
 * <Attr>
 *    scale_y: the scaling factor for dy in bounding box deltas.
 *    scale_x: the scaling factor for dx in bounding box deltas.
 *    scale_h: the scaling factor for dh in bounding box deltas.
 *    scale_w: the scaling factor for dw in bounding box deltas.
 *    max_num_detections: the maxmum number of boxes for the output Boxes with the lowest scores are descarded to
 *    meet the limit.
 *    score_threshold: the score threshold, boxes with scores lower than the threshold are filtered before sending
 *    to the NMS algorithm.
 *    iou_threshold: the iou threshold for hard NMS.
 *    use_regular_nms: setting to true to use regular multi-class NMS algorithm that do NMS separately for each class
 *    and false for a faster algorithm that only do one single NMS using the highest class score
 *    max_classes_per_detection: using when use_regular_nms is set to false, specifying the maximum number of classes
 *    per detection.
 *    max_detections_per_class: using when use_regular_nms is set to true, specifying the maximum number of detections
 *    when applying NMS algorithm for each single class.
 *    is_bg_in_label: set to true to include background class in the list of label map for the output, set fo false
 *    to not include the background.
 *
 * <Added in HiAI version>
 *    100.320.010.010
 */
const char* const DETECTIONPOSTPROCESSING_ATTR_SCALE_Y = "scale_y";
const char* const DETECTIONPOSTPROCESSING_ATTR_SCALE_X = "scale_x";
const char* const DETECTIONPOSTPROCESSING_ATTR_SCALE_H = "scale_h";
const char* const DETECTIONPOSTPROCESSING_ATTR_SCALE_W = "scale_w";
const char* const DETECTIONPOSTPROCESSING_ATTR_MAX_NUM_DETECTIONS = "max_num_detections";
const char* const DETECTIONPOSTPROCESSING_ATTR_SCORE_THRESHOLD = "score_threshold";
const char* const DETECTIONPOSTPROCESSING_ATTR_IOU_THRESHOLD = "iou_threshold";
const char* const DETECTIONPOSTPROCESSING_ATTR_USE_REGULAR_NMS = "use_regular_nms";
const char* const DETECTIONPOSTPROCESSING_ATTR_MAX_CLASSES_PER_DETECTION = "max_classes_per_detection";
const char* const DETECTIONPOSTPROCESSING_ATTR_MAX_DETECTIONS_PER_CLASS = "max_detections_per_class";
const char* const DETECTIONPOSTPROCESSING_ATTR_IS_BG_IN_LABEL = "is_bg_in_label";

REG_OP(DetectionPostprocessing)
.INPUT(score, TensorType({ DT_FLOAT }))
.INPUT(bbox_delta, TensorType({ DT_FLOAT }))
.INPUT(anchors, TensorType({ DT_FLOAT }))
.OUTPUT(detect_scores, TensorType({ DT_FLOAT }))
.OUTPUT(rois, TensorType({ DT_FLOAT }))
.OUTPUT(detect_class, TensorType({ DT_INT32 }))
.OUTPUT(actual_rois_num, TensorType({ DT_INT32 }))
.REQUIRED_ATTR(scale_y, AttrValue::FLOAT)
.REQUIRED_ATTR(scale_x, AttrValue::FLOAT)
.REQUIRED_ATTR(scale_h, AttrValue::FLOAT)
.REQUIRED_ATTR(scale_w, AttrValue::FLOAT)
.REQUIRED_ATTR(max_num_detections, AttrValue::INT)
.REQUIRED_ATTR(score_threshold, AttrValue::FLOAT)
.REQUIRED_ATTR(iou_threshold, AttrValue::FLOAT)
.ATTR(use_regular_nms, AttrValue::BOOL { false })
.ATTR(max_classes_per_detection, AttrValue::INT { 1 })
.ATTR(max_detections_per_class, AttrValue::INT { 1 })
.ATTR(is_bg_in_label, AttrValue::BOOL { false })
.OP_END()
/*
* A layer in SSD net, the role of SSDDetectionOutput is to generate the  number and coordinate of label boxes
* according to position offset of prior box and adjusting parameters(nms threshold and confidence threshold).
* only support in CPUCL
* <Input>
*    mbox_conf : Input tensor.
*    mbox_loc : Input tensor.
*    mbox_priorbox : Input tensor.
* <Output>
*    out_boxnum : The number of output box.
*    regionProposal : Region proposal output tensor
* <Attr>
*    num_classes: The number of classes.
*    shared_location: if true, bounding box are shared among different classes.
*    background_label_id: Background label id. If there is no background class,set it as -1.
*    nms_threshold: Non maximum suppression threshold and must be between 0 and 1.
*    top_k: Number of bboxes to be considered for per class before NMS.
*    eta: Parameter for adaptive nms.
*    variance_encoded_in_target: If true, variance is encoded in target;
*    code_type: Type of coding method for bbox.
*    keep_top_k: Number of total bboxes to be kept per image after nms step.
*    confidence_threshold: Confidence threshold parameter, and must be between 0 and 1.
* <Added in HiAI version>
*    100.500.010.010
*/
REG_OP(SSDDetectionOutput)
.INPUT(mbox_conf, TensorType({ DT_FLOAT }))
.INPUT(mbox_loc, TensorType({ DT_FLOAT }))
.INPUT(mbox_priorbox, TensorType({ DT_FLOAT }))
.OUTPUT(out_boxnum, TensorType({ DT_INT32 }))
.OUTPUT(regionProposal, TensorType({ DT_FLOAT }))
.REQUIRED_ATTR(num_classes, AttrValue::INT)
.ATTR(shared_location, AttrValue::BOOL { false })
.ATTR(background_label_id, AttrValue::INT { 0 })
.ATTR(nms_threshold, AttrValue::FLOAT { 0.3f })
.ATTR(top_k, AttrValue::INT { 200 })
.ATTR(eta, AttrValue::FLOAT { 1.0f })
.ATTR(variance_encoded_in_target, AttrValue::BOOL { false })
.ATTR(code_type, AttrValue::INT { 2 })
.ATTR(keep_top_k, AttrValue::INT { 200 })
.ATTR(confidence_threshold, AttrValue::FLOAT { 0.1f })
.OP_END()
}  // namespace hiai
#pragma GCC diagnostic pop
#endif  // _HIAI_GRAPH_OP_GE_OP_DETECTION_DEFS_H