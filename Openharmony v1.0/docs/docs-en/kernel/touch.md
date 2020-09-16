# touch<a name="EN-US_TOPIC_0000001051611542"></a>

## Command Function<a name="section17541924112716"></a>

-   This command is used to create an empty file in a specified directory.
-   If this command is executed to create an existing file, the execution will be successful but the timestamp will not be updated.

## Syntax<a name="section866182711274"></a>

touch \[_filename_\]

## Parameter Description<a name="section268912296270"></a>

**Table  1**  Parameters

<a name="table1635mcpsimp"></a>
<table><thead align="left"><tr id="row1642mcpsimp"><th class="cellrowborder" valign="top" width="20.73%" id="mcps1.2.4.1.1"><p id="p1653mcpsimp"><a name="p1653mcpsimp"></a><a name="p1653mcpsimp"></a><strong id="b132581435193918"><a name="b132581435193918"></a><a name="b132581435193918"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52.44%" id="mcps1.2.4.1.2"><p id="p1655mcpsimp"><a name="p1655mcpsimp"></a><a name="p1655mcpsimp"></a><strong id="b88661537163918"><a name="b88661537163918"></a><a name="b88661537163918"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="26.83%" id="mcps1.2.4.1.3"><p id="p1657mcpsimp"><a name="p1657mcpsimp"></a><a name="p1657mcpsimp"></a><strong id="b164851738193910"><a name="b164851738193910"></a><a name="b164851738193910"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1684mcpsimp"><td class="cellrowborder" valign="top" width="20.73%" headers="mcps1.2.4.1.1 "><p id="p1686mcpsimp"><a name="p1686mcpsimp"></a><a name="p1686mcpsimp"></a>filename</p>
</td>
<td class="cellrowborder" valign="top" width="52.44%" headers="mcps1.2.4.1.2 "><p id="p1688mcpsimp"><a name="p1688mcpsimp"></a><a name="p1688mcpsimp"></a>Indicates the name of the file to be created.</p>
</td>
<td class="cellrowborder" valign="top" width="26.83%" headers="mcps1.2.4.1.3 "><p id="p1690mcpsimp"><a name="p1690mcpsimp"></a><a name="p1690mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section412093332714"></a>

-   The  **touch**  command creates a read-write empty file.
-   The  **touch**  command creates only one file at a time.

    >![](public_sys-resources/icon-notice.gif) **NOTICE:** 
    >If you run the  **touch**  command to create a file in a path storing important system resources, unexpected results such as a system breakdown may occur. For example, if you run the  **touch uartdev-0**  command in the  **/dev**  path, the system may stop responding.


## Example<a name="section414434814354"></a>

Enter  **touch file.c**.

## Output<a name="section1028419515711"></a>

**Figure  1**  Creating  **file.c**<a name="fig188183221532"></a>  
![](figures/creating-file-c.png "creating-file-c")

