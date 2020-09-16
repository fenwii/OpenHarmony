# surface\_type.h<a name="ZH-CN_TOPIC_0000001054879512"></a>

## **Overview**<a name="section598602689093527"></a>

**Related Modules:**

[Surface](Surface.md)

**Description:**

Provides the capabilities of setting shared memory parameters. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1683909942093527"></a>

## Enumerations<a name="enum-members"></a>

<a name="table738453042093527"></a>
<table><thead align="left"><tr id="row1197400887093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p181520215093527"><a name="p181520215093527"></a><a name="p181520215093527"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2099628718093527"><a name="p2099628718093527"></a><a name="p2099628718093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1911626343093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p163207284093527"><a name="p163207284093527"></a><a name="p163207284093527"></a><a href="Surface.md#ga16d4d4f73d748455e45924ffbdd1e891">OHOS::BufferConsumerUsage</a> { &nbsp;&nbsp;<a href="Surface.md#gga16d4d4f73d748455e45924ffbdd1e891a59c0ac95bd7994b6eda43b34f59c237b">OHOS::BUFFER_CONSUMER_USAGE_SORTWARE</a> = 0, <a href="Surface.md#gga16d4d4f73d748455e45924ffbdd1e891abe0bc63ca1799ca0b2182e908780da7b">OHOS::BUFFER_CONSUMER_USAGE_HARDWARE</a>, <a href="Surface.md#gga16d4d4f73d748455e45924ffbdd1e891a93eebf8af6f264494a57771865c90b08">OHOS::BUFFER_CONSUMER_USAGE_HARDWARE_CONSUMER_CACHE</a>, <a href="Surface.md#gga16d4d4f73d748455e45924ffbdd1e891a7a31f6403b7aa4ba989e7cd5b3eb7a06">OHOS::BUFFER_CONSUMER_USAGE_HARDWARE_PRODUCER_CACHE</a>, &nbsp;&nbsp;<a href="Surface.md#gga16d4d4f73d748455e45924ffbdd1e891a56aa1994f77d06504c40421f6555f1cf">OHOS::BUFFER_CONSUMER_USAGE_MAX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1177014950093527"><a name="p1177014950093527"></a><a name="p1177014950093527"></a>Enumerates shared memory usage scenarios, including physically contiguous memory and virtual memory. </p>
</td>
</tr>
<tr id="row1635115539093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1157019265093527"><a name="p1157019265093527"></a><a name="p1157019265093527"></a><a href="Surface.md#gaa191d6e3b92a0f527744d43e056ae025">OHOS::ImagePixelFormat</a> { &nbsp;&nbsp;<a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a9690a1d8cf1d21fcad76876f122a12ab">OHOS::IMAGE_PIXEL_FORMAT_NONE</a> = 0, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025aff11848c6a38afb3afdcbeaec2400055">OHOS::IMAGE_PIXEL_FORMAT_RGB565</a> = 101, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a9cf3bfb5153d8cf23f4c0d3bb9cc4f43">OHOS::IMAGE_PIXEL_FORMAT_ARGB1555</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025ad4774f5ba15cf25a3d0951f5986ab0d5">OHOS::IMAGE_PIXEL_FORMAT_RGB888</a>, &nbsp;&nbsp;<a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a1a18541878a09cbca269918a7ef4796f">OHOS::IMAGE_PIXEL_FORMAT_ARGB8888</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025affcb2a4b4832e3c33789f9e8efffe7b0">OHOS::IMAGE_PIXEL_FORMAT_YUYV</a> = 201, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a4ec5bc985a5f49f26178ab18c074cfa6">OHOS::IMAGE_PIXEL_FORMAT_YVYU</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a098b93504ac8e11c4d5d488930187f37">OHOS::IMAGE_PIXEL_FORMAT_UYVY</a>, &nbsp;&nbsp;<a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a0e242cad6dae11690013c6771b80fc9b">OHOS::IMAGE_PIXEL_FORMAT_VYUY</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025ab690ca190de1686041f0d0c320427b1c">OHOS::IMAGE_PIXEL_FORMAT_AYUV</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025aa4e3c6974a86c29cf707f371ad1b0b49">OHOS::IMAGE_PIXEL_FORMAT_YUV410</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a3c4c9612392a81fa2d1d305d08064146">OHOS::IMAGE_PIXEL_FORMAT_YVU410</a>, &nbsp;&nbsp;<a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025acc77b028562f155f1099de249b7bffae">OHOS::IMAGE_PIXEL_FORMAT_YUV411</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a99cb00970d669d9ba2ac1049d19c60e4">OHOS::IMAGE_PIXEL_FORMAT_YVU411</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025acf60892315d8aee3d421f75d70db796f">OHOS::IMAGE_PIXEL_FORMAT_YUV420</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025ac3dfd6c2f350194d2a525a14d9e72b71">OHOS::IMAGE_PIXEL_FORMAT_YVU420</a>, &nbsp;&nbsp;<a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025ae87be6ce296c907d99381d1db48c288f">OHOS::IMAGE_PIXEL_FORMAT_YUV422</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025ab33d1df10479e267ca7c3cb6102d8dbb">OHOS::IMAGE_PIXEL_FORMAT_YVU422</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a7f2a90344e786071a49db0da82b201e4">OHOS::IMAGE_PIXEL_FORMAT_YUV444</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a4e18880bae5fa08cbd510f23f549087d">OHOS::IMAGE_PIXEL_FORMAT_YVU444</a>, &nbsp;&nbsp;<a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a93a54b97b83f6e042c993d045be27a33">OHOS::IMAGE_PIXEL_FORMAT_NV12</a> = 301, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025ab7d0f6b75189a47fdf613bbbeaa3b628">OHOS::IMAGE_PIXEL_FORMAT_NV21</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a5fd084cc32d1fdbe8017fd210a7e3ffa">OHOS::IMAGE_PIXEL_FORMAT_NV16</a>, <a href="Surface.md#ggaa191d6e3b92a0f527744d43e056ae025a77a0063a555db3ca68a304e494f094cf">OHOS::IMAGE_PIXEL_FORMAT_NV61</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1402708779093527"><a name="p1402708779093527"></a><a name="p1402708779093527"></a>Enumerates a pixel format. </p>
</td>
</tr>
</tbody>
</table>

