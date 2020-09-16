# sem<a name="EN-US_TOPIC_0000001052810290"></a>

## Command Function<a name="section366714216619"></a>

This command is used to query information about kernel semaphores.

## Syntax<a name="section8833164614615"></a>

sem \[_ID__ / fulldata_\]

## Parameter Description<a name="section12809111019453"></a>

**Table  1**  Parameters

<a name="table438mcpsimp"></a>
<table><thead align="left"><tr id="row444mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p446mcpsimp"><a name="p446mcpsimp"></a><a name="p446mcpsimp"></a><strong id="b1111222772019"><a name="b1111222772019"></a><a name="b1111222772019"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p448mcpsimp"><a name="p448mcpsimp"></a><a name="p448mcpsimp"></a><strong id="b84871307209"><a name="b84871307209"></a><a name="b84871307209"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p450mcpsimp"><a name="p450mcpsimp"></a><a name="p450mcpsimp"></a><strong id="b101742225281"><a name="b101742225281"></a><a name="b101742225281"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row451mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p453mcpsimp"><a name="p453mcpsimp"></a><a name="p453mcpsimp"></a>ID</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p455mcpsimp"><a name="p455mcpsimp"></a><a name="p455mcpsimp"></a>Indicates the semaphore ID.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p457mcpsimp"><a name="p457mcpsimp"></a><a name="p457mcpsimp"></a>[0, 0xFFFFFFFF]</p>
</td>
</tr>
<tr id="row458mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p460mcpsimp"><a name="p460mcpsimp"></a><a name="p460mcpsimp"></a>fulldata</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p462mcpsimp"><a name="p462mcpsimp"></a><a name="p462mcpsimp"></a>Queries information about all the semaphores in use. The information to be printed includes <strong id="b20538161115251"><a name="b20538161115251"></a><a name="b20538161115251"></a>SemID</strong>, <strong id="b18465101411257"><a name="b18465101411257"></a><a name="b18465101411257"></a>Count</strong>, <strong id="b11825131802514"><a name="b11825131802514"></a><a name="b11825131802514"></a>OriginalCount</strong>, <strong id="b626012213257"><a name="b626012213257"></a><a name="b626012213257"></a>Creater(TaskEntry)</strong>, and <strong id="b1176182715258"><a name="b1176182715258"></a><a name="b1176182715258"></a>LastAccessTime</strong>.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="entry464mcpsimpp0"><a name="entry464mcpsimpp0"></a><a name="entry464mcpsimpp0"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section15935131220717"></a>

-   If the parameters are not specified, this command displays the number of used semaphores and the total number of semaphores.
-   If the  **ID**  parameter is specified, semaphores of the specified ID are displayed.
-   The  **fulldata**  parameter depends on  **LOSCFG\_DEBUG\_SEMAPHORE**. Before specifying the  **fulldata**  parameter, enable the  **Enable Semaphore Debugging**  configuration item using  **menuconfig**.

    Debug  ---\> Enable a Debug Version ---\> Enable Debug LiteOS Kernel Resource ---\> Enable Semaphore Debugging


## Example<a name="section79281818476"></a>

Example 1: Enter  **sem fulldata**.

## Output<a name="section1975118519456"></a>

**Figure  1**  Querying information about all semaphores in use<a name="fig18750181620222"></a>  
![](figures/querying-information-about-all-semaphores-in-use.png "querying-information-about-all-semaphores-in-use")

**Table  2**  Output description

<a name="table487mcpsimp"></a>
<table><thead align="left"><tr id="row492mcpsimp"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p494mcpsimp"><a name="p494mcpsimp"></a><a name="p494mcpsimp"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p496mcpsimp"><a name="p496mcpsimp"></a><a name="p496mcpsimp"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row497mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p499mcpsimp"><a name="p499mcpsimp"></a><a name="p499mcpsimp"></a>SemID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p501mcpsimp"><a name="p501mcpsimp"></a><a name="p501mcpsimp"></a>Indicates the semaphore ID.</p>
</td>
</tr>
<tr id="row502mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p504mcpsimp"><a name="p504mcpsimp"></a><a name="p504mcpsimp"></a>Count</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p506mcpsimp"><a name="p506mcpsimp"></a><a name="p506mcpsimp"></a>Indicates the number of used semaphores.</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **NOTE:** 
>-   The  **ID**  value can be in decimal or hexadecimal format.
>-   When the  **ID**  value is within the range of \[0, 1023\], semaphore information of the specified ID is displayed. If the semaphore ID is not used, a message is displayed to inform you of this case. For other values, a message is displayed indicating that the input parameter is incorrect.

