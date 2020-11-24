# 检测网络demo中加载开源依赖：
## 进入检测网络demo目录：
```{r, engine='bash', count_lines}
cd $DDK_PATH/tools/tools_dopt/demo/hiaiml/ea_det_coco
```
## 下载开源实现：
```{r, engine='bash', count_lines}
git clone https://github.com/pierluigiferrari/ssd_keras.git
```
## 进入开源代码目录：
```{r, engine='bash', count_lines}
cd ssd_keras
```
## 切换到指定版本：
```{r, engine='bash', count_lines}
git checkout -b v0.9.0
```
## 修改开源实现：
**step1**：修改object_detection_2d_data_generator.py。该文件的路径为：ssd_keras\data_generator\object_detection_2d_data_generator.py。
1. 第837行，```degenerate_box_handling='remove'):``` 修改为 ```degenerate_box_handling='remove', is_get_proxy=False):```
2. 第954行， ```if not (self.labels is None):``` 修改为 ```if not (self.labels is None) and (not is_get_proxy):```
3. 第1068行，```if not (self.labels is None):``` 修改为 ```if not (self.labels is None) and (not is_get_proxy):```
4. 第1095行，```if not (self.labels is None):``` 修改为 ```if not (self.labels is None) and (not is_get_proxy):```
5. 第1124行，```if not (self.labels is None): batch_y.pop(j)``` 修改为 ```if not (self.labels is None) and (not is_get_proxy): batch_y.pop(j)```
6. 第1128行，```if 'original_labels' in returns and not (self.labels is None): batch_original_labels.pop(j)```
修改为 ```if 'original_labels' in returns and not (self.labels is None) and (not is_get_proxy): batch_original_labels.pop(j)```
7. 第31行下面，添加```sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../'))```

**step2**：修改keras_layer_AnchorBoxes.py。该文件的路径为：ssd_keras\keras_layers\keras_layer_AnchorBoxes.py。
1. 第21-23行，
```python
import keras.backend as K
from keras.engine.topology import InputSpec
from keras.engine.topology import Layer
```
修改为：
```python
import tensorflow.keras.backend as K
from tensorflow.python.keras.layers import Layer, InputSpec
import tensorflow as tf
```
2 第171-174行，
```python
if K.image_dim_ordering() == 'tf':
    batch_size, feature_map_height, feature_map_width, feature_map_channels = x._keras_shape
else: # Not yet relevant since TensorFlow is the only supported backend right now, but it can't harm to have this in here for the future
    batch_size, feature_map_channels, feature_map_height, feature_map_width = x._keras_shape
```
修改为：
```python
if K.image_data_format() == 'channels_last':
    batch_size, feature_map_height, feature_map_width, feature_map_channels = x._shape_tuple()
else: # Not yet relevant since TensorFlow is the only supported backend right now, but it can't harm to have this in here for the future
    batch_size, feature_map_channels, feature_map_height, feature_map_width = x._shape_tuple()
```
3 第258行，```if K.image_dim_ordering() == 'tf':``` 修改为 ```if K.image_data_format() == 'channels_last':```
4 第253行，```boxes_tensor = K.tile(K.constant(boxes_tensor, dtype='float32'), (K.shape(x)[0], 1, 1, 1, 1))```
修改为：
```python
boxes_tensor_temp = boxes_tensor + np.zeros_like(boxes_tensor)
for _ in range(x._shape_tuple()[0] - 1):
    boxes_tensor = np.concatenate((boxes_tensor, boxes_tensor_temp), axis=0)
boxes_tensor = K.constant(boxes_tensor, dtype='float32')
```

