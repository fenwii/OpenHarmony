# 分割网络demo中加载开源依赖
## 进入分割网络demo目录
```{r, engine='bash', count_lines}
cd $DDK_PATH/tools/tools_dopt/demo/hiaiml/ea_seg_voc
```
## 下载开源实现
```{r, engine='bash', count_lines}
git clone https://github.com/tensorflow/models.git
```
## 进入开源代码目录
```{r, engine='bash', count_lines}
cd models
```
## 切换到指定版本
```{r, engine='bash', count_lines}
git checkout v1.13.0
```
## 返回分割网络demo目录
```{r, engine='bash', count_lines}
cd ..
```
## 设置PYTHONPATH默认路径
```{r, engine='bash', count_lines}
export PYTHONPATH=$PYTHONPATH:`pwd`/models/research:`pwd`/models/research/slim
```
注意：每次打开终端需要重新执行一次，或添加到“~/.bashrc”文件，并执行“source ~/.bashrc”。
## 修改开源实现
*当前路径为“ea_seg_voc”*  
**step1**：修改train_utils.py，该文件的路径为：“.\models\research\deeplab\utils\train_utils.py”。
1. 将第72行的“slim.one_hot_encoding”修改为“tf.one_hot”；
2. 在第74行的“tf.losses.softmax_cross_entropy”前面增加“return”；

# 分割网络重训练：
1. 网络结构搜索完成后，生成1个或多个model_arch_result_*.py文件。用户可根据日志或tensorboard中的pareto图自行选择合适的网络结构。
2. 将选中的.py文件拷贝到上一级目录。
3. model_arch_result_*.py中的网络结构默认是tf.keras实现，用户可直接使用。
4. 如果用户想要使用非tf.keras框架进行训练，可直接执行```python3 model_arch_result_*.py```，产生可在tensorboard查看graph的可视化文件以及pb文件，用户将网络结构翻译成所需要的版本。

# Load dependent open source of segmentation network's demo
## Enter segmentation network's demo
```{r, engine='bash', count_lines}
cd $DDK_PATH/tools/tools_dopt/demo/hiaiml/ea_seg_voc
```
## Download dependent open source
```{r, engine='bash', count_lines}
git clone https://github.com/tensorflow/models.git
```
## Enter the open source
```{r, engine='bash', count_lines}
cd models
```
## Switch to the specified version
```{r, engine='bash', count_lines}
git checkout v1.13.0
```
## Return to the split network demo directory
```{r, engine='bash', count_lines}
cd ..
```
## Set PYTHONPATH default path
```{r, engine='bash', count_lines}
export PYTHONPATH=$PYTHONPATH:`pwd`/models/research:`pwd`/models/research/slim
```
Note: Each time you open the terminal, you need to execute it again, or add it to the "~ / .bashrc" file, and execute "source ~ / .bashrc".
## Modify the source code according to the following steps  
*The current path is "ea_seg_voc"*    
**step1**: Modify train_utils.py. The path of file is: ".\models\research\deeplab\utils\train_utils.py":
1. Modify "slim.one_hot_encoding" in the function "def add_softmax_cross_entropy_loss_for_each_scale" to "tf.one_hot";
2. Add "return" before "tf.losses.softmax_cross_entropy" in the function "def add_softmax_cross_entropy_loss_for_each_scale";
1. Modify "slim.one_hot_encoding" to "tf.one_hot" on line 72;
2. Add "return" before "tf.losses.softmax_cross_entropy" on line 74;

# Retraining of segmentation network
1. We will get one or more model_arch_result_*.py files after search. Users can choose the appropriate network structure according to the log or Pareto Diagram in tensorboard.
2. Copy the selected .py file to the previous directory.
3. The network structure in model_arch_result_*.py is implemented by tf.keras by default, and users can use it directly.
4. If users want to use other framework for training, they can directly execute ```python3 model_arch_result_*.py```, generates visualization files that can be viewed in tensorboard and pb files, and transform network into the required version.
