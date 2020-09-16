# OHOS::Media::CameraStateCallback<a name="EN-US_TOPIC_0000001055358118"></a>

## **Overview**<a name="section1192860886084837"></a>

**Related Modules:**

[MultiMedia\_CameraStateCallback](multimedia_camerastatecallback.md)

**Description:**

Provides functions to response to camera states. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1385326206084837"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table993882186084837"></a>
<table><thead align="left"><tr id="row1642032164084837"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1628780351084837"><a name="p1628780351084837"></a><a name="p1628780351084837"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1933074763084837"><a name="p1933074763084837"></a><a name="p1933074763084837"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row115358837084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1828943655084837"><a name="p1828943655084837"></a><a name="p1828943655084837"></a><a href="multimedia_camerastatecallback.md#gaa9499b36ed4aac41a67065f62342df70">CameraStateCallback</a> ()=default</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p105220139084837"><a name="p105220139084837"></a><a name="p105220139084837"></a> </p>
<p id="p2013635481084837"><a name="p2013635481084837"></a><a name="p2013635481084837"></a>A constructor used to create a <strong id="b357147616084837"><a name="b357147616084837"></a><a name="b357147616084837"></a><a href="ohos-media-camerastatecallback.md">CameraStateCallback</a></strong> instance. </p>
</td>
</tr>
<tr id="row1662588644084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1436476135084837"><a name="p1436476135084837"></a><a name="p1436476135084837"></a><a href="multimedia_camerastatecallback.md#ga80ba3b334f93c4d9cab07bc749813f9a">~CameraStateCallback</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2932673084837"><a name="p2932673084837"></a><a name="p2932673084837"></a>virtual </p>
<p id="p1506380074084837"><a name="p1506380074084837"></a><a name="p1506380074084837"></a>A destructor used to delete the <strong id="b325563648084837"><a name="b325563648084837"></a><a name="b325563648084837"></a><a href="ohos-media-camerastatecallback.md">CameraStateCallback</a></strong> instance. </p>
</td>
</tr>
<tr id="row1496042617084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1725712289084837"><a name="p1725712289084837"></a><a name="p1725712289084837"></a><a href="multimedia_camerastatecallback.md#ga29901c517d444a013d44a99350905390">OnCreated</a> (<a href="ohos-media-camera.md">Camera</a> &amp;c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1636818446084837"><a name="p1636818446084837"></a><a name="p1636818446084837"></a>virtual void </p>
<p id="p1569506649084837"><a name="p1569506649084837"></a><a name="p1569506649084837"></a>Called when the camera is successfully created. </p>
</td>
</tr>
<tr id="row1161319698084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1322753927084837"><a name="p1322753927084837"></a><a name="p1322753927084837"></a><a href="multimedia_camerastatecallback.md#ga9844a6e2c1d4295fe23537a918bdc683">OnCreateFailed</a> (const std::string cameraId, int32_t errorCode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p652702112084837"><a name="p652702112084837"></a><a name="p652702112084837"></a>virtual void </p>
<p id="p1776162075084837"><a name="p1776162075084837"></a><a name="p1776162075084837"></a>Called when the camera fails to be created. </p>
</td>
</tr>
<tr id="row533440666084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2006532559084837"><a name="p2006532559084837"></a><a name="p2006532559084837"></a><a href="multimedia_camerastatecallback.md#ga4351c9011831fe3e93d986e5a287fe80">OnReleased</a> (<a href="ohos-media-camera.md">Camera</a> &amp;c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p612285546084837"><a name="p612285546084837"></a><a name="p612285546084837"></a>virtual void </p>
<p id="p1308283547084837"><a name="p1308283547084837"></a><a name="p1308283547084837"></a>Called when the camera is released. </p>
</td>
</tr>
<tr id="row1766493792084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1491168446084837"><a name="p1491168446084837"></a><a name="p1491168446084837"></a><a href="multimedia_camerastatecallback.md#ga5a0115afe9c5a7ddf8e9acd93a03fd21">OnConfigured</a> (<a href="ohos-media-camera.md">Camera</a> &amp;c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p597015559084837"><a name="p597015559084837"></a><a name="p597015559084837"></a>virtual void </p>
<p id="p1018752427084837"><a name="p1018752427084837"></a><a name="p1018752427084837"></a>Called when the camera is configured. </p>
</td>
</tr>
<tr id="row1731659382084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1272043111084837"><a name="p1272043111084837"></a><a name="p1272043111084837"></a><a href="multimedia_camerastatecallback.md#gab334119760044ef810ce8ac2301c0d16">OnConfigureFailed</a> (const std::string cameraId, int32_t errorCode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2102965863084837"><a name="p2102965863084837"></a><a name="p2102965863084837"></a>virtual void </p>
<p id="p1070773310084837"><a name="p1070773310084837"></a><a name="p1070773310084837"></a>Called when the camera fails to be configured. </p>
</td>
</tr>
</tbody>
</table>

