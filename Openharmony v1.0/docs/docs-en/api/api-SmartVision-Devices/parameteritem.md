# ParameterItem<a name="EN-US_TOPIC_0000001054799635"></a>

## **Overview**<a name="section656493946084841"></a>

**Related Modules:**

[Format](format.md)

**Description:**

Defines a structure for configuring and obtaining dynamic parameters. 

## **Summary**<a name="section1318280446084841"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table982081186084841"></a>
<table><thead align="left"><tr id="row728678639084841"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1388930400084841"><a name="p1388930400084841"></a><a name="p1388930400084841"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p570348048084841"><a name="p570348048084841"></a><a name="p570348048084841"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1127790613084841"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p102699915084841"><a name="p102699915084841"></a><a name="p102699915084841"></a><a href="parameteritem.md#a7fd3dd0c0ddbf9e4cf04d214fae1a857">key</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p999242365084841"><a name="p999242365084841"></a><a name="p999242365084841"></a>uint32_t </p>
</td>
</tr>
<tr id="row1243347874084841"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1526017954084841"><a name="p1526017954084841"></a><a name="p1526017954084841"></a><a href="parameteritem.md#ad708dec0457cddcc56f1955f80ea2dfe">size</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p431414726084841"><a name="p431414726084841"></a><a name="p431414726084841"></a>int32_t </p>
</td>
</tr>
<tr id="row364452827084841"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1002089515084841"><a name="p1002089515084841"></a><a name="p1002089515084841"></a><em id="a83a7f9de38060f001ba350c2e64c537e"><a name="a83a7f9de38060f001ba350c2e64c537e"></a><a name="a83a7f9de38060f001ba350c2e64c537e"></a></em></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p716604458084841"><a name="p716604458084841"></a><a name="p716604458084841"></a><strong id="b823853223"><a name="b823853223"></a><a name="b823853223"></a></strong> union {</p>
</td>
</tr>
<tr id="row1285176023084841"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p849805100084841"><a name="p849805100084841"></a><a name="p849805100084841"></a>   int32_t   <a href="parameteritem.md#a67b4403be08a141554d8974be14c9ec4">s32Value</a></p>
</td>
</tr>
<tr id="row107209938084841"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p370983548084841"><a name="p370983548084841"></a><a name="p370983548084841"></a>   uint32_t   <a href="parameteritem.md#a20cbcbc7418ac8d885418d09a4041e00">u32Value</a></p>
</td>
</tr>
<tr id="row39893835084841"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2137573273084841"><a name="p2137573273084841"></a><a name="p2137573273084841"></a>   int64_t   <a href="parameteritem.md#af7566b817d49b505e9a3f25be6feafe3">s64Value</a></p>
</td>
</tr>
<tr id="row76366062084841"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p179446130084841"><a name="p179446130084841"></a><a name="p179446130084841"></a>   uint64_t   <a href="parameteritem.md#a4f04b2e5166d5e39142a16b6a1ae2392">u64Value</a></p>
</td>
</tr>
<tr id="row1153258608084841"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p146391305084841"><a name="p146391305084841"></a><a name="p146391305084841"></a>   float   <a href="parameteritem.md#ae6d56dc8bd3f5a206fdd085ce65a9e33">fValue</a></p>
</td>
</tr>
<tr id="row1556099049084841"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p20975611084841"><a name="p20975611084841"></a><a name="p20975611084841"></a>   double   <a href="parameteritem.md#af4be109572705fcd01778c2af5ad1868">dValue</a></p>
</td>
</tr>
<tr id="row883463666084841"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p449346122084841"><a name="p449346122084841"></a><a name="p449346122084841"></a>   const void *   <a href="parameteritem.md#a7bd2066c1aa644f4cd7a88a4fa0f9776">pValue</a></p>
</td>
</tr>
<tr id="row1659543651084841"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1727353908084841"><a name="p1727353908084841"></a><a name="p1727353908084841"></a><em id="i1319419059"><a name="i1319419059"></a><a name="i1319419059"></a></em>value </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p252925809084841"><a name="p252925809084841"></a><a name="p252925809084841"></a>} </p>
<p id="p1243062238084841"><a name="p1243062238084841"></a><a name="p1243062238084841"></a>Defines value types of the parameters. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1128522066084841"></a>

## **Field Documentation**<a name="section847585637084841"></a>

## dValue<a name="af4be109572705fcd01778c2af5ad1868"></a>

```
double ParameterItem::dValue
```

 **Description:**

Double-precision floating point number 

## fValue<a name="ae6d56dc8bd3f5a206fdd085ce65a9e33"></a>

```
float ParameterItem::fValue
```

 **Description:**

Single-precision floating point number 

## key<a name="a7fd3dd0c0ddbf9e4cf04d214fae1a857"></a>

```
uint32_t ParameterItem::key
```

 **Description:**

Key type. For details, see  [KeyType](format.md#gaab0feaba617470cb4aa830dc5935238c) 

## pValue<a name="a7bd2066c1aa644f4cd7a88a4fa0f9776"></a>

```
const void* ParameterItem::pValue
```

 **Description:**

Pointer 

## s32Value<a name="a67b4403be08a141554d8974be14c9ec4"></a>

```
int32_t ParameterItem::s32Value
```

 **Description:**

32-bit integer 

## s64Value<a name="af7566b817d49b505e9a3f25be6feafe3"></a>

```
int64_t ParameterItem::s64Value
```

 **Description:**

64-bit integer 

## size<a name="ad708dec0457cddcc56f1955f80ea2dfe"></a>

```
int32_t ParameterItem::size
```

 **Description:**

Data size, which indicates the size of the buffer memory pointed by  **pValue** 

## u32Value<a name="a20cbcbc7418ac8d885418d09a4041e00"></a>

```
uint32_t ParameterItem::u32Value
```

 **Description:**

32-bit unsigned integer 

## u64Value<a name="a4f04b2e5166d5e39142a16b6a1ae2392"></a>

```
uint64_t ParameterItem::u64Value
```

 **Description:**

64-bit unsigned integer 

