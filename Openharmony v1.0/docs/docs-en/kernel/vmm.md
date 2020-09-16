# vmm<a name="EN-US_TOPIC_0000001054144356"></a>

## Command Function<a name="section445335110416"></a>

This command is used to query the virtual memory usage of a process.

## Syntax<a name="section1795712553416"></a>

vmm \[_-a / -h / --help_\]

vmm \[_pid_\]

## Parameter Description<a name="section92544592410"></a>

**Table  1**  Parameters

<a name="table3900mcpsimp"></a>
<table><thead align="left"><tr id="row3906mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p3908mcpsimp"><a name="p3908mcpsimp"></a><a name="p3908mcpsimp"></a><strong id="b163184874711750"><a name="b163184874711750"></a><a name="b163184874711750"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p3910mcpsimp"><a name="p3910mcpsimp"></a><a name="p3910mcpsimp"></a><strong id="b1593993618367"><a name="b1593993618367"></a><a name="b1593993618367"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p3912mcpsimp"><a name="p3912mcpsimp"></a><a name="p3912mcpsimp"></a><strong id="b194294887511750"><a name="b194294887511750"></a><a name="b194294887511750"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row3913mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p17944444181717"><a name="p17944444181717"></a><a name="p17944444181717"></a>-a</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p209441344121716"><a name="p209441344121716"></a><a name="p209441344121716"></a>Displays the virtual memory usage of all processes.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3919mcpsimp"><a name="p3919mcpsimp"></a><a name="p3919mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row3920mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1944124412171"><a name="p1944124412171"></a><a name="p1944124412171"></a>-h | --help</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1494494441713"><a name="p1494494441713"></a><a name="p1494494441713"></a>Displays the help information.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3926mcpsimp"><a name="p3926mcpsimp"></a><a name="p3926mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row3934mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p5945444181720"><a name="p5945444181720"></a><a name="p5945444181720"></a>pid</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1594515442177"><a name="p1594515442177"></a><a name="p1594515442177"></a>Indicates the ID of the process to query.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3940mcpsimp"><a name="p3940mcpsimp"></a><a name="p3940mcpsimp"></a>[0, 63]</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section104151141252"></a>

By default, the virtual memory usage of all processes is displayed.

## Example<a name="section11545171957"></a>

Enter  **vmm 3**.

## Output<a name="section075617368542"></a>

**Figure  1**  Virtual memory usage of the process with PID 3<a name="fig17645956122214"></a>  
![](figures/virtual-memory-usage-of-the-process-with-pid-3.png "virtual-memory-usage-of-the-process-with-pid-3")

**Table  2**  Basic process information

<a name="table17136143042317"></a>
<table><thead align="left"><tr id="row1113611307232"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p17137173017232"><a name="p17137173017232"></a><a name="p17137173017232"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p171371302230"><a name="p171371302230"></a><a name="p171371302230"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row11371230202317"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p0137630122313"><a name="p0137630122313"></a><a name="p0137630122313"></a>PID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p513793016233"><a name="p513793016233"></a><a name="p513793016233"></a>Indicates the process ID.</p>
</td>
</tr>
<tr id="row61371630112315"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p18137133019236"><a name="p18137133019236"></a><a name="p18137133019236"></a>aspace</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p9137130122311"><a name="p9137130122311"></a><a name="p9137130122311"></a>Indicates the address of the virtual memory control block.</p>
</td>
</tr>
<tr id="row613793015232"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p12137230172311"><a name="p12137230172311"></a><a name="p12137230172311"></a>name</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p19137193018235"><a name="p19137193018235"></a><a name="p19137193018235"></a>Indicates the process name.</p>
</td>
</tr>
<tr id="row1613763019237"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1413723015233"><a name="p1413723015233"></a><a name="p1413723015233"></a>base</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1613783082319"><a name="p1613783082319"></a><a name="p1613783082319"></a>Indicates the start address of the virtual memory.</p>
</td>
</tr>
<tr id="row141376308237"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p101371730162319"><a name="p101371730162319"></a><a name="p101371730162319"></a>size</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p18137143092313"><a name="p18137143092313"></a><a name="p18137143092313"></a>Indicates the size of virtual memory.</p>
</td>
</tr>
<tr id="row19137163072316"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p16137183013235"><a name="p16137183013235"></a><a name="p16137183013235"></a>pages</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p5137130142314"><a name="p5137130142314"></a><a name="p5137130142314"></a>Indicates the number of used physical pages.</p>
</td>
</tr>
</tbody>
</table>

**Table  3**  Virtual memory region information

<a name="table1195314682418"></a>
<table><thead align="left"><tr id="row14953144632413"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p1195314617242"><a name="p1195314617242"></a><a name="p1195314617242"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p13953174614243"><a name="p13953174614243"></a><a name="p13953174614243"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row18953114610242"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p09531746132417"><a name="p09531746132417"></a><a name="p09531746132417"></a>region</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1795344642412"><a name="p1795344642412"></a><a name="p1795344642412"></a>Indicates the address of the control block in the virtual memory region.</p>
</td>
</tr>
<tr id="row1795384682411"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p199531846112417"><a name="p199531846112417"></a><a name="p199531846112417"></a>name</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p19539466245"><a name="p19539466245"></a><a name="p19539466245"></a>Indicates the name of the virtual memory region.</p>
</td>
</tr>
<tr id="row99531446132410"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p139531946132417"><a name="p139531946132417"></a><a name="p139531946132417"></a>base</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p139536468242"><a name="p139536468242"></a><a name="p139536468242"></a>Indicates the start address of the virtual memory region.</p>
</td>
</tr>
<tr id="row79531046122418"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p11953546102418"><a name="p11953546102418"></a><a name="p11953546102418"></a>size</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p89531246142419"><a name="p89531246142419"></a><a name="p89531246142419"></a>Indicates the size of the virtual memory region.</p>
</td>
</tr>
<tr id="row1295315464240"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p7953154602419"><a name="p7953154602419"></a><a name="p7953154602419"></a>mmu_flags</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p395464620242"><a name="p395464620242"></a><a name="p395464620242"></a>Indicates the MMU mapping attribute of the virtual memory region.</p>
</td>
</tr>
<tr id="row10954154692413"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p1195484642410"><a name="p1195484642410"></a><a name="p1195484642410"></a>pages</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p29541546112416"><a name="p29541546112416"></a><a name="p29541546112416"></a>Indicates the number of used physical pages (including the shared memory).</p>
</td>
</tr>
<tr id="row1395411463246"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p14954146152418"><a name="p14954146152418"></a><a name="p14954146152418"></a>pg/ref</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p10954164642419"><a name="p10954164642419"></a><a name="p10954164642419"></a>Indicates the number of used physical pages.</p>
</td>
</tr>
</tbody>
</table>

