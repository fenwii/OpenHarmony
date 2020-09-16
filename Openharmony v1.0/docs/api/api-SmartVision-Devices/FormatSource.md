# FormatSource<a name="ZH-CN_TOPIC_0000001054879530"></a>

## **Overview**<a name="section1841736801084835"></a>

**Related Modules:**

[Format](Format.md)

**Description:**

Defines the demuxer data source. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section364047497084835"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1943431407084835"></a>
<table><thead align="left"><tr id="row1613403606084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p472802673084835"><a name="p472802673084835"></a><a name="p472802673084835"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1966326085084835"><a name="p1966326085084835"></a><a name="p1966326085084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row738113921084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p320719351084835"><a name="p320719351084835"></a><a name="p320719351084835"></a><a href="FormatSource.md#abdb0407f672c5e9af53eae7726c2e7b2">type</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1000720170084835"><a name="p1000720170084835"></a><a name="p1000720170084835"></a><a href="Format.md#ga3ae727773c367ac1041d72ac770a0ab1">SourceType</a>&nbsp;</p>
</td>
</tr>
<tr id="row86011175084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p10681898084835"><a name="p10681898084835"></a><a name="p10681898084835"></a><em id="a70fb2123cb4e5c7719118e8db94c13af"><a name="a70fb2123cb4e5c7719118e8db94c13af"></a><a name="a70fb2123cb4e5c7719118e8db94c13af"></a></em></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1959493610084835"><a name="p1959493610084835"></a><a name="p1959493610084835"></a><strong id="a70fb2123cb4e5c7719118e8db94c13af_1"><a name="a70fb2123cb4e5c7719118e8db94c13af_1"></a><a name="a70fb2123cb4e5c7719118e8db94c13af_1"></a></strong> union {</p>
</td>
</tr>
<tr id="row495325954084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1805485256084835"><a name="p1805485256084835"></a><a name="p1805485256084835"></a>&nbsp;&nbsp;&nbsp;int&nbsp;&nbsp;&nbsp;<a href="FormatSource.md#adc25d5e97f531f36d7f129136abb483d">fd</a></p>
</td>
</tr>
<tr id="row2075347042084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p881547841084835"><a name="p881547841084835"></a><a name="p881547841084835"></a>&nbsp;&nbsp;&nbsp;char&nbsp;&nbsp;&nbsp;<a href="FormatSource.md#adc0405c090069d6bbf2017995710a0f8">url</a> [<a href="Format.md#ga1ac54dd3b9b49c1800b5f502a87650be">URL_LEN</a>]</p>
</td>
</tr>
<tr id="row1791639536084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">&nbsp;&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1422545273084835"><a name="p1422545273084835"></a><a name="p1422545273084835"></a>&nbsp;&nbsp;&nbsp;<a href="BufferStream.md">BufferStream</a> *&nbsp;&nbsp;&nbsp;<a href="FormatSource.md#a33f6a121891b692ef246011e0415f3fe">stream</a></p>
</td>
</tr>
<tr id="row692051822084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1831026417084835"><a name="p1831026417084835"></a><a name="p1831026417084835"></a><em id="a70fb2123cb4e5c7719118e8db94c13af_2"><a name="a70fb2123cb4e5c7719118e8db94c13af_2"></a><a name="a70fb2123cb4e5c7719118e8db94c13af_2"></a></em></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p376002917084835"><a name="p376002917084835"></a><a name="p376002917084835"></a>};&nbsp;</p>
<p id="p1172510347084835"><a name="p1172510347084835"></a><a name="p1172510347084835"></a>Defines information about different types of data sources. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1920740890084835"></a>

## **Field Documentation**<a name="section783899785084835"></a>

## fd<a name="adc25d5e97f531f36d7f129136abb483d"></a>

```
int FormatSource::fd
```

 **Description:**

Local file descriptor 

## stream<a name="a33f6a121891b692ef246011e0415f3fe"></a>

```
[BufferStream](BufferStream.md)* FormatSource::stream
```

 **Description:**

Pointer to the function for reading buffer stream data 

## type<a name="abdb0407f672c5e9af53eae7726c2e7b2"></a>

```
[SourceType](Format.md#ga3ae727773c367ac1041d72ac770a0ab1) FormatSource::type
```

 **Description:**

Data source type. For details, see  [SourceType](Format.md#ga3ae727773c367ac1041d72ac770a0ab1). 

## url<a name="adc0405c090069d6bbf2017995710a0f8"></a>

```
char FormatSource::url[[URL_LEN](Format.md#ga1ac54dd3b9b49c1800b5f502a87650be)]
```

 **Description:**

Network URI or local file path. The maximum length is specified by  **URL\_LEN**. 

