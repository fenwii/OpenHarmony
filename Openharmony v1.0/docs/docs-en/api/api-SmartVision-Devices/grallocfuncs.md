# GrallocFuncs<a name="EN-US_TOPIC_0000001054918153"></a>

## **Overview**<a name="section81925780084835"></a>

**Related Modules:**

[Display](display.md)

**Description:**

Defines pointers to the memory driver functions. 

## **Summary**<a name="section276023094084835"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1659591001084835"></a>
<table><thead align="left"><tr id="row1911929041084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p762184989084835"><a name="p762184989084835"></a><a name="p762184989084835"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p484447162084835"><a name="p484447162084835"></a><a name="p484447162084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1706603624084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1700833088084835"><a name="p1700833088084835"></a><a name="p1700833088084835"></a><a href="grallocfuncs.md#a48c1f21c086ead11bcb1a53bbec2d285">AllocMem</a> )(<a href="grallocbuffer.md">GrallocBuffer</a> *buffer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2018125726084835"><a name="p2018125726084835"></a><a name="p2018125726084835"></a>int32_t(* </p>
<p id="p1974635407084835"><a name="p1974635407084835"></a><a name="p1974635407084835"></a>Allocates memory based on the parameters passed by the GUI. </p>
</td>
</tr>
<tr id="row959834804084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p75187792084835"><a name="p75187792084835"></a><a name="p75187792084835"></a><a href="grallocfuncs.md#af80e6c92c5ba7e2419da27cafe19bcff">FreeMem</a> )(<a href="grallocbuffer.md">GrallocBuffer</a> *buffer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p204246818084835"><a name="p204246818084835"></a><a name="p204246818084835"></a>void(* </p>
<p id="p1340713927084835"><a name="p1340713927084835"></a><a name="p1340713927084835"></a>Releases memory. </p>
</td>
</tr>
<tr id="row1472282367084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p980997475084835"><a name="p980997475084835"></a><a name="p980997475084835"></a><a href="grallocfuncs.md#ab64438d785bc59050cd4f0a759bd531b">Mmap</a> )(<a href="grallocbuffer.md">GrallocBuffer</a> *buffer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p168461579084835"><a name="p168461579084835"></a><a name="p168461579084835"></a>void *(* </p>
<p id="p403700544084835"><a name="p403700544084835"></a><a name="p403700544084835"></a>Maps memory with a specified physical address and size to memory without cache in the process's address space. </p>
</td>
</tr>
<tr id="row2057647528084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1341207457084835"><a name="p1341207457084835"></a><a name="p1341207457084835"></a><a href="grallocfuncs.md#a25005370b14ff2a0c860b2272b354e3f">MmapCache</a> )(<a href="grallocbuffer.md">GrallocBuffer</a> *buffer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p472609768084835"><a name="p472609768084835"></a><a name="p472609768084835"></a>void *(* </p>
<p id="p372939386084835"><a name="p372939386084835"></a><a name="p372939386084835"></a>Maps memory with a specified physical address and size to memory with cache in the process's address space. </p>
</td>
</tr>
<tr id="row167531346084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1970116128084835"><a name="p1970116128084835"></a><a name="p1970116128084835"></a><a href="grallocfuncs.md#a55864e4912348f40dd77584e96ad4647">Unmap</a> )(<a href="grallocbuffer.md">GrallocBuffer</a> *buffer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p80143544084835"><a name="p80143544084835"></a><a name="p80143544084835"></a>int32_t(* </p>
<p id="p2009230258084835"><a name="p2009230258084835"></a><a name="p2009230258084835"></a>Unmaps memory, that is, removes any mappings in the process's address space. </p>
</td>
</tr>
<tr id="row1715976391084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p659267272084835"><a name="p659267272084835"></a><a name="p659267272084835"></a><a href="grallocfuncs.md#ad56665aa0ff48995b5ec72a8095416d8">FlushCache</a> )(<a href="grallocbuffer.md">GrallocBuffer</a> *buffer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1848658763084835"><a name="p1848658763084835"></a><a name="p1848658763084835"></a>int32_t(* </p>
<p id="p1332482849084835"><a name="p1332482849084835"></a><a name="p1332482849084835"></a>Flushes data from the cache to memory and invalidates the data in the cache. </p>
</td>
</tr>
<tr id="row1083635257084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1745886196084835"><a name="p1745886196084835"></a><a name="p1745886196084835"></a><a href="grallocfuncs.md#aceac1511a490c2ade1e33723d0e20960">FlushMCache</a> )(<a href="grallocbuffer.md">GrallocBuffer</a> *buffer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1810196051084835"><a name="p1810196051084835"></a><a name="p1810196051084835"></a>int32_t(* </p>
<p id="p909551594084835"><a name="p909551594084835"></a><a name="p909551594084835"></a>Flushes data from the cache mapping to <a href="grallocfuncs.md#ab64438d785bc59050cd4f0a759bd531b">Mmap</a> to memory and invalidates the data in the cache. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1267296291084835"></a>

## **Field Documentation**<a name="section919666985084835"></a>

## AllocMem<a name="a48c1f21c086ead11bcb1a53bbec2d285"></a>

```
int32_t(* GrallocFuncs::AllocMem) ([GrallocBuffer](grallocbuffer.md) *buffer)
```

 **Description:**

Allocates memory based on the parameters passed by the GUI. 

**Parameters:**

<a name="table1662159424084835"></a>
<table><thead align="left"><tr id="row56459889084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p99269541084835"><a name="p99269541084835"></a><a name="p99269541084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p110894276084835"><a name="p110894276084835"></a><a name="p110894276084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row867311423084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">hdl</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the handle of memory. </td>
</tr>
<tr id="row1600437501084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the type of memory to allocate. The value<span style="background-color: yellow;"><span style="font-weight: bold">[/table/tgroup/tbody/row/entry/div
				{""}) </span><span style="background-color: yellow;"><span style="font-weight: bold">[/table/tgroup/tbody/row/entry/div/div
				{""}) </span>0 <span style="font-weight: bold"> (div]</span></span> <span style="font-weight: bold"> (div]</span></span> indicates memory without cache, <span style="background-color: yellow;"><span style="font-weight: bold">[/table/tgroup/tbody/row/entry/div
				{""}) </span><span style="background-color: yellow;"><span style="font-weight: bold">[/table/tgroup/tbody/row/entry/div/div
				{""}) </span>1 <span style="font-weight: bold"> (div]</span></span> <span style="font-weight: bold"> (div]</span></span> indicates memory with cache, and<span style="background-color: yellow;"><span style="font-weight: bold">[/table/tgroup/tbody/row/entry/div
				{""}) </span><span style="background-color: yellow;"><span style="font-weight: bold">[/table/tgroup/tbody/row/entry/div/div
				{""}) </span>2 <span style="font-weight: bold"> (div]</span></span> <span style="font-weight: bold"> (div]</span></span> indicates shared memory. </td>
