# malloc.h<a name="EN-US_TOPIC_0000001054948035"></a>

## **Overview**<a name="section355391420084831"></a>

**Related Modules:**

[MEM](mem.md)

**Description:**

Declares APIs for allocating and releasing memory. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2031297944084831"></a>

## Functions<a name="func-members"></a>

<a name="table1618211647084831"></a>
<table><thead align="left"><tr id="row1553619567084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1231510754084831"><a name="p1231510754084831"></a><a name="p1231510754084831"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p170947371084831"><a name="p170947371084831"></a><a name="p170947371084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1286288522084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p559559883084831"><a name="p559559883084831"></a><a name="p559559883084831"></a><a href="mem.md#ga7ac38fce3243a7dcf448301ee9ffd392">malloc</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2144765097084831"><a name="p2144765097084831"></a><a name="p2144765097084831"></a>void * </p>
<p id="p1052049641084831"><a name="p1052049641084831"></a><a name="p1052049641084831"></a>Dynamically allocates a block of uninitialized memory with the specified size. </p>
</td>
</tr>
<tr id="row446087096084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1258174176084831"><a name="p1258174176084831"></a><a name="p1258174176084831"></a><a href="mem.md#ga62b7798461bd461da64c5f9d35feddf7">calloc</a> (size_t nmemb, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p172438574084831"><a name="p172438574084831"></a><a name="p172438574084831"></a>void * </p>
<p id="p1930095899084831"><a name="p1930095899084831"></a><a name="p1930095899084831"></a>Dynamically allocates multiple blocks of memory with the specified size. </p>
</td>
</tr>
<tr id="row1698937458084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2073999569084831"><a name="p2073999569084831"></a><a name="p2073999569084831"></a><a href="mem.md#ga1a6b5e8d2f1c37e5b43e4345586075be">realloc</a> (void *ptr, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p757982475084831"><a name="p757982475084831"></a><a name="p757982475084831"></a>void * </p>
<p id="p819441211084831"><a name="p819441211084831"></a><a name="p819441211084831"></a>Changes the size of a previously allocated memory block pointed to by <strong id="b833252481084831"><a name="b833252481084831"></a><a name="b833252481084831"></a>ptr</strong> to the specified size. </p>
</td>
</tr>
<tr id="row176590533084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p160653850084831"><a name="p160653850084831"></a><a name="p160653850084831"></a><a href="mem.md#gafbedc913aa4651b3c3b4b3aecd9b4711">free</a> (void *ptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1153828844084831"><a name="p1153828844084831"></a><a name="p1153828844084831"></a>void </p>
<p id="p950076617084831"><a name="p950076617084831"></a><a name="p950076617084831"></a>Frees the memory space pointed to by <strong id="b227628279084831"><a name="b227628279084831"></a><a name="b227628279084831"></a>ptr</strong>. </p>
</td>
</tr>
<tr id="row2104780570084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2107844069084831"><a name="p2107844069084831"></a><a name="p2107844069084831"></a><a href="mem.md#ga6a1c0668b7069bb45fd6e69f301ed5b9">memalign</a> (size_t alignment, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2110591285084831"><a name="p2110591285084831"></a><a name="p2110591285084831"></a>void * </p>
<p id="p383299053084831"><a name="p383299053084831"></a><a name="p383299053084831"></a>Allocates a block of memory with the specified size based on the given alignment mode. </p>
</td>
</tr>
<tr id="row1696005048084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p186020634084831"><a name="p186020634084831"></a><a name="p186020634084831"></a><a href="mem.md#gaa011d7b7bfeba45c8c32e04204a0f565">malloc_usable_size</a> (void *ptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1713520853084831"><a name="p1713520853084831"></a><a name="p1713520853084831"></a>size_t </p>
<p id="p1946442847084831"><a name="p1946442847084831"></a><a name="p1946442847084831"></a>Obtains the size of the memory block pointed to by <strong id="b17098951084831"><a name="b17098951084831"></a><a name="b17098951084831"></a>ptr</strong>. </p>
</td>
</tr>
</tbody>
</table>

