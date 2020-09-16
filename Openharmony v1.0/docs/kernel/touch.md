# touch<a name="ZH-CN_TOPIC_0000001051611542"></a>

## 命令功能<a name="section17541924112716"></a>

-   touch命令用来在指定的目录下创建一个不存在的空文件。
-   touch命令操作已存在的文件会成功，不会更新时间戳。

## 命令格式<a name="section866182711274"></a>

touch \[_filename_\]

## 参数说明<a name="section268912296270"></a>

**表 1**  参数说明

<a name="table1635mcpsimp"></a>
<table><thead align="left"><tr id="row1642mcpsimp"><th class="cellrowborder" valign="top" width="20.73%" id="mcps1.2.4.1.1"><p id="p1653mcpsimp"><a name="p1653mcpsimp"></a><a name="p1653mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52.44%" id="mcps1.2.4.1.2"><p id="p1655mcpsimp"><a name="p1655mcpsimp"></a><a name="p1655mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="26.83%" id="mcps1.2.4.1.3"><p id="p1657mcpsimp"><a name="p1657mcpsimp"></a><a name="p1657mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row1684mcpsimp"><td class="cellrowborder" valign="top" width="20.73%" headers="mcps1.2.4.1.1 "><p id="p1686mcpsimp"><a name="p1686mcpsimp"></a><a name="p1686mcpsimp"></a>filename</p>
</td>
<td class="cellrowborder" valign="top" width="52.44%" headers="mcps1.2.4.1.2 "><p id="p1688mcpsimp"><a name="p1688mcpsimp"></a><a name="p1688mcpsimp"></a>需要创建文件的名称。</p>
</td>
<td class="cellrowborder" valign="top" width="26.83%" headers="mcps1.2.4.1.3 "><p id="p1690mcpsimp"><a name="p1690mcpsimp"></a><a name="p1690mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section412093332714"></a>

-   touch命令用来创建一个空文件，该文件可读写。
-   使用touch命令一次只能创建一个文件。

    >![](public_sys-resources/icon-notice.gif) **须知：** 
    >在系统重要资源路径下使用touch命令创建文件，会对系统造成死机等未知影响，如在/dev路径下执行touch uartdev-0，会产生系统卡死现象。


## 使用实例<a name="section414434814354"></a>

举例：输入touch file.c 输出说明

## 输出说明<a name="section1028419515711"></a>

**图 1**  创建一个名为 file.c 的文件<a name="fig188183221532"></a>  
![](figures/创建一个名为-file-c-的文件.png "创建一个名为-file-c-的文件")

