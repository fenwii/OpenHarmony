# FormatOutputConfig<a name="ZH-CN_TOPIC_0000001055198128"></a>

## **Overview**<a name="section1995986596093530"></a>

**Related Modules:**

[Format](Format.md)

**Description:**

Defines the muxer output configuration. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1083989366093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table435518432093530"></a>
<table><thead align="left"><tr id="row1470264234093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p112886687093530"><a name="p112886687093530"></a><a name="p112886687093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p629509750093530"><a name="p629509750093530"></a><a name="p629509750093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1804199517093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p524525647093530"><a name="p524525647093530"></a><a name="p524525647093530"></a><a href="FormatOutputConfig.md#afdd8b72dc265610db88ed9893f673bb4">type</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p752015605093530"><a name="p752015605093530"></a><a name="p752015605093530"></a><a href="Format.md#ga4e0517338e6c4a31a2addafc06d4f3a3">OutputType</a>&nbsp;</p>
</td>
</tr>
<tr id="row1800943811093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1789278700093530"><a name="p1789278700093530"></a><a name="p1789278700093530"></a><a href="FormatOutputConfig.md#a594a547d286a447681e983582c671a6a">format</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1939153468093530"><a name="p1939153468093530"></a><a name="p1939153468093530"></a><a href="Format.md#gaeb712c6c6c0a8af0dfd79f451ecb9277">OutputFormat</a>&nbsp;</p>
</td>
</tr>
<tr id="row906880794093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1969804671093530"><a name="p1969804671093530"></a><a name="p1969804671093530"></a><a href="FormatOutputConfig.md#a06757484a244827b91183a40f636b2de">fd</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p870683150093530"><a name="p870683150093530"></a><a name="p870683150093530"></a>int32_t&nbsp;</p>
</td>
</tr>
<tr id="row178593871093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1041455370093530"><a name="p1041455370093530"></a><a name="p1041455370093530"></a><a href="FormatOutputConfig.md#a9ce729405e9489d021713689ed1ca17b">url</a> [<a href="Format.md#ga1ac54dd3b9b49c1800b5f502a87650be">URL_LEN</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p60161405093530"><a name="p60161405093530"></a><a name="p60161405093530"></a>char&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section937346252093530"></a>

## **Field Documentation**<a name="section442684155093530"></a>

## fd<a name="a06757484a244827b91183a40f636b2de"></a>

```
int32_t FormatOutputConfig::fd
```

 **Description:**

File descriptor 

## format<a name="a594a547d286a447681e983582c671a6a"></a>

```
[OutputFormat](Format.md#gaeb712c6c6c0a8af0dfd79f451ecb9277) FormatOutputConfig::format
```

 **Description:**

File format 

## type<a name="afdd8b72dc265610db88ed9893f673bb4"></a>

```
[OutputType](Format.md#ga4e0517338e6c4a31a2addafc06d4f3a3) FormatOutputConfig::type
```

 **Description:**

Output type. For details, see  [OutputType](Format.md#ga4e0517338e6c4a31a2addafc06d4f3a3). 

## url<a name="a9ce729405e9489d021713689ed1ca17b"></a>

```
char FormatOutputConfig::url[[URL_LEN](Format.md#ga1ac54dd3b9b49c1800b5f502a87650be)]
```

 **Description:**

File path. For details, see  [URL\_LEN](Format.md#ga1ac54dd3b9b49c1800b5f502a87650be). 

