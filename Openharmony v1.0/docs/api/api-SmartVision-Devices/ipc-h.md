# ipc.h<a name="ZH-CN_TOPIC_0000001055707978"></a>

## **Overview**<a name="section1201797316084830"></a>

**Related Modules:**

[IPC](IPC.md)

**Description:**

Defines IPC-related macros. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section749686755084830"></a>

## Macros<a name="define-members"></a>

<a name="table39994971084830"></a>
<table><thead align="left"><tr id="row1788495736084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1021235006084830"><a name="p1021235006084830"></a><a name="p1021235006084830"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1000747520084830"><a name="p1000747520084830"></a><a name="p1000747520084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row10474912084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p649033125084830"><a name="p649033125084830"></a><a name="p649033125084830"></a><a href="IPC.md#gace43f23fcb66ddaad964bb8ea8de6e9c">IPC_CREAT</a>&nbsp;&nbsp;&nbsp;01000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p274162207084830"><a name="p274162207084830"></a><a name="p274162207084830"></a>Defines the input parameter used to create an IPC object. </p>
</td>
</tr>
<tr id="row1538777053084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2116250335084830"><a name="p2116250335084830"></a><a name="p2116250335084830"></a><a href="IPC.md#gacd312ab97691605718a3ee9a1c7c63e9">IPC_EXCL</a>&nbsp;&nbsp;&nbsp;02000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p572479829084830"><a name="p572479829084830"></a><a name="p572479829084830"></a>Defines the input parameter used together with <a href="IPC.md#gace43f23fcb66ddaad964bb8ea8de6e9c">IPC_CREAT</a> to prevent duplicate key values during IPC creation. </p>
</td>
</tr>
<tr id="row321803090084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1806443214084830"><a name="p1806443214084830"></a><a name="p1806443214084830"></a><a href="IPC.md#ga5afdf5fc48bb22fa27fbd85627b189b9">IPC_NOWAIT</a>&nbsp;&nbsp;&nbsp;04000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p445200724084830"><a name="p445200724084830"></a><a name="p445200724084830"></a>Defines the input parameter that specifies whether the communication is in non-blocking mode. </p>
</td>
</tr>
<tr id="row445631171084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p808429200084830"><a name="p808429200084830"></a><a name="p808429200084830"></a><a href="IPC.md#ga752c83032a7bec60c904d97508ea4599">IPC_RMID</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p233268257084830"><a name="p233268257084830"></a><a name="p233268257084830"></a>Defines the input parameter used to delete an IPC object. </p>
</td>
</tr>
<tr id="row560322094084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1862842160084830"><a name="p1862842160084830"></a><a name="p1862842160084830"></a><a href="IPC.md#ga1f1cdce55426e50878b1c71a4fc67a41">IPC_SET</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1192336878084830"><a name="p1192336878084830"></a><a name="p1192336878084830"></a>Defines the input parameter used to set information to the kernel. </p>
</td>
</tr>
<tr id="row1086007487084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1113143498084830"><a name="p1113143498084830"></a><a name="p1113143498084830"></a><a href="IPC.md#ga17d3735e2d47ffa00a2cdf3a066f40d0">IPC_INFO</a>&nbsp;&nbsp;&nbsp;3</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p46535273084830"><a name="p46535273084830"></a><a name="p46535273084830"></a>Defines the input parameter used to obtain the system-level restriction information of a specified communication type, for example, <a href="shminfo.md">shminfo</a>. </p>
</td>
</tr>
<tr id="row210704987084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p837124249084830"><a name="p837124249084830"></a><a name="p837124249084830"></a><a href="IPC.md#gae2b9b856a4a657c250b0b2e1cc0835d9">IPC_PRIVATE</a>&nbsp;&nbsp;&nbsp;((key_t) 0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p832360481084830"><a name="p832360481084830"></a><a name="p832360481084830"></a>Defines the IPC object as a private object. </p>
</td>
</tr>
</tbody>
</table>

