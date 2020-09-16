# common.h<a name="EN-US_TOPIC_0000001054748147"></a>

## **Overview**<a name="section917562391090253"></a>

**Related Modules:**

[Samgr](samgr.md)

**Description:**

Provides common objects and functions for Samgr and external modules. 

This file provides simplified vector containers and downcast functions. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section207963847090253"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1041402256090253"></a>
<table><thead align="left"><tr id="row575764760090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1958633150090253"><a name="p1958633150090253"></a><a name="p1958633150090253"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p607088803090253"><a name="p607088803090253"></a><a name="p607088803090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row176264653090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1672025839090253"><a name="p1672025839090253"></a><a name="p1672025839090253"></a><a href="simplevector.md">SimpleVector</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p126749333090253"><a name="p126749333090253"></a><a name="p126749333090253"></a>Defines the simplified vector class, which is extended by four elements. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1823955663090253"></a>
<table><thead align="left"><tr id="row153689233090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p448270990090253"><a name="p448270990090253"></a><a name="p448270990090253"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1451378623090253"><a name="p1451378623090253"></a><a name="p1451378623090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row796156066090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1196137381090253"><a name="p1196137381090253"></a><a name="p1196137381090253"></a><a href="samgr.md#gab094855efe05ae51eaaf3e0ddf0346cc">GET_OFFSIZE</a>(T, member)   (long)((char *)&amp;(((T *)(0))-&gt;member))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p541446860090253"><a name="p541446860090253"></a><a name="p541446860090253"></a>Calculates the offset of the member in the T type. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1075790323090253"></a>
<table><thead align="left"><tr id="row625798343090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1982495866090253"><a name="p1982495866090253"></a><a name="p1982495866090253"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1812322960090253"><a name="p1812322960090253"></a><a name="p1812322960090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1288084268090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p170812912090253"><a name="p170812912090253"></a><a name="p170812912090253"></a><a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1998565861090253"><a name="p1998565861090253"></a><a name="p1998565861090253"></a>typedef struct <a href="simplevector.md">SimpleVector</a> </p>
<p id="p1600376810090253"><a name="p1600376810090253"></a><a name="p1600376810090253"></a>Defines the simplified vector class, which is extended by four elements. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1931269751090253"></a>
<table><thead align="left"><tr id="row951551819090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p72149921090253"><a name="p72149921090253"></a><a name="p72149921090253"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p466152835090253"><a name="p466152835090253"></a><a name="p466152835090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row910526754090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1120587951090253"><a name="p1120587951090253"></a><a name="p1120587951090253"></a><a href="samgr.md#gae790345f8a2863c143bfee4bab3fb6d7">VECTOR_Make</a> (VECTOR_Key key, VECTOR_Compare compare)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1925406323090253"><a name="p1925406323090253"></a><a name="p1925406323090253"></a><a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> </p>
<p id="p430206460090253"><a name="p430206460090253"></a><a name="p430206460090253"></a>Creates or initializes a vector object. </p>
</td>
</tr>
<tr id="row2135362259090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1349790793090253"><a name="p1349790793090253"></a><a name="p1349790793090253"></a><a href="samgr.md#gaebfe9ac38f2667d61bf39420aa8e7035">VECTOR_Clear</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p345664392090253"><a name="p345664392090253"></a><a name="p345664392090253"></a>void </p>
<p id="p579563299090253"><a name="p579563299090253"></a><a name="p579563299090253"></a>Destruct a vector object. </p>
</td>
</tr>
<tr id="row1810354472090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p948554496090253"><a name="p948554496090253"></a><a name="p948554496090253"></a><a href="samgr.md#ga234ba2452c973e9fa4a8be47eaea9d06">VECTOR_Add</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, void *element)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p288447048090253"><a name="p288447048090253"></a><a name="p288447048090253"></a>int16 </p>
<p id="p632665072090253"><a name="p632665072090253"></a><a name="p632665072090253"></a>Adds an element to the vector. </p>
</td>
</tr>
<tr id="row648958554090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p306425308090253"><a name="p306425308090253"></a><a name="p306425308090253"></a><a href="samgr.md#ga1432f30c136d14bc00414d883d8be3bd">VECTOR_Size</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1535693346090253"><a name="p1535693346090253"></a><a name="p1535693346090253"></a>int16 </p>
<p id="p25337563090253"><a name="p25337563090253"></a><a name="p25337563090253"></a>Obtains the number of elements in the vector, including elements that have been set to <strong id="b611608716090253"><a name="b611608716090253"></a><a name="b611608716090253"></a>NULL</strong>. </p>
</td>
</tr>
<tr id="row1534092227090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1394281776090253"><a name="p1394281776090253"></a><a name="p1394281776090253"></a><a href="samgr.md#ga90523bfd48091a0135f74670076af4d5">VECTOR_Num</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1505673030090253"><a name="p1505673030090253"></a><a name="p1505673030090253"></a>int16 </p>
<p id="p1555592269090253"><a name="p1555592269090253"></a><a name="p1555592269090253"></a>Obtains the number of valid elements in the vector, excluding elements that have been set to <strong id="b1728477789090253"><a name="b1728477789090253"></a><a name="b1728477789090253"></a>NULL</strong>. </p>
</td>
</tr>
<tr id="row758959612090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p23069766090253"><a name="p23069766090253"></a><a name="p23069766090253"></a><a href="samgr.md#ga75210ba0bd37a38a1902c4904e61246a">VECTOR_At</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, int16 index)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p199554158090253"><a name="p199554158090253"></a><a name="p199554158090253"></a>void * </p>
<p id="p667439705090253"><a name="p667439705090253"></a><a name="p667439705090253"></a>Obtains the element at a specified position. </p>
</td>
</tr>
<tr id="row193217981090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1971292744090253"><a name="p1971292744090253"></a><a name="p1971292744090253"></a><a href="samgr.md#ga7f435d33ba61d145de9d5892b68a0eda">VECTOR_Swap</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, int16 index, void *element)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p459827829090253"><a name="p459827829090253"></a><a name="p459827829090253"></a>void * </p>
<p id="p2025902525090253"><a name="p2025902525090253"></a><a name="p2025902525090253"></a>Swaps the element at a specified position in a vector with another element. </p>
</td>
</tr>
<tr id="row367732658090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1351171885090253"><a name="p1351171885090253"></a><a name="p1351171885090253"></a><a href="samgr.md#gaabc5b0eda1ee6889411e6dacb233cb07">VECTOR_Find</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, const void *element)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1028569945090253"><a name="p1028569945090253"></a><a name="p1028569945090253"></a>int16 </p>
<p id="p934240726090253"><a name="p934240726090253"></a><a name="p934240726090253"></a>Checks the position of an element. </p>
</td>
</tr>
<tr id="row243034961090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p470465466090253"><a name="p470465466090253"></a><a name="p470465466090253"></a><a href="samgr.md#gac65bc6dc959a90d95dff93368abd97c7">VECTOR_FindByKey</a> (<a href="samgr.md#ga255ca81c214b8a94a90f786ceef94514">Vector</a> *vector, const void *key)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p453944916090253"><a name="p453944916090253"></a><a name="p453944916090253"></a>int16 </p>
<p id="p1406605495090253"><a name="p1406605495090253"></a><a name="p1406605495090253"></a>Checks the position of the element with a specified key. </p>
</td>
</tr>
</tbody>
</table>

