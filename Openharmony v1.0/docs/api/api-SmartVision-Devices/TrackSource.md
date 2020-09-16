# TrackSource<a name="ZH-CN_TOPIC_0000001055078179"></a>

## **Overview**<a name="section351713298084842"></a>

**Related Modules:**

[Format](Format.md)

**Description:**

Defines information about the muxer source. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1631620134084842"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table751733938084842"></a>
<table><thead align="left"><tr id="row1709016909084842"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1339020229084842"><a name="p1339020229084842"></a><a name="p1339020229084842"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1190343295084842"><a name="p1190343295084842"></a><a name="p1190343295084842"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row241190412084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p975374521084842"><a name="p975374521084842"></a><a name="p975374521084842"></a><a href="TrackSource.md#a39d729c668eddbf6b8403b7364e74b61">trackSourceType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p844334696084842"><a name="p844334696084842"></a><a name="p844334696084842"></a><a href="Format.md#ga953bc46f95d7b2d8866838d792f8f6aa">TrackSourceType</a>&nbsp;</p>
</td>
</tr>
<tr id="row1510191155084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2099702031084842"><a name="p2099702031084842"></a><a name="p2099702031084842"></a><em id="a3015a69b8b7b5afe4792ee2563ce220c"><a name="a3015a69b8b7b5afe4792ee2563ce220c"></a><a name="a3015a69b8b7b5afe4792ee2563ce220c"></a></em></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p367802265084842"><a name="p367802265084842"></a><a name="p367802265084842"></a><strong id="a3015a69b8b7b5afe4792ee2563ce220c_1"><a name="a3015a69b8b7b5afe4792ee2563ce220c_1"></a><a name="a3015a69b8b7b5afe4792ee2563ce220c_1"></a></strong> union {</p>
</td>
</tr>
<tr id="row903277367084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p982151517084842"><a name="p982151517084842"></a><a name="p982151517084842"></a>&nbsp;&nbsp;&nbsp;<a href="VideoTrackSourceInfo.md">VideoTrackSourceInfo</a>&nbsp;&nbsp;&nbsp;<a href="TrackSource.md#abee3acb91d3005141f11abd87c77aa83">videoInfo</a></p>
</td>
</tr>
<tr id="row2120553217084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1035570793084842"><a name="p1035570793084842"></a><a name="p1035570793084842"></a>&nbsp;&nbsp;&nbsp;<a href="AudioTrackSourceInfo.md">AudioTrackSourceInfo</a>&nbsp;&nbsp;&nbsp;<a href="TrackSource.md#a0cac47bdef450bfb8fd3b8ed882ef674">audioInfo</a></p>
</td>
</tr>
<tr id="row965636496084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1003010887084842"><a name="p1003010887084842"></a><a name="p1003010887084842"></a>&nbsp;&nbsp;&nbsp;<a href="DataTrackSourceInfo.md">DataTrackSourceInfo</a>&nbsp;&nbsp;&nbsp;<a href="TrackSource.md#a89cccaaf705df735a3ab8e9792564105">dataInfo</a></p>
</td>
</tr>
<tr id="row1952682130084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1401404177084842"><a name="p1401404177084842"></a><a name="p1401404177084842"></a><em id="a3015a69b8b7b5afe4792ee2563ce220c_2"><a name="a3015a69b8b7b5afe4792ee2563ce220c_2"></a><a name="a3015a69b8b7b5afe4792ee2563ce220c_2"></a></em>trackSourceInfo </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p389095578084842"><a name="p389095578084842"></a><a name="p389095578084842"></a>}&nbsp;</p>
<p id="p16172861084842"><a name="p16172861084842"></a><a name="p16172861084842"></a>Defines detailed information about different types of stream sources. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1698337440084842"></a>

## **Field Documentation**<a name="section1974120722084842"></a>

## audioInfo<a name="a0cac47bdef450bfb8fd3b8ed882ef674"></a>

```
[AudioTrackSourceInfo](AudioTrackSourceInfo.md) TrackSource::audioInfo
```

 **Description:**

Audio stream. For details, see  [AudioTrackSourceInfo](AudioTrackSourceInfo.md). 

## dataInfo<a name="a89cccaaf705df735a3ab8e9792564105"></a>

```
[DataTrackSourceInfo](DataTrackSourceInfo.md) TrackSource::dataInfo
```

 **Description:**

Data stream. For details, see  [DataTrackSourceInfo](DataTrackSourceInfo.md) 

## trackSourceType<a name="a39d729c668eddbf6b8403b7364e74b61"></a>

```
[TrackSourceType](Format.md#ga953bc46f95d7b2d8866838d792f8f6aa) TrackSource::trackSourceType
```

 **Description:**

Stream source type. For details, see  [TrackSourceType](Format.md#ga953bc46f95d7b2d8866838d792f8f6aa) 

## videoInfo<a name="abee3acb91d3005141f11abd87c77aa83"></a>

```
[VideoTrackSourceInfo](VideoTrackSourceInfo.md) TrackSource::videoInfo
```

 **Description:**

Video stream. For details, see  [VideoTrackSourceInfo](VideoTrackSourceInfo.md). 

