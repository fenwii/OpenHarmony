# cd<a name="EN-US_TOPIC_0000001051690313"></a>

## Command Function<a name="section11690184921316"></a>

This command is used to change the current working directory.

## Syntax<a name="section75695409569"></a>

cd \[_path_\]

## Parameter Description<a name="section71961353181311"></a>

**Table  1**  Parameters

<a name="table1087mcpsimp"></a>
<table><thead align="left"><tr id="row1093mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p1095mcpsimp"><a name="p1095mcpsimp"></a><a name="p1095mcpsimp"></a><strong id="b76096875111729"><a name="b76096875111729"></a><a name="b76096875111729"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p1097mcpsimp"><a name="p1097mcpsimp"></a><a name="p1097mcpsimp"></a><strong id="b1343743615221"><a name="b1343743615221"></a><a name="b1343743615221"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p1099mcpsimp"><a name="p1099mcpsimp"></a><a name="p1099mcpsimp"></a><strong id="b163024311311729"><a name="b163024311311729"></a><a name="b163024311311729"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1100mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1102mcpsimp"><a name="p1102mcpsimp"></a><a name="p1102mcpsimp"></a>path</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1104mcpsimp"><a name="p1104mcpsimp"></a><a name="p1104mcpsimp"></a>Indicates the file path.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1106mcpsimp"><a name="p1106mcpsimp"></a><a name="p1106mcpsimp"></a>The user must have the execution (search) permission for the specified directory.</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section3629759111317"></a>

-   If the  **path**  parameter is not specified, the system switches to the root directory.
-   If the  **path**  parameter is specified, the system switches to the specified path.
-   The  **path**  value starting with a slash \(/\) represents the root directory.
-   The  **path**  value starting with a dot \(.\) represents the current directory.
-   The  **path**  value starting with two dots \(..\) represents the parent directory.

## Example<a name="section211620301412"></a>

Enter  **cd ..**.

## Output<a name="section1968117214577"></a>

**Figure  1**  Directory switching result<a name="fig16500959144812"></a>  
![](figures/directory-switching-result.png "directory-switching-result")

