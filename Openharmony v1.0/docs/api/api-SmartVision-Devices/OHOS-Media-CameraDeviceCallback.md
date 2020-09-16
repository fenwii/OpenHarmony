# OHOS::Media::CameraDeviceCallback<a name="ZH-CN_TOPIC_0000001055198140"></a>

## **Overview**<a name="section22242444084837"></a>

**Related Modules:**

[MuiltiMedia\_CameraDeviceCallback](MuiltiMedia_CameraDeviceCallback.md)

**Description:**

Provides functions to response to device changes. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section939279060084837"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table63365618084837"></a>
<table><thead align="left"><tr id="row488775744084837"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2085697336084837"><a name="p2085697336084837"></a><a name="p2085697336084837"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p899200295084837"><a name="p899200295084837"></a><a name="p899200295084837"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row743254399084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p830904546084837"><a name="p830904546084837"></a><a name="p830904546084837"></a><a href="MuiltiMedia_CameraDeviceCallback.md#ga5e81f9fa5dd53d9d1f8ca0cc4497fd59">CameraDeviceCallback</a> ()=default</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1918113253084837"><a name="p1918113253084837"></a><a name="p1918113253084837"></a>&nbsp;</p>
<p id="p2044627039084837"><a name="p2044627039084837"></a><a name="p2044627039084837"></a>A constructor used to create a <strong id="b1371388698084837"><a name="b1371388698084837"></a><a name="b1371388698084837"></a><a href="OHOS-Media-CameraDeviceCallback.md">CameraDeviceCallback</a></strong> instance. </p>
</td>
</tr>
<tr id="row1442282571084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1463892480084837"><a name="p1463892480084837"></a><a name="p1463892480084837"></a><a href="MuiltiMedia_CameraDeviceCallback.md#gac88b6972227ec2ba65feeb15c31aea83">~CameraDeviceCallback</a> ()=default</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1152635674084837"><a name="p1152635674084837"></a><a name="p1152635674084837"></a>virtual&nbsp;</p>
<p id="p154859668084837"><a name="p154859668084837"></a><a name="p154859668084837"></a>A destructor used to delete the <strong id="b744581697084837"><a name="b744581697084837"></a><a name="b744581697084837"></a><a href="OHOS-Media-CameraDeviceCallback.md">CameraDeviceCallback</a></strong> instance. </p>
</td>
</tr>
<tr id="row983509211084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1642425549084837"><a name="p1642425549084837"></a><a name="p1642425549084837"></a><a href="MuiltiMedia_CameraDeviceCallback.md#ga2ae4d3d8ae13f73986f8dc7cf4bb7960">OnCameraStatus</a> (std::string cameraId, int32_t status)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p239148770084837"><a name="p239148770084837"></a><a name="p239148770084837"></a>virtual void&nbsp;</p>
<p id="p932860682084837"><a name="p932860682084837"></a><a name="p932860682084837"></a>Called when the camera state changes. </p>
</td>
</tr>
</tbody>
</table>

