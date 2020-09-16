# SubtitleTrackInfo<a name="EN-US_TOPIC_0000001055678132"></a>

## **Overview**<a name="section1162109046093537"></a>

**Related Modules:**

[Format](format.md)

**Description:**

Defines subtitle stream information. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1854808027093537"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table667818964093537"></a>
<table><thead align="left"><tr id="row1387054851093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p450220337093537"><a name="p450220337093537"></a><a name="p450220337093537"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1670804223093537"><a name="p1670804223093537"></a><a name="p1670804223093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1641854632093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p352900465093537"><a name="p352900465093537"></a><a name="p352900465093537"></a><a href="subtitletrackinfo.md#a8f0db970e60f19d5deb18fbbdbc7ea28">format</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p679887282093537"><a name="p679887282093537"></a><a name="p679887282093537"></a><a href="format.md#gadac45ce4731516c262292c15433439b3">SubtitleFormat</a> </p>
</td>
</tr>
<tr id="row342940954093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1601083183093537"><a name="p1601083183093537"></a><a name="p1601083183093537"></a><a href="subtitletrackinfo.md#a71f5455adc1defa10b4f292dede95f58">charSet</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1638937567093537"><a name="p1638937567093537"></a><a name="p1638937567093537"></a>uint32_t </p>
</td>
</tr>
<tr id="row654950707093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1840499981093537"><a name="p1840499981093537"></a><a name="p1840499981093537"></a><a href="subtitletrackinfo.md#abb57b361b445696d272cf8bb54cb12d0">language</a> [<a href="format.md#gac2d2d077edb8e9bb9f85ab6350015c5b">FORMAT_MAX_LANGUAGE_NUM</a>][<a href="format.md#gaa70508bb1089c99f9aa3d59fcbdfa8eb">FORMAT_LANGUAGE_LEN</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2083829945093537"><a name="p2083829945093537"></a><a name="p2083829945093537"></a>char </p>
</td>
</tr>
<tr id="row1500367991093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1087957239093537"><a name="p1087957239093537"></a><a name="p1087957239093537"></a><a href="subtitletrackinfo.md#a7d5cefc1e9f402657c2f9c2950688472">originalFrameWidth</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1325418658093537"><a name="p1325418658093537"></a><a name="p1325418658093537"></a>uint16_t </p>
</td>
</tr>
<tr id="row862987752093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1914503094093537"><a name="p1914503094093537"></a><a name="p1914503094093537"></a><a href="subtitletrackinfo.md#a70c3d91bb8b6d8e79a22fe0206130a2f">originalFrameHeight</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p622491950093537"><a name="p622491950093537"></a><a name="p622491950093537"></a>uint16_t </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section2128784002093537"></a>

## **Field Documentation**<a name="section1681909984093537"></a>

## charSet<a name="a71f5455adc1defa10b4f292dede95f58"></a>

```
uint32_t SubtitleTrackInfo::charSet
```

 **Description:**

Character encoding format 

## format<a name="a8f0db970e60f19d5deb18fbbdbc7ea28"></a>

```
[SubtitleFormat](format.md#gadac45ce4731516c262292c15433439b3) SubtitleTrackInfo::format
```

 **Description:**

Subtitle encoding and decoding format. For details, see  [SubtitleFormat](format.md#gadac45ce4731516c262292c15433439b3) 

## language<a name="abb57b361b445696d272cf8bb54cb12d0"></a>

```
char SubtitleTrackInfo::language[[FORMAT_MAX_LANGUAGE_NUM](format.md#gac2d2d077edb8e9bb9f85ab6350015c5b)][[FORMAT_LANGUAGE_LEN](format.md#gaa70508bb1089c99f9aa3d59fcbdfa8eb)]
```

 **Description:**

Subtitle language 

## originalFrameHeight<a name="a70c3d91bb8b6d8e79a22fe0206130a2f"></a>

```
uint16_t SubtitleTrackInfo::originalFrameHeight
```

 **Description:**

Height of the original image. This variable is valid for the image subtitle. 

## originalFrameWidth<a name="a7d5cefc1e9f402657c2f9c2950688472"></a>

```
uint16_t SubtitleTrackInfo::originalFrameWidth
```

 **Description:**

Width of the original image. This variable is valid for the image subtitle. 

