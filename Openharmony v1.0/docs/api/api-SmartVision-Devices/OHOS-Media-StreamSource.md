# OHOS::Media::StreamSource<a name="ZH-CN_TOPIC_0000001054879546"></a>

## **Overview**<a name="section25430804093532"></a>

**Related Modules:**

[MultiMedia\_MediaCommon](MultiMedia_MediaCommon.md)

**Description:**

Provides functions related to the stream source for upper-layer applications. 

After the  **SetSource**  function is called, the player invokes  [OnBufferAvailable](MultiMedia_MediaCommon.md#gaaebd4fe9df44b434f410aec32cf23467)  to notify your application of the buffer memory block that can be filled with data. The player can invoke  [SetStreamCallback](MultiMedia_MediaCommon.md#ga078516891396a86226c945e02c79c1f5)  to register a callback for your application. For example, the  **GetBuffer**  callback obtains the address of the buffer block and sends the filled buffer memory block to the player. The buffer memory block is allocated and processed on the player.  **[StreamSource](OHOS-Media-StreamSource.md)**is available only for the media source of the  **SOURCE\_TYPE\_STREAM**  type. For details, see  [SourceType](Format.md#ga3ae727773c367ac1041d72ac770a0ab1). 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section178024689093532"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table604178437093532"></a>
<table><thead align="left"><tr id="row2073141114093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1109619490093532"><a name="p1109619490093532"></a><a name="p1109619490093532"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1843627956093532"><a name="p1843627956093532"></a><a name="p1843627956093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row717410358093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1832986306093532"><a name="p1832986306093532"></a><a name="p1832986306093532"></a><a href="MultiMedia_MediaCommon.md#gaaebd4fe9df44b434f410aec32cf23467">OnBufferAvailable</a> (size_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>, size_t offset, size_t size)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1217160767093532"><a name="p1217160767093532"></a><a name="p1217160767093532"></a>virtual void&nbsp;</p>
<p id="p2070504676093532"><a name="p2070504676093532"></a><a name="p2070504676093532"></a>Notifies your application of the information about the buffer memory block that can be filled with data. </p>
</td>
</tr>
<tr id="row721469379093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1043998234093532"><a name="p1043998234093532"></a><a name="p1043998234093532"></a><a href="MultiMedia_MediaCommon.md#ga078516891396a86226c945e02c79c1f5">SetStreamCallback</a> (const std::shared_ptr&lt; <a href="OHOS-Media-StreamCallback.md">StreamCallback</a> &gt; &amp;callback)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p763226835093532"><a name="p763226835093532"></a><a name="p763226835093532"></a>virtual void&nbsp;</p>
<p id="p2139923513093532"><a name="p2139923513093532"></a><a name="p2139923513093532"></a>Sets a callback function for your application. </p>
</td>
</tr>
</tbody>
</table>

