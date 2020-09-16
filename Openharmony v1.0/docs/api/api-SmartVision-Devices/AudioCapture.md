# AudioCapture<a name="ZH-CN_TOPIC_0000001055358098"></a>

## **Overview**<a name="section1550799600093529"></a>

**Related Modules:**

[Audio](Audio.md)

**Description:**

Provides capabilities for audio capturing, including controlling the capturing, setting audio attributes, scenes, and volume, and capturing audio frames. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section595577548093529"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1641141835093529"></a>
<table><thead align="left"><tr id="row1490799119093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p347042305093529"><a name="p347042305093529"></a><a name="p347042305093529"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1643032236093529"><a name="p1643032236093529"></a><a name="p1643032236093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1633996888093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p202617334093529"><a name="p202617334093529"></a><a name="p202617334093529"></a><em id="a3722b1e55fa79af775b5d3acd08f29c4"><a name="a3722b1e55fa79af775b5d3acd08f29c4"></a><a name="a3722b1e55fa79af775b5d3acd08f29c4"></a></em>control </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1885462155093529"><a name="p1885462155093529"></a><a name="p1885462155093529"></a><strong id="a3722b1e55fa79af775b5d3acd08f29c4_1"><a name="a3722b1e55fa79af775b5d3acd08f29c4_1"></a><a name="a3722b1e55fa79af775b5d3acd08f29c4_1"></a></strong> struct <a href="AudioControl.md">AudioControl</a>&nbsp;</p>
<p id="p1094414039093529"><a name="p1094414039093529"></a><a name="p1094414039093529"></a>Defines the audio control. For details, see <a href="AudioControl.md">AudioControl</a>. </p>
</td>
</tr>
<tr id="row929769433093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p598134718093529"><a name="p598134718093529"></a><a name="p598134718093529"></a><em id="a3b1231763ecdab4d60809048136ae017"><a name="a3b1231763ecdab4d60809048136ae017"></a><a name="a3b1231763ecdab4d60809048136ae017"></a></em>attr </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p928200404093529"><a name="p928200404093529"></a><a name="p928200404093529"></a><strong id="a3b1231763ecdab4d60809048136ae017_1"><a name="a3b1231763ecdab4d60809048136ae017_1"></a><a name="a3b1231763ecdab4d60809048136ae017_1"></a></strong> struct <a href="AudioAttribute.md">AudioAttribute</a>&nbsp;</p>
<p id="p1088516646093529"><a name="p1088516646093529"></a><a name="p1088516646093529"></a>Defines the audio attribute. For details, see <a href="AudioAttribute.md">AudioAttribute</a>. </p>
</td>
</tr>
<tr id="row2044678942093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1396988978093529"><a name="p1396988978093529"></a><a name="p1396988978093529"></a><em id="a55ba54428fc285c97032ce27ae0ab4aa"><a name="a55ba54428fc285c97032ce27ae0ab4aa"></a><a name="a55ba54428fc285c97032ce27ae0ab4aa"></a></em>scene </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p548690535093529"><a name="p548690535093529"></a><a name="p548690535093529"></a><strong id="a55ba54428fc285c97032ce27ae0ab4aa_1"><a name="a55ba54428fc285c97032ce27ae0ab4aa_1"></a><a name="a55ba54428fc285c97032ce27ae0ab4aa_1"></a></strong> struct <a href="AudioScene.md">AudioScene</a>&nbsp;</p>
<p id="p555674588093529"><a name="p555674588093529"></a><a name="p555674588093529"></a>Defines the audio scene. For details, see <a href="AudioScene.md">AudioScene</a>. </p>
</td>
</tr>
<tr id="row1245657443093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2014839697093529"><a name="p2014839697093529"></a><a name="p2014839697093529"></a><em id="a066923e8aff005d677c7b7c33a036f41"><a name="a066923e8aff005d677c7b7c33a036f41"></a><a name="a066923e8aff005d677c7b7c33a036f41"></a></em>volume </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1757452737093529"><a name="p1757452737093529"></a><a name="p1757452737093529"></a><strong id="a066923e8aff005d677c7b7c33a036f41_1"><a name="a066923e8aff005d677c7b7c33a036f41_1"></a><a name="a066923e8aff005d677c7b7c33a036f41_1"></a></strong> struct <a href="AudioVolume.md">AudioVolume</a>&nbsp;</p>
<p id="p1506348135093529"><a name="p1506348135093529"></a><a name="p1506348135093529"></a>Defines audio volume. For details, see <a href="AudioVolume.md">AudioVolume</a>. </p>
</td>
</tr>
<tr id="row1043506489093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p144334651093529"><a name="p144334651093529"></a><a name="p144334651093529"></a><a href="AudioCapture.md#a89f1baf4b6177f91b9135e86cc8681da">CaptureFrame</a> )(struct <a href="AudioCapture.md">AudioCapture</a> *capture, void *frame, uint64_t requestBytes, uint64_t *replyBytes)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1129021365093529"><a name="p1129021365093529"></a><a name="p1129021365093529"></a>int32_t(*&nbsp;</p>
<p id="p619466526093529"><a name="p619466526093529"></a><a name="p619466526093529"></a>Reads a frame of input data (uplink data) from the audio driver for capturing. </p>
</td>
</tr>
<tr id="row9833962093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1403013655093529"><a name="p1403013655093529"></a><a name="p1403013655093529"></a><a href="AudioCapture.md#ad307fd1eca38f257f865c1316db6e5d5">GetCapturePosition</a> )(struct <a href="AudioCapture.md">AudioCapture</a> *capture, uint64_t *frames, struct <a href="AudioTimeStamp.md">AudioTimeStamp</a> *<a href="zh-cn_topic_0000001054879478.md#gae7841e681c8c9d59818568d39553642c">time</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p773940120093529"><a name="p773940120093529"></a><a name="p773940120093529"></a>int32_t(*&nbsp;</p>
<p id="p1116354382093529"><a name="p1116354382093529"></a><a name="p1116354382093529"></a>Obtains the last number of input audio frames. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section582608160093529"></a>

## **Field Documentation**<a name="section492081041093529"></a>

## CaptureFrame<a name="a89f1baf4b6177f91b9135e86cc8681da"></a>

```
int32_t(* AudioCapture::CaptureFrame) (struct [AudioCapture](AudioCapture.md) *capture, void *frame, uint64_t requestBytes, uint64_t *replyBytes)
```

 **Description:**

Reads a frame of input data \(uplink data\) from the audio driver for capturing. 

**Parameters:**

<a name="table140051798093529"></a>
<table><thead align="left"><tr id="row1394800258093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p577538040093529"><a name="p577538040093529"></a><a name="p577538040093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p235927425093529"><a name="p235927425093529"></a><a name="p235927425093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row527086799093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">capture</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b1433720451093529"><a name="b1433720451093529"></a><a name="b1433720451093529"></a><a href="AudioCapture.md">AudioCapture</a></strong> object to operate. </td>
</tr>
<tr id="row2115926708093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">frame</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the input data to read. </td>
</tr>
<tr id="row1952493270093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">requestBytes</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the input data, in bytes. </td>
</tr>
<tr id="row1289968801093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">replyBytes</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the actual length (in bytes) of the audio data to read. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the input data is read successfully; returns a negative value otherwise. 



## GetCapturePosition<a name="ad307fd1eca38f257f865c1316db6e5d5"></a>

```
int32_t(* AudioCapture::GetCapturePosition) (struct [AudioCapture](AudioCapture.md) *capture, uint64_t *frames, struct [AudioTimeStamp](AudioTimeStamp.md) *[time](zh-cn_topic_0000001054879478.md#gae7841e681c8c9d59818568d39553642c))
```

 **Description:**

Obtains the last number of input audio frames. 

**Parameters:**

<a name="table87355972093529"></a>
<table><thead align="left"><tr id="row1167051633093529"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p379980165093529"><a name="p379980165093529"></a><a name="p379980165093529"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p721145769093529"><a name="p721145769093529"></a><a name="p721145769093529"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1266347294093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">capture</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b862984819093529"><a name="b862984819093529"></a><a name="b862984819093529"></a><a href="AudioCapture.md">AudioCapture</a></strong> object to operate. </td>
</tr>
<tr id="row1834905831093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">frames</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the last number of input audio frames. </td>
</tr>
<tr id="row671286905093529"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">time</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the timestamp associated with the frame. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the last number is obtained; returns a negative value otherwise. 

**See also:**

[CaptureFrame](AudioCapture.md#a89f1baf4b6177f91b9135e86cc8681da) 

