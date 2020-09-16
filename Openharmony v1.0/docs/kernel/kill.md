# kill<a name="ZH-CN_TOPIC_0000001053719629"></a>

## 命令功能<a name="section366714216619"></a>

命令用于发送特定信号给指定进程。

## 命令格式<a name="section8833164614615"></a>

kill \[_signo_  |  _-signo_\] \[_pid_\]

## 参数说明<a name="section12809111019453"></a>

**表 1**  参数说明

<a name="table438mcpsimp"></a>
<table><thead align="left"><tr id="row444mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p446mcpsimp"><a name="p446mcpsimp"></a><a name="p446mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="51.92%" id="mcps1.2.4.1.2"><p id="p448mcpsimp"><a name="p448mcpsimp"></a><a name="p448mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="27.08%" id="mcps1.2.4.1.3"><p id="p450mcpsimp"><a name="p450mcpsimp"></a><a name="p450mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row451mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2500105121818"><a name="p2500105121818"></a><a name="p2500105121818"></a>signo</p>
</td>
<td class="cellrowborder" valign="top" width="51.92%" headers="mcps1.2.4.1.2 "><p id="p1149945111817"><a name="p1149945111817"></a><a name="p1149945111817"></a>信号ID。</p>
</td>
<td class="cellrowborder" valign="top" width="27.08%" headers="mcps1.2.4.1.3 "><p id="p749810571812"><a name="p749810571812"></a><a name="p749810571812"></a>[1,30]</p>
</td>
</tr>
<tr id="row113001232165611"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p18301173213562"><a name="p18301173213562"></a><a name="p18301173213562"></a>pid</p>
</td>
<td class="cellrowborder" valign="top" width="51.92%" headers="mcps1.2.4.1.2 "><p id="p1730143212569"><a name="p1730143212569"></a><a name="p1730143212569"></a>进程ID。</p>
</td>
<td class="cellrowborder" valign="top" width="27.08%" headers="mcps1.2.4.1.3 "><p id="p1301193275618"><a name="p1301193275618"></a><a name="p1301193275618"></a>[1,MAX_INT]</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-notice.gif) **须知：** 
>signo有效范围为\[0,64\]，建议取值范围为\[1,30\]，其余为保留内容。

## 使用指南<a name="section15935131220717"></a>

必须指定发送的信号编号及进程号。

进程编号取值范围根据系统配置变化，例如系统最大支持pid为256，则取值范围缩小为\[1-256\]。

## 使用实例<a name="section79281818476"></a>

1.  查看当前进程列表，查看需要杀死的进程PID（7）。

**图 1**  查看进程PID<a name="fig6133125414256"></a>  
![](figures/查看进程PID.png "查看进程PID")

2. 发送信号14（SIGALRM默认行为为进程终止）给7号进程**helloworld\_d**（用户态进程）：**kill 14 7**（kill -14 7效果相同），并查看当前进程列表，7号进程已终止。

**图 2**  信号发送结果图<a name="fig2281711563"></a>  
![](figures/信号发送结果图.png "信号发送结果图")

## 输出说明<a name="section12742311179"></a>

发送成功或失败输出结果如下。

**图 3**  发送信号给指定进程<a name="fig11800272147"></a>  
![](figures/发送信号给指定进程.png "发送信号给指定进程")

信号发送会显示发送记录，未报错表示信号发送成功。

**图 4**  信号发送失败<a name="fig24081235151813"></a>  
![](figures/信号发送失败.png "信号发送失败")

信号发送失败，上图所示原因为信号发送命令参数无效，请排查信号编号及进程编号是否无效。

