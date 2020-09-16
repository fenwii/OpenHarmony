# task<a name="EN-US_TOPIC_0000001051451548"></a>

## Command Function<a name="section0533181714106"></a>

This command is used to query information about processes and threads.

## Syntax<a name="section1014412308101"></a>

task/task -a

## Parameter Description<a name="section116057158506"></a>

**Table  1**  Parameters

<a name="table672mcpsimp"></a>
<table><thead align="left"><tr id="row678mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p680mcpsimp"><a name="p680mcpsimp"></a><a name="p680mcpsimp"></a><strong id="b125104616912"><a name="b125104616912"></a><a name="b125104616912"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p682mcpsimp"><a name="p682mcpsimp"></a><a name="p682mcpsimp"></a><strong id="b1786612506919"><a name="b1786612506919"></a><a name="b1786612506919"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p684mcpsimp"><a name="p684mcpsimp"></a><a name="p684mcpsimp"></a><strong id="b195753017289"><a name="b195753017289"></a><a name="b195753017289"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row685mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p687mcpsimp"><a name="p687mcpsimp"></a><a name="p687mcpsimp"></a>-a</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p689mcpsimp"><a name="p689mcpsimp"></a><a name="p689mcpsimp"></a>Displays all information.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p691mcpsimp"><a name="p691mcpsimp"></a><a name="p691mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section2053502951112"></a>

If the parameter is not specified, partial task information is printed by default.

## Example<a name="section12629113381116"></a>

Enter  **task**.

## Output<a name="section19299103465015"></a>

**Figure  1**  Querying partial task information<a name="fig13685195715451"></a>  
![](figures/querying-partial-task-information.png "querying-partial-task-information")

**Table  2**  Output description

<a name="table809mcpsimp"></a>
<table><thead align="left"><tr id="row814mcpsimp"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p816mcpsimp"><a name="p816mcpsimp"></a><a name="p816mcpsimp"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p818mcpsimp"><a name="p818mcpsimp"></a><a name="p818mcpsimp"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row20360171311398"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p123611139397"><a name="p123611139397"></a><a name="p123611139397"></a>PID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p3361171333920"><a name="p3361171333920"></a><a name="p3361171333920"></a>Indicates the process ID.</p>
</td>
</tr>
<tr id="row262535153913"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p862625163918"><a name="p862625163918"></a><a name="p862625163918"></a>PPID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1062611511398"><a name="p1062611511398"></a><a name="p1062611511398"></a>Indicates the parent process ID.</p>
</td>
</tr>
<tr id="row9683953153916"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p76831753103915"><a name="p76831753103915"></a><a name="p76831753103915"></a>PGID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2068355383916"><a name="p2068355383916"></a><a name="p2068355383916"></a>Indicates the process group ID.</p>
</td>
</tr>
<tr id="row85721136402"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p8572151313402"><a name="p8572151313402"></a><a name="p8572151313402"></a>UID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p55721813164013"><a name="p55721813164013"></a><a name="p55721813164013"></a>Indicates the user ID.</p>
</td>
</tr>
<tr id="row19180126151415"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p836mcpsimp"><a name="p836mcpsimp"></a><a name="p836mcpsimp"></a>Status</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p838mcpsimp"><a name="p838mcpsimp"></a><a name="p838mcpsimp"></a>Indicates the current task status.</p>
</td>
</tr>
<tr id="row511517331702"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2116833506"><a name="p2116833506"></a><a name="p2116833506"></a>CPUUSE10s</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2011611331604"><a name="p2011611331604"></a><a name="p2011611331604"></a>Indicates the CPU usage within 10 seconds.</p>
</td>
</tr>
<tr id="row136191839311"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p66199397110"><a name="p66199397110"></a><a name="p66199397110"></a>PName</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p11619153916110"><a name="p11619153916110"></a><a name="p11619153916110"></a>Indicates the process name.</p>
</td>
</tr>
<tr id="row824mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p826mcpsimp"><a name="p826mcpsimp"></a><a name="p826mcpsimp"></a>TID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p828mcpsimp"><a name="p828mcpsimp"></a><a name="p828mcpsimp"></a>Indicates the task ID.</p>
</td>
</tr>
<tr id="row839mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p841mcpsimp"><a name="p841mcpsimp"></a><a name="p841mcpsimp"></a>StackSize</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p843mcpsimp"><a name="p843mcpsimp"></a><a name="p843mcpsimp"></a>Indicates the size of the task stack.</p>
</td>
</tr>
<tr id="row844mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p846mcpsimp"><a name="p846mcpsimp"></a><a name="p846mcpsimp"></a>WaterLine</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p848mcpsimp"><a name="p848mcpsimp"></a><a name="p848mcpsimp"></a>Indicates the peak value used by the stack.</p>
</td>
</tr>
<tr id="row10188146131813"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p218912671818"><a name="p218912671818"></a><a name="p218912671818"></a>MEMUSE</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1518926151810"><a name="p1518926151810"></a><a name="p1518926151810"></a>Indicates the memory usage.</p>
</td>
</tr>
<tr id="row45465584313"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p821mcpsimp"><a name="p821mcpsimp"></a><a name="p821mcpsimp"></a>TaskName</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p823mcpsimp"><a name="p823mcpsimp"></a><a name="p823mcpsimp"></a>Indicates the task name.</p>
</td>
</tr>
</tbody>
</table>

