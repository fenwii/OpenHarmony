# osal\_mem.h<a name="EN-US_TOPIC_0000001054799575"></a>

## **Overview**<a name="section1943350453093526"></a>

**Related Modules:**

[OSAL](osal.md)

**Description:**

Declares the driver memory request and release interfaces. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1258604360093526"></a>

## Functions<a name="func-members"></a>

<a name="table1054806352093526"></a>
<table><thead align="left"><tr id="row399296609093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p44722601093526"><a name="p44722601093526"></a><a name="p44722601093526"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1356555093526"><a name="p1356555093526"></a><a name="p1356555093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1385769459093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p905718090093526"><a name="p905718090093526"></a><a name="p905718090093526"></a><a href="osal.md#ga0a1c85eaad6c1588ed091e0e89b74ed2">OsalMemAlloc</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p201428324093526"><a name="p201428324093526"></a><a name="p201428324093526"></a>void * </p>
<p id="p1201524557093526"><a name="p1201524557093526"></a><a name="p1201524557093526"></a>Allocates memory of a specified size. </p>
</td>
</tr>
<tr id="row329575113093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2145025480093526"><a name="p2145025480093526"></a><a name="p2145025480093526"></a><a href="osal.md#ga7a6d0f6400e835bcbe9ec655bc9f43ee">OsalMemCalloc</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p108209818093526"><a name="p108209818093526"></a><a name="p108209818093526"></a>void * </p>
<p id="p368563913093526"><a name="p368563913093526"></a><a name="p368563913093526"></a>Allocates memory of a specified size, and clears the allocated memory. </p>
</td>
</tr>
<tr id="row124526779093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1363261393093526"><a name="p1363261393093526"></a><a name="p1363261393093526"></a><a href="osal.md#gaf6d1b6e5583d9e1ca5abf5048bb3bad9">OsalMemAllocAlign</a> (size_t alignment, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1730202321093526"><a name="p1730202321093526"></a><a name="p1730202321093526"></a>void * </p>
<p id="p1699244590093526"><a name="p1699244590093526"></a><a name="p1699244590093526"></a>Allocates memory of a specified size, and aligns the memory address on a given boundary. </p>
</td>
</tr>
<tr id="row1341024802093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p757987342093526"><a name="p757987342093526"></a><a name="p757987342093526"></a><a href="osal.md#ga20dc9c415433effea4d481180a50cfa1">OsalMemFree</a> (void *mem)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1036122493093526"><a name="p1036122493093526"></a><a name="p1036122493093526"></a>void </p>
<p id="p1111530925093526"><a name="p1111530925093526"></a><a name="p1111530925093526"></a>Releases memory. </p>
</td>
</tr>
</tbody>
</table>

