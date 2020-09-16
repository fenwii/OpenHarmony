# chgrp<a name="EN-US_TOPIC_0000001052370297"></a>

## Command Function<a name="section6103119161418"></a>

This command is used to change a file group.

## Syntax<a name="section186958132141"></a>

chgrp \[_group_\] \[_pathname_\]

## Parameter Description<a name="section81796174141"></a>

**Table  1**  Parameters

<a name="table1049mcpsimp"></a>
<table><thead align="left"><tr id="row1055mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p1057mcpsimp"><a name="p1057mcpsimp"></a><a name="p1057mcpsimp"></a><strong id="b152503343511626"><a name="b152503343511626"></a><a name="b152503343511626"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p1059mcpsimp"><a name="p1059mcpsimp"></a><a name="p1059mcpsimp"></a><strong id="b14728419275"><a name="b14728419275"></a><a name="b14728419275"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p1061mcpsimp"><a name="p1061mcpsimp"></a><a name="p1061mcpsimp"></a><strong id="b71533702411626"><a name="b71533702411626"></a><a name="b71533702411626"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1062mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1064mcpsimp"><a name="p1064mcpsimp"></a><a name="p1064mcpsimp"></a>group</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1066mcpsimp"><a name="p1066mcpsimp"></a><a name="p1066mcpsimp"></a>Indicates the file group.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1068mcpsimp"><a name="p1068mcpsimp"></a><a name="p1068mcpsimp"></a>[0, 0xFFFFFFFF]</p>
</td>
</tr>
<tr id="row172161126124218"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p12217026154215"><a name="p12217026154215"></a><a name="p12217026154215"></a>pathname</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p4218826194210"><a name="p4218826194210"></a><a name="p4218826194210"></a>Indicates the file path.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p182181026104214"><a name="p182181026104214"></a><a name="p182181026104214"></a>An existing file</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section14330152417140"></a>

By specifying a file group before the file name in this command, you can change the group to which the file belongs.

## Example<a name="section951823119149"></a>

Enter  **chgrp 100 hello-harmony.txt**.

## Output<a name="section14271133125715"></a>

**Figure  1**  Changing the group of the  **hello-harmony.txt**  file to  **100**<a name="fig17908710194919"></a>  
![](figures/changing-the-group-of-the-hello-harmony-txt-file-to-100.png "changing-the-group-of-the-hello-harmony-txt-file-to-100")