</tr>
<tr id="row746736895084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of memory to allocate, in bytes.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 



## FlushCache<a name="ad56665aa0ff48995b5ec72a8095416d8"></a>

```
int32_t(* GrallocFuncs::FlushCache) ([GrallocBuffer](grallocbuffer.md) *buffer)
```

 **Description:**

Flushes data from the cache to memory and invalidates the data in the cache. 

**Parameters:**

<a name="table104235383084835"></a>
<table><thead align="left"><tr id="row128937476084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1944519611084835"><a name="p1944519611084835"></a><a name="p1944519611084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1102766729084835"><a name="p1102766729084835"></a><a name="p1102766729084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1790516978084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">hdl</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the handle of the cache. </td>
</tr>
<tr id="row1481257992084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the cache from which data is to flush.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 



## FlushMCache<a name="aceac1511a490c2ade1e33723d0e20960"></a>

```
int32_t(* GrallocFuncs::FlushMCache) ([GrallocBuffer](grallocbuffer.md) *buffer)
```

 **Description:**

Flushes data from the cache mapping to  [Mmap](grallocfuncs.md#ab64438d785bc59050cd4f0a759bd531b)  to memory and invalidates the data in the cache. 

**Parameters:**

<a name="table918470824084835"></a>
<table><thead align="left"><tr id="row341890934084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2085660690084835"><a name="p2085660690084835"></a><a name="p2085660690084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p613319402084835"><a name="p613319402084835"></a><a name="p613319402084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row47699950084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">hdl</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the handle of the cache. </td>
</tr>
<tr id="row407551711084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the cache from which data is to flush.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 



## FreeMem<a name="af80e6c92c5ba7e2419da27cafe19bcff"></a>

```
void(* GrallocFuncs::FreeMem) ([GrallocBuffer](grallocbuffer.md) *buffer)
```

 **Description:**

Releases memory. 

**Parameters:**

<a name="table526039614084835"></a>
<table><thead align="left"><tr id="row270627118084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1723068196084835"><a name="p1723068196084835"></a><a name="p1723068196084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1977204585084835"><a name="p1977204585084835"></a><a name="p1977204585084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row183099994084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">hdl</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the handle of memory that has been applied for.</td>
</tr>
</tbody>
</table>

## Mmap<a name="ab64438d785bc59050cd4f0a759bd531b"></a>

```
void*(* GrallocFuncs::Mmap) ([GrallocBuffer](grallocbuffer.md) *buffer)
```

 **Description:**

Maps memory with a specified physical address and size to memory without cache in the process's address space. 

**Parameters:**

<a name="table237558825084835"></a>
<table><thead align="left"><tr id="row657793817084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1193131286084835"><a name="p1193131286084835"></a><a name="p1193131286084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p223516010084835"><a name="p223516010084835"></a><a name="p223516010084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row926444915084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">phyAddr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the physical address of memory to map. </td>
</tr>
<tr id="row775406279084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of memory to map.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to a valid address if the operation is successful; returns  **NULL**  otherwise. 



## MmapCache<a name="a25005370b14ff2a0c860b2272b354e3f"></a>

```
void*(* GrallocFuncs::MmapCache) ([GrallocBuffer](grallocbuffer.md) *buffer)
```

 **Description:**

Maps memory with a specified physical address and size to memory with cache in the process's address space. 

**Parameters:**

<a name="table959227480084835"></a>
<table><thead align="left"><tr id="row1468644493084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2021778635084835"><a name="p2021778635084835"></a><a name="p2021778635084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p500949379084835"><a name="p500949379084835"></a><a name="p500949379084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1302844667084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">phyAddr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the physical address of memory to map. </td>
</tr>
<tr id="row1601142069084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of memory to map.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to a valid address if the operation is successful; returns  **NULL**  otherwise. 



## Unmap<a name="a55864e4912348f40dd77584e96ad4647"></a>

```
int32_t(* GrallocFuncs::Unmap) ([GrallocBuffer](grallocbuffer.md) *buffer)
```

 **Description:**

Unmaps memory, that is, removes any mappings in the process's address space. 

**Parameters:**

<a name="table573218536084835"></a>
<table><thead align="left"><tr id="row1391012883084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p259934062084835"><a name="p259934062084835"></a><a name="p259934062084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1094849982084835"><a name="p1094849982084835"></a><a name="p1094849982084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row921700608084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">virAddr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the virtual address of memory to unmap. </td>
</tr>
<tr id="row311575550084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of memory to unmap.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 



