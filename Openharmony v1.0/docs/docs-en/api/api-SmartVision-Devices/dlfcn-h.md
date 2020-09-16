# dlfcn.h<a name="EN-US_TOPIC_0000001054748005"></a>

## **Overview**<a name="section638678398084829"></a>

**Related Modules:**

[LINKER](linker.md)

**Description:**

Provides functions and structures related to linking and loading. 

This file provides functions and structures for opening and closing a dynamic-link library \(DLL\) and searching for the specified symbols based on the DLL. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1313122279084829"></a>

## Macros<a name="define-members"></a>

<a name="table1032506755084829"></a>
<table><thead align="left"><tr id="row596209300084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p443867435084829"><a name="p443867435084829"></a><a name="p443867435084829"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p568398474084829"><a name="p568398474084829"></a><a name="p568398474084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1572653643084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1724004990084829"><a name="p1724004990084829"></a><a name="p1724004990084829"></a><a href="linker.md#ga5c83709ee3bd7d316f8f47e122f3be20">RTLD_LAZY</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1805162152084829"><a name="p1805162152084829"></a><a name="p1805162152084829"></a>All undefined symbols in the shared object are not resolved before <a href="linker.md#gad559be443b3edb0af8835d6ec2c29a3a">dlopen()</a> returns. </p>
</td>
</tr>
<tr id="row693870697084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1080758526084829"><a name="p1080758526084829"></a><a name="p1080758526084829"></a><a href="linker.md#ga98a6517467cf7d1dd27d6c6dce78a6cf">RTLD_NOW</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2141100169084829"><a name="p2141100169084829"></a><a name="p2141100169084829"></a>All undefined symbols in the shared object are resolved before <a href="linker.md#gad559be443b3edb0af8835d6ec2c29a3a">dlopen()</a> returns. </p>
</td>
</tr>
<tr id="row1862711445084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p451160471084829"><a name="p451160471084829"></a><a name="p451160471084829"></a><a href="linker.md#ga65cc8226321c99d43c9d854b0fb86081">RTLD_NOLOAD</a>   4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p553254864084829"><a name="p553254864084829"></a><a name="p553254864084829"></a>The shared object is not loaded. It can be used to test whether the object resides in the memory. </p>
</td>
</tr>
<tr id="row861153271084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p8774017084829"><a name="p8774017084829"></a><a name="p8774017084829"></a><a href="linker.md#ga63b65253a063469ae964534ab38fe635">RTLD_NODELETE</a>   4096</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p889616552084829"><a name="p889616552084829"></a><a name="p889616552084829"></a>The shared object is not deleted during <a href="linker.md#gaf483b6c4400965aa885f9f1a144138a5">dlclose()</a>. </p>
</td>
</tr>
<tr id="row1828661749084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1978197521084829"><a name="p1978197521084829"></a><a name="p1978197521084829"></a><a href="linker.md#gace65454279c135fe5e6168d456c31263">RTLD_GLOBAL</a>   256</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1481554828084829"><a name="p1481554828084829"></a><a name="p1481554828084829"></a>The symbols defined by the loaded shared object can be resolved by other shared objects opened later. </p>
</td>
</tr>
<tr id="row821963814084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1392202459084829"><a name="p1392202459084829"></a><a name="p1392202459084829"></a><a href="linker.md#ga233010260f7e61c5dab09e2bca10a590">RTLD_LOCAL</a>   0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1857075848084829"><a name="p1857075848084829"></a><a name="p1857075848084829"></a>The symbols defined by the loaded shared object cannot be resolved by other shared objects opened later. </p>
</td>
</tr>
<tr id="row1944458160084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1197957670084829"><a name="p1197957670084829"></a><a name="p1197957670084829"></a><a href="linker.md#ga51d4212b17b1edeb2fc5a48c7c497267">RTLD_NEXT</a>   ((void *)-1)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p922642474084829"><a name="p922642474084829"></a><a name="p922642474084829"></a>The next match of the required symbol is searched in the search order after the current object. </p>
</td>
</tr>
<tr id="row825446789084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1129903190084829"><a name="p1129903190084829"></a><a name="p1129903190084829"></a><a href="linker.md#ga58d13c5dcabbb85848fa97b446086247">RTLD_DEFAULT</a>   ((void *)0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1537297080084829"><a name="p1537297080084829"></a><a name="p1537297080084829"></a>The first match of the required symbol is searched in the default shared object search order. The search scope includes the global symbols of the program and its dependencies, and the global symbols loaded by the <a href="linker.md#gad559be443b3edb0af8835d6ec2c29a3a">dlopen()</a> function. </p>
</td>
</tr>
<tr id="row75393830084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p319455423084829"><a name="p319455423084829"></a><a name="p319455423084829"></a><a href="linker.md#gafc522c1a0d6100a1af90b59ded39ef91">RTLD_DI_LINKMAP</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1240645994084829"><a name="p1240645994084829"></a><a name="p1240645994084829"></a>The pointer to the <strong id="b1055314691084829"><a name="b1055314691084829"></a><a name="b1055314691084829"></a>link_map</strong> structure of the specified handle. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table517367491084829"></a>
<table><thead align="left"><tr id="row354760371084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p715728642084829"><a name="p715728642084829"></a><a name="p715728642084829"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1076380648084829"><a name="p1076380648084829"></a><a name="p1076380648084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2122350502084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p150328062084829"><a name="p150328062084829"></a><a name="p150328062084829"></a><a href="linker.md#gaf483b6c4400965aa885f9f1a144138a5">dlclose</a> (void *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1008254210084829"><a name="p1008254210084829"></a><a name="p1008254210084829"></a>int </p>
<p id="p1472024599084829"><a name="p1472024599084829"></a><a name="p1472024599084829"></a>Closes the DLL of a specified handle. </p>
</td>
</tr>
<tr id="row285918096084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1547205883084829"><a name="p1547205883084829"></a><a name="p1547205883084829"></a><a href="linker.md#ga541c343ae5cdf90926014c65972c86cc">dlerror</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1208598086084829"><a name="p1208598086084829"></a><a name="p1208598086084829"></a>char * </p>
<p id="p1170100037084829"><a name="p1170100037084829"></a><a name="p1170100037084829"></a>Obtains the latest error that occurred during a DLL function execution failure. </p>
</td>
</tr>
<tr id="row14375949084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1758781105084829"><a name="p1758781105084829"></a><a name="p1758781105084829"></a><a href="linker.md#gad559be443b3edb0af8835d6ec2c29a3a">dlopen</a> (const char *filename, int flags)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1089051938084829"><a name="p1089051938084829"></a><a name="p1089051938084829"></a>void * </p>
<p id="p640702437084829"><a name="p640702437084829"></a><a name="p640702437084829"></a>Opens a DLL and returns its handle. </p>
</td>
</tr>
<tr id="row1609908953084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p752149057084829"><a name="p752149057084829"></a><a name="p752149057084829"></a><a href="linker.md#ga84cb8784df910bfcc3002dc5e9e2f406">dlsym</a> (void *handle, const char *symbol)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1273274903084829"><a name="p1273274903084829"></a><a name="p1273274903084829"></a>void * </p>
<p id="p827885656084829"><a name="p827885656084829"></a><a name="p827885656084829"></a>Searches for a specified symbol based on the DLL handle. </p>
</td>
</tr>
</tbody>
</table>

