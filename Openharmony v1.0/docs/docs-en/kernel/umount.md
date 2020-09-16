# umount<a name="EN-US_TOPIC_0000001051451595"></a>

## Command Function<a name="section365125133520"></a>

This command is used to unmount a specified file system.

## Syntax<a name="section9615254123512"></a>

umount \[_dir_\]

## Parameter Description<a name="section63446577355"></a>

**Table  1**  Parameters

<a name="table1713mcpsimp"></a>
<table><thead align="left"><tr id="row1719mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p1721mcpsimp"><a name="p1721mcpsimp"></a><a name="p1721mcpsimp"></a><strong id="b18608121184416"><a name="b18608121184416"></a><a name="b18608121184416"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p1723mcpsimp"><a name="p1723mcpsimp"></a><a name="p1723mcpsimp"></a><strong id="b123794114417"><a name="b123794114417"></a><a name="b123794114417"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p1725mcpsimp"><a name="p1725mcpsimp"></a><a name="p1725mcpsimp"></a><strong id="b8664446440"><a name="b8664446440"></a><a name="b8664446440"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1726mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1728mcpsimp"><a name="p1728mcpsimp"></a><a name="p1728mcpsimp"></a>dir</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1730mcpsimp"><a name="p1730mcpsimp"></a><a name="p1730mcpsimp"></a>Indicates the directory from which the file system is to be unmounted.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1732mcpsimp"><a name="p1732mcpsimp"></a><a name="p1732mcpsimp"></a>Directory to which the file system has been mounted</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section92931509368"></a>

By specifying the  **dir**  parameter in the  **unmount**  command, you can unmount the specified file system from the directory.

## Example<a name="section144311323616"></a>

Enter  **umount /bin1/vs/sd**.

## Output<a name="section360525113611"></a>

Unmounting the file system from  **/bin1/vs/sd**

**Figure  1**  Unmounting result<a name="fig2304134118557"></a>  
![](figures/unmounting-result.png "unmounting-result")

