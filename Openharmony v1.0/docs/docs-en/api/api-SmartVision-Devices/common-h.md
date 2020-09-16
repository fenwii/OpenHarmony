# common.h<a name="EN-US_TOPIC_0000001055228012"></a>

## **Overview**<a name="section442599878084829"></a>

**Related Modules:**

[Samgr](samgr.md)

**Description:**

Provides common objects and functions for Samgr and external modules. 

This file provides simplified vector containers and downcast functions. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1465612784084829"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table645771945084829"></a>
<table><thead align="left"><tr id="row895033026084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1465440290084829"><a name="p1465440290084829"></a><a name="p1465440290084829"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p343099128084829"><a name="p343099128084829"></a><a name="p343099128084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1829469714084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1053495260084829"><a name="p1053495260084829"></a><a name="p1053495260084829"></a><a href="simplevector.md">SimpleVector</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1130662023084829"><a name="p1130662023084829"></a><a name="p1130662023084829"></a>Defines the simplified vector class, which is extended by four elements. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1342798978084829"></a>
<table><thead align="left"><tr id="row684569336084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2013278882084829"><a name="p2013278882084829"></a><a name="p2013278882084829"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p760384676084829"><a name="p760384676084829"></a><a name="p760384676084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1748160862084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1951619495084829"><a name="p1951619495084829"></a><a name="p1951619495084829"></a><a href="samgr.md#gab094855efe05ae51eaaf3e0ddf0346cc">GET_OFFSIZE</a>(T, member)   (long)((char *)&amp;(((T *)(0))-&gt;member))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1481142113084829"><a name="p1481142113084829"></a><a name="p1481142113084829"></a>Calculates the offset of the member in the T type. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table629763407084829"></a>
<table><thead align="left"><tr id="row211825259084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p841756497084829"><a name="p841756497084829"></a><a name="p841756497084829"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1008946612084829"><a name="p1008946612084829"></a><a name="p1008946612084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row279621227084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1826683570084829"><a name="p1826683570084829"></a><a name="p1826683570084829"></a><a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1915636425084829"><a name="p1915636425084829"></a><a name="p1915636425084829"></a>typedef struct <a href="simplevector.md">SimpleVector</a> </p>
<p id="p1295488024084829"><a name="p1295488024084829"></a><a name="p1295488024084829"></a>Defines the simplified vector class, which is extended by four elements. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table914503870084829"></a>
<table><thead align="left"><tr id="row1480004627084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p994091695084829"><a name="p994091695084829"></a><a name="p994091695084829"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1924818835084829"><a name="p1924818835084829"></a><a name="p1924818835084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row341086008084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1993631919084829"><a name="p1993631919084829"></a><a name="p1993631919084829"></a><a href="samgr.md#gae790345f8a2863c143bfee4bab3fb6d7">VECTOR_Make</a> (VECTOR_Key key, VECTOR_Compare compare)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p460002576084829"><a name="p460002576084829"></a><a name="p460002576084829"></a><a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> </p>
<p id="p911995001084829"><a name="p911995001084829"></a><a name="p911995001084829"></a>Creates or initializes a vector object. </p>
</td>
</tr>
<tr id="row1678313751084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p621409671084829"><a name="p621409671084829"></a><a name="p621409671084829"></a><a href="samgr.md#gaebfe9ac38f2667d61bf39420aa8e7035">VECTOR_Clear</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p985384400084829"><a name="p985384400084829"></a><a name="p985384400084829"></a>void </p>
<p id="p745201302084829"><a name="p745201302084829"></a><a name="p745201302084829"></a>Destruct a vector object. </p>
</td>
</tr>
<tr id="row1151716189084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p238184110084829"><a name="p238184110084829"></a><a name="p238184110084829"></a><a href="samgr.md#ga234ba2452c973e9fa4a8be47eaea9d06">VECTOR_Add</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, void *element)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p805674329084829"><a name="p805674329084829"></a><a name="p805674329084829"></a>int16 </p>
<p id="p1436443396084829"><a name="p1436443396084829"></a><a name="p1436443396084829"></a>Adds an element to the vector. </p>
</td>
</tr>
<tr id="row2063212975084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p567382327084829"><a name="p567382327084829"></a><a name="p567382327084829"></a><a href="samgr.md#ga1432f30c136d14bc00414d883d8be3bd">VECTOR_Size</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1216378305084829"><a name="p1216378305084829"></a><a name="p1216378305084829"></a>int16 </p>
<p id="p1984979656084829"><a name="p1984979656084829"></a><a name="p1984979656084829"></a>Obtains the number of elements in the vector, including elements that have been set to <strong id="b1254256173084829"><a name="b1254256173084829"></a><a name="b1254256173084829"></a>NULL</strong>. </p>
</td>
</tr>
<tr id="row786643968084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1283731084829"><a name="p1283731084829"></a><a name="p1283731084829"></a><a href="samgr.md#ga90523bfd48091a0135f74670076af4d5">VECTOR_Num</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1579904021084829"><a name="p1579904021084829"></a><a name="p1579904021084829"></a>int16 </p>
<p id="p1381585756084829"><a name="p1381585756084829"></a><a name="p1381585756084829"></a>Obtains the number of valid elements in the vector, excluding elements that have been set to <strong id="b1993478785084829"><a name="b1993478785084829"></a><a name="b1993478785084829"></a>NULL</strong>. </p>
</td>
</tr>
<tr id="row78862721084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p940902735084829"><a name="p940902735084829"></a><a name="p940902735084829"></a><a href="samgr.md#ga75210ba0bd37a38a1902c4904e61246a">VECTOR_At</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, int16 <a href="utils.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p480539533084829"><a name="p480539533084829"></a><a name="p480539533084829"></a>void * </p>
<p id="p1078481822084829"><a name="p1078481822084829"></a><a name="p1078481822084829"></a>Obtains the element at a specified position. </p>
</td>
</tr>
<tr id="row1513843380084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1307298800084829"><a name="p1307298800084829"></a><a name="p1307298800084829"></a><a href="samgr.md#ga7f435d33ba61d145de9d5892b68a0eda">VECTOR_Swap</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, int16 <a href="utils.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>, void *element)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1873037282084829"><a name="p1873037282084829"></a><a name="p1873037282084829"></a>void * </p>
<p id="p1183549760084829"><a name="p1183549760084829"></a><a name="p1183549760084829"></a>Swaps the element at a specified position in a vector with another element. </p>
</td>
</tr>
<tr id="row1063540854084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p863328461084829"><a name="p863328461084829"></a><a name="p863328461084829"></a><a href="samgr.md#gaabc5b0eda1ee6889411e6dacb233cb07">VECTOR_Find</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, const void *element)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p177130075084829"><a name="p177130075084829"></a><a name="p177130075084829"></a>int16 </p>
<p id="p1048676133084829"><a name="p1048676133084829"></a><a name="p1048676133084829"></a>Checks the position of an element. </p>
</td>
</tr>
<tr id="row1943039642084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1846340884084829"><a name="p1846340884084829"></a><a name="p1846340884084829"></a><a href="samgr.md#gac65bc6dc959a90d95dff93368abd97c7">VECTOR_FindByKey</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, const void *key)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1185594924084829"><a name="p1185594924084829"></a><a name="p1185594924084829"></a>int16 </p>
<p id="p614322523084829"><a name="p614322523084829"></a><a name="p614322523084829"></a>Checks the position of the element with a specified key. </p>
</td>
</tr>
</tbody>
</table>