**step3**：修改keras_layer_L2Normalization.py，该文件的路径为：ssd_keras\keras_layers\keras_layer_L2Normalization.py
1. 第47行， ```if K.image_dim_ordering() == 'tf':``` 修改为 ```if K.image_data_format() == 'channels_last':```
2. 第58行， ```self.trainable_weights = [self.gamma]``` 修改为 ```self._trainable_weights = [self.gamma]```
3. 第21-23行，
```python
import keras.backend as K
from keras.engine.topology import InputSpec
from keras.engine.topology import Layer
```
修改为：
```python
import tensorflow.keras.backend as K
from tensorflow.python.keras.layers import Layer, InputSpec
```
**step4**：修改user_module.py，该文件的路径为：DDK_PATH\tools\tools_dopt/demo\hiaiml\ea_det_coco\user_module.py
1. 在user_module.py第10行下面，插入如下内容：
```
from ssd_keras.data_generator.object_detection_2d_data_generator import DataGenerator
from ssd_keras.data_generator.object_detection_2d_geometric_ops import Resize
from ssd_keras.data_generator.object_detection_2d_photometric_ops import ConvertTo3Channels
from ssd_keras.data_generator.data_augmentation_chain_original_ssd import SSDDataAugmentation
from ssd_keras.eval_utils.coco_utils import get_coco_category_maps
from ssd_keras.keras_layers.keras_layer_AnchorBoxes import AnchorBoxes
from ssd_keras.keras_layers.keras_layer_L2Normalization import L2Normalization
from ssd_keras.keras_loss_function.keras_ssd_loss import SSDLoss
from ssd_keras.ssd_encoder_decoder.ssd_input_encoder import SSDInputEncoder
from ssd_keras.ssd_encoder_decoder.ssd_output_decoder import decode_detections,decode_detections_fast
from ssd_keras.data_generator.object_detection_2d_misc_utils import apply_inverse_transforms
```
2.将ssd_keras\ssd300_training.ipynb中56-59行，插入到
user_module.py中的136行下面
3.将ssd_keras\ssd300_training.ipynb中61行，插入到
user_module.py中的140行下面，并将值修改为80
4.将ssd_keras\ssd300_training.ipynb中63行，插入到
user_module.py中的141行下面
5、user_module.py中的142行：
```
scales_coco
```
修改为
```
scales
```
6.将ssd_keras\ssd300_training.ipynb中65-76行，插入到
user_module.py中的142行下面
7.将ssd_keras\models\keras_ssd300.py中50行的中的"coords='centroids'"，插入到
user_module.py中的154行下面
8.将ssd_keras\ssd300_evaluation_COCO.ipynb中149行，拷贝到
user_module.py中的181行下面
9.将ssd_keras\ssd300_evaluation_COCO.ipynb中167-179行，拷贝到
user_module.py中的186行下面，然后将入参由
```
(out_file=results_file,
    model=model,
    img_height=img_height,
    img_width=img_width,
    classes_to_cats=classes_to_cats,
    data_generator=dataset,
    batch_size=batch_size,
    data_generator_mode='resize',
    model_mode='inference',
    confidence_thresh=0.01,
    iou_threshold=0.45,
    top_k=200,
    normalize_coords=True)
```
修改为
```
(out_file=results_file,
    model=model,
    block_choice=block_choice,
    img_height=img_height,
    img_width=img_width,
    classes_to_cats=classes_to_cats,
    data_generator=data_generator,
    proxy_val_image_ids=proxy_val_image_ids,
    data_size=data_size,
    batch_size=val_batch_size,
    confidence_thresh=0.01,
    iou_threshold=0.45,
    top_k=200,
    normalize_coords=True)
```
10.将ssd_keras\ssd300_evaluation_COCO.ipynb中189-191行，插入到
user_module.py中的第200行下面
11、在user_module.py，第203行
```
sorted(coco_gt.getImgIds())
```
修改为
```
sorted(proxy_val_image_ids)
```
12、将ssd_keras\ssd300_evaluation_COCO.ipynb中195-201行，插入到
user_module.py中的第203行下面
13、将ssd_keras\ssd300_training.ipynb中190行，插入到
user_module.py中的第217行下面

14、将ssd_keras\ssd300_evaluation_COCO.ipynb中142-146行，插入到
user_module.py中的第218行下面

15、在user_module.py，第219-223行
```
    dataset.parse_json(images_dirs=[MS_COCO_dataset_images_dir],
                       annotations_filenames=[MS_COCO_dataset_annotations_filename],
                       ground_truth_available=False, # It doesn't matter whether you set this `True` or `False` because the ground truth won't be used anyway, but the parsing goes faster if you don't load the ground truth.
                       include_classes='all',
                       ret=False)
```
修改为
```
    train_dataset.parse_json(images_dirs=[train_images_dir],
                             annotations_filenames=[train_labels_filename],
                             ground_truth_available=True,
                             include_classes='all',
                             ret=False,
                             verbose=False)
 ```
