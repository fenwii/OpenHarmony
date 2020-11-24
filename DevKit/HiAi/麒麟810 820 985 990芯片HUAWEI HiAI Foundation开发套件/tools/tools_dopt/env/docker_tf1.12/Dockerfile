FROM nvidia/cuda:9.0-cudnn7-devel-ubuntu16.04
ARG TIMEZONE="Asia/Shanghai"
ARG HTTP_PROXY

# Copy tools
COPY tools /root/ddk/tools

# Install cudnn
RUN cp -P /usr/include/cudnn.h /usr/local/cuda/include
RUN cp -P /usr/lib/x86_64-linux-gnu/libcudnn* /usr/local/cuda/lib64
RUN chmod a+r /usr/local/cuda/include/cudnn.h /usr/local/cuda/lib64/libcudnn*

# Install nccl
RUN mkdir /usr/local/cuda/lib &&  \
    ln -s /usr/lib/x86_64-linux-gnu/libnccl.so.2 /usr/local/cuda/lib/libnccl.so.2 && \
    ln -s /usr/include/nccl.h /usr/local/cuda/include/nccl.h

ENV PATH /usr/local/cuda/bin:${PATH}
ENV LIBRARY_PATH /usr/local/cuda/lib64:/usr/local/cuda/lib:$LIBRARY_PATH
ENV LD_LIBRARY_PATH /usr/local/cuda/lib64:/usr/local/cuda/lib:$LD_LIBRARY_PATH

ENV http_proxy  ${HTTP_PROXY}
ENV https_proxy  ${HTTP_PROXY}

