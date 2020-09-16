# exec<a name="ZH-CN_TOPIC_0000001053502450"></a>

## 命令功能<a name="section4643204919313"></a>

exec命令属于shell内置命令，目前实现最基础的执行用户态程序的功能。

## 命令格式<a name="section6553153635"></a>

exec <_executable-file_\>

## 参数说明<a name="section208971157532"></a>

**表 1**  参数说明

<a name="table3900mcpsimp"></a>
<table><thead align="left"><tr id="row3906mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p3908mcpsimp"><a name="p3908mcpsimp"></a><a name="p3908mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p3910mcpsimp"><a name="p3910mcpsimp"></a><a name="p3910mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p3912mcpsimp"><a name="p3912mcpsimp"></a><a name="p3912mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row3913mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3915mcpsimp"><a name="p3915mcpsimp"></a><a name="p3915mcpsimp"></a>executable-file</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p3917mcpsimp"><a name="p3917mcpsimp"></a><a name="p3917mcpsimp"></a>有效的可执行文件。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3919mcpsimp"><a name="p3919mcpsimp"></a><a name="p3919mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section213115219413"></a>

该命令当前仅支持执行有效的二进制程序，程序成功执行，默认后台运行，但与Shell共用终端，可能会导致程序打印输出与Shell输出交错显示。

## 使用实例<a name="section13736564418"></a>

举例：

输入exec helloworld。

## 输出说明<a name="section194005101413"></a>

```
OHOS # exec helloworld
OHOS # hello world!
```

>![](public_sys-resources/icon-note.gif) **说明：** 
>可执行文件执行后，先打印“OHOS \#”提示符原因：目前Shell “exec”命令执行均为后台执行，结果可能导致提示符提前打印。

