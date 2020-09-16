# Js Profiler转换工具说明

将真机的数字化文本转换成js性能打点记录

## 文件说明

- `js_profiler.py`  入口文件，根据参数进行信息转换
- `js_profiler_config.py`  配置文件

## 使用方法

#### 环境搭建

1. 安装python环境
   - python >= 3.6
2. 使用python 运行`js_profiler.py`文件

#### 使用示例：

``` bash
# 转换
python js_profiler.py --source D:\workspace\hmf\ace\lite\ace_profiler_582.log  --destination D:\workspace\hmf\ace\lite\ace_profiler_582_real.log
```

#### 参数说明

* `--source` 带转换的文件，例如 `D:\workspace\hmf\ace\lite\ace_profiler_582.log`
* `--destination` 生成的文件，例如 `D:\workspace\hmf\ace\lite\ace_profiler_582_real.log`
