# graphic\_math.h<a name="EN-US_TOPIC_0000001054879500"></a>

## **Overview**<a name="section110260599093525"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines mathematical operation functions and types, including trigonometric functions, two-dimensional vectors, three-dimensional vectors, and matrices. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section660969732093525"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table194026780093525"></a>
<table><thead align="left"><tr id="row624151140093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p706334282093525"><a name="p706334282093525"></a><a name="p706334282093525"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p532255134093525"><a name="p532255134093525"></a><a name="p532255134093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row478338079093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p128423598093525"><a name="p128423598093525"></a><a name="p128423598093525"></a><a href="ohos-vector2-t.md">OHOS::Vector2&lt; T &gt;</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p321309070093525"><a name="p321309070093525"></a><a name="p321309070093525"></a>Defines the two-dimensional vector, and provides basic mathematical operations such as vector assignment, scalar product, cross product, addition, and subtraction. </p>
</td>
</tr>
<tr id="row816914240093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p612840969093525"><a name="p612840969093525"></a><a name="p612840969093525"></a><a href="ohos-vector3-t.md">OHOS::Vector3&lt; T &gt;</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1482858357093525"><a name="p1482858357093525"></a><a name="p1482858357093525"></a>Defines the 3-dimensional vector, and provides basic operators such as [] and ==. </p>
</td>
</tr>
<tr id="row943707529093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p702070756093525"><a name="p702070756093525"></a><a name="p702070756093525"></a><a href="ohos-matrix3-t.md">OHOS::Matrix3&lt; T &gt;</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p131697398093525"><a name="p131697398093525"></a><a name="p131697398093525"></a>Defines a 3 x 3 matrix. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1727381616093525"></a>
<table><thead align="left"><tr id="row389229656093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1631740361093525"><a name="p1631740361093525"></a><a name="p1631740361093525"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p503944064093525"><a name="p503944064093525"></a><a name="p503944064093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row535488027093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p509873420093525"><a name="p509873420093525"></a><a name="p509873420093525"></a><a href="graphic.md#ga3e18a38ff2f4dbf813d85d14ae7cc7f6">MATH_MAX</a>(a, b)   ((a) &gt; (b) ? (a) : (b))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1408728007093525"><a name="p1408728007093525"></a><a name="p1408728007093525"></a>Larger of a and b. </p>
</td>
</tr>
<tr id="row450062810093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1312815711093525"><a name="p1312815711093525"></a><a name="p1312815711093525"></a><a href="graphic.md#ga0707ec809a1938e6b07386ce8e403313">MATH_MIN</a>(a, b)   ((a) &lt; (b) ? (a) : (b))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1248916696093525"><a name="p1248916696093525"></a><a name="p1248916696093525"></a>Smaller of a and b. </p>
</td>
</tr>
<tr id="row884684959093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p237749312093525"><a name="p237749312093525"></a><a name="p237749312093525"></a><a href="graphic.md#ga1336a0214be7acc7fb308f2f88542e39">MATH_ABS</a>(x)   ((x) &gt; 0 ? (x) : (-(x)))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1153866147093525"><a name="p1153866147093525"></a><a name="p1153866147093525"></a>Absolute value of x. </p>
</td>
</tr>
<tr id="row1266267053093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p51523618093525"><a name="p51523618093525"></a><a name="p51523618093525"></a><a href="graphic.md#ga16f420abdb8bee5c5323d203fa1ca43b">MATH_MINUS</a>(a, b)   ((a) &lt; (b) ? ((b) - (a)) : ((a) - (b)))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p259006608093525"><a name="p259006608093525"></a><a name="p259006608093525"></a>Difference between a and b. </p>
</td>
</tr>
</tbody>
</table>

