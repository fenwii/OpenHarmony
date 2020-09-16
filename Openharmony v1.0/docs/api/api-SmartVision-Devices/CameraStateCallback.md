# CameraStateCallback<a name="ZH-CN_TOPIC_0000001054414161"></a>

## **Overview**<a name="section780111076113033"></a>

**Related Modules:**

[MultiMedia\_CameraStateCallback](MultiMedia_CameraStateCallback.md)

**Description:**

Declares functions in the  **[CameraStateCallback](CameraStateCallback.md)**  class. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1198182525113033"></a>

## Public Member Functions<a name="pub-methods"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_CameraStateCallback.md#gaa9499b36ed4aac41a67065f62342df70">CameraStateCallback</a> ()=default</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p> &nbsp;</p>
<p>constructed function. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_CameraStateCallback.md#ga80ba3b334f93c4d9cab07bc749813f9a">~CameraStateCallback</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p> virtual&nbsp;</p>
<p>destructor function. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_CameraStateCallback.md#ga29901c517d444a013d44a99350905390">OnCreated</a> (<a href="Camera.md">Camera</a> &amp;c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual void&nbsp;</p>
<p>Called when the camera is successfully created. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_CameraStateCallback.md#ga9844a6e2c1d4295fe23537a918bdc683">OnCreateFailed</a> (const std::string cameraId, int32_t errorCode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual void&nbsp;</p>
<p>Called when the camera fails to be created. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_CameraStateCallback.md#ga4351c9011831fe3e93d986e5a287fe80">OnReleased</a> (<a href="Camera.md">Camera</a> &amp;c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual void&nbsp;</p>
<p>Called when the camera is released. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_CameraStateCallback.md#ga5a0115afe9c5a7ddf8e9acd93a03fd21">OnConfigured</a> (<a href="Camera.md">Camera</a> &amp;c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual void&nbsp;</p>
<p>Called when the camera is configured. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_CameraStateCallback.md#gab334119760044ef810ce8ac2301c0d16">OnConfigureFailed</a> (const std::string cameraId, int32_t errorCode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual void&nbsp;</p>
<p>Called when the camera fails to be configured. </p>
</td>
</tr>
</tbody>
</table>

