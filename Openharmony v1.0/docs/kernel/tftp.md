# tftp<a name="ZH-CN_TOPIC_0000001051451597"></a>

## 命令功能<a name="section15142134573911"></a>

TFTP（Trivial File Transfer Protocol，简单文件传输协议）是TCP/IP协议族中的一个用来在客户机与服务器之间进行简单文件传输的协议，提供简单、低开销的文件传输服务。端口号为69。

tftp命令可以从TFTP服务器上下载文件。

## 命令格式<a name="section20958174917394"></a>

tftp  _<-g/-p\>_ _-l_ _\[FullPathLocalFile\] -r \[RemoteFile\] \[Host\]_

## 参数说明<a name="section576613532395"></a>

**表 1**  参数说明

<a name="table2894mcpsimp"></a>
<table><thead align="left"><tr id="row2900mcpsimp"><th class="cellrowborder" valign="top" width="20.79%" id="mcps1.2.4.1.1"><p id="p2902mcpsimp"><a name="p2902mcpsimp"></a><a name="p2902mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52.480000000000004%" id="mcps1.2.4.1.2"><p id="p2904mcpsimp"><a name="p2904mcpsimp"></a><a name="p2904mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="26.729999999999997%" id="mcps1.2.4.1.3"><p id="p2906mcpsimp"><a name="p2906mcpsimp"></a><a name="p2906mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row2907mcpsimp"><td class="cellrowborder" valign="top" width="20.79%" headers="mcps1.2.4.1.1 "><p id="p2909mcpsimp"><a name="p2909mcpsimp"></a><a name="p2909mcpsimp"></a>-g/-p</p>
</td>
<td class="cellrowborder" valign="top" width="52.480000000000004%" headers="mcps1.2.4.1.2 "><p id="p2911mcpsimp"><a name="p2911mcpsimp"></a><a name="p2911mcpsimp"></a>文件传输方向：</p>
<a name="ul73571240131312"></a><a name="ul73571240131312"></a><ul id="ul73571240131312"><li>-g 从TFTP服务器获取文件。</li><li>-p 上传文件到TFTP服务器。</li></ul>
</td>
<td class="cellrowborder" valign="top" width="26.729999999999997%" headers="mcps1.2.4.1.3 "><p id="p14399194271310"><a name="p14399194271310"></a><a name="p14399194271310"></a>N/A</p>
</td>
</tr>
<tr id="row2921mcpsimp"><td class="cellrowborder" valign="top" width="20.79%" headers="mcps1.2.4.1.1 "><p id="p2923mcpsimp"><a name="p2923mcpsimp"></a><a name="p2923mcpsimp"></a>-l FullPathLocalFile</p>
</td>
<td class="cellrowborder" valign="top" width="52.480000000000004%" headers="mcps1.2.4.1.2 "><p id="p2925mcpsimp"><a name="p2925mcpsimp"></a><a name="p2925mcpsimp"></a>本地文件完整路径。</p>
</td>
<td class="cellrowborder" valign="top" width="26.729999999999997%" headers="mcps1.2.4.1.3 "><p id="entry2926mcpsimpp0"><a name="entry2926mcpsimpp0"></a><a name="entry2926mcpsimpp0"></a>N/A</p>
</td>
</tr>
<tr id="row2927mcpsimp"><td class="cellrowborder" valign="top" width="20.79%" headers="mcps1.2.4.1.1 "><p id="p2929mcpsimp"><a name="p2929mcpsimp"></a><a name="p2929mcpsimp"></a>-r RemoteFile</p>
</td>
<td class="cellrowborder" valign="top" width="52.480000000000004%" headers="mcps1.2.4.1.2 "><p id="p2931mcpsimp"><a name="p2931mcpsimp"></a><a name="p2931mcpsimp"></a>服务端文件名。</p>
</td>
<td class="cellrowborder" valign="top" width="26.729999999999997%" headers="mcps1.2.4.1.3 "><p id="entry2932mcpsimpp0"><a name="entry2932mcpsimpp0"></a><a name="entry2932mcpsimpp0"></a>N/A</p>
</td>
</tr>
<tr id="row2933mcpsimp"><td class="cellrowborder" valign="top" width="20.79%" headers="mcps1.2.4.1.1 "><p id="p2935mcpsimp"><a name="p2935mcpsimp"></a><a name="p2935mcpsimp"></a>Host</p>
</td>
<td class="cellrowborder" valign="top" width="52.480000000000004%" headers="mcps1.2.4.1.2 "><p id="p2937mcpsimp"><a name="p2937mcpsimp"></a><a name="p2937mcpsimp"></a>服务端IP。</p>
</td>
<td class="cellrowborder" valign="top" width="26.729999999999997%" headers="mcps1.2.4.1.3 "><p id="entry2938mcpsimpp0"><a name="entry2938mcpsimpp0"></a><a name="entry2938mcpsimpp0"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section149795134408"></a>

1.  在服务器端搭建TFTP服务器，并进行正确配置。
2.  OpenHarmony单板使用tftp命令上传、下载文件。
3.  传输的文件大小是有限制的不能大于32M。

    >![](public_sys-resources/icon-notice.gif) **须知：** 
    >tftp属于调测功能，默认配置为关闭，正式产品中禁止使用该功能。


## 使用实例<a name="section148921918114015"></a>

举例：从服务器下载out文件。

## 输出说明<a name="section7872155631313"></a>

```
OHOS # tftp -g -l /nfs/out -r out 192.168.1.2
TFTP transfer finish
```

tftp命令执行后，传输正常完成会显示TFTP transfer finish， 失败的话会显示其他的打印信息帮助定位问题。

