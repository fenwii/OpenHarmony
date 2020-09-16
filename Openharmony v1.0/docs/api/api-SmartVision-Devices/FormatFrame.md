# FormatFrame<a name="ZH-CN_TOPIC_0000001055039514"></a>

## **Overview**<a name="section279555793093530"></a>

**Related Modules:**

[Format](Format.md)

**Description:**

Defines the data frame, which is used for data transferring. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section384642120093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1497790836093530"></a>
<table><thead align="left"><tr id="row33732217093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1775649076093530"><a name="p1775649076093530"></a><a name="p1775649076093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p952200420093530"><a name="p952200420093530"></a><a name="p952200420093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1111986526093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p955714736093530"><a name="p955714736093530"></a><a name="p955714736093530"></a><a href="FormatFrame.md#a9cb91c927687f9875efa0d5600e04d1a">frameType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p735055668093530"><a name="p735055668093530"></a><a name="p735055668093530"></a><a href="Format.md#gad495a9f61af7fff07d7e97979d1ab854">FrameType</a>&nbsp;</p>
</td>
</tr>
<tr id="row1477348980093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1451603897093530"><a name="p1451603897093530"></a><a name="p1451603897093530"></a><a href="FormatFrame.md#a36d27cb02e6d06479354618e959a429a">trackId</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1700319205093530"><a name="p1700319205093530"></a><a name="p1700319205093530"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row1140089981093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p586576836093530"><a name="p586576836093530"></a><a name="p586576836093530"></a><a href="FormatFrame.md#a6a1cd875ac96a43d01524249a7f32026">isKeyFrame</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1415293647093530"><a name="p1415293647093530"></a><a name="p1415293647093530"></a>bool&nbsp;</p>
</td>
</tr>
<tr id="row249054281093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1449166326093530"><a name="p1449166326093530"></a><a name="p1449166326093530"></a><a href="FormatFrame.md#a290ab46c3660d73cde08b268bf36c323">timestampUs</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p922323956093530"><a name="p922323956093530"></a><a name="p922323956093530"></a>int64_t&nbsp;</p>
</td>
</tr>
<tr id="row1305691963093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1950740115093530"><a name="p1950740115093530"></a><a name="p1950740115093530"></a><a href="FormatFrame.md#ab342d9f6536876e5d0a5952a9043ca2d">durationUs</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p481822025093530"><a name="p481822025093530"></a><a name="p481822025093530"></a>int64_t&nbsp;</p>
</td>
</tr>
<tr id="row549532221093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p702188991093530"><a name="p702188991093530"></a><a name="p702188991093530"></a><a href="FormatFrame.md#a632575f46669a67c78ab28049e5654c6">data</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1719578098093530"><a name="p1719578098093530"></a><a name="p1719578098093530"></a>uint8_t *&nbsp;</p>
</td>
</tr>
<tr id="row63976146093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p675070914093530"><a name="p675070914093530"></a><a name="p675070914093530"></a><a href="FormatFrame.md#aa8bb4e843e90b0f4a7dd95d23faee65f">len</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p392468246093530"><a name="p392468246093530"></a><a name="p392468246093530"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row842131003093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p455451310093530"><a name="p455451310093530"></a><a name="p455451310093530"></a><a href="FormatFrame.md#a1a966266639de3b0b8db994232c71687">frameIndex</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p354637938093530"><a name="p354637938093530"></a><a name="p354637938093530"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row1096688480093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1080635909093530"><a name="p1080635909093530"></a><a name="p1080635909093530"></a><a href="FormatFrame.md#a8d0f0f738cab6d389423afd66dddcab2">position</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p302694082093530"><a name="p302694082093530"></a><a name="p302694082093530"></a>int64_t&nbsp;</p>
</td>
</tr>
<tr id="row151140162093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p125779450093530"><a name="p125779450093530"></a><a name="p125779450093530"></a><a href="FormatFrame.md#ace44c0b0dfc642c8a296e69b6a3e7d9d">itemCnt</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1446650218093530"><a name="p1446650218093530"></a><a name="p1446650218093530"></a>int32_t&nbsp;</p>
</td>
</tr>
<tr id="row1244592501093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1200445098093530"><a name="p1200445098093530"></a><a name="p1200445098093530"></a><a href="FormatFrame.md#a9739fdfe949e2464d14a0a2c56f3fff6">item</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1829556545093530"><a name="p1829556545093530"></a><a name="p1829556545093530"></a><a href="ParameterItem.md">ParameterItem</a> *&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section290234710093530"></a>

## **Field Documentation**<a name="section377043222093530"></a>

## data<a name="a632575f46669a67c78ab28049e5654c6"></a>

```
uint8_t* FormatFrame::data
```

 **Description:**

Address of the data frame buffer 

## durationUs<a name="ab342d9f6536876e5d0a5952a9043ca2d"></a>

```
int64_t FormatFrame::durationUs
```

 **Description:**

Data frame duration, in us 

## frameIndex<a name="a1a966266639de3b0b8db994232c71687"></a>

```
uint32_t FormatFrame::frameIndex
```

 **Description:**

Data frame index. For the MPF container, the value indicates the index of the sub-image frame. 

## frameType<a name="a9cb91c927687f9875efa0d5600e04d1a"></a>

```
[FrameType](Format.md#gad495a9f61af7fff07d7e97979d1ab854) FormatFrame::frameType
```

 **Description:**

Data frame type. For details, see  [FrameType](Format.md#gad495a9f61af7fff07d7e97979d1ab854). 

## isKeyFrame<a name="a6a1cd875ac96a43d01524249a7f32026"></a>

```
bool FormatFrame::isKeyFrame
```

 **Description:**

Keyframe flag.  **false**: The data frame is not a keyframe.  **true**: The data frame is a keyframe. 

## item<a name="a9739fdfe949e2464d14a0a2c56f3fff6"></a>

```
[ParameterItem](ParameterItem.md)* FormatFrame::item
```

 **Description:**

Pointer to the parameter array 

## itemCnt<a name="ace44c0b0dfc642c8a296e69b6a3e7d9d"></a>

```
int32_t FormatFrame::itemCnt
```

 **Description:**

Number of parameters, which can be used for information such as side data, PSSH, DRM, and HDR. 

## len<a name="aa8bb4e843e90b0f4a7dd95d23faee65f"></a>

```
uint32_t FormatFrame::len
```

 **Description:**

Data frame length 

## position<a name="a8d0f0f738cab6d389423afd66dddcab2"></a>

```
int64_t FormatFrame::position
```

 **Description:**

Position of the data frame in the file 

## timestampUs<a name="a290ab46c3660d73cde08b268bf36c323"></a>

```
int64_t FormatFrame::timestampUs
```

 **Description:**

Timestamp of a data frame, in us 

## trackId<a name="a36d27cb02e6d06479354618e959a429a"></a>

```
uint32_t FormatFrame::trackId
```

 **Description:**

Index of the track where the data frame is located 

