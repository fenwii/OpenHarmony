# su<a name="EN-US_TOPIC_0000001052451605"></a>

## Command Function<a name="section297810431676"></a>

This command is used to switch the user.

## Syntax<a name="section157131147876"></a>

su \[_uid_\] \[_gid_\]

## Parameter Description<a name="section04145521671"></a>

**Table  1**  Parameters

<a name="table1049mcpsimp"></a>
<table><thead align="left"><tr id="row1055mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p1057mcpsimp"><a name="p1057mcpsimp"></a><a name="p1057mcpsimp"></a><strong id="b2054553312209"><a name="b2054553312209"></a><a name="b2054553312209"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="51.93%" id="mcps1.2.4.1.2"><p id="p1059mcpsimp"><a name="p1059mcpsimp"></a><a name="p1059mcpsimp"></a><strong id="b209241335142015"><a name="b209241335142015"></a><a name="b209241335142015"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27.07%" id="mcps1.2.4.1.3"><p id="p1061mcpsimp"><a name="p1061mcpsimp"></a><a name="p1061mcpsimp"></a><strong id="b13675131682811"><a name="b13675131682811"></a><a name="b13675131682811"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1062mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1064mcpsimp"><a name="p1064mcpsimp"></a><a name="p1064mcpsimp"></a>uid</p>
</td>
<td class="cellrowborder" valign="top" width="51.93%" headers="mcps1.2.4.1.2 "><p id="p14138191243"><a name="p14138191243"></a><a name="p14138191243"></a>Indicates the ID of the target user.</p>
</td>
<td class="cellrowborder" valign="top" width="27.07%" headers="mcps1.2.4.1.3 "><a name="ul14151675449"></a><a name="ul14151675449"></a><ul id="ul14151675449"><li>Left blank</li><li>[0, 60000]</li></ul>
</td>
</tr>
<tr id="row172161126124218"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p12217026154215"><a name="p12217026154215"></a><a name="p12217026154215"></a>gid</p>
</td>
<td class="cellrowborder" valign="top" width="51.93%" headers="mcps1.2.4.1.2 "><p id="p48748461789"><a name="p48748461789"></a><a name="p48748461789"></a>Indicates the ID of the target user group.</p>
</td>
<td class="cellrowborder" valign="top" width="27.07%" headers="mcps1.2.4.1.3 "><a name="ul10433713134417"></a><a name="ul10433713134417"></a><ul id="ul10433713134417"><li>Left blank</li><li>[0, 60000]</li></ul>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section14615155610719"></a>

-   The  **su**  command is used to switch to user  **root**  by default. The default value for both  **uid**  and  **gid**  is  **0**.
-   If the  **uid**  and  **gid**  parameters are specified, this command can switch to the user with the specified  **uid**  and  **gid**.
-   If the input parameter is out of the range, an error message is printed.

## Example<a name="section13338150985"></a>

Enter  **su 1000 1000**.

## Output<a name="section125021924194613"></a>

**Figure  1**  Switching to the user whose  **uid**  and  **gid**  are both  **1000**<a name="fig666918538448"></a>  
![](figures/switching-to-the-user-whose-uid-and-gid-are-both-1000.png "switching-to-the-user-whose-uid-and-gid-are-both-1000")

