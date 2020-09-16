# log<a name="ZH-CN_TOPIC_0000001052370295"></a>

## 命令功能<a name="section128219131856"></a>

log命令用于修改&查询日志配置。

## 命令格式<a name="section3894181710519"></a>

log level \[_levelNum_\]

## 参数说明<a name="section7693122310515"></a>

**表 1**  参数说明

<a name="table237mcpsimp"></a>
<table><thead align="left"><tr id="row243mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p245mcpsimp"><a name="p245mcpsimp"></a><a name="p245mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p247mcpsimp"><a name="p247mcpsimp"></a><a name="p247mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p249mcpsimp"><a name="p249mcpsimp"></a><a name="p249mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row250mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p252mcpsimp"><a name="p252mcpsimp"></a><a name="p252mcpsimp"></a>levelNum</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p254mcpsimp"><a name="p254mcpsimp"></a><a name="p254mcpsimp"></a>配置日志打印等级。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p256mcpsimp"><a name="p256mcpsimp"></a><a name="p256mcpsimp"></a>[0x0，0x5]</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section1982111281512"></a>

-   该命令依赖于LOSCFG\_SHELL\_LK，使用时通过menuconfig在配置项中开启"Enable Shell lk"：

    Debug  ---\> Enable a Debug Version ---\> Enable Shell ---\> Enable Shell lK。

-   log level命令用于配置日志的打印等级，包括6个等级

    TRACE\_EMG = 0,

    TRACE\_COMMON = 1,

    TRACE\_ERROR = 2,

    TRACE\_WARN = 3,

    TRACE\_INFO = 4,

    TRACE\_DEBUG = 5

    若level不在有效范围内，会打印提示信息。

-   若log level命令不加\[levelNum\]参数，则默认查看当前打印等级，并且提示使用方法。

## 使用实例<a name="section176301333259"></a>

举例：

输入log level 4

## 输出说明<a name="section14354765415"></a>

![](figures/zh-cn_image_0000001052530298.png)

