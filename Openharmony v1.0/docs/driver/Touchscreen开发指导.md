# Touchscreen开发指导<a name="ZH-CN_TOPIC_0000001052537515"></a>

Touchscreen驱动基于HDF框架、以及PLATFORM和OSAL基础接口进行开发，不区分操作系统和芯片平台，为Touchscreen器件提供统一的驱动模型。

1.  HDF驱动框架会提供统一的驱动管理模型，通过模块配置信息，识别并加载对应模块驱动。由HDF驱动框架通过Init入口函数，依次启动器件驱动。
2.  在器件驱动入口函数Init中需实现如下操作：
    -   使用OSAL提供的创建设备节点接口，创建设备节点“/dev/input/eventx”，并实现对此节点操作的方法，如open、close、read、write、ioctl等，以便上下层传递报点数据及控制指令；
    -   根据Touchscreen器件的硬件连接，使用PLATFORM框架提供的GPIO接口配置及操作对应的Reset管脚、中断管脚；
    -   根据Touchscreen硬件选择的通信接口，使用PLATFORM框架提供的I2C或SPI的操作接口。


## 约束与限制<a name="section355831574414"></a>

无。

## 开发步骤<a name="section1255740132616"></a>

1.  从Init入口函数启动驱动

    目前驱动基于HDF驱动模型编写，驱动的加载启动由HDF驱动管理框架统一处理。首先需要在对应的配置文件中，将驱动信息注册进去，此后HDF驱动框架会逐一启动注册过的驱动模块。驱动的相关配置请参考[HDF驱动框架配置指导](驱动开发.md#section1969312275533)。

2.  初始化IO状态及Input配置

    配置对应的IO管脚功能，例如对单板上为Touchscreen设计预留的I2C Pin脚，需设置对应的寄存器，使其选择I2C的通信功能。

3.  执行上电时序

    根据硬件单板设计的通信接口，使用PLATFORM框架提供的管脚操作接口配置对应的复位管脚、中断管脚以及电源操作，对于GPIO的操作，可参考[GPIO操作接口指导](GPIO使用指导.md)。

4.  实现中断处理函数
5.  获取电源状态并实现对应处理
6.  下载对应的Touchscreen固件
7.  创建设备节点并实现操作接口

    根据实际业务需要，创建input设备，例如创建的设备文件为"dev/input/event0"。同时，需要提供对设备文件对应的操作方法，例如open、close、read、write、ioctl、poll等相关操作接口，根据实际需求增删。


## 常见问题<a name="section18129131212275"></a>

无。

