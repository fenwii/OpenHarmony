# CameraAbility<a name="ZH-CN_TOPIC_0000001054094140"></a>

## **Overview**<a name="section2006563881113033"></a>

**Related Modules:**

[MultiMedia\_CameraAbility](MultiMedia_CameraAbility.md)

**Description:**

Declares functions of the  **[CameraAbility](CameraAbility.md)**  class. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2104562814113033"></a>

## Public Member Functions<a name="pub-methods"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_CameraAbility.md#ga7f1b94b32f7c7b121ea14b3147788497">CameraAbility</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p> &nbsp;</p>
<p>constructed function. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_CameraAbility.md#ga797435bcd10278e33fb7b6f4951f0d7f">~CameraAbility</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p> virtual&nbsp;</p>
<p>destructor function. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_CameraAbility.md#ga840850d531b96cc5a829b257ade3c7e6">GetSupportedSizes</a> (int format) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>std::list&lt; CameraPicSize &gt;&nbsp;</p>
<p>Obtains the supported image sizes for a specified image format. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_CameraAbility.md#ga191e1cf20062b485c4bb5ff89a59605e">GetSupportedAeMode</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>std::list&lt; int32_t &gt;&nbsp;</p>
<p>Obtains the supported auto exposure modes. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_CameraAbility.md#gacd0357f6d263600c4d288c03ffde31fc">GetSupportedParameters</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>std::list&lt; uint32_t &gt;&nbsp;</p>
<p>Obtains the parameters supported by the camera. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;&nbsp;</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p></p>
<p>Obtains the parameter value range based on a specified parameter key. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_CameraAbility.md#ga1d83b65d5bd01d1a7f805df4b6b07122">GetSupportedResults</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>std::list&lt; uint32_t &gt;&nbsp;</p>
<p>Obtains the keys of returnable results related to the parameter settings supported by the camera. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="MultiMedia_CameraAbility.md#ga2089757300e3f34aba4e8d71e96ad72a">GetSupportedProperties</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>std::list&lt; uint32_t &gt;&nbsp;</p>
<p>Obtains the properties supported by the camera. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;&nbsp;</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p></p>
<p>Obtains the value of a specified property key. </p>
</td>
</tr>
</tbody>
</table>

