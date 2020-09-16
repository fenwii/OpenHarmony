# display\_gfx.h<a name="EN-US_TOPIC_0000001054598125"></a>

## **Overview**<a name="section1123174810093524"></a>

**Related Modules:**

[Display](display.md)

**Description:**

Declares the driver functions for implementing hardware acceleration. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section760185958093524"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1023170531093524"></a>
<table><thead align="left"><tr id="row1359896850093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1706551451093524"><a name="p1706551451093524"></a><a name="p1706551451093524"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1864837852093524"><a name="p1864837852093524"></a><a name="p1864837852093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row808936824093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p611844677093524"><a name="p611844677093524"></a><a name="p611844677093524"></a><a href="gfxfuncs.md">GfxFuncs</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p367177210093524"><a name="p367177210093524"></a><a name="p367177210093524"></a>Defines pointers to the hardware acceleration driver functions. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1757652777093524"></a>
<table><thead align="left"><tr id="row786632505093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p194028169093524"><a name="p194028169093524"></a><a name="p194028169093524"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p196385697093524"><a name="p196385697093524"></a><a name="p196385697093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1373644688093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p214927290093524"><a name="p214927290093524"></a><a name="p214927290093524"></a><a href="display.md#ga251580eb0614b601ef2c901c722a59d3">GfxInitialize</a> (<a href="gfxfuncs.md">GfxFuncs</a> **funcs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p8785221093524"><a name="p8785221093524"></a><a name="p8785221093524"></a>int32_t </p>
<p id="p628494205093524"><a name="p628494205093524"></a><a name="p628494205093524"></a>Initializes the hardware acceleration module to obtain the pointer to functions for hardware acceleration operations. </p>
</td>
</tr>
<tr id="row768420985093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p693311414093524"><a name="p693311414093524"></a><a name="p693311414093524"></a><a href="display.md#ga32595139adb26cfaacf709661b29b347">GfxUninitialize</a> (<a href="gfxfuncs.md">GfxFuncs</a> *funcs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1887319559093524"><a name="p1887319559093524"></a><a name="p1887319559093524"></a>int32_t </p>
<p id="p2084723740093524"><a name="p2084723740093524"></a><a name="p2084723740093524"></a>Deinitializes the hardware acceleration module to release the memory allocated to the pointer to functions for hardware acceleration operations. </p>
</td>
</tr>
</tbody>
</table>