16、将ssd_keras\ssd300_training.ipynb中第267-269行，插入到
user_module.py中的第224行下面

17、将ssd_keras\ssd300_training.ipynb中285-299行，插入到
user_module.py中的第227行下面

18、将ssd_keras\ssd300_training.ipynb中303-309行，插入到
user_module.py中的第242行下面
19、在user_module.py，第243-244行
```
batch_size=batch_size,
shuffle=True,
```
修改为
```
batch_size=self.batch_size,
shuffle=is_shuffle,
```
20、将ssd_keras\ssd300_training.ipynb中321行，插入到
user_module.py中的第249行下面
21、将ssd_keras\ssd300_training.ipynb中191行，插入到
user_module.py中的第254行下面
22、将ssd_keras\ssd300_evaluation_COCO.ipynb中142-146行，插入到
user_module.py中的第255行下面
23、在user_module.py，第256-260行
```
dataset.parse_json(images_dirs=[MS_COCO_dataset_images_dir],
                   annotations_filenames=[MS_COCO_dataset_annotations_filename],
                   ground_truth_available=False, # It doesn't matter whether you set this `True` or `False` because the ground truth won't be used anyway, but the parsing goes faster if you don't load the ground truth.
                   include_classes='all',
                   ret=False)
```
修改为
```
val_dataset.parse_json(images_dirs=[MS_COCO_dataset_images_dir],
                       annotations_filenames=[MS_COCO_dataset_annotations_filename],
                       ground_truth_available=True,
                       include_classes='all',
                       ret=False,
                       verbose=False)
```
24、将ssd_keras\eval_utils\coco_utils.py中119-120行，插入到
user_module.py中的第261行下面
25、将ssd_keras\eval_utils\coco_utils.py中122-123行，插入到
user_module.py中的第263行下面
26、将ssd_keras\eval_utils\coco_utils.py中133-140行，插入到
user_module.py中的第265行下面
27、在user_module.py，第266-267行
```
    generator = data_generator.generate(batch_size=batch_size,
                                        shuffle=False,
```
修改为
```
    val_generator = val_dataset.generate(batch_size=val_batch_size,
                                                 shuffle=is_shuffle,

28、在user_module.py，第273行
```
    keep_images_without_gt=True)
```
修改为
```
    keep_images_without_gt=True,
    is_get_proxy=True)

29、将ssd_keras\ssd300_training.ipynb中322行，插入到
user_module.py中的第274行下面
30、将ssd_keras\models\keras_ssd300.py中339-357行，插入到
user_module.py中的第470行下面
31、将ssd_keras\eval_utils\coco_utils.py中62-75行，插入到
user_module.py中的574行(末行)下面
32、在user_module.py，第575-588行
```
    (out_file,
        model,
        img_height,
        img_width,
        classes_to_cats,
        data_generator,
        batch_size,
        data_generator_mode='resize',
        model_mode='training',
        confidence_thresh=0.01,
        iou_threshold=0.45,
        top_k=200,
        pred_coords='centroids',
        normalize_coords=True):
```
修改为
```
    (out_file,
       model,
       block_choice,
       img_height,
       img_width,
       classes_to_cats,
       data_generator,
       proxy_val_image_ids,
       data_size,
       batch_size,
       confidence_thresh=0.01,
       iou_threshold=0.45,
       top_k=200,
       pred_coords='centroids',
       normalize_coords=True):
```
33、将ssd_keras\eval_utils\coco_utils.py中142行，插入到
user_module.py中的第589行下面
34、将ssd_keras\eval_utils\coco_utils.py中146行，拷贝到
user_module.py中的第590行下面
35、在user_module.py，第591行
```
n_batches = int(ceil(n_images / batch_size))
```
修改为
```
n_batches = int(ceil(data_size / batch_size))
```
36、将ssd_keras\eval_utils\coco_utils.py中150-198行，插入到
user_module.py中的第591行下面
37、在user_module.py，第592行
```
    for i in tr:
```
修改为
```
    for i in range(n_batches):
```
38、在user_module.py，第596行
```
    y_pred = model.predict(batch_X)
```
修改为
```
        batch_X = tf.cast(batch_X, tf.float32)
        if batch_image_ids[0] in proxy_val_image_ids:
            y_pred = model(block_choice, batch_X, training=False)
        else:
            continue
```

