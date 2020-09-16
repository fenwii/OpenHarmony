# FrameConfig<a name="ZH-CN_TOPIC_0000001054094144"></a>

## **Overview**<a name="section851545612113033"></a>

**Related Modules:**

[MultiMedia\_FrameConfig](MultiMedia_FrameConfig.md)

**Description:**

Declares APIs of the  **[FrameConfig](FrameConfig.md)**  class. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section933933672113033"></a>

## Public Member Functions<a name="pub-methods"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_FrameConfig.md#ga043537d52f5db46d981f9e89848b0fba">FrameConfig</a> ()=delete</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p> &nbsp;</p>
<p>constructed function; </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_FrameConfig.md#gac8f74ff3689605a59a17997bdeaec1fc">FrameConfig</a> (int32_t type)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p> &nbsp;</p>
<p>constructed function by a param </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_FrameConfig.md#gaa2e58c2ce602d9263b76596374823616">~FrameConfig</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p> &nbsp;</p>
<p>destructor function. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_FrameConfig.md#ga382977445a583ed0424c5ccf581e824c">GetFrameConfigType</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int32_t&nbsp;</p>
<p>Obtains the frame configuration type. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_FrameConfig.md#ga955d04df96c009e4699ea6ed46d9e758">GetSurfaces</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>std::list&lt; <a href="OHOS-Surface.md">Surface</a> * &gt;&nbsp;</p>
<p>Obtains a list of shared memories (surface objects). </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_FrameConfig.md#ga2bd863a5547e60869f3d3d1d74d81be0">GetAeMode</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int32_t&nbsp;</p>
<p>Obtains the auto exposure mode. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_FrameConfig.md#gabb80bb69be64811636d458dd3277a360">GetAeRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>CameraRect&nbsp;</p>
<p>Obtains the auto exposure region. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_FrameConfig.md#ga2f63711483f6cdbf48606a28cb527c35">GetImageRotation</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int32_t&nbsp;</p>
<p>Obtains the image rotation mode. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_FrameConfig.md#ga79182a9a02696de0b82f4869a18a87d8">GetKeys</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>std::list&lt; uint32_t &gt;&nbsp;</p>
<p>Obtains keys of parameters that can be configured. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_FrameConfig.md#ga16760311713db03bf06ea0a6d6622013">AddSurface</a> (<a href="OHOS-Surface.md">Surface</a> &amp;surface)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Adds a surface (an object of shared memory). </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_FrameConfig.md#ga9ac4bc5e52840ee579482a3836774762">RemoveSurface</a> (<a href="OHOS-Surface.md">Surface</a> &amp;surface)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Removes a surface (an object of shared memory). You can call this function to release the surface when your application does not need to obtain data. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_FrameConfig.md#ga34ceaece8b453a6770a5b525f346fa37">SetAeMode</a> (int32_t aeMode, CameraRect &amp;rect)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Sets the auto exposure mode and exposure region. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_FrameConfig.md#ga1beece389ed07a6b3568c65c2ba3e011">SetImageRotation</a> (int32_t degrees)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>void&nbsp;</p>
<p>Sets the image rotation angle. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;&nbsp;</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p></p>
<p>Sets the common parameter. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;&nbsp;</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p></p>
<p>Obtains the value of a common parameter based on its key. For details, see <strong>CAMERA_FUC_KEY</strong>. </p>
</td>
</tr>
</tbody>
</table>

