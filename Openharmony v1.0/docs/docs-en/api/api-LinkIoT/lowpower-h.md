# lowpower.h<a name="EN-US_TOPIC_0000001055515020"></a>

## **Overview**<a name="section1869520665191849"></a>

**Related Modules:**

[Power](power.md)

**Description:**

Sets low power consumption for the device. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section169206093191849"></a>

## Enumerations<a name="enum-members"></a>

<a name="table676306712191849"></a>
<table><thead align="left"><tr id="row1475797647191849"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p275506765191849"><a name="p275506765191849"></a><a name="p275506765191849"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1430326347191849"><a name="p1430326347191849"></a><a name="p1430326347191849"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1765382937191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p272459864191849"><a name="p272459864191849"></a><a name="p272459864191849"></a><a href="power.md#gaa6139ca73fa81742134fe74345ccb748">LpcType</a> { <a href="power.md#ggaa6139ca73fa81742134fe74345ccb748a79dbeab2cc1e9d820df3b261984ffdf9">NO_SLEEP</a>, <a href="power.md#ggaa6139ca73fa81742134fe74345ccb748a84d5857ff1535c751c3b15fea913ae40">LIGHT_SLEEP</a>, <a href="power.md#ggaa6139ca73fa81742134fe74345ccb748a3c282494db59c58249a6b608e20050bf">DEEP_SLEEP</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1443940612191849"><a name="p1443940612191849"></a><a name="p1443940612191849"></a>Enumerates low power consumption modes. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1310274830191849"></a>
<table><thead align="left"><tr id="row1022035574191849"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p647657277191849"><a name="p647657277191849"></a><a name="p647657277191849"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1341006982191849"><a name="p1341006982191849"></a><a name="p1341006982191849"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1027022897191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2106300157191849"><a name="p2106300157191849"></a><a name="p2106300157191849"></a><a href="power.md#gac4363d7384c17fd7dcc0b70b432ca750">LpcInit</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2074763651191849"><a name="p2074763651191849"></a><a name="p2074763651191849"></a>unsigned int </p>
<p id="p1570402203191849"><a name="p1570402203191849"></a><a name="p1570402203191849"></a>Initializes low power consumption. </p>
</td>
</tr>
<tr id="row435349728191849"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1130333949191849"><a name="p1130333949191849"></a><a name="p1130333949191849"></a><a href="power.md#ga6a7b9016d6742e82a044369b3f960554">LpcSetType</a> (<a href="power.md#gaa6139ca73fa81742134fe74345ccb748">LpcType</a> type)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p37707211191849"><a name="p37707211191849"></a><a name="p37707211191849"></a>unsigned int </p>
<p id="p1762275115191849"><a name="p1762275115191849"></a><a name="p1762275115191849"></a>Sets low power consumption for the device. </p>
</td>
</tr>
</tbody>
</table>

