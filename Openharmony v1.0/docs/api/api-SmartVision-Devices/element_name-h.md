# element\_name.h<a name="ZH-CN_TOPIC_0000001055039482"></a>

## **Overview**<a name="section2011780030093524"></a>

**Related Modules:**

[BundleManager](BundleManager.md)

**Description:**

Declares the structure that defines the required information for querying  [AbilityInfo](AbilityInfo.md), including the device ID, bundle name, and class name, and functions for setting such information. 

You can use functions provided in this file to specify the information for querying  [AbilityInfo](AbilityInfo.md).

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1788201670093524"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1286421684093524"></a>
<table><thead align="left"><tr id="row539471327093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1057860312093524"><a name="p1057860312093524"></a><a name="p1057860312093524"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p890172267093524"><a name="p890172267093524"></a><a name="p890172267093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1512696557093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1090747403093524"><a name="p1090747403093524"></a><a name="p1090747403093524"></a><a href="ElementName.md">ElementName</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1713251351093524"><a name="p1713251351093524"></a><a name="p1713251351093524"></a>Defines the ability information. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table407967701093524"></a>
<table><thead align="left"><tr id="row334156160093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1228040278093524"><a name="p1228040278093524"></a><a name="p1228040278093524"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2840654093524"><a name="p2840654093524"></a><a name="p2840654093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row44750899093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p231460126093524"><a name="p231460126093524"></a><a name="p231460126093524"></a><a href="BundleManager.md#ga3abe15ac14571de84ca72c98f4009724">ClearElement</a> (<a href="ElementName.md">ElementName</a> *element)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p504266708093524"><a name="p504266708093524"></a><a name="p504266708093524"></a>void&nbsp;</p>
<p id="p1460624492093524"><a name="p1460624492093524"></a><a name="p1460624492093524"></a>Clears the internal data of a specified <strong id="b961138592093524"><a name="b961138592093524"></a><a name="b961138592093524"></a><a href="ElementName.md">ElementName</a></strong>. </p>
</td>
</tr>
<tr id="row1906777353093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1386157326093524"><a name="p1386157326093524"></a><a name="p1386157326093524"></a><a href="BundleManager.md#ga90e16f159ee8e7f1a9385feebb3dbc0c">SetElementDeviceID</a> (<a href="ElementName.md">ElementName</a> *element, const char *deviceId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p187687761093524"><a name="p187687761093524"></a><a name="p187687761093524"></a>bool&nbsp;</p>
<p id="p567326309093524"><a name="p567326309093524"></a><a name="p567326309093524"></a>Sets the device ID used to query <a href="AbilityInfo.md">AbilityInfo</a>. </p>
</td>
</tr>
<tr id="row482255498093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1493016093524"><a name="p1493016093524"></a><a name="p1493016093524"></a><a href="BundleManager.md#ga60692e66a3a204a2f16f70c5cd452c1d">SetElementBundleName</a> (<a href="ElementName.md">ElementName</a> *element, const char *bundleName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1911366541093524"><a name="p1911366541093524"></a><a name="p1911366541093524"></a>bool&nbsp;</p>
<p id="p830119332093524"><a name="p830119332093524"></a><a name="p830119332093524"></a>Sets the bundle name used to query <a href="AbilityInfo.md">AbilityInfo</a>. </p>
</td>
</tr>
<tr id="row404784956093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1709912674093524"><a name="p1709912674093524"></a><a name="p1709912674093524"></a><a href="BundleManager.md#ga93a575cc428cb96526ae02b3997f1f3b">SetElementAbilityName</a> (<a href="ElementName.md">ElementName</a> *element, const char *abilityName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p362346621093524"><a name="p362346621093524"></a><a name="p362346621093524"></a>bool&nbsp;</p>
<p id="p1875017114093524"><a name="p1875017114093524"></a><a name="p1875017114093524"></a>Sets the class name of the ability used to query <a href="AbilityInfo.md">AbilityInfo</a>. </p>
</td>
</tr>
</tbody>
</table>