39、在user_module.py，第601-618行
```
        # If the model was created in 'training' mode, the raw predictions need to
        # be decoded and filtered, otherwise that's already taken care of.
        if model_mode == 'training':
            # Decode.
            y_pred = decode_detections(y_pred,
                                       confidence_thresh=confidence_thresh,
                                       iou_threshold=iou_threshold,
                                       top_k=top_k,
                                       input_coords=pred_coords,
                                       normalize_coords=normalize_coords,
                                       img_height=img_height,
                                       img_width=img_width)
        else:
            # Filter out the all-zeros dummy elements of `y_pred`.
            y_pred_filtered = []
            for i in range(len(y_pred)):
                y_pred_filtered.append(y_pred[i][y_pred[i,:,0] != 0])
            y_pred = y_pred_filtered
```
修改为
```
        y_pred = np.array(y_pred)
        y_pred = decode_detections_fast(y_pred,
                                        confidence_thresh=confidence_thresh,
                                        iou_threshold=iou_threshold,
                                        top_k=top_k,
                                        input_coords=pred_coords,
                                        normalize_coords=normalize_coords,
                                        img_height=img_height,
                                        img_width=img_width)
```
40、在user_module.py，第594行
```
    next(generator)
```
修改为
```
    next(data_generator)
```


# 检测网络重训练：
1. 网络结构搜索完成后，生成1个或多个model_arch_result_*.py文件。用户可根据日志或tensorboard中的pareto图自行选择合适的网络结构。
2. 将选中的.py文件拷贝到上一级目录。
3. model_arch_result_*.py中的网络结构默认是tf.keras实现，用户可直接使用。
4. 如果用户想要使用非tf.keras框架进行训练，可直接执行```python3 model_arch_result_*.py```，产生可在tensorboard查看graph的可视化文件以及pb文件，用户将网络结构翻译成所需要的版本。\r

# Load dependent open source of detection network's demo：
## Enter detection network's demo：
```{r, engine='bash', count_lines}
cd $DDK_PATH/tools/tools_dopt/demo/hiaiml/ea_det_coco
```
## Download dependent open source：
```{r, engine='bash', count_lines}
git clone https://github.com/pierluigiferrari/ssd_keras.git
```
## Enter the open source：
```{r, engine='bash', count_lines}
cd ssd_keras
```
## Switch to the specified version：
```{r, engine='bash', count_lines}
git checkout -b v0.9.0
```
## Modify corresponding files refer to the following instructions:
**step1**：Modify object_detection_2d_data_generator.py. The file path is ssd_keras\data_generator\object_detection_2d_data_generator.py.
1. Line 837,  ```degenerate_box_handling='remove'):``` modified to ```degenerate_box_handling='remove', is_get_proxy=False):```
2. Line 954,  ```if not (self.labels is None):``` modified to ```if not (self.labels is None) and (not is_get_proxy):```
3. Line 1068, ```if not (self.labels is None):``` modified to ```if not (self.labels is None) and (not is_get_proxy):```
4. Line 1095, ```if not (self.labels is None):``` modified to ```if not (self.labels is None) and (not is_get_proxy):```
5. Line 1124, ```if not (self.labels is None): batch_y.pop(j)``` modified to ```if not (self.labels is None) and (not is_get_proxy): batch_y.pop(j)```
6. Line 1128, ```if 'original_labels' in returns and not (self.labels is None): batch_original_labels.pop(j)``` modified to ```if 'original_labels' in returns and not (self.labels is None) and (not is_get_proxy): batch_original_labels.pop(j)```
7. Below Line 31，```add sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../'))```


