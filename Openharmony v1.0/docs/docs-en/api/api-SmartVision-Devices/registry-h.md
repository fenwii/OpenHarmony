# registry.h<a name="EN-US_TOPIC_0000001055039494"></a>

## **Overview**<a name="section1750823703093527"></a>

**Related Modules:**

[Registry](registry.md)

**Description:**

Provides basic APIs for remote service registration and discovery. 

APIs provided by this file include the factory registration function of the client code. This file is used when there are customized client objects. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section57142229093527"></a>

## Typedefs<a name="typedef-members"></a>

<a name="table1579802673093527"></a>
<table><thead align="left"><tr id="row1532636330093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p897708944093527"><a name="p897708944093527"></a><a name="p897708944093527"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1448794068093527"><a name="p1448794068093527"></a><a name="p1448794068093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1275950893093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1292551469093527"><a name="p1292551469093527"></a><a name="p1292551469093527"></a><a href="registry.md#ga0c8aa2ef9883bd97b4f1309895adaa4c">Creator</a>) (const char *service, const char *feature, uint32 size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1346593584093527"><a name="p1346593584093527"></a><a name="p1346593584093527"></a>typedef void *(* </p>
<p id="p1203244515093527"><a name="p1203244515093527"></a><a name="p1203244515093527"></a>Indicates the creator of the customized client proxy. </p>
</td>
</tr>
<tr id="row2091055333093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1543371174093527"><a name="p1543371174093527"></a><a name="p1543371174093527"></a><a href="registry.md#ga1e6298b1246357f70ad0b581e0eb9305">Destroyer</a>) (const char *service, const char *feature, void *iproxy)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p122232638093527"><a name="p122232638093527"></a><a name="p122232638093527"></a>typedef void(* </p>
<p id="p1192528488093527"><a name="p1192528488093527"></a><a name="p1192528488093527"></a>Indicates the destroyer of the customized client proxy. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table294292615093527"></a>
<table><thead align="left"><tr id="row1788642989093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p718015609093527"><a name="p718015609093527"></a><a name="p718015609093527"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p45092534093527"><a name="p45092534093527"></a><a name="p45092534093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2096703007093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p488816527093527"><a name="p488816527093527"></a><a name="p488816527093527"></a><a href="registry.md#ga64797e3f63201c40dbdf21b90cff23d2">SAMGR_RegisterFactory</a> (const char *service, const char *feature, <a href="registry.md#ga0c8aa2ef9883bd97b4f1309895adaa4c">Creator</a> creator, <a href="registry.md#ga1e6298b1246357f70ad0b581e0eb9305">Destroyer</a> destroyer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p207287737093527"><a name="p207287737093527"></a><a name="p207287737093527"></a>int </p>
<p id="p1454260602093527"><a name="p1454260602093527"></a><a name="p1454260602093527"></a>Registers the factory method of the client proxy object with the Samgr. </p>
</td>
</tr>
</tbody>
</table>

