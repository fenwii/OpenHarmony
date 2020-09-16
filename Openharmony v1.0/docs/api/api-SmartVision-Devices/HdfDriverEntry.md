# HdfDriverEntry<a name="ZH-CN_TOPIC_0000001055198130"></a>

## **Overview**<a name="section1581955005093530"></a>

**Related Modules:**

[Core](Core.md)

**Description:**

Defines the entry structure of the driver in the HDF. 

This structure must be used as the entry for the driver to use the HDF mechanism.

**Since:**

1.0

## **Summary**<a name="section650324895093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1987806604093530"></a>
<table><thead align="left"><tr id="row818756400093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p165021017093530"><a name="p165021017093530"></a><a name="p165021017093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p19758762093530"><a name="p19758762093530"></a><a name="p19758762093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row212260450093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p478030396093530"><a name="p478030396093530"></a><a name="p478030396093530"></a><a href="HdfDriverEntry.md#a3c5f146bd9494eb0f052454157e2b4b0">moduleVersion</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p710240930093530"><a name="p710240930093530"></a><a name="p710240930093530"></a>int32_t&nbsp;</p>
</td>
</tr>
<tr id="row1847194104093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p348719435093530"><a name="p348719435093530"></a><a name="p348719435093530"></a><a href="HdfDriverEntry.md#af889c158a46b9805a96bd2281c024191">moduleName</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p160544658093530"><a name="p160544658093530"></a><a name="p160544658093530"></a>const char *&nbsp;</p>
</td>
</tr>
<tr id="row354817518093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p933120991093530"><a name="p933120991093530"></a><a name="p933120991093530"></a><a href="HdfDriverEntry.md#a9e26ffb43d0d3ab221aad844cd172582">Bind</a> )(struct <a href="HdfDeviceObject.md">HdfDeviceObject</a> *deviceObject)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1567956148093530"><a name="p1567956148093530"></a><a name="p1567956148093530"></a>int32_t(*&nbsp;</p>
<p id="p2069446148093530"><a name="p2069446148093530"></a><a name="p2069446148093530"></a>Binds the external service interface of a driver to the HDF. This function is implemented by the driver developer and called by the HDF. </p>
</td>
</tr>
<tr id="row513604183093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p709932817093530"><a name="p709932817093530"></a><a name="p709932817093530"></a><a href="HdfDriverEntry.md#a1009f6ddf7188c63ed4b66597edbc446">Init</a> )(struct <a href="HdfDeviceObject.md">HdfDeviceObject</a> *deviceObject)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1232534717093530"><a name="p1232534717093530"></a><a name="p1232534717093530"></a>int32_t(*&nbsp;</p>
<p id="p776622132093530"><a name="p776622132093530"></a><a name="p776622132093530"></a>Initializes the driver. This function is implemented by the driver developer and called by the HDF. </p>
</td>
</tr>
<tr id="row272743313093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1721650541093530"><a name="p1721650541093530"></a><a name="p1721650541093530"></a><a href="HdfDriverEntry.md#a5ff4bb43cf9d0a89ebf17876adbbff50">Release</a> )(struct <a href="HdfDeviceObject.md">HdfDeviceObject</a> *deviceObject)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p861725352093530"><a name="p861725352093530"></a><a name="p861725352093530"></a>void(*&nbsp;</p>
<p id="p1730175520093530"><a name="p1730175520093530"></a><a name="p1730175520093530"></a>Releases driver resources. This function is implemented by the driver developer. When an exception occurs during driver loading or the driver is uninstalled, the HDF calls this function to release the driver resources. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section192447625093530"></a>

## **Field Documentation**<a name="section568932252093530"></a>

## Bind<a name="a9e26ffb43d0d3ab221aad844cd172582"></a>

```
int32_t(* HdfDriverEntry::Bind) (struct [HdfDeviceObject](HdfDeviceObject.md) *deviceObject)
```

 **Description:**

Binds the external service interface of a driver to the HDF. This function is implemented by the driver developer and called by the HDF. 

**Parameters:**

<a name="table1210275753093530"></a>
<table><thead align="left"><tr id="row1957419726093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1424207885093530"><a name="p1424207885093530"></a><a name="p1424207885093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p213686554093530"><a name="p213686554093530"></a><a name="p213686554093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1363443885093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">deviceObject</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the variable of the <a href="HdfDeviceObject.md">HdfDeviceObject</a> type. This variable is generated by the HDF and passed to the driver. Then, the service object of the driver is bound to the <strong id="b1842144287093530"><a name="b1842144287093530"></a><a name="b1842144287093530"></a>service</strong> parameter of <strong id="b854691468093530"><a name="b854691468093530"></a><a name="b854691468093530"></a>deviceObject</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.



## Init<a name="a1009f6ddf7188c63ed4b66597edbc446"></a>

```
int32_t(* HdfDriverEntry::Init) (struct [HdfDeviceObject](HdfDeviceObject.md) *deviceObject)
```

 **Description:**

Initializes the driver. This function is implemented by the driver developer and called by the HDF. 

**Parameters:**

<a name="table8352818093530"></a>
<table><thead align="left"><tr id="row455029010093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p532453084093530"><a name="p532453084093530"></a><a name="p532453084093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p585839807093530"><a name="p585839807093530"></a><a name="p585839807093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row315445105093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">deviceObject</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the variable of the <a href="HdfDeviceObject.md">HdfDeviceObject</a> type. It is the same as the parameter of <a href="HdfDriverEntry.md#a9e26ffb43d0d3ab221aad844cd172582">Bind</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.



## moduleName<a name="af889c158a46b9805a96bd2281c024191"></a>

```
const char* HdfDriverEntry::moduleName
```

 **Description:**

Driver module name, which is used to match the driver information in the configuration file. 

## moduleVersion<a name="a3c5f146bd9494eb0f052454157e2b4b0"></a>

```
int32_t HdfDriverEntry::moduleVersion
```

 **Description:**

Driver version 

## Release<a name="a5ff4bb43cf9d0a89ebf17876adbbff50"></a>

```
void(* HdfDriverEntry::Release) (struct [HdfDeviceObject](HdfDeviceObject.md) *deviceObject)
```

 **Description:**

Releases driver resources. This function is implemented by the driver developer. When an exception occurs during driver loading or the driver is uninstalled, the HDF calls this function to release the driver resources. 

**Parameters:**

<a name="table233552048093530"></a>
<table><thead align="left"><tr id="row1484163634093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2075782583093530"><a name="p2075782583093530"></a><a name="p2075782583093530"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1748914770093530"><a name="p1748914770093530"></a><a name="p1748914770093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1763031368093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">deviceObject</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the variable of the <a href="HdfDeviceObject.md">HdfDeviceObject</a> type. It is the same as the parameter of <a href="HdfDriverEntry.md#a9e26ffb43d0d3ab221aad844cd172582">Bind</a>.</td>
</tr>
</tbody>
</table>

