# oom<a name="EN-US_TOPIC_0000001053839618"></a>

## Command Function<a name="section366714216619"></a>

This command is used to query and set the low memory threshold and the page cache reclaim threshold.

## Syntax<a name="section8833164614615"></a>

oom

oom -i \[_interval_\]

oom -m \[_mem byte_\]

oom -r \[_mem byte_\]

oom -h | --help

## Parameter Description<a name="section12809111019453"></a>

**Table  1**  Parameters

<a name="table438mcpsimp"></a>
<table><thead align="left"><tr id="row444mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p446mcpsimp"><a name="p446mcpsimp"></a><a name="p446mcpsimp"></a><strong id="b1892061783110"><a name="b1892061783110"></a><a name="b1892061783110"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p448mcpsimp"><a name="p448mcpsimp"></a><a name="p448mcpsimp"></a><strong id="b993819190313"><a name="b993819190313"></a><a name="b993819190313"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p450mcpsimp"><a name="p450mcpsimp"></a><a name="p450mcpsimp"></a><strong id="b1570192842814"><a name="b1570192842814"></a><a name="b1570192842814"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row451mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p5196112612119"><a name="p5196112612119"></a><a name="p5196112612119"></a>-i [interval]</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1149945111817"><a name="p1149945111817"></a><a name="p1149945111817"></a>Sets the interval for checking the Out Of Memory (OOM) thread task.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p749810571812"><a name="p749810571812"></a><a name="p749810571812"></a>100 ms – 10000 ms</p>
</td>
</tr>
<tr id="row18583553793"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p95841853292"><a name="p95841853292"></a><a name="p95841853292"></a>-m [mem byte]</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2058485315912"><a name="p2058485315912"></a><a name="p2058485315912"></a>Sets the low memory threshold.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1584105318917"><a name="p1584105318917"></a><a name="p1584105318917"></a>0 MB (does not check for low memory) – 1 MB</p>
</td>
</tr>
<tr id="row17926124131218"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p49266245128"><a name="p49266245128"></a><a name="p49266245128"></a>-r [mem byte]</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p159263241121"><a name="p159263241121"></a><a name="p159263241121"></a>Sets the page cache reclaim threshold.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p692642412121"><a name="p692642412121"></a><a name="p692642412121"></a>Ranging from the low memory threshold to the maximum available system memory</p>
</td>
</tr>
<tr id="row1176110379557"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p4762113745519"><a name="p4762113745519"></a><a name="p4762113745519"></a>-h | --help</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p9762113775517"><a name="p9762113775517"></a><a name="p9762113775517"></a>Uses the help.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p7762133765511"><a name="p7762133765511"></a><a name="p7762133765511"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section15935131220717"></a>

-   If no parameter is specified, the current configurations of the OOM function are displayed.

## Example<a name="section79281818476"></a>

When the system memory is insufficient, the system displays a message indicating the insufficiency.

## Output<a name="section12742311179"></a>

![](figures/en-us_image_0000001053710680.png)

**Table  2**  Output description

<a name="table487mcpsimp"></a>
<table><thead align="left"><tr id="row492mcpsimp"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p494mcpsimp"><a name="p494mcpsimp"></a><a name="p494mcpsimp"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p496mcpsimp"><a name="p496mcpsimp"></a><a name="p496mcpsimp"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row502mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p583513382179"><a name="p583513382179"></a><a name="p583513382179"></a>[oom] OS is in low memory state</p>
<p id="p636114453553"><a name="p636114453553"></a><a name="p636114453553"></a>total physical memory: 0x1bcf000(byte), used: 0x1b50000(byte), free: 0x7f000(byte), low memory threshold: 0x80000(byte)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p19833143819174"><a name="p19833143819174"></a><a name="p19833143819174"></a>The memory usage of the OS is low.</p>
<p id="p83883291587"><a name="p83883291587"></a><a name="p83883291587"></a>The available physical memory in the entire OS is <strong id="b4224742143819"><a name="b4224742143819"></a><a name="b4224742143819"></a>0x1bcf000</strong> bytes, <strong id="b119851011113911"><a name="b119851011113911"></a><a name="b119851011113911"></a>0x1b50000</strong> bytes have been used, and <strong id="b64661823143914"><a name="b64661823143914"></a><a name="b64661823143914"></a>0x7f000</strong> bytes are available. The current low memory threshold is <strong id="b186415313396"><a name="b186415313396"></a><a name="b186415313396"></a>0x80000</strong> bytes.</p>
</td>
</tr>
<tr id="row1990234224612"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p3902144294612"><a name="p3902144294612"></a><a name="p3902144294612"></a>[oom] candidate victim process init pid: 1, actual phy mem byte: 82602</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p13903144284610"><a name="p13903144284610"></a><a name="p13903144284610"></a>The memory usage of each process is printed. The <strong id="b181925124408"><a name="b181925124408"></a><a name="b181925124408"></a>init</strong> process actually uses <strong id="b218710196403"><a name="b218710196403"></a><a name="b218710196403"></a>82602</strong> bytes, and the shared memory is calculated based on the proportion.</p>
</td>
</tr>
<tr id="row520212272335"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p172038278339"><a name="p172038278339"></a><a name="p172038278339"></a>[oom] candidate victim process UserProcess12 pid: 12, actual phy mem byte: 25951558</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p112034276331"><a name="p112034276331"></a><a name="p112034276331"></a>The actual memory used by the <strong id="b20223184217402"><a name="b20223184217402"></a><a name="b20223184217402"></a>UserProcess12</strong> process is <strong id="b7661644114117"><a name="b7661644114117"></a><a name="b7661644114117"></a>25951558</strong> bytes.</p>
</td>
</tr>
<tr id="row3273195033416"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p184989213512"><a name="p184989213512"></a><a name="p184989213512"></a>[oom] max phy mem used process UserProcess12 pid: 12, actual phy mem: 25951558</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p112741750143417"><a name="p112741750143417"></a><a name="p112741750143417"></a>The process that uses the most memory currently is <strong id="b51291279435"><a name="b51291279435"></a><a name="b51291279435"></a>UserProcess12</strong>.</p>
</td>
</tr>
<tr id="row16442089365"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p045148153618"><a name="p045148153618"></a><a name="p045148153618"></a>excFrom: User!</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p6452818367"><a name="p6452818367"></a><a name="p6452818367"></a>When the system memory is low, the <strong id="b1538164417439"><a name="b1538164417439"></a><a name="b1538164417439"></a>UserProcess12</strong> process fails to apply for memory and exits as a result.</p>
</td>
</tr>
</tbody>
</table>