**step2**：Modify keras_layer_AnchorBoxes.py. The file path is ssd_keras\keras_layers\keras_layer_AnchorBoxes.py
1. Line 21-23,
```python
import keras.backend as K
from keras.engine.topology import InputSpec
from keras.engine.topology import Layer
```
modified to:
```python
import tensorflow.keras.backend as K
from tensorflow.python.keras.layers import Layer, InputSpec
import tensorflow as tf
```
2 Line 171-174,
```python
if K.image_dim_ordering() == 'tf':
    batch_size, feature_map_height, feature_map_width, feature_map_channels = x._keras_shape
else: # Not yet relevant since TensorFlow is the only supported backend right now, but it can't harm to have this in here for the future
    batch_size, feature_map_channels, feature_map_height, feature_map_width = x._keras_shape
```
modified to:
```python
if K.image_data_format() == 'channels_last':
    batch_size, feature_map_height, feature_map_width, feature_map_channels = x._shape_tuple()
else: # Not yet relevant since TensorFlow is the only supported backend right now, but it can't harm to have this in here for the future
    batch_size, feature_map_channels, feature_map_height, feature_map_width = x._shape_tuple()
```
3 Line 258, ```if K.image_dim_ordering() == 'tf':``` modified to ```if K.image_data_format() == 'channels_last':```
4 Line 253, ```boxes_tensor = K.tile(K.constant(boxes_tensor, dtype='float32'), (K.shape(x)[0], 1, 1, 1, 1))```
modified to:
```python
boxes_tensor_temp = boxes_tensor + np.zeros_like(boxes_tensor)
for _ in range(x._shape_tuple()[0] - 1):
    boxes_tensor = np.concatenate((boxes_tensor, boxes_tensor_temp), axis=0)
boxes_tensor = K.constant(boxes_tensor, dtype='float32')
```


**step3**：Modify keras_layer_L2Normalization.py. The file path is ssd_keras\keras_layers\keras_layer_L2Normalization.py
1. Line 47, ```if K.image_dim_ordering() == 'tf':``` modified to ```if K.image_data_format() == 'channels_last':```
2. Line 58, ```self.trainable_weights = [self.gamma]``` modified to ```self._trainable_weights = [self.gamma]```
3. Line 21-23,
```python
import keras.backend as K
from keras.engine.topology import InputSpec
from keras.engine.topology import Layer
```
modified to:
```python
import tensorflow.keras.backend as K
from tensorflow.python.keras.layers import Layer, InputSpec
```
**step4**：：Modify user_module.py，The file path is DDK_PATH/tools/tools_dopt/demo/hiaiml/ea_det_coco/user_module.py
1. Insert the following content below line 10 in the user_module.py file:
```
from ssd_keras.data_generator.object_detection_2d_data_generator import DataGenerator
from ssd_keras.data_generator.object_detection_2d_geometric_ops import Resize
from ssd_keras.data_generator.object_detection_2d_photometric_ops import ConvertTo3Channels
from ssd_keras.data_generator.data_augmentation_chain_original_ssd import SSDDataAugmentation
from ssd_keras.eval_utils.coco_utils import get_coco_category_maps
from ssd_keras.keras_layers.keras_layer_AnchorBoxes import AnchorBoxes
from ssd_keras.keras_layers.keras_layer_L2Normalization import L2Normalization
from ssd_keras.keras_loss_function.keras_ssd_loss import SSDLoss
from ssd_keras.ssd_encoder_decoder.ssd_input_encoder import SSDInputEncoder
from ssd_keras.ssd_encoder_decoder.ssd_output_decoder import decode_detections,decode_detections_fast
from ssd_keras.data_generator.object_detection_2d_misc_utils import apply_inverse_transforms
```
2.Insert lines 56 to 59 in the ssd_keras\ssd300_training.ipynb file to the
below line 136 in user_module.py
3.Insert lines 61 in the ssd_keras\ssd300_training.ipynb file to the
below line 140 in user_module.py, then change the value to 80.
4.Insert lines 63 in the ssd_keras\ssd300_training.ipynb file to the
below line 141 in user_module.py
5、Line 142 in user_module.py:
```
scales_coco
```
modified to:
```
scales
```
6.Insert lines 65 to 76 in the ssd_keras\ssd300_training.ipynb file to the
below line 142 in user_module.py
7.Insert "coords='centroids'" in line 50 of the ssd_keras\models\keras_ssd300.py file to the
under line 154 in user_module.py
8.Insert lines 149 in the ssd_keras\ssd300_evaluation_COCO.ipynb file to the
below line 181 in user_module.py

