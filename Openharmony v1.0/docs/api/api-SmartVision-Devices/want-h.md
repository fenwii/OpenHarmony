# want.h<a name="ZH-CN_TOPIC_0000001054799587"></a>

## **Overview**<a name="section1966378519093528"></a>

**Related Modules:**

[AbilityKit](AbilityKit.md)

**Description:**

Declares the structure that provides abstract description of the operation to be performed, including the ability information and the carried data, and functions for setting data in the structure. 

You can use functions provided in this file to specify information about the ability to start.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1112523791093528"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table11835348093528"></a>
<table><thead align="left"><tr id="row642900649093528"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1324983084093528"><a name="p1324983084093528"></a><a name="p1324983084093528"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p613769340093528"><a name="p613769340093528"></a><a name="p613769340093528"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1634031208093528"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2066174009093528"><a name="p2066174009093528"></a><a name="p2066174009093528"></a><a href="Want.md">Want</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1906083816093528"><a name="p1906083816093528"></a><a name="p1906083816093528"></a>Defines the abstract description of an operation, including information about the ability and the extra data to carry. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1610534067093528"></a>
<table><thead align="left"><tr id="row1949411591093528"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p753652029093528"><a name="p753652029093528"></a><a name="p753652029093528"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p649253249093528"><a name="p649253249093528"></a><a name="p649253249093528"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row713626832093528"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1511465948093528"><a name="p1511465948093528"></a><a name="p1511465948093528"></a><a href="AbilityKit.md#ga62ca448e092c81497ffdd1f0b1c56938">ClearWant</a> (<a href="Want.md">Want</a> *want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2038546370093528"><a name="p2038546370093528"></a><a name="p2038546370093528"></a>void&nbsp;</p>
<p id="p177132328093528"><a name="p177132328093528"></a><a name="p177132328093528"></a>Clears the memory of a specified <strong id="b1323142701093528"><a name="b1323142701093528"></a><a name="b1323142701093528"></a><a href="Want.md">Want</a></strong> object. </p>
</td>
</tr>
<tr id="row1878033273093528"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1336388561093528"><a name="p1336388561093528"></a><a name="p1336388561093528"></a><a href="AbilityKit.md#ga65f4d2eab99497e496dcd493bd0d047e">SetWantElement</a> (<a href="Want.md">Want</a> *want, <a href="ElementName.md">ElementName</a> element)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1814493311093528"><a name="p1814493311093528"></a><a name="p1814493311093528"></a>bool&nbsp;</p>
<p id="p1869179729093528"><a name="p1869179729093528"></a><a name="p1869179729093528"></a>Sets the <strong id="b2025441398093528"><a name="b2025441398093528"></a><a name="b2025441398093528"></a>element</strong> variable for a specified <strong id="b1271515273093528"><a name="b1271515273093528"></a><a name="b1271515273093528"></a><a href="Want.md">Want</a></strong> object. </p>
</td>
</tr>
<tr id="row1651537355093528"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2076259577093528"><a name="p2076259577093528"></a><a name="p2076259577093528"></a><a href="AbilityKit.md#ga89a719b5f730bc5fde9f637a5ed630c9">SetWantData</a> (<a href="Want.md">Want</a> *want, const void *data, uint16_t dataLength)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1533105285093528"><a name="p1533105285093528"></a><a name="p1533105285093528"></a>bool&nbsp;</p>
<p id="p2017229025093528"><a name="p2017229025093528"></a><a name="p2017229025093528"></a>Sets data to carry in a specified <strong id="b535717527093528"><a name="b535717527093528"></a><a name="b535717527093528"></a><a href="Want.md">Want</a></strong> object for starting a particular ability. </p>
</td>
</tr>
<tr id="row408465509093528"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p118274325093528"><a name="p118274325093528"></a><a name="p118274325093528"></a><a href="AbilityKit.md#gab8e5fac952fc6407f20cd9b7185d3a65">SetWantSvcIdentity</a> (<a href="Want.md">Want</a> *want, SvcIdentity sid)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p310795849093528"><a name="p310795849093528"></a><a name="p310795849093528"></a>bool&nbsp;</p>
<p id="p1609160887093528"><a name="p1609160887093528"></a><a name="p1609160887093528"></a>Sets the <strong id="b613162487093528"><a name="b613162487093528"></a><a name="b613162487093528"></a>sid</strong> member variable for a specified <strong id="b1007041193093528"><a name="b1007041193093528"></a><a name="b1007041193093528"></a><a href="Want.md">Want</a></strong> object. </p>
</td>
</tr>
<tr id="row238410249093528"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2045438127093528"><a name="p2045438127093528"></a><a name="p2045438127093528"></a><a href="AbilityKit.md#ga31adc60981c10b22d0e9bbdc7126d17c">WantToUri</a> (<a href="Want.md">Want</a> want)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1046589400093528"><a name="p1046589400093528"></a><a name="p1046589400093528"></a>const char *&nbsp;</p>
<p id="p1018371209093528"><a name="p1018371209093528"></a><a name="p1018371209093528"></a>Converts a specified <strong id="b854825587093528"><a name="b854825587093528"></a><a name="b854825587093528"></a><a href="Want.md">Want</a></strong> object into a character string. </p>
</td>
</tr>
<tr id="row430738677093528"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p621822145093528"><a name="p621822145093528"></a><a name="p621822145093528"></a><a href="AbilityKit.md#ga43226d0858faa92e83bea33aaf4b614c">WantParseUri</a> (const char *uri)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p634980377093528"><a name="p634980377093528"></a><a name="p634980377093528"></a><a href="Want.md">Want</a> *&nbsp;</p>
<p id="p821576415093528"><a name="p821576415093528"></a><a name="p821576415093528"></a>Converts a specified character string into a <strong id="b1256239536093528"><a name="b1256239536093528"></a><a name="b1256239536093528"></a><a href="Want.md">Want</a></strong> object. </p>
</td>
</tr>
</tbody>
</table>

