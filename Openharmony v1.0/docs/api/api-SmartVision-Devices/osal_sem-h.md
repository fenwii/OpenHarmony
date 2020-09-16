# osal\_sem.h<a name="ZH-CN_TOPIC_0000001054479539"></a>

## **Overview**<a name="section368268633093526"></a>

**Related Modules:**

[OSAL](OSAL.md)

**Description:**

Declares semaphore structures and interfaces. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2143897633093526"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1254984032093526"></a>
<table><thead align="left"><tr id="row141706278093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1638088728093526"><a name="p1638088728093526"></a><a name="p1638088728093526"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1031349596093526"><a name="p1031349596093526"></a><a name="p1031349596093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row359925426093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p800554381093526"><a name="p800554381093526"></a><a name="p800554381093526"></a><a href="OsalSem.md">OsalSem</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1619358017093526"><a name="p1619358017093526"></a><a name="p1619358017093526"></a>Describes a semaphore. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table2060596592093526"></a>
<table><thead align="left"><tr id="row1986520447093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p132164872093526"><a name="p132164872093526"></a><a name="p132164872093526"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p982771753093526"><a name="p982771753093526"></a><a name="p982771753093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1530926999093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p177129044093526"><a name="p177129044093526"></a><a name="p177129044093526"></a><a href="OSAL.md#ga5e37d1f50835b70611517ad96146fc93">OSAL_DECLARE_SEMAPHORE</a>(sem)&nbsp;&nbsp;&nbsp;struct <a href="OsalSem.md">OsalSem</a> sem</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1037949904093526"><a name="p1037949904093526"></a><a name="p1037949904093526"></a>Defines a semaphore. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table263735022093526"></a>
<table><thead align="left"><tr id="row1999581433093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1948319163093526"><a name="p1948319163093526"></a><a name="p1948319163093526"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1427464669093526"><a name="p1427464669093526"></a><a name="p1427464669093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row438323939093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p504068097093526"><a name="p504068097093526"></a><a name="p504068097093526"></a><a href="OSAL.md#ga7e4325c951479e93abe072290162da0b">OsalSemInit</a> (struct <a href="OsalSem.md">OsalSem</a> *sem, uint32_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2126405524093526"><a name="p2126405524093526"></a><a name="p2126405524093526"></a>int32_t&nbsp;</p>
<p id="p1775488568093526"><a name="p1775488568093526"></a><a name="p1775488568093526"></a>Initializes a semaphore. </p>
</td>
</tr>
<tr id="row1403806888093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1291661195093526"><a name="p1291661195093526"></a><a name="p1291661195093526"></a><a href="OSAL.md#ga0000b9ee1421950d5b3a04cbc839c6af">OsalSemWait</a> (struct <a href="OsalSem.md">OsalSem</a> *sem, uint32_t ms)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p282981153093526"><a name="p282981153093526"></a><a name="p282981153093526"></a>int32_t&nbsp;</p>
<p id="p397265793093526"><a name="p397265793093526"></a><a name="p397265793093526"></a>Waits for a semaphore. </p>
</td>
</tr>
<tr id="row390327607093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1800101901093526"><a name="p1800101901093526"></a><a name="p1800101901093526"></a><a href="OSAL.md#gadc3205b416d3fc8e1fa9c332b82e634a">OsalSemPost</a> (struct <a href="OsalSem.md">OsalSem</a> *sem)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p4191395093526"><a name="p4191395093526"></a><a name="p4191395093526"></a>int32_t&nbsp;</p>
<p id="p306487132093526"><a name="p306487132093526"></a><a name="p306487132093526"></a>Releases a semaphore. </p>
</td>
</tr>
<tr id="row526461809093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1189777411093526"><a name="p1189777411093526"></a><a name="p1189777411093526"></a><a href="OSAL.md#ga0b6642005b8a128ac01f69385bd6969f">OsalSemDestroy</a> (struct <a href="OsalSem.md">OsalSem</a> *sem)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1163258816093526"><a name="p1163258816093526"></a><a name="p1163258816093526"></a>int32_t&nbsp;</p>
<p id="p1302878288093526"><a name="p1302878288093526"></a><a name="p1302878288093526"></a>Destroys a semaphore. </p>
</td>
</tr>
</tbody>
</table>

