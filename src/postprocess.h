#ifndef _RKNN_POSTPROCESS_H_
#define _RKNN_POSTPROCESS_H_

#include <stdint.h>
#include <vector>

#define OBJ_NAME_MAX_SIZE 16                // Maximum size of object name (character count)
#define OBJ_NUMB_MAX_SIZE 64                // Maximum number of detectable objects
#define OBJ_CLASS_NUM     80                // Number of object classes in the model
#define NMS_THRESH        0.45              // Default Non-Maximum Suppression threshold
#define BOX_THRESH        0.25              // Default confidence threshold for object detection
#define PROP_BOX_SIZE     (5+OBJ_CLASS_NUM) // Size of each bounding box property (including class probabilities)

// Structure to hold bounding box coordinates
typedef struct _BOX_RECT
{
    int left;
    int right;
    int top;
    int bottom;
} BOX_RECT;

// Structure to hold detection result for a single object
typedef struct __detect_result_t
{
    char name[OBJ_NAME_MAX_SIZE];           // Name or label of the detected object
    BOX_RECT box;                           // Bounding box coordinates
    float prop;                             // Confidence probability of the detection
} detect_result_t;

// Structure to hold a group of detection results
typedef struct _detect_result_group_t
{
    int id;             // Identifier for the result group (usually unused)
    int count;          // Number of valid detections in this group
    detect_result_t results[OBJ_NUMB_MAX_SIZE]; // Array to store individual detection results
} detect_result_group_t;

// Main post-processing function
int post_process(int8_t *input0, int8_t *input1, int8_t *input2, int model_in_h, int model_in_w,
                 float conf_threshold, float nms_threshold, float scale_w, float scale_h,
                 std::vector<int32_t> &qnt_zps, std::vector<float> &qnt_scales,
                 detect_result_group_t *group);

// Deinitialization function (if needed)
void deinitPostProcess();
#endif //_RKNN_POSTPROCESS_H_
