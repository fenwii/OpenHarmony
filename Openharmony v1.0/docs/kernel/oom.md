# oom<a name="ZH-CN_TOPIC_0000001053839618"></a>

## 命令功能<a name="section366714216619"></a>

查看和设置低内存阈值以及pagecache内存回收阈值。

## 命令格式<a name="section8833164614615"></a>

oom

oom -i \[_interval_\]

oom -m \[_mem byte_\]

oom -r \[_mem byte_\]

oom -h | --help

## 参数说明<a name="section12809111019453"></a>

**表 1**  参数说明

<a name="table438mcpsimp"></a>
<table><thead align="left"><tr id="row444mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p446mcpsimp"><a name="p446mcpsimp"></a><a name="p446mcpsimp"></a>参数</p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p448mcpsimp"><a name="p448mcpsimp"></a><a name="p448mcpsimp"></a>参数说明</p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p450mcpsimp"><a name="p450mcpsimp"></a><a name="p450mcpsimp"></a>取值范围</p>
</th>
</tr>
</thead>
<tbody><tr id="row451mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p5196112612119"><a name="p5196112612119"></a><a name="p5196112612119"></a>-i [interval]</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1149945111817"><a name="p1149945111817"></a><a name="p1149945111817"></a>设置oom线程任务检查的时间间隔。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p749810571812"><a name="p749810571812"></a><a name="p749810571812"></a>100ms ~ 10000ms</p>
</td>
</tr>
<tr id="row18583553793"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p95841853292"><a name="p95841853292"></a><a name="p95841853292"></a>-m [mem byte]</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2058485315912"><a name="p2058485315912"></a><a name="p2058485315912"></a>设置低内存阈值。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1584105318917"><a name="p1584105318917"></a><a name="p1584105318917"></a>0MB ~ 1MB，0MB表示不做低内存阈值检查。</p>
</td>
</tr>
<tr id="row17926124131218"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p49266245128"><a name="p49266245128"></a><a name="p49266245128"></a>-r [mem byte]</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p159263241121"><a name="p159263241121"></a><a name="p159263241121"></a>设置pagecache内存回收阈值。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p692642412121"><a name="p692642412121"></a><a name="p692642412121"></a>低内存阈值 ~ 系统可用最大内存。</p>
</td>
</tr>
<tr id="row1176110379557"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p4762113745519"><a name="p4762113745519"></a><a name="p4762113745519"></a>-h | --help</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p9762113775517"><a name="p9762113775517"></a><a name="p9762113775517"></a>使用帮助。</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p7762133765511"><a name="p7762133765511"></a><a name="p7762133765511"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## 使用指南<a name="section15935131220717"></a>

-   参数缺省时，显示oom功能当前配置信息。

## 使用实例<a name="section79281818476"></a>

当系统内存不足时，会打印出内存不足的提示信息。

## 输出说明<a name="section12742311179"></a>

![](figures/zh-cn_image_0000001053710680.png)

**表 2**  输出说明

<a name="table487mcpsimp"></a>
<table><thead align="left"><tr id="row492mcpsimp"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p494mcpsimp"><a name="p494mcpsimp"></a><a name="p494mcpsimp"></a>输出</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p496mcpsimp"><a name="p496mcpsimp"></a><a name="p496mcpsimp"></a>说明</p>
</th>
</tr>
</thead>
<tbody><tr id="row502mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p583513382179"><a name="p583513382179"></a><a name="p583513382179"></a>[oom] OS is in low memory state</p>
<p id="p636114453553"><a name="p636114453553"></a><a name="p636114453553"></a>total physical memory: 0x1bcf000(byte), used: 0x1b50000(byte), free: 0x7f000(byte), low memory threshold: 0x80000(byte)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p19833143819174"><a name="p19833143819174"></a><a name="p19833143819174"></a>操作系统处于低内存状态。</p>
<p id="p83883291587"><a name="p83883291587"></a><a name="p83883291587"></a>整个系统可用物理内存为0x1bcf000 byte，已经使用了 0x1b50000 byte， 还剩0x7f000 byte，当前设置的低内存阈值为0x80000 byte。</p>
</td>
</tr>
<tr id="row1990234224612"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p3902144294612"><a name="p3902144294612"></a><a name="p3902144294612"></a>[oom] candidate victim process init pid: 1, actual phy mem byte: 82602</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p13903144284610"><a name="p13903144284610"></a><a name="p13903144284610"></a>打印当前各个进程的内存使用情况，init进程实际使用82602byte，其中共享内存按照比例算的。</p>
</td>
</tr>
<tr id="row520212272335"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p172038278339"><a name="p172038278339"></a><a name="p172038278339"></a>[oom] candidate victim process UserProcess12 pid: 12, actual phy mem byte: 25951558</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p112034276331"><a name="p112034276331"></a><a name="p112034276331"></a>UserProcess12进程实际使用25951558byte内存。</p>
</td>
</tr>
<tr id="row3273195033416"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p184989213512"><a name="p184989213512"></a><a name="p184989213512"></a>[oom] max phy mem used process UserProcess12 pid: 12, actual phy mem: 25951558</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p112741750143417"><a name="p112741750143417"></a><a name="p112741750143417"></a>当前使用内存最多的进程是UserProcess12。</p>
</td>
</tr>
<tr id="row16442089365"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p045148153618"><a name="p045148153618"></a><a name="p045148153618"></a>excFrom: User!</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p6452818367"><a name="p6452818367"></a><a name="p6452818367"></a>当系统处于低内存的情况下，UserProcess12进程再去申请内存时失败退出。</p>
</td>
</tr>
</tbody>
</table>

