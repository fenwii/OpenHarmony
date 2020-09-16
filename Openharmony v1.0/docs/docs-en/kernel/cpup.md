# cpup<a name="EN-US_TOPIC_0000001051451546"></a>

## Command Function<a name="section1842161614217"></a>

This command is used to query the CPU usage of the system.

## Syntax<a name="section5629527427"></a>

cpup \[_mode_\] \[_taskID_\]

## Parameter Description<a name="section133651361023"></a>

**Table  1**  Parameters

<a name="table3774mcpsimp"></a>
<table><thead align="left"><tr id="row3780mcpsimp"><th class="cellrowborder" valign="top" width="16%" id="mcps1.2.4.1.1"><p id="p3782mcpsimp"><a name="p3782mcpsimp"></a><a name="p3782mcpsimp"></a><strong id="b2691194217466"><a name="b2691194217466"></a><a name="b2691194217466"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="56.99999999999999%" id="mcps1.2.4.1.2"><p id="p3784mcpsimp"><a name="p3784mcpsimp"></a><a name="p3784mcpsimp"></a><strong id="b5417164517462"><a name="b5417164517462"></a><a name="b5417164517462"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p3786mcpsimp"><a name="p3786mcpsimp"></a><a name="p3786mcpsimp"></a><strong id="b10469421112910"><a name="b10469421112910"></a><a name="b10469421112910"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row3787mcpsimp"><td class="cellrowborder" valign="top" width="16%" headers="mcps1.2.4.1.1 "><p id="p3789mcpsimp"><a name="p3789mcpsimp"></a><a name="p3789mcpsimp"></a>mode</p>
</td>
<td class="cellrowborder" valign="top" width="56.99999999999999%" headers="mcps1.2.4.1.2 "><p id="p168830912393"><a name="p168830912393"></a><a name="p168830912393"></a>Indicates the period in which the CPU usage is to be queried. By default, the CPU usage within the last 10 seconds is displayed.</p>
<a name="ul115118371817"></a><a name="ul115118371817"></a><ul id="ul115118371817"><li><strong id="b125115372117"><a name="b125115372117"></a><a name="b125115372117"></a>0</strong>: displays the CPU usage of the system within the last 10 seconds.</li><li><strong id="b105118370110"><a name="b105118370110"></a><a name="b105118370110"></a>1</strong>: displays the CPU usage of the system within the last 1 second.</li><li>Other value: displays the total CPU usage since the system is started.</li></ul>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3794mcpsimp"><a name="p3794mcpsimp"></a><a name="p3794mcpsimp"></a>[0, 0xFFFFFFFF]</p>
</td>
</tr>
<tr id="row3795mcpsimp"><td class="cellrowborder" valign="top" width="16%" headers="mcps1.2.4.1.1 "><p id="p3797mcpsimp"><a name="p3797mcpsimp"></a><a name="p3797mcpsimp"></a>taskID</p>
</td>
<td class="cellrowborder" valign="top" width="56.99999999999999%" headers="mcps1.2.4.1.2 "><p id="p3799mcpsimp"><a name="p3799mcpsimp"></a><a name="p3799mcpsimp"></a>Indicates the task ID.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3802mcpsimp"><a name="p3802mcpsimp"></a><a name="p3802mcpsimp"></a>[0, 0xFFFFFFFF]</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section156611948521"></a>

-   If the parameters are not specified, the CPU usage within the last 10 seconds is displayed.
-   If only the  **mode**  parameter is specified, the CPU usage within the specified period is displayed.
-   If both the  **mode**  and  **taskID**  parameters are specified, the CPU usage of the specified task within the given period is displayed.

## Example<a name="section68501605319"></a>

Enter  **cpup 1 5**.

## Output<a name="section19871522144219"></a>

**Figure  1**  CPU usage<a name="fig1251224812504"></a>  
![](figures/cpu-usage.png "cpu-usage")

