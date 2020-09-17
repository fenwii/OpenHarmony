# 环境配置

## 硬件推荐配置

- 2 GHz 双核处理器或者更高等级CPU

- 2 GB 系统内存及以上

- 200GB 可用磁盘空间

## 开发环境推荐

您需要安装一个64位版本的Ubuntu（推荐Ubuntu 16.04）


```
sudo apt-get -y install openjdk-8-jdk git-core build-essential zlib1g-dev libc6-dev-i386 g++-multilib gcc-multilib linux-libc-dev:i386
sudo apt-get -y install gcc-5-aarch64-linux-gnu g++-5-aarch64-linux-gnu
```


## 安装Clang编译器并完成配置（用于编译方舟编译器代码）

下载**clang+llvm-8.0.0-x86_64-linux-gnu-ubuntu-16.04**
LLVM下载地址：http://releases.llvm.org/download.html#8.0.0

放置到`openarkcompiler/tools`目录，打开`openarkcompiler/build/config/BUILDCONFIG.gn`文件，将`GN_C_COMPILER`、`GN_CXX_COMPILER`和`GN_AR_COMPILER`三个变量配置为Clang编译器所在路径，例如：

```
GN_C_COMPILER = "${MAPLE_ROOT}/tools/clang_llvm-8.0.0-x86_64-linux-gnu-ubuntu-16.04/bin/clang"
GN_CXX_COMPILER = "${MAPLE_ROOT}/tools/clang_llvm-8.0.0-x86_64-linux-gnu-ubuntu-16.04/bin/clang++"
GN_AR_COMPILER = "${MAPLE_ROOT}/tools/clang_llvm-8.0.0-x86_64-linux-gnu-ubuntu-16.04/bin/llvm-ar"
```

其中${MAPLE_ROOT}为openarkcompiler源码根目录。

## 安装Ninja、GN 并完成配置

下载**Ninja(v1.9.0)**及**GN(Linux Version)**
Ninja下载地址：https://github.com/ninja-build/ninja/releases
GN下载地址：https://archive.softwareheritage.org/browse/content/sha1_git:2dc0d5b26caef44f467de8120b26f8aad8b878be/raw/?filename=gn

将GN和Ninja可执行程序放置到openarkcompiler/tools目录，打开openarkcompiler/Makefile文件，将GN和NINJA两个变量配置为GN和Ninja可执行程序所在路径。例如：

```
GN := ${MAPLE_ROOT}/tools/gn/gn
NINJA := ${MAPLE_ROOT}/tools/ninja_1.9.0/ninja
```
