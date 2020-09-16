# OHOS::Media::StreamCallback<a name="ZH-CN_TOPIC_0000001054479577"></a>

## **Overview**<a name="section469107709093532"></a>

**Related Modules:**

[MultiMedia\_MediaCommon](MultiMedia_MediaCommon.md)

**Description:**

Provides functions to obtain the address of a buffer memory and write the filled buffers into the playback queue. You need to implement the  **[StreamCallback](OHOS-Media-StreamCallback.md)**  functions in a player object. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section891520998093532"></a>

## Public Types<a name="pub-types"></a>

<a name="table1379170230093532"></a>
<table><thead align="left"><tr id="row1204165414093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1298451830093532"><a name="p1298451830093532"></a><a name="p1298451830093532"></a>Public Type Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p227328659093532"><a name="p227328659093532"></a><a name="p227328659093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1357337895093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p408322624093532"><a name="p408322624093532"></a><a name="p408322624093532"></a><a href="MultiMedia_MediaCommon.md#ga6f4847f443de5cdf3641386011335e21">BufferFlags</a> : uint32_t { &nbsp;&nbsp;<a href="MultiMedia_MediaCommon.md#gga6f4847f443de5cdf3641386011335e21ac1a3ce4ddd663c55f87a8275ccf285ad">STREAM_FLAG_SYNCFRAME</a> = 1, <a href="MultiMedia_MediaCommon.md#gga6f4847f443de5cdf3641386011335e21afd0d977a6a5d48657d694c9acb8ac2b5">STREAM_FLAG_CODECCONFIG</a> = 2, <a href="MultiMedia_MediaCommon.md#gga6f4847f443de5cdf3641386011335e21aa76ecb4ee6077a1ad3ceac569b875487">STREAM_FLAG_EOS</a> = 4, <a href="MultiMedia_MediaCommon.md#gga6f4847f443de5cdf3641386011335e21a29e735a1e41790c24cc9ac9e7342dd2a">STREAM_FLAG_PARTIAL_FRAME</a> = 8, &nbsp;&nbsp;<a href="MultiMedia_MediaCommon.md#gga6f4847f443de5cdf3641386011335e21a8b2c1f065ce398ac48bac2b8e62e481b">STREAM_FLAG_ENDOFFRAME</a> = 16, <a href="MultiMedia_MediaCommon.md#gga6f4847f443de5cdf3641386011335e21a9001c389dd39f08025e76ae2872fad02">STREAM_FLAG_MUXER_DATA</a> = 32 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1826002100093532"><a name="p1826002100093532"></a><a name="p1826002100093532"></a>Enumerates buffer types of stream sources. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1470441378093532"></a>
<table><thead align="left"><tr id="row1960562158093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p280666664093532"><a name="p280666664093532"></a><a name="p280666664093532"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p692400253093532"><a name="p692400253093532"></a><a name="p692400253093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row906499042093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p28755524093532"><a name="p28755524093532"></a><a name="p28755524093532"></a><a href="MultiMedia_MediaCommon.md#ga8f897b8b2d5baf06e15accfeb97892ae">GetBuffer</a> (size_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1402970513093532"><a name="p1402970513093532"></a><a name="p1402970513093532"></a>virtual uint8_t *&nbsp;</p>
<p id="p1094987232093532"><a name="p1094987232093532"></a><a name="p1094987232093532"></a>Obtains the virtual address of a buffer memory block based on its index. </p>
</td>
</tr>
<tr id="row210011413093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p409138702093532"><a name="p409138702093532"></a><a name="p409138702093532"></a><a href="MultiMedia_MediaCommon.md#gaa62705632557f47f9fd9632157e53a21">QueueBuffer</a> (size_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>, size_t offset, size_t size, int64_t timestampUs, uint32_t flags)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p181696310093532"><a name="p181696310093532"></a><a name="p181696310093532"></a>virtual void&nbsp;</p>
<p id="p575845046093532"><a name="p575845046093532"></a><a name="p575845046093532"></a>Writes the filled buffer memory block into the player memory. </p>
</td>
</tr>
<tr id="row504220373093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1120357178093532"><a name="p1120357178093532"></a><a name="p1120357178093532"></a><a href="MultiMedia_MediaCommon.md#ga29f8c86744bda61f84920654c5f40df0">SetParameters</a> (const <a href="OHOS-Media-Format.md">Format</a> &amp;params)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2000203206093532"><a name="p2000203206093532"></a><a name="p2000203206093532"></a>virtual void&nbsp;</p>
<p id="p1627319576093532"><a name="p1627319576093532"></a><a name="p1627319576093532"></a>Sets additional information about a stream. </p>
</td>
</tr>
</tbody>
</table>

