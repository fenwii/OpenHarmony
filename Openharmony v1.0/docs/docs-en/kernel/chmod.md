# chmod<a name="EN-US_TOPIC_0000001052170278"></a>

## Command Function<a name="section13992936121418"></a>

This command is used to change the file operation permission.

## Syntax<a name="section63342439147"></a>

chmod \[_mode_\] \[_pathname_\]

## Parameter Description<a name="section894414671411"></a>

**Table  1**  Parameters

<a name="table1049mcpsimp"></a>
<table><thead align="left"><tr id="row1055mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p1057mcpsimp"><a name="p1057mcpsimp"></a><a name="p1057mcpsimp"></a><strong id="b144816543511718"><a name="b144816543511718"></a><a name="b144816543511718"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p1059mcpsimp"><a name="p1059mcpsimp"></a><a name="p1059mcpsimp"></a><strong id="b1544627143010"><a name="b1544627143010"></a><a name="b1544627143010"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p1061mcpsimp"><a name="p1061mcpsimp"></a><a name="p1061mcpsimp"></a><strong id="b44030524511718"><a name="b44030524511718"></a><a name="b44030524511718"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1062mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1064mcpsimp"><a name="p1064mcpsimp"></a><a name="p1064mcpsimp"></a>mode</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p13519122819294"><a name="p13519122819294"></a><a name="p13519122819294"></a>Indicates the permission for a file or directory. The value is an octal number, representing the permission of <strong id="b11602834153114"><a name="b11602834153114"></a><a name="b11602834153114"></a>User</strong> (owner), <strong id="b032113853120"><a name="b032113853120"></a><a name="b032113853120"></a>Group</strong> (group), or <strong id="b1980114418310"><a name="b1980114418310"></a><a name="b1980114418310"></a>Other</strong> (other groups).</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p182181026104214"><a name="p182181026104214"></a><a name="p182181026104214"></a>[0, 777]</p>
</td>
</tr>
<tr id="row172161126124218"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p12217026154215"><a name="p12217026154215"></a><a name="p12217026154215"></a>pathname</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p4218826194210"><a name="p4218826194210"></a><a name="p4218826194210"></a>Indicates the file path.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p13872195215290"><a name="p13872195215290"></a><a name="p13872195215290"></a>An existing file</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section182415221419"></a>

By specifying the  **mode**  parameter before the file name, you can change the permission for this file.

## Example<a name="section8518195718147"></a>

Enter  **chmod 666 hello-harmony.txt**.

## Output<a name="section127391818158"></a>

**Figure  1**  Changing the permission on the  **hello-harmony.txt**  file to  **666**<a name="fig501223144912"></a>  
![](figures/changing-the-permission-on-the-hello-harmony-txt-file-to-666.png "changing-the-permission-on-the-hello-harmony-txt-file-to-666")