9.Insert lines 167 to 179 in the ssd_keras\ssd300_evaluation_COCO.ipynb file to the
below line 186 in user_module.py, then change the input parameter:
```
(out_file=results_file,
    model=model,
    img_height=img_height,
    img_width=img_width,
    classes_to_cats=classes_to_cats,
    data_generator=dataset,
    batch_size=batch_size,
    data_generator_mode='resize',
    model_mode='inference',
    confidence_thresh=0.01,
    iou_threshold=0.45,
    top_k=200,
    normalize_coords=True)
```
modified to:
```
(out_file=results_file,
    model=model,
    block_choice=block_choice,
    img_height=img_height,
    img_width=img_width,
    classes_to_cats=classes_to_cats,
    data_generator=data_generator,
    proxy_val_image_ids=proxy_val_image_ids,
    data_size=data_size,
    batch_size=val_batch_size,
    confidence_thresh=0.01,
    iou_threshold=0.45,
    top_k=200,
    normalize_coords=True)
```
10.Insert lines 189 to 191 in the ssd_keras\ssd300_evaluation_COCO.ipynb file to the
below line 200 in user_module.py
11、In user_module.py, line 203:
```
sorted(coco_gt.getImgIds())
```
modified to:
```
sorted(proxy_val_image_ids)
```
12、Insert lines 195 to 201 in the ssd_keras\ssd300_evaluation_COCO.ipynb file to the
below line 203 in user_module.py

13、Insert lines 190 in the ssd_keras\ssd300_training.ipynb file to the
below line 217 in user_module.py

14、Insert lines 142 to 146 in the ssd_keras\ssd300_evaluation_COCO.ipynb file to the
below line 218 in user_module.py

15、In user_module.py, line 219 to 223:
```
    dataset.parse_json(images_dirs=[MS_COCO_dataset_images_dir],
                       annotations_filenames=[MS_COCO_dataset_annotations_filename],
                       ground_truth_available=False, # It doesn't matter whether you set this `True` or `False` because the ground truth won't be used anyway, but the parsing goes faster if you don't load the ground truth.
                       include_classes='all',
                       ret=False)
```
modified to:
```
    train_dataset.parse_json(images_dirs=[train_images_dir],
                             annotations_filenames=[train_labels_filename],
                             ground_truth_available=True,
                             include_classes='all',
                             ret=False,
                             verbose=False)
 ```
16、Insert lines 267 to 269 in the ssd_keras\ssd300_training.ipynb file to the
below line 224 in user_module.py

17、Insert lines 285 to 299 in the ssd_keras\ssd300_training.ipynb file to the
below line 227 in user_module.py
18、Insert lines 303 to 309 in the ssd_keras\ssd300_training.ipynb file to the
below line 242 in user_module.py
19、In user_module.py, line 243 to 244:
```
batch_size=batch_size,
shuffle=True,
```
modified to:
```
batch_size=self.batch_size,
shuffle=is_shuffle,
```
20、Insert lines 321 in the ssd_keras\ssd300_training.ipynb file to the
below line 249 in user_module.py
21、Insert lines 191 in the ssd_keras\ssd300_training.ipynb file to the
below line 254 in user_module.py
22、Insert lines 142 to 146 in the ssd_keras\ssd300_evaluation_COCO.ipynb file to the
below line 255 in user_module.py
23、In user_module.py, line 256 to 260:
```
dataset.parse_json(images_dirs=[MS_COCO_dataset_images_dir],
                   annotations_filenames=[MS_COCO_dataset_annotations_filename],
                   ground_truth_available=False, # It doesn't matter whether you set this `True` or `False` because the ground truth won't be used anyway, but the parsing goes faster if you don't load the ground truth.
                   include_classes='all',
                   ret=False)
```
modified to:
```
val_dataset.parse_json(images_dirs=[MS_COCO_dataset_images_dir],
                       annotations_filenames=[MS_COCO_dataset_annotations_filename],
                       ground_truth_available=True,
                       include_classes='all',
                       ret=False,
                       verbose=False)
```
24、Insert lines 119 to 120 in the ssd_keras\eval_utils\coco_utils.py file to the
below line 261 in user_module.py
25、Insert lines 122 to 123 in the ssd_keras\eval_utils\coco_utils.py file to the
below line 263 in user_module.py
26、Insert lines 133 to 140 in the ssd_keras\eval_utils\coco_utils.py file to the
below line 265 in user_module.py
27、In user_module.py, line 266 to 267:
```
    generator = data_generator.generate(batch_size=batch_size,
                                        shuffle=False,
```
modified to:
```
    val_generator = val_dataset.generate(batch_size=val_batch_size,
                                                 shuffle=is_shuffle,

28、In user_module.py, line 273:
```
    keep_images_without_gt=True)
