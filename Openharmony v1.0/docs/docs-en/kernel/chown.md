# chown<a name="EN-US_TOPIC_0000001052810292"></a>

## Command Function<a name="section247414691513"></a>

This command is used to change the owner and group of a specified file.

## Syntax<a name="section14773151018159"></a>

chown \[_owner_\] \[_group_\] \[_pathname_\]

## Parameter Description<a name="section598731391517"></a>

**Table  1**  Parameters

<a name="table1049mcpsimp"></a>
<table><thead align="left"><tr id="row1055mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p1057mcpsimp"><a name="p1057mcpsimp"></a><a name="p1057mcpsimp"></a><strong id="b130925344111510"><a name="b130925344111510"></a><a name="b130925344111510"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p1059mcpsimp"><a name="p1059mcpsimp"></a><a name="p1059mcpsimp"></a><strong id="b1226032904716"><a name="b1226032904716"></a><a name="b1226032904716"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p1061mcpsimp"><a name="p1061mcpsimp"></a><a name="p1061mcpsimp"></a><strong id="b34190246311510"><a name="b34190246311510"></a><a name="b34190246311510"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1062mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1064mcpsimp"><a name="p1064mcpsimp"></a><a name="p1064mcpsimp"></a>owner</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p13519122819294"><a name="p13519122819294"></a><a name="p13519122819294"></a>Indicates the file owner.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p182181026104214"><a name="p182181026104214"></a><a name="p182181026104214"></a>[0, 0xFFFFFFFF]</p>
</td>
</tr>
<tr id="row172161126124218"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p68901524203516"><a name="p68901524203516"></a><a name="p68901524203516"></a>group</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1066mcpsimp"><a name="p1066mcpsimp"></a><a name="p1066mcpsimp"></a>Indicates the file group.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><a name="ul10145121994816"></a><a name="ul10145121994816"></a><ul id="ul10145121994816"><li>Left blank</li><li>[0, 0xFFFFFFFF]</li></ul>
</td>
</tr>
<tr id="row10616101153510"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p12217026154215"><a name="p12217026154215"></a><a name="p12217026154215"></a>pathname</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p4218826194210"><a name="p4218826194210"></a><a name="p4218826194210"></a>Indicates the file path.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p13872195215290"><a name="p13872195215290"></a><a name="p13872195215290"></a>An existing file</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section16524152071510"></a>

-   By specifying the  **owner**  and  **group**  parameters in this command, you can change the owner and group of the file.
-   If the  **owner**  or  **group**  value is  **-1**, the owner or group of the file will not be changed.
-   The  **group**  parameter can be left blank.

## Example<a name="section17901152561510"></a>

Enter  **chown 100 200 hello-harmony.txt**.

## Output<a name="section15513163115816"></a>

**Figure  1**  Changing the owner and group of the hello-harmony.txt file to 100 and 200 respectively<a name="fig518593394920"></a>  
![](figures/changing-the-owner-and-group-of-the-hello-harmony-txt-file-to-100-and-200-respectively.png "changing-the-owner-and-group-of-the-hello-harmony-txt-file-to-100-and-200-respectively")

