# partinfo<a name="EN-US_TOPIC_0000001051930303"></a>

## Command Function<a name="section1777503617199"></a>

This command is used to query information about multiple partitions of a hard disk or SD card identified by the system.

## Syntax<a name="section185501447132114"></a>

partinfo <_dev\_inodename_\>

## Parameter Description<a name="section1304151212252"></a>

**Table  1**  Parameters

<a name="table1390mcpsimp"></a>
<table><thead align="left"><tr id="row1396mcpsimp"><th class="cellrowborder" valign="top" width="22%" id="mcps1.2.4.1.1"><p id="p1398mcpsimp"><a name="p1398mcpsimp"></a><a name="p1398mcpsimp"></a><strong id="b130786349111516"><a name="b130786349111516"></a><a name="b130786349111516"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="51%" id="mcps1.2.4.1.2"><p id="p1400mcpsimp"><a name="p1400mcpsimp"></a><a name="p1400mcpsimp"></a><strong id="b1089142031013"><a name="b1089142031013"></a><a name="b1089142031013"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p1402mcpsimp"><a name="p1402mcpsimp"></a><a name="p1402mcpsimp"></a><strong id="b17244395211516"><a name="b17244395211516"></a><a name="b17244395211516"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1403mcpsimp"><td class="cellrowborder" valign="top" width="22%" headers="mcps1.2.4.1.1 "><p id="p1405mcpsimp"><a name="p1405mcpsimp"></a><a name="p1405mcpsimp"></a>dev_inodename</p>
</td>
<td class="cellrowborder" valign="top" width="51%" headers="mcps1.2.4.1.2 "><p id="p1407mcpsimp"><a name="p1407mcpsimp"></a><a name="p1407mcpsimp"></a>Indicates the name of the partition to be queried.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1409mcpsimp"><a name="p1409mcpsimp"></a><a name="p1409mcpsimp"></a>A valid partition name</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section4566131982520"></a>

None

## Example<a name="section4351134942514"></a>

Enter  **partinfo /dev/mmcblk0p0**.

## Output<a name="section66689331412"></a>

![](figures/en-us_image_0000001052370303.png)

