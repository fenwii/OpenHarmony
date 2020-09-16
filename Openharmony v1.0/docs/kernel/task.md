# task<a name="ZH-CN_TOPIC_0000001051451548"></a>

## 命令功能<a name="section0533181714106"></a>

task命令用于查询进程及线程信息。

## 命令格式<a name="section1014412308101"></a>

task/task -a

## 参数说明<a name="section116057158506"></a>

**表 1**  参数说明

<a name="table672mcpsimp"></a>
<table><thead align="left"><tr id="row678mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p680mcpsimp"><a name="p680mcpsimp"></a><a name="p680mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p682mcpsimp"><a name="p682mcpsimp"></a><a name="p682mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p684mcpsimp"><a name="p684mcpsimp"></a><a name="p684mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row685mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p687mcpsimp"><a name="p687mcpsimp"></a><a name="p687mcpsimp"></a>-a</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p689mcpsimp"><a name="p689mcpsimp"></a><a name="p689mcpsimp"></a>查看更多信息。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p691mcpsimp"><a name="p691mcpsimp"></a><a name="p691mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section2053502951112"></a>

-   参数缺省时默认打印部分任务信息。

## 使用实例<a name="section12629113381116"></a>

举例：输入task

## 输出说明<a name="section19299103465015"></a>

**图 1**  查询任务部分信息<a name="fig13685195715451"></a>  
![](figures/查询任务部分信息.png "查询任务部分信息")

**表 2**  输出说明

<a name="table809mcpsimp"></a>
<table><thead align="left"><tr id="row814mcpsimp"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p816mcpsimp"><a name="p816mcpsimp"></a><a name="p816mcpsimp"></a>输出</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p818mcpsimp"><a name="p818mcpsimp"></a><a name="p818mcpsimp"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row20360171311398"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p123611139397"><a name="p123611139397"></a><a name="p123611139397"></a>PID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p3361171333920"><a name="p3361171333920"></a><a name="p3361171333920"></a>进程ID。</p>
</td>
</tr>
<tr id="row262535153913"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p862625163918"><a name="p862625163918"></a><a name="p862625163918"></a>PPID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1062611511398"><a name="p1062611511398"></a><a name="p1062611511398"></a>父进程ID。</p>
</td>
</tr>
<tr id="row9683953153916"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p76831753103915"><a name="p76831753103915"></a><a name="p76831753103915"></a>PGID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2068355383916"><a name="p2068355383916"></a><a name="p2068355383916"></a>进程组ID。</p>
</td>
</tr>
<tr id="row85721136402"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p8572151313402"><a name="p8572151313402"></a><a name="p8572151313402"></a>UID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p55721813164013"><a name="p55721813164013"></a><a name="p55721813164013"></a>用户ID。</p>
</td>
</tr>
<tr id="row19180126151415"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p836mcpsimp"><a name="p836mcpsimp"></a><a name="p836mcpsimp"></a>Status</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p838mcpsimp"><a name="p838mcpsimp"></a><a name="p838mcpsimp"></a>任务当前的状态。</p>
</td>
</tr>
<tr id="row511517331702"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2116833506"><a name="p2116833506"></a><a name="p2116833506"></a>CPUUSE10s</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2011611331604"><a name="p2011611331604"></a><a name="p2011611331604"></a>10秒内CPU使用率。</p>
</td>
</tr>
<tr id="row136191839311"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p66199397110"><a name="p66199397110"></a><a name="p66199397110"></a>PName</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p11619153916110"><a name="p11619153916110"></a><a name="p11619153916110"></a>进程名。</p>
</td>
</tr>
<tr id="row824mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p826mcpsimp"><a name="p826mcpsimp"></a><a name="p826mcpsimp"></a>TID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p828mcpsimp"><a name="p828mcpsimp"></a><a name="p828mcpsimp"></a>任务ID。</p>
</td>
</tr>
<tr id="row839mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p841mcpsimp"><a name="p841mcpsimp"></a><a name="p841mcpsimp"></a>StackSize</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p843mcpsimp"><a name="p843mcpsimp"></a><a name="p843mcpsimp"></a>任务堆栈的大小。</p>
</td>
</tr>
<tr id="row844mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p846mcpsimp"><a name="p846mcpsimp"></a><a name="p846mcpsimp"></a>WaterLine</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p848mcpsimp"><a name="p848mcpsimp"></a><a name="p848mcpsimp"></a>栈使用的峰值。</p>
</td>
</tr>
<tr id="row10188146131813"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p218912671818"><a name="p218912671818"></a><a name="p218912671818"></a>MEMUSE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1518926151810"><a name="p1518926151810"></a><a name="p1518926151810"></a>内存使用量。</p>
</td>
</tr>
<tr id="row45465584313"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p821mcpsimp"><a name="p821mcpsimp"></a><a name="p821mcpsimp"></a>TaskName</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p823mcpsimp"><a name="p823mcpsimp"></a><a name="p823mcpsimp"></a>任务名。</p>
</td>
</tr>
</tbody>
</table>

