# 分类网络重训练：

1. 网络结构搜索完成后，生成1个或多个model_arch_result_*.py文件。用户可根据日志或tensorboard中的pareto图自行选择合适的网络结构。
2. 将选中的.py文件拷贝到上一级目录。
3. model_arch_result_*.py中的网络结构默认是tf.keras实现，用户可直接使用。
4. 如果用户想要使用非tf.keras框架进行训练，可直接执行```python3 model_arch_result_*.py```，产生可在tensorboard查看graph的可视化文件以及pb文件，用户将网络结构翻译成所需要的版本。

# Retrain Process of Classification network:

1. We will get one or more model_arch_result_*.py files after search. Users can choose the appropriate network structure according to the log or Pareto Diagram in tensorboard.
2. Copy the selected. Py file to the previous directory.
2. The network structure in model_arch_result_*.py is implemented by tf.keras by default, and users can use it directly.
3. If users want to use other framework for training, they can directly execute ```python3 model_arch_result_*.py```, generates visualization files that can be viewed in tensorboard and pb files, and transform network into the required version.