# Camera<a name="ZH-CN_TOPIC_0000001054094209"></a>

## **Overview**<a name="section1433807515113033"></a>

**Related Modules:**

[MultiMedia\_Camera](MultiMedia_Camera.md)

**Description:**

Declares functions in the  **[Camera](Camera.md)**  class to implement camera operations. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section534839265113033"></a>

## Public Member Functions<a name="pub-methods"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_Camera.md#gab24c0e4ca1e15bb2a481fb1550955611">~Camera</a> ()=default</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p> virtual&nbsp;</p>
<p>destructor function. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_Camera.md#ga4b6fec3c9290e7d388147dcdd288b918">GetCameraId</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual std::string&nbsp;</p>
<p>Obtains the camera ID. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_Camera.md#ga04cc021b827824d0363037b630326264">GetCameraConfig</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual const CameraConfig *&nbsp;</p>
<p>Obtains the camera configuration. You can use the obtained <strong>CameraConfig</strong> object to configure the camera. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_Camera.md#ga4e3f97ac484b85cd221a996689a3de61">GetFrameConfig</a> (int32_t type)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual <a href="FrameConfig.md">FrameConfig</a> *&nbsp;</p>
<p>Obtains the frame configuration. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_Camera.md#ga5f240a74fefa168cbf94b4603b76ef7b">Configure</a> (CameraConfig &amp;config)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual void&nbsp;</p>
<p>Configures the camera using the <strong>CameraConfig</strong> object. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_Camera.md#ga1cd68b1b385da5224dbfdb6993c5cf08">TriggerLoopingCapture</a> (<a href="FrameConfig.md">FrameConfig</a> &amp;frameConfig)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual int32_t&nbsp;</p>
<p>Triggers looping-frame capture. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_Camera.md#ga564c26b845affb1dbe05d4d7982ed1ad">StopLoopingCapture</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual void&nbsp;</p>
<p>Stops looping-frame capture. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_Camera.md#gac05d783b1655fe505a4afa23496d7e84">TriggerSingleCapture</a> (<a href="FrameConfig.md">FrameConfig</a> &amp;frameConfig)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>virtual int32_t&nbsp;</p>
<p>Starts single-frame capture. The frame parameters are set through the <strong><a href="FrameConfig.md">FrameConfig</a></strong> object, and the captured image data is stored in the surface of the <strong><a href="FrameConfig.md">FrameConfig</a></strong> object. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_Camera.md#ga7986d17e54fe9cd77df9465287fa5643">Release</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p> virtual void&nbsp;</p>
<p>Releases the <strong><a href="Camera.md">Camera</a></strong> object and associated resources. </p>
</td>
</tr>
</tbody>
</table>

## Protected Member Functions<a name="pro-methods"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Protected Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_Camera.md#ga7df4eba3316a6fe7c623e420c0a295e5">Camera</a> ()=default</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p> &nbsp;</p>
<p>constructed function. </p>
</td>
</tr>
</tbody>
</table>

