# cpup<a name="ZH-CN_TOPIC_0000001051451546"></a>

## 命令功能<a name="section1842161614217"></a>

cpup命令用于查询系统CPU的占用率。

## 命令格式<a name="section5629527427"></a>

cpup \[_mode_\] \[_taskID_\]

## 参数说明<a name="section133651361023"></a>

**表 1**  参数说明

<a name="table3774mcpsimp"></a>
<table><thead align="left"><tr id="row3780mcpsimp"><th class="cellrowborder" valign="top" width="16%" id="mcps1.2.4.1.1"><p id="p3782mcpsimp"><a name="p3782mcpsimp"></a><a name="p3782mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="56.99999999999999%" id="mcps1.2.4.1.2"><p id="p3784mcpsimp"><a name="p3784mcpsimp"></a><a name="p3784mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p3786mcpsimp"><a name="p3786mcpsimp"></a><a name="p3786mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row3787mcpsimp"><td class="cellrowborder" valign="top" width="16%" headers="mcps1.2.4.1.1 "><p id="p3789mcpsimp"><a name="p3789mcpsimp"></a><a name="p3789mcpsimp"></a>mode</p>
</td>
<td class="cellrowborder" valign="top" width="56.99999999999999%" headers="mcps1.2.4.1.2 "><p id="p168830912393"><a name="p168830912393"></a><a name="p168830912393"></a>● 缺省：显示系统最近10s内的CPU占用率。</p>
<p id="p1522761212395"><a name="p1522761212395"></a><a name="p1522761212395"></a>● 0：显示系统最近10s内的CPU占用率。</p>
<p id="p325915149394"><a name="p325915149394"></a><a name="p325915149394"></a>● 1：显示系统最近1s内的CPU占用率。</p>
<p id="p3791mcpsimp"><a name="p3791mcpsimp"></a><a name="p3791mcpsimp"></a>● 其他数字：显示系统启动至今总的CPU 占用率。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3794mcpsimp"><a name="p3794mcpsimp"></a><a name="p3794mcpsimp"></a>[0,0xFFFFFFFF]</p>
</td>
</tr>
<tr id="row3795mcpsimp"><td class="cellrowborder" valign="top" width="16%" headers="mcps1.2.4.1.1 "><p id="p3797mcpsimp"><a name="p3797mcpsimp"></a><a name="p3797mcpsimp"></a>taskID</p>
</td>
<td class="cellrowborder" valign="top" width="56.99999999999999%" headers="mcps1.2.4.1.2 "><p id="p3799mcpsimp"><a name="p3799mcpsimp"></a><a name="p3799mcpsimp"></a>任务ID号</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3802mcpsimp"><a name="p3802mcpsimp"></a><a name="p3802mcpsimp"></a>[0,0xFFFFFFFF]</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section156611948521"></a>

-   参数缺省时，显示系统10s前的CPU占用率。
-   只有一个参数时，该参数为mode，显示系统相应时间前的CPU占用率。
-   输入两个参数时，第一个参数为mode，第二个参数为taskID，显示对应ID号任务的相应时间前的CPU占用率。

## 使用实例<a name="section68501605319"></a>

举例：输入cpup 1 5

## 输出说明<a name="section19871522144219"></a>

**图 1**  指令输出结果<a name="fig1251224812504"></a>  
![](figures/指令输出结果.png "指令输出结果")

