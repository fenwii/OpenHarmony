# display\_layer.h<a name="ZH-CN_TOPIC_0000001054718091"></a>

## **Overview**<a name="section113061926093524"></a>

**Related Modules:**

[Display](Display.md)

**Description:**

Declares the driver functions for implementing layer operations. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1373895787093524"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table726570929093524"></a>
<table><thead align="left"><tr id="row153368926093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p252552433093524"><a name="p252552433093524"></a><a name="p252552433093524"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1922770767093524"><a name="p1922770767093524"></a><a name="p1922770767093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row157037025093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p737300598093524"><a name="p737300598093524"></a><a name="p737300598093524"></a><a href="LayerFuncs.md">LayerFuncs</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1101921298093524"><a name="p1101921298093524"></a><a name="p1101921298093524"></a>Defines pointers to the layer driver functions. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table155157046093524"></a>
<table><thead align="left"><tr id="row1980471608093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2082517237093524"><a name="p2082517237093524"></a><a name="p2082517237093524"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p539357339093524"><a name="p539357339093524"></a><a name="p539357339093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row934946557093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1001903378093524"><a name="p1001903378093524"></a><a name="p1001903378093524"></a><a href="Display.md#ga061e587306a5d0367ff228d64434c05d">LayerInitialize</a> (<a href="LayerFuncs.md">LayerFuncs</a> **funcs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p880211728093524"><a name="p880211728093524"></a><a name="p880211728093524"></a>int32_t&nbsp;</p>
<p id="p392734025093524"><a name="p392734025093524"></a><a name="p392734025093524"></a>Initializes the layer to apply for resources used by the layer and obtain the pointer to functions for layer operations. </p>
</td>
</tr>
<tr id="row464166746093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2006620035093524"><a name="p2006620035093524"></a><a name="p2006620035093524"></a><a href="Display.md#ga4e32b1a65cf243a9ac015b632a4eea0b">LayerUninitialize</a> (<a href="LayerFuncs.md">LayerFuncs</a> *funcs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2010988724093524"><a name="p2010988724093524"></a><a name="p2010988724093524"></a>int32_t&nbsp;</p>
<p id="p1401999149093524"><a name="p1401999149093524"></a><a name="p1401999149093524"></a>Deinitializes the layer module to release the memory allocated to the pointer to functions for layer operations. </p>
</td>
</tr>
</tbody>
</table>

