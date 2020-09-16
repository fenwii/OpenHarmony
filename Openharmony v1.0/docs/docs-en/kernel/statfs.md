# statfs<a name="EN-US_TOPIC_0000001052810294"></a>

## Command Function<a name="section153921657152613"></a>

This command is used to print information about a file system, such as the type, total size, and available size.

## Syntax<a name="section135391102717"></a>

statfs \[_directory_\]

## Parameter Description<a name="section074312314279"></a>

**Table  1**  Parameters

<a name="table1597mcpsimp"></a>
<table><thead align="left"><tr id="row1603mcpsimp"><th class="cellrowborder" valign="top" width="33.33333333333333%" id="mcps1.2.4.1.1"><p id="p1605mcpsimp"><a name="p1605mcpsimp"></a><a name="p1605mcpsimp"></a><strong id="b156942710240"><a name="b156942710240"></a><a name="b156942710240"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="33.33333333333333%" id="mcps1.2.4.1.2"><p id="p1607mcpsimp"><a name="p1607mcpsimp"></a><a name="p1607mcpsimp"></a><strong id="b1759110293240"><a name="b1759110293240"></a><a name="b1759110293240"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="33.33333333333333%" id="mcps1.2.4.1.3"><p id="p1609mcpsimp"><a name="p1609mcpsimp"></a><a name="p1609mcpsimp"></a><strong id="b10264183019242"><a name="b10264183019242"></a><a name="b10264183019242"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1610mcpsimp"><td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.1 "><p id="p1612mcpsimp"><a name="p1612mcpsimp"></a><a name="p1612mcpsimp"></a>directory</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.2 "><p id="p1615mcpsimp"><a name="p1615mcpsimp"></a><a name="p1615mcpsimp"></a>Indicates the file system directory.</p>
</td>
<td class="cellrowborder" valign="top" width="33.33333333333333%" headers="mcps1.2.4.1.3 "><p id="p1617mcpsimp"><a name="p1617mcpsimp"></a><a name="p1617mcpsimp"></a>The file system must exist and support the <strong id="b1635148125717"><a name="b1635148125717"></a><a name="b1635148125717"></a>statfs</strong> command. Currently, the following file systems are supported: JFFS2, FAT, and NFS.</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section133816772712"></a>

The printed information varies depending on the file system.

## Example<a name="section526149182717"></a>

The following uses the NFS file system as an example:

Enter  **statfs /nfs**.

**Figure  1**  Output of the statfs command<a name="fig1810654276"></a>  
![](figures/output-of-the-statfs-command.png "output-of-the-statfs-command")

