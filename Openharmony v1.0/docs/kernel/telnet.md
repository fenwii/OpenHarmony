# telnet<a name="ZH-CN_TOPIC_0000001051611544"></a>

## 命令功能<a name="section3551830123913"></a>

本命令用于启动或关闭telnet server服务。

## 命令格式<a name="section14897133233918"></a>

telnet \[_on | off_\]

## 参数说明<a name="section977718353392"></a>

**表 1**  参数说明

<a name="table2844mcpsimp"></a>
<table><thead align="left"><tr id="row2850mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p2852mcpsimp"><a name="p2852mcpsimp"></a><a name="p2852mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p2854mcpsimp"><a name="p2854mcpsimp"></a><a name="p2854mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p2856mcpsimp"><a name="p2856mcpsimp"></a><a name="p2856mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row2857mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2859mcpsimp"><a name="p2859mcpsimp"></a><a name="p2859mcpsimp"></a>on</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2861mcpsimp"><a name="p2861mcpsimp"></a><a name="p2861mcpsimp"></a>启动telnet server服务。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2863mcpsimp"><a name="p2863mcpsimp"></a><a name="p2863mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2864mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2866mcpsimp"><a name="p2866mcpsimp"></a><a name="p2866mcpsimp"></a>off</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2868mcpsimp"><a name="p2868mcpsimp"></a><a name="p2868mcpsimp"></a>关闭telnet server服务。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2870mcpsimp"><a name="p2870mcpsimp"></a><a name="p2870mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section134991538183916"></a>

-   telnet启动要确保网络驱动及网络协议栈已经初始化完成，且板子的网卡是link up状态。
-   暂时无法支持多个客户端（telnet + IP）同时连接开发板。

    >![](public_sys-resources/icon-notice.gif) **须知：** 
    >telnet属于调测功能，默认配置为关闭，正式产品中禁止使用该功能。


## 使用实例<a name="section1097414426398"></a>

举例：输入telnet on

## 输出说明<a name="section11846624191310"></a>

**图 1**  输入 telnet on<a name="fig127221042155418"></a>  
![](figures/输入-telnet-on.png "输入-telnet-on")

