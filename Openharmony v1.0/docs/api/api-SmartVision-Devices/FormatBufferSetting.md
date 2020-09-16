# FormatBufferSetting<a name="ZH-CN_TOPIC_0000001054799597"></a>

## **Overview**<a name="section1047185445093530"></a>

**Related Modules:**

[Format](Format.md)

**Description:**

Defines the buffer configuration. 

If  **maxSize**  and  **maxDurationMs**  are valid at the same time, the smaller value is used as the upper limit for the buffer.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1325472422093530"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1757548532093530"></a>
<table><thead align="left"><tr id="row1254227807093530"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p360596573093530"><a name="p360596573093530"></a><a name="p360596573093530"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1213970763093530"><a name="p1213970763093530"></a><a name="p1213970763093530"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row456653161093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p595310106093530"><a name="p595310106093530"></a><a name="p595310106093530"></a><a href="FormatBufferSetting.md#a9f23c583e5dd21894f4ffce0589ed179">maxSize</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1653924248093530"><a name="p1653924248093530"></a><a name="p1653924248093530"></a>int64_t&nbsp;</p>
</td>
</tr>
<tr id="row74347930093530"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1467996997093530"><a name="p1467996997093530"></a><a name="p1467996997093530"></a><a href="FormatBufferSetting.md#a6cf1da1ecc6506d134027d3a057cf968">maxDurationMs</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1324532317093530"><a name="p1324532317093530"></a><a name="p1324532317093530"></a>int64_t&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section305341950093530"></a>

## **Field Documentation**<a name="section2090642988093530"></a>

## maxDurationMs<a name="a6cf1da1ecc6506d134027d3a057cf968"></a>

```
int64_t FormatBufferSetting::maxDurationMs
```

 **Description:**

Maximum duration of a media file 

## maxSize<a name="a9f23c583e5dd21894f4ffce0589ed179"></a>

```
int64_t FormatBufferSetting::maxSize
```

 **Description:**

Maximum buffer size 

