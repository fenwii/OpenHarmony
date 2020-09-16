# display\_gralloc.h<a name="ZH-CN_TOPIC_0000001054918119"></a>

## **Overview**<a name="section188009000093524"></a>

**Related Modules:**

[Display](Display.md)

**Description:**

Declares the driver functions for memory. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1070136579093524"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table222091418093524"></a>
<table><thead align="left"><tr id="row1277375738093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1899833231093524"><a name="p1899833231093524"></a><a name="p1899833231093524"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1117816771093524"><a name="p1117816771093524"></a><a name="p1117816771093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row82386209093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1444302344093524"><a name="p1444302344093524"></a><a name="p1444302344093524"></a><a href="GrallocFuncs.md">GrallocFuncs</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p59746773093524"><a name="p59746773093524"></a><a name="p59746773093524"></a>Defines pointers to the memory driver functions. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table399585054093524"></a>
<table><thead align="left"><tr id="row349153863093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1238362651093524"><a name="p1238362651093524"></a><a name="p1238362651093524"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1546825885093524"><a name="p1546825885093524"></a><a name="p1546825885093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row598719486093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1489526944093524"><a name="p1489526944093524"></a><a name="p1489526944093524"></a><a href="Display.md#ga304347c32a67bf7b20ef5d2b5714e5fa">GrallocInitialize</a> (<a href="GrallocFuncs.md">GrallocFuncs</a> **funcs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p256045231093524"><a name="p256045231093524"></a><a name="p256045231093524"></a>int32_t&nbsp;</p>
<p id="p593927137093524"><a name="p593927137093524"></a><a name="p593927137093524"></a>Initializes the memory module to obtain the pointer to functions for memory operations. </p>
</td>
</tr>
<tr id="row454310873093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2058431726093524"><a name="p2058431726093524"></a><a name="p2058431726093524"></a><a href="Display.md#ga8842b25f91c247606048ab2d5cdb338f">GrallocUninitialize</a> (<a href="GrallocFuncs.md">GrallocFuncs</a> *funcs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p436348574093524"><a name="p436348574093524"></a><a name="p436348574093524"></a>int32_t&nbsp;</p>
<p id="p674246264093524"><a name="p674246264093524"></a><a name="p674246264093524"></a>Deinitializes the memory module to release the memory allocated to the pointer to functions for memory operations. </p>
</td>
</tr>
</tbody>
</table>

