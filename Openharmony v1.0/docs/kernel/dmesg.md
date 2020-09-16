# dmesg<a name="ZH-CN_TOPIC_0000001052530284"></a>

## 命令功能<a name="section4643204919313"></a>

dmesg命令用于控制内核dmesg缓存区。

## 命令格式<a name="section6553153635"></a>

dmesg

dmesg \[_-c/-C/-D/-E/-L/-U_\]

dmesg -s \[_size_\]

dmesg -l \[_level_\]

dmesg \> \[_fileA_\]

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
<tbody><tr id="row3913mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3915mcpsimp"><a name="p3915mcpsimp"></a><a name="p3915mcpsimp"></a>-c</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p3917mcpsimp"><a name="p3917mcpsimp"></a><a name="p3917mcpsimp"></a>打印缓存区内容并清空缓存区。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3919mcpsimp"><a name="p3919mcpsimp"></a><a name="p3919mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row3920mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3922mcpsimp"><a name="p3922mcpsimp"></a><a name="p3922mcpsimp"></a>-C</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p3924mcpsimp"><a name="p3924mcpsimp"></a><a name="p3924mcpsimp"></a>清空缓存区。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3926mcpsimp"><a name="p3926mcpsimp"></a><a name="p3926mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row3927mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3929mcpsimp"><a name="p3929mcpsimp"></a><a name="p3929mcpsimp"></a>-D/-E</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p3931mcpsimp"><a name="p3931mcpsimp"></a><a name="p3931mcpsimp"></a>关闭/开启控制台打印。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3933mcpsimp"><a name="p3933mcpsimp"></a><a name="p3933mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row3934mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3936mcpsimp"><a name="p3936mcpsimp"></a><a name="p3936mcpsimp"></a>-L/-U</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p3938mcpsimp"><a name="p3938mcpsimp"></a><a name="p3938mcpsimp"></a>关闭/开启串口打印。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3940mcpsimp"><a name="p3940mcpsimp"></a><a name="p3940mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row3941mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3943mcpsimp"><a name="p3943mcpsimp"></a><a name="p3943mcpsimp"></a>-s size</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p3945mcpsimp"><a name="p3945mcpsimp"></a><a name="p3945mcpsimp"></a>设置缓存区大小 size是要设置的大小。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3947mcpsimp"><a name="p3947mcpsimp"></a><a name="p3947mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row3948mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3950mcpsimp"><a name="p3950mcpsimp"></a><a name="p3950mcpsimp"></a>-l level</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p3952mcpsimp"><a name="p3952mcpsimp"></a><a name="p3952mcpsimp"></a>设置缓存等级。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3954mcpsimp"><a name="p3954mcpsimp"></a><a name="p3954mcpsimp"></a>0 - 5</p>
</td>
</tr>
<tr id="row3955mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3957mcpsimp"><a name="p3957mcpsimp"></a><a name="p3957mcpsimp"></a>&gt; fileA</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p3959mcpsimp"><a name="p3959mcpsimp"></a><a name="p3959mcpsimp"></a>将缓存区内容写入文件。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3961mcpsimp"><a name="p3961mcpsimp"></a><a name="p3961mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section213115219413"></a>

-   该命令依赖于LOSCFG\_SHELL\_DMESG，使用时通过menuconfig在配置项中开启"Enable Shell dmesg"：

    Debug  ---\> Enable a Debug Version ---\> Enable Shell ---\> Enable Shell dmesg

-   dmesg参数缺省时，默认打印缓存区内容。
-   各“ - ”选项不能混合使用。
    1.  写入文件需确保已挂载文件系统。
    2.  关闭串口打印会影响shell使用，建议先连接telnet再尝试关闭串口。


## 使用实例<a name="section13736564418"></a>

举例：

输入dmesg \> /usr/dmesg.log。

## 输出说明<a name="section194005101413"></a>

**图 1**  dmesg重定向到文件。<a name="fig11150135113566"></a>  
![](figures/dmesg重定向到文件.png "dmesg重定向到文件")

