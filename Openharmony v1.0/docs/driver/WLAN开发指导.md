# WLAN开发指导<a name="ZH-CN_TOPIC_0000001051802310"></a>

WLAN驱动基于HDF框架和PAL框架开发，不区分OS和芯片平台，为不同厂商的WLAN模组提供统一的驱动模型，各WLAN模组厂商根据如下指导适配WLAN驱动框架。

## 约束与限制<a name="section355831574414"></a>

无。

## 开发步骤<a name="section96091936185820"></a>

1.  通过wifi\_config.hcs文件，配置硬件参数：module\(不同feature\)，芯片等；
2.  解析配置文件， 生成全量配置的结构体对象；
3.  Module初始化，创建Module；
4.  挂接chip，初始化chip；
5.  总线初始化；
6.  上层wpa业务挂接。

>![](public_sys-resources/icon-note.gif) **说明：** 
>以上驱动框架适配步骤一部分已经提供（详细见开发实例），待开发人员实现的部分有：1、根据硬件，修改配置参数；2：适配挂接模组；3：测试自验证。