# Set default shell to /bin/bash
SHELL ["/bin/bash", "-cu"]
# No need nvidia apt-source, use huawei apt mirror
RUN rm -f /etc/apt/sources.list.d/*.list && \
    cp -a /etc/apt/sources.list /etc/apt/sources.list.bak && \
    sed -i "s@http://.*archive.ubuntu.com@http://mirrors.huaweicloud.com@g" /etc/apt/sources.list && \
    sed -i "s@http://.*security.ubuntu.com@http://mirrors.huaweicloud.com@g" /etc/apt/sources.list

# Install base tools
RUN apt-get update && apt-get install -y --fix-missing --allow-downgrades --allow-change-held-packages --no-install-recommends\
        apt-utils locales openssh-client openssh-server build-essential libsqlite3-dev\
        cmake g++-4.8 git curl vim wget libjpeg-dev libpng-dev openssl \
        libssl-dev unzip liblz4-tool libglib2.0-0 \
        libprotobuf-dev libleveldb-dev libsnappy-dev libopencv-dev libhdf5-serial-dev libatlas-base-dev \
        protobuf-compiler libboost-all-dev libgflags-dev libgoogle-glog-dev liblmdb-dev python-numpy&& \
        rm -rf /var/lib/apt/lists/*

# Install Open MPI
RUN mkdir /tmp/openmpi && \
    cd /tmp/openmpi && \
    wget --no-check-certificate https://www.open-mpi.org/software/ompi/v4.0/downloads/openmpi-4.0.0.tar.gz && \
    tar zxf openmpi-4.0.0.tar.gz && \
    cd openmpi-4.0.0 && \
    ./configure --enable-orterun-prefix-by-default&& \
    make -j $(nproc) all && \
    make install && \
    ldconfig && \
    rm -rf /tmp/*

# install pip2
RUN mkdir /tmp/python && \
    cd /tmp/python && \
    wget --no-check-certificate https://bootstrap.pypa.io/get-pip.py &&\
    python2 get-pip.py && pip install --upgrade pip &&\
    ldconfig &&\
    rm -rf /tmp/*

ENV PYTHON3_VERSION="3.6.8"
# Install Python3 Pip3
RUN mkdir /tmp/python && \
    cd /tmp/python && \
    wget --no-check-certificate https://www.python.org/ftp/python/${PYTHON3_VERSION}/Python-${PYTHON3_VERSION}.tgz && \
    tar -zxvf Python-${PYTHON3_VERSION}.tgz && \
    cd Python-${PYTHON3_VERSION} && \
    ./configure --prefix=/usr/local/python${PYTHON3_VERSION} --with-ssl --enable-loadable-sqlite-extensions && \
    make -j $(nproc) all && \
    make -j $(nproc) install &&\
    ldconfig &&\
    rm -rf /tmp/*
ENV PATH=/usr/local/python${PYTHON3_VERSION}/bin:$PATH
ENV LD_LIBRARY_PATH=/usr/local/python${PYTHON3_VERSION}/lib/python3.6:$LD_LIBRARY_PATH
RUN ln -s /usr/local/python${PYTHON3_VERSION}/bin/python3.6 /usr/bin/python3 && \
    ln -s /usr/local/python${PYTHON3_VERSION}/bin/pip3.6 /usr/bin/pip3 && \
    update-alternatives --install /usr/bin/python python /usr/bin/python3 500 && \
    update-alternatives --install /usr/local/bin/pip pip /usr/bin/pip3 500 && \
    pip3 install --upgrade pip

# Install HiAIML requirements
ADD ./tools/tools_dopt/env/docker_tf1.12/requirements3.txt /requirements3.txt
RUN cat /requirements3.txt | xargs -n1 pip3 install
# Bugfix for pycocotools on py3
RUN sed -ri 's/== unicode/== bytes/' /usr/local/python3.6.8/lib/python3.6/site-packages/pycocotools/coco.py

# Install horovod
RUN ldconfig /usr/local/cuda/lib64/stubs
RUN HOROVOD_WITH_TENSORFLOW=1 HOROVOD_WITHOUT_PYTORCH=1 HOROVOD_WITHOUT_MXNET=1 \
    HOROVOD_NCCL_HOME=/usr/local/cuda HOROVOD_GPU_ALLREDUCE=NCCL \
    pip3 install --no-cache-dir horovod
RUN ldconfig

# Install caffe1 in ddk
WORKDIR /root
ADD ./tools/tools_dopt/env/docker_tf1.12/requirements2.txt /requirements2.txt
RUN cat /requirements2.txt | xargs -n1 pip2 install
RUN wget --no-check-certificate https://github.com/BVLC/caffe/archive/1.0.tar.gz && \
    tar zxf 1.0.tar.gz -C /root/ddk/tools/tools_dopt/caffe/ && \
    rm -rf /root/1.0.tar.gz && \
    cd /root/ddk/tools/tools_dopt/caffe/caffe-1.0/python && \
    for req in $(cat requirements.txt) pydot; do pip2 install $req; done
RUN cd /root/ddk/tools/tools_dopt/caffe/caffe-1.0 && \
    sed -i "s/arch=compute_20,code=sm_20/arch=compute_30,code=sm_30/" Makefile.config.example && \
    sed -i "s/arch=compute_20,code=sm_21/arch=compute_30,code=sm_30/" Makefile.config.example && \
    sed -i "s/\/usr\/lib\/python2.7/\/usr\/local\/lib\/python2.7/" Makefile.config.example && \
    sed -i "s/.\/src .\/include/.\/src .\/include \/usr\/include\/hdf5\/serial/" Makefile && \
    sed -i "s/hdf5_hl hdf5/hdf5_serial_hl hdf5_serial/" Makefile && \
    cd /root/ddk/tools/tools_dopt/caffe/ && \
    chmod +x ./build_caffe.sh && \
    chmod +x ./caffe-patch/optpatch.sh && \
    sh build_caffe.sh

ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/root/ddk/tools/tools_dopt/caffe/caffe-mod/libs/
ENV PYTHONPATH=/root/ddk/tools/tools_dopt/caffe/caffe-mod/python:$PYTHONPATH

# Unset env
ENV http_proxy ""
ENV https_proxy ""
ENV HTTP_PROXY ""
