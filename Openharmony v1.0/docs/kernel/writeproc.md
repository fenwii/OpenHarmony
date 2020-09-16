# writeproc<a name="ZH-CN_TOPIC_0000001053240965"></a>

## 命令功能<a name="section366714216619"></a>

proc fs支持传入字符串参数，需要每个文件实现自己的写方法。

## 命令格式<a name="section8833164614615"></a>

writeproc <_data_\>  \>\>  /proc/<_filename_\>

## 参数说明<a name="section12809111019453"></a>

**表 1**  参数说明

<a name="table438mcpsimp"></a>
<table><thead align="left"><tr id="row444mcpsimp"><th class="cellrowborder" valign="top" width="21.000000000000004%" id="mcps1.2.4.1.1"><p id="p446mcpsimp"><a name="p446mcpsimp"></a><a name="p446mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52.970000000000006%" id="mcps1.2.4.1.2"><p id="p448mcpsimp"><a name="p448mcpsimp"></a><a name="p448mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="26.030000000000005%" id="mcps1.2.4.1.3"><p id="p450mcpsimp"><a name="p450mcpsimp"></a><a name="p450mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row451mcpsimp"><td class="cellrowborder" valign="top" width="21.000000000000004%" headers="mcps1.2.4.1.1 "><p id="p2500105121818"><a name="p2500105121818"></a><a name="p2500105121818"></a>data</p>
</td>
<td class="cellrowborder" valign="top" width="52.970000000000006%" headers="mcps1.2.4.1.2 "><p id="p1149945111817"><a name="p1149945111817"></a><a name="p1149945111817"></a>要输入的字符串，以空格为结束符，如需输入空格，请用""包裹。</p>
</td>
<td class="cellrowborder" valign="top" width="26.030000000000005%" headers="mcps1.2.4.1.3 "><p id="p749810571812"><a name="p749810571812"></a><a name="p749810571812"></a>N/A</p>
</td>
</tr>
<tr id="row155978258237"><td class="cellrowborder" valign="top" width="21.000000000000004%" headers="mcps1.2.4.1.1 "><p id="p195983258238"><a name="p195983258238"></a><a name="p195983258238"></a>filename</p>
</td>
<td class="cellrowborder" valign="top" width="52.970000000000006%" headers="mcps1.2.4.1.2 "><p id="p25985252238"><a name="p25985252238"></a><a name="p25985252238"></a>data要传入的proc文件。</p>
</td>
<td class="cellrowborder" valign="top" width="26.030000000000005%" headers="mcps1.2.4.1.3 "><p id="p10598425112312"><a name="p10598425112312"></a><a name="p10598425112312"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section15935131220717"></a>

proc文件实现自身的write函数，调用writeproc命令后会将入参传入write函数。

>![](public_sys-resources/icon-note.gif) **说明：** 
>procfs不支持多线程访问。

## 使用实例<a name="section79281818476"></a>

举例：writeproc test \>\> /proc/uptime

## 输出说明<a name="section12742311179"></a>

OHOS \# writeproc test \>\> /proc/uptime

\[INFO\]write buf is: test

test \>\> /proc/uptime

>![](public_sys-resources/icon-note.gif) **说明：** 
>uptime proc文件临时实现write函数，INFO日志为实现的测试函数打印的日志。

