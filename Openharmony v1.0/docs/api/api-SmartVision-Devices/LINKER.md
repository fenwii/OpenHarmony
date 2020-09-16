# LINKER<a name="ZH-CN_TOPIC_0000001054948029"></a>

## **Overview**<a name="section140551700084825"></a>

Provides functions and structures related to linking and loading. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1353198702084825"></a>

## Files<a name="files"></a>

<a name="table624197257084825"></a>
<table><thead align="left"><tr id="row1401306351084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p391479296084825"><a name="p391479296084825"></a><a name="p391479296084825"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p231466388084825"><a name="p231466388084825"></a><a name="p231466388084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1305381503084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p13423372084825"><a name="p13423372084825"></a><a name="p13423372084825"></a><a href="dlfcn-h.md">dlfcn.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1465033084084825"><a name="p1465033084084825"></a><a name="p1465033084084825"></a>Provides functions and structures related to linking and loading. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table819809426084825"></a>
<table><thead align="left"><tr id="row1264510603084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1765023098084825"><a name="p1765023098084825"></a><a name="p1765023098084825"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p411603155084825"><a name="p411603155084825"></a><a name="p411603155084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1534629431084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p580560698084825"><a name="p580560698084825"></a><a name="p580560698084825"></a><em id="ga5c83709ee3bd7d316f8f47e122f3be20"><a name="ga5c83709ee3bd7d316f8f47e122f3be20"></a><a name="ga5c83709ee3bd7d316f8f47e122f3be20"></a></em>RTLD_LAZY &nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1039447625084825"><a name="p1039447625084825"></a><a name="p1039447625084825"></a>All undefined symbols in the shared object are not resolved before <a href="LINKER.md#gad559be443b3edb0af8835d6ec2c29a3a">dlopen()</a> returns. </p>
</td>
</tr>
<tr id="row516241716084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1329594192084825"><a name="p1329594192084825"></a><a name="p1329594192084825"></a><em id="ga98a6517467cf7d1dd27d6c6dce78a6cf"><a name="ga98a6517467cf7d1dd27d6c6dce78a6cf"></a><a name="ga98a6517467cf7d1dd27d6c6dce78a6cf"></a></em>RTLD_NOW &nbsp;&nbsp;&nbsp;2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1912809440084825"><a name="p1912809440084825"></a><a name="p1912809440084825"></a>All undefined symbols in the shared object are resolved before <a href="LINKER.md#gad559be443b3edb0af8835d6ec2c29a3a">dlopen()</a> returns. </p>
</td>
</tr>
<tr id="row1865641305084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2142172841084825"><a name="p2142172841084825"></a><a name="p2142172841084825"></a><em id="ga65cc8226321c99d43c9d854b0fb86081"><a name="ga65cc8226321c99d43c9d854b0fb86081"></a><a name="ga65cc8226321c99d43c9d854b0fb86081"></a></em>RTLD_NOLOAD &nbsp;&nbsp;&nbsp;4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1250652025084825"><a name="p1250652025084825"></a><a name="p1250652025084825"></a>The shared object is not loaded. It can be used to test whether the object resides in the memory. </p>
</td>
</tr>
<tr id="row1362129475084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1155307019084825"><a name="p1155307019084825"></a><a name="p1155307019084825"></a><em id="ga63b65253a063469ae964534ab38fe635"><a name="ga63b65253a063469ae964534ab38fe635"></a><a name="ga63b65253a063469ae964534ab38fe635"></a></em>RTLD_NODELETE &nbsp;&nbsp;&nbsp;4096</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p734018458084825"><a name="p734018458084825"></a><a name="p734018458084825"></a>The shared object is not deleted during <a href="LINKER.md#gaf483b6c4400965aa885f9f1a144138a5">dlclose()</a>. </p>
</td>
</tr>
<tr id="row1646745202084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p413856703084825"><a name="p413856703084825"></a><a name="p413856703084825"></a><em id="gace65454279c135fe5e6168d456c31263"><a name="gace65454279c135fe5e6168d456c31263"></a><a name="gace65454279c135fe5e6168d456c31263"></a></em>RTLD_GLOBAL &nbsp;&nbsp;&nbsp;256</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1535058742084825"><a name="p1535058742084825"></a><a name="p1535058742084825"></a>The symbols defined by the loaded shared object can be resolved by other shared objects opened later. </p>
</td>
</tr>
<tr id="row1629672610084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1864746640084825"><a name="p1864746640084825"></a><a name="p1864746640084825"></a><em id="ga233010260f7e61c5dab09e2bca10a590"><a name="ga233010260f7e61c5dab09e2bca10a590"></a><a name="ga233010260f7e61c5dab09e2bca10a590"></a></em>RTLD_LOCAL &nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1952382172084825"><a name="p1952382172084825"></a><a name="p1952382172084825"></a>The symbols defined by the loaded shared object cannot be resolved by other shared objects opened later. </p>
</td>
</tr>
<tr id="row21390697084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1113481075084825"><a name="p1113481075084825"></a><a name="p1113481075084825"></a><em id="ga51d4212b17b1edeb2fc5a48c7c497267"><a name="ga51d4212b17b1edeb2fc5a48c7c497267"></a><a name="ga51d4212b17b1edeb2fc5a48c7c497267"></a></em>RTLD_NEXT &nbsp;&nbsp;&nbsp;((void *)-1)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p77250570084825"><a name="p77250570084825"></a><a name="p77250570084825"></a>The next match of the required symbol is searched in the search order after the current object. </p>
</td>
</tr>
<tr id="row1281839865084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1464345516084825"><a name="p1464345516084825"></a><a name="p1464345516084825"></a><em id="ga58d13c5dcabbb85848fa97b446086247"><a name="ga58d13c5dcabbb85848fa97b446086247"></a><a name="ga58d13c5dcabbb85848fa97b446086247"></a></em>RTLD_DEFAULT &nbsp;&nbsp;&nbsp;((void *)0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p38595140084825"><a name="p38595140084825"></a><a name="p38595140084825"></a>The first match of the required symbol is searched in the default shared object search order. The search scope includes the global symbols of the program and its dependencies, and the global symbols loaded by the <a href="LINKER.md#gad559be443b3edb0af8835d6ec2c29a3a">dlopen()</a> function. </p>
</td>
</tr>
<tr id="row1854508129084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p731551837084825"><a name="p731551837084825"></a><a name="p731551837084825"></a><em id="gafc522c1a0d6100a1af90b59ded39ef91"><a name="gafc522c1a0d6100a1af90b59ded39ef91"></a><a name="gafc522c1a0d6100a1af90b59ded39ef91"></a></em>RTLD_DI_LINKMAP &nbsp;&nbsp;&nbsp;2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1812546376084825"><a name="p1812546376084825"></a><a name="p1812546376084825"></a>The pointer to the <strong id="b227696225084825"><a name="b227696225084825"></a><a name="b227696225084825"></a>link_map</strong> structure of the specified handle. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1293402643084825"></a>
<table><thead align="left"><tr id="row442721617084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p892210895084825"><a name="p892210895084825"></a><a name="p892210895084825"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1640702598084825"><a name="p1640702598084825"></a><a name="p1640702598084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1622817765084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1285494619084825"><a name="p1285494619084825"></a><a name="p1285494619084825"></a><a href="LINKER.md#gaf483b6c4400965aa885f9f1a144138a5">dlclose</a> (void *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1810650637084825"><a name="p1810650637084825"></a><a name="p1810650637084825"></a>int&nbsp;</p>
<p id="p375954653084825"><a name="p375954653084825"></a><a name="p375954653084825"></a>Closes the DLL of a specified handle. </p>
</td>
</tr>
<tr id="row1190872416084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1928172100084825"><a name="p1928172100084825"></a><a name="p1928172100084825"></a><a href="LINKER.md#ga541c343ae5cdf90926014c65972c86cc">dlerror</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1863841544084825"><a name="p1863841544084825"></a><a name="p1863841544084825"></a>char *&nbsp;</p>
<p id="p736658124084825"><a name="p736658124084825"></a><a name="p736658124084825"></a>Obtains the latest error that occurred during a DLL function execution failure. </p>
</td>
</tr>
<tr id="row1561549575084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1619130112084825"><a name="p1619130112084825"></a><a name="p1619130112084825"></a><a href="LINKER.md#gad559be443b3edb0af8835d6ec2c29a3a">dlopen</a> (const char *filename, int flags)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p870530651084825"><a name="p870530651084825"></a><a name="p870530651084825"></a>void *&nbsp;</p>
<p id="p1241362467084825"><a name="p1241362467084825"></a><a name="p1241362467084825"></a>Opens a DLL and returns its handle. </p>
</td>
</tr>
<tr id="row2120726308084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2006475076084825"><a name="p2006475076084825"></a><a name="p2006475076084825"></a><a href="LINKER.md#ga84cb8784df910bfcc3002dc5e9e2f406">dlsym</a> (void *handle, const char *symbol)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p885766960084825"><a name="p885766960084825"></a><a name="p885766960084825"></a>void *&nbsp;</p>
<p id="p1073482357084825"><a name="p1073482357084825"></a><a name="p1073482357084825"></a>Searches for a specified symbol based on the DLL handle. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section576298094084825"></a>

## **Function Documentation**<a name="section1400772950084825"></a>

## dlclose\(\)<a name="gaf483b6c4400965aa885f9f1a144138a5"></a>

```
int dlclose (void * handle)
```

 **Description:**

Closes the DLL of a specified handle. 

**Parameters:**

<a name="table1691553557084825"></a>
<table><thead align="left"><tr id="row1679938918084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1993083246084825"><a name="p1993083246084825"></a><a name="p1993083246084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1221975086084825"><a name="p1221975086084825"></a><a name="p1221975086084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row934813209084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the loaded DLL handle. </td>
</tr>
</tbody>
</table>

**Attention:**

The symbols associated with the handle may not be removed from the caller's address space even if the  **[dlclose\(\)](LINKER.md#gaf483b6c4400965aa885f9f1a144138a5)**  function returns. The symbols are removed only when the reference count of the DLL is 0. The reference count is incremented \(by 1\) each time the  **[dlopen\(\)](LINKER.md#gad559be443b3edb0af8835d6ec2c29a3a)**  function is explicitly called. In addition, the reference of DLL depended on by other DLLs or programs will be counted if it has been implicitly loaded. A shared object can be removed from the address space only after all references are released.

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value if the operation fails. 



## dlerror\(\)<a name="ga541c343ae5cdf90926014c65972c86cc"></a>

```
char* dlerror (void )
```

 **Description:**

Obtains the latest error that occurred during a DLL function execution failure. 

**Returns:**

Returns the error if occurred; returns  **NULL**  if the DLL function execution is successful. 



## dlopen\(\)<a name="gad559be443b3edb0af8835d6ec2c29a3a"></a>

```
void* dlopen (const char * filename, int flags )
```

 **Description:**

Opens a DLL and returns its handle. 

**Parameters:**

<a name="table510911007084825"></a>
<table><thead align="left"><tr id="row992879704084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1139497308084825"><a name="p1139497308084825"></a><a name="p1139497308084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p844740991084825"><a name="p844740991084825"></a><a name="p844740991084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1456031842084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">filename</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the file name of the DLL. </td>
</tr>
<tr id="row1012545503084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">flags</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the flag of the DLL to be loaded. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the DLL handle if the operation is successful; returns  **NULL**  if the operation fails. 



## dlsym\(\)<a name="ga84cb8784df910bfcc3002dc5e9e2f406"></a>

```
void* dlsym (void * handle, const char * symbol )
```

 **Description:**

Searches for a specified symbol based on the DLL handle. 

You can also use this function to obtain the loading addresses of global variables. 

**Parameters:**

<a name="table680747883084825"></a>
<table><thead align="left"><tr id="row544373741084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1736147775084825"><a name="p1736147775084825"></a><a name="p1736147775084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p839346772084825"><a name="p839346772084825"></a><a name="p839346772084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1337981219084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the loaded DLL handle. </td>
</tr>
<tr id="row1830289209084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">symbol</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the symbol name. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the symbol address if the operation is successful; returns  **NULL**  if the operation fails. 



