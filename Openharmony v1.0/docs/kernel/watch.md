# watch<a name="ZH-CN_TOPIC_0000001052530286"></a>

## 命令功能<a name="section20643141481314"></a>

watch命令用于周期性的监视一个命令的运行结果。

## 命令格式<a name="section1075441721316"></a>

watch

watch \[_-c/-n/-t/--count/--interval/-no-title/--over_\] \[_command_\]

## 参数说明<a name="section1472810220135"></a>

**表 1**  参数说明

<a name="table966mcpsimp"></a>
<table><thead align="left"><tr id="row973mcpsimp"><th class="cellrowborder" valign="top" width="19.801980198019802%" id="mcps1.2.5.1.1"><p id="p975mcpsimp"><a name="p975mcpsimp"></a><a name="p975mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="29.222922292229224%" id="mcps1.2.5.1.2"><p id="p977mcpsimp"><a name="p977mcpsimp"></a><a name="p977mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="22.26222622262226%" id="mcps1.2.5.1.3"><p id="p979mcpsimp"><a name="p979mcpsimp"></a><a name="p979mcpsimp"></a>缺省值</p>
</th>
<th class="cellrowborder" valign="top" width="28.712871287128717%" id="mcps1.2.5.1.4"><p id="p981mcpsimp"><a name="p981mcpsimp"></a><a name="p981mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row982mcpsimp"><td class="cellrowborder" valign="top" width="19.801980198019802%" headers="mcps1.2.5.1.1 "><p id="p984mcpsimp"><a name="p984mcpsimp"></a><a name="p984mcpsimp"></a>-c / --count</p>
</td>
<td class="cellrowborder" valign="top" width="29.222922292229224%" headers="mcps1.2.5.1.2 "><p id="p986mcpsimp"><a name="p986mcpsimp"></a><a name="p986mcpsimp"></a>命令执行的总次数。</p>
</td>
<td class="cellrowborder" valign="top" width="22.26222622262226%" headers="mcps1.2.5.1.3 "><p id="p988mcpsimp"><a name="p988mcpsimp"></a><a name="p988mcpsimp"></a>0xFFFFFF</p>
</td>
<td class="cellrowborder" valign="top" width="28.712871287128717%" headers="mcps1.2.5.1.4 "><p id="p990mcpsimp"><a name="p990mcpsimp"></a><a name="p990mcpsimp"></a>（0,0xFFFFFF]</p>
</td>
</tr>
<tr id="row991mcpsimp"><td class="cellrowborder" valign="top" width="19.801980198019802%" headers="mcps1.2.5.1.1 "><p id="p993mcpsimp"><a name="p993mcpsimp"></a><a name="p993mcpsimp"></a>-n / --interval</p>
</td>
<td class="cellrowborder" valign="top" width="29.222922292229224%" headers="mcps1.2.5.1.2 "><p id="p995mcpsimp"><a name="p995mcpsimp"></a><a name="p995mcpsimp"></a>命令周期性执行的时间间隔（s）。</p>
</td>
<td class="cellrowborder" valign="top" width="22.26222622262226%" headers="mcps1.2.5.1.3 "><p id="p997mcpsimp"><a name="p997mcpsimp"></a><a name="p997mcpsimp"></a>1s</p>
</td>
<td class="cellrowborder" valign="top" width="28.712871287128717%" headers="mcps1.2.5.1.4 "><p id="p999mcpsimp"><a name="p999mcpsimp"></a><a name="p999mcpsimp"></a>（0,0xFFFFFF]</p>
</td>
</tr>
<tr id="row1000mcpsimp"><td class="cellrowborder" valign="top" width="19.801980198019802%" headers="mcps1.2.5.1.1 "><p id="p1002mcpsimp"><a name="p1002mcpsimp"></a><a name="p1002mcpsimp"></a>-t / -no-title</p>
</td>
<td class="cellrowborder" valign="top" width="29.222922292229224%" headers="mcps1.2.5.1.2 "><p id="p1004mcpsimp"><a name="p1004mcpsimp"></a><a name="p1004mcpsimp"></a>关闭顶端的时间显示。</p>
</td>
<td class="cellrowborder" valign="top" width="22.26222622262226%" headers="mcps1.2.5.1.3 "><p id="p1006mcpsimp"><a name="p1006mcpsimp"></a><a name="p1006mcpsimp"></a>N/A</p>
</td>
<td class="cellrowborder" valign="top" width="28.712871287128717%" headers="mcps1.2.5.1.4 "><p id="p1008mcpsimp"><a name="p1008mcpsimp"></a><a name="p1008mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row1009mcpsimp"><td class="cellrowborder" valign="top" width="19.801980198019802%" headers="mcps1.2.5.1.1 "><p id="p1011mcpsimp"><a name="p1011mcpsimp"></a><a name="p1011mcpsimp"></a>command</p>
</td>
<td class="cellrowborder" valign="top" width="29.222922292229224%" headers="mcps1.2.5.1.2 "><p id="p1013mcpsimp"><a name="p1013mcpsimp"></a><a name="p1013mcpsimp"></a>需要监测的命令。</p>
</td>
<td class="cellrowborder" valign="top" width="22.26222622262226%" headers="mcps1.2.5.1.3 "><p id="p1015mcpsimp"><a name="p1015mcpsimp"></a><a name="p1015mcpsimp"></a>N/A</p>
</td>
<td class="cellrowborder" valign="top" width="28.712871287128717%" headers="mcps1.2.5.1.4 "><p id="p1017mcpsimp"><a name="p1017mcpsimp"></a><a name="p1017mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row1018mcpsimp"><td class="cellrowborder" valign="top" width="19.801980198019802%" headers="mcps1.2.5.1.1 "><p id="p1020mcpsimp"><a name="p1020mcpsimp"></a><a name="p1020mcpsimp"></a>--over</p>
</td>
<td class="cellrowborder" valign="top" width="29.222922292229224%" headers="mcps1.2.5.1.2 "><p id="p1022mcpsimp"><a name="p1022mcpsimp"></a><a name="p1022mcpsimp"></a>关闭当前监测指令。</p>
</td>
<td class="cellrowborder" valign="top" width="22.26222622262226%" headers="mcps1.2.5.1.3 "><p id="p1024mcpsimp"><a name="p1024mcpsimp"></a><a name="p1024mcpsimp"></a>N/A</p>
</td>
<td class="cellrowborder" valign="top" width="28.712871287128717%" headers="mcps1.2.5.1.4 "><p id="p1026mcpsimp"><a name="p1026mcpsimp"></a><a name="p1026mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section186772414131"></a>

watch运行过程中可以执行**watch --over**结束本次watch命令。

## 使用实例<a name="section4764192791314"></a>

输入举例：

watch  -n 2 -c 6 task

## 输出说明<a name="section5791253155517"></a>

**图 1**  watch task 结果<a name="fig125034159462"></a>  
![](figures/watch-task-结果.png "watch-task-结果")

>![](public_sys-resources/icon-note.gif) **说明：** 
>示例中，总共有6次task命令打印，每次间隔2秒，截图为最后一次打印详情。