```
modified to:
```
    keep_images_without_gt=True,
    is_get_proxy=True)

29、Insert lines 322 in the ssd_keras\ssd300_training.ipynb file to the
below line 274 in user_module.py
30、Insert lines 339 to 357 in the ssd_keras\models\keras_ssd300.py file to the
below line 470 in user_module.py
31、Insert lines 62 to 75 in the ssd_keras\eval_utils\coco_utils.py file to the
below line 574(Last line) in user_module.py
32、In user_module.py, line 575 to 588:
```
    (out_file,
        model,
        img_height,
        img_width,
        classes_to_cats,
        data_generator,
        batch_size,
        data_generator_mode='resize',
        model_mode='training',
        confidence_thresh=0.01,
        iou_threshold=0.45,
        top_k=200,
        pred_coords='centroids',
        normalize_coords=True):
```
modified to:
```
    (out_file,
       model,
       block_choice,
       img_height,
       img_width,
       classes_to_cats,
       data_generator,
       proxy_val_image_ids,
       data_size,
       batch_size,
       confidence_thresh=0.01,
       iou_threshold=0.45,
       top_k=200,
       pred_coords='centroids',
       normalize_coords=True):
```
33、Insert lines 142 in the ssd_keras\eval_utils\coco_utils.py file to the
below line 589 in user_module.py
34、Insert lines 146 in the ssd_keras\eval_utils\coco_utils.py file to the
below line 590 in user_module.py
35、In user_module.py, line 591:
```
n_batches = int(ceil(n_images / batch_size))
```
modified to:
```
n_batches = int(ceil(data_size / batch_size))
```
36、Insert lines 150 to 198 in the ssd_keras\eval_utils\coco_utils.py file to the
below line 591 in user_module.py
37、In user_module.py, line 592:
```
    for i in tr:
```
modified to:
```
    for i in range(n_batches):
```
38、In user_module.py, line 596:
```
    y_pred = model.predict(batch_X)
```
modified to:
```
        batch_X = tf.cast(batch_X, tf.float32)
        if batch_image_ids[0] in proxy_val_image_ids:
            y_pred = model(block_choice, batch_X, training=False)
        else:
            continue
```

39、In user_module.py, line 601 to 618:
```
        # If the model was created in 'training' mode, the raw predictions need to
        # be decoded and filtered, otherwise that's already taken care of.
        if model_mode == 'training':
            # Decode.
            y_pred = decode_detections(y_pred,
                                       confidence_thresh=confidence_thresh,
                                       iou_threshold=iou_threshold,
                                       top_k=top_k,
                                       input_coords=pred_coords,
                                       normalize_coords=normalize_coords,
                                       img_height=img_height,
                                       img_width=img_width)
        else:
            # Filter out the all-zeros dummy elements of `y_pred`.
            y_pred_filtered = []
            for i in range(len(y_pred)):
                y_pred_filtered.append(y_pred[i][y_pred[i,:,0] != 0])
            y_pred = y_pred_filtered
```
modified to:
```
        y_pred = np.array(y_pred)
        y_pred = decode_detections_fast(y_pred,
                                        confidence_thresh=confidence_thresh,
                                        iou_threshold=iou_threshold,
                                        top_k=top_k,
                                        input_coords=pred_coords,
                                        normalize_coords=normalize_coords,
                                        img_height=img_height,
                                        img_width=img_width)
```
40、In user_module.py, line 594:
```
    next(generator)
```
modified to:
```
    next(data_generator)
```

# Retraining of detection network:
1. We will get one or more model_arch_result_*.py files after search. Users can choose the appropriate network structure according to the log or Pareto Diagram in tensorboard.
2. Copy the selected .py file to the previous directory.
3. The network structure in model_arch_result_*.py is implemented by tf.keras by default, and users can use it directly.
4. If users want to use other framework for training, they can directly execute ```python3 model_arch_result_*.py```, generates visualization files that can be viewed in tensorboard and pb files, and transform network into the required version.