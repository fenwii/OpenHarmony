# OHOS::Media::Camera<a name="ZH-CN_TOPIC_0000001055078149"></a>

## **Overview**<a name="section455850576084837"></a>

**Related Modules:**

[MultiMedia\_Camera](MultiMedia_Camera.md)

**Description:**

Provides functions in the  **[Camera](OHOS-Media-Camera.md)**  class to implement camera operations. operations. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section693905067084837"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1534326397084837"></a>
<table><thead align="left"><tr id="row1212986860084837"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2122580763084837"><a name="p2122580763084837"></a><a name="p2122580763084837"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1817490957084837"><a name="p1817490957084837"></a><a name="p1817490957084837"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1851377578084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p570807519084837"><a name="p570807519084837"></a><a name="p570807519084837"></a><a href="MultiMedia_Camera.md#gab24c0e4ca1e15bb2a481fb1550955611">~Camera</a> ()=default</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1714813098084837"><a name="p1714813098084837"></a><a name="p1714813098084837"></a>virtual&nbsp;</p>
<p id="p1792733091084837"><a name="p1792733091084837"></a><a name="p1792733091084837"></a>A destructor used to delete the <strong id="b776008023084837"><a name="b776008023084837"></a><a name="b776008023084837"></a><a href="OHOS-Media-Camera.md">Camera</a></strong> instance. </p>
</td>
</tr>
<tr id="row753751485084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1124650315084837"><a name="p1124650315084837"></a><a name="p1124650315084837"></a><a href="MultiMedia_Camera.md#ga4b6fec3c9290e7d388147dcdd288b918">GetCameraId</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p734845198084837"><a name="p734845198084837"></a><a name="p734845198084837"></a>virtual std::string&nbsp;</p>
<p id="p382935395084837"><a name="p382935395084837"></a><a name="p382935395084837"></a>Obtains the camera ID. </p>
</td>
</tr>
<tr id="row810391028084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1583135111084837"><a name="p1583135111084837"></a><a name="p1583135111084837"></a><a href="MultiMedia_Camera.md#ga04cc021b827824d0363037b630326264">GetCameraConfig</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p904752093084837"><a name="p904752093084837"></a><a name="p904752093084837"></a>virtual const <a href="OHOS-Media-CameraConfig.md">CameraConfig</a> *&nbsp;</p>
<p id="p876404331084837"><a name="p876404331084837"></a><a name="p876404331084837"></a>Obtains the camera configuration. You can use the obtained <strong id="b933516020084837"><a name="b933516020084837"></a><a name="b933516020084837"></a><a href="OHOS-Media-CameraConfig.md">CameraConfig</a></strong> object to configure the camera. </p>
</td>
</tr>
<tr id="row1708267102084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1563983965084837"><a name="p1563983965084837"></a><a name="p1563983965084837"></a><a href="MultiMedia_Camera.md#ga4e3f97ac484b85cd221a996689a3de61">GetFrameConfig</a> (int32_t type)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1813904243084837"><a name="p1813904243084837"></a><a name="p1813904243084837"></a>virtual <a href="OHOS-Media-FrameConfig.md">FrameConfig</a> *&nbsp;</p>
<p id="p550510690084837"><a name="p550510690084837"></a><a name="p550510690084837"></a>Obtains the frame configuration. </p>
</td>
</tr>
<tr id="row1008285181084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1639012422084837"><a name="p1639012422084837"></a><a name="p1639012422084837"></a><a href="MultiMedia_Camera.md#ga5f240a74fefa168cbf94b4603b76ef7b">Configure</a> (<a href="OHOS-Media-CameraConfig.md">CameraConfig</a> &amp;config)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1159911130084837"><a name="p1159911130084837"></a><a name="p1159911130084837"></a>virtual void&nbsp;</p>
<p id="p1735959964084837"><a name="p1735959964084837"></a><a name="p1735959964084837"></a>Configures the camera using the <strong id="b42621797084837"><a name="b42621797084837"></a><a name="b42621797084837"></a><a href="OHOS-Media-CameraConfig.md">CameraConfig</a></strong> object. </p>
</td>
</tr>
<tr id="row63521441084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p292416924084837"><a name="p292416924084837"></a><a name="p292416924084837"></a><a href="MultiMedia_Camera.md#ga1cd68b1b385da5224dbfdb6993c5cf08">TriggerLoopingCapture</a> (<a href="OHOS-Media-FrameConfig.md">FrameConfig</a> &amp;frameConfig)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p630399138084837"><a name="p630399138084837"></a><a name="p630399138084837"></a>virtual int32_t&nbsp;</p>
<p id="p1636203630084837"><a name="p1636203630084837"></a><a name="p1636203630084837"></a>Triggers looping-frame capture. </p>
</td>
</tr>
<tr id="row1186007180084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p271155847084837"><a name="p271155847084837"></a><a name="p271155847084837"></a><a href="MultiMedia_Camera.md#ga564c26b845affb1dbe05d4d7982ed1ad">StopLoopingCapture</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1575040783084837"><a name="p1575040783084837"></a><a name="p1575040783084837"></a>virtual void&nbsp;</p>
<p id="p1521137653084837"><a name="p1521137653084837"></a><a name="p1521137653084837"></a>Stops looping-frame capture. </p>
</td>
</tr>
<tr id="row114011837084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p488171572084837"><a name="p488171572084837"></a><a name="p488171572084837"></a><a href="MultiMedia_Camera.md#gac05d783b1655fe505a4afa23496d7e84">TriggerSingleCapture</a> (<a href="OHOS-Media-FrameConfig.md">FrameConfig</a> &amp;frameConfig)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2002552335084837"><a name="p2002552335084837"></a><a name="p2002552335084837"></a>virtual int32_t&nbsp;</p>
<p id="p1055588723084837"><a name="p1055588723084837"></a><a name="p1055588723084837"></a>Starts single-frame capture. The frame parameters are set through the <strong id="b581899579084837"><a name="b581899579084837"></a><a name="b581899579084837"></a><a href="OHOS-Media-FrameConfig.md">FrameConfig</a></strong> object, and the captured image data is stored in the surface of the <strong id="b1098400045084837"><a name="b1098400045084837"></a><a name="b1098400045084837"></a><a href="OHOS-Media-FrameConfig.md">FrameConfig</a></strong> object. </p>
</td>
</tr>
<tr id="row671673900084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1703725359084837"><a name="p1703725359084837"></a><a name="p1703725359084837"></a><a href="MultiMedia_Camera.md#ga7986d17e54fe9cd77df9465287fa5643">Release</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p39673563084837"><a name="p39673563084837"></a><a name="p39673563084837"></a>virtual void&nbsp;</p>
<p id="p1949066734084837"><a name="p1949066734084837"></a><a name="p1949066734084837"></a>Releases the <strong id="b205875486084837"><a name="b205875486084837"></a><a name="b205875486084837"></a><a href="OHOS-Media-Camera.md">Camera</a></strong> object and associated resources. </p>
</td>
</tr>
</tbody>
</table>

## Protected Member Functions<a name="pro-methods"></a>

<a name="table1421329586084837"></a>
<table><thead align="left"><tr id="row1022501532084837"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1409017724084837"><a name="p1409017724084837"></a><a name="p1409017724084837"></a>Protected Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p108168340084837"><a name="p108168340084837"></a><a name="p108168340084837"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2124729560084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p348110938084837"><a name="p348110938084837"></a><a name="p348110938084837"></a><a href="MultiMedia_Camera.md#ga7df4eba3316a6fe7c623e420c0a295e5">Camera</a> ()=default</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p554468712084837"><a name="p554468712084837"></a><a name="p554468712084837"></a>&nbsp;</p>
<p id="p1775436573084837"><a name="p1775436573084837"></a><a name="p1775436573084837"></a>A constructor used to create a <strong id="b1800210354084837"><a name="b1800210354084837"></a><a name="b1800210354084837"></a><a href="OHOS-Media-Camera.md">Camera</a></strong> instance. </p>
</td>
</tr>
</tbody>
</table>

