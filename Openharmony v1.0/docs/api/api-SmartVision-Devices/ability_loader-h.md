# ability\_loader.h<a name="ZH-CN_TOPIC_0000001055678052"></a>

## **Overview**<a name="section1407457396093524"></a>

**Related Modules:**

[AbilityKit](AbilityKit.md)

**Description:**

Declares functions for registering the class names of  **Ability**  and  **AbilitySlice**  with the ability management framework. 

After creating your own  **Ability**  and  **AbilitySlice**  child classes, you should register their class names with the ability management framework so that the application can start  **Ability**  instances created in the background.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1806722486093524"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table879877609093524"></a>
<table><thead align="left"><tr id="row881221322093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1499130424093524"><a name="p1499130424093524"></a><a name="p1499130424093524"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p13583890093524"><a name="p13583890093524"></a><a name="p13583890093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1006031050093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p484223976093524"><a name="p484223976093524"></a><a name="p484223976093524"></a><a href="OHOS-AbilityLoader.md">OHOS::AbilityLoader</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1547286898093524"><a name="p1547286898093524"></a><a name="p1547286898093524"></a>Declares functions for registering the class names of <a href="OHOS-Ability.md">Ability</a> and <a href="OHOS-AbilitySlice.md">AbilitySlice</a> with the ability management framework. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table721116483093524"></a>
<table><thead align="left"><tr id="row772852315093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p398447470093524"><a name="p398447470093524"></a><a name="p398447470093524"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p294798191093524"><a name="p294798191093524"></a><a name="p294798191093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row37520221093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p123407550093524"><a name="p123407550093524"></a><a name="p123407550093524"></a><a href="AbilityKit.md#ga2c5bd891b502a92f937ae4bff3f80cad">REGISTER_AA</a>(className)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1479464248093524"><a name="p1479464248093524"></a><a name="p1479464248093524"></a>Registers the class name of an <strong id="b252917959093524"><a name="b252917959093524"></a><a name="b252917959093524"></a>Ability</strong> child class. </p>
</td>
</tr>
<tr id="row1847719165093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1573214227093524"><a name="p1573214227093524"></a><a name="p1573214227093524"></a><a href="AbilityKit.md#ga8e811999b2b7780e67cb746d045ab5b8">REGISTER_AS</a>(className)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p476228238093524"><a name="p476228238093524"></a><a name="p476228238093524"></a>Registers the class name of an <strong id="b389525011093524"><a name="b389525011093524"></a><a name="b389525011093524"></a>AbilitySlice</strong> child class. </p>
</td>
</tr>
</tbody>
</table>

