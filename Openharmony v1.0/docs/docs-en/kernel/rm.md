# rm<a name="EN-US_TOPIC_0000001052370299"></a>

## Command Function<a name="section181141523142613"></a>

This command is used to delete a file or folder.

## Syntax<a name="section8800926132619"></a>

rm \[_-r_\] \[_dirname / filename_\]

## Parameter Description<a name="section15476229152617"></a>

**Table  1**  Parameters

<a name="table1507mcpsimp"></a>
<table><thead align="left"><tr id="row1513mcpsimp"><th class="cellrowborder" valign="top" width="22.220000000000002%" id="mcps1.2.4.1.1"><p id="p1515mcpsimp"><a name="p1515mcpsimp"></a><a name="p1515mcpsimp"></a><strong id="b8231115224817"><a name="b8231115224817"></a><a name="b8231115224817"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="51.519999999999996%" id="mcps1.2.4.1.2"><p id="p1517mcpsimp"><a name="p1517mcpsimp"></a><a name="p1517mcpsimp"></a><strong id="b1599275514488"><a name="b1599275514488"></a><a name="b1599275514488"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="26.26%" id="mcps1.2.4.1.3"><p id="p1519mcpsimp"><a name="p1519mcpsimp"></a><a name="p1519mcpsimp"></a><strong id="b186611453114810"><a name="b186611453114810"></a><a name="b186611453114810"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1520mcpsimp"><td class="cellrowborder" valign="top" width="22.220000000000002%" headers="mcps1.2.4.1.1 "><p id="p1522mcpsimp"><a name="p1522mcpsimp"></a><a name="p1522mcpsimp"></a>-r</p>
</td>
<td class="cellrowborder" valign="top" width="51.519999999999996%" headers="mcps1.2.4.1.2 "><p id="p1524mcpsimp"><a name="p1524mcpsimp"></a><a name="p1524mcpsimp"></a>Deletes a directory. This parameter is optional. It is required if a directory is to be deleted.</p>
</td>
<td class="cellrowborder" valign="top" width="26.26%" headers="mcps1.2.4.1.3 "><p id="p1526mcpsimp"><a name="p1526mcpsimp"></a><a name="p1526mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row1527mcpsimp"><td class="cellrowborder" valign="top" width="22.220000000000002%" headers="mcps1.2.4.1.1 "><p id="p1529mcpsimp"><a name="p1529mcpsimp"></a><a name="p1529mcpsimp"></a>dirname/filename</p>
</td>
<td class="cellrowborder" valign="top" width="51.519999999999996%" headers="mcps1.2.4.1.2 "><p id="p1531mcpsimp"><a name="p1531mcpsimp"></a><a name="p1531mcpsimp"></a>Indicates the name of the file or directory to be deleted. The value can be a path.</p>
</td>
<td class="cellrowborder" valign="top" width="26.26%" headers="mcps1.2.4.1.3 "><p id="p1533mcpsimp"><a name="p1533mcpsimp"></a><a name="p1533mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section10578163215262"></a>

-   The  **rm**  command deletes only one file or directory at a time.
-   The  **rm -r**  command can be used to delete a non-empty directory.

## Example<a name="section18548133511263"></a>

Example:

1.  Enter  **rm log1.txt**.
2.  Enter  **rm -r sd**.

## Output<a name="section1565323814265"></a>

**Figure  1**  Deleting the  **log1.txt**  file<a name="fig886111415523"></a>  
![](figures/deleting-the-log1-txt-file.png "deleting-the-log1-txt-file")

**Figure  2**  Deleting the  **sd**  directory<a name="fig20659194885211"></a>  
![](figures/deleting-the-sd-directory.png "deleting-the-sd-directory")

