# OHOS::Media::CameraKit<a name="ZH-CN_TOPIC_0000001054479573"></a>

## **Overview**<a name="section1846356450084837"></a>

**Related Modules:**

[MultiMedia\_CameraKit](MultiMedia_CameraKit.md)

**Description:**

Provides functions in the  **[CameraKit](OHOS-Media-CameraKit.md)**  class. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1128057952084837"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1737726919084837"></a>
<table><thead align="left"><tr id="row1438485495084837"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1311287129084837"><a name="p1311287129084837"></a><a name="p1311287129084837"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1530618767084837"><a name="p1530618767084837"></a><a name="p1530618767084837"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row932133213084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2003074278084837"><a name="p2003074278084837"></a><a name="p2003074278084837"></a><a href="MultiMedia_CameraKit.md#ga7d36867ec1bd57e25d1c60b5de24cbe6">~CameraKit</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1908203702084837"><a name="p1908203702084837"></a><a name="p1908203702084837"></a>&nbsp;</p>
<p id="p823664340084837"><a name="p823664340084837"></a><a name="p823664340084837"></a>A destructor used to delete the <strong id="b2017646138084837"><a name="b2017646138084837"></a><a name="b2017646138084837"></a><a href="OHOS-Media-CameraKit.md">CameraKit</a></strong> instance. </p>
</td>
</tr>
<tr id="row489768631084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p371433000084837"><a name="p371433000084837"></a><a name="p371433000084837"></a><a href="MultiMedia_CameraKit.md#ga8894d876198f2614d65b432a8a002163">GetCameraIds</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2137886597084837"><a name="p2137886597084837"></a><a name="p2137886597084837"></a>std::list&lt; std::string &gt;&nbsp;</p>
<p id="p827158600084837"><a name="p827158600084837"></a><a name="p827158600084837"></a>Obtains IDs of cameras that are currently available. </p>
</td>
</tr>
<tr id="row938847282084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1865418789084837"><a name="p1865418789084837"></a><a name="p1865418789084837"></a><a href="MultiMedia_CameraKit.md#gab4cfb051de29415d080a203ca4639448">GetCameraAbility</a> (std::string cameraId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1259713203084837"><a name="p1259713203084837"></a><a name="p1259713203084837"></a>const <a href="OHOS-Media-CameraAbility.md">CameraAbility</a> *&nbsp;</p>
<p id="p1208944555084837"><a name="p1208944555084837"></a><a name="p1208944555084837"></a>Obtains the camera capability, including the resolutions and frame rates. </p>
</td>
</tr>
<tr id="row1915957177084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1054839492084837"><a name="p1054839492084837"></a><a name="p1054839492084837"></a><a href="MultiMedia_CameraKit.md#ga4e6cd8787f06c4a82ad982d36029b3ec">RegisterCameraDeviceCallback</a> (<a href="OHOS-Media-CameraDeviceCallback.md">CameraDeviceCallback</a> &amp;callback, EventHandler &amp;handler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p579915727084837"><a name="p579915727084837"></a><a name="p579915727084837"></a>void&nbsp;</p>
<p id="p229129189084837"><a name="p229129189084837"></a><a name="p229129189084837"></a>Registers a camera callback for camera status changes and an event callback to respond to a triggered event. </p>
</td>
</tr>
<tr id="row1985856625084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p314398586084837"><a name="p314398586084837"></a><a name="p314398586084837"></a><a href="MultiMedia_CameraKit.md#ga4f0117575ee988f6d74a3636e01f0aba">UnregisterCameraDeviceCallback</a> (<a href="OHOS-Media-CameraDeviceCallback.md">CameraDeviceCallback</a> &amp;callback)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p842893368084837"><a name="p842893368084837"></a><a name="p842893368084837"></a>void&nbsp;</p>
<p id="p1009065650084837"><a name="p1009065650084837"></a><a name="p1009065650084837"></a>Unregisters a camera callback. </p>
</td>
</tr>
<tr id="row304292232084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1953192361084837"><a name="p1953192361084837"></a><a name="p1953192361084837"></a><a href="MultiMedia_CameraKit.md#gaa21f4e248e3a46a4f78f4261cba82fe2">CreateCamera</a> (const std::string &amp;cameraId, <a href="OHOS-Media-CameraStateCallback.md">CameraStateCallback</a> &amp;callback, EventHandler &amp;handler)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1156663941084837"><a name="p1156663941084837"></a><a name="p1156663941084837"></a>void&nbsp;</p>
<p id="p1047182015084837"><a name="p1047182015084837"></a><a name="p1047182015084837"></a>Creates a camera object. </p>
</td>
</tr>
</tbody>
</table>

## Static Public Member Functions<a name="pub-static-methods"></a>

<a name="table1262423450084837"></a>
<table><thead align="left"><tr id="row998005134084837"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p999865786084837"><a name="p999865786084837"></a><a name="p999865786084837"></a>Static Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1594590350084837"><a name="p1594590350084837"></a><a name="p1594590350084837"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row884513512084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p302820120084837"><a name="p302820120084837"></a><a name="p302820120084837"></a><a href="MultiMedia_CameraKit.md#ga1911ba8eca0e57ddc15df25cf2b21f7b">GetInstance</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1503563113084837"><a name="p1503563113084837"></a><a name="p1503563113084837"></a>static <a href="OHOS-Media-CameraKit.md">CameraKit</a> *&nbsp;</p>
<p id="p271702311084837"><a name="p271702311084837"></a><a name="p271702311084837"></a>Obtains a single instance of the <strong id="b1781434161084837"><a name="b1781434161084837"></a><a name="b1781434161084837"></a><a href="OHOS-Media-CameraKit.md">CameraKit</a></strong>. </p>
</td>
</tr>
</tbody>
</table>

